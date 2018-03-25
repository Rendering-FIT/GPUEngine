#include "OctreeSidesDrawer.hpp"
#include "../CSSVShaders.h"
#include "GenerateSidesProgram.hpp"
#include <geGL/StaticCalls.h>

#define MAX_MULTIPLICITY 2

OctreeSidesDrawer::OctreeSidesDrawer(std::shared_ptr<OctreeVisitor> visitor, unsigned int subgroupSize) : _octreeVisitor(visitor), _subgroupSize(subgroupSize)
{
}

bool OctreeSidesDrawer::_initShaders(unsigned int subgroupSize)
{
	_drawSidesProgram = std::make_shared<ge::gl::Program>(
		std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, drawVPSrc),
		std::make_shared<ge::gl::Shader>(GL_TESS_CONTROL_SHADER, drawCPSrc),
		std::make_shared<ge::gl::Shader>(GL_TESS_EVALUATION_SHADER, drawEPSrc)
		);

	_generateSidesProgram = std::make_shared<ge::gl::Program>(
		std::make_shared<ge::gl::Shader>(GL_COMPUTE_SHADER,
			"#version 450 core\n",
			ge::gl::Shader::define("WORKGROUP_SIZE_X", int32_t(_subgroupSize * 4)),
			generateSidesCS)
		);

	_testAndGenerateSidesProgram = std::make_shared<ge::gl::Program>(
		std::make_shared<ge::gl::Shader>(GL_COMPUTE_SHADER,
			"#version 450 core\n",
			ge::gl::Shader::define("WORKGROUP_SIZE_X", int32_t(_subgroupSize * 4)),
			testAndGenerateSidesCS)
		);

	return _drawSidesProgram->isProgram() && _generateSidesProgram->isProgram() && _testAndGenerateSidesProgram->isProgram();
}

bool OctreeSidesDrawer::init(std::shared_ptr<GpuEdges> gpuEdges)
{
	if (!_initShaders(_subgroupSize))
		return false;

	_initBuffers();

	_gpuEdges = gpuEdges;
}

void OctreeSidesDrawer::_initBuffers()
{
	size_t maxPotentialEdges, maxSilhouetteEdges;

	_getMaxPossibleEdgeCountInTraversal(maxPotentialEdges, maxSilhouetteEdges);
	
	_vboPotential = std::make_shared<ge::gl::Buffer>(maxPotentialEdges * size_t(MAX_MULTIPLICITY)  * (16ul * sizeof(float)), nullptr);
	_vboSilhouette = std::make_shared<ge::gl::Buffer>(maxSilhouetteEdges * size_t(MAX_MULTIPLICITY)  * (16ul * sizeof(float)), nullptr);
	
	_edgesIdsToGenerate = std::make_shared<ge::gl::Buffer>(maxSilhouetteEdges * sizeof(uint32_t), nullptr);
	_edgesIdsToTestAndGenerate = std::make_shared<ge::gl::Buffer>(maxPotentialEdges*sizeof(uint32_t), nullptr);

	_sidesVaoPotential = std::make_shared<ge::gl::VertexArray>();
	_sidesVaoPotential->addAttrib(_vboPotential, 0, 3, GL_FLOAT);

	_sidesVaoSilhouette = std::make_shared<ge::gl::VertexArray>();
	_sidesVaoSilhouette->addAttrib(_vboSilhouette, 0, 3, GL_FLOAT);

	uint32_t indirectBuffer[4] = { 0 };
	_indirectDrawBufferPotential = std::make_shared<ge::gl::Buffer>(4 * sizeof(uint32_t), indirectBuffer);
	_indirectDrawBufferSilhouette = std::make_shared<ge::gl::Buffer>(4 * sizeof(uint32_t), indirectBuffer);
}


