#pragma once

#include "ISidesDrawer.hpp"
#include "OctreeVisitor.hpp"

class CpuSidesDrawer : public ISidesDrawer
{
public:

	CpuSidesDrawer(std::shared_ptr<OctreeVisitor> visitor, std::shared_ptr<const Adjacency> edges);

	bool init(std::shared_ptr<GpuEdges> gpuEdges) override;

	void drawSides(const glm::mat4& mvp, const glm::vec4& light) override;

protected:

	void _getSilhouetteFromLightPos(const glm::vec3& lightPos, std::vector<float>& silhouetteVertices);
		void _generatePushSideFromEdge(const glm::vec3& lightPos, const glm::vec3& lowerPoint, const glm::vec3& higherPoint, int multiplicitySign, std::vector<float>& sides);

	void _prepareBuffers(size_t maxVboSize);
	void _prepareProgram();
	void _updateSidesVBO(const std::vector<float>& vertices);

	std::shared_ptr<ge::gl::Buffer> _sidesVBO = nullptr;
	std::shared_ptr<ge::gl::VertexArray> _sidesVAO = nullptr;
	std::shared_ptr<ge::gl::Program> _sidesProgram = nullptr;

	std::shared_ptr<const Adjacency> _edges;
	std::shared_ptr<Octree> _octree;
};
