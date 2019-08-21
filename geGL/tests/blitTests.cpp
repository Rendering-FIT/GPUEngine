#include<catch.hpp>
#include<SDLWin.h>
#include<geGL/geGL.h>
#include<geGL/StaticCalls.h>

using namespace ge::gl;
using namespace std;

GLuint createDepthTex(uint32_t w,uint32_t h){
  GLuint id;
  REQUIRE(glGetError() == GL_NO_ERROR);
  glCreateTextures(GL_TEXTURE_RECTANGLE,1,&id);
  REQUIRE(glGetError() == GL_NO_ERROR);
  glTextureStorage2D(id,1,GL_DEPTH_COMPONENT24,w,h);
  REQUIRE(glGetError() == GL_NO_ERROR);
  return id;
}

void clear(GLuint id,float a){
  glClearTexImage(id,0,GL_DEPTH_COMPONENT,GL_FLOAT,&a);
  REQUIRE(glGetError() == GL_NO_ERROR);
}

float getTexel(GLuint id,uint32_t w,uint32_t h){
  std::vector<float>d(w*h);
  glGetTextureImage(id,0,GL_DEPTH_COMPONENT,GL_FLOAT,sizeof(float)*d.size(),d.data());
  REQUIRE(glGetError() == GL_NO_ERROR);
  return d.at(0);
}

GLuint createDepthFrame(GLuint tex){
  GLuint id;
  REQUIRE(glGetError() == GL_NO_ERROR);
  glCreateFramebuffers(1,&id);
  REQUIRE(glGetError() == GL_NO_ERROR);
  glNamedFramebufferTexture(id,GL_DEPTH_ATTACHMENT,tex,0);
  REQUIRE(glGetError() == GL_NO_ERROR);
  return id;
}

TEST_CASE("blitTests"){
  SDLWin win;
  win.beginFrame();
  ge::gl::init();
  ge::gl::setHighDebugMessage();
  {
    int const w=10;
    int const h=10;
    GLuint id = createDepthTex(w,h);
    clear(id,1.f);

    auto d = getTexel(id,w,h);
    REQUIRE(d==1.f);

    GLuint tid = createDepthTex(w,h);
    clear(tid,0.f);
    REQUIRE(getTexel(tid,w,h) == 0.f);

    auto fid = createDepthFrame(id);
    auto ftid = createDepthFrame(tid);
    glBlitNamedFramebuffer(fid,ftid,0,0,w,h,0,0,w,h,GL_DEPTH_BUFFER_BIT,GL_NEAREST);
    REQUIRE(glGetError() == GL_NO_ERROR);
    REQUIRE(getTexel(tid,w,h) == 1.f);


    glDeleteTextures(1,&id);
    REQUIRE(glGetError() == GL_NO_ERROR);
  }
  win.endFrame();
}
