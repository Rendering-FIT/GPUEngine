#include<geGL/TextureObject.h>
/*
   GLint RenderbufferSamples=13;
   GLint textureWidth=1234,textureHeight=1234,textureDepth=1234;
   GLint textureFixedSampleLocations=1234;
   GLint textureCompressed=1234;
   GLint textureCompressedImageSize=1234;
   GLint textureImmutableFormat=1234;
   GLint textureSamples=1234;
   GLint textureSwizzleR=1234,textureSwizzleG=1234,textureSwizzleB=1234,textureSwizzleA=1234;
   GLint textureMaxLevel=1234;
   GLint textureBaseLevel=1234;
   GLint textureDepthStencilTextureMode=1234;
   GLint textureMagFilter=1234,textureMinFilter=1234;
   GLint textureMaxLod=1234,textureMinLod=1234;
   GLint textureCompareFunc=1234,textureCompareMode=1234;
   GLfloat textureLodBias=1234;
   GLfloat textureBorderColor[4]={1234,1234,1234,1234};
   GLint   textureWrapS=1234,textureWrapT=1234,textureWrapR=1234;
   glGetTexLevelParameteriv(GL_TEXTURE_2D,0,GL_TEXTURE_WIDTH                 ,&textureWidth );
   glGetTexLevelParameteriv(GL_TEXTURE_2D,0,GL_TEXTURE_HEIGHT                ,&textureHeight);
   glGetTexLevelParameteriv(GL_TEXTURE_2D,0,GL_TEXTURE_DEPTH                 ,&textureDepth );
   glGetTexLevelParameteriv(GL_TEXTURE_2D,0,GL_TEXTURE_FIXED_SAMPLE_LOCATIONS,&textureFixedSampleLocations );
   glGetTexLevelParameteriv(GL_TEXTURE_2D,0,GL_TEXTURE_COMPRESSED            ,&textureCompressed );
//glGetTexLevelParameteriv(GL_TEXTURE_2D,0,GL_TEXTURE_COMPRESSED_IMAGE_SIZE ,&textureCompressedImageSize);
glGetTexParameteriv(GL_TEXTURE_2D,GL_TEXTURE_IMMUTABLE_FORMAT      ,&textureImmutableFormat );
glGetTexLevelParameteriv(GL_TEXTURE_2D,0,GL_TEXTURE_SAMPLES               ,&textureSamples );
glGetTexParameteriv(GL_TEXTURE_2D,GL_TEXTURE_SWIZZLE_R             ,&textureSwizzleR);
glGetTexParameteriv(GL_TEXTURE_2D,GL_TEXTURE_SWIZZLE_G             ,&textureSwizzleG);
glGetTexParameteriv(GL_TEXTURE_2D,GL_TEXTURE_SWIZZLE_B             ,&textureSwizzleB);
glGetTexParameteriv(GL_TEXTURE_2D,GL_TEXTURE_SWIZZLE_A             ,&textureSwizzleA);
glGetTexParameteriv(GL_TEXTURE_2D,GL_TEXTURE_MAX_LEVEL             ,&textureMaxLevel);
glGetTexParameteriv(GL_TEXTURE_2D,GL_TEXTURE_BASE_LEVEL            ,&textureBaseLevel);
//glGetTexParameteriv(GL_TEXTURE_2D,GL_DEPTH_STENCIL_TEXTURE_MODE    ,&textureDepthStencilTextureMode);
//glGetTexParameterIiv(GL_TEXTURE_2D,GL_DEPTH_STENCIL_TEXTURE_MODE   ,&textureDepthStencilTextureMode);
glGetTexParameteriv(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,&textureMagFilter);
glGetTexParameteriv(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,&textureMinFilter);
glGetTexParameteriv(GL_TEXTURE_2D,GL_TEXTURE_MAX_LOD,&textureMaxLod);
glGetTexParameteriv(GL_TEXTURE_2D,GL_TEXTURE_MIN_LOD,&textureMinLod);
glGetTexParameterfv(GL_TEXTURE_2D,GL_TEXTURE_BORDER_COLOR,textureBorderColor);
glGetTexParameteriv(GL_TEXTURE_2D,GL_TEXTURE_COMPARE_FUNC,&textureCompareFunc);
glGetTexParameteriv(GL_TEXTURE_2D,GL_TEXTURE_COMPARE_MODE,&textureCompareMode);
glGetTexParameterfv(GL_TEXTURE_2D,GL_TEXTURE_LOD_BIAS,&textureLodBias);
glGetTexParameteriv(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,&textureWrapS);
glGetTexParameteriv(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,&textureWrapT);
glGetTexParameteriv(GL_TEXTURE_2D,GL_TEXTURE_WRAP_R,&textureWrapR);






std::cerr<<"width:                  "<<textureWidth               <<std::endl;
std::cerr<<"height:                 "<<textureHeight              <<std::endl;
std::cerr<<"depth:                  "<<textureDepth               <<std::endl;
std::cerr<<"fixedSampleLocation:    "<<textureFixedSampleLocations<<std::endl;
std::cerr<<"compressed:             "<<textureCompressed          <<std::endl;
std::cerr<<"compressedImageSize:    "<<textureCompressedImageSize <<std::endl;
std::cerr<<"immutableFormat:        "<<textureImmutableFormat     <<std::endl;
std::cerr<<"samples:                "<<textureSamples             <<std::endl;
std::cerr<<"swizzleR:               "<<translateTextureSwizzle(textureSwizzleR)<<std::endl;
std::cerr<<"swizzleG:               "<<translateTextureSwizzle(textureSwizzleG)<<std::endl;
std::cerr<<"swizzleB:               "<<translateTextureSwizzle(textureSwizzleB)<<std::endl;
std::cerr<<"swizzleA:               "<<translateTextureSwizzle(textureSwizzleA)<<std::endl;
std::cerr<<"maxLevel:               "<<textureMaxLevel <<std::endl;
std::cerr<<"baseLevel:              "<<textureBaseLevel<<std::endl;
std::cerr<<"depthStencilTextureMode:"<<textureDepthStencilTextureMode          <<std::endl;
std::cerr<<"magFilter:              "<<translateTextureFilter(textureMagFilter)<<std::endl;
std::cerr<<"minFilter:              "<<translateTextureFilter(textureMinFilter)<<std::endl;
std::cerr<<"maxLod:                 "<<textureMaxLod<<std::endl;
std::cerr<<"minLod:                 "<<textureMinLod<<std::endl;
std::cerr<<"borderColor:            "<<textureBorderColor[0]<<" "<<textureBorderColor[1]<<" "<<textureBorderColor[2]<<" "<<textureBorderColor[3]<<std::endl;
std::cerr<<"compareFunc:            "<<translateTextureCompareFunc(textureCompareFunc)<<std::endl;
std::cerr<<"compareMode:            "<<translateTextureCompareMode(textureCompareMode)<<std::endl;
std::cerr<<"lodBias:                "<<textureLodBias                   <<std::endl;
std::cerr<<"wrapS:                  "<<translateTextureWrap(textureWrapS)<<std::endl;
std::cerr<<"wrapT:                  "<<translateTextureWrap(textureWrapT)<<std::endl;
std::cerr<<"wrapR:                  "<<translateTextureWrap(textureWrapR)<<std::endl;
glGetRenderbufferParameteriv(GL_RENDERBUFFER,GL_RENDERBUFFER_SAMPLES,&RenderbufferSamples);
std::cerr<<"D->RBO_Stencil Samples: "<<RenderbufferSamples<<std::endl;

*/
/*
glTexSubImage3D glTexImage3D

glTexStorage3D
glCompressedTexSubImage3D glCompressedTexImage3D
glTexImage3DMultisample
glTexStorage3DMultisample


glTextureSubImage3D
glTextureStorage3D
glCompressedTextureSubImage3D
glTextureStorage3DMultisample


glTexImage2D
glTexImage1D
glTexSubImage2D
glTexSubImage1D

glTextureSubImage2D
glTextureSubImage1D
glTextureStorage2D
glTextureStorage1D
glTextureStorage2DMultisample

glTexImage2DMultisample
glTexStorage2D
glTexStorage1D
glTexStorage2DMultisample
glCompressedTexImage2D
glCompressedTexImage1D
glCompressedTexSubImage2D
glCompressedTexSubImage1D
glCompressedTextureSubImage2D
glCompressedTextureSubImage1D



{Tex,Texture}{1D,2D,3D}{Sub,€}{Storage,€}{Multisample,€}{Compressed,€}

Texture(
    GLenum      target                        ,
    GLsizei     width                         ,
    GLsizei     height                        ,
    GLsizei     depth                         ,
    GLint       internalFormat                ,
    GLint       levels              = 0       ,
    GLenum      type                = GL_FLOAT,
    GLenum      format              = GL_RGBA ,
    const void *data                = NULL    ,
    GLsizei     imageSize           = 0       ,
    GLsizei     samples             = 1       ,
    GLboolean   fixedSampleLocation = GL_FALSE);

//standard variant
Texture(
    GLsizei       width                         ,
    GLsizei       height                        ,
    GLsizei       depth                         ,
    GLint         internalFormat                ,
    GLenum        target         = GL_TEXTURE_2D,
    GLint         level          = 0            ,
    GLenum        type           = GL_FLOAT     ,
    GLenum        format         = GL_RGBA      ,
    const GLvoid *data           = NULL         );

//multisample variant
Texture(
    GLsizei   width                         ,
    GLsizei   height                        ,
    GLsizei   depth                         ,
    GLint     internalFormat                ,
    GLsizei   samples             = 0       ,
    GLboolean fixedSampleLocation = GL_FALSE);

//compressed variant
Texture(
    GLsizei     width                         ,
    GLsizei     height                        ,
    GLsizei     depth                         ,
    GLint       internalFormat                ,
    GLenum      target                        ,
    GLint       levels              = 0       ,
    GLenum      type                = GL_FLOAT,
    GLenum      format              = GL_RGBA ,
    const void *data                = NULL    ,
    GLsizei     imageSize           = 0       );


//Proc nedavat do konstruktoru data
//nektere typy textur nechteji data (multisampling)
//textury jsou casto mipmapovane data nahrajou jen nejvetsi rozliseni
//moc parametru na konstruktor
//immutable storage
//cube mapy jsou dalsi priklad
//

data    == NULL -> levels == NOF_LEVELS & glTexStorage2D/glTextureStorage2D
samples == 1    -> glTexStorage2DMultisample/glTextureStorage2DMultisample

// */


