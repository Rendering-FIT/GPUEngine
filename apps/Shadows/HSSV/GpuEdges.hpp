#pragma once

#include <geGL/Buffer.h>

struct GpuEdges
{
	std::shared_ptr<ge::gl::Buffer> _edges;
	std::shared_ptr<ge::gl::Buffer> _oppositeVertices;
};