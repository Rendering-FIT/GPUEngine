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
	void recomputeMatrices(int count);
	void preparePrograms();
	
	int getProgramID();
	int getSide();

	void setCalibrate();
	void setTest();

	void updateState();
	
	std::shared_ptr<ge::gl::Program> programs[8];

	std::shared_ptr<ge::gl::Buffer> vertexBuffer;
	std::shared_ptr<ge::gl::Buffer> indirectBuffer;
	std::shared_ptr<ge::gl::Buffer> matrixBuffer;
	std::shared_ptr<ge::gl::Buffer> textureBuffer;
	std::shared_ptr<ge::gl::VertexArray> vertexArray;

	float angle = glm::radians(45.0f);
	float zoom = 100;
	int cubeCount = 0;
	int maxCubes = 0;
	int currentSide = 0;
	int waitCounter = 0;
	int difCounter = 0;
	int zeroCounter = 0;
	int textureCount = 0;
	int maxTextures = 0;
	unsigned int waitStart = 0;
	unsigned int waitTime = 0;

	AppMode currentState;
	DrawMode currentDrawMode;
	std::vector<std::function<void()>> stateStack;
};