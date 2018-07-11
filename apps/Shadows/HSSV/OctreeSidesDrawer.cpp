#include "OctreeSidesDrawer.hpp"
#include "GenerateSidesProgram.hpp"
#include <geGL/StaticCalls.h>
#include "MultiplicityCoding.hpp"
#include "../CSSVShaders.h"
#include "OctreeTraversalShader.hpp"
#include "GenerateSidesDataOnGpuProgram.hpp"

#define MAX_MULTIPLICITY 2

OctreeSidesDrawer::OctreeSidesDrawer(std::shared_ptr<OctreeVisitor> visitor, unsigned int workgroupSize, DrawingMethod potential, DrawingMethod silhouette) : 
	_octreeVisitor(visitor), _workgroupSize(workgroupSize), _potentialDrawingMethod(potential), _silhouetteDrawingMethod(silhouette)
{
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

	_gpuOctreeTraversalProgramSingleBuffer = std::make_shared<ge::gl::Program>(
		std::make_shared<ge::gl::Shader>(GL_COMPUTE_SHADER,
			"#version 450 core\n",
			ge::gl::Shader::define("WORKGROUP_SIZE_X", _workgroupSize),
			ge::gl::Shader::define("DEEPEST_LEVEL", _octreeVisitor->getOctree()->getDeepestLevel()),
			edgeTraversalShaderBody)
		);
}

bool OctreeSidesDrawer::_generateLoadGpuTraversalShader()
{
	std::string shaderBody = genTraversalComputeShader(_lastNodePerEdgeBuffer, _octreeVisitor->getOctree(), _workgroupSize);

	_gpuOctreeTraversalProgramMultipleBuffers = std::make_shared<ge::gl::Program>(
		std::make_shared<ge::gl::Shader>(GL_COMPUTE_SHADER, shaderBody) );

	return _gpuOctreeTraversalProgramMultipleBuffers->getValidateStatus();
}

void OctreeSidesDrawer::init(std::shared_ptr<GpuEdges> gpuEdges)
{
	_initShaders();

	_initBuffers();
#ifdef USE_GPU_OCTREE
	_loadOctreeToGpu();
	if (!_generateLoadGpuTraversalShader())
		return;

#endif

	_gpuEdges = gpuEdges;
}

void OctreeSidesDrawer::_initBuffers()
{
	size_t maxPotentialEdges, maxSilhouetteEdges, maxEdges;
	_getMaxPossibleEdgeCountInTraversal(maxPotentialEdges, maxSilhouetteEdges, maxEdges);
	_maxNofEdgesInVoxel = maxEdges;

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
}

void OctreeSidesDrawer::_loadOctreeToGpu()
{
	const unsigned int nofVoxels = _octreeVisitor->getOctree()->getTotalNumNodes();
	
	uint64_t remainingSize = _octreeVisitor->getOctree()->getOctreeSizeBytes();
	const uint64_t maxBufferSize = 2ull * 1024ull * 1024ull * 1024ull;
	unsigned int currentNode = 0;

	std::vector<uint32_t> nofEdgesPrefixSums;
	nofEdgesPrefixSums.reserve(nofVoxels + 1);

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

			uint64_t sz = (node->edgesAlwaysCast.size() + node->edgesMayCast.size()) * sizeof(uint32_t);

			if ((sz + currentNumIndices*sizeof(uint32_t)) > currentSize)
				break;

			currentNode++;

			if (node->edgesMayCast.size())
			{
				memcpy(dataPtr + nofEdgesPrefixSums[nofEdgesPrefixSums.size() - 1], node->edgesMayCast.data(), node->edgesMayCast.size() * sizeof(uint32_t));
				currentNumIndices += node->edgesMayCast.size();
			}
			nofEdgesPrefixSums.push_back(nofEdgesPrefixSums[nofEdgesPrefixSums.size() - 1] + node->edgesMayCast.size());

			const auto offset = nofEdgesPrefixSums[nofEdgesPrefixSums.size() - 1];
			if (node->edgesAlwaysCast.size())
			{
				memcpy(dataPtr + nofEdgesPrefixSums[nofEdgesPrefixSums.size() - 1], node->edgesAlwaysCast.data(), node->edgesAlwaysCast.size() * sizeof(uint32_t));
				currentNumIndices += node->edgesAlwaysCast.size();
			}
			nofEdgesPrefixSums.push_back(nofEdgesPrefixSums[nofEdgesPrefixSums.size() - 1] + node->edgesAlwaysCast.size());
		}

		buffer->unmap();

		_gpuOctreeBuffers.push_back(buffer);
		_lastNodePerEdgeBuffer.push_back(currentNode);
	}

	_voxelNofPotentialSilhouetteEdgesPrefixSum = std::make_shared<ge::gl::Buffer>(nofEdgesPrefixSums.size() * sizeof(uint32_t), nofEdgesPrefixSums.data());
}

void OctreeSidesDrawer::_getMaxPossibleEdgeCountInTraversal(size_t& potential, size_t& silhouette, size_t& maxInVoxel) const
{
	potential = 0;
	silhouette = 0;
	maxInVoxel = 0;

	const unsigned int maxLevel = _octreeVisitor->getOctree()->getDeepestLevel();
	for (unsigned int i = 0; i <= maxLevel; ++i)
	{
		size_t pot = 0, silh = 0;
		_getMaximumNofEdgesInLevel(i, pot, silh);

		maxInVoxel = std::max(pot, maxInVoxel);
		maxInVoxel = std::max(silh, maxInVoxel);

		potential += pot;
		silhouette += silh;
	}
}

