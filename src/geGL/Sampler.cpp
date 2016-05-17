#include<geGL/Sampler.h>

using namespace ge::gl;
using namespace ge::gl::opengl;

Sampler::Sampler(){
  glCreateSamplers(1,&this->_id);
}

Sampler::Sampler(Sampler*sampler){
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

Sampler::Sampler (
    FunctionTablePointer const&table):OpenGLObject(table){
  glCreateSamplers(1,&this->_id);
}

Sampler::Sampler(
    FunctionTablePointer const&table,
    Sampler*sampler):OpenGLObject(table){
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

Sampler::~Sampler(){
  glDeleteSamplers(1,&this->_id);
}

void Sampler::setBorderColor(GLfloat*color    )const{
  glSamplerParameterfv(this->_id,GL_TEXTURE_BORDER_COLOR,color);
}

void Sampler::setCompareFunc(GLenum  func     )const{
  glSamplerParameteri(this->_id,GL_TEXTURE_COMPARE_FUNC,func);
}

void Sampler::setCompareMode(GLenum  mode     )const{
  glSamplerParameteri(this->_id,GL_TEXTURE_COMPARE_MODE,mode);
}

void Sampler::setLodBias    (GLfloat lodBias  )const{
  glSamplerParameterf(this->_id,GL_TEXTURE_LOD_BIAS,lodBias);
}

void Sampler::setMinLod     (GLfloat minLod   )const{
  glSamplerParameterf(this->_id,GL_TEXTURE_MIN_LOD,minLod);
}

void Sampler::setMaxLod     (GLfloat maxLod   )const{
  glSamplerParameterf(this->_id,GL_TEXTURE_MAX_LOD,maxLod);
}

void Sampler::setMinFilter  (GLenum  minFilter)const{
  glSamplerParameteri(this->_id,GL_TEXTURE_MIN_FILTER,minFilter);
}

void Sampler::setMagFilter  (GLenum  magFilter)const{
  glSamplerParameteri(this->_id,GL_TEXTURE_MAG_FILTER,magFilter);
}

void Sampler::setWrapS      (GLenum  wrapS    )const{
  glSamplerParameteri(this->_id,GL_TEXTURE_WRAP_S,wrapS);
}

void Sampler::setWrapT      (GLenum  wrapT    )const{
  glSamplerParameteri(this->_id,GL_TEXTURE_WRAP_T,wrapT);
}

void Sampler::setWrapR      (GLenum  wrapR    )const{
  glSamplerParameteri(this->_id,GL_TEXTURE_WRAP_R,wrapR);
}

void Sampler::getBorderColor(GLfloat*color    )const{
  glGetSamplerParameterfv(this->_id,GL_TEXTURE_BORDER_COLOR,color);
}

GLenum Sampler::getCompareFunc()const{
  GLenum func;
  glGetSamplerParameteriv(this->_id,GL_TEXTURE_COMPARE_FUNC,(GLint*)&func);
  return func;
}

GLenum Sampler::getCompareMode()const{
  GLenum mode;
  glGetSamplerParameteriv(this->_id,GL_TEXTURE_COMPARE_MODE,(GLint*)&mode);
  return mode;
}

GLfloat Sampler::getLodBias()const{
  GLfloat lodBias;
  glGetSamplerParameterfv(this->_id,GL_TEXTURE_LOD_BIAS,&lodBias);
  return lodBias;
}

GLfloat Sampler::getMinLod()const{
  GLfloat minLod;
  glGetSamplerParameterfv(this->_id,GL_TEXTURE_MIN_LOD,&minLod);
  return minLod;
}

GLfloat Sampler::getMaxLod()const{
  GLfloat maxLod;
  glGetSamplerParameterfv(this->_id,GL_TEXTURE_MAX_LOD,&maxLod);
  return maxLod;
}

GLenum Sampler::getMinFilter()const{
  GLenum minFilter;
  glGetSamplerParameteriv(this->_id,GL_TEXTURE_MIN_FILTER,(GLint*)&minFilter);
  return minFilter;
}

GLenum Sampler::getMagFilter()const{
  GLenum magFilter;
  glGetSamplerParameteriv(this->_id,GL_TEXTURE_MAG_FILTER,(GLint*)&magFilter);
  return magFilter;
}

GLenum Sampler::getWrapS()const{
  GLenum wrapS;
  glGetSamplerParameteriv(this->_id,GL_TEXTURE_WRAP_S,(GLint*)&wrapS);
  return wrapS;
}

GLenum Sampler::getWrapT()const{
  GLenum wrapT;
  glGetSamplerParameteriv(this->_id,GL_TEXTURE_WRAP_T,(GLint*)&wrapT);
  return wrapT;
}

GLenum Sampler::getWrapR()const{
  GLenum wrapR;
  glGetSamplerParameteriv(this->_id,GL_TEXTURE_WRAP_R,(GLint*)&wrapR);
  return wrapR;
}

void Sampler::bind(GLuint unit)const{
  glBindSampler(unit,this->_id);
}

void Sampler::unbind(GLuint unit)const{
  glBindSampler(unit,0);
}
