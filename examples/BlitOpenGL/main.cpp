#include <geAd/SDLWindow/SDLWindow.h>
#include <geAd/SDLWindow/SDLMainLoop.h>
#include <geGL/geGL.h>
#include <chrono>

using namespace std;
using namespace ge::gl;
using namespace ge::ad;

int main(){
  uint32_t windowWidth = 1024;
  uint32_t windowHeight = 768;
  auto mainLoop = make_shared<SDLMainLoop>();
  auto window = make_shared<SDLWindow>(windowWidth,windowHeight);

  window->createContext("rendering");
  mainLoop->addWindow("mainWindow", window);

  ge::gl::init(SDL_GL_GetProcAddress);
  setHighDebugMessage();

  auto gl = make_shared<Context>();

  GLenum fbo;
  GLenum texture;
  gl->glViewport(0, 0, windowWidth, windowHeight);
  gl->glCreateFramebuffers(1,&fbo);
  gl->glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  gl->glCreateTextures(GL_TEXTURE_2D,1,&texture);
  gl->glTextureImage2DEXT(texture,GL_TEXTURE_2D,0,GL_RGBA,windowWidth,windowHeight,0,GL_RGBA,GL_UNSIGNED_BYTE,nullptr);
  gl->glNamedFramebufferTexture(fbo,GL_COLOR_ATTACHMENT0,texture,0);

  std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
  mainLoop->setIdleCallback([&]() {
      std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
      std::chrono::duration<double> elapsed_seconds = now - start;
      gl->glBindFramebuffer(GL_FRAMEBUFFER,fbo);
      gl->glClearColor(0.f, float(cos(elapsed_seconds.count()))*.5f+.5f, 0.f, 1.f);
      gl->glClear(GL_COLOR_BUFFER_BIT);
      gl->glBindFramebuffer(GL_FRAMEBUFFER, 0);
      gl->glBlitNamedFramebuffer(fbo, 0, 0, 0, windowWidth, windowHeight, 0, 0, windowWidth, windowHeight, GL_COLOR_BUFFER_BIT, GL_NEAREST); 
      window->swap();
      });

  (*mainLoop)();
  return 0;
}
