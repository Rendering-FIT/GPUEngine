#pragma once
#include <string>
#include <vector>
#include <memory>

class Octree;

//In iterative manner
//Not expecting to have a lot of buffers
const std::string genGetNodeFromBuffer(uint32_t numBuffers);

std::string genBuffer(uint32_t i);

std::string genFindBufferFunc();

std::string getCompressionIdWithinParentFunction(uint32_t compressionLevel);

std::string isCompressionIdPresentFunction(uint32_t compressionLevel);

std::string genPrologue(uint32_t workgroupSize);

std::string genGetSubBufferId();

std::string getNearestPow2Func();

std::string genStoreBufferID(uint32_t nofBuffers);

std::string genBufferPreprocessShaderNoCompreess(const std::vector<uint32_t>& lastNodePerEdgeBuffer, std::shared_ptr<Octree> octree, uint32_t workgroupSize);

std::string genBufferPreprocessShader(const std::vector<uint32_t>& lastNodePerEdgeBuffer, std::shared_ptr<Octree> octree, uint32_t workgroupSize);

std::string genCopyShader3(const std::vector<uint32_t>& lastNodePerEdgeBuffer, uint32_t workgroupSize);

//From https://developer.nvidia.com/gpugems/GPUGems3/gpugems3_ch39.html
std::string genPrefixSumKernelSimple(uint32_t workgroupSize);

std::string genPrefixSumKernelTwoLevel(uint32_t workgroupSize);

std::string generateSummationKernel(uint32_t workgroupSize);

std::string generatePrefixSum8bit(const std::vector<uint32_t>& lastNodePerEdgeBuffer, std::shared_ptr<Octree> octree, uint32_t workgroupSize, uint32_t nofSubbuffs, uint32_t subbuffCorrection, uint32_t compBuffSize);

std::string genDivisorKernel();


std::string genTraversalNoCompressKernel(const std::vector<uint32_t>& lastNodePerEdgeBuffer, std::shared_ptr<Octree> octree, unsigned int workgroupSize);

std::string genPreprocessKernelNoCompress(const std::vector<uint32_t>& lastNodePerEdgeBuffer, std::shared_ptr<Octree> octree);