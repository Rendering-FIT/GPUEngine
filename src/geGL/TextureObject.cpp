#include<geGL/TextureObject.h>

#include<sstream>

/*

   glTexImage3D
   glTexImage2D
   glTexImage1D

   glCompressedTexImage3D
   glCompressedTexImage2D
   glCompressedTexImage1D

   glTexImage3DMultisample
   glTexImage2DMultisample

   glTexStorage3D
   glTexStorage2D
   glTexStorage1D

   glTextureStorage3D
   glTextureStorage2D
   glTextureStorage1D

   glTexStorage3DMultisample
   glTexStorage2DMultisample

   glTextureStorage3DMultisample
   glTextureStorage2DMultisample


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

glTextureStorage1D
glTextureStorage2D
glTextureStorage3D


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
    default                             :return 0                                      ;
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
    default                                     :return 0                              ;
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
std::string ge::gl::translateTextureSwizzle(GLint swizzle){
  switch(swizzle){
    case GL_RED  :return"GL_RED"  ;
    case GL_GREEN:return"GL_GREEN";
    case GL_BLUE :return"GL_BLUE" ;
    case GL_ALPHA:return"GL_ALPHA";
    default      :return"unknown" ;
  }
}

std::string ge::gl::translateTextureWrap(GLint wrap){
  switch(wrap){
    case GL_CLAMP_TO_EDGE       :return"GL_CLAMP_TO_EDGE"       ;
    case GL_CLAMP_TO_BORDER     :return"GL_CLAMP_TO_BORDER"     ;
    case GL_MIRRORED_REPEAT     :return"GL_MIRRORED_REPEAT"     ;
    case GL_REPEAT              :return"GL_REPEAT"              ;
    case GL_MIRROR_CLAMP_TO_EDGE:return"GL_MIRROR_CLAMP_TO_EDGE";
    default                     :return"unknown"                ;
  }
}

std::string ge::gl::translateTextureFilter(GLint filter){
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
std::string ge::gl::translateTextureCompareFunc(GLint func){
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
std::string ge::gl::translateTextureCompareMode(GLint mode){
  switch(mode){
    case GL_COMPARE_REF_TO_TEXTURE:return"GL_COMPARE_REF_TO_TEXTURE";
    case GL_NONE                  :return"GL_NONE"                  ;
    default                       :return"unknown"                  ;
  }
}

std::string ge::gl::translateTextureChannelType(GLenum type){
  switch(type){
    case GL_NONE               :return"GL_NONE"               ;
    case GL_SIGNED_NORMALIZED  :return"GL_SIGNED_NORMALIZED"  ;
    case GL_UNSIGNED_NORMALIZED:return"GL_UNSIGNED_NORMALIZED";
    case GL_FLOAT              :return"GL_FLOAT"              ;
    case GL_INT                :return"GL_INT"                ;
    case GL_UNSIGNED_INT       :return"GL_UNSIGNED_INT"       ;
    default                    :return"unknown"               ;
  }
}

std::string ge::gl::translateInternalFormat(GLenum internalFormat){
  switch(internalFormat){
    case GL_STENCIL_INDEX1    :return"GL_STENCIL_INDEX1"    ;
    case GL_STENCIL_INDEX4    :return"GL_STENCIL_INDEX4"    ;
    case GL_R8                :return"GL_R8"                ;
    case GL_R8UI              :return"GL_R8UI"              ;
    case GL_R8I               :return"GL_R8I"               ;
    case GL_R8_SNORM          :return"GL_R8_SNORM"          ;
    case GL_R3_G3_B2          :return"GL_R3_G3_B2"          ;
    case GL_RGBA2             :return"GL_RGBA2"             ;
    case GL_STENCIL_INDEX8    :return"GL_STENCIL_INDEX8"    ;
    case GL_RGB4              :return"GL_RGB4"              ;
    case GL_RGB5              :return"GL_RGB5"              ;
    case GL_R16               :return"GL_R16"               ;
    case GL_R16F              :return"GL_R16F"              ;
    case GL_R16UI             :return"GL_R16UI"             ;
    case GL_R16I              :return"GL_R16I"              ;
    case GL_R16_SNORM         :return"GL_R16_SNORM"         ;
    case GL_RG8               :return"GL_RG8"               ;
    case GL_RG8UI             :return"GL_RG8UI"             ;
    case GL_RG8I              :return"GL_RG8I"              ;
    case GL_RGB565            :return"GL_RGB565"            ;
    case GL_RGB5_A1           :return"GL_RGB5_A1"           ;
    case GL_RGBA4             :return"GL_RGBA4"             ;
    case GL_DEPTH_COMPONENT16 :return"GL_DEPTH_COMPONENT16" ;
    case GL_STENCIL_INDEX16   :return"GL_STENCIL_INDEX16"   ;
    case GL_RGB8              :return"GL_RGB8"              ;
    case GL_RGB8_SNORM        :return"GL_RGB8_SNORM"        ;
    case GL_RGB8UI            :return"GL_RGB8UI"            ;
    case GL_RGB8I             :return"GL_RGB8I"             ;
    case GL_DEPTH_COMPONENT24 :return"GL_DEPTH_COMPONENT24" ;
    case GL_SRGB8             :return"GL_SRGB8"             ;
    case GL_SRGB8_ALPHA8      :return"GL_SRGB8_ALPHA8"      ;
    case GL_RG16              :return"GL_RG16"              ;
    case GL_RG16_SNORM        :return"GL_RG16_SNORM"        ;
    case GL_DEPTH24_STENCIL8  :return"GL_DEPTH24_STENCIL8"  ;
    case GL_DEPTH_COMPONENT32F:return"GL_DEPTH_COMPONENT32F";
    case GL_DEPTH_COMPONENT32 :return"GL_DEPTH_COMPONENT32" ;
    case GL_DEPTH32F_STENCIL8 :return"GL_DEPTH32F_STENCIL8" ;
    case GL_RGB16F            :return"GL_RGB16F"            ;
    case GL_RGB16I            :return"GL_RGB16I"            ;
    case GL_RGB16UI           :return"GL_RGB16UI"           ;
    case GL_RGBA16F           :return"GL_RGBA16F"           ;
    case GL_RGBA16I           :return"GL_RGBA16I"           ;
    case GL_RGBA16UI          :return"GL_RGBA16UI"          ;
    case GL_RGBA32F           :return"GL_RGBA32F"           ;
    case GL_RGBA32UI          :return"GL_RGBA32UI"          ;
    case GL_RGBA32I           :return"GL_RGBA32I"           ;
    default                   :return"unknown"              ;
  };
}


unsigned ge::gl::internalFormatSize(GLenum internalFormat){
  switch(internalFormat){
    case GL_STENCIL_INDEX1:
      return 1;
    case GL_STENCIL_INDEX4:
      return 4;
    case GL_R8            :
    case GL_R8UI          :
    case GL_R8I           :
    case GL_R8_SNORM      :
    case GL_R3_G3_B2      :
    case GL_RGBA2         :
    case GL_STENCIL_INDEX8:
      return 8;

    case GL_RGB4:
      return 12;
    case GL_RGB5:
      return 16;//TODO CHECK

    case GL_R16              :
    case GL_R16F             :
    case GL_R16UI            :
    case GL_R16I             :
    case GL_R16_SNORM        :
    case GL_RG8              :
    case GL_RG8UI            :
    case GL_RG8I             :
    case GL_RGB565           :
    case GL_RGB5_A1          :
    case GL_RGBA4            :
    case GL_DEPTH_COMPONENT16:
    case GL_STENCIL_INDEX16  :
      return 16;

    case GL_RGB8             :
    case GL_RGB8_SNORM       :
    case GL_RGB8UI           :
    case GL_RGB8I            :
    case GL_DEPTH_COMPONENT24:
    case GL_SRGB8            :
      return 24;

    case GL_SRGB8_ALPHA8      :
    case GL_RG16              :
    case GL_RG16_SNORM        :
    case GL_DEPTH24_STENCIL8  :
    case GL_DEPTH_COMPONENT32F:
    case GL_DEPTH_COMPONENT32 :
      return 32;
    case GL_DEPTH32F_STENCIL8:
      return 32+8;
    case GL_RGB16F:
    case GL_RGB16I:
    case GL_RGB16UI:
      return 3*16;
    case GL_RGBA16F:
    case GL_RGBA16I:
    case GL_RGBA16UI:
      return 4*16;
    case GL_RGBA32F :
    case GL_RGBA32UI:
    case GL_RGBA32I :
      return 4*32;
  }
  return 32;//TODO
}


/**
 * @brief Creates 1D texture
 *
 * @param target target of texture
 * @param internalFormat internal format of data of texture
 * @param levels number of mipmap levels
 * @param width x size of texture
 */
