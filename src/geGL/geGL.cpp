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
  #define PUSH_VAO()\
    GLuint oldId;\
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING,(GLint*)&oldId)
  #define  POP_VAO()\
    glBindVertexArray(oldId)
  #define PUSH_SAMPLER()\
    GLuint oldId;\
    glGetIntegeri_v(GL_SAMPLER_BINDING,0,(GLint*)&oldId)
  #define POP_SAMPLER()\
    glBindSampler(0,oldId)
  #define PUSH_FRAMEBUFFER()\
    GLuint oldId;\
    glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING,(GLint*)&oldId)
  #define POP_FRAMEBUFFER()\
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER,oldId)
  #define PUSH_RENDERBUFFER()\
    GLuint oldId;\
    glGetIntegerv(GL_RENDERBUFFER_BINDING,(GLint*)&oldId)
  #define POP_RENDERBUFFER()\
    glBindRenderbuffer(GL_RENDERBUFFER,oldId)
  #define PUSH_PIPELINE()\
    GLuint oldId;\
    glGetIntegerv(GL_PROGRAM_PIPELINE_BINDING,(GLint*)&oldId)
  #define POP_PIPELINE()\
    glBindProgramPipeline(oldId)
#else //SAVE_PREVIOUS_BINDING
  #define PUSH_WRITE_BUFFER()
  #define POP_WRITE_BUFFER()
  #define PUSH_READ_BUFFER()
  #define POP_READ_BUFFER()
  #define PUSH_VAO()
  #define  POP_VAO()
  #define PUSH_SAMPLER()
  #define POP_SAMPLER()
  #define PUSH_FRAMEBUFFER()
  #define POP_FRAMEBUFFER()
  #define PUSH_RENDERBUFFER()
  #define POP_RENDERBUFFER()
  #define PUSH_PIPELINE()
  #define POP_PIPELINE()
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

void geGL_glGetVertexArrayiv(GLuint id,GLenum pname,GLint*param){
  PUSH_VAO();
  glBindVertexArray(id);
  glGetIntegerv(pname,param);
  POP_VAO();
}

void geGL_glGetVertexArrayIndexediv(GLuint id,GLuint index,GLenum pname,GLint*param){
  PUSH_VAO();
  glBindVertexArray(id);
  glGetVertexAttribiv(index,pname,param);
  POP_VAO();
}

void geGL_glVertexArrayElementBuffer(GLuint id,GLuint buffer){
  PUSH_VAO();
  glBindVertexArray(id);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,buffer);
  POP_VAO();
}

void geGL_glCreateVertexArrays(GLsizei n,GLuint*arrays){
  PUSH_VAO();
  glGenVertexArrays(n,arrays);
  for(GLsizei i=0;i<n;++i)
    glBindVertexArray(arrays[i]);
  POP_VAO();
}

void geGL_glVertexArrayBindingDivisor(GLuint id,GLuint bindingindex,GLuint divisor){
  PUSH_VAO();
  glBindVertexArray(id);
  glVertexBindingDivisor(bindingindex,divisor);
  POP_VAO();
}

void geGL_glVertexArrayVertexBuffer(GLuint id,GLuint bindingindex,GLuint buffer,GLintptr offset,GLsizei stride){
  PUSH_VAO();
  glBindVertexArray(id);
  glBindVertexBuffer(bindingindex,buffer,offset,stride);
  POP_VAO();
}

void geGL_glVertexArrayAttribLFormat(GLuint id,GLuint attribindex,GLint size,GLenum type,GLuint relativeoffset){
  PUSH_VAO();
  glBindVertexArray(id);
  glVertexAttribLFormat(attribindex,size,type,relativeoffset);
  POP_VAO();
}

void geGL_glVertexArrayAttribIFormat(GLuint id,GLuint attribindex,GLint size,GLenum type,GLuint relativeoffset){
  PUSH_VAO();
  glBindVertexArray(id);
  glVertexAttribIFormat(attribindex,size,type,relativeoffset);
  POP_VAO();
}

void geGL_glVertexArrayAttribFormat(GLuint id,GLuint attribindex,GLint size,GLenum type,GLboolean normalized,GLuint relativeoffset){
  PUSH_VAO();
  glBindVertexArray(id);
  glVertexAttribFormat(attribindex,size,type,normalized,relativeoffset);
  POP_VAO();
}

