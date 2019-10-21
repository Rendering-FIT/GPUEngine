#include<geDE/TypeRegister.h>
#include<limits>
#include<string>
#include<limits>
#include<geGL/geGL.h>

#include<geAd/SDLWindow/SDLWindow.h>
#undef main

#include<geGL/OpenGLCommands.h>
#include<geGL/OpenGLContext.h>
#include<geGL/StaticCalls.h>

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
#include"CSM/CubeShadowMapping.h"
#include"CSSV.h"
#include"TimeStamp.h"
#include"Sintorn.h"
#include"SintornTiles.h"
#include"DrawPrimitive.h"
#include"CSV.h"
#include"RSSV.h"
#include"VSSV.h"
#include"CSSVSOE.h"
#include "TSSV/TSSV.hpp"
#include "GSSV/GSSV.hpp"
#include "HSSV/HSSV.hpp"
#include "SM/ShadowMapping.h"
#include "FTS/FrustumTracedShadows.h"

struct Application{
  std::shared_ptr<ge::ad::SDLMainLoop       >mainLoop         = nullptr;
  std::shared_ptr<ge::ad::SDLWindow         >window           = nullptr;
  std::shared_ptr<ge::gl::VertexArray       >emptyVAO         = nullptr;
  std::shared_ptr<GBuffer                   >gBuffer          = nullptr;
  std::shared_ptr<Model                     >model            = nullptr;
  std::shared_ptr<RenderModel               >renderModel      = nullptr;
  std::shared_ptr<ge::util::CameraTransform >cameraTransform  = nullptr;
  std::shared_ptr<ge::util::CameraProjection>cameraProjection = nullptr;
  std::shared_ptr<Shading                   >shading          = nullptr;
  std::shared_ptr<ge::gl::Texture           >shadowMask       = nullptr;
  std::shared_ptr<ShadowMethod              >shadowMethod     = nullptr;
  std::shared_ptr<DrawPrimitive             >drawPrimitive    = nullptr;
  std::shared_ptr<TimeStamp                 >timeStamper      = nullptr;
  glm::uvec2  windowSize          = glm::uvec2(512u,512u);

  std::string cameraType          = "orbit"           ;
  float       cameraFovy          = glm::radians(90.f);
  float       cameraNear          = 0.1f              ;
  float       cameraFar           = 1000.f            ;
  float       sensitivity         = 0.01f             ;
  float       orbitZoomSpeed      = 0.2f              ;
  float       freeCameraSpeed     = 1.f               ;

  glm::vec4   lightPosition       = glm::vec4(100.f,100.f,100.f,1.f);

  size_t      wavefrontSize       = 0;

  size_t      maxMultiplicity     = 2    ;

  float       testWarmupSecs     = 2.0;

  float		  m_LightStepSize    = 1.0f;

  ShadowVolumesParams     svParams     ;
  CubeShadowMappingParams cubeSMParams ;
  CSSVParams              cssvParams   ;
  CSSVSOEParams           cssvsoeParams;
  VSSVParams              vssvParams   ;
  SintornParams           sintornParams;
  RSSVParams              rssvParams   ;
  TSSVParams              tssvParams   ;
  GSSVParams              gssvParams   ;
  HSSVParams			  hssvParams   ;
  ShadowMappingParams	  smParams;

  std::string testName                 = ""           ;
  std::string testFlyKeyFileName       = ""           ;
  size_t      testFlyLength            = 0            ;
  size_t      testFramesPerMeasurement = 5            ;
  std::string testOutputName           = "measurement";
  glm::uvec3  lightGrid				   = glm::uvec3(1);

  std::string modelName  = "";
  std::string methodName = "";
  bool verbose    = false;
  bool useShadows = true;

  bool init(int argc,char*argv[]);
  void parseArguments(int argc,char*argv[]);
  void initWavefrontSize();
  void initCamera();
  void draw();
  void measure();
  void measureLightGrid();
  void warmpUp();

  void drawScene();
  bool mouseMove(SDL_Event const&event);
  void printCamParams();
  std::map<SDL_Keycode,bool>keyDown;
  template<bool DOWN>bool keyboard(SDL_Event const&event);
};

