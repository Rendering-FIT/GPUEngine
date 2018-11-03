#include "OctreeSidesDrawer.hpp"
#include "GenerateSidesProgram.hpp"
#include <geGL/StaticCalls.h>
#include "MultiplicityCoding.hpp"
#include "../CSSVShaders.h"
#include "OctreeTraversalShader.hpp"
#include "GenerateSidesDataOnGpuProgram.hpp"
#include "GenerateSidesDataOnGpuProgram2.hpp"
#include "../TimeStamp.h"


#define MAX_MULTIPLICITY 2

#define TRAVERSAL_SHADER_2

OctreeSidesDrawer::OctreeSidesDrawer(std::shared_ptr<OctreeVisitor> visitor, unsigned int workgroupSize, DrawingMethod potential, DrawingMethod silhouette) : 
	_octreeVisitor(visitor), _workgroupSize(workgroupSize), _potentialDrawingMethod(potential), _silhouetteDrawingMethod(silhouette)
{
}

void OctreeSidesDrawer::setStamper(std::shared_ptr<TimeStamp> stamper)
{
	_timer = stamper;
}


#define USE_GPU_OCTREE

void OctreeSidesDrawer::_initShaders()
{
	if(_silhouetteDrawingMethod==DrawingMethod::TS)
		_silhouetteSidesTsProgram = std::make_shared<ge::gl::Program>(
			std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, sidesVS),
			std::make_shared<ge::gl::Shader>(GL_TESS_CONTROL_SHADER, sidesTCS),
			std::make_shared<ge::gl::Shader>(GL_TESS_EVALUATION_SHADER, silhouetteSidesTES),
			std::make_shared<ge::gl::Shader>(GL_GEOMETRY_SHADER, 
			"#version 450 core\n",
			ge::gl::Shader::define("MAX_VERTICES", int32_t(3*MAX_MULTIPLICITY)),
			sidesGS)
		);

	if (_silhouetteDrawingMethod == DrawingMethod::GS)
		_silhouetteSidesGsProgram = std::make_shared<ge::gl::Program>(
			std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, sidesVS),
			std::make_shared<ge::gl::Shader>(GL_GEOMETRY_SHADER, 
			"#version 450 core\n",
			ge::gl::Shader::define("MAX_VERTICES", int32_t(3 * MAX_MULTIPLICITY)),
			silhouetteSidesGS)
		);

	if(_potentialDrawingMethod == DrawingMethod::TS)
		_potentialTsProgram = std::make_shared<ge::gl::Program>(
			std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, sidesVS),
			std::make_shared<ge::gl::Shader>(GL_TESS_CONTROL_SHADER, sidesTCS),
			std::make_shared<ge::gl::Shader>(GL_TESS_EVALUATION_SHADER, potentialSidesTES),
			std::make_shared<ge::gl::Shader>(GL_GEOMETRY_SHADER,
			"#version 450 core\n",
			ge::gl::Shader::define("MAX_VERTICES", int32_t(3 * MAX_MULTIPLICITY)),
			sidesGS)
		);

	if (_potentialDrawingMethod == DrawingMethod::GS)
		_potentialGsProgram = std::make_shared<ge::gl::Program>(
			std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, sidesVS),
			std::make_shared<ge::gl::Shader>(GL_GEOMETRY_SHADER,
			"#version 450 core\n",
			ge::gl::Shader::define("MAX_VERTICES", int32_t(3 * MAX_MULTIPLICITY)),
			potentialSidesGS)
		);

	if(_silhouetteDrawingMethod == DrawingMethod::CS || _potentialDrawingMethod == DrawingMethod::CS)
		_drawSidesProgram = std::make_shared<ge::gl::Program>(
			std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, drawVPSrc),
			std::make_shared<ge::gl::Shader>(GL_TESS_CONTROL_SHADER, drawCPSrc),
			std::make_shared<ge::gl::Shader>(GL_TESS_EVALUATION_SHADER, drawEPSrc)
			);

	if(_potentialDrawingMethod == DrawingMethod::CS)
		_testAndGenerateSidesProgram = std::make_shared<ge::gl::Program>(
			std::make_shared<ge::gl::Shader>(GL_COMPUTE_SHADER,
			"#version 450 core\n",
			ge::gl::Shader::define("WORKGROUP_SIZE_X", _workgroupSize),
			testAndGenerateSidesCS)
		);

	if (_silhouetteDrawingMethod == DrawingMethod::CS)
		_generateSidesProgram = std::make_shared<ge::gl::Program>(
			std::make_shared<ge::gl::Shader>(GL_COMPUTE_SHADER,
			"#version 450 core\n",
			ge::gl::Shader::define("WORKGROUP_SIZE_X", _workgroupSize),
			generateSidesCS)
		);

	/*
	_gpuOctreeTraversalProgramSingleBuffer = std::make_shared<ge::gl::Program>(
		std::make_shared<ge::gl::Shader>(GL_COMPUTE_SHADER,
			"#version 450 core\n",
			ge::gl::Shader::define("WORKGROUP_SIZE_X", _workgroupSize),
			ge::gl::Shader::define("DEEPEST_LEVEL", _octreeVisitor->getOctree()->getDeepestLevel()),
			edgeTraversalShaderBody)
		);
	*/
}

//#define USE_VERSION_1
//Version 1 has been proven slower
#include <fstream>
bool OctreeSidesDrawer::_generateLoadGpuTraversalShader()
{
#ifdef USE_VERSION_1
	std::string shaderBody = genTraversalComputeShader(_lastNodePerEdgeBuffer, _octreeVisitor->getOctree(), _workgroupSize);
#else
	std::string shaderBody = genTraversalComputeShader2Compress(_lastNodePerEdgeBuffer, _octreeVisitor->getOctree(), _workgroupSize);//genTraversalComputeShader2(_lastNodePerEdgeBuffer, _octreeVisitor->getOctree(), _workgroupSize);
	/*
	//std::ifstream t("C:\\Users\\Jofo\\Desktop\\tmp.glsl");
	std::ifstream t("C:\\Users\\ikobrtek\\Desktop\\tmpShaderCompress.glsl");
	std::string shaderBody((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());
	//*/
#endif
	
	_gpuOctreeTraversalProgramMultipleBuffers = std::make_shared<ge::gl::Program>(
		std::make_shared<ge::gl::Shader>(GL_COMPUTE_SHADER, shaderBody) );

	return _gpuOctreeTraversalProgramMultipleBuffers->getValidateStatus();
}

void OctreeSidesDrawer::init(std::shared_ptr<GpuEdges> gpuEdges)
{
	_initShaders();

	_initBuffers();

	_loadOctreeToGpu();
#ifdef TRAVERSAL_SHADER_2
	if (!_generateLoadGpuTraversalShader2())
#elif defined(TRAVERSAL_SHADER_3)
	if (!_generateLoadGpuTraversalShader3())
#else
	if (!_generateLoadGpuTraversalShader())
#endif
		return;
	_gpuEdges = gpuEdges;
}

