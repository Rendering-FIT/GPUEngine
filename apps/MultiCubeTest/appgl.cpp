#include "appgl.h"

using namespace std;
using namespace ge::gl;
using namespace ge::ad;
using namespace ge::util;
using namespace glm;

const string vertSrcA = R".(
#version 450
#extension GL_ARB_shader_draw_parameters : require
#extension GL_NV_bindless_texture : require
layout(location=0) in vec3 aPosition;
layout(location=1) in vec3 aNormal;
layout(location=2) in vec2 aTexCoord;
uniform mat4 v,p;
uniform int textureCount;
out vec3 position;
out vec3 normal;
out vec2 texCoord;
out flat sampler2D tex;

layout(std430, binding = 0) buffer matrixBuffer{
    mat4 model[];
};
layout(std430, binding= 1) buffer textureBuffer {
    sampler2D textures[];
};
).";

const string vertSrcBinstance = R".(
mat4 getModel(){
	return model[gl_InstanceID];
}
sampler2D getTex(){
	return textures[gl_InstanceID%textureCount];
}
).";

const string vertSrcBmultidraw = R".(
mat4 getModel(){
	return model[gl_DrawIDARB];
}
sampler2D getTex(){
	return textures[gl_DrawIDARB%textureCount];
}
).";

const string vertSrcBmany = R".(
uniform int id;
mat4 getModel(){
	return model[id];
}
sampler2D getTex(){
	return textures[id%textureCount];
}
).";

const string vertSrcBsingle = R".(
mat4 getModel(){
	return model[gl_VertexID/36];
}
sampler2D getTex(){
	return textures[(gl_VertexID/36)%textureCount];
}
).";

const string vertSrcC = R".(
void main() {
	mat4 m = getModel();
	vec4 pos = m*vec4(aPosition,1);
	position = pos.xyz;
	normal = aNormal;
	texCoord = aTexCoord;
	tex = getTex();
	gl_Position = p*v*pos;
}
).";



const string fragSrcA = R".(
#version 450
#extension GL_NV_bindless_texture : require
in vec3 position;
in vec3 normal;
in vec2 texCoord;

uniform vec3 ambientLight = vec3(0.4);
uniform vec3 diffuseLight = vec3(0.6);
uniform vec3 lightPosition = vec3(50,500,50);
).";

const string fragSrcBtexture = R".(
in flat sampler2D tex;
vec3 getColor(){
	return texture(tex,texCoord).xyz;
}
).";

const string fragSrcBcolor = R".(
vec3 getColor(){
	return vec3(1);	
}
).";

const string fragSrcC = R".(
out vec4 fragColor;
void main() {
	vec3 color = getColor();
	vec3 N = normalize(normal);
	vec3 L = normalize(lightPosition-position);
	vec3 A = color*ambientLight;
	vec3 D = color*diffuseLight*clamp(dot(N,L),0,1);
	fragColor = vec4(A+D,1);
}
).";

DrawMode modes[] = { INSTANCED, SINGLE_DRAW, /*MANY_DRAW,*/  MULTIDRAW_INDIRECT };
int texCounts[] = { 16,32,64,128,512,1024 };

AppGL::AppGL(Options const & o) :App(o) {
	maxCubes = o.cubeCount;
	cubeCount = maxCubes;

	maxTextures = o.textureCount;
	textureCount = maxTextures;
	currentDrawMode = o.drawMode;

	switch (options.appMode) {
	case CALIBRATE:
		currentState = WAIT;
		waitCounter = 60;
		cubeCount = 1000;
		stateStack.push_back([&]() {
			currentState = CALIBRATE;
		});
		break;
	case INTERATIVE:
		currentState = INTERATIVE;
		break;
	case TEST:
		currentState = WAIT_TIME;
		waitTime = 5000;
		waitStart = SDL_GetTicks();
		stateStack.push_back([&]() {
			currentState = TEST;
			angle = 0;
		});
		break;
	case CALIBRATE_ALL: {
		currentState = WAIT_TIME;
		waitTime = 5000;
		waitStart = SDL_GetTicks();
		// calibration tests
		for (int m = 0; m < 3; m++) {
			auto mode = modes[m];
			auto tc = 0;
			stateStack.push_back([&, mode, tc]() {

				currentDrawMode = mode;
				textureCount = tc;
				setCalibrate();
			});
			stateStack.push_back([&]() {
				currentState = WAIT;
				waitCounter = 60;
			});
		}

		for (int t = 0; t < 6; t++) {
			if (texCounts[t] <= maxTextures) {
				auto mode = SINGLE_DRAW;
				auto tc = texCounts[t];
				stateStack.push_back([&, mode, tc]() {
					currentDrawMode = mode;
					textureCount = tc;
					setCalibrate();
				});
				stateStack.push_back([&]() {
					currentState = WAIT;
					waitCounter = 60;
				});
			}
		}
		break;
	}
	case TEST_ALL: {
		currentState = WAIT_TIME;
		waitTime = 5000;
		waitStart = SDL_GetTicks();

		// fps tests
		for (int t = 0; t < 6; t++) {
			if (texCounts[t] <= maxTextures) {
				auto mode = SINGLE_DRAW;
				auto tc = texCounts[t];
				stateStack.push_back([&, mode, tc]() {
					setTest();
					currentDrawMode = mode;
					textureCount = tc;
					cubeCount = maxCubes;
				});
				stateStack.push_back([&]() {
					currentState = WAIT;
					waitCounter = 60;
				});
			}
		}

		for (int m = 0; m < 3; m++) {
			auto mode = modes[m];
			auto tc = 0;
			stateStack.push_back([&, mode, tc]() {
				setTest();
				currentDrawMode = mode;
				textureCount = tc;
				cubeCount = maxCubes;
			});
			stateStack.push_back([&]() {
				currentState = WAIT;
				waitCounter = 60;
			});
		}

		break;
	}
	}

	auto c = glGetString(GL_VENDOR);
	std::cout << c << "\n";
	c = glGetString(GL_VERSION);
	std::cout << c << "\n";
	c = glGetString(GL_RENDERER);
	std::cout << c << "\n";
}