TextureObject::TextureObject(
    GLenum  target,
    GLenum  internalFormat,
    GLsizei levels,
    GLsizei width){
#ifndef USE_DSA
  this->_target = target;
#endif//USE_DSA
  this->_format = internalFormat;
#ifndef USE_DSA
  glGenTextures (1,&this->_id);
  glBindTexture (this->getTarget(),this->_id);
  glTexStorage1D(this->getTarget(),levels,this->_format,width);
#else //USE_DSA
  glCreateTextures(target,1,&this->_id);
  glTextureStorage1D(this->_id,levels,this->_format,width);
#endif//USE_DSA

}

/**
 * @brief Creates 2D texture
 *
 * @param target target of texture
 * @param internalFormat internal format of data of texture
 * @param levels number of mipmap levels
 * @param width x size of texture
 * @param height y size of texture
 */
TextureObject::TextureObject(
    GLenum  target,
    GLenum  internalFormat,
    GLsizei levels,
    GLsizei width,
    GLsizei height){
#ifndef USE_DSA
  this->_target = target;
#endif//USE_DSA
  this->_format = internalFormat;
#ifndef USE_DSA
  glGenTextures(1,&this->_id);
  glBindTexture (this->getTarget(),this->_id);
  glTexStorage2D(this->getTarget(),levels,this->_format,width,height);
#else //USE_DSA
  glCreateTextures(target,1,&this->_id);
  glTextureStorage2D(this->_id,levels,this->_format,width,height);
#endif//USE_DSA
}

