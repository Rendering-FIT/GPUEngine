#include<limits>
#include<string>
#include<geGL/geGL.h>
#include<geAd/SDLWindow/SDLWindow.h>
#include<algorithm>
#include<iomanip>
#include<geCore/Dtemplates.h>
#include<geGL/OpenGLUtil.h>
#include<geUtil/ArgumentObject.h>

const size_t GIGA                  = 1<<30     ;
const size_t NANOSECONDS_IN_SECOND = 1000000000;
const size_t COMPUTE_UNITS         = 20        ;
const size_t WAVEFRONT_SIZE        = 64        ;

size_t nofDigits(size_t number,size_t base = 10){
  size_t digs=1;
  while(number>base-1){
    number/=base;
    digs++;
  }
  return digs;
}

double median(std::function<double()>const&fce,size_t iteration = 10){
  assert(iteration>0);
  std::vector<double>values;
  for(size_t i=0;i<iteration;++i)
    values.push_back(fce());
  std::sort(values.begin(),values.end());
  return values.at(iteration/2);
}

double basicBufferTest(
    size_t      nofThreads           = 2048   ,
    size_t      workgroupSize        = 64     ,
    std::string baseType             = "float",
    size_t      nofComponents        = 1      ,
    size_t      nofElementsPerThread = 32     ){
  const size_t nofIterations = 50;

  size_t byteSizeOfBaseType = 4;
  if(baseType == "float")byteSizeOfBaseType = sizeof(float   );
  if(baseType == "int"  )byteSizeOfBaseType = sizeof(int32_t );
  if(baseType == "uint" )byteSizeOfBaseType = sizeof(uint32_t);

  const std::string compSrc = R".(
#ifndef BASE_TYPE
#define BASE_TYPE float
#endif//BASE_TYPE

#ifndef NOF_COMPONENTS
#define NOF_COMPONENTS 1
#endif//NOF_COMPONENTS

#ifndef ELEMENTS_PER_THREAD
#define ELEMENTS_PER_THREAD 1
#endif//ELEMENTS_PER_THREAD

#define JOIN__(x,y) x##y
#define JOIN_(x,y) JOIN__(x,y)
#define JOIN(x,y) JOIN_(x,y)
#define TYPE_float1 float
#define TYPE_float2 vec2
#define TYPE_float3 vec3
#define TYPE_float4 vec4
#define TYPE_int1 int
#define TYPE_int2 ivec2
#define TYPE_int3 ivec3
#define TYPE_int4 ivec4
#define TYPE_uint1 uint
#define TYPE_uint2 uvec2
#define TYPE_uint3 uvec3
#define TYPE_uint4 uvec4

float addComponents(float a){return a              ;}
float addComponents(vec2  a){return a.x+a.y        ;}
float addComponents(vec3  a){return a.x+a.y+a.z    ;}
float addComponents(vec4  a){return a.x+a.y+a.z+a.w;}
int   addComponents(int   a){return a              ;}
int   addComponents(ivec2 a){return a.x+a.y        ;}
int   addComponents(ivec3 a){return a.x+a.y+a.z    ;}
int   addComponents(ivec4 a){return a.x+a.y+a.z+a.w;}
uint  addComponents(uint  a){return a              ;}
uint  addComponents(uvec2 a){return a.x+a.y        ;}
uint  addComponents(uvec3 a){return a.x+a.y+a.z    ;}
uint  addComponents(uvec4 a){return a.x+a.y+a.z+a.w;}

#define TYPE JOIN(TYPE_,JOIN(BASE_TYPE,NOF_COMPONENTS))

layout(std430,binding=0)buffer Data{TYPE readBuffer[];};
layout(local_size_x=WORKGROUP_SIZE)in;
void main(){
  BASE_TYPE data = 0;
  for(uint element=0;element<ELEMENTS_PER_THREAD;++element)
    data += addComponents(readBuffer[gl_WorkGroupID.x*ELEMENTS_PER_THREAD*gl_WorkGroupSize.x+gl_LocalInvocationID.x+gl_WorkGroupSize.x*element]);
  if(data==123)
    readBuffer[gl_GlobalInvocationID.x]=TYPE(1);
}).";
  auto program = std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(
        GL_COMPUTE_SHADER,
        "#version 450\n",
        ge::gl::Shader::define("WORKGROUP_SIZE"     ,int(workgroupSize)       ),
        ge::gl::Shader::define("BASE_TYPE"          ,baseType                 ),
        ge::gl::Shader::define("ELEMENTS_PER_THREAD",int(nofElementsPerThread)),
        ge::gl::Shader::define("NOF_COMPONENTS"     ,int(nofComponents)       ),
        compSrc));
  auto data = std::make_shared<ge::gl::Buffer>(nofThreads*nofElementsPerThread*nofComponents*byteSizeOfBaseType,nullptr,GL_DYNAMIC_COPY);
  auto query = std::make_shared<ge::gl::AsynchronousQuery>(GL_TIME_ELAPSED,GL_QUERY_RESULT,ge::gl::AsynchronousQuery::UINT64);
  auto gl = ge::gl::getDefaultContext();
  program->use();

  data->bindBase(GL_SHADER_STORAGE_BUFFER,0);
  gl->glFinish();
  query->begin();
  for(size_t i=0;i<nofIterations;++i)
    gl->glDispatchCompute(GLuint(ge::core::divRoundUp(nofThreads,workgroupSize)),1,1);
  query->end();
  gl->glFinish();
  auto elapsedTime = query->getui64();

  double throughput=
    double(nofIterations)*
    double(byteSizeOfBaseType)*
    double(nofComponents)*
    double(nofThreads)*
    double(nofElementsPerThread)/
    double(elapsedTime)*
    double(NANOSECONDS_IN_SECOND);
  return throughput/GIGA;
}

