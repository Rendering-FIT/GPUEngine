#pragma once
#include "../ShadowVolumes.h"
#include "../GSCaps.h"
#include "../Model.h"
#include "Octree.hpp"
#include "OctreeVisitor.hpp"
#include "GpuEdges.hpp"
#include "OctreeSidesDrawer.hpp"
#include "OctreeWireframeDrawer.hpp"

struct HSSVParams
{
	uint32_t maxOctreeLevel;
	glm::vec3 sceneAABBscale;
	glm::vec3 initialLightPos; //for build test only
	uint32_t maxGpuMemoryToUsePerBuffer;
	unsigned char potentialDrawingMethod;
	unsigned char silhouetteDrawingMethod;
	uint32_t workgroupSize;
	float potSpeculativeFactor;
	float silSpeculativeFactor;
	bool forceOctreeBuild;
	bool drawOctree;
	bool doBuildTest;
	bool noCompression;
};

class HSSV : public ShadowVolumes
{
public:
	HSSV(std::shared_ptr<Model> model,
		const HSSVParams& hssvParams,
		std::shared_ptr<ge::gl::Texture>const& shadowMask,
		std::shared_ptr<ge::gl::Texture>const& depth,
		ShadowVolumesParams const& params);

	virtual ~HSSV();

	void drawSides(glm::vec4 const&lightPosition, glm::mat4 const&viewMatrix, glm::mat4 const&projectionMatrix) override;
	void drawCaps(glm::vec4 const&lightPosition, glm::mat4 const&viewMatrix, glm::mat4 const&projectionMatrix) override;

	void setTimeStamper(std::shared_ptr<TimeStamp> stamper) override;

	void drawUser(glm::vec4 const&lightPosition, glm::mat4 const&viewMatrix, glm::mat4 const&projectionMatrix) override;

protected:

	AABB _getSceneAabb(float* vertices3fv, size_t numVertices);
		void _fixSceneAABB(AABB& bbox);

	void _prepareBuffers(size_t maxVboSize);
	void _prepareProgram();
	void _updateSidesVBO(const std::vector<float>& vertices);

	void _getSilhouetteFromLightPos(const glm::vec3& lightPos, std::vector<float>& silhouetteVertices);
		void _generatePushSideFromEdge(const glm::vec3& lightPos, const glm::vec3& lowerPoint, const glm::vec3& higherPoint, int multiplicitySign, std::vector<float>& sides);
		
	void _loadGpuEdges(AdjacencyType edges);
		void _serializeEdges(AdjacencyType edges, std::vector<float>& serializedEdges, std::vector<glm::vec3>& serializedOppositeVertices);
protected:

	std::shared_ptr<ge::gl::Buffer> _sidesVBO = nullptr;
	std::shared_ptr<ge::gl::VertexArray> _sidesVAO = nullptr;
	std::shared_ptr<ge::gl::Program> _sidesProgram = nullptr;

	std::shared_ptr<OctreeSidesDrawer> _octreeSidesDrawer;
	std::shared_ptr<GSCaps> _capsDrawer = nullptr;

	std::shared_ptr<Octree> _octree = nullptr;
	std::shared_ptr<OctreeVisitor> _visitor = nullptr;
	std::shared_ptr<const Adjacency> _edges = nullptr;

	std::shared_ptr<GpuEdges> _gpuEdges;

	std::unique_ptr<OctreeWireframeDrawer> _wireframeDrawer;

	float* _vertices = nullptr;

	int _previousOctreeNodeLightPos = -1;

	bool _isDrawOctree = false;
};
