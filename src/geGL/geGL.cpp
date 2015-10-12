#include<geGL/geGL.h>

using namespace ge::gl;

//toggle saving previous bindings
#define SAVE_PREVIOUS_BINDING

#ifdef  SAVE_PREVIOUS_BINDING
  #define PUSH_WRITE_BUFFER()\
    GLuint oldWriteId;\
    glGetIntegerv(GL_COPY_WRITE_BUFFER_BINDING,(GLint*)&oldWriteId)
  #define POP_WRITE_BUFFER()\
    glBindBuffer(GL_COPY_WRITE_BUFFER,oldWriteId)
  #define PUSH_READ_BUFFER()\
    GLuint oldReadId;\
    glGetIntegerv(GL_COPY_WRITE_BUFFER_BINDING,(GLint*)&oldReadId)
  #define POP_READ_BUFFER()\
    glBindBuffer(GL_COPY_WRITE_BUFFER,oldReadId)
#else //SAVE_PREVIOUS_BINDING
  #define PUSH_WRITE_BUFFER()
  #define POP_WRITE_BUFFER()
  #define PUSH_READ_BUFFER()
  #define POP_READ_BUFFER()
#endif//SAVE_PREVIOUS_BINDING

void geGL_glNamedBufferStorage(GLuint buffer,GLsizeiptr size,const void*data,GLbitfield flags){
  PUSH_WRITE_BUFFER();
  glBindBuffer(GL_COPY_WRITE_BUFFER,buffer);
  glBufferStorage(GL_COPY_WRITE_BUFFER,size,data,flags);
  POP_WRITE_BUFFER();
}

void geGL_glNamedBufferData(GLuint buffer,GLsizeiptr size,const void*data,GLenum usage){
  PUSH_WRITE_BUFFER();
  glBindBuffer(GL_COPY_WRITE_BUFFER,buffer);
  glBufferData(GL_COPY_WRITE_BUFFER,size,data,usage);
  POP_WRITE_BUFFER();
}

void geGL_glCreateBuffers(GLsizei n,GLuint*buffers){
  PUSH_WRITE_BUFFER();
  glGenBuffers(n,buffers);
  for(GLsizei i=0;i<n;++n)
    glBindBuffer(GL_COPY_WRITE_BUFFER,buffers[i]);
  POP_WRITE_BUFFER();
}

void geGL_glCopyNamedBufferSubData(GLuint readBuffer,GLuint writeBuffer,GLintptr readOffest,GLintptr writeOffset,GLsizeiptr size){
  PUSH_READ_BUFFER();
  PUSH_WRITE_BUFFER();
  glBindBuffer(GL_COPY_READ_BUFFER ,readBuffer );
  glBindBuffer(GL_COPY_WRITE_BUFFER,writeBuffer);
  glCopyBufferSubData(
      GL_COPY_READ_BUFFER,
      GL_COPY_WRITE_BUFFER,
      readOffest,
      writeOffset,
      size);
  POP_READ_BUFFER();
  POP_WRITE_BUFFER();
}

void geGL_glFlushMappedNamedBufferRange(GLuint buffer,GLintptr offset,GLsizeiptr length){
  PUSH_WRITE_BUFFER();
  glBindBuffer(GL_COPY_WRITE_BUFFER,buffer);
  glFlushMappedBufferRange(GL_COPY_WRITE_BUFFER,offset,length);
  POP_WRITE_BUFFER();
}

void geGL_glClearNamedBufferData(GLuint buffer,GLenum internalFormat,GLenum format,GLenum type,const void*data){
  PUSH_WRITE_BUFFER();
  glBindBuffer     (GL_COPY_WRITE_BUFFER,buffer);
  glClearBufferData(GL_COPY_WRITE_BUFFER,internalFormat,format,type,data);
  POP_WRITE_BUFFER();
}

