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
#include"FreeLookCamera.h"
#include"CameraPath.h"
#include"PerspectiveCamera.h"
#include"Shading.h"
#include"ShadowMethod.h"
#include"CubeShadowMapping.h"
#include"CSSV.h"
#include"TimeStamp.h"
#include"Sintorn.h"
#include"SintornTiles.h"
#include"DrawPrimitive.h"
#include"CSV.h"

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
  std::shared_ptr<DrawPrimitive>drawPrimitive = nullptr;
  std::string cameraType = "orbit";
  std::string outputName = "measurement";
  glm::uvec2 windowSize = glm::uvec2(1024u,768u);
  float cameraFovy = glm::radians(90.f);
  float cameraNear = 0.1f;
  float cameraFar = 1000.f;
  float sensitivity = 0.01f;
  float orbitZoomSpeed = 0.2f;
  float freeCameraSpeed = 1.f;
  std::string cameraPathFile = "";
  glm::vec4 lightPosition = glm::vec4(100.f,100.f,100.f,1.f);
  size_t   wavefrontSize = 0;
  uint32_t shadowMapResolution = 1024;
  float    shadowMapNear = .1f;
  float    shadowMapFar  = 1000.f;
  uint32_t shadowMapFaces = 6;

  size_t   cssvWGS = 64;
  size_t   cssvMaxMultiplicity = 2;

  size_t   sintornShadowFrustumsPerWorkGroup = 1;
  float    sintornBias = 0.01f;

  std::string testName = "";
  std::string testFlyKeyFileName = "";
  size_t      testFlyLength = 0;

  size_t      testGridSize = 10;
  size_t      testGridAngleY = 10;
  size_t      testGridAngleX = 10;
  size_t      testFramesPerMeasurement = 5;

  std::shared_ptr<TimeStamp>timeStamper = nullptr;
  std::string modelName = "";
  std::string methodName = "";
  bool useShadows = true;
  bool init(int argc,char*argv[]);
  void draw();
  void drawScene();
  bool mouseMove(SDL_Event const&event);
  std::map<SDL_Keycode,bool>keyDown;
  template<bool DOWN>bool keyboard(SDL_Event const&event);
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
    std::cout<<"--camera-speed - free camera speed"<<std::endl;
    std::cout<<"--camera-type - orbit/free camera type"<<std::endl;
    std::cout<<"--camera-path - file name of camera path"<<std::endl;
    std::cout<<"--no-shadows"<<" - "<<"turn off shadows"<<std::endl;
    std::cout<<"--shadowMap-resolution"<<" - "<<"shadow map resolution"<<std::endl;
    std::cout<<"--shadowMap-near"<<" - "<<"shadow map near plane position"<<std::endl;
    std::cout<<"--shadowMap-far"<<" - "<<"shadow map far plane position"<<std::endl;
    std::cout<<"--shadowMap-faces - cube shadow map faces"<<std::endl;
    std::cout<<"--cssv-WGS - compute sillhouette shadow volumes work group size"<<std::endl;
    std::cout<<"--cssv-maxMultiplicity - compute sillhouette shadow volumes max multiplicity"<<std::endl;
    std::cout<<"--sintorn-frustumsPerWorkgroup - nof triangles solved by work group"<<std::endl;
    std::cout<<"--sintorn-bias - offset of triangle planes"<<std::endl;
    std::cout<<"--wavefrontSize - warp/wavefrontSize usually 32 for NVidia and 64 for AMD"<<std::endl;
    std::cout<<"--method - name of shadow method: cubeShadowMapping cssv"<<std::endl;
    std::cout<<"--test - name of test - fly,grid or empty"<<std::endl;
    std::cout<<"--test-fly-keys - filename containing fly keyframes - csv x,y,z,vx,vy,vz,ux,uy,uz"<<std::endl;
    std::cout<<"--test-fly-length - number of measurements, 1000"<<std::endl;
    std::cout<<"--test-grid-size - size of grid test cube - size^3 is number of measurement camera points"<<std::endl;
    std::cout<<"--test-grid-angles-y - number of camera direction angles arount Y axis"<<std::endl;
    std::cout<<"--test-grid-angles-x - number of camera direction angles around X axis"<<std::endl;
    std::cout<<"--test-framesPerMeasurement - number of frames that is averaged per one measurement point"<<std::endl;
    std::cout<<"--test-output - name of output file"<<std::endl;
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
  this->freeCameraSpeed     = this->args->getArgf("--camera-speed","1.f");
  this->cameraType          = this->args->getArg ("--camera-type","orbit");
  this->cameraPathFile      = this->args->getArg ("--camera-path","");

  this->useShadows          = !this->args->isPresent("--no-shadows");
  this->methodName          = this->args->getArg("--method","");

  this->wavefrontSize       = this->args->getArgi("-wavefrontSize","0");

  this->shadowMapResolution = this->args->getArgi("--shadowMap-resolution","1024");
  this->shadowMapNear       = this->args->getArgf("--shadowMap-near","0.1f");
  this->shadowMapFar        = this->args->getArgf("--shadowMap-far","1000.f");
  this->shadowMapFaces      = this->args->getArgi("--shadowMap-faces","6");

  this->cssvWGS             = this->args->getArgi("--cssv-WGS","64");
  this->cssvMaxMultiplicity = this->args->getArgi("--cssv-maxMultiplicity","2");

  this->sintornShadowFrustumsPerWorkGroup = this->args->getArgi("--sintorn-frustumsPerWorkgroup","1"    );
  this->sintornBias                       = this->args->getArgf("--sintorn-bias"                ,"0.01f");

  this->testName           = this->args->getArg ("--test"              ,""    );
  this->testFlyKeyFileName = this->args->getArg ("--test-fly-keys"     ,""    );
  this->testFlyLength      = this->args->getArgi("--test-fly-length"   ,"1000");
  this->testGridSize       = this->args->getArgi("--test-grid-size"    ,"10"  );
  this->testGridAngleX     = this->args->getArgi("--test-grid-angles-x","10"  );
  this->testGridAngleY     = this->args->getArgi("--test-grid-angles-y","10"  );
  this->testFramesPerMeasurement = this->args->getArgi("--test-framesPerMeasurement","5");
  this->outputName         = this->args->getArg ("--test-output","measurement");

  this->mainLoop = std::make_shared<ge::ad::SDLMainLoop>();
  this->mainLoop->setIdleCallback(std::bind(&Application::draw,this));
  this->window   = std::make_shared<ge::ad::SDLWindow>(this->windowSize.x,this->windowSize.y);
  this->window->setEventCallback(SDL_MOUSEMOTION,std::bind(&Application::mouseMove      ,this,std::placeholders::_1));
  this->window->setEventCallback(SDL_KEYDOWN    ,std::bind(&Application::keyboard<true> ,this,std::placeholders::_1));
  this->window->setEventCallback(SDL_KEYUP      ,std::bind(&Application::keyboard<false>,this,std::placeholders::_1));
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

  if(this->wavefrontSize==0){
    std::string renderer = std::string((char*)this->gl->glGetString(GL_RENDERER));
    if     (renderer.find("AMD")!=std::string::npos)
      this->wavefrontSize = 64;
    else if(renderer.find("NVIDIA")!=std::string::npos)
      this->wavefrontSize = 32;
    else{
      std::cerr<<"WARNING: renderer is not NVIDIA or AMD, setting wavefrontSize to 32"<<std::endl;
      this->wavefrontSize = 32;
    }
  }

  if(this->testName == "fly" || this->testName == "grid")
    this->cameraType = "free";

  if     (this->cameraType == "orbit")
    this->cameraTransform = std::make_shared<OrbitCamera>();
  else if(this->cameraType == "free")
    this->cameraTransform = std::make_shared<FreeLookCamera>();
  else{
    std::cerr<<"ERROR: --camera-type is incorrect"<<std::endl;
    exit(0);
  }

  this->cameraProjection = std::make_shared<PerspectiveCamera>(this->cameraFovy,(float)this->windowSize.x/this->windowSize.y,this->cameraNear,this->cameraFar);

  this->gBuffer = std::make_shared<GBuffer>(this->windowSize.x,this->windowSize.y);

  this->model = std::make_shared<Model>(this->modelName);
  this->renderModel = std::make_shared<RenderModel>(this->model);

  this->shadowMask = std::make_shared<ge::gl::Texture>(GL_TEXTURE_2D,GL_R32F,1,this->windowSize.x,this->windowSize.y);
  this->shading = std::make_shared<Shading>(this->gBuffer->color,this->gBuffer->position,this->gBuffer->normal,this->shadowMask);

  this->emptyVAO = std::make_shared<ge::gl::VertexArray>();

  if     (this->methodName=="cubeShadowMapping")
    this->shadowMethod = std::make_shared<CubeShadowMapping>(
        this->windowSize,
        this->shadowMapResolution,
        this->shadowMapNear,
        this->shadowMapFar,
        this->shadowMapFaces,
        this->gBuffer->position,
        this->renderModel->nofVertices,
        this->renderModel->vertices,
        this->shadowMask);
  else if(this->methodName=="cssv")
    this->shadowMethod = std::make_shared<CSSV>(
        this->cssvMaxMultiplicity,
        this->cssvWGS,
        this->windowSize,
        this->gBuffer->depth,
        this->model,
        this->shadowMask);
  else if(this->methodName=="sintorn")
    this->shadowMethod = std::make_shared<Sintorn>(
        this->windowSize,
        this->gBuffer->depth,
        this->model,
        64,
        this->sintornShadowFrustumsPerWorkGroup,
        this->sintornBias);
  else
    this->useShadows = false;

  this->timeStamper = std::make_shared<TimeStamp>(nullptr);

  if(this->testName == "fly" || this->testName == "grid"){
    if(this->shadowMethod!=nullptr){
      this->shadowMethod->timeStamp = this->timeStamper;
    }
  }


  this->drawPrimitive = std::make_shared<DrawPrimitive>(this->windowSize);
  return true;
}

