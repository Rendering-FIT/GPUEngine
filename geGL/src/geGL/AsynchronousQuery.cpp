#include<geGL/AsynchronousQuery.h>

#include<cassert>

using namespace ge::gl;

AsynchronousQuery::AsynchronousQuery(){
  assert(this!=nullptr);
  this->getContext().glGenQueries(1,&this->getId());
}

void AsynchronousQuery::create(
    GLenum     const&target     ,
    GLenum     const&waitingType,
    ResultSize const&resultSize ){
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
    GLenum     const&target     ,
    GLenum     const&waitingType,
    ResultSize const&resultSize ){
  assert(this!=nullptr);
  this->getContext().glGenQueries(1,&this->getId());
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
    AsynchronousQuery const*const&existingQuery){
  assert(this!=nullptr);
  this->getContext().glGenQueries(1,&this->getId());
  this->_target      = existingQuery->_target;
  this->_waitingType = existingQuery->_waitingType;
  this->_resultSize  = existingQuery->_resultSize;
}

AsynchronousQuery::AsynchronousQuery(
    FunctionTablePointer const&table      ,
    GLenum               const&target     ,
    GLenum               const&waitingType,
    ResultSize           const&resultSize ):OpenGLObject(table){
  assert(this!=nullptr);
  this->getContext().glGenQueries(1,&this->getId());
  this->_target      = target;
  this->_waitingType = waitingType;
  this->_resultSize  = resultSize;
}

AsynchronousQuery::AsynchronousQuery(
    FunctionTablePointer       const&table        ,
    AsynchronousQuery    const*const&existingQuery):OpenGLObject(table){
  assert(this!=nullptr);
  this->getContext().glGenQueries(1,&this->getId());
  this->_target      = existingQuery->_target;
  this->_waitingType = existingQuery->_waitingType;
  this->_resultSize  = existingQuery->_resultSize;
}

/**
 * @brief Destructor
 */
AsynchronousQuery::~AsynchronousQuery(){
  assert(this!=nullptr);
  this->getContext().glDeleteQueries(1,&this->getId());
}

/**
 * @brief Begins query
 */
void AsynchronousQuery::begin(){
  assert(this!=nullptr);
  this->getContext().glBeginQuery(this->_target,this->getId());
}

/**
 * @brief Ends query
 */
void AsynchronousQuery::end(){
  assert(this!=nullptr);
  this->getContext().glEndQuery(this->_target);
  switch(this->_resultSize){
    case INT32:
      this->getContext().glGetQueryObjectiv   (this->getId(),this->_waitingType,&this->_datai32);
      break;
    case UINT32:
      this->getContext().glGetQueryObjectuiv  (this->getId(),this->_waitingType,&this->_dataui32);
      break;
    case INT64:
      this->getContext().glGetQueryObjecti64v (this->getId(),this->_waitingType,&this->_datai64);
      break;
    case UINT64:
      this->getContext().glGetQueryObjectui64v(this->getId(),this->_waitingType,&this->_dataui64);
      break;
  }
}

/**
 * @brief Begins indexed query
 *
 * @param index index of query
 */
void AsynchronousQuery::begin(GLuint const&index){
  assert(this!=nullptr);
  this->getContext().glBeginQueryIndexed(this->_target,index,this->getId());
}

/**
 * @brief Ends indexed query
 *
 * @param index index of query
 */
void AsynchronousQuery::end(GLuint const&index){
  assert(this!=nullptr);
  this->getContext().glEndQueryIndexed(this->_target,index);
}

/**
 * @brief Gets results
 *
 * @return query uint64 results
 */
GLuint64 AsynchronousQuery::getui64()const{
  assert(this!=nullptr);
  return this->_dataui64;
}

/**
 * @brief Gets result
 *
 * @return query int64 results
 */
GLint64  AsynchronousQuery::geti64()const{
  assert(this!=nullptr);
  return this->_datai64;
}

/**
 * @brief Gets result
 *
 * @return query uint resutls
 */
GLuint   AsynchronousQuery::getui()const{
  assert(this!=nullptr);
  return this->_dataui32;
}

/**
 * @brief Gets result
 *
 * @return query int results
 */
GLint    AsynchronousQuery::geti()const{
  assert(this!=nullptr);
  return this->_datai32;
}

/**
 * @brief gets target of query
 *
 * @return target
 */
GLenum   AsynchronousQuery::getTarget()const{
  assert(this!=nullptr);
  return this->_target;
}

/**
 * @brief gets type of waiting
 *
 * @return wainting type
 */
GLenum   AsynchronousQuery::getWaitingType()const{
  assert(this!=nullptr);
  return this->_waitingType;
}