void OctreeSidesDrawer::_initBuffers()
{
	size_t maxPotentialEdges, maxSilhouetteEdges, maxEdges, maxPath;
	_getMaxPossibleEdgeCountInTraversal(maxPotentialEdges, maxSilhouetteEdges, maxEdges, maxPath);
	_maxNofEdgesInVoxel = maxEdges;
	_maxNofEdgesPath = maxPath;

	_edgesIdsToGenerate = std::make_shared<ge::gl::Buffer>(maxSilhouetteEdges * sizeof(uint32_t), nullptr);
	_edgesIdsToTestAndGenerate = std::make_shared<ge::gl::Buffer>(maxPotentialEdges * sizeof(uint32_t), nullptr);

	if (_potentialDrawingMethod != DrawingMethod::CS || _silhouetteDrawingMethod != DrawingMethod::CS)
		_dummyVAO = std::make_shared<ge::gl::VertexArray>();

	const uint32_t indirectBuffer[4] = { 0, 1, 0, 0 };
	_indirectDrawBufferPotentialCS = std::make_shared<ge::gl::Buffer>(4 * sizeof(uint32_t), indirectBuffer);
	_indirectDrawBufferSilhouetteCS = std::make_shared<ge::gl::Buffer>(4 * sizeof(uint32_t), indirectBuffer);

	if (_potentialDrawingMethod == DrawingMethod::CS)
	{
		_potentialEdgeCsVBO = std::make_shared<ge::gl::Buffer>(MAX_MULTIPLICITY * maxPotentialEdges * 4 * sizeof(float), nullptr);

		_potentialSidesCsVAO = std::make_shared<ge::gl::VertexArray>();
		_potentialSidesCsVAO->addAttrib(_potentialEdgeCsVBO, 0, 4, GL_FLOAT);
	}

	if (_silhouetteDrawingMethod == DrawingMethod::CS)
	{
		_silhouetteEdgeCsVBO = std::make_shared<ge::gl::Buffer>(MAX_MULTIPLICITY * maxSilhouetteEdges * 4 * sizeof(float), nullptr);

		_silhouetteSidesCsVAO = std::make_shared<ge::gl::VertexArray>();
		_silhouetteSidesCsVAO->addAttrib(_silhouetteEdgeCsVBO, 0, 4, GL_FLOAT);
	}

	const uint32_t indirectData[] = { 0, 1, 1 };
	_indirectDispatchCsPotential = std::make_shared<ge::gl::Buffer>(3 * sizeof(uint32_t), indirectData);
	_indirectDispatchCsSilhouette = std::make_shared<ge::gl::Buffer>(3 * sizeof(uint32_t), indirectData);

	_compressedNodesInfoIndexingBuffer = std::make_shared<ge::gl::Buffer>(_octreeVisitor->getOctree()->getTotalNumNodes() * sizeof(uint32_t));
	_compressedNodesInfoBuffer = std::make_shared<ge::gl::Buffer>();
}

void OctreeSidesDrawer::_breakCompressionIdToUintsAndPush(const BitmaskType& id, std::vector<uint32_t>& vectorToStore) const
{
	if (std::is_same<unsigned char, BitmaskType>::value)
		vectorToStore.push_back(id);
	else
	{
		const unsigned int nofUints = BitmaskTypeSizeBits / 32;
		const uint32_t* val = reinterpret_cast<const uint32_t*>(&id);

		for (unsigned int i = 0; i < nofUints; ++i)
			vectorToStore.push_back(val[i]);
	}
}

void OctreeSidesDrawer::_processSubBuffer(
	const std::unordered_map<BitmaskType, std::vector<uint32_t>>::value_type& subBuffer,
	std::vector<uint32_t>& compressedNodesInfo,
	std::vector<uint32_t>& nofEdgesPrefixSums,
	uint32_t* gpuMappedBuffer
)
{
	const auto subBufferSize = subBuffer.second.size();
	assert(subBufferSize!=0);

	memcpy(gpuMappedBuffer + nofEdgesPrefixSums[nofEdgesPrefixSums.size() - 1], subBuffer.second.data(), subBufferSize * sizeof(uint32_t));
	
	const auto startIndex = nofEdgesPrefixSums.size() - 1;//nofEdgesPrefixSums[nofEdgesPrefixSums.size() - 1];
	
	nofEdgesPrefixSums.push_back(nofEdgesPrefixSums[nofEdgesPrefixSums.size() - 1] + subBufferSize);

	//Push compression ID
	_breakCompressionIdToUintsAndPush(subBuffer.first, compressedNodesInfo);

	//Push starting index
	compressedNodesInfo.push_back(startIndex);
}

void OctreeSidesDrawer::_loadOctreeToGpu()
{
	const unsigned int nofVoxels = _octreeVisitor->getOctree()->getTotalNumNodes();
	
	uint64_t remainingSize = _octreeVisitor->getOctree()->getOctreeSizeBytes();
	const uint64_t maxBufferSize = 2ull * 1024ull * 1024ull * 1024ull; //2GB
	unsigned int currentNode = 0;

	std::vector<uint32_t> nofEdgesPrefixSums;
	std::vector<uint32_t> compressedNodesInfo;
	std::vector<uint32_t> compressedNodesInfoIndexing;

	nofEdgesPrefixSums.reserve(nofVoxels + 1);
	compressedNodesInfoIndexing.reserve(nofVoxels);

	auto octree = _octreeVisitor->getOctree();

	while(remainingSize>0)
	{
		const uint64_t currentSize = remainingSize > maxBufferSize ? maxBufferSize : remainingSize;
		remainingSize -= currentSize;

		nofEdgesPrefixSums.push_back(0);

		std::shared_ptr<ge::gl::Buffer> buffer = std::make_shared<ge::gl::Buffer>(currentSize, nullptr);
		uint32_t* dataPtr = reinterpret_cast<uint32_t*>(buffer->map(GL_WRITE_ONLY));
		
		uint64_t currentNumIndices = 0;

		while(currentNode<nofVoxels)
		{
			auto node = octree->getNode(currentNode);

			uint64_t sz = _octreeVisitor->getNofAllIndicesInNode(currentNode);

			if ((sz + currentNumIndices)*sizeof(uint32_t) > currentSize)
				break;

			currentNode++;

			compressedNodesInfoIndexing.push_back(compressedNodesInfo.size());
			compressedNodesInfo.push_back(node->edgesMayCastMap.size());
			compressedNodesInfo.push_back(node->edgesAlwaysCastMap.size());

			for (const auto& subBuffer : node->edgesMayCastMap)
				_processSubBuffer(subBuffer, compressedNodesInfo, nofEdgesPrefixSums, dataPtr);

			for (const auto& subBuffer : node->edgesAlwaysCastMap)
				_processSubBuffer(subBuffer, compressedNodesInfo, nofEdgesPrefixSums, dataPtr);

			currentNumIndices += sz;
		}

		buffer->unmap();

		_gpuOctreeBuffers.push_back(buffer);
		_lastNodePerEdgeBuffer.push_back(currentNode);
	}

	_voxelNofPotentialSilhouetteEdgesPrefixSum = std::make_shared<ge::gl::Buffer>(nofEdgesPrefixSums.size() * sizeof(uint32_t), nofEdgesPrefixSums.data());
	_compressedNodesInfoBuffer->alloc(compressedNodesInfo.size() * sizeof(uint32_t));
	_compressedNodesInfoBuffer->setData(compressedNodesInfo.data());
	_compressedNodesInfoIndexingBuffer->setData(compressedNodesInfoIndexing.data());
}

void OctreeSidesDrawer::_getMaxPossibleEdgeCountInTraversal(size_t& potential, size_t& silhouette, size_t& maxInVoxel, size_t& maxPath) const
{
	potential = 0;
	silhouette = 0;
	maxInVoxel = 0;
	maxPath = 0;

	const unsigned int maxLevel = _octreeVisitor->getOctree()->getDeepestLevel();
	for (unsigned int i = 0; i <= maxLevel; ++i)
	{
		size_t pot = 0, silh = 0;
		_getMaximumNofEdgesInLevel(i, pot, silh);

		maxInVoxel = std::max(pot, maxInVoxel);
		maxInVoxel = std::max(silh, maxInVoxel);

		maxPath += pot;
		maxPath += silh;

		potential += pot;
		silhouette += silh;
	}
}

void OctreeSidesDrawer::_getNofEdgesInNode(unsigned int nodeId, size_t& potential, size_t& silhouette) const
{
	potential = silhouette = 0;
	const auto node = _octreeVisitor->getOctree()->getNode(nodeId);
	for (const auto& buffer : node->edgesAlwaysCastMap)
		silhouette += buffer.second.size();

	for (const auto& buffer : node->edgesMayCastMap)
		potential += buffer.second.size();
}

