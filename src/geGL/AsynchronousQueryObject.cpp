#include <geGL/AsynchronousQueryObject.h>

using namespace ge::gl;
using namespace ge::gl::opengl;

AsynchronousQueryObject::AsynchronousQueryObject(
    GLenum     target,
    GLenum     waitingType,
    ResultSize resultSize){
  glGenQueries(1,&this->_id);
  this->_target      = target;
  this->_waitingType = waitingType;
  this->_resultSize  = resultSize;
}

AsynchronousQueryObject::AsynchronousQueryObject(
    AsynchronousQueryObject*existingQuery){
  glGenQueries(1,&this->_id);
  this->_target      = existingQuery->_target;
  this->_waitingType = existingQuery->_waitingType;
  this->_resultSize  = existingQuery->_resultSize;
}

AsynchronousQueryObject::AsynchronousQueryObject(
    FunctionTablePointer const&table,
    GLenum     target,
    GLenum     waitingType,
    ResultSize resultSize):OpenGLObject(table){
  glGenQueries(1,&this->_id);
  this->_target      = target;
  this->_waitingType = waitingType;
  this->_resultSize  = resultSize;
}

AsynchronousQueryObject::AsynchronousQueryObject(
    FunctionTablePointer const&table,
    AsynchronousQueryObject*existingQuery):OpenGLObject(table){
  glGenQueries(1,&this->_id);
  this->_target      = existingQuery->_target;
  this->_waitingType = existingQuery->_waitingType;
  this->_resultSize  = existingQuery->_resultSize;
}

AsynchronousQueryObject::~AsynchronousQueryObject(){
  glDeleteQueries(1,&this->_id);
}
void AsynchronousQueryObject::begin(){
  glBeginQuery(this->_target,this->_id);
}
void AsynchronousQueryObject::end(){
  glEndQuery(this->_target);
  switch(this->_resultSize){
    case INT32:
      glGetQueryObjectiv   (this->_id,this->_waitingType,&this->_datai32);
      break;
    case UINT32:
      glGetQueryObjectuiv  (this->_id,this->_waitingType,&this->_dataui32);
      break;
    case INT64:
      glGetQueryObjecti64v (this->_id,this->_waitingType,&this->_datai64);
      break;
    case UINT64:
      glGetQueryObjectui64v(this->_id,this->_waitingType,&this->_dataui64);
      break;
  }
}
void AsynchronousQueryObject::begin(GLuint index){
  glBeginQueryIndexed(this->_target,index,this->_id);
  //TODO
}
void AsynchronousQueryObject::end(GLuint index){
  glEndQueryIndexed(this->_target,index);
  //TODO
}
GLuint64 AsynchronousQueryObject::getui64(){
  return this->_dataui64;
}
GLint64  AsynchronousQueryObject::geti64(){
  return this->_datai64;
}
GLuint   AsynchronousQueryObject::getui(){
  return this->_dataui32;
}
GLint    AsynchronousQueryObject::geti(){
  return this->_datai32;
}
GLenum   AsynchronousQueryObject::getTarget(){
  return this->_target;
}
GLenum   AsynchronousQueryObject::getWaitingType(){
  return this->_waitingType;
}

