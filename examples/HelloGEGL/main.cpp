#include <geGL/Program.h>
#include <geAd/SDLWindow/SDLWindow.h>
#include <geAd/SDLWindow/SDLMainLoop.h>
#include <geGL/geGL.h>

#include <memory>

using namespace std;
using namespace ge::gl;
using namespace ge::ad;


std::string vsrc = R".(
#version 450
vec4 cc[3] = vec4[](vec4(1, 0, 0, 1), vec4(0, 1, 0, 1), vec4(0, 0, 1, 1));
vec2 pp[3] = vec2[](vec2(0, 0.8), vec2(-0.7, -0.4), vec2(0.7, -0.4));
out vec4 c;
void main() {
	c = cc[gl_VertexID];
	gl_Position = vec4(pp[gl_VertexID],1,1);
}).";

std::string fsrc = R".(
#version 450
in vec4 c;
out vec4 f;
void main(){
	f=c;
}
).";

int main(int argc,char* argv[]){
	auto mainLoop = make_shared<SDLMainLoop>();
	auto window = make_shared<SDLWindow>();

	window->createContext("rendering", 450u, SDLWindow::CORE, SDLWindow::DEBUG);
	mainLoop->addWindow("mainWindow", window);

	ge::gl::init(SDL_GL_GetProcAddress);
	setHighDebugMessage();

	auto vs = make_shared<Shader>(GL_VERTEX_SHADER, vsrc);
	auto fs = make_shared<Shader>(GL_FRAGMENT_SHADER, fsrc);
	auto program = make_shared<Program>(vs, fs);
	auto vao = make_shared<VertexArray>();
	
	auto gl = make_shared<Context>();

	mainLoop->setIdleCallback([&]() {
		gl->glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		gl->glClear(GL_COLOR_BUFFER_BIT);
		program->use();
		vao->bind();
		gl->glDrawArrays(GL_TRIANGLES, 0, 3);
		window->swap();
	});

	(*mainLoop)();
	return 0;
}