void OctreeSidesDrawer::_getMaximumNofEdgesInLevel(unsigned int level, size_t& potential, size_t& silhouette) const
{
	potential = 0;
	silhouette = 0;

	const auto startingIndex = _octreeVisitor->getOctree()->getLevelFirstNodeID(level);
	const auto levelSize = ipow(OCTREE_NUM_CHILDREN, level);

	for(unsigned int i=0; i<levelSize; ++i)
	{
		size_t nodePot = 0, nodeSil = 0;
		_getNofEdgesInNode(startingIndex + i, nodePot, nodeSil);
		potential = std::max(potential, nodePot);
		silhouette = std::max(silhouette,nodeSil);
	}
}

void OctreeSidesDrawer::_getMaxNofBuffersPotSil(uint32_t& pot, uint32_t& sil)
{
	pot = sil = 0;

	const unsigned int maxLevel = _octreeVisitor->getOctree()->getDeepestLevel();
	for (unsigned int level = 0; level <= maxLevel; ++level)
	{
		const auto startingIndex = _octreeVisitor->getOctree()->getLevelFirstNodeID(level);
		const auto levelSize = ipow(OCTREE_NUM_CHILDREN, level);
		size_t p = 0, s = 0;
		for (unsigned int i = 0; i < levelSize; ++i)
		{
			size_t nodePot = 0, nodeSil = 0;
			_getNofEdgesInNode(startingIndex + i, nodePot, nodeSil);
			p = std::max(p, nodePot);
			s = std::max(s, nodeSil);
		}

		pot += p;
		sil += s;
	}
}

void OctreeSidesDrawer::drawSides(const glm::mat4& mvp, const glm::vec4& light)
{
	const auto cellIndex = _octreeVisitor->getLowestNodeIndexFromPoint(glm::vec3(light));

	if(cellIndex<0)
	{
		static bool printOnce = false;

		if(!printOnce)
		{
			std::cout << "Light " << light.x << ", " << light.y << ", " << light.z << " is out of range\n";
			printOnce = true;
		}
	}
	else
	{
		//static bool once = true;
		//if(once)
		//_loadPotentialSilhouetteEdgesFromVoxelGPU(cellIndex);
		//once = false;
#ifdef TRAVERSAL_SHADER_2
		_getPotentialSilhouetteEdgesGpu2(cellIndex);
#elif defined(TRAVERSAL_SHADER_3)
		_getPotentialSilhouetteEdgesGpu3(cellIndex);
#else
		_getPotentialSilhouetteEdgesGpu(cellIndex);
#endif
		if (_silhouetteDrawingMethod == DrawingMethod::CS && _potentialDrawingMethod == DrawingMethod::CS)
			_drawSidesCS(mvp, light, cellIndex);
		else
		{
			switch (_silhouetteDrawingMethod)
			{
			case DrawingMethod::GS:
				_drawSidesFromSilhouetteEdgesGS(mvp, light, cellIndex); break;
			case DrawingMethod::TS:
				_drawSidesFromSilhouetteEdgesTS(mvp, light, cellIndex); break;
			case DrawingMethod::CS:
				_drawSidesFromSilhouetteEdgesCS(mvp, light, cellIndex); break;
			}

			switch (_potentialDrawingMethod)
			{
			case DrawingMethod::GS:
				_drawSidesFromPotentialEdgesGS(mvp, light, cellIndex); break;
			case DrawingMethod::TS:
				_drawSidesFromPotentialEdgesTS(mvp, light, cellIndex); break;
			case DrawingMethod::CS:
				_drawSidesFromPotentialEdgesCS(mvp, light, cellIndex); break;
			}
		}
	}

	_lastFrameCellIndex = cellIndex;
}
/*
unsigned int OctreeSidesDrawer::_loadEdgesFromIdUpGetNof(unsigned cellContainingLightId, bool loadSilhouette)
{
	const int deepestLevel = _octreeVisitor->getOctree()->getDeepestLevel();

	size_t currentPosition = 0;
	int currentCell = cellContainingLightId;
	unsigned int numLoaded = 0;
	
	for(int i = deepestLevel; i>=0; --i)
	{
		const auto n = _octreeVisitor->getOctree()->getNode(currentCell);
		const std::vector<uint32_t>& edges = loadSilhouette ? n->edgesAlwaysCast : n->edgesMayCast;
		const size_t edgesSize = edges.size() * sizeof(uint32_t);
		
		if (edgesSize)
		{
			if (loadSilhouette)
				_edgesIdsToGenerate->setData(edges.data(), edgesSize, currentPosition);
			else
				_edgesIdsToTestAndGenerate->setData(edges.data(), edgesSize, currentPosition);

			currentPosition += edgesSize;
		}

		currentCell = _octreeVisitor->getOctree()->getNodeParent(currentCell);
		numLoaded += edges.size();
	}
	
	return numLoaded;
}
*/
void OctreeSidesDrawer::_drawSidesFromSilhouetteEdgesTS(const glm::mat4& mvp, const glm::vec4& lightPos, unsigned int cellContainingLightId)
{
	if (_timer) _timer->stamp("");
#ifndef USE_GPU_OCTREE
	if (_lastFrameCellIndex != int(cellContainingLightId))
	{
		_nofSilhouetteEdgesToDraw = _loadEdgesFromIdUpGetNof(cellContainingLightId, true);
		std::cout << "Acquiring " << _nofSilhouetteEdgesToDraw << " silhouette edges\n";
	}

	if (!_nofSilhouetteEdgesToDraw)
	return;
#endif

	auto err = ge::gl::glGetError();
	assert(err == GL_NO_ERROR);

	_silhouetteSidesTsProgram->use();
	_silhouetteSidesTsProgram->setMatrix4fv("mvp", glm::value_ptr(mvp))->set4fv("lightPosition", glm::value_ptr(lightPos));

	_dummyVAO->bind();

	_gpuEdges->_edges->bindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_edgesIdsToGenerate->bindBase(GL_SHADER_STORAGE_BUFFER, 1);

	ge::gl::glPatchParameteri(GL_PATCH_VERTICES, 1);
#ifdef USE_GPU_OCTREE
	_indirectDrawBufferSilhouetteCS->bind(GL_DRAW_INDIRECT_BUFFER);
	ge::gl::glDrawArraysIndirect(GL_PATCHES, nullptr);
	_indirectDrawBufferSilhouetteCS->unbind(GL_DRAW_INDIRECT_BUFFER);
#else
	ge::gl::glDrawArrays(GL_PATCHES, 0, _nofSilhouetteEdgesToDraw);
#endif
	
	_gpuEdges->_edges->unbindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_edgesIdsToGenerate->unbindBase(GL_SHADER_STORAGE_BUFFER, 1);

	_dummyVAO->unbind();

	if (_timer) _timer->stamp("SilhouetteEdges");

	err = ge::gl::glGetError();
	assert(err == GL_NO_ERROR);
}

void OctreeSidesDrawer::_drawSidesFromSilhouetteEdgesGS(const glm::mat4& mvp, const glm::vec4& lightPos, unsigned cellContainingLightId)
{
	if (_timer) _timer->stamp("");
#ifndef USE_GPU_OCTREE	
	if (_lastFrameCellIndex != int(cellContainingLightId))
	{
		_nofSilhouetteEdgesToDraw = _loadEdgesFromIdUpGetNof(cellContainingLightId, true);
		std::cout << "Acquiring " << _nofSilhouetteEdgesToDraw << " silhouette edges\n";
	}

	if (!_nofSilhouetteEdgesToDraw)
		return;
#endif
	
	_silhouetteSidesGsProgram->use();
	_silhouetteSidesGsProgram->setMatrix4fv("mvp", glm::value_ptr(mvp))->set4fv("lightPosition", glm::value_ptr(lightPos));

	_dummyVAO->bind();

	_gpuEdges->_edges->bindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_edgesIdsToGenerate->bindBase(GL_SHADER_STORAGE_BUFFER, 1);
	
#ifdef USE_GPU_OCTREE
	_indirectDrawBufferSilhouetteCS->bind(GL_DRAW_INDIRECT_BUFFER);
	ge::gl::glDrawArraysIndirect(GL_POINTS, 0);
	_indirectDrawBufferSilhouetteCS->unbind(GL_DRAW_INDIRECT_BUFFER);
#else
	ge::gl::glDrawArrays(GL_POINTS, 0, _nofSilhouetteEdgesToDraw);
#endif
	
	_gpuEdges->_edges->unbindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_edgesIdsToGenerate->unbindBase(GL_SHADER_STORAGE_BUFFER, 1);

	_dummyVAO->unbind();

	if (_timer) _timer->stamp("SilhouetteEdges");
}

