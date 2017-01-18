#include<limits>
#include<string>
#include<limits>
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
#include<geUtil/OrbitCamera.h>
#include<geUtil/FreeLookCamera.h>
#include<geUtil/ArgumentViewer.h>
#include"CameraPath.h"
#include<geUtil/PerspectiveCamera.h>
#include"Shading.h"
#include"ShadowMethod.h"
#include"CubeShadowMapping.h"
#include"CSSV.h"
#include"TimeStamp.h"
#include"Sintorn.h"
#include"SintornTiles.h"
#include"DrawPrimitive.h"
#include"CSV.h"
#include"RSSV.h"
#include"VSSV.h"

class RenderNode{
  public:
    virtual void operator()() = 0;
    virtual ~RenderNode(){}
};

class RenderFunction final: public RenderNode{
  public:
    RenderFunction(std::function<void()>const&fce):impl(fce){}
    std::function<void()>impl;
    virtual void operator()()override{
      assert(this);
      assert(this->impl);
      this->impl();
    }
    virtual ~RenderFunction()override{}
};

class RenderList final: public RenderNode{
  public:
    std::vector<std::shared_ptr<RenderNode>>childs;
    virtual void operator()()override{
      assert(this);
      for(auto const&x:this->childs){
        assert(x);
        (*x)();
      }
    }
    void add(std::function<void()>const&fce){
      assert(this);
      assert(fce);
      this->childs.emplace_back(std::make_shared<RenderFunction>(fce));
    }
    virtual ~RenderList()override{}
};

struct Application{
  std::shared_ptr<ge::gl::Context>    gl       = nullptr;
  std::shared_ptr<ge::ad::SDLMainLoop>mainLoop = nullptr;
  std::shared_ptr<ge::ad::SDLWindow>  window   = nullptr;
  std::shared_ptr<ge::gl::VertexArray>emptyVAO = nullptr;
  std::shared_ptr<GBuffer>gBuffer = nullptr;
  std::shared_ptr<Model>model = nullptr;
  std::shared_ptr<RenderModel>renderModel = nullptr;
  std::shared_ptr<ge::util::ArgumentObject>args = nullptr;
  std::shared_ptr<ge::util::CameraTransform>cameraTransform = nullptr;
  std::shared_ptr<ge::util::CameraProjection>cameraProjection = nullptr;
  std::shared_ptr<Shading>shading = nullptr;
  std::shared_ptr<ge::gl::Texture>shadowMask = nullptr;
  std::shared_ptr<ShadowMethod>shadowMethod = nullptr;
  std::shared_ptr<DrawPrimitive>drawPrimitive = nullptr;
  std::shared_ptr<RenderNode>drawSceneCmd;
  std::string cameraType = "orbit";
  glm::uvec2 windowSize = glm::uvec2(512u,512u);
  float cameraFovy = glm::radians(90.f);
  float cameraNear = 0.1f;
  float cameraFar = 1000.f;
  float sensitivity = 0.01f;
  float orbitZoomSpeed = 0.2f;
  float freeCameraSpeed = 1.f;
  glm::vec4 lightPosition = glm::vec4(100.f,100.f,100.f,1.f);
  size_t   wavefrontSize = 0;
  uint32_t shadowMapResolution = 1024;
  float    shadowMapNear = .1f;
  float    shadowMapFar  = 1000.f;
  uint32_t shadowMapFaces = 6;

  size_t   cssvWGS = 64;
  size_t   maxMultiplicity = 2;
  bool     zfail = true;
  bool     cssvLocalAtomic = true;
  bool     cssvCullSides = false;

  bool     vssvUsePlanes = false;
  bool     vssvUseStrips = true;
  bool     vssvUseAll    = false;

  size_t   sintornShadowFrustumsPerWorkGroup = 1;
  float    sintornBias = 0.01f;
  bool     sintornDiscardBackFacing = true;

  size_t   rssvComputeSilhouetteWGS = 64;
  bool     rssvLocalAtomic = true;
  bool     rssvCullSides = false;
  size_t   rssvSilhouettesPerWorkgroup = 1;

