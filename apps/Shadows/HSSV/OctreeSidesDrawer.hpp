#pragma once

#include <geGL/Program.h>
#include <geGL/Buffer.h>
#include <geGL/VertexArray.h>

#include "OctreeVisitor.hpp"
#include "GpuEdges.hpp"

class OctreeSidesDrawer
{
public:
	OctreeSidesDrawer(std::shared_ptr<OctreeVisitor> octreeVisitor, unsigned int subgroupSize);

	bool init(std::shared_ptr<GpuEdges> gpuEdges);

	void drawSides(const glm::mat4& mvp,const glm::vec4& light);

protected:

	void _drawSidesFromSilhouetteEdges(const glm::mat4& mvp, const glm::vec4& lightPos);
	void _genSidesFromSilhouetteEdges(unsigned int cellContainingLightId);
		unsigned int _loadSilhouetteEdgesFromIdUpGetNof(unsigned int cellContainingLightId);

	void _testAndGenPotential(unsigned int cellContainingLightId);
		unsigned int _loadPotentialEdgesFromIdUpGetNof(unsigned int cellContainingLightId);

	bool _initShaders(unsigned int subgroupSize);
	void _initBuffers();
		void _getMaxPossibleEdgeCountInTraversal(size_t& potential, size_t& silhouette) const;
		void _getMaximumNofEdgesInLevel(unsigned int level, size_t& potential, size_t& silhouette) const;

	int lastFrameVoxel = -1;

	std::shared_ptr<ge::gl::Program> _testAndGenerateSidesProgram = nullptr;
	std::shared_ptr<ge::gl::Program> _generateSidesProgram = nullptr;
	std::shared_ptr<ge::gl::Program> _drawSidesProgram = nullptr;
	
	std::shared_ptr<ge::gl::Buffer> _indirectDrawBufferPotential = nullptr;
	std::shared_ptr<ge::gl::Buffer> _indirectDrawBufferSilhouette = nullptr;

	std::shared_ptr<ge::gl::VertexArray>_sidesVaoPotential = nullptr;
	std::shared_ptr<ge::gl::VertexArray>_sidesVaoSilhouette = nullptr;

	std::shared_ptr<ge::gl::Buffer> _vboPotential = nullptr;
	std::shared_ptr<ge::gl::Buffer> _vboSilhouette = nullptr;

	std::shared_ptr<ge::gl::Buffer> _edgesIdsToGenerate = nullptr;
	std::shared_ptr<ge::gl::Buffer> _edgesIdsToTestAndGenerate = nullptr;

	std::shared_ptr<GpuEdges> _gpuEdges;

	std::shared_ptr<OctreeVisitor> _octreeVisitor = nullptr;
	unsigned int _subgroupSize =0;
};