void geGL_glEnableVertexArrayAttrib(GLuint id,GLuint index){
  PUSH_VAO();
  glBindVertexArray(id);
  glEnableVertexAttribArray(index);
  POP_VAO();
}

void geGL_glVertexArrayAttribBinding(GLuint id,GLuint attribindex,GLuint bindingindex){
  PUSH_VAO();
  glBindVertexArray(id);
  glVertexAttribBinding(attribindex,bindingindex);
  POP_VAO();
}

void geGL_glCreateSamplers(GLsizei n,GLuint*samplers){
  PUSH_SAMPLER();
  glGenSamplers(n,samplers);
  for(GLsizei i=0;i<n;++i)
    glBindSampler(0,samplers[i]);
  POP_SAMPLER();
}

GLenum geGL_glCheckNamedFramebufferStatus(GLuint id,GLenum target){
  GLenum result;
  PUSH_FRAMEBUFFER();
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER,id);
  result = glCheckFramebufferStatus(target);
  POP_FRAMEBUFFER();
  return result;
}

void geGL_glCreateFramebuffers(GLsizei n,GLuint*ids){
  PUSH_FRAMEBUFFER();
  glGenFramebuffers(n,ids);
  for(GLsizei i=0;i<n;++i)
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER,ids[i]);
  POP_FRAMEBUFFER();
}

void geGL_glNamedFramebufferTexture(GLuint id,GLenum attachment,GLuint texture,GLint level){
  PUSH_FRAMEBUFFER();
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER,id);
  glFramebufferTexture(GL_DRAW_FRAMEBUFFER,attachment,texture,level);
  POP_FRAMEBUFFER();
}

void geGL_glNamedFramebufferRenderbuffer(GLuint id,GLenum attachment,GLenum rtarget,GLuint renderbuffer){
  PUSH_FRAMEBUFFER();
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER,id);
  glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER,attachment,rtarget,renderbuffer);
  POP_FRAMEBUFFER();
}

void geGL_glGetNamedFramebufferAttachmentParameteriv(GLuint id,GLenum attachment,GLenum pname,GLint*params){
  PUSH_FRAMEBUFFER();
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER,id);
  glGetFramebufferAttachmentParameteriv(GL_DRAW_FRAMEBUFFER,attachment,pname,params);
  POP_FRAMEBUFFER();
}

void geGL_glNamedFramebufferParameteri(GLuint id,GLenum pname,GLint param){
  PUSH_FRAMEBUFFER();
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER,id);
  glFramebufferParameteri(GL_DRAW_FRAMEBUFFER,pname,param);
  POP_FRAMEBUFFER();
}

void geGL_glGetNamedFramebufferParameteriv(GLuint id,GLenum pname,GLint*params){
  PUSH_FRAMEBUFFER();
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER,id);
  glGetFramebufferParameteriv(GL_DRAW_FRAMEBUFFER,pname,params);
  POP_FRAMEBUFFER();
}

void geGL_glNamedFramebufferDrawBuffer(GLuint id,GLenum buffer){
  PUSH_FRAMEBUFFER();
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER,id);
  glDrawBuffer(buffer);
  POP_FRAMEBUFFER();
}

void geGL_glNamedFramebufferDrawBuffers(GLuint id,GLsizei n,const GLenum*bufs){
  PUSH_FRAMEBUFFER();
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER,id);
  glDrawBuffers(n,bufs);
  POP_FRAMEBUFFER();
}

void geGL_glNamedFramebufferTextureLayer(GLuint id,GLenum attachment,GLuint texture,GLint level,GLint layer){
  PUSH_FRAMEBUFFER();
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER,id);
  glFramebufferTextureLayer(GL_DRAW_FRAMEBUFFER,attachment,texture,level,layer);
  POP_FRAMEBUFFER();
}

void geGL_glClearNamedFramebufferiv(GLuint id,GLenum buffer,GLint drawBuffer,const GLint*value){
  PUSH_FRAMEBUFFER();
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER,id);
  glClearBufferiv(buffer,drawBuffer,value);
  POP_FRAMEBUFFER();
}

void geGL_glClearNamedFramebufferfv(GLuint id,GLenum buffer,GLint drawBuffer,const GLfloat*value){
  PUSH_FRAMEBUFFER();
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER,id);
  glClearBufferfv(buffer,drawBuffer,value);
  POP_FRAMEBUFFER();
}