/**
 * @brief Creates 3D texture
 *
 * @param target target of texture
 * @param internalFormat internal format of data of texture
 * @param levels number of mipmap levels
 * @param width x size of texture
 * @param height y size of texture
 * @param depth z size of texture
 */
TextureObject::TextureObject(
    GLenum  target,
    GLenum  internalFormat,
    GLsizei levels,
    GLsizei width,
    GLsizei height,
    GLsizei depth){
#ifndef USE_DSA
  this->_target = target;
#endif//USE_DSA
  this->_format = internalFormat;
#ifndef USE_DSA
  glGenTextures(1,&this->_id);
  glBindTexture (this->getTarget(),this->_id);
  glTexStorage3D(this->getTarget(),levels,this->_format,width,height,depth);
#else //USE_DSA
  glCreateTextures(target,1,&this->_id);
  glTextureStorage3D(this->_id,levels,this->_format,width,height,depth);
#endif//USE_DSA

}

/**
 * @brief destroys texture
 */
TextureObject::~TextureObject(){
  glDeleteTextures(1,&this->_id);
}

/**
 * @brief binds texture to texture unit
 *
 * @param unit texture unit
 */
void   TextureObject::bind(GLuint unit){
#ifndef USE_DSA
  glActiveTexture(unit);
  glBindTexture(this->getTarget(),this->_id);
#else //USE_DSA
  glBindTextureUnit(unit,this->_id);
#endif//USE_DSA
}

/**
 * @brief unbinds texture unit
 *
 * @param unit texture unit
 */
void TextureObject::unbind(GLuint unit){
#ifndef USE_DSA
  glActiveTexture(unit);
  glBindTexture(this->getTarget(),0);
#else //USE_DSA
  glBindTextureUnit(unit,0);
#endif//USE_DSA
}

/**
 * @brief binds image of texture
 *
 * @param unit texture unit
 * @param level level of mipmap
 * @param format format of data
 * @param access read/write
 * @param layered use layered 
 * @param layer index of layer
 */
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

/**
 * @brief sets parameters of texture
 *
 * @param pname name of parameter
 * @param params value of parameter
 */
void TextureObject::texParameteri(GLenum pname,GLint params){
#ifndef USE_DSA
  glBindTexture  (this->getTarget(),this->_id);
  glTexParameteri(this->getTarget(),pname,params);
#else //USE_DSA
  glTextureParameteri(this->_id,pname,params);
#endif//USE_DSA
}

/**
 * @brief sets parameters of texture
 *
 * @param pname name of parameter
 * @param params values of parameter
 */
void TextureObject::texParameterfv(GLenum pname,GLfloat *params){
#ifndef USE_DSA
  glBindTexture   (this->getTarget(),this->_id);
  glTexParameterfv(this->getTarget(),pname,params);
#else //USE_DSA
  glTextureParameterfv(this->_id,pname,params);
#endif//USE_DSA
}


/**
 * @brief gets internal format of texture
 *
 * @return format
 */
GLenum TextureObject::getFormat(){
  return this->_format;
  //glGetTextureParameteriv(this->_id,GL_TEXTURE_INTERNAL_FORMAT,(GLint*)format);
}

GLuint TextureObject::_bindSafe(){
  GLuint oldId;
  GLenum target=this->getTarget();
  glGetIntegerv(ge::gl::textureTarget2Binding(target),(GLint*)&oldId);
  glBindTexture(target,this->_id);
  return oldId;
}

