#pragma once
#include "../ShadowVolumes.h"
#include "../GSCaps.h"
#include "../Model.h"
#include "Octree.hpp"
#include "OctreeVisitor.hpp"
#include "GpuEdges.hpp"
#include "ISidesDrawer.hpp"
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
	bool drawFromCpu;
	bool doEdgeTest;
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

	bool init() override;
	void drawSides(glm::vec4 const&lightPosition, glm::mat4 const&viewMatrix, glm::mat4 const&projectionMatrix) override;
	void drawCaps(glm::vec4 const&lightPosition, glm::mat4 const&viewMatrix, glm::mat4 const&projectionMatrix) override;

	void setTimeStamper(std::shared_ptr<TimeStamp> stamper) override;

	void drawUser(glm::vec4 const&lightPosition, glm::mat4 const&viewMatrix, glm::mat4 const&projectionMatrix) override;

protected:
	std::vector<float> _loadVertices(std::shared_ptr<Model> const model);
	void _createAdjacency(std::vector<float> const& verts3f);
	AABB _calculateOctreeSpace(std::vector<float> const & verts3f, glm::vec3 scale);
	void _createOctree(uint32_t maxOctreeLevel, AABB const& octreeSpace, bool verbose = true);
	void _loadOctreeFromFile(std::string const& filename, uint32_t octreeLevel, uint32_t compressionLevel, glm::vec3 sceneScale);
	void _storeOctree(glm::vec3 const& sceneScale);

	void _buildTest();
	void _edgeTest();

	AABB _getSceneAabb(std::vector<float> const& verts3f);
		void _fixSceneAABB(AABB& bbox);

	void _loadGpuEdges(AdjacencyType edges);
		void _serializeEdges(AdjacencyType edges, std::vector<float>& serializedEdges, std::vector<glm::vec3>& serializedOppositeVertices);

protected:
	std::shared_ptr<Model> _model;
	HSSVParams _params;
	uint32_t _compressionLevel = 0;
	AABB _octreeSpace;

	std::shared_ptr<ISidesDrawer> _octreeSidesDrawer;
	std::shared_ptr<GSCaps> _capsDrawer = nullptr;

	std::shared_ptr<Octree> _octree = nullptr;
	std::shared_ptr<OctreeVisitor> _visitor = nullptr;
	std::shared_ptr<const Adjacency> _edges = nullptr;

	std::shared_ptr<GpuEdges> _gpuEdges;

	std::unique_ptr<OctreeWireframeDrawer> _wireframeDrawer;
};
