#include "HSSV.hpp"

#include <glm/gtx/transform.hpp>
#include "geGL/StaticCalls.h"
#include "MultiplicityCoding.hpp"
#include "HighResolutionTimer.hpp"

#include <fstream>

#include "OctreeSerializer.hpp"
#include "OctreeCompressor.hpp"
#include "OctreeSidesDrawer.hpp"
#include "CpuSidesDrawer.hpp"
#include "OctreeWireframeDrawer.hpp"
#include <iomanip>

HSSV::HSSV(
	std::shared_ptr<Model> model,
	const HSSVParams& hssvParams,
	std::shared_ptr<ge::gl::Texture> const& shadowMask,
	std::shared_ptr<ge::gl::Texture> const& depth,
	ShadowVolumesParams const& params) : ShadowVolumes(shadowMask, depth, params)
{
	_params = hssvParams;
	_model = model;
}

HSSV::~HSSV()
{}

bool HSSV::init()
{
	printf("Renderer: %s %s\n", glGetString(GL_VENDOR), glGetString(GL_RENDERER));

	auto const vertices = _loadVertices(_model);
	_createAdjacency(vertices);

	_loadGpuEdges(_edges);

	_compressionLevel = _params.noCompression ? 0 : (int)(log(BitmaskTypeSizeBits) / log(8));

	//Build test
	if (_params.doBuildTest)
	{
		_buildTest();
		exit(0);
	}

	//Edge test
	if(_params.doEdgeTest)
	{
		_edgeTest();
		exit(0);
	}

	_octreeSpace = _calculateOctreeSpace(vertices, _params.sceneAABBscale);


	if (!_params.forceOctreeBuild)
	{
		_loadOctreeFromFile(_model->modelFilename, _params.maxOctreeLevel, _compressionLevel, _params.sceneAABBscale);
	}

	if(_octree==nullptr)
	{
		_createOctree(_params.maxOctreeLevel, _octreeSpace);
		_storeOctree(_params.sceneAABBscale);
	}

	if(_params.drawOctree)
	{
		_wireframeDrawer = std::make_unique<OctreeWireframeDrawer>();
		_wireframeDrawer->init(_octree);
	}

	if(_params.drawFromCpu)
	{
		_octreeSidesDrawer = std::make_shared<CpuSidesDrawer>(_visitor, _edges);
	}
	else
	{
		_octreeSidesDrawer = std::make_shared<OctreeSidesDrawer>(_visitor, _params.workgroupSize, DrawingMethod(_params.potentialDrawingMethod), DrawingMethod(_params.silhouetteDrawingMethod));
	}

	if (!_octreeSidesDrawer->init(_gpuEdges))
	{
		return false;
	}

	_capsDrawer = std::make_shared<GSCaps>(_edges);

	return true;
}

std::vector<float> HSSV::_loadVertices(std::shared_ptr<Model> const model)
{
	std::vector<float>vertices;
	model->getVertices(vertices);
	return vertices;
}


void HSSV::_createAdjacency(std::vector<float> const& verts3f)
{
	size_t const nofTriangles = verts3f.size() / (verticesPerTriangle*componentsPerVertex3D);
	size_t const dataSize = verts3f.size();
	float* verts = new float[dataSize]; //this will leak...
	memcpy(verts, verts3f.data(), dataSize * sizeof(float));
	_edges = std::make_shared<Adjacency const>(verts, nofTriangles, 2);
}

AABB HSSV::_calculateOctreeSpace(std::vector<float> const& verts3f, glm::vec3 scale)
{
	AABB sceneBbox = _getSceneAabb(verts3f);
	_fixSceneAABB(sceneBbox);

	auto minP = sceneBbox.getMinPoint();
	auto maxP = sceneBbox.getMaxPoint();
	std::cout << "Scene AABB " << minP.x << ", " << minP.y << ", " << minP.z << " Max: " << maxP.x << ", " << maxP.y << ", " << maxP.z << "\n";

	AABB octreeSpace;
	octreeSpace.setCenterExtents(sceneBbox.getCenterPoint(), sceneBbox.getExtents()*scale);

	return octreeSpace;
}