glm::vec2  vector2vec2 (std::vector<float   >const&v){assert(v.size()>=2);return glm::vec2 (v[0],v[1]          );}
glm::vec3  vector2vec3 (std::vector<float   >const&v){assert(v.size()>=3);return glm::vec3 (v[0],v[1],v[2]     );}
glm::vec4  vector2vec4 (std::vector<float   >const&v){assert(v.size()>=4);return glm::vec4 (v[0],v[1],v[2],v[3]);}
glm::ivec2 vector2ivec2(std::vector<int32_t >const&v){assert(v.size()>=2);return glm::ivec2(v[0],v[1]          );}
glm::ivec3 vector2ivec3(std::vector<int32_t >const&v){assert(v.size()>=3);return glm::ivec3(v[0],v[1],v[2]     );}
glm::ivec4 vector2ivec4(std::vector<int32_t >const&v){assert(v.size()>=4);return glm::ivec4(v[0],v[1],v[2],v[3]);}
glm::uvec2 vector2uvec2(std::vector<uint32_t>const&v){assert(v.size()>=2);return glm::uvec2(v[0],v[1]          );}
glm::uvec3 vector2uvec3(std::vector<uint32_t>const&v){assert(v.size()>=3);return glm::uvec3(v[0],v[1],v[2]     );}
glm::uvec4 vector2uvec4(std::vector<uint32_t>const&v){assert(v.size()>=4);return glm::uvec4(v[0],v[1],v[2],v[3]);}
glm::vec2  vector2vec2 (std::vector<double  >const&v){assert(v.size()>=2);return glm::vec2 (v[0],v[1]          );}
glm::vec3  vector2vec3 (std::vector<double  >const&v){assert(v.size()>=3);return glm::vec3 (v[0],v[1],v[2]     );}
glm::vec4  vector2vec4 (std::vector<double  >const&v){assert(v.size()>=4);return glm::vec4 (v[0],v[1],v[2],v[3]);}

