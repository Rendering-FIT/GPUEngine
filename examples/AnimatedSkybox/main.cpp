#include <geAd/SDLWindow/SDLWindow.h>
#include <geAd/SDLWindow/SDLMainLoop.h>
#include <geGL/StaticCalls.h>
#include <geGL/geGL.h>
#include<geUtil/OrbitCamera.h>
#include<geUtil/PerspectiveCamera.h>

using namespace std;
using namespace ge::gl;
using namespace ge::ad;
using namespace ge::util;

std::string vSrc = R".(
#version 450
out vec2 vCoord;
void main() {
  vec2 coord = vec2(-1+2*(gl_VertexID%2),-1+2*(gl_VertexID/2));
  vCoord = coord;
  gl_Position = vec4(coord,1,1);
}).";

std::string fSrc = R".(
#version 450
out vec4 fColor;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
in vec2 vCoord;
void main(){
  mat4 ipv = inverse(projectionMatrix*viewMatrix);
  vec3 viewVector = (ipv*vec4(vCoord,1,1)).xyz;
  vec3 viewPosition = (ipv*vec4(0,0,0,1)).xyz;
  fColor = mix(vec4(1,1,1,1),vec4(0,0,1,1),pow(abs(viewVector.y),.3));
//  fColor=vec4(viewVector,1);
}
).";

int main(int,char*[]){
  glm::uvec2 windowSize = glm::uvec2(1024,768);
  auto mainLoop = make_shared<SDLMainLoop>();
  auto window = make_shared<SDLWindow>(windowSize.x,windowSize.y);

  window->createContext("rendering");
  mainLoop->addWindow("mainWindow", window);

  ge::gl::init(SDL_GL_GetProcAddress);
  setHighDebugMessage();

  auto vs = make_shared<Shader>(GL_VERTEX_SHADER, vSrc);
  auto fs = make_shared<Shader>(GL_FRAGMENT_SHADER, fSrc);
  auto program = make_shared<Program>(vs, fs);
  auto vao = make_shared<VertexArray>();

  OrbitCamera orbitCamera;
  PerspectiveCamera perspectiveCamera(float(windowSize.x)/float(windowSize.y));
  float sensitivity = 0.001f;
  float orbitZoomSpeed = 0.1f;
 
  mainLoop->setIdleCallback([&]() {
    glClear(GL_COLOR_BUFFER_BIT);
    program->use();
    program->setMatrix4fv("viewMatrix",glm::value_ptr(orbitCamera.getView()));
    program->setMatrix4fv("projectionMatrix",glm::value_ptr(perspectiveCamera.getProjection()));
    vao->bind();
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    window->swap();
  });
  window->setEventCallback(SDL_MOUSEMOTION,[&](SDL_Event const&event){
    auto rel=glm::vec2(event.motion.yrel,event.motion.xrel);
    if(event.motion.state & SDL_BUTTON_LMASK){
      orbitCamera.addAngles(rel*sensitivity);
    }
    if(event.motion.state & SDL_BUTTON_RMASK){
      orbitCamera.addDistance(rel.y*orbitZoomSpeed);
    }
    if(event.motion.state & SDL_BUTTON_MMASK){
      orbitCamera.addXYPosition(rel*glm::vec2(-1.f,1.f)/glm::vec2(windowSize)*2.f);
    }
    return true;
  });

  (*mainLoop)();
  return 0;
}
