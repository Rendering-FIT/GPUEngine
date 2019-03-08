#pragma once

#include <geGL/Program.h>
#include <geGL/Buffer.h>
#include <geGL/VertexArray.h>

#include "OctreeVisitor.hpp"
#include "GpuEdges.hpp"
#include "../TimeStamp.h"

enum class DrawingMethod : unsigned char
{
	GS = 0,
	TS = 1,
	CS = 2
};

class OctreeSidesDrawer
{
public:
	OctreeSidesDrawer(std::shared_ptr<OctreeVisitor> octreeVisitor, uint32_t subgroupSize, DrawingMethod potential, DrawingMethod silhouette);

	void init(std::shared_ptr<GpuEdges> gpuEdges);

	void drawSides(const glm::mat4& mvp,const glm::vec4& light);

	void setStamper(std::shared_ptr<TimeStamp> stamper);

protected:
	void _loadOctreeToGpu();
	void _loadOctreeToGpu8BitOrNoCompress();

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
		void _getMaxPossibleEdgeCountInTraversal(size_t& potentialPath, size_t& silhouettePath, size_t& maxInVoxel, size_t& maxPath) const;
		void _getMaximumNofEdgesInLevel(uint32_t level, size_t& potential, size_t& silhouette) const;
			void _getNofEdgesInNode(uint32_t nodeId, size_t& potential, size_t& silhouette) const;

	bool _generateLoadGpuTraversalShader3();
	void _getPotentialSilhouetteEdgesGpu3(uint32_t lowestNodeContainingLight);

	bool _loadGpuTraversalShader8bit(unsigned int workgroupSize);
	void _getPotentialSilhouetteEdgesGpu8bit(uint32_t lowestNodeContainingLight);

	void _processSubBuffer(
		const std::unordered_map<BitmaskType, std::vector<uint32_t>>::value_type& subBuffer, 
		std::vector<uint32_t>& compressedNodesInfo,
		std::vector<uint32_t>& nofEdgesPrefixSums,
		uint32_t* gpuMappedBuffer
		);

	void _breakCompressionIdToUintsAndPush(const BitmaskType& id, std::vector<uint32_t>& vectorToStore) const;

	void _allocSubBuffersDataBuffers();

	void _calcPrefixSums();
		void _calcPrefixSum(std::shared_ptr<ge::gl::Buffer> input, std::shared_ptr<ge::gl::Buffer> output, std::shared_ptr<ge::gl::Buffer> count, uint32_t worstCase, uint32_t tmpIndex);

	void _calcSingleTwoLevelPrefixSumWgSizes(uint32_t maxNofPotSubBuffs, uint32_t maxNofSilSubBuffs);
		uint32_t _getNearstLowerPow2(uint32_t x) const;

	void _calcBitMasks8(unsigned int minBits);
	void _loadUbo();
private:	
	int _lastFrameCellIndex = -1;

	std::shared_ptr<ge::gl::Program> _potentialGsProgram = nullptr;
	std::shared_ptr<ge::gl::Program> _potentialTsProgram = nullptr;
	std::shared_ptr<ge::gl::Program> _silhouetteSidesTsProgram = nullptr;
	std::shared_ptr<ge::gl::Program> _silhouetteSidesGsProgram = nullptr;
	std::shared_ptr<ge::gl::Program> _drawSidesProgram = nullptr;
	std::shared_ptr<ge::gl::Program> _testAndGenerateSidesProgram = nullptr;
	std::shared_ptr<ge::gl::Program> _generateSidesProgram = nullptr;
	std::shared_ptr<ge::gl::Program> m_getSubBufssSader = nullptr;

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
	std::shared_ptr<ge::gl::Buffer> _voxelNofPotentialSilhouetteEdgesPrefixSum = nullptr;

	std::shared_ptr<ge::gl::Buffer> _indirectDispatchCsPotential = nullptr;
	std::shared_ptr<ge::gl::Buffer> _indirectDispatchCsSilhouette = nullptr;

	std::shared_ptr<ge::gl::Buffer> _compressedNodesInfoBuffer = nullptr;
	std::shared_ptr<ge::gl::Buffer> _compressedNodesInfoIndexingBuffer = nullptr;

	std::shared_ptr<GpuEdges> _gpuEdges;

	std::shared_ptr<OctreeVisitor> _octreeVisitor = nullptr;

	std::vector<std::shared_ptr<ge::gl::Buffer>> _gpuOctreeBuffers;
	std::vector<uint32_t> _lastNodePerEdgeBuffer;

	uint32_t _nofPotentialEdgesToDraw = 0;
	uint32_t _nofSilhouetteEdgesToDraw = 0;

	uint32_t _maxNofEdgesInVoxel;
	uint32_t _maxNofEdgesPath;

	uint32_t _workgroupSize = 0;

	DrawingMethod _potentialDrawingMethod;
	DrawingMethod _silhouetteDrawingMethod;

	std::shared_ptr<TimeStamp> _timer;

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

	std::vector< std::vector<uint32_t> > m_bitMasks;

	std::shared_ptr<ge::gl::Buffer> m_ubo;

	uint32_t m_nofTotalSubbuffers = 0;
	uint32_t m_subBufferCorrection = 0;

	uint32_t m_compressionLevel;
};