void Application::parseArguments(int argc,char*argv[]){
  assert(this!=nullptr);
  auto arg = std::make_shared<ge::util::ArgumentViewer>(argc,argv);
  modelName  = arg->gets("--model","/media/windata/ft/prace/models/o/o.3ds","model file name");

  windowSize = vector2uvec2(arg->getu32v("--window-size",{512,512},"window size" ));

  lightPosition       = vector2vec4(arg->getf32v("--light",{100.f,100.f,100.f,1.f},"light position"));

  cameraFovy          = arg->getf32("--camera-fovy"       ,1.5707963267948966f                   ,"camera field of view in y direction");
  cameraNear          = arg->getf32("--camera-near"       ,0.1f                                  ,"camera near plane position"         );
  cameraFar           = arg->getf32("--camera-far"        ,std::numeric_limits<float>::infinity(),"camera far plane position"          );
  sensitivity         = arg->getf32("--camera-sensitivity",0.01f                                 ,"camera sensitivity"                 );
  orbitZoomSpeed      = arg->getf32("--camera-zoomSpeed"  ,0.2f                                  ,"orbit camera zoom speed"            );
  freeCameraSpeed     = arg->getf32("--camera-speed"      ,1.f                                   ,"free camera speed"                  );
  cameraType          = arg->gets  ("--camera-type"       ,"orbit"                               ,"orbit/free camera type"             );

  useShadows          = !arg->isPresent("--no-shadows",   "turns off shadows"                                                      );
  verbose             =  arg->isPresent("--verbose"   ,   "toggle verbose mode"                                                    );
  methodName          =  arg->gets     ("--method"    ,"","name of shadow method: cubeShadowMapping/sm/fts/cssv/sintorn/rssv/vssv/cssvsoe/tssv/gssv/hssv");

  wavefrontSize       = arg->getu32("--wavefrontSize",0,"warp/wavefront size, usually 32 for NVidia and 64 for AMD");

  maxMultiplicity     = arg->getu32("--maxMultiplicity" ,2 ,"max number of triangles that share the same edge"        );
  svParams.zfail      = arg->getu32("--zfail"           ,1 ,"shadow volumes zfail 0/1"                                );
  svParams.rasterDiscard = arg->isPresent("--sv-raster-discard", "disable shadow volumes sides rasterization, for benchmarking");

  smParams.resolution.x = cubeSMParams.resolution = arg->getu32("--shadowMap-resolution",1024  ,"shadow map resolution"               );
  smParams.resolution.y = smParams.resolution.x;
  smParams.near       = cubeSMParams.near       = arg->getf32("--shadowMap-near"      ,0.1f  ,"shadow map near plane position"      );
  smParams.far        = cubeSMParams.far        = arg->getf32("--shadowMap-far"       ,1000.f,"shadow map far plane position"       );
  cubeSMParams.faces  = arg->getu32("--shadowMap-faces"     ,6     ,"number of used cube shadow map faces");
  smParams.resolution.z = arg->getu32("--fts-depth", 10, "Maximum number of triangles in Irregular Z-Buffer per cell");
  smParams.upDir      = vector2vec3(arg->getf32v("--shadowMap-up", { 0, 1, 0 }, "light up vector"));
  smParams.viewDir    = vector2vec3(arg->getf32v("--shadowMap-lightDir", { 0, -1, 0 }, "Light direction"));
  smParams.fovy       = arg->getf32("shadowMap-fovy", 1.5707963267948966f, "Shadow map field-of-view");
  smParams.pcfTaps    = arg->geti32("--shadowMap-pcf", 0, "NoF PCF taps");

  cssvParams.computeSidesWGS = arg->getu32("--cssv-WGS"            ,64,"compute silhouette shadow volumes work group size"      );
  cssvParams.localAtomic     = arg->getu32("--cssv-localAtomic"    ,1 ,"use local atomic instructions"                           );
  cssvParams.cullSides       = arg->getu32("--cssv-cullSides"      ,0 ,"enables culling of sides that are outside of viewfrustum");
  cssvParams.usePlanes       = arg->getu32("--cssv-usePlanes"      ,1 ,"use triangle planes instead of opposite vertices"        );
  cssvParams.useInterleaving = arg->getu32("--cssv-useInterleaving",1 ,"reorder edge that so it is struct of arrays"             );
  cssvParams.lobotomized     = arg->getu32("--cssv-lobotomized"    ,0 ,"lobotomize shader - it will not output edge data but edge indices");

  cssvsoeParams.computeSidesWGS = arg->getu32("--cssvsoe-WGS",64,"compute silhouette shadow volumes work group size");

  vssvParams.usePlanes              = arg->geti32("--vssv-usePlanes"   ,0,"use planes instead of opposite vertices"            );
  vssvParams.useStrips              = arg->geti32("--vssv-useStrips"   ,1,"use triangle strips for sides of shadow volumes 0/1");
  vssvParams.useAllOppositeVertices = arg->geti32("--vssv-useAll"      ,0,"use all opposite vertices (even empty) 0/1"         );
  vssvParams.drawCapsSeparately     = arg->geti32("--vssv-capsSeparate",0,"draw caps using two draw calls"                     );

  sintornParams.shadowFrustaPerWorkGroup = arg->geti32("--sintorn-frustumsPerWorkgroup",1    ,"nof triangles solved by work group"                                              );
  sintornParams.bias                     = arg->getf32("--sintorn-bias"                ,0.01f,"offset of triangle planes"                                                       );
  sintornParams.discardBackFacing        = arg->geti32("--sintorn-discardBackFacing"   ,1    ,"discard light back facing fragments from hierarchical depth texture construction");

  rssvParams.computeSilhouetteWGS    = arg->geti32("--rssv-computeSilhouettesWGS"  ,64,"workgroups size for silhouette computation"                  );
  rssvParams.localAtomic             = arg->geti32("--rssv-localAtomic"            ,1 ,"use local atomic instructions in silhouette computation"     );
  rssvParams.cullSides               = arg->geti32("--rssv-cullSides"              ,0 ,"enables frustum culling of silhouettes"                      );
  rssvParams.silhouettesPerWorkgroup = arg->geti32("--rssv-silhouettesPerWorkgroup",1 ,"number of silhouette edges that are compute by one workgroup");
  rssvParams.usePlanes               = arg->geti32("--rssv-usePlanes"              ,0 ,"use triangle planes instead of opposite vertices"            );

  tssvParams.UseReferenceEdge      = arg->isPresent("--tssv-useRefEdge", "Use Reference Edge");
  tssvParams.CullSides             = arg->isPresent("--tssv-cullSides", "Cull Sides");
  tssvParams.UseStencilValueExport = arg->isPresent("--tssv-useStencilExport" "Use stencil value export");

  gssvParams.UseReferenceEdge = arg->isPresent("--gssv-useRefEdge", "Use Reference Edge");
  gssvParams.CullSides = arg->isPresent("--gssv-cullSides", "Cull Sides");
  gssvParams.UseStencilValueExport = arg->isPresent("--gssv-useStencilExport" "Use stencil value export");

  hssvParams.maxOctreeLevel = arg->geti32("--hssv-maxOctreeLevel", 5, "Deepest octree level (octree granularity = 8^deepestLevel)");
  hssvParams.sceneAABBscale = vector2vec3(arg->getf32v("--hssv-sceneScale", { 1.f,1.f,1.f}, "Defines octree volume in terms of scene AABB scaling"));
  hssvParams.maxGpuMemoryToUsePerBuffer = arg->geti32("--hssv-maxBufSize", 2048, "Amount of GPU memory to use during octree build for potential edges buffer, default 2048MB. It's not total memory consumption, usually ~x2");
  hssvParams.potentialDrawingMethod = (unsigned char)(arg->getu32("--hssv-potentialMethod", 0, "Method for drawing sides from potentially silhouette edges. 0 = Geometry shader, 1 = Tessellation shader, 2 = Compute shader"));
  hssvParams.silhouetteDrawingMethod = (unsigned char)(arg->getu32("--hssv-silhouetteMethod", 0, "Method for drawing sides from always silhouette edges. 0 = Geometry shader, 1 = Tessellation shader, 2 = Compute shader"));
  hssvParams.workgroupSize = arg->getu32("--hssv-wg", 256, "Workgroup size for HSSV method, used in octree traversal CS and CS drawing methods.");
  hssvParams.forceOctreeBuild = arg->isPresent("--hssv-forceBuild", "Forces octree build (won't load from file if present)");
  glm::vec2 ratios = vector2vec2(arg->getf32v("--hssv-speculativeRatios", { 0.8f, 0.3f }, "Speculatively reduce memory during octree loading (factors for potential and silhouette ednges)"));
  hssvParams.potSpeculativeFactor = ratios.x;
  hssvParams.silSpeculativeFactor = ratios.y;
  hssvParams.drawOctree = arg->isPresent("--hssv-drawOctree", "Draws lowest-level octree cells as wireframe");
  hssvParams.initialLightPos = lightPosition;
  hssvParams.doBuildTest = arg->isPresent("--hssv-buildTest", "Performs build benchmark on input scene and light position");
  hssvParams.doEdgeTest = arg->isPresent("--hssv-silTest", "Performs edge statistics test in model");
  hssvParams.noCompression = arg->isPresent("--hssv-noCompress", "Performs build benchmark on input scene and light position");
  hssvParams.drawFromCpu = arg->isPresent("--hssv-drawCpu", "Uses CPU traversal instead of GPU traversal");

  testName                 = arg->gets  ("--test"                     ,""           ,"name of test - fly or grid"                                    );
  testFlyKeyFileName       = arg->gets  ("--test-fly-keys"            ,""           ,"filename containing fly keyframes - csv x,y,z,vx,vy,vz,ux,uy,uz");
  testFlyLength            = arg->geti32("--test-fly-length"          ,1000         ,"number of measurements, 1000"                                   );
  testFramesPerMeasurement = arg->geti32("--test-framesPerMeasurement",5            ,"number of frames that is averaged per one measurement point"    );
  testOutputName           = arg->gets  ("--test-output"              ,"measurement","name of output file"                                            );
  lightGrid = vector2uvec3(arg->getu32v("--test-gridSize", {1, 1, 1 }, "Nof of division of light grid per axis"));
  testWarmupSecs = arg->getf32("--test-warmupSecs", 2.0, "NoF seconds to warm up the card before the actual measurement");

  bool printHelp = arg->isPresent("-h","prints this help");

  printHelp = printHelp || !arg->validate();
  if(printHelp){
    std::cerr<<arg->toStr();
    exit(0);
  }
}