void HSSV::_loadOctreeFromFile(std::string const& filename, uint32_t octreeLevel, uint32_t compressionLevel, glm::vec3 sceneScale)
{
	OctreeSerializer serializer;
	_octree = serializer.loadFromFile(filename, sceneScale, octreeLevel, compressionLevel);
	if(_octree)
	{
		_visitor = std::make_shared<OctreeVisitor>(_octree);
	}
}

void HSSV::_storeOctree(glm::vec3 const& sceneScale)
{
	OctreeSerializer serializer;
	serializer.storeToFile(_model->modelFilename, sceneScale, _octree);
}

void HSSV::_createOctree(uint32_t maxOctreeLevel, AABB const& octreeSpace, bool verbose)
{
	_octree = std::make_shared<Octree>(maxOctreeLevel, octreeSpace);
	_visitor = std::make_shared<OctreeVisitor>(_octree);

	HighResolutionTimer t;
	t.reset();

	const bool useGpuCompression = std::is_same<unsigned char, BitmaskType>::value && !_params.noCompression;
	_visitor->addEdges(_edges, _gpuEdges, useGpuCompression && !_params.noCompression, _params.maxGpuMemoryToUsePerBuffer, _params.potSpeculativeFactor, _params.silSpeculativeFactor);

	if (verbose)
	{
		const auto dt = t.getElapsedTimeFromLastQuerySeconds();
		std::cout << "Building octree took " << dt << " seconds.\n";
	}

	if (!useGpuCompression && !_params.noCompression)
	{
		if (verbose)
		{
			std::cout << "Compressing on CPU...\n";
		}

		OctreeCompressor compressor;
		compressor.compressOctree(_visitor, _compressionLevel);

		if (verbose)
		{
			std::cout << "Compresing octree took " << t.getElapsedTimeFromLastQuerySeconds() << "s\n";
		}
	}

	_visitor->getOctree()->setCompressionLevel(_compressionLevel);
	_visitor->shrinkOctree();

	if (verbose)
	{
		std::cout << "Final size: " << _octree->getOctreeSizeBytes() / 1024 / 1024 << " MB\n";
		std::cout << "Shrinking octree took " << t.getElapsedTimeFromLastQuerySeconds() << "s\n";
	}
}

void HSSV::_buildTest()
{
	const std::vector<float> sceneScales = { 1, 2, 4, 8, 16 };
	const std::vector<uint32_t> octreeLevels = { 3, 4, 5 };
	const uint32_t nofIterations = 3;

	std::ofstream saveFile;
	saveFile.open(std::string("buildTest_") + _model->modelFilename + ".txt");

	std::vector<float> vertices3f;
	_model->getVertices(vertices3f);
	AABB const sceneBbox = _getSceneAabb(vertices3f);
	AABB octreeSpace;

	for (const auto depth : octreeLevels)
	{
		for (const auto scale : sceneScales)
		{
			octreeSpace.setCenterExtents(sceneBbox.getCenterPoint(), sceneBbox.getExtents()*glm::vec3(scale, scale, scale));

			HighResolutionTimer t;
			double buildTime = 0;
			for (uint32_t i = 0; i < nofIterations; ++i)
			{
				_octree.reset();
				_visitor.reset();
				_createOctree(depth, octreeSpace, false);
				
				buildTime += t.getElapsedTimeSeconds();
			}

			buildTime /= double(nofIterations);

			const size_t octreeSizeMB = _octree->getOctreeSizeBytes() / 1024ull / 1024ull;

			size_t const nofVoxels = _octree->getTotalNumNodes();
			size_t potSizes = 0, silSizes = 0;
			for (unsigned int i = _octree->getLevelFirstNodeID(_octree->getDeepestLevel()); i<nofVoxels; ++i)
			{
				std::vector<uint32_t> silhouetteEdges;
				std::vector<uint32_t> potentialEdges;
				_visitor->getSilhouttePotentialEdgesFromNodeUp(potentialEdges, silhouetteEdges, i);

				potSizes += potentialEdges.size();
				silSizes += silhouetteEdges.size();
			}

			potSizes /= nofVoxels;
			silSizes /= nofVoxels;

			/*
			//Get NofEdges
			const int lowestNode = _visitor->getLowestNodeIndexFromPoint(hssvParams.initialLightPos);
			std::vector<uint32_t> silhouetteEdges;
			std::vector<uint32_t> potentialEdges;
			_visitor->getSilhouttePotentialEdgesFromNodeUp(potentialEdges, silhouetteEdges, lowestNode);
			*/
			std::string str;
			//str = "depth " + std::to_string(depth) + " scale " + std::to_string(scale) + " buildTime " + std::to_string(buildTime) + " sizeMB " + std::to_string(octreeSizeMB) + " potEdges " + std::to_string(potentialEdges.size()) + " silEdges " + std::to_string(silhouetteEdges.size()) + "\n";
			saveFile << std::scientific << depth << std::setw(15) << scale << std::setw(15) << buildTime << std::setw(10) << octreeSizeMB << std::setw(15) << potSizes << std::setw(15) << silSizes << "\n";
			//saveFile << str;
			std::cerr << str;
		}
	}

	std::cerr << "---END OF BUILD TEST---\n";

	saveFile.close();
}

