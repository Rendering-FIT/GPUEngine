#include <string>
#include <typeinfo>
#include <typeindex>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <geGL/BufferObject.h>
#include <geGL/DebugMessage.h>
#include <geGL/ProgramObject.h>
#include <geRG/Mesh.h>
#include <geRG/RenderingContext.h>
#include <geRG/StateSet.h>
#include <geAd/WindowObject/WindowObject.h>
#include <geUtil/ArgumentObject.h>

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

static shared_ptr<ProgramObject> glProgram;
static Mesh meshDirectNI;
static Mesh meshDirectI;
static Mesh meshIndirectNI;
static Mesh meshIndirectI;


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
  RenderingContext::setCurrent(make_shared<RenderingContext>());

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


void Wheel(int /*d*/){
}


void Idle()
{
   RenderingContext::current()->frame();

   // draw meshDirectNI
   glProgram->use();
   meshDirectNI.attribStorage()->bind();
   unsigned baseIndex=meshDirectNI.attribStorage()->vertexAllocationBlock(meshDirectNI.verticesDataId()).startIndex;
   glDrawArrays(GL_TRIANGLES,baseIndex+0,3);
   glDrawArrays(GL_TRIANGLES,baseIndex+3,3);

   // draw meshDirectI
   meshDirectI.attribStorage()->bind();
   baseIndex=meshDirectI.attribStorage()->indexAllocationBlock(meshDirectI.indicesDataId()).startIndex;
   glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_INT,(void*)(intptr_t(baseIndex)*4+0));
   glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_INT,(void*)(intptr_t(baseIndex)*4+12));

   Window->swap();
}