void Application::initWavefrontSize(){
  assert(this!=nullptr);
  if(wavefrontSize==0){
    std::string renderer = std::string((char*)ge::gl::glGetString(GL_RENDERER));
	std::transform(renderer.begin(), renderer.end(), renderer.begin(), ::tolower);
    if     (renderer.find("amd")!=std::string::npos || renderer.find("ati") != std::string::npos || renderer.find("radeon") != std::string::npos || renderer.find("firegl") != std::string::npos || renderer.find("firepro") != std::string::npos)
      wavefrontSize = 64;
    else if(renderer.find("nvidia")!=std::string::npos || renderer.find("geforce") != std::string::npos || renderer.find("titan") != std::string::npos || renderer.find("quadro") != std::string::npos)
      wavefrontSize = 32;
    else{
      std::cerr<<"WARNING: renderer is not NVIDIA or AMD, setting wavefrontSize to 32"<<std::endl;
      wavefrontSize = 32;
    }
  }
}

void Application::initCamera(){
  assert(this!=nullptr);
  if     (cameraType == "orbit")
    cameraTransform = std::make_shared<ge::util::OrbitCamera>();
  else if(cameraType == "free")
    cameraTransform = std::make_shared<ge::util::FreeLookCamera>();
  else{
    std::cerr<<"ERROR: --camera-type is incorrect"<<std::endl;
    exit(0);
  }
  cameraProjection = std::make_shared<ge::util::PerspectiveCamera>(cameraFovy,(float)windowSize.x/(float)windowSize.y,cameraNear,cameraFar);
}