void Application::drawScene(){
  if(this->timeStamper)this->timeStamper->begin();
  this->gl->glEnable(GL_DEPTH_TEST);
  this->gBuffer->begin();
  this->gl->glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
  this->gl->glClearTexImage(this->shadowMask->getId(),0,GL_RED,GL_FLOAT,NULL);
  this->renderModel->draw(this->cameraProjection->getProjection()*this->cameraTransform->getView());
  this->gBuffer->end();

  if(this->timeStamper)this->timeStamper->stamp("gBuffer");
  if(this->shadowMethod)
    this->shadowMethod->create(this->lightPosition,this->cameraTransform->getView(),this->cameraProjection->getProjection());
  if(this->timeStamper)this->timeStamper->stamp("");
  this->gl->glDisable(GL_DEPTH_TEST);
  this->shading->draw(this->lightPosition,glm::vec3(glm::inverse(this->cameraTransform->getView())*glm::vec4(0,0,0,1)),this->useShadows);
  if(this->timeStamper)this->timeStamper->end("shading");
}

void Application::draw(){
  assert(this!=nullptr);
  if      (this->testName == "fly"){
    //TODO fly part
    if(this->cameraPathFile==""){
      ge::core::printError(GE_CORE_FCENAME,"camera path file is empty");
      this->mainLoop->removeWindow(this->window->getId());
      return;
    }
    auto cameraPath = std::make_shared<CameraPath>(false,this->cameraPathFile);
    std::map<std::string,float>measurement;
    this->timeStamper->setPrinter([&](std::vector<std::string>const&names,std::vector<float>const&values){
        for(size_t i=0;i<names.size();++i)
          if(names[i]!=""){
            if(measurement.count(names[i])==0)measurement[names[i]]=0.f;
            measurement[names[i]]+=values[i];
          }});


    std::vector<std::vector<std::string>>csv;
    for(size_t k=0;k<this->testFlyLength;++k){
      auto keypoint = cameraPath->getKeypoint(float(k)/float(this->testFlyLength));
      auto flc = std::dynamic_pointer_cast<FreeLookCamera>(this->cameraTransform);
      flc->setPosition(keypoint.position);
      flc->setRotation(keypoint.viewVector,keypoint.upVector);
      for(size_t f=0;f<this->testFramesPerMeasurement;++f)
        this->drawScene();

      std::vector<std::string>line;
      if(csv.size()==0){
        for(auto const&x:measurement)
          if(x.first!="")line.push_back(x.first);
      }else{
        for(auto const&x:measurement)
          if(x.first!=""){
            std::stringstream ss;
            ss<<x.second/float(this->testFramesPerMeasurement);
            line.push_back(ss.str());
          }
      }
      csv.push_back(line);
    }
    std::string output = this->outputName+"_fly_"+this->modelName+".csv";
    saveCSV(output,csv);
    this->mainLoop->removeWindow(this->window->getId());
    return;
  }else if(this->testName == "grid"){
    //TODO grid part
    for(size_t zz=0;zz<this->testGridSize;++zz){
      for(size_t yy=0;yy<this->testGridSize;++yy){
        for(size_t xx=0;xx<this->testGridSize;++xx){
          for(size_t ya=0;ya<this->testGridAngleY;++ya){
            for(size_t xa=0;xa<this->testGridAngleX;++xa){
              float yangle = glm::radians((float)ya/(float)this->testGridAngleY*360);
              float xangle = glm::radians((float)xa/(float)this->testGridAngleX*180);
              (void)yangle;
              (void)xangle;
              for(size_t f=0;f<this->testFramesPerMeasurement;++f){
                this->drawScene();
              }
            }
          }
        }
      }
    }
    this->mainLoop->removeWindow(this->window->getId());
    return;
  }

  if(this->cameraType == "free"){
    auto freeLook = std::dynamic_pointer_cast<FreeLookCamera>(this->cameraTransform);
    for(int a=0;a<3;++a)freeLook->move(a,(this->keyDown["d s"[a]]-this->keyDown["acw"[a]]));
  }

  this->drawScene();

  //this->drawPrimitive->drawTexture(this->gBuffer->normal);
  /*
  auto sintorn = std::dynamic_pointer_cast<Sintorn>(this->shadowMethod);
  if(this->keyDown['a'])this->drawPrimitive->drawTexture(sintorn->_HDT[0]);
  if(this->keyDown['s'])this->drawPrimitive->drawTexture(sintorn->_HDT[1]);
  if(this->keyDown['d'])this->drawPrimitive->drawTexture(sintorn->_HDT[2]);
  if(this->keyDown['f'])this->drawPrimitive->drawTexture(sintorn->_HDT[3]);

  if(this->keyDown['y'])sintorn->drawHST(0);
  if(this->keyDown['x'])sintorn->drawHST(1);
  if(this->keyDown['c'])sintorn->drawHST(2);
  if(this->keyDown['v'])sintorn->drawHST(3);
  if(this->keyDown['b'])sintorn->drawFinalStencilMask();
  */
  this->window->swap();
}

int main(int argc,char*argv[]){
  Application app;
  if(!app.init(argc,argv))return EXIT_FAILURE;
  (*app.mainLoop)();
  return EXIT_SUCCESS;
}


template<bool DOWN>bool Application::keyboard(SDL_Event const&event){
  this->keyDown[event.key.keysym.sym] = DOWN;
  return true;
}

bool Application::mouseMove(SDL_Event const&event){
  if(this->cameraType == "orbit"){
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
  }
  if(this->cameraType == "free"){
    auto freeCamera = std::dynamic_pointer_cast<FreeLookCamera>(this->cameraTransform);
    if(event.motion.state & SDL_BUTTON_LMASK){
      freeCamera->setAngle(1,freeCamera->getAngle(1)+event.motion.xrel*this->sensitivity);
      freeCamera->setAngle(0,freeCamera->getAngle(0)+event.motion.yrel*this->sensitivity);
    }
  }

  return true;
}
