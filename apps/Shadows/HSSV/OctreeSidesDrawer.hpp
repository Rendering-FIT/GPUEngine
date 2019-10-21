#pragma once

#include <geGL/Program.h>
#include <geGL/Buffer.h>
#include <geGL/VertexArray.h>

#include "OctreeVisitor.hpp"
#include "IGpuOctreeSidesDrawer.hpp"


enum class DrawingMethod : unsigned char
{
	GS = 0,
	TS = 1,
	CS = 2
};

class OctreeSidesDrawer : public IGpuOctreeSidesDrawer
{
public:
	OctreeSidesDrawer(std::shared_ptr<OctreeVisitor> octreeVisitor, uint32_t subgroupSize, DrawingMethod potential, DrawingMethod silhouette);

	bool init(std::shared_ptr<GpuEdges> gpuEdges) override;

	void drawSides(const glm::mat4& mvp,const glm::vec4& light) override;

protected:
	
	void _drawSidesFromSilhouetteEdgesTS(const glm::mat4& mvp, const glm::vec4& lightPos);
	void _drawSidesFromSilhouetteEdgesGS(const glm::mat4& mvp, const glm::vec4& lightPos);
	void _drawSidesFromSilhouetteEdgesCS(const glm::mat4& mvp, const glm::vec4& lightPos);

	void _drawSidesFromPotentialEdgesGS(const glm::mat4& mvp, const glm::vec4& lightPos);
	void _drawSidesFromPotentialEdgesTS(const glm::mat4& mvp, const glm::vec4& lightPos);
	void _drawSidesFromPotentialEdgesCS(const glm::mat4& mvp, const glm::vec4& lightPos);

	void _drawSidesCS(const glm::mat4& mvp, const glm::vec4& lightPos);

	void _generateSidesFromPotentialCS(const glm::vec4& lightPos);
	void _generateSidesFromSilhouetteCS();

	void _initShaders();
	void _initBuffers();

	bool _generateLoadGpuTraversalShader3();
	void _getPotentialSilhouetteEdgesGpu3(uint32_t lowestNodeContainingLight);

	bool _loadGpuTraversalShader8bit();
	void _getPotentialSilhouetteEdgesGpu8bit(uint32_t lowestNodeContainingLight);

	void _getPotentialSilhouetteEdgesNoCompress(uint32_t lowestNodeContainingLight);

	bool _loadOctreeTraversalKernelNoCompress(uint32_t workgroupSize);

	bool _loadOctreeTraversalKernelNoCompress2();
	void _getPotentialSilhouetteEdgesNoCompress2(uint32_t lowestNodeContainingLight);

	void _allocSubBuffersDataBuffers();

	void _calcPrefixSums();
		void _calcPrefixSum(std::shared_ptr<ge::gl::Buffer> input, std::shared_ptr<ge::gl::Buffer> output, std::shared_ptr<ge::gl::Buffer> count, uint32_t worstCase, uint32_t tmpIndex);

	void _calcSingleTwoLevelPrefixSumWgSizes(uint32_t maxNofPotSubBuffs, uint32_t maxNofSilSubBuffs);
		uint32_t _getNearstLowerPow2(uint32_t x) const;

	void _loadUbo();

	void _fixDispatchSizes(uint32_t potDivisor, uint32_t silDivisor);
private:	

	std::shared_ptr<ge::gl::Program> _potentialGsProgram = nullptr;
	std::shared_ptr<ge::gl::Program> _potentialTsProgram = nullptr;
	std::shared_ptr<ge::gl::Program> _silhouetteSidesTsProgram = nullptr;
	std::shared_ptr<ge::gl::Program> _silhouetteSidesGsProgram = nullptr;
	std::shared_ptr<ge::gl::Program> _drawSidesProgram = nullptr;
	std::shared_ptr<ge::gl::Program> _testAndGenerateSidesProgram = nullptr;
	std::shared_ptr<ge::gl::Program> _generateSidesProgram = nullptr;
	std::shared_ptr<ge::gl::Program> m_getSubBufssSader = nullptr;
	std::shared_ptr<ge::gl::Program> m_patchingKernel = nullptr;
	std::shared_ptr<ge::gl::Program> m_traverseOctreeNoCompressKernel = nullptr;

