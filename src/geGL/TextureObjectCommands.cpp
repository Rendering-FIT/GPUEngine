#include<geGL/TextureObjectCommands.h>
#include<geGL/TextureObject.h>

using namespace ge::gl;

BindTextureObject2Unit::BindTextureObject2Unit(
    std::shared_ptr<TextureObject>const&textureObject,
    GLenum                              unit         ){
  this->setTextureObject(textureObject);
  this->setUnit(unit);
}

void BindTextureObject2Unit::operator()(){
  this->_texture->bind(this->_unit);
}

std::shared_ptr<TextureObject>const&BindTextureObject2Unit::getTextureObject(){
  return this->_texture;
}

void BindTextureObject2Unit::setTextureObject(std::shared_ptr<TextureObject>const&TextureObject){
  this->_texture = TextureObject;
}

GLenum BindTextureObject2Unit::getUnit(){
  return this->_unit;
}

void BindTextureObject2Unit::setUnit(GLenum unit){
  this->_unit = unit;
}

