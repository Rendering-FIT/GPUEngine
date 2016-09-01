#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <geGL/geGL.h>
#include <geGL/Program.h>
#include <geRG/RenderingContext.h>
#include <geRG/Transformation.h>
#include <geUtil/ArgumentObject.h>
#include <geAd/SDLWindow/SDLWindow.h>
#include <typeinfo> // MSVC 2013 requires this rather at the end of headers to compile successfully
#include <typeindex>


using namespace std;
using namespace ge::rg;


static void init(unsigned windowWidth,unsigned windowHeight);
static void idleCallback(void*);

static ge::ad::SDLMainLoop mainLoop;
static shared_ptr<ge::ad::SDLWindow> window;
static shared_ptr<ge::gl::Program> glProgram;
static Mesh mesh;


int main(int argc,char* argv[])
{
   // argument parser
   ge::util::ArgumentObject* args=new ge::util::ArgumentObject(argc,argv);

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

   // init scene and main loop
   init(window->getWidth(),window->getHeight());
   mainLoop.operator()();

   // clean up
   delete args;

   return 0;
}


static void idleCallback(void*)
{
   RenderingContext::current()->frame();
   window->swap();
}


static void init(unsigned windowWidth,unsigned windowHeight)
{
   // setup OpenGL
   auto& gl=RenderingContext::current()->gl;
   gl.glEnable(GL_DEPTH_TEST);
   gl.glDepthFunc(GL_LEQUAL);
   gl.glDisable(GL_CULL_FACE);

   // setup shaders and prepare GLSL program
   glProgram=make_shared<ge::gl::Program>(
      make_shared<ge::gl::Shader>(GL_VERTEX_SHADER,
         "#version 330\n"
         "layout(location=0)  in vec3 coords;\n"
         "layout(location=12) in mat4 instancingMatrix;\n"
         "uniform mat4 mvp;\n"
         "void main()\n"
         "{\n"
         "   gl_Position = mvp*instancingMatrix*vec4(coords,1.f);\n"
         "}\n"),
      make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER,
         "#version 330\n"
         "layout(location=0) out vec4 fragColor;\n"
         "void main()\n"
         "{\n"
         "   fragColor=vec4(1.f,1.f,0.,1.);\n"
         "}\n"));
   glm::mat4 modelView(1.f); // identity
   glm::mat4 projection=glm::perspective(float(60.*M_PI/180.),float(windowWidth)/float(windowHeight),1.f,100.f);
   glm::mat4 mvp=modelView*projection;
   glProgram->use();
   glProgram->setMatrix4fv("mvp",glm::value_ptr(mvp),1,GL_FALSE);

   // state set
   StateSetManager::GLState *glState=RenderingContext::current()->createGLState();
   glState->set("bin",type_index(typeid(int)),reinterpret_cast<void*>(0)); // bin 0 is for ambient pass
   glState->set("glProgram",type_index(typeid(shared_ptr<ge::gl::Program>*)),&glProgram);
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
      { 3,0,true },
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