void OctreeSidesDrawer::_drawSidesFromSilhouetteEdgesCS(const glm::mat4& mvp, const glm::vec4& lightPos, unsigned int cellContainingLightId)
{
	if (_timer) _timer->stamp("");
	_generateSidesFromSilhouetteCS(lightPos, cellContainingLightId);
	if (_timer) _timer->stamp("SilhouetteEdges");
	ge::gl::glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT | GL_COMMAND_BARRIER_BIT);

	_drawSidesProgram->use();
	_drawSidesProgram->setMatrix4fv("mvp", glm::value_ptr(mvp))->set4fv("lightPosition", glm::value_ptr(lightPos));

	_silhouetteSidesCsVAO->bind();
	_indirectDrawBufferSilhouetteCS->bind(GL_DRAW_INDIRECT_BUFFER);

	ge::gl::glPatchParameteri(GL_PATCH_VERTICES, 2);
	ge::gl::glDrawArraysIndirect(GL_PATCHES, nullptr);

	_indirectDrawBufferSilhouetteCS->unbind(GL_DRAW_INDIRECT_BUFFER);
	_silhouetteSidesCsVAO->unbind();

	assert(ge::gl::glGetError() == GL_NO_ERROR);
}

void OctreeSidesDrawer::_drawSidesFromPotentialEdgesTS(const glm::mat4& mvp, const glm::vec4& lightPos, unsigned cellContainingLightId)
{
	if (_timer) _timer->stamp("");
#ifndef USE_GPU_OCTREE
	if (_lastFrameCellIndex != int(cellContainingLightId))
	{
		_nofPotentialEdgesToDraw = _loadEdgesFromIdUpGetNof(cellContainingLightId, false);
		std::cout << "Acquiring " << _nofPotentialEdgesToDraw << " potential edges\n";
	}

	if (!_nofPotentialEdgesToDraw)
	return;
#endif
	assert(ge::gl::glGetError() == GL_NO_ERROR);

	_potentialTsProgram->use();
	_potentialTsProgram->setMatrix4fv("mvp", glm::value_ptr(mvp))->set4fv("lightPosition", glm::value_ptr(lightPos));

	_dummyVAO->bind();

	_gpuEdges->_edges->bindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_gpuEdges->_oppositeVertices->bindBase(GL_SHADER_STORAGE_BUFFER, 1);
	_edgesIdsToTestAndGenerate->bindBase(GL_SHADER_STORAGE_BUFFER, 2);
	
	ge::gl::glPatchParameteri(GL_PATCH_VERTICES, 1);

#ifdef USE_GPU_OCTREE
	_indirectDrawBufferPotentialCS->bind(GL_DRAW_INDIRECT_BUFFER);
	ge::gl::glDrawArraysIndirect(GL_PATCHES, 0);
	_indirectDrawBufferPotentialCS->unbind(GL_DRAW_INDIRECT_BUFFER);
#else
	ge::gl::glDrawArrays(GL_PATCHES, 0, _nofPotentialEdgesToDraw);
#endif
	
	_gpuEdges->_edges->unbindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_gpuEdges->_oppositeVertices->unbindBase(GL_SHADER_STORAGE_BUFFER, 1);
	_edgesIdsToTestAndGenerate->unbindBase(GL_SHADER_STORAGE_BUFFER, 2);

	_dummyVAO->unbind();
	
	if (_timer) _timer->stamp("PotentialEdges");

	assert(ge::gl::glGetError() == GL_NO_ERROR);
}

void OctreeSidesDrawer::_drawSidesFromPotentialEdgesGS(const glm::mat4& mvp, const glm::vec4& lightPos, unsigned cellContainingLightId)
{
	assert(ge::gl::glGetError() == GL_NO_ERROR);
#ifndef USE_GPU_OCTREE
	if (_lastFrameCellIndex != int(cellContainingLightId))
	{
		_nofPotentialEdgesToDraw = _loadEdgesFromIdUpGetNof(cellContainingLightId, false);
		std::cout << "Acquiring " << _nofPotentialEdgesToDraw << " potential edges\n";
	}

	if (!_nofPotentialEdgesToDraw)
		return;
#endif
	if (_timer) _timer->stamp("");
	_potentialGsProgram->use();
	_potentialGsProgram->setMatrix4fv("mvp", glm::value_ptr(mvp))->set4fv("lightPosition", glm::value_ptr(lightPos));

	_dummyVAO->bind();

	_gpuEdges->_edges->bindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_gpuEdges->_oppositeVertices->bindBase(GL_SHADER_STORAGE_BUFFER, 1);
	_edgesIdsToTestAndGenerate->bindBase(GL_SHADER_STORAGE_BUFFER, 2);
	
#ifdef USE_GPU_OCTREE
	_indirectDrawBufferPotentialCS->bind(GL_DRAW_INDIRECT_BUFFER);
	ge::gl::glDrawArraysIndirect(GL_POINTS, nullptr);
	_indirectDrawBufferPotentialCS->unbind(GL_DRAW_INDIRECT_BUFFER);
#else
	ge::gl::glDrawArrays(GL_POINTS, 0, _nofPotentialEdgesToDraw);
#endif

	
	_gpuEdges->_edges->unbindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_gpuEdges->_oppositeVertices->unbindBase(GL_SHADER_STORAGE_BUFFER, 1);
	_edgesIdsToTestAndGenerate->unbindBase(GL_SHADER_STORAGE_BUFFER, 2);

	_dummyVAO->unbind();

	if (_timer) _timer->stamp("PotentialEdges");

	assert(ge::gl::glGetError() == GL_NO_ERROR);
}

void OctreeSidesDrawer::_drawSidesFromPotentialEdgesCS(const glm::mat4& mvp, const glm::vec4& lightPos, unsigned cellContainingLightId)
{
	if (_timer) _timer->stamp("");
	_generateSidesFromPotentialCS(lightPos, cellContainingLightId);
	if (_timer) _timer->stamp("PotentialEdges");
	ge::gl::glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT | GL_COMMAND_BARRIER_BIT);

	_drawSidesProgram->use();
	_drawSidesProgram->setMatrix4fv("mvp", glm::value_ptr(mvp))->set4fv("lightPosition", glm::value_ptr(lightPos));

	_potentialSidesCsVAO->bind();
	_indirectDrawBufferPotentialCS->bind(GL_DRAW_INDIRECT_BUFFER);

	ge::gl::glPatchParameteri(GL_PATCH_VERTICES, 2);
	ge::gl::glDrawArraysIndirect(GL_PATCHES, nullptr);

	_indirectDrawBufferPotentialCS->unbind(GL_DRAW_INDIRECT_BUFFER);
	_potentialSidesCsVAO->unbind();

	assert(ge::gl::glGetError() == GL_NO_ERROR);
}