void HSSV::_edgeTest()
{
	const std::vector<float> sceneScales = { 1, 2, 4, 8, 16 };
	const std::vector<uint32_t> octreeLevels = { 3, 4, 5 };

	std::ofstream saveFile;
	saveFile.open(std::string("silTest_") + _model->modelFilename + ".txt");

	std::vector<float> vertices3f;
	_model->getVertices(vertices3f);
	AABB const sceneBbox = _getSceneAabb(vertices3f);
	AABB octreeSpace;

	for (const auto depth : octreeLevels)
	{
		for (const auto scale : sceneScales)
		{
			_octree.reset();
			_visitor.reset();
			auto const sceneScale = glm::vec3(scale, scale, scale);

			_loadOctreeFromFile(_model->modelFilename, depth, _compressionLevel, sceneScale);

			if (_octree == nullptr)
			{
				octreeSpace.setCenterExtents(sceneBbox.getCenterPoint(), sceneBbox.getExtents()*sceneScale);
				_createOctree(depth, octreeSpace, false);
				_storeOctree(sceneScale);
			}

			_visitor = std::make_shared<OctreeVisitor>(_octree);
			printf("Depth %d scale %d\n", depth, int(scale));
			size_t const nofAllVoxels = _octree->getTotalNumNodes();
			float silPercent = 0;

			for (unsigned int i = _octree->getLevelFirstNodeID(_octree->getDeepestLevel()); i<nofAllVoxels; ++i)
			{
				std::vector<uint32_t> silhouetteEdges;
				std::vector<uint32_t> potentialEdges;
				_visitor->getSilhouttePotentialEdgesFromNodeUp(potentialEdges, silhouetteEdges, i);

				std::vector<int> ed;
				ed.reserve(potentialEdges.size() + silhouetteEdges.size());
				ed.insert(ed.end(), silhouetteEdges.begin(), silhouetteEdges.end());
				glm::vec3 const lightPos = _octree->getNode(i)->volume.getCenterPoint();
				for (const auto edge : potentialEdges)
				{
					const int multiplicity = GeometryOps::calcEdgeMultiplicity(_edges, edge, lightPos);
					if (multiplicity != 0)
					{
						ed.push_back(edge);
					}
				}

				float const dp = (100.0f*float(silhouetteEdges.size()) / float(ed.size()));
				silPercent += dp;
			}

			float const tt = float(_octree->getNumNodesInLevel(_octree->getDeepestLevel()));
			silPercent /= tt;

			saveFile << std::scientific << depth << std::setw(15) << scale << std::setw(15) << silPercent << "\n";
		}
	}

	saveFile.close();
	exit(0);
}

void HSSV::drawCaps(glm::vec4 const& lightPosition, glm::mat4 const& viewMatrix, glm::mat4 const& projectionMatrix)
{
	_capsDrawer->drawCaps(lightPosition, viewMatrix, projectionMatrix);
}

void HSSV::drawSides(glm::vec4 const& lightPosition, glm::mat4 const& viewMatrix, glm::mat4 const& projectionMatrix)
{
	const glm::mat4 mvp = projectionMatrix * viewMatrix;

	_octreeSidesDrawer->drawSides(mvp, lightPosition);
}

