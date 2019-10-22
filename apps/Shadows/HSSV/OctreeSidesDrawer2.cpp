#include "OctreeSidesDrawer2.hpp"
#include "OctreeVisitor.hpp"
#include "GenerateSidesDataOnGpuProgram.hpp"
#include "geGL/StaticCalls.h"
//--
#include "MultiplicityCoding.hpp"
//--

OctreeSidesDrawer2::OctreeSidesDrawer2(std::shared_ptr<OctreeVisitor> octreeVisitor, uint32_t subgroupSize) : IGpuOctreeSidesDrawer(octreeVisitor)
{
}

bool OctreeSidesDrawer2::init(std::shared_ptr<GpuEdges> gpuEdges)
{
	_initBuffers();

	_initShaders();
	
	if (m_compressionLevel == 0)
	{
		_loadOctreeToGpu8BitOrNoCompress();
	}
	else if (m_compressionLevel == 1)
	{
		_loadOctreeToGpu8BitOrNoCompress();
	}
	else //64b
	{
		_loadOctreeToGpu();
	}

	m_gpuEdges = gpuEdges;

	return true;
}


void OctreeSidesDrawer2::_initBuffers()
{
	size_t maxPotentialEdges, maxSilhouetteEdges, maxEdges, maxPath;
	_getMaxPossibleEdgeCountInTraversal(maxPotentialEdges, maxSilhouetteEdges, maxEdges, maxPath);

	_loadBitmaskBuffer();

	m_dataStride = m_gpuOctreeBuffers.size() > 1 ? 4 : 2;
	_visitor->getMaxNofSubBuffersPotSil(m_maxNofPotBuffers, m_maxNofSilBuffers);

	//Max nof edges pot + sil, expanded as sides with 6 vertices, 4 floats each
	m_edgeVBO = std::make_shared<ge::gl::Buffer>(OCTREE_MAX_MULTIPLICITY * (maxSilhouetteEdges + maxPotentialEdges ) * 6 * 4 * sizeof(float), nullptr);

	m_VAO = std::make_shared<ge::gl::VertexArray>();
	m_VAO->addAttrib(m_edgeVBO, 0, 4, GL_FLOAT);

	const uint32_t indirectData[4] = { 0, 1, 0, 0 };
	m_IBO = std::make_shared<ge::gl::Buffer>((sizeof(indirectData)/sizeof(uint32_t)) * sizeof(uint32_t), indirectData);

	m_nofPotSilBuffers = std::make_shared<ge::gl::Buffer>(4 * sizeof(uint32_t), nullptr);
	m_potSubBuffers = std::make_shared<ge::gl::Buffer>(m_dataStride * m_maxNofPotBuffers * sizeof(uint32_t));
	m_silSubBuffers = std::make_shared<ge::gl::Buffer>(m_dataStride * m_maxNofSilBuffers * sizeof(uint32_t));

	shit = std::make_shared<ge::gl::Buffer>(1024 * sizeof(uint32_t));
}

void OctreeSidesDrawer2::_loadBitmaskBuffer()
{
	_calcBitMasks8(3);

	m_bitmasksBuffer = std::make_shared<ge::gl::Buffer>(8 * _getNofIndicesPerBitmask() * sizeof(uint32_t));

	std::vector<uint32_t> data;
	data.resize(8 * _getNofIndicesPerBitmask());
	uint32_t* ptr = data.data();

	uint32_t currentOffset = 0;

	for (auto const& b : m_bitMasks)
	{
		auto const sz = b.size();
		memcpy(ptr + currentOffset, b.data(), sz * sizeof(uint32_t));
		currentOffset += uint32_t(sz);
	}

	m_bitmasksBuffer->setData(ptr, data.size() * sizeof(uint32_t));
}