  std::string testName = "";
  std::string testFlyKeyFileName = "";
  size_t      testFlyLength = 0;
  size_t      testFramesPerMeasurement = 5;
  std::string testOutputName = "measurement";

  std::shared_ptr<TimeStamp>timeStamper = nullptr;
  std::string modelName = "";
  std::string methodName = "";
  bool verbose = false;
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
    std::cout<<"--model                        - model file name"<<std::endl;
    std::cout<<"--window-size-x                - window width"<<std::endl;
    std::cout<<"--window-size-y                - window height"<<std::endl;
    std::cout<<"--light-x                      - light position.x"<<std::endl;
    std::cout<<"--light-y                      - light position.y"<<std::endl;
    std::cout<<"--light-z                      - light position.z"<<std::endl;
    std::cout<<"--light-w                      - light position.w"<<std::endl;
    std::cout<<"--camera-fovy                  - camera fovy"<<std::endl;
    std::cout<<"--camera-near                  - camera near plane position"<<std::endl;
    std::cout<<"--camera-far                   - camera far plane position"<<std::endl;
    std::cout<<"--camera-sensitivity           - camera sensitivity"<<std::endl;
    std::cout<<"--camera-zoomSpeed             - orbit camera zoom speed"<<std::endl;
    std::cout<<"--camera-speed                 - free camera speed"<<std::endl;
    std::cout<<"--camera-type                  - orbit/free camera type"<<std::endl;
    std::cout<<"--no-shadows                   - turn off shadows"<<std::endl;
    std::cout<<"--shadowMap-resolution         - shadow map resolution"<<std::endl;
    std::cout<<"--shadowMap-near               - shadow map near plane position"<<std::endl;
    std::cout<<"--shadowMap-far                - shadow map far plane position"<<std::endl;
    std::cout<<"--shadowMap-faces              - cube shadow map faces"<<std::endl;
    std::cout<<"--cssv-WGS                     - compute sillhouette shadow volumes work group size"<<std::endl;
    std::cout<<"--maxMultiplicity              - max number of triangles that share the same edge"<<std::endl;
    std::cout<<"--zfail                        - shadow volumes zfail 0/1"<<std::endl;
    std::cout<<"--cssv-localAtomic             - use local atomic instructions"<<std::endl;
    std::cout<<"--cssv-cullSides               - enables culling of sides that are outside of viewfrustum"<<std::endl;
    std::cout<<"--vssv-usePlanes               - use planes instead of opposite vertices"<<std::endl;
    std::cout<<"--vssv-useStrips               - use triangle strips for sides of shadow volumes 0/1"<<std::endl;
    std::cout<<"--vssv-useAll                  - use all opposite vertices (even empty) 0/1"<<std::endl;
    std::cout<<"--sintorn-frustumsPerWorkgroup - nof triangles solved by work group"<<std::endl;
    std::cout<<"--sintorn-bias                 - offset of triangle planes"<<std::endl;
    std::cout<<"--sintorn-discardBackFacing    - discard light back facing fragments from hierarchical depth texture construction"<<std::endl;
    std::cout<<"--rssv-computeSilhouettesWGS   - workgroups size for silhouette computation"<<std::endl;
    std::cout<<"--rssv-localAtomic             - use local atomic instructions in silhouette computation"<<std::endl;
    std::cout<<"--rssv-cullSides               - enables frustum culling of silhouettes"<<std::endl;
    std::cout<<"--rssv-silhouettesPerWorkgroup - number of silhouette edges that are compute by one workgroup"<<std::endl;
    std::cout<<"--wavefrontSize                - warp/wavefrontSize usually 32 for NVidia and 64 for AMD"<<std::endl;
    std::cout<<"--method                       - name of shadow method: cubeShadowMapping/cssv/sintorn/rssv/vssv"<<std::endl;
    std::cout<<"--test                         - name of test - fly or empty"<<std::endl;
    std::cout<<"--test-fly-keys                - filename containing fly keyframes - csv x,y,z,vx,vy,vz,ux,uy,uz"<<std::endl;
    std::cout<<"--test-fly-length              - number of measurements, 1000"<<std::endl;
    std::cout<<"--test-framesPerMeasurement    - number of frames that is averaged per one measurement point"<<std::endl;
    std::cout<<"--test-output                  - name of output file"<<std::endl;
    std::cout<<"--verbose                      - toggle verbose mode"<<std::endl;
    exit(0);
  }

  auto arg = std::make_shared<ge::util::ArgumentViewer>(argc,argv);
  this->modelName = arg->gets("--model","/media/windata/ft/prace/models/o/o.3ds","model file name");
  this->windowSize.x = arg->getu32("--window-size-x",512,"window width" );
  this->windowSize.y = arg->getu32("--window-size-y",512,"window height");

  this->lightPosition.x     = arg->getf32("--light-x",100.f,"light position x");
  this->lightPosition.y     = arg->getf32("--light-y",100.f,"light position y");
  this->lightPosition.z     = arg->getf32("--light-z",100.f,"light position z");
  this->lightPosition.w     = arg->getf32("--light-w",1.f  ,"light position z");

  this->cameraFovy          = arg->getf32("--camera-fovy"       ,1.5707963267948966f                   ,"camera field of view in y direction");
  this->cameraNear          = arg->getf32("--camera-near"       ,0.1f                                  ,"camera near plane position"         );
  this->cameraFar           = arg->getf32("--camera-far"        ,std::numeric_limits<float>::infinity(),"camera far plane position"          );
  this->sensitivity         = arg->getf32("--camera-sensitivity",0.01f                                 ,"camera sensitivity"                 );
  this->orbitZoomSpeed      = arg->getf32("--camera-zoomSpeed"  ,0.2f                                  ,"orbit camera zoom speed"            );
  this->freeCameraSpeed     = arg->getf32("--camera-speed"      ,1.f                                   ,"free camera speed"                  );
  this->cameraType          = arg->gets  ("--camera-type"       ,"orbit"                               ,"orbit/free camera type"             );

  this->modelName           = this->args->getArg("--model","/media/windata/ft/prace/models/o/o.3ds");
  this->windowSize.x        = this->args->getArgi("--window-size-x","512");
  this->windowSize.y        = this->args->getArgi("--window-size-y","512");

  this->lightPosition.x     = this->args->getArgf("--light-x","100.f");
  this->lightPosition.y     = this->args->getArgf("--light-y","100.f");
  this->lightPosition.z     = this->args->getArgf("--light-z","100.f");
  this->lightPosition.w     = this->args->getArgf("--light-w","1.f");

  this->cameraFovy          = this->args->getArgf("--camera-fovy","1.5707963267948966f");
  this->cameraNear          = this->args->getArgf("--camera-near","0.1f");
  this->cameraFar           = this->args->getArgf("--camera-far","inf");
  this->sensitivity         = this->args->getArgf("--camera-sensitivity","0.01f");
  this->orbitZoomSpeed      = this->args->getArgf("--camera-zoomSpeed","0.2f");
  this->freeCameraSpeed     = this->args->getArgf("--camera-speed","1.f");
  this->cameraType          = this->args->getArg ("--camera-type","orbit");

  this->useShadows          = !this->args->isPresent("--no-shadows");
  this->verbose             = this->args->isPresent("--verbose");
  this->methodName          = this->args->getArg("--method","");

  this->wavefrontSize       = this->args->getArgi("-wavefrontSize","0");

  this->shadowMapResolution = this->args->getArgi("--shadowMap-resolution","1024");
  this->shadowMapNear       = this->args->getArgf("--shadowMap-near","0.1f");
  this->shadowMapFar        = this->args->getArgf("--shadowMap-far","1000.f");
  this->shadowMapFaces      = this->args->getArgi("--shadowMap-faces","6");

  this->cssvWGS             = this->args->getArgi("--cssv-WGS","64");
  this->maxMultiplicity     = this->args->getArgi("--maxMultiplicity","2");
  this->zfail               = this->args->getArgi("--zfail","1");
  this->cssvLocalAtomic     = this->args->getArgi("--cssv-localAtomic","1");
  this->cssvCullSides       = this->args->getArgi("--cssv-cullSides","0");

  this->vssvUsePlanes       = this->args->getArgi("--vssv-usePlanes","0");
  this->vssvUseStrips       = this->args->getArgi("--vssv-useStrips","1");
  this->vssvUseAll          = this->args->getArgi("--vssv-useAll"   ,"0");


  this->sintornShadowFrustumsPerWorkGroup = this->args->getArgi("--sintorn-frustumsPerWorkgroup","1"    );
  this->sintornBias                       = this->args->getArgf("--sintorn-bias"                ,"0.01f");
  this->sintornDiscardBackFacing          = this->args->getArgi("--sintorn-discardBackFacing"   ,"1"    );

  this->rssvComputeSilhouetteWGS    = this->args->getArgi("--rssw-computeSilhouettesWGS"  ,"64");
  this->rssvLocalAtomic             = this->args->getArgi("--rssw-localAtomic"            ,"1" );
  this->rssvCullSides               = this->args->getArgi("--rssw-cullSides"              ,"0" );
  this->rssvSilhouettesPerWorkgroup = this->args->getArgi("--rssw-silhouettesPerWorkgroup","1" );

  this->testName                 = this->args->getArg ("--test"                     ,""           );
  this->testFlyKeyFileName       = this->args->getArg ("--test-fly-keys"            ,""           );
  this->testFlyLength            = this->args->getArgi("--test-fly-length"          ,"1000"       );
  this->testFramesPerMeasurement = this->args->getArgi("--test-framesPerMeasurement","5"          );
  this->testOutputName           = this->args->getArg ("--test-output"              ,"measurement");

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
    this->cameraTransform = std::make_shared<ge::util::OrbitCamera>();
  else if(this->cameraType == "free")
    this->cameraTransform = std::make_shared<ge::util::FreeLookCamera>();
  else{
    std::cerr<<"ERROR: --camera-type is incorrect"<<std::endl;
    exit(0);
  }

  this->cameraProjection = std::make_shared<ge::util::PerspectiveCamera>(this->cameraFovy,(float)this->windowSize.x/(float)this->windowSize.y,this->cameraNear,this->cameraFar);

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
        this->maxMultiplicity,
        this->cssvWGS,
        this->zfail,
        this->cssvLocalAtomic,
        this->cssvCullSides,
        this->windowSize,
        this->gBuffer->depth,
        this->model,
        this->shadowMask);
  else if(this->methodName=="sintorn")
    this->shadowMethod = std::make_shared<Sintorn>(
        this->windowSize,
        this->gBuffer->depth,
        this->gBuffer->normal,
        this->model,
        64,
        this->sintornShadowFrustumsPerWorkGroup,
        this->sintornBias,
        this->sintornDiscardBackFacing,
        this->shadowMask);
  else if(this->methodName=="rssv")
    this->shadowMethod = std::make_shared<RSSV>(
        this->windowSize,
        this->shadowMask,
        this->gBuffer->depth,
        this->model,
        this->maxMultiplicity,
        this->rssvComputeSilhouetteWGS,
        this->rssvLocalAtomic,
        this->rssvCullSides,
        this->rssvSilhouettesPerWorkgroup);
  else if(this->methodName=="vssv")
    this->shadowMethod = std::make_shared<VSSV>(
        this->maxMultiplicity,
        this->zfail,
        this->windowSize,
        this->gBuffer->depth,
        this->model,
        this->shadowMask,
        this->vssvUsePlanes,
        this->vssvUseStrips,
        this->vssvUseAll);
  else
    this->useShadows = false;

  if(this->verbose)
    this->timeStamper = std::make_shared<TimeStamp>();
  else
    this->timeStamper = std::make_shared<TimeStamp>(nullptr);
  if(this->shadowMethod)
    this->shadowMethod->timeStamp = this->timeStamper;

  if(this->testName == "fly" || this->testName == "grid"){
    if(this->shadowMethod!=nullptr){
      this->shadowMethod->timeStamp = this->timeStamper;
    }
  }

  this->drawPrimitive = std::make_shared<DrawPrimitive>(this->windowSize);

  this->drawSceneCmd = std::make_shared<RenderList>();
  auto cmdList = std::dynamic_pointer_cast<RenderList>(this->drawSceneCmd);
  cmdList->add(std::bind(&ge::gl::Context::glViewport,this->gl,0,0,this->windowSize.x,this->windowSize.y));
  cmdList->add(std::bind(&ge::gl::Context::glEnable,this->gl,GL_DEPTH_TEST));
  cmdList->add(std::bind(&ge::gl::Context::glEnable,this->gl,GL_POLYGON_OFFSET_FILL));
  cmdList->add(std::bind(&ge::gl::Context::glPolygonOffset,this->gl,0,0));
  cmdList->add([this]{this->gBuffer->begin();});
  cmdList->add(std::bind(&ge::gl::Context::glClear,this->gl,GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT));
  cmdList->add([this]{this->shadowMask->clear(0,GL_RED,GL_FLOAT);});
  cmdList->add([this]{this->renderModel->draw(this->cameraProjection->getProjection()*this->cameraTransform->getView());});
  cmdList->add([this]{this->gBuffer->end();});
  cmdList->add(std::bind(&ge::gl::Context::glDisable,this->gl,GL_POLYGON_OFFSET_FILL));
  return true;
}

