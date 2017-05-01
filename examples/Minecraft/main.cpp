#include<geAd/SDLWindow/SDLWindow.h>
#include<geAd/SDLWindow/SDLMainLoop.h>
#include<geGL/StaticCalls.h>
#include<geGL/geGL.h>
#include<geGL/GLSLNoise.h>
#include<geUtil/OrbitCamera.h>
#include<geUtil/PerspectiveCamera.h>
#include<geUtil/Timer.h>

using namespace std;
using namespace ge::gl;
using namespace ge::ad;
using namespace ge::util;

std::string const vSrc = R".(
#version 450
flat out uint vId;
void main(){
  vId=gl_VertexID;
}).";

std::string const gSrc = R".(
layout(points)in;
layout(triangle_strip,max_vertices=24)out;

flat in uint vId[];

out vec3 gNormal;
out vec3 gPosition;

uniform uint gridSize;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 cameraPosition;

void main(){
  vec3 cubeCorner = vec3(vId[0]%gridSize,(vId[0]/gridSize)%gridSize,(vId[0]/gridSize/gridSize)%gridSize);

  cubeCorner -= vec3(gridSize/2.f);
  cubeCorner -= cameraPosition;
  vec3 Pos = cubeCorner;//trunc(cameraPosition*gridSize)/gridSize;
  float t=noise(ivec3(Pos),6u,6u,2.)*.5+.5;

  if(t<.35||t>0.45)return;
  
  mat4 mvp = projectionMatrix * viewMatrix;

  //cubeCorner -= fract(cameraPosition*gridSize)/gridSize;
  vec4 pp=mvp*vec4(cubeCorner,1);
  if(pp.z>pp.w||pp.z<-pp.w||pp.x<-pp.w||pp.x>pp.w||pp.y<-pp.w||pp.y>pp.w)return;

  gl_Position=mvp*vec4(cubeCorner+vec3(0,0,0),1);gNormal=vec3(0,0,-1);gPosition=cubeCorner+vec3(0,0,0);EmitVertex();
  gl_Position=mvp*vec4(cubeCorner+vec3(1,0,0),1);gNormal=vec3(0,0,-1);gPosition=cubeCorner+vec3(1,0,0);EmitVertex();
  gl_Position=mvp*vec4(cubeCorner+vec3(0,1,0),1);gNormal=vec3(0,0,-1);gPosition=cubeCorner+vec3(0,1,0);EmitVertex();
  gl_Position=mvp*vec4(cubeCorner+vec3(1,1,0),1);gNormal=vec3(0,0,-1);gPosition=cubeCorner+vec3(1,1,0);EmitVertex();
  EndPrimitive();

  gl_Position=mvp*vec4(cubeCorner+vec3(0,1,0),1);gNormal=vec3(0,1,0 );gPosition=cubeCorner+vec3(0,1,0);EmitVertex();
  gl_Position=mvp*vec4(cubeCorner+vec3(1,1,0),1);gNormal=vec3(0,1,0 );gPosition=cubeCorner+vec3(1,1,0);EmitVertex();
  gl_Position=mvp*vec4(cubeCorner+vec3(0,1,1),1);gNormal=vec3(0,1,0 );gPosition=cubeCorner+vec3(0,1,1);EmitVertex();
  gl_Position=mvp*vec4(cubeCorner+vec3(1,1,1),1);gNormal=vec3(0,1,0 );gPosition=cubeCorner+vec3(1,1,1);EmitVertex();
  EndPrimitive();

  gl_Position=mvp*vec4(cubeCorner+vec3(0,1,1),1);gNormal=vec3(0,0,1 );gPosition=cubeCorner+vec3(0,1,1);EmitVertex();
  gl_Position=mvp*vec4(cubeCorner+vec3(1,1,1),1);gNormal=vec3(0,0,1 );gPosition=cubeCorner+vec3(1,1,1);EmitVertex();
  gl_Position=mvp*vec4(cubeCorner+vec3(0,0,1),1);gNormal=vec3(0,0,1 );gPosition=cubeCorner+vec3(0,0,1);EmitVertex();
  gl_Position=mvp*vec4(cubeCorner+vec3(1,0,1),1);gNormal=vec3(0,0,1 );gPosition=cubeCorner+vec3(1,0,1);EmitVertex();
  EndPrimitive();

  gl_Position=mvp*vec4(cubeCorner+vec3(0,0,1),1);gNormal=vec3(0,-1,0);gPosition=cubeCorner+vec3(0,0,1);EmitVertex();
  gl_Position=mvp*vec4(cubeCorner+vec3(1,0,1),1);gNormal=vec3(0,-1,0);gPosition=cubeCorner+vec3(1,0,1);EmitVertex();
  gl_Position=mvp*vec4(cubeCorner+vec3(0,0,0),1);gNormal=vec3(0,-1,0);gPosition=cubeCorner+vec3(0,0,0);EmitVertex();
  gl_Position=mvp*vec4(cubeCorner+vec3(1,0,0),1);gNormal=vec3(0,-1,0);gPosition=cubeCorner+vec3(1,0,0);EmitVertex();
  EndPrimitive();

  gl_Position=mvp*vec4(cubeCorner+vec3(0,0,1),1);gNormal=vec3(-1,0,0);gPosition=cubeCorner+vec3(0,0,1);EmitVertex();
  gl_Position=mvp*vec4(cubeCorner+vec3(0,0,0),1);gNormal=vec3(-1,0,0);gPosition=cubeCorner+vec3(0,0,0);EmitVertex();
  gl_Position=mvp*vec4(cubeCorner+vec3(0,1,1),1);gNormal=vec3(-1,0,0);gPosition=cubeCorner+vec3(0,1,1);EmitVertex();
  gl_Position=mvp*vec4(cubeCorner+vec3(0,1,0),1);gNormal=vec3(-1,0,0);gPosition=cubeCorner+vec3(0,1,0);EmitVertex();
  EndPrimitive();

  gl_Position=mvp*vec4(cubeCorner+vec3(1,0,0),1);gNormal=vec3( 1,0,0);gPosition=cubeCorner+vec3(1,0,0);EmitVertex();
  gl_Position=mvp*vec4(cubeCorner+vec3(1,0,1),1);gNormal=vec3( 1,0,0);gPosition=cubeCorner+vec3(1,0,1);EmitVertex();
  gl_Position=mvp*vec4(cubeCorner+vec3(1,1,0),1);gNormal=vec3( 1,0,0);gPosition=cubeCorner+vec3(1,1,0);EmitVertex();
  gl_Position=mvp*vec4(cubeCorner+vec3(1,1,1),1);gNormal=vec3( 1,0,0);gPosition=cubeCorner+vec3(1,1,1);EmitVertex();
  EndPrimitive();
}).";

