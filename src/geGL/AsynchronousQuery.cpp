#include<geGL/AsynchronousQuery.h>

#include<cassert>

using namespace ge::gl;

AsynchronousQuery::AsynchronousQuery(){
  assert(this!=nullptr);
  this->_gl.glGenQueries(1,&this->_id);
}

void AsynchronousQuery::create(
    GLenum     target,
    GLenum     waitingType,
    ResultSize resultSize){
  assert(this!=nullptr);
  this->_target      = target;
  this->_waitingType = waitingType;
  this->_resultSize  = resultSize;
}

/**
 * @brief Constructor
 *
 * @param target type of query
 * @param waitingType type of waiting for results
 * @param resultSize size and type of result
 */
AsynchronousQuery::AsynchronousQuery(
    GLenum     target,
    GLenum     waitingType,
    ResultSize resultSize){
  assert(this!=nullptr);
  this->_gl.glGenQueries(1,&this->_id);
  this->_target      = target;
  this->_waitingType = waitingType;
  this->_resultSize  = resultSize;
}

/**
 * @brief Constructor of query from existing query
 *
 * @param existingQuery This query has already been created
 */
AsynchronousQuery::AsynchronousQuery(
    AsynchronousQuery*existingQuery){
  assert(this!=nullptr);
  this->_gl.glGenQueries(1,&this->_id);
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
  this->_gl.glGenQueries(1,&this->_id);
  this->_target      = target;
  this->_waitingType = waitingType;
  this->_resultSize  = resultSize;
}

AsynchronousQuery::AsynchronousQuery(
    FunctionTablePointer const&table,
    AsynchronousQuery*existingQuery):OpenGLObject(table){
  assert(this!=nullptr);
  this->_gl.glGenQueries(1,&this->_id);
  this->_target      = existingQuery->_target;
  this->_waitingType = existingQuery->_waitingType;
  this->_resultSize  = existingQuery->_resultSize;
}

/**
 * @brief Destructor
 */
AsynchronousQuery::~AsynchronousQuery(){
  assert(this!=nullptr);
  this->_gl.glDeleteQueries(1,&this->_id);
}

/**
 * @brief Begins query
 */
void AsynchronousQuery::begin(){
  assert(this!=nullptr);
  this->_gl.glBeginQuery(this->_target,this->_id);
}

/**
 * @brief Ends query
 */
void AsynchronousQuery::end(){
  assert(this!=nullptr);
  this->_gl.glEndQuery(this->_target);
  switch(this->_resultSize){
    case INT32:
      this->_gl.glGetQueryObjectiv   (this->_id,this->_waitingType,&this->_datai32);
      break;
    case UINT32:
      this->_gl.glGetQueryObjectuiv  (this->_id,this->_waitingType,&this->_dataui32);
      break;
    case INT64:
      this->_gl.glGetQueryObjecti64v (this->_id,this->_waitingType,&this->_datai64);
      break;
    case UINT64:
      this->_gl.glGetQueryObjectui64v(this->_id,this->_waitingType,&this->_dataui64);
      break;
  }
}

/**
 * @brief Begins indexed query
 *
 * @param index index of query
 */
void AsynchronousQuery::begin(GLuint index){
  assert(this!=nullptr);
  this->_gl.glBeginQueryIndexed(this->_target,index,this->_id);
}

/**
 * @brief Ends indexed query
 *
 * @param index index of query
 */
void AsynchronousQuery::end(GLuint index){
  assert(this!=nullptr);
  this->_gl.glEndQueryIndexed(this->_target,index);
}

/**
 * @brief Gets results
 *
 * @return query uint64 results
 */
GLuint64 AsynchronousQuery::getui64(){
  assert(this!=nullptr);
  return this->_dataui64;
}

/**
 * @brief Gets result
 *
 * @return query int64 results
 */
GLint64  AsynchronousQuery::geti64(){
  assert(this!=nullptr);
  return this->_datai64;
}

/**
 * @brief Gets result
 *
 * @return query uint resutls
 */
GLuint   AsynchronousQuery::getui(){
  assert(this!=nullptr);
  return this->_dataui32;
}

/**
 * @brief Gets result
 *
 * @return query int results
 */
GLint    AsynchronousQuery::geti(){
  assert(this!=nullptr);
  return this->_datai32;
}

/**
 * @brief gets target of query
 *
 * @return target
 */
GLenum   AsynchronousQuery::getTarget(){
  assert(this!=nullptr);
  return this->_target;
}

/**
 * @brief gets type of waiting
 *
 * @return wainting type
 */
GLenum   AsynchronousQuery::getWaitingType(){
  assert(this!=nullptr);
  return this->_waitingType;
}

