#include <string>
#include <GL/glew.h>
#include <glm/vec2.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <geGL/DebugMessage.h>
#include <geGL/geGL.h>
#include <geGL/ProgramObject.h>
#include <geRG/FlexibleUniform.h>
#include <geRG/Model.h>
#include <geRG/RenderingContext.h>
#include <geRG/Transformation.h>
#include <geAd/OsgImport/OsgImport.h>
#include <geAd/WindowObject/WindowObject.h>
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


void Init();
void Idle();
void Mouse();
void Wheel(int d);


struct SContextParam{
  unsigned    Version;
  std::string Profile;
  std::string Flag;
}ContextParam;


struct SWindowParam{
  unsigned Size[2];
  bool     Fullscreen;
}WindowParam;


bool disableAnttweakbar=true;
ge::util::ArgumentObject *args;
ge::util::WindowObject   *window;

static bool useARBShaderDrawParameters=false;
static fsg::OrbitObjectManipulator cameraManipulator;
static shared_ptr<Transformation> cameraTransformation;
static string fileName;
static shared_ptr<Model> model;

static bool mouseRightDown=false;
static glm::ivec2 lastMousePos;


int main(int argc,char*argv[])
{
   args=new ge::util::ArgumentObject(argc,argv);

   disableAnttweakbar=true;

   //window args
   WindowParam.Size[0]    = atoi(args->getArg("-w","800").c_str());
   WindowParam.Size[1]    = atoi(args->getArg("-h","600").c_str());
   WindowParam.Fullscreen = args->isPresent("-f");

   //context args
   ContextParam.Version = atoi(args->getArg("--context-version","430").c_str());
   ContextParam.Profile = args->getArg("--context-profile","core");
   ContextParam.Flag    = args->getArg("--context-flag","debug");

   // file name
   if(argc>1)
   {
      int i=argc-1;
      if(argv[i][0]!='-')
         if(argc==2 || argv[i-1][0]!='-')  fileName=argv[1];
   }

   window=new ge::util::WindowObject(
         WindowParam.Size[0],
         WindowParam.Size[1],
         WindowParam.Fullscreen,
         Idle,
         Mouse,
         !disableAnttweakbar,
         ContextParam.Version,
         ContextParam.Profile,
         ContextParam.Flag);

   glewExperimental=GL_TRUE;
   glewInit();
   glGetError(); // glewInit() might generate GL_INVALID_ENUM on some glew versions
                 // as said on https://www.opengl.org/wiki/OpenGL_Loading_Library,
                 // problem seen on CentOS 7.1 (release date 2015-03-31) with GLEW 1.9 (release date 2012-08-06)
   ge::gl::init();
   RenderingContext::setCurrent(make_shared<RenderingContext>());
   RenderingContext::current()->setUseARBShaderDrawParameters(useARBShaderDrawParameters);
   cameraTransformation=make_shared<Transformation>();
   RenderingContext::current()->addTransformationGraph(cameraTransformation);

   // OpenGL debugging messages
   //ge::gl::setDefaultDebugMessage();

   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LEQUAL);
   glDisable(GL_CULL_FACE);

   Init();
   window->mainLoop();
   delete window;
   delete args;
   return 0;
}


void Mouse()
{
   if(!mouseRightDown && window->isRightDown()!=0) {
      mouseRightDown=true;
      lastMousePos=glm::make_vec2(window->getMousePosition());
   }
   else if(mouseRightDown && window->isRightDown()) {
      glm::ivec2 currentMousePos=glm::make_vec2(window->getMousePosition());
      glm::vec2 size=glm::make_vec2(window->getWindowSize());
      glm::vec2 delta=glm::vec2(currentMousePos-lastMousePos)/size;
      lastMousePos=currentMousePos;
      cameraManipulator.rotate(delta.x,delta.y);
   }
   else if(mouseRightDown && !window->isRightDown()) {
      mouseRightDown=false;
      glm::vec2 size=glm::make_vec2(window->getWindowSize());
      glm::vec2 delta=glm::vec2(glm::make_vec2(window->getMousePosition())-lastMousePos)/size;
      cameraManipulator.rotate(delta.x,delta.y);
   }
}


void Wheel(int){
}


void Idle()
{
   cameraManipulator.updateViewMatrix();
   cameraTransformation->uploadMatrix(cameraManipulator.getMatrix());

   // render scene
   RenderingContext::current()->frame();

   window->swap();
}


void Init()
{
   ge::gl::initShadersAndPrograms();

   // load model
   glm::vec3 center;
   float radius;
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

   // unmap buffers
   // (it has to be done before rendering)
   RenderingContext::current()->unmapBuffers();

   const glm::vec4 ambientLight(0.2f,0.2f,0.2f,1.f);
   glm::mat4 projection=glm::perspective(float(60.*M_PI/180.),float(WindowParam.Size[0])/WindowParam.Size[1],zNear,zFar);
   auto ambientProgram=RenderingContext::current()->getAmbientProgram();
   ambientProgram->use();
   ambientProgram->set("globalAmbientLight",ambientLight.r,ambientLight.g,ambientLight.b,ambientLight.a);
   ambientProgram->set("projection",1,GL_FALSE,glm::value_ptr(projection));
   ambientProgram->set("colorTexture",int(0));
   auto phongProgram=RenderingContext::current()->getPhongProgram();
   phongProgram->use();
   phongProgram->set("projection",1,GL_FALSE,glm::value_ptr(projection));
   phongProgram->set("colorTexture",int(0));
   auto ambientUniformColorProgram=RenderingContext::current()->getAmbientUniformColorProgram();
   ambientUniformColorProgram->use();
   ambientUniformColorProgram->set("globalAmbientLight",ambientLight.r,ambientLight.g,ambientLight.b,ambientLight.a);
   ambientUniformColorProgram->set("projection",1,GL_FALSE,glm::value_ptr(projection));
   ambientUniformColorProgram->set("colorTexture",int(0));
   auto phongUniformColorProgram=RenderingContext::current()->getPhongUniformColorProgram();
   phongUniformColorProgram->use();
   phongUniformColorProgram->set("projection",1,GL_FALSE,glm::value_ptr(projection));
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
   int e=glGetError();
   if(e!=GL_NO_ERROR)
      cout<<"OpenGL errror after Init(): "<<e<<endl;
}