GLint TextureObject::_getTexLevelParameter(GLint level,GLenum pname){
  GLint param;
#ifndef USE_DSA
  GLuint oldId=this->_bindSafe();
  glGetTexLevelParameteriv(this->getTarget(),level,pname,&param);
  glBindTexture(this->getTarget(),oldId);
#else //USE_DSA
  glGetTextureLevelParameteriv(this->_id,level,pname,&param);
#endif//USE_DSA
  return param;
}

GLint TextureObject::_getTexParameter(GLenum pname){
  GLint param;
#ifndef USE_DSA
  GLuint oldId=this->_bindSafe();
  glGetTexParameteriv(this->getTarget(),pname,&param);
  glBindTexture(this->getTarget(),oldId);
#else //USE_DSA
  glGetTextureParameteriv(this->_id,pname,&param));
#endif//USE_DSA
  return param;
}

void TextureObject::_getTexParameterf(GLfloat*data,GLenum pname){
#ifndef USE_DSA
  GLuint oldId=this->_bindSafe();
  glGetTexParameterfv(this->getTarget(),pname,data);
  glBindTexture(this->getTarget(),oldId);
#else
  glGetTextureParameterfv(this->_id,pname,data);
#endif//USE_DSA
}

/**
 * @brief gets width of texture at specific level
 *
 * @param level level of mipmap
 *
 * @return width of mipmap
 */
GLuint TextureObject::getWidth(GLint level){
  return this->_getTexLevelParameter(level,GL_TEXTURE_WIDTH);
}

/**
 * @brief gets height of texture at specific level
 *
 * @param level level of mipmap
 *
 * @return height of mipmap
 */
GLuint TextureObject::getHeight(GLint level){
  return this->_getTexLevelParameter(level,GL_TEXTURE_HEIGHT);
}

/**
 * @brief gets depth of texture at specific level
 *
 * @param level level of mipmap
 *
 * @return depth of mipmap
 */
GLuint TextureObject::getDepth(GLint level){
  return this->_getTexLevelParameter(level,GL_TEXTURE_DEPTH);
}

/**
 * @brief gets number of samples 
 *
 * @param level level of mipmap
 *
 * @return number of samples
 */
GLuint TextureObject::getSamples(GLint level){
  return this->_getTexLevelParameter(level,GL_TEXTURE_SAMPLES);
}

/**
 * @brief gets fixed sample location
 *
 * @param level level of mipmap
 *
 * @return fixed sample location
 */
GLboolean TextureObject::getFixedSampleLocation(GLint level){
  return this->_getTexLevelParameter(level,GL_TEXTURE_FIXED_SAMPLE_LOCATIONS);
}

/**
 * @brief gets internal format
 *
 * @param level level of mipmap
 *
 * @return internal format
 */
GLenum TextureObject::getInternalFormat(GLint level){
  return this->_getTexLevelParameter(level,GL_TEXTURE_INTERNAL_FORMAT);
}

/**
 * @brief gets red size
 *
 * @param level level of mipmap
 *
 * @return red size
 */
GLuint TextureObject::getRedSize(GLint level){
  return this->_getTexLevelParameter(level,GL_TEXTURE_RED_SIZE);
}

/**
 * @brief gets green size
 *
 * @param level level of mipmap
 *
 * @return green size
 */
GLuint TextureObject::getGreenSize(GLint level){
  return this->_getTexLevelParameter(level,GL_TEXTURE_GREEN_SIZE);
}

/**
 * @brief gets blue size
 *
 * @param level level of mipmap
 *
 * @return blue size
 */
GLuint TextureObject::getBlueSize(GLint level){
  return this->_getTexLevelParameter(level,GL_TEXTURE_BLUE_SIZE);
}

/**
 * @brief gets alpha size
 *
 * @param level level of mipmap
 *
 * @return alpha size
 */
GLuint TextureObject::getAlphaSize(GLint level){
  return this->_getTexLevelParameter(level,GL_TEXTURE_ALPHA_SIZE);
}

/**
 * @brief gets depth size
 *
 * @param level level of mipmap
 *
 * @return depth size
 */
GLuint TextureObject::getDepthSize(GLint level){
  return this->_getTexLevelParameter(level,GL_TEXTURE_DEPTH_SIZE);
}

/**
 * @brief gets stencil size
 *
 * @param level level of mipmap
 *
 * @return stencil size
 */
