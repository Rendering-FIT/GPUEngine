#include "GpuOctreeEdgePropagator.hpp"
#include "PropagateIndicesShader.hpp"

#include <geGL/StaticCalls.h>




bool GpuOctreeEdgePropagator::_createPropagateProgram(unsigned numSubgroupsPerWG, unsigned subgroupSize)
{
	assert(subgroupSize == 32 || subgroupSize == 64);
	assert(ge::gl::glGetError() == GL_NO_ERROR);

	_propagateProgram = std::make_shared<ge::gl::Program>(std::make_shared<ge::gl::Shader>(GL_COMPUTE_SHADER, buildComputeShaderPropagate(numSubgroupsPerWG, subgroupSize)));

	assert(ge::gl::glGetError() == GL_NO_ERROR);
	return _propagateProgram->isProgram();
}
