#include<geGL/VertexArrayObject.h>
#include<sstream>

using namespace ge::gl;

std::string ge::gl::translateAttribType(GLenum type){
  switch(type){
    case GL_BYTE                        :return"GL_BYTE"                        ;
    case GL_UNSIGNED_BYTE               :return"GL_UNSIGNED_BYTE"               ;
    case GL_SHORT                       :return"GL_SHORT"                       ;
    case GL_UNSIGNED_SHORT              :return"GL_UNSIGNED_SHORT"              ;
    case GL_INT                         :return"GL_INT"                         ;
    case GL_UNSIGNED_INT                :return"GL_UNSIGNED_INT"                ;
    case GL_FLOAT                       :return"GL_FLOAT"                       ;
    case GL_HALF_FLOAT                  :return"GL_HALF_FLOAT"                  ;
    case GL_DOUBLE                      :return"GL_DOUBLE"                      ;
    case GL_FIXED                       :return"GL_FIXED"                       ;
    case GL_INT_2_10_10_10_REV          :return"GL_INT_2_10_10_10_REV"          ;
    case GL_UNSIGNED_INT_2_10_10_10_REV :return"GL_UNSIGNED_INT_2_10_10_10_REV" ;
    case GL_UNSIGNED_INT_10F_11F_11F_REV:return"GL_UNSIGNED_INT_10F_11F_11F_REV";
    default                             :return"unknown"                        ;
  }
}

std::string ge::gl::translateBoolean(GLboolean boolean){
  switch(boolean){
    case GL_TRUE :return"GL_TRUE" ;
    case GL_FALSE:return"GL_FALSE";
    default      :return"unknown" ;
  }
}

unsigned ge::gl::getTypeSize(GLenum type){
  switch(type){
    case GL_BYTE          :return sizeof(GLbyte  );
    case GL_UNSIGNED_BYTE :return sizeof(GLubyte );
    case GL_SHORT         :return sizeof(GLshort );
    case GL_UNSIGNED_SHORT:return sizeof(GLushort);
    case GL_INT           :return sizeof(GLint   );
    case GL_UNSIGNED_INT  :return sizeof(GLuint  );
    case GL_FLOAT         :return sizeof(GLfloat );
    case GL_HALF_FLOAT    :return sizeof(GLhalf  );
    case GL_DOUBLE        :return sizeof(GLdouble);
    default               :return sizeof(GLbyte  );
  }
}

/**
 * @brief Creates empty vertex array object
 */
VertexArrayObject::VertexArrayObject (){
  glCreateVertexArrays(1,&this->_id);
}

#if defined(REPLACE_GLEW)
VertexArrayObject::VertexArrayObject (
    std::shared_ptr<OpenGLFunctionTable>const&table):OpenGLObject(table){
  glCreateVertexArrays(1,&this->_id);
}
#endif

/**
 * @brief Destroyes vertex array object
 */
VertexArrayObject::~VertexArrayObject(){
  glDeleteVertexArrays(1,&this->_id);
}

/**
 * @brief Adds vertex attrib into vertex array object
 *
 * @param buffer        id of buffer where a attrib is stored
 * @param index         index of attrib layout(location=index)
 * @param nofComponents number of components of attrib vec3 = 3
 * @param type          type of attrib vec3 = float, ivec2 = int
 * @param stride        distance between attribs 
 * @param pointer       offset to the first attrib
 * @param normalized    should the attrib be normalized?
 * @param divisor       rate of incrementation of attrib per instance, 0 = per VS invocation
 * @param apt           NONE - glVertexAttribPointer, I - glVertexAttribIPointer, L - glVertexAttribLPointer
 */
void VertexArrayObject::addAttrib(
    GLuint                  buffer       ,
    GLuint                  index        ,
    GLint                   nofComponents,
    GLenum                  type         ,
    GLsizei                 stride       ,
    const GLvoid           *pointer      ,
    GLboolean               normalized   ,
    GLuint                  divisor      ,
    enum AttribPointerType  apt          )const{
  if(stride==0)
    stride=ge::gl::getTypeSize(type)*nofComponents;
  glVertexArrayAttribBinding (this->_id,index,index);
  glEnableVertexArrayAttrib  (this->_id,index);

  if(apt==VertexArrayObject::AttribPointerType::NONE)
    glVertexArrayAttribFormat  (this->_id,index,nofComponents,type,normalized,0);
  else if(apt==VertexArrayObject::AttribPointerType::I)
    glVertexArrayAttribIFormat (this->_id,index,nofComponents,type,0);
  else if(apt==VertexArrayObject::AttribPointerType::L)
    glVertexArrayAttribLFormat (this->_id,index,nofComponents,type,0);

  glVertexArrayVertexBuffer  (this->_id,index,buffer,(GLintptr)pointer,stride);
  glVertexArrayBindingDivisor(this->_id,index,divisor);
}