GLuint TextureObject::getStencilSize(GLint level){
  return this->_getTexLevelParameter(level,GL_TEXTURE_STENCIL_SIZE);
}

/**
 * @brief gets shared size
 *
 * @param level level of mipmap
 *
 * @return shared size
 */
GLuint TextureObject::getSharedSize(GLint level){
  return this->_getTexLevelParameter(level,GL_TEXTURE_SHARED_SIZE);
}

/**
 * @brief gets red type
 *
 * @param level level of mipmap
 *
 * @return red type
 */
GLenum TextureObject::getRedType(GLint level){
  return this->_getTexLevelParameter(level,GL_TEXTURE_RED_TYPE);
}

/**
 * @brief gets blue type
 *
 * @param level level of mipmap
 *
 * @return blue type
 */
GLenum TextureObject::getBlueType(GLint level){
  return this->_getTexLevelParameter(level,GL_TEXTURE_BLUE_TYPE);
}

/**
 * @brief gets green type
 *
 * @param level level of mipmap
 *
 * @return green type
 */
GLenum TextureObject::getGreenType(GLint level){
  return this->_getTexLevelParameter(level,GL_TEXTURE_GREEN_TYPE);
}

/**
 * @brief gets alpha type
 *
 * @param level level of mipmap
 *
 * @return alpha type
 */
GLenum TextureObject::getAlphaType(GLint level){
  return this->_getTexLevelParameter(level,GL_TEXTURE_ALPHA_TYPE);
}

/**
 * @brief gets depth type
 *
 * @param level level of mipmap
 *
 * @return depth type
 */
GLenum TextureObject::getDepthType(GLint level){
  return this->_getTexLevelParameter(level,GL_TEXTURE_DEPTH_TYPE);
}

/**
 * @brief gets compressed flag
 *
 * @param level level of mipmap
 *
 * @return compressed flag
 */
GLboolean TextureObject::getCompressed(GLint level){
  return this->_getTexLevelParameter(level,GL_TEXTURE_COMPRESSED);
}

/**
 * @brief gets compressed image size
 *
 * @param level level of mipmap
 *
 * @return compressed image size
 */
GLuint TextureObject::getCompressedImageSize(GLint level){
  return this->_getTexLevelParameter(level,GL_TEXTURE_COMPRESSED_IMAGE_SIZE);
}

/**
 * @brief gets texture buffer binding
 *
 * @param level mipmap level
 *
 * @return texture buffer binding
 */
GLuint TextureObject::getBufferDataStoreBinding(GLint level){
  return this->_getTexLevelParameter(level,GL_TEXTURE_BUFFER_DATA_STORE_BINDING);
}

/**
 * @brief gets texture buffer offset
 *
 * @param level mipmap level
 *
 * @return texture buffer offset
 */
GLint TextureObject::getBufferOffset(GLint level){
  return this->_getTexLevelParameter(level,GL_TEXTURE_BUFFER_OFFSET);
}

/**
 * @brief gets texture buffer size
 *
 * @param level mipmap level
 *
 * @return texture buffer size
 */
GLint TextureObject::getBufferSize(GLint level){
  return this->_getTexLevelParameter(level,GL_TEXTURE_BUFFER_SIZE);
}

/**
 * @brief gets red swizzle
 *
 * @return red swizzle
 */
GLenum TextureObject::getSwizzleR(){
  return this->_getTexParameter(GL_TEXTURE_SWIZZLE_R);
}

/**
 * @brief gets green swizzle
 *
 * @return green swizzle
 */
GLenum TextureObject::getSwizzleG(){
  return this->_getTexParameter(GL_TEXTURE_SWIZZLE_G);
}

/**
 * @brief gets blue swizzle
 *
 * @return blue swizzle
 */
GLenum TextureObject::getSwizzleB(){
  return this->_getTexParameter(GL_TEXTURE_SWIZZLE_B);
}

/**
 * @brief gets alpha swizzle
 *
 * @return alpha swizzle
 */
GLenum TextureObject::getSwizzleA(){
  return this->_getTexParameter(GL_TEXTURE_SWIZZLE_A);
}

/**
 * @brief gets border color
 *
 * @param color border color
 */
void TextureObject::getBorderColor(GLfloat*color){
  this->_getTexParameterf(color,GL_TEXTURE_BORDER_COLOR);
}

/**
 * @brief gets min filter
 *
 * @return min filter
 */
GLenum TextureObject::getMinFilter(){
  return this->_getTexParameter(GL_TEXTURE_MIN_FILTER);
}

/**
 * @brief gets mag filter
 *
 * @return mag filter
 */