using namespace ge::gl;

GLenum ge::gl::textureTarget2Binding(GLenum target){
  switch(target){
    case GL_TEXTURE_1D                  :return GL_TEXTURE_BINDING_1D                  ;
    case GL_TEXTURE_1D_ARRAY            :return GL_TEXTURE_BINDING_1D_ARRAY            ;
    case GL_TEXTURE_2D                  :return GL_TEXTURE_BINDING_2D                  ;
    case GL_TEXTURE_2D_ARRAY            :return GL_TEXTURE_BINDING_2D_ARRAY            ;
    case GL_TEXTURE_2D_MULTISAMPLE      :return GL_TEXTURE_BINDING_2D_MULTISAMPLE      ;
    case GL_TEXTURE_2D_MULTISAMPLE_ARRAY:return GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY;
    case GL_TEXTURE_3D                  :return GL_TEXTURE_BINDING_3D                  ;
    case GL_TEXTURE_BUFFER              :return GL_TEXTURE_BINDING_BUFFER              ;
    case GL_TEXTURE_CUBE_MAP            :return GL_TEXTURE_BINDING_CUBE_MAP            ;
    case GL_TEXTURE_RECTANGLE           :return GL_TEXTURE_BINDING_RECTANGLE           ;
    default                             :return 0;
  }
}