bool Application::init(int argc,char*argv[]){
  parseArguments(argc,argv);

  mainLoop = std::make_shared<ge::ad::SDLMainLoop>();
  mainLoop->setIdleCallback(std::bind(&Application::draw,this));
  window   = std::make_shared<ge::ad::SDLWindow>(windowSize.x,windowSize.y);
  window->setEventCallback(SDL_MOUSEMOTION,std::bind(&Application::mouseMove      ,this,std::placeholders::_1));
  window->setEventCallback(SDL_KEYDOWN    ,std::bind(&Application::keyboard<true> ,this,std::placeholders::_1));
  window->setEventCallback(SDL_KEYUP      ,std::bind(&Application::keyboard<false>,this,std::placeholders::_1));
  window->createContext("rendering",450u,ge::ad::SDLWindow::CORE,ge::ad::SDLWindow::DEBUG);
  mainLoop->addWindow("primaryWindow",window);
  window->makeCurrent("rendering");
  SDL_GL_SetSwapInterval(0); //disable vsync

  ge::gl::init(SDL_GL_GetProcAddress);
  ge::gl::setHighDebugMessage();

  ge::gl::glEnable(GL_DEPTH_TEST);
  ge::gl::glDepthFunc(GL_LEQUAL);
  ge::gl::glDisable(GL_CULL_FACE);

  initWavefrontSize();

  printf("Renderer: %s %s\n", ge::gl::glGetString(GL_VENDOR), ge::gl::glGetString(GL_RENDERER));

  if(testName == "fly" || testName == "grid")
    cameraType = "free";

  initCamera();

  gBuffer = std::make_shared<GBuffer>(windowSize.x,windowSize.y);
  gBuffer->setClearColor(glm::uvec4(153, 153, 255, 255));

  model = std::make_shared<Model>(modelName);
  renderModel = std::make_shared<RenderModel>(model);

  shadowMask = std::make_shared<ge::gl::Texture>(GL_TEXTURE_2D,GL_R32F,1,windowSize.x,windowSize.y);
  shading = std::make_shared<Shading>(gBuffer->color,gBuffer->position,gBuffer->normal,shadowMask);

  emptyVAO = std::make_shared<ge::gl::VertexArray>();

  if (useShadows)
  {
	  if (methodName == "cubeShadowMapping")
		  shadowMethod = std::make_shared<CubeShadowMapping>(
			  shadowMask,
			  windowSize,
			  gBuffer->position,
			  renderModel->nofVertices,
			  renderModel->vertices,
			  cubeSMParams);
	  else if (methodName == "sm")
		  shadowMethod = std::make_shared<ShadowMapping>(
			  shadowMask,
			  windowSize,
			  gBuffer->position,
			  renderModel->nofVertices,
			  renderModel->vertices,
			  smParams);
      else if (methodName == "fts")
          shadowMethod = std::make_shared<FrustumTracedShadows>(
              smParams,
              shadowMask,
              windowSize,
              gBuffer->position,
              renderModel->nofVertices,
              renderModel->vertices);
	  else if (methodName == "cssv")
		  shadowMethod = std::make_shared<CSSV>(
			  shadowMask,
			  model,
			  gBuffer->depth,
			  svParams,
			  maxMultiplicity,
			  cssvParams);
	  else if (methodName == "cssvsoe")
		  shadowMethod = std::make_shared<CSSVSOE>(
			  shadowMask,
			  model,
			  gBuffer->depth,
			  svParams,
			  maxMultiplicity,
			  cssvsoeParams);
	  else if (methodName == "sintorn")
		  shadowMethod = std::make_shared<Sintorn>(
			  shadowMask,
			  windowSize,
			  gBuffer->depth,
			  gBuffer->normal,
			  model,
			  wavefrontSize,
			  sintornParams);
	  else if (methodName == "rssv")
		  shadowMethod = std::make_shared<RSSV>(
			  shadowMask,
			  windowSize,
			  gBuffer->depth,
			  model,
			  maxMultiplicity,
			  rssvParams);
	  else if (methodName == "vssv")
		  shadowMethod = std::make_shared<VSSV>(
			  shadowMask,
			  model,
			  gBuffer->depth,
			  svParams,
			  maxMultiplicity,
			  vssvParams);
	  else if (methodName == "tssv")
		  shadowMethod = std::make_shared<TSSV>(
			  model,
			  tssvParams.UseReferenceEdge,
			  tssvParams.CullSides,
			  tssvParams.UseStencilValueExport,
			  maxMultiplicity,
			  shadowMask,
			  gBuffer->depth,
			  svParams);
	  else if (methodName == "gssv")
		  shadowMethod = std::make_shared<GSSV>(
			  model,
			  gssvParams.UseReferenceEdge,
			  gssvParams.CullSides,
			  gssvParams.UseStencilValueExport,
			  maxMultiplicity,
			  shadowMask,
			  gBuffer->depth,
			  svParams);
	  else if (methodName == "hssv")
		  shadowMethod = std::make_shared<HSSV>(
			  model,
			  hssvParams,
			  shadowMask,
			  gBuffer->depth,
			  svParams);
      else
      {
          std::cerr << "Failed to init the shadow method!\n";
          useShadows = false;
      }
  }

  if (useShadows && !shadowMethod->init())
  {
    std::cerr << "Failed to init the shadow method!\n";
  	return false;
  }

  if(verbose)
    timeStamper = std::make_shared<TimeStamp>();
  else
    timeStamper = std::make_shared<TimeStamp>(nullptr);
  if (shadowMethod)
	  shadowMethod->setTimeStamper(timeStamper);

  if(testName == "fly" || testName == "grid"){
    if(shadowMethod!=nullptr){
      shadowMethod->setTimeStamper(timeStamper);
    }
  }

  drawPrimitive = std::make_shared<DrawPrimitive>(windowSize);

  return true;
}

//#define USE_STATIC_CAM

