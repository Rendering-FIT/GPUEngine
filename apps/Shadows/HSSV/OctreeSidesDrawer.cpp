#include "OctreeSidesDrawer.hpp"
#include "../CSSVShaders.h"
#include "GenerateSidesProgram.hpp"
#include <geGL/StaticCalls.h>
#include "MultiplicityCoding.hpp"

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

	/*
	_generateSidesProgram = std::make_shared<ge::gl::Program>(
		std::make_shared<ge::gl::Shader>(GL_COMPUTE_SHADER,
			"#version 450 core\n",
			ge::gl::Shader::define("WORKGROUP_SIZE_X", int32_t(_subgroupSize * 4)),
			generateSidesCS)
		);
	*/

	_generateAndDrawSidesProgram = std::make_shared<ge::gl::Program>(
		std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, silhouetteSidesVS),
		std::make_shared<ge::gl::Shader>(GL_TESS_CONTROL_SHADER, silhouetteSidesTCS),
		std::make_shared<ge::gl::Shader>(GL_TESS_EVALUATION_SHADER, silhouetteSidesTES),
		std::make_shared<ge::gl::Shader>(GL_GEOMETRY_SHADER, 
			"#version 450 core\n",
			ge::gl::Shader::define("MAX_VERTICES", int32_t(3*MAX_MULTIPLICITY)),
			silhouetteSidesGS)
		);

	_testAndGenerateSidesProgram = std::make_shared<ge::gl::Program>(
		std::make_shared<ge::gl::Shader>(GL_COMPUTE_SHADER,
			"#version 450 core\n",
			ge::gl::Shader::define("WORKGROUP_SIZE_X", int32_t(_subgroupSize * 4)),
			testAndGenerateSidesCS)
		);

	_genDrawSidesGS = std::make_shared<ge::gl::Program>(
		std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, silhouetteSidesVS),
		std::make_shared<ge::gl::Shader>(GL_GEOMETRY_SHADER, silhouetteSidesGS2)
		);

	return _drawSidesProgram->isProgram() && _generateAndDrawSidesProgram->isProgram() && _testAndGenerateSidesProgram->isProgram();
}

bool OctreeSidesDrawer::init(std::shared_ptr<GpuEdges> gpuEdges)
{
	if (!_initShaders(_subgroupSize))
		return false;

	_initBuffers();

	_gpuEdges = gpuEdges;

	return true;
}

void OctreeSidesDrawer::_initBuffers()
{
	size_t maxPotentialEdges, maxSilhouetteEdges;

	_getMaxPossibleEdgeCountInTraversal(maxPotentialEdges, maxSilhouetteEdges);
	
	_vboPotential = std::make_shared<ge::gl::Buffer>(maxPotentialEdges * size_t(MAX_MULTIPLICITY)  * (16ul * sizeof(float)), nullptr);
	//_vboSilhouette = std::make_shared<ge::gl::Buffer>(maxSilhouetteEdges * size_t(MAX_MULTIPLICITY)  * (16ul * sizeof(float)), nullptr);
	
	_edgesIdsToGenerate = std::make_shared<ge::gl::Buffer>(maxSilhouetteEdges * sizeof(uint32_t), nullptr);
	_edgesIdsToTestAndGenerate = std::make_shared<ge::gl::Buffer>(maxPotentialEdges*sizeof(uint32_t), nullptr);

	_sidesVaoPotential = std::make_shared<ge::gl::VertexArray>();
	_sidesVaoPotential->addAttrib(_vboPotential, 0, 4, GL_FLOAT);

	_sidesVaoSilhouette = std::make_shared<ge::gl::VertexArray>();
	//_sidesVaoSilhouette->addAttrib(_vboSilhouette, 0, 4, GL_FLOAT);

	uint32_t indirectBuffer[4] = { 0, 1, 0, 0 };
	_indirectDrawBufferPotential = std::make_shared<ge::gl::Buffer>(4 * sizeof(uint32_t), indirectBuffer);
	//_indirectDrawBufferSilhouette = std::make_shared<ge::gl::Buffer>(4 * sizeof(uint32_t), indirectBuffer);


	_atomicCounter = std::make_shared<ge::gl::Buffer>(sizeof(uint32_t), &indirectBuffer[0]);
	_edgeDump = std::make_shared<ge::gl::Buffer>(4*maxSilhouetteEdges*2*4*sizeof(float), nullptr);
}


void OctreeSidesDrawer::_getMaxPossibleEdgeCountInTraversal(size_t& potential, size_t& silhouette) const
{
	potential = 0;
	silhouette = 0;

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
	const auto cellIndex = _octreeVisitor->getLowestNodeIndexFromPoint(glm::vec3(light));

	//_drawSidesFromSilhouetteEdges(mvp, light, cellIndex);
	_drawSidesFromSilhouetteEdgesGS(mvp, light, cellIndex);
}

