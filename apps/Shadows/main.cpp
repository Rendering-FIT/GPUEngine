#include<limits>
#include<string>
#include<geGL/geGL.h>
#include<geAd/SDLWindow/SDLWindow.h>
#include<geGL/OpenGLCommands.h>
#include<geGL/OpenGLContext.h>

#include<geUtil/ArgumentObject.h>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtc/matrix_access.hpp>


#include"Deferred.h"
#include"Model.h"
#include"OrbitCamera.h"
#include"PerspectiveCamera.h"
#include"Shading.h"
#include"ShadowMethod.h"
#include"CubeShadowMapping.h"
#include"CSSV.h"
#include"TimeStamp.h"
#include"Sintorn.h"
#include"SintornTiles.h"

struct Application{
  std::shared_ptr<ge::gl::Context>    gl       = nullptr;
  std::shared_ptr<ge::ad::SDLMainLoop>mainLoop = nullptr;
  std::shared_ptr<ge::ad::SDLWindow>  window   = nullptr;
  std::shared_ptr<ge::gl::VertexArray>emptyVAO = nullptr;
  std::shared_ptr<GBuffer>gBuffer = nullptr;
  std::shared_ptr<Model>model = nullptr;
  std::shared_ptr<RenderModel>renderModel = nullptr;
  std::shared_ptr<ge::util::ArgumentObject>args = nullptr;
  std::shared_ptr<CameraTransform>cameraTransform = nullptr;
  std::shared_ptr<CameraProjection>cameraProjection = nullptr;
  std::shared_ptr<Shading>shading = nullptr;
  std::shared_ptr<ge::gl::Texture>shadowMask = nullptr;
  std::shared_ptr<ShadowMethod>shadowMethod = nullptr;
  glm::uvec2 windowSize = glm::uvec2(1024u,768u);
  float cameraFovy = glm::radians(90.f);
  float cameraNear = 0.1f;
  float cameraFar = 1000.f;
  float sensitivity = 0.01f;
  float orbitZoomSpeed = 0.2f;
  glm::vec4 lightPosition = glm::vec4(100.f,100.f,100.f,1.f);
  uint32_t shadowMapResolution = 1024;
  float    shadowMapNear = .1f;
  float    shadowMapFar  = 1000.f;
  uint32_t shadowMapFaces = 6;

  size_t   cssvWGS = 64;
  size_t   cssvMaxMultiplicity = 2;
  std::shared_ptr<TimeStamp>timeStamper = nullptr;
  std::string modelName = "";
  std::string methodName = "";
  bool useShadows = true;
  bool init(int argc,char*argv[]);
  void draw();
  bool mouseMove(SDL_Event const&event);
};