void geGL_glClearNamedFramebufferuiv(GLuint id,GLenum buffer,GLint drawBuffer,const GLuint*value){
  PUSH_FRAMEBUFFER();
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER,id);
  glClearBufferuiv(buffer,drawBuffer,value);
  POP_FRAMEBUFFER();
}

void geGL_glClearNamedFramebufferfi(GLuint id,GLenum buffer,GLfloat depth,GLint stencil){
  PUSH_FRAMEBUFFER();
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER,id);
  glClearBufferfi(GL_DRAW_FRAMEBUFFER,buffer,depth,stencil);
  POP_FRAMEBUFFER();
}

void geGL_glInvalidateNamedFramebufferData(GLuint id,GLsizei numAttachments,const GLenum*attachments){
  PUSH_FRAMEBUFFER();
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER,id);
  glInvalidateFramebuffer(GL_DRAW_FRAMEBUFFER,numAttachments,attachments);
  POP_FRAMEBUFFER();
}

void geGL_glInvalidateNamedFramebufferSubData(GLuint id,GLsizei numAttachments,const GLenum*attachments,GLint x,GLint y,GLsizei width,GLsizei height){
  PUSH_FRAMEBUFFER();
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER,id);
  glInvalidateSubFramebuffer(GL_DRAW_FRAMEBUFFER,numAttachments,attachments,x,y,width,height);
  POP_FRAMEBUFFER();
}

void geGL_glGetNamedRenderbufferParameteriv(GLuint id,GLenum pname,GLint*params){
  PUSH_RENDERBUFFER();
  glBindRenderbuffer(GL_RENDERBUFFER,id);
  glGetRenderbufferParameteriv(GL_RENDERBUFFER,pname,params);
  POP_RENDERBUFFER();
}

void geGL_glNamedRenderbufferStorageMultisample(GLuint id,GLsizei samples,GLenum internalFormat,GLsizei width,GLsizei height){
  PUSH_RENDERBUFFER();
  glBindRenderbuffer(GL_RENDERBUFFER,id);
  glRenderbufferStorageMultisample(GL_RENDERBUFFER,samples,internalFormat,width,height);
  POP_RENDERBUFFER();
}

void geGL_glNamedRenderbufferStorage(GLuint id,GLenum internalFormat,GLsizei width,GLsizei height){
  PUSH_RENDERBUFFER();
  glBindRenderbuffer(GL_RENDERBUFFER,id);
  glRenderbufferStorage(GL_RENDERBUFFER,internalFormat,width,height);
  POP_RENDERBUFFER();
}

void geGL_glCreateRenderbuffers(GLsizei n,GLuint*ids){
  PUSH_RENDERBUFFER();
  glGenRenderbuffers(n,ids);
  for(GLsizei i=0;i<n;++i)
    glBindRenderbuffer(GL_RENDERBUFFER,ids[i]);
  POP_RENDERBUFFER();
}

void geGL_glCreateProgramPipelines(GLsizei n,GLuint*ids){
  PUSH_PIPELINE();
  glGenProgramPipelines(n,ids);
  for(GLsizei i=0;i<n;++i)
    glBindProgramPipeline(ids[i]);
  POP_PIPELINE();
}