void OctreeSidesDrawer::_generateSidesFromPotentialCS(const glm::vec4& lightPos, unsigned cellContainingLightId)
{
	const uint32_t zero = 0;
	_indirectDrawBufferPotentialCS->setData(&zero, sizeof(uint32_t));

	_testAndGenerateSidesProgram->use();
	_testAndGenerateSidesProgram->set4fv("lightPosition", glm::value_ptr(lightPos));
	_gpuEdges->_edges->bindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_gpuEdges->_oppositeVertices->bindBase(GL_SHADER_STORAGE_BUFFER, 1);
	_edgesIdsToTestAndGenerate->bindBase(GL_SHADER_STORAGE_BUFFER, 2);
	_potentialEdgeCsVBO->bindBase(GL_SHADER_STORAGE_BUFFER, 3);
	_indirectDrawBufferPotentialCS->bindBase(GL_SHADER_STORAGE_BUFFER, 4);
	_indirectDispatchCsPotential->bindRange(GL_SHADER_STORAGE_BUFFER, 5, 0, sizeof(uint32_t));
	_indirectDispatchCsPotential->bind(GL_DISPATCH_INDIRECT_BUFFER);

	ge::gl::glDispatchComputeIndirect(0);

	_indirectDispatchCsPotential->unbind(GL_DISPATCH_INDIRECT_BUFFER);
	_gpuEdges->_edges->unbindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_gpuEdges->_oppositeVertices->unbindBase(GL_SHADER_STORAGE_BUFFER, 1);
	_edgesIdsToTestAndGenerate->unbindBase(GL_SHADER_STORAGE_BUFFER, 2);
	_potentialEdgeCsVBO->unbindBase(GL_SHADER_STORAGE_BUFFER, 3);
	_indirectDrawBufferPotentialCS->unbindBase(GL_SHADER_STORAGE_BUFFER, 4);
	_indirectDispatchCsPotential->unbindRange(GL_SHADER_STORAGE_BUFFER, 5);
}

void OctreeSidesDrawer::_generateSidesFromSilhouetteCS(const glm::vec4& lightPos, unsigned cellContainingLightId)
{
	const uint32_t zero = 0;
	_indirectDrawBufferSilhouetteCS->setData(&zero, sizeof(uint32_t));

	_generateSidesProgram->use();

	_gpuEdges->_edges->bindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_edgesIdsToGenerate->bindBase(GL_SHADER_STORAGE_BUFFER, 1);
	_silhouetteEdgeCsVBO->bindBase(GL_SHADER_STORAGE_BUFFER, 2);
	_indirectDrawBufferSilhouetteCS->bindBase(GL_SHADER_STORAGE_BUFFER, 3);
	_indirectDispatchCsSilhouette->bindRange(GL_SHADER_STORAGE_BUFFER, 5, 0, sizeof(uint32_t));
	_indirectDispatchCsSilhouette->bind(GL_DISPATCH_INDIRECT_BUFFER);

	ge::gl::glDispatchComputeIndirect(0);

	_indirectDispatchCsSilhouette->unbind(GL_DISPATCH_INDIRECT_BUFFER);
	_gpuEdges->_edges->bindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_edgesIdsToGenerate->bindBase(GL_SHADER_STORAGE_BUFFER, 1);
	_silhouetteEdgeCsVBO->bindBase(GL_SHADER_STORAGE_BUFFER, 2);
	_indirectDrawBufferSilhouetteCS->bindBase(GL_SHADER_STORAGE_BUFFER, 3);
	_indirectDispatchCsSilhouette->unbindRange(GL_SHADER_STORAGE_BUFFER, 5);
}

void OctreeSidesDrawer::_drawSidesCS(const glm::mat4& mvp, const glm::vec4& lightPos, unsigned cellContainingLightId)
{
	if (_timer) _timer->stamp("");
	_generateSidesFromPotentialCS(lightPos, cellContainingLightId);
	if (_timer) _timer->stamp("PotentialEdges");
	_generateSidesFromSilhouetteCS(lightPos, cellContainingLightId);
	if (_timer) _timer->stamp("SilhouetteEdges");
	ge::gl::glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT | GL_COMMAND_BARRIER_BIT);

	_drawSidesProgram->use();
	_drawSidesProgram->setMatrix4fv("mvp", glm::value_ptr(mvp))->set4fv("lightPosition", glm::value_ptr(lightPos));

	_potentialSidesCsVAO->bind();
	_indirectDrawBufferPotentialCS->bind(GL_DRAW_INDIRECT_BUFFER);

	ge::gl::glPatchParameteri(GL_PATCH_VERTICES, 2);
	ge::gl::glDrawArraysIndirect(GL_PATCHES, nullptr);

	_silhouetteSidesCsVAO->bind();
	_indirectDrawBufferSilhouetteCS->bind(GL_DRAW_INDIRECT_BUFFER);
	ge::gl::glDrawArraysIndirect(GL_PATCHES, nullptr);

	_silhouetteSidesCsVAO->unbind();
	_indirectDrawBufferSilhouetteCS->unbind(GL_DRAW_INDIRECT_BUFFER);
}
/*
void OctreeSidesDrawer::_loadPotentialSilhouetteEdgesFromVoxelGPU(unsigned int voxelId)
{
	assert(ge::gl::glGetError() == GL_NO_ERROR);

	const uint32_t zero = 0;
	_indirectDrawBufferPotentialCS->setData(&zero, sizeof(uint32_t), 0);
	_indirectDrawBufferSilhouetteCS->setData(&zero, sizeof(uint32_t), 0);

	_gpuOctreeTraversalProgramSingleBuffer->use();
	_gpuOctreeTraversalProgramSingleBuffer->set1ui("voxelIndex", voxelId);

	_voxelEdgeIndices->bindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_voxelNofPotentialSilhouetteEdgesPrefixSum->bindBase(GL_SHADER_STORAGE_BUFFER, 1);
	_edgesIdsToTestAndGenerate->bindBase(GL_SHADER_STORAGE_BUFFER, 2);
	_edgesIdsToGenerate->bindBase(GL_SHADER_STORAGE_BUFFER, 3);
	_indirectDrawBufferPotentialCS->bindRange(GL_SHADER_STORAGE_BUFFER, 4, 0, sizeof(uint32_t));
	_indirectDrawBufferSilhouetteCS->bindRange(GL_SHADER_STORAGE_BUFFER, 5, 0, sizeof(uint32_t));

	ge::gl::glDispatchCompute(ceil(_maxNofEdgesInVoxel / float(_workgroupSize)), 1, 1);

	_voxelEdgeIndices->unbindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_voxelNofPotentialSilhouetteEdgesPrefixSum->unbindBase(GL_SHADER_STORAGE_BUFFER, 1);
	_edgesIdsToTestAndGenerate->unbindBase(GL_SHADER_STORAGE_BUFFER, 2);
	_edgesIdsToGenerate->unbindBase(GL_SHADER_STORAGE_BUFFER, 3);
	_indirectDrawBufferPotentialCS->unbindRange(GL_SHADER_STORAGE_BUFFER, 4);
	_indirectDrawBufferSilhouetteCS->unbindRange(GL_SHADER_STORAGE_BUFFER, 5);

	assert(ge::gl::glGetError() == GL_NO_ERROR);
}
*/

#include <fstream>
void OctreeSidesDrawer::_getPotentialSilhouetteEdgesGpu(unsigned int lowestNodeContainingLight)
{
	if (_timer) _timer->stamp("");
	
	_gpuOctreeTraversalProgramMultipleBuffers->use();
	_gpuOctreeTraversalProgramMultipleBuffers->set1ui("cellContainingLight", lowestNodeContainingLight);

	std::shared_ptr<ge::gl::Buffer> nofPotentialEdgesBuffer;
	std::shared_ptr<ge::gl::Buffer> nofSilhouetteEdgesBuffer;

	if (_potentialDrawingMethod == DrawingMethod::CS)
		nofPotentialEdgesBuffer = _indirectDispatchCsPotential;
	else
		nofPotentialEdgesBuffer = _indirectDrawBufferPotentialCS;

	if (_silhouetteDrawingMethod == DrawingMethod::CS)
		nofSilhouetteEdgesBuffer = _indirectDispatchCsSilhouette;
	else
		nofSilhouetteEdgesBuffer = _indirectDrawBufferSilhouetteCS;

	const uint32_t zero = 0;
	nofPotentialEdgesBuffer->setData(&zero, sizeof(uint32_t), 0);
	nofSilhouetteEdgesBuffer->setData(&zero, sizeof(uint32_t), 0);

	unsigned int bindingPoint = 0;

	for (const auto b : _gpuOctreeBuffers)
		b->bindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);

	_voxelNofPotentialSilhouetteEdgesPrefixSum->bindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);

	nofPotentialEdgesBuffer->bindRange(GL_SHADER_STORAGE_BUFFER, bindingPoint++, 0, sizeof(uint32_t));
	nofSilhouetteEdgesBuffer->bindRange(GL_SHADER_STORAGE_BUFFER, bindingPoint++, 0, sizeof(uint32_t));
	_edgesIdsToTestAndGenerate->bindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	_edgesIdsToGenerate->bindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	_compressedNodesInfoBuffer->bindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	_compressedNodesInfoIndexingBuffer->bindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);