#include <fstream>
#include <iostream>
void OctreeSidesDrawer2::_initShaders()
{
	//std::string program = generatePrefixSum8bit(m_lastNodePerEdgebuffer, _visitor->getOctree(), 1024, m_nofTotalSubbuffers, m_subBufferCorrection, uint32_t(m_bitMasks[0].size()));
	std::ifstream t1("C:\\Users\\ikobrtek\\Desktop\\newGetSubbuffs.glsl");
	std::string program((std::istreambuf_iterator<char>(t1)),
		std::istreambuf_iterator<char>());

	m_getSubBufsProgram = std::make_shared<ge::gl::Program>(
		std::make_shared<ge::gl::Shader>(GL_COMPUTE_SHADER, program));

	std::ifstream t2("C:\\Users\\ikobrtek\\Desktop\\newCopy.glsl");
	std::string genprogram((std::istreambuf_iterator<char>(t2)),
	std::istreambuf_iterator<char>());
	//*/
	m_getEdgesProgram = std::make_shared<ge::gl::Program>(
		std::make_shared<ge::gl::Shader>(GL_COMPUTE_SHADER, genprogram));

	const char* vsSource = R"(
#version 430 core

layout(location=0)in vec4 Position;

uniform mat4 mvp = mat4(1);

void main(){
  gl_Position=mvp*Position;
}
)";

	m_drawSidesProgram = std::make_shared<ge::gl::Program>(
		std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, vsSource));
}