void geGL_glClearNamedBufferSubData(GLuint buffer,GLenum internalFormat,GLintptr offset,GLsizeiptr size,GLenum format,GLenum type,const void*data){
  PUSH_WRITE_BUFFER();
  glBindBuffer        (GL_COPY_WRITE_BUFFER,buffer);
  glClearBufferSubData(GL_COPY_WRITE_BUFFER,internalFormat,offset,size,format,type,data);
  POP_WRITE_BUFFER();
}

GLvoid*geGL_glMapNamedBufferRange(GLuint buffer,GLintptr offset,GLsizeiptr length,GLbitfield access){
  GLvoid*ptr;
  PUSH_WRITE_BUFFER();
  glBindBuffer        (GL_COPY_WRITE_BUFFER,buffer);
  ptr=glMapBufferRange(GL_COPY_WRITE_BUFFER,offset,length,access);
  POP_WRITE_BUFFER();
  return ptr;
}

GLboolean geGL_glUnmapNamedBuffer(GLuint buffer){
  PUSH_WRITE_BUFFER();
  glBindBuffer (GL_COPY_WRITE_BUFFER,buffer);
  GLboolean result=glUnmapBuffer(GL_COPY_WRITE_BUFFER);
  POP_WRITE_BUFFER();
  return result;
}

void geGL_glNamedBufferSubData(GLuint buffer,GLintptr offset,GLsizeiptr size,const GLvoid*data){
  PUSH_WRITE_BUFFER();
  glBindBuffer   (GL_COPY_WRITE_BUFFER,buffer);//bind buffer
  glBufferSubData(GL_COPY_WRITE_BUFFER,offset,size,data);//copy data
  POP_WRITE_BUFFER();
}

void geGL_glGetNamedBufferSubData(GLuint buffer,GLintptr offset,GLsizeiptr size,GLvoid*data){
  PUSH_WRITE_BUFFER();
  glBindBuffer      (GL_COPY_WRITE_BUFFER,buffer);//bind buffer
  glGetBufferSubData(GL_COPY_WRITE_BUFFER,offset,size,data);//obtain data
  POP_WRITE_BUFFER();
}

void geGL_glGetNamedBufferParameteriv(GLuint buffer,GLenum pname,GLint*param){
  PUSH_WRITE_BUFFER();
  glBindBuffer          (GL_COPY_WRITE_BUFFER,buffer);
  glGetBufferParameteriv(GL_COPY_WRITE_BUFFER,pname,param);
  POP_WRITE_BUFFER();
}

void geGL_glGetNamedBufferPointerv(GLuint buffer,GLenum pname,GLvoid**param){
  PUSH_WRITE_BUFFER();
  glBindBuffer       (GL_COPY_WRITE_BUFFER,buffer);
  glGetBufferPointerv(GL_COPY_WRITE_BUFFER,pname,param);
  POP_WRITE_BUFFER();
}

#define IMPLEMENT(name)\
  if(!name)name = geGL_##name

void implementBufferDSA(){
  IMPLEMENT(glNamedBufferData            );
  IMPLEMENT(glNamedBufferStorage         );
  IMPLEMENT(glCreateBuffers              );
  IMPLEMENT(glCopyNamedBufferSubData     );
  IMPLEMENT(glFlushMappedNamedBufferRange);
  IMPLEMENT(glClearNamedBufferData       );
  IMPLEMENT(glClearNamedBufferSubData    );
  IMPLEMENT(glMapNamedBufferRange        );
  IMPLEMENT(glUnmapNamedBuffer           );
  IMPLEMENT(glNamedBufferSubData         );
  IMPLEMENT(glGetNamedBufferSubData      );
  IMPLEMENT(glGetNamedBufferParameteriv  );
  IMPLEMENT(glGetNamedBufferPointerv     );
}

/**
 * @brief initialize geGL it shout be called fater glewInit
 */
void ge::gl::init(){
  implementBufferDSA();
}