void OctreeSidesDrawer::_getMaxPossibleEdgeCountInTraversal(size_t& potential, size_t& silhouette) const
{
	const unsigned int maxLevel = _octreeVisitor->getOctree()->getDeepestLevel();
	for (unsigned int i = 0; i < maxLevel; ++i)
	{
		size_t pot=0, silh=0;
		_getMaximumNofEdgesInLevel(i, pot, silh);
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
	const auto cellIndex = _octreeVisitor->getOctree()->getLowestLevelCellIndexFromPointInSpace(glm::vec3(light));

	_genSidesFromSilhouetteEdges(cellIndex);

	_drawSidesFromSilhouetteEdges(mvp, light);
}

void OctreeSidesDrawer::_genSidesFromSilhouetteEdges(unsigned int cellContainingLightId)
{	
	const auto nofEdgesToGenerate = _loadSilhouetteEdgesFromIdUpGetNof(cellContainingLightId);

	_generateSidesProgram->use();
	_generateSidesProgram->set1ui("nofEdgesToGenerate", nofEdgesToGenerate);

	_gpuEdges->_edges->bindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_gpuEdges->_oppositeVertices->bindBase(GL_SHADER_STORAGE_BUFFER, 1);
	_vboSilhouette->bindBase(GL_SHADER_STORAGE_BUFFER, 2);
	_indirectDrawBufferSilhouette->bindBase(GL_SHADER_STORAGE_BUFFER, 3);

	//TODO - upravit tie pocty grup nejak
	ge::gl::glDispatchCompute(nofEdgesToGenerate/(4*_subgroupSize), 1, 1);

	_gpuEdges->_edges->unbindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_gpuEdges->_oppositeVertices->unbindBase(GL_SHADER_STORAGE_BUFFER, 1);
	_vboSilhouette->unbindBase(GL_SHADER_STORAGE_BUFFER, 2);
	_indirectDrawBufferSilhouette->unbindBase(GL_SHADER_STORAGE_BUFFER, 3);
}

unsigned int OctreeSidesDrawer::_loadSilhouetteEdgesFromIdUpGetNof(unsigned cellContainingLightId)
{
	const int deepestLevel = _octreeVisitor->getOctree()->getDeepestLevel();

	size_t currentPosition = 0;
	int currentCell = cellContainingLightId;
	unsigned int numLoaded = 0;

	for(int i = deepestLevel; i>=0; --i)
	{
		const auto n = _octreeVisitor->getOctree()->getNode(currentCell);
		const size_t edgesSize = n->edgesAlwaysCast.size() * sizeof(uint32_t);

		_edgesIdsToGenerate->setData(n->edgesAlwaysCast.data(), edgesSize, currentPosition);

		currentPosition += edgesSize;
		currentCell = _octreeVisitor->getOctree()->getNodeParent(currentCell);
		numLoaded += n->edgesAlwaysCast.size();
	}

	return numLoaded;
}

unsigned int OctreeSidesDrawer::_loadPotentialEdgesFromIdUpGetNof(unsigned int cellContainingLightId)
{
	const int deepestLevel = _octreeVisitor->getOctree()->getDeepestLevel();

	size_t currentPosition = 0;
	int currentCell = cellContainingLightId;
	unsigned int numLoaded = 0;

	for (int i = deepestLevel; i >= 0; --i)
	{
		const auto n = _octreeVisitor->getOctree()->getNode(currentCell);
		const size_t edgesSize = n->edgesMayCast.size() * sizeof(uint32_t);

		_edgesIdsToTestAndGenerate->setData(n->edgesMayCast.data(), edgesSize, currentPosition);

		currentPosition += edgesSize;
		currentCell = _octreeVisitor->getOctree()->getNodeParent(currentCell);
		numLoaded += n->edgesMayCast.size();
	}

	return numLoaded;
}

void OctreeSidesDrawer::_drawSidesFromSilhouetteEdges(const glm::mat4& mvp, const glm::vec4& lightPos)
{
	_drawSidesProgram->use();
	_drawSidesProgram->setMatrix4fv("mvp", glm::value_ptr(mvp))->set4fv("lightPosition", glm::value_ptr(lightPos));

	_sidesVaoSilhouette->bind();
	_indirectDrawBufferSilhouette->bind(GL_DRAW_INDIRECT_BUFFER);

	ge::gl::glPatchParameteri(GL_PATCH_VERTICES, 2);
	ge::gl::glDrawArraysIndirect(GL_PATCHES, NULL);

	_indirectDrawBufferSilhouette->unbind(GL_DRAW_INDIRECT_BUFFER);
	_sidesVaoSilhouette->unbind();	
}