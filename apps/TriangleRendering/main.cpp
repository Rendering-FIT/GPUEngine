#include <string>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <geGL/BufferObject.h>
#include <geGL/DebugMessage.h>
#include <geGL/ProgramObject.h>
#include <geSG/AttribReference.h>
#include <geSG/RenderingContext.h>
#include <geSG/StateSet.h>
#include <geUtil/WindowObject.h>
#include <geUtil/ArgumentObject.h>

using namespace std;
using namespace ge::gl;
using namespace ge::sg;


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

static ProgramObject *glProgram = NULL;
static ProgramObject *processInstanceProgram = NULL;
static shared_ptr<StateSet> stateSet;
static AttribReference attribsRefNI;
static AttribReference attribsRefI;
static AttribReference attribsRefInstNI;
static AttribReference attribsRefInstI;


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
  delete glProgram;
  delete processInstanceProgram;
  delete Window;
  delete Args;
  return 0;
}


void Mouse(){
}


void Wheel(int d){
}


void Idle(){
   processInstanceProgram->use();
   processInstanceProgram->set("numToProcess",2);
   RenderingContext::current()->getDrawCommandBuffer()->bindBase(GL_SHADER_STORAGE_BUFFER,0);
   RenderingContext::current()->getInstanceBuffer()->bindBase(GL_SHADER_STORAGE_BUFFER,1);
   RenderingContext::current()->getIndirectCommandBuffer()->bindBase(GL_SHADER_STORAGE_BUFFER,2);
   glDispatchCompute(1,1,1);

   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   glProgram->use();
   attribsRefNI.attribStorage->bind();
   unsigned baseIndex=attribsRefNI.attribStorage->getVertexAllocationBlock(attribsRefNI.verticesDataId).startIndex;
   glDrawArrays(GL_TRIANGLES,baseIndex+0,3);
   glDrawArrays(GL_TRIANGLES,baseIndex+3,3);
   attribsRefI.attribStorage->bind();
   baseIndex=attribsRefI.attribStorage->getIndexAllocationBlock(attribsRefI.indicesDataId).startIndex;
   glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_INT,(void*)(intptr_t(baseIndex)*4+0));
   glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_INT,(void*)(intptr_t(baseIndex)*4+12));

   RenderingContext::current()->getIndirectCommandBuffer()->bind(GL_DRAW_INDIRECT_BUFFER);
   attribsRefNI.attribStorage->bind();
   glMemoryBarrier(GL_COMMAND_BARRIER_BIT);
   glMultiDrawArraysIndirect(GL_TRIANGLES,nullptr,2,0);

   Window->swap();
}


