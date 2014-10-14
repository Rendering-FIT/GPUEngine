#include"main.h"

void Init();
void Idle();
void Mouse();
void Wheel(int d);

void MyDebug(GLenum Source,GLenum Type,GLuint Id,GLenum severity,
    GLsizei Length,const GLchar*Message,void*UserParam);

struct SContextParam{
  unsigned    Version;
  std::string Profile;
  std::string Flag;
}ContextParam;

struct SWindowParam{
  unsigned Size[2];
  bool     Fullscreen;
}WindowParam;

float MyAtof(const char*S){
  if(S[0]=='-')return -std::atof(S+1);
  std::string Str(S);
  if(Str=="inf")return std::numeric_limits<float>::infinity();
  else return std::atof(S);
}

bool DisableAnttweakbar=true;
ArgumentObject *Args;
WindowObject   *Window;
//NDormon::CVertexArray*EmptyVAO;

int main(int Argc,char*Argv[]){
  Args=new ArgumentObject(Argc,Argv);

  ShaderDir=Args->getArg("--shader-directory","");

  DisableAnttweakbar=Args->isPresent("--disable-anttweakbar");

  //window args
  WindowParam.Size[0] =atoi(Args->getArg("-w","800").c_str());
  WindowParam.Size[1]=atoi(Args->getArg("-h","600").c_str());
  WindowParam.Fullscreen=Args->isPresent("-f");

  //context args
  ContextParam.Version=atoi(Args->getArg("--context-version","430").c_str());
  ContextParam.Profile=Args->getArg("--context-profile","core");
  ContextParam.Flag=Args->getArg("--context-flag","debug");

  Window=new WindowObject(
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
  //ProgramObject::initShaderManager();

  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback((GLDEBUGPROC)MyDebug,NULL);

  //EmptyVAO=new NDormon::CVertexArray();

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

void Wheel(int d){
}

void Idle(){
  Window->swap();
}

std::string TranslateSource(GLenum Source){
  switch(Source){//swich over debug sources
    case GL_DEBUG_SOURCE_API:
      return"GL_DEBUG_SOURCE_API";
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
      return"GL_DEBUG_SOURCE_WINDOW_SYSTEM";
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
      return"GL_DEBUG_SOURCE_SHADER_COMPILER";
    case GL_DEBUG_SOURCE_THIRD_PARTY:
      return"GL_DEBUG_SOURCE_THIRD_PARTY";
    case GL_DEBUG_SOURCE_APPLICATION:
      return"GL_DEBUG_SOURCE_APPLICATION";
    case GL_DEBUG_SOURCE_OTHER:
      return"GL_DEBUG_SOURCE_OTHER";
    default:
      return"Unknown DEBUG SOURCE";
  }
}

std::string TranslateType(GLenum Type){
  switch(Type){//switch over debug types
    case GL_DEBUG_TYPE_ERROR:
      return"GL_DEBUG_TYPE_ERROR";
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
      return"GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR";
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
      return"GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR";
    case GL_DEBUG_TYPE_PORTABILITY:
      return"GL_DEBUG_TYPE_PORTABILITY";
    case GL_DEBUG_TYPE_PERFORMANCE:
      return"GL_DEBUG_TYPE_PERFORMANCE";
    case GL_DEBUG_TYPE_MARKER:
      return"GL_DEBUG_TYPE_MARKER";
    case GL_DEBUG_TYPE_PUSH_GROUP:
      return"GL_DEBUG_TYPE_PUSH_GROUP";
    case GL_DEBUG_TYPE_POP_GROUP:
      return"GL_DEBUG_TYPE_POP_GROUP";
    case GL_DEBUG_TYPE_OTHER:
      return"GL_DEBUG_TYPE_OTHER";
    case GL_DONT_CARE:
      return"GL_DONT_CARE";
    default:
      return"Unknown DEBUG TYPE";
  }
}

std::string TranslateSeverity(GLenum Severity){
  switch(Severity){//switch over debug severities
    case GL_DEBUG_SEVERITY_LOW:
      return"GL_DEBUG_SEVERITY_LOW";
    case GL_DEBUG_SEVERITY_MEDIUM:
      return"GL_DEBUG_SEVERITY_MEDIUM";
    case GL_DEBUG_SEVERITY_HIGH:
      return"GL_DEBUG_SEVERITY_HIGH";
    case GL_DEBUG_SEVERITY_NOTIFICATION:
      return"GL_DEBUG_SEVERITY_NOTIFICATION";
    case GL_DONT_CARE:
      return"GL_DONT_CARE";
    default:
      return"Unknown DEBUG SEVERITY";
  }
}

void MyDebug(GLenum Source,GLenum Type,GLuint Id,GLenum severity,
    GLsizei Length,const GLchar*Message,void*UserParam){
  std::cerr<<"Source: "<<TranslateSource(Source)<<
    " Type: "<<TranslateType(Type)<</*" Id: "<<Id<<*/
    " Severity: "<<TranslateSeverity(severity)<</*" Length: "<<Length<<*/" : ";
  std::cerr<<Message<<std::endl;
}

void Init(){

}


