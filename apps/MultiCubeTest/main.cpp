#include <limits>
#include <string>
#include <geGL/geGL.h>
#include <geAd/SDLWindow/SDLWindow.h>
#include <geGL/OpenGLCommands.h>
#include <geGL/OpenGLContext.h>
#include <functional>
#include <geUtil/CameraObject.h>
#include <geUtil/OrbitManipulator.h>
#include <cmath>

#include "gui.h"
#include "stats.h"


using namespace std;
using namespace ge::gl;
using namespace ge::ad;
using namespace ge::util;
using namespace glm;

struct Vertex {
	vec3 pos;
	vec3 norm;
	vec2 tc;
};

struct DrawArraysIndirectCommand {
	uint  count;
	uint  primCount;
	uint  first;
	uint  baseInstance;
};

class App : Context {
public:
	App();
	int run();
	void draw();
	bool handleEvent(SDL_Event const&e);
private:
	void init();
	void createCubes(int count);
	GLuint generateTexture();
	shared_ptr<Context> gl;
	shared_ptr<SDLMainLoop> mainLoop;
	shared_ptr<SDLWindow> window;
	SDL_Window* windowHandle;

	shared_ptr<Program> program;
	shared_ptr<CameraObject> camera;
	shared_ptr<OrbitManipulator> manipulator;

	shared_ptr<Buffer> vertexBuffer;
	shared_ptr<Buffer> indirectBuffer;
	shared_ptr<Buffer> matrixBuffer;
	shared_ptr<Buffer> textureBuffer;
	shared_ptr<VertexArray> vertexArray;
	shared_ptr<Stats> stats;

	mat4 view;
	mat4 projection;
	const int cubeCount = 100000;
};

void bindDraw(void* app) {
	((App*)app)->draw();
}

bool bindHandleEvent(SDL_Event const&e, void* app) {
	return ((App*)app)->handleEvent(e);
}

App::App() {
	mainLoop = make_shared<SDLMainLoop>();
	mainLoop->setIdleCallback(bindDraw, this);
	mainLoop->setIdleCallback(std::bind(&App::draw,this));
	mainLoop->setEventHandler(std::bind(&App::handleEvent, this, std::placeholders::_1));

	window = make_shared<SDLWindow>();
	window->createContext("rendering", 450u, SDLWindow::CORE, SDLWindow::DEBUG);
	mainLoop->addWindow("mainWindow", window);
	window->makeCurrent("rendering");

	ge::gl::init(SDL_GL_GetProcAddress);

	this->setFunctionTable(getDefaultContext()->getFunctionTable());
	setHighDebugMessage();

	stats = make_shared<Stats>();


	windowHandle = SDL_GetWindowFromID(window->getId());
	ImGui_ImplSdlGL3_Init(windowHandle);
}



void App::init() {
	const string vertSrc = R".(
#version 450
#extension GL_ARB_shader_draw_parameters : require
layout(location=0) in vec3 aPosition;
layout(location=1) in vec3 aNormal;
layout(location=2) in vec2 aTexCoord;

layout(std430, binding = 0) buffer matrixBuffer{
    mat4 model[];
};

uniform mat4 v,p;

out vec3 position;
out vec3 normal;
out vec2 texCoord;
out int drawID;
void main() {
	drawID=gl_VertexID/36;
	mat4 m = model[drawID];
	vec4 pos = m*vec4(aPosition,1);
	position = pos.xyz;
	normal = aNormal;
	texCoord = aTexCoord;
	gl_Position = p*v*pos;
}).";

	const string fragSrc = R".(
#version 450
#extension GL_ARB_bindless_texture : require
in vec3 position;
in vec3 normal;
in vec2 texCoord;
in flat int drawID;

layout(binding=1) buffer textureBuffer {
    sampler2D tex[];
};

uniform vec3 ambientLight = vec3(0.4);
uniform vec3 diffuseLight = vec3(0.6);
uniform vec3 lightPosition = vec3(50,500,50);

out vec4 fragColor;
void main() {
	vec3 color = texture(tex[drawID&0x3FF],texCoord).xyz;
	vec3 N = normalize(normal);
	vec3 L = normalize(lightPosition-position);
	vec3 A = color*ambientLight;
	vec3 D = color*diffuseLight*clamp(dot(N,L),0,1);
	fragColor = vec4(A+D,1);
}).";

	auto vs = make_shared<Shader>(GL_VERTEX_SHADER, vertSrc);
	auto fs = make_shared<Shader>(GL_FRAGMENT_SHADER, fragSrc);
	program = make_shared<Program>(vs, fs);

	glClearColor(0, 0, 0, 1);

	int w = window->getWidth();
	int h = window->getHeight();
	view = lookAt(vec3(20, 20, 20), vec3(0, 0, 0), vec3(0, 1, 0));
	projection = perspective(radians(60.f), float(w) / float(h), 10.0f, 10000.f);

	vertexBuffer = make_shared<Buffer>();
	matrixBuffer = make_shared<Buffer>();
	indirectBuffer = make_shared<Buffer>();
	textureBuffer = make_shared<Buffer>();

	createCubes(cubeCount);

	vertexArray = make_shared<VertexArray>();
	vertexArray->addAttrib(vertexBuffer, 0, 3, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, pos));
	vertexArray->addAttrib(vertexBuffer, 1, 3, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, norm));
	vertexArray->addAttrib(vertexBuffer, 2, 2, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, tc));

	indirectBuffer->bind(GL_DRAW_INDIRECT_BUFFER);
	matrixBuffer->bindBase(GL_SHADER_STORAGE_BUFFER, 0);
	textureBuffer->bindBase(GL_SHADER_STORAGE_BUFFER, 1);
}

