#include <string>
#include <chrono>
#include <glm/vec2.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <geGL/geGL.h>
#include <geRG/FlexibleUniform.h>
#include <geRG/Model.h>
#include <geRG/RenderingContext.h>
#include <geRG/Transformation.h>
#include <geAd/OsgImport/OsgImport.h>
#include <geAd/SDLOrbitManipulator/SDLOrbitManipulator.h>
#include <geAd/SDLWindow/SDLWindow.h>
#include <geUtil/ArgumentObject.h>
#include <osg/ref_ptr>
#if defined(_MSC_VER) && _MSC_VER<1900 // MSVC 2013 (seen on Update 5) does not put type_info into std
      // namespace. Actually, it puts, but only when exceptions are enabled (_HAS_EXCEPTIONS must be defined).
namespace std { typedef type_info type_info; }
#endif
#include <osgDB/ReadFile>
#include "OrbitCameraManipulator.h"

using namespace std;
using namespace ge::gl;
using namespace ge::rg;


static void init(unsigned windowWidth,unsigned windowHeight);
static void idleCallback();


static ge::util::ArgumentObject *args;
static ge::ad::SDLMainLoop mainLoop;
static shared_ptr<ge::ad::SDLWindow> window;
static bool printModelInfo=false;
static bool showFPS=false;
static vector<chrono::steady_clock::time_point> frameTimePoints;

static ge::ad::SDLOrbitManipulator cameraManipulator;
static shared_ptr<Transformation> cameraTransformation;
static string fileName;
static shared_ptr<Model> model;


int main(int argc,char*argv[])
{
   // arguments
   args=new ge::util::ArgumentObject(argc,argv);
   showFPS=args->isPresent("--show-fps");
   printModelInfo=args->isPresent("--model-info");

   // window
   window=std::make_shared<ge::ad::SDLWindow>(atoi(args->getArg("-w","800").c_str()),
                                              atoi(args->getArg("-h","600").c_str()));
   if(args->isPresent("-f"))
      window->setFullscreen(ge::ad::SDLWindow::FULLSCREEN);
   if(!window->createContext("rendering",430,ge::ad::SDLWindow::CORE)) {
      std::cout<<"Error: Can not create OpenGL context."<<std::endl;
      return EXIT_FAILURE;
   }
   mainLoop.addWindow("primaryWindow",window);
   mainLoop.setIdleCallback(idleCallback);

   // rendering context
   ge::gl::init(SDL_GL_GetProcAddress);
   RenderingContext::setCurrent(make_shared<RenderingContext>());

   // file name
   if(argc>1)
   {
      for(int i=1; i<argc; i++)
         if(argv[i][0]!='-') {
            fileName=argv[i];
            break;
         }
   }

   // create scene
   cameraTransformation=make_shared<Transformation>();
   RenderingContext::current()->addTransformationGraph(cameraTransformation);
   cameraManipulator.connect(window,SDL_BUTTON_RMASK);
   init(window->getWidth(),window->getHeight());

   // main loop
   mainLoop.operator()();

   // clean up
   delete args;
   return 0;
}


static void idleCallback()
{
   // initial frame time point
   if(showFPS && frameTimePoints.empty())
      frameTimePoints.push_back(chrono::steady_clock::now());

   // update camera
   cameraTransformation->uploadMatrix(cameraManipulator.mat());

   // render scene
   RenderingContext::current()->frame();
   window->swap();

   // print FPS each second
   if(showFPS) {
      auto t=chrono::steady_clock::now();
      double dt=chrono::duration<double>(t-frameTimePoints[0]).count();
      if(dt<1.)
         frameTimePoints.push_back(t);
      else
      {
         double avgFrameTime=dt/double(frameTimePoints.size());
         cout<<"Average frame time: "<<avgFrameTime*1000<<"ms  (FPS: "<<1./avgFrameTime<<")"<<endl;
         frameTimePoints.clear();
         frameTimePoints.push_back(t);
      }
   }
}


static const char* primitiveType2str(unsigned t)
{
   switch(t) {
      case 0: return "POINTS";
      case 1: return "LINES";
      case 2: return "LINE_LOOP";
      case 3: return "LINE_STRIP";
      case 4: return "TRIANGLES";
      case 5: return "TRIANGLE_STRIP";
      case 6: return "TRIANGLE_FAN";
      case 7: return "QUADS";
      case 8: return "QUAD_STRIP";
      case 9: return "POLYGON";
      case 10: return "LINES_ADJACENCY";
      case 11: return "LINE_STRIP_ADJACENCY";
      case 12: return "TRIANGLES_ADJACENCY";
      case 13: return "TRIANGLE_STRIP_ADJACENCY";
      case 14: return "PATCHES";
      default: return "unknown";
   }
}


static unsigned countTransformations(Transformation *t)
{
   unsigned r=1;
   for(auto& ch : t->childList())
      r+=countTransformations(ch.get());
   return r;
}


