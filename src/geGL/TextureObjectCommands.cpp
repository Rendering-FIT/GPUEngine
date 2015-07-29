#include<geGL/TextureObjectCommands.h>
#include<geGL/TextureObject.h>
#include<geGL/ProgramObject.h>
#include<geGL/TextureCommands.h>

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

ge::core::Command*ge::gl::newActiveTexture(ProgramObject*program,std::string samplerName){
  return new ActiveTexture(program->getSamplerBinding(samplerName));
}

ge::core::Command*ge::gl::newBindTexture(TextureObject*texture){
  return new BindTexture(texture->getTarget(),texture->getId());
}

ge::core::Command*ge::gl::newBindTextureUnit(
    ProgramObject*program    ,
    std::string   samplerName,
    TextureObject*texture    ){
  return new BindTextureUnit(program->getSamplerBinding(samplerName),texture->getId());
}