void quad(vector<Vertex>& vertexData,
	vec3 p0, vec3 p1, vec3 p2, vec3 p3) {
	vec3 norm = normalize(cross(p1 - p0, p2 - p0));
	vertexData.emplace_back(Vertex{ p0,norm,vec2(0,0) });
	vertexData.emplace_back(Vertex{ p1,norm,vec2(1,0) });
	vertexData.emplace_back(Vertex{ p2,norm,vec2(1,1) });
	vertexData.emplace_back(Vertex{ p0,norm,vec2(0,0) });
	vertexData.emplace_back(Vertex{ p2,norm,vec2(1,1) });
	vertexData.emplace_back(Vertex{ p3,norm,vec2(0,1) });
}

void App::createCubes(int count) {
	vector<Vertex> vertexData;
	vertexData.reserve(count * 6 * 6);
	vector<DrawArraysIndirectCommand> indirectData;
	indirectData.reserve(count);
	vector<mat4> matrixData;
	matrixData.reserve(count);
	vector<GLuint64> texHandleData;
	texHandleData.reserve(count);

	int side = (int)ceil(cbrt(count));
	vec3 offset = vec3(float(side));
	for (int i = 0; i < count; i++) {
		uint firstVertex = (uint) vertexData.size();
		quad(vertexData, vec3(0, 1, 1), vec3(0, 0, 1), vec3(1, 0, 1), vec3(1, 1, 1));
		quad(vertexData, vec3(1, 1, 0), vec3(1, 0, 0), vec3(0, 0, 0), vec3(0, 1, 0));
		quad(vertexData, vec3(1, 1, 1), vec3(1, 0, 1), vec3(1, 0, 0), vec3(1, 1, 0));
		quad(vertexData, vec3(0, 1, 0), vec3(0, 0, 0), vec3(0, 0, 1), vec3(0, 1, 1));
		quad(vertexData, vec3(0, 0, 1), vec3(0, 0, 0), vec3(1, 0, 0), vec3(1, 0, 1));
		quad(vertexData, vec3(0, 1, 1), vec3(1, 1, 1), vec3(1, 1, 0), vec3(0, 1, 0));

		indirectData.emplace_back(DrawArraysIndirectCommand{ 36,1,firstVertex,0 });

		if(i<=0x3FF){
			GLuint tex = generateTexture();
			GLuint64 handle = glGetTextureHandleARB(tex);
			glMakeTextureHandleResidentARB(handle);
			texHandleData.emplace_back(handle);
		}

		int x = i % side;
		int y = (i / side) % side;
		int z = i / (side*side);
		mat4 m = translate(mat4(), vec3(x, y, z)*2.0f - offset);
		matrixData.emplace_back(m);
	}
	vertexBuffer->alloc(sizeof(Vertex)*vertexData.size(), vertexData.data());
	indirectBuffer->alloc(sizeof(DrawArraysIndirectCommand)*indirectData.size(), indirectData.data());
	matrixBuffer->alloc(sizeof(mat4)*matrixData.size(), matrixData.data());
	textureBuffer->alloc(sizeof(GLuint64)*texHandleData.size(), texHandleData.data());
}

GLuint App::generateTexture() {
	int width = 128;
	int height = 128;
	uint *data = new uint[width * height];
	unsigned int colors[] = {
		0xFF000000,
		0xFFFF0000,
		0xFF00FF00,
		0xFF0000FF,
		0xFFFFFF00,
		0xFFFF00FF,
		0xFF00FFFF,
		0xFFFFFFFF
	};
	int c1 = rand() % 8;
	int c2 = rand() % 8;
	if (c2 == c1)c2 = (c2 + 1) % 8;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (((x >> 4) & 1) == ((y >> 4) & 1))
				data[y * width + x] = colors[c1];
			else
				data[y * width + x] = colors[c2];
		}
	}
	GLuint tex;
	glCreateTextures(GL_TEXTURE_2D, 1, &tex);
	glTextureImage2DEXT(tex, GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateTextureMipmap(tex);
	glTextureParameteri(tex, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTextureParameteri(tex, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTextureParameteri(tex, GL_TEXTURE_WRAP_R, GL_REPEAT);
	glTextureParameteri(tex, GL_TEXTURE_WRAP_S, GL_REPEAT);
	delete[] data;
	return tex;
}

void App::draw() {
	
	uint ticks = SDL_GetTicks();
	ImGui_ImplSdlGL3_NewFrame(windowHandle);

	stats->startFrame();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	view = lookAt(100.0f*vec3(cos(ticks*0.0002), 1, sin(ticks*0.0002)), vec3(0, 0, 0), vec3(0, 1, 0));

	program->use();
	vertexArray->bind();

	program->setMatrix4fv("v", value_ptr(view));
	program->setMatrix4fv("p", value_ptr(projection));

	//glMultiDrawArraysIndirect(GL_TRIANGLES, 0, cubeCount, 0);
	glDrawArrays(GL_TRIANGLES, 0, cubeCount*36);
	//glDrawArraysInstanced(GL_TRIANGLES, 0, 36, cubeCount);

	stats->endFrame();

	stats->draw();


	ImGui::Render();
	window->swap();
}

bool App::handleEvent(SDL_Event const & e) {
	SDL_Event ev = e;
	ImGui_ImplSdlGL3_ProcessEvent(&ev);

	switch (e.type) {
	case SDL_QUIT:
		mainLoop->removeWindow("mainWindow");
		break;
	}
	return true;
}

int App::run() {
	init();
	(*mainLoop)();
	return 0;
}

int main(int, char*[]) {
	App app;
	return app.run();
}
