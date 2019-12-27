#pragma once

#include<map>
#include<geGL/OpenGLFunctionTable.h>
#include<geGL/OpenGLUtil.h>

#define ASSIGN_DSA(name)\
  this->m_ptr_##name =\
    (decltype(FunctionTable::m_ptr_##name))\
      &DSATableDecorator::m_##name##_dsa

#define IF_NOT_M_PTR_FCE(name)\
  if(!this->m_ptr_##name)

#define IMPLEMENT_VENDOR(name,ven)\
  if(this->m_ptr_##name##ven)this->m_ptr_##name = this->m_ptr_##name##ven;

#define IMPLEMENT0(name)\
  IF_NOT_M_PTR_FCE(name)ASSIGN_DSA(name)

#define IMPLEMENT1(name,ven0)\
  IF_NOT_M_PTR_FCE(name){\
    IMPLEMENT_VENDOR(name,ven0)\
    else ASSIGN_DSA(name);\
  }

#define IMPLEMENT2(name,ven0,ven1)\
  IF_NOT_M_PTR_FCE(name){\
    IMPLEMENT_VENDOR(name,ven0)\
    else IMPLEMENT_VENDOR(name,ven1)\
    else ASSIGN_DSA(name);\
  }

#define IMPLEMENT3(name,ven0,ven1,ven2)\
  IF_NOT_M_PTR_FCE(name){\
    IMPLEMENT_VENDOR(name,ven0)\
    else IMPLEMENT_VENDOR(name,ven1)\
    else IMPLEMENT_VENDOR(name,ven2)\
    else ASSIGN_DSA(name);\
  }

#define IMPLEMENT4(name,ven0,ven1,ven2,ven3)\
  IF_NOT_M_PTR_FCE(name){\
    IMPLEMENT_VENDOR(name,ven0)\
    else IMPLEMENT_VENDOR(name,ven1)\
    else IMPLEMENT_VENDOR(name,ven2)\
    else IMPLEMENT_VENDOR(name,ven3)\
    else ASSIGN_DSA(name);\
  }

//toggle saving previous bindings
#define SAVE_PREVIOUS_BINDING

#ifdef  SAVE_PREVIOUS_BINDING
#define PUSH_WRITE_BUFFER()\
  GLuint oldWriteId;\
this->glGetIntegerv(GL_COPY_WRITE_BUFFER_BINDING,(GLint*)&oldWriteId)
#define POP_WRITE_BUFFER()\
  this->glBindBuffer(GL_COPY_WRITE_BUFFER,oldWriteId)
#define PUSH_READ_BUFFER()\
  GLuint oldReadId;\
this->glGetIntegerv(GL_COPY_WRITE_BUFFER_BINDING,(GLint*)&oldReadId)
#define POP_READ_BUFFER()\
  this->glBindBuffer(GL_COPY_WRITE_BUFFER,oldReadId)
#define PUSH_VAO()\
  GLuint oldId;\
this->glGetIntegerv(GL_VERTEX_ARRAY_BINDING,(GLint*)&oldId)
#define  POP_VAO()\
  this->glBindVertexArray(oldId)
#define PUSH_SAMPLER()\
  GLuint oldId;\
this->glGetIntegeri_v(GL_SAMPLER_BINDING,0,(GLint*)&oldId)
#define POP_SAMPLER()\
  this->glBindSampler(0,oldId)
#define PUSH_FRAMEBUFFER()\
  GLuint oldId;\
this->glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING,(GLint*)&oldId)
#define POP_FRAMEBUFFER()\
  this->glBindFramebuffer(GL_DRAW_FRAMEBUFFER,oldId)
#define PUSH_RENDERBUFFER()\
  GLuint oldId;\
this->glGetIntegerv(GL_RENDERBUFFER_BINDING,(GLint*)&oldId)
#define POP_RENDERBUFFER()\
  this->glBindRenderbuffer(GL_RENDERBUFFER,oldId)
#define PUSH_PIPELINE()\
  GLuint oldId;\
this->glGetIntegerv(GL_PROGRAM_PIPELINE_BINDING,(GLint*)&oldId)
#define POP_PIPELINE()\
  this->glBindProgramPipeline(oldId)
#define PUSH_TEXTURE(x)\
  GLuint oldId;\
this->glGetIntegerv(ge::gl::textureTarget2Binding(x),(GLint*)&oldId)
#define POP_TEXTURE(x)\
  this->glBindTexture(x,oldId)
#define PUSH_ACTIVE_TEXTURE()\
  GLenum oldTex;\
this->glGetIntegerv(GL_ACTIVE_TEXTURE,(GLint*)&oldTex)
#define POP_ACTIVE_TEXTURE()\
  this->glActiveTexture(oldTex)
#else //SAVE_PREVIOUS_BINDING
#define PUSH_WRITE_BUFFER()
#define POP_WRITE_BUFFER()
#define PUSH_READ_BUFFER()
#define POP_READ_BUFFER()
#define PUSH_VAO()
#define POP_VAO()
#define PUSH_SAMPLER()
#define POP_SAMPLER()
#define PUSH_FRAMEBUFFER()
#define POP_FRAMEBUFFER()
#define PUSH_RENDERBUFFER()
#define POP_RENDERBUFFER()
#define PUSH_PIPELINE()
#define POP_PIPELINE()
#define PUSH_TEXTURE(x)
#define POP_TEXTURE(x)
#define PUSH_ACTIVE_TEXTURE()
#define POP_ACTIVE_TEXTURE()
#endif//SAVE_PREVIOUS_BINDING


namespace ge{
  namespace gl{
    template<typename T>
      class DSATableDecorator: public T{
        public:
          template<typename...ARGS>
            DSATableDecorator(ARGS&&...args):T(args...){}
          virtual ~DSATableDecorator(){}
        protected:
          virtual bool m_init(){
            if(!T::m_init())return false;
            IMPLEMENT1(glNamedBufferData            ,EXT);
            IMPLEMENT1(glNamedBufferStorage         ,EXT);
            IMPLEMENT0(glCreateBuffers                  );
            IMPLEMENT0(glCopyNamedBufferSubData         );
            IMPLEMENT1(glFlushMappedNamedBufferRange,EXT);
            IMPLEMENT1(glClearNamedBufferData       ,EXT);
            IMPLEMENT1(glClearNamedBufferSubData    ,EXT);
            IMPLEMENT1(glMapNamedBufferRange        ,EXT);
            IMPLEMENT1(glUnmapNamedBuffer           ,EXT);
            IMPLEMENT1(glNamedBufferSubData         ,EXT);
            IMPLEMENT1(glGetNamedBufferSubData      ,EXT);
            IMPLEMENT1(glGetNamedBufferParameteriv  ,EXT);
            IMPLEMENT0(glGetNamedBufferParameteri64v    );
            IMPLEMENT1(glGetNamedBufferPointerv     ,EXT);

            IMPLEMENT0(glCreateVertexArrays           );
            IMPLEMENT0(glGetVertexArrayiv             );
            IMPLEMENT0(glGetVertexArrayIndexediv      );
            IMPLEMENT0(glVertexArrayElementBuffer     );
            IMPLEMENT0(glVertexArrayBindingDivisor    );
            IMPLEMENT0(glVertexArrayVertexBuffer      );
            IMPLEMENT0(glVertexArrayAttribLFormat     );
            IMPLEMENT0(glVertexArrayAttribIFormat     );
            IMPLEMENT0(glVertexArrayAttribFormat      );
            IMPLEMENT1(glEnableVertexArrayAttrib  ,EXT);
            IMPLEMENT0(glVertexArrayAttribBinding     );

            IMPLEMENT0(glCreateSamplers);

            IMPLEMENT1(glCheckNamedFramebufferStatus             ,EXT);
            IMPLEMENT0(glCreateFramebuffers                          );
            IMPLEMENT1(glNamedFramebufferTexture                 ,EXT);
            IMPLEMENT1(glNamedFramebufferRenderbuffer            ,EXT);
            IMPLEMENT1(glGetNamedFramebufferAttachmentParameteriv,EXT);
            IMPLEMENT1(glNamedFramebufferParameteri              ,EXT);
            IMPLEMENT1(glGetNamedFramebufferParameteriv          ,EXT);
            IMPLEMENT0(glNamedFramebufferDrawBuffer                  );
            IMPLEMENT0(glNamedFramebufferDrawBuffers                 );
            IMPLEMENT1(glNamedFramebufferTextureLayer            ,EXT);
            IMPLEMENT0(glClearNamedFramebufferiv                     );
            IMPLEMENT0(glClearNamedFramebufferfv                     );
            IMPLEMENT0(glClearNamedFramebufferuiv                    );
            IMPLEMENT0(glClearNamedFramebufferfi                     );
            IMPLEMENT0(glInvalidateNamedFramebufferData              );
            IMPLEMENT0(glInvalidateNamedFramebufferSubData           );

            IMPLEMENT1(glGetNamedRenderbufferParameteriv    ,EXT);
            IMPLEMENT1(glNamedRenderbufferStorageMultisample,EXT);
            IMPLEMENT1(glNamedRenderbufferStorage           ,EXT);
            IMPLEMENT0(glCreateRenderbuffers                    );

            IMPLEMENT0(glCreateProgramPipelines);

            if(!this->m_ptr_glCreateTextures){
              this->m_ptr_glCreateTextures =(decltype(FunctionTable::m_ptr_glCreateTextures))&DSATableDecorator::m_glCreateTextures_dsa;
              this->m_ptr_glDeleteTextures =(decltype(FunctionTable::m_ptr_glDeleteTextures))&DSATableDecorator::m_glDeleteTextures_dsa;
            }
            IMPLEMENT0(glTextureImage1DEXT          );
            IMPLEMENT0(glTextureImage2DEXT          );
            IMPLEMENT0(glTextureImage3DEXT          );
            IMPLEMENT0(glTextureSubImage2DEXT       );
            IMPLEMENT0(glTextureSubImage3DEXT       );
            IMPLEMENT0(glCompressedTextureImage1DEXT);
            IMPLEMENT0(glCompressedTextureImage2DEXT);
            IMPLEMENT0(glCompressedTextureImage3DEXT);
            IMPLEMENT0(glTextureSubImage1D          );
            IMPLEMENT0(glTextureSubImage2D          );
            IMPLEMENT0(glTextureSubImage3D          );
            IMPLEMENT0(glBindTextureUnit            );
            IMPLEMENT0(glTextureStorage1D           );
            IMPLEMENT0(glTextureStorage2D           );
            IMPLEMENT0(glTextureStorage3D           );
            IMPLEMENT0(glTextureParameteri          );
            IMPLEMENT0(glTextureParameterf          );
            IMPLEMENT0(glTextureParameteriv         );
            IMPLEMENT0(glTextureParameterfv         );
            IMPLEMENT0(glGetTextureLevelParameteriv );
            IMPLEMENT0(glGetTextureLevelParameterfv );
            IMPLEMENT0(glGetTextureParameteriv      );
            IMPLEMENT0(glGetTextureParameterfv      );
            IMPLEMENT0(glGetTextureParameterIiv     );
            IMPLEMENT0(glGetTextureParameterIuiv    );

            return true;
          }
          void m_glNamedBufferStorage_dsa(GLuint buffer,GLsizeiptr size,const void*data,GLbitfield flags){
            PUSH_WRITE_BUFFER();
            this->glBindBuffer(GL_COPY_WRITE_BUFFER,buffer);
            this->glBufferStorage(GL_COPY_WRITE_BUFFER,size,data,flags);
            POP_WRITE_BUFFER();
          }

          void m_glNamedBufferData_dsa(GLuint buffer,GLsizeiptr size,const void*data,GLenum usage){
            PUSH_WRITE_BUFFER();
            this->glBindBuffer(GL_COPY_WRITE_BUFFER,buffer);
            this->glBufferData(GL_COPY_WRITE_BUFFER,size,data,usage);
            POP_WRITE_BUFFER();
          }

          void m_glCreateBuffers_dsa(GLsizei n,GLuint*buffers){
            PUSH_WRITE_BUFFER();
            this->glGenBuffers(n,buffers);
            for(GLsizei i=0;i<n;++i)
              this->glBindBuffer(GL_COPY_WRITE_BUFFER,buffers[i]);
            POP_WRITE_BUFFER();
          }

          void m_glCopyNamedBufferSubData_dsa(GLuint readBuffer,GLuint writeBuffer,GLintptr readOffest,GLintptr writeOffset,GLsizeiptr size){
            PUSH_READ_BUFFER();
            PUSH_WRITE_BUFFER();
            this->glBindBuffer(GL_COPY_READ_BUFFER ,readBuffer );
            this->glBindBuffer(GL_COPY_WRITE_BUFFER,writeBuffer);
            this->glCopyBufferSubData(
                GL_COPY_READ_BUFFER,
                GL_COPY_WRITE_BUFFER,
                readOffest,
                writeOffset,
                size);
            POP_READ_BUFFER();
            POP_WRITE_BUFFER();
          }

          void m_glFlushMappedNamedBufferRange_dsa(GLuint buffer,GLintptr offset,GLsizeiptr length){
            PUSH_WRITE_BUFFER();
            this->glBindBuffer(GL_COPY_WRITE_BUFFER,buffer);
            this->glFlushMappedBufferRange(GL_COPY_WRITE_BUFFER,offset,length);
            POP_WRITE_BUFFER();
          }

          void m_glClearNamedBufferData_dsa(GLuint buffer,GLenum internalFormat,GLenum format,GLenum type,const void*data){
            PUSH_WRITE_BUFFER();
            this->glBindBuffer     (GL_COPY_WRITE_BUFFER,buffer);
            this->glClearBufferData(GL_COPY_WRITE_BUFFER,internalFormat,format,type,data);
            POP_WRITE_BUFFER();
          }

          void m_glClearNamedBufferSubData_dsa(GLuint buffer,GLenum internalFormat,GLintptr offset,GLsizeiptr size,GLenum format,GLenum type,const void*data){
            PUSH_WRITE_BUFFER();
            this->glBindBuffer        (GL_COPY_WRITE_BUFFER,buffer);
            this->glClearBufferSubData(GL_COPY_WRITE_BUFFER,internalFormat,offset,size,format,type,data);
            POP_WRITE_BUFFER();
          }

          GLvoid*m_glMapNamedBufferRange_dsa(GLuint buffer,GLintptr offset,GLsizeiptr length,GLbitfield access){
            GLvoid*ptr;
            PUSH_WRITE_BUFFER();
            this->glBindBuffer        (GL_COPY_WRITE_BUFFER,buffer);
            ptr=this->glMapBufferRange(GL_COPY_WRITE_BUFFER,offset,length,access);
            POP_WRITE_BUFFER();
            return ptr;
          }

          GLboolean m_glUnmapNamedBuffer_dsa(GLuint buffer){
            PUSH_WRITE_BUFFER();
            this->glBindBuffer (GL_COPY_WRITE_BUFFER,buffer);
            GLboolean result=this->glUnmapBuffer(GL_COPY_WRITE_BUFFER);
            POP_WRITE_BUFFER();
            return result;
          }

          void m_glNamedBufferSubData_dsa(GLuint buffer,GLintptr offset,GLsizeiptr size,const GLvoid*data){
            PUSH_WRITE_BUFFER();
            this->glBindBuffer   (GL_COPY_WRITE_BUFFER,buffer);//bind buffer
            this->glBufferSubData(GL_COPY_WRITE_BUFFER,offset,size,data);//copy data
            POP_WRITE_BUFFER();
          }

          void m_glGetNamedBufferSubData_dsa(GLuint buffer,GLintptr offset,GLsizeiptr size,GLvoid*data){
            PUSH_WRITE_BUFFER();
            this->glBindBuffer      (GL_COPY_WRITE_BUFFER,buffer);//bind buffer
            this->glGetBufferSubData(GL_COPY_WRITE_BUFFER,offset,size,data);//obtain data
            POP_WRITE_BUFFER();
          }

          void m_glGetNamedBufferParameteriv_dsa(GLuint buffer,GLenum pname,GLint*param){
            PUSH_WRITE_BUFFER();
            this->glBindBuffer          (GL_COPY_WRITE_BUFFER,buffer);
            this->glGetBufferParameteriv(GL_COPY_WRITE_BUFFER,pname,param);
            POP_WRITE_BUFFER();
          }

          void m_glGetNamedBufferParameteri64v_dsa(GLuint buffer,GLenum pname,GLint64*param){
            PUSH_WRITE_BUFFER();
            this->glBindBuffer          (GL_COPY_WRITE_BUFFER,buffer);
            this->glGetBufferParameteri64v(GL_COPY_WRITE_BUFFER,pname,param);
            POP_WRITE_BUFFER();
          }

          void m_glGetNamedBufferPointerv_dsa(GLuint buffer,GLenum pname,GLvoid**param){
            PUSH_WRITE_BUFFER();
            this->glBindBuffer       (GL_COPY_WRITE_BUFFER,buffer);
            this->glGetBufferPointerv(GL_COPY_WRITE_BUFFER,pname,param);
            POP_WRITE_BUFFER();
          }
          void m_glGetVertexArrayiv_dsa(GLuint id,GLenum pname,GLint*param){
            PUSH_VAO();
            this->glBindVertexArray(id);
            this->glGetIntegerv(pname,param);
            POP_VAO();
          }

          void m_glGetVertexArrayIndexediv_dsa(GLuint id,GLuint index,GLenum pname,GLint*param){
            PUSH_VAO();
            this->glBindVertexArray(id);
            this->glGetVertexAttribiv(index,pname,param);
            POP_VAO();
          }

          void m_glVertexArrayElementBuffer_dsa(GLuint id,GLuint buffer){
            PUSH_VAO();
            this->glBindVertexArray(id);
            this->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,buffer);
            POP_VAO();
          }

          void m_glCreateVertexArrays_dsa(GLsizei n,GLuint*arrays){
            PUSH_VAO();
            this->glGenVertexArrays(n,arrays);
            for(GLsizei i=0;i<n;++i)
              this->glBindVertexArray(arrays[i]);
            POP_VAO();
          }

          void m_glVertexArrayBindingDivisor_dsa(GLuint id,GLuint bindingindex,GLuint divisor){
            PUSH_VAO();
            this->glBindVertexArray(id);
            this->glVertexBindingDivisor(bindingindex,divisor);
            POP_VAO();
          }

          void m_glVertexArrayVertexBuffer_dsa(GLuint id,GLuint bindingindex,GLuint buffer,GLintptr offset,GLsizei stride){
            PUSH_VAO();
            this->glBindVertexArray(id);
            this->glBindVertexBuffer(bindingindex,buffer,offset,stride);
            POP_VAO();
          }

          void m_glVertexArrayAttribLFormat_dsa(GLuint id,GLuint attribindex,GLint size,GLenum type,GLuint relativeoffset){
            PUSH_VAO();
            this->glBindVertexArray(id);
            this->glVertexAttribLFormat(attribindex,size,type,relativeoffset);
            POP_VAO();
          }

          void m_glVertexArrayAttribIFormat_dsa(GLuint id,GLuint attribindex,GLint size,GLenum type,GLuint relativeoffset){
            PUSH_VAO();
            this->glBindVertexArray(id);
            this->glVertexAttribIFormat(attribindex,size,type,relativeoffset);
            POP_VAO();
          }

          void m_glVertexArrayAttribFormat_dsa(GLuint id,GLuint attribindex,GLint size,GLenum type,GLboolean normalized,GLuint relativeoffset){
            PUSH_VAO();
            this->glBindVertexArray(id);
            this->glVertexAttribFormat(attribindex,size,type,normalized,relativeoffset);
            POP_VAO();
          }

          void m_glEnableVertexArrayAttrib_dsa(GLuint id,GLuint index){
            PUSH_VAO();
            this->glBindVertexArray(id);
            this->glEnableVertexAttribArray(index);
            POP_VAO();
          }

          void m_glVertexArrayAttribBinding_dsa(GLuint id,GLuint attribindex,GLuint bindingindex){
            PUSH_VAO();
            this->glBindVertexArray(id);
            this->glVertexAttribBinding(attribindex,bindingindex);
            POP_VAO();
          }

          void m_glCreateSamplers_dsa(GLsizei n,GLuint*samplers){
            PUSH_SAMPLER();
            this->glGenSamplers(n,samplers);
            for(GLsizei i=0;i<n;++i)
              this->glBindSampler(0,samplers[i]);
            POP_SAMPLER();
          }

          GLenum m_glCheckNamedFramebufferStatus_dsa(GLuint id,GLenum target){
            GLenum result;
            PUSH_FRAMEBUFFER();
            this->glBindFramebuffer(GL_DRAW_FRAMEBUFFER,id);
            result = this->glCheckFramebufferStatus(target);
            POP_FRAMEBUFFER();
            return result;
          }

          void m_glCreateFramebuffers_dsa(GLsizei n,GLuint*ids){
            PUSH_FRAMEBUFFER();
            this->glGenFramebuffers(n,ids);
            for(GLsizei i=0;i<n;++i)
              this->glBindFramebuffer(GL_DRAW_FRAMEBUFFER,ids[i]);
            POP_FRAMEBUFFER();
          }

          void m_glNamedFramebufferTexture_dsa(GLuint id,GLenum attachment,GLuint texture,GLint level){
            PUSH_FRAMEBUFFER();
            this->glBindFramebuffer(GL_DRAW_FRAMEBUFFER,id);
            this->glFramebufferTexture(GL_DRAW_FRAMEBUFFER,attachment,texture,level);
            POP_FRAMEBUFFER();
          }

          void m_glNamedFramebufferRenderbuffer_dsa(GLuint id,GLenum attachment,GLenum rtarget,GLuint renderbuffer){
            PUSH_FRAMEBUFFER();
            this->glBindFramebuffer(GL_DRAW_FRAMEBUFFER,id);
            this->glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER,attachment,rtarget,renderbuffer);
            POP_FRAMEBUFFER();
          }

          void m_glGetNamedFramebufferAttachmentParameteriv_dsa(GLuint id,GLenum attachment,GLenum pname,GLint*params){
            PUSH_FRAMEBUFFER();
            this->glBindFramebuffer(GL_DRAW_FRAMEBUFFER,id);
            this->glGetFramebufferAttachmentParameteriv(GL_DRAW_FRAMEBUFFER,attachment,pname,params);
            POP_FRAMEBUFFER();
          }

          void m_glNamedFramebufferParameteri_dsa(GLuint id,GLenum pname,GLint param){
            PUSH_FRAMEBUFFER();
            this->glBindFramebuffer(GL_DRAW_FRAMEBUFFER,id);
            this->glFramebufferParameteri(GL_DRAW_FRAMEBUFFER,pname,param);
            POP_FRAMEBUFFER();
          }

          void m_glGetNamedFramebufferParameteriv_dsa(GLuint id,GLenum pname,GLint*params){
            PUSH_FRAMEBUFFER();
            this->glBindFramebuffer(GL_DRAW_FRAMEBUFFER,id);
            this->glGetFramebufferParameteriv(GL_DRAW_FRAMEBUFFER,pname,params);
            POP_FRAMEBUFFER();
          }

          void m_glNamedFramebufferDrawBuffer_dsa(GLuint id,GLenum buffer){
            PUSH_FRAMEBUFFER();
            this->glBindFramebuffer(GL_DRAW_FRAMEBUFFER,id);
            this->glDrawBuffer(buffer);
            POP_FRAMEBUFFER();
          }

          void m_glNamedFramebufferDrawBuffers_dsa(GLuint id,GLsizei n,const GLenum*bufs){
            PUSH_FRAMEBUFFER();
            this->glBindFramebuffer(GL_DRAW_FRAMEBUFFER,id);
            this->glDrawBuffers(n,bufs);
            POP_FRAMEBUFFER();
          }

          void m_glNamedFramebufferTextureLayer_dsa(GLuint id,GLenum attachment,GLuint texture,GLint level,GLint layer){
            PUSH_FRAMEBUFFER();
            this->glBindFramebuffer(GL_DRAW_FRAMEBUFFER,id);
            this->glFramebufferTextureLayer(GL_DRAW_FRAMEBUFFER,attachment,texture,level,layer);
            POP_FRAMEBUFFER();
          }

          void m_glClearNamedFramebufferiv_dsa(GLuint id,GLenum buffer,GLint drawBuffer,const GLint*value){
            PUSH_FRAMEBUFFER();
            this->glBindFramebuffer(GL_DRAW_FRAMEBUFFER,id);
            this->glClearBufferiv(buffer,drawBuffer,value);
            POP_FRAMEBUFFER();
          }

          void m_glClearNamedFramebufferfv_dsa(GLuint id,GLenum buffer,GLint drawBuffer,const GLfloat*value){
            PUSH_FRAMEBUFFER();
            this->glBindFramebuffer(GL_DRAW_FRAMEBUFFER,id);
            this->glClearBufferfv(buffer,drawBuffer,value);
            POP_FRAMEBUFFER();
          }

          void m_glClearNamedFramebufferuiv_dsa(GLuint id,GLenum buffer,GLint drawBuffer,const GLuint*value){
            PUSH_FRAMEBUFFER();
            this->glBindFramebuffer(GL_DRAW_FRAMEBUFFER,id);
            this->glClearBufferuiv(buffer,drawBuffer,value);
            POP_FRAMEBUFFER();
          }

          void m_glClearNamedFramebufferfi_dsa(GLuint id,GLenum buffer,GLfloat depth,GLint stencil){
            PUSH_FRAMEBUFFER();
            this->glBindFramebuffer(GL_DRAW_FRAMEBUFFER,id);
            this->glClearBufferfi(GL_DRAW_FRAMEBUFFER,buffer,depth,stencil);
            POP_FRAMEBUFFER();
          }

          void m_glInvalidateNamedFramebufferData_dsa(GLuint id,GLsizei numAttachments,const GLenum*attachments){
            PUSH_FRAMEBUFFER();
            this->glBindFramebuffer(GL_DRAW_FRAMEBUFFER,id);
            this->glInvalidateFramebuffer(GL_DRAW_FRAMEBUFFER,numAttachments,attachments);
            POP_FRAMEBUFFER();
          }

          void m_glInvalidateNamedFramebufferSubData_dsa(GLuint id,GLsizei numAttachments,const GLenum*attachments,GLint x,GLint y,GLsizei width,GLsizei height){
            PUSH_FRAMEBUFFER();
            this->glBindFramebuffer(GL_DRAW_FRAMEBUFFER,id);
            this->glInvalidateSubFramebuffer(GL_DRAW_FRAMEBUFFER,numAttachments,attachments,x,y,width,height);
            POP_FRAMEBUFFER();
          }

          void m_glGetNamedRenderbufferParameteriv_dsa(GLuint id,GLenum pname,GLint*params){
            PUSH_RENDERBUFFER();
            this->glBindRenderbuffer(GL_RENDERBUFFER,id);
            this->glGetRenderbufferParameteriv(GL_RENDERBUFFER,pname,params);
            POP_RENDERBUFFER();
          }

          void m_glNamedRenderbufferStorageMultisample_dsa(GLuint id,GLsizei samples,GLenum internalFormat,GLsizei width,GLsizei height){
            PUSH_RENDERBUFFER();
            this->glBindRenderbuffer(GL_RENDERBUFFER,id);
            this->glRenderbufferStorageMultisample(GL_RENDERBUFFER,samples,internalFormat,width,height);
            POP_RENDERBUFFER();
          }

          void m_glNamedRenderbufferStorage_dsa(GLuint id,GLenum internalFormat,GLsizei width,GLsizei height){
            PUSH_RENDERBUFFER();
            this->glBindRenderbuffer(GL_RENDERBUFFER,id);
            this->glRenderbufferStorage(GL_RENDERBUFFER,internalFormat,width,height);
            POP_RENDERBUFFER();
          }

          void m_glCreateRenderbuffers_dsa(GLsizei n,GLuint*ids){
            PUSH_RENDERBUFFER();
            this->glGenRenderbuffers(n,ids);
            for(GLsizei i=0;i<n;++i)
              this->glBindRenderbuffer(GL_RENDERBUFFER,ids[i]);
            POP_RENDERBUFFER();
          }

          void m_glCreateProgramPipelines_dsa(GLsizei n,GLuint*ids){
            PUSH_PIPELINE();
            this->glGenProgramPipelines(n,ids);
            for(GLsizei i=0;i<n;++i)
              this->glBindProgramPipeline(ids[i]);
            POP_PIPELINE();
          }


          std::map<GLuint,GLenum>m_texture2Target;

          void m_glCreateTextures_dsa(GLenum target,GLsizei n,GLuint*ids){
            PUSH_TEXTURE(target);
            this->glGenTextures(n,ids);
            for(GLsizei i=0;i<n;++i){
              this->glBindTexture(target,ids[i]);
              this->m_texture2Target[ids[i]]=target;
            }
            POP_TEXTURE(target);
          }

          void m_glDeleteTextures_dsa(GLsizei n,const GLuint*ids){
            this->m_glDeleteTextures(n,ids);
            for(GLsizei i=0;i<n;++i)
              this->m_texture2Target.erase(ids[i]);
          }

          void m_glTextureImage1DEXT_dsa(GLuint id,GLenum target,GLint level,GLint internalFormat,GLsizei width,GLint border,GLenum format,GLenum type,const GLvoid*pixels){
            PUSH_TEXTURE(target);
            this->glBindTexture(target,id);
            this->glTexImage1D(target,level,internalFormat,width,border,format,type,pixels);
            POP_TEXTURE(target);
          }

          void m_glTextureImage2DEXT_dsa(GLuint id,GLenum target,GLint level,GLint internalFormat,GLsizei width,GLsizei height,GLint border,GLenum format,GLenum type,const GLvoid*pixels){
            PUSH_TEXTURE(target);
            this->glBindTexture(target,id);
            this->glTexImage2D(target,level,internalFormat,width,height,border,format,type,pixels);
            POP_TEXTURE(target);
          }

          void m_glTextureImage3DEXT_dsa(GLuint id,GLenum target,GLint level,GLint internalFormat,GLsizei width,GLsizei height,GLsizei depth,GLint border,GLenum format,GLenum type,const GLvoid*pixels){
            PUSH_TEXTURE(target);
            this->glBindTexture(target,id);
            this->glTexImage3D(target,level,internalFormat,width,height,depth,border,format,type,pixels);
            POP_TEXTURE(target);
          }

          void m_glTextureSubImage2DEXT_dsa(GLuint id,GLenum target,GLint level,GLint xoffset,GLint yoffset,GLsizei width,GLsizei height,GLenum format,GLenum type,const GLvoid*pixels){
            PUSH_TEXTURE(target);
            this->glBindTexture(target,id);
            this->glTexSubImage2D(target,level,xoffset,yoffset,width,height,format,type,pixels);
            POP_TEXTURE(target);
          }

          void m_glTextureSubImage3DEXT_dsa(GLuint id,GLenum target,GLint level,GLint xoffset,GLint yoffset,GLint zoffset,GLsizei width,GLsizei height,GLsizei depth,GLenum format,GLenum type,const GLvoid*pixels){
            PUSH_TEXTURE(target);
            this->glBindTexture(target,id);
            this->glTexSubImage3D(target,level,xoffset,yoffset,zoffset,width,height,depth,format,type,pixels);
            POP_TEXTURE(target);
          }

          void m_glCompressedTextureImage1DEXT_dsa(GLuint texture,GLenum target,GLint level,GLenum internalFormat,GLsizei width,GLint border, GLsizei imageSize,const GLvoid *data){
            PUSH_TEXTURE(target);
            this->glBindTexture(target,texture);
            this->glCompressedTexImage1D(target,level,internalFormat,width,border,imageSize,data);
            POP_TEXTURE(target);
          }

          void m_glCompressedTextureImage2DEXT_dsa(GLuint texture,GLenum target,GLint level,GLenum internalFormat,GLsizei width,GLsizei height,GLint border, GLsizei imageSize,const GLvoid *data){
            PUSH_TEXTURE(target);
            this->glBindTexture(target,texture);
            this->glCompressedTexImage2D(target,level,internalFormat,width,height,border,imageSize,data);
            POP_TEXTURE(target);
          }

          void m_glCompressedTextureImage3DEXT_dsa(GLuint texture,GLenum target,GLint level,GLenum internalFormat,GLsizei width,GLsizei height,GLsizei depth,GLint border, GLsizei imageSize,const GLvoid *data){
            PUSH_TEXTURE(target);
            this->glBindTexture(target,texture);
            this->glCompressedTexImage3D(target,level,internalFormat,width,height,depth,border,imageSize,data);
            POP_TEXTURE(target);
          }

          void m_glTextureSubImage1D_dsa(GLuint texture,GLint level,GLint xoffset,GLsizei width,GLenum format,GLenum type,const GLvoid*data){
            GLenum target=this->m_texture2Target[texture];
            PUSH_TEXTURE(target);
            this->glBindTexture(target,texture);
            this->glTexSubImage1D(target,level,xoffset,width,format,type,data);
            POP_TEXTURE(target);
          }

          void m_glTextureSubImage2D_dsa(GLuint texture,GLint level,GLint xoffset,GLint yoffset,GLsizei width,GLsizei height,GLenum format,GLenum type,const GLvoid*data){
            GLenum target=this->m_texture2Target[texture];
            PUSH_TEXTURE(target);
            this->glBindTexture(target,texture);
            this->glTexSubImage2D(target,level,xoffset,yoffset,width,height,format,type,data);
            POP_TEXTURE(target);
          }

          void m_glTextureSubImage3D_dsa(GLuint texture,GLint level,GLint xoffset,GLint yoffset,GLint zoffset,GLsizei width,GLsizei height,GLsizei depth,GLenum format,GLenum type,const GLvoid*data){
            GLenum target=this->m_texture2Target[texture];
            PUSH_TEXTURE(target);
            this->glBindTexture(target,texture);
            this->glTexSubImage3D(target,level,xoffset,yoffset,zoffset,width,height,depth,format,type,data);
            POP_TEXTURE(target);
          }

          void m_glBindTextureUnit_dsa(GLuint unit,GLuint texture){
            GLenum target=this->m_texture2Target[texture];
            PUSH_ACTIVE_TEXTURE();
            PUSH_TEXTURE(target);
            this->glActiveTexture(GL_TEXTURE0+unit);
            this->glBindTexture(target,texture);
            POP_TEXTURE(target);
            POP_ACTIVE_TEXTURE();
          }

          void m_glTextureStorage1D_dsa(GLuint texture,GLsizei levels,GLenum internalFormat,GLsizei width){
            GLenum target=this->m_texture2Target[texture];
            PUSH_TEXTURE(target);
            this->glBindTexture(target,texture);
            this->glTexStorage1D(target,levels,internalFormat,width);
            POP_TEXTURE(target);
          }

          void m_glTextureStorage2D_dsa(GLuint texture,GLsizei levels,GLenum internalFormat,GLsizei width,GLsizei height){
            GLenum target=this->m_texture2Target[texture];
            PUSH_TEXTURE(target);
            this->glBindTexture(target,texture);
            this->glTexStorage2D(target,levels,internalFormat,width,height);
            POP_TEXTURE(target);
          }

          void m_glTextureStorage3D_dsa(GLuint texture,GLsizei levels,GLenum internalFormat,GLsizei width,GLsizei height,GLsizei depth){
            GLenum target=this->m_texture2Target[texture];
            PUSH_TEXTURE(target);
            this->glBindTexture(target,texture);
            this->glTexStorage3D(target,levels,internalFormat,width,height,depth);
            POP_TEXTURE(target);
          }

          void m_glTextureParameteri_dsa(GLuint texture,GLenum pname,GLint params){
            GLenum target=this->m_texture2Target[texture];
            PUSH_TEXTURE(target);
            this->glBindTexture(target,texture);
            this->glTexParameteri(target,pname,params);
            POP_TEXTURE(target);
          }

          void m_glTextureParameterf_dsa(GLuint texture,GLenum pname,GLfloat params){
            GLenum target=this->m_texture2Target[texture];
            PUSH_TEXTURE(target);
            this->glBindTexture(target,texture);
            this->glTexParameterf(target,pname,params);
            POP_TEXTURE(target);
          }

          void m_glTextureParameteriv_dsa(GLuint texture,GLenum pname,const GLint*params){
            GLenum target=this->m_texture2Target[texture];
            PUSH_TEXTURE(target);
            this->glBindTexture(target,texture);
            this->glTexParameteriv(target,pname,params);
            POP_TEXTURE(target);
          }

          void m_glTextureParameterfv_dsa(GLuint texture,GLenum pname,const GLfloat*params){
            GLenum target=this->m_texture2Target[texture];
            PUSH_TEXTURE(target);
            this->glBindTexture(target,texture);
            this->glTexParameterfv(target,pname,params);
            POP_TEXTURE(target);
          }

          void m_glGetTextureLevelParameteriv_dsa(GLuint texture,GLint level,GLenum pname,GLint*params){
            GLenum target=this->m_texture2Target[texture];
            PUSH_TEXTURE(target);
            this->glBindTexture(target,texture);
            this->glGetTexLevelParameteriv(target,level,pname,params);
            POP_TEXTURE(target);
          }

          void m_glGetTextureLevelParameterfv_dsa(GLuint texture,GLint level,GLenum pname,GLfloat*params){
            GLenum target=this->m_texture2Target[texture];
            PUSH_TEXTURE(target);
            this->glBindTexture(target,texture);
            this->glGetTexLevelParameterfv(target,level,pname,params);
            POP_TEXTURE(target);
          }

          void m_glGetTextureParameteriv_dsa(GLuint texture,GLenum pname,GLint*params){
            GLenum target=this->m_texture2Target[texture];
            PUSH_TEXTURE(target);
            this->glBindTexture(target,texture);
            this->glGetTexParameteriv(target,pname,params);
            POP_TEXTURE(target);
          }

          void m_glGetTextureParameterfv_dsa(GLuint texture,GLenum pname,GLfloat*params){
            GLenum target=this->m_texture2Target[texture];
            PUSH_TEXTURE(target);
            this->glBindTexture(target,texture);
            this->glGetTexParameterfv(target,pname,params);
            POP_TEXTURE(target);
          }

          void m_glGetTextureParameterIiv_dsa(GLuint texture,GLenum pname,GLint*params){
            GLenum target=this->m_texture2Target[texture];
            PUSH_TEXTURE(target);
            this->glBindTexture(target,texture);
            this->glGetTexParameterIiv(target,pname,params);
            POP_TEXTURE(target);
          }

          void m_glGetTextureParameterIuiv_dsa(GLuint texture,GLenum pname,GLuint*params){
            GLenum target=this->m_texture2Target[texture];
            PUSH_TEXTURE(target);
            this->glBindTexture(target,texture);
            this->glGetTexParameterIuiv(target,pname,params);
            POP_TEXTURE(target);
          }

      };

  }
}