void OctreeSidesDrawer2::_geSidesData8b(const glm::vec4& light, uint32_t cellContainingLight)
{
	m_nofPotSilBuffers->clear(GL_R32UI, GL_RED, GL_UNSIGNED_INT, nullptr);
	m_IBO->clear(GL_R32UI, 0, sizeof(uint32_t), GL_RED, GL_UNSIGNED_INT, nullptr);

	shit->clear(GL_R32UI, 0, 1024*sizeof(uint32_t), GL_RED, GL_UNSIGNED_INT, nullptr);

	m_getSubBufsProgram->use();
	m_getSubBufsProgram->set1ui("cellContainingLight", cellContainingLight);

	uint32_t index = 0;
	m_voxelNofPotentialSilhouetteEdgesPrefixSum->bindBase(GL_SHADER_STORAGE_BUFFER, index++);
	m_nofPotSilBuffers->bindBase(GL_SHADER_STORAGE_BUFFER, index++);
	m_potSubBuffers->bindBase(GL_SHADER_STORAGE_BUFFER, index++);
	m_silSubBuffers->bindBase(GL_SHADER_STORAGE_BUFFER, index++);
	m_bitmasksBuffer->bindBase(GL_SHADER_STORAGE_BUFFER, index++);

	ge::gl::glDispatchCompute(1, 1, 1);

	index = 0;
	m_voxelNofPotentialSilhouetteEdgesPrefixSum->unbindBase(GL_SHADER_STORAGE_BUFFER, index++);
	m_nofPotSilBuffers->unbindBase(GL_SHADER_STORAGE_BUFFER, index++);
	m_potSubBuffers->unbindBase(GL_SHADER_STORAGE_BUFFER, index++);
	m_silSubBuffers->unbindBase(GL_SHADER_STORAGE_BUFFER, index++);
	m_bitmasksBuffer->unbindBase(GL_SHADER_STORAGE_BUFFER, index++);

	ge::gl::glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
	/*
	{
		ge::gl::glFinish();

		uint32_t nofPS[2];
		m_nofPotSilBuffers->getData(nofPS, 2 * sizeof(uint32_t));

		std::vector<uint32_t> v;
		v.resize(6);
		m_silSubBuffers->getData(v.data(), 6 * sizeof(uint32_t));

		printf("");
	}
	//*/

	m_getEdgesProgram->use();
	m_getEdgesProgram->set4fv("lightPosition", glm::value_ptr(light));
	index = 0;

	for (const auto b : m_gpuOctreeBuffers)
		b->bindBase(GL_SHADER_STORAGE_BUFFER, index++);
	m_gpuEdges->_edges->bindBase(GL_SHADER_STORAGE_BUFFER, index++);
	m_gpuEdges->_oppositeVertices->bindBase(GL_SHADER_STORAGE_BUFFER, index++);
	m_nofPotSilBuffers->bindBase(GL_SHADER_STORAGE_BUFFER, index++);
	m_potSubBuffers->bindBase(GL_SHADER_STORAGE_BUFFER, index++);
	m_silSubBuffers->bindBase(GL_SHADER_STORAGE_BUFFER, index++);
	m_IBO->bindRange(GL_SHADER_STORAGE_BUFFER, index++, 0, sizeof(uint32_t));
	m_edgeVBO->bindBase(GL_SHADER_STORAGE_BUFFER, index++);
	shit->bindBase(GL_SHADER_STORAGE_BUFFER, index++);

	ge::gl::glDispatchCompute((m_maxNofPotBuffers + m_maxNofSilBuffers)/8u, 1, 1);

	index = 0;

	for (const auto b : m_gpuOctreeBuffers)
		b->unbindBase(GL_SHADER_STORAGE_BUFFER, index++);
	m_gpuEdges->_edges->unbindBase(GL_SHADER_STORAGE_BUFFER, index++);
	m_gpuEdges->_oppositeVertices->unbindBase(GL_SHADER_STORAGE_BUFFER, index++);
	m_nofPotSilBuffers->unbindBase(GL_SHADER_STORAGE_BUFFER, index++);
	m_potSubBuffers->unbindBase(GL_SHADER_STORAGE_BUFFER, index++);
	m_silSubBuffers->unbindBase(GL_SHADER_STORAGE_BUFFER, index++);
	m_IBO->unbindRange(GL_SHADER_STORAGE_BUFFER, index++);
	m_edgeVBO->unbindBase(GL_SHADER_STORAGE_BUFFER, index++);
	shit->unbindBase(GL_SHADER_STORAGE_BUFFER, index++);
	
	ge::gl::glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
	/*
	{
		static uint32_t frame = 0;
		ge::gl::glFinish();
		uint32_t nofIndices = 0;
		m_IBO->getData(&nofIndices, sizeof(uint32_t));

		std::vector<int32_t> v;
		v.resize(1024);
		shit->getData(v.data(), 1024 * sizeof(int32_t));

		std::vector<glm::vec4>  p;
		p.resize(72);
		m_edgeVBO->getData(p.data(), 72 * sizeof(glm::vec4));

		std::vector<uint32_t> silIdices;
		silIdices.resize(10);
		m_silSubBuffers->getData(silIdices.data(), 10 * sizeof(uint32_t));

		printf("");

		std::vector<uint32_t> potentialEdges, silhouetteEdges, castPot;

		const uint32_t nofSubbuffs = 3;
		const uint32_t offset1 = 360;
		const uint32_t offset2 = 600;

		potentialEdges.insert(potentialEdges.end(), v.begin() + nofSubbuffs, v.begin() + nofSubbuffs + v[0]);
		silhouetteEdges.insert(silhouetteEdges.end(), v.begin() + offset1 + nofSubbuffs, v.begin() + offset1 + nofSubbuffs + v[1]);
		castPot.insert(castPot.end(), v.begin() + offset2 + nofSubbuffs, v.begin() + offset2 + nofSubbuffs + v[2]);

		//assert(potentialEdges.size() == 346);
		//assert(silhouetteEdges.size() == 40);
		//assert(castPot.size() == 98);

		std::ofstream of;
		of.open("GPU_Edges.txt");
		std::sort(potentialEdges.begin(), potentialEdges.end());
		std::sort(silhouetteEdges.begin(), silhouetteEdges.end());
		std::sort(castPot.begin(), castPot.end());

		of << "Potential:\n";
		for (const auto e : potentialEdges)
			of << e << std::endl;

		of << "\nSilhouette:\n";
		for (const auto e : silhouetteEdges)
			of << decodeEdgeFromEncoded(e) << " multiplicity: " << decodeEdgeMultiplicityFromId(e) << std::endl;

		of << "\nUsedPot:\n";
		for (auto const cp : castPot)
			of << decodeEdgeFromEncoded(cp) << " multiplicity: " << decodeEdgeMultiplicityFromId(cp) << std::endl;

		of.close();
		++frame;
	}
	//*/
}

void OctreeSidesDrawer2::drawSides(const glm::mat4& mvp, const glm::vec4& light)
{
	const auto cellIndex = _visitor->getLowestNodeIndexFromPoint(glm::vec3(light));

	if (cellIndex<0)
	{
		static bool printOnce = false;

		if (!printOnce)
		{
			std::cout << "Light " << light.x << ", " << light.y << ", " << light.z << " is out of range\n";
			//printOnce = true;
		}
	}
	else
	{
		_geSidesData8b(light, cellIndex);

		m_drawSidesProgram->use();
		m_drawSidesProgram->setMatrix4fv("mvp", glm::value_ptr(mvp));

		m_VAO->bind();
		m_IBO->bind(GL_DRAW_INDIRECT_BUFFER);

		ge::gl::glDrawArraysIndirect(GL_TRIANGLES, 0);

		m_VAO->unbind();
		m_IBO->unbind(GL_DRAW_INDIRECT_BUFFER);
	}
}
