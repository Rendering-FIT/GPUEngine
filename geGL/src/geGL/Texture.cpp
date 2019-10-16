#include<geGL/Texture.h>
#include<geGL/Framebuffer.h>
#include<geGL/OpenGLUtil.h>
#include<sstream>

//#include<GPUEngine/geCore/Dtemplates.h>

using namespace ge::gl;

Texture::Texture(){}

void Texture::create(
    GLenum  target        ,
    GLenum  internalFormat,
    GLsizei levels        ,
    GLsizei width         ,
    GLsizei height        ,
    GLsizei depth         ){
  assert(this!=nullptr);
  assert((width!=0)||(width!=0&&height!=0)||(width!=0&&height!=0&&depth!=0));
  this->_target = target;
  this->_format = internalFormat;
  this->getContext().glCreateTextures(this->_target,1,&this->getId());
  if(levels>0){
    if     (height == 0)this->getContext().glTextureStorage1D(this->getId(),levels,this->_format,width             );
    else if(depth  == 0)this->getContext().glTextureStorage2D(this->getId(),levels,this->_format,width,height      );
    else                this->getContext().glTextureStorage3D(this->getId(),levels,this->_format,width,height,depth);
  }else{
    if(target == GL_TEXTURE_CUBE_MAP){
      for(uint32_t i=0;i<6;++i){
        if     (height == 0)this->getContext().glTextureImage1DEXT(this->getId(),GL_TEXTURE_CUBE_MAP_POSITIVE_X+i,0,this->_format,width             ,0,GL_RGBA,GL_UNSIGNED_BYTE,nullptr);
        else if(depth  == 0)this->getContext().glTextureImage2DEXT(this->getId(),GL_TEXTURE_CUBE_MAP_POSITIVE_X+i,0,this->_format,width,height      ,0,GL_RGBA,GL_UNSIGNED_BYTE,nullptr);
        else                this->getContext().glTextureImage3DEXT(this->getId(),GL_TEXTURE_CUBE_MAP_POSITIVE_X+i,0,this->_format,width,height,depth,0,GL_RGBA,GL_UNSIGNED_BYTE,nullptr);
      }
    }else{
      if     (height == 0)this->getContext().glTextureImage1DEXT(this->getId(),this->_target,0,this->_format,width             ,0,GL_RGBA,GL_UNSIGNED_BYTE,nullptr);
      else if(depth  == 0)this->getContext().glTextureImage2DEXT(this->getId(),this->_target,0,this->_format,width,height      ,0,GL_RGBA,GL_UNSIGNED_BYTE,nullptr);
      else                this->getContext().glTextureImage3DEXT(this->getId(),this->_target,0,this->_format,width,height,depth,0,GL_RGBA,GL_UNSIGNED_BYTE,nullptr);
    }
  }
}

/**
 * @brief Creates 1D texture
 *
 * @param target target of texture
 * @param width x size of texture
 * @param internalFormat internal format of data of texture
 * @param levels number of mipmap levels, 0 - mutable texture
 */
Texture::Texture(
    GLenum  target,
    GLenum  internalFormat,
    GLsizei levels,
    GLsizei width){
  assert(this!=nullptr);
  this->create(target,internalFormat,levels,width);
}

/**
 * @brief Creates 2D texture
 *
 * @param target target of texture
 * @param width x size of texture
 * @param height y size of texture
 * @param internalFormat internal format of data of texture
 * @param levels number of mipmap levels
 */