static void init(unsigned windowWidth,unsigned windowHeight)
{
   // setup OpenGL
   auto& gl=RenderingContext::current()->gl;
   gl.glEnable(GL_DEPTH_TEST);
   gl.glDepthFunc(GL_LEQUAL);
   gl.glEnable(GL_CULL_FACE);

   // load model
   glm::vec3 center;
   float radius=1.f;
   float zNear=1.f;
   float zFar=100.f;
   if(!fileName.empty())
   {
      osg::ref_ptr<osg::Node> root=osgDB::readNodeFile(fileName);
      if(root==nullptr)
         cout<<"Failed to load file "<<fileName<<endl;
      else
      {
         // convert model
         model=ge::osgImport::import(root);

         // get bounding sphere
         osg::BoundingSphere bs=root->getBound();
         center=glm::vec3(bs.center().x(),bs.center().z(),-bs.center().y());
         radius=bs.radius();
      }

      // release OSG memory
      root=nullptr;
      osgDB::Registry::instance()->closeAllLibraries();
      osgDB::Registry::instance(true);
   }

   if(model)
   {
      // add model bellow camera transformation
      cameraTransformation->addChild(model->transformationRoot());

      // setup orbit manipulator and clipping planes
      cameraManipulator.setCenter(center);
      cameraManipulator.setEye(center+glm::vec3(0.f,0.f,radius*2.f));
      zNear=radius*0.99f;
      zFar=radius*3.01f;
   }

   if(model && printModelInfo)
   {
      auto mgr=static_cast<StateSetDefaultManager*>(RenderingContext::current()->stateSetManager().get());
      auto& ssm=mgr->stateSetMap();
      array<unsigned,16> vertexCountsPerType;
      for(unsigned &a : vertexCountsPerType)
         a=0;
      cout<<"Num Meshes: "<<model->meshList().size()<<endl;
      cout<<"Num StateSets: "<<ssm.size()<<endl;
      unsigned numTransformations=0;
      auto& transformationRootList=model->transformationRootList();
      for(auto& t : transformationRootList)
         numTransformations+=countTransformations(t.second.get());
      cout<<"Num Transformations: "<<numTransformations<<endl;
      unsigned counter=0;
      for(auto it1=ssm.begin(); it1!=ssm.end(); it1++,counter++) {
         shared_ptr<StateSet> ss=it1->second.lock();
         auto& asdMap=ss->attribStorageDataMap();
         cout<<"StateSet "<<counter<<" (num used AttribStorages: "<<asdMap.size()<<")"<<endl;
         for(auto it2=asdMap.begin(); it2!=asdMap.end(); it2++) {
            auto& rd=it2->second.renderingData;
            for(auto it3=rd.begin(); it3!=rd.end(); it3++) {
               cout<<"   PrimitiveType: "<<primitiveType2str(it3->glMode)<<", Count: "<<it3->drawCommandCount<<endl;
               vertexCountsPerType[it3->glMode]+=it3->drawCommandCount;
            }
         }
      }
      for(unsigned i=0; i<vertexCountsPerType.size(); i++)
         if(vertexCountsPerType[i]!=0)
            cout<<"Total VertexCounts for "<<primitiveType2str(i)<<": "<<vertexCountsPerType[i]<<endl;
   }

   // unmap buffers
   // (it has to be done before rendering)
   RenderingContext::current()->unmapBuffers();

   const glm::vec4 ambientLight(0.2f,0.2f,0.2f,1.f);
   glm::mat4 projection=glm::perspective(float(60.*M_PI/180.),float(windowWidth)/float(windowHeight),zNear,zFar);
   auto ambientProgram=RenderingContext::current()->getAmbientProgram();
   ambientProgram->use();
   ambientProgram->setMatrix4fv("projection",glm::value_ptr(projection),1,GL_FALSE);
   ambientProgram->set("globalAmbientLight",ambientLight.r,ambientLight.g,ambientLight.b,ambientLight.a);
   ambientProgram->set("colorTexture",int(0));
   auto phongProgram=RenderingContext::current()->getPhongProgram();
   phongProgram->use();
   phongProgram->setMatrix4fv("projection",glm::value_ptr(projection),1,GL_FALSE);
   phongProgram->set("colorTexture",int(0));
   auto ambientUniformColorProgram=RenderingContext::current()->getAmbientUniformColorProgram();
   ambientUniformColorProgram->use();
   ambientUniformColorProgram->setMatrix4fv("projection",glm::value_ptr(projection),1,GL_FALSE);
   ambientUniformColorProgram->set("globalAmbientLight",ambientLight.r,ambientLight.g,ambientLight.b,ambientLight.a);
   ambientUniformColorProgram->set("colorTexture",int(0));
   auto phongUniformColorProgram=RenderingContext::current()->getPhongUniformColorProgram();
   phongUniformColorProgram->use();
   phongUniformColorProgram->setMatrix4fv("projection",glm::value_ptr(projection),1,GL_FALSE);
   phongUniformColorProgram->set("colorTexture",int(0));

   // append light
#if 0 // FIXME: addLight must be given transformation matrix of the light (here probably view matrix)
   auto lightCommands=make_shared<ge::core::SharedCommandList>();
   glm::vec4 pos(0.f,0.f,0.f,1.f); // in eye coordinates, w must be 0 or 1
   auto posUniform=make_shared<FlexibleUniform4f>("lightPosition",pos[0],pos[1],pos[2],pos[3]);
   lightCommands->emplace_back(posUniform);
   lightCommands->emplace_back(make_shared<FlexibleUniform3f>("lightColor",1.f,1.f,1.f));
   lightCommands->emplace_back(make_shared<FlexibleUniform3f>("lightAttenuation",1.f,0.f,0.f));
   //RenderingContext::current()->stateSetManager()->addLight(pos,posUniform,lightCommands,nullptr);
#endif

   // check for OpenGL errors
   int e=gl.glGetError();
   if(e!=GL_NO_ERROR)
      cout<<"OpenGL errror after Init(): "<<e<<endl;
}
