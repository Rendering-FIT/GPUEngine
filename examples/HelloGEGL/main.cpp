#include <geAd/SDLWindow/SDLWindow.h>
#include <geAd/SDLWindow/SDLMainLoop.h>
#include <geGL/geGL.h>

using namespace std;
using namespace ge::gl;
using namespace ge::ad;

std::string vSrc = R".(
#version 450
void main() {
  gl_Position = vec4(gl_VertexID%2,gl_VertexID/2,1,1);
}).";

std::string fSrc = R".(
#version 450
out vec4 fColor;
void main(){
  fColor=vec4(1);
}
).";

int main(){
  auto mainLoop = make_shared<SDLMainLoop>();
  auto window = make_shared<SDLWindow>();

  window->createContext("rendering");
  mainLoop->addWindow("mainWindow", window);

  ge::gl::init(SDL_GL_GetProcAddress);
  setHighDebugMessage();

  auto vs = make_shared<Shader>(GL_VERTEX_SHADER, vSrc);
  auto fs = make_shared<Shader>(GL_FRAGMENT_SHADER, fSrc);
  auto program = make_shared<Program>(vs, fs);
  auto vao = make_shared<VertexArray>();
  
  auto gl = make_shared<Context>();

  mainLoop->setIdleCallback([&]() {
    gl->glClear(GL_COLOR_BUFFER_BIT);
    program->use();
    vao->bind();
    gl->glDrawArrays(GL_TRIANGLES, 0, 3);
    window->swap();
  });

  (*mainLoop)();
  return 0;
}
