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

std::string vSrc = R".(
#version 450
out vec2 vCoord;
void main() {
  vec2 coord = vec2(-1+2*(gl_VertexID%2),-1+2*(gl_VertexID/2));
  vCoord = coord;
  gl_Position = vec4(coord,1,1);
}).";

std::string fSrc = R".(
out vec4 fColor;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform float time = 0;
in vec2 vCoord;

BEGINGRADIENT(skyColors)
  vec4(0),
  vec4(.4,.4,1,1),
  vec4(.4,.4,1,1),
  vec4(.4,.4,1,1),
  vec4(.4,.4,1,1),
  vec4(.4,.4,1,1),
  vec4(.5,.3,0,1),
  vec4(.5,0,0,1),
  vec4(0),
ENDGRADIENT

BEGINGRADIENT(horizonColors)
  vec4(0,0,0,1),
  vec4(.5,.5,.5,1),
  vec4(1),
  vec4(1),
  vec4(1),
  vec4(1),
  vec4(1,1,.5,1),
  vec4(1,1,0,1),
  vec4(.5,0,0,1),
  vec4(0,0,0,1)
ENDGRADIENT

BEGINGRADIENT(sunColors)
  vec4(0,0,0,1),
  vec4(1),
  vec4(1),
  vec4(1),
  vec4(1),
  vec4(1,1,0,1),
  vec4(1,.7,0,1),
  vec4(0,0,0,1)
ENDGRADIENT

const float pi=3.141592653589793;

float viewSunDistance(vec3 view,vec3 sun){
  return clamp(dot(view,sun),0,1);
}

float horizont(vec3 view){
  return pow(abs(view.y),.2);
}

vec4 starColor(vec3 view,float day){
  return vec4(smoothstep(.55,.9,noise(uvec3(ivec3(view*10000)),6u,6u,2.f)*.5+.5));
}

const float earthRadius    = 6378000.f;
const float atmosphereSize = 10000.f;

vec3 endOfAtmosphere(vec3 view){
  vec3 pos=vec3(0,earthRadius,0);
  float a=dot(view,view);
  float b=2*dot(view,pos);
  float c=dot(pos,pos)-earthRadius*earthRadius-atmosphereSize*atmosphereSize;
  float d=b*b-4*a*c;
  float t0=(-b-sqrt(d))/(2*a);
  float t1=(-b+sqrt(d))/(2*a);
  return max(t0,t1)*view+vec3(0,earthRadius,0);
}

float sunRay2Earth(vec3 pos,vec3 sun){
  float t=-dot(pos,sun)/dot(sun,sun);
  float dist=0;
  if(t<0)dist=length(pos);
  else dist=length(pos+sun*t);
  return clamp((dist-earthRadius)/atmosphereSize,0,1);
}

vec4 skyColor(vec3 view,vec3 sun,float day){
  float skyGradient=horizont(view);
  float t=1-(sun.y*.5+.5);

  float toSun=(dot(view,sun)*.5+.5);
  float st=smoothstep(0.1,.3,pow(toSun,2));
  float ht=smoothstep(0.1,0.4,toSun);

  vec4 sky      = vec4(skyColors    (day).xyz,st);
  vec4 horizont = vec4(horizonColors(day).xyz,ht);
  return mix(horizont,sky,skyGradient);
}

vec4 sunColor(vec3 view,vec3 sun,float day){
  const float maxRange=0.998;
  const float minRange=0.999;
  const float power   =4;
  float gradient=pow(smoothstep(maxRange,minRange,viewSunDistance(view,sun)),power);
  return vec4(sunColors(day).xyz,gradient);
}

float cloudDensity(vec2 pos,vec3 view,float time){
  if(view.y<0)return 0.;
  time*=10000;
  const float height=100;
  uvec3 coord=uvec3(ivec2(pos+view.xz*height/view.y+time),uint(time));
  float gnoise=noise(coord,8u,8u,2.f);
  return pow(clamp(gnoise,0,1),.4)*smoothstep(0.0,.1,view.y);
}