#ifdef USE_STATIC_CAM
void Application::drawScene() {
	
	const float camData[] = { 602.281,88.1596,96.8042,-0.276641,-0.514136,0.811871,-0.165827,0.857709,0.486659 };

	auto flc = std::dynamic_pointer_cast<ge::util::FreeLookCamera>(cameraTransform);
	if (!flc)return;
	flc->setPosition(glm::vec3(camData[0], camData[1], camData[2]));
	flc->setRotation(glm::vec3(camData[3], camData[4], camData[5]), glm::vec3(camData[6], camData[7], camData[8]));

	if (timeStamper)timeStamper->begin();

	ge::gl::glViewport(0, 0, windowSize.x, windowSize.y);
	ge::gl::glEnable(GL_DEPTH_TEST);
	gBuffer->begin();
	shadowMask->clear(0, GL_RED, GL_FLOAT);
	
	renderModel->draw(cameraProjection->getProjection()* flc->getView());
	gBuffer->end();

	if (timeStamper)timeStamper->stamp("gBuffer");

	if (useShadows)
		shadowMethod->create(lightPosition,flc->getView(), cameraProjection->getProjection());

	if (timeStamper)timeStamper->stamp("");
	ge::gl::glDisable(GL_DEPTH_TEST);
	shading->draw(lightPosition, glm::vec3(glm::inverse(flc->getView())*glm::vec4(0, 0, 0, 1)), useShadows);
	if (timeStamper)timeStamper->end("shading");

	//Blit depth into default FBO
	ge::gl::glBlitNamedFramebuffer(gBuffer->fbo->getId(), 0, 0, 0, windowSize.x, windowSize.y, 0, 0, windowSize.x, windowSize.y, GL_DEPTH_BUFFER_BIT, GL_NEAREST);

    if (useShadows)
    {
        shadowMethod->drawUser(lightPosition, flc->getView(), cameraProjection->getProjection());
    }
}

#else
void Application::drawScene() {
	if (timeStamper)timeStamper->begin();

	ge::gl::glViewport(0, 0, windowSize.x, windowSize.y);
	ge::gl::glEnable(GL_DEPTH_TEST);
	gBuffer->begin();

	shadowMask->clear(0, GL_RED, GL_FLOAT);

	renderModel->draw(cameraProjection->getProjection()*cameraTransform->getView());
	gBuffer->end();

	if (timeStamper)timeStamper->stamp("gBuffer");

	if (useShadows)
		shadowMethod->create(lightPosition,cameraTransform->getView(), cameraProjection->getProjection());

	if (timeStamper)timeStamper->stamp("");
	ge::gl::glDisable(GL_DEPTH_TEST);
	shading->draw(lightPosition, glm::vec3(glm::inverse(cameraTransform->getView())*glm::vec4(0, 0, 0, 1)), useShadows);
	if (timeStamper)timeStamper->end("shading");

	//Blit depth into default FBO
	ge::gl::glBlitNamedFramebuffer(gBuffer->fbo->getId(), 0, 0, 0, windowSize.x, windowSize.y, 0, 0, windowSize.x, windowSize.y, GL_DEPTH_BUFFER_BIT, GL_NEAREST);

	if(shadowMethod) 
		shadowMethod->drawUser(lightPosition, cameraTransform->getView(), cameraProjection->getProjection());
}
#endif
#include "HSSV/HighResolutionTimer.hpp"

void Application::warmpUp()
{
	std::cout << "Warming up...\n";
	SDL_Event event;
	HighResolutionTimer t;
	t.reset();
	float elapsedTimeS = 0;
	while (elapsedTimeS<testWarmupSecs)
	{
		while (SDL_PollEvent(&event));
		t.reset();
		drawScene();
		ge::gl::glFinish();
		elapsedTimeS += float(t.getElapsedTimeSeconds());
		window->swap();
	}
	std::cout << "Go!\n";
}

