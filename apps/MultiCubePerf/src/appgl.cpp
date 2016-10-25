#include "appgl.h"

using namespace std;
using namespace ge::gl;
using namespace ge::ad;
using namespace ge::util;
using namespace glm;

const string vertSrcA = R".(
#version 450
#extension GL_ARB_shader_draw_parameters : require
#extension GL_ARB_bindless_texture : require
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
#extension GL_ARB_bindless_texture : require
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
}

void AppGL::init() {
	printOpenGLVersion();

	prepareTextures();
	prepareGeometry();
	prepareMatrices();
	preparePrograms();

	SDL_GL_SetSwapInterval(0);
	ImGui_ImplSdlGL3_Init(windowHandle);
}

void AppGL::draw() {
	updateState();
	updateCamera();

	ImGui_ImplSdlGL3_NewFrame(windowHandle);
	stats->startFrame();

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	auto& p = *programs[getProgramID()].get();
	p.use();
	p.setMatrix4fv("v", value_ptr(view));
	p.setMatrix4fv("p", value_ptr(projection));
	p.set1i("textureCount", currentTextures);

	vertexArray->bind();

	switch (currentDrawMode) {
	case SINGLE_DRAW:
		glDrawArrays(GL_TRIANGLES, 0, 36 * currentCubes);
		break;
	case MANY_DRAW:
		for (int i = 0; i < currentCubes; i++) {
			p.set1i("id", i);
			glDrawArrays(GL_TRIANGLES, 36 * i, 36);
		}
		break;
	case INSTANCED:
		glDrawArraysInstanced(GL_TRIANGLES, 0, 36, currentCubes);
		break;
	case MULTIDRAW_INDIRECT:
		glMultiDrawArraysIndirect(GL_TRIANGLES, 0, currentCubes, 0);
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
		glMakeTextureHandleResidentARB(handle);
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
	int end = glm::min(maxCubes, side*side*side);
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
	id = (id << 1) | int(currentTextures > 0 && options.textureSize > 0);
	return id;
}