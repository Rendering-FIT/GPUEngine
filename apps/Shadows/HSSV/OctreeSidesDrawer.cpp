#include "OctreeSidesDrawer.hpp"
#include "GenerateSidesProgram.hpp"
#include <geGL/StaticCalls.h>
#include "MultiplicityCoding.hpp"
#include "../CSSVShaders.h"

#define MAX_MULTIPLICITY 2

OctreeSidesDrawer::OctreeSidesDrawer(std::shared_ptr<OctreeVisitor> visitor, unsigned int workgroupSize, DrawingMethod potential, DrawingMethod silhouette) : 
	_octreeVisitor(visitor), _workgroupSize(workgroupSize), _potentialDrawingMethod(potential), _silhouetteDrawingMethod(silhouette)
{
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

void OctreeSidesDrawer::init(std::shared_ptr<GpuEdges> gpuEdges)
{
	_initShaders();

	_initBuffers();

	_gpuEdges = gpuEdges;
}

void OctreeSidesDrawer::_initBuffers()
{
	size_t maxPotentialEdges, maxSilhouetteEdges;
	_getMaxPossibleEdgeCountInTraversal(maxPotentialEdges, maxSilhouetteEdges);
	
	_edgesIdsToGenerate =        std::make_shared<ge::gl::Buffer>(maxSilhouetteEdges* sizeof(uint32_t), nullptr);
	_edgesIdsToTestAndGenerate = std::make_shared<ge::gl::Buffer>(maxPotentialEdges * sizeof(uint32_t), nullptr);

	if(_potentialDrawingMethod!=DrawingMethod::CS || _silhouetteDrawingMethod!=DrawingMethod::CS)
		_dummyVAO = std::make_shared<ge::gl::VertexArray>();

	const uint32_t indirectBuffer[4] = { 0, 1, 0, 0 };

	if (_potentialDrawingMethod == DrawingMethod::CS)
	{
		_indirectDrawBufferPotentialCS = std::make_shared<ge::gl::Buffer>(4 * sizeof(uint32_t), indirectBuffer);
		_potentialEdgeCsVBO = std::make_shared<ge::gl::Buffer>(MAX_MULTIPLICITY * maxPotentialEdges * 4 * sizeof(float), nullptr);

		_potentialSidesCsVAO = std::make_shared<ge::gl::VertexArray>();
		_potentialSidesCsVAO->addAttrib(_potentialEdgeCsVBO, 0, 4, GL_FLOAT);
	}

	if (_silhouetteDrawingMethod == DrawingMethod::CS)
	{
		_indirectDrawBufferSilhouetteCS = std::make_shared<ge::gl::Buffer>(4 * sizeof(uint32_t), indirectBuffer);
		_silhouetteEdgeCsVBO = std::make_shared<ge::gl::Buffer>(MAX_MULTIPLICITY * maxSilhouetteEdges * 4 * sizeof(float), nullptr);

		_silhouetteSidesCsVAO = std::make_shared<ge::gl::VertexArray>();
		_silhouetteSidesCsVAO->addAttrib(_silhouetteEdgeCsVBO, 0, 4, GL_FLOAT);
	}
}

void OctreeSidesDrawer::_getMaxPossibleEdgeCountInTraversal(size_t& potential, size_t& silhouette) const
{
	potential = 0;
	silhouette = 0;

	const unsigned int maxLevel = _octreeVisitor->getOctree()->getDeepestLevel();
	for (unsigned int i = 0; i <= maxLevel; ++i)
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
	if (_lastFrameCellIndex != int(cellContainingLightId))
	{
		_nofSilhouetteEdgesToDraw = _loadEdgesFromIdUpGetNof(cellContainingLightId, true);
		std::cout << "Acquiring " << _nofSilhouetteEdgesToDraw << " silhouette edges\n";
	}

	if (!_nofSilhouetteEdgesToDraw)
		return;

	auto err = ge::gl::glGetError();
	assert(err == GL_NO_ERROR);

	_silhouetteSidesTsProgram->use();
	_silhouetteSidesTsProgram->setMatrix4fv("mvp", glm::value_ptr(mvp))->set4fv("lightPosition", glm::value_ptr(lightPos));

	_dummyVAO->bind();

	_gpuEdges->_edges->bindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_edgesIdsToGenerate->bindBase(GL_SHADER_STORAGE_BUFFER, 1);

	ge::gl::glPatchParameteri(GL_PATCH_VERTICES, 1);
	ge::gl::glDrawArrays(GL_PATCHES, 0, _nofSilhouetteEdgesToDraw);
	
	_gpuEdges->_edges->unbindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_edgesIdsToGenerate->unbindBase(GL_SHADER_STORAGE_BUFFER, 1);

	_dummyVAO->unbind();

	err = ge::gl::glGetError();
	assert(err == GL_NO_ERROR);
}

void OctreeSidesDrawer::_drawSidesFromSilhouetteEdgesGS(const glm::mat4& mvp, const glm::vec4& lightPos, unsigned cellContainingLightId)
{
	if (_lastFrameCellIndex != int(cellContainingLightId))
	{
		_nofSilhouetteEdgesToDraw = _loadEdgesFromIdUpGetNof(cellContainingLightId, true);
		std::cout << "Acquiring " << _nofSilhouetteEdgesToDraw << " silhouette edges\n";
	}

	if (!_nofSilhouetteEdgesToDraw)
		return;

	auto err = ge::gl::glGetError();
	assert(err == GL_NO_ERROR);

	_silhouetteSidesGsProgram->use();
	_silhouetteSidesGsProgram->setMatrix4fv("mvp", glm::value_ptr(mvp))->set4fv("lightPosition", glm::value_ptr(lightPos));

	_dummyVAO->bind();

	_gpuEdges->_edges->bindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_edgesIdsToGenerate->bindBase(GL_SHADER_STORAGE_BUFFER, 1);

	ge::gl::glDrawArrays(GL_POINTS, 0, _nofSilhouetteEdgesToDraw);

	_gpuEdges->_edges->unbindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_edgesIdsToGenerate->unbindBase(GL_SHADER_STORAGE_BUFFER, 1);
	
	_dummyVAO->unbind();

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
	if (_lastFrameCellIndex != int(cellContainingLightId))
	{
		_nofPotentialEdgesToDraw = _loadEdgesFromIdUpGetNof(cellContainingLightId, false);
		std::cout << "Acquiring " << _nofPotentialEdgesToDraw << " potential edges\n";
	}

	if (!_nofPotentialEdgesToDraw)
		return;
	auto err = ge::gl::glGetError();
	assert(err == GL_NO_ERROR);

	_potentialTsProgram->use();
	_potentialTsProgram->setMatrix4fv("mvp", glm::value_ptr(mvp))->set4fv("lightPosition", glm::value_ptr(lightPos));

	_dummyVAO->bind();

	_gpuEdges->_edges->bindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_gpuEdges->_oppositeVertices->bindBase(GL_SHADER_STORAGE_BUFFER, 1);
	_edgesIdsToTestAndGenerate->bindBase(GL_SHADER_STORAGE_BUFFER, 2);

	ge::gl::glPatchParameteri(GL_PATCH_VERTICES, 1);
	ge::gl::glDrawArrays(GL_PATCHES, 0, _nofPotentialEdgesToDraw);

	_gpuEdges->_edges->unbindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_gpuEdges->_oppositeVertices->unbindBase(GL_SHADER_STORAGE_BUFFER, 1);
	_edgesIdsToTestAndGenerate->unbindBase(GL_SHADER_STORAGE_BUFFER, 2);

	_dummyVAO->unbind();

	err = ge::gl::glGetError();
	assert(err == GL_NO_ERROR);
}

void OctreeSidesDrawer::_drawSidesFromPotentialEdgesGS(const glm::mat4& mvp, const glm::vec4& lightPos, unsigned cellContainingLightId)
{
	assert(ge::gl::glGetError() == GL_NO_ERROR);

	if (_lastFrameCellIndex != int(cellContainingLightId))
	{
		_nofPotentialEdgesToDraw = _loadEdgesFromIdUpGetNof(cellContainingLightId, false);
		std::cout << "Acquiring " << _nofPotentialEdgesToDraw << " potential edges\n";
	}

	if (!_nofPotentialEdgesToDraw)
		return;

	_potentialGsProgram->use();
	_potentialGsProgram->setMatrix4fv("mvp", glm::value_ptr(mvp))->set4fv("lightPosition", glm::value_ptr(lightPos));

	_dummyVAO->bind();

	_gpuEdges->_edges->bindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_gpuEdges->_oppositeVertices->bindBase(GL_SHADER_STORAGE_BUFFER, 1);
	_edgesIdsToTestAndGenerate->bindBase(GL_SHADER_STORAGE_BUFFER, 2);

	ge::gl::glDrawArrays(GL_POINTS, 0, _nofPotentialEdgesToDraw);

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

	if (_lastFrameCellIndex != int(cellContainingLightId))
	{
		_nofPotentialEdgesToDraw = _loadEdgesFromIdUpGetNof(cellContainingLightId, false);
		std::cout << "Acquiring " << _nofPotentialEdgesToDraw << " potential edges\n";
	}

	if (!_nofPotentialEdgesToDraw)
		return;

	const uint32_t zero = 0;
	_indirectDrawBufferPotentialCS->setData(&zero, sizeof(uint32_t));

	_testAndGenerateSidesProgram->use();
	_testAndGenerateSidesProgram->set4fv("lightPosition", glm::value_ptr(lightPos))->set1ui("nofEdgesToTest", _nofPotentialEdgesToDraw);
	_gpuEdges->_edges->bindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_gpuEdges->_oppositeVertices->bindBase(GL_SHADER_STORAGE_BUFFER, 1);
	_edgesIdsToTestAndGenerate->bindBase(GL_SHADER_STORAGE_BUFFER, 2);
	_potentialEdgeCsVBO->bindBase(GL_SHADER_STORAGE_BUFFER, 3);
	_indirectDrawBufferPotentialCS->bindBase(GL_SHADER_STORAGE_BUFFER, 4);

	ge::gl::glDispatchCompute(ceil(float(_nofPotentialEdgesToDraw) / (_workgroupSize)), 1, 1);
	//ge::gl::glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

	_gpuEdges->_edges->unbindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_gpuEdges->_oppositeVertices->unbindBase(GL_SHADER_STORAGE_BUFFER, 1);
	_edgesIdsToTestAndGenerate->unbindBase(GL_SHADER_STORAGE_BUFFER, 2);
	_potentialEdgeCsVBO->unbindBase(GL_SHADER_STORAGE_BUFFER, 3);
	_indirectDrawBufferPotentialCS->unbindBase(GL_SHADER_STORAGE_BUFFER, 4);

	assert(ge::gl::glGetError() == GL_NO_ERROR);
}

void OctreeSidesDrawer::_generateSidesFromSilhouetteCS(const glm::vec4& lightPos, unsigned cellContainingLightId)
{
	if (_lastFrameCellIndex != int(cellContainingLightId))
	{
		_nofSilhouetteEdgesToDraw = _loadEdgesFromIdUpGetNof(cellContainingLightId, true);
		std::cout << "Acquiring " << _nofSilhouetteEdgesToDraw << " silhouette edges\n";
	}

	if (!_nofSilhouetteEdgesToDraw)
		return;

	const uint32_t zero = 0;
	_indirectDrawBufferSilhouetteCS->setData(&zero, sizeof(uint32_t));

	_generateSidesProgram->use();
	_generateSidesProgram->set1ui("nofEdgesToGenerate", _nofSilhouetteEdgesToDraw);

	_gpuEdges->_edges->bindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_edgesIdsToGenerate->bindBase(GL_SHADER_STORAGE_BUFFER, 1);
	_silhouetteEdgeCsVBO->bindBase(GL_SHADER_STORAGE_BUFFER, 2);
	_indirectDrawBufferSilhouetteCS->bindBase(GL_SHADER_STORAGE_BUFFER, 3);

	ge::gl::glDispatchCompute(ceil(float(_nofSilhouetteEdgesToDraw) / (_workgroupSize)), 1, 1);

	_gpuEdges->_edges->bindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_edgesIdsToGenerate->bindBase(GL_SHADER_STORAGE_BUFFER, 1);
	_silhouetteEdgeCsVBO->bindBase(GL_SHADER_STORAGE_BUFFER, 2);
	_indirectDrawBufferSilhouetteCS->bindBase(GL_SHADER_STORAGE_BUFFER, 3);
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