/*
void OctreeSidesDrawer::_genSidesFromSilhouetteEdgesCS(unsigned int cellContainingLightId)
{	
	const auto nofEdgesToGenerate = _loadEdgesFromIdUpGetNof(cellContainingLightId, true);
	const uint32_t zero = 0;
	
	_indirectDrawBufferSilhouette->setData(&zero, sizeof(uint32_t));

	_generateSidesProgram->use();
	_generateSidesProgram->set1ui("nofEdgesToGenerate", nofEdgesToGenerate);

	_gpuEdges->_edges->bindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_edgesIdsToGenerate->bindBase(GL_SHADER_STORAGE_BUFFER, 1);
	_vboSilhouette->bindBase(GL_SHADER_STORAGE_BUFFER, 2);
	_indirectDrawBufferSilhouette->bindBase(GL_SHADER_STORAGE_BUFFER, 3);

	//TODO - upravit tie pocty grup nejak
	ge::gl::glDispatchCompute(ceil(nofEdgesToGenerate/(4.0f*_subgroupSize)), 1, 1);

	_gpuEdges->_edges->unbindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_edgesIdsToGenerate->unbindBase(GL_SHADER_STORAGE_BUFFER, 1);
	_vboSilhouette->unbindBase(GL_SHADER_STORAGE_BUFFER, 2);
	_indirectDrawBufferSilhouette->unbindBase(GL_SHADER_STORAGE_BUFFER, 3);
}
*/

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

void OctreeSidesDrawer::_drawSidesFromSilhouetteEdges(const glm::mat4& mvp, const glm::vec4& lightPos, unsigned int cellContainingLightId)
{
	const auto nofEdgesToGenerate = _loadEdgesFromIdUpGetNof(cellContainingLightId, true);
	
	_generateAndDrawSidesProgram->use();
	_generateAndDrawSidesProgram->setMatrix4fv("mvp", glm::value_ptr(mvp))->set4fv("lightPosition", glm::value_ptr(lightPos));
	const uint32_t zero = 0;
	_atomicCounter->setData(&zero, sizeof(uint32_t));

	_sidesVaoSilhouette->bind();
	_gpuEdges->_edges->bindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_edgesIdsToGenerate->bindBase(GL_SHADER_STORAGE_BUFFER, 1);
	_edgeDump->bindBase(GL_SHADER_STORAGE_BUFFER, 2);
	_atomicCounter->bindBase(GL_SHADER_STORAGE_BUFFER, 3);

	ge::gl::glPatchParameteri(GL_PATCH_VERTICES, 1);
	ge::gl::glDrawArrays(GL_PATCHES, 0, nofEdgesToGenerate);

	ge::gl::glFinish();
	/*
	const auto ptr = _edgeDump->map(GL_READ_ONLY);
	std::vector<glm::vec4> vec;
	vec.resize(4*2*nofEdgesToGenerate);
	memcpy(vec.data(), ptr, 4*nofEdgesToGenerate * 2 * 4 * sizeof(float));
	_edgeDump->unmap();

	

	const auto edgePtr = _gpuEdges->_edges->map(GL_READ_ONLY);
	std::vector<float> ee;
	const auto sz = _gpuEdges->_edges->getSize() / (sizeof(float));
	ee.resize(sz);
	memcpy(ee.data(), edgePtr, _gpuEdges->_edges->getSize());
	_gpuEdges->_edges->unmap();


	std::vector<uint32_t> vvv;
	vvv.resize(nofEdgesToGenerate);
	_edgesIdsToGenerate->getData(vvv.data());

	for (auto d : vvv)
	{
		const auto real = decodeEdgeFromEncoded(d);
		std::cout << ee[8 * real + 0] << ", " << ee[8 * real + 1] << ", " << ee[8 * real + 2] << std::endl;
		std::cout << ee[8 * real + 3] << ", " << ee[8 * real + 4] << ", " << ee[8 * real + 5] << std::endl << std::endl;
	}

	std::cout << "--------------\n";

	int node = cellContainingLightId;

	while (node > 0)
	{
		const auto nn = _octreeVisitor->getOctree()->getNode(node);
		
		for (auto const& d : nn->edgesAlwaysCast)
		{
			std::cout << decodeEdgeMultiplicityFromId(d) << std::endl;
		}

		node = _octreeVisitor->getOctree()->getNodeParent(node);
	}
	*/
	_sidesVaoSilhouette->unbind();	
}

void OctreeSidesDrawer::_drawSidesFromSilhouetteEdgesGS(const glm::mat4& mvp, const glm::vec4& lightPos, unsigned cellContainingLightId)
{
	const auto nofEdgesToGenerate = _loadEdgesFromIdUpGetNof(cellContainingLightId, true);

	_genDrawSidesGS->use();
	_genDrawSidesGS->setMatrix4fv("mvp", glm::value_ptr(mvp))->set4fv("lightPosition", glm::value_ptr(lightPos));

	_sidesVaoSilhouette->bind();
	_gpuEdges->_edges->bindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_edgesIdsToGenerate->bindBase(GL_SHADER_STORAGE_BUFFER, 1);
	
	ge::gl::glDrawArrays(GL_POINTS, 0, nofEdgesToGenerate);

	_gpuEdges->_edges->unbindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_edgesIdsToGenerate->unbindBase(GL_SHADER_STORAGE_BUFFER, 1);
	
	_sidesVaoSilhouette->unbind();
}
