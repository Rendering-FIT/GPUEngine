#include<geGL/ProgramObjectCommands.h>

using namespace ge::gl;
using namespace ge::gl::po;

Use::Use(const std::shared_ptr<ProgramObject>&program):Shared<ProgramObject>(program){}

void Use::operator()(){
  this->_object->use();
}



SetVersion::Data::Data(unsigned version,std::string profile,GLenum shader){
  this->_version = version;
  this->_profile = profile;
  this->_shader  = shader ;
}

unsigned SetVersion::Data::getVersion(){
  return this->_version;
}

std::string SetVersion::Data::getProfile(){
  return this->_profile;
}

GLenum SetVersion::Data::getShader(){
  return this->_shader;
}

void SetVersion::Data::setVersion(unsigned version){
  this->_version = version;
}

void SetVersion::Data::setProfile(std::string profile){
  this->_profile = profile;
}

void SetVersion::Data::setShader(GLenum shader){
  this->_shader = shader;
}



SetVersion::SetVersion(
    const std::shared_ptr<ProgramObject>&program,
    const std::shared_ptr<Data         >&data   ):Shared<ProgramObject>(program){
  this->setData(data);
}

void SetVersion::operator()(){
  if(this->_data->getShader()==DEFAULT_SHADER)
    this->_object->setVersion(
        this->_data->getVersion(),
        this->_data->getProfile());
  else
    this->_object->setVersion(
        this->_data->getShader (),
        this->_data->getVersion(),
        this->_data->getProfile());
}

std::shared_ptr<SetVersion::Data>&SetVersion::getData(){
  return this->_data;
}

void SetVersion::setData(const std::shared_ptr<Data>&data){
  this->_data = data;
}


Append::Data::Data(
    std::string defs  ,
    GLenum      shader){
  this->_defs   = defs  ;
  this->_shader = shader;
}

std::string Append::Data::getDefs  (){
  return this->_defs;
}

GLenum Append::Data::getShader(){
  return this->_shader;
}

void Append::Data::setDefs(std::string defs){
  this->_defs = defs;
}

void Append::Data::setShader(GLenum shader){
  this->_shader = shader;
}

Append::Append(
    const std::shared_ptr<ProgramObject>&program,
    const std::shared_ptr<Data         >&data):Shared<ProgramObject>(program){
  this->setData(data);
}

void Append::operator()(){
  if(this->_data->getShader() == DEFAULT_SHADER)
    this->_object->appendAfterVersion(this->_data->getDefs());
  else
    this->_object->appendAfterVersion(this->_data->getShader(),this->_data->getDefs());
}

std::shared_ptr<Append::Data>&Append::getData(){
  return this->_data;
}
void Append::setData(const std::shared_ptr<Data>&data){
  this->_data = data;
}



Location::Location(
    const std::shared_ptr<ProgramObject>&program,
    std::string name):Shared<ProgramObject>(program){
  this->setName(name);
}

std::string Location::getName(){
  return this->_name;
}

void Location::setName(std::string name){
  this->_name = name;
}

