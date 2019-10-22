#pragma once
#include "IGpuOctreeSidesDrawer.hpp"

class OctreeVisitor;

class OctreeSidesDrawer2 : public IGpuOctreeSidesDrawer
{
public:
	OctreeSidesDrawer2(std::shared_ptr<OctreeVisitor> octreeVisitor, uint32_t subgroupSize);

	bool init(std::shared_ptr<GpuEdges> gpuEdges) override;

	void drawSides(const glm::mat4& mvp, const glm::vec4& light) override;

protected:
	void _initShaders();
	void _initBuffers();
		void _loadBitmaskBuffer();

	void _geSidesData8b(const glm::vec4& light, uint32_t cellContainingLight);

protected:
	std::shared_ptr<ge::gl::Program> m_getSubBufsProgram;
	std::shared_ptr<ge::gl::Program> m_getEdgesProgram;
	std::shared_ptr<ge::gl::Program> m_drawSidesProgram;

	std::shared_ptr<ge::gl::Buffer> m_bitmasksBuffer;

	std::shared_ptr<ge::gl::Buffer> m_edgeVBO;
	std::shared_ptr<ge::gl::Buffer> m_IBO;

	std::shared_ptr<ge::gl::VertexArray> m_VAO;


	std::shared_ptr<ge::gl::Buffer> m_nofPotSilBuffers;
	std::shared_ptr<ge::gl::Buffer> m_potSubBuffers;
	std::shared_ptr<ge::gl::Buffer> m_silSubBuffers;

	uint32_t m_dataStride = 0;
	uint32_t m_maxNofPotBuffers = 0;
	uint32_t m_maxNofSilBuffers = 0;

	std::shared_ptr<ge::gl::Buffer> shit;

	std::shared_ptr<GpuEdges> m_gpuEdges;
};