void Application::measure(){
  assert(this!=nullptr);
  if(testFlyKeyFileName==""){
    ge::core::printError(GE_CORE_FCENAME,"camera path file is empty");
    mainLoop->removeWindow(window->getId());
    return;
  }
  auto cameraPath = std::make_shared<CameraPath>(false,testFlyKeyFileName);
  std::map<std::string,float>measurement;
  timeStamper->setPrinter([&](std::vector<std::string>const&names,std::vector<float>const&values){
      for(size_t i=0;i<names.size();++i)
      if(names[i]!=""){
      if(measurement.count(names[i])==0)measurement[names[i]]=0.f;
      measurement[names[i]]+=values[i];
      }});

  warmpUp();

  std::vector<std::vector<std::string>>csv;
  for(size_t k=0;k<testFlyLength;++k){
    auto keypoint = cameraPath->getKeypoint(float(k)/float(testFlyLength));
    auto flc = std::dynamic_pointer_cast<ge::util::FreeLookCamera>(cameraTransform);
    flc->setPosition(keypoint.position);
    flc->setRotation(keypoint.viewVector,keypoint.upVector);
	SDL_Event event;
	for (size_t f = 0; f < testFramesPerMeasurement; ++f)
	{
		while(SDL_PollEvent(&event));
		drawScene();
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
      if(x.first!="")
        line.push_back(ge::core::value2str(x.second/float(testFramesPerMeasurement)));
    csv.push_back(line);
    measurement.clear();
    window->swap();
  }
  std::string output = testOutputName+".csv";
  saveCSV(output,csv);
  mainLoop->removeWindow(window->getId());
}

void Application::measureLightGrid()
{
	assert(this != nullptr);
	
	std::map<std::string, float>measurement;
	timeStamper->setPrinter([&](std::vector<std::string>const&names, std::vector<float>const&values)
	{
		for (size_t i = 0; i<names.size(); ++i)
			if (names[i] != "") {
				if (measurement.count(names[i]) == 0)measurement[names[i]] = 0.f;
				measurement[names[i]] += values[i];
				}});

	std::vector<std::vector<std::string>>csv;

	std::vector<float> verts;
	model->getVertices(verts);

	AABB bbox;
	bbox.updateWithVerticesVec3(verts.data(), verts.size());
	
	glm::vec3 extents = bbox.getExtents() * hssvParams.sceneAABBscale;

	bbox.setCenterExtents(bbox.getCenterPoint(), extents);
	extents = bbox.getExtents();
	auto const minPoint = bbox.getMinPoint();
	auto const unitSize = extents / glm::vec3(lightGrid.x, lightGrid.y, lightGrid.z);
	auto const offset = unitSize / 2.0f;

	size_t k = 0;

	lightPosition = glm::vec4(0, 0, 0, 1);
	warmpUp();

	for (size_t z = 0; z<lightGrid.z; ++z)
		for (size_t y = 0; y<lightGrid.y; ++y)
			for (size_t x = 0; x<lightGrid.x; ++x)
	{
		lightPosition = glm::vec4(minPoint + offset + unitSize * glm::vec3(x, y, z), 1);

		SDL_Event event;
		for (size_t f = 0; f < testFramesPerMeasurement; ++f)
		{
			while (SDL_PollEvent(&event));
			drawScene();
		}

		std::vector<std::string>line;

		if (csv.size() == 0) 
		{
			line.push_back("frame");
			for (auto const&x : measurement)
				if (x.first != "")line.push_back(x.first);
			csv.push_back(line);
			line.clear();
		}

		line.push_back(ge::core::value2str(k));

		for (auto const&x : measurement)
			if (x.first != "")
				line.push_back(ge::core::value2str(x.second / float(testFramesPerMeasurement)));

		csv.push_back(line);
		measurement.clear();
		window->swap();
		
		++k;
	}
	std::string output = testOutputName + ".csv";
	saveCSV(output, csv);
	mainLoop->removeWindow(window->getId());
}

void Application::draw(){
  assert(this!=nullptr);

  if(testName == "fly"){
    measure();
    return;
  }

  if (testName == "grid") {
	  measureLightGrid();
	  return;
  }

  if(cameraType == "free"){
    auto freeLook = std::dynamic_pointer_cast<ge::util::FreeLookCamera>(cameraTransform);
    for(int a=0;a<3;++a)freeLook->move(a,float(keyDown["d s"[a]]-keyDown["acw"[a]])*freeCameraSpeed);
  }

  drawScene();

  //drawPrimitive->drawTexture(gBuffer->normal);
  //*
  if(methodName == "sintorn"){
    auto sintorn = std::dynamic_pointer_cast<Sintorn>(shadowMethod);
    if(keyDown['h'])drawPrimitive->drawTexture(sintorn->_HDT[0]);
    if(keyDown['j'])drawPrimitive->drawTexture(sintorn->_HDT[1]);
    if(keyDown['k'])drawPrimitive->drawTexture(sintorn->_HDT[2]);
    if(keyDown['l'])drawPrimitive->drawTexture(sintorn->_HDT[3]);

    if(keyDown['v'])sintorn->drawHST(0);
    if(keyDown['b'])sintorn->drawHST(1);
    if(keyDown['n'])sintorn->drawHST(2);
    if(keyDown['m'])sintorn->drawHST(3);
    if(keyDown[','])sintorn->drawFinalStencilMask();
  }
  if(methodName == "rssv"){
    auto rssv = std::dynamic_pointer_cast<RSSV>(shadowMethod);
    if(keyDown['h'])drawPrimitive->drawTexture(rssv->_HDT[0]);
    if(keyDown['j'])drawPrimitive->drawTexture(rssv->_HDT[1]);
    if(keyDown['k'])drawPrimitive->drawTexture(rssv->_HDT[2]);
    if(keyDown['l'])drawPrimitive->drawTexture(rssv->_HDT[3]);
  }

  // */
  window->swap();
}

int main(int argc,char*argv[]){
  Application app;
  if(!app.init(argc,argv))return EXIT_FAILURE;
  (*app.mainLoop)();
  return EXIT_SUCCESS;
}


template<bool DOWN>bool Application::keyboard(SDL_Event const&event)
{
  keyDown[event.key.keysym.sym] = DOWN;
  
  if(DOWN && event.key.keysym.sym=='p')
  {
    auto flc = std::dynamic_pointer_cast<ge::util::FreeLookCamera>(cameraTransform);
    if(!flc)return true;
    auto rv = flc->getRotation();
    auto pos = flc->getPosition();
    auto up = glm::normalize(glm::vec3(glm::row(rv,1)));
    auto view = glm::normalize(-glm::vec3(glm::row(rv,2)));
    std::cout<< pos .x<<","<<pos .y<<","<<pos .z<<",";
    std::cout<< view.x<<","<<view.y<<","<<view.z<<",";
    std::cout<< up  .x<<","<<up  .y<<","<<up  .z<<std::endl;
  }

  const float lightMovementSpeed = m_LightStepSize;

  if (DOWN && event.key.keysym.sym == 'j')
  {
	  lightPosition.x += lightMovementSpeed;
	  std::cout << lightPosition.x << "," << lightPosition.y << "," << lightPosition.z << std::endl;
  }

  if (DOWN && event.key.keysym.sym == 'k')
  {
	  lightPosition.y += lightMovementSpeed;
	  std::cout << lightPosition.x << "," << lightPosition.y << "," << lightPosition.z << std::endl;
  }

  if (DOWN && event.key.keysym.sym == 'l')
  {
	  lightPosition.z += lightMovementSpeed;
	  std::cout << lightPosition.x << "," << lightPosition.y << "," << lightPosition.z << std::endl;
  }


  if (DOWN && event.key.keysym.sym == 'n')
  {
	  lightPosition.x -= lightMovementSpeed;
	  std::cout << lightPosition.x << "," << lightPosition.y << "," << lightPosition.z << std::endl;
  }

  if (DOWN && event.key.keysym.sym == 'm')
  {
	  lightPosition.y -= lightMovementSpeed;
	  std::cout << lightPosition.x << "," << lightPosition.y << "," << lightPosition.z << std::endl;
  }

  if (DOWN && event.key.keysym.sym == ',')
  {
	  lightPosition.z -= lightMovementSpeed;
	  std::cout << lightPosition.x << "," << lightPosition.y << "," << lightPosition.z << std::endl;
  }

  if (DOWN && event.key.keysym.sym == 'v')
  {
	  lightPosition = glm::vec4(0, 0, 0, 1);
	  std::cout << lightPosition.x << "," << lightPosition.y << "," << lightPosition.z << std::endl;
  }

  if (DOWN && event.key.keysym.sym == SDLK_KP_MINUS)
  {
	  m_LightStepSize /= 2.0;
	  std::cout << "Light move step " << m_LightStepSize << std::endl;
  }

  if (DOWN && event.key.keysym.sym == SDLK_KP_PLUS)
  {
	  m_LightStepSize *= 2.0;
	  std::cout << "Light move step " << m_LightStepSize << std::endl;
  }

  if (DOWN && event.key.keysym.sym == SDLK_o)
  {
	  auto freeLookCam = std::dynamic_pointer_cast<ge::util::FreeLookCamera>(cameraTransform);
	  if (!freeLookCam)
	  {
		  return true;
	  }

	  auto pos = freeLookCam->getPosition();
	  auto rv = freeLookCam->getRotation();
	  auto view = glm::normalize(-glm::vec3(glm::row(rv, 2)));
	  auto up = glm::normalize(glm::vec3(glm::row(rv, 1)));

	  lightPosition = glm::vec4(pos, 1);

	  std::cout << "Light pos: " << lightPosition.x << "," << lightPosition.y << "," << lightPosition.z << std::endl;
	  std::cout << "Light dir: " << view.x << "," << view.y << "," << view.z << std::endl;
      std::cout << "Light up: " << up.x << "," << up.y << "," << up.z << std::endl;


	  auto sm = std::dynamic_pointer_cast<IShadowMapping>(shadowMethod);
	  if (sm)
	  {
		  sm->setLightViewProps(view, up);
	  }
  }

  if (DOWN && event.key.keysym.sym == SDLK_ESCAPE)
  {
      mainLoop->removeWindow(window->getId());
  }

  return true;
}

bool Application::mouseMove(SDL_Event const&event){
  if(cameraType == "orbit"){
    if(event.motion.state & SDL_BUTTON_LMASK){
      auto orbitCamera = std::dynamic_pointer_cast<ge::util::OrbitCamera>(cameraTransform);
      if(orbitCamera){
        orbitCamera->addXAngle(float(event.motion.yrel)*sensitivity);
        orbitCamera->addYAngle(float(event.motion.xrel)*sensitivity);
      }
    }
    if(event.motion.state & SDL_BUTTON_RMASK){
      auto orbitCamera = std::dynamic_pointer_cast<ge::util::OrbitCamera>(cameraTransform);
      if(orbitCamera)
        orbitCamera->addDistance(float(event.motion.yrel)*orbitZoomSpeed);
    }
    if(event.motion.state & SDL_BUTTON_MMASK){
      auto orbitCamera = std::dynamic_pointer_cast<ge::util::OrbitCamera>(cameraTransform);
      orbitCamera->addXPosition(+orbitCamera->getDistance()*float(event.motion.xrel)/float(windowSize.x)*2.f);
      orbitCamera->addYPosition(-orbitCamera->getDistance()*float(event.motion.yrel)/float(windowSize.y)*2.f);
    }
  }
  if(cameraType == "free"){
    auto freeCamera = std::dynamic_pointer_cast<ge::util::FreeLookCamera>(cameraTransform);
    if(event.motion.state & SDL_BUTTON_LMASK){
      freeCamera->setAngle(1,freeCamera->getAngle(1)+float(event.motion.xrel)*sensitivity);
      freeCamera->setAngle(0,freeCamera->getAngle(0)+float(event.motion.yrel)*sensitivity);
    }
  }
  return true;
}