vec4 cloudColor(vec3 view,vec3 sun,float time,float day){
  float toSun=(dot(view,sun)*.5+.5);
  float st=smoothstep(0.1,.3,pow(toSun,2));
  return vec4(sunColors(day).xyz*st,cloudDensity(vec2(0,0),view,time));
}

vec3 groundPosition(vec3 view){
  const float height=-100;
  return (view.xyz*height/view.y);
}

vec4 groudColor(vec3 view){
  uvec2 coord=uvec2(ivec2(groundPosition(view).xz));
  float gnoise=noise(coord,8u,8u,2.f)*smoothstep(0.0,.1,-view.y)*.5+.5;
  
  float ground=step(view.y,0);
  return vec4(mix(vec3(1),vec3(0,gnoise,0),horizont(view)),ground);
}

void mixColor(inout vec4 color,vec4 newColor){
  color=vec4(mix(color.xyz,newColor.xyz,newColor.w),1);
}



void main(){
  mat4 ipv = inverse(projectionMatrix*viewMatrix);
  vec3 viewVector = normalize((ipv*vec4(vCoord,1,1)).xyz);
  vec3 viewPosition = (ipv*vec4(0,0,0,1)).xyz;

  float time2 = time/20;
  float day=mod(time2,1);

  mat3 system;
  float angle=time2*2*pi;
  system[0]=vec3(1,0,0);
  system[1]=vec3(0,cos(angle),-sin(angle));
  system[2]=vec3(0,sin(angle),cos(angle));
  vec3 sun  = system*vec3(0,-1,0);//vec3(0,-cos(time2*2*pi),-sin(time2*2*pi));

  vec4 color=vec4(0);
  mixColor(color,starColor(viewVector*system,day));
  mixColor(color,skyColor(viewVector,sun,day));
  mixColor(color,sunColor(viewVector,sun,day));
  mixColor(color,groudColor(viewVector));
  mixColor(color,cloudColor(viewVector,sun,time2,day));

  vec3 normal=vec3(0.0);
  
  if(viewVector.y<0)normal=vec3(0,1,0);
  if(dot(normal,normal)!=0){
    float ambient=0.1;
    float diffuse=clamp(dot(sun,normal),0,1);
    float shadow=1-(cloudDensity(groundPosition(viewVector).xz,sun,time2))*smoothstep(0.0,0.1,-viewVector.y);
    vec4 finalColor;
    finalColor+=ambient*color*skyColors(day);
    finalColor+=shadow*diffuse*color*sunColors(day);
    fColor=finalColor;
  }else
    fColor=color;
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
  auto fs = make_shared<Shader>(GL_FRAGMENT_SHADER,
      "#version 450\n",
      getNoiseSource(),
      getGradientSource(),
      fSrc);
  auto program = make_shared<Program>(vs, fs);
  auto vao = make_shared<VertexArray>();

  OrbitCamera orbitCamera;
  PerspectiveCamera perspectiveCamera(float(windowSize.x)/float(windowSize.y));
  float sensitivity = 0.001f;
  float orbitZoomSpeed = 0.1f;
  Timer<float>timer;
 
  mainLoop->setIdleCallback([&]() {
    glClear(GL_COLOR_BUFFER_BIT);
    program->use();
    program->setMatrix4fv("viewMatrix",glm::value_ptr(orbitCamera.getView()));
    program->setMatrix4fv("projectionMatrix",glm::value_ptr(perspectiveCamera.getProjection()));
    program->set1f("time",timer.elapsedFromStart());
    vao->bind();
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    window->swap();
  });
  window->setEventCallback(SDL_MOUSEMOTION,[&](SDL_Event const&event){
    auto rel=glm::vec2(event.motion.yrel,event.motion.xrel);
    if(event.motion.state & SDL_BUTTON_LMASK)
      orbitCamera.addAngles(rel*sensitivity);
    if(event.motion.state & SDL_BUTTON_RMASK)
      orbitCamera.addDistance(rel.y*orbitZoomSpeed);
    if(event.motion.state & SDL_BUTTON_MMASK)
      orbitCamera.addXYPosition(rel/glm::vec2(windowSize)*2.f);
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
