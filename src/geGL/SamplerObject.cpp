#include<geGL/SamplerObject.h>

using namespace ge::gl;

SamplerObject::SamplerObject(){
  glCreateSamplers(1,&this->_id);
}

SamplerObject::SamplerObject(SamplerObject*sampler){
  glCreateSamplers(1,&this->_id);
  GLfloat borderColor[4];
  sampler->getBorderColor(borderColor);
  this->setBorderColor(borderColor);

  GLenum compareFunc = sampler->getCompareFunc();
  this->setCompareFunc(compareFunc);

  GLenum compareMode = sampler->getCompareMode();
  this->setCompareMode(compareMode);

  GLfloat lodBias = sampler->getLodBias();
  this->setLodBias(lodBias);

  GLfloat minLod = sampler->getMinLod();
  this->setMinLod(minLod);

  GLfloat maxLod = sampler->getMaxLod();
  this->setMinLod(maxLod);

  GLenum minFilter =  sampler->getMinFilter();
  this->setMinFilter(minFilter);

  GLenum magFilter = sampler->getMagFilter();
  this->setMagFilter(magFilter);

  GLenum wrapS = sampler->getWrapS();
  this->setWrapS(wrapS);

  GLenum wrapT = sampler->getWrapT();
  this->setWrapS(wrapT);

  GLenum wrapR = sampler->getWrapR();
  this->setWrapS(wrapR);
}

#if defined(REPLACE_GLEW)
SamplerObject::SamplerObject (
    std::shared_ptr<OpenGLFunctionTable>const&table):OpenGLObject(table){
  glCreateSamplers(1,&this->_id);
}
SamplerObject::SamplerObject(
    std::shared_ptr<OpenGLFunctionTable>const&table,
    SamplerObject*sampler):OpenGLObject(table){
  glCreateSamplers(1,&this->_id);
  GLfloat borderColor[4];
  sampler->getBorderColor(borderColor);
  this->setBorderColor(borderColor);

  GLenum compareFunc = sampler->getCompareFunc();
  this->setCompareFunc(compareFunc);

  GLenum compareMode = sampler->getCompareMode();
  this->setCompareMode(compareMode);

  GLfloat lodBias = sampler->getLodBias();
  this->setLodBias(lodBias);

  GLfloat minLod = sampler->getMinLod();
  this->setMinLod(minLod);

  GLfloat maxLod = sampler->getMaxLod();
  this->setMinLod(maxLod);

  GLenum minFilter =  sampler->getMinFilter();
  this->setMinFilter(minFilter);

  GLenum magFilter = sampler->getMagFilter();
  this->setMagFilter(magFilter);

  GLenum wrapS = sampler->getWrapS();
  this->setWrapS(wrapS);

  GLenum wrapT = sampler->getWrapT();
  this->setWrapS(wrapT);

  GLenum wrapR = sampler->getWrapR();
  this->setWrapS(wrapR);

}

#endif


SamplerObject::~SamplerObject(){
  glDeleteSamplers(1,&this->_id);
}

void SamplerObject::setBorderColor(GLfloat*color    )const{
  glSamplerParameterfv(this->_id,GL_TEXTURE_BORDER_COLOR,color);
}

void SamplerObject::setCompareFunc(GLenum  func     )const{
  glSamplerParameteri(this->_id,GL_TEXTURE_COMPARE_FUNC,func);
}

void SamplerObject::setCompareMode(GLenum  mode     )const{
  glSamplerParameteri(this->_id,GL_TEXTURE_COMPARE_MODE,mode);
}

void SamplerObject::setLodBias    (GLfloat lodBias  )const{
  glSamplerParameterf(this->_id,GL_TEXTURE_LOD_BIAS,lodBias);
}

void SamplerObject::setMinLod     (GLfloat minLod   )const{
  glSamplerParameterf(this->_id,GL_TEXTURE_MIN_LOD,minLod);
}

void SamplerObject::setMaxLod     (GLfloat maxLod   )const{
  glSamplerParameterf(this->_id,GL_TEXTURE_MAX_LOD,maxLod);
}

void SamplerObject::setMinFilter  (GLenum  minFilter)const{
  glSamplerParameteri(this->_id,GL_TEXTURE_MIN_FILTER,minFilter);
}

void SamplerObject::setMagFilter  (GLenum  magFilter)const{
  glSamplerParameteri(this->_id,GL_TEXTURE_MAG_FILTER,magFilter);
}

void SamplerObject::setWrapS      (GLenum  wrapS    )const{
  glSamplerParameteri(this->_id,GL_TEXTURE_WRAP_S,wrapS);
}

void SamplerObject::setWrapT      (GLenum  wrapT    )const{
  glSamplerParameteri(this->_id,GL_TEXTURE_WRAP_T,wrapT);
}

void SamplerObject::setWrapR      (GLenum  wrapR    )const{
  glSamplerParameteri(this->_id,GL_TEXTURE_WRAP_R,wrapR);
}

void SamplerObject::getBorderColor(GLfloat*color    )const{
  glGetSamplerParameterfv(this->_id,GL_TEXTURE_BORDER_COLOR,color);
}

GLenum SamplerObject::getCompareFunc()const{
  GLenum func;
  glGetSamplerParameteriv(this->_id,GL_TEXTURE_COMPARE_FUNC,(GLint*)&func);
  return func;
}

GLenum SamplerObject::getCompareMode()const{
  GLenum mode;
  glGetSamplerParameteriv(this->_id,GL_TEXTURE_COMPARE_MODE,(GLint*)&mode);
  return mode;
}

GLfloat SamplerObject::getLodBias()const{
  GLfloat lodBias;
  glGetSamplerParameterfv(this->_id,GL_TEXTURE_LOD_BIAS,&lodBias);
  return lodBias;
}

GLfloat SamplerObject::getMinLod()const{
  GLfloat minLod;
  glGetSamplerParameterfv(this->_id,GL_TEXTURE_MIN_LOD,&minLod);
  return minLod;
}

GLfloat SamplerObject::getMaxLod()const{
  GLfloat maxLod;
  glGetSamplerParameterfv(this->_id,GL_TEXTURE_MAX_LOD,&maxLod);
  return maxLod;
}

GLenum SamplerObject::getMinFilter()const{
  GLenum minFilter;
  glGetSamplerParameteriv(this->_id,GL_TEXTURE_MIN_FILTER,(GLint*)&minFilter);
  return minFilter;
}

GLenum SamplerObject::getMagFilter()const{
  GLenum magFilter;
  glGetSamplerParameteriv(this->_id,GL_TEXTURE_MAG_FILTER,(GLint*)&magFilter);
  return magFilter;
}

GLenum SamplerObject::getWrapS()const{
  GLenum wrapS;
  glGetSamplerParameteriv(this->_id,GL_TEXTURE_WRAP_S,(GLint*)&wrapS);
  return wrapS;
}

GLenum SamplerObject::getWrapT()const{
  GLenum wrapT;
  glGetSamplerParameteriv(this->_id,GL_TEXTURE_WRAP_T,(GLint*)&wrapT);
  return wrapT;
}

GLenum SamplerObject::getWrapR()const{
  GLenum wrapR;
  glGetSamplerParameteriv(this->_id,GL_TEXTURE_WRAP_R,(GLint*)&wrapR);
  return wrapR;
}

void SamplerObject::bind(GLuint unit)const{
  glBindSampler(unit,this->_id);
}

void SamplerObject::unbind(GLuint unit)const{
  glBindSampler(unit,0);
}