GLenum ge::gl::textureBinding2Target(GLenum binding){
  switch(binding){
    case GL_TEXTURE_BINDING_1D                  :return GL_TEXTURE_1D                  ;
    case GL_TEXTURE_BINDING_1D_ARRAY            :return GL_TEXTURE_1D_ARRAY            ;
    case GL_TEXTURE_BINDING_2D                  :return GL_TEXTURE_2D                  ;
    case GL_TEXTURE_BINDING_2D_ARRAY            :return GL_TEXTURE_2D_ARRAY            ;
    case GL_TEXTURE_BINDING_2D_MULTISAMPLE      :return GL_TEXTURE_2D_MULTISAMPLE      ;
    case GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY:return GL_TEXTURE_2D_MULTISAMPLE_ARRAY;
    case GL_TEXTURE_BINDING_3D                  :return GL_TEXTURE_3D                  ;
    case GL_TEXTURE_BINDING_BUFFER              :return GL_TEXTURE_BUFFER              ;
    case GL_TEXTURE_BINDING_CUBE_MAP            :return GL_TEXTURE_CUBE_MAP            ;
    case GL_TEXTURE_BINDING_RECTANGLE           :return GL_TEXTURE_RECTANGLE           ;
    default                                     :return 0;
  }
}

std::string ge::gl::translateTextureTarget(GLenum target){
  switch(target){
    case GL_TEXTURE_1D                  :return "GL_TEXTURE_1D"                  ;
    case GL_TEXTURE_1D_ARRAY            :return "GL_TEXTURE_1D_ARRAY"            ;
    case GL_TEXTURE_2D                  :return "GL_TEXTURE_2D"                  ;
    case GL_TEXTURE_2D_ARRAY            :return "GL_TEXTURE_2D_ARRAY"            ;
    case GL_TEXTURE_2D_MULTISAMPLE      :return "GL_TEXTURE_2D_MULTISAMPLE"      ;
    case GL_TEXTURE_2D_MULTISAMPLE_ARRAY:return "GL_TEXTURE_2D_MULTISAMPLE_ARRAY";
    case GL_TEXTURE_3D                  :return "GL_TEXTURE_3D"                  ;
    case GL_TEXTURE_BUFFER              :return "GL_TEXTURE_BUFFER"              ;
    case GL_TEXTURE_CUBE_MAP            :return "GL_TEXTURE_CUBE_MAP"            ;
    case GL_TEXTURE_RECTANGLE           :return "GL_TEXTURE_RECTANGLE"           ;
    default                             :return "unknown"                        ;
  }
}