#ifdef USE_VERSION_1
	ge::gl::glDispatchCompute(ceil(float(_maxNofEdgesInVoxel) / float(_workgroupSize)), 1, 1);
#else
	ge::gl::glDispatchCompute(ceil(float(_maxNofEdgesPath)*0.6875 /float(_workgroupSize)), 1, 1);
#endif
	bindingPoint = 0;
	for (const auto b : _gpuOctreeBuffers)
		b->unbindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	
	_voxelNofPotentialSilhouetteEdgesPrefixSum->unbindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	nofPotentialEdgesBuffer->unbindRange(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	nofSilhouetteEdgesBuffer->unbindRange(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	_edgesIdsToTestAndGenerate->unbindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	_edgesIdsToGenerate->unbindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	_compressedNodesInfoBuffer->unbindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	_compressedNodesInfoIndexingBuffer->unbindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);

	ge::gl::glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT | GL_COMMAND_BARRIER_BIT);

	if (_timer) _timer->stamp("TraverseOctree");

	//DEBUG
	//Get data
	/*
	ge::gl::glFinish();
	uint32_t nofPot = 0, nofSil = 0;
	nofPotentialEdgesBuffer->getData(&nofPot, sizeof(uint32_t), 0);
	nofSilhouetteEdgesBuffer->getData(&nofSil, sizeof(uint32_t), 0);

	std::vector<uint32_t> pe, se;
	pe.resize(nofPot);
	se.resize(nofSil);

	if(nofPot)
		_edgesIdsToTestAndGenerate->getData(pe.data(), nofPot * sizeof(uint32_t), 0);
	if(nofSil)
		_edgesIdsToGenerate->getData(se.data(), nofSil * sizeof(uint32_t), 0);

	std::sort(pe.begin(), pe.end());
	std::sort(se.begin(), se.end());

	std::ofstream of;
	of.open("GpuEdges.txt");
	of << "Potential:\n";
	for (const auto e : pe)
		of << e << std::endl;
	of << "\nSilhouette:\n";
	for (const auto e : se)
		of << decodeEdgeFromEncoded(e) << " multiplicity: " << decodeEdgeMultiplicityFromId(e) << std::endl;
	of.close();
	//*/
	return;
	//*/
}

bool OctreeSidesDrawer::_generateLoadGpuTraversalShader2()
{
#define USE_LOCAL_SHADER_1	
#ifdef USE_LOCAL_SHADER_1

	const std::string shaderBody = genBufferPreprocessShader(_lastNodePerEdgeBuffer, _octreeVisitor->getOctree(), _workgroupSize);
#else
	std::ifstream t1("C:\\Users\\Jofo\\Desktop\\tmp.glsl");
	std::string shaderBody((std::istreambuf_iterator<char>(t1)),
		std::istreambuf_iterator<char>());
#endif
	m_subBuffersPreprocessShader = std::make_shared<ge::gl::Program>(
		std::make_shared<ge::gl::Shader>(GL_COMPUTE_SHADER, shaderBody));

#define USE_LOCAL_SHADER_2	
#ifdef USE_LOCAL_SHADER_2
	const std::string shaderBody2 = genCopyShader(_lastNodePerEdgeBuffer, _octreeVisitor->getOctree(), _workgroupSize);
#else
	std::ifstream t2("C:\\Users\\ikobrtek\\Desktop\\compressShader.glsl");
	std::string shaderBody2((std::istreambuf_iterator<char>(t2)),
		std::istreambuf_iterator<char>());
#endif

	m_getDataFromPrecomputedBuffersShader = std::make_shared<ge::gl::Program>(
		std::make_shared<ge::gl::Shader>(GL_COMPUTE_SHADER, shaderBody2));

	_allocSubBuffersDataBuffers();

	return m_subBuffersPreprocessShader->getValidateStatus() || m_getDataFromPrecomputedBuffersShader->getValidateStatus();
}

void OctreeSidesDrawer::_allocSubBuffersDataBuffers()
{
	m_nofPotBuffers = std::make_shared<ge::gl::Buffer>(sizeof(uint32_t), nullptr);
	m_nofSilBuffers = std::make_shared<ge::gl::Buffer>(sizeof(uint32_t), nullptr);

	unsigned int pot = 0, sil = 0;
	_getMaxNofBuffersPotSil(pot, sil);

	m_maxNofSubBuffersPath = _octreeVisitor->getMaxNofSubBuffers();

	m_potSuBuffers = std::make_shared<ge::gl::Buffer>(2 * _octreeVisitor->getOctree()->getCompressionLevel() * pot * sizeof(uint32_t));
	m_silSuBuffers = std::make_shared<ge::gl::Buffer>(2 * _octreeVisitor->getOctree()->getCompressionLevel() * sil * sizeof(uint32_t));
	
	//--
	shitBuffer = std::make_shared<ge::gl::Buffer>(800 * sizeof(uint32_t));
	//--
}

