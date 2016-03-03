#include <string>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <geGL/DebugMessage.h>
#include <geGL/geGL.h>
#include <geGL/ProgramObject.h>
#include <geRG/Model.h>
#include <geRG/RenderingContext.h>
#include <geRG/Transformation.h>
#include <geAd/OsgImport/OsgImport.h>
#include <geAd/WindowObject/WindowObject.h>
#include <geUtil/ArgumentObject.h>
#include <osg/ref_ptr>
#include <osgDB/ReadFile>

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


bool DisableAnttweakbar=true;
ge::util::ArgumentObject *Args;
ge::util::WindowObject   *Window;

static bool useARBShaderDrawParameters=false;
static string fileName;
static shared_ptr<Model> model;


int main(int Argc,char*Argv[])
{
  Args=new ge::util::ArgumentObject(Argc,Argv);

  DisableAnttweakbar=true;

  //window args
  WindowParam.Size[0]    = atoi(Args->getArg("-w","800").c_str());
  WindowParam.Size[1]    = atoi(Args->getArg("-h","600").c_str());
  WindowParam.Fullscreen = Args->isPresent("-f");

  //context args
  ContextParam.Version = atoi(Args->getArg("--context-version","430").c_str());
  ContextParam.Profile = Args->getArg("--context-profile","core");
  ContextParam.Flag    = Args->getArg("--context-flag","debug");

  // file name
  if(Argc>1)
  {
     int i=Argc-1;
     if(Argv[i][0]!='-')
        if(Argc==2 || Argv[i-1][0]!='-')  fileName=Argv[1];
  }

  Window=new ge::util::WindowObject(
      WindowParam.Size[0],
      WindowParam.Size[1],
      WindowParam.Fullscreen,
      Idle,
      Mouse,
      !DisableAnttweakbar,
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

  // OpenGL debugging messages
  //ge::gl::setDefaultDebugMessage();

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glDisable(GL_CULL_FACE);

  Init();
  Window->mainLoop();
  delete Window;
  delete Args;
  return 0;
}


void Mouse(){
}


void Wheel(int){
}


void Idle()
{
   // render scene
   RenderingContext::current()->frame();

   Window->swap();
}




void Init()
{
   ge::gl::initShadersAndPrograms();

   // load model
   if(!fileName.empty())
   {
      osg::ref_ptr<osg::Node> root=osgDB::readNodeFile(fileName);
      if(root==nullptr)
         cout<<"Failed to load file "<<fileName<<endl;
      else
      {
         model=ge::osgImport::import(root);
      }

      // release OSG memory
      root=nullptr;
      osgDB::Registry::instance()->closeAllLibraries();
      osgDB::Registry::instance(true);
   }

   if(model)
   {
      // instantiate model with given transformation matrix
      shared_ptr<Transformation> t=make_shared<Transformation>();
      const float m[16] = {
         1.f, 0.f, 0.f, 0.f,
         0.f, 1.f, 0.f, 0.f,
         0.f, 0.f, 1.f, 0.f,
         0.f, 0.f,-10.f, 1.f,
      };
      t->uploadMatrix(m);
      t->addChild(model->transformationRoot());
      RenderingContext::current()->addTransformationGraph(t);
   }

   // unmap buffers
   // (it has to be done before rendering)
   RenderingContext::current()->unmapBuffers();

   glm::mat4 projection=glm::perspective(float(60.*M_PI/180.),float(WindowParam.Size[0])/WindowParam.Size[1],1.f,100.f);
   auto ambientProgram=RenderingContext::current()->getAmbientProgram();
   ambientProgram->use();
   ambientProgram->set("globalAmbientLight",0.2f,0.2f,0.2f,1.f);
   ambientProgram->set("projection",1,GL_FALSE,glm::value_ptr(projection));
   ambientProgram->set("colorTexture",int(0));
   auto phongProgram=RenderingContext::current()->getPhongProgram();
   phongProgram->use();
   phongProgram->set("projection",1,GL_FALSE,glm::value_ptr(projection));
   phongProgram->set("specularAndShininess",0.33f,0.33f,0.33f,0.f); // shininess in alpha
   phongProgram->set("lightPosition",0.f,0.f,0.f,1.f); // in eye coordinates, w must be 0 or 1
   phongProgram->set("lightColor",1.f,1.f,1.f);
   phongProgram->set("lightAttenuation",1.f,0.f,0.f);
   phongProgram->set("colorTexture",int(0));
}