GLenum TextureObject::getMagFilter(){
  return this->_getTexParameter(GL_TEXTURE_MAG_FILTER);
}

/**
 * @brief gets wrapS
 *
 * @return wrapS
 */
GLenum TextureObject::getWrapS(){
  return this->_getTexParameter(GL_TEXTURE_WRAP_S);
}

/**
 * @brief gets wrapT
 *
 * @return wrapT
 */
GLenum TextureObject::getWrapT(){
  return this->_getTexParameter(GL_TEXTURE_WRAP_T);
}

/**
 * @brief gets wrapR
 *
 * @return wrapR
 */
GLenum TextureObject::getWrapR(){
  return this->_getTexParameter(GL_TEXTURE_WRAP_R);
}

/**
 * @brief gets target of texture
 *
 * @return target
 */
GLenum TextureObject::getTarget(){
#ifndef USE_DSA
  return this->_target;
#else //USE_DSA
  return this->_getTexParameter(GL_TEXTURE_TARGET);
#endif//USE_DSA
}

/**
 * @brief gets texture minlod
 *
 * @return texture minlod
 */
GLfloat TextureObject::getMinLod(){
  GLfloat lod;
  this->_getTexParameterf(&lod,GL_TEXTURE_MIN_LOD);
  return lod;
}

/**
 * @brief gets texture maxlod
 *
 * @return texture maxlod
 */
GLfloat TextureObject::getMaxLod(){
  GLfloat lod;
  this->_getTexParameterf(&lod,GL_TEXTURE_MAX_LOD);
  return lod;
}

/**
 * @brief gets texture base level
 *
 * @return texture base level
 */
GLuint TextureObject::getBaseLevel(){
  return this->_getTexParameter(GL_TEXTURE_BASE_LEVEL);
}

/**
 * @brief gets texture max level
 *
 * @return texture max level
 */
GLuint TextureObject::getMaxLevel(){
  return this->_getTexParameter(GL_TEXTURE_MAX_LEVEL);
}

/**
 * @brief gets texture lod bias
 *
 * @return texture lod bias
 */
GLfloat TextureObject::getLodBias(){
  GLfloat bias;
  this->_getTexParameterf(&bias,GL_TEXTURE_LOD_BIAS);
  return bias;
}

/**
 * @brief gets depth stencil texture mode
 *
 * @return depth stencil texture mode
 */
GLenum TextureObject::getDepthStencilTextureMode(){
  return this->_getTexParameter(GL_DEPTH_STENCIL_TEXTURE_MODE);
}

/**
 * @brief gets texture compare mode
 *
 * @return texture compare mode
 */
GLenum TextureObject::getCompareMode(){
  return this->_getTexParameter(GL_TEXTURE_COMPARE_MODE);
}

/**
 * @brief gets texture compare func
 *
 * @return texture compare func
 */
GLenum TextureObject::getCompareFunc(){
  return this->_getTexParameter(GL_TEXTURE_COMPARE_FUNC);
}

/**
 * @brief gets texture image format compatibility type
 *
 * @return texture image format compatibility type
 */
GLenum TextureObject::getImageFormatCompatibilityType(){
  return this->_getTexParameter(GL_IMAGE_FORMAT_COMPATIBILITY_TYPE);
}

/**
 * @brief gets texture immutable format
 *
 * @return texture immutable format
 */
GLboolean TextureObject::getImmutableFormat(){
  return this->_getTexParameter(GL_TEXTURE_IMMUTABLE_FORMAT);
}

/**
 * @brief gets texture immutable levels
 *
 * @return texture immutable levels
 */
GLuint TextureObject::getImmutableLevels(){
  return this->_getTexParameter(GL_TEXTURE_IMMUTABLE_LEVELS);
}

/**
 * @brief gets texture view min level
 *
 * @return texture view min level
 */
GLuint TextureObject::getViewMinLevel(){
  return this->_getTexParameter(GL_TEXTURE_VIEW_MIN_LEVEL);
}

/**
 * @brief gets texture view num levels
 *
 * @return texture view num levels
 */
GLuint TextureObject::getViewNumLevels(){
  return this->_getTexParameter(GL_TEXTURE_VIEW_NUM_LEVELS);
}

/**
 * @brief gets texture view min layer
 *
 * @return texture view min layer
 */
GLuint TextureObject::getViewMinLayer(){
  return this->_getTexParameter(GL_TEXTURE_VIEW_MIN_LAYER);
}

/**
 * @brief gets texture view num layers
 *
 * @return texture view num layers
 */
