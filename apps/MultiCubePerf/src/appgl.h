#pragma once

#include "app.h"
#include <functional>

struct DrawArraysIndirectCommand {
	GLuint count;
	GLuint primCount;
	GLuint first;
	GLuint baseInstance;
};

class AppGL : public App {
public:
	AppGL(Options const& o = Options());

	virtual void init();
	virtual void draw();
protected:
	void prepareTextures();
	void prepareGeometry();
	void prepareMatrices();
	virtual void recomputeMatrices(int count);
	void preparePrograms();

	int getProgramID();

	std::shared_ptr<ge::gl::Program> programs[8];

	std::shared_ptr<ge::gl::Buffer> vertexBuffer;
	std::shared_ptr<ge::gl::Buffer> indirectBuffer;
	std::shared_ptr<ge::gl::Buffer> matrixBuffer;
	std::shared_ptr<ge::gl::Buffer> textureBuffer;
	std::shared_ptr<ge::gl::VertexArray> vertexArray;

};