void OctreeSidesDrawer::_getPotentialSilhouetteEdgesGpu2(unsigned int lowestNodeContainingLight)
{
	if (_timer) _timer->stamp("");

	m_subBuffersPreprocessShader->use();
	m_subBuffersPreprocessShader->set1ui("cellContainingLight", lowestNodeContainingLight);

	std::shared_ptr<ge::gl::Buffer> nofPotentialEdgesBuffer;
	std::shared_ptr<ge::gl::Buffer> nofSilhouetteEdgesBuffer;
	if (_potentialDrawingMethod == DrawingMethod::CS)
		nofPotentialEdgesBuffer = _indirectDispatchCsPotential;
	else
		nofPotentialEdgesBuffer = _indirectDrawBufferPotentialCS;

	if (_silhouetteDrawingMethod == DrawingMethod::CS)
		nofSilhouetteEdgesBuffer = _indirectDispatchCsSilhouette;
	else
		nofSilhouetteEdgesBuffer = _indirectDrawBufferSilhouetteCS;

	//Clear buffers
	const uint32_t zero = 0;
	nofPotentialEdgesBuffer->setData(&zero, sizeof(uint32_t), 0);
	nofSilhouetteEdgesBuffer->setData(&zero, sizeof(uint32_t), 0);
	m_nofPotBuffers->setData(&zero, sizeof(uint32_t), 0);
	m_nofSilBuffers->setData(&zero, sizeof(uint32_t), 0);
	const unsigned int shitSize = 800;
	shitBuffer->setData(zero, shitSize * sizeof(uint32_t), 0);

	unsigned int bindingPoint = 0;

	//Bind
	_voxelNofPotentialSilhouetteEdgesPrefixSum->bindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	m_potSuBuffers->bindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	m_silSuBuffers->bindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	m_nofPotBuffers->bindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	m_nofSilBuffers->bindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	nofPotentialEdgesBuffer->bindRange(GL_SHADER_STORAGE_BUFFER, bindingPoint++, 0, sizeof(uint32_t));
	nofSilhouetteEdgesBuffer->bindRange(GL_SHADER_STORAGE_BUFFER, bindingPoint++, 0, sizeof(uint32_t));
	_compressedNodesInfoBuffer->bindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	_compressedNodesInfoIndexingBuffer->bindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	

	ge::gl::glDispatchCompute(ceil(float(m_maxNofSubBuffersPath) / float(_workgroupSize)), 1, 1);

	ge::gl::glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT | GL_UNIFORM_BARRIER_BIT);

	//Unbind
	bindingPoint = 0;
	_voxelNofPotentialSilhouetteEdgesPrefixSum->unbindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	m_potSuBuffers->unbindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	m_silSuBuffers->unbindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	m_nofPotBuffers->unbindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	m_nofSilBuffers->unbindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	nofPotentialEdgesBuffer->unbindRange(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	nofSilhouetteEdgesBuffer->unbindRange(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	_compressedNodesInfoBuffer->unbindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	_compressedNodesInfoIndexingBuffer->unbindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	
	//--
	/*
	ge::gl::glFinish();
	uint32_t nofPot = 0, nofSil = 0;
	nofPotentialEdgesBuffer->getData(&nofPot, sizeof(uint32_t), 0);
	nofSilhouetteEdgesBuffer->getData(&nofSil, sizeof(uint32_t), 0);
	
	//uint32_t shi[shitSize] = { 0 };
	//shitBuffer->getData(shi, shitSize * sizeof(uint32_t));

	uint32_t nofPotBuffs = 0, nofSilBuffs = 0;
	m_nofPotSilBuffers->getData(&nofPotBuffs, sizeof(uint32_t), 0);
	m_nofPotSilBuffers->getData(&nofSilBuffs, sizeof(uint32_t), sizeof(uint32_t));
	ge::gl::glFinish();
	std::vector<uint32_t> v;
	v.resize(nofPotBuffs * (_gpuOctreeBuffers.size()>1 ? 4 : 2));
	m_potSuBuffers->getData(v.data(), v.size() * sizeof(uint32_t));

	//*/
	//--

	m_getDataFromPrecomputedBuffersShader->use();

	bindingPoint = 0;
	for (const auto b : _gpuOctreeBuffers)
		b->bindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	m_potSuBuffers->bindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	m_silSuBuffers->bindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	m_nofPotBuffers->bindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	m_nofSilBuffers->bindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	nofPotentialEdgesBuffer->bindRange(GL_SHADER_STORAGE_BUFFER, bindingPoint++, 0, sizeof(uint32_t));
	nofSilhouetteEdgesBuffer->bindRange(GL_SHADER_STORAGE_BUFFER, bindingPoint++, 0, sizeof(uint32_t));
	_edgesIdsToTestAndGenerate->bindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	_edgesIdsToGenerate->bindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);

	ge::gl::glDispatchCompute(ceil(float(_maxNofEdgesPath) / float(_workgroupSize)), 1, 1);

	bindingPoint = 0;
	for (const auto b : _gpuOctreeBuffers)
		b->unbindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	m_potSuBuffers->unbindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	m_silSuBuffers->unbindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	m_nofPotBuffers->unbindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	m_nofSilBuffers->unbindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);


	nofPotentialEdgesBuffer->unbindRange(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	nofSilhouetteEdgesBuffer->unbindRange(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	_edgesIdsToTestAndGenerate->unbindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	_edgesIdsToGenerate->unbindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);

	ge::gl::glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT | GL_COMMAND_BARRIER_BIT);

	//--
	/*
	ge::gl::glFinish();
	std::vector<uint32_t> a;
	a.resize(nofSil);
	_edgesIdsToGenerate->getData(a.data(), nofSil * sizeof(uint32_t));
	
	nofPotentialEdgesBuffer->getData(&nofPot, sizeof(uint32_t), 0);
	nofSilhouetteEdgesBuffer->getData(&nofSil, sizeof(uint32_t), 0);

	std::vector<uint32_t> pe, se;
	pe.resize(nofPot);
	se.resize(nofSil);

	if (nofPot)
		_edgesIdsToTestAndGenerate->getData(pe.data(), nofPot * sizeof(uint32_t), 0);
	if (nofSil)
		_edgesIdsToGenerate->getData(se.data(), nofSil * sizeof(uint32_t), 0);

	std::sort(pe.begin(), pe.end());
	std::sort(se.begin(), se.end());

	std::ofstream of;
	of.open("GpuEdges.txt");
	of << "Potential:\n";
	for (const auto e : pe)
		of << e << std::endl;
	of << "\nSilhouette:\n";
	for (const auto e : se)
		of << decodeEdgeFromEncoded(e) << " multiplicity: " << decodeEdgeMultiplicityFromId(e) << std::endl;
	of.close();
	//*/
	//--

	if (_timer) _timer->stamp("TraverseOctree");
}

bool OctreeSidesDrawer::_generateLoadGpuTraversalShader3()
{
	const std::string shaderBody1 = genBufferPreprocessShader(_lastNodePerEdgeBuffer, _octreeVisitor->getOctree(), _workgroupSize);
	
	m_subBuffersPreprocessShader = std::make_shared<ge::gl::Program>(
		std::make_shared<ge::gl::Shader>(GL_COMPUTE_SHADER, shaderBody1));

	std::ifstream t1("C:\\Users\\ikobrtek\\Desktop\\prefixSumKernel.glsl");
	std::string shaderBody2((std::istreambuf_iterator<char>(t1)),
		std::istreambuf_iterator<char>());

	m_prefixSumShader = std::make_shared<ge::gl::Program>(
		std::make_shared<ge::gl::Shader>(GL_COMPUTE_SHADER, shaderBody2));


//#define USE_LOCAL_SHADER_3
#ifdef USE_LOCAL_SHADER_3
	const std::string shaderBody3 = genCopyShader(_lastNodePerEdgeBuffer, _octreeVisitor->getOctree(), _workgroupSize);
#else
	std::ifstream t2("C:\\Users\\ikobrtek\\Desktop\\compressShader2.glsl");
	std::string shaderBody3((std::istreambuf_iterator<char>(t2)),
		std::istreambuf_iterator<char>());
#endif

	m_getDataFromPrecomputedBuffersShader2 = std::make_shared<ge::gl::Program>(
		std::make_shared<ge::gl::Shader>(GL_COMPUTE_SHADER, shaderBody3));

	m_dataStride = _gpuOctreeBuffers.size() > 1 ? 4 : 2;

	_allocSubBuffersDataBuffers();

	return m_prefixSumShader->getValidateStatus() && m_subBuffersPreprocessShader->getValidateStatus() && m_getDataFromPrecomputedBuffersShader2->getValidateStatus();
}