GLuint TextureObject::getViewNumLayers(){
  return this->_getTexParameter(GL_TEXTURE_VIEW_NUM_LAYERS);
}


std::string TextureObject::getInfo(){
  std::stringstream ss;
  ss<<"GL_TEXTURE_WIDTH: " <<this->getWidth (0)<<std::endl;
  ss<<"GL_TEXTURE_HEIGHT: "<<this->getHeight(0)<<std::endl;
  if(this->getTarget()==GL_TEXTURE_3D)//TODO array 2D, etc
    ss<<"GL_TEXTURE_DEPTH: "           <<this->getDepth (0)<<std::endl;

  ss<<"GL_TEXTURE_SAMPLES: "                  <<this->getSamples               (0)<<std::endl;
  ss<<"GL_TEXTURE_FIXED_SAMPLE_LOCATIONS: "   <<(bool)this->getFixedSampleLocation   (0)<<std::endl;
  ss<<"GL_TEXTURE_INTERNAL_FORMAT: "          <<ge::gl::translateInternalFormat(this->getInternalFormat(0))<<std::endl;
  ss<<"GL_TEXTURE_RED_SIZE: "                 <<this->getRedSize               (0)<<std::endl;
  ss<<"GL_TEXTURE_BLUE_SIZE: "                <<this->getBlueSize              (0)<<std::endl;
  ss<<"GL_TEXTURE_GREEN_SIZE: "               <<this->getGreenSize             (0)<<std::endl;
  ss<<"GL_TEXTURE_ALPHA_SIZE: "               <<this->getAlphaSize             (0)<<std::endl;
  ss<<"GL_TEXTURE_DEPTH_SIZE: "               <<this->getDepthSize             (0)<<std::endl;
  ss<<"GL_TEXTURE_STENCIL_SIZE: "             <<this->getStencilSize           (0)<<std::endl;
  ss<<"GL_TEXTURE_RED_TYPE: "                 <<ge::gl::translateTextureChannelType(this->getRedType               (0))<<std::endl;
  ss<<"GL_TEXTURE_BLUE_TYPE: "                <<ge::gl::translateTextureChannelType(this->getBlueType              (0))<<std::endl;
  ss<<"GL_TEXTURE_GREEN_TYPE: "               <<ge::gl::translateTextureChannelType(this->getGreenType             (0))<<std::endl;
  ss<<"GL_TEXTURE_ALPHA_TYPE: "               <<ge::gl::translateTextureChannelType(this->getAlphaType             (0))<<std::endl;
  ss<<"GL_TEXTURE_DEPTH_TYPE: "               <<ge::gl::translateTextureChannelType(this->getDepthType             (0))<<std::endl;
  
  ss<<"GL_TEXTURE_COMPRESSED: "               <<this->getCompressed            (0)<<std::endl;
  ss<<"GL_TEXTURE_COMPRESSED_IMAGE_SIZE: "    <<this->getCompressedImageSize   (0)<<std::endl;
  
  //ss<<"GL_TEXTURE_BUFFER_DATA_STORE_BINDING: "<<this->getBufferDataStoreBinding(0)<<std::endl;
  /*ss<<"GL_TEXTURE_BUFFER_OFFSET: "            <<this->getBufferOffset          (0)<<std::endl;
  ss<<"GL_TEXTURE_BUFFER_SIZE: "              <<this->getBufferSize            (0)<<std::endl;*/
  

  ss<<"GL_TEXTURE_SWIZZLE_R: "         <<ge::gl::translateTextureSwizzle(this->getSwizzleR())<<std::endl;
  ss<<"GL_TEXTURE_SWIZZLE_G: "         <<ge::gl::translateTextureSwizzle(this->getSwizzleG())<<std::endl;
  ss<<"GL_TEXTURE_SWIZZLE_B: "         <<ge::gl::translateTextureSwizzle(this->getSwizzleB())<<std::endl;
  ss<<"GL_TEXTURE_SWIZZLE_A: "         <<ge::gl::translateTextureSwizzle(this->getSwizzleA())<<std::endl;
  GLfloat bColor[4];
  this->getBorderColor(bColor);
  ss<<"GL_TEXTURE_BORDER_COLOR: "      <<bColor[0]<<" "<<bColor[1]<<" "<<bColor[2]<<" "<<bColor[3]<<std::endl;
  ss<<"GL_TEXTURE_MIN_FILTER: "        <<ge::gl::translateTextureFilter(this->getMinFilter())<<std::endl;
  ss<<"GL_TEXTURE_MAG_FILTER: "        <<ge::gl::translateTextureFilter(this->getMagFilter())<<std::endl;
  ss<<"GL_TEXTURE_WRAP_S: "            <<ge::gl::translateTextureWrap(this->getWrapS())<<std::endl;
  ss<<"GL_TEXTURE_WRAP_T: "            <<ge::gl::translateTextureWrap(this->getWrapT())<<std::endl;
  ss<<"GL_TEXTURE_WRAP_R: "            <<ge::gl::translateTextureWrap(this->getWrapR())<<std::endl;
  ss<<"GL_TEXTURE_TARGET: "            <<ge::gl::translateTextureTarget(this->getTarget())<<std::endl;
  ss<<"GL_TEXTURE_MIN_LOD: "           <<this->getMinLod()<<std::endl;
  ss<<"GL_TEXTURE_MAX_LOD: "           <<this->getMaxLod()<<std::endl;
  ss<<"GL_TEXTURE_BASE_LEVEL: "        <<this->getBaseLevel()<<std::endl;
  ss<<"GL_TEXTURE_MAX_LEVEL: "         <<this->getMaxLevel()<<std::endl;
  ss<<"GL_TEXTURE_LOD_BIAS: "          <<this->getLodBias()<<std::endl;
  ss<<"GL_DEPTH_STENCIL_TEXTURE_MODE: "<<this->getDepthStencilTextureMode()<<std::endl;
  ss<<"GL_TEXTURE_COMPARE_MODE: "      <<ge::gl::translateTextureCompareMode(this->getCompareMode())<<std::endl;
  ss<<"GL_TEXTURE_COMPARE_FUNC: "      <<ge::gl::translateTextureCompareFunc(this->getCompareFunc())<<std::endl;
  ss<<"GL_IMAGE_FORMAT_COMPATIBILITY_TYPE: "<<this->getImageFormatCompatibilityType()<<std::endl;
  ss<<"GL_TEXTURE_IMMUTABLE_FORMAT: "  <<(bool)this->getImmutableFormat()<<std::endl;
  ss<<"GL_TEXTURE_IMMUTABLE_LEVELS: "  <<this->getImmutableLevels()<<std::endl;
  ss<<"GL_TEXTURE_VIEW_MIN_LEVEL: "    <<this->getViewMinLevel ()<<std::endl;
  ss<<"GL_TEXTURE_VIEW_NUM_LEVELS: "   <<this->getViewNumLevels()<<std::endl;
  ss<<"GL_TEXTURE_VIEW_MIN_LAYER: "    <<this->getViewMinLayer ()<<std::endl;
  ss<<"GL_TEXTURE_VIEW_NUM_LAYERS: "   <<this->getViewNumLayers()<<std::endl;
  return ss.str();
}