void OctreeSidesDrawer::_getMaximumNofEdgesInLevel(unsigned int level, size_t& potential, size_t& silhouette) const
{
	potential = 0;
	silhouette = 0;

	const auto startingIndex = _octreeVisitor->getOctree()->getLevelFirstNodeID(level);
	const auto levelSize = ipow(OCTREE_NUM_CHILDREN, level);

	for(unsigned int i=0; i<levelSize; ++i)
	{
		const auto n = _octreeVisitor->getOctree()->getNode(startingIndex + i);
		potential = std::max(potential, n->edgesMayCast.size());
		silhouette = std::max(silhouette, n->edgesAlwaysCast.size());
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
#ifdef USE_GPU_OCTREE
		//static bool once = true;
		//if(once)
		//_loadPotentialSilhouetteEdgesFromVoxelGPU(cellIndex);
		//once = false;
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

void OctreeSidesDrawer::_drawSidesFromSilhouetteEdgesTS(const glm::mat4& mvp, const glm::vec4& lightPos, unsigned int cellContainingLightId)
{
	//TimeStamp ts;
	//ts.begin();
	//ge::gl::glEnable(GL_RASTERIZER_DISCARD);
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
	//ts.stamp("DrawSidesFromSilhouetteTS");
	//ts.end("TS SIL");
	//ge::gl::glDisable(GL_RASTERIZER_DISCARD);

	err = ge::gl::glGetError();
	assert(err == GL_NO_ERROR);
}

void OctreeSidesDrawer::_drawSidesFromSilhouetteEdgesGS(const glm::mat4& mvp, const glm::vec4& lightPos, unsigned cellContainingLightId)
{
	//TimeStamp ts;
	//ts.begin();
	//ge::gl::glEnable(GL_RASTERIZER_DISCARD);
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

	//ts.stamp("DrawSidesSilhouetteGS");
	//ts.end("GS SIL");
	//ge::gl::glDisable(GL_RASTERIZER_DISCARD);

	err = ge::gl::glGetError();
	assert(err == GL_NO_ERROR);
}

void OctreeSidesDrawer::_drawSidesFromSilhouetteEdgesCS(const glm::mat4& mvp, const glm::vec4& lightPos, unsigned int cellContainingLightId)
{
	_generateSidesFromSilhouetteCS(lightPos, cellContainingLightId);

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
	//TimeStamp ts;
	//ts.begin();
	//ge::gl::glEnable(GL_RASTERIZER_DISCARD);
#ifndef USE_GPU_OCTREE
	if (_lastFrameCellIndex != int(cellContainingLightId))
	{
		_nofPotentialEdgesToDraw = _loadEdgesFromIdUpGetNof(cellContainingLightId, false);
		std::cout << "Acquiring " << _nofPotentialEdgesToDraw << " potential edges\n";
	}

	if (!_nofPotentialEdgesToDraw)
	return;
#endif

	auto err = ge::gl::glGetError();
	assert(err == GL_NO_ERROR);

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
	//ts.stamp("DrawSidesPotentialTS");
	//ts.end("TS POT");
	//ge::gl::glDisable(GL_RASTERIZER_DISCARD);

	err = ge::gl::glGetError();
	assert(err == GL_NO_ERROR);
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

	assert(ge::gl::glGetError() == GL_NO_ERROR);
}

void OctreeSidesDrawer::_drawSidesFromPotentialEdgesCS(const glm::mat4& mvp, const glm::vec4& lightPos, unsigned cellContainingLightId)
{
	_generateSidesFromPotentialCS(lightPos, cellContainingLightId);

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
	assert(ge::gl::glGetError() == GL_NO_ERROR);
	
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

	assert(ge::gl::glGetError() == GL_NO_ERROR);
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
	_generateSidesFromPotentialCS(lightPos, cellContainingLightId);
	_generateSidesFromSilhouetteCS(lightPos, cellContainingLightId);

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

//#include <fstream>
void OctreeSidesDrawer::_getPotentialSilhouetteEdgesGpu(unsigned int lowestNodeContainingLight)
{

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

	ge::gl::glDispatchCompute(ceil(float(_maxNofEdgesInVoxel) / 128.0f), 1, 1);

	bindingPoint = 0;
	for (const auto b : _gpuOctreeBuffers)
		b->unbindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);

	_voxelNofPotentialSilhouetteEdgesPrefixSum->unbindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	nofPotentialEdgesBuffer->unbindRange(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	nofSilhouetteEdgesBuffer->unbindRange(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	_edgesIdsToTestAndGenerate->unbindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);
	_edgesIdsToGenerate->unbindBase(GL_SHADER_STORAGE_BUFFER, bindingPoint++);

	//DEBUG
	//Get data
	/*
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
	of.open("PotEdges.txt");
	of << "Potential:\n";
	for (const auto e : pe)
		of << e << std::endl;
	of << "\nSilhouette:\n";
	for (const auto e : se)
		of << decodeEdgeFromEncoded(e) << " multiplicity: " << decodeEdgeMultiplicityFromId(e) << std::endl;
	of.close();

	return;
	//*/
}