#include<geGL/SamplerObject.h>

using namespace ge::gl;

SamplerObject::SamplerObject(){
#ifndef USE_DSA
  glGenSamplers(1,&this->_id);
#else //USE_DSA
  glCreateSamplers(1,&this->_id);
#endif//USE_DSA
}

SamplerObject::SamplerObject(SamplerObject*sampler){
#ifndef USE_DSA
  glGenSamplers(1,&this->_id);
#else //USE_DSA
  glCreateSamplers(1,&this->_id);
#endif//USE_DSA
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
SamplerObject::~SamplerObject(){
  glDeleteSamplers(1,&this->_id);
}
void SamplerObject::setBorderColor(GLfloat*color    ){
  glSamplerParameterfv(this->_id,GL_TEXTURE_BORDER_COLOR,color);
}
void SamplerObject::setCompareFunc(GLenum  func     ){
  glSamplerParameteri(this->_id,GL_TEXTURE_COMPARE_FUNC,func);
}
void SamplerObject::setCompareMode(GLenum  mode     ){
  glSamplerParameteri(this->_id,GL_TEXTURE_COMPARE_MODE,mode);
}
void SamplerObject::setLodBias    (GLfloat lodBias  ){
  glSamplerParameterf(this->_id,GL_TEXTURE_LOD_BIAS,lodBias);
}
void SamplerObject::setMinLod     (GLfloat minLod   ){
  glSamplerParameterf(this->_id,GL_TEXTURE_MIN_LOD,minLod);
}
void SamplerObject::setMaxLod     (GLfloat maxLod   ){
  glSamplerParameterf(this->_id,GL_TEXTURE_MAX_LOD,maxLod);
}
void SamplerObject::setMinFilter  (GLenum  minFilter){
  glSamplerParameteri(this->_id,GL_TEXTURE_MIN_FILTER,minFilter);
}
void SamplerObject::setMagFilter  (GLenum  magFilter){
  glSamplerParameteri(this->_id,GL_TEXTURE_MAG_FILTER,magFilter);
}
void SamplerObject::setWrapS      (GLenum  wrapS    ){
  glSamplerParameteri(this->_id,GL_TEXTURE_WRAP_S,wrapS);
}
void SamplerObject::setWrapT      (GLenum  wrapT    ){
  glSamplerParameteri(this->_id,GL_TEXTURE_WRAP_T,wrapT);
}
void SamplerObject::setWrapR      (GLenum  wrapR    ){
  glSamplerParameteri(this->_id,GL_TEXTURE_WRAP_R,wrapR);
}
void SamplerObject::getBorderColor(GLfloat*color    ){
  glGetSamplerParameterfv(this->_id,GL_TEXTURE_BORDER_COLOR,color);
}
GLenum SamplerObject::getCompareFunc(){
  GLenum func;
  glGetSamplerParameteriv(this->_id,GL_TEXTURE_COMPARE_FUNC,(GLint*)&func);
  return func;
}
GLenum SamplerObject::getCompareMode(){
  GLenum mode;
  glGetSamplerParameteriv(this->_id,GL_TEXTURE_COMPARE_MODE,(GLint*)&mode);
  return mode;
}
GLfloat SamplerObject::getLodBias(){
  GLfloat lodBias;
  glGetSamplerParameterfv(this->_id,GL_TEXTURE_LOD_BIAS,&lodBias);
  return lodBias;
}
GLfloat SamplerObject::getMinLod(){
  GLfloat minLod;
  glGetSamplerParameterfv(this->_id,GL_TEXTURE_MIN_LOD,&minLod);
  return minLod;
}
GLfloat SamplerObject::getMaxLod(){
  GLfloat maxLod;
  glGetSamplerParameterfv(this->_id,GL_TEXTURE_MAX_LOD,&maxLod);
  return maxLod;
}
GLenum SamplerObject::getMinFilter(){
  GLenum minFilter;
  glGetSamplerParameteriv(this->_id,GL_TEXTURE_MIN_FILTER,(GLint*)&minFilter);
  return minFilter;
}
GLenum SamplerObject::getMagFilter(){
  GLenum magFilter;
  glGetSamplerParameteriv(this->_id,GL_TEXTURE_MAG_FILTER,(GLint*)&magFilter);
  return magFilter;
}
GLenum SamplerObject::getWrapS(){
  GLenum wrapS;
  glGetSamplerParameteriv(this->_id,GL_TEXTURE_WRAP_S,(GLint*)&wrapS);
  return wrapS;
}
GLenum SamplerObject::getWrapT(){
  GLenum wrapT;
  glGetSamplerParameteriv(this->_id,GL_TEXTURE_WRAP_T,(GLint*)&wrapT);
  return wrapT;
}
GLenum SamplerObject::getWrapR(){
  GLenum wrapR;
  glGetSamplerParameteriv(this->_id,GL_TEXTURE_WRAP_R,(GLint*)&wrapR);
  return wrapR;
}
void SamplerObject::bind(GLuint unit){
  glBindSampler(unit,this->_id);
}
void SamplerObject::unbind(GLuint unit){
  glBindSampler(unit,0);
}