	std::shared_ptr<ge::gl::VertexArray>_dummyVAO = nullptr;
	std::shared_ptr<ge::gl::VertexArray>_potentialSidesCsVAO = nullptr;
	std::shared_ptr<ge::gl::VertexArray>_silhouetteSidesCsVAO = nullptr;

	std::shared_ptr<ge::gl::Buffer> _edgesIdsToGenerate = nullptr;
	std::shared_ptr<ge::gl::Buffer> _edgesIdsToTestAndGenerate = nullptr;

	std::shared_ptr<ge::gl::Buffer> _potentialEdgeCsVBO = nullptr;
	std::shared_ptr<ge::gl::Buffer> _silhouetteEdgeCsVBO = nullptr;

	std::shared_ptr<ge::gl::Buffer> _indirectDrawBufferPotentialCS = nullptr;
	std::shared_ptr<ge::gl::Buffer> _indirectDrawBufferSilhouetteCS = nullptr;

	std::shared_ptr<ge::gl::Buffer> _voxelEdgeIndices = nullptr;


	std::shared_ptr<ge::gl::Buffer> _indirectDispatchCsPotential = nullptr;
	std::shared_ptr<ge::gl::Buffer> _indirectDispatchCsSilhouette = nullptr;

	std::shared_ptr<ge::gl::Buffer> _nofEdgesPotSil = nullptr;

	std::shared_ptr<GpuEdges> _gpuEdges;

	uint32_t _nofPotentialEdgesToDraw = 0;
	uint32_t _nofSilhouetteEdgesToDraw = 0;

	uint32_t _maxNofEdgesInVoxel;
	uint32_t _maxNofEdgesPath;

	uint32_t _workgroupSize = 0;

	DrawingMethod _potentialDrawingMethod;
	DrawingMethod _silhouetteDrawingMethod;

	std::shared_ptr<ge::gl::Program> m_subBuffersPreprocessShader = nullptr;
	std::shared_ptr<ge::gl::Program> m_getDataFromPrecomputedBuffersShader2 = nullptr;

	std::shared_ptr<ge::gl::Buffer> m_potSuBuffers = nullptr;
	std::shared_ptr<ge::gl::Buffer> m_silSuBuffers = nullptr;
	std::shared_ptr<ge::gl::Buffer> m_nofPotBuffers = nullptr;
	std::shared_ptr<ge::gl::Buffer> m_nofSilBuffers = nullptr;

	//Prefix sum
	std::shared_ptr<ge::gl::Buffer> m_prefixSumTmp[2] = { nullptr, nullptr };
	std::shared_ptr<ge::gl::Buffer> m_prefixSumTmpAtomic[2] = { nullptr, nullptr };

	std::shared_ptr<ge::gl::Program> m_prefixSumShaderSimple = nullptr;
	std::shared_ptr<ge::gl::Program> m_prefixSumShaderTwoLevel = nullptr;
	std::shared_ptr<ge::gl::Program> m_prefixSumShaderAdd = nullptr;

	uint32_t m_dataStride = 0;
	uint32_t m_maxNofPotBuffers = 0;
	uint32_t m_maxNofSilBuffers = 0;
	uint32_t m_prefixSumWorkgroupSizeSingle = 0;
	uint32_t m_prefixSumWorkgroupSizeTwoLevel = 0;
	uint32_t m_prefixSumWorkgroupSizeSummation = 256;

	uint32_t m_maxNofSubBuffersPath = 0;

	std::shared_ptr<ge::gl::Buffer> m_ubo;

	
};