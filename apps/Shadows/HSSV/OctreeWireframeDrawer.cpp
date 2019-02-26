#include "OctreeWireframeDrawer.hpp"
#include <geGL/Program.h>
#include <geGL/VertexArray.h>
#include <geGL/StaticCalls.h>
#include <glm/gtc/type_ptr.hpp>

const std::string vsSource = R".(
#version 450 core

layout(location=0) in vec3 vertex;
layout(location=1) in vec3 positionOffset;

uniform mat4 vp;

void main()
{
	gl_Position = vp * vec4(vertex + positionOffset, 1);
}
).";

const std::string fsSource = R".(
#version 450 core

uniform vec4 color;

out vec4 outColor;

void main()
{
	outColor = color;
}
).";

OctreeWireframeDrawer::OctreeWireframeDrawer()
{}


bool OctreeWireframeDrawer::init(std::shared_ptr<Octree> octree)
{
	_octree = octree;
	_instanceCount = _octree->getLevelSize(_octree->getDeepestLevel());

	if (!_initProgram())
	{
		return false;
	}

	_initBuffers();

	ge::gl::glLineWidth(3.0f);

	return true;
}

void OctreeWireframeDrawer::drawWireframe(glm::mat4 const& vp)
{
	const glm::vec4 color = glm::vec4(1.0f, 1.0f, 0, 1.0f);

	_program->use();
	_program->setMatrix4fv("vp", glm::value_ptr(vp))->set4fv("color", glm::value_ptr(color));
	_vao->bind();

	ge::gl::glDrawElementsInstanced(GL_LINES, 24, GL_UNSIGNED_SHORT, nullptr, _instanceCount);

	_vao->unbind();
}

bool OctreeWireframeDrawer::_initProgram()
{
	_program = std::make_shared<ge::gl::Program>(
		std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, vsSource), 
		std::make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER, fsSource));

	return _program->isProgram();
}

void OctreeWireframeDrawer::_initBuffers()
{
	const auto deepestLevel = _octree->getDeepestLevel();
	const auto levelSize = _octree->getLevelSize(deepestLevel);
	const auto startIndex = _octree->getLevelFirstNodeID(_octree->getDeepestLevel());
	
	//Get cube scale x,y,z
	const auto n = _octree->getNode(startIndex);
	glm::vec3 extents = n->volume.getExtents();

	//Generate single cell geometry, based on scale (all cells are same size)
	glm::vec3 vertices[8];
	for(uint32_t i=0; i<8; ++i)
	{
		vertices[i] = glm::vec3(0.5 *((i & 1) ? 1.0f : -1.0f), 0.5 * ((i & 2) ? 1.0f : -1.0f), 0.5*((i & 4) ? 1.0f : -1.0f)) * extents;
	}

	//Construct lines
	uint16_t ebo[] = 
	{
		//Front
		0, 1,
		0, 2,
		1, 3,
		2, 3,
		//Back
		4, 5,
		5, 7,
		7, 6,
		4, 6,
		//Top
		3, 7,
		2, 6,
		//Bottom
		0, 4,
		1, 5
	};

	_vbo = std::make_shared<ge::gl::Buffer>(8 * 3 * sizeof(float), vertices);
	_ebo = std::make_shared<ge::gl::Buffer>(24 * sizeof(glm::uint), ebo);

	//Get position offsets
	std::vector<glm::vec3> offsets;
	offsets.resize(levelSize);

	for(uint32_t i = startIndex; i<(startIndex + levelSize); ++i)
	{
		const auto node = _octree->getNode(i);
		offsets[i - startIndex] = node->volume.getCenterPoint();
	}

	_instanceBuffer = std::make_shared<ge::gl::Buffer>(levelSize * 3 * sizeof(float), offsets.data());

	_vao = std::make_shared<ge::gl::VertexArray>();
	_vao->addAttrib(_vbo, 0, 3, GL_FLOAT);
	_vao->addAttrib(_instanceBuffer, 1, 3, GL_FLOAT, 0, 0, 0, 1);
	_vao->addElementBuffer(_ebo);
}
