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
#include <geSG/AttribsReference.h>
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


static AttribsReference attribsRef;
static AttribsConfig ac;


void Idle(){
   glProgram->use();
   attribsRef.attribsStorage->bind();
   //glDrawArrays(GL_TRIANGLES,0,6);
   glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_INT,(void*)0);
   glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_INT,(void*)12);
   Window->swap();
}


void Init(){
   AttribsConfig ac;
   ac.push_back(AttribType::Vec3);
#if 0
   ac.ebo=false;
   ac.updateConfigId();
# if 0
   shared_ptr<vector<glm::vec3>> data = make_shared<vector<glm::vec3>>();
   constexpr float z=-5.f;
   data->push_back(glm::vec3(0,0,z));
   data->push_back(glm::vec3(0,1,z));
   data->push_back(glm::vec3(1,0,z));
   data->push_back(glm::vec3(0,0,z));
   data->push_back(glm::vec3(0,-1,z));
   data->push_back(glm::vec3(-1,0,z));
   vector<Array> v;
   v.resize(1);
   v[0].set(data);
# elif 0
   vector<Array> v;
   v.reserve(1);
   v.emplace_back(make_shared<vector<glm::vec3>>());
   const shared_ptr<vector<glm::vec3>> &data = v[0].get<glm::vec3>();
   constexpr float z=-5.f;
   const vector<glm::vec3> twoTriangles = {
      glm::vec3(0,0,z),
      glm::vec3(0,1,z),
      glm::vec3(1,0,z),
      glm::vec3(0,0,z),
      glm::vec3(0,-1,z),
      glm::vec3(-1,0,z),
   };
   (*data) = twoTriangles;
# elif 0
   constexpr float z=-5.f;
   const vector<glm::vec3> twoTriangles = {
      glm::vec3(0,0,z),
      glm::vec3(0,1,z),
      glm::vec3(1,0,z),
      glm::vec3(0,0,z),
      glm::vec3(0,-1,z),
      glm::vec3(-1,0,z),
   };
   vector<Array> v;
   v.reserve(1);
   v.emplace_back(make_shared<vector<glm::vec3>>(twoTriangles));
# elif 0
   constexpr float z=-5.f;
   const vector<glm::vec3> twoTriangles = {
      glm::vec3(0,0,z),
      glm::vec3(0,1,z),
      glm::vec3(1,0,z),
      glm::vec3(0,0,z),
      glm::vec3(0,-1,z),
      glm::vec3(-1,0,z),
   };
   vector<Array> v;
   v.reserve(1);
   v.emplace_back(twoTriangles);
# else
   constexpr float z=-5.f;
   const vector<glm::vec3> twoTriangles = {
      glm::vec3(0,0,z),
      glm::vec3(0,1,z),
      glm::vec3(1,0,z),
      glm::vec3(0,0,z),
      glm::vec3(0,-1,z),
      glm::vec3(-1,0,z),
   };
   vector<Array> v;
   v.reserve(1);
   v.emplace_back(twoTriangles);
# endif
   attribsRef.allocData(ac,6,0);
   attribsRef.uploadVertexData(v);
#else
   ac.ebo=true;
   ac.updateConfigId();

   constexpr float z=-1.1f;
   const vector<glm::vec3> twoTriangles = {
      glm::vec3(0,0,z),
      glm::vec3(0,1,z),
      glm::vec3(1,0,z),
      glm::vec3(0.f,0.1f,z),
      glm::vec3(0,-1,z),
      glm::vec3(-1,0,z),
   };
   vector<Array> v;
   v.reserve(1);
   v.emplace_back(twoTriangles);

   attribsRef.allocData(ac,6,6);
   attribsRef.uploadVertexData(v);
   const vector<unsigned> indices = { 5, 1, 2, 3, 4, 5 };
   attribsRef.uploadIndicesData(Array(indices));
#endif

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
