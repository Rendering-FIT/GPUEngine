#pragma once
#include "../ShadowVolumes.h"
#include "../GSCaps.h"
#include "../Model.h"
#include "Octree.hpp"
#include "OctreeVisitor.hpp"

struct HSSVParams
{
	unsigned int maxOctreeLevel;
	glm::vec3 sceneAABBscale;
};

class HSSV : public ShadowVolumes
{
public:
	HSSV(std::shared_ptr<Model> model,
		const glm::vec3& sceneAABBscale,
		unsigned int maxOctreeLevel,
		std::shared_ptr<ge::gl::Texture>const& shadowMask,
		std::shared_ptr<ge::gl::Texture>const& depth,
		ShadowVolumesParams const& params);

	~HSSV();

	void drawSides(glm::vec4 const&lightPosition, glm::mat4 const&viewMatrix, glm::mat4 const&projectionMatrix) override;
	void drawCaps(glm::vec4 const&lightPosition, glm::mat4 const&viewMatrix, glm::mat4 const&projectionMatrix) override;


protected:

	AABB _getSceneAabb(float* vertices3fv, size_t numVertices);
		void _fixSceneAABB(AABB& bbox);

	void _prepareBuffers(size_t maxVboSize);
	void _prepareProgram();
	void _updateSidesVBO(const std::vector<float>& vertices);

	void _getSilhouetteFromLightPos(const glm::vec3& lightPos, std::vector<float>& silhouetteVertices);
		void _generateSilhouetteGeometry();
		void _generatePushSideFromEdge(const glm::vec3& lightPos, const glm::vec3& lowerPoint, const glm::vec3& higherPoint, int multiplicitySign, std::vector<float>& sides);

	std::shared_ptr<ge::gl::Buffer> _sidesVBO = nullptr;
	std::shared_ptr<ge::gl::VertexArray> _sidesVAO = nullptr;
	std::shared_ptr<ge::gl::Program> _sidesProgram = nullptr;

	std::shared_ptr<GSCaps> _capsDrawer = nullptr;

	std::shared_ptr<Octree> _octree = nullptr;
	std::shared_ptr<OctreeVisitor> _visitor = nullptr;
	std::shared_ptr<const Adjacency> _edges = nullptr;

	float* _vertices = nullptr;

	int _previousOctreeNodeLightPos = -1;

};