std::string ge::gl::translateTextureBinding(GLenum binding){
  switch(binding){
    case GL_TEXTURE_BINDING_1D                  :return "GL_TEXTURE_BINDING_1D"                  ;
    case GL_TEXTURE_BINDING_1D_ARRAY            :return "GL_TEXTURE_BINDING_1D_ARRAY"            ;
    case GL_TEXTURE_BINDING_2D                  :return "GL_TEXTURE_BINDING_2D"                  ;
    case GL_TEXTURE_BINDING_2D_ARRAY            :return "GL_TEXTURE_BINDING_2D_ARRAY"            ;
    case GL_TEXTURE_BINDING_2D_MULTISAMPLE      :return "GL_TEXTURE_BINDING_2D_MULTISAMPLE"      ;
    case GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY:return "GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY";
    case GL_TEXTURE_BINDING_3D                  :return "GL_TEXTURE_BINDING_3D"                  ;
    case GL_TEXTURE_BINDING_BUFFER              :return "GL_TEXTURE_BINDING_BUFFER"              ;
    case GL_TEXTURE_BINDING_CUBE_MAP            :return "GL_TEXTURE_BINDING_CUBE_MAP"            ;
    case GL_TEXTURE_BINDING_RECTANGLE           :return "GL_TEXTURE_BINDING_RECTANGLE"           ;
    default                                     :return "unknown"                                ;
  }
}
std::string translateTextureSwizzle(GLint swizzle){
  switch(swizzle){
    case GL_RED  :return"GL_RED"  ;
    case GL_GREEN:return"GL_GREEN";
    case GL_BLUE :return"GL_BLUE" ;
    case GL_ALPHA:return"GL_ALPHA";
    default      :return"unknown" ;
  }
}