void OctreeSidesDrawer::_getPotentialSilhouetteEdgesGpu3(unsigned int lowestNodeContainingLight)
{
	//Prefix sum computation TEST
	/*
	{
		std::vector<unsigned int> kokot;
		const unsigned int nofItem = 3;

		for (unsigned int i = 0; i < nofItem; ++i)
		{
			kokot.push_back(1);
			kokot.push_back(0);
		}

		shitBuffer->setData(kokot.data(), kokot.size() * sizeof(uint32_t));
		m_nofPotBuffers->setData(&nofItem, sizeof(uint32_t));

		m_prefixSumShader->use();
		uint32_t consts[4] = { m_dataStride, 0, m_dataStride, 0 };
		m_prefixSumShader->set4uiv("stridesOffsets", consts);

		shitBuffer->bindBase(GL_SHADER_STORAGE_BUFFER, 0);
		m_nofPotBuffers->bindRange(GL_SHADER_STORAGE_BUFFER, 1, 0, sizeof(uint32_t));

		ge::gl::glDispatchCompute(1, 1, 1);

		shitBuffer->unbindBase(GL_SHADER_STORAGE_BUFFER, 0);
		m_nofPotBuffers->unbindRange(GL_SHADER_STORAGE_BUFFER, 1);

		ge::gl::glFinish();

		shitBuffer->getData(kokot.data(), nofItem * m_dataStride * sizeof(uint32_t));
		kokot[0];
	}
	//*/

	//Process Subbuffers, generate per subbuffer data
	if (_timer) _timer->stamp("");

	m_subBuffersPreprocessShader->use();
	m_subBuffersPreprocessShader->set1ui("cellContainingLight", lowestNodeContainingLight);

	std::shared_ptr<ge::gl::Buffer> nofPotentialEdgesBuffer;
	std::shared_ptr<ge::gl::Buffer> nofSilhouetteEdgesBuffer;
	if (_potentialDrawingMethod == DrawingMethod::CS)
		nofPotentialEdgesBuffer = _indirectDispatchCsPotential;
	else
		nofPotentialEdgesBuffer = _indirectDrawBufferPotentialCS;

	if (_silhouetteDrawingMethod == DrawingMethod::CS)
		nofSilhouetteEdgesBuffer = _indirectDispatchCsSilhouette;
	else
		nofSilhouetteEdgesBuffer = _indirectDrawBufferSilhouetteCS;

	//clear buffers
	const uint32_t zero = 0;
	nofPotentialEdgesBuffer->setData(&zero, sizeof(uint32_t), 0);
	nofSilhouetteEdgesBuffer->setData(&zero, sizeof(uint32_t), 0);
	m_nofPotBuffers->setData(&zero, sizeof(uint32_t), 0);
	m_nofSilBuffers->setData(&zero, sizeof(uint32_t), 0);

	unsigned int bindingPoint = 0;

	//bind
	_voxelNofPotentialSilhouetteEdgesPrefixSum->bindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	m_potSuBuffers->bindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	m_silSuBuffers->bindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	m_nofPotBuffers->bindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	m_nofSilBuffers->bindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	nofPotentialEdgesBuffer->bindRange(GL_SHADER_STORAGE_BUFFER, bindingPoint++, 0, sizeof(uint32_t));
	nofSilhouetteEdgesBuffer->bindRange(GL_SHADER_STORAGE_BUFFER, bindingPoint++, 0, sizeof(uint32_t));
	_compressedNodesInfoBuffer->bindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	_compressedNodesInfoIndexingBuffer->bindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);

	ge::gl::glDispatchCompute(ceil(float(m_maxNofSubBuffersPath) / float(_workgroupSize)), 1, 1);

	ge::gl::glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

	//unbind
	bindingPoint = 0;
	_voxelNofPotentialSilhouetteEdgesPrefixSum->unbindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	m_potSuBuffers->unbindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	m_silSuBuffers->unbindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	m_nofPotBuffers->unbindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	m_nofSilBuffers->unbindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	nofPotentialEdgesBuffer->unbindRange(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	nofSilhouetteEdgesBuffer->unbindRange(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	_compressedNodesInfoBuffer->unbindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	_compressedNodesInfoIndexingBuffer->unbindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);

	//--
	/*
	ge::gl::glFinish();
	uint32_t nofPot = 0, nofSil = 0;
	nofPotentialEdgesBuffer->getData(&nofPot, sizeof(uint32_t), 0);
	nofSilhouetteEdgesBuffer->getData(&nofSil, sizeof(uint32_t), 0);

	uint32_t nofPotBuffs = 0, nofSilBuffs = 0;
	m_nofPotBuffers->getData(&nofPotBuffs, sizeof(uint32_t));
	m_nofSilBuffers->getData(&nofSilBuffs, sizeof(uint32_t));
	ge::gl::glFinish();
	if (nofPotBuffs)
	{
		std::vector<uint32_t> v;
		v.resize(nofPotBuffs *m_dataStride);
		m_potSuBuffers->getData(v.data(), v.size() * sizeof(uint32_t));
		v.size();
	}
	if (nofSilBuffs)
	{
		std::vector<uint32_t> v;
		v.resize(nofSilBuffs *m_dataStride);
		m_silSuBuffers->getData(v.data(), v.size() * sizeof(uint32_t));
		v.size();
	}
	//*/
	//--

	//Prefix sum computation POT
	m_prefixSumShader->use();
	uint32_t consts[4] = { m_dataStride, 0, m_dataStride, 0 };
	m_prefixSumShader->set4uiv("stridesOffsets", consts);

	m_potSuBuffers->bindBase(GL_SHADER_STORAGE_BUFFER, 0);
	m_nofPotBuffers->bindBase(GL_SHADER_STORAGE_BUFFER, 1);

	ge::gl::glDispatchCompute(1, 1, 1);

	//m_potSuBuffers->unbindBase(GL_SHADER_STORAGE_BUFFER, 0);
	//m_nofPotSilBuffers->unbindRange(GL_SHADER_STORAGE_BUFFER, 1);

	//Prefix sum computation SIL
	m_silSuBuffers->bindBase(GL_SHADER_STORAGE_BUFFER, 0);
	m_nofSilBuffers->bindBase(GL_SHADER_STORAGE_BUFFER, 1);

	ge::gl::glDispatchCompute(1, 1, 1);

	m_silSuBuffers->unbindBase(GL_SHADER_STORAGE_BUFFER, 0);
	m_nofSilBuffers->unbindBase(GL_SHADER_STORAGE_BUFFER, 1);

	ge::gl::glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

	//--
	/*
	ge::gl::glFinish();
	std::vector<unsigned int> dp, ds;
	ds.resize(nofSilBuffs*m_dataStride);
	dp.resize(nofPotBuffs*m_dataStride);
	if(nofSilBuffs)
		m_silSuBuffers->getData(ds.data(), ds.size() * sizeof(uint32_t));

	if (nofPotBuffs)
		m_potSuBuffers->getData(dp.data(), dp.size() * sizeof(uint32_t));
	//*/
	//--

	//Copy
	m_getDataFromPrecomputedBuffersShader2->use();

	bindingPoint = 0;
	for (const auto b : _gpuOctreeBuffers)
		b->bindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	m_potSuBuffers->bindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	m_silSuBuffers->bindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	m_nofPotBuffers->bindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	m_nofSilBuffers->bindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	nofPotentialEdgesBuffer->bindRange(GL_SHADER_STORAGE_BUFFER, bindingPoint++, 0, sizeof(uint32_t));
	nofSilhouetteEdgesBuffer->bindRange(GL_SHADER_STORAGE_BUFFER, bindingPoint++, 0, sizeof(uint32_t));
	_edgesIdsToTestAndGenerate->bindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	_edgesIdsToGenerate->bindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);

	ge::gl::glDispatchCompute(ceil(float(_maxNofEdgesPath) / float(_workgroupSize)), 1, 1);

	bindingPoint = 0;
	for (const auto b : _gpuOctreeBuffers)
		b->unbindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	m_potSuBuffers->unbindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	m_silSuBuffers->unbindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	m_nofPotBuffers->unbindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	m_nofSilBuffers->unbindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	nofPotentialEdgesBuffer->unbindRange(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	nofSilhouetteEdgesBuffer->unbindRange(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	_edgesIdsToTestAndGenerate->unbindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	_edgesIdsToGenerate->unbindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);

	ge::gl::glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT | GL_COMMAND_BARRIER_BIT);


	//--
	/*
	ge::gl::glFinish();
	std::vector<uint32_t> a;
	a.resize(nofSil);
	_edgesIdsToGenerate->getData(a.data(), nofSil * sizeof(uint32_t));

	nofPotentialEdgesBuffer->getData(&nofPot, sizeof(uint32_t), 0);
	nofSilhouetteEdgesBuffer->getData(&nofSil, sizeof(uint32_t), 0);

	std::vector<uint32_t> pe, se;
	pe.resize(nofPot);
	se.resize(nofSil);

	if (nofPot)
	_edgesIdsToTestAndGenerate->getData(pe.data(), nofPot * sizeof(uint32_t), 0);
	if (nofSil)
	_edgesIdsToGenerate->getData(se.data(), nofSil * sizeof(uint32_t), 0);

	std::sort(pe.begin(), pe.end());
	std::sort(se.begin(), se.end());

	std::ofstream of;
	of.open("GpuEdges.txt");
	of << "Potential:\n";
	for (const auto e : pe)
	of << e << std::endl;
	of << "\nSilhouette:\n";
	for (const auto e : se)
	of << decodeEdgeFromEncoded(e) << " multiplicity: " << decodeEdgeMultiplicityFromId(e) << std::endl;
	of.close();
	//*/
	//--
}