AABB HSSV::_getSceneAabb(std::vector<float> const& verts)
{
	AABB bbox;
	bbox.updateWithVerticesVec3(verts.data(), verts.size());

	return bbox;
}

void HSSV::_fixSceneAABB(AABB& bbox)
{
	float ex, ey, ez;
	bbox.getExtents(ex, ey, ez);

	const float minSize = 0.01f;

	if(ex<minSize)
	{
		auto min = bbox.getMinPoint();
		auto max = bbox.getMaxPoint();

		bbox.setMinMaxPoints(min - glm::vec3(minSize, 0, 0), max + glm::vec3(minSize, 0, 0));

		std::cout << "Fixing X AABB dimension\n";
	}

	if(ey<minSize)
	{
		auto min = bbox.getMinPoint();
		auto max = bbox.getMaxPoint();

		bbox.setMinMaxPoints(min - glm::vec3(0, minSize, 0), max + glm::vec3(0, minSize, 0));

		std::cout << "Fixing Y AABB dimension\n";
	}

	if(ez<minSize)
	{
		auto min = bbox.getMinPoint();
		auto max = bbox.getMaxPoint();

		bbox.setMinMaxPoints(min - glm::vec3(0, 0, minSize), max + glm::vec3(0, 0, minSize));

		std::cout << "Fixing Z AABB dimension\n";
	}
}

void HSSV::_loadGpuEdges(AdjacencyType edges)
{
	_gpuEdges = std::make_shared<GpuEdges>();
	_gpuEdges->_edges = std::make_shared<ge::gl::Buffer>();
	_gpuEdges->_oppositeVertices = std::make_shared<ge::gl::Buffer>();

	std::vector<float> serializedEdges;
	std::vector<glm::vec3> serializedOppositeVertices;

	_serializeEdges(edges, serializedEdges, serializedOppositeVertices);

	_gpuEdges->_edges->alloc(serializedEdges.size() * sizeof(float), serializedEdges.data(), GL_STATIC_READ);
	_gpuEdges->_oppositeVertices->alloc(serializedOppositeVertices.size() * 3 * sizeof(float), serializedOppositeVertices.data(), GL_STATIC_READ);
}

void HSSV::_serializeEdges(AdjacencyType edges, std::vector<float>& serializedEdges, std::vector<glm::vec3>& serializedOppositeVertices)
{
	const auto nofEdges = edges->getNofEdges();

	const glm::vec3* vertices = reinterpret_cast<const glm::vec3*>(edges->getVertices());

	for (size_t edgeIndex = 0; edgeIndex<nofEdges; ++edgeIndex)
	{
		glm::vec3 v1 = vertices[edges->getEdgeVertexA(edgeIndex) / 3];
		glm::vec3 v2 = vertices[edges->getEdgeVertexB(edgeIndex) / 3];

		const uint32_t nofOpposite = uint32_t(edges->getNofOpposite(edgeIndex));
		const uint32_t starting_index = uint32_t(serializedOppositeVertices.size()) * 3;

		serializedEdges.push_back(v1.x); serializedEdges.push_back(v1.y); serializedEdges.push_back(v1.z);
		serializedEdges.push_back(v2.x); serializedEdges.push_back(v2.y); serializedEdges.push_back(v2.z);
		serializedEdges.push_back(*((float*)&nofOpposite));
		serializedEdges.push_back(*((float*)&starting_index));

		for (uint32_t i = 0; i < nofOpposite; ++i)
		{
			serializedOppositeVertices.push_back(vertices[edges->getOpposite(edgeIndex, i) / 3]);
		}
	}
}

void HSSV::setTimeStamper(std::shared_ptr<TimeStamp> stamper)
{
	timeStamp = stamper;
	if (_octreeSidesDrawer)
	{
		_octreeSidesDrawer->setStamper(stamper);
	}
}

void HSSV::drawUser(glm::vec4 const&lightPosition, glm::mat4 const&viewMatrix, glm::mat4 const&projectionMatrix)
{
	if (_params.drawOctree)
	{
		ge::gl::glEnable(GL_DEPTH_TEST);
		ge::gl::glDepthMask(GL_FALSE);

		_wireframeDrawer->drawWireframe(projectionMatrix * viewMatrix);

		ge::gl::glDepthMask(GL_TRUE);
	}
}