std::string translateTextureWrap(GLint wrap){
  switch(wrap){
    case GL_CLAMP_TO_EDGE       :return"GL_CLAMP_TO_EDGE"       ;
    case GL_CLAMP_TO_BORDER     :return"GL_CLAMP_TO_BORDER"     ;
    case GL_MIRRORED_REPEAT     :return"GL_MIRRORED_REPEAT"     ;
    case GL_REPEAT              :return"GL_REPEAT"              ;
    case GL_MIRROR_CLAMP_TO_EDGE:return"GL_MIRROR_CLAMP_TO_EDGE";
    default                     :return"unknown"                ;
  }
}

std::string translateTextureFilter(GLint filter){
  switch(filter){
    case GL_NEAREST               :return"GL_NEAREST"               ;
    case GL_LINEAR                :return"GL_LINEAR"                ;
    case GL_NEAREST_MIPMAP_NEAREST:return"GL_NEAREST_MIPMAP_NEAREST";
    case GL_LINEAR_MIPMAP_NEAREST :return"GL_LINEAR_MIPMAP_NEAREST" ;
    case GL_NEAREST_MIPMAP_LINEAR :return"GL_NEAREST_MIPMAP_LINEAR" ;
    case GL_LINEAR_MIPMAP_LINEAR  :return"GL_LINEAR_MIPMAP_LINEAR"  ;
    default                       :return"unknown"                  ;
  }
}
std::string translateTextureCompareFunc(GLint func){
  switch(func){
    case GL_LEQUAL  :return"GL_LEQUAL"  ;
    case GL_GEQUAL  :return"GL_GEQUAL"  ;
    case GL_LESS    :return"GL_LESS"    ;
    case GL_GREATER :return"GL_GREATER" ;
    case GL_EQUAL   :return"GL_EQUAL"   ;
    case GL_NOTEQUAL:return"GL_NOTEQUAL";
    case GL_ALWAYS  :return"GL_ALWAYS"  ;
    case GL_NEVER   :return"GL_NEVER"   ;
    default         :return"unknown"    ;
  }
}
std::string translateTextureCompareMode(GLint mode){
  switch(mode){
    case GL_COMPARE_REF_TO_TEXTURE:return"GL_COMPARE_REF_TO_TEXTURE";
    case GL_NONE                  :return"GL_NONE"                  ;
    default                       :return"unknown"                  ;
  }
}
TextureObject::TextureObject(
    GLenum  target,
    GLenum  internalFormat,
    GLsizei levels,
    GLsizei width){
  this->_target = target;
  this->_format = internalFormat;
#ifndef USE_DSA
  glGenTextures(1,&this->_id);
  glBindTexture(this->_target,this->_id);
  glTexStorage1D(this->_target,levels,this->_format,width);
#else //USE_DSA
  glCreateTextures(target,1,&this->_id);
  glTextureStorage2D(this->_id,levels,this->_format,width);
#endif//USE_DSA

}

TextureObject::TextureObject(
    GLenum  target,
    GLenum  internalFormat,
    GLsizei levels,
    GLsizei width,
    GLsizei height){
  this->_target = target;
  this->_format = internalFormat;
#ifndef USE_DSA
  glGenTextures(1,&this->_id);
  glBindTexture(this->_target,this->_id);
  glTexStorage2D(this->_target,levels,this->_format,width,height);
#else //USE_DSA
  glCreateTextures(target,1,&this->_id);
  glTextureStorage2D(this->_id,levels,this->_format,width,height);
#endif//USE_DSA
}

TextureObject::TextureObject(
    GLenum  target,
    GLenum  internalFormat,
    GLsizei levels,
    GLsizei width,
    GLsizei height,
    GLsizei depth){
  this->_target = target;
  this->_format = internalFormat;
#ifndef USE_DSA
  glGenTextures(1,&this->_id);
  glBindTexture(this->_target,this->_id);
  glTexStorage3D(this->_target,levels,this->_format,width,height,depth);
#else //USE_DSA
  glCreateTextures(target,1,&this->_id);
  glTextureStorage3D(this->_id,levels,this->_format,width,height,depth);
#endif//USE_DSA

}

TextureObject::~TextureObject(){
  glDeleteTextures(1,&this->_id);
}

void   TextureObject::bind(GLuint unit){
#ifndef USE_DSA
  glActiveTexture(unit);
  glBindTexture(this->_target,this->_id);
#else //USE_DSA
  glBindTextureUnit(unit,this->_id);
#endif//USE_DSA
}

