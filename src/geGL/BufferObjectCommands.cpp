#include<geGL/BufferObjectCommands.h>

using namespace ge::gl;
using namespace ge::gl::bo;


BufferData::BufferData(
    GLsizeiptr    size,
    const GLvoid* data){
  this->set(size,data);
}

void BufferData::set(
    GLsizeiptr    size,
    const GLvoid* data){
  this->_size = size;
  this->_data = data;
}

GLsizeiptr BufferData::getSize(){
  return this->_size;
}

const GLvoid*BufferData::getData(){
  return this->_data;
}

Offset::Offset(GLintptr offset){
  this->setOffset(offset);
}
GLintptr Offset::getOffset(){
  return this->_offset;
}
void Offset::setOffset(GLintptr offset){
  this->_offset = offset;
}

Size::Size(GLsizeiptr size){
  this->setSize(size);
}
GLsizeiptr Size::getSize(){
  return this->_size;
}
void Size::setSize(GLsizeiptr size){
  this->_size = size;
}


Map::Map(
    std::shared_ptr<BufferObject>buffer,
    std::shared_ptr<GLvoid*>     ptr   ,
    GLbitfield                   access):Shared<BufferObject>(buffer){
  this->_ptr    = ptr   ;
  this->_access = std::make_shared<GLbitfield>(access);
  this->_offset = 0     ;
  this->_size   = 0     ;
}
Map::Map(
    std::shared_ptr<BufferObject>buffer,
    std::shared_ptr<GLvoid*>     ptr   ,
    GLintptr                     offset,
    GLsizeiptr                   size  ,
    GLbitfield                   access):Shared<BufferObject>(buffer){
  this->_ptr    = ptr   ;
  this->_offset = std::make_shared<GLintptr  >(offset);
  this->_size   = std::make_shared<GLsizeiptr>(size  );
  this->_access = std::make_shared<GLbitfield>(access);
}

void Map::operator()(){
  if(this->_size==0)
    *this->_ptr=this->_object->map(*this->_access);
  else
    *this->_ptr=this->_object->map(*this->_offset,*this->_size,*this->_access);
}

std::shared_ptr<GLvoid*>&Map::getPtr(){
  return this->_ptr;
}

std::shared_ptr<GLbitfield>&Map::getAccess(){
  return this->_access;
}

std::shared_ptr<GLintptr>&Map::getOffset(){
  return this->_offset;
}

std::shared_ptr<GLsizeiptr>&Map::getSize(){
  return this->_size;
}



Unmap::Unmap(std::shared_ptr<BufferObject>buffer):Shared<BufferObject>(buffer){
}

void Unmap::operator()(){
  this->_object->unmap();
}

