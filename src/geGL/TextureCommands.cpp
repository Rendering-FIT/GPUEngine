#include<geGL/TextureCommands.h>

using namespace ge::gl;

ActiveTexture::ActiveTexture(GLenum unit){
  this->setUnit(unit);
}

void ActiveTexture::operator()(){
  glActiveTexture(this->_unit);
}

GLenum ActiveTexture::getUnit(){
  return this->_unit;
}

void ActiveTexture::setUnit(GLenum unit){
  this->_unit = unit;
}


BindTexture::BindTexture(GLenum target,GLuint texture){
  this->setTarget (target );
  this->setTexture(texture);
}

void   BindTexture::operator()(){
  glBindTexture(this->_texture,this->_texture);
}

GLenum BindTexture::getTarget(){
  return this->_target;
}

void   BindTexture::setTarget(GLenum target){
  this->_target = target;
}


GLuint BindTexture::getTexture(){
  return this->_texture;
}

void   BindTexture::setTexture(GLuint texture){
  this->_texture = texture;
}


BindTextureUnit::BindTextureUnit(GLuint unit,GLuint texture){
  this->setUnit   (unit   );
  this->setTexture(texture);
}

void   BindTextureUnit::operator()(){
  glBindTextureUnit(this->_unit,this->_texture);
}

GLuint BindTextureUnit::getUnit(){
  return this->_unit;
}

void   BindTextureUnit::setUnit(GLuint unit){
  this->_unit = unit;
}

GLuint BindTextureUnit::getTexture(){
  return this->_texture;
}

void   BindTextureUnit::setTexture(GLuint texture){
  this->_texture = texture;
}