double basicTextureTest(
    GLenum internalFormat,
    size_t WGSX = 8,
    size_t WGSY = 8,
    size_t texelsPerThreadX = 4,
    size_t texelsPerThreadY = 4,
    size_t dispatchSizeX = 2048,
    size_t dispatchSizeY = 2048){
  const size_t ITERATIONS = 100;

  const std::string compSrc = R".(
#ifndef BASE_TYPE
#define BASE_TYPE float
#endif//BASE_TYPE

#ifndef NOF_CHANNELS
#define NOF_CHANNELS 1
#endif//NOF_CHANNELS

#ifndef BIT_SIZE
#define BIT_SIZE 32
#endif//BIT_SIZE

#ifndef TEXELS_PER_THREAD
#define TEXELS_PER_THREAD uvec2(1,1)
#endif//TEXELS_PER_THREAD

#define JOIN__(x,y) x##y
#define JOIN_(x,y) JOIN__(x,y)
#define JOIN(x,y) JOIN_(x,y)
#define CHANNELS_1 r
#define CHANNELS_2 rg
#define CHANNELS_4 rgba
#define TYPE_SUFFIX_float f
#define TYPE_SUFFIX_int   i
#define TYPE_SUFFIX_uint  ui
#define TYPE_float1 float
#define TYPE_float2 vec2
#define TYPE_float3 vec3
#define TYPE_float4 vec4
#define TYPE_int1 int
#define TYPE_int2 ivec2
#define TYPE_int3 ivec3
#define TYPE_int4 ivec4
#define TYPE_uint1 uint
#define TYPE_uint2 uvec2
#define TYPE_uint3 uvec3
#define TYPE_uint4 uvec4
#define IMAGE_TYPE_float image2D
#define IMAGE_TYPE_int iimage2D
#define IMAGE_TYPE_uint uimage2D
#define FULL_VECTOR_TYPE JOIN(TYPE_,JOIN(BASE_TYPE,4)) 
#define TYPE JOIN(TYPE_,JOIN(BASE_TYPE,NOF_CHANNELS))
#define FORMAT JOIN(JOIN(CHANNELS_,NOF_CHANNELS),JOIN(BIT_SIZE,JOIN(TYPE_SUFFIX_,BASE_TYPE)))
layout(local_size_x=WGSX,local_size_y=WGSY)in;
layout(FORMAT,binding=0)uniform JOIN(IMAGE_TYPE_,BASE_TYPE) readTexture;
float addComponents(float a){return a              ;}
float addComponents(vec2  a){return a.x+a.y        ;}
float addComponents(vec4  a){return a.x+a.y+a.z+a.w;}
int   addComponents(int   a){return a              ;}
int   addComponents(ivec2 a){return a.x+a.y        ;}
int   addComponents(ivec4 a){return a.x+a.y+a.z+a.w;}
uint  addComponents(uint  a){return a              ;}
uint  addComponents(uvec2 a){return a.x+a.y        ;}
uint  addComponents(uvec4 a){return a.x+a.y+a.z+a.w;}
void main(){
  BASE_TYPE data = 0;
  for(uint j=0;j<TEXELS_PER_THREAD.y;++j)
    for(uint i=0;i<TEXELS_PER_THREAD.x;++i)
      data += addComponents(TYPE(imageLoad(readTexture,ivec2(gl_WorkGroupID.xy*gl_WorkGroupSize.xy*TEXELS_PER_THREAD+gl_LocalInvocationID.xy+gl_WorkGroupSize.xy*uvec2(i,j)))));
  if(data==123)
    imageStore(readTexture,ivec2(gl_GlobalInvocationID.xy),FULL_VECTOR_TYPE(1));
}).";

  std::string baseType = "float";
  size_t nofChannels   = 1;
  size_t bitSize       = 32;
  size_t byteSize      = 8;
  if(std::set<GLenum>({GL_R32F ,GL_RG32F ,GL_RGBA32F ,GL_R16F ,GL_RG16F ,GL_RGBA16F }).count(internalFormat))baseType = "float";
  if(std::set<GLenum>({GL_R32I ,GL_RG32I ,GL_RGBA32I ,GL_R16I ,GL_RG16I ,GL_RGBA16I ,GL_R8I ,GL_RG8I ,GL_RGBA8I }).count(internalFormat))baseType = "int"  ;
  if(std::set<GLenum>({GL_R32UI,GL_RG32UI,GL_RGBA32UI,GL_R16UI,GL_RG16UI,GL_RGBA16UI,GL_R8UI,GL_RG8UI,GL_RGBA8UI}).count(internalFormat))baseType = "uint" ;
  if(std::set<GLenum>({GL_R32F   ,GL_R32I   ,GL_R32UI   ,GL_R16I   ,GL_R16UI   ,GL_R8I   ,GL_R8UI   }).count(internalFormat))nofChannels = 1;
  if(std::set<GLenum>({GL_RG32F  ,GL_RG32I  ,GL_RG32UI  ,GL_RG16I  ,GL_RG16UI  ,GL_RG8I  ,GL_RG8UI  }).count(internalFormat))nofChannels = 2;
  if(std::set<GLenum>({GL_RGBA32F,GL_RGBA32I,GL_RGBA32UI,GL_RGBA16I,GL_RGBA16UI,GL_RGBA8I,GL_RGBA8UI}).count(internalFormat))nofChannels = 4;
  if(std::set<GLenum>({GL_R32F,GL_RG32F,GL_RGBA32F,GL_R32I,GL_RG32I,GL_RGBA32I,GL_R32UI,GL_RG32UI,GL_RGBA32UI}).count(internalFormat))bitSize = 32;
  if(std::set<GLenum>({GL_R16F,GL_RG16F,GL_RGBA16F,GL_R16I,GL_RG16I,GL_RGBA16I,GL_R16UI,GL_RG16UI,GL_RGBA16UI}).count(internalFormat))bitSize = 16;
  if(std::set<GLenum>({GL_R8I ,GL_RG8I ,GL_RGBA8I ,GL_R8UI,GL_RG8UI,GL_RGBA8UI}).count(internalFormat))bitSize = 8;

  auto program = std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(
        GL_COMPUTE_SHADER,
        "#version 450\n",
        ge::gl::Shader::define("WGSX"             ,int(WGSX)                                  ),
        ge::gl::Shader::define("WGSY"             ,int(WGSY)                                  ),
        ge::gl::Shader::define("BASE_TYPE"        ,baseType                                   ),
        ge::gl::Shader::define("NOF_CHANNELS"     ,int(nofChannels)                           ),
        ge::gl::Shader::define("BIT_SIZE"         ,int(bitSize)                               ),
        ge::gl::Shader::define("TEXELS_PER_THREAD",int(texelsPerThreadX),int(texelsPerThreadY)),
        compSrc));
  auto texture = std::make_shared<ge::gl::Texture>(GL_TEXTURE_2D,internalFormat,1,GLsizei(dispatchSizeX*texelsPerThreadX),GLsizei(dispatchSizeY*texelsPerThreadY));
  auto query = std::make_shared<ge::gl::AsynchronousQuery>(GL_TIME_ELAPSED,GL_QUERY_RESULT,ge::gl::AsynchronousQuery::UINT64);
  auto gl = ge::gl::getDefaultContext();
  program->use();

  texture->bindImage(0,0);
  gl->glFinish();
  query->begin();
  for(size_t i=0;i<ITERATIONS;++i){
    gl->glDispatchCompute(
        GLuint(ge::core::divRoundUp(dispatchSizeX,WGSX)),
        GLuint(ge::core::divRoundUp(dispatchSizeY,WGSY)),
        1);
  }
  query->end();
  auto elapsedTime = query->getui64();

  double throughput=
    double(ITERATIONS)*
    double(bitSize)/double(byteSize)*
    double(nofChannels)*
    double(texelsPerThreadX*texelsPerThreadY)*
    double(dispatchSizeX*dispatchSizeY)/
    double(elapsedTime)*
    double(NANOSECONDS_IN_SECOND);
  return throughput/GIGA;
}

