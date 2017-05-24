#include <geAd/SDLWindow/SDLWindow.h>
#include <geAd/SDLWindow/SDLMainLoop.h>
#include <geGL/geGL.h>
#include <geGL/StaticCalls.h>
#include <chrono>

using namespace std;
using namespace ge::gl;
using namespace ge::ad;

int main(int,char*[]){
  uint32_t windowWidth = 1024;
  uint32_t windowHeight = 768;
  auto mainLoop = make_shared<SDLMainLoop>();
  auto window = make_shared<SDLWindow>(windowWidth,windowHeight);

  window->createContext("rendering");
  mainLoop->addWindow("mainWindow", window);

  ge::gl::init();
  setHighDebugMessage();

  GLenum fbo;
  GLenum texture;
  glViewport(0, 0, windowWidth, windowHeight);
  glCreateFramebuffers(1,&fbo);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glCreateTextures(GL_TEXTURE_2D,1,&texture);
  glTextureImage2DEXT(texture,GL_TEXTURE_2D,0,GL_RGBA,windowWidth,windowHeight,0,GL_RGBA,GL_UNSIGNED_BYTE,nullptr);
  glNamedFramebufferTexture(fbo,GL_COLOR_ATTACHMENT0,texture,0);

  std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
  mainLoop->setIdleCallback([&]() {
      std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
      std::chrono::duration<double> elapsed_seconds = now - start;
      glBindFramebuffer(GL_FRAMEBUFFER,fbo);
      glClearColor(0.f, float(cos(elapsed_seconds.count()))*.5f+.5f, 0.f, 1.f);
      glClear(GL_COLOR_BUFFER_BIT);
      glBindFramebuffer(GL_FRAMEBUFFER, 0);
      glBlitNamedFramebuffer(fbo, 0, 0, 0, windowWidth, windowHeight, 0, 0, windowWidth, windowHeight, GL_COLOR_BUFFER_BIT, GL_NEAREST); 
      window->swap();
      });

  (*mainLoop)();
  return 0;
}