void Application::drawScene(){
  if(this->timeStamper)this->timeStamper->begin();
  (*this->drawSceneCmd)();
  /*
  this->gl->glViewport(0,0,this->windowSize.x,this->windowSize.y);
  this->gl->glEnable(GL_DEPTH_TEST);
  this->gl->glEnable(GL_POLYGON_OFFSET_FILL);
  this->gl->glPolygonOffset(0,100);
  this->gBuffer->begin();
  this->gl->glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
  this->shadowMask->clear(0,GL_RED,GL_FLOAT);
  this->renderModel->draw(this->cameraProjection->getProjection()*this->cameraTransform->getView());
  this->gBuffer->end();
  this->gl->glDisable(GL_POLYGON_OFFSET_FILL);
  // */
  if(this->timeStamper)this->timeStamper->stamp("gBuffer");


  if(this->shadowMethod)
    this->shadowMethod->create(this->lightPosition,this->cameraTransform->getView(),this->cameraProjection->getProjection());


  if(this->timeStamper)this->timeStamper->stamp("");
  this->gl->glDisable(GL_DEPTH_TEST);
  this->shading->draw(this->lightPosition,glm::vec3(glm::inverse(this->cameraTransform->getView())*glm::vec4(0,0,0,1)),this->useShadows);
  if(this->timeStamper)this->timeStamper->end("shading");
}