Texture::Texture(
    GLenum  target,
    GLenum  internalFormat,
    GLsizei levels,
    GLsizei width,
    GLsizei height){
  assert(this!=nullptr);
  this->create(target,internalFormat,levels,width,height);
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
Texture::Texture(
    GLenum  target,
    GLenum  internalFormat,
    GLsizei levels,
    GLsizei width,
    GLsizei height,
    GLsizei depth){
  assert(this!=nullptr);
  this->create(target,internalFormat,levels,width,height,depth);
}



Texture::Texture(
    FunctionTablePointer const&table,
    GLenum  target,
    GLenum  internalFormat,
    GLsizei levels,
    GLsizei width):OpenGLObject(table){
  assert(this!=nullptr);
  this->create(target,internalFormat,levels,width);
}

Texture::Texture(
    FunctionTablePointer const&table,
    GLenum  target,
    GLenum  internalFormat,
    GLsizei levels,
    GLsizei width,
    GLsizei height):OpenGLObject(table){
  assert(this!=nullptr);
  this->create(target,internalFormat,levels,width,height);
}

Texture::Texture(
    FunctionTablePointer const&table,
    GLenum  target,
    GLenum  internalFormat,
    GLsizei levels,
    GLsizei width,
    GLsizei height,
    GLsizei depth):OpenGLObject(table){
  assert(this!=nullptr);
  this->create(target,internalFormat,levels,width,height,depth);
}


/**
 * @brief destroys texture
 */
Texture::~Texture(){
  assert(this!=nullptr);
  auto fs = _framebuffers;
  for(auto const&f:fs){
    std::vector<GLenum>attachments;
    for(auto const&a:f->_textureAttachments)
      if(a.second == this)
        attachments.push_back(a.first);
    for(auto const&a:attachments)
      f->attachTexture(a,nullptr);
  }
  this->getContext().glDeleteTextures(1,&this->getId());
}

/**
 * @brief binds texture to texture unit
 *
 * @param unit texture unit
 */
void   Texture::bind(GLuint unit)const{
  assert(this!=nullptr);
  this->getContext().glBindTextureUnit(unit,this->getId());
}

/**
 * @brief unbinds texture unit
 *
 * @param unit texture unit
 */
void Texture::unbind(GLuint unit)const{
  assert(this!=nullptr);
  this->getContext().glBindTextureUnit(unit,0);
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
void Texture::bindImage(
    GLuint    unit,
    GLint     level,
    GLenum    format,
    GLenum    access,
    GLboolean layered,
    GLint     layer)const{
  assert(this!=nullptr);
  if(format == 0)format=this->_format;
  this->getContext().glBindImageTexture(unit,this->getId(),level,layered,
      layer,access,format);
}

void Texture::setData1D(
    const GLvoid*data   ,
    GLenum       format ,
    GLenum       type   ,
    GLint        level  ,
    GLint        xoffset,
    GLsizei      width  )const{
  assert(this!=nullptr);
  if(width==0)width=this->getWidth(0);
  for(GLint l=0;l<level;++l)width/=2;
  this->getContext().glTextureSubImage1D(this->getId(),level,xoffset,width,format,type,data);
}

void Texture::setData2D(
    const GLvoid*data     ,
    GLenum       format   ,
    GLenum       type     ,
    GLint        level    ,
    GLenum       target   ,
    GLint        xoffset  ,
    GLint        yoffset  ,
    GLsizei      width    ,
    GLsizei      height   ,
    GLint        rowLength)const{
  assert(this!=nullptr);
  if(width==0){
    width  = this->getWidth (0);
    height = this->getHeight(0);
    height = this->getHeight(0);
    for(GLint l=0;l<level;++l){
      width /=2;
      height/=2;
    }
  }
  if(rowLength==0)rowLength=width;
  this->getContext().glPixelStorei(GL_UNPACK_ROW_LENGTH,rowLength);
    
  this->getContext().glPixelStorei(GL_UNPACK_ALIGNMENT ,1        );
  if(target!=0){
    this->getContext().glTextureSubImage2DEXT(this->getId(),target       ,level,xoffset,yoffset,width,height,format,type,data);
  }else{
    this->getContext().glTextureSubImage2DEXT(this->getId(),this->_target,level,xoffset,yoffset,width,height,format,type,data);
  }
  this->getContext().glPixelStorei(GL_UNPACK_ALIGNMENT ,4);
  this->getContext().glPixelStorei(GL_UNPACK_ROW_LENGTH,0);
}

void Texture::setData3D(
    const GLvoid*data     ,
    GLenum       format   ,
    GLenum       type     ,
    GLint        level    ,
    GLenum       target   ,
    GLint        xoffset  ,
    GLint        yoffset  ,
    GLint        zoffset  ,
    GLsizei      width    ,
    GLsizei      height   ,
    GLsizei      depth    ,
    GLint        rowLength,
    GLint        imgHeight)const{
  assert(this!=nullptr);
  if(width==0){
    width  = this->getWidth (0);
    height = this->getHeight(0);
    depth  = this->getDepth (0);
    for(GLint l=0;l<level;++l){
      width /=2;
      height/=2;
      depth /=2;
    }
  }
  if(rowLength==0)rowLength=width;
  if(imgHeight==0)imgHeight=height;
  this->getContext().glPixelStorei(GL_UNPACK_ROW_LENGTH  ,rowLength);
  this->getContext().glPixelStorei(GL_UNPACK_IMAGE_HEIGHT,imgHeight);
  this->getContext().glPixelStorei(GL_UNPACK_ALIGNMENT   ,1        );
  if(target!=0)
    this->getContext().glTextureSubImage3DEXT(this->getId(),target       ,level,xoffset,yoffset,zoffset,width,height,depth,format,type,data);
  else
    this->getContext().glTextureSubImage3DEXT(this->getId(),this->_target,level,xoffset,yoffset,zoffset,width,height,depth,format,type,data);
  this->getContext().glPixelStorei(GL_UNPACK_ALIGNMENT   ,4);
  this->getContext().glPixelStorei(GL_UNPACK_ROW_LENGTH  ,0);
  this->getContext().glPixelStorei(GL_UNPACK_IMAGE_HEIGHT,0);
}

void Texture::getCompressedData(void*data,GLsizei bufSize,GLint level){
  getContext().glGetCompressedTextureImage(getId(),level,bufSize,data);
}

void Texture::getCompressedData(std::vector<uint8_t>&data,GLint level){
  auto const bufSize = getCompressedImageSize(level);
  data.resize(bufSize);
  getCompressedData(data.data(),bufSize,level);
}

void Texture::generateMipmap()const{
  assert(this!=nullptr);
  this->getContext().glGenerateTextureMipmap(this->getId());
}

void Texture::clear(
    GLint        level ,
    GLenum       format,
    GLenum       type  ,
    GLvoid const*data  ){
  assert(this!=nullptr);
  this->getContext().glClearTexImage(this->getId(),level,format,type,data);
}


/**
 * @brief sets parameters of texture
 *
 * @param pname name of parameter
 * @param params value of parameter
 */
void Texture::texParameteri(GLenum pname,GLint params)const{
  assert(this!=nullptr);
  this->getContext().glTextureParameteri(this->getId(),pname,params);
}

/**
 * @brief sets parameters of texture
 *
 * @param pname name of parameter
 * @param params values of parameter
 */
void Texture::texParameterfv(GLenum pname,GLfloat *params)const{
  assert(this!=nullptr);
#ifndef USE_DSA
  this->getContext().glBindTexture   (this->getTarget(),this->getId());
  this->getContext().glTexParameterfv(this->getTarget(),pname,params);
#else //USE_DSA
  this->getContext().glTextureParameterfv(this->getId(),pname,params);
#endif//USE_DSA
}


/**
 * @brief gets internal format of texture
 *
 * @return format
 */
GLenum Texture::getFormat()const{
  assert(this!=nullptr);
  return this->_format;
  //glGetTextureParameteriv(this->getId(),GL_TEXTURE_INTERNAL_FORMAT,(GLint*)format);
}

GLuint Texture::_bindSafe()const{
  assert(this!=nullptr);
  GLuint oldId;
  GLenum target=this->getTarget();
  this->getContext().glGetIntegerv(ge::gl::textureTarget2Binding(target),(GLint*)&oldId);
  this->getContext().glBindTexture(target,this->getId());
  return oldId;
}

GLint Texture::_getTexLevelParameter(GLint level,GLenum pname)const{
  assert(this!=nullptr);
  GLint param;
#ifndef USE_DSA
  GLuint oldId=this->_bindSafe();
  GLenum target = this->getTarget();
  if(target == GL_TEXTURE_CUBE_MAP)target = GL_TEXTURE_CUBE_MAP_POSITIVE_X;
  this->getContext().glGetTexLevelParameteriv(target,level,pname,&param);
  this->getContext().glBindTexture(this->getTarget(),oldId);
#else //USE_DSA
  this->getContext().glGetTextureLevelParameteriv(this->getId(),level,pname,&param);
#endif//USE_DSA
  return param;
}

GLint Texture::_getTexParameter(GLenum pname)const{
  assert(this!=nullptr);
  GLint param;
#ifndef USE_DSA
  GLuint oldId=this->_bindSafe();
  this->getContext().glGetTexParameteriv(this->getTarget(),pname,&param);
  this->getContext().glBindTexture(this->getTarget(),oldId);
#else //USE_DSA
  this->getContext().glGetTextureParameteriv(this->getId(),pname,&param));
#endif//USE_DSA
  return param;
}

void Texture::_getTexParameterf(GLfloat*data,GLenum pname)const{
  assert(this!=nullptr);
#ifndef USE_DSA
  GLuint oldId=this->_bindSafe();
  this->getContext().glGetTexParameterfv(this->getTarget(),pname,data);
  this->getContext().glBindTexture(this->getTarget(),oldId);
#else
  this->getContext().glGetTextureParameterfv(this->getId(),pname,data);
#endif//USE_DSA
}

/**
 * @brief gets width of texture at specific level
 *
 * @param level level of mipmap
 *
 * @return width of mipmap
 */
GLuint Texture::getWidth(GLint level)const{
  assert(this!=nullptr);
  return this->_getTexLevelParameter(level,GL_TEXTURE_WIDTH);

}

/**
 * @brief gets height of texture at specific level
 *
 * @param level level of mipmap
 *
 * @return height of mipmap
 */
GLuint Texture::getHeight(GLint level)const{
  assert(this!=nullptr);
  return this->_getTexLevelParameter(level,GL_TEXTURE_HEIGHT);
}

/**
 * @brief gets depth of texture at specific level
 *
 * @param level level of mipmap
 *
 * @return depth of mipmap
 */
GLuint Texture::getDepth(GLint level)const{
  assert(this!=nullptr);
  return this->_getTexLevelParameter(level,GL_TEXTURE_DEPTH);
}

/**
 * @brief gets number of samples 
 *
 * @param level level of mipmap
 *
 * @return number of samples
 */
GLuint Texture::getSamples(GLint level)const{
  assert(this!=nullptr);
  return this->_getTexLevelParameter(level,GL_TEXTURE_SAMPLES);
}

/**
 * @brief gets fixed sample location
 *
 * @param level level of mipmap
 *
 * @return fixed sample location
 */
GLboolean Texture::getFixedSampleLocation(GLint level)const{
  assert(this!=nullptr);
  return (GLboolean)this->_getTexLevelParameter(level,GL_TEXTURE_FIXED_SAMPLE_LOCATIONS);
}

/**
 * @brief gets internal format
 *
 * @param level level of mipmap
 *
 * @return internal format
 */
GLenum Texture::getInternalFormat(GLint level)const{
  assert(this!=nullptr);
  return this->_getTexLevelParameter(level,GL_TEXTURE_INTERNAL_FORMAT);
}

/**
 * @brief gets red size
 *
 * @param level level of mipmap
 *
 * @return red size
 */
GLuint Texture::getRedSize(GLint level)const{
  assert(this!=nullptr);
  return this->_getTexLevelParameter(level,GL_TEXTURE_RED_SIZE);
}

/**
 * @brief gets green size
 *
 * @param level level of mipmap
 *
 * @return green size
 */
GLuint Texture::getGreenSize(GLint level)const{
  assert(this!=nullptr);
  return this->_getTexLevelParameter(level,GL_TEXTURE_GREEN_SIZE);
}

/**
 * @brief gets blue size
 *
 * @param level level of mipmap
 *
 * @return blue size
 */
GLuint Texture::getBlueSize(GLint level)const{
  assert(this!=nullptr);
  return this->_getTexLevelParameter(level,GL_TEXTURE_BLUE_SIZE);
}

/**
 * @brief gets alpha size
 *
 * @param level level of mipmap
 *
 * @return alpha size
 */
GLuint Texture::getAlphaSize(GLint level)const{
  assert(this!=nullptr);
  return this->_getTexLevelParameter(level,GL_TEXTURE_ALPHA_SIZE);
}

/**
 * @brief gets depth size
 *
 * @param level level of mipmap
 *
 * @return depth size
 */
GLuint Texture::getDepthSize(GLint level)const{
  assert(this!=nullptr);
  return this->_getTexLevelParameter(level,GL_TEXTURE_DEPTH_SIZE);
}

/**
 * @brief gets stencil size
 *
 * @param level level of mipmap
 *
 * @return stencil size
 */
GLuint Texture::getStencilSize(GLint level)const{
  assert(this!=nullptr);
  return this->_getTexLevelParameter(level,GL_TEXTURE_STENCIL_SIZE);
}

/**
 * @brief gets shared size
 *
 * @param level level of mipmap
 *
 * @return shared size
 */
GLuint Texture::getSharedSize(GLint level)const{
  assert(this!=nullptr);
  return this->_getTexLevelParameter(level,GL_TEXTURE_SHARED_SIZE);
}

/**
 * @brief gets red type
 *
 * @param level level of mipmap
 *
 * @return red type
 */
GLenum Texture::getRedType(GLint level)const{
  assert(this!=nullptr);
  return this->_getTexLevelParameter(level,GL_TEXTURE_RED_TYPE);
}

/**
 * @brief gets blue type
 *
 * @param level level of mipmap
 *
 * @return blue type
 */
GLenum Texture::getBlueType(GLint level)const{
  assert(this!=nullptr);
  return this->_getTexLevelParameter(level,GL_TEXTURE_BLUE_TYPE);
}

/**
 * @brief gets green type
 *
 * @param level level of mipmap
 *
 * @return green type
 */
GLenum Texture::getGreenType(GLint level)const{
  assert(this!=nullptr);
  return this->_getTexLevelParameter(level,GL_TEXTURE_GREEN_TYPE);
}

/**
 * @brief gets alpha type
 *
 * @param level level of mipmap
 *
 * @return alpha type
 */
GLenum Texture::getAlphaType(GLint level)const{
  assert(this!=nullptr);
  return this->_getTexLevelParameter(level,GL_TEXTURE_ALPHA_TYPE);
}

/**
 * @brief gets depth type
 *
 * @param level level of mipmap
 *
 * @return depth type
 */
GLenum Texture::getDepthType(GLint level)const{
  assert(this!=nullptr);
  return this->_getTexLevelParameter(level,GL_TEXTURE_DEPTH_TYPE);
}

/**
 * @brief gets compressed flag
 *
 * @param level level of mipmap
 *
 * @return compressed flag
 */
GLboolean Texture::getCompressed(GLint level)const{
  assert(this!=nullptr);
  return (GLboolean)this->_getTexLevelParameter(level,GL_TEXTURE_COMPRESSED);
}

/**
 * @brief gets compressed image size
 *
 * @param level level of mipmap
 *
 * @return compressed image size
 */
GLuint Texture::getCompressedImageSize(GLint level)const{
  assert(this!=nullptr);
  return this->_getTexLevelParameter(level,GL_TEXTURE_COMPRESSED_IMAGE_SIZE);
}

/**
 * @brief gets texture buffer binding
 *
 * @param level mipmap level
 *
 * @return texture buffer binding
 */
GLuint Texture::getBufferDataStoreBinding(GLint level)const{
  assert(this!=nullptr);
  return this->_getTexLevelParameter(level,GL_TEXTURE_BUFFER_DATA_STORE_BINDING);
}

/**
 * @brief gets texture buffer offset
 *
 * @param level mipmap level
 *
 * @return texture buffer offset
 */
GLint Texture::getBufferOffset(GLint level)const{
  assert(this!=nullptr);
  return this->_getTexLevelParameter(level,GL_TEXTURE_BUFFER_OFFSET);
}

/**
 * @brief gets texture buffer size
 *
 * @param level mipmap level
 *
 * @return texture buffer size
 */
GLint Texture::getBufferSize(GLint level)const{
  assert(this!=nullptr);
  return this->_getTexLevelParameter(level,GL_TEXTURE_BUFFER_SIZE);
}

/**
 * @brief gets red swizzle
 *
 * @return red swizzle
 */
GLenum Texture::getSwizzleR()const{
  assert(this!=nullptr);
  return this->_getTexParameter(GL_TEXTURE_SWIZZLE_R);
}

/**
 * @brief gets green swizzle
 *
 * @return green swizzle
 */
GLenum Texture::getSwizzleG()const{
  assert(this!=nullptr);
  return this->_getTexParameter(GL_TEXTURE_SWIZZLE_G);
}

/**
 * @brief gets blue swizzle
 *
 * @return blue swizzle
 */
GLenum Texture::getSwizzleB()const{
  assert(this!=nullptr);
  return this->_getTexParameter(GL_TEXTURE_SWIZZLE_B);
}

/**
 * @brief gets alpha swizzle
 *
 * @return alpha swizzle
 */
GLenum Texture::getSwizzleA()const{
  assert(this!=nullptr);
  return this->_getTexParameter(GL_TEXTURE_SWIZZLE_A);
}

/**
 * @brief gets border color
 *
 * @param color border color
 */
void Texture::getBorderColor(GLfloat*color)const{
  assert(this!=nullptr);
  this->_getTexParameterf(color,GL_TEXTURE_BORDER_COLOR);
}

/**
 * @brief gets min filter
 *
 * @return min filter
 */
GLenum Texture::getMinFilter()const{
  assert(this!=nullptr);
  return this->_getTexParameter(GL_TEXTURE_MIN_FILTER);
}

/**
 * @brief gets mag filter
 *
 * @return mag filter
 */
GLenum Texture::getMagFilter()const{
  assert(this!=nullptr);
  return this->_getTexParameter(GL_TEXTURE_MAG_FILTER);
}

/**
 * @brief gets wrapS
 *
 * @return wrapS
 */
GLenum Texture::getWrapS()const{
  assert(this!=nullptr);
  return this->_getTexParameter(GL_TEXTURE_WRAP_S);
}

/**
 * @brief gets wrapT
 *
 * @return wrapT
 */
GLenum Texture::getWrapT()const{
  assert(this!=nullptr);
  return this->_getTexParameter(GL_TEXTURE_WRAP_T);
}

/**
 * @brief gets wrapR
 *
 * @return wrapR
 */
GLenum Texture::getWrapR()const{
  assert(this!=nullptr);
  return this->_getTexParameter(GL_TEXTURE_WRAP_R);
}

/**
 * @brief gets target of texture
 *
 * @return target
 */
GLenum Texture::getTarget()const{
  assert(this!=nullptr);
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
GLfloat Texture::getMinLod()const{
  assert(this!=nullptr);
  GLfloat lod;
  this->_getTexParameterf(&lod,GL_TEXTURE_MIN_LOD);
  return lod;
}

/**
 * @brief gets texture maxlod
 *
 * @return texture maxlod
 */
GLfloat Texture::getMaxLod()const{
  assert(this!=nullptr);
  GLfloat lod;
  this->_getTexParameterf(&lod,GL_TEXTURE_MAX_LOD);
  return lod;
}

/**
 * @brief gets texture base level
 *
 * @return texture base level
 */
GLuint Texture::getBaseLevel()const{
  assert(this!=nullptr);
  return this->_getTexParameter(GL_TEXTURE_BASE_LEVEL);
}

/**
 * @brief gets texture max level
 *
 * @return texture max level
 */
GLuint Texture::getMaxLevel()const{
  assert(this!=nullptr);
  return this->_getTexParameter(GL_TEXTURE_MAX_LEVEL);
}

/**
 * @brief gets texture lod bias
 *
 * @return texture lod bias
 */
GLfloat Texture::getLodBias()const{
  assert(this!=nullptr);
  GLfloat bias;
  this->_getTexParameterf(&bias,GL_TEXTURE_LOD_BIAS);
  return bias;
}

/**
 * @brief gets depth stencil texture mode
 *
 * @return depth stencil texture mode
 */
GLenum Texture::getDepthStencilTextureMode()const{
  assert(this!=nullptr);
  return this->_getTexParameter(GL_DEPTH_STENCIL_TEXTURE_MODE);
}

/**
 * @brief gets texture compare mode
 *
 * @return texture compare mode
 */
GLenum Texture::getCompareMode()const{
  assert(this!=nullptr);
  return this->_getTexParameter(GL_TEXTURE_COMPARE_MODE);
}

/**
 * @brief gets texture compare func
 *
 * @return texture compare func
 */
GLenum Texture::getCompareFunc()const{
  assert(this!=nullptr);
  return this->_getTexParameter(GL_TEXTURE_COMPARE_FUNC);
}

/**
 * @brief gets texture image format compatibility type
 *
 * @return texture image format compatibility type
 */
GLenum Texture::getImageFormatCompatibilityType()const{
  assert(this!=nullptr);
  return this->_getTexParameter(GL_IMAGE_FORMAT_COMPATIBILITY_TYPE);
}

/**
 * @brief gets texture immutable format
 *
 * @return texture immutable format
 */
GLboolean Texture::getImmutableFormat()const{
  assert(this!=nullptr);
  return (GLboolean)this->_getTexParameter(GL_TEXTURE_IMMUTABLE_FORMAT);
}

/**
 * @brief gets texture immutable levels
 *
 * @return texture immutable levels
 */
GLuint Texture::getImmutableLevels()const{
  assert(this!=nullptr);
  return this->_getTexParameter(GL_TEXTURE_IMMUTABLE_LEVELS);
}

/**
 * @brief gets texture view min level
 *
 * @return texture view min level
 */
GLuint Texture::getViewMinLevel()const{
  assert(this!=nullptr);
  return this->_getTexParameter(GL_TEXTURE_VIEW_MIN_LEVEL);
}

/**
 * @brief gets texture view num levels
 *
 * @return texture view num levels
 */
GLuint Texture::getViewNumLevels()const{
  assert(this!=nullptr);
  return this->_getTexParameter(GL_TEXTURE_VIEW_NUM_LEVELS);
}

/**
 * @brief gets texture view min layer
 *
 * @return texture view min layer
 */
GLuint Texture::getViewMinLayer()const{
  assert(this!=nullptr);
  return this->_getTexParameter(GL_TEXTURE_VIEW_MIN_LAYER);
}

/**
 * @brief gets texture view num layers
 *
 * @return texture view num layers
 */
GLuint Texture::getViewNumLayers()const{
  assert(this!=nullptr);
  return this->_getTexParameter(GL_TEXTURE_VIEW_NUM_LAYERS);
}


std::string Texture::getInfo()const{
  assert(this!=nullptr);
  std::stringstream ss;
  ss<<"GL_TEXTURE_WIDTH: " <<this->getWidth (0)<<std::endl;
  ss<<"GL_TEXTURE_HEIGHT: "<<this->getHeight(0)<<std::endl;
  if(this->getTarget()==GL_TEXTURE_3D)//TODO array 2D, etc
    ss<<"GL_TEXTURE_DEPTH: "           <<this->getDepth (0)<<std::endl;

  ss<<"GL_TEXTURE_SAMPLES: "                  <<this->getSamples               (0)<<std::endl;
  ss<<"GL_TEXTURE_FIXED_SAMPLE_LOCATIONS: "   <<(bool)(0!=this->getFixedSampleLocation   (0))<<std::endl;
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
  ss<<"GL_IMAGE_FORMAT_COMPATIBILITY_TYPE: "<<ge::gl::translateImageFormatCompatibilityType(this->getImageFormatCompatibilityType())<<std::endl;
  ss<<"GL_TEXTURE_IMMUTABLE_FORMAT: "  <<(bool)(0!=this->getImmutableFormat())<<std::endl;
  ss<<"GL_TEXTURE_IMMUTABLE_LEVELS: "  <<this->getImmutableLevels()<<std::endl;
  ss<<"GL_TEXTURE_VIEW_MIN_LEVEL: "    <<this->getViewMinLevel ()<<std::endl;
  ss<<"GL_TEXTURE_VIEW_NUM_LEVELS: "   <<this->getViewNumLevels()<<std::endl;
  ss<<"GL_TEXTURE_VIEW_MIN_LAYER: "    <<this->getViewMinLayer ()<<std::endl;
  ss<<"GL_TEXTURE_VIEW_NUM_LAYERS: "   <<this->getViewNumLayers()<<std::endl;
  return ss.str();
}

bool Texture::hasHeight()const{
  assert(this!=nullptr);
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

bool Texture::hasDepth ()const{
  assert(this!=nullptr);
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

unsigned long long Texture::getLevelSize(GLint level)const{
  assert(this!=nullptr);
  unsigned long long size=internalFormatSize(this->getInternalFormat(level))*this->getWidth(level);
  if(this->hasHeight())size*=this->getHeight(level);
  if(this->hasDepth())size*=this->getDepth(level);
  return size/8;
}

unsigned long long Texture::getSize()const{
  assert(this!=nullptr);
  GLint nofLevels=this->getViewNumLayers();//TODO neco lepsiho?
  unsigned long long size=0;
  for(GLint l=0;l<nofLevels;++l)
    size+=this->getLevelSize(l);
  return size;
}