bool Application::init(int argc,char*argv[]){
  this->args = std::make_shared<ge::util::ArgumentObject>(argc-1,argv+1);
  if(this->args->isPresent("-h") || this->args->isPresent("--help")){
    std::cout<<"--model"<<" - "<<"model file name"<<std::endl;
    std::cout<<"--window-size-x"<<" - "<<"window width"<<std::endl;
    std::cout<<"--window-size-y"<<" - "<<"window height"<<std::endl;
    std::cout<<"--camera-fovy"<<" - "<<"camera fovy"<<std::endl;
    std::cout<<"--camera-near"<<" - "<<"camera near plane position"<<std::endl;
    std::cout<<"--camera-far"<<" - "<<"camera far plane position"<<std::endl;
    std::cout<<"--camera-sensitivity"<<" - "<<"camera sensitivity"<<std::endl;
    std::cout<<"--camera-zoomSpeed - orbit camera zoom speed"<<std::endl;
    std::cout<<"--no-shadows"<<" - "<<"turn off shadows"<<std::endl;
    std::cout<<"--shadowMap-resolution"<<" - "<<"shadow map resolution"<<std::endl;
    std::cout<<"--shadowMap-near"<<" - "<<"shadow map near plane position"<<std::endl;
    std::cout<<"--shadowMap-far"<<" - "<<"shadow map far plane position"<<std::endl;
    std::cout<<"--shadowMap-faces - cube shadow map faces"<<std::endl;
    std::cout<<"--cssv-WGS - compute sillhouette shadow volumes work group size"<<std::endl;
    std::cout<<"--cssv-maxMultiplicity - compute sillhouette shadow volumes max multiplicity"<<std::endl;
    std::cout<<"--method - name of shadow method: cubeShadowMapping cssv"<<std::endl;
    exit(0);
  }
  this->modelName           = this->args->getArg("--model","/media/windata/ft/prace/models/cube/cube.obj");
  this->modelName           = this->args->getArg("--model","/media/windata/ft/prace/models/o/o.3ds");
  //this->modelName           = this->args->getArg("--model","/media/windata/ft/prace/models/sponza/sponza.obj");
  this->windowSize.x        = this->args->getArgi("--window-size-x","1024");
  this->windowSize.y        = this->args->getArgi("--window-size-y","1024");
  this->cameraFovy          = this->args->getArgf("--camera-fovy","1.5707963267948966f");
  this->cameraNear          = this->args->getArgf("--camera-near","0.1f");
  this->cameraFar           = this->args->getArgf("--camera-far","inf");
  this->sensitivity         = this->args->getArgf("--camera-sensitivity","0.01f");
  this->orbitZoomSpeed      = this->args->getArgf("--camera-zoomSpeed","0.2f");
  this->useShadows          = !this->args->isPresent("--no-shadows");
  this->methodName          = this->args->getArg("--method","");
  this->shadowMapResolution = this->args->getArgi("--shadowMap-resolution","1024");
  this->shadowMapNear       = this->args->getArgf("--shadowMap-near","0.1f");
  this->shadowMapFar        = this->args->getArgf("--shadowMap-far","1000.f");
  this->shadowMapFaces      = this->args->getArgi("--shadowMap-faces","6");

  this->cssvWGS             = this->args->getArgi("--cssv-WGS","64");
  this->cssvMaxMultiplicity = this->args->getArgi("--cssv-maxMultiplicity","2");

  this->mainLoop = std::make_shared<ge::ad::SDLMainLoop>();
  this->mainLoop->setIdleCallback(std::bind(&Application::draw,this));
  this->window   = std::make_shared<ge::ad::SDLWindow>(this->windowSize.x,this->windowSize.y);
  this->window->setEventCallback(SDL_MOUSEMOTION,std::bind(&Application::mouseMove,this,std::placeholders::_1));
  this->window->createContext("rendering",450u,ge::ad::SDLWindow::CORE,ge::ad::SDLWindow::DEBUG);
  this->mainLoop->addWindow("primaryWindow",this->window);
  this->window->makeCurrent("rendering");
  ge::gl::init(SDL_GL_GetProcAddress);
  this->gl = ge::gl::getDefaultContext();
  ge::gl::setHighDebugMessage();

  this->gl->glEnable(GL_DEPTH_TEST);
  this->gl->glDepthFunc(GL_LEQUAL);
  this->gl->glDisable(GL_CULL_FACE);
  this->gl->glClearColor(0,0,0,1);

  this->cameraTransform = std::make_shared<OrbitCamera>();
  this->cameraProjection = std::make_shared<PerspectiveCamera>(this->cameraFovy,(float)this->windowSize.x/this->windowSize.y,this->cameraNear,this->cameraFar);

  this->gBuffer = std::make_shared<GBuffer>(this->windowSize.x,this->windowSize.y);

  this->model = std::make_shared<Model>(this->modelName);
  this->renderModel = std::make_shared<RenderModel>(this->model);

  this->shadowMask = std::make_shared<ge::gl::Texture>(GL_TEXTURE_2D,GL_R32F,1,this->windowSize.x,this->windowSize.y);
  this->shading = std::make_shared<Shading>(this->gBuffer->color,this->gBuffer->position,this->gBuffer->normal,this->shadowMask);

  this->emptyVAO = std::make_shared<ge::gl::VertexArray>();

  if     (this->methodName=="cubeShadowMapping")
    this->shadowMethod = std::make_shared<CubeShadowMapping>(this->windowSize,this->shadowMapResolution,this->shadowMapNear,this->shadowMapFar,this->shadowMapFaces,this->gBuffer->position,this->renderModel->nofVertices,this->renderModel->vertices,this->shadowMask);
  else if(this->methodName=="cssv")
    this->shadowMethod = std::make_shared<CSSV>(this->cssvMaxMultiplicity,this->cssvWGS,this->windowSize,this->gBuffer->depth,this->model,this->shadowMask);
  else
    this->useShadows = false;

  auto sintorn = std::make_shared<Sintorn>(this->windowSize,this->gBuffer->depth,this->model,64,1);

  this->timeStamper = std::make_shared<TimeStamp>();
  return true;
}

void Application::draw(){
  this->timeStamper->begin();
  this->gl->glEnable(GL_DEPTH_TEST);
  this->gBuffer->begin();
  this->gl->glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
  this->gl->glClearTexImage(this->shadowMask->getId(),0,GL_RED,GL_FLOAT,NULL);
  this->renderModel->draw(this->cameraProjection->getProjection()*this->cameraTransform->getView());
  this->gBuffer->end();
  auto orbitCamera = std::dynamic_pointer_cast<OrbitCamera>(this->cameraTransform);
  if(this->shadowMethod)
    this->shadowMethod->create(this->lightPosition,this->cameraTransform->getView(),this->cameraProjection->getProjection());
  this->gl->glDisable(GL_DEPTH_TEST);
  this->shading->draw(this->lightPosition,glm::vec3(glm::inverse(orbitCamera->getView())*glm::vec4(0,0,0,1)),this->useShadows);
  this->timeStamper->end("frame");
  this->window->swap();
}

int main(int argc,char*argv[]){
  Application app;
  if(!app.init(argc,argv))return EXIT_FAILURE;
  (*app.mainLoop)();
  return EXIT_SUCCESS;
}

bool Application::mouseMove(SDL_Event const&event){
  if(event.motion.state & SDL_BUTTON_LMASK){
    auto orbitCamera = std::dynamic_pointer_cast<OrbitCamera>(this->cameraTransform);
    if(orbitCamera){
      orbitCamera->setXAngle(orbitCamera->getXAngle() + event.motion.yrel*this->sensitivity);
      orbitCamera->setYAngle(orbitCamera->getYAngle() + event.motion.xrel*this->sensitivity);
    }
  }
  if(event.motion.state & SDL_BUTTON_RMASK){
    auto orbitCamera = std::dynamic_pointer_cast<OrbitCamera>(this->cameraTransform);
    if(orbitCamera){
      orbitCamera->setDistance(orbitCamera->getDistance() + event.motion.yrel*this->orbitZoomSpeed);
    }
  }
  if(event.motion.state & SDL_BUTTON_MMASK){
    auto orbitCamera = std::dynamic_pointer_cast<OrbitCamera>(this->cameraTransform);
    orbitCamera->addXPosition(+orbitCamera->getDistance()*event.motion.xrel/this->windowSize.x*2.f);
    orbitCamera->addYPosition(-orbitCamera->getDistance()*event.motion.yrel/this->windowSize.y*2.f);
  }

  return true;
}