void AppGL::init() {
	prepareTextures();
	prepareGeometry();
	prepareMatrices();
	preparePrograms();
}

void AppGL::draw() {
	updateState();

	ImGui_ImplSdlGL3_NewFrame(windowHandle);
	stats->startFrame();

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);


	int side = getSide();
	zoom = side * 2.2f;
	float a = radians(angle + 45);
	view = lookAt(zoom*vec3(cos(a), 1, sin(a)), vec3(0, 0, 0), vec3(0, 1, 0));
	int w = window->getWidth();
	int h = window->getHeight();
	projection = perspective(radians(60.f), float(w) / float(h), 1.0f, 10000.f);

	auto& p = *programs[getProgramID()].get();
	p.use();
	p.setMatrix4fv("v", value_ptr(view));
	p.setMatrix4fv("p", value_ptr(projection));
	p.set1i("textureCount", textureCount);

	vertexArray->bind();

	switch (currentDrawMode) {
	case SINGLE_DRAW:
		glDrawArrays(GL_TRIANGLES, 0, 36 * cubeCount);
		break;
	case MANY_DRAW:
		for (int i = 0; i < cubeCount; i++) {
			p.set1i("id", i);
			glDrawArrays(GL_TRIANGLES, 36 * i, 36);
		}
		break;
	case INSTANCED:
		glDrawArraysInstanced(GL_TRIANGLES, 0, 36, cubeCount);
		break;
	case MULTIDRAW_INDIRECT:
		glMultiDrawArraysIndirect(GL_TRIANGLES, 0, cubeCount, 0);
		break;
	}

	stats->endFrame();
	stats->draw();
	ImGui::Render();
	window->swap();
}

void AppGL::prepareTextures() {
	vector<GLuint64> texHandleData;
	texHandleData.reserve(maxTextures);

	for (int i = 0; i < maxTextures; i++) {
		GLuint tex = generateTexture(options.textureSize);
		GLuint64 handle = glGetTextureHandleARB(tex);
		glMakeTextureHandleResidentNV(handle);
		texHandleData.push_back(handle);
	}

	textureBuffer = make_shared<Buffer>();
	textureBuffer->alloc(sizeof(GLuint64)*texHandleData.size(), texHandleData.data());
	textureBuffer->bindBase(GL_SHADER_STORAGE_BUFFER, 1);
}

void AppGL::prepareGeometry() {
	int count = maxCubes;
	if (options.drawMode == INSTANCED &&
		options.appMode != TEST_ALL) {
		count = 1;
	}

	vector<Vertex> vertexData;
	vertexData.reserve(count * 36);
	vector<DrawArraysIndirectCommand> indirectData;
	indirectData.reserve(count);

	for (int i = 0; i < count; i++) {
		uint firstVertex = (uint)vertexData.size();
		generateCubeVertices(vertexData);
		indirectData.emplace_back(DrawArraysIndirectCommand{ 36,1,firstVertex,0 });
	}

	vertexBuffer = make_shared<Buffer>();
	vertexBuffer->alloc(sizeof(Vertex)*vertexData.size(), vertexData.data());

	indirectBuffer = make_shared<Buffer>();
	indirectBuffer->alloc(sizeof(DrawArraysIndirectCommand)*indirectData.size(), indirectData.data());
	indirectBuffer->bind(GL_DRAW_INDIRECT_BUFFER);

	vertexArray = make_shared<VertexArray>();
	vertexArray->addAttrib(vertexBuffer, 0, 3, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, pos));
	vertexArray->addAttrib(vertexBuffer, 1, 3, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, norm));
	vertexArray->addAttrib(vertexBuffer, 2, 2, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, tc));
}

