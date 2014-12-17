#include <string>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <geGL/DebugMessage.h>
#include <geGL/ProgramObject.h>
#include <geSG/Array.h>
#include <geSG/AttribReference.h>
#include <geSG/Mesh.h>
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
static AttribReference attribsRefNI;
static AttribReference attribsRefI;
static shared_ptr<Mesh> meshNI;
static shared_ptr<Mesh> meshI;


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

  ge::gl::setDefaultDebugMessage();

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glDisable(GL_CULL_FACE);

  Init();
  Window->mainLoop();
  delete glProgram;
  delete Window;
  delete Args;
  return 0;
}


void Mouse(){
}


void Wheel(int d){
}


void Idle(){
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   glProgram->use();
   attribsRefNI.attribStorage->bind();
   glDrawArrays(GL_TRIANGLES,0,3);
   glDrawArrays(GL_TRIANGLES,3,3);
   attribsRefI.attribStorage->bind();
   glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_INT,(void*)0);
   glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_INT,(void*)12);
   AttribStorage *storageNI=meshNI->getAttribReference().attribStorage;
   storageNI->bind();
   const AttribStorage::AllocationBlock &blockNI=storageNI->getVerticesAllocationBlock(meshNI->getAttribReference().verticesDataId);
   glDrawArrays(GL_TRIANGLES,blockNI.startIndex,blockNI.numElements);
   AttribStorage *storageI=meshI->getAttribReference().attribStorage;
   storageI->bind();
   const AttribStorage::AllocationBlock &blockI=storageI->getIndicesAllocationBlock(meshI->getAttribReference().indicesDataId);
   glDrawElementsBaseVertex(GL_TRIANGLES,blockI.numElements,GL_UNSIGNED_INT,(void*)(blockI.startIndex*sizeof(uint32_t)),6);
   Window->swap();
}


void Init(){
   AttribConfig::ConfigData config;
   config.attribTypes.push_back(AttribType::Vec3);

   // top-left geometry
   config.ebo=false;
   config.updateId();

   constexpr float z=-6.f;
   constexpr float niShiftX=-1.5f;
   constexpr float shiftY=1.5f;
   const vector<glm::vec3> twoTrianglesNI = {
      glm::vec3(niShiftX+0,shiftY+0,z),
      glm::vec3(niShiftX+0,shiftY+1,z),
      glm::vec3(niShiftX+1,shiftY+0,z),
      glm::vec3(niShiftX+0,shiftY+0,z),
      glm::vec3(niShiftX+0,shiftY-1,z),
      glm::vec3(niShiftX-1,shiftY+0,z),
   };
   vector<Array> v;
   v.reserve(1);
   v.emplace_back(twoTrianglesNI);

   attribsRefNI.allocData(config,6,0);
   attribsRefNI.uploadVertexData(v);

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
   v.clear();
   v.reserve(1);
   v.emplace_back(twoTrianglesI);

   attribsRefI.allocData(config,6,6);
   attribsRefI.uploadVertexData(v);
   const vector<unsigned> indices = { 5, 1, 2, 3, 4, 5 };
   attribsRefI.uploadIndices(Array(indices));

   // bottom-left geometry
   constexpr float meshShiftY=-1.5f;
   const vector<glm::vec3> twoTrianglesMeshNI = {
      glm::vec3(niShiftX+0,meshShiftY+0,z),
      glm::vec3(niShiftX+0,meshShiftY+1,z),
      glm::vec3(niShiftX+1,meshShiftY+0,z),
      glm::vec3(niShiftX+0,meshShiftY+0,z),
      glm::vec3(niShiftX+0,meshShiftY-1,z),
      glm::vec3(niShiftX-1,meshShiftY+0,z),
   };
   v.clear();
   v.reserve(1);
   v.emplace_back(twoTrianglesMeshNI);
   vector<Mesh::ArrayContent> contents;
   contents.reserve(1);
   contents.push_back(Mesh::ArrayContent::COORDINATES);
   meshNI=Mesh::create();
   meshNI->setAttribArrays(v,contents);
   meshNI->gpuUploadGeometryData();

   // bottom-right geometry
   const vector<glm::vec3> twoTrianglesMeshI = {
      glm::vec3(iShiftX+0,meshShiftY+0,z),
      glm::vec3(iShiftX+0,meshShiftY+1,z),
      glm::vec3(iShiftX+1,meshShiftY+0,z),
      glm::vec3(iShiftX+0,meshShiftY+0.1f,z),
      glm::vec3(iShiftX+0,meshShiftY-1,z),
      glm::vec3(iShiftX-1,meshShiftY+0,z),
   };
   v.clear();
   v.reserve(1);
   v.emplace_back(twoTrianglesMeshI);
   meshI=Mesh::create();
   meshI->setAttribArrays(v,contents);
   meshI->setIndexArray(indices);
   meshI->gpuUploadGeometryData();

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
}
