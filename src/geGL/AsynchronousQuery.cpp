#include<geGL/AsynchronousQuery.h>

#include<cassert>

using namespace ge::gl;
using namespace ge::gl::opengl;

AsynchronousQuery::AsynchronousQuery(
    GLenum     target,
    GLenum     waitingType,
    ResultSize resultSize){
  assert(this!=nullptr);
  glGenQueries(1,&this->_id);
  this->_target      = target;
  this->_waitingType = waitingType;
  this->_resultSize  = resultSize;
}

AsynchronousQuery::AsynchronousQuery(
    AsynchronousQuery*existingQuery){
  assert(this!=nullptr);
  glGenQueries(1,&this->_id);
  this->_target      = existingQuery->_target;
  this->_waitingType = existingQuery->_waitingType;
  this->_resultSize  = existingQuery->_resultSize;
}

AsynchronousQuery::AsynchronousQuery(
    FunctionTablePointer const&table,
    GLenum     target,
    GLenum     waitingType,
    ResultSize resultSize):OpenGLObject(table){
  assert(this!=nullptr);
  glGenQueries(1,&this->_id);
  this->_target      = target;
  this->_waitingType = waitingType;
  this->_resultSize  = resultSize;
}

AsynchronousQuery::AsynchronousQuery(
    FunctionTablePointer const&table,
    AsynchronousQuery*existingQuery):OpenGLObject(table){
  assert(this!=nullptr);
  glGenQueries(1,&this->_id);
  this->_target      = existingQuery->_target;
  this->_waitingType = existingQuery->_waitingType;
  this->_resultSize  = existingQuery->_resultSize;
}

AsynchronousQuery::~AsynchronousQuery(){
  assert(this!=nullptr);
  glDeleteQueries(1,&this->_id);
}

void AsynchronousQuery::begin(){
  assert(this!=nullptr);
  glBeginQuery(this->_target,this->_id);
}

void AsynchronousQuery::end(){
  assert(this!=nullptr);
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

void AsynchronousQuery::begin(GLuint index){
  assert(this!=nullptr);
  glBeginQueryIndexed(this->_target,index,this->_id);
  //TODO
}

void AsynchronousQuery::end(GLuint index){
  assert(this!=nullptr);
  glEndQueryIndexed(this->_target,index);
  //TODO
}

GLuint64 AsynchronousQuery::getui64(){
  assert(this!=nullptr);
  return this->_dataui64;
}

GLint64  AsynchronousQuery::geti64(){
  assert(this!=nullptr);
  return this->_datai64;
}

GLuint   AsynchronousQuery::getui(){
  assert(this!=nullptr);
  return this->_dataui32;
}

GLint    AsynchronousQuery::geti(){
  assert(this!=nullptr);
  return this->_datai32;
}

GLenum   AsynchronousQuery::getTarget(){
  assert(this!=nullptr);
  return this->_target;
}

GLenum   AsynchronousQuery::getWaitingType(){
  assert(this!=nullptr);
  return this->_waitingType;
}

