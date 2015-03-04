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

namespace ge{
  namespace gl{
    void _glCreateVertexArrays(GLsizei n,GLuint*arrays);
  }
}

void ge::gl::_glCreateVertexArrays(GLsizei n,GLuint*arrays){
  GLint oldVAO;
  glGetIntegerv(GL_VERTEX_ARRAY_BINDING,&oldVAO);
  glGenVertexArrays(n,arrays);
  for(GLint i=0;i<n;++n)glBindVertexArray(arrays[n]);
  glBindVertexArray(oldVAO);
}

void initVertexArrayObjects(){
  std::string result320  = "";
  std::string result420  = "";
  std::string warning320 = "";
  std::string warning420 = "";
  bool openGL320=true;
  bool openGL420=true;
  if(!glBindBuffer             ){result320+="glBindBuffer "             ;openGL320=false;}
  if(!glBindVertexArray        ){result320+="glBindVertexArray "        ;openGL320=false;}
  if(!glDeleteVertexArrays     ){result320+="glDeleteVertexArrays "     ;openGL320=false;}
  if(!glEnableVertexAttribArray){result320+="glEnableVertexAttribArray ";openGL320=false;}
  if(!glGenVertexArrays        ){result320+="glGenVertexArrays "        ;openGL320=false;}
  //if(!glGetIntegerv            ){result320+="glGetIntegerv "            ;openGL320=false;}
  if(!glGetVertexAttribiv      ){result320+="glGetVertexAttribiv "      ;openGL320=false;}
  if(!glVertexAttribPointer    ){
    if(glVertexAttribPointerARB){
      glVertexAttribPointer=glVertexAttribPointerARB;
      warning320+="glVertexAttribPointer=glVertexAttribPointerARB ";
    /*}else if(glVertexAttribPointerNV){
      glVertexAttribPointer=glVertexAttribPointerNV;
      warning320+="glVertexAttribPointer=glVertexAttribPointerNV";*/
    }else{
      result320+="glVertexAttribPointer "    ;
      openGL320=false;
    }
  }
  if(!glVertexAttribIPointer   ){
    if(glVertexAttribIPointerEXT){
      glVertexAttribIPointer=glVertexAttribIPointerEXT;
      warning320="glVertexAttribIPointer=glVertexAttribIPointerEXT";
    }else{
      result320+="glVertexAttribIPointer "   ;
      openGL320=false;
    }
  }
//  if(!glCreateVertexArrays){
//    glCreateVertexArrays=ge::gl::_glCreateVertexArrays;
//  }
  if(!glVertexAttribLPointer){
    if(glVertexAttribLPointerEXT){
      glVertexAttribLPointer=glVertexAttribLPointerEXT;
      warning420+="glVertexAttribLPointer=glVertexAttribLPointerEXT";
    }else{
      result420+="glVertexAttribLPointer "   ;
      openGL420=false;
    }
  }
  if(!openGL320){
    throw(std::string(result320));
  }
  if(!openGL420){
    throw(std::string(result420));
  }
}

/**
 * @brief Creates empty vertex array object
 */
VertexArrayObject::VertexArrayObject (){
#ifndef USE_DSA
  glGenVertexArrays   (1,&this->_id);
#else //USE_DSA
  glCreateVertexArrays(1,&this->_id);
#endif//USE_DSA
}
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
    enum AttribPointerType  apt          ){
#ifndef USE_DSA
  this->bind();
  glBindBuffer(GL_ARRAY_BUFFER,buffer);
  glEnableVertexAttribArray(index);

  if(apt==VertexArrayObject::AttribPointerType::NONE)
    glVertexAttribPointer (index,nofComponents,type,normalized,stride,pointer);
  else if(apt==VertexArrayObject::AttribPointerType::I)
    glVertexAttribIPointer(index,nofComponents,type,stride,pointer);
  else if(apt==VertexArrayObject::AttribPointerType::L)
    glVertexAttribLPointer(index,nofComponents,type,stride,pointer);    

  glVertexAttribDivisor    (index,divisor);
  this->unbind();
#else //USE_DSA
  if(stride==VERTEXARRAYOBJECT_DEFAULT_STRIDE)
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
#endif//USE_DSA
}
void VertexArrayObject::addElementBuffer(
    GLuint buffer){
#ifndef USE_DSA
  this->bind();
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,buffer);
  this->unbind();
