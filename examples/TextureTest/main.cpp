#include<geAd/SDLWindow/SDLWindow.h>
#include<geAd/SDLWindow/SDLMainLoop.h>
#include<geGL/StaticCalls.h>
#include<geGL/geGL.h>
#include<geGL/OpenGLUtil.h>

using namespace std;
using namespace ge::gl;
using namespace ge::ad;

std::string vSrc = R".(
#version 450
flat out uint vDirection;
void main() {
  uint triangleID = gl_VertexID/3;
  uint vertexIDInTriangle = gl_VertexID%3;
  vec2 vertexPosition = vec2(vertexIDInTriangle%2,vertexIDInTriangle/2);
  float scale = 1/6.;
  vec2 triangleOffset = vec2(triangleID*scale,0);
  gl_Position = vec4(vertexPosition*scale+triangleOffset,1,1);
  vDirection = triangleID;
}).";

std::string fSrc = R".(
#version 450
out vec4 fColor;
layout(binding=0)uniform usamplerCube cube;
flat in uint vDirection;
void main(){
  vec3 directions[6]={
    vec3(-1,+0,+0),vec3(+1,+0,+0),
    vec3(+0,-1,+0),vec3(+0,+1,+0),
    vec3(+0,+0,-1),vec3(+0,+0,+1)
  };
  fColor=texture(cube,directions[vDirection]);
}
).";

