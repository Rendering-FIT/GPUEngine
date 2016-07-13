#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <geGL/geGL.h>
#include <geGL/ProgramObject.h>
#include <geRG/RenderingContext.h>
#include <geRG/Transformation.h>
#include <geUtil/ArgumentObject.h>
#include <geAd/WindowObject/WindowObject.h>
#include <typeinfo> // MSVC 2013 requires this rather at the end of headers to compile successfully
#include <typeindex>


using namespace std;
using namespace ge::rg;


static ge::util::WindowObject* window;
static glm::ivec2 windowSize;
static shared_ptr<ge::gl::ProgramObject> glProgram;
static Mesh mesh;

void Init();
void Idle();
void Mouse();
void Wheel(int d);


int main(int argc,char* argv[])
{
   ge::util::ArgumentObject* args=new ge::util::ArgumentObject(argc,argv);

   windowSize=glm::ivec2(atoi(args->getArg("-w","800").c_str()),
                         atoi(args->getArg("-h","600").c_str()));

   window=new ge::util::WindowObject(
         windowSize[0],
         windowSize[1],
         args->isPresent("-f"),
         Idle,
         Mouse,
         false,
         atoi(args->getArg("--context-version","430").c_str()),
         args->getArg("--context-profile","core"),
         args->getArg("--context-flag","debug"));

   glewExperimental=GL_TRUE;
   glewInit();
   glGetError(); // glewInit() might generate GL_INVALID_ENUM on some glew versions
                 // as said on https://www.opengl.org/wiki/OpenGL_Loading_Library,
                 // problem seen on CentOS 7.1 (release date 2015-03-31) with GLEW 1.9 (release date 2012-08-06)
   ge::gl::init();
   RenderingContext::setCurrent(make_shared<RenderingContext>());

   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LEQUAL);
   glDisable(GL_CULL_FACE);

   Init();
   window->mainLoop();

   delete window;
   delete args;

   return 0;
}


void Mouse(){
}


void Wheel(int /*d*/){
}


void Idle()
{
   RenderingContext::current()->frame();
   window->swap();
}


void Init()
{
   // setup shaders and prepare GLSL program
   //ge::gl::initShadersAndPrograms();
   glProgram=make_shared<ge::gl::ProgramObject>(
      GL_VERTEX_SHADER,
      "#version 330\n"
      "layout(location=0)  in vec3 coords;\n"
      "layout(location=12) in mat4 instancingMatrix;\n"
      "uniform mat4 mvp;\n"
      "void main()\n"
      "{\n"
      "   gl_Position = mvp*instancingMatrix*vec4(coords,1.f);\n"
      "}\n",
      GL_FRAGMENT_SHADER,
      "#version 330\n"
      "layout(location=0) out vec4 fragColor;\n"
      "void main()\n"
      "{\n"
      "   fragColor=vec4(1.f,1.f,0.,1.);\n"
      "}\n");
   glm::mat4 modelView(1.f); // identity
   glm::mat4 projection=glm::perspective(float(60.*M_PI/180.),float(windowSize[0])/(float)windowSize[1],1.f,100.f);
   glm::mat4 mvp=modelView*projection;
   glProgram->use();
   glProgram->set("mvp",1,GL_FALSE,glm::value_ptr(mvp));

   // state set
   StateSetManager::GLState *glState=RenderingContext::current()->createGLState();
   glState->set("bin",type_index(typeid(int)),reinterpret_cast<void*>(0)); // bin 0 is for ambient pass
   glState->set("glProgram",type_index(typeid(shared_ptr<ge::gl::ProgramObject>*)),&glProgram);
   shared_ptr<StateSet> stateSet=RenderingContext::current()->getOrCreateStateSet(glState);
   delete glState;

   // transformation
   shared_ptr<Transformation> transformation=make_shared<Transformation>();
   transformation->uploadMatrix(glm::translate(glm::vec3(0.f,0.f,-10.f)));
   RenderingContext::current()->addTransformationGraph(transformation);


   // triangle vertices
   const vector<glm::vec3> vertices = {
      glm::vec3( 0,2,0),
      glm::vec3( 1,0,0),
      glm::vec3(-1,0,0),
   };

   // triangle indices
   const vector<unsigned> indices = { 0, 1, 2 };

   // primitive data (count,first,vertexOffset)
   vector<PrimitiveGpuData> primitives = {
      { 0x80000003,0,0 },
   };

   // GL primitive mode and offset to primitives
   const vector<unsigned> modesAndOffsets4 = {
      GL_TRIANGLES,0,
   };


   // attribute configuration
   AttribConfig::ConfigData config;
   config.attribTypes.push_back(AttribType::Vec3);
   config.ebo=true;
   config.updateId();

   // temporary list of attributes
   vector<const void*> attribList;
   attribList.emplace_back(vertices.data());

   // alloc space for vertices and indices in AttribStorage
   // and for primitives in RenderingContext::PrimitiveStorage
   mesh.allocData(config,3,3,1); // numVertices,numIndices,numPrimitives

   // upload vertices to AttribStorage
   mesh.uploadVertices(attribList.data(),1,3); // attribListSize,numVertices

   // upload indices to AttribStorage
   mesh.uploadIndices(indices.data(),3); // numIndices

   // upload primitives to RenderingContext::PrimitiveStorage
   mesh.setAndUploadPrimitives(primitives.data(),
                               modesAndOffsets4.data(),1); // numPrimitives

   // create drawable
   mesh.createDrawable(transformation->getOrCreateMatrixList().get(),stateSet.get());

   // unmap buffers
   // (it has to be done before rendering)
   RenderingContext::current()->unmapBuffers();
}