int main(int argc,char*argv[]){
  auto window   = std::make_shared<ge::ad::SDLWindow>(512,512);
  window->createContext("rendering",450u,ge::ad::SDLWindow::CORE,ge::ad::SDLWindow::DEBUG);
  ge::gl::init(SDL_GL_GetProcAddress);
  ge::gl::setHighDebugMessage();

  auto args = std::make_shared<ge::util::ArgumentObject>(argc-1,argv+1);
  if(args->isPresent("--help")||args->isPresent("-h")){
    std::cout<<"--help -h - prints help"<<std::endl;
    std::cout<<"Argument section for buffer test begins with --bufferStart and ends with --bufferEnd"<<std::endl;
    std::cout<<"Argument in buffer test section contains:"<<std::endl;
    std::cout<<"  --nofThreads 1048576 - number of active threads"<<std::endl;
    std::cout<<"  --minimalWorkgroupSize 64 - minimal size of workgroup"<<std::endl;
    std::cout<<"  --maximalWorkgroupSize 1024 - maximal size of workgroup"<<std::endl;
    std::cout<<"  --minimalNofComponents 1 - minimal number of components of vector"<<std::endl;
    std::cout<<"  --maximalNofComponents 4 - maximal number of components of vector"<<std::endl;
    std::cout<<"  --bufferTypeStart --bufferTypeEnd buffer type section containing float, int, uint"<<std::endl;
    return EXIT_SUCCESS;
  }
  size_t buffer_nofThreads                  = args->getArgi("--bufferStart","--bufferEnd","--nofThreads"                 ,"1048576");
  size_t buffer_minimalWorkgroupSize        = args->getArgi("--bufferStart","--bufferEnd","--minimalWorkgroupSize"       ,"64"     );
  size_t buffer_maximalWorkgroupSize        = args->getArgi("--bufferStart","--bufferEnd","--maximalWorkgroupSize"       ,"1024"   );
  size_t buffer_minimalNofElementsPerThread = args->getArgi("--bufferStart","--bufferEnd","--minimalNofElementsPerThread","1"      );
  size_t buffer_maximalNofElementsPerThread = args->getArgi("--bufferStart","--bufferEnd","--maximalNofElementsPerThread","16"     );
  size_t buffer_minimalNofComponents        = args->getArgi("--bufferStart","--bufferEnd","--minimalNofComponents"       ,"1"      );
  size_t buffer_maximalNofComponents        = args->getArgi("--bufferStart","--bufferEnd","--minimalNofComponents"       ,"4"      );
  std::vector<std::string>buffer_baseTypes;
  for(size_t i=0;i<args->getContextLength("--bufferTypeStart","--bufferTypeEnd");++i)
    buffer_baseTypes.push_back(args->getArg("--bufferTypeStart","--bufferTypeEnd",i));

  {
    std::vector<std::string> baseTypes = {"float","int","uint"};
    for(auto const&baseType:baseTypes)
      for(size_t nofComponents = buffer_minimalNofComponents; nofComponents <= buffer_maximalNofComponents; nofComponents <<= 1)
        for(size_t elementsPerThread = buffer_minimalNofElementsPerThread; elementsPerThread <= buffer_maximalNofElementsPerThread; elementsPerThread <<= 1)
          for(size_t workgroupSize = buffer_minimalWorkgroupSize; workgroupSize <= buffer_maximalWorkgroupSize; workgroupSize <<= 1)
          {
            auto bandwidth = median(std::bind(basicBufferTest,buffer_nofThreads,workgroupSize,baseType,nofComponents,elementsPerThread));
            std::cout<<std::scientific<< std::setprecision(6)<<bandwidth<<" GB/second";
            std::cout<<" baseType: "         <<std::setfill(' ')<<std::setw(5)<<baseType<<nofComponents;
            std::cout<<" elementsPerThread: "<<std::setfill(' ')<<std::setw(int32_t(nofDigits(buffer_maximalNofElementsPerThread)))<<elementsPerThread;
            std::cout<<" workgroupSize: "    <<std::setfill(' ')<<std::setw(int32_t(nofDigits(buffer_maximalWorkgroupSize)))<<workgroupSize<<std::endl;
          }
  }

  {
    size_t const minimalWorkgroupSize      = 64  ;
    size_t const maximalWorkgroupSize      = 1024;
    size_t const minimalNofTexelsPerThread = 1   ;
    size_t const maximalNofTexelsPerThread = 16  ;
    size_t const dispatchSizeX             = 1024;
    size_t const dispatchSizeY             = 1024;
    auto const internalFormats = {
      /*
      GL_R11F_G11F_B10F,
      GL_RGB10_A2,
      GL_RGBA16_SNORM,
      GL_RGBA8_SNORM,
      GL_RG16_SNORM,
      GL_RG8_SNORM,
      GL_R16_SNORM,
      GL_R8_SNORM,
      GL_RGB10_A2UI,*/
//*
      GL_R32F ,GL_RG32F ,GL_RGBA32F ,
      GL_R16F ,GL_RG16F ,GL_RGBA16F ,
      GL_R32I ,GL_RG32I ,GL_RGBA32I ,
      GL_R16I ,GL_RG16I ,GL_RGBA16I ,
      GL_R8I  ,GL_RG8I  ,GL_RGBA8I  ,
      GL_R32UI,GL_RG32UI,GL_RGBA32UI,
      GL_R16UI,GL_RG16UI,GL_RGBA16UI,
      GL_R8UI ,GL_RG8UI ,GL_RGBA8UI ,
      // */
    };
    for(GLenum const&internalFormat:internalFormats)
      for(size_t workgroupSize=minimalWorkgroupSize;workgroupSize<=maximalWorkgroupSize;workgroupSize<<=1)
        for(size_t workgroupSizeX=1;workgroupSizeX<=workgroupSize;workgroupSizeX<<=1)
          for(size_t texelsPerThread=minimalNofTexelsPerThread;texelsPerThread<=maximalNofTexelsPerThread;texelsPerThread<<=1)
            for(size_t texelsPerThreadX=1;texelsPerThreadX<=texelsPerThread;texelsPerThreadX<<=1){
              size_t workgroupSizeY   = workgroupSize   / workgroupSizeX  ;
              size_t texelsPerThreadY = texelsPerThread / texelsPerThreadX;
              auto bandwidth = median(std::bind(basicTextureTest,internalFormat,workgroupSizeX,workgroupSizeY,texelsPerThreadX,texelsPerThreadY,dispatchSizeX,dispatchSizeY));
              std::cout<<std::scientific<< std::setprecision(6)<<bandwidth<<" GB/second ";
              std::cout<<"internalFormat("<<std::left<<std::setw(12)<<std::setfill(' ')<<ge::gl::translateInternalFormat(internalFormat)<<") ";
              std::cout<<"workgroupSize("<<std::setfill(' ')<<std::setw(int32_t(nofDigits(maximalWorkgroupSize)))<<workgroupSize<<")(";
              std::cout<<std::right<<std::setfill(' ')<<std::setw(int32_t(nofDigits(maximalWorkgroupSize)))<<workgroupSizeX
                <<" x "<<std::setfill(' ')<<std::setw(int32_t(nofDigits(maximalWorkgroupSize)))<<workgroupSizeY<<") ";
              std::cout<<"texelsPerThread("<<std::setfill(' ')<<std::setw(int32_t(nofDigits(maximalNofTexelsPerThread)))<<texelsPerThread<<")(";
              std::cout<<std::setfill(' ')<<std::setw(int32_t(nofDigits(maximalNofTexelsPerThread)))<<texelsPerThreadX
                <<" x "<<std::setfill(' ')<<std::setw(int32_t(nofDigits(maximalNofTexelsPerThread)))<<texelsPerThreadY<<")"<<std::endl;
            }
  }
  return EXIT_SUCCESS;
}

