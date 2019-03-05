#include "OctreeSidesDrawer.hpp"
#include "GenerateSidesProgram.hpp"
#include <geGL/StaticCalls.h>
#include "MultiplicityCoding.hpp"
#include "../CSSVShaders.h"
#include "GenerateSidesDataOnGpuProgram.hpp"
#include "../TimeStamp.h"


#define MAX_MULTIPLICITY 2
#define MAX_NOF_SUBBUFFERS_SINGLE_PASS 1024

OctreeSidesDrawer::OctreeSidesDrawer(std::shared_ptr<OctreeVisitor> visitor, uint32_t workgroupSize, DrawingMethod potential, DrawingMethod silhouette) : 
	_octreeVisitor(visitor), _workgroupSize(workgroupSize), _potentialDrawingMethod(potential), _silhouetteDrawingMethod(silhouette)
{
}

void OctreeSidesDrawer::setStamper(std::shared_ptr<TimeStamp> stamper)
{
	_timer = stamper;
}

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
}

#include <fstream>

void OctreeSidesDrawer::init(std::shared_ptr<GpuEdges> gpuEdges)
{
	_initShaders();

	_initBuffers();

	_loadOctreeToGpu();

	if (!_generateLoadGpuTraversalShader3())
		return;

	_gpuEdges = gpuEdges;
}