std::string vec3Tostr(glm::vec3 const&v){
  std::stringstream ss;
  ss<<v.x<<","<<v.y<<","<<v.z;
  return ss.str();
}

void Application::draw(){
  assert(this!=nullptr);
  if      (this->testName == "fly"){
    if(this->testFlyKeyFileName==""){
      ge::core::printError(GE_CORE_FCENAME,"camera path file is empty");
      this->mainLoop->removeWindow(this->window->getId());
      return;
    }
    auto cameraPath = std::make_shared<CameraPath>(false,this->testFlyKeyFileName);
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
      auto flc = std::dynamic_pointer_cast<ge::util::FreeLookCamera>(this->cameraTransform);
      flc->setPosition(keypoint.position);
      flc->setRotation(keypoint.viewVector,keypoint.upVector);
      for(size_t f=0;f<this->testFramesPerMeasurement;++f){
        this->drawScene();
      }

      std::vector<std::string>line;
      if(csv.size()==0){
        line.push_back("frame");
        for(auto const&x:measurement)
          if(x.first!="")line.push_back(x.first);
        csv.push_back(line);
        line.clear();
      }
      line.push_back(ge::core::value2str(k));
      for(auto const&x:measurement)
        if(x.first!=""){
          std::stringstream ss;
          ss<<x.second/float(this->testFramesPerMeasurement);
          line.push_back(ss.str());
        }
      csv.push_back(line);
      measurement.clear();
      this->window->swap();
    }
    std::string output = this->testOutputName+".csv";
    saveCSV(output,csv);
    this->mainLoop->removeWindow(this->window->getId());
    return;
  }

  if(this->cameraType == "free"){
    auto freeLook = std::dynamic_pointer_cast<ge::util::FreeLookCamera>(this->cameraTransform);
    for(int a=0;a<3;++a)freeLook->move(a,float(this->keyDown["d s"[a]]-this->keyDown["acw"[a]])*this->freeCameraSpeed);
  }

  this->drawScene();

  //this->drawPrimitive->drawTexture(this->gBuffer->normal);
  //*
  if(this->methodName == "sintorn"){
     auto sintorn = std::dynamic_pointer_cast<Sintorn>(this->shadowMethod);
     if(this->keyDown['h'])this->drawPrimitive->drawTexture(sintorn->_HDT[0]);
     if(this->keyDown['j'])this->drawPrimitive->drawTexture(sintorn->_HDT[1]);
     if(this->keyDown['k'])this->drawPrimitive->drawTexture(sintorn->_HDT[2]);
     if(this->keyDown['l'])this->drawPrimitive->drawTexture(sintorn->_HDT[3]);

     if(this->keyDown['v'])sintorn->drawHST(0);
     if(this->keyDown['b'])sintorn->drawHST(1);
     if(this->keyDown['n'])sintorn->drawHST(2);
     if(this->keyDown['m'])sintorn->drawHST(3);
     if(this->keyDown[','])sintorn->drawFinalStencilMask();
  }
  if(this->methodName == "rssv"){
     auto rssv = std::dynamic_pointer_cast<RSSV>(this->shadowMethod);
     if(this->keyDown['h'])this->drawPrimitive->drawTexture(rssv->_HDT[0]);
     if(this->keyDown['j'])this->drawPrimitive->drawTexture(rssv->_HDT[1]);
     if(this->keyDown['k'])this->drawPrimitive->drawTexture(rssv->_HDT[2]);
     if(this->keyDown['l'])this->drawPrimitive->drawTexture(rssv->_HDT[3]);
  }

  // */
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
  if(DOWN && event.key.keysym.sym=='p'){
    auto flc = std::dynamic_pointer_cast<ge::util::FreeLookCamera>(this->cameraTransform);
    if(flc){
      auto rv = flc->getRotation();
      auto pos = flc->getPosition();
      auto up = glm::normalize(glm::vec3(glm::row(rv,1)));
      auto view = glm::normalize(-glm::vec3(glm::row(rv,2)));
      std::cout<<pos.x<<","<<pos.y<<","<<pos.z<<",";
      std::cout<<view.x<<","<<view.y<<","<<view.z<<",";
      std::cout<<up.x<<","<<up.y<<","<<up.z<<std::endl;
    }
  }
  return true;
}