void VertexArrayObject::addElementBuffer(
    GLuint buffer)const{
  glVertexArrayElementBuffer(this->_id,buffer);
}

void VertexArrayObject::bind()const{
  glBindVertexArray(this->_id);
}

void VertexArrayObject::unbind()const{
  glBindVertexArray(0);
}

GLint VertexArrayObject::_getAttrib(GLuint index,GLenum pname)const{
  GLint param;
  glGetVertexArrayIndexediv(this->_id,index,pname,&param);
  return param;
}

GLuint    VertexArrayObject::getAttribBufferBinding (GLuint index)const{
  return this->_getAttrib(index,GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING);
}

GLboolean VertexArrayObject::isAttribEnabled        (GLuint index)const{
  return (GLboolean)this->_getAttrib(index,GL_VERTEX_ATTRIB_ARRAY_ENABLED);
}

GLint     VertexArrayObject::getAttribSize          (GLuint index)const{
  return this->_getAttrib(index,GL_VERTEX_ATTRIB_ARRAY_SIZE);
}

GLsizei   VertexArrayObject::getAttribStride        (GLuint index)const{
  return this->_getAttrib(index,GL_VERTEX_ATTRIB_ARRAY_STRIDE);
}

GLenum    VertexArrayObject::getAttribType          (GLuint index)const{
  return this->_getAttrib(index,GL_VERTEX_ATTRIB_ARRAY_TYPE);
}

GLboolean VertexArrayObject::isAttribNormalized    (GLuint index)const{
  return (GLboolean)this->_getAttrib(index,GL_VERTEX_ATTRIB_ARRAY_NORMALIZED);
}

GLboolean VertexArrayObject::isAttribInteger       (GLuint index)const{
  return (GLboolean)this->_getAttrib(index,GL_VERTEX_ATTRIB_ARRAY_INTEGER);
}

GLboolean VertexArrayObject::isAttribLong          (GLuint index)const{
  return (GLboolean)this->_getAttrib(index,GL_VERTEX_ATTRIB_ARRAY_LONG);
}

GLuint    VertexArrayObject::getAttribDivisor       (GLuint index)const{
  return this->_getAttrib(index,GL_VERTEX_ATTRIB_ARRAY_DIVISOR);
}

GLuint    VertexArrayObject::getAttribBinding       (GLuint index)const{
  return this->_getAttrib(index,GL_VERTEX_ATTRIB_BINDING);
}

GLuint    VertexArrayObject::getAttribRelativeOffset(GLuint index)const{
  return this->_getAttrib(index,GL_VERTEX_ATTRIB_RELATIVE_OFFSET);
}

GLuint    VertexArrayObject::getElementBuffer()const{
  GLint id;
  glGetVertexArrayiv(this->_id,GL_ELEMENT_ARRAY_BUFFER_BINDING,&id);
  return id;
}