std::string const fSrc = R".(
#version 450

uniform vec4 lightPosition = vec4(0,0,0,1);

in vec3 gNormal;
in vec3 gPosition;

layout(location=0)out vec4 fColor;

void main(){
  vec3 N=normalize(gNormal);
  vec3 L=normalize(lightPosition.xyz - gPosition.xyz*lightPosition.w);
  float d=max(0,dot(N,L));

  vec3 La=vec3(.1);

  vec3 Ld=vec3(1,1,1);
  vec3 Kd=mix(vec3(1,0,0),vec3(0,1,0),(50+gPosition)/100.);
  vec3 Ka=Kd;

  fColor=vec4(Ka*La+Kd*Ld*d,1);
}).";

int main(int,char*[]){
  glm::uvec2 windowSize = glm::uvec2(1024,768);
  auto mainLoop = make_shared<SDLMainLoop>();
  auto window = make_shared<SDLWindow>(windowSize.x,windowSize.y);

  window->createContext("rendering");
  mainLoop->addWindow("mainWindow", window);

  ge::gl::init(SDL_GL_GetProcAddress);
  setHighDebugMessage();

  auto vs = make_shared<Shader>(GL_VERTEX_SHADER, vSrc);
  auto gs = make_shared<Shader>(GL_GEOMETRY_SHADER,
      "#version 450\n",
      getNoiseSource(),
      gSrc);
  auto fs = make_shared<Shader>(GL_FRAGMENT_SHADER,fSrc);
  auto program = make_shared<Program>(vs,gs,fs);
  auto vao = make_shared<VertexArray>();

  OrbitCamera orbitCamera;
  PerspectiveCamera perspectiveCamera(float(windowSize.x)/float(windowSize.y));
  float sensitivity = 0.001f;
  float orbitZoomSpeed = 0.1f;
  Timer<float>timer;
  glEnable(GL_DEPTH_TEST);
 
  float timePerFrame = 0.f;
  std::map<SDL_Keycode,bool>keys;
  auto isKeyOn = [&](SDL_Keycode const&s){
    auto it = keys.find(s);
    if(it == keys.end()){
      keys[s] = false;
      return false;
    }
    return it->second;
  };
  mainLoop->setIdleCallback([&]() {

    for(size_t i = 0; i<3; ++i){
      auto movement = static_cast<float>(static_cast<int>(isKeyOn("a w"[i])) - static_cast<int>(isKeyOn("dcs"[i])));
      auto axis = glm::vec3(glm::row(orbitCamera.getRotation(),i));
      orbitCamera.setFocus(orbitCamera.getFocus()+axis*movement);
    }
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    uint32_t gridSize = 100;
    program->use();
    program->setMatrix4fv("viewMatrix"      ,glm::value_ptr(orbitCamera.getView())            );
    program->setMatrix4fv("projectionMatrix",glm::value_ptr(perspectiveCamera.getProjection()));
    program->set3fv      ("cameraPosition"  ,glm::value_ptr(orbitCamera.getFocus())           );
    //program->set1f       ("time"            ,timer.elapsedFromStart()                         );
    program->set1ui      ("gridSize"        ,gridSize                                         );
    timePerFrame = timer.elapsedFromLast();
    vao->bind();
    glDrawArrays(GL_POINTS, 0, gridSize*gridSize*gridSize);
    window->swap();
  });
  window->setEventCallback(SDL_MOUSEMOTION,[&](SDL_Event const&event){
    auto rel=glm::vec2(event.motion.yrel,event.motion.xrel);
    if(event.motion.state & SDL_BUTTON_LMASK)
      orbitCamera.addAngles(rel*sensitivity);
    if(event.motion.state & SDL_BUTTON_RMASK)
      orbitCamera.addDistance(rel.x*orbitZoomSpeed);
    if(event.motion.state & SDL_BUTTON_MMASK)
      orbitCamera.addXYPosition(rel/glm::vec2(windowSize)*2.f);
    return true;
  });

  window->setEventCallback(SDL_KEYDOWN,[&](SDL_Event const&e){
    keys[e.key.keysym.sym] = true;
    return true;
  });
  window->setEventCallback(SDL_KEYUP,[&](SDL_Event const&e){
    keys[e.key.keysym.sym] = false;
    return true;
  });


  window->setWindowEventCallback(SDL_WINDOWEVENT_RESIZED,[&](SDL_Event const&event){
    windowSize = glm::uvec2(event.window.data1,event.window.data2);
    glViewport(0,0,windowSize.x,windowSize.y);
    perspectiveCamera.setAspect(float(windowSize.x)/float(windowSize.y));
    return true;
  });

  (*mainLoop)();
  return 0;
}