void TextureObject::unbind(GLuint unit){
#ifndef USE_DSA
  glActiveTexture(unit);
  glBindTexture(this->_target,0);
#else //USE_DSA
  glBindTextureUnit(unit,0);
#endif//USE_DSA
}

void TextureObject::bindImage(
    GLuint    unit,
    GLint     level,
    GLenum    format,
    GLenum    access,
    GLboolean layered,
    GLint     layer){
  if(format == TEXTUREOBJECT_DEFAULT_FORMAT)
    format=this->_format;
  glBindImageTexture(
      unit,
      this->_id,
      level,
      layered,
      layer,
      access,
      format);
}

void TextureObject::texParameteri(GLenum pname,GLint params){
#ifndef USE_DSA
  glBindTexture(this->_target,this->_id);
  glTexParameteri(this->_target,pname,params);
#else //USE_DSA
  glTextureParameteri(this->_id,pname,params);
#endif//USE_DSA
}

void TextureObject::texParameterfv(GLenum pname,GLfloat *params){
#ifndef USE_DSA
  glBindTexture(this->_target,this->_id);
  glTexParameterfv(this->_target,pname,params);
#else //USE_DSA
  glTextureParameterfv(this->_id,pname,params);
#endif//USE_DSA
}

GLenum TextureObject::getTarget(){
  return this->_target;
  //glGetTextureParameteriv(this->_id,GL_TEXTURE_TARGET,(GLint*)&target);
}

GLenum TextureObject::getFormat(){
  return this->_format;
  //glGetTextureParameteriv(this->_id,GL_TEXTURE_INTERNAL_FORMAT,(GLint*)format);
}
GLint TextureObject::_getTexLevelParameter(GLint level,GLenum pname){
  GLint param;
#ifndef USE_DSA
  GLuint oldId;
  GLenum target=this->getTarget();
  glGetTexParameteriv(target,textureTarget2Binding(target),(GLint*)&oldId);
  glBindTexture(GL_TEXTURE_2D,this->_id);
  glGetTexLevelParameteriv(GL_TEXTURE_2D,level,pname,&param);
  glBindTexture(GL_TEXTURE_2D,oldId);
#else //USE_DSA
  glGetTextureLevelParameteriv(this->_id,level,GL_TEXTURE_WIDTH,&param);
#endif//USE_DSA
  return param;
}
GLsizei TextureObject::getWidth(GLint level){
  return this->_getTexLevelParameter(level,GL_TEXTURE_WIDTH);
}
GLsizei TextureObject::getHeight(GLint level){
  return this->_getTexLevelParameter(level,GL_TEXTURE_HEIGHT);
}
GLsizei TextureObject::getDepth(GLint level){
  return this->_getTexLevelParameter(level,GL_TEXTURE_DEPTH);
}
GLint TextureObject::getFixedSampleLocation(GLint level){
  return this->_getTexLevelParameter(level,GL_TEXTURE_FIXED_SAMPLE_LOCATIONS);
}
GLint TextureObject::getCompressed(GLint level){
  return this->_getTexLevelParameter(level,GL_TEXTURE_COMPRESSED);
}
GLint TextureObject::getCompressedImageSize(GLint level){
  return this->_getTexLevelParameter(level,GL_TEXTURE_COMPRESSED_IMAGE_SIZE);
}
GLint TextureObject::getSamples(GLint level){
  return this->_getTexLevelParameter(level,GL_TEXTURE_SAMPLES);
}
GLint TextureObject::_getTexParameter(GLenum pname){
  GLint param;
#ifndef USE_DSA
  GLuint oldId;
  GLenum target=this->getTarget();
  glGetTexParameteriv(target,textureTarget2Binding(target),(GLint*)&oldId);
  glBindTexture(GL_TEXTURE_2D,this->_id);
  glGetTexParameteriv(GL_TEXTURE_2D,pname,&param);
  glBindTexture(GL_TEXTURE_2D,oldId);
#else //USE_DSA
  glGetTextureParameteriv(this->_id,pname,&param));
#endif//USE_DSA
  return param;
}