std::string VertexArrayObject::getInfo()const{
  std::stringstream ss;
  GLint maxVertexAttribs;
  glGetIntegerv(GL_MAX_VERTEX_ATTRIBS,&maxVertexAttribs);
  ss<<"vao: "<<this->getId()<<std::endl;
  ss<<"GL_MAX_VERTEX_ATTRIBS: "<<maxVertexAttribs<<std::endl;
  for(GLint a=0;a<maxVertexAttribs;++a){
    if(this->isAttribEnabled(a)==GL_FALSE)continue;
    ss<<"attrib: "<<a<<std::endl;
    ss<<"  GL_VERTEX_ATTRIB_ARRAY_ENABLED:        "<<ge::gl::translateBoolean(
        /*                                         */this->isAttribEnabled        (a))<<std::endl;
    ss<<"  GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING: "<<this->getAttribBufferBinding (a) <<std::endl;
    ss<<"  GL_VERTEX_ATTRIB_ARRAY_SIZE:           "<<this->getAttribSize          (a) <<std::endl;
    ss<<"  GL_VERTEX_ATTRIB_ARRAY_STRIDE:         "<<this->getAttribStride        (a) <<std::endl;
    ss<<"  GL_VERTEX_ATTRIB_ARRAY_TYPE:           "<<ge::gl::translateAttribType(
        /*                                         */this->getAttribType          (a))<<std::endl;
    ss<<"  GL_VERTEX_ATTRIB_ARRAY_NORMALIZED:     "<<ge::gl::translateBoolean(
        /*                                         */this->isAttribNormalized     (a))<<std::endl;
    ss<<"  GL_VERTEX_ATTRIB_ARRAY_INTEGER:        "<<ge::gl::translateBoolean(
        /*                                         */this->isAttribInteger        (a))<<std::endl;
    ss<<"  GL_VERTEX_ATTRIB_ARRAY_LONG:           "<<ge::gl::translateBoolean(
        /*                                         */this->isAttribLong           (a))<<std::endl;
    ss<<"  GL_VERTEX_ATTRIB_ARRAY_DIVISOR:        "<<this->getAttribDivisor       (a) <<std::endl;
    ss<<"  GL_VERTEX_ATTRIB_BINDING:              "<<this->getAttribBinding       (a) <<std::endl;
    ss<<"  GL_VERTEX_ATTRIB_RELATIVE_OFFSET:      "<<this->getAttribRelativeOffset(a) <<std::endl;
  }
  return ss.str();
}
std::shared_ptr<ge::gl::BufferObject>const&VertexArrayObject::getElement()const{
  return this->_elementBuffer;
}

std::shared_ptr<ge::gl::BufferObject>VertexArrayObject::getBuffer(GLuint index)const{
  auto ii=this->_buffers.find(index);
  if(ii==this->_buffers.end())return nullptr;
  return ii->second;
}

void VertexArrayObject::addAttrib(
    ge::gl::BufferObject   *buffer       ,
    GLuint                  index        ,
    GLint                   nofComponents,
    GLenum                  type         ,
    GLsizei                 stride       ,
    const GLvoid           *pointer      ,
    GLboolean               normalized   ,
    GLuint                  divisor      ,
    enum AttribPointerType  apt          )const{
  this->addAttrib(
      buffer->getId(),
      index,
      nofComponents,
      type,
      stride,
      pointer,
      normalized,
      divisor,
      apt);
}

void VertexArrayObject::addAttrib(
    std::shared_ptr<ge::gl::BufferObject>const&buffer           ,
    GLuint                                     index            ,
    GLint                                      nofComponents    ,
    GLenum                                     type             ,
    GLsizei                                    stride           ,
    const GLvoid*                              pointer          ,
    GLboolean                                  normalized       ,  
    GLuint                                     divisor          ,
    enum AttribPointerType                     attribPointerType){
  this->_buffers[index]=buffer;
  this->addAttrib(
      buffer->getId(),
      index,
      nofComponents,
      type,
      stride,
      pointer,
      normalized,
      divisor,
      attribPointerType);
}

void VertexArrayObject::addElementBuffer(
    ge::gl::BufferObject *buffer)const{
  this->addElementBuffer(buffer->getId());
}

void VertexArrayObject::addElementBuffer(
    std::shared_ptr<ge::gl::BufferObject>const&buffer){
  this->_elementBuffer = buffer;
  this->addElementBuffer(buffer->getId());
}

//OpenGL 3.3
//glBindBuffer
//glBindVertexArray
//glDeleteVertexArrays
//glEnableVertexAttribArray
//glGenVertexArrays   
//glGetIntegerv
//glGetVertexAttribiv
//glVertexAttribPointer 
//glVertexAttribIPointer

//OpenGL 4.2
//glVertexAttribDivisor    
//glVertexAttribLPointer

//
//OpenGL 4.5
//glCreateVertexArrays
//glEnableVertexArrayAttrib  
//glGetVertexArrayIndexediv
//glGetVertexArrayiv
//glVertexArrayAttribBinding 
//glVertexArrayAttribFormat  
//glVertexArrayAttribIFormat 
//glVertexArrayAttribLFormat 
//glVertexArrayBindingDivisor
//glVertexArrayElementBuffer
//glVertexArrayVertexBuffer

