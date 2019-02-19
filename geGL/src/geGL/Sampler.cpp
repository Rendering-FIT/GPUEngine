#include<geGL/Sampler.h>

using namespace ge::gl;

Sampler::Sampler(){
  assert(this!=nullptr);
  this->getContext().glCreateSamplers(1,&this->getId());
}

Sampler::Sampler(Sampler*sampler){
  assert(this!=nullptr);
  this->getContext().glCreateSamplers(1,&this->getId());
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
  assert(this!=nullptr);
  this->getContext().glCreateSamplers(1,&this->getId());
}

Sampler::Sampler(
    FunctionTablePointer const&table,
    Sampler*sampler):OpenGLObject(table){
  assert(this!=nullptr);
  this->getContext().glCreateSamplers(1,&this->getId());
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
  assert(this!=nullptr);
  this->getContext().glDeleteSamplers(1,&this->getId());
}

void Sampler::setBorderColor(GLfloat const*const&color    )const{
  assert(this!=nullptr);
  this->getContext().glSamplerParameterfv(this->getId(),GL_TEXTURE_BORDER_COLOR,color);
}

void Sampler::setCompareFunc(GLenum  const&func     )const{
  assert(this!=nullptr);
  this->getContext().glSamplerParameteri(this->getId(),GL_TEXTURE_COMPARE_FUNC,func);
}

void Sampler::setCompareMode(GLenum  const&mode     )const{
  assert(this!=nullptr);
  this->getContext().glSamplerParameteri(this->getId(),GL_TEXTURE_COMPARE_MODE,mode);
}

void Sampler::setLodBias    (GLfloat const&lodBias  )const{
  assert(this!=nullptr);
  this->getContext().glSamplerParameterf(this->getId(),GL_TEXTURE_LOD_BIAS,lodBias);
}

void Sampler::setMinLod     (GLfloat const&minLod   )const{
  assert(this!=nullptr);
  this->getContext().glSamplerParameterf(this->getId(),GL_TEXTURE_MIN_LOD,minLod);
}

void Sampler::setMaxLod     (GLfloat const&maxLod   )const{
  assert(this!=nullptr);
  this->getContext().glSamplerParameterf(this->getId(),GL_TEXTURE_MAX_LOD,maxLod);
}

void Sampler::setMinFilter  (GLenum  const&minFilter)const{
  assert(this!=nullptr);
  this->getContext().glSamplerParameteri(this->getId(),GL_TEXTURE_MIN_FILTER,minFilter);
}

void Sampler::setMagFilter  (GLenum  const&magFilter)const{
  assert(this!=nullptr);
  this->getContext().glSamplerParameteri(this->getId(),GL_TEXTURE_MAG_FILTER,magFilter);
}

void Sampler::setWrapS      (GLenum  const&wrapS    )const{
  assert(this!=nullptr);
  this->getContext().glSamplerParameteri(this->getId(),GL_TEXTURE_WRAP_S,wrapS);
}

void Sampler::setWrapT      (GLenum  const&wrapT    )const{
  assert(this!=nullptr);
  this->getContext().glSamplerParameteri(this->getId(),GL_TEXTURE_WRAP_T,wrapT);
}

void Sampler::setWrapR      (GLenum  const&wrapR    )const{
  assert(this!=nullptr);
  this->getContext().glSamplerParameteri(this->getId(),GL_TEXTURE_WRAP_R,wrapR);
}

void Sampler::getBorderColor(GLfloat*const&color    )const{
  assert(this!=nullptr);
  this->getContext().glGetSamplerParameterfv(this->getId(),GL_TEXTURE_BORDER_COLOR,color);
}

GLenum Sampler::getCompareFunc()const{
  assert(this!=nullptr);
  GLenum func;
  this->getContext().glGetSamplerParameteriv(this->getId(),GL_TEXTURE_COMPARE_FUNC,(GLint*)&func);
  return func;
}

GLenum Sampler::getCompareMode()const{
  assert(this!=nullptr);
  GLenum mode;
  this->getContext().glGetSamplerParameteriv(this->getId(),GL_TEXTURE_COMPARE_MODE,(GLint*)&mode);
  return mode;
}

GLfloat Sampler::getLodBias()const{
  assert(this!=nullptr);
  GLfloat lodBias;
  this->getContext().glGetSamplerParameterfv(this->getId(),GL_TEXTURE_LOD_BIAS,&lodBias);
  return lodBias;
}

GLfloat Sampler::getMinLod()const{
  assert(this!=nullptr);
  GLfloat minLod;
  this->getContext().glGetSamplerParameterfv(this->getId(),GL_TEXTURE_MIN_LOD,&minLod);
  return minLod;
}

GLfloat Sampler::getMaxLod()const{
  assert(this!=nullptr);
  GLfloat maxLod;
  this->getContext().glGetSamplerParameterfv(this->getId(),GL_TEXTURE_MAX_LOD,&maxLod);
  return maxLod;
}

GLenum Sampler::getMinFilter()const{
  assert(this!=nullptr);
  GLenum minFilter;
  this->getContext().glGetSamplerParameteriv(this->getId(),GL_TEXTURE_MIN_FILTER,(GLint*)&minFilter);
  return minFilter;
}

GLenum Sampler::getMagFilter()const{
  assert(this!=nullptr);
  GLenum magFilter;
  this->getContext().glGetSamplerParameteriv(this->getId(),GL_TEXTURE_MAG_FILTER,(GLint*)&magFilter);
  return magFilter;
}

GLenum Sampler::getWrapS()const{
  assert(this!=nullptr);
  GLenum wrapS;
  this->getContext().glGetSamplerParameteriv(this->getId(),GL_TEXTURE_WRAP_S,(GLint*)&wrapS);
  return wrapS;
}

GLenum Sampler::getWrapT()const{
  assert(this!=nullptr);
  GLenum wrapT;
  this->getContext().glGetSamplerParameteriv(this->getId(),GL_TEXTURE_WRAP_T,(GLint*)&wrapT);
  return wrapT;
}

GLenum Sampler::getWrapR()const{
  assert(this!=nullptr);
  GLenum wrapR;
  this->getContext().glGetSamplerParameteriv(this->getId(),GL_TEXTURE_WRAP_R,(GLint*)&wrapR);
  return wrapR;
}

void Sampler::bind(GLuint const&unit)const{
  assert(this!=nullptr);
  this->getContext().glBindSampler(unit,this->getId());
}

void Sampler::unbind(GLuint const&unit)const{
  assert(this!=nullptr);
  this->getContext().glBindSampler(unit,0);
}
