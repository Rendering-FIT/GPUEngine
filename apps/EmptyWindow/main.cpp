#include<limits>
#include<string>
#include<GL/glew.h>
#include<geGL/geGL.h>
#include<geUtil/NamespaceWithUsers.h>
#include<geUtil/copyArgumentManager2Namespace.h>
#include<geUtil/ArgumentManager/ArgumentManager.h>
#include<geAd/WindowObject/WindowObject.h>

void init();
void idle();
void mouse();

ge::util::WindowObject*                           window       = nullptr;
std::shared_ptr<ge::core::TypeRegister>           typeRegister = nullptr;
std::shared_ptr<ge::util::sim::NamespaceWithUsers>sData        = nullptr;

int main(int argc,char*argv[]){
  typeRegister = std::make_shared<ge::core::TypeRegister>();
  sData        = std::make_shared<ge::util::sim::NamespaceWithUsers>("*");
  ge::util::ArgumentManager*argm = new ge::util::ArgumentManager(argc-1,argv+1);
  ge::util::sim::copyArgumentManager2Namespace(sData,argm,typeRegister);

  window = new ge::util::WindowObject(
      sData->get<unsigned[2]>("window.size"      ,{1024u,1024u})[0],
      sData->get<unsigned[2]>("window.size"      ,{1024u,1024u})[1],
      sData->get<bool       >("window.fullscreen",false        )   ,
      idle,
      mouse,
      sData->get<bool       >("enableAntTweakBar",true         )   ,
      sData->get<unsigned   >("context.version"  ,450          )   ,
      sData->get<std::string>("context.profile"  ,"core"       )   ,
      sData->get<std::string>("context.debug"    ,"debug"      )   );

  init();
  window->mainLoop();
  delete window;
  delete argm;
  return 0;
}

void mouse(){
}

void idle(){
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  window->swap();
}

void init(){
  glewExperimental=GL_TRUE;
  glewInit();

  ge::gl::setDefaultDebugMessage();

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glDisable(GL_CULL_FACE);
}
