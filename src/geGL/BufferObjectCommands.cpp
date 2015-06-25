#include<geGL/BufferObjectCommands.h>

using namespace ge::gl;
using namespace ge::gl::bo;

SharedBuffer::SharedBuffer(
    std::shared_ptr<BufferObject>buffer){
  this->_buffer = buffer;
}

std::shared_ptr<BufferObject>&SharedBuffer::getBuffer(){
  return this->_buffer;
}



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



Constructor::Constructor(
    std::shared_ptr<BufferObject>buffer,
    std::shared_ptr<BufferData>  data  ,
    std::shared_ptr<GLbitfield>  flags ):Shared<BufferObject>(buffer){
  this->_data  = data ;
  this->_flags = flags;
}

Constructor::Constructor(
    std::shared_ptr<BufferObject>buffer,
    std::shared_ptr<BufferData>  data  ,
    GLbitfield                   flags ):Shared<BufferObject>(buffer){
  this->_data  = data;
  this->_flags = std::make_shared<GLbitfield>(flags);
}

Constructor::Constructor(
    std::shared_ptr<BufferObject>buffer,
    GLsizeiptr                   size  ,
    const GLvoid*                data  ,
    GLbitfield                   flags ):Shared<BufferObject>(buffer){
  this->_data  = std::make_shared<BufferData>(size,data);
  this->_flags = std::make_shared<GLbitfield>(flags);
}

void Constructor::operator()(){
  this->Shared<BufferObject>::_obj=std::make_shared<BufferObject>(
        this->_data->getSize(),
        this->_data->getData(),
        *this->_flags);
}

std::shared_ptr<BufferData>&Constructor::getData (){
  return this->_data;
}

std::shared_ptr<GLbitfield>&Constructor::getFlags(){
  return this->_flags;
}

Map::Map(
    std::shared_ptr<BufferObject>buffer,
    std::shared_ptr<GLvoid*>     ptr   ,
    GLbitfield                   access):SharedBuffer(buffer){
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
    GLbitfield                   access):SharedBuffer(buffer){
  this->_ptr    = ptr   ;
  this->_offset = std::make_shared<GLintptr  >(offset);
  this->_size   = std::make_shared<GLsizeiptr>(size  );
  this->_access = std::make_shared<GLbitfield>(access);
}

void Map::operator()(){
  if(this->_size==0)
    *this->_ptr=this->_buffer->map(*this->_access);
  else
    *this->_ptr=this->_buffer->map(*this->_offset,*this->_size,*this->_access);
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



Unmap::Unmap(std::shared_ptr<BufferObject>buffer):SharedBuffer(buffer){
}

void Unmap::operator()(){
  this->_buffer->unmap();
}