void AppGL::prepareMatrices() {
	matrixBuffer = make_shared<Buffer>();
	matrixBuffer->alloc(sizeof(mat4)*maxCubes);
	matrixBuffer->bindBase(GL_SHADER_STORAGE_BUFFER, 0);
	recomputeMatrices(maxCubes);
}

void AppGL::recomputeMatrices(int count) {
	vector<mat4> matrixData;

	int side = (int)ceil(cbrtf(float(count)));
	vec3 offset = vec3(float(side));
	int end = min(maxCubes, side*side*side);
	matrixData.reserve(end);

	for (int i = 0; i < end; i++) {
		int x = i % side;
		int y = (i / side) % side;
		int z = i / (side*side);
		mat4 m = translate(mat4(), vec3(x, y, z)*2.0f - offset);
		matrixData.emplace_back(m);
	}
	matrixBuffer->setData(matrixData.data(), sizeof(mat4)*matrixData.size());
	glFinish();
}

void AppGL::preparePrograms() {
	std::string vertSrcB[] = { vertSrcBsingle,vertSrcBmany,vertSrcBinstance,vertSrcBmultidraw };
	std::string fragSrcB[] = { fragSrcBcolor,fragSrcBtexture };
	ge::gl::Program::setNonexistingUniformWarning(false);
	for (int i = 0; i < 8; i++) {
		auto vs = make_shared<Shader>(GL_VERTEX_SHADER, vertSrcA, vertSrcB[i >> 1], vertSrcC);
		auto fs = make_shared<Shader>(GL_FRAGMENT_SHADER, fragSrcA, fragSrcB[i & 1], fragSrcC);
		programs[i] = make_shared<Program>(vs, fs);
	}

}

int AppGL::getProgramID() {
	int id = (int)currentDrawMode;
	id = (id << 1) | int(textureCount > 0 && options.textureSize > 0);
	return id;
}

int AppGL::getSide() {
	return (int)ceil(cbrtf(float(cubeCount)));
}

void AppGL::setCalibrate() {
	cubeCount = 1000;
	currentState = CALIBRATE;
	zeroCounter = 0;
	difCounter = 0;
}

void AppGL::setTest() {
	angle = 0;
	currentState = TEST;
}

void AppGL::updateState() {
	switch (currentState) {
	case INTERATIVE:
		break;
	case TEST: {
		float fps = stats->getFps();
		if (angle == 0) {
			std::cout << "Test " << cubeCount << " cubes, " << textureCount << " textures, " << drawModeToString(currentDrawMode) << ": ";
			std::cout << "back-front: " << fps;
		}
		if (angle == 180) {
			std::cout << ", front-back: " << fps;
		}
		if (angle == 360) {
			std::cout << ", 360-avg: " << 1e3 / stats->getAvg(120) << "\n";
			currentState = WAIT;
		}
		angle += 3;
		break;
	}
	case CALIBRATE: {
		//cout << "cubeCount " << cubeCount << " "<< maxCubes<<"\n";
		float fps = stats->getFps();

		if (fps < 60) {
			difCounter = max(difCounter - 1, -10);
			if (difCounter == -10) {
				cubeCount -= 10;
			}
		}
		if (fps > 60) {
			difCounter = min(difCounter + 1, 10);
			if (difCounter == 10) {
				if (fps > 150 && currentDrawMode != MANY_DRAW)cubeCount *= 2;
				else if (fps > 75 && currentDrawMode != MANY_DRAW)cubeCount += 1000;
				else if (fps > 61)cubeCount += 100;
				else cubeCount += 10;
				cubeCount = min(cubeCount, maxCubes);
			}
		}

		if (difCounter == 0)zeroCounter++;
		if (zeroCounter == 5) {
			std::cout << "Calibrate 60 fps, " << textureCount << " textures, " << drawModeToString(currentDrawMode) << " - " << cubeCount << " cubes\n";
			currentState = WAIT;
		}
		if (cubeCount == maxCubes) {
			std::cout << "Calibrate reached max, " << textureCount << " textures, " << drawModeToString(currentDrawMode) << " - " << cubeCount << " cubes, " << fps << " fps\n";
			currentState = WAIT;
		}

		if (getSide() != currentSide) {
			recomputeMatrices(cubeCount);
			currentSide = getSide();
			currentState = WAIT;
			waitCounter = 10;
			stateStack.insert(stateStack.begin(), [&]() {
				currentState = CALIBRATE;
			});

		}
		break;
	}
	case WAIT_TIME: {
		if (SDL_GetTicks() - waitStart > waitTime) {
			currentState = WAIT;
			waitCounter = 0;
		}
		break;
	}
	case WAIT:
		waitCounter--;
		if (waitCounter <= 0) {
			if (stateStack.size() == 0) {
				quit();
			}
			else {
				stateStack.at(0)();
				stateStack.erase(stateStack.begin());
			}
		}
		break;
	}
}