#else //USE_DSA
  glVertexArrayElementBuffer(this->_id,buffer);
#endif//USE_DSA
}
void VertexArrayObject::bind(){
  glBindVertexArray(this->_id);
}
void VertexArrayObject::unbind(){
  glBindVertexArray(VERTExARRAYOBJECT_DEFAULT_ID);
}

GLint     VertexArrayObject::getAttrib(GLuint index,GLenum pname){
  GLint param;
#ifndef USE_DSA
  this->bind();
  glGetVertexAttribiv(index,pname,&param);
  this->unbind();
#else //USE_DSA
  glGetVertexArrayIndexediv(this->_id,index,pname,&param);
#endif//USE_DSA
  return param;
}

GLuint    VertexArrayObject::getAttribBufferBinding (GLuint index){
  return this->getAttrib(index,GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING);
}
GLboolean VertexArrayObject::isAttribEnabled        (GLuint index){
  return this->getAttrib(index,GL_VERTEX_ATTRIB_ARRAY_ENABLED);
}
GLint     VertexArrayObject::getAttribSize          (GLuint index){
  return this->getAttrib(index,GL_VERTEX_ATTRIB_ARRAY_SIZE);
}
GLsizei   VertexArrayObject::getAttribStride        (GLuint index){
  return this->getAttrib(index,GL_VERTEX_ATTRIB_ARRAY_STRIDE);
}
GLenum    VertexArrayObject::getAttribType          (GLuint index){
  return this->getAttrib(index,GL_VERTEX_ATTRIB_ARRAY_TYPE);
}
GLboolean VertexArrayObject::isAttribNormalized    (GLuint index){
  return this->getAttrib(index,GL_VERTEX_ATTRIB_ARRAY_NORMALIZED);
}
GLboolean VertexArrayObject::isAttribInteger       (GLuint index){
  return this->getAttrib(index,GL_VERTEX_ATTRIB_ARRAY_INTEGER);
}
GLboolean VertexArrayObject::isAttribLong          (GLuint index){
  return this->getAttrib(index,GL_VERTEX_ATTRIB_ARRAY_LONG);
}
GLuint    VertexArrayObject::getAttribDivisor       (GLuint index){
  return this->getAttrib(index,GL_VERTEX_ATTRIB_ARRAY_DIVISOR);
}
GLuint    VertexArrayObject::getAttribBinding       (GLuint index){
  return this->getAttrib(index,GL_VERTEX_ATTRIB_BINDING);
}
GLuint    VertexArrayObject::getAttribRelativeOffset(GLuint index){
  return this->getAttrib(index,GL_VERTEX_ATTRIB_RELATIVE_OFFSET);
}
GLuint    VertexArrayObject::getElementBuffer(){
  GLint id;
#ifndef USE_DSA
  this->bind();
  glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER,&id);
  this->unbind();
#else //USE_DSA
  glGetVertexArrayiv(this->_id,GL_ELEMENT_ARRAY_BUFFER_BINDING,&id);
#endif//USE_DSA
  return id;
}
std::string VertexArrayObject::getInfo(){
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
#ifndef REMOVE_FUNCTIONS_WITH_OBJECTS_AS_PARAMETERS
void VertexArrayObject::addAttrib(
    ge::gl::BufferObject   *buffer       ,
    GLuint                  index        ,
    GLint                   nofComponents,
    GLenum                  type         ,
    GLsizei                 stride       ,
    const GLvoid           *pointer      ,
    GLboolean               normalized   ,
    GLuint                  divisor      ,
    enum AttribPointerType  apt          ){
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
void VertexArrayObject::addElementBuffer(
    ge::gl::BufferObject *buffer){
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


#endif//REMOVE_FUNCTIONS_WITH_OBJECTS_AS_PARAMETERS