void OctreeSidesDrawer::_initBuffers()
{
	size_t maxPotentialEdges, maxSilhouetteEdges, maxEdges, maxPath;
	_getMaxPossibleEdgeCountInTraversal(maxPotentialEdges, maxSilhouetteEdges, maxEdges, maxPath);
	_maxNofEdgesInVoxel = uint32_t(maxEdges);
	_maxNofEdgesPath = uint32_t(maxPath);

	_edgesIdsToGenerate = std::make_shared<ge::gl::Buffer>(maxSilhouetteEdges * sizeof(uint32_t), nullptr);
	_edgesIdsToTestAndGenerate = std::make_shared<ge::gl::Buffer>(maxPotentialEdges * sizeof(uint32_t), nullptr);

	if (_potentialDrawingMethod != DrawingMethod::CS || _silhouetteDrawingMethod != DrawingMethod::CS)
		_dummyVAO = std::make_shared<ge::gl::VertexArray>();

	const uint32_t indirectBuffer[4] = { 0, 1, 0, 0 };
	_indirectDrawBufferPotentialCS = std::make_shared<ge::gl::Buffer>(4 * sizeof(uint32_t), indirectBuffer);
	_indirectDrawBufferSilhouetteCS = std::make_shared<ge::gl::Buffer>(4 * sizeof(uint32_t), indirectBuffer);

	if (_potentialDrawingMethod == DrawingMethod::CS)
	{
		_potentialEdgeCsVBO = std::make_shared<ge::gl::Buffer>(2 * MAX_MULTIPLICITY * maxPotentialEdges * 4 * sizeof(float), nullptr); //2* because each edges consists of 2 points

		_potentialSidesCsVAO = std::make_shared<ge::gl::VertexArray>();
		_potentialSidesCsVAO->addAttrib(_potentialEdgeCsVBO, 0, 4, GL_FLOAT);
	}

	if (_silhouetteDrawingMethod == DrawingMethod::CS)
	{
		_silhouetteEdgeCsVBO = std::make_shared<ge::gl::Buffer>(2 * MAX_MULTIPLICITY * maxSilhouetteEdges * 4 * sizeof(float), nullptr);

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
		const uint32_t nofUints = BitmaskTypeSizeBits / 32;
		const uint32_t* val = reinterpret_cast<const uint32_t*>(&id);

		for (uint32_t i = 0; i < nofUints; ++i)
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
	
	const auto startIndex = nofEdgesPrefixSums.size() - 1;
	
	nofEdgesPrefixSums.push_back(nofEdgesPrefixSums[nofEdgesPrefixSums.size() - 1] + uint32_t(subBufferSize));

	//Push compression ID
	_breakCompressionIdToUintsAndPush(subBuffer.first, compressedNodesInfo);

	//Push starting index
	compressedNodesInfo.push_back(uint32_t(startIndex));
}

void OctreeSidesDrawer::_loadOctreeToGpu()
{
	const uint32_t nofVoxels = _octreeVisitor->getOctree()->getTotalNumNodes();
	
	uint64_t remainingSize = _octreeVisitor->getOctree()->getOctreeSizeBytes();
	const uint64_t maxBufferSize = 2ull * 1024ull * 1024ull * 1024ull; //2GB
	uint32_t currentNode = 0;

	std::vector<uint32_t> nofEdgesPrefixSums;
	std::vector<uint32_t> compressedNodesInfo;
	std::vector<uint32_t> compressedNodesInfoIndexing;

	nofEdgesPrefixSums.reserve(nofVoxels + 1);
	compressedNodesInfoIndexing.reserve(nofVoxels);

	auto octree = _octreeVisitor->getOctree();

	while(remainingSize>0)
	{
		const uint64_t currentSize = remainingSize > maxBufferSize ? maxBufferSize : remainingSize;

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

			compressedNodesInfoIndexing.push_back(uint32_t(compressedNodesInfo.size()));
			compressedNodesInfo.push_back(uint32_t(node->edgesMayCastMap.size()));
			compressedNodesInfo.push_back(uint32_t(node->edgesAlwaysCastMap.size()));

			for (const auto& subBuffer : node->edgesMayCastMap)
				_processSubBuffer(subBuffer, compressedNodesInfo, nofEdgesPrefixSums, dataPtr);

			for (const auto& subBuffer : node->edgesAlwaysCastMap)
				_processSubBuffer(subBuffer, compressedNodesInfo, nofEdgesPrefixSums, dataPtr);

			currentNumIndices += sz;
		}

		buffer->unmap();
		remainingSize -= currentNumIndices * sizeof(uint32_t);
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

	const uint32_t maxLevel = _octreeVisitor->getOctree()->getDeepestLevel();
	for (uint32_t i = 0; i <= maxLevel; ++i)
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

void OctreeSidesDrawer::_getNofEdgesInNode(uint32_t nodeId, size_t& potential, size_t& silhouette) const
{
	potential = silhouette = 0;
	const auto node = _octreeVisitor->getOctree()->getNode(nodeId);
	for (const auto& buffer : node->edgesAlwaysCastMap)
		silhouette += buffer.second.size();

	for (const auto& buffer : node->edgesMayCastMap)
		potential += buffer.second.size();
}

void OctreeSidesDrawer::_getMaximumNofEdgesInLevel(uint32_t level, size_t& potential, size_t& silhouette) const
{
	potential = 0;
	silhouette = 0;

	const auto startingIndex = _octreeVisitor->getOctree()->getLevelFirstNodeID(level);
	const auto levelSize = ipow(OCTREE_NUM_CHILDREN, level);

	for(int i=0; i<levelSize; ++i)
	{
		size_t nodePot = 0, nodeSil = 0;
		_getNofEdgesInNode(startingIndex + i, nodePot, nodeSil);
		potential = std::max(potential, nodePot);
		silhouette = std::max(silhouette,nodeSil);
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
		static bool printOnce = false;

		if (!printOnce)
		{
			std::cout << "Light " << light.x << ", " << light.y << ", " << light.z << std::endl;
			std::cout << "Cell index: " << cellIndex << std::endl;
			printOnce = true;
		}

		_getPotentialSilhouetteEdgesGpu3(cellIndex);

		if (_silhouetteDrawingMethod == DrawingMethod::CS && _potentialDrawingMethod == DrawingMethod::CS)
			_drawSidesCS(mvp, light);
		else
		{
			switch (_silhouetteDrawingMethod)
			{
			case DrawingMethod::GS:
				_drawSidesFromSilhouetteEdgesGS(mvp, light); break;
			case DrawingMethod::TS:
				_drawSidesFromSilhouetteEdgesTS(mvp, light); break;
			case DrawingMethod::CS:
				_drawSidesFromSilhouetteEdgesCS(mvp, light); break;
			}

			switch (_potentialDrawingMethod)
			{
			case DrawingMethod::GS:
				_drawSidesFromPotentialEdgesGS(mvp, light); break;
			case DrawingMethod::TS:
				_drawSidesFromPotentialEdgesTS(mvp, light); break;
			case DrawingMethod::CS:
				_drawSidesFromPotentialEdgesCS(mvp, light); break;
			}
		}
	}

	_lastFrameCellIndex = cellIndex;
}

void OctreeSidesDrawer::_drawSidesFromSilhouetteEdgesTS(const glm::mat4& mvp, const glm::vec4& lightPos)
{
	if (_timer) _timer->stamp("");

	assert(GL_NO_ERROR == ge::gl::glGetError());

	_silhouetteSidesTsProgram->use();
	_silhouetteSidesTsProgram->setMatrix4fv("mvp", glm::value_ptr(mvp))->set4fv("lightPosition", glm::value_ptr(lightPos));

	_dummyVAO->bind();

	_gpuEdges->_edges->bindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_edgesIdsToGenerate->bindBase(GL_SHADER_STORAGE_BUFFER, 1);

	ge::gl::glPatchParameteri(GL_PATCH_VERTICES, 1);

	_indirectDrawBufferSilhouetteCS->bind(GL_DRAW_INDIRECT_BUFFER);
	ge::gl::glDrawArraysIndirect(GL_PATCHES, nullptr);
	_indirectDrawBufferSilhouetteCS->unbind(GL_DRAW_INDIRECT_BUFFER);
	
	_gpuEdges->_edges->unbindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_edgesIdsToGenerate->unbindBase(GL_SHADER_STORAGE_BUFFER, 1);

	_dummyVAO->unbind();

	if (_timer) _timer->stamp("SilhouetteEdges");

	assert(GL_NO_ERROR == ge::gl::glGetError());
}

void OctreeSidesDrawer::_drawSidesFromSilhouetteEdgesGS(const glm::mat4& mvp, const glm::vec4& lightPos)
{
	if (_timer) _timer->stamp("");
	
	_silhouetteSidesGsProgram->use();
	_silhouetteSidesGsProgram->setMatrix4fv("mvp", glm::value_ptr(mvp))->set4fv("lightPosition", glm::value_ptr(lightPos));

	_dummyVAO->bind();

	_gpuEdges->_edges->bindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_edgesIdsToGenerate->bindBase(GL_SHADER_STORAGE_BUFFER, 1);
	
	_indirectDrawBufferSilhouetteCS->bind(GL_DRAW_INDIRECT_BUFFER);
	ge::gl::glDrawArraysIndirect(GL_POINTS, 0);
	_indirectDrawBufferSilhouetteCS->unbind(GL_DRAW_INDIRECT_BUFFER);
	
	_gpuEdges->_edges->unbindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_edgesIdsToGenerate->unbindBase(GL_SHADER_STORAGE_BUFFER, 1);

	_dummyVAO->unbind();

	if (_timer) _timer->stamp("SilhouetteEdges");
}

void OctreeSidesDrawer::_drawSidesFromSilhouetteEdgesCS(const glm::mat4& mvp, const glm::vec4& lightPos)
{
	if (_timer) _timer->stamp("");
	_generateSidesFromSilhouetteCS();
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

void OctreeSidesDrawer::_drawSidesFromPotentialEdgesTS(const glm::mat4& mvp, const glm::vec4& lightPos)
{
	if (_timer) _timer->stamp("");

	assert(ge::gl::glGetError() == GL_NO_ERROR);

	_potentialTsProgram->use();
	_potentialTsProgram->setMatrix4fv("mvp", glm::value_ptr(mvp))->set4fv("lightPosition", glm::value_ptr(lightPos));

	_dummyVAO->bind();

	_gpuEdges->_edges->bindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_gpuEdges->_oppositeVertices->bindBase(GL_SHADER_STORAGE_BUFFER, 1);
	_edgesIdsToTestAndGenerate->bindBase(GL_SHADER_STORAGE_BUFFER, 2);
	
	ge::gl::glPatchParameteri(GL_PATCH_VERTICES, 1);

	_indirectDrawBufferPotentialCS->bind(GL_DRAW_INDIRECT_BUFFER);
	ge::gl::glDrawArraysIndirect(GL_PATCHES, 0);
	_indirectDrawBufferPotentialCS->unbind(GL_DRAW_INDIRECT_BUFFER);
	
	_gpuEdges->_edges->unbindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_gpuEdges->_oppositeVertices->unbindBase(GL_SHADER_STORAGE_BUFFER, 1);
	_edgesIdsToTestAndGenerate->unbindBase(GL_SHADER_STORAGE_BUFFER, 2);

	_dummyVAO->unbind();
	
	if (_timer) _timer->stamp("PotentialEdges");

	assert(ge::gl::glGetError() == GL_NO_ERROR);
}

void OctreeSidesDrawer::_drawSidesFromPotentialEdgesGS(const glm::mat4& mvp, const glm::vec4& lightPos)
{
	assert(ge::gl::glGetError() == GL_NO_ERROR);

	if (_timer) _timer->stamp("");
	_potentialGsProgram->use();
	_potentialGsProgram->setMatrix4fv("mvp", glm::value_ptr(mvp))->set4fv("lightPosition", glm::value_ptr(lightPos));

	_dummyVAO->bind();

	_gpuEdges->_edges->bindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_gpuEdges->_oppositeVertices->bindBase(GL_SHADER_STORAGE_BUFFER, 1);
	_edgesIdsToTestAndGenerate->bindBase(GL_SHADER_STORAGE_BUFFER, 2);
	
	_indirectDrawBufferPotentialCS->bind(GL_DRAW_INDIRECT_BUFFER);
	ge::gl::glDrawArraysIndirect(GL_POINTS, nullptr);
	_indirectDrawBufferPotentialCS->unbind(GL_DRAW_INDIRECT_BUFFER);

	_gpuEdges->_edges->unbindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_gpuEdges->_oppositeVertices->unbindBase(GL_SHADER_STORAGE_BUFFER, 1);
	_edgesIdsToTestAndGenerate->unbindBase(GL_SHADER_STORAGE_BUFFER, 2);

	_dummyVAO->unbind();

	if (_timer) _timer->stamp("PotentialEdges");

	assert(ge::gl::glGetError() == GL_NO_ERROR);
}

void OctreeSidesDrawer::_drawSidesFromPotentialEdgesCS(const glm::mat4& mvp, const glm::vec4& lightPos)
{
	if (_timer) _timer->stamp("");
	_generateSidesFromPotentialCS(lightPos);
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

void OctreeSidesDrawer::_generateSidesFromPotentialCS(const glm::vec4& lightPos)
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

void OctreeSidesDrawer::_generateSidesFromSilhouetteCS()
{
	const uint32_t zero = 0;
	_indirectDrawBufferSilhouetteCS->setData(&zero, sizeof(uint32_t));

	_generateSidesProgram->use();

	_gpuEdges->_edges->bindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_edgesIdsToGenerate->bindBase(GL_SHADER_STORAGE_BUFFER, 1);
	_silhouetteEdgeCsVBO->bindBase(GL_SHADER_STORAGE_BUFFER, 2);
	_indirectDrawBufferSilhouetteCS->bindBase(GL_SHADER_STORAGE_BUFFER, 3);
	_indirectDispatchCsSilhouette->bindRange(GL_SHADER_STORAGE_BUFFER, 4, 0, sizeof(uint32_t));
	_indirectDispatchCsSilhouette->bind(GL_DISPATCH_INDIRECT_BUFFER);

	ge::gl::glDispatchComputeIndirect(0);

	_indirectDispatchCsSilhouette->unbind(GL_DISPATCH_INDIRECT_BUFFER);
	_gpuEdges->_edges->bindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_edgesIdsToGenerate->bindBase(GL_SHADER_STORAGE_BUFFER, 1);
	_silhouetteEdgeCsVBO->bindBase(GL_SHADER_STORAGE_BUFFER, 2);
	_indirectDrawBufferSilhouetteCS->bindBase(GL_SHADER_STORAGE_BUFFER, 3);
	_indirectDispatchCsSilhouette->unbindRange(GL_SHADER_STORAGE_BUFFER, 4);

	assert(GL_NO_ERROR == ge::gl::glGetError());
}

void OctreeSidesDrawer::_drawSidesCS(const glm::mat4& mvp, const glm::vec4& lightPos)
{
	if (_timer) _timer->stamp("");
	_generateSidesFromPotentialCS(lightPos);
	if (_timer) _timer->stamp("PotentialEdges");
	_generateSidesFromSilhouetteCS();
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

	assert(GL_NO_ERROR == ge::gl::glGetError());
}

void OctreeSidesDrawer::_allocSubBuffersDataBuffers()
{
	m_nofPotBuffers = std::make_shared<ge::gl::Buffer>(sizeof(uint32_t), nullptr);
	m_nofSilBuffers = std::make_shared<ge::gl::Buffer>(sizeof(uint32_t), nullptr);

	m_potSuBuffers = std::make_shared<ge::gl::Buffer>(m_dataStride * m_maxNofPotBuffers * sizeof(uint32_t));
	m_silSuBuffers = std::make_shared<ge::gl::Buffer>(m_dataStride * m_maxNofSilBuffers * sizeof(uint32_t));
	
	if(m_prefixSumShaderTwoLevel)
	{
		m_prefixSumTmp[0] = std::make_shared<ge::gl::Buffer>(m_prefixSumWorkgroupSizeTwoLevel *sizeof(uint32_t));
		m_prefixSumTmp[1] = std::make_shared<ge::gl::Buffer>(m_prefixSumWorkgroupSizeTwoLevel *sizeof(uint32_t));

		m_prefixSumTmpAtomic[0] = std::make_shared<ge::gl::Buffer>(sizeof(uint32_t));
		m_prefixSumTmpAtomic[1] = std::make_shared<ge::gl::Buffer>(sizeof(uint32_t));
	}
}

void OctreeSidesDrawer::_calcSingleTwoLevelPrefixSumWgSizes(uint32_t maxNofPotSubBuffs, uint32_t maxNofSilSubBuffs)
{
	const uint32_t minumumWgSize = 128;
	const uint32_t twoLevelDefault = 256;

	uint32_t singlePot = 0;
	uint32_t singleSil = 0;
	uint32_t twoLevel = 0;

	if(maxNofPotSubBuffs <= MAX_NOF_SUBBUFFERS_SINGLE_PASS)
	{
		const uint32_t w = _getNearstLowerPow2(maxNofPotSubBuffs);
		singlePot = std::max(minumumWgSize, w);
	}
	else
	{
		twoLevel = twoLevelDefault;
		singlePot = std::max(minumumWgSize, uint32_t(ceil(float(maxNofPotSubBuffs)/ (2 * twoLevel))));
	}

	if (maxNofSilSubBuffs <= MAX_NOF_SUBBUFFERS_SINGLE_PASS)
	{
		const uint32_t w = _getNearstLowerPow2(maxNofSilSubBuffs);
		singleSil = std::max(minumumWgSize, w);
	}
	else
	{
		twoLevel = twoLevelDefault;
		singleSil = std::max(minumumWgSize, uint32_t(ceil(float(maxNofSilSubBuffs) / (2*twoLevel))));
	}

	m_prefixSumWorkgroupSizeTwoLevel = twoLevel;
	m_prefixSumWorkgroupSizeSingle = std::max(singlePot, singleSil);
}

uint32_t OctreeSidesDrawer::_getNearstLowerPow2(uint32_t x) const
{
	uint32_t n = x / 2;
	n--;
	n |= n >> 1;
	n |= n >> 2;
	n |= n >> 4;
	n |= n >> 8;
	n |= n >> 16;
	n++;

	return n;
}

bool OctreeSidesDrawer::_generateLoadGpuTraversalShader3()
{
	const std::string shaderBody1 = genBufferPreprocessShader(_lastNodePerEdgeBuffer, _octreeVisitor->getOctree(), _workgroupSize);

	m_subBuffersPreprocessShader = std::make_shared<ge::gl::Program>(
		std::make_shared<ge::gl::Shader>(GL_COMPUTE_SHADER, shaderBody1));

	_octreeVisitor->getMaxNofSubBuffersPotSil(m_maxNofPotBuffers, m_maxNofSilBuffers);
	_calcSingleTwoLevelPrefixSumWgSizes(m_maxNofPotBuffers, m_maxNofSilBuffers);

	const std::string shaderBody2s = genPrefixSumKernelSimple(m_prefixSumWorkgroupSizeSingle);
	if (m_prefixSumWorkgroupSizeTwoLevel)
	{
		const std::string shaderBody2t = genPrefixSumKernelTwoLevel(m_prefixSumWorkgroupSizeTwoLevel);

		m_prefixSumShaderTwoLevel = std::make_shared<ge::gl::Program>(
			std::make_shared<ge::gl::Shader>(GL_COMPUTE_SHADER, shaderBody2t));
	}

	m_prefixSumShaderSimple = std::make_shared<ge::gl::Program>(
		std::make_shared<ge::gl::Shader>(GL_COMPUTE_SHADER, shaderBody2s));

	const std::string shaderBody3 = genCopyShader3(_lastNodePerEdgeBuffer, _workgroupSize);

	m_getDataFromPrecomputedBuffersShader2 = std::make_shared<ge::gl::Program>(
		std::make_shared<ge::gl::Shader>(GL_COMPUTE_SHADER, shaderBody3));

	m_dataStride = _gpuOctreeBuffers.size() > 1 ? 4 : 2;

	const std::string addProgram = generateSummationKernel(m_prefixSumWorkgroupSizeSummation);
	m_prefixSumShaderAdd = std::make_shared<ge::gl::Program>(
		std::make_shared<ge::gl::Shader>(GL_COMPUTE_SHADER, addProgram));

	_allocSubBuffersDataBuffers();

	return m_prefixSumShaderSimple->getValidateStatus() && m_subBuffersPreprocessShader->getValidateStatus() && m_getDataFromPrecomputedBuffersShader2->getValidateStatus();
}

void OctreeSidesDrawer::_calcPrefixSum(
	std::shared_ptr<ge::gl::Buffer> input, 
	std::shared_ptr<ge::gl::Buffer> output, 
	std::shared_ptr<ge::gl::Buffer> count, 
	uint32_t worstCase, 
	uint32_t tmpIndex)
{
	if(worstCase <= MAX_NOF_SUBBUFFERS_SINGLE_PASS)
	{
		m_prefixSumShaderSimple->use();

		uint32_t consts[4] = { m_dataStride, 0, m_dataStride, 0 };
		m_prefixSumShaderSimple->set4uiv("stridesOffsets", consts);
		
		input->bindBase(GL_SHADER_STORAGE_BUFFER, 0);
		output->bindBase(GL_SHADER_STORAGE_BUFFER, 1);
		count->bindBase(GL_SHADER_STORAGE_BUFFER, 2);

		ge::gl::glDispatchCompute(1, 1, 1);

		input->unbindBase(GL_SHADER_STORAGE_BUFFER, 0);
		output->unbindBase(GL_SHADER_STORAGE_BUFFER, 1);
		count->unbindBase(GL_SHADER_STORAGE_BUFFER, 2);
	}
	else
	{
		//1st pass
		m_prefixSumShaderTwoLevel->use();

		uint32_t consts[4] = { m_dataStride, 0, m_dataStride, 0 };
		m_prefixSumShaderTwoLevel->set4uiv("stridesOffsets", consts);

		uint32_t binding = 0;

		input->bindBase(GL_SHADER_STORAGE_BUFFER, binding++);
		output->bindBase(GL_SHADER_STORAGE_BUFFER, binding++);
		count->bindBase(GL_SHADER_STORAGE_BUFFER, binding++);
		m_prefixSumTmp[tmpIndex]->bindBase(GL_SHADER_STORAGE_BUFFER, binding++);
		m_prefixSumTmpAtomic[tmpIndex]->bindBase(GL_SHADER_STORAGE_BUFFER, binding++);

		ge::gl::glDispatchCompute(uint32_t(ceil(float(worstCase) / float(2*m_prefixSumWorkgroupSizeTwoLevel))), 1, 1);

		ge::gl::glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

		//2nd pass
		binding = 0;
		m_prefixSumShaderSimple->use();

		uint32_t consts1[4] = { 1, 0, 1, 0 };
		m_prefixSumShaderSimple->set4uiv("stridesOffsets", consts1);
		m_prefixSumTmp[tmpIndex]->bindBase(GL_SHADER_STORAGE_BUFFER, binding++);
		m_prefixSumTmp[tmpIndex]->bindBase(GL_SHADER_STORAGE_BUFFER, binding++);
		m_prefixSumTmpAtomic[tmpIndex]->bindBase(GL_SHADER_STORAGE_BUFFER, binding++);

		ge::gl::glDispatchCompute(1, 1, 1);

		ge::gl::glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

		//Summation
		m_prefixSumShaderAdd->use();
		m_prefixSumShaderAdd->set1ui("previousWgSize", m_prefixSumWorkgroupSizeTwoLevel);
		m_prefixSumShaderAdd->set2uiv("outputStrideOffset", &consts[2]);
		output->bindBase(GL_SHADER_STORAGE_BUFFER, 0);
		m_prefixSumTmp[tmpIndex]->bindBase(GL_SHADER_STORAGE_BUFFER, 1);
		count->bindBase(GL_SHADER_STORAGE_BUFFER, 2);

		ge::gl::glDispatchCompute(uint32_t(ceil(float(worstCase) / float(m_prefixSumWorkgroupSizeSummation))), 1, 1);
	}
}

void OctreeSidesDrawer::_calcPrefixSums()
{
	if(m_prefixSumShaderTwoLevel)
	{
		const uint32_t zero = 0;
		m_prefixSumTmpAtomic[0]->setData(&zero, sizeof(uint32_t));
		m_prefixSumTmpAtomic[1]->setData(&zero, sizeof(uint32_t));
	}

	_calcPrefixSum(m_potSuBuffers, m_potSuBuffers, m_nofPotBuffers, m_maxNofPotBuffers, 0);
	_calcPrefixSum(m_silSuBuffers, m_silSuBuffers, m_nofSilBuffers, m_maxNofSilBuffers, 1);
}

void OctreeSidesDrawer::_getPotentialSilhouetteEdgesGpu3(uint32_t lowestNodeContainingLight)
{
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

	uint32_t bindingPoint = 0;

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

	ge::gl::glDispatchCompute(GLuint(ceil(float(m_maxNofPotBuffers + m_maxNofSilBuffers) / float(_workgroupSize))), 1, 1);

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
	
	//Prefix sum
	_calcPrefixSums();

	ge::gl::glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

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

	ge::gl::glDispatchCompute(GLuint(ceil(float(_maxNofEdgesPath) / float(_workgroupSize))), 1, 1);

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
}