int main(int,char*[]){
  auto mainLoop = make_shared<SDLMainLoop>();
  auto window = make_shared<SDLWindow>();

  window->createContext("rendering");
  mainLoop->addWindow("mainWindow", window);

  ge::gl::init();
  setHighDebugMessage();

  auto vs = make_shared<Shader>(GL_VERTEX_SHADER, vSrc);
  auto fs = make_shared<Shader>(GL_FRAGMENT_SHADER, fSrc);
  auto program = make_shared<Program>(vs, fs);
  auto vao = make_shared<VertexArray>();

  auto tex = make_shared<Texture>(GL_TEXTURE_CUBE_MAP,GL_RGBA8UI,1,1,1);
  for(uint32_t i=0;i<6;++i){
    uint32_t color = 0xff000000+0xff*(((i+1)>>0)&1)+0xff00*(((i+1)>>1)&1)+0xff0000*(((i+1)>>2)&1);
    tex->setData2D(&color,GL_RGBA_INTEGER,GL_UNSIGNED_BYTE,0,GL_TEXTURE_CUBE_MAP_POSITIVE_X+i);
  }

  mainLoop->setIdleCallback([&]() {
    glClear(GL_COLOR_BUFFER_BIT);
    program->use();
    vao->bind();
    tex->bind(0);
    glDrawArrays(GL_TRIANGLES, 0, 3*6);
    window->swap();
  });


  std::map<GLenum,std::string>const internalFormats = {
    {GL_R8,"GL_R8"},
    {GL_R8_SNORM,"GL_R8_SNORM"},
    {GL_R16,"GL_R16"},
    {GL_R16_SNORM,"GL_R16_SNORM"},
    {GL_RG8,"GL_RG8"},
    {GL_RG8_SNORM,"GL_RG8_SNORM"},
    {GL_RG16,"GL_RG16"},
    {GL_RG16_SNORM,"GL_RG16_SNORM"},
    {GL_R3_G3_B2,"GL_R3_G3_B2"},
    {GL_RGB4,"GL_RGB4"},
    {GL_RGB5,"GL_RGB5"},
    {GL_RGB8,"GL_RGB8"},
    {GL_RGB8_SNORM,"GL_RGB8_SNORM"},
    {GL_RGB10,"GL_RGB10"},
    {GL_RGB12,"GL_RGB12"},
    {GL_RGB16_SNORM,"GL_RGB16_SNORM"},
    {GL_RGBA2,"GL_RGBA2"},
    {GL_RGBA4,"GL_RGBA4"},
    {GL_RGB5_A1,"GL_RGB5_A1"},
    {GL_RGBA8,"GL_RGBA8"},
    {GL_RGBA8_SNORM,"GL_RGBA8_SNORM"},
    {GL_RGB10_A2,"GL_RGB10_A2"},
    {GL_RGB10_A2UI,"GL_RGB10_A2UI"},
    {GL_RGBA12,"GL_RGBA12"},
    {GL_RGBA16,"GL_RGBA16"},
    {GL_SRGB8,"GL_SRGB8"},
    {GL_SRGB8_ALPHA8,"GL_SRGB8_ALPHA8"},
    {GL_R16F,"GL_R16F"},
    {GL_RG16F,"GL_RG16F"},
    {GL_RGB16F,"GL_RGB16F"},
    {GL_RGBA16F,"GL_RGBA16F"},
    {GL_R32F,"GL_R32F"},
    {GL_RG32F,"GL_RG32F"},
    {GL_RGB32F,"GL_RGB32F"},
    {GL_RGBA32F,"GL_RGBA32F"},
    {GL_R11F_G11F_B10F,"GL_R11F_G11F_B10F"},
    {GL_RGB9_E5,"GL_RGB9_E5"},
    {GL_R8I,"GL_R8I"},
    {GL_R8UI,"GL_R8UI"},
    {GL_R16I,"GL_R16I"},
    {GL_R16UI,"GL_R16UI"},
    {GL_R32I,"GL_R32I"},
    {GL_R32UI,"GL_R32UI"},
    {GL_RG8I,"GL_RG8I"},
    {GL_RG8UI,"GL_RG8UI"},
    {GL_RG16I,"GL_RG16I"},
    {GL_RG16UI,"GL_RG16UI"},
    {GL_RG32I,"GL_RG32I"},
    {GL_RG32UI,"GL_RG32UI"},
    {GL_RGB8I,"GL_RGB8I"},
    {GL_RGB8UI,"GL_RGB8UI"},
    {GL_RGB16I,"GL_RGB16I"},
    {GL_RGB16UI,"GL_RGB16UI"},
    {GL_RGB32I,"GL_RGB32I"},
    {GL_RGB32UI,"GL_RGB32UI"},
    {GL_RGBA8I,"GL_RGBA8I"},
    {GL_RGBA8UI,"GL_RGBA8UI"},
    {GL_RGBA16I,"GL_RGBA16I"},
    {GL_RGBA16UI,"GL_RGBA16UI"},
    {GL_RGBA32I,"GL_RGBA32I"},
    {GL_RGBA32UI,"GL_RGBA32UI"},
    {GL_COMPRESSED_RED,"GL_COMPRESSED_RED"},
    {GL_COMPRESSED_RG,"GL_COMPRESSED_RG"},
    {GL_COMPRESSED_RGB,"GL_COMPRESSED_RGB"},
    {GL_COMPRESSED_RGBA,"GL_COMPRESSED_RGBA"},
    {GL_COMPRESSED_SRGB,"GL_COMPRESSED_SRGB"},
    {GL_COMPRESSED_SRGB_ALPHA,"GL_COMPRESSED_SRGB_ALPHA"},
    {GL_COMPRESSED_RED_RGTC1,"GL_COMPRESSED_RED_RGTC1"},
    {GL_COMPRESSED_SIGNED_RED_RGTC1,"GL_COMPRESSED_SIGNED_RED_RGTC1"},
    {GL_COMPRESSED_RG_RGTC2,"GL_COMPRESSED_RG_RGTC2"},
    {GL_COMPRESSED_SIGNED_RG_RGTC2,"GL_COMPRESSED_SIGNED_RG_RGTC2"},
    {GL_COMPRESSED_RGBA_BPTC_UNORM,"GL_COMPRESSED_RGBA_BPTC_UNORM"},
    {GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM,"GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM"},
    {GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT,"GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT"},
    {GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT,"GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT"},
    {GL_DEPTH_COMPONENT,"GL_DEPTH_COMPONENT"},
    {GL_DEPTH_STENCIL,"GL_DEPTH_STENCIL"},
    {GL_RED,"GL_RED"},
    {GL_RG,"GL_RG"},
    {GL_RGB,"GL_RGB"},
    {GL_RGBA,"GL_RGBA"},
  }; 

  std::map<GLenum,std::string>const formats = {
    {GL_RED,"GL_RED"},
    {GL_RG,"GL_RG"},
    {GL_RGB,"GL_RGB"},
    {GL_RGBA,"GL_RGBA"},
    {GL_RED_INTEGER,"GL_RED_INTEGER"},
    {GL_RG_INTEGER,"GL_RG_INTEGER"},
    {GL_RGB_INTEGER,"GL_RGB_INTEGER"},
    {GL_RGBA_INTEGER,"GL_RGBA_INTEGER"},
  };

  std::map<GLenum,std::string>const types = {
    {GL_UNSIGNED_BYTE,"GL_UNSIGNED_BYTE"},
    {GL_BYTE,"GL_BYTE"},
    {GL_UNSIGNED_SHORT,"GL_UNSIGNED_SHORT"},
    {GL_SHORT,"GL_SHORT"},
    {GL_UNSIGNED_INT,"GL_UNSIGNED_INT"},
    {GL_INT,"GL_INT"},
    {GL_FLOAT,"GL_FLOAT"},
    {GL_UNSIGNED_BYTE_3_3_2,"GL_UNSIGNED_BYTE_3_3_2"},
    {GL_UNSIGNED_BYTE_2_3_3_REV,"GL_UNSIGNED_BYTE_2_3_3_REV"},
    {GL_UNSIGNED_SHORT_5_6_5,"GL_UNSIGNED_SHORT_5_6_5"},
    {GL_UNSIGNED_SHORT_5_6_5_REV,"GL_UNSIGNED_SHORT_5_6_5_REV"},
    {GL_UNSIGNED_SHORT_4_4_4_4,"GL_UNSIGNED_SHORT_4_4_4_4"},
    {GL_UNSIGNED_SHORT_4_4_4_4_REV,"GL_UNSIGNED_SHORT_4_4_4_4_REV"},
    {GL_UNSIGNED_SHORT_5_5_5_1,"GL_UNSIGNED_SHORT_5_5_5_1"},
    {GL_UNSIGNED_SHORT_1_5_5_5_REV,"GL_UNSIGNED_SHORT_1_5_5_5_REV"},
    {GL_UNSIGNED_INT_8_8_8_8,"GL_UNSIGNED_INT_8_8_8_8"},
    {GL_UNSIGNED_INT_8_8_8_8_REV,"GL_UNSIGNED_INT_8_8_8_8_REV"},
    {GL_UNSIGNED_INT_10_10_10_2,"GL_UNSIGNED_INT_10_10_10_2"},
    {GL_UNSIGNED_INT_2_10_10_10_REV,"GL_UNSIGNED_INT_2_10_10_10_REV"},
  };

#define TRY_TEXTURE_FORMAT(internal,format,type)\
  do{\
    GLuint tex;\
    glGetError();\
    glCreateTextures(GL_TEXTURE_2D,1,&tex);\
    glTextureImage2DEXT(tex,GL_TEXTURE_2D,0,internal,1,1,0,format,type,nullptr);\
    glDeleteTextures(1,&tex);\
    if(glGetError() !=  GL_NO_ERROR)\
      std::cerr << internalFormats.at(internal) << " " << formats.at(format) << " " << types.at(type) << " - failed" << std::endl;\
    else\
      std::cerr << internalFormats.at(internal) << " " << formats.at(format) << " " << types.at(type) << " - passed" << std::endl;\
    break;\
  }while(true)


  for(auto const&i:internalFormats)
    for(auto const&f:formats)
      for(auto const&t:types)
        TRY_TEXTURE_FORMAT(i.first,f.first,t.first);
  //TRY_TEXTURE_FORMAT(GL_RGBA8UI,GL_RED_INTEGER,GL_INT);
  //Texture a;
  //a.create(GL_TEXTURE_2D,GL_DEPTH_COMPONENT24,1,1024,1024);
  (*mainLoop)();
  return 0;
}