#define IMPLEMENT_VENDOR(name,ven)\
  if(name##ven)name=name##ven;

#define IMPLEMENT_VENDOR_ELSEIF(name,ven)\
  else if(name##ven)=name=name##ven;

#define IMPLEMENT1(name,ven0)\
  if(!name){\
    IMPLEMENT_VENDOR(name,ven0)\
    else name = geGL_##name;\
  }

#define IMPLEMENT2(name,ven0,ven1)\
  if(!name){\
    IMPLEMENT_VENDOR(name,ven0)\
    IMPLEMENT_VENDOR_ELSEIF(name,ven1)\
    else name = geGL_##name;\
  }

#define IMPLEMENT3(name,ven0,ven1,ven2)\
  if(!name){\
    IMPLEMENT_VENDOR(name,ven0)\
    IMPLEMENT_VENDOR_ELSEIF(name,ven1)\
    IMPLEMENT_VENDOR_ELSEIF(name,ven2)\
    else name = geGL_##name;\
  }

#define IMPLEMENT4(name,ven0,ven1,ven2,ven3)\
  if(!name){\
    IMPLEMENT_VENDOR(name,ven0)\
    IMPLEMENT_VENDOR_ELSEIF(name,ven1)\
    IMPLEMENT_VENDOR_ELSEIF(name,ven2)\
    IMPLEMENT_VENDOR_ELSEIF(name,ven3)\
    else name = geGL_##name;\
  }

#define IMPLEMENT(name)\
  if(!name)name = geGL_##name

void implementBufferDSA(){
  IMPLEMENT1(glNamedBufferData            ,EXT);
  IMPLEMENT1(glNamedBufferStorage         ,EXT);
  IMPLEMENT (glCreateBuffers                  );
  IMPLEMENT (glCopyNamedBufferSubData         );
  IMPLEMENT1(glFlushMappedNamedBufferRange,EXT);
  IMPLEMENT1(glClearNamedBufferData       ,EXT);
  IMPLEMENT1(glClearNamedBufferSubData    ,EXT);
  IMPLEMENT1(glMapNamedBufferRange        ,EXT);
  IMPLEMENT1(glUnmapNamedBuffer           ,EXT);
  IMPLEMENT1(glNamedBufferSubData         ,EXT);
  IMPLEMENT1(glGetNamedBufferSubData      ,EXT);
  IMPLEMENT1(glGetNamedBufferParameteriv  ,EXT);
  IMPLEMENT1(glGetNamedBufferPointerv     ,EXT);
}

void implementVertexArrayDSA(){
  IMPLEMENT (glCreateVertexArrays           );
  IMPLEMENT (glGetVertexArrayiv             );
  IMPLEMENT (glGetVertexArrayIndexediv      );
  IMPLEMENT (glVertexArrayElementBuffer     );
  IMPLEMENT (glVertexArrayBindingDivisor    );
  IMPLEMENT (glVertexArrayVertexBuffer      );
  IMPLEMENT (glVertexArrayAttribLFormat     );
  IMPLEMENT (glVertexArrayAttribIFormat     );
  IMPLEMENT (glVertexArrayAttribFormat      );
  IMPLEMENT1(glEnableVertexArrayAttrib  ,EXT);
  IMPLEMENT (glVertexArrayAttribBinding     );
}

void implementSamplerDSA(){
  IMPLEMENT(glCreateSamplers);
}

void implementFramebufferDSA(){
  IMPLEMENT1(glCheckNamedFramebufferStatus             ,EXT);
  IMPLEMENT (glCreateFramebuffers                          );
  IMPLEMENT1(glNamedFramebufferTexture                 ,EXT);
  IMPLEMENT1(glNamedFramebufferRenderbuffer            ,EXT);
  IMPLEMENT1(glGetNamedFramebufferAttachmentParameteriv,EXT);
  IMPLEMENT1(glNamedFramebufferParameteri              ,EXT);
  IMPLEMENT1(glGetNamedFramebufferParameteriv          ,EXT);
  IMPLEMENT (glNamedFramebufferDrawBuffer                  );
  IMPLEMENT (glNamedFramebufferDrawBuffers                 );
  IMPLEMENT1(glNamedFramebufferTextureLayer            ,EXT);
  IMPLEMENT (glClearNamedFramebufferiv                     );
  IMPLEMENT (glClearNamedFramebufferfv                     );
  IMPLEMENT (glClearNamedFramebufferuiv                    );
  IMPLEMENT (glClearNamedFramebufferfi                     );
  IMPLEMENT (glInvalidateNamedFramebufferData              );
  IMPLEMENT (glInvalidateNamedFramebufferSubData           );
}

void implementRenderbufferDSA(){
  IMPLEMENT1(glGetNamedRenderbufferParameteriv    ,EXT);
  IMPLEMENT1(glNamedRenderbufferStorageMultisample,EXT);
  IMPLEMENT1(glNamedRenderbufferStorage           ,EXT);
  IMPLEMENT (glCreateRenderbuffers                    );
}

void implementPipelineDSA(){
  IMPLEMENT(glCreateProgramPipelines);
}

/**
 * @brief initialize geGL it shout be called fater glewInit
 */
void ge::gl::init(){
  implementBufferDSA      ();
  implementVertexArrayDSA ();
  implementSamplerDSA     ();
  implementFramebufferDSA ();
  implementRenderbufferDSA();
  implementPipelineDSA    ();
}