void Init()
{
   // setup shaders, etc.
   ge::gl::initShadersAndPrograms();
   glProgram=make_shared<ProgramObject>(
      GL_VERTEX_SHADER,
      "#version 330\n"
      "layout(location=0) in vec3 coords;\n"
      "uniform mat4 mvp;\n"
      "void main()\n"
      "{\n"
      "   gl_Position = mvp*vec4(coords,1.f);\n"
      "}\n",
      GL_FRAGMENT_SHADER,
      "#version 330\n"
      "layout(location=0) out vec4 fragColor;\n"
      "void main()\n"
      "{\n"
      "   fragColor=vec4(1.f,1.f,0.,1.);\n"
      "}\n");
   glm::mat4 modelView(1.f); // identity
   glm::mat4 projection=glm::perspective(float(60.*M_PI/180.),float(WindowParam.Size[0])/WindowParam.Size[1],1.f,100.f);
   glm::mat4 mvp=modelView*projection;
   glProgram->use();
   glProgram->set("mvp",1,GL_FALSE,glm::value_ptr(mvp));
   RenderingContext::current()->setGLProgram(idof(Ambient,geRG_GLPrograms),glProgram);
   RenderingContext::current()->init();

   StateSetManager::GLState *glState=RenderingContext::current()->createGLState();
   glState->set("glProgram",type_index(typeid(shared_ptr<ge::gl::ProgramObject>*)),&glProgram);
   shared_ptr<StateSet> stateSet=RenderingContext::current()->getOrCreateStateSet(glState);
   delete glState;


   AttribConfig::ConfigData config;
   config.attribTypes.push_back(AttribType::Vec3);

   // top-left geometry - raw rendering, not using indirect draw optimization
   // (only coordinates in AttribStorage while manual OpenGL setup and draw calls are required)
   // (non-indexed, not indirect draw)
   config.ebo=false;
   config.updateId();

   constexpr float z=-10.f;
   constexpr float niShiftX=-1.5f;
   constexpr float directShiftY=3.0f;
   const vector<glm::vec3> twoTrianglesNI = {
      glm::vec3(niShiftX+0,directShiftY+0,z),
      glm::vec3(niShiftX+0,directShiftY+1,z),
      glm::vec3(niShiftX+1,directShiftY+0,z),
      glm::vec3(niShiftX+0,directShiftY+0,z),
      glm::vec3(niShiftX+0,directShiftY-1,z),
      glm::vec3(niShiftX-1,directShiftY+0,z),
   };

   vector<const void*> attribList;
   attribList.reserve(1);
   attribList.emplace_back(twoTrianglesNI.data());
   meshDirectNI.allocData(config,6,0,0);
   meshDirectNI.uploadVertices(attribList.data(),attribList.size(),twoTrianglesNI.size());

   // top-right geometry - the same as above but using indexing
   config.ebo=true;
   config.updateId();

   constexpr float iShiftX=1.5f;
   const vector<glm::vec3> twoTrianglesI = {
      glm::vec3(iShiftX+0,directShiftY+0,z),
      glm::vec3(iShiftX+0,directShiftY+1,z),
      glm::vec3(iShiftX+1,directShiftY+0,z),
      glm::vec3(iShiftX+0,directShiftY+0.1f,z),
      glm::vec3(iShiftX+0,directShiftY-1,z),
      glm::vec3(iShiftX-1,directShiftY+0,z),
   };
   const vector<unsigned> indices = { 5, 1, 2, 3, 4, 5 };

   attribList[0]=twoTrianglesI.data();
   meshDirectI.allocData(config,6,6,0);
   meshDirectI.uploadVertices(attribList.data(),attribList.size(),twoTrianglesI.size());
   meshDirectI.uploadIndices(indices.data(),indices.size());

   // bottom-left geometry - high level, using indirect rendering optimization
   // (non-indexed, using optimized rendering, using identity transformation matrix)
   constexpr float indirectShiftY=directShiftY-3.0f;
   const vector<glm::vec3> twoTrianglesIndirectNI = {
      glm::vec3(niShiftX+0,indirectShiftY+0,z),
      glm::vec3(niShiftX+0,indirectShiftY+1,z),
      glm::vec3(niShiftX+1,indirectShiftY+0,z),
      glm::vec3(niShiftX+0,indirectShiftY+0,z),
      glm::vec3(niShiftX+0,indirectShiftY-1,z),
      glm::vec3(niShiftX-1,indirectShiftY+0,z),
   };
   vector<PrimitiveGpuData> primitiveDataNI = {
      { 3,0,0 },
      { 3,3,3 }
   };
   const vector<unsigned> modesAndOffsets4 = {
      GL_TRIANGLES,0,
      GL_TRIANGLES,3,
   };

   config.ebo=false;
   config.updateId();
   attribList[0]=twoTrianglesIndirectNI.data();
   meshIndirectNI.allocData(config,6,0,primitiveDataNI.size());
   meshIndirectNI.uploadVertices(attribList.data(),attribList.size(),twoTrianglesIndirectNI.size());
   meshIndirectNI.setAndUploadPrimitives(primitiveDataNI.data(),
                                         modesAndOffsets4.data(),primitiveDataNI.size());
   shared_ptr<MatrixList> identity=make_shared<MatrixList>(1);
   identity->upload(RenderingContext::identityMatrix,1);
   meshIndirectNI.createDrawable(identity.get(),stateSet.get());

   // bottom-right geometry - high level, using indirect rendering optimization
   // (indexed, using optimized rendering)
   const vector<glm::vec3> twoTrianglesIndirectI = {
      glm::vec3(iShiftX+0,indirectShiftY+0,z),
      glm::vec3(iShiftX+0,indirectShiftY+1,z),
      glm::vec3(iShiftX+1,indirectShiftY+0,z),
      glm::vec3(iShiftX+0,indirectShiftY+0,z),
      glm::vec3(iShiftX+0,indirectShiftY-1,z),
      glm::vec3(iShiftX-1,indirectShiftY+0,z),
   };
   vector<PrimitiveGpuData> primitiveDataI = {
      { 0x80000003,0,0 },
      { 0x80000003,3,3 }
   };

   config.ebo=true;
   config.updateId();
   attribList[0]=twoTrianglesIndirectI.data();
   meshIndirectI.allocData(config,6,6,primitiveDataI.size());
   meshIndirectI.uploadVertices(attribList.data(),attribList.size(),twoTrianglesIndirectI.size());
   meshIndirectI.uploadIndices(indices.data(),indices.size());
   meshIndirectI.setAndUploadPrimitives(primitiveDataI.data(),
                                        modesAndOffsets4.data(),primitiveDataI.size());
   meshIndirectI.createDrawable(identity.get(),stateSet.get());


   // unmap buffers
   // (it has to be done before rendering)
   RenderingContext::current()->unmapBuffers();
}
