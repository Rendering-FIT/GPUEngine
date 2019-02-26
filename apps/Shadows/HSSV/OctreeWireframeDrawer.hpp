#pragma once

#include "Octree.hpp"

#include <memory>
#include <geGL/Buffer.h>

class OctreeWireframeDrawer
{
public:
	OctreeWireframeDrawer();
	virtual ~OctreeWireframeDrawer(){}

	bool init(std::shared_ptr<Octree> octree);
	void drawWireframe(glm::mat4& vp);

protected:
	bool _initProgram();
	void _initBuffers();

private:
	std::shared_ptr<Octree> _octree;
	uint32_t _instanceCount = 0;

	std::shared_ptr<ge::gl::Buffer> _vbo;
	std::shared_ptr<ge::gl::VertexArray> _vao;
	std::shared_ptr<ge::gl::Buffer> _ebo;
	std::shared_ptr<ge::gl::Buffer> _instanceBuffer;

	std::shared_ptr<ge::gl::Program> _program;
};