void Init(){
   AttribConfig::ConfigData config;
   config.attribTypes.push_back(AttribType::Vec3);

   // top-left geometry
   config.ebo=false;
   config.updateId();

   constexpr float z=-10.f;
   constexpr float niShiftX=-1.5f;
   constexpr float shiftY=3.0f;
   const vector<glm::vec3> twoTrianglesNI = {
      glm::vec3(niShiftX+0,shiftY+0,z),
      glm::vec3(niShiftX+0,shiftY+1,z),
      glm::vec3(niShiftX+1,shiftY+0,z),
      glm::vec3(niShiftX+0,shiftY+0,z),
      glm::vec3(niShiftX+0,shiftY-1,z),
      glm::vec3(niShiftX-1,shiftY+0,z),
   };
   vector<const void*> a;
   a.reserve(1);
   a.emplace_back(twoTrianglesNI.data());

   attribsRefNI.allocData(config,6,0,0);
   attribsRefNI.uploadVertices(a.data(),twoTrianglesNI.size());

   // top-right geometry
   config.ebo=true;
   config.updateId();

   constexpr float iShiftX=1.5f;
   const vector<glm::vec3> twoTrianglesI = {
      glm::vec3(iShiftX+0,shiftY+0,z),
      glm::vec3(iShiftX+0,shiftY+1,z),
      glm::vec3(iShiftX+1,shiftY+0,z),
      glm::vec3(iShiftX+0,shiftY+0.1f,z),
      glm::vec3(iShiftX+0,shiftY-1,z),
      glm::vec3(iShiftX-1,shiftY+0,z),
   };
   a[0]=twoTrianglesI.data();

   attribsRefI.allocData(config,6,6,0);
   attribsRefI.uploadVertices(a.data(),twoTrianglesI.size());
   const vector<unsigned> indices = { 5, 1, 2, 3, 4, 5 };
   attribsRefI.uploadIndices(indices.data(),indices.size());

   // bottom-left geometry
   constexpr float instanceShiftY=shiftY-3.0f;
   const vector<glm::vec3> twoTriangleInstancesNI = {
      glm::vec3(niShiftX+0,instanceShiftY+0,z),
      glm::vec3(niShiftX+0,instanceShiftY+1,z),
      glm::vec3(niShiftX+1,instanceShiftY+0,z),
      glm::vec3(niShiftX+0,instanceShiftY+0,z),
      glm::vec3(niShiftX+0,instanceShiftY-1,z),
      glm::vec3(niShiftX-1,instanceShiftY+0,z),
   };
   vector<unsigned> drawCommands = {
      GL_TRIANGLES,3,0,0,
      GL_TRIANGLES,3,3,3,
   };
   const vector<unsigned> drawCommandOffsets4 = {
      0,4,
   };
   a[0]=twoTriangleInstancesNI.data();
   config.ebo=false;
   config.updateId();
   stateSet=make_shared<StateSet>();
   attribsRefInstNI.allocData(config,6,0,24);
   attribsRefInstNI.uploadVertices(a.data(),twoTriangleInstancesNI.size());
   attribsRefInstNI.uploadDrawCommands(drawCommands.data(),drawCommands.size()*sizeof(unsigned),
                                       drawCommandOffsets4.data(),drawCommandOffsets4.size());
   attribsRefInstNI.createInstances(0u,stateSet.get());


   // unmap instance buffer
   // (it has to be done before rendering, for sure always before the frame,
   // or at least when there were any modifications to the instance buffer)
   RenderingContext::current()->unmapInstanceBuffer();


   ge::gl::initShadersAndPrograms();
   glProgram = new ProgramObject(
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
   processInstanceProgram=new ProgramObject(
      GL_COMPUTE_SHADER,
      "#version 430\n"
      "\n"
      "layout(local_size_x=64,local_size_y=1,local_size_z=1) in;\n"
      "\n"
      "layout(std430,binding=0) restrict readonly buffer DrawCommandBuffer {\n"
      "   uint drawCommandBuffer[];\n"
      "};\n"
      "layout(std430,binding=1) restrict readonly buffer InstanceBuffer {\n"
      "   uint instanceBuffer[];\n"
      "};\n"
      "layout(std430,binding=2) restrict writeonly buffer IndirectBuffer {\n"
      "   uint indirectBuffer[];\n"
      "};\n"
      "\n"
      "uniform int numToProcess;\n"
      "\n"
      "void main()\n"
      "{\n"
      "   if(gl_GlobalInvocationID.x>=numToProcess)\n"
      "      return;\n"
      "\n"
      "   uint instanceIndex=gl_GlobalInvocationID.x*3;\n"
      "   uint drawCommandOffset4=instanceBuffer[instanceIndex+0];\n"
      "\n"
      "   uint writeIndex=gl_GlobalInvocationID.x*4;\n"
      "   indirectBuffer[writeIndex+0]=drawCommandBuffer[drawCommandOffset4+1]; // count\n"
      "   indirectBuffer[writeIndex+1]=1; // instance count\n"
      "   indirectBuffer[writeIndex+2]=drawCommandBuffer[drawCommandOffset4+2]+\n"
      "                                drawCommandBuffer[drawCommandOffset4+3]; // first\n"
      "   indirectBuffer[writeIndex+3]=0; // base instance\n"
      "}\n");
}