bool Application::mouseMove(SDL_Event const&event){
  if(this->cameraType == "orbit"){
    if(event.motion.state & SDL_BUTTON_LMASK){
      auto orbitCamera = std::dynamic_pointer_cast<ge::util::OrbitCamera>(this->cameraTransform);
      if(orbitCamera){
        orbitCamera->addXAngle(float(event.motion.yrel)*this->sensitivity);
        orbitCamera->addYAngle(float(event.motion.xrel)*this->sensitivity);
      }
    }
    if(event.motion.state & SDL_BUTTON_RMASK){
      auto orbitCamera = std::dynamic_pointer_cast<ge::util::OrbitCamera>(this->cameraTransform);
      if(orbitCamera){
        orbitCamera->addDistance(float(event.motion.yrel)*this->orbitZoomSpeed);
      }
    }
    if(event.motion.state & SDL_BUTTON_MMASK){
      auto orbitCamera = std::dynamic_pointer_cast<ge::util::OrbitCamera>(this->cameraTransform);
      orbitCamera->addXPosition(+orbitCamera->getDistance()*float(event.motion.xrel)/float(this->windowSize.x)*2.f);
      orbitCamera->addYPosition(-orbitCamera->getDistance()*float(event.motion.yrel)/float(this->windowSize.y)*2.f);
    }
  }
  if(this->cameraType == "free"){
    auto freeCamera = std::dynamic_pointer_cast<ge::util::FreeLookCamera>(this->cameraTransform);
    if(event.motion.state & SDL_BUTTON_LMASK){
      freeCamera->setAngle(1,freeCamera->getAngle(1)+float(event.motion.xrel)*this->sensitivity);
      freeCamera->setAngle(0,freeCamera->getAngle(0)+float(event.motion.yrel)*this->sensitivity);
    }
  }
  return true;
}
