#include "IGpuOctreeLoader.hpp"
#include <omp.h>
#include "geGL/StaticCalls.h"

IGpuOctreeLoader::IGpuOctreeLoader()
{
	_createBuffers();
}

void IGpuOctreeLoader::_loadVoxels(const std::vector<glm::vec3>& voxels, unsigned int startingIndex, unsigned int batchSize)
{
	assert(ge::gl::glGetError() == GL_NO_ERROR);
	_voxels->setData((voxels.data() + (2 * startingIndex)), 6 * sizeof(float) * batchSize);
	assert(ge::gl::glGetError() == GL_NO_ERROR);
}

void IGpuOctreeLoader::_clearAtomicCounter()
{
	assert(_atomicCounter);
	assert(ge::gl::glGetError() == GL_NO_ERROR);

	uint32_t zero = 0;
	_atomicCounter->setData(&zero, sizeof(uint32_t));

	assert(ge::gl::glGetError() == GL_NO_ERROR);
}

void IGpuOctreeLoader::_copyBuffer(std::shared_ptr<ge::gl::Buffer> buffer, void* destination, size_t size)
{
	assert(ge::gl::glGetError() == GL_NO_ERROR);
	/*
	const auto source = buffer->map(GL_READ_ONLY);

	memcpy(destination, source, size);

	buffer->unmap();
	*/
	buffer->getData(destination, size);
	ge::gl::glFinish();
	assert(ge::gl::glGetError() == GL_NO_ERROR);
}
void IGpuOctreeLoader::_createBuffers()
{
	_voxels = std::make_shared<ge::gl::Buffer>();
	_voxelPotentialEdges = std::make_shared<ge::gl::Buffer>();
	_voxelSilhouetteEdges = std::make_shared<ge::gl::Buffer>();
	_nofPotentialEdges = std::make_shared<ge::gl::Buffer>();
	_nofSilhouetteEdges = std::make_shared<ge::gl::Buffer>();
	_atomicCounter = std::make_shared<ge::gl::Buffer>();
	_atomicCounter->alloc(sizeof(uint32_t), nullptr, GL_DYNAMIC_DRAW);
}

void IGpuOctreeLoader::_serializeDeepestLevelVoxels(std::vector<glm::vec3>& voxels)
{
	const int deepestLevelSize = ipow(OCTREE_NUM_CHILDREN, _octree->getDeepestLevel());
	const int startingIndex = _octree->getLevelFirstNodeID(_octree->getDeepestLevel());
	const int stopIndex = startingIndex + deepestLevelSize;

	voxels.resize(2 * deepestLevelSize);

#pragma omp parallel for
	for (int i = 0; i<deepestLevelSize; ++i)
	{
		const auto bbox = _octree->getNodeVolume(startingIndex + i);

		voxels[2 * i + 0] = bbox.getMinPoint();
		voxels[2 * i + 1] = bbox.getMaxPoint();
	}
}

void IGpuOctreeLoader::_calculateLowestLevelBufferOffsets(unsigned int nofEdges)
{
	assert(_speculativeRatioPot >= _speculativeRatioSil);

	_potBufferOffset = unsigned int(ceilf(nofEdges * _speculativeRatioPot));
	_silBufferOffset = unsigned int(ceilf(nofEdges * _speculativeRatioSil));
}

void IGpuOctreeLoader::setMaxBufferSize(uint64_t size)
{
	_maxBufferSizeBytes = size * 1024ull * 1024ull;
}

void IGpuOctreeLoader::setSpeculativeRatios(float potRatio, float silRatio)
{
	_speculativeRatioPot = potRatio;
	_speculativeRatioSil = silRatio;
}