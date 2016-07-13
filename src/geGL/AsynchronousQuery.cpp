#include <geGL/AsynchronousQuery.h>

using namespace ge::gl;
using namespace ge::gl::opengl;

AsynchronousQuery::AsynchronousQuery(
    GLenum     target,
    GLenum     waitingType,
    ResultSize resultSize){
  glGenQueries(1,&this->_id);
  this->_target      = target;
  this->_waitingType = waitingType;
  this->_resultSize  = resultSize;
}

AsynchronousQuery::AsynchronousQuery(
    AsynchronousQuery*existingQuery){
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
  glGenQueries(1,&this->_id);
  this->_target      = target;
  this->_waitingType = waitingType;
  this->_resultSize  = resultSize;
}

AsynchronousQuery::AsynchronousQuery(
    FunctionTablePointer const&table,
    AsynchronousQuery*existingQuery):OpenGLObject(table){
  glGenQueries(1,&this->_id);
  this->_target      = existingQuery->_target;
  this->_waitingType = existingQuery->_waitingType;
  this->_resultSize  = existingQuery->_resultSize;
}

AsynchronousQuery::~AsynchronousQuery(){
  glDeleteQueries(1,&this->_id);
}
void AsynchronousQuery::begin(){
  glBeginQuery(this->_target,this->_id);
}
void AsynchronousQuery::end(){
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
  glBeginQueryIndexed(this->_target,index,this->_id);
  //TODO
}
void AsynchronousQuery::end(GLuint index){
  glEndQueryIndexed(this->_target,index);
  //TODO
}
GLuint64 AsynchronousQuery::getui64(){
  return this->_dataui64;
}
GLint64  AsynchronousQuery::geti64(){
  return this->_datai64;
}
GLuint   AsynchronousQuery::getui(){
  return this->_dataui32;
}
GLint    AsynchronousQuery::geti(){
  return this->_datai32;
}
GLenum   AsynchronousQuery::getTarget(){
  return this->_target;
}
GLenum   AsynchronousQuery::getWaitingType(){
  return this->_waitingType;
}