bool TextureObject::hasHeight(){
  switch(this->_target){
    case GL_TEXTURE_1D_ARRAY            :
    case GL_TEXTURE_2D                  :
    case GL_TEXTURE_2D_ARRAY            :
    case GL_TEXTURE_2D_MULTISAMPLE      :
    case GL_TEXTURE_2D_MULTISAMPLE_ARRAY:
    case GL_TEXTURE_3D                  :
    case GL_TEXTURE_BUFFER              :
    case GL_TEXTURE_CUBE_MAP            :
    case GL_TEXTURE_RECTANGLE           :return true ;
    case GL_TEXTURE_1D                  :
    default                             :return false;
  }
}

bool TextureObject::hasDepth (){
   switch(this->_target){
    case GL_TEXTURE_2D_ARRAY            :
    case GL_TEXTURE_2D_MULTISAMPLE_ARRAY:
    case GL_TEXTURE_3D                  :
    case GL_TEXTURE_CUBE_MAP            :return true ;
    case GL_TEXTURE_1D                  :
    case GL_TEXTURE_1D_ARRAY            :
    case GL_TEXTURE_2D                  :
    case GL_TEXTURE_2D_MULTISAMPLE      :
    case GL_TEXTURE_RECTANGLE           :
    case GL_TEXTURE_BUFFER              :
    default                             :return false;
  }
}

unsigned long long TextureObject::getLevelSize(GLint level){
  unsigned long long size=internalFormatSize(this->getInternalFormat(level))*this->getWidth(level);
  if(this->hasHeight())size*=this->getHeight(level);
  if(this->hasDepth())size*=this->getDepth(level);
  return size/8;
}

unsigned long long TextureObject::getSize(){
  GLint nofLevels=this->getViewNumLayers();//TODO neco lepsiho?
  unsigned long long size=0;
  for(GLint l=0;l<nofLevels;++l)
    size+=this->getLevelSize(l);
  return size;
}

