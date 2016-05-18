inline void glTextureParameterfv(GLuint texture,GLenum pname,const GLfloat* param)const{(this->*(this->m_ptr_glTextureParameterfv))(texture,pname,param);}
inline void glVertexArrayElementBuffer(GLuint vaobj,GLuint buffer)const{(this->*(this->m_ptr_glVertexArrayElementBuffer))(vaobj,buffer);}
inline void glStencilMaskSeparate(GLenum face,GLuint mask)const{(this->*(this->m_ptr_glStencilMaskSeparate))(face,mask);}
inline void glGetFramebufferAttachmentParameterivEXT(GLenum target,GLenum attachment,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetFramebufferAttachmentParameterivEXT))(target,attachment,pname,params);}
inline void glTextureStorage3DMultisample(GLuint texture,GLsizei samples,GLenum internalformat,GLsizei width,GLsizei height,GLsizei depth,GLboolean fixedsamplelocations)const{(this->*(this->m_ptr_glTextureStorage3DMultisample))(texture,samples,internalformat,width,height,depth,fixedsamplelocations);}
inline void glGetIntegerIndexedvEXT(GLenum target,GLuint index,GLint* data)const{(this->*(this->m_ptr_glGetIntegerIndexedvEXT))(target,index,data);}
inline void glCopyTexImage1D(GLenum target,GLint level,GLenum internalformat,GLint x,GLint y,GLsizei width,GLint border)const{(this->*(this->m_ptr_glCopyTexImage1D))(target,level,internalformat,x,y,width,border);}
inline void glIndexi(GLint c)const{(this->*(this->m_ptr_glIndexi))(c);}
inline void glCompressedTexSubImage3D(GLenum target,GLint level,GLint xoffset,GLint yoffset,GLint zoffset,GLsizei width,GLsizei height,GLsizei depth,GLenum format,GLsizei imageSize,const GLvoid* data)const{(this->*(this->m_ptr_glCompressedTexSubImage3D))(target,level,xoffset,yoffset,zoffset,width,height,depth,format,imageSize,data);}
inline void glEvalCoord2d(GLdouble u,GLdouble v)const{(this->*(this->m_ptr_glEvalCoord2d))(u,v);}
inline void glTexCoordP3uiv(GLenum type,const GLuint* coords)const{(this->*(this->m_ptr_glTexCoordP3uiv))(type,coords);}
inline void glIndexd(GLdouble c)const{(this->*(this->m_ptr_glIndexd))(c);}
inline void glIndexf(GLfloat c)const{(this->*(this->m_ptr_glIndexf))(c);}
inline void glTextureStorage3DEXT(GLuint texture,GLenum target,GLsizei levels,GLenum internalformat,GLsizei width,GLsizei height,GLsizei depth)const{(this->*(this->m_ptr_glTextureStorage3DEXT))(texture,target,levels,internalformat,width,height,depth);}
inline void glUniform4uiEXT(GLint location,GLuint v0,GLuint v1,GLuint v2,GLuint v3)const{(this->*(this->m_ptr_glUniform4uiEXT))(location,v0,v1,v2,v3);}
inline void glIndexs(GLshort c)const{(this->*(this->m_ptr_glIndexs))(c);}
inline void glVertexArrayBindVertexBufferEXT(GLuint vaobj,GLuint bindingindex,GLuint buffer,GLintptr offset,GLsizei stride)const{(this->*(this->m_ptr_glVertexArrayBindVertexBufferEXT))(vaobj,bindingindex,buffer,offset,stride);}
inline void glConvolutionParameteriEXT(GLenum target,GLenum pname,GLint params)const{(this->*(this->m_ptr_glConvolutionParameteriEXT))(target,pname,params);}
inline void glVertexAttribI3uivEXT(GLuint index,const GLuint* v)const{(this->*(this->m_ptr_glVertexAttribI3uivEXT))(index,v);}
inline void glVertex3sv(const GLshort* v)const{(this->*(this->m_ptr_glVertex3sv))(v);}
inline void glCopyTexImage2DEXT(GLenum target,GLint level,GLenum internalformat,GLint x,GLint y,GLsizei width,GLsizei height,GLint border)const{(this->*(this->m_ptr_glCopyTexImage2DEXT))(target,level,internalformat,x,y,width,height,border);}
inline void glGetnMapfv(GLenum target,GLenum query,GLsizei bufSize,GLfloat* v)const{(this->*(this->m_ptr_glGetnMapfv))(target,query,bufSize,v);}
inline void glTransformFeedbackBufferRange(GLuint xfb,GLuint index,GLuint buffer,GLintptr offset,GLsizeiptr size)const{(this->*(this->m_ptr_glTransformFeedbackBufferRange))(xfb,index,buffer,offset,size);}
inline void glSecondaryColor3fv(const GLfloat* v)const{(this->*(this->m_ptr_glSecondaryColor3fv))(v);}
inline void glFogfv(GLenum pname,const GLfloat* params)const{(this->*(this->m_ptr_glFogfv))(pname,params);}
inline void glVertexP4ui(GLenum type,GLuint value)const{(this->*(this->m_ptr_glVertexP4ui))(type,value);}
inline void glDrawElementsInstancedBaseInstance(GLenum mode,GLsizei count,GLenum type,const void* indices,GLsizei instancecount,GLuint baseinstance)const{(this->*(this->m_ptr_glDrawElementsInstancedBaseInstance))(mode,count,type,indices,instancecount,baseinstance);}
inline void glVertexAttribL4dEXT(GLuint index,GLdouble x,GLdouble y,GLdouble z,GLdouble w)const{(this->*(this->m_ptr_glVertexAttribL4dEXT))(index,x,y,z,w);}
inline void glVertex4iv(const GLint* v)const{(this->*(this->m_ptr_glVertex4iv))(v);}
inline void glVertexAttribP4ui(GLuint index,GLenum type,GLboolean normalized,GLuint value)const{(this->*(this->m_ptr_glVertexAttribP4ui))(index,type,normalized,value);}
inline GLboolean glIsBuffer(GLuint buffer)const{return (this->*(this->m_ptr_glIsBuffer))(buffer);}
inline void glGetMultisamplefv(GLenum pname,GLuint index,GLfloat* val)const{(this->*(this->m_ptr_glGetMultisamplefv))(pname,index,val);}
inline void glCompressedMultiTexSubImage3DEXT(GLenum texunit,GLenum target,GLint level,GLint xoffset,GLint yoffset,GLint zoffset,GLsizei width,GLsizei height,GLsizei depth,GLenum format,GLsizei imageSize,const void* bits)const{(this->*(this->m_ptr_glCompressedMultiTexSubImage3DEXT))(texunit,target,level,xoffset,yoffset,zoffset,width,height,depth,format,imageSize,bits);}
inline void glMinSampleShading(GLfloat value)const{(this->*(this->m_ptr_glMinSampleShading))(value);}
inline void glProgramUniform4fEXT(GLuint program,GLint location,GLfloat v0,GLfloat v1,GLfloat v2,GLfloat v3)const{(this->*(this->m_ptr_glProgramUniform4fEXT))(program,location,v0,v1,v2,v3);}
inline void glDebugMessageControl(GLenum source,GLenum type,GLenum severity,GLsizei count,const GLuint* ids,GLboolean enabled)const{(this->*(this->m_ptr_glDebugMessageControl))(source,type,severity,count,ids,enabled);}
inline void glPopAttrib()const{(this->*(this->m_ptr_glPopAttrib))();}
inline void glProgramUniform4iEXT(GLuint program,GLint location,GLint v0,GLint v1,GLint v2,GLint v3)const{(this->*(this->m_ptr_glProgramUniform4iEXT))(program,location,v0,v1,v2,v3);}
inline void glColorMaterial(GLenum face,GLenum mode)const{(this->*(this->m_ptr_glColorMaterial))(face,mode);}
inline void glColor3b(GLbyte red,GLbyte green,GLbyte blue)const{(this->*(this->m_ptr_glColor3b))(red,green,blue);}
inline void glColor3f(GLfloat red,GLfloat green,GLfloat blue)const{(this->*(this->m_ptr_glColor3f))(red,green,blue);}
inline void glColor3d(GLdouble red,GLdouble green,GLdouble blue)const{(this->*(this->m_ptr_glColor3d))(red,green,blue);}
inline void glGetnMapiv(GLenum target,GLenum query,GLsizei bufSize,GLint* v)const{(this->*(this->m_ptr_glGetnMapiv))(target,query,bufSize,v);}
inline void glColor3i(GLint red,GLint green,GLint blue)const{(this->*(this->m_ptr_glColor3i))(red,green,blue);}
inline void glVertexAttrib4ubv(GLuint index,const GLubyte* v)const{(this->*(this->m_ptr_glVertexAttrib4ubv))(index,v);}
inline void glGetBufferParameteriv(GLenum target,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetBufferParameteriv))(target,pname,params);}
inline void glMatrixPushEXT(GLenum mode)const{(this->*(this->m_ptr_glMatrixPushEXT))(mode);}
inline void glProgramUniform2fEXT(GLuint program,GLint location,GLfloat v0,GLfloat v1)const{(this->*(this->m_ptr_glProgramUniform2fEXT))(program,location,v0,v1);}
inline void glBlitFramebuffer(GLint srcX0,GLint srcY0,GLint srcX1,GLint srcY1,GLint dstX0,GLint dstY0,GLint dstX1,GLint dstY1,GLbitfield mask,GLenum filter)const{(this->*(this->m_ptr_glBlitFramebuffer))(srcX0,srcY0,srcX1,srcY1,dstX0,dstY0,dstX1,dstY1,mask,filter);}
inline void glMultiTexCoordP2ui(GLenum texture,GLenum type,GLuint coords)const{(this->*(this->m_ptr_glMultiTexCoordP2ui))(texture,type,coords);}
inline void glVertexAttribL4d(GLuint index,GLdouble x,GLdouble y,GLdouble z,GLdouble w)const{(this->*(this->m_ptr_glVertexAttribL4d))(index,x,y,z,w);}
inline void glVertex2iv(const GLint* v)const{(this->*(this->m_ptr_glVertex2iv))(v);}
inline void glUniformMatrix3dv(GLint location,GLsizei count,GLboolean transpose,const GLdouble* value)const{(this->*(this->m_ptr_glUniformMatrix3dv))(location,count,transpose,value);}
inline void glGetVertexAttribLdvEXT(GLuint index,GLenum pname,GLdouble* params)const{(this->*(this->m_ptr_glGetVertexAttribLdvEXT))(index,pname,params);}
inline void glEvalCoord2f(GLfloat u,GLfloat v)const{(this->*(this->m_ptr_glEvalCoord2f))(u,v);}
inline void glInvalidateBufferSubData(GLuint buffer,GLintptr offset,GLsizeiptr length)const{(this->*(this->m_ptr_glInvalidateBufferSubData))(buffer,offset,length);}
inline void glResumeTransformFeedback()const{(this->*(this->m_ptr_glResumeTransformFeedback))();}
inline void glInsertEventMarkerEXT(GLsizei length,const GLchar* marker)const{(this->*(this->m_ptr_glInsertEventMarkerEXT))(length,marker);}
inline void glFogi(GLenum pname,GLint param)const{(this->*(this->m_ptr_glFogi))(pname,param);}
inline void glVertexPointer(GLint size,GLenum type,GLsizei stride,const GLvoid* ptr)const{(this->*(this->m_ptr_glVertexPointer))(size,type,stride,ptr);}
inline void glBeginVertexShaderEXT()const{(this->*(this->m_ptr_glBeginVertexShaderEXT))();}
inline void glFogf(GLenum pname,GLfloat param)const{(this->*(this->m_ptr_glFogf))(pname,param);}
inline void glMultiTexCoord1d(GLenum target,GLdouble s)const{(this->*(this->m_ptr_glMultiTexCoord1d))(target,s);}
inline void glMultiTexCoord1f(GLenum target,GLfloat s)const{(this->*(this->m_ptr_glMultiTexCoord1f))(target,s);}
inline void glGetMultiTexParameterivEXT(GLenum texunit,GLenum target,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetMultiTexParameterivEXT))(texunit,target,pname,params);}
inline void glProgramUniformMatrix3x4fvEXT(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLfloat* value)const{(this->*(this->m_ptr_glProgramUniformMatrix3x4fvEXT))(program,location,count,transpose,value);}
inline void glVertexAttribI2i(GLuint index,GLint x,GLint y)const{(this->*(this->m_ptr_glVertexAttribI2i))(index,x,y);}
inline void glMultiTexCoord1i(GLenum target,GLint s)const{(this->*(this->m_ptr_glMultiTexCoord1i))(target,s);}
inline void glWriteMaskEXT(GLuint res,GLuint in,GLenum outX,GLenum outY,GLenum outZ,GLenum outW)const{(this->*(this->m_ptr_glWriteMaskEXT))(res,in,outX,outY,outZ,outW);}
inline GLenum glGetGraphicsResetStatus()const{return (this->*(this->m_ptr_glGetGraphicsResetStatus))();}
inline void glVertexAttrib1fv(GLuint index,const GLfloat* v)const{(this->*(this->m_ptr_glVertexAttrib1fv))(index,v);}
inline GLboolean glIsEnabled(GLenum cap)const{return (this->*(this->m_ptr_glIsEnabled))(cap);}
inline void glStencilOp(GLenum fail,GLenum zfail,GLenum zpass)const{(this->*(this->m_ptr_glStencilOp))(fail,zfail,zpass);}
inline void glFramebufferTexture2D(GLenum target,GLenum attachment,GLenum textarget,GLuint texture,GLint level)const{(this->*(this->m_ptr_glFramebufferTexture2D))(target,attachment,textarget,texture,level);}
inline void glTexCoord3sv(const GLshort* v)const{(this->*(this->m_ptr_glTexCoord3sv))(v);}
inline void glIndexPointerEXT(GLenum type,GLsizei stride,GLsizei count,const void* pointer)const{(this->*(this->m_ptr_glIndexPointerEXT))(type,stride,count,pointer);}
inline void glVertexArrayAttribIFormat(GLuint vaobj,GLuint attribindex,GLint size,GLenum type,GLuint relativeoffset)const{(this->*(this->m_ptr_glVertexArrayAttribIFormat))(vaobj,attribindex,size,type,relativeoffset);}
inline void glGenFramebuffers(GLsizei n,GLuint* framebuffers)const{(this->*(this->m_ptr_glGenFramebuffers))(n,framebuffers);}
inline void glPixelMapx(GLenum map,GLint size,const GLfixed* values)const{(this->*(this->m_ptr_glPixelMapx))(map,size,values);}
inline void glTexSubImage3DEXT(GLenum target,GLint level,GLint xoffset,GLint yoffset,GLint zoffset,GLsizei width,GLsizei height,GLsizei depth,GLenum format,GLenum type,const void* pixels)const{(this->*(this->m_ptr_glTexSubImage3DEXT))(target,level,xoffset,yoffset,zoffset,width,height,depth,format,type,pixels);}
inline void glGetAttachedShaders(GLuint program,GLsizei maxCount,GLsizei* count,GLuint* shaders)const{(this->*(this->m_ptr_glGetAttachedShaders))(program,maxCount,count,shaders);}
inline void glProgramUniform3uiv(GLuint program,GLint location,GLsizei count,const GLuint* value)const{(this->*(this->m_ptr_glProgramUniform3uiv))(program,location,count,value);}
inline void glViewportArrayv(GLuint first,GLsizei count,const GLfloat* v)const{(this->*(this->m_ptr_glViewportArrayv))(first,count,v);}
inline void glMultiTexCoord2s(GLenum target,GLshort s,GLshort t)const{(this->*(this->m_ptr_glMultiTexCoord2s))(target,s,t);}
inline void glVertex3dv(const GLdouble* v)const{(this->*(this->m_ptr_glVertex3dv))(v);}
inline void glColor4fv(const GLfloat* v)const{(this->*(this->m_ptr_glColor4fv))(v);}
inline void glGetNamedBufferSubDataEXT(GLuint buffer,GLintptr offset,GLsizeiptr size,void* data)const{(this->*(this->m_ptr_glGetNamedBufferSubDataEXT))(buffer,offset,size,data);}
inline void glConvolutionFilter2D(GLenum target,GLenum internalformat,GLsizei width,GLsizei height,GLenum format,GLenum type,const GLvoid* image)const{(this->*(this->m_ptr_glConvolutionFilter2D))(target,internalformat,width,height,format,type,image);}
inline void glMemoryBarrierByRegion(GLbitfield barriers)const{(this->*(this->m_ptr_glMemoryBarrierByRegion))(barriers);}
inline void glMatrixRotatedEXT(GLenum mode,GLdouble angle,GLdouble x,GLdouble y,GLdouble z)const{(this->*(this->m_ptr_glMatrixRotatedEXT))(mode,angle,x,y,z);}
inline void glTexCoord2sv(const GLshort* v)const{(this->*(this->m_ptr_glTexCoord2sv))(v);}
inline void glUniform2dv(GLint location,GLsizei count,const GLdouble* value)const{(this->*(this->m_ptr_glUniform2dv))(location,count,value);}
inline void glGetPixelMapuiv(GLenum map,GLuint* values)const{(this->*(this->m_ptr_glGetPixelMapuiv))(map,values);}
inline void glDepthBoundsEXT(GLclampd zmin,GLclampd zmax)const{(this->*(this->m_ptr_glDepthBoundsEXT))(zmin,zmax);}
inline void glMultiTexParameteriEXT(GLenum texunit,GLenum target,GLenum pname,GLint param)const{(this->*(this->m_ptr_glMultiTexParameteriEXT))(texunit,target,pname,param);}
inline void glGetPointerv(GLenum pname,GLvoid** params)const{(this->*(this->m_ptr_glGetPointerv))(pname,params);}
inline void glVertexBindingDivisor(GLuint bindingindex,GLuint divisor)const{(this->*(this->m_ptr_glVertexBindingDivisor))(bindingindex,divisor);}
inline void glGetUniformfv(GLuint program,GLint location,GLfloat* params)const{(this->*(this->m_ptr_glGetUniformfv))(program,location,params);}
inline void glGetUniformuiv(GLuint program,GLint location,GLuint* params)const{(this->*(this->m_ptr_glGetUniformuiv))(program,location,params);}
inline void glFrustum(GLdouble left,GLdouble right,GLdouble bottom,GLdouble top,GLdouble near_val,GLdouble far_val)const{(this->*(this->m_ptr_glFrustum))(left,right,bottom,top,near_val,far_val);}
inline void glMultiTexCoord2f(GLenum target,GLfloat s,GLfloat t)const{(this->*(this->m_ptr_glMultiTexCoord2f))(target,s,t);}
inline void glVertexArrayBindingDivisor(GLuint vaobj,GLuint bindingindex,GLuint divisor)const{(this->*(this->m_ptr_glVertexArrayBindingDivisor))(vaobj,bindingindex,divisor);}
inline void glProgramUniform1dvEXT(GLuint program,GLint location,GLsizei count,const GLdouble* value)const{(this->*(this->m_ptr_glProgramUniform1dvEXT))(program,location,count,value);}
inline void glDrawElementsInstanced(GLenum mode,GLsizei count,GLenum type,const void* indices,GLsizei instancecount)const{(this->*(this->m_ptr_glDrawElementsInstanced))(mode,count,type,indices,instancecount);}
inline void glVariantfvEXT(GLuint id,const GLfloat* addr)const{(this->*(this->m_ptr_glVariantfvEXT))(id,addr);}
inline void glMatrixLoadfEXT(GLenum mode,const GLfloat* m)const{(this->*(this->m_ptr_glMatrixLoadfEXT))(mode,m);}
inline void glGetRenderbufferParameteriv(GLenum target,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetRenderbufferParameteriv))(target,pname,params);}
inline void glNamedRenderbufferStorage(GLuint renderbuffer,GLenum internalformat,GLsizei width,GLsizei height)const{(this->*(this->m_ptr_glNamedRenderbufferStorage))(renderbuffer,internalformat,width,height);}
inline GLsync glFenceSync(GLenum condition,GLbitfield flags)const{return (this->*(this->m_ptr_glFenceSync))(condition,flags);}
inline void glGetVertexAttribIivEXT(GLuint index,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetVertexAttribIivEXT))(index,pname,params);}
inline void glFramebufferDrawBuffersEXT(GLuint framebuffer,GLsizei n,const GLenum* bufs)const{(this->*(this->m_ptr_glFramebufferDrawBuffersEXT))(framebuffer,n,bufs);}
inline void glVertexAttrib3sv(GLuint index,const GLshort* v)const{(this->*(this->m_ptr_glVertexAttrib3sv))(index,v);}
inline void glGetQueryObjecti64vEXT(GLuint id,GLenum pname,GLint64* params)const{(this->*(this->m_ptr_glGetQueryObjecti64vEXT))(id,pname,params);}
inline void glProgramUniform4uiEXT(GLuint program,GLint location,GLuint v0,GLuint v1,GLuint v2,GLuint v3)const{(this->*(this->m_ptr_glProgramUniform4uiEXT))(program,location,v0,v1,v2,v3);}
inline void glValidateProgramPipeline(GLuint pipeline)const{(this->*(this->m_ptr_glValidateProgramPipeline))(pipeline);}
inline void glGenSamplers(GLsizei count,GLuint* samplers)const{(this->*(this->m_ptr_glGenSamplers))(count,samplers);}
inline void glDrawTransformFeedbackInstanced(GLenum mode,GLuint id,GLsizei instancecount)const{(this->*(this->m_ptr_glDrawTransformFeedbackInstanced))(mode,id,instancecount);}
inline void glTexCoord4iv(const GLint* v)const{(this->*(this->m_ptr_glTexCoord4iv))(v);}
inline void glDrawTransformFeedback(GLenum mode,GLuint id)const{(this->*(this->m_ptr_glDrawTransformFeedback))(mode,id);}
inline void glGetTexParameterIuiv(GLenum target,GLenum pname,GLuint* params)const{(this->*(this->m_ptr_glGetTexParameterIuiv))(target,pname,params);}
inline void glIndexPointer(GLenum type,GLsizei stride,const GLvoid* ptr)const{(this->*(this->m_ptr_glIndexPointer))(type,stride,ptr);}
inline void glVertexAttrib4Nbv(GLuint index,const GLbyte* v)const{(this->*(this->m_ptr_glVertexAttrib4Nbv))(index,v);}
inline GLboolean glIsSync(GLsync sync)const{return (this->*(this->m_ptr_glIsSync))(sync);}
inline void glGetTextureParameterivEXT(GLuint texture,GLenum target,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetTextureParameterivEXT))(texture,target,pname,params);}
inline void glFramebufferTextureLayerEXT(GLenum target,GLenum attachment,GLuint texture,GLint level,GLint layer)const{(this->*(this->m_ptr_glFramebufferTextureLayerEXT))(target,attachment,texture,level,layer);}
inline void glGetObjectPtrLabel(const void* ptr,GLsizei bufSize,GLsizei* length,GLchar* label)const{(this->*(this->m_ptr_glGetObjectPtrLabel))(ptr,bufSize,length,label);}
inline void glTextureParameteri(GLuint texture,GLenum pname,GLint param)const{(this->*(this->m_ptr_glTextureParameteri))(texture,pname,param);}
inline void glTextureParameterf(GLuint texture,GLenum pname,GLfloat param)const{(this->*(this->m_ptr_glTextureParameterf))(texture,pname,param);}
inline void glUniformMatrix2x3dv(GLint location,GLsizei count,GLboolean transpose,const GLdouble* value)const{(this->*(this->m_ptr_glUniformMatrix2x3dv))(location,count,transpose,value);}
inline void glFramebufferDrawBufferEXT(GLuint framebuffer,GLenum mode)const{(this->*(this->m_ptr_glFramebufferDrawBufferEXT))(framebuffer,mode);}
inline void glCopyColorSubTable(GLenum target,GLsizei start,GLint x,GLint y,GLsizei width)const{(this->*(this->m_ptr_glCopyColorSubTable))(target,start,x,y,width);}
inline void glVertexAttribL3d(GLuint index,GLdouble x,GLdouble y,GLdouble z)const{(this->*(this->m_ptr_glVertexAttribL3d))(index,x,y,z);}
inline void glWindowPos2iv(const GLint* v)const{(this->*(this->m_ptr_glWindowPos2iv))(v);}
inline void glDrawRangeElementsEXT(GLenum mode,GLuint start,GLuint end,GLsizei count,GLenum type,const void* indices)const{(this->*(this->m_ptr_glDrawRangeElementsEXT))(mode,start,end,count,type,indices);}
inline void glFogCoordd(GLdouble coord)const{(this->*(this->m_ptr_glFogCoordd))(coord);}
inline void glFogCoordf(GLfloat coord)const{(this->*(this->m_ptr_glFogCoordf))(coord);}
inline void glCopyTexImage2D(GLenum target,GLint level,GLenum internalformat,GLint x,GLint y,GLsizei width,GLsizei height,GLint border)const{(this->*(this->m_ptr_glCopyTexImage2D))(target,level,internalformat,x,y,width,height,border);}
inline void glProgramUniformMatrix2x4fvEXT(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLfloat* value)const{(this->*(this->m_ptr_glProgramUniformMatrix2x4fvEXT))(program,location,count,transpose,value);}
inline void glRenderbufferStorageEXT(GLenum target,GLenum internalformat,GLsizei width,GLsizei height)const{(this->*(this->m_ptr_glRenderbufferStorageEXT))(target,internalformat,width,height);}
inline void glUniform4uiv(GLint location,GLsizei count,const GLuint* value)const{(this->*(this->m_ptr_glUniform4uiv))(location,count,value);}
inline void glSecondaryColor3fEXT(GLfloat red,GLfloat green,GLfloat blue)const{(this->*(this->m_ptr_glSecondaryColor3fEXT))(red,green,blue);}
inline void glVertexAttribL1dv(GLuint index,const GLdouble* v)const{(this->*(this->m_ptr_glVertexAttribL1dv))(index,v);}
inline void glSetInvariantEXT(GLuint id,GLenum type,const void* addr)const{(this->*(this->m_ptr_glSetInvariantEXT))(id,type,addr);}
inline void glScissorArrayv(GLuint first,GLsizei count,const GLint* v)const{(this->*(this->m_ptr_glScissorArrayv))(first,count,v);}
inline void glCallList(GLuint list)const{(this->*(this->m_ptr_glCallList))(list);}
inline void glGetMultiTexEnvfvEXT(GLenum texunit,GLenum target,GLenum pname,GLfloat* params)const{(this->*(this->m_ptr_glGetMultiTexEnvfvEXT))(texunit,target,pname,params);}
inline void glProgramUniformMatrix4dvEXT(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLdouble* value)const{(this->*(this->m_ptr_glProgramUniformMatrix4dvEXT))(program,location,count,transpose,value);}
inline void glGetnColorTable(GLenum target,GLenum format,GLenum type,GLsizei bufSize,void* table)const{(this->*(this->m_ptr_glGetnColorTable))(target,format,type,bufSize,table);}
inline void glVertexAttribL2dvEXT(GLuint index,const GLdouble* v)const{(this->*(this->m_ptr_glVertexAttribL2dvEXT))(index,v);}
inline void glInvalidateSubFramebuffer(GLenum target,GLsizei numAttachments,const GLenum* attachments,GLint x,GLint y,GLsizei width,GLsizei height)const{(this->*(this->m_ptr_glInvalidateSubFramebuffer))(target,numAttachments,attachments,x,y,width,height);}
inline void* glMapBuffer(GLenum target,GLenum access)const{return (this->*(this->m_ptr_glMapBuffer))(target,access);}
inline void glSecondaryColor3d(GLdouble red,GLdouble green,GLdouble blue)const{(this->*(this->m_ptr_glSecondaryColor3d))(red,green,blue);}
inline void glSecondaryColor3f(GLfloat red,GLfloat green,GLfloat blue)const{(this->*(this->m_ptr_glSecondaryColor3f))(red,green,blue);}
inline void glVertexAttribLFormat(GLuint attribindex,GLint size,GLenum type,GLuint relativeoffset)const{(this->*(this->m_ptr_glVertexAttribLFormat))(attribindex,size,type,relativeoffset);}
inline void glSecondaryColor3b(GLbyte red,GLbyte green,GLbyte blue)const{(this->*(this->m_ptr_glSecondaryColor3b))(red,green,blue);}
inline void glSecondaryColor3i(GLint red,GLint green,GLint blue)const{(this->*(this->m_ptr_glSecondaryColor3i))(red,green,blue);}
inline void glDeleteSync(GLsync sync)const{(this->*(this->m_ptr_glDeleteSync))(sync);}
inline void glUniformMatrix4x2dv(GLint location,GLsizei count,GLboolean transpose,const GLdouble* value)const{(this->*(this->m_ptr_glUniformMatrix4x2dv))(location,count,transpose,value);}
inline void glVertexArrayVertexAttribLOffsetEXT(GLuint vaobj,GLuint buffer,GLuint index,GLint size,GLenum type,GLsizei stride,GLintptr offset)const{(this->*(this->m_ptr_glVertexArrayVertexAttribLOffsetEXT))(vaobj,buffer,index,size,type,stride,offset);}
inline void glSecondaryColor3s(GLshort red,GLshort green,GLshort blue)const{(this->*(this->m_ptr_glSecondaryColor3s))(red,green,blue);}
inline void glUniform3iv(GLint location,GLsizei count,const GLint* value)const{(this->*(this->m_ptr_glUniform3iv))(location,count,value);}
inline void glPolygonMode(GLenum face,GLenum mode)const{(this->*(this->m_ptr_glPolygonMode))(face,mode);}
inline void glProgramUniform4iv(GLuint program,GLint location,GLsizei count,const GLint* value)const{(this->*(this->m_ptr_glProgramUniform4iv))(program,location,count,value);}
inline void glTextureSubImage2DEXT(GLuint texture,GLenum target,GLint level,GLint xoffset,GLint yoffset,GLsizei width,GLsizei height,GLenum format,GLenum type,const void* pixels)const{(this->*(this->m_ptr_glTextureSubImage2DEXT))(texture,target,level,xoffset,yoffset,width,height,format,type,pixels);}
inline void glUseProgram(GLuint program)const{(this->*(this->m_ptr_glUseProgram))(program);}
inline void glLineStipple(GLint factor,GLushort pattern)const{(this->*(this->m_ptr_glLineStipple))(factor,pattern);}
inline void glGetProgramInfoLog(GLuint program,GLsizei bufSize,GLsizei* length,GLchar* infoLog)const{(this->*(this->m_ptr_glGetProgramInfoLog))(program,bufSize,length,infoLog);}
inline void glProgramUniformMatrix3x2fvEXT(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLfloat* value)const{(this->*(this->m_ptr_glProgramUniformMatrix3x2fvEXT))(program,location,count,transpose,value);}
inline void glCopyTextureSubImage3DEXT(GLuint texture,GLenum target,GLint level,GLint xoffset,GLint yoffset,GLint zoffset,GLint x,GLint y,GLsizei width,GLsizei height)const{(this->*(this->m_ptr_glCopyTextureSubImage3DEXT))(texture,target,level,xoffset,yoffset,zoffset,x,y,width,height);}
inline void glMultiTexImage1DEXT(GLenum texunit,GLenum target,GLint level,GLint internalformat,GLsizei width,GLint border,GLenum format,GLenum type,const void* pixels)const{(this->*(this->m_ptr_glMultiTexImage1DEXT))(texunit,target,level,internalformat,width,border,format,type,pixels);}
inline void glTextureLightEXT(GLenum pname)const{(this->*(this->m_ptr_glTextureLightEXT))(pname);}
inline void glNamedFramebufferTextureEXT(GLuint framebuffer,GLenum attachment,GLuint texture,GLint level)const{(this->*(this->m_ptr_glNamedFramebufferTextureEXT))(framebuffer,attachment,texture,level);}
inline void glBindFragDataLocationEXT(GLuint program,GLuint color,const GLchar* name)const{(this->*(this->m_ptr_glBindFragDataLocationEXT))(program,color,name);}
inline void glDeleteShader(GLuint shader)const{(this->*(this->m_ptr_glDeleteShader))(shader);}
inline void glCopyTextureSubImage1D(GLuint texture,GLint level,GLint xoffset,GLint x,GLint y,GLsizei width)const{(this->*(this->m_ptr_glCopyTextureSubImage1D))(texture,level,xoffset,x,y,width);}
inline void glCompressedTexImage3D(GLenum target,GLint level,GLenum internalformat,GLsizei width,GLsizei height,GLsizei depth,GLint border,GLsizei imageSize,const GLvoid* data)const{(this->*(this->m_ptr_glCompressedTexImage3D))(target,level,internalformat,width,height,depth,border,imageSize,data);}
inline void glTextureParameterIuiv(GLuint texture,GLenum pname,const GLuint* params)const{(this->*(this->m_ptr_glTextureParameterIuiv))(texture,pname,params);}
inline void glGetMinmaxParameterivEXT(GLenum target,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetMinmaxParameterivEXT))(target,pname,params);}
inline void glGetConvolutionParameterfv(GLenum target,GLenum pname,GLfloat* params)const{(this->*(this->m_ptr_glGetConvolutionParameterfv))(target,pname,params);}
inline void glCopyTexSubImage3D(GLenum target,GLint level,GLint xoffset,GLint yoffset,GLint zoffset,GLint x,GLint y,GLsizei width,GLsizei height)const{(this->*(this->m_ptr_glCopyTexSubImage3D))(target,level,xoffset,yoffset,zoffset,x,y,width,height);}
inline void glVertexAttribI3i(GLuint index,GLint x,GLint y,GLint z)const{(this->*(this->m_ptr_glVertexAttribI3i))(index,x,y,z);}
inline void glVertexAttribFormat(GLuint attribindex,GLint size,GLenum type,GLboolean normalized,GLuint relativeoffset)const{(this->*(this->m_ptr_glVertexAttribFormat))(attribindex,size,type,normalized,relativeoffset);}
inline void glVertexAttribI4usv(GLuint index,const GLushort* v)const{(this->*(this->m_ptr_glVertexAttribI4usv))(index,v);}
inline void glTexParameterf(GLenum target,GLenum pname,GLfloat param)const{(this->*(this->m_ptr_glTexParameterf))(target,pname,param);}
inline void glVertexAttribBinding(GLuint attribindex,GLuint bindingindex)const{(this->*(this->m_ptr_glVertexAttribBinding))(attribindex,bindingindex);}
inline void glGetHistogramParameteriv(GLenum target,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetHistogramParameteriv))(target,pname,params);}
inline void glTexParameteri(GLenum target,GLenum pname,GLint param)const{(this->*(this->m_ptr_glTexParameteri))(target,pname,param);}
inline void glGetShaderSource(GLuint shader,GLsizei bufSize,GLsizei* length,GLchar* source)const{(this->*(this->m_ptr_glGetShaderSource))(shader,bufSize,length,source);}
inline void glVertexAttrib4s(GLuint index,GLshort x,GLshort y,GLshort z,GLshort w)const{(this->*(this->m_ptr_glVertexAttrib4s))(index,x,y,z,w);}
inline void glPopName()const{(this->*(this->m_ptr_glPopName))();}
inline void glTextureBufferEXT(GLuint texture,GLenum target,GLenum internalformat,GLuint buffer)const{(this->*(this->m_ptr_glTextureBufferEXT))(texture,target,internalformat,buffer);}
inline void glGetMultiTexImageEXT(GLenum texunit,GLenum target,GLint level,GLenum format,GLenum type,void* pixels)const{(this->*(this->m_ptr_glGetMultiTexImageEXT))(texunit,target,level,format,type,pixels);}
inline void glGenProgramPipelines(GLsizei n,GLuint* pipelines)const{(this->*(this->m_ptr_glGenProgramPipelines))(n,pipelines);}
inline void glColor4ub(GLubyte red,GLubyte green,GLubyte blue,GLubyte alpha)const{(this->*(this->m_ptr_glColor4ub))(red,green,blue,alpha);}
inline void glColor4ui(GLuint red,GLuint green,GLuint blue,GLuint alpha)const{(this->*(this->m_ptr_glColor4ui))(red,green,blue,alpha);}
inline void glGetNamedBufferParameteriv(GLuint buffer,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetNamedBufferParameteriv))(buffer,pname,params);}
inline void glColor4us(GLushort red,GLushort green,GLushort blue,GLushort alpha)const{(this->*(this->m_ptr_glColor4us))(red,green,blue,alpha);}
inline void glVertexAttribP1uiv(GLuint index,GLenum type,GLboolean normalized,const GLuint* value)const{(this->*(this->m_ptr_glVertexAttribP1uiv))(index,type,normalized,value);}
inline void glLinkProgram(GLuint program)const{(this->*(this->m_ptr_glLinkProgram))(program);}
inline void glTexCoord2dv(const GLdouble* v)const{(this->*(this->m_ptr_glTexCoord2dv))(v);}
inline void glGetObjectLabel(GLenum identifier,GLuint name,GLsizei bufSize,GLsizei* length,GLchar* label)const{(this->*(this->m_ptr_glGetObjectLabel))(identifier,name,bufSize,length,label);}
inline void glVertexPointerEXT(GLint size,GLenum type,GLsizei stride,GLsizei count,const void* pointer)const{(this->*(this->m_ptr_glVertexPointerEXT))(size,type,stride,count,pointer);}
inline const GLubyte* glGetString(GLenum name)const{return (this->*(this->m_ptr_glGetString))(name);}
inline void glEndQuery(GLenum target)const{(this->*(this->m_ptr_glEndQuery))(target);}
inline void glSecondaryColor3uiv(const GLuint* v)const{(this->*(this->m_ptr_glSecondaryColor3uiv))(v);}
inline void glEdgeFlagPointer(GLsizei stride,const GLvoid* ptr)const{(this->*(this->m_ptr_glEdgeFlagPointer))(stride,ptr);}
inline void glFramebufferParameteri(GLenum target,GLenum pname,GLint param)const{(this->*(this->m_ptr_glFramebufferParameteri))(target,pname,param);}
inline void glCopyPixels(GLint x,GLint y,GLsizei width,GLsizei height,GLenum type)const{(this->*(this->m_ptr_glCopyPixels))(x,y,width,height,type);}
inline void glVertexAttribI2ui(GLuint index,GLuint x,GLuint y)const{(this->*(this->m_ptr_glVertexAttribI2ui))(index,x,y);}
inline void glDeleteTextures(GLsizei n,const GLuint* textures)const{(this->*(this->m_ptr_glDeleteTextures))(n,textures);}
inline void glGetMinmaxParameterfvEXT(GLenum target,GLenum pname,GLfloat* params)const{(this->*(this->m_ptr_glGetMinmaxParameterfvEXT))(target,pname,params);}
inline void glClipControl(GLenum origin,GLenum depth)const{(this->*(this->m_ptr_glClipControl))(origin,depth);}
inline void glVertexAttrib4f(GLuint index,GLfloat x,GLfloat y,GLfloat z,GLfloat w)const{(this->*(this->m_ptr_glVertexAttrib4f))(index,x,y,z,w);}
inline void glVertexAttrib4d(GLuint index,GLdouble x,GLdouble y,GLdouble z,GLdouble w)const{(this->*(this->m_ptr_glVertexAttrib4d))(index,x,y,z,w);}
inline void glGetNamedFramebufferParameteriv(GLuint framebuffer,GLenum pname,GLint* param)const{(this->*(this->m_ptr_glGetNamedFramebufferParameteriv))(framebuffer,pname,param);}
inline void glCreateVertexArrays(GLsizei n,GLuint* arrays)const{(this->*(this->m_ptr_glCreateVertexArrays))(n,arrays);}
inline void glBeginConditionalRender(GLuint id,GLenum mode)const{(this->*(this->m_ptr_glBeginConditionalRender))(id,mode);}
inline void glSamplerParameteri(GLuint sampler,GLenum pname,GLint param)const{(this->*(this->m_ptr_glSamplerParameteri))(sampler,pname,param);}
inline void glSamplerParameterf(GLuint sampler,GLenum pname,GLfloat param)const{(this->*(this->m_ptr_glSamplerParameterf))(sampler,pname,param);}
inline void glShaderOp1EXT(GLenum op,GLuint res,GLuint arg1)const{(this->*(this->m_ptr_glShaderOp1EXT))(op,res,arg1);}
inline void glGetnHistogram(GLenum target,GLboolean reset,GLenum format,GLenum type,GLsizei bufSize,void* values)const{(this->*(this->m_ptr_glGetnHistogram))(target,reset,format,type,bufSize,values);}
inline void glUniform1d(GLint location,GLdouble x)const{(this->*(this->m_ptr_glUniform1d))(location,x);}
inline GLint glRenderMode(GLenum mode)const{return (this->*(this->m_ptr_glRenderMode))(mode);}
inline void glClearColorIiEXT(GLint red,GLint green,GLint blue,GLint alpha)const{(this->*(this->m_ptr_glClearColorIiEXT))(red,green,blue,alpha);}
inline void glGetCompressedTexImage(GLenum target,GLint lod,GLvoid* img)const{(this->*(this->m_ptr_glGetCompressedTexImage))(target,lod,img);}
inline void glUniform1i(GLint location,GLint v0)const{(this->*(this->m_ptr_glUniform1i))(location,v0);}
inline void glGetTexEnvfv(GLenum target,GLenum pname,GLfloat* params)const{(this->*(this->m_ptr_glGetTexEnvfv))(target,pname,params);}
inline void glCullFace(GLenum mode)const{(this->*(this->m_ptr_glCullFace))(mode);}
inline void glProgramUniform4i(GLuint program,GLint location,GLint v0,GLint v1,GLint v2,GLint v3)const{(this->*(this->m_ptr_glProgramUniform4i))(program,location,v0,v1,v2,v3);}
inline void glProgramUniform4f(GLuint program,GLint location,GLfloat v0,GLfloat v1,GLfloat v2,GLfloat v3)const{(this->*(this->m_ptr_glProgramUniform4f))(program,location,v0,v1,v2,v3);}
inline void glViewportIndexedf(GLuint index,GLfloat x,GLfloat y,GLfloat w,GLfloat h)const{(this->*(this->m_ptr_glViewportIndexedf))(index,x,y,w,h);}
inline void glProgramUniform4d(GLuint program,GLint location,GLdouble v0,GLdouble v1,GLdouble v2,GLdouble v3)const{(this->*(this->m_ptr_glProgramUniform4d))(program,location,v0,v1,v2,v3);}
inline const GLubyte* glGetStringi(GLenum name,GLuint index)const{return (this->*(this->m_ptr_glGetStringi))(name,index);}
inline void glAttachShader(GLuint program,GLuint shader)const{(this->*(this->m_ptr_glAttachShader))(program,shader);}
inline void glQueryCounter(GLuint id,GLenum target)const{(this->*(this->m_ptr_glQueryCounter))(id,target);}
inline void glFogCoordPointer(GLenum type,GLsizei stride,const void* pointer)const{(this->*(this->m_ptr_glFogCoordPointer))(type,stride,pointer);}
inline GLboolean glUnmapNamedBuffer(GLuint buffer)const{return (this->*(this->m_ptr_glUnmapNamedBuffer))(buffer);}
inline void glSecondaryColor3dv(const GLdouble* v)const{(this->*(this->m_ptr_glSecondaryColor3dv))(v);}
inline void glVertexAttribI4sv(GLuint index,const GLshort* v)const{(this->*(this->m_ptr_glVertexAttribI4sv))(index,v);}
inline void glDrawTransformFeedbackStreamInstanced(GLenum mode,GLuint id,GLuint stream,GLsizei instancecount)const{(this->*(this->m_ptr_glDrawTransformFeedbackStreamInstanced))(mode,id,stream,instancecount);}
inline void glTexEnvfv(GLenum target,GLenum pname,const GLfloat* params)const{(this->*(this->m_ptr_glTexEnvfv))(target,pname,params);}
inline void glTexParameterIuiv(GLenum target,GLenum pname,const GLuint* params)const{(this->*(this->m_ptr_glTexParameterIuiv))(target,pname,params);}
inline void glWindowPos3fv(const GLfloat* v)const{(this->*(this->m_ptr_glWindowPos3fv))(v);}
inline void glLightModelfv(GLenum pname,const GLfloat* params)const{(this->*(this->m_ptr_glLightModelfv))(pname,params);}
inline void glConvolutionParameteri(GLenum target,GLenum pname,GLint params)const{(this->*(this->m_ptr_glConvolutionParameteri))(target,pname,params);}
inline void glColorMaskIndexedEXT(GLuint index,GLboolean r,GLboolean g,GLboolean b,GLboolean a)const{(this->*(this->m_ptr_glColorMaskIndexedEXT))(index,r,g,b,a);}
inline void glConvolutionParameterf(GLenum target,GLenum pname,GLfloat params)const{(this->*(this->m_ptr_glConvolutionParameterf))(target,pname,params);}
inline void glVertexAttribI4ubvEXT(GLuint index,const GLubyte* v)const{(this->*(this->m_ptr_glVertexAttribI4ubvEXT))(index,v);}
inline void glNamedProgramLocalParameterI4uiEXT(GLuint program,GLenum target,GLuint index,GLuint x,GLuint y,GLuint z,GLuint w)const{(this->*(this->m_ptr_glNamedProgramLocalParameterI4uiEXT))(program,target,index,x,y,z,w);}
inline void glProgramUniform1iEXT(GLuint program,GLint location,GLint v0)const{(this->*(this->m_ptr_glProgramUniform1iEXT))(program,location,v0);}
inline void glVertex4s(GLshort x,GLshort y,GLshort z,GLshort w)const{(this->*(this->m_ptr_glVertex4s))(x,y,z,w);}
inline GLboolean glIsTransformFeedback(GLuint id)const{return (this->*(this->m_ptr_glIsTransformFeedback))(id);}
inline void glGetMinmaxParameterfv(GLenum target,GLenum pname,GLfloat* params)const{(this->*(this->m_ptr_glGetMinmaxParameterfv))(target,pname,params);}
inline void glGetObjectLabelEXT(GLenum type,GLuint object,GLsizei bufSize,GLsizei* length,GLchar* label)const{(this->*(this->m_ptr_glGetObjectLabelEXT))(type,object,bufSize,length,label);}
inline void glRotated(GLdouble angle,GLdouble x,GLdouble y,GLdouble z)const{(this->*(this->m_ptr_glRotated))(angle,x,y,z);}
inline GLboolean glIsProgramPipeline(GLuint pipeline)const{return (this->*(this->m_ptr_glIsProgramPipeline))(pipeline);}
inline void glRotatef(GLfloat angle,GLfloat x,GLfloat y,GLfloat z)const{(this->*(this->m_ptr_glRotatef))(angle,x,y,z);}
inline void glVertex4i(GLint x,GLint y,GLint z,GLint w)const{(this->*(this->m_ptr_glVertex4i))(x,y,z,w);}
inline void glGetActiveSubroutineUniformName(GLuint program,GLenum shadertype,GLuint index,GLsizei bufsize,GLsizei* length,GLchar* name)const{(this->*(this->m_ptr_glGetActiveSubroutineUniformName))(program,shadertype,index,bufsize,length,name);}
inline void glUniformMatrix3fv(GLint location,GLsizei count,GLboolean transpose,const GLfloat* value)const{(this->*(this->m_ptr_glUniformMatrix3fv))(location,count,transpose,value);}
inline void glGetnUniformfv(GLuint program,GLint location,GLsizei bufSize,GLfloat* params)const{(this->*(this->m_ptr_glGetnUniformfv))(program,location,bufSize,params);}
inline void glVertexAttribL2dv(GLuint index,const GLdouble* v)const{(this->*(this->m_ptr_glVertexAttribL2dv))(index,v);}
inline void glVertexWeightPointerEXT(GLint size,GLenum type,GLsizei stride,const void* pointer)const{(this->*(this->m_ptr_glVertexWeightPointerEXT))(size,type,stride,pointer);}
inline void glTangent3sEXT(GLshort tx,GLshort ty,GLshort tz)const{(this->*(this->m_ptr_glTangent3sEXT))(tx,ty,tz);}
inline void glSecondaryColorPointer(GLint size,GLenum type,GLsizei stride,const void* pointer)const{(this->*(this->m_ptr_glSecondaryColorPointer))(size,type,stride,pointer);}
inline void glAlphaFunc(GLenum func,GLclampf ref)const{(this->*(this->m_ptr_glAlphaFunc))(func,ref);}
inline void glVertexAttribL2d(GLuint index,GLdouble x,GLdouble y)const{(this->*(this->m_ptr_glVertexAttribL2d))(index,x,y);}
inline void glStencilFunc(GLenum func,GLint ref,GLuint mask)const{(this->*(this->m_ptr_glStencilFunc))(func,ref,mask);}
inline void glMultiTexCoord1fv(GLenum target,const GLfloat* v)const{(this->*(this->m_ptr_glMultiTexCoord1fv))(target,v);}
inline void glGetQueryBufferObjectiv(GLuint id,GLuint buffer,GLenum pname,GLintptr offset)const{(this->*(this->m_ptr_glGetQueryBufferObjectiv))(id,buffer,pname,offset);}
inline void glGetProgramPipelineiv(GLuint pipeline,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetProgramPipelineiv))(pipeline,pname,params);}
inline void glGetColorTableEXT(GLenum target,GLenum format,GLenum type,void* data)const{(this->*(this->m_ptr_glGetColorTableEXT))(target,format,type,data);}
inline void glGetShaderInfoLog(GLuint shader,GLsizei bufSize,GLsizei* length,GLchar* infoLog)const{(this->*(this->m_ptr_glGetShaderInfoLog))(shader,bufSize,length,infoLog);}
inline void glVertexAttribI4i(GLuint index,GLint x,GLint y,GLint z,GLint w)const{(this->*(this->m_ptr_glVertexAttribI4i))(index,x,y,z,w);}
inline void glRasterPos2iv(const GLint* v)const{(this->*(this->m_ptr_glRasterPos2iv))(v);}
inline void glBlendEquationSeparate(GLenum modeRGB,GLenum modeAlpha)const{(this->*(this->m_ptr_glBlendEquationSeparate))(modeRGB,modeAlpha);}
inline GLuint glGetSubroutineIndex(GLuint program,GLenum shadertype,const GLchar* name)const{return (this->*(this->m_ptr_glGetSubroutineIndex))(program,shadertype,name);}
inline void glVertexAttrib2sv(GLuint index,const GLshort* v)const{(this->*(this->m_ptr_glVertexAttrib2sv))(index,v);}
inline void glPushAttrib(GLbitfield mask)const{(this->*(this->m_ptr_glPushAttrib))(mask);}
inline void glCompressedTextureImage1DEXT(GLuint texture,GLenum target,GLint level,GLenum internalformat,GLsizei width,GLint border,GLsizei imageSize,const void* bits)const{(this->*(this->m_ptr_glCompressedTextureImage1DEXT))(texture,target,level,internalformat,width,border,imageSize,bits);}
inline void glLightiv(GLenum light,GLenum pname,const GLint* params)const{(this->*(this->m_ptr_glLightiv))(light,pname,params);}
inline void glNamedProgramLocalParameter4fEXT(GLuint program,GLenum target,GLuint index,GLfloat x,GLfloat y,GLfloat z,GLfloat w)const{(this->*(this->m_ptr_glNamedProgramLocalParameter4fEXT))(program,target,index,x,y,z,w);}
inline void glVertexAttribL1dEXT(GLuint index,GLdouble x)const{(this->*(this->m_ptr_glVertexAttribL1dEXT))(index,x);}
inline void glSecondaryColor3bEXT(GLbyte red,GLbyte green,GLbyte blue)const{(this->*(this->m_ptr_glSecondaryColor3bEXT))(red,green,blue);}
inline void glProgramUniform1uivEXT(GLuint program,GLint location,GLsizei count,const GLuint* value)const{(this->*(this->m_ptr_glProgramUniform1uivEXT))(program,location,count,value);}
inline void glVertexArrayVertexAttribLFormatEXT(GLuint vaobj,GLuint attribindex,GLint size,GLenum type,GLuint relativeoffset)const{(this->*(this->m_ptr_glVertexArrayVertexAttribLFormatEXT))(vaobj,attribindex,size,type,relativeoffset);}
inline void glDeleteBuffers(GLsizei n,const GLuint* buffers)const{(this->*(this->m_ptr_glDeleteBuffers))(n,buffers);}
inline void glBindProgramPipeline(GLuint pipeline)const{(this->*(this->m_ptr_glBindProgramPipeline))(pipeline);}
inline void glScissor(GLint x,GLint y,GLsizei width,GLsizei height)const{(this->*(this->m_ptr_glScissor))(x,y,width,height);}
inline void glProgramUniform4fv(GLuint program,GLint location,GLsizei count,const GLfloat* value)const{(this->*(this->m_ptr_glProgramUniform4fv))(program,location,count,value);}
inline void glGetBooleanv(GLenum pname,GLboolean* params)const{(this->*(this->m_ptr_glGetBooleanv))(pname,params);}
inline void glMaterialfv(GLenum face,GLenum pname,const GLfloat* params)const{(this->*(this->m_ptr_glMaterialfv))(face,pname,params);}
inline void glVertexAttribIPointerEXT(GLuint index,GLint size,GLenum type,GLsizei stride,const void* pointer)const{(this->*(this->m_ptr_glVertexAttribIPointerEXT))(index,size,type,stride,pointer);}
inline void glProgramUniform4uivEXT(GLuint program,GLint location,GLsizei count,const GLuint* value)const{(this->*(this->m_ptr_glProgramUniform4uivEXT))(program,location,count,value);}
inline void glGetTextureLevelParameteriv(GLuint texture,GLint level,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetTextureLevelParameteriv))(texture,level,pname,params);}
inline void glVertexAttribI2uiv(GLuint index,const GLuint* v)const{(this->*(this->m_ptr_glVertexAttribI2uiv))(index,v);}
inline void glColor4dv(const GLdouble* v)const{(this->*(this->m_ptr_glColor4dv))(v);}
inline void glGetVertexArrayIndexediv(GLuint vaobj,GLuint index,GLenum pname,GLint* param)const{(this->*(this->m_ptr_glGetVertexArrayIndexediv))(vaobj,index,pname,param);}
inline void glPointParameterfv(GLenum pname,const GLfloat* params)const{(this->*(this->m_ptr_glPointParameterfv))(pname,params);}
inline void glUniform2fv(GLint location,GLsizei count,const GLfloat* value)const{(this->*(this->m_ptr_glUniform2fv))(location,count,value);}
inline void glGetMultiTexGenfvEXT(GLenum texunit,GLenum coord,GLenum pname,GLfloat* params)const{(this->*(this->m_ptr_glGetMultiTexGenfvEXT))(texunit,coord,pname,params);}
inline void glGetMinmaxEXT(GLenum target,GLboolean reset,GLenum format,GLenum type,void* values)const{(this->*(this->m_ptr_glGetMinmaxEXT))(target,reset,format,type,values);}
inline void glMatrixFrustumEXT(GLenum mode,GLdouble left,GLdouble right,GLdouble bottom,GLdouble top,GLdouble zNear,GLdouble zFar)const{(this->*(this->m_ptr_glMatrixFrustumEXT))(mode,left,right,bottom,top,zNear,zFar);}
inline void glDispatchComputeIndirect(GLintptr indirect)const{(this->*(this->m_ptr_glDispatchComputeIndirect))(indirect);}
inline void glInvalidateNamedFramebufferSubData(GLuint framebuffer,GLsizei numAttachments,const GLenum* attachments,GLint x,GLint y,GLsizei width,GLsizei height)const{(this->*(this->m_ptr_glInvalidateNamedFramebufferSubData))(framebuffer,numAttachments,attachments,x,y,width,height);}
inline void glBindBufferRange(GLenum target,GLuint index,GLuint buffer,GLintptr offset,GLsizeiptr size)const{(this->*(this->m_ptr_glBindBufferRange))(target,index,buffer,offset,size);}
inline void glNormal3iv(const GLint* v)const{(this->*(this->m_ptr_glNormal3iv))(v);}
inline void glVertexAttribL3dv(GLuint index,const GLdouble* v)const{(this->*(this->m_ptr_glVertexAttribL3dv))(index,v);}
inline void glGetUniformdv(GLuint program,GLint location,GLdouble* params)const{(this->*(this->m_ptr_glGetUniformdv))(program,location,params);}
inline void glGetMultiTexLevelParameterfvEXT(GLenum texunit,GLenum target,GLint level,GLenum pname,GLfloat* params)const{(this->*(this->m_ptr_glGetMultiTexLevelParameterfvEXT))(texunit,target,level,pname,params);}
inline void glCullParameterdvEXT(GLenum pname,GLdouble* params)const{(this->*(this->m_ptr_glCullParameterdvEXT))(pname,params);}
inline void glConvolutionParameterfEXT(GLenum target,GLenum pname,GLfloat params)const{(this->*(this->m_ptr_glConvolutionParameterfEXT))(target,pname,params);}
inline void glTexCoord1iv(const GLint* v)const{(this->*(this->m_ptr_glTexCoord1iv))(v);}
inline void glProgramUniform3fvEXT(GLuint program,GLint location,GLsizei count,const GLfloat* value)const{(this->*(this->m_ptr_glProgramUniform3fvEXT))(program,location,count,value);}
inline void glColor3uiv(const GLuint* v)const{(this->*(this->m_ptr_glColor3uiv))(v);}
inline void glListBase(GLuint base)const{(this->*(this->m_ptr_glListBase))(base);}
inline void glGetLightiv(GLenum light,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetLightiv))(light,pname,params);}
inline void glGetVertexArrayPointervEXT(GLuint vaobj,GLenum pname,void** param)const{(this->*(this->m_ptr_glGetVertexArrayPointervEXT))(vaobj,pname,param);}
inline void glColorSubTableEXT(GLenum target,GLsizei start,GLsizei count,GLenum format,GLenum type,const void* data)const{(this->*(this->m_ptr_glColorSubTableEXT))(target,start,count,format,type,data);}
inline GLenum glClientWaitSync(GLsync sync,GLbitfield flags,GLuint64 timeout)const{return (this->*(this->m_ptr_glClientWaitSync))(sync,flags,timeout);}
inline void glColor3s(GLshort red,GLshort green,GLshort blue)const{(this->*(this->m_ptr_glColor3s))(red,green,blue);}
inline void glVariantPointerEXT(GLuint id,GLenum type,GLuint stride,const void* addr)const{(this->*(this->m_ptr_glVariantPointerEXT))(id,type,stride,addr);}
inline void glNamedFramebufferParameteriEXT(GLuint framebuffer,GLenum pname,GLint param)const{(this->*(this->m_ptr_glNamedFramebufferParameteriEXT))(framebuffer,pname,param);}
inline void glVertexAttribI1uiEXT(GLuint index,GLuint x)const{(this->*(this->m_ptr_glVertexAttribI1uiEXT))(index,x);}
inline void glInvalidateTexImage(GLuint texture,GLint level)const{(this->*(this->m_ptr_glInvalidateTexImage))(texture,level);}
inline void glCopyImageSubData(GLuint srcName,GLenum srcTarget,GLint srcLevel,GLint srcX,GLint srcY,GLint srcZ,GLuint dstName,GLenum dstTarget,GLint dstLevel,GLint dstX,GLint dstY,GLint dstZ,GLsizei srcWidth,GLsizei srcHeight,GLsizei srcDepth)const{(this->*(this->m_ptr_glCopyImageSubData))(srcName,srcTarget,srcLevel,srcX,srcY,srcZ,dstName,dstTarget,dstLevel,dstX,dstY,dstZ,srcWidth,srcHeight,srcDepth);}
inline void glGetUniformSubroutineuiv(GLenum shadertype,GLint location,GLuint* params)const{(this->*(this->m_ptr_glGetUniformSubroutineuiv))(shadertype,location,params);}
inline void glBindVertexBuffer(GLuint bindingindex,GLuint buffer,GLintptr offset,GLsizei stride)const{(this->*(this->m_ptr_glBindVertexBuffer))(bindingindex,buffer,offset,stride);}
inline void glDebugMessageInsert(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar* buf)const{(this->*(this->m_ptr_glDebugMessageInsert))(source,type,id,severity,length,buf);}
inline void glGetBooleani_v(GLenum target,GLuint index,GLboolean* data)const{(this->*(this->m_ptr_glGetBooleani_v))(target,index,data);}
inline GLboolean glIsVariantEnabledEXT(GLuint id,GLenum cap)const{return (this->*(this->m_ptr_glIsVariantEnabledEXT))(id,cap);}
inline GLuint glBindMaterialParameterEXT(GLenum face,GLenum value)const{return (this->*(this->m_ptr_glBindMaterialParameterEXT))(face,value);}
inline GLboolean glIsSampler(GLuint sampler)const{return (this->*(this->m_ptr_glIsSampler))(sampler);}
inline void glMultiTexGenivEXT(GLenum texunit,GLenum coord,GLenum pname,const GLint* params)const{(this->*(this->m_ptr_glMultiTexGenivEXT))(texunit,coord,pname,params);}
inline void glNamedFramebufferTexture2DEXT(GLuint framebuffer,GLenum attachment,GLenum textarget,GLuint texture,GLint level)const{(this->*(this->m_ptr_glNamedFramebufferTexture2DEXT))(framebuffer,attachment,textarget,texture,level);}
inline void glCopyTexSubImage1D(GLenum target,GLint level,GLint xoffset,GLint x,GLint y,GLsizei width)const{(this->*(this->m_ptr_glCopyTexSubImage1D))(target,level,xoffset,x,y,width);}
inline void glTexCoord1i(GLint s)const{(this->*(this->m_ptr_glTexCoord1i))(s);}
inline GLenum glCheckFramebufferStatus(GLenum target)const{return (this->*(this->m_ptr_glCheckFramebufferStatus))(target);}
inline void glTexCoord1d(GLdouble s)const{(this->*(this->m_ptr_glTexCoord1d))(s);}
inline void glTexCoord1f(GLfloat s)const{(this->*(this->m_ptr_glTexCoord1f))(s);}
inline void glNamedBufferStorageEXT(GLuint buffer,GLsizeiptr size,const void* data,GLbitfield flags)const{(this->*(this->m_ptr_glNamedBufferStorageEXT))(buffer,size,data,flags);}
inline void glBindImageTexture(GLuint unit,GLuint texture,GLint level,GLboolean layered,GLint layer,GLenum access,GLenum format)const{(this->*(this->m_ptr_glBindImageTexture))(unit,texture,level,layered,layer,access,format);}
inline void glDrawRangeElements(GLenum mode,GLuint start,GLuint end,GLsizei count,GLenum type,const GLvoid* indices)const{(this->*(this->m_ptr_glDrawRangeElements))(mode,start,end,count,type,indices);}
inline void glMultiTexCoordPointerEXT(GLenum texunit,GLint size,GLenum type,GLsizei stride,const void* pointer)const{(this->*(this->m_ptr_glMultiTexCoordPointerEXT))(texunit,size,type,stride,pointer);}
inline void glBindBufferBase(GLenum target,GLuint index,GLuint buffer)const{(this->*(this->m_ptr_glBindBufferBase))(target,index,buffer);}
inline void glColor3bv(const GLbyte* v)const{(this->*(this->m_ptr_glColor3bv))(v);}
inline void glCreateSamplers(GLsizei n,GLuint* samplers)const{(this->*(this->m_ptr_glCreateSamplers))(n,samplers);}
inline void glMultiDrawArrays(GLenum mode,const GLint* first,const GLsizei* count,GLsizei drawcount)const{(this->*(this->m_ptr_glMultiDrawArrays))(mode,first,count,drawcount);}
inline void glBinormal3ivEXT(const GLint* v)const{(this->*(this->m_ptr_glBinormal3ivEXT))(v);}
inline void glUniformBufferEXT(GLuint program,GLint location,GLuint buffer)const{(this->*(this->m_ptr_glUniformBufferEXT))(program,location,buffer);}
inline void glVertexAttribL1d(GLuint index,GLdouble x)const{(this->*(this->m_ptr_glVertexAttribL1d))(index,x);}
inline void glMultiTexSubImage1DEXT(GLenum texunit,GLenum target,GLint level,GLint xoffset,GLsizei width,GLenum format,GLenum type,const void* pixels)const{(this->*(this->m_ptr_glMultiTexSubImage1DEXT))(texunit,target,level,xoffset,width,format,type,pixels);}
inline void glNamedProgramLocalParameter4dEXT(GLuint program,GLenum target,GLuint index,GLdouble x,GLdouble y,GLdouble z,GLdouble w)const{(this->*(this->m_ptr_glNamedProgramLocalParameter4dEXT))(program,target,index,x,y,z,w);}
inline void glVertexAttribIFormat(GLuint attribindex,GLint size,GLenum type,GLuint relativeoffset)const{(this->*(this->m_ptr_glVertexAttribIFormat))(attribindex,size,type,relativeoffset);}
inline void glCreateFramebuffers(GLsizei n,GLuint* framebuffers)const{(this->*(this->m_ptr_glCreateFramebuffers))(n,framebuffers);}
inline void glClearAccum(GLfloat red,GLfloat green,GLfloat blue,GLfloat alpha)const{(this->*(this->m_ptr_glClearAccum))(red,green,blue,alpha);}
inline void glUniform2uivEXT(GLint location,GLsizei count,const GLuint* value)const{(this->*(this->m_ptr_glUniform2uivEXT))(location,count,value);}
inline void glBeginQuery(GLenum target,GLuint id)const{(this->*(this->m_ptr_glBeginQuery))(target,id);}
inline void glBindBuffer(GLenum target,GLuint buffer)const{(this->*(this->m_ptr_glBindBuffer))(target,buffer);}
inline void glMap2d(GLenum target,GLdouble u1,GLdouble u2,GLint ustride,GLint uorder,GLdouble v1,GLdouble v2,GLint vstride,GLint vorder,const GLdouble* points)const{(this->*(this->m_ptr_glMap2d))(target,u1,u2,ustride,uorder,v1,v2,vstride,vorder,points);}
inline void glMap2f(GLenum target,GLfloat u1,GLfloat u2,GLint ustride,GLint uorder,GLfloat v1,GLfloat v2,GLint vstride,GLint vorder,const GLfloat* points)const{(this->*(this->m_ptr_glMap2f))(target,u1,u2,ustride,uorder,v1,v2,vstride,vorder,points);}
inline void glUniformMatrix2x4fv(GLint location,GLsizei count,GLboolean transpose,const GLfloat* value)const{(this->*(this->m_ptr_glUniformMatrix2x4fv))(location,count,transpose,value);}
inline void glGetMultiTexParameterfvEXT(GLenum texunit,GLenum target,GLenum pname,GLfloat* params)const{(this->*(this->m_ptr_glGetMultiTexParameterfvEXT))(texunit,target,pname,params);}
inline void glDepthRangeIndexed(GLuint index,GLdouble n,GLdouble f)const{(this->*(this->m_ptr_glDepthRangeIndexed))(index,n,f);}
inline void glMultiTexCoord1s(GLenum target,GLshort s)const{(this->*(this->m_ptr_glMultiTexCoord1s))(target,s);}
inline void glMatrixScalefEXT(GLenum mode,GLfloat x,GLfloat y,GLfloat z)const{(this->*(this->m_ptr_glMatrixScalefEXT))(mode,x,y,z);}
inline GLenum glGetError()const{return (this->*(this->m_ptr_glGetError))();}
inline void glGetTexEnviv(GLenum target,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetTexEnviv))(target,pname,params);}
inline GLuint glBindTextureUnitParameterEXT(GLenum unit,GLenum value)const{return (this->*(this->m_ptr_glBindTextureUnitParameterEXT))(unit,value);}
inline void glVertexAttribI3ivEXT(GLuint index,const GLint* v)const{(this->*(this->m_ptr_glVertexAttribI3ivEXT))(index,v);}
inline void glEvalCoord1d(GLdouble u)const{(this->*(this->m_ptr_glEvalCoord1d))(u);}
inline void glGetTexLevelParameterfv(GLenum target,GLint level,GLenum pname,GLfloat* params)const{(this->*(this->m_ptr_glGetTexLevelParameterfv))(target,level,pname,params);}
inline void glEvalCoord1f(GLfloat u)const{(this->*(this->m_ptr_glEvalCoord1f))(u);}
inline void glPixelMapfv(GLenum map,GLsizei mapsize,const GLfloat* values)const{(this->*(this->m_ptr_glPixelMapfv))(map,mapsize,values);}
inline void glVertexAttribI1ivEXT(GLuint index,const GLint* v)const{(this->*(this->m_ptr_glVertexAttribI1ivEXT))(index,v);}
inline void glGetPixelMapusv(GLenum map,GLushort* values)const{(this->*(this->m_ptr_glGetPixelMapusv))(map,values);}
inline void glAccum(GLenum op,GLfloat value)const{(this->*(this->m_ptr_glAccum))(op,value);}
inline void glGetnTexImage(GLenum target,GLint level,GLenum format,GLenum type,GLsizei bufSize,void* pixels)const{(this->*(this->m_ptr_glGetnTexImage))(target,level,format,type,bufSize,pixels);}
inline void glTexCoord2iv(const GLint* v)const{(this->*(this->m_ptr_glTexCoord2iv))(v);}
inline void glGetFramebufferAttachmentParameteriv(GLenum target,GLenum attachment,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetFramebufferAttachmentParameteriv))(target,attachment,pname,params);}
inline void glProgramUniform4ui(GLuint program,GLint location,GLuint v0,GLuint v1,GLuint v2,GLuint v3)const{(this->*(this->m_ptr_glProgramUniform4ui))(program,location,v0,v1,v2,v3);}
inline void glStencilMask(GLuint mask)const{(this->*(this->m_ptr_glStencilMask))(mask);}
inline void glGenRenderbuffersEXT(GLsizei n,GLuint* renderbuffers)const{(this->*(this->m_ptr_glGenRenderbuffersEXT))(n,renderbuffers);}
inline void glNamedBufferData(GLuint buffer,GLsizeiptr size,const void* data,GLenum usage)const{(this->*(this->m_ptr_glNamedBufferData))(buffer,size,data,usage);}
inline void glClearNamedBufferSubData(GLuint buffer,GLenum internalformat,GLintptr offset,GLsizeiptr size,GLenum format,GLenum type,const void* data)const{(this->*(this->m_ptr_glClearNamedBufferSubData))(buffer,internalformat,offset,size,format,type,data);}
inline void* glMapNamedBufferRange(GLuint buffer,GLintptr offset,GLsizeiptr length,GLbitfield access)const{return (this->*(this->m_ptr_glMapNamedBufferRange))(buffer,offset,length,access);}
inline void glProgramUniform3dvEXT(GLuint program,GLint location,GLsizei count,const GLdouble* value)const{(this->*(this->m_ptr_glProgramUniform3dvEXT))(program,location,count,value);}
inline void glRectsv(const GLshort* v1,const GLshort* v2)const{(this->*(this->m_ptr_glRectsv))(v1,v2);}
inline void glMultiTexImage2DEXT(GLenum texunit,GLenum target,GLint level,GLint internalformat,GLsizei width,GLsizei height,GLint border,GLenum format,GLenum type,const void* pixels)const{(this->*(this->m_ptr_glMultiTexImage2DEXT))(texunit,target,level,internalformat,width,height,border,format,type,pixels);}
inline void glGetTexGeniv(GLenum coord,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetTexGeniv))(coord,pname,params);}
inline void glPixelStorei(GLenum pname,GLint param)const{(this->*(this->m_ptr_glPixelStorei))(pname,param);}
inline void glGetCompressedTextureSubImage(GLuint texture,GLint level,GLint xoffset,GLint yoffset,GLint zoffset,GLsizei width,GLsizei height,GLsizei depth,GLsizei bufSize,void* pixels)const{(this->*(this->m_ptr_glGetCompressedTextureSubImage))(texture,level,xoffset,yoffset,zoffset,width,height,depth,bufSize,pixels);}
inline void glDepthMask(GLboolean flag)const{(this->*(this->m_ptr_glDepthMask))(flag);}
inline void glPatchParameterfv(GLenum pname,const GLfloat* values)const{(this->*(this->m_ptr_glPatchParameterfv))(pname,values);}
inline GLboolean glIsFramebufferEXT(GLuint framebuffer)const{return (this->*(this->m_ptr_glIsFramebufferEXT))(framebuffer);}
inline void glTextureStorage2D(GLuint texture,GLsizei levels,GLenum internalformat,GLsizei width,GLsizei height)const{(this->*(this->m_ptr_glTextureStorage2D))(texture,levels,internalformat,width,height);}
inline void glTexBufferRange(GLenum target,GLenum internalformat,GLuint buffer,GLintptr offset,GLsizeiptr size)const{(this->*(this->m_ptr_glTexBufferRange))(target,internalformat,buffer,offset,size);}
inline void glTextureSubImage3DEXT(GLuint texture,GLenum target,GLint level,GLint xoffset,GLint yoffset,GLint zoffset,GLsizei width,GLsizei height,GLsizei depth,GLenum format,GLenum type,const void* pixels)const{(this->*(this->m_ptr_glTextureSubImage3DEXT))(texture,target,level,xoffset,yoffset,zoffset,width,height,depth,format,type,pixels);}
inline void glProgramUniform1uiEXT(GLuint program,GLint location,GLuint v0)const{(this->*(this->m_ptr_glProgramUniform1uiEXT))(program,location,v0);}
inline void glGetProgramResourceiv(GLuint program,GLenum programInterface,GLuint index,GLsizei propCount,const GLenum* props,GLsizei bufSize,GLsizei* length,GLint* params)const{(this->*(this->m_ptr_glGetProgramResourceiv))(program,programInterface,index,propCount,props,bufSize,length,params);}
inline void glVertexAttribI3ui(GLuint index,GLuint x,GLuint y,GLuint z)const{(this->*(this->m_ptr_glVertexAttribI3ui))(index,x,y,z);}
inline void glVertexArrayVertexBuffers(GLuint vaobj,GLuint first,GLsizei count,const GLuint* buffers,const GLintptr* offsets,const GLsizei* strides)const{(this->*(this->m_ptr_glVertexArrayVertexBuffers))(vaobj,first,count,buffers,offsets,strides);}
inline void glProgramParameteri(GLuint program,GLenum pname,GLint value)const{(this->*(this->m_ptr_glProgramParameteri))(program,pname,value);}
inline void glGetMapfv(GLenum target,GLenum query,GLfloat* v)const{(this->*(this->m_ptr_glGetMapfv))(target,query,v);}
inline void glVertexAttribL2dEXT(GLuint index,GLdouble x,GLdouble y)const{(this->*(this->m_ptr_glVertexAttribL2dEXT))(index,x,y);}
inline void glRasterPos2fv(const GLfloat* v)const{(this->*(this->m_ptr_glRasterPos2fv))(v);}
inline void glProgramUniformMatrix3x2dvEXT(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLdouble* value)const{(this->*(this->m_ptr_glProgramUniformMatrix3x2dvEXT))(program,location,count,transpose,value);}
inline void glEnableVertexArrayAttribEXT(GLuint vaobj,GLuint index)const{(this->*(this->m_ptr_glEnableVertexArrayAttribEXT))(vaobj,index);}
inline void glProgramUniform2uivEXT(GLuint program,GLint location,GLsizei count,const GLuint* value)const{(this->*(this->m_ptr_glProgramUniform2uivEXT))(program,location,count,value);}
inline void glGetDoubleIndexedvEXT(GLenum target,GLuint index,GLdouble* data)const{(this->*(this->m_ptr_glGetDoubleIndexedvEXT))(target,index,data);}
inline void glCopyConvolutionFilter1DEXT(GLenum target,GLenum internalformat,GLint x,GLint y,GLsizei width)const{(this->*(this->m_ptr_glCopyConvolutionFilter1DEXT))(target,internalformat,x,y,width);}
inline void glWindowPos2sv(const GLshort* v)const{(this->*(this->m_ptr_glWindowPos2sv))(v);}
inline void glBindFramebufferEXT(GLenum target,GLuint framebuffer)const{(this->*(this->m_ptr_glBindFramebufferEXT))(target,framebuffer);}
inline GLuint glCreateShader(GLenum type)const{return (this->*(this->m_ptr_glCreateShader))(type);}
inline void glGetColorTableParameterfvEXT(GLenum target,GLenum pname,GLfloat* params)const{(this->*(this->m_ptr_glGetColorTableParameterfvEXT))(target,pname,params);}
inline void glGenRenderbuffers(GLsizei n,GLuint* renderbuffers)const{(this->*(this->m_ptr_glGenRenderbuffers))(n,renderbuffers);}
inline void glCopyTexSubImage2D(GLenum target,GLint level,GLint xoffset,GLint yoffset,GLint x,GLint y,GLsizei width,GLsizei height)const{(this->*(this->m_ptr_glCopyTexSubImage2D))(target,level,xoffset,yoffset,x,y,width,height);}
inline void glBlendFuncSeparate(GLenum sfactorRGB,GLenum dfactorRGB,GLenum sfactorAlpha,GLenum dfactorAlpha)const{(this->*(this->m_ptr_glBlendFuncSeparate))(sfactorRGB,dfactorRGB,sfactorAlpha,dfactorAlpha);}
inline void glActiveShaderProgram(GLuint pipeline,GLuint program)const{(this->*(this->m_ptr_glActiveShaderProgram))(pipeline,program);}
inline void glTexCoord2fv(const GLfloat* v)const{(this->*(this->m_ptr_glTexCoord2fv))(v);}
inline void glGetVariantFloatvEXT(GLuint id,GLenum value,GLfloat* data)const{(this->*(this->m_ptr_glGetVariantFloatvEXT))(id,value,data);}
inline void glVertexP2ui(GLenum type,GLuint value)const{(this->*(this->m_ptr_glVertexP2ui))(type,value);}
inline void glTexCoord4fv(const GLfloat* v)const{(this->*(this->m_ptr_glTexCoord4fv))(v);}
inline void glPointSize(GLfloat size)const{(this->*(this->m_ptr_glPointSize))(size);}
inline void glBindTextureUnit(GLuint unit,GLuint texture)const{(this->*(this->m_ptr_glBindTextureUnit))(unit,texture);}
inline void glGetProgramPipelineInfoLog(GLuint pipeline,GLsizei bufSize,GLsizei* length,GLchar* infoLog)const{(this->*(this->m_ptr_glGetProgramPipelineInfoLog))(pipeline,bufSize,length,infoLog);}
inline void glVertexAttrib4Nuiv(GLuint index,const GLuint* v)const{(this->*(this->m_ptr_glVertexAttrib4Nuiv))(index,v);}
inline void glRenderbufferStorage(GLenum target,GLenum internalformat,GLsizei width,GLsizei height)const{(this->*(this->m_ptr_glRenderbufferStorage))(target,internalformat,width,height);}
inline void glWaitSync(GLsync sync,GLbitfield flags,GLuint64 timeout)const{(this->*(this->m_ptr_glWaitSync))(sync,flags,timeout);}
inline void glUniform3i(GLint location,GLint v0,GLint v1,GLint v2)const{(this->*(this->m_ptr_glUniform3i))(location,v0,v1,v2);}
inline void glBlendEquationSeparatei(GLuint buf,GLenum modeRGB,GLenum modeAlpha)const{(this->*(this->m_ptr_glBlendEquationSeparatei))(buf,modeRGB,modeAlpha);}
inline void glTextureParameterivEXT(GLuint texture,GLenum target,GLenum pname,const GLint* params)const{(this->*(this->m_ptr_glTextureParameterivEXT))(texture,target,pname,params);}
inline void glUniform3d(GLint location,GLdouble x,GLdouble y,GLdouble z)const{(this->*(this->m_ptr_glUniform3d))(location,x,y,z);}
inline void glUniform3f(GLint location,GLfloat v0,GLfloat v1,GLfloat v2)const{(this->*(this->m_ptr_glUniform3f))(location,v0,v1,v2);}
inline void glActiveProgramEXT(GLuint program)const{(this->*(this->m_ptr_glActiveProgramEXT))(program);}
inline void glDeleteVertexArrays(GLsizei n,const GLuint* arrays)const{(this->*(this->m_ptr_glDeleteVertexArrays))(n,arrays);}
inline void glTextureParameterfEXT(GLuint texture,GLenum target,GLenum pname,GLfloat param)const{(this->*(this->m_ptr_glTextureParameterfEXT))(texture,target,pname,param);}
inline void glColorSubTable(GLenum target,GLsizei start,GLsizei count,GLenum format,GLenum type,const GLvoid* data)const{(this->*(this->m_ptr_glColorSubTable))(target,start,count,format,type,data);}
inline GLint glGetFragDataIndex(GLuint program,const GLchar* name)const{return (this->*(this->m_ptr_glGetFragDataIndex))(program,name);}
inline void glColor3sv(const GLshort* v)const{(this->*(this->m_ptr_glColor3sv))(v);}
inline void glPolygonOffsetEXT(GLfloat factor,GLfloat bias)const{(this->*(this->m_ptr_glPolygonOffsetEXT))(factor,bias);}
inline void glPointParameterfEXT(GLenum pname,GLfloat param)const{(this->*(this->m_ptr_glPointParameterfEXT))(pname,param);}
inline void glCopyTexImage1DEXT(GLenum target,GLint level,GLenum internalformat,GLint x,GLint y,GLsizei width,GLint border)const{(this->*(this->m_ptr_glCopyTexImage1DEXT))(target,level,internalformat,x,y,width,border);}
inline void glVertex4sv(const GLshort* v)const{(this->*(this->m_ptr_glVertex4sv))(v);}
inline void glMatrixMultfEXT(GLenum mode,const GLfloat* m)const{(this->*(this->m_ptr_glMatrixMultfEXT))(mode,m);}
inline void glCompressedTextureSubImage3DEXT(GLuint texture,GLenum target,GLint level,GLint xoffset,GLint yoffset,GLint zoffset,GLsizei width,GLsizei height,GLsizei depth,GLenum format,GLsizei imageSize,const void* bits)const{(this->*(this->m_ptr_glCompressedTextureSubImage3DEXT))(texture,target,level,xoffset,yoffset,zoffset,width,height,depth,format,imageSize,bits);}
inline void glVertexAttribL3dvEXT(GLuint index,const GLdouble* v)const{(this->*(this->m_ptr_glVertexAttribL3dvEXT))(index,v);}
inline void glMultiTexCoordP4ui(GLenum texture,GLenum type,GLuint coords)const{(this->*(this->m_ptr_glMultiTexCoordP4ui))(texture,type,coords);}
inline void glGetTextureLevelParameterivEXT(GLuint texture,GLenum target,GLint level,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetTextureLevelParameterivEXT))(texture,target,level,pname,params);}
inline void glDeleteFramebuffers(GLsizei n,const GLuint* framebuffers)const{(this->*(this->m_ptr_glDeleteFramebuffers))(n,framebuffers);}
inline void glDrawArrays(GLenum mode,GLint first,GLsizei count)const{(this->*(this->m_ptr_glDrawArrays))(mode,first,count);}
inline void glGetTransformFeedbackiv(GLuint xfb,GLenum pname,GLint* param)const{(this->*(this->m_ptr_glGetTransformFeedbackiv))(xfb,pname,param);}
inline void glClear(GLbitfield mask)const{(this->*(this->m_ptr_glClear))(mask);}
inline void glVertexAttribP2ui(GLuint index,GLenum type,GLboolean normalized,GLuint value)const{(this->*(this->m_ptr_glVertexAttribP2ui))(index,type,normalized,value);}
inline void glTexCoord1s(GLshort s)const{(this->*(this->m_ptr_glTexCoord1s))(s);}
inline void glProgramUniform3iEXT(GLuint program,GLint location,GLint v0,GLint v1,GLint v2)const{(this->*(this->m_ptr_glProgramUniform3iEXT))(program,location,v0,v1,v2);}
inline void glTranslatef(GLfloat x,GLfloat y,GLfloat z)const{(this->*(this->m_ptr_glTranslatef))(x,y,z);}
inline void glVertexAttrib4Nub(GLuint index,GLubyte x,GLubyte y,GLubyte z,GLubyte w)const{(this->*(this->m_ptr_glVertexAttrib4Nub))(index,x,y,z,w);}
inline void glTranslated(GLdouble x,GLdouble y,GLdouble z)const{(this->*(this->m_ptr_glTranslated))(x,y,z);}
inline void glSamplerParameterIiv(GLuint sampler,GLenum pname,const GLint* param)const{(this->*(this->m_ptr_glSamplerParameterIiv))(sampler,pname,param);}
inline void glDrawElementsIndirect(GLenum mode,GLenum type,const void* indirect)const{(this->*(this->m_ptr_glDrawElementsIndirect))(mode,type,indirect);}
inline GLboolean glIsRenderbufferEXT(GLuint renderbuffer)const{return (this->*(this->m_ptr_glIsRenderbufferEXT))(renderbuffer);}
inline void glGetInvariantFloatvEXT(GLuint id,GLenum value,GLfloat* data)const{(this->*(this->m_ptr_glGetInvariantFloatvEXT))(id,value,data);}
inline void glSecondaryColor3bv(const GLbyte* v)const{(this->*(this->m_ptr_glSecondaryColor3bv))(v);}
inline void glMatrixMultTransposedEXT(GLenum mode,const GLdouble* m)const{(this->*(this->m_ptr_glMatrixMultTransposedEXT))(mode,m);}
inline void glGetQueryObjecti64v(GLuint id,GLenum pname,GLint64* params)const{(this->*(this->m_ptr_glGetQueryObjecti64v))(id,pname,params);}
inline GLboolean glIsRenderbuffer(GLuint renderbuffer)const{return (this->*(this->m_ptr_glIsRenderbuffer))(renderbuffer);}
inline void glVertex3iv(const GLint* v)const{(this->*(this->m_ptr_glVertex3iv))(v);}
inline void glTexGenfv(GLenum coord,GLenum pname,const GLfloat* params)const{(this->*(this->m_ptr_glTexGenfv))(coord,pname,params);}
inline void glBindVertexBuffers(GLuint first,GLsizei count,const GLuint* buffers,const GLintptr* offsets,const GLsizei* strides)const{(this->*(this->m_ptr_glBindVertexBuffers))(first,count,buffers,offsets,strides);}
inline void glMateriali(GLenum face,GLenum pname,GLint param)const{(this->*(this->m_ptr_glMateriali))(face,pname,param);}
inline GLboolean glIsVertexArray(GLuint array)const{return (this->*(this->m_ptr_glIsVertexArray))(array);}
inline void glDisableVertexAttribArray(GLuint index)const{(this->*(this->m_ptr_glDisableVertexAttribArray))(index);}
inline void glBlitNamedFramebuffer(GLuint readFramebuffer,GLuint drawFramebuffer,GLint srcX0,GLint srcY0,GLint srcX1,GLint srcY1,GLint dstX0,GLint dstY0,GLint dstX1,GLint dstY1,GLbitfield mask,GLenum filter)const{(this->*(this->m_ptr_glBlitNamedFramebuffer))(readFramebuffer,drawFramebuffer,srcX0,srcY0,srcX1,srcY1,dstX0,dstY0,dstX1,dstY1,mask,filter);}
inline void glMatrixLoadTransposefEXT(GLenum mode,const GLfloat* m)const{(this->*(this->m_ptr_glMatrixLoadTransposefEXT))(mode,m);}
inline void glMultiTexGenfEXT(GLenum texunit,GLenum coord,GLenum pname,GLfloat param)const{(this->*(this->m_ptr_glMultiTexGenfEXT))(texunit,coord,pname,param);}
inline void glShaderStorageBlockBinding(GLuint program,GLuint storageBlockIndex,GLuint storageBlockBinding)const{(this->*(this->m_ptr_glShaderStorageBlockBinding))(program,storageBlockIndex,storageBlockBinding);}
inline void glMaterialf(GLenum face,GLenum pname,GLfloat param)const{(this->*(this->m_ptr_glMaterialf))(face,pname,param);}
inline GLenum glCheckNamedFramebufferStatusEXT(GLuint framebuffer,GLenum target)const{return (this->*(this->m_ptr_glCheckNamedFramebufferStatusEXT))(framebuffer,target);}
inline void glVertexArrayVertexAttribFormatEXT(GLuint vaobj,GLuint attribindex,GLint size,GLenum type,GLboolean normalized,GLuint relativeoffset)const{(this->*(this->m_ptr_glVertexArrayVertexAttribFormatEXT))(vaobj,attribindex,size,type,normalized,relativeoffset);}
inline void glDeleteVertexShaderEXT(GLuint id)const{(this->*(this->m_ptr_glDeleteVertexShaderEXT))(id);}
inline void glTexImage3DEXT(GLenum target,GLint level,GLenum internalformat,GLsizei width,GLsizei height,GLsizei depth,GLint border,GLenum format,GLenum type,const void* pixels)const{(this->*(this->m_ptr_glTexImage3DEXT))(target,level,internalformat,width,height,depth,border,format,type,pixels);}
inline void glTextureStorage1D(GLuint texture,GLsizei levels,GLenum internalformat,GLsizei width)const{(this->*(this->m_ptr_glTextureStorage1D))(texture,levels,internalformat,width);}
inline void glBinormal3sEXT(GLshort bx,GLshort by,GLshort bz)const{(this->*(this->m_ptr_glBinormal3sEXT))(bx,by,bz);}
inline void glGetProgramInterfaceiv(GLuint program,GLenum programInterface,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetProgramInterfaceiv))(program,programInterface,pname,params);}
inline void glTexCoordPointerEXT(GLint size,GLenum type,GLsizei stride,GLsizei count,const void* pointer)const{(this->*(this->m_ptr_glTexCoordPointerEXT))(size,type,stride,count,pointer);}
inline void glMultiTexGeniEXT(GLenum texunit,GLenum coord,GLenum pname,GLint param)const{(this->*(this->m_ptr_glMultiTexGeniEXT))(texunit,coord,pname,param);}
inline void glNamedProgramStringEXT(GLuint program,GLenum target,GLenum format,GLsizei len,const void* string)const{(this->*(this->m_ptr_glNamedProgramStringEXT))(program,target,format,len,string);}
inline void* glMapNamedBuffer(GLuint buffer,GLenum access)const{return (this->*(this->m_ptr_glMapNamedBuffer))(buffer,access);}
inline void glGetMinmaxParameteriv(GLenum target,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetMinmaxParameteriv))(target,pname,params);}
inline void glGetnUniformdv(GLuint program,GLint location,GLsizei bufSize,GLdouble* params)const{(this->*(this->m_ptr_glGetnUniformdv))(program,location,bufSize,params);}
inline void glGetTextureSubImage(GLuint texture,GLint level,GLint xoffset,GLint yoffset,GLint zoffset,GLsizei width,GLsizei height,GLsizei depth,GLenum format,GLenum type,GLsizei bufSize,void* pixels)const{(this->*(this->m_ptr_glGetTextureSubImage))(texture,level,xoffset,yoffset,zoffset,width,height,depth,format,type,bufSize,pixels);}
inline void glBinormal3fEXT(GLfloat bx,GLfloat by,GLfloat bz)const{(this->*(this->m_ptr_glBinormal3fEXT))(bx,by,bz);}
inline void glPolygonOffset(GLfloat factor,GLfloat units)const{(this->*(this->m_ptr_glPolygonOffset))(factor,units);}
inline void glFlushMappedNamedBufferRangeEXT(GLuint buffer,GLintptr offset,GLsizeiptr length)const{(this->*(this->m_ptr_glFlushMappedNamedBufferRangeEXT))(buffer,offset,length);}
inline void glGetVertexAttribIiv(GLuint index,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetVertexAttribIiv))(index,pname,params);}
inline void glSecondaryColor3ubvEXT(const GLubyte* v)const{(this->*(this->m_ptr_glSecondaryColor3ubvEXT))(v);}
inline void glPatchParameteri(GLenum pname,GLint value)const{(this->*(this->m_ptr_glPatchParameteri))(pname,value);}
inline void glGetBufferParameteri64v(GLenum target,GLenum pname,GLint64* params)const{(this->*(this->m_ptr_glGetBufferParameteri64v))(target,pname,params);}
inline void glMap1d(GLenum target,GLdouble u1,GLdouble u2,GLint stride,GLint order,const GLdouble* points)const{(this->*(this->m_ptr_glMap1d))(target,u1,u2,stride,order,points);}
inline void glMap1f(GLenum target,GLfloat u1,GLfloat u2,GLint stride,GLint order,const GLfloat* points)const{(this->*(this->m_ptr_glMap1f))(target,u1,u2,stride,order,points);}
inline void glVertexArrayVertexBindingDivisorEXT(GLuint vaobj,GLuint bindingindex,GLuint divisor)const{(this->*(this->m_ptr_glVertexArrayVertexBindingDivisorEXT))(vaobj,bindingindex,divisor);}
inline void glGetConvolutionParameteriv(GLenum target,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetConvolutionParameteriv))(target,pname,params);}
inline void glGetNamedFramebufferAttachmentParameteriv(GLuint framebuffer,GLenum attachment,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetNamedFramebufferAttachmentParameteriv))(framebuffer,attachment,pname,params);}
inline void glGetnSeparableFilter(GLenum target,GLenum format,GLenum type,GLsizei rowBufSize,void* row,GLsizei columnBufSize,void* column,void* span)const{(this->*(this->m_ptr_glGetnSeparableFilter))(target,format,type,rowBufSize,row,columnBufSize,column,span);}
inline void glGetHistogramParameterfvEXT(GLenum target,GLenum pname,GLfloat* params)const{(this->*(this->m_ptr_glGetHistogramParameterfvEXT))(target,pname,params);}
inline void glTextureStorage2DEXT(GLuint texture,GLenum target,GLsizei levels,GLenum internalformat,GLsizei width,GLsizei height)const{(this->*(this->m_ptr_glTextureStorage2DEXT))(texture,target,levels,internalformat,width,height);}
inline void glVertexArrayFogCoordOffsetEXT(GLuint vaobj,GLuint buffer,GLenum type,GLsizei stride,GLintptr offset)const{(this->*(this->m_ptr_glVertexArrayFogCoordOffsetEXT))(vaobj,buffer,type,stride,offset);}
inline void glLighti(GLenum light,GLenum pname,GLint param)const{(this->*(this->m_ptr_glLighti))(light,pname,param);}
inline void glLightf(GLenum light,GLenum pname,GLfloat param)const{(this->*(this->m_ptr_glLightf))(light,pname,param);}
inline void glClientAttribDefaultEXT(GLbitfield mask)const{(this->*(this->m_ptr_glClientAttribDefaultEXT))(mask);}
inline void glStencilFuncSeparate(GLenum face,GLenum func,GLint ref,GLuint mask)const{(this->*(this->m_ptr_glStencilFuncSeparate))(face,func,ref,mask);}
inline void glProgramUniform2iEXT(GLuint program,GLint location,GLint v0,GLint v1)const{(this->*(this->m_ptr_glProgramUniform2iEXT))(program,location,v0,v1);}
inline void glSecondaryColor3usv(const GLushort* v)const{(this->*(this->m_ptr_glSecondaryColor3usv))(v);}
inline GLboolean glUnmapNamedBufferEXT(GLuint buffer)const{return (this->*(this->m_ptr_glUnmapNamedBufferEXT))(buffer);}
inline void glGetTransformFeedbacki_v(GLuint xfb,GLenum pname,GLuint index,GLint* param)const{(this->*(this->m_ptr_glGetTransformFeedbacki_v))(xfb,pname,index,param);}
inline void glGetFloati_vEXT(GLenum pname,GLuint index,GLfloat* params)const{(this->*(this->m_ptr_glGetFloati_vEXT))(pname,index,params);}
inline void glMultiTexEnvivEXT(GLenum texunit,GLenum target,GLenum pname,const GLint* params)const{(this->*(this->m_ptr_glMultiTexEnvivEXT))(texunit,target,pname,params);}
inline void glSecondaryColor3uiEXT(GLuint red,GLuint green,GLuint blue)const{(this->*(this->m_ptr_glSecondaryColor3uiEXT))(red,green,blue);}
inline void glCompressedTextureImage2DEXT(GLuint texture,GLenum target,GLint level,GLenum internalformat,GLsizei width,GLsizei height,GLint border,GLsizei imageSize,const void* bits)const{(this->*(this->m_ptr_glCompressedTextureImage2DEXT))(texture,target,level,internalformat,width,height,border,imageSize,bits);}
inline void glUniform2i(GLint location,GLint v0,GLint v1)const{(this->*(this->m_ptr_glUniform2i))(location,v0,v1);}
inline void glMapGrid2d(GLint un,GLdouble u1,GLdouble u2,GLint vn,GLdouble v1,GLdouble v2)const{(this->*(this->m_ptr_glMapGrid2d))(un,u1,u2,vn,v1,v2);}
inline void glUniform2d(GLint location,GLdouble x,GLdouble y)const{(this->*(this->m_ptr_glUniform2d))(location,x,y);}
inline void glTexCoordP4ui(GLenum type,GLuint coords)const{(this->*(this->m_ptr_glTexCoordP4ui))(type,coords);}
inline void glFramebufferTextureFaceEXT(GLenum target,GLenum attachment,GLuint texture,GLint level,GLenum face)const{(this->*(this->m_ptr_glFramebufferTextureFaceEXT))(target,attachment,texture,level,face);}
inline void glFramebufferTextureLayer(GLenum target,GLenum attachment,GLuint texture,GLint level,GLint layer)const{(this->*(this->m_ptr_glFramebufferTextureLayer))(target,attachment,texture,level,layer);}
inline void glGetVertexArrayPointeri_vEXT(GLuint vaobj,GLuint index,GLenum pname,void** param)const{(this->*(this->m_ptr_glGetVertexArrayPointeri_vEXT))(vaobj,index,pname,param);}
inline void glProgramUniformMatrix2x3fvEXT(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLfloat* value)const{(this->*(this->m_ptr_glProgramUniformMatrix2x3fvEXT))(program,location,count,transpose,value);}
inline void glBinormal3bEXT(GLbyte bx,GLbyte by,GLbyte bz)const{(this->*(this->m_ptr_glBinormal3bEXT))(bx,by,bz);}
inline void glProgramUniform2fv(GLuint program,GLint location,GLsizei count,const GLfloat* value)const{(this->*(this->m_ptr_glProgramUniform2fv))(program,location,count,value);}
inline void glCopyMultiTexSubImage3DEXT(GLenum texunit,GLenum target,GLint level,GLint xoffset,GLint yoffset,GLint zoffset,GLint x,GLint y,GLsizei width,GLsizei height)const{(this->*(this->m_ptr_glCopyMultiTexSubImage3DEXT))(texunit,target,level,xoffset,yoffset,zoffset,x,y,width,height);}
inline void glProgramUniformMatrix2x4dv(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLdouble* value)const{(this->*(this->m_ptr_glProgramUniformMatrix2x4dv))(program,location,count,transpose,value);}
inline void glDrawArraysEXT(GLenum mode,GLint first,GLsizei count)const{(this->*(this->m_ptr_glDrawArraysEXT))(mode,first,count);}
inline void glBlendEquationEXT(GLenum mode)const{(this->*(this->m_ptr_glBlendEquationEXT))(mode);}
inline void glCopyTextureSubImage2DEXT(GLuint texture,GLenum target,GLint level,GLint xoffset,GLint yoffset,GLint x,GLint y,GLsizei width,GLsizei height)const{(this->*(this->m_ptr_glCopyTextureSubImage2DEXT))(texture,target,level,xoffset,yoffset,x,y,width,height);}
inline void glTexEnvf(GLenum target,GLenum pname,GLfloat param)const{(this->*(this->m_ptr_glTexEnvf))(target,pname,param);}
inline void glGetInteger64i_v(GLenum target,GLuint index,GLint64* data)const{(this->*(this->m_ptr_glGetInteger64i_v))(target,index,data);}
inline void glGetHistogramParameterfv(GLenum target,GLenum pname,GLfloat* params)const{(this->*(this->m_ptr_glGetHistogramParameterfv))(target,pname,params);}
inline void glTexEnvi(GLenum target,GLenum pname,GLint param)const{(this->*(this->m_ptr_glTexEnvi))(target,pname,param);}
inline void glMultiTexCoord1iv(GLenum target,const GLint* v)const{(this->*(this->m_ptr_glMultiTexCoord1iv))(target,v);}
inline GLboolean glIsEnabledi(GLenum target,GLuint index)const{return (this->*(this->m_ptr_glIsEnabledi))(target,index);}
inline void glMatrixTranslatedEXT(GLenum mode,GLdouble x,GLdouble y,GLdouble z)const{(this->*(this->m_ptr_glMatrixTranslatedEXT))(mode,x,y,z);}
inline void glBinormal3dvEXT(const GLdouble* v)const{(this->*(this->m_ptr_glBinormal3dvEXT))(v);}
inline GLsync glImportSyncEXT(GLenum external_sync_type,GLintptr external_sync,GLbitfield flags)const{return (this->*(this->m_ptr_glImportSyncEXT))(external_sync_type,external_sync,flags);}
inline void glGetMapiv(GLenum target,GLenum query,GLint* v)const{(this->*(this->m_ptr_glGetMapiv))(target,query,v);}
inline void glMultiTexCoord4sv(GLenum target,const GLshort* v)const{(this->*(this->m_ptr_glMultiTexCoord4sv))(target,v);}
inline void glProgramUniformMatrix3fv(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLfloat* value)const{(this->*(this->m_ptr_glProgramUniformMatrix3fv))(program,location,count,transpose,value);}
inline void glObjectPtrLabel(const void* ptr,GLsizei length,const GLchar* label)const{(this->*(this->m_ptr_glObjectPtrLabel))(ptr,length,label);}
inline GLuint glGetDebugMessageLog(GLuint count,GLsizei bufSize,GLenum* sources,GLenum* types,GLuint* ids,GLenum* severities,GLsizei* lengths,GLchar* messageLog)const{return (this->*(this->m_ptr_glGetDebugMessageLog))(count,bufSize,sources,types,ids,severities,lengths,messageLog);}
inline void glBindFragDataLocation(GLuint program,GLuint color,const GLchar* name)const{(this->*(this->m_ptr_glBindFragDataLocation))(program,color,name);}
inline void glTangent3ivEXT(const GLint* v)const{(this->*(this->m_ptr_glTangent3ivEXT))(v);}
inline void glSecondaryColor3ubv(const GLubyte* v)const{(this->*(this->m_ptr_glSecondaryColor3ubv))(v);}
inline void glMultiTexCoord3iv(GLenum target,const GLint* v)const{(this->*(this->m_ptr_glMultiTexCoord3iv))(target,v);}
inline void glLightModelf(GLenum pname,GLfloat param)const{(this->*(this->m_ptr_glLightModelf))(pname,param);}
inline void glMultiTexSubImage2DEXT(GLenum texunit,GLenum target,GLint level,GLint xoffset,GLint yoffset,GLsizei width,GLsizei height,GLenum format,GLenum type,const void* pixels)const{(this->*(this->m_ptr_glMultiTexSubImage2DEXT))(texunit,target,level,xoffset,yoffset,width,height,format,type,pixels);}
inline void glTangent3dvEXT(const GLdouble* v)const{(this->*(this->m_ptr_glTangent3dvEXT))(v);}
inline void glLightModeli(GLenum pname,GLint param)const{(this->*(this->m_ptr_glLightModeli))(pname,param);}
inline void glWindowPos3iv(const GLint* v)const{(this->*(this->m_ptr_glWindowPos3iv))(v);}
inline void glMultiTexCoordP1uiv(GLenum texture,GLenum type,const GLuint* coords)const{(this->*(this->m_ptr_glMultiTexCoordP1uiv))(texture,type,coords);}
inline void glMultiDrawElementsIndirect(GLenum mode,GLenum type,const void* indirect,GLsizei drawcount,GLsizei stride)const{(this->*(this->m_ptr_glMultiDrawElementsIndirect))(mode,type,indirect,drawcount,stride);}
inline void glProgramUniform1dEXT(GLuint program,GLint location,GLdouble x)const{(this->*(this->m_ptr_glProgramUniform1dEXT))(program,location,x);}
inline void glCallLists(GLsizei n,GLenum type,const GLvoid* lists)const{(this->*(this->m_ptr_glCallLists))(n,type,lists);}
inline void glTexCoord3i(GLint s,GLint t,GLint r)const{(this->*(this->m_ptr_glTexCoord3i))(s,t,r);}
inline void glVertexAttribI3uiv(GLuint index,const GLuint* v)const{(this->*(this->m_ptr_glVertexAttribI3uiv))(index,v);}
inline void glPushDebugGroup(GLenum source,GLuint id,GLsizei length,const GLchar* message)const{(this->*(this->m_ptr_glPushDebugGroup))(source,id,length,message);}
inline void glTexCoord3f(GLfloat s,GLfloat t,GLfloat r)const{(this->*(this->m_ptr_glTexCoord3f))(s,t,r);}
inline void glTexCoord3d(GLdouble s,GLdouble t,GLdouble r)const{(this->*(this->m_ptr_glTexCoord3d))(s,t,r);}
inline void glGetNamedBufferPointervEXT(GLuint buffer,GLenum pname,void** params)const{(this->*(this->m_ptr_glGetNamedBufferPointervEXT))(buffer,pname,params);}
inline void glTexCoord3s(GLshort s,GLshort t,GLshort r)const{(this->*(this->m_ptr_glTexCoord3s))(s,t,r);}
inline void glMatrixMultTransposefEXT(GLenum mode,const GLfloat* m)const{(this->*(this->m_ptr_glMatrixMultTransposefEXT))(mode,m);}
inline void glGetActiveUniformBlockiv(GLuint program,GLuint uniformBlockIndex,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetActiveUniformBlockiv))(program,uniformBlockIndex,pname,params);}
inline GLboolean glAreTexturesResident(GLsizei n,const GLuint* textures,GLboolean* residences)const{return (this->*(this->m_ptr_glAreTexturesResident))(n,textures,residences);}
inline void glVertexAttribI4iEXT(GLuint index,GLint x,GLint y,GLint z,GLint w)const{(this->*(this->m_ptr_glVertexAttribI4iEXT))(index,x,y,z,w);}
inline void glRasterPos4sv(const GLshort* v)const{(this->*(this->m_ptr_glRasterPos4sv))(v);}
inline void glColor4s(GLshort red,GLshort green,GLshort blue,GLshort alpha)const{(this->*(this->m_ptr_glColor4s))(red,green,blue,alpha);}
inline void glProgramUniformMatrix2x3dvEXT(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLdouble* value)const{(this->*(this->m_ptr_glProgramUniformMatrix2x3dvEXT))(program,location,count,transpose,value);}
inline void glBindVertexArray(GLuint array)const{(this->*(this->m_ptr_glBindVertexArray))(array);}
inline void glColor4b(GLbyte red,GLbyte green,GLbyte blue,GLbyte alpha)const{(this->*(this->m_ptr_glColor4b))(red,green,blue,alpha);}
inline void glColor4f(GLfloat red,GLfloat green,GLfloat blue,GLfloat alpha)const{(this->*(this->m_ptr_glColor4f))(red,green,blue,alpha);}
inline void glColor4d(GLdouble red,GLdouble green,GLdouble blue,GLdouble alpha)const{(this->*(this->m_ptr_glColor4d))(red,green,blue,alpha);}
inline void glColor4i(GLint red,GLint green,GLint blue,GLint alpha)const{(this->*(this->m_ptr_glColor4i))(red,green,blue,alpha);}
inline void glNamedBufferSubData(GLuint buffer,GLintptr offset,GLsizeiptr size,const void* data)const{(this->*(this->m_ptr_glNamedBufferSubData))(buffer,offset,size,data);}
inline void glGetMultiTexParameterIivEXT(GLenum texunit,GLenum target,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetMultiTexParameterIivEXT))(texunit,target,pname,params);}
inline void glVertex2dv(const GLdouble* v)const{(this->*(this->m_ptr_glVertex2dv))(v);}
inline void glBindFramebuffer(GLenum target,GLuint framebuffer)const{(this->*(this->m_ptr_glBindFramebuffer))(target,framebuffer);}
inline void glProgramUniform4ivEXT(GLuint program,GLint location,GLsizei count,const GLint* value)const{(this->*(this->m_ptr_glProgramUniform4ivEXT))(program,location,count,value);}
inline void glRectfv(const GLfloat* v1,const GLfloat* v2)const{(this->*(this->m_ptr_glRectfv))(v1,v2);}
inline void glCopyMultiTexImage1DEXT(GLenum texunit,GLenum target,GLint level,GLenum internalformat,GLint x,GLint y,GLsizei width,GLint border)const{(this->*(this->m_ptr_glCopyMultiTexImage1DEXT))(texunit,target,level,internalformat,x,y,width,border);}
inline void glGetVertexAttribIuivEXT(GLuint index,GLenum pname,GLuint* params)const{(this->*(this->m_ptr_glGetVertexAttribIuivEXT))(index,pname,params);}
inline void glUniformMatrix2x4dv(GLint location,GLsizei count,GLboolean transpose,const GLdouble* value)const{(this->*(this->m_ptr_glUniformMatrix2x4dv))(location,count,transpose,value);}
inline GLint glGetProgramResourceLocationIndex(GLuint program,GLenum programInterface,const GLchar* name)const{return (this->*(this->m_ptr_glGetProgramResourceLocationIndex))(program,programInterface,name);}
inline void glViewport(GLint x,GLint y,GLsizei width,GLsizei height)const{(this->*(this->m_ptr_glViewport))(x,y,width,height);}
inline void glGetInvariantBooleanvEXT(GLuint id,GLenum value,GLboolean* data)const{(this->*(this->m_ptr_glGetInvariantBooleanvEXT))(id,value,data);}
inline void glTexStorage2DMultisample(GLenum target,GLsizei samples,GLenum internalformat,GLsizei width,GLsizei height,GLboolean fixedsamplelocations)const{(this->*(this->m_ptr_glTexStorage2DMultisample))(target,samples,internalformat,width,height,fixedsamplelocations);}
inline void glPixelStorex(GLenum pname,GLfixed param)const{(this->*(this->m_ptr_glPixelStorex))(pname,param);}
inline void glVertexAttribL1dvEXT(GLuint index,const GLdouble* v)const{(this->*(this->m_ptr_glVertexAttribL1dvEXT))(index,v);}
inline void glGetActiveSubroutineUniformiv(GLuint program,GLenum shadertype,GLuint index,GLenum pname,GLint* values)const{(this->*(this->m_ptr_glGetActiveSubroutineUniformiv))(program,shadertype,index,pname,values);}
inline void glTexBuffer(GLenum target,GLenum internalformat,GLuint buffer)const{(this->*(this->m_ptr_glTexBuffer))(target,internalformat,buffer);}
inline void glArrayElement(GLint i)const{(this->*(this->m_ptr_glArrayElement))(i);}
inline void glValidateProgram(GLuint program)const{(this->*(this->m_ptr_glValidateProgram))(program);}
inline void glPixelStoref(GLenum pname,GLfloat param)const{(this->*(this->m_ptr_glPixelStoref))(pname,param);}
inline void glEvalCoord1dv(const GLdouble* u)const{(this->*(this->m_ptr_glEvalCoord1dv))(u);}
inline void glMultiTexCoordP2uiv(GLenum texture,GLenum type,const GLuint* coords)const{(this->*(this->m_ptr_glMultiTexCoordP2uiv))(texture,type,coords);}
inline void glRecti(GLint x1,GLint y1,GLint x2,GLint y2)const{(this->*(this->m_ptr_glRecti))(x1,y1,x2,y2);}
inline void glRectf(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2)const{(this->*(this->m_ptr_glRectf))(x1,y1,x2,y2);}
inline void glRectd(GLdouble x1,GLdouble y1,GLdouble x2,GLdouble y2)const{(this->*(this->m_ptr_glRectd))(x1,y1,x2,y2);}
inline void glGetMultiTexGendvEXT(GLenum texunit,GLenum coord,GLenum pname,GLdouble* params)const{(this->*(this->m_ptr_glGetMultiTexGendvEXT))(texunit,coord,pname,params);}
inline void glClearNamedBufferSubDataEXT(GLuint buffer,GLenum internalformat,GLsizeiptr offset,GLsizeiptr size,GLenum format,GLenum type,const void* data)const{(this->*(this->m_ptr_glClearNamedBufferSubDataEXT))(buffer,internalformat,offset,size,format,type,data);}
inline void glBindTexture(GLenum target,GLuint texture)const{(this->*(this->m_ptr_glBindTexture))(target,texture);}
inline void glRects(GLshort x1,GLshort y1,GLshort x2,GLshort y2)const{(this->*(this->m_ptr_glRects))(x1,y1,x2,y2);}
inline void glHistogramEXT(GLenum target,GLsizei width,GLenum internalformat,GLboolean sink)const{(this->*(this->m_ptr_glHistogramEXT))(target,width,internalformat,sink);}
inline void glPixelTransformParameteriEXT(GLenum target,GLenum pname,GLint param)const{(this->*(this->m_ptr_glPixelTransformParameteriEXT))(target,pname,param);}
inline void glDetachShader(GLuint program,GLuint shader)const{(this->*(this->m_ptr_glDetachShader))(program,shader);}
inline void glUniformMatrix3x4dv(GLint location,GLsizei count,GLboolean transpose,const GLdouble* value)const{(this->*(this->m_ptr_glUniformMatrix3x4dv))(location,count,transpose,value);}
inline GLint glGetProgramResourceLocation(GLuint program,GLenum programInterface,const GLchar* name)const{return (this->*(this->m_ptr_glGetProgramResourceLocation))(program,programInterface,name);}
inline void glVertexArrayAttribLFormat(GLuint vaobj,GLuint attribindex,GLint size,GLenum type,GLuint relativeoffset)const{(this->*(this->m_ptr_glVertexArrayAttribLFormat))(vaobj,attribindex,size,type,relativeoffset);}
inline void glNamedCopyBufferSubDataEXT(GLuint readBuffer,GLuint writeBuffer,GLintptr readOffset,GLintptr writeOffset,GLsizeiptr size)const{(this->*(this->m_ptr_glNamedCopyBufferSubDataEXT))(readBuffer,writeBuffer,readOffset,writeOffset,size);}
inline void glVertexArrayVertexAttribOffsetEXT(GLuint vaobj,GLuint buffer,GLuint index,GLint size,GLenum type,GLboolean normalized,GLsizei stride,GLintptr offset)const{(this->*(this->m_ptr_glVertexArrayVertexAttribOffsetEXT))(vaobj,buffer,index,size,type,normalized,stride,offset);}
inline void glViewportIndexedfv(GLuint index,const GLfloat* v)const{(this->*(this->m_ptr_glViewportIndexedfv))(index,v);}
inline void glBindBuffersBase(GLenum target,GLuint first,GLsizei count,const GLuint* buffers)const{(this->*(this->m_ptr_glBindBuffersBase))(target,first,count,buffers);}
inline void glDrawElementsBaseVertex(GLenum mode,GLsizei count,GLenum type,const void* indices,GLint basevertex)const{(this->*(this->m_ptr_glDrawElementsBaseVertex))(mode,count,type,indices,basevertex);}
inline void glSampleCoverage(GLclampf value,GLboolean invert)const{(this->*(this->m_ptr_glSampleCoverage))(value,invert);}
inline void glClearBufferSubData(GLenum target,GLenum internalformat,GLintptr offset,GLsizeiptr size,GLenum format,GLenum type,const void* data)const{(this->*(this->m_ptr_glClearBufferSubData))(target,internalformat,offset,size,format,type,data);}
inline void glTexStorage1D(GLenum target,GLsizei levels,GLenum internalformat,GLsizei width)const{(this->*(this->m_ptr_glTexStorage1D))(target,levels,internalformat,width);}
inline void glVertexAttribI3iEXT(GLuint index,GLint x,GLint y,GLint z)const{(this->*(this->m_ptr_glVertexAttribI3iEXT))(index,x,y,z);}
inline void glGetPixelMapxv(GLenum map,GLint size,GLfixed* values)const{(this->*(this->m_ptr_glGetPixelMapxv))(map,size,values);}
inline void glProgramUniformMatrix2dvEXT(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLdouble* value)const{(this->*(this->m_ptr_glProgramUniformMatrix2dvEXT))(program,location,count,transpose,value);}
inline void glGetUniformiv(GLuint program,GLint location,GLint* params)const{(this->*(this->m_ptr_glGetUniformiv))(program,location,params);}
inline void glUniform4ui(GLint location,GLuint v0,GLuint v1,GLuint v2,GLuint v3)const{(this->*(this->m_ptr_glUniform4ui))(location,v0,v1,v2,v3);}
inline void glDisableVertexArrayAttribEXT(GLuint vaobj,GLuint index)const{(this->*(this->m_ptr_glDisableVertexArrayAttribEXT))(vaobj,index);}
inline void glTexGenf(GLenum coord,GLenum pname,GLfloat param)const{(this->*(this->m_ptr_glTexGenf))(coord,pname,param);}
inline void glTexGend(GLenum coord,GLenum pname,GLdouble param)const{(this->*(this->m_ptr_glTexGend))(coord,pname,param);}
inline void glTexGeni(GLenum coord,GLenum pname,GLint param)const{(this->*(this->m_ptr_glTexGeni))(coord,pname,param);}
inline void glDeleteFramebuffersEXT(GLsizei n,const GLuint* framebuffers)const{(this->*(this->m_ptr_glDeleteFramebuffersEXT))(n,framebuffers);}
inline void glResetMinmaxEXT(GLenum target)const{(this->*(this->m_ptr_glResetMinmaxEXT))(target);}
inline void glEnableVariantClientStateEXT(GLuint id)const{(this->*(this->m_ptr_glEnableVariantClientStateEXT))(id);}
inline void glScissorIndexed(GLuint index,GLint left,GLint bottom,GLsizei width,GLsizei height)const{(this->*(this->m_ptr_glScissorIndexed))(index,left,bottom,width,height);}
inline void glGetInvariantIntegervEXT(GLuint id,GLenum value,GLint* data)const{(this->*(this->m_ptr_glGetInvariantIntegervEXT))(id,value,data);}
inline void glGenFramebuffersEXT(GLsizei n,GLuint* framebuffers)const{(this->*(this->m_ptr_glGenFramebuffersEXT))(n,framebuffers);}
inline void glVertexArrayColorOffsetEXT(GLuint vaobj,GLuint buffer,GLint size,GLenum type,GLsizei stride,GLintptr offset)const{(this->*(this->m_ptr_glVertexArrayColorOffsetEXT))(vaobj,buffer,size,type,stride,offset);}
inline void glVertexWeightfEXT(GLfloat weight)const{(this->*(this->m_ptr_glVertexWeightfEXT))(weight);}
inline void glRasterPos4dv(const GLdouble* v)const{(this->*(this->m_ptr_glRasterPos4dv))(v);}
inline void glRasterPos2dv(const GLdouble* v)const{(this->*(this->m_ptr_glRasterPos2dv))(v);}
inline void glGetVariantPointervEXT(GLuint id,GLenum value,void** data)const{(this->*(this->m_ptr_glGetVariantPointervEXT))(id,value,data);}
inline void* glMapNamedBufferRangeEXT(GLuint buffer,GLintptr offset,GLsizeiptr length,GLbitfield access)const{return (this->*(this->m_ptr_glMapNamedBufferRangeEXT))(buffer,offset,length,access);}
inline GLuint glCreateShaderProgramv(GLenum type,GLsizei count,const GLchar*const* strings)const{return (this->*(this->m_ptr_glCreateShaderProgramv))(type,count,strings);}
inline void glGetQueryObjectiv(GLuint id,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetQueryObjectiv))(id,pname,params);}
inline void glGenerateMipmap(GLenum target)const{(this->*(this->m_ptr_glGenerateMipmap))(target);}
inline void glCompressedTextureSubImage2D(GLuint texture,GLint level,GLint xoffset,GLint yoffset,GLsizei width,GLsizei height,GLenum format,GLsizei imageSize,const void* data)const{(this->*(this->m_ptr_glCompressedTextureSubImage2D))(texture,level,xoffset,yoffset,width,height,format,imageSize,data);}
inline void glNamedRenderbufferStorageMultisampleEXT(GLuint renderbuffer,GLsizei samples,GLenum internalformat,GLsizei width,GLsizei height)const{(this->*(this->m_ptr_glNamedRenderbufferStorageMultisampleEXT))(renderbuffer,samples,internalformat,width,height);}
inline void glPolygonOffsetClampEXT(GLfloat factor,GLfloat units,GLfloat clamp)const{(this->*(this->m_ptr_glPolygonOffsetClampEXT))(factor,units,clamp);}
inline void glDeleteLists(GLuint list,GLsizei range)const{(this->*(this->m_ptr_glDeleteLists))(list,range);}
inline void glTexCoord2d(GLdouble s,GLdouble t)const{(this->*(this->m_ptr_glTexCoord2d))(s,t);}
inline void glPointParameteri(GLenum pname,GLint param)const{(this->*(this->m_ptr_glPointParameteri))(pname,param);}
inline void glTexCoord2f(GLfloat s,GLfloat t)const{(this->*(this->m_ptr_glTexCoord2f))(s,t);}
inline void glColor4iv(const GLint* v)const{(this->*(this->m_ptr_glColor4iv))(v);}
inline GLboolean glUnmapBuffer(GLenum target)const{return (this->*(this->m_ptr_glUnmapBuffer))(target);}
inline void glSampleMaskEXT(GLclampf value,GLboolean invert)const{(this->*(this->m_ptr_glSampleMaskEXT))(value,invert);}
inline void glTexCoord2i(GLint s,GLint t)const{(this->*(this->m_ptr_glTexCoord2i))(s,t);}
inline void glPointParameterf(GLenum pname,GLfloat param)const{(this->*(this->m_ptr_glPointParameterf))(pname,param);}
inline void glGetVertexArrayiv(GLuint vaobj,GLenum pname,GLint* param)const{(this->*(this->m_ptr_glGetVertexArrayiv))(vaobj,pname,param);}
inline void glTexCoord2s(GLshort s,GLshort t)const{(this->*(this->m_ptr_glTexCoord2s))(s,t);}
inline void glTextureParameterIuivEXT(GLuint texture,GLenum target,GLenum pname,const GLuint* params)const{(this->*(this->m_ptr_glTextureParameterIuivEXT))(texture,target,pname,params);}
inline void glTexCoord4dv(const GLdouble* v)const{(this->*(this->m_ptr_glTexCoord4dv))(v);}
inline void glNamedFramebufferTextureFaceEXT(GLuint framebuffer,GLenum attachment,GLuint texture,GLint level,GLenum face)const{(this->*(this->m_ptr_glNamedFramebufferTextureFaceEXT))(framebuffer,attachment,texture,level,face);}
inline void glNormal3dv(const GLdouble* v)const{(this->*(this->m_ptr_glNormal3dv))(v);}
inline void glReleaseShaderCompiler()const{(this->*(this->m_ptr_glReleaseShaderCompiler))();}
inline void glTexCoord1dv(const GLdouble* v)const{(this->*(this->m_ptr_glTexCoord1dv))(v);}
inline void glReadPixels(GLint x,GLint y,GLsizei width,GLsizei height,GLenum format,GLenum type,GLvoid* pixels)const{(this->*(this->m_ptr_glReadPixels))(x,y,width,height,format,type,pixels);}
inline void glVertexAttribI3iv(GLuint index,const GLint* v)const{(this->*(this->m_ptr_glVertexAttribI3iv))(index,v);}
inline void glMultiTexSubImage3DEXT(GLenum texunit,GLenum target,GLint level,GLint xoffset,GLint yoffset,GLint zoffset,GLsizei width,GLsizei height,GLsizei depth,GLenum format,GLenum type,const void* pixels)const{(this->*(this->m_ptr_glMultiTexSubImage3DEXT))(texunit,target,level,xoffset,yoffset,zoffset,width,height,depth,format,type,pixels);}
inline void glShadeModel(GLenum mode)const{(this->*(this->m_ptr_glShadeModel))(mode);}
inline void glMapGrid1d(GLint un,GLdouble u1,GLdouble u2)const{(this->*(this->m_ptr_glMapGrid1d))(un,u1,u2);}
inline void glGetHistogramParameterivEXT(GLenum target,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetHistogramParameterivEXT))(target,pname,params);}
inline void glMapGrid1f(GLint un,GLfloat u1,GLfloat u2)const{(this->*(this->m_ptr_glMapGrid1f))(un,u1,u2);}
inline void glVertexAttribI1iEXT(GLuint index,GLint x)const{(this->*(this->m_ptr_glVertexAttribI1iEXT))(index,x);}
inline void glGetDoublei_vEXT(GLenum pname,GLuint index,GLdouble* params)const{(this->*(this->m_ptr_glGetDoublei_vEXT))(pname,index,params);}
inline void glFogCoordfEXT(GLfloat coord)const{(this->*(this->m_ptr_glFogCoordfEXT))(coord);}
inline void glMultiTexBufferEXT(GLenum texunit,GLenum target,GLenum internalformat,GLuint buffer)const{(this->*(this->m_ptr_glMultiTexBufferEXT))(texunit,target,internalformat,buffer);}
inline void glInvalidateNamedFramebufferData(GLuint framebuffer,GLsizei numAttachments,const GLenum* attachments)const{(this->*(this->m_ptr_glInvalidateNamedFramebufferData))(framebuffer,numAttachments,attachments);}
inline void glRectiv(const GLint* v1,const GLint* v2)const{(this->*(this->m_ptr_glRectiv))(v1,v2);}
inline void glColorP4ui(GLenum type,GLuint color)const{(this->*(this->m_ptr_glColorP4ui))(type,color);}
inline void glUseProgramStages(GLuint pipeline,GLbitfield stages,GLuint program)const{(this->*(this->m_ptr_glUseProgramStages))(pipeline,stages,program);}
inline void glRasterPos3dv(const GLdouble* v)const{(this->*(this->m_ptr_glRasterPos3dv))(v);}
inline void glProgramUniform2dEXT(GLuint program,GLint location,GLdouble x,GLdouble y)const{(this->*(this->m_ptr_glProgramUniform2dEXT))(program,location,x,y);}
inline void glVertexAttribI4iv(GLuint index,const GLint* v)const{(this->*(this->m_ptr_glVertexAttribI4iv))(index,v);}
inline void glNamedFramebufferDrawBuffer(GLuint framebuffer,GLenum buf)const{(this->*(this->m_ptr_glNamedFramebufferDrawBuffer))(framebuffer,buf);}
inline void glColor4ubv(const GLubyte* v)const{(this->*(this->m_ptr_glColor4ubv))(v);}
inline void glGetBufferSubData(GLenum target,GLintptr offset,GLsizeiptr size,void* data)const{(this->*(this->m_ptr_glGetBufferSubData))(target,offset,size,data);}
inline void glGetVertexAttribLdv(GLuint index,GLenum pname,GLdouble* params)const{(this->*(this->m_ptr_glGetVertexAttribLdv))(index,pname,params);}
inline void glGetnUniformuiv(GLuint program,GLint location,GLsizei bufSize,GLuint* params)const{(this->*(this->m_ptr_glGetnUniformuiv))(program,location,bufSize,params);}
inline void glNamedRenderbufferStorageEXT(GLuint renderbuffer,GLenum internalformat,GLsizei width,GLsizei height)const{(this->*(this->m_ptr_glNamedRenderbufferStorageEXT))(renderbuffer,internalformat,width,height);}
inline void glTextureStorage1DEXT(GLuint texture,GLenum target,GLsizei levels,GLenum internalformat,GLsizei width)const{(this->*(this->m_ptr_glTextureStorage1DEXT))(texture,target,levels,internalformat,width);}
inline void glColorTableEXT(GLenum target,GLenum internalFormat,GLsizei width,GLenum format,GLenum type,const void* table)const{(this->*(this->m_ptr_glColorTableEXT))(target,internalFormat,width,format,type,table);}
inline void glGenBuffers(GLsizei n,GLuint* buffers)const{(this->*(this->m_ptr_glGenBuffers))(n,buffers);}
inline void glTexCoordP1uiv(GLenum type,const GLuint* coords)const{(this->*(this->m_ptr_glTexCoordP1uiv))(type,coords);}
inline void glClearNamedFramebufferiv(GLuint framebuffer,GLenum buffer,GLint drawbuffer,const GLint* value)const{(this->*(this->m_ptr_glClearNamedFramebufferiv))(framebuffer,buffer,drawbuffer,value);}
inline void glTexImage3D(GLenum target,GLint level,GLint internalFormat,GLsizei width,GLsizei height,GLsizei depth,GLint border,GLenum format,GLenum type,const GLvoid* pixels)const{(this->*(this->m_ptr_glTexImage3D))(target,level,internalFormat,width,height,depth,border,format,type,pixels);}
inline GLboolean glIsFramebuffer(GLuint framebuffer)const{return (this->*(this->m_ptr_glIsFramebuffer))(framebuffer);}
inline void glMatrixPopEXT(GLenum mode)const{(this->*(this->m_ptr_glMatrixPopEXT))(mode);}
inline void glMultiTexEnviEXT(GLenum texunit,GLenum target,GLenum pname,GLint param)const{(this->*(this->m_ptr_glMultiTexEnviEXT))(texunit,target,pname,param);}
inline void glVertexAttribI2iEXT(GLuint index,GLint x,GLint y)const{(this->*(this->m_ptr_glVertexAttribI2iEXT))(index,x,y);}
inline void glTexCoordP4uiv(GLenum type,const GLuint* coords)const{(this->*(this->m_ptr_glTexCoordP4uiv))(type,coords);}
inline void glGetVariantIntegervEXT(GLuint id,GLenum value,GLint* data)const{(this->*(this->m_ptr_glGetVariantIntegervEXT))(id,value,data);}
inline void glTexGendv(GLenum coord,GLenum pname,const GLdouble* params)const{(this->*(this->m_ptr_glTexGendv))(coord,pname,params);}
inline void glVertexP2uiv(GLenum type,const GLuint* value)const{(this->*(this->m_ptr_glVertexP2uiv))(type,value);}
inline void glVertexAttrib3f(GLuint index,GLfloat x,GLfloat y,GLfloat z)const{(this->*(this->m_ptr_glVertexAttrib3f))(index,x,y,z);}
inline void glVertexAttribI2ivEXT(GLuint index,const GLint* v)const{(this->*(this->m_ptr_glVertexAttribI2ivEXT))(index,v);}
inline void glPopMatrix()const{(this->*(this->m_ptr_glPopMatrix))();}
inline void glProgramUniform4dv(GLuint program,GLint location,GLsizei count,const GLdouble* value)const{(this->*(this->m_ptr_glProgramUniform4dv))(program,location,count,value);}
inline void glEdgeFlagPointerEXT(GLsizei stride,GLsizei count,const GLboolean* pointer)const{(this->*(this->m_ptr_glEdgeFlagPointerEXT))(stride,count,pointer);}
inline void glVariantuivEXT(GLuint id,const GLuint* addr)const{(this->*(this->m_ptr_glVariantuivEXT))(id,addr);}
inline GLenum glCheckNamedFramebufferStatus(GLuint framebuffer,GLenum target)const{return (this->*(this->m_ptr_glCheckNamedFramebufferStatus))(framebuffer,target);}
inline void glConvolutionParameterfv(GLenum target,GLenum pname,const GLfloat* params)const{(this->*(this->m_ptr_glConvolutionParameterfv))(target,pname,params);}
inline void glTextureNormalEXT(GLenum mode)const{(this->*(this->m_ptr_glTextureNormalEXT))(mode);}
inline void glProgramUniform2uiEXT(GLuint program,GLint location,GLuint v0,GLuint v1)const{(this->*(this->m_ptr_glProgramUniform2uiEXT))(program,location,v0,v1);}
inline void glProgramUniform2fvEXT(GLuint program,GLint location,GLsizei count,const GLfloat* value)const{(this->*(this->m_ptr_glProgramUniform2fvEXT))(program,location,count,value);}
inline void glProgramUniformMatrix4x3fvEXT(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLfloat* value)const{(this->*(this->m_ptr_glProgramUniformMatrix4x3fvEXT))(program,location,count,transpose,value);}
inline void glProgramUniform3dEXT(GLuint program,GLint location,GLdouble x,GLdouble y,GLdouble z)const{(this->*(this->m_ptr_glProgramUniform3dEXT))(program,location,x,y,z);}
inline void glGetConvolutionFilterEXT(GLenum target,GLenum format,GLenum type,void* image)const{(this->*(this->m_ptr_glGetConvolutionFilterEXT))(target,format,type,image);}
inline void glFogCoordPointerEXT(GLenum type,GLsizei stride,const void* pointer)const{(this->*(this->m_ptr_glFogCoordPointerEXT))(type,stride,pointer);}
inline void glCreateRenderbuffers(GLsizei n,GLuint* renderbuffers)const{(this->*(this->m_ptr_glCreateRenderbuffers))(n,renderbuffers);}
inline void glVertexAttrib4Nusv(GLuint index,const GLushort* v)const{(this->*(this->m_ptr_glVertexAttrib4Nusv))(index,v);}
inline void glColorMask(GLboolean red,GLboolean green,GLboolean blue,GLboolean alpha)const{(this->*(this->m_ptr_glColorMask))(red,green,blue,alpha);}
inline void glEnableClientStateIndexedEXT(GLenum array,GLuint index)const{(this->*(this->m_ptr_glEnableClientStateIndexedEXT))(array,index);}
inline void glBlendFunci(GLuint buf,GLenum src,GLenum dst)const{(this->*(this->m_ptr_glBlendFunci))(buf,src,dst);}
inline void glMatrixLoadIdentityEXT(GLenum mode)const{(this->*(this->m_ptr_glMatrixLoadIdentityEXT))(mode);}
inline GLuint glCreateShaderProgramEXT(GLenum type,const GLchar* string)const{return (this->*(this->m_ptr_glCreateShaderProgramEXT))(type,string);}
inline void glBufferStorage(GLenum target,GLsizeiptr size,const void* data,GLbitfield flags)const{(this->*(this->m_ptr_glBufferStorage))(target,size,data,flags);}
inline void glRenderbufferStorageMultisampleEXT(GLenum target,GLsizei samples,GLenum internalformat,GLsizei width,GLsizei height)const{(this->*(this->m_ptr_glRenderbufferStorageMultisampleEXT))(target,samples,internalformat,width,height);}
inline void glGetFloati_v(GLenum target,GLuint index,GLfloat* data)const{(this->*(this->m_ptr_glGetFloati_v))(target,index,data);}
inline void glVertex3fv(const GLfloat* v)const{(this->*(this->m_ptr_glVertex3fv))(v);}
inline GLint glGetUniformLocation(GLuint program,const GLchar* name)const{return (this->*(this->m_ptr_glGetUniformLocation))(program,name);}
inline void glNamedFramebufferDrawBuffers(GLuint framebuffer,GLsizei n,const GLenum* bufs)const{(this->*(this->m_ptr_glNamedFramebufferDrawBuffers))(framebuffer,n,bufs);}
inline void glUniform4fv(GLint location,GLsizei count,const GLfloat* value)const{(this->*(this->m_ptr_glUniform4fv))(location,count,value);}
inline void glNormalPointerEXT(GLenum type,GLsizei stride,GLsizei count,const void* pointer)const{(this->*(this->m_ptr_glNormalPointerEXT))(type,stride,count,pointer);}
inline void glVertexAttribP4uiv(GLuint index,GLenum type,GLboolean normalized,const GLuint* value)const{(this->*(this->m_ptr_glVertexAttribP4uiv))(index,type,normalized,value);}
inline void glCompressedTextureSubImage3D(GLuint texture,GLint level,GLint xoffset,GLint yoffset,GLint zoffset,GLsizei width,GLsizei height,GLsizei depth,GLenum format,GLsizei imageSize,const void* data)const{(this->*(this->m_ptr_glCompressedTextureSubImage3D))(texture,level,xoffset,yoffset,zoffset,width,height,depth,format,imageSize,data);}
inline void glBindSamplers(GLuint first,GLsizei count,const GLuint* samplers)const{(this->*(this->m_ptr_glBindSamplers))(first,count,samplers);}
inline void glGetConvolutionParameterivEXT(GLenum target,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetConvolutionParameterivEXT))(target,pname,params);}
inline void glPrioritizeTexturesEXT(GLsizei n,const GLuint* textures,const GLclampf* priorities)const{(this->*(this->m_ptr_glPrioritizeTexturesEXT))(n,textures,priorities);}
inline void glEndConditionalRender()const{(this->*(this->m_ptr_glEndConditionalRender))();}
inline void glEnableClientState(GLenum cap)const{(this->*(this->m_ptr_glEnableClientState))(cap);}
inline void glResetHistogram(GLenum target)const{(this->*(this->m_ptr_glResetHistogram))(target);}
inline void glUniform1uiEXT(GLint location,GLuint v0)const{(this->*(this->m_ptr_glUniform1uiEXT))(location,v0);}
inline void glMultiTexCoord2sv(GLenum target,const GLshort* v)const{(this->*(this->m_ptr_glMultiTexCoord2sv))(target,v);}
inline void glTexSubImage2DEXT(GLenum target,GLint level,GLint xoffset,GLint yoffset,GLsizei width,GLsizei height,GLenum format,GLenum type,const void* pixels)const{(this->*(this->m_ptr_glTexSubImage2DEXT))(target,level,xoffset,yoffset,width,height,format,type,pixels);}
inline void glProgramUniform2uiv(GLuint program,GLint location,GLsizei count,const GLuint* value)const{(this->*(this->m_ptr_glProgramUniform2uiv))(program,location,count,value);}
inline void glGetQueryObjectuiv(GLuint id,GLenum pname,GLuint* params)const{(this->*(this->m_ptr_glGetQueryObjectuiv))(id,pname,params);}
inline void glGenerateMultiTexMipmapEXT(GLenum texunit,GLenum target)const{(this->*(this->m_ptr_glGenerateMultiTexMipmapEXT))(texunit,target);}
inline void glVertexAttrib4iv(GLuint index,const GLint* v)const{(this->*(this->m_ptr_glVertexAttrib4iv))(index,v);}
inline void glLabelObjectEXT(GLenum type,GLuint object,GLsizei length,const GLchar* label)const{(this->*(this->m_ptr_glLabelObjectEXT))(type,object,length,label);}
inline void glProgramUniform1uiv(GLuint program,GLint location,GLsizei count,const GLuint* value)const{(this->*(this->m_ptr_glProgramUniform1uiv))(program,location,count,value);}
inline void glFramebufferTexture(GLenum target,GLenum attachment,GLuint texture,GLint level)const{(this->*(this->m_ptr_glFramebufferTexture))(target,attachment,texture,level);}
inline void glMultiTexEnvfEXT(GLenum texunit,GLenum target,GLenum pname,GLfloat param)const{(this->*(this->m_ptr_glMultiTexEnvfEXT))(texunit,target,pname,param);}
inline void glGetTexGendv(GLenum coord,GLenum pname,GLdouble* params)const{(this->*(this->m_ptr_glGetTexGendv))(coord,pname,params);}
inline void glVertexAttribI2uivEXT(GLuint index,const GLuint* v)const{(this->*(this->m_ptr_glVertexAttribI2uivEXT))(index,v);}
inline void glNamedProgramLocalParameter4fvEXT(GLuint program,GLenum target,GLuint index,const GLfloat* params)const{(this->*(this->m_ptr_glNamedProgramLocalParameter4fvEXT))(program,target,index,params);}
inline void glColor3usv(const GLushort* v)const{(this->*(this->m_ptr_glColor3usv))(v);}
inline void glGetPixelTransformParameterfvEXT(GLenum target,GLenum pname,GLfloat* params)const{(this->*(this->m_ptr_glGetPixelTransformParameterfvEXT))(target,pname,params);}
inline void glProgramUniformMatrix2x4fv(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLfloat* value)const{(this->*(this->m_ptr_glProgramUniformMatrix2x4fv))(program,location,count,transpose,value);}
inline void glColorTable(GLenum target,GLenum internalformat,GLsizei width,GLenum format,GLenum type,const GLvoid* table)const{(this->*(this->m_ptr_glColorTable))(target,internalformat,width,format,type,table);}
inline void glBeginQueryIndexed(GLenum target,GLuint index,GLuint id)const{(this->*(this->m_ptr_glBeginQueryIndexed))(target,index,id);}
inline void glProgramUniform2dv(GLuint program,GLint location,GLsizei count,const GLdouble* value)const{(this->*(this->m_ptr_glProgramUniform2dv))(program,location,count,value);}
inline void glActiveStencilFaceEXT(GLenum face)const{(this->*(this->m_ptr_glActiveStencilFaceEXT))(face);}
inline void glProgramUniform4dEXT(GLuint program,GLint location,GLdouble x,GLdouble y,GLdouble z,GLdouble w)const{(this->*(this->m_ptr_glProgramUniform4dEXT))(program,location,x,y,z,w);}
inline void glRasterPos2sv(const GLshort* v)const{(this->*(this->m_ptr_glRasterPos2sv))(v);}
inline GLuint glBindParameterEXT(GLenum value)const{return (this->*(this->m_ptr_glBindParameterEXT))(value);}
inline void glTexCoord1sv(const GLshort* v)const{(this->*(this->m_ptr_glTexCoord1sv))(v);}
inline void glNamedProgramLocalParameter4dvEXT(GLuint program,GLenum target,GLuint index,const GLdouble* params)const{(this->*(this->m_ptr_glNamedProgramLocalParameter4dvEXT))(program,target,index,params);}
inline void glGetTextureParameterfvEXT(GLuint texture,GLenum target,GLenum pname,GLfloat* params)const{(this->*(this->m_ptr_glGetTextureParameterfvEXT))(texture,target,pname,params);}
inline void glVertex2i(GLint x,GLint y)const{(this->*(this->m_ptr_glVertex2i))(x,y);}
inline void glNewList(GLuint list,GLenum mode)const{(this->*(this->m_ptr_glNewList))(list,mode);}
inline GLintptr glGetUniformOffsetEXT(GLuint program,GLint location)const{return (this->*(this->m_ptr_glGetUniformOffsetEXT))(program,location);}
inline void glSecondaryColorP3uiv(GLenum type,const GLuint* color)const{(this->*(this->m_ptr_glSecondaryColorP3uiv))(type,color);}
inline void glGetIntegerv(GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetIntegerv))(pname,params);}
inline void glMatrixLoaddEXT(GLenum mode,const GLdouble* m)const{(this->*(this->m_ptr_glMatrixLoaddEXT))(mode,m);}
inline void glProgramUniformMatrix3dv(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLdouble* value)const{(this->*(this->m_ptr_glProgramUniformMatrix3dv))(program,location,count,transpose,value);}
inline void glGetHistogramEXT(GLenum target,GLboolean reset,GLenum format,GLenum type,void* values)const{(this->*(this->m_ptr_glGetHistogramEXT))(target,reset,format,type,values);}
inline GLboolean glIsQuery(GLuint id)const{return (this->*(this->m_ptr_glIsQuery))(id);}
inline void glTexImage2D(GLenum target,GLint level,GLint internalFormat,GLsizei width,GLsizei height,GLint border,GLenum format,GLenum type,const GLvoid* pixels)const{(this->*(this->m_ptr_glTexImage2D))(target,level,internalFormat,width,height,border,format,type,pixels);}
inline void glEnableIndexedEXT(GLenum target,GLuint index)const{(this->*(this->m_ptr_glEnableIndexedEXT))(target,index);}
inline void glDrawPixels(GLsizei width,GLsizei height,GLenum format,GLenum type,const GLvoid* pixels)const{(this->*(this->m_ptr_glDrawPixels))(width,height,format,type,pixels);}
inline void glMultMatrixd(const GLdouble* m)const{(this->*(this->m_ptr_glMultMatrixd))(m);}
inline void glMultMatrixf(const GLfloat* m)const{(this->*(this->m_ptr_glMultMatrixf))(m);}
inline GLboolean glIsTexture(GLuint texture)const{return (this->*(this->m_ptr_glIsTexture))(texture);}
inline void glVertexAttrib4Nubv(GLuint index,const GLubyte* v)const{(this->*(this->m_ptr_glVertexAttrib4Nubv))(index,v);}
inline void glVertexArrayVertexAttribIOffsetEXT(GLuint vaobj,GLuint buffer,GLuint index,GLint size,GLenum type,GLsizei stride,GLintptr offset)const{(this->*(this->m_ptr_glVertexArrayVertexAttribIOffsetEXT))(vaobj,buffer,index,size,type,stride,offset);}
inline void glProgramUniform3fEXT(GLuint program,GLint location,GLfloat v0,GLfloat v1,GLfloat v2)const{(this->*(this->m_ptr_glProgramUniform3fEXT))(program,location,v0,v1,v2);}
inline void glColor4usv(const GLushort* v)const{(this->*(this->m_ptr_glColor4usv))(v);}
inline void glPolygonStipple(const GLubyte* mask)const{(this->*(this->m_ptr_glPolygonStipple))(mask);}
inline void glInterleavedArrays(GLenum format,GLsizei stride,const GLvoid* pointer)const{(this->*(this->m_ptr_glInterleavedArrays))(format,stride,pointer);}
inline void glTextureRenderbufferEXT(GLuint texture,GLenum target,GLuint renderbuffer)const{(this->*(this->m_ptr_glTextureRenderbufferEXT))(texture,target,renderbuffer);}
inline GLint glGetSubroutineUniformLocation(GLuint program,GLenum shadertype,const GLchar* name)const{return (this->*(this->m_ptr_glGetSubroutineUniformLocation))(program,shadertype,name);}
inline void glGetFramebufferParameteriv(GLenum target,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetFramebufferParameteriv))(target,pname,params);}
inline void glPixelMapusv(GLenum map,GLsizei mapsize,const GLushort* values)const{(this->*(this->m_ptr_glPixelMapusv))(map,mapsize,values);}
inline void glGetSamplerParameteriv(GLuint sampler,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetSamplerParameteriv))(sampler,pname,params);}
inline void glGetPointervEXT(GLenum pname,void** params)const{(this->*(this->m_ptr_glGetPointervEXT))(pname,params);}
inline void glProgramUniformMatrix3dvEXT(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLdouble* value)const{(this->*(this->m_ptr_glProgramUniformMatrix3dvEXT))(program,location,count,transpose,value);}
inline void glCopyBufferSubData(GLenum readTarget,GLenum writeTarget,GLintptr readOffset,GLintptr writeOffset,GLsizeiptr size)const{(this->*(this->m_ptr_glCopyBufferSubData))(readTarget,writeTarget,readOffset,writeOffset,size);}
inline void glVertexAttribI1uiv(GLuint index,const GLuint* v)const{(this->*(this->m_ptr_glVertexAttribI1uiv))(index,v);}
inline void glTexStorage2D(GLenum target,GLsizei levels,GLenum internalformat,GLsizei width,GLsizei height)const{(this->*(this->m_ptr_glTexStorage2D))(target,levels,internalformat,width,height);}
inline void glColor3fv(const GLfloat* v)const{(this->*(this->m_ptr_glColor3fv))(v);}
inline void glVertexAttribL4dvEXT(GLuint index,const GLdouble* v)const{(this->*(this->m_ptr_glVertexAttribL4dvEXT))(index,v);}
inline void glGetActiveUniform(GLuint program,GLuint index,GLsizei bufSize,GLsizei* length,GLint* size,GLenum* type,GLchar* name)const{(this->*(this->m_ptr_glGetActiveUniform))(program,index,bufSize,length,size,type,name);}
inline void glColorPointer(GLint size,GLenum type,GLsizei stride,const GLvoid* ptr)const{(this->*(this->m_ptr_glColorPointer))(size,type,stride,ptr);}
inline void glMultiTexParameterfEXT(GLenum texunit,GLenum target,GLenum pname,GLfloat param)const{(this->*(this->m_ptr_glMultiTexParameterfEXT))(texunit,target,pname,param);}
inline void glNamedFramebufferTextureLayer(GLuint framebuffer,GLenum attachment,GLuint texture,GLint level,GLint layer)const{(this->*(this->m_ptr_glNamedFramebufferTextureLayer))(framebuffer,attachment,texture,level,layer);}
inline void glGetVertexArrayIntegervEXT(GLuint vaobj,GLenum pname,GLint* param)const{(this->*(this->m_ptr_glGetVertexArrayIntegervEXT))(vaobj,pname,param);}
inline void glSecondaryColor3sv(const GLshort* v)const{(this->*(this->m_ptr_glSecondaryColor3sv))(v);}
inline void glUniform3uiEXT(GLint location,GLuint v0,GLuint v1,GLuint v2)const{(this->*(this->m_ptr_glUniform3uiEXT))(location,v0,v1,v2);}
inline void glTexParameterIuivEXT(GLenum target,GLenum pname,const GLuint* params)const{(this->*(this->m_ptr_glTexParameterIuivEXT))(target,pname,params);}
inline void glProgramUniformMatrix4fv(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLfloat* value)const{(this->*(this->m_ptr_glProgramUniformMatrix4fv))(program,location,count,transpose,value);}
inline void glVertex2fv(const GLfloat* v)const{(this->*(this->m_ptr_glVertex2fv))(v);}
inline void glVertexAttribL3dEXT(GLuint index,GLdouble x,GLdouble y,GLdouble z)const{(this->*(this->m_ptr_glVertexAttribL3dEXT))(index,x,y,z);}
inline void glFramebufferRenderbuffer(GLenum target,GLenum attachment,GLenum renderbuffertarget,GLuint renderbuffer)const{(this->*(this->m_ptr_glFramebufferRenderbuffer))(target,attachment,renderbuffertarget,renderbuffer);}
inline void glGetDoublei_v(GLenum target,GLuint index,GLdouble* data)const{(this->*(this->m_ptr_glGetDoublei_v))(target,index,data);}
inline void glVertexAttrib1sv(GLuint index,const GLshort* v)const{(this->*(this->m_ptr_glVertexAttrib1sv))(index,v);}
inline void glBindSampler(GLuint unit,GLuint sampler)const{(this->*(this->m_ptr_glBindSampler))(unit,sampler);}
inline void glLineWidth(GLfloat width)const{(this->*(this->m_ptr_glLineWidth))(width);}
inline void glBindBufferOffsetEXT(GLenum target,GLuint index,GLuint buffer,GLintptr offset)const{(this->*(this->m_ptr_glBindBufferOffsetEXT))(target,index,buffer,offset);}
inline void glGetIntegeri_v(GLenum target,GLuint index,GLint* data)const{(this->*(this->m_ptr_glGetIntegeri_v))(target,index,data);}
inline void glGetTransformFeedbackVarying(GLuint program,GLuint index,GLsizei bufSize,GLsizei* length,GLsizei* size,GLenum* type,GLchar* name)const{(this->*(this->m_ptr_glGetTransformFeedbackVarying))(program,index,bufSize,length,size,type,name);}
inline void glFogiv(GLenum pname,const GLint* params)const{(this->*(this->m_ptr_glFogiv))(pname,params);}
inline void glLightModeliv(GLenum pname,const GLint* params)const{(this->*(this->m_ptr_glLightModeliv))(pname,params);}
inline void glDepthRangef(GLfloat n,GLfloat f)const{(this->*(this->m_ptr_glDepthRangef))(n,f);}
inline void glCompressedTextureSubImage1DEXT(GLuint texture,GLenum target,GLint level,GLint xoffset,GLsizei width,GLenum format,GLsizei imageSize,const void* bits)const{(this->*(this->m_ptr_glCompressedTextureSubImage1DEXT))(texture,target,level,xoffset,width,format,imageSize,bits);}
inline void glEnablei(GLenum target,GLuint index)const{(this->*(this->m_ptr_glEnablei))(target,index);}
inline void glEvalCoord1fv(const GLfloat* u)const{(this->*(this->m_ptr_glEvalCoord1fv))(u);}
inline void glProgramUniformMatrix2dv(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLdouble* value)const{(this->*(this->m_ptr_glProgramUniformMatrix2dv))(program,location,count,transpose,value);}
inline void glSampleMaski(GLuint maskNumber,GLbitfield mask)const{(this->*(this->m_ptr_glSampleMaski))(maskNumber,mask);}
inline void glIndexFuncEXT(GLenum func,GLclampf ref)const{(this->*(this->m_ptr_glIndexFuncEXT))(func,ref);}
inline void glUniformMatrix3x2fv(GLint location,GLsizei count,GLboolean transpose,const GLfloat* value)const{(this->*(this->m_ptr_glUniformMatrix3x2fv))(location,count,transpose,value);}
inline void glGetFramebufferParameterivEXT(GLuint framebuffer,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetFramebufferParameterivEXT))(framebuffer,pname,params);}
inline void glGetInternalformativ(GLenum target,GLenum internalformat,GLenum pname,GLsizei bufSize,GLint* params)const{(this->*(this->m_ptr_glGetInternalformativ))(target,internalformat,pname,bufSize,params);}
inline void glNamedFramebufferTexture3DEXT(GLuint framebuffer,GLenum attachment,GLenum textarget,GLuint texture,GLint level,GLint zoffset)const{(this->*(this->m_ptr_glNamedFramebufferTexture3DEXT))(framebuffer,attachment,textarget,texture,level,zoffset);}
inline void glVertexAttrib2dv(GLuint index,const GLdouble* v)const{(this->*(this->m_ptr_glVertexAttrib2dv))(index,v);}
inline void glUniformMatrix3x4fv(GLint location,GLsizei count,GLboolean transpose,const GLfloat* value)const{(this->*(this->m_ptr_glUniformMatrix3x4fv))(location,count,transpose,value);}
inline void glProgramUniformMatrix3fvEXT(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLfloat* value)const{(this->*(this->m_ptr_glProgramUniformMatrix3fvEXT))(program,location,count,transpose,value);}
inline void glEnableVertexArrayEXT(GLuint vaobj,GLenum array)const{(this->*(this->m_ptr_glEnableVertexArrayEXT))(vaobj,array);}
inline void glEdgeFlag(GLboolean flag)const{(this->*(this->m_ptr_glEdgeFlag))(flag);}
inline void glProgramUniform1ui(GLuint program,GLint location,GLuint v0)const{(this->*(this->m_ptr_glProgramUniform1ui))(program,location,v0);}
inline void glVertex3d(GLdouble x,GLdouble y,GLdouble z)const{(this->*(this->m_ptr_glVertex3d))(x,y,z);}
inline void glVertex3f(GLfloat x,GLfloat y,GLfloat z)const{(this->*(this->m_ptr_glVertex3f))(x,y,z);}
inline void glVertex3i(GLint x,GLint y,GLint z)const{(this->*(this->m_ptr_glVertex3i))(x,y,z);}
inline void glGetColorTable(GLenum target,GLenum format,GLenum type,GLvoid* table)const{(this->*(this->m_ptr_glGetColorTable))(target,format,type,table);}
inline void glVertex3s(GLshort x,GLshort y,GLshort z)const{(this->*(this->m_ptr_glVertex3s))(x,y,z);}
inline void glTexCoordP2ui(GLenum type,GLuint coords)const{(this->*(this->m_ptr_glTexCoordP2ui))(type,coords);}
inline void glColorMaski(GLuint index,GLboolean r,GLboolean g,GLboolean b,GLboolean a)const{(this->*(this->m_ptr_glColorMaski))(index,r,g,b,a);}
inline void glCopyNamedBufferSubData(GLuint readBuffer,GLuint writeBuffer,GLintptr readOffset,GLintptr writeOffset,GLsizeiptr size)const{(this->*(this->m_ptr_glCopyNamedBufferSubData))(readBuffer,writeBuffer,readOffset,writeOffset,size);}
inline void glTexStorage3D(GLenum target,GLsizei levels,GLenum internalformat,GLsizei width,GLsizei height,GLsizei depth)const{(this->*(this->m_ptr_glTexStorage3D))(target,levels,internalformat,width,height,depth);}
inline void glTextureParameteriv(GLuint texture,GLenum pname,const GLint* param)const{(this->*(this->m_ptr_glTextureParameteriv))(texture,pname,param);}
inline void glNamedBufferDataEXT(GLuint buffer,GLsizeiptr size,const void* data,GLenum usage)const{(this->*(this->m_ptr_glNamedBufferDataEXT))(buffer,size,data,usage);}
inline void glNormalPointer(GLenum type,GLsizei stride,const GLvoid* ptr)const{(this->*(this->m_ptr_glNormalPointer))(type,stride,ptr);}
inline void glNamedFramebufferTexture(GLuint framebuffer,GLenum attachment,GLuint texture,GLint level)const{(this->*(this->m_ptr_glNamedFramebufferTexture))(framebuffer,attachment,texture,level);}
inline void glPassThrough(GLfloat token)const{(this->*(this->m_ptr_glPassThrough))(token);}
inline void glTangent3fvEXT(const GLfloat* v)const{(this->*(this->m_ptr_glTangent3fvEXT))(v);}
inline void glProgramUniformMatrix4x3fv(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLfloat* value)const{(this->*(this->m_ptr_glProgramUniformMatrix4x3fv))(program,location,count,transpose,value);}
inline void glBegin(GLenum mode)const{(this->*(this->m_ptr_glBegin))(mode);}
inline void glEvalCoord2dv(const GLdouble* u)const{(this->*(this->m_ptr_glEvalCoord2dv))(u);}
inline void glColor3ubv(const GLubyte* v)const{(this->*(this->m_ptr_glColor3ubv))(v);}
inline void glFogCoordfvEXT(const GLfloat* coord)const{(this->*(this->m_ptr_glFogCoordfvEXT))(coord);}
inline void glVertexP3ui(GLenum type,GLuint value)const{(this->*(this->m_ptr_glVertexP3ui))(type,value);}
inline void glLightfv(GLenum light,GLenum pname,const GLfloat* params)const{(this->*(this->m_ptr_glLightfv))(light,pname,params);}
inline void glStencilClearTagEXT(GLsizei stencilTagBits,GLuint stencilClearTag)const{(this->*(this->m_ptr_glStencilClearTagEXT))(stencilTagBits,stencilClearTag);}
inline void glGetActiveUniformName(GLuint program,GLuint uniformIndex,GLsizei bufSize,GLsizei* length,GLchar* uniformName)const{(this->*(this->m_ptr_glGetActiveUniformName))(program,uniformIndex,bufSize,length,uniformName);}
inline void glTangentPointerEXT(GLenum type,GLsizei stride,const void* pointer)const{(this->*(this->m_ptr_glTangentPointerEXT))(type,stride,pointer);}
inline void glProgramUniform2ui(GLuint program,GLint location,GLuint v0,GLuint v1)const{(this->*(this->m_ptr_glProgramUniform2ui))(program,location,v0,v1);}
inline void glCopyTexSubImage2DEXT(GLenum target,GLint level,GLint xoffset,GLint yoffset,GLint x,GLint y,GLsizei width,GLsizei height)const{(this->*(this->m_ptr_glCopyTexSubImage2DEXT))(target,level,xoffset,yoffset,x,y,width,height);}
inline void glResetHistogramEXT(GLenum target)const{(this->*(this->m_ptr_glResetHistogramEXT))(target);}
inline void glNamedProgramLocalParameterI4ivEXT(GLuint program,GLenum target,GLuint index,const GLint* params)const{(this->*(this->m_ptr_glNamedProgramLocalParameterI4ivEXT))(program,target,index,params);}
inline void glGetMultiTexParameterIuivEXT(GLenum texunit,GLenum target,GLenum pname,GLuint* params)const{(this->*(this->m_ptr_glGetMultiTexParameterIuivEXT))(texunit,target,pname,params);}
inline void glTexParameteriv(GLenum target,GLenum pname,const GLint* params)const{(this->*(this->m_ptr_glTexParameteriv))(target,pname,params);}
inline void glMatrixOrthoEXT(GLenum mode,GLdouble left,GLdouble right,GLdouble bottom,GLdouble top,GLdouble zNear,GLdouble zFar)const{(this->*(this->m_ptr_glMatrixOrthoEXT))(mode,left,right,bottom,top,zNear,zFar);}
inline void glVertexArrayVertexBuffer(GLuint vaobj,GLuint bindingindex,GLuint buffer,GLintptr offset,GLsizei stride)const{(this->*(this->m_ptr_glVertexArrayVertexBuffer))(vaobj,bindingindex,buffer,offset,stride);}
inline void glGetTexImage(GLenum target,GLint level,GLenum format,GLenum type,GLvoid* pixels)const{(this->*(this->m_ptr_glGetTexImage))(target,level,format,type,pixels);}
inline void glTransformFeedbackBufferBase(GLuint xfb,GLuint index,GLuint buffer)const{(this->*(this->m_ptr_glTransformFeedbackBufferBase))(xfb,index,buffer);}
inline void glIndexsv(const GLshort* c)const{(this->*(this->m_ptr_glIndexsv))(c);}
inline void glBitmap(GLsizei width,GLsizei height,GLfloat xorig,GLfloat yorig,GLfloat xmove,GLfloat ymove,const GLubyte* bitmap)const{(this->*(this->m_ptr_glBitmap))(width,height,xorig,yorig,xmove,ymove,bitmap);}
inline void glNamedFramebufferTextureLayerEXT(GLuint framebuffer,GLenum attachment,GLuint texture,GLint level,GLint layer)const{(this->*(this->m_ptr_glNamedFramebufferTextureLayerEXT))(framebuffer,attachment,texture,level,layer);}
inline void glMultiTexGenfvEXT(GLenum texunit,GLenum coord,GLenum pname,const GLfloat* params)const{(this->*(this->m_ptr_glMultiTexGenfvEXT))(texunit,coord,pname,params);}
inline void glGetNamedBufferSubData(GLuint buffer,GLintptr offset,GLsizeiptr size,void* data)const{(this->*(this->m_ptr_glGetNamedBufferSubData))(buffer,offset,size,data);}
inline void glProgramUniform2iv(GLuint program,GLint location,GLsizei count,const GLint* value)const{(this->*(this->m_ptr_glProgramUniform2iv))(program,location,count,value);}
inline void glGetQueryiv(GLenum target,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetQueryiv))(target,pname,params);}
inline void glTexCoord4f(GLfloat s,GLfloat t,GLfloat r,GLfloat q)const{(this->*(this->m_ptr_glTexCoord4f))(s,t,r,q);}
inline void glMapGrid2f(GLint un,GLfloat u1,GLfloat u2,GLint vn,GLfloat v1,GLfloat v2)const{(this->*(this->m_ptr_glMapGrid2f))(un,u1,u2,vn,v1,v2);}
inline void glTexCoord4d(GLdouble s,GLdouble t,GLdouble r,GLdouble q)const{(this->*(this->m_ptr_glTexCoord4d))(s,t,r,q);}
inline void glCreateQueries(GLenum target,GLsizei n,GLuint* ids)const{(this->*(this->m_ptr_glCreateQueries))(target,n,ids);}
inline void glGetSamplerParameterfv(GLuint sampler,GLenum pname,GLfloat* params)const{(this->*(this->m_ptr_glGetSamplerParameterfv))(sampler,pname,params);}
inline void glTexCoord4i(GLint s,GLint t,GLint r,GLint q)const{(this->*(this->m_ptr_glTexCoord4i))(s,t,r,q);}
inline void glTexCoord4s(GLshort s,GLshort t,GLshort r,GLshort q)const{(this->*(this->m_ptr_glTexCoord4s))(s,t,r,q);}
inline void glColorTableParameteriv(GLenum target,GLenum pname,const GLint* params)const{(this->*(this->m_ptr_glColorTableParameteriv))(target,pname,params);}
inline void glGetUniformIndices(GLuint program,GLsizei uniformCount,const GLchar*const* uniformNames,GLuint* uniformIndices)const{(this->*(this->m_ptr_glGetUniformIndices))(program,uniformCount,uniformNames,uniformIndices);}
inline void glMultiTexImage3DEXT(GLenum texunit,GLenum target,GLint level,GLint internalformat,GLsizei width,GLsizei height,GLsizei depth,GLint border,GLenum format,GLenum type,const void* pixels)const{(this->*(this->m_ptr_glMultiTexImage3DEXT))(texunit,target,level,internalformat,width,height,depth,border,format,type,pixels);}
inline void glPointParameteriv(GLenum pname,const GLint* params)const{(this->*(this->m_ptr_glPointParameteriv))(pname,params);}
inline void glNormal3fv(const GLfloat* v)const{(this->*(this->m_ptr_glNormal3fv))(v);}
inline void glProgramUniformMatrix3x4dvEXT(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLdouble* value)const{(this->*(this->m_ptr_glProgramUniformMatrix3x4dvEXT))(program,location,count,transpose,value);}
inline void glTexCoord1fv(const GLfloat* v)const{(this->*(this->m_ptr_glTexCoord1fv))(v);}
inline void glProgramUniformMatrix4x3dvEXT(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLdouble* value)const{(this->*(this->m_ptr_glProgramUniformMatrix4x3dvEXT))(program,location,count,transpose,value);}
inline void glMultiTexCoord1dv(GLenum target,const GLdouble* v)const{(this->*(this->m_ptr_glMultiTexCoord1dv))(target,v);}
inline void glTexCoord3fv(const GLfloat* v)const{(this->*(this->m_ptr_glTexCoord3fv))(v);}
inline void glMatrixTranslatefEXT(GLenum mode,GLfloat x,GLfloat y,GLfloat z)const{(this->*(this->m_ptr_glMatrixTranslatefEXT))(mode,x,y,z);}
inline void glTextureMaterialEXT(GLenum face,GLenum mode)const{(this->*(this->m_ptr_glTextureMaterialEXT))(face,mode);}
inline void glMultiTexCoordP3uiv(GLenum texture,GLenum type,const GLuint* coords)const{(this->*(this->m_ptr_glMultiTexCoordP3uiv))(texture,type,coords);}
inline void glVertexAttribP3ui(GLuint index,GLenum type,GLboolean normalized,GLuint value)const{(this->*(this->m_ptr_glVertexAttribP3ui))(index,type,normalized,value);}
inline void glTextureBufferRange(GLuint texture,GLenum internalformat,GLuint buffer,GLintptr offset,GLsizeiptr size)const{(this->*(this->m_ptr_glTextureBufferRange))(texture,internalformat,buffer,offset,size);}
inline void glGetPixelTransformParameterivEXT(GLenum target,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetPixelTransformParameterivEXT))(target,pname,params);}
inline void glGetVariantBooleanvEXT(GLuint id,GLenum value,GLboolean* data)const{(this->*(this->m_ptr_glGetVariantBooleanvEXT))(id,value,data);}
inline void glDepthRange(GLclampd near_val,GLclampd far_val)const{(this->*(this->m_ptr_glDepthRange))(near_val,far_val);}
inline void glGetColorTableParameterfv(GLenum target,GLenum pname,GLfloat* params)const{(this->*(this->m_ptr_glGetColorTableParameterfv))(target,pname,params);}
inline void glDrawArraysInstancedEXT(GLenum mode,GLint start,GLsizei count,GLsizei primcount)const{(this->*(this->m_ptr_glDrawArraysInstancedEXT))(mode,start,count,primcount);}
inline void glDisableClientStateIndexedEXT(GLenum array,GLuint index)const{(this->*(this->m_ptr_glDisableClientStateIndexedEXT))(array,index);}
inline void glDrawBuffer(GLenum mode)const{(this->*(this->m_ptr_glDrawBuffer))(mode);}
inline void glGetnPixelMapusv(GLenum map,GLsizei bufSize,GLushort* values)const{(this->*(this->m_ptr_glGetnPixelMapusv))(map,bufSize,values);}
inline void glRasterPos3fv(const GLfloat* v)const{(this->*(this->m_ptr_glRasterPos3fv))(v);}
inline void glClearBufferuiv(GLenum buffer,GLint drawbuffer,const GLuint* value)const{(this->*(this->m_ptr_glClearBufferuiv))(buffer,drawbuffer,value);}
inline void glGetInternalformati64v(GLenum target,GLenum internalformat,GLenum pname,GLsizei bufSize,GLint64* params)const{(this->*(this->m_ptr_glGetInternalformati64v))(target,internalformat,pname,bufSize,params);}
inline void glShaderOp3EXT(GLenum op,GLuint res,GLuint arg1,GLuint arg2,GLuint arg3)const{(this->*(this->m_ptr_glShaderOp3EXT))(op,res,arg1,arg2,arg3);}
inline void glClearIndex(GLfloat c)const{(this->*(this->m_ptr_glClearIndex))(c);}
inline void glProvokingVertexEXT(GLenum mode)const{(this->*(this->m_ptr_glProvokingVertexEXT))(mode);}
inline void glVariantubvEXT(GLuint id,const GLubyte* addr)const{(this->*(this->m_ptr_glVariantubvEXT))(id,addr);}
inline void glFlush()const{(this->*(this->m_ptr_glFlush))();}
inline void glGetColorTableParameterivEXT(GLenum target,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetColorTableParameterivEXT))(target,pname,params);}
inline GLuint glGenVertexShadersEXT(GLuint range)const{return (this->*(this->m_ptr_glGenVertexShadersEXT))(range);}
inline void glDrawElementsInstancedBaseVertexBaseInstance(GLenum mode,GLsizei count,GLenum type,const void* indices,GLsizei instancecount,GLint basevertex,GLuint baseinstance)const{(this->*(this->m_ptr_glDrawElementsInstancedBaseVertexBaseInstance))(mode,count,type,indices,instancecount,basevertex,baseinstance);}
inline void glGetTexLevelParameteriv(GLenum target,GLint level,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetTexLevelParameteriv))(target,level,pname,params);}
inline void glMatrixRotatefEXT(GLenum mode,GLfloat angle,GLfloat x,GLfloat y,GLfloat z)const{(this->*(this->m_ptr_glMatrixRotatefEXT))(mode,angle,x,y,z);}
inline void glTexStorage3DMultisample(GLenum target,GLsizei samples,GLenum internalformat,GLsizei width,GLsizei height,GLsizei depth,GLboolean fixedsamplelocations)const{(this->*(this->m_ptr_glTexStorage3DMultisample))(target,samples,internalformat,width,height,depth,fixedsamplelocations);}
inline void glProgramUniform3uivEXT(GLuint program,GLint location,GLsizei count,const GLuint* value)const{(this->*(this->m_ptr_glProgramUniform3uivEXT))(program,location,count,value);}
inline void glClampColor(GLenum target,GLenum clamp)const{(this->*(this->m_ptr_glClampColor))(target,clamp);}
inline void glClearStencil(GLint s)const{(this->*(this->m_ptr_glClearStencil))(s);}
inline void glMultiTexCoord3fv(GLenum target,const GLfloat* v)const{(this->*(this->m_ptr_glMultiTexCoord3fv))(target,v);}
inline void glVertexAttribI4bvEXT(GLuint index,const GLbyte* v)const{(this->*(this->m_ptr_glVertexAttribI4bvEXT))(index,v);}
inline void glVertex2f(GLfloat x,GLfloat y)const{(this->*(this->m_ptr_glVertex2f))(x,y);}
inline void glCopyTextureImage2DEXT(GLuint texture,GLenum target,GLint level,GLenum internalformat,GLint x,GLint y,GLsizei width,GLsizei height,GLint border)const{(this->*(this->m_ptr_glCopyTextureImage2DEXT))(texture,target,level,internalformat,x,y,width,height,border);}
inline void glVertex2d(GLdouble x,GLdouble y)const{(this->*(this->m_ptr_glVertex2d))(x,y);}
inline void glSecondaryColor3bvEXT(const GLbyte* v)const{(this->*(this->m_ptr_glSecondaryColor3bvEXT))(v);}
inline void glTangent3bvEXT(const GLbyte* v)const{(this->*(this->m_ptr_glTangent3bvEXT))(v);}
inline void glHistogram(GLenum target,GLsizei width,GLenum internalformat,GLboolean sink)const{(this->*(this->m_ptr_glHistogram))(target,width,internalformat,sink);}
inline void glGetProgramiv(GLuint program,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetProgramiv))(program,pname,params);}
inline void glVertex2s(GLshort x,GLshort y)const{(this->*(this->m_ptr_glVertex2s))(x,y);}
inline void glFlushMappedBufferRange(GLenum target,GLintptr offset,GLsizeiptr length)const{(this->*(this->m_ptr_glFlushMappedBufferRange))(target,offset,length);}
inline void glVertexAttribI3uiEXT(GLuint index,GLuint x,GLuint y,GLuint z)const{(this->*(this->m_ptr_glVertexAttribI3uiEXT))(index,x,y,z);}
inline void glProgramUniformMatrix2fvEXT(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLfloat* value)const{(this->*(this->m_ptr_glProgramUniformMatrix2fvEXT))(program,location,count,transpose,value);}
inline void glGetTextureParameterIuivEXT(GLuint texture,GLenum target,GLenum pname,GLuint* params)const{(this->*(this->m_ptr_glGetTextureParameterIuivEXT))(texture,target,pname,params);}
inline void glGetMultiTexEnvivEXT(GLenum texunit,GLenum target,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetMultiTexEnvivEXT))(texunit,target,pname,params);}
inline void glGenQueries(GLsizei n,GLuint* ids)const{(this->*(this->m_ptr_glGenQueries))(n,ids);}
inline void glGetPixelMapfv(GLenum map,GLfloat* values)const{(this->*(this->m_ptr_glGetPixelMapfv))(map,values);}
inline void glBlendColorEXT(GLfloat red,GLfloat green,GLfloat blue,GLfloat alpha)const{(this->*(this->m_ptr_glBlendColorEXT))(red,green,blue,alpha);}
inline void glResetMinmax(GLenum target)const{(this->*(this->m_ptr_glResetMinmax))(target);}
inline void glTexSubImage3D(GLenum target,GLint level,GLint xoffset,GLint yoffset,GLint zoffset,GLsizei width,GLsizei height,GLsizei depth,GLenum format,GLenum type,const GLvoid* pixels)const{(this->*(this->m_ptr_glTexSubImage3D))(target,level,xoffset,yoffset,zoffset,width,height,depth,format,type,pixels);}
inline void glDeleteSamplers(GLsizei count,const GLuint* samplers)const{(this->*(this->m_ptr_glDeleteSamplers))(count,samplers);}
inline void glDeleteRenderbuffersEXT(GLsizei n,const GLuint* renderbuffers)const{(this->*(this->m_ptr_glDeleteRenderbuffersEXT))(n,renderbuffers);}
inline void glVertexArrayNormalOffsetEXT(GLuint vaobj,GLuint buffer,GLenum type,GLsizei stride,GLintptr offset)const{(this->*(this->m_ptr_glVertexArrayNormalOffsetEXT))(vaobj,buffer,type,stride,offset);}
inline void glGetTextureParameterfv(GLuint texture,GLenum pname,GLfloat* params)const{(this->*(this->m_ptr_glGetTextureParameterfv))(texture,pname,params);}
inline void glSecondaryColorP3ui(GLenum type,GLuint color)const{(this->*(this->m_ptr_glSecondaryColorP3ui))(type,color);}
inline void glVertexArrayTexCoordOffsetEXT(GLuint vaobj,GLuint buffer,GLint size,GLenum type,GLsizei stride,GLintptr offset)const{(this->*(this->m_ptr_glVertexArrayTexCoordOffsetEXT))(vaobj,buffer,size,type,stride,offset);}
inline void glGetHistogram(GLenum target,GLboolean reset,GLenum format,GLenum type,GLvoid* values)const{(this->*(this->m_ptr_glGetHistogram))(target,reset,format,type,values);}
inline void glMatrixMode(GLenum mode)const{(this->*(this->m_ptr_glMatrixMode))(mode);}
inline void glProgramUniformMatrix4x2fvEXT(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLfloat* value)const{(this->*(this->m_ptr_glProgramUniformMatrix4x2fvEXT))(program,location,count,transpose,value);}
inline void glVariantbvEXT(GLuint id,const GLbyte* addr)const{(this->*(this->m_ptr_glVariantbvEXT))(id,addr);}
inline void glBindTextures(GLuint first,GLsizei count,const GLuint* textures)const{(this->*(this->m_ptr_glBindTextures))(first,count,textures);}
inline void glPrioritizeTextures(GLsizei n,const GLuint* textures,const GLclampf* priorities)const{(this->*(this->m_ptr_glPrioritizeTextures))(n,textures,priorities);}
inline void glSecondaryColor3uivEXT(const GLuint* v)const{(this->*(this->m_ptr_glSecondaryColor3uivEXT))(v);}
inline void glGetDoublev(GLenum pname,GLdouble* params)const{(this->*(this->m_ptr_glGetDoublev))(pname,params);}
inline void glBindBufferRangeEXT(GLenum target,GLuint index,GLuint buffer,GLintptr offset,GLsizeiptr size)const{(this->*(this->m_ptr_glBindBufferRangeEXT))(target,index,buffer,offset,size);}
inline void glCompressedTexImage2D(GLenum target,GLint level,GLenum internalformat,GLsizei width,GLsizei height,GLint border,GLsizei imageSize,const GLvoid* data)const{(this->*(this->m_ptr_glCompressedTexImage2D))(target,level,internalformat,width,height,border,imageSize,data);}
inline void glUniform4dv(GLint location,GLsizei count,const GLdouble* value)const{(this->*(this->m_ptr_glUniform4dv))(location,count,value);}
inline void glProgramUniform3dv(GLuint program,GLint location,GLsizei count,const GLdouble* value)const{(this->*(this->m_ptr_glProgramUniform3dv))(program,location,count,value);}
inline void glInvalidateBufferData(GLuint buffer)const{(this->*(this->m_ptr_glInvalidateBufferData))(buffer);}
inline void glCompressedTextureSubImage1D(GLuint texture,GLint level,GLint xoffset,GLsizei width,GLenum format,GLsizei imageSize,const void* data)const{(this->*(this->m_ptr_glCompressedTextureSubImage1D))(texture,level,xoffset,width,format,imageSize,data);}
inline void glGenTexturesEXT(GLsizei n,GLuint* textures)const{(this->*(this->m_ptr_glGenTexturesEXT))(n,textures);}
inline void glTangent3iEXT(GLint tx,GLint ty,GLint tz)const{(this->*(this->m_ptr_glTangent3iEXT))(tx,ty,tz);}
inline void glClearTexImage(GLuint texture,GLint level,GLenum format,GLenum type,const void* data)const{(this->*(this->m_ptr_glClearTexImage))(texture,level,format,type,data);}
inline void glBinormal3bvEXT(const GLbyte* v)const{(this->*(this->m_ptr_glBinormal3bvEXT))(v);}
inline void glUniform3fv(GLint location,GLsizei count,const GLfloat* value)const{(this->*(this->m_ptr_glUniform3fv))(location,count,value);}
inline void glMultiTexCoordP1ui(GLenum texture,GLenum type,GLuint coords)const{(this->*(this->m_ptr_glMultiTexCoordP1ui))(texture,type,coords);}
inline void glClearNamedBufferDataEXT(GLuint buffer,GLenum internalformat,GLenum format,GLenum type,const void* data)const{(this->*(this->m_ptr_glClearNamedBufferDataEXT))(buffer,internalformat,format,type,data);}
inline void glDisableIndexedEXT(GLenum target,GLuint index)const{(this->*(this->m_ptr_glDisableIndexedEXT))(target,index);}
inline void glGetTextureLevelParameterfvEXT(GLuint texture,GLenum target,GLint level,GLenum pname,GLfloat* params)const{(this->*(this->m_ptr_glGetTextureLevelParameterfvEXT))(texture,target,level,pname,params);}
inline void glMultiDrawElements(GLenum mode,const GLsizei* count,GLenum type,const void*const* indices,GLsizei drawcount)const{(this->*(this->m_ptr_glMultiDrawElements))(mode,count,type,indices,drawcount);}
inline void glTexSubImage1DEXT(GLenum target,GLint level,GLint xoffset,GLsizei width,GLenum format,GLenum type,const void* pixels)const{(this->*(this->m_ptr_glTexSubImage1DEXT))(target,level,xoffset,width,format,type,pixels);}
inline void glDrawBuffers(GLsizei n,const GLenum* bufs)const{(this->*(this->m_ptr_glDrawBuffers))(n,bufs);}
inline void glCopyTextureSubImage1DEXT(GLuint texture,GLenum target,GLint level,GLint xoffset,GLint x,GLint y,GLsizei width)const{(this->*(this->m_ptr_glCopyTextureSubImage1DEXT))(texture,target,level,xoffset,x,y,width);}
inline void glNamedFramebufferReadBuffer(GLuint framebuffer,GLenum src)const{(this->*(this->m_ptr_glNamedFramebufferReadBuffer))(framebuffer,src);}
inline void glVertexAttribI1uivEXT(GLuint index,const GLuint* v)const{(this->*(this->m_ptr_glVertexAttribI1uivEXT))(index,v);}
inline void glGetTexGenfv(GLenum coord,GLenum pname,GLfloat* params)const{(this->*(this->m_ptr_glGetTexGenfv))(coord,pname,params);}
inline void glBindTransformFeedback(GLenum target,GLuint id)const{(this->*(this->m_ptr_glBindTransformFeedback))(target,id);}
inline void glMultiTexCoord2iv(GLenum target,const GLint* v)const{(this->*(this->m_ptr_glMultiTexCoord2iv))(target,v);}
inline void glCopyMultiTexSubImage1DEXT(GLenum texunit,GLenum target,GLint level,GLint xoffset,GLint x,GLint y,GLsizei width)const{(this->*(this->m_ptr_glCopyMultiTexSubImage1DEXT))(texunit,target,level,xoffset,x,y,width);}
inline void glRasterPos3iv(const GLint* v)const{(this->*(this->m_ptr_glRasterPos3iv))(v);}
inline void glGetnConvolutionFilter(GLenum target,GLenum format,GLenum type,GLsizei bufSize,void* image)const{(this->*(this->m_ptr_glGetnConvolutionFilter))(target,format,type,bufSize,image);}
inline void glTexCoord4sv(const GLshort* v)const{(this->*(this->m_ptr_glTexCoord4sv))(v);}
inline void glUniform2uiv(GLint location,GLsizei count,const GLuint* value)const{(this->*(this->m_ptr_glUniform2uiv))(location,count,value);}
inline void glFinish()const{(this->*(this->m_ptr_glFinish))();}
inline void glColorTableParameterfv(GLenum target,GLenum pname,const GLfloat* params)const{(this->*(this->m_ptr_glColorTableParameterfv))(target,pname,params);}
inline void glProgramUniform3ivEXT(GLuint program,GLint location,GLsizei count,const GLint* value)const{(this->*(this->m_ptr_glProgramUniform3ivEXT))(program,location,count,value);}
inline void glVertexArrayVertexOffsetEXT(GLuint vaobj,GLuint buffer,GLint size,GLenum type,GLsizei stride,GLintptr offset)const{(this->*(this->m_ptr_glVertexArrayVertexOffsetEXT))(vaobj,buffer,size,type,stride,offset);}
inline void glUniform1uiv(GLint location,GLsizei count,const GLuint* value)const{(this->*(this->m_ptr_glUniform1uiv))(location,count,value);}
inline void glUniformMatrix2dv(GLint location,GLsizei count,GLboolean transpose,const GLdouble* value)const{(this->*(this->m_ptr_glUniformMatrix2dv))(location,count,transpose,value);}
inline void glIndexdv(const GLdouble* c)const{(this->*(this->m_ptr_glIndexdv))(c);}
inline void glSecondaryColor3ivEXT(const GLint* v)const{(this->*(this->m_ptr_glSecondaryColor3ivEXT))(v);}
inline void glTexCoord3iv(const GLint* v)const{(this->*(this->m_ptr_glTexCoord3iv))(v);}
inline void glGetTransformFeedbacki64_v(GLuint xfb,GLenum pname,GLuint index,GLint64* param)const{(this->*(this->m_ptr_glGetTransformFeedbacki64_v))(xfb,pname,index,param);}
inline void glClearDepth(GLclampd depth)const{(this->*(this->m_ptr_glClearDepth))(depth);}
inline void glUniformMatrix4dv(GLint location,GLsizei count,GLboolean transpose,const GLdouble* value)const{(this->*(this->m_ptr_glUniformMatrix4dv))(location,count,transpose,value);}
inline void glVertexWeightfvEXT(const GLfloat* weight)const{(this->*(this->m_ptr_glVertexWeightfvEXT))(weight);}
inline void glVertex4dv(const GLdouble* v)const{(this->*(this->m_ptr_glVertex4dv))(v);}
inline void glInsertComponentEXT(GLuint res,GLuint src,GLuint num)const{(this->*(this->m_ptr_glInsertComponentEXT))(res,src,num);}
inline void glCreateTextures(GLenum target,GLsizei n,GLuint* textures)const{(this->*(this->m_ptr_glCreateTextures))(target,n,textures);}
inline void glSecondaryColor3iv(const GLint* v)const{(this->*(this->m_ptr_glSecondaryColor3iv))(v);}
inline void glCreateBuffers(GLsizei n,GLuint* buffers)const{(this->*(this->m_ptr_glCreateBuffers))(n,buffers);}
inline void glBeginTransformFeedbackEXT(GLenum primitiveMode)const{(this->*(this->m_ptr_glBeginTransformFeedbackEXT))(primitiveMode);}
inline void glNormal3sv(const GLshort* v)const{(this->*(this->m_ptr_glNormal3sv))(v);}
inline void glRasterPos4iv(const GLint* v)const{(this->*(this->m_ptr_glRasterPos4iv))(v);}
inline void glEdgeFlagv(const GLboolean* flag)const{(this->*(this->m_ptr_glEdgeFlagv))(flag);}
inline void glBlendFuncSeparateEXT(GLenum sfactorRGB,GLenum dfactorRGB,GLenum sfactorAlpha,GLenum dfactorAlpha)const{(this->*(this->m_ptr_glBlendFuncSeparateEXT))(sfactorRGB,dfactorRGB,sfactorAlpha,dfactorAlpha);}
inline void glConvolutionParameterivEXT(GLenum target,GLenum pname,const GLint* params)const{(this->*(this->m_ptr_glConvolutionParameterivEXT))(target,pname,params);}
inline void glUniformMatrix4x3dv(GLint location,GLsizei count,GLboolean transpose,const GLdouble* value)const{(this->*(this->m_ptr_glUniformMatrix4x3dv))(location,count,transpose,value);}
inline void glSecondaryColor3dEXT(GLdouble red,GLdouble green,GLdouble blue)const{(this->*(this->m_ptr_glSecondaryColor3dEXT))(red,green,blue);}
inline void glDeleteQueries(GLsizei n,const GLuint* ids)const{(this->*(this->m_ptr_glDeleteQueries))(n,ids);}
inline void glNormalP3uiv(GLenum type,const GLuint* coords)const{(this->*(this->m_ptr_glNormalP3uiv))(type,coords);}
inline void glInitNames()const{(this->*(this->m_ptr_glInitNames))();}
inline void glBinormal3fvEXT(const GLfloat* v)const{(this->*(this->m_ptr_glBinormal3fvEXT))(v);}
inline void glColor3dv(const GLdouble* v)const{(this->*(this->m_ptr_glColor3dv))(v);}
inline void glVertexArrayVertexAttribDivisorEXT(GLuint vaobj,GLuint index,GLuint divisor)const{(this->*(this->m_ptr_glVertexArrayVertexAttribDivisorEXT))(vaobj,index,divisor);}
inline void glArrayElementEXT(GLint i)const{(this->*(this->m_ptr_glArrayElementEXT))(i);}
inline void glGetnMinmax(GLenum target,GLboolean reset,GLenum format,GLenum type,GLsizei bufSize,void* values)const{(this->*(this->m_ptr_glGetnMinmax))(target,reset,format,type,bufSize,values);}
inline void glUniform3uivEXT(GLint location,GLsizei count,const GLuint* value)const{(this->*(this->m_ptr_glUniform3uivEXT))(location,count,value);}
inline void glPopGroupMarkerEXT()const{(this->*(this->m_ptr_glPopGroupMarkerEXT))();}
inline void glClearNamedFramebufferuiv(GLuint framebuffer,GLenum buffer,GLint drawbuffer,const GLuint* value)const{(this->*(this->m_ptr_glClearNamedFramebufferuiv))(framebuffer,buffer,drawbuffer,value);}
inline void glSetLocalConstantEXT(GLuint id,GLenum type,const void* addr)const{(this->*(this->m_ptr_glSetLocalConstantEXT))(id,type,addr);}
inline void glGetVertexAttribfv(GLuint index,GLenum pname,GLfloat* params)const{(this->*(this->m_ptr_glGetVertexAttribfv))(index,pname,params);}
inline void glDispatchCompute(GLuint num_groups_x,GLuint num_groups_y,GLuint num_groups_z)const{(this->*(this->m_ptr_glDispatchCompute))(num_groups_x,num_groups_y,num_groups_z);}
inline void glGetActiveAttrib(GLuint program,GLuint index,GLsizei bufSize,GLsizei* length,GLint* size,GLenum* type,GLchar* name)const{(this->*(this->m_ptr_glGetActiveAttrib))(program,index,bufSize,length,size,type,name);}
inline void glPixelTransferi(GLenum pname,GLint param)const{(this->*(this->m_ptr_glPixelTransferi))(pname,param);}
inline void glTexSubImage2D(GLenum target,GLint level,GLint xoffset,GLint yoffset,GLsizei width,GLsizei height,GLenum format,GLenum type,const GLvoid* pixels)const{(this->*(this->m_ptr_glTexSubImage2D))(target,level,xoffset,yoffset,width,height,format,type,pixels);}
inline void glClearBufferfv(GLenum buffer,GLint drawbuffer,const GLfloat* value)const{(this->*(this->m_ptr_glClearBufferfv))(buffer,drawbuffer,value);}
inline void glLogicOp(GLenum opcode)const{(this->*(this->m_ptr_glLogicOp))(opcode);}
inline void glProgramUniformMatrix3x4fv(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLfloat* value)const{(this->*(this->m_ptr_glProgramUniformMatrix3x4fv))(program,location,count,transpose,value);}
inline void glPixelTransferf(GLenum pname,GLfloat param)const{(this->*(this->m_ptr_glPixelTransferf))(pname,param);}
inline void glGetTextureParameterIuiv(GLuint texture,GLenum pname,GLuint* params)const{(this->*(this->m_ptr_glGetTextureParameterIuiv))(texture,pname,params);}
inline void glProgramUniformMatrix4dv(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLdouble* value)const{(this->*(this->m_ptr_glProgramUniformMatrix4dv))(program,location,count,transpose,value);}
inline void glFramebufferTexture1DEXT(GLenum target,GLenum attachment,GLenum textarget,GLuint texture,GLint level)const{(this->*(this->m_ptr_glFramebufferTexture1DEXT))(target,attachment,textarget,texture,level);}
inline void glTextureParameterIiv(GLuint texture,GLenum pname,const GLint* params)const{(this->*(this->m_ptr_glTextureParameterIiv))(texture,pname,params);}
inline void glGetSeparableFilterEXT(GLenum target,GLenum format,GLenum type,void* row,void* column,void* span)const{(this->*(this->m_ptr_glGetSeparableFilterEXT))(target,format,type,row,column,span);}
inline void glDrawTransformFeedbackStream(GLenum mode,GLuint id,GLuint stream)const{(this->*(this->m_ptr_glDrawTransformFeedbackStream))(mode,id,stream);}
inline void glVertexArrayMultiTexCoordOffsetEXT(GLuint vaobj,GLuint buffer,GLenum texunit,GLint size,GLenum type,GLsizei stride,GLintptr offset)const{(this->*(this->m_ptr_glVertexArrayMultiTexCoordOffsetEXT))(vaobj,buffer,texunit,size,type,stride,offset);}
inline void glProvokingVertex(GLenum mode)const{(this->*(this->m_ptr_glProvokingVertex))(mode);}
inline void glShaderBinary(GLsizei count,const GLuint* shaders,GLenum binaryformat,const void* binary,GLsizei length)const{(this->*(this->m_ptr_glShaderBinary))(count,shaders,binaryformat,binary,length);}
inline void glGetMultiTexGenivEXT(GLenum texunit,GLenum coord,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetMultiTexGenivEXT))(texunit,coord,pname,params);}
inline void glSwizzleEXT(GLuint res,GLuint in,GLenum outX,GLenum outY,GLenum outZ,GLenum outW)const{(this->*(this->m_ptr_glSwizzleEXT))(res,in,outX,outY,outZ,outW);}
inline void glClearColorIuiEXT(GLuint red,GLuint green,GLuint blue,GLuint alpha)const{(this->*(this->m_ptr_glClearColorIuiEXT))(red,green,blue,alpha);}
inline void glBindMultiTextureEXT(GLenum texunit,GLenum target,GLuint texture)const{(this->*(this->m_ptr_glBindMultiTextureEXT))(texunit,target,texture);}
inline void glTexGeniv(GLenum coord,GLenum pname,const GLint* params)const{(this->*(this->m_ptr_glTexGeniv))(coord,pname,params);}
inline void glDrawElements(GLenum mode,GLsizei count,GLenum type,const GLvoid* indices)const{(this->*(this->m_ptr_glDrawElements))(mode,count,type,indices);}
inline void glConvolutionFilter1DEXT(GLenum target,GLenum internalformat,GLsizei width,GLenum format,GLenum type,const void* image)const{(this->*(this->m_ptr_glConvolutionFilter1DEXT))(target,internalformat,width,format,type,image);}
inline void glDisableVertexArrayEXT(GLuint vaobj,GLenum array)const{(this->*(this->m_ptr_glDisableVertexArrayEXT))(vaobj,array);}
inline void glClientActiveTexture(GLenum texture)const{(this->*(this->m_ptr_glClientActiveTexture))(texture);}
inline void glUniform1iv(GLint location,GLsizei count,const GLint* value)const{(this->*(this->m_ptr_glUniform1iv))(location,count,value);}
inline GLuint glBindLightParameterEXT(GLenum light,GLenum value)const{return (this->*(this->m_ptr_glBindLightParameterEXT))(light,value);}
inline void glDrawArraysInstanced(GLenum mode,GLint first,GLsizei count,GLsizei instancecount)const{(this->*(this->m_ptr_glDrawArraysInstanced))(mode,first,count,instancecount);}
inline void glTexBufferEXT(GLenum target,GLenum internalformat,GLuint buffer)const{(this->*(this->m_ptr_glTexBufferEXT))(target,internalformat,buffer);}
inline void glProgramUniformMatrix2fv(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLfloat* value)const{(this->*(this->m_ptr_glProgramUniformMatrix2fv))(program,location,count,transpose,value);}
inline void glSamplerParameteriv(GLuint sampler,GLenum pname,const GLint* param)const{(this->*(this->m_ptr_glSamplerParameteriv))(sampler,pname,param);}
inline void glVertexAttrib4uiv(GLuint index,const GLuint* v)const{(this->*(this->m_ptr_glVertexAttrib4uiv))(index,v);}
inline void glEndQueryIndexed(GLenum target,GLuint index)const{(this->*(this->m_ptr_glEndQueryIndexed))(target,index);}
inline void glProgramUniform1iv(GLuint program,GLint location,GLsizei count,const GLint* value)const{(this->*(this->m_ptr_glProgramUniform1iv))(program,location,count,value);}
inline void glBindRenderbuffer(GLenum target,GLuint renderbuffer)const{(this->*(this->m_ptr_glBindRenderbuffer))(target,renderbuffer);}
inline void glMaterialiv(GLenum face,GLenum pname,const GLint* params)const{(this->*(this->m_ptr_glMaterialiv))(face,pname,params);}
inline GLboolean glIsProgram(GLuint program)const{return (this->*(this->m_ptr_glIsProgram))(program);}
inline void glGetLocalConstantBooleanvEXT(GLuint id,GLenum value,GLboolean* data)const{(this->*(this->m_ptr_glGetLocalConstantBooleanvEXT))(id,value,data);}
inline void glUniformMatrix3x2dv(GLint location,GLsizei count,GLboolean transpose,const GLdouble* value)const{(this->*(this->m_ptr_glUniformMatrix3x2dv))(location,count,transpose,value);}
inline void glVertexAttrib4fv(GLuint index,const GLfloat* v)const{(this->*(this->m_ptr_glVertexAttrib4fv))(index,v);}
inline void glPushClientAttrib(GLbitfield mask)const{(this->*(this->m_ptr_glPushClientAttrib))(mask);}
inline void glGetnPixelMapfv(GLenum map,GLsizei bufSize,GLfloat* values)const{(this->*(this->m_ptr_glGetnPixelMapfv))(map,bufSize,values);}
inline void glVertexAttrib2fv(GLuint index,const GLfloat* v)const{(this->*(this->m_ptr_glVertexAttrib2fv))(index,v);}
inline void glCopyConvolutionFilter2D(GLenum target,GLenum internalformat,GLint x,GLint y,GLsizei width,GLsizei height)const{(this->*(this->m_ptr_glCopyConvolutionFilter2D))(target,internalformat,x,y,width,height);}
inline void glDisableClientState(GLenum cap)const{(this->*(this->m_ptr_glDisableClientState))(cap);}
inline void glVertexArrayIndexOffsetEXT(GLuint vaobj,GLuint buffer,GLenum type,GLsizei stride,GLintptr offset)const{(this->*(this->m_ptr_glVertexArrayIndexOffsetEXT))(vaobj,buffer,type,stride,offset);}
inline void glPixelTransformParameterivEXT(GLenum target,GLenum pname,const GLint* params)const{(this->*(this->m_ptr_glPixelTransformParameterivEXT))(target,pname,params);}
inline void glDisableClientStateiEXT(GLenum array,GLuint index)const{(this->*(this->m_ptr_glDisableClientStateiEXT))(array,index);}
inline void glGetLocalConstantIntegervEXT(GLuint id,GLenum value,GLint* data)const{(this->*(this->m_ptr_glGetLocalConstantIntegervEXT))(id,value,data);}
inline void glColor4uiv(const GLuint* v)const{(this->*(this->m_ptr_glColor4uiv))(v);}
inline void glProgramUniform3i(GLuint program,GLint location,GLint v0,GLint v1,GLint v2)const{(this->*(this->m_ptr_glProgramUniform3i))(program,location,v0,v1,v2);}
inline void glMultiTexParameterIuivEXT(GLenum texunit,GLenum target,GLenum pname,const GLuint* params)const{(this->*(this->m_ptr_glMultiTexParameterIuivEXT))(texunit,target,pname,params);}
inline void glEvalMesh2(GLenum mode,GLint i1,GLint i2,GLint j1,GLint j2)const{(this->*(this->m_ptr_glEvalMesh2))(mode,i1,i2,j1,j2);}
inline void glEvalMesh1(GLenum mode,GLint i1,GLint i2)const{(this->*(this->m_ptr_glEvalMesh1))(mode,i1,i2);}
inline void glProgramUniform3f(GLuint program,GLint location,GLfloat v0,GLfloat v1,GLfloat v2)const{(this->*(this->m_ptr_glProgramUniform3f))(program,location,v0,v1,v2);}
inline void glProgramUniform3d(GLuint program,GLint location,GLdouble v0,GLdouble v1,GLdouble v2)const{(this->*(this->m_ptr_glProgramUniform3d))(program,location,v0,v1,v2);}
inline void glEvalCoord2fv(const GLfloat* u)const{(this->*(this->m_ptr_glEvalCoord2fv))(u);}
inline void glProgramLocalParameters4fvEXT(GLenum target,GLuint index,GLsizei count,const GLfloat* params)const{(this->*(this->m_ptr_glProgramLocalParameters4fvEXT))(target,index,count,params);}
inline void glVertexAttribI1ui(GLuint index,GLuint x)const{(this->*(this->m_ptr_glVertexAttribI1ui))(index,x);}
inline void glCompressedMultiTexImage3DEXT(GLenum texunit,GLenum target,GLint level,GLenum internalformat,GLsizei width,GLsizei height,GLsizei depth,GLint border,GLsizei imageSize,const void* bits)const{(this->*(this->m_ptr_glCompressedMultiTexImage3DEXT))(texunit,target,level,internalformat,width,height,depth,border,imageSize,bits);}
inline void glGetRenderbufferParameterivEXT(GLenum target,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetRenderbufferParameterivEXT))(target,pname,params);}
inline void glGetnPolygonStipple(GLsizei bufSize,GLubyte* pattern)const{(this->*(this->m_ptr_glGetnPolygonStipple))(bufSize,pattern);}
inline void glGetNamedRenderbufferParameterivEXT(GLuint renderbuffer,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetNamedRenderbufferParameterivEXT))(renderbuffer,pname,params);}
inline void glMultiTexGendvEXT(GLenum texunit,GLenum coord,GLenum pname,const GLdouble* params)const{(this->*(this->m_ptr_glMultiTexGendvEXT))(texunit,coord,pname,params);}
inline void glBlendEquationSeparateEXT(GLenum modeRGB,GLenum modeAlpha)const{(this->*(this->m_ptr_glBlendEquationSeparateEXT))(modeRGB,modeAlpha);}
inline void glInvalidateTexSubImage(GLuint texture,GLint level,GLint xoffset,GLint yoffset,GLint zoffset,GLsizei width,GLsizei height,GLsizei depth)const{(this->*(this->m_ptr_glInvalidateTexSubImage))(texture,level,xoffset,yoffset,zoffset,width,height,depth);}
inline void glGetInteger64v(GLenum pname,GLint64* data)const{(this->*(this->m_ptr_glGetInteger64v))(pname,data);}
inline void glClipPlane(GLenum plane,const GLdouble* equation)const{(this->*(this->m_ptr_glClipPlane))(plane,equation);}
inline void glIndexub(GLubyte c)const{(this->*(this->m_ptr_glIndexub))(c);}
inline void glNamedFramebufferRenderbuffer(GLuint framebuffer,GLenum attachment,GLenum renderbuffertarget,GLuint renderbuffer)const{(this->*(this->m_ptr_glNamedFramebufferRenderbuffer))(framebuffer,attachment,renderbuffertarget,renderbuffer);}
inline void glGetFloatIndexedvEXT(GLenum target,GLuint index,GLfloat* data)const{(this->*(this->m_ptr_glGetFloatIndexedvEXT))(target,index,data);}
inline void glVertexAttrib4Niv(GLuint index,const GLint* v)const{(this->*(this->m_ptr_glVertexAttrib4Niv))(index,v);}
inline void glClearBufferiv(GLenum buffer,GLint drawbuffer,const GLint* value)const{(this->*(this->m_ptr_glClearBufferiv))(buffer,drawbuffer,value);}
inline void glColorP4uiv(GLenum type,const GLuint* color)const{(this->*(this->m_ptr_glColorP4uiv))(type,color);}
inline void glGetNamedProgramStringEXT(GLuint program,GLenum target,GLenum pname,void* string)const{(this->*(this->m_ptr_glGetNamedProgramStringEXT))(program,target,pname,string);}
inline void glGetTextureLevelParameterfv(GLuint texture,GLint level,GLenum pname,GLfloat* params)const{(this->*(this->m_ptr_glGetTextureLevelParameterfv))(texture,level,pname,params);}
inline void glTexCoord3dv(const GLdouble* v)const{(this->*(this->m_ptr_glTexCoord3dv))(v);}
inline void glGetSamplerParameterIuiv(GLuint sampler,GLenum pname,GLuint* params)const{(this->*(this->m_ptr_glGetSamplerParameterIuiv))(sampler,pname,params);}
inline void glTexCoordP3ui(GLenum type,GLuint coords)const{(this->*(this->m_ptr_glTexCoordP3ui))(type,coords);}
inline void glTextureSubImage1D(GLuint texture,GLint level,GLint xoffset,GLsizei width,GLenum format,GLenum type,const void* pixels)const{(this->*(this->m_ptr_glTextureSubImage1D))(texture,level,xoffset,width,format,type,pixels);}
inline void glVertexAttribLPointerEXT(GLuint index,GLint size,GLenum type,GLsizei stride,const void* pointer)const{(this->*(this->m_ptr_glVertexAttribLPointerEXT))(index,size,type,stride,pointer);}
inline void glWindowPos3s(GLshort x,GLshort y,GLshort z)const{(this->*(this->m_ptr_glWindowPos3s))(x,y,z);}
inline void glClearDepthf(GLfloat d)const{(this->*(this->m_ptr_glClearDepthf))(d);}
inline void glWindowPos3i(GLint x,GLint y,GLint z)const{(this->*(this->m_ptr_glWindowPos3i))(x,y,z);}
inline void glWindowPos3d(GLdouble x,GLdouble y,GLdouble z)const{(this->*(this->m_ptr_glWindowPos3d))(x,y,z);}
inline void glWindowPos3f(GLfloat x,GLfloat y,GLfloat z)const{(this->*(this->m_ptr_glWindowPos3f))(x,y,z);}
inline GLboolean glIsEnabledIndexedEXT(GLenum target,GLuint index)const{return (this->*(this->m_ptr_glIsEnabledIndexedEXT))(target,index);}
inline void glGetNamedProgramivEXT(GLuint program,GLenum target,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetNamedProgramivEXT))(program,target,pname,params);}
inline void glColor3us(GLushort red,GLushort green,GLushort blue)const{(this->*(this->m_ptr_glColor3us))(red,green,blue);}
inline void glMultiTexCoord4s(GLenum target,GLshort s,GLshort t,GLshort r,GLshort q)const{(this->*(this->m_ptr_glMultiTexCoord4s))(target,s,t,r,q);}
inline void glProgramUniformMatrix4x3dv(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLdouble* value)const{(this->*(this->m_ptr_glProgramUniformMatrix4x3dv))(program,location,count,transpose,value);}
inline void glGetNamedProgramLocalParameterIuivEXT(GLuint program,GLenum target,GLuint index,GLuint* params)const{(this->*(this->m_ptr_glGetNamedProgramLocalParameterIuivEXT))(program,target,index,params);}
inline void glReadnPixels(GLint x,GLint y,GLsizei width,GLsizei height,GLenum format,GLenum type,GLsizei bufSize,void* data)const{(this->*(this->m_ptr_glReadnPixels))(x,y,width,height,format,type,bufSize,data);}
inline void glMultiTexCoord4f(GLenum target,GLfloat s,GLfloat t,GLfloat r,GLfloat q)const{(this->*(this->m_ptr_glMultiTexCoord4f))(target,s,t,r,q);}
inline void glColor3ub(GLubyte red,GLubyte green,GLubyte blue)const{(this->*(this->m_ptr_glColor3ub))(red,green,blue);}
inline void glMultiTexCoord4d(GLenum target,GLdouble s,GLdouble t,GLdouble r,GLdouble q)const{(this->*(this->m_ptr_glMultiTexCoord4d))(target,s,t,r,q);}
inline void glColor3ui(GLuint red,GLuint green,GLuint blue)const{(this->*(this->m_ptr_glColor3ui))(red,green,blue);}
inline void glProgramUniform4fvEXT(GLuint program,GLint location,GLsizei count,const GLfloat* value)const{(this->*(this->m_ptr_glProgramUniform4fvEXT))(program,location,count,value);}
inline void glMultiTexCoord4i(GLenum target,GLint s,GLint t,GLint r,GLint q)const{(this->*(this->m_ptr_glMultiTexCoord4i))(target,s,t,r,q);}
inline GLenum glCheckFramebufferStatusEXT(GLenum target)const{return (this->*(this->m_ptr_glCheckFramebufferStatusEXT))(target);}
inline void glGetPolygonStipple(GLubyte* mask)const{(this->*(this->m_ptr_glGetPolygonStipple))(mask);}
inline void glVertexAttribI4ui(GLuint index,GLuint x,GLuint y,GLuint z,GLuint w)const{(this->*(this->m_ptr_glVertexAttribI4ui))(index,x,y,z,w);}
inline void glMultiTexRenderbufferEXT(GLenum texunit,GLenum target,GLuint renderbuffer)const{(this->*(this->m_ptr_glMultiTexRenderbufferEXT))(texunit,target,renderbuffer);}
inline void glDepthFunc(GLenum func)const{(this->*(this->m_ptr_glDepthFunc))(func);}
inline void glGetMapdv(GLenum target,GLenum query,GLdouble* v)const{(this->*(this->m_ptr_glGetMapdv))(target,query,v);}
inline void glBlendEquation(GLenum mode)const{(this->*(this->m_ptr_glBlendEquation))(mode);}
inline void glUnlockArraysEXT()const{(this->*(this->m_ptr_glUnlockArraysEXT))();}
inline void glGetQueryObjectui64vEXT(GLuint id,GLenum pname,GLuint64* params)const{(this->*(this->m_ptr_glGetQueryObjectui64vEXT))(id,pname,params);}
inline void glVertexAttribI4uivEXT(GLuint index,const GLuint* v)const{(this->*(this->m_ptr_glVertexAttribI4uivEXT))(index,v);}
inline void glMultiTexCoord3dv(GLenum target,const GLdouble* v)const{(this->*(this->m_ptr_glMultiTexCoord3dv))(target,v);}
inline void glColor4sv(const GLshort* v)const{(this->*(this->m_ptr_glColor4sv))(v);}
inline void glPopClientAttrib()const{(this->*(this->m_ptr_glPopClientAttrib))();}
inline void glClearBufferData(GLenum target,GLenum internalformat,GLenum format,GLenum type,const void* data)const{(this->*(this->m_ptr_glClearBufferData))(target,internalformat,format,type,data);}
inline void glBeginTransformFeedback(GLenum primitiveMode)const{(this->*(this->m_ptr_glBeginTransformFeedback))(primitiveMode);}
inline void glColor3iv(const GLint* v)const{(this->*(this->m_ptr_glColor3iv))(v);}
inline void glCompressedTexImage1D(GLenum target,GLint level,GLenum internalformat,GLsizei width,GLint border,GLsizei imageSize,const GLvoid* data)const{(this->*(this->m_ptr_glCompressedTexImage1D))(target,level,internalformat,width,border,imageSize,data);}
inline void glDeleteTransformFeedbacks(GLsizei n,const GLuint* ids)const{(this->*(this->m_ptr_glDeleteTransformFeedbacks))(n,ids);}
inline void glDrawRangeElementsBaseVertex(GLenum mode,GLuint start,GLuint end,GLsizei count,GLenum type,const void* indices,GLint basevertex)const{(this->*(this->m_ptr_glDrawRangeElementsBaseVertex))(mode,start,end,count,type,indices,basevertex);}
inline void glTextureStorage3DMultisampleEXT(GLuint texture,GLenum target,GLsizei samples,GLenum internalformat,GLsizei width,GLsizei height,GLsizei depth,GLboolean fixedsamplelocations)const{(this->*(this->m_ptr_glTextureStorage3DMultisampleEXT))(texture,target,samples,internalformat,width,height,depth,fixedsamplelocations);}
inline void glBindAttribLocation(GLuint program,GLuint index,const GLchar* name)const{(this->*(this->m_ptr_glBindAttribLocation))(program,index,name);}
inline void glCompressedMultiTexImage1DEXT(GLenum texunit,GLenum target,GLint level,GLenum internalformat,GLsizei width,GLint border,GLsizei imageSize,const void* bits)const{(this->*(this->m_ptr_glCompressedMultiTexImage1DEXT))(texunit,target,level,internalformat,width,border,imageSize,bits);}
inline void glProgramUniform2ivEXT(GLuint program,GLint location,GLsizei count,const GLint* value)const{(this->*(this->m_ptr_glProgramUniform2ivEXT))(program,location,count,value);}
inline void glPushGroupMarkerEXT(GLsizei length,const GLchar* marker)const{(this->*(this->m_ptr_glPushGroupMarkerEXT))(length,marker);}
inline void glVertexAttrib1dv(GLuint index,const GLdouble* v)const{(this->*(this->m_ptr_glVertexAttrib1dv))(index,v);}
inline void glBufferSubData(GLenum target,GLintptr offset,GLsizeiptr size,const void* data)const{(this->*(this->m_ptr_glBufferSubData))(target,offset,size,data);}
inline void glBlendFuncSeparatei(GLuint buf,GLenum srcRGB,GLenum dstRGB,GLenum srcAlpha,GLenum dstAlpha)const{(this->*(this->m_ptr_glBlendFuncSeparatei))(buf,srcRGB,dstRGB,srcAlpha,dstAlpha);}
inline void glGetBooleanIndexedvEXT(GLenum target,GLuint index,GLboolean* data)const{(this->*(this->m_ptr_glGetBooleanIndexedvEXT))(target,index,data);}
inline void glVertexP4uiv(GLenum type,const GLuint* value)const{(this->*(this->m_ptr_glVertexP4uiv))(type,value);}
inline void glUniform2ui(GLint location,GLuint v0,GLuint v1)const{(this->*(this->m_ptr_glUniform2ui))(location,v0,v1);}
inline void glWindowPos2fv(const GLfloat* v)const{(this->*(this->m_ptr_glWindowPos2fv))(v);}
inline void glDisablei(GLenum target,GLuint index)const{(this->*(this->m_ptr_glDisablei))(target,index);}
inline void glGetSynciv(GLsync sync,GLenum pname,GLsizei bufSize,GLsizei* length,GLint* values)const{(this->*(this->m_ptr_glGetSynciv))(sync,pname,bufSize,length,values);}
inline void glProgramUniform2i(GLuint program,GLint location,GLint v0,GLint v1)const{(this->*(this->m_ptr_glProgramUniform2i))(program,location,v0,v1);}
inline void glProgramUniform2d(GLuint program,GLint location,GLdouble v0,GLdouble v1)const{(this->*(this->m_ptr_glProgramUniform2d))(program,location,v0,v1);}
inline void glProgramUniform2f(GLuint program,GLint location,GLfloat v0,GLfloat v1)const{(this->*(this->m_ptr_glProgramUniform2f))(program,location,v0,v1);}
inline void glGetProgramBinary(GLuint program,GLsizei bufSize,GLsizei* length,GLenum* binaryFormat,void* binary)const{(this->*(this->m_ptr_glGetProgramBinary))(program,bufSize,length,binaryFormat,binary);}
inline void glBinormal3iEXT(GLint bx,GLint by,GLint bz)const{(this->*(this->m_ptr_glBinormal3iEXT))(bx,by,bz);}
inline void glEvalPoint1(GLint i)const{(this->*(this->m_ptr_glEvalPoint1))(i);}
inline void glEvalPoint2(GLint i,GLint j)const{(this->*(this->m_ptr_glEvalPoint2))(i,j);}
inline void glPauseTransformFeedback()const{(this->*(this->m_ptr_glPauseTransformFeedback))();}
inline void glCreateTransformFeedbacks(GLsizei n,GLuint* ids)const{(this->*(this->m_ptr_glCreateTransformFeedbacks))(n,ids);}
inline void glTexturePageCommitmentEXT(GLuint texture,GLint level,GLint xoffset,GLint yoffset,GLint zoffset,GLsizei width,GLsizei height,GLsizei depth,GLboolean commit)const{(this->*(this->m_ptr_glTexturePageCommitmentEXT))(texture,level,xoffset,yoffset,zoffset,width,height,depth,commit);}
inline void glTexSubImage1D(GLenum target,GLint level,GLint xoffset,GLsizei width,GLenum format,GLenum type,const GLvoid* pixels)const{(this->*(this->m_ptr_glTexSubImage1D))(target,level,xoffset,width,format,type,pixels);}
inline void glConvolutionParameterfvEXT(GLenum target,GLenum pname,const GLfloat* params)const{(this->*(this->m_ptr_glConvolutionParameterfvEXT))(target,pname,params);}
inline void glBlitFramebufferEXT(GLint srcX0,GLint srcY0,GLint srcX1,GLint srcY1,GLint dstX0,GLint dstY0,GLint dstX1,GLint dstY1,GLbitfield mask,GLenum filter)const{(this->*(this->m_ptr_glBlitFramebufferEXT))(srcX0,srcY0,srcX1,srcY1,dstX0,dstY0,dstX1,dstY1,mask,filter);}
inline void glVertexAttribP3uiv(GLuint index,GLenum type,GLboolean normalized,const GLuint* value)const{(this->*(this->m_ptr_glVertexAttribP3uiv))(index,type,normalized,value);}
inline void glGetMultiTexLevelParameterivEXT(GLenum texunit,GLenum target,GLint level,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetMultiTexLevelParameterivEXT))(texunit,target,level,pname,params);}
inline void glVertexAttrib4sv(GLuint index,const GLshort* v)const{(this->*(this->m_ptr_glVertexAttrib4sv))(index,v);}
inline void glLoadName(GLuint name)const{(this->*(this->m_ptr_glLoadName))(name);}
inline void glBindVertexShaderEXT(GLuint id)const{(this->*(this->m_ptr_glBindVertexShaderEXT))(id);}
inline void glGetNamedProgramLocalParameterIivEXT(GLuint program,GLenum target,GLuint index,GLint* params)const{(this->*(this->m_ptr_glGetNamedProgramLocalParameterIivEXT))(program,target,index,params);}
inline void glProgramUniform3uiEXT(GLuint program,GLint location,GLuint v0,GLuint v1,GLuint v2)const{(this->*(this->m_ptr_glProgramUniform3uiEXT))(program,location,v0,v1,v2);}
inline void glProgramUniformMatrix4x2dvEXT(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLdouble* value)const{(this->*(this->m_ptr_glProgramUniformMatrix4x2dvEXT))(program,location,count,transpose,value);}
inline void glLoadMatrixf(const GLfloat* m)const{(this->*(this->m_ptr_glLoadMatrixf))(m);}
inline void glLoadMatrixd(const GLdouble* m)const{(this->*(this->m_ptr_glLoadMatrixd))(m);}
inline void glTexParameterfv(GLenum target,GLenum pname,const GLfloat* params)const{(this->*(this->m_ptr_glTexParameterfv))(target,pname,params);}
inline void glVariantdvEXT(GLuint id,const GLdouble* addr)const{(this->*(this->m_ptr_glVariantdvEXT))(id,addr);}
inline void glCullParameterfvEXT(GLenum pname,GLfloat* params)const{(this->*(this->m_ptr_glCullParameterfvEXT))(pname,params);}
inline void glUniform3dv(GLint location,GLsizei count,const GLdouble* value)const{(this->*(this->m_ptr_glUniform3dv))(location,count,value);}
inline void glProgramUniform3fv(GLuint program,GLint location,GLsizei count,const GLfloat* value)const{(this->*(this->m_ptr_glProgramUniform3fv))(program,location,count,value);}
inline GLuint glGenSymbolsEXT(GLenum datatype,GLenum storagetype,GLenum range,GLuint components)const{return (this->*(this->m_ptr_glGenSymbolsEXT))(datatype,storagetype,range,components);}
inline void glGetConvolutionFilter(GLenum target,GLenum format,GLenum type,GLvoid* image)const{(this->*(this->m_ptr_glGetConvolutionFilter))(target,format,type,image);}
inline void glProgramUniform1fvEXT(GLuint program,GLint location,GLsizei count,const GLfloat* value)const{(this->*(this->m_ptr_glProgramUniform1fvEXT))(program,location,count,value);}
inline void glTexImage1D(GLenum target,GLint level,GLint internalFormat,GLsizei width,GLint border,GLenum format,GLenum type,const GLvoid* pixels)const{(this->*(this->m_ptr_glTexImage1D))(target,level,internalFormat,width,border,format,type,pixels);}
inline void glGetQueryObjectui64v(GLuint id,GLenum pname,GLuint64* params)const{(this->*(this->m_ptr_glGetQueryObjectui64v))(id,pname,params);}
inline void glGetTextureImage(GLuint texture,GLint level,GLenum format,GLenum type,GLsizei bufSize,void* pixels)const{(this->*(this->m_ptr_glGetTextureImage))(texture,level,format,type,bufSize,pixels);}
inline void glProgramUniform1fv(GLuint program,GLint location,GLsizei count,const GLfloat* value)const{(this->*(this->m_ptr_glProgramUniform1fv))(program,location,count,value);}
inline void glUniformMatrix4fv(GLint location,GLsizei count,GLboolean transpose,const GLfloat* value)const{(this->*(this->m_ptr_glUniformMatrix4fv))(location,count,transpose,value);}
inline void glMultiDrawArraysEXT(GLenum mode,const GLint* first,const GLsizei* count,GLsizei primcount)const{(this->*(this->m_ptr_glMultiDrawArraysEXT))(mode,first,count,primcount);}
inline void glDeleteProgramPipelines(GLsizei n,const GLuint* pipelines)const{(this->*(this->m_ptr_glDeleteProgramPipelines))(n,pipelines);}
inline void glCopyColorSubTableEXT(GLenum target,GLsizei start,GLint x,GLint y,GLsizei width)const{(this->*(this->m_ptr_glCopyColorSubTableEXT))(target,start,x,y,width);}
inline void glVariantsvEXT(GLuint id,const GLshort* addr)const{(this->*(this->m_ptr_glVariantsvEXT))(id,addr);}
inline void glVertexArrayEdgeFlagOffsetEXT(GLuint vaobj,GLuint buffer,GLsizei stride,GLintptr offset)const{(this->*(this->m_ptr_glVertexArrayEdgeFlagOffsetEXT))(vaobj,buffer,stride,offset);}
inline void glWindowPos2s(GLshort x,GLshort y)const{(this->*(this->m_ptr_glWindowPos2s))(x,y);}
inline void glSecondaryColor3iEXT(GLint red,GLint green,GLint blue)const{(this->*(this->m_ptr_glSecondaryColor3iEXT))(red,green,blue);}
inline void glWindowPos2i(GLint x,GLint y)const{(this->*(this->m_ptr_glWindowPos2i))(x,y);}
inline void glWindowPos2f(GLfloat x,GLfloat y)const{(this->*(this->m_ptr_glWindowPos2f))(x,y);}
inline void glWindowPos2d(GLdouble x,GLdouble y)const{(this->*(this->m_ptr_glWindowPos2d))(x,y);}
inline void glUniform4uivEXT(GLint location,GLsizei count,const GLuint* value)const{(this->*(this->m_ptr_glUniform4uivEXT))(location,count,value);}
inline void glUniformSubroutinesuiv(GLenum shadertype,GLsizei count,const GLuint* indices)const{(this->*(this->m_ptr_glUniformSubroutinesuiv))(shadertype,count,indices);}
inline void glRectdv(const GLdouble* v1,const GLdouble* v2)const{(this->*(this->m_ptr_glRectdv))(v1,v2);}
inline void glVertexAttribI4uiEXT(GLuint index,GLuint x,GLuint y,GLuint z,GLuint w)const{(this->*(this->m_ptr_glVertexAttribI4uiEXT))(index,x,y,z,w);}
inline void glSecondaryColor3ubEXT(GLubyte red,GLubyte green,GLubyte blue)const{(this->*(this->m_ptr_glSecondaryColor3ubEXT))(red,green,blue);}
inline void glCompressedMultiTexSubImage1DEXT(GLenum texunit,GLenum target,GLint level,GLint xoffset,GLsizei width,GLenum format,GLsizei imageSize,const void* bits)const{(this->*(this->m_ptr_glCompressedMultiTexSubImage1DEXT))(texunit,target,level,xoffset,width,format,imageSize,bits);}
inline void glMultiTexGendEXT(GLenum texunit,GLenum coord,GLenum pname,GLdouble param)const{(this->*(this->m_ptr_glMultiTexGendEXT))(texunit,coord,pname,param);}
inline void glColorP3uiv(GLenum type,const GLuint* color)const{(this->*(this->m_ptr_glColorP3uiv))(type,color);}
inline void glFogCoordfv(const GLfloat* coord)const{(this->*(this->m_ptr_glFogCoordfv))(coord);}
inline void glCompileShader(GLuint shader)const{(this->*(this->m_ptr_glCompileShader))(shader);}
inline void glUniform1uivEXT(GLint location,GLsizei count,const GLuint* value)const{(this->*(this->m_ptr_glUniform1uivEXT))(location,count,value);}
inline void glIndexfv(const GLfloat* c)const{(this->*(this->m_ptr_glIndexfv))(c);}
inline void glGetCompressedTextureImage(GLuint texture,GLint level,GLsizei bufSize,void* pixels)const{(this->*(this->m_ptr_glGetCompressedTextureImage))(texture,level,bufSize,pixels);}
inline void glGetUniformuivEXT(GLuint program,GLint location,GLuint* params)const{(this->*(this->m_ptr_glGetUniformuivEXT))(program,location,params);}
inline void glFramebufferTextureEXT(GLenum target,GLenum attachment,GLuint texture,GLint level)const{(this->*(this->m_ptr_glFramebufferTextureEXT))(target,attachment,texture,level);}
inline void glVertexAttribIPointer(GLuint index,GLint size,GLenum type,GLsizei stride,const void* pointer)const{(this->*(this->m_ptr_glVertexAttribIPointer))(index,size,type,stride,pointer);}
inline void glMultiTexCoordP3ui(GLenum texture,GLenum type,GLuint coords)const{(this->*(this->m_ptr_glMultiTexCoordP3ui))(texture,type,coords);}
inline void glGetNamedProgramLocalParameterfvEXT(GLuint program,GLenum target,GLuint index,GLfloat* params)const{(this->*(this->m_ptr_glGetNamedProgramLocalParameterfvEXT))(program,target,index,params);}
inline void glSeparableFilter2DEXT(GLenum target,GLenum internalformat,GLsizei width,GLsizei height,GLenum format,GLenum type,const void* row,const void* column)const{(this->*(this->m_ptr_glSeparableFilter2DEXT))(target,internalformat,width,height,format,type,row,column);}
inline void glInvalidateFramebuffer(GLenum target,GLsizei numAttachments,const GLenum* attachments)const{(this->*(this->m_ptr_glInvalidateFramebuffer))(target,numAttachments,attachments);}
inline void glVertexAttrib1d(GLuint index,GLdouble x)const{(this->*(this->m_ptr_glVertexAttrib1d))(index,x);}
inline void glVertexAttrib1f(GLuint index,GLfloat x)const{(this->*(this->m_ptr_glVertexAttrib1f))(index,x);}
inline void glVertex4fv(const GLfloat* v)const{(this->*(this->m_ptr_glVertex4fv))(v);}
inline void glClearNamedFramebufferfi(GLuint framebuffer,GLenum buffer,GLint drawbuffer,GLfloat depth,GLint stencil)const{(this->*(this->m_ptr_glClearNamedFramebufferfi))(framebuffer,buffer,drawbuffer,depth,stencil);}
inline void glGetQueryBufferObjectuiv(GLuint id,GLuint buffer,GLenum pname,GLintptr offset)const{(this->*(this->m_ptr_glGetQueryBufferObjectuiv))(id,buffer,pname,offset);}
inline void glClearNamedFramebufferfv(GLuint framebuffer,GLenum buffer,GLint drawbuffer,const GLfloat* value)const{(this->*(this->m_ptr_glClearNamedFramebufferfv))(framebuffer,buffer,drawbuffer,value);}
inline void glEndVertexShaderEXT()const{(this->*(this->m_ptr_glEndVertexShaderEXT))();}
inline void glVertexAttrib1s(GLuint index,GLshort x)const{(this->*(this->m_ptr_glVertexAttrib1s))(index,x);}
inline void glMultiTexCoord1sv(GLenum target,const GLshort* v)const{(this->*(this->m_ptr_glMultiTexCoord1sv))(target,v);}
inline void glRasterPos2s(GLshort x,GLshort y)const{(this->*(this->m_ptr_glRasterPos2s))(x,y);}
inline void glGetSeparableFilter(GLenum target,GLenum format,GLenum type,GLvoid* row,GLvoid* column,GLvoid* span)const{(this->*(this->m_ptr_glGetSeparableFilter))(target,format,type,row,column,span);}
inline void glDeleteProgram(GLuint program)const{(this->*(this->m_ptr_glDeleteProgram))(program);}
inline void glColor4bv(const GLbyte* v)const{(this->*(this->m_ptr_glColor4bv))(v);}
inline void glRasterPos2f(GLfloat x,GLfloat y)const{(this->*(this->m_ptr_glRasterPos2f))(x,y);}
inline void glRasterPos2d(GLdouble x,GLdouble y)const{(this->*(this->m_ptr_glRasterPos2d))(x,y);}
inline void glLoadIdentity()const{(this->*(this->m_ptr_glLoadIdentity))();}
inline void glRasterPos2i(GLint x,GLint y)const{(this->*(this->m_ptr_glRasterPos2i))(x,y);}
inline void glUniformMatrix4x3fv(GLint location,GLsizei count,GLboolean transpose,const GLfloat* value)const{(this->*(this->m_ptr_glUniformMatrix4x3fv))(location,count,transpose,value);}
inline void glBindImageTextures(GLuint first,GLsizei count,const GLuint* textures)const{(this->*(this->m_ptr_glBindImageTextures))(first,count,textures);}
inline void glTextureBarrier()const{(this->*(this->m_ptr_glTextureBarrier))();}
inline void glMultiTexParameterIivEXT(GLenum texunit,GLenum target,GLenum pname,const GLint* params)const{(this->*(this->m_ptr_glMultiTexParameterIivEXT))(texunit,target,pname,params);}
inline void glClearBufferfi(GLenum buffer,GLint drawbuffer,GLfloat depth,GLint stencil)const{(this->*(this->m_ptr_glClearBufferfi))(buffer,drawbuffer,depth,stencil);}
inline void glDrawArraysIndirect(GLenum mode,const void* indirect)const{(this->*(this->m_ptr_glDrawArraysIndirect))(mode,indirect);}
inline void glGenVertexArrays(GLsizei n,GLuint* arrays)const{(this->*(this->m_ptr_glGenVertexArrays))(n,arrays);}
inline void glEnableVertexArrayAttrib(GLuint vaobj,GLuint index)const{(this->*(this->m_ptr_glEnableVertexArrayAttrib))(vaobj,index);}
inline void glProgramUniformMatrix3x2dv(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLdouble* value)const{(this->*(this->m_ptr_glProgramUniformMatrix3x2dv))(program,location,count,transpose,value);}
inline void glGetSamplerParameterIiv(GLuint sampler,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetSamplerParameterIiv))(sampler,pname,params);}
inline void glGetQueryBufferObjecti64v(GLuint id,GLuint buffer,GLenum pname,GLintptr offset)const{(this->*(this->m_ptr_glGetQueryBufferObjecti64v))(id,buffer,pname,offset);}
inline void glGetVertexAttribdv(GLuint index,GLenum pname,GLdouble* params)const{(this->*(this->m_ptr_glGetVertexAttribdv))(index,pname,params);}
inline GLboolean glAreTexturesResidentEXT(GLsizei n,const GLuint* textures,GLboolean* residences)const{return (this->*(this->m_ptr_glAreTexturesResidentEXT))(n,textures,residences);}
inline void glProgramUniformMatrix3x4dv(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLdouble* value)const{(this->*(this->m_ptr_glProgramUniformMatrix3x4dv))(program,location,count,transpose,value);}
inline void glSecondaryColor3sEXT(GLshort red,GLshort green,GLshort blue)const{(this->*(this->m_ptr_glSecondaryColor3sEXT))(red,green,blue);}
inline void glGetTexParameterIivEXT(GLenum target,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetTexParameterIivEXT))(target,pname,params);}
inline void glVertexAttribI4ivEXT(GLuint index,const GLint* v)const{(this->*(this->m_ptr_glVertexAttribI4ivEXT))(index,v);}
inline void glUniform1ui(GLint location,GLuint v0)const{(this->*(this->m_ptr_glUniform1ui))(location,v0);}
inline void glVertexAttribI4svEXT(GLuint index,const GLshort* v)const{(this->*(this->m_ptr_glVertexAttribI4svEXT))(index,v);}
inline void glMemoryBarrier(GLbitfield barriers)const{(this->*(this->m_ptr_glMemoryBarrier))(barriers);}
inline void glBindImageTextureEXT(GLuint index,GLuint texture,GLint level,GLboolean layered,GLint layer,GLenum access,GLint format)const{(this->*(this->m_ptr_glBindImageTextureEXT))(index,texture,level,layered,layer,access,format);}
inline GLint glGetFragDataLocation(GLuint program,const GLchar* name)const{return (this->*(this->m_ptr_glGetFragDataLocation))(program,name);}
inline void glTextureStorage2DMultisampleEXT(GLuint texture,GLenum target,GLsizei samples,GLenum internalformat,GLsizei width,GLsizei height,GLboolean fixedsamplelocations)const{(this->*(this->m_ptr_glTextureStorage2DMultisampleEXT))(texture,target,samples,internalformat,width,height,fixedsamplelocations);}
inline void glGetMaterialfv(GLenum face,GLenum pname,GLfloat* params)const{(this->*(this->m_ptr_glGetMaterialfv))(face,pname,params);}
inline void glPixelMapuiv(GLenum map,GLsizei mapsize,const GLuint* values)const{(this->*(this->m_ptr_glPixelMapuiv))(map,mapsize,values);}
inline void glColorPointerEXT(GLint size,GLenum type,GLsizei stride,GLsizei count,const void* pointer)const{(this->*(this->m_ptr_glColorPointerEXT))(size,type,stride,count,pointer);}
inline void glEnableClientStateiEXT(GLenum array,GLuint index)const{(this->*(this->m_ptr_glEnableClientStateiEXT))(array,index);}
inline void glClearTexSubImage(GLuint texture,GLint level,GLint xoffset,GLint yoffset,GLint zoffset,GLsizei width,GLsizei height,GLsizei depth,GLenum format,GLenum type,const void* data)const{(this->*(this->m_ptr_glClearTexSubImage))(texture,level,xoffset,yoffset,zoffset,width,height,depth,format,type,data);}
inline void glGetTextureParameterIiv(GLuint texture,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetTextureParameterIiv))(texture,pname,params);}
inline void glVariantusvEXT(GLuint id,const GLushort* addr)const{(this->*(this->m_ptr_glVariantusvEXT))(id,addr);}
inline void glCompressedTextureImage3DEXT(GLuint texture,GLenum target,GLint level,GLenum internalformat,GLsizei width,GLsizei height,GLsizei depth,GLint border,GLsizei imageSize,const void* bits)const{(this->*(this->m_ptr_glCompressedTextureImage3DEXT))(texture,target,level,internalformat,width,height,depth,border,imageSize,bits);}
inline void glGetVertexArrayIntegeri_vEXT(GLuint vaobj,GLuint index,GLenum pname,GLint* param)const{(this->*(this->m_ptr_glGetVertexArrayIntegeri_vEXT))(vaobj,index,pname,param);}
inline void glVertexAttribI4ubv(GLuint index,const GLubyte* v)const{(this->*(this->m_ptr_glVertexAttribI4ubv))(index,v);}
inline void glProgramUniformMatrix4x2dv(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLdouble* value)const{(this->*(this->m_ptr_glProgramUniformMatrix4x2dv))(program,location,count,transpose,value);}
inline GLboolean glIsShader(GLuint shader)const{return (this->*(this->m_ptr_glIsShader))(shader);}
inline void glConvolutionParameteriv(GLenum target,GLenum pname,const GLint* params)const{(this->*(this->m_ptr_glConvolutionParameteriv))(target,pname,params);}
inline void glCopyMultiTexSubImage2DEXT(GLenum texunit,GLenum target,GLint level,GLint xoffset,GLint yoffset,GLint x,GLint y,GLsizei width,GLsizei height)const{(this->*(this->m_ptr_glCopyMultiTexSubImage2DEXT))(texunit,target,level,xoffset,yoffset,x,y,width,height);}
inline void glEnable(GLenum cap)const{(this->*(this->m_ptr_glEnable))(cap);}
inline void glGetActiveUniformsiv(GLuint program,GLsizei uniformCount,const GLuint* uniformIndices,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetActiveUniformsiv))(program,uniformCount,uniformIndices,pname,params);}
inline void glBlendEquationi(GLuint buf,GLenum mode)const{(this->*(this->m_ptr_glBlendEquationi))(buf,mode);}
inline GLint glGetAttribLocation(GLuint program,const GLchar* name)const{return (this->*(this->m_ptr_glGetAttribLocation))(program,name);}
inline void glVertexAttrib4dv(GLuint index,const GLdouble* v)const{(this->*(this->m_ptr_glVertexAttrib4dv))(index,v);}
inline void glGetTextureParameteriv(GLuint texture,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetTextureParameteriv))(texture,pname,params);}
inline void glShaderOp2EXT(GLenum op,GLuint res,GLuint arg1,GLuint arg2)const{(this->*(this->m_ptr_glShaderOp2EXT))(op,res,arg1,arg2);}
inline void glNamedFramebufferParameteri(GLuint framebuffer,GLenum pname,GLint param)const{(this->*(this->m_ptr_glNamedFramebufferParameteri))(framebuffer,pname,param);}
inline void glProgramUniform3ui(GLuint program,GLint location,GLuint v0,GLuint v1,GLuint v2)const{(this->*(this->m_ptr_glProgramUniform3ui))(program,location,v0,v1,v2);}
inline void glGetNamedBufferParameterivEXT(GLuint buffer,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetNamedBufferParameterivEXT))(buffer,pname,params);}
inline void glMatrixScaledEXT(GLenum mode,GLdouble x,GLdouble y,GLdouble z)const{(this->*(this->m_ptr_glMatrixScaledEXT))(mode,x,y,z);}
inline void glProgramUniformMatrix2x3fv(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLfloat* value)const{(this->*(this->m_ptr_glProgramUniformMatrix2x3fv))(program,location,count,transpose,value);}
inline void glPushMatrix()const{(this->*(this->m_ptr_glPushMatrix))();}
inline void glGenerateMipmapEXT(GLenum target)const{(this->*(this->m_ptr_glGenerateMipmapEXT))(target);}
inline void glWindowPos3sv(const GLshort* v)const{(this->*(this->m_ptr_glWindowPos3sv))(v);}
inline void glProgramUniform1i(GLuint program,GLint location,GLint v0)const{(this->*(this->m_ptr_glProgramUniform1i))(program,location,v0);}
inline void glProgramUniform1d(GLuint program,GLint location,GLdouble v0)const{(this->*(this->m_ptr_glProgramUniform1d))(program,location,v0);}
inline void glProgramUniform1f(GLuint program,GLint location,GLfloat v0)const{(this->*(this->m_ptr_glProgramUniform1f))(program,location,v0);}
inline void glProgramParameteriEXT(GLuint program,GLenum pname,GLint value)const{(this->*(this->m_ptr_glProgramParameteriEXT))(program,pname,value);}
inline void glCompressedMultiTexImage2DEXT(GLenum texunit,GLenum target,GLint level,GLenum internalformat,GLsizei width,GLsizei height,GLint border,GLsizei imageSize,const void* bits)const{(this->*(this->m_ptr_glCompressedMultiTexImage2DEXT))(texunit,target,level,internalformat,width,height,border,imageSize,bits);}
inline void glProgramUniform3iv(GLuint program,GLint location,GLsizei count,const GLint* value)const{(this->*(this->m_ptr_glProgramUniform3iv))(program,location,count,value);}
inline void glIndexiv(const GLint* c)const{(this->*(this->m_ptr_glIndexiv))(c);}
inline void glGetVertexAttribPointerv(GLuint index,GLenum pname,void** pointer)const{(this->*(this->m_ptr_glGetVertexAttribPointerv))(index,pname,pointer);}
inline void glPixelZoom(GLfloat xfactor,GLfloat yfactor)const{(this->*(this->m_ptr_glPixelZoom))(xfactor,yfactor);}
inline void glFramebufferReadBufferEXT(GLuint framebuffer,GLenum mode)const{(this->*(this->m_ptr_glFramebufferReadBufferEXT))(framebuffer,mode);}
inline void glExtractComponentEXT(GLuint res,GLuint src,GLuint num)const{(this->*(this->m_ptr_glExtractComponentEXT))(res,src,num);}
inline void glMinmax(GLenum target,GLenum internalformat,GLboolean sink)const{(this->*(this->m_ptr_glMinmax))(target,internalformat,sink);}
inline void glColorP3ui(GLenum type,GLuint color)const{(this->*(this->m_ptr_glColorP3ui))(type,color);}
inline void glFogCoorddEXT(GLdouble coord)const{(this->*(this->m_ptr_glFogCoorddEXT))(coord);}
inline void glSecondaryColorPointerEXT(GLint size,GLenum type,GLsizei stride,const void* pointer)const{(this->*(this->m_ptr_glSecondaryColorPointerEXT))(size,type,stride,pointer);}
inline void glMultiTexCoordP4uiv(GLenum texture,GLenum type,const GLuint* coords)const{(this->*(this->m_ptr_glMultiTexCoordP4uiv))(texture,type,coords);}
inline void glDisableVertexArrayAttrib(GLuint vaobj,GLuint index)const{(this->*(this->m_ptr_glDisableVertexArrayAttrib))(vaobj,index);}
inline void glUniform4iv(GLint location,GLsizei count,const GLint* value)const{(this->*(this->m_ptr_glUniform4iv))(location,count,value);}
inline void glSecondaryColor3dvEXT(const GLdouble* v)const{(this->*(this->m_ptr_glSecondaryColor3dvEXT))(v);}
inline void glGenTextures(GLsizei n,GLuint* textures)const{(this->*(this->m_ptr_glGenTextures))(n,textures);}
inline void glTextureStorage2DMultisample(GLuint texture,GLsizei samples,GLenum internalformat,GLsizei width,GLsizei height,GLboolean fixedsamplelocations)const{(this->*(this->m_ptr_glTextureStorage2DMultisample))(texture,samples,internalformat,width,height,fixedsamplelocations);}
inline void glTexParameterIivEXT(GLenum target,GLenum pname,const GLint* params)const{(this->*(this->m_ptr_glTexParameterIivEXT))(target,pname,params);}
inline void glNamedFramebufferTexture1DEXT(GLuint framebuffer,GLenum attachment,GLenum textarget,GLuint texture,GLint level)const{(this->*(this->m_ptr_glNamedFramebufferTexture1DEXT))(framebuffer,attachment,textarget,texture,level);}
inline void glTextureSubImage1DEXT(GLuint texture,GLenum target,GLint level,GLint xoffset,GLsizei width,GLenum format,GLenum type,const void* pixels)const{(this->*(this->m_ptr_glTextureSubImage1DEXT))(texture,target,level,xoffset,width,format,type,pixels);}
inline void glGetActiveUniformBlockName(GLuint program,GLuint uniformBlockIndex,GLsizei bufSize,GLsizei* length,GLchar* uniformBlockName)const{(this->*(this->m_ptr_glGetActiveUniformBlockName))(program,uniformBlockIndex,bufSize,length,uniformBlockName);}
inline void glVertexAttribPointer(GLuint index,GLint size,GLenum type,GLboolean normalized,GLsizei stride,const void* pointer)const{(this->*(this->m_ptr_glVertexAttribPointer))(index,size,type,normalized,stride,pointer);}
inline void glDeleteTexturesEXT(GLsizei n,const GLuint* textures)const{(this->*(this->m_ptr_glDeleteTexturesEXT))(n,textures);}
inline void glNormal3bv(const GLbyte* v)const{(this->*(this->m_ptr_glNormal3bv))(v);}
inline void glApplyTextureEXT(GLenum mode)const{(this->*(this->m_ptr_glApplyTextureEXT))(mode);}
inline void glGetMinmax(GLenum target,GLboolean reset,GLenum format,GLenum types,GLvoid* values)const{(this->*(this->m_ptr_glGetMinmax))(target,reset,format,types,values);}
inline void glSamplePatternEXT(GLenum pattern)const{(this->*(this->m_ptr_glSamplePatternEXT))(pattern);}
inline void glUniform1f(GLint location,GLfloat v0)const{(this->*(this->m_ptr_glUniform1f))(location,v0);}
inline void glFogCoorddvEXT(const GLdouble* coord)const{(this->*(this->m_ptr_glFogCoorddvEXT))(coord);}
inline void glCopyTextureImage1DEXT(GLuint texture,GLenum target,GLint level,GLenum internalformat,GLint x,GLint y,GLsizei width,GLint border)const{(this->*(this->m_ptr_glCopyTextureImage1DEXT))(texture,target,level,internalformat,x,y,width,border);}
inline void glProgramUniform1ivEXT(GLuint program,GLint location,GLsizei count,const GLint* value)const{(this->*(this->m_ptr_glProgramUniform1ivEXT))(program,location,count,value);}
inline void glVertexAttribP1ui(GLuint index,GLenum type,GLboolean normalized,GLuint value)const{(this->*(this->m_ptr_glVertexAttribP1ui))(index,type,normalized,value);}
inline void glProgramUniform4dvEXT(GLuint program,GLint location,GLsizei count,const GLdouble* value)const{(this->*(this->m_ptr_glProgramUniform4dvEXT))(program,location,count,value);}
inline void glEndTransformFeedbackEXT()const{(this->*(this->m_ptr_glEndTransformFeedbackEXT))();}
inline void glBinormal3dEXT(GLdouble bx,GLdouble by,GLdouble bz)const{(this->*(this->m_ptr_glBinormal3dEXT))(bx,by,bz);}
inline void glGetNamedRenderbufferParameteriv(GLuint renderbuffer,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetNamedRenderbufferParameteriv))(renderbuffer,pname,params);}
inline void glBindBuffersRange(GLenum target,GLuint first,GLsizei count,const GLuint* buffers,const GLintptr* offsets,const GLsizeiptr* sizes)const{(this->*(this->m_ptr_glBindBuffersRange))(target,first,count,buffers,offsets,sizes);}
inline void glBindFragDataLocationIndexed(GLuint program,GLuint colorNumber,GLuint index,const GLchar* name)const{(this->*(this->m_ptr_glBindFragDataLocationIndexed))(program,colorNumber,index,name);}
inline void glMultiTexCoord2dv(GLenum target,const GLdouble* v)const{(this->*(this->m_ptr_glMultiTexCoord2dv))(target,v);}
inline void glUniform2iv(GLint location,GLsizei count,const GLint* value)const{(this->*(this->m_ptr_glUniform2iv))(location,count,value);}
inline void glNamedFramebufferRenderbufferEXT(GLuint framebuffer,GLenum attachment,GLenum renderbuffertarget,GLuint renderbuffer)const{(this->*(this->m_ptr_glNamedFramebufferRenderbufferEXT))(framebuffer,attachment,renderbuffertarget,renderbuffer);}
inline void glFeedbackBuffer(GLsizei size,GLenum type,GLfloat* buffer)const{(this->*(this->m_ptr_glFeedbackBuffer))(size,type,buffer);}
inline void glMultiTexCoord2i(GLenum target,GLint s,GLint t)const{(this->*(this->m_ptr_glMultiTexCoord2i))(target,s,t);}
inline void glTextureSubImage3D(GLuint texture,GLint level,GLint xoffset,GLint yoffset,GLint zoffset,GLsizei width,GLsizei height,GLsizei depth,GLenum format,GLenum type,const void* pixels)const{(this->*(this->m_ptr_glTextureSubImage3D))(texture,level,xoffset,yoffset,zoffset,width,height,depth,format,type,pixels);}
inline void glFramebufferTexture1D(GLenum target,GLenum attachment,GLenum textarget,GLuint texture,GLint level)const{(this->*(this->m_ptr_glFramebufferTexture1D))(target,attachment,textarget,texture,level);}
inline void glGetShaderiv(GLuint shader,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetShaderiv))(shader,pname,params);}
inline void glMultiTexCoord2d(GLenum target,GLdouble s,GLdouble t)const{(this->*(this->m_ptr_glMultiTexCoord2d))(target,s,t);}
inline void glMatrixLoadTransposedEXT(GLenum mode,const GLdouble* m)const{(this->*(this->m_ptr_glMatrixLoadTransposedEXT))(mode,m);}
inline void glGetPointeri_vEXT(GLenum pname,GLuint index,void** params)const{(this->*(this->m_ptr_glGetPointeri_vEXT))(pname,index,params);}
inline void glNamedBufferStorage(GLuint buffer,GLsizeiptr size,const void* data,GLbitfield flags)const{(this->*(this->m_ptr_glNamedBufferStorage))(buffer,size,data,flags);}
inline void glUniform1dv(GLint location,GLsizei count,const GLdouble* value)const{(this->*(this->m_ptr_glUniform1dv))(location,count,value);}
inline void glSecondaryColor3usvEXT(const GLushort* v)const{(this->*(this->m_ptr_glSecondaryColor3usvEXT))(v);}
inline void glVertex2sv(const GLshort* v)const{(this->*(this->m_ptr_glVertex2sv))(v);}
inline GLboolean glIsTextureEXT(GLuint texture)const{return (this->*(this->m_ptr_glIsTextureEXT))(texture);}
inline void glVertexArrayVertexAttribBindingEXT(GLuint vaobj,GLuint attribindex,GLuint bindingindex)const{(this->*(this->m_ptr_glVertexArrayVertexAttribBindingEXT))(vaobj,attribindex,bindingindex);}
inline void glMultiTexCoord4fv(GLenum target,const GLfloat* v)const{(this->*(this->m_ptr_glMultiTexCoord4fv))(target,v);}
inline void glRasterPos3i(GLint x,GLint y,GLint z)const{(this->*(this->m_ptr_glRasterPos3i))(x,y,z);}
inline void glRasterPos3d(GLdouble x,GLdouble y,GLdouble z)const{(this->*(this->m_ptr_glRasterPos3d))(x,y,z);}
inline void glRasterPos3f(GLfloat x,GLfloat y,GLfloat z)const{(this->*(this->m_ptr_glRasterPos3f))(x,y,z);}
inline void glTextureParameteriEXT(GLuint texture,GLenum target,GLenum pname,GLint param)const{(this->*(this->m_ptr_glTextureParameteriEXT))(texture,target,pname,param);}
inline void glVariantivEXT(GLuint id,const GLint* addr)const{(this->*(this->m_ptr_glVariantivEXT))(id,addr);}
inline void glGetVertexAttribiv(GLuint index,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetVertexAttribiv))(index,pname,params);}
inline void glGetPointerIndexedvEXT(GLenum target,GLuint index,void** data)const{(this->*(this->m_ptr_glGetPointerIndexedvEXT))(target,index,data);}
inline void glVertexAttrib3fv(GLuint index,const GLfloat* v)const{(this->*(this->m_ptr_glVertexAttrib3fv))(index,v);}
inline void glRasterPos3s(GLshort x,GLshort y,GLshort z)const{(this->*(this->m_ptr_glRasterPos3s))(x,y,z);}
inline void glConvolutionFilter1D(GLenum target,GLenum internalformat,GLsizei width,GLenum format,GLenum type,const GLvoid* image)const{(this->*(this->m_ptr_glConvolutionFilter1D))(target,internalformat,width,format,type,image);}
inline void glTransformFeedbackVaryingsEXT(GLuint program,GLsizei count,const GLchar*const* varyings,GLenum bufferMode)const{(this->*(this->m_ptr_glTransformFeedbackVaryingsEXT))(program,count,varyings,bufferMode);}
inline GLboolean glIsList(GLuint list)const{return (this->*(this->m_ptr_glIsList))(list);}
inline void glUniformMatrix2fv(GLint location,GLsizei count,GLboolean transpose,const GLfloat* value)const{(this->*(this->m_ptr_glUniformMatrix2fv))(location,count,transpose,value);}
inline void glTextureParameterfvEXT(GLuint texture,GLenum target,GLenum pname,const GLfloat* params)const{(this->*(this->m_ptr_glTextureParameterfvEXT))(texture,target,pname,params);}
inline void glMatrixMultdEXT(GLenum mode,const GLdouble* m)const{(this->*(this->m_ptr_glMatrixMultdEXT))(mode,m);}
inline void glOrtho(GLdouble left,GLdouble right,GLdouble bottom,GLdouble top,GLdouble near_val,GLdouble far_val)const{(this->*(this->m_ptr_glOrtho))(left,right,bottom,top,near_val,far_val);}
inline void glGenerateTextureMipmap(GLuint texture)const{(this->*(this->m_ptr_glGenerateTextureMipmap))(texture);}
inline void glNamedProgramLocalParameterI4uivEXT(GLuint program,GLenum target,GLuint index,const GLuint* params)const{(this->*(this->m_ptr_glNamedProgramLocalParameterI4uivEXT))(program,target,index,params);}
inline void glMultiDrawElementsBaseVertex(GLenum mode,const GLsizei* count,GLenum type,const void*const* indices,GLsizei drawcount,const GLint* basevertex)const{(this->*(this->m_ptr_glMultiDrawElementsBaseVertex))(mode,count,type,indices,drawcount,basevertex);}
inline void glProgramUniformMatrix2x4dvEXT(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLdouble* value)const{(this->*(this->m_ptr_glProgramUniformMatrix2x4dvEXT))(program,location,count,transpose,value);}
inline void glMemoryBarrierEXT(GLbitfield barriers)const{(this->*(this->m_ptr_glMemoryBarrierEXT))(barriers);}
inline void glCompressedTexSubImage1D(GLenum target,GLint level,GLint xoffset,GLsizei width,GLenum format,GLsizei imageSize,const GLvoid* data)const{(this->*(this->m_ptr_glCompressedTexSubImage1D))(target,level,xoffset,width,format,imageSize,data);}
inline void glCopyConvolutionFilter1D(GLenum target,GLenum internalformat,GLint x,GLint y,GLsizei width)const{(this->*(this->m_ptr_glCopyConvolutionFilter1D))(target,internalformat,x,y,width);}
inline void glTextureBuffer(GLuint texture,GLenum internalformat,GLuint buffer)const{(this->*(this->m_ptr_glTextureBuffer))(texture,internalformat,buffer);}
inline void glVertexAttrib4Nsv(GLuint index,const GLshort* v)const{(this->*(this->m_ptr_glVertexAttrib4Nsv))(index,v);}
inline void glVertexAttribI4usvEXT(GLuint index,const GLushort* v)const{(this->*(this->m_ptr_glVertexAttribI4usvEXT))(index,v);}
inline void glTextureBufferRangeEXT(GLuint texture,GLenum target,GLenum internalformat,GLuint buffer,GLintptr offset,GLsizeiptr size)const{(this->*(this->m_ptr_glTextureBufferRangeEXT))(texture,target,internalformat,buffer,offset,size);}
inline void glVertexP3uiv(GLenum type,const GLuint* value)const{(this->*(this->m_ptr_glVertexP3uiv))(type,value);}
inline void glTransformFeedbackVaryings(GLuint program,GLsizei count,const GLchar*const* varyings,GLenum bufferMode)const{(this->*(this->m_ptr_glTransformFeedbackVaryings))(program,count,varyings,bufferMode);}
inline void glCompressedMultiTexSubImage2DEXT(GLenum texunit,GLenum target,GLint level,GLint xoffset,GLint yoffset,GLsizei width,GLsizei height,GLenum format,GLsizei imageSize,const void* bits)const{(this->*(this->m_ptr_glCompressedMultiTexSubImage2DEXT))(texunit,target,level,xoffset,yoffset,width,height,format,imageSize,bits);}
inline void glGetnMapdv(GLenum target,GLenum query,GLsizei bufSize,GLdouble* v)const{(this->*(this->m_ptr_glGetnMapdv))(target,query,bufSize,v);}
inline void glDebugMessageCallback(GLDEBUGPROC callback,const void* userParam)const{(this->*(this->m_ptr_glDebugMessageCallback))(callback,userParam);}
inline void glTangent3svEXT(const GLshort* v)const{(this->*(this->m_ptr_glTangent3svEXT))(v);}
inline void glRasterPos4fv(const GLfloat* v)const{(this->*(this->m_ptr_glRasterPos4fv))(v);}
inline void glNamedProgramLocalParametersI4ivEXT(GLuint program,GLenum target,GLuint index,GLsizei count,const GLint* params)const{(this->*(this->m_ptr_glNamedProgramLocalParametersI4ivEXT))(program,target,index,count,params);}
inline void glProgramUniform2dvEXT(GLuint program,GLint location,GLsizei count,const GLdouble* value)const{(this->*(this->m_ptr_glProgramUniform2dvEXT))(program,location,count,value);}
inline void glGetNamedFramebufferAttachmentParameterivEXT(GLuint framebuffer,GLenum attachment,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetNamedFramebufferAttachmentParameterivEXT))(framebuffer,attachment,pname,params);}
inline void glGetFloatv(GLenum pname,GLfloat* params)const{(this->*(this->m_ptr_glGetFloatv))(pname,params);}
inline void glVertexArrayVertexAttribIFormatEXT(GLuint vaobj,GLuint attribindex,GLint size,GLenum type,GLuint relativeoffset)const{(this->*(this->m_ptr_glVertexArrayVertexAttribIFormatEXT))(vaobj,attribindex,size,type,relativeoffset);}
inline void glHint(GLenum target,GLenum mode)const{(this->*(this->m_ptr_glHint))(target,mode);}
inline void glGetTextureImageEXT(GLuint texture,GLenum target,GLint level,GLenum format,GLenum type,void* pixels)const{(this->*(this->m_ptr_glGetTextureImageEXT))(texture,target,level,format,type,pixels);}
inline void glMultiDrawArraysIndirect(GLenum mode,const void* indirect,GLsizei drawcount,GLsizei stride)const{(this->*(this->m_ptr_glMultiDrawArraysIndirect))(mode,indirect,drawcount,stride);}
inline void glVertexAttribP2uiv(GLuint index,GLenum type,GLboolean normalized,const GLuint* value)const{(this->*(this->m_ptr_glVertexAttribP2uiv))(index,type,normalized,value);}
inline void glPushClientAttribDefaultEXT(GLbitfield mask)const{(this->*(this->m_ptr_glPushClientAttribDefaultEXT))(mask);}
inline void glScalef(GLfloat x,GLfloat y,GLfloat z)const{(this->*(this->m_ptr_glScalef))(x,y,z);}
inline void glScaled(GLdouble x,GLdouble y,GLdouble z)const{(this->*(this->m_ptr_glScaled))(x,y,z);}
inline void glGetProgramResourceName(GLuint program,GLenum programInterface,GLuint index,GLsizei bufSize,GLsizei* length,GLchar* name)const{(this->*(this->m_ptr_glGetProgramResourceName))(program,programInterface,index,bufSize,length,name);}
inline void glCopyColorTable(GLenum target,GLenum internalformat,GLint x,GLint y,GLsizei width)const{(this->*(this->m_ptr_glCopyColorTable))(target,internalformat,x,y,width);}
inline void glDepthRangeArrayv(GLuint first,GLsizei count,const GLdouble* v)const{(this->*(this->m_ptr_glDepthRangeArrayv))(first,count,v);}
inline void glMultiTexParameterivEXT(GLenum texunit,GLenum target,GLenum pname,const GLint* params)const{(this->*(this->m_ptr_glMultiTexParameterivEXT))(texunit,target,pname,params);}
inline void glGetActiveAtomicCounterBufferiv(GLuint program,GLuint bufferIndex,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetActiveAtomicCounterBufferiv))(program,bufferIndex,pname,params);}
inline void glStencilOpSeparate(GLenum face,GLenum sfail,GLenum dpfail,GLenum dppass)const{(this->*(this->m_ptr_glStencilOpSeparate))(face,sfail,dpfail,dppass);}
inline void glVertexArrayAttribBinding(GLuint vaobj,GLuint attribindex,GLuint bindingindex)const{(this->*(this->m_ptr_glVertexArrayAttribBinding))(vaobj,attribindex,bindingindex);}
inline void glVertexAttribL4dv(GLuint index,const GLdouble* v)const{(this->*(this->m_ptr_glVertexAttribL4dv))(index,v);}
inline void glGetTexParameteriv(GLenum target,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetTexParameteriv))(target,pname,params);}
inline void glProgramUniform1dv(GLuint program,GLint location,GLsizei count,const GLdouble* value)const{(this->*(this->m_ptr_glProgramUniform1dv))(program,location,count,value);}
inline void glTangent3fEXT(GLfloat tx,GLfloat ty,GLfloat tz)const{(this->*(this->m_ptr_glTangent3fEXT))(tx,ty,tz);}
inline void glGetnCompressedTexImage(GLenum target,GLint lod,GLsizei bufSize,void* pixels)const{(this->*(this->m_ptr_glGetnCompressedTexImage))(target,lod,bufSize,pixels);}
inline void glWindowPos2dv(const GLdouble* v)const{(this->*(this->m_ptr_glWindowPos2dv))(v);}
inline void* glMapNamedBufferEXT(GLuint buffer,GLenum access)const{return (this->*(this->m_ptr_glMapNamedBufferEXT))(buffer,access);}
inline void glDisable(GLenum cap)const{(this->*(this->m_ptr_glDisable))(cap);}
inline void glVertexAttribI2uiEXT(GLuint index,GLuint x,GLuint y)const{(this->*(this->m_ptr_glVertexAttribI2uiEXT))(index,x,y);}
inline void glProgramUniform4uiv(GLuint program,GLint location,GLsizei count,const GLuint* value)const{(this->*(this->m_ptr_glProgramUniform4uiv))(program,location,count,value);}
inline void glGetConvolutionParameterfvEXT(GLenum target,GLenum pname,GLfloat* params)const{(this->*(this->m_ptr_glGetConvolutionParameterfvEXT))(target,pname,params);}
inline void glFramebufferRenderbufferEXT(GLenum target,GLenum attachment,GLenum renderbuffertarget,GLuint renderbuffer)const{(this->*(this->m_ptr_glFramebufferRenderbufferEXT))(target,attachment,renderbuffertarget,renderbuffer);}
inline void glBinormal3svEXT(const GLshort* v)const{(this->*(this->m_ptr_glBinormal3svEXT))(v);}
inline void glCopyTextureSubImage2D(GLuint texture,GLint level,GLint xoffset,GLint yoffset,GLint x,GLint y,GLsizei width,GLsizei height)const{(this->*(this->m_ptr_glCopyTextureSubImage2D))(texture,level,xoffset,yoffset,x,y,width,height);}
inline void glBinormalPointerEXT(GLenum type,GLsizei stride,const void* pointer)const{(this->*(this->m_ptr_glBinormalPointerEXT))(type,stride,pointer);}
inline void glGetLightfv(GLenum light,GLenum pname,GLfloat* params)const{(this->*(this->m_ptr_glGetLightfv))(light,pname,params);}
inline void glMultiTexCoord3s(GLenum target,GLshort s,GLshort t,GLshort r)const{(this->*(this->m_ptr_glMultiTexCoord3s))(target,s,t,r);}
inline void glTextureSubImage2D(GLuint texture,GLint level,GLint xoffset,GLint yoffset,GLsizei width,GLsizei height,GLenum format,GLenum type,const void* pixels)const{(this->*(this->m_ptr_glTextureSubImage2D))(texture,level,xoffset,yoffset,width,height,format,type,pixels);}
inline void glMultiTexCoord3i(GLenum target,GLint s,GLint t,GLint r)const{(this->*(this->m_ptr_glMultiTexCoord3i))(target,s,t,r);}
inline void glMultiTexCoord3f(GLenum target,GLfloat s,GLfloat t,GLfloat r)const{(this->*(this->m_ptr_glMultiTexCoord3f))(target,s,t,r);}
inline void glMultiTexCoord3d(GLenum target,GLdouble s,GLdouble t,GLdouble r)const{(this->*(this->m_ptr_glMultiTexCoord3d))(target,s,t,r);}
inline void glFogCoorddv(const GLdouble* coord)const{(this->*(this->m_ptr_glFogCoorddv))(coord);}
inline void glGetBufferPointerv(GLenum target,GLenum pname,void** params)const{(this->*(this->m_ptr_glGetBufferPointerv))(target,pname,params);}
inline void glNamedRenderbufferStorageMultisample(GLuint renderbuffer,GLsizei samples,GLenum internalformat,GLsizei width,GLsizei height)const{(this->*(this->m_ptr_glNamedRenderbufferStorageMultisample))(renderbuffer,samples,internalformat,width,height);}
inline void glClearNamedBufferData(GLuint buffer,GLenum internalformat,GLenum format,GLenum type,const void* data)const{(this->*(this->m_ptr_glClearNamedBufferData))(buffer,internalformat,format,type,data);}
inline void glReadBuffer(GLenum mode)const{(this->*(this->m_ptr_glReadBuffer))(mode);}
inline void glProgramUniformMatrix4fvEXT(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLfloat* value)const{(this->*(this->m_ptr_glProgramUniformMatrix4fvEXT))(program,location,count,transpose,value);}
inline void glFlushMappedNamedBufferRange(GLuint buffer,GLintptr offset,GLsizeiptr length)const{(this->*(this->m_ptr_glFlushMappedNamedBufferRange))(buffer,offset,length);}
inline void glPushName(GLuint name)const{(this->*(this->m_ptr_glPushName))(name);}
inline void glGetClipPlane(GLenum plane,GLdouble* equation)const{(this->*(this->m_ptr_glGetClipPlane))(plane,equation);}
inline void glRasterPos4i(GLint x,GLint y,GLint z,GLint w)const{(this->*(this->m_ptr_glRasterPos4i))(x,y,z,w);}
inline void glVertexAttrib3d(GLuint index,GLdouble x,GLdouble y,GLdouble z)const{(this->*(this->m_ptr_glVertexAttrib3d))(index,x,y,z);}
inline void glBlendColor(GLfloat red,GLfloat green,GLfloat blue,GLfloat alpha)const{(this->*(this->m_ptr_glBlendColor))(red,green,blue,alpha);}
inline void glSamplerParameterIuiv(GLuint sampler,GLenum pname,const GLuint* param)const{(this->*(this->m_ptr_glSamplerParameterIuiv))(sampler,pname,param);}
inline void glIndexubv(const GLubyte* c)const{(this->*(this->m_ptr_glIndexubv))(c);}
inline void glNamedBufferPageCommitmentEXT(GLuint buffer,GLintptr offset,GLsizeiptr size,GLboolean commit)const{(this->*(this->m_ptr_glNamedBufferPageCommitmentEXT))(buffer,offset,size,commit);}
inline void glCopyTexSubImage3DEXT(GLenum target,GLint level,GLint xoffset,GLint yoffset,GLint zoffset,GLint x,GLint y,GLsizei width,GLsizei height)const{(this->*(this->m_ptr_glCopyTexSubImage3DEXT))(target,level,xoffset,yoffset,zoffset,x,y,width,height);}
inline void glRasterPos4d(GLdouble x,GLdouble y,GLdouble z,GLdouble w)const{(this->*(this->m_ptr_glRasterPos4d))(x,y,z,w);}
inline void glRasterPos4f(GLfloat x,GLfloat y,GLfloat z,GLfloat w)const{(this->*(this->m_ptr_glRasterPos4f))(x,y,z,w);}
inline void glVertexAttrib3s(GLuint index,GLshort x,GLshort y,GLshort z)const{(this->*(this->m_ptr_glVertexAttrib3s))(index,x,y,z);}
inline void glDrawElementsInstancedEXT(GLenum mode,GLsizei count,GLenum type,const void* indices,GLsizei primcount)const{(this->*(this->m_ptr_glDrawElementsInstancedEXT))(mode,count,type,indices,primcount);}
inline void glNamedProgramLocalParameterI4iEXT(GLuint program,GLenum target,GLuint index,GLint x,GLint y,GLint z,GLint w)const{(this->*(this->m_ptr_glNamedProgramLocalParameterI4iEXT))(program,target,index,x,y,z,w);}
inline void glRasterPos4s(GLshort x,GLshort y,GLshort z,GLshort w)const{(this->*(this->m_ptr_glRasterPos4s))(x,y,z,w);}
inline void glGetProgramStageiv(GLuint program,GLenum shadertype,GLenum pname,GLint* values)const{(this->*(this->m_ptr_glGetProgramStageiv))(program,shadertype,pname,values);}
inline void glTangent3bEXT(GLbyte tx,GLbyte ty,GLbyte tz)const{(this->*(this->m_ptr_glTangent3bEXT))(tx,ty,tz);}
inline void glUniform4i(GLint location,GLint v0,GLint v1,GLint v2,GLint v3)const{(this->*(this->m_ptr_glUniform4i))(location,v0,v1,v2,v3);}
inline void glActiveTexture(GLenum texture)const{(this->*(this->m_ptr_glActiveTexture))(texture);}
inline void glEnableVertexAttribArray(GLuint index)const{(this->*(this->m_ptr_glEnableVertexAttribArray))(index);}
inline void glUniform4d(GLint location,GLdouble x,GLdouble y,GLdouble z,GLdouble w)const{(this->*(this->m_ptr_glUniform4d))(location,x,y,z,w);}
inline void glUniform4f(GLint location,GLfloat v0,GLfloat v1,GLfloat v2,GLfloat v3)const{(this->*(this->m_ptr_glUniform4f))(location,v0,v1,v2,v3);}
inline void glRenderbufferStorageMultisample(GLenum target,GLsizei samples,GLenum internalformat,GLsizei width,GLsizei height)const{(this->*(this->m_ptr_glRenderbufferStorageMultisample))(target,samples,internalformat,width,height);}
inline void glCreateProgramPipelines(GLsizei n,GLuint* pipelines)const{(this->*(this->m_ptr_glCreateProgramPipelines))(n,pipelines);}
inline void glVertexAttribLPointer(GLuint index,GLint size,GLenum type,GLsizei stride,const void* pointer)const{(this->*(this->m_ptr_glVertexAttribLPointer))(index,size,type,stride,pointer);}
inline void glUniform2uiEXT(GLint location,GLuint v0,GLuint v1)const{(this->*(this->m_ptr_glUniform2uiEXT))(location,v0,v1);}
inline void glMultiTexCoord3sv(GLenum target,const GLshort* v)const{(this->*(this->m_ptr_glMultiTexCoord3sv))(target,v);}
inline void glDrawElementsInstancedBaseVertex(GLenum mode,GLsizei count,GLenum type,const void* indices,GLsizei instancecount,GLint basevertex)const{(this->*(this->m_ptr_glDrawElementsInstancedBaseVertex))(mode,count,type,indices,instancecount,basevertex);}
inline void glPixelTransformParameterfvEXT(GLenum target,GLenum pname,const GLfloat* params)const{(this->*(this->m_ptr_glPixelTransformParameterfvEXT))(target,pname,params);}
inline void glNamedRenderbufferStorageMultisampleCoverageEXT(GLuint renderbuffer,GLsizei coverageSamples,GLsizei colorSamples,GLenum internalformat,GLsizei width,GLsizei height)const{(this->*(this->m_ptr_glNamedRenderbufferStorageMultisampleCoverageEXT))(renderbuffer,coverageSamples,colorSamples,internalformat,width,height);}
inline void glGetActiveSubroutineName(GLuint program,GLenum shadertype,GLuint index,GLsizei bufsize,GLsizei* length,GLchar* name)const{(this->*(this->m_ptr_glGetActiveSubroutineName))(program,shadertype,index,bufsize,length,name);}
inline void glMultiTexCoord4iv(GLenum target,const GLint* v)const{(this->*(this->m_ptr_glMultiTexCoord4iv))(target,v);}
inline void glPopDebugGroup()const{(this->*(this->m_ptr_glPopDebugGroup))();}
inline void glUniformBlockBinding(GLuint program,GLuint uniformBlockIndex,GLuint uniformBlockBinding)const{(this->*(this->m_ptr_glUniformBlockBinding))(program,uniformBlockIndex,uniformBlockBinding);}
inline void glGenerateTextureMipmapEXT(GLuint texture,GLenum target)const{(this->*(this->m_ptr_glGenerateTextureMipmapEXT))(texture,target);}
inline void glTexCoordPointer(GLint size,GLenum type,GLsizei stride,const GLvoid* ptr)const{(this->*(this->m_ptr_glTexCoordPointer))(size,type,stride,ptr);}
inline void glProgramUniformMatrix3x2fv(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLfloat* value)const{(this->*(this->m_ptr_glProgramUniformMatrix3x2fv))(program,location,count,transpose,value);}
inline void glSecondaryColor3svEXT(const GLshort* v)const{(this->*(this->m_ptr_glSecondaryColor3svEXT))(v);}
inline void glGetQueryIndexediv(GLenum target,GLuint index,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetQueryIndexediv))(target,index,pname,params);}
inline void glFramebufferTexture3DEXT(GLenum target,GLenum attachment,GLenum textarget,GLuint texture,GLint level,GLint zoffset)const{(this->*(this->m_ptr_glFramebufferTexture3DEXT))(target,attachment,textarget,texture,level,zoffset);}
inline void glObjectLabel(GLenum identifier,GLuint name,GLsizei length,const GLchar* label)const{(this->*(this->m_ptr_glObjectLabel))(identifier,name,length,label);}
inline void glGetCompressedTextureImageEXT(GLuint texture,GLenum target,GLint lod,void* img)const{(this->*(this->m_ptr_glGetCompressedTextureImageEXT))(texture,target,lod,img);}
inline void glIndexMaterialEXT(GLenum face,GLenum mode)const{(this->*(this->m_ptr_glIndexMaterialEXT))(face,mode);}
inline void glFramebufferTexture2DEXT(GLenum target,GLenum attachment,GLenum textarget,GLuint texture,GLint level)const{(this->*(this->m_ptr_glFramebufferTexture2DEXT))(target,attachment,textarget,texture,level);}
inline void glTexEnviv(GLenum target,GLenum pname,const GLint* params)const{(this->*(this->m_ptr_glTexEnviv))(target,pname,params);}
inline void glSelectBuffer(GLsizei size,GLuint* buffer)const{(this->*(this->m_ptr_glSelectBuffer))(size,buffer);}
inline void glNamedBufferSubDataEXT(GLuint buffer,GLintptr offset,GLsizeiptr size,const void* data)const{(this->*(this->m_ptr_glNamedBufferSubDataEXT))(buffer,offset,size,data);}
inline void glBlendFunc(GLenum sfactor,GLenum dfactor)const{(this->*(this->m_ptr_glBlendFunc))(sfactor,dfactor);}
inline GLuint glCreateProgram()const{return (this->*(this->m_ptr_glCreateProgram))();}
inline void glPrimitiveRestartIndex(GLuint index)const{(this->*(this->m_ptr_glPrimitiveRestartIndex))(index);}
inline void glEnd()const{(this->*(this->m_ptr_glEnd))();}
inline void glGetNamedFramebufferParameterivEXT(GLuint framebuffer,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetNamedFramebufferParameterivEXT))(framebuffer,pname,params);}
inline void glUniform3uiv(GLint location,GLsizei count,const GLuint* value)const{(this->*(this->m_ptr_glUniform3uiv))(location,count,value);}
inline void glClearColor(GLclampf red,GLclampf green,GLclampf blue,GLclampf alpha)const{(this->*(this->m_ptr_glClearColor))(red,green,blue,alpha);}
inline void glTangent3dEXT(GLdouble tx,GLdouble ty,GLdouble tz)const{(this->*(this->m_ptr_glTangent3dEXT))(tx,ty,tz);}
inline void glGetLocalConstantFloatvEXT(GLuint id,GLenum value,GLfloat* data)const{(this->*(this->m_ptr_glGetLocalConstantFloatvEXT))(id,value,data);}
inline void glUseShaderProgramEXT(GLenum type,GLuint program)const{(this->*(this->m_ptr_glUseShaderProgramEXT))(type,program);}
inline void glBindRenderbufferEXT(GLenum target,GLuint renderbuffer)const{(this->*(this->m_ptr_glBindRenderbufferEXT))(target,renderbuffer);}
inline void glGetnUniformiv(GLuint program,GLint location,GLsizei bufSize,GLint* params)const{(this->*(this->m_ptr_glGetnUniformiv))(program,location,bufSize,params);}
inline void glUniform3ui(GLint location,GLuint v0,GLuint v1,GLuint v2)const{(this->*(this->m_ptr_glUniform3ui))(location,v0,v1,v2);}
inline void glGetNamedProgramLocalParameterdvEXT(GLuint program,GLenum target,GLuint index,GLdouble* params)const{(this->*(this->m_ptr_glGetNamedProgramLocalParameterdvEXT))(program,target,index,params);}
inline void glSecondaryColor3us(GLushort red,GLushort green,GLushort blue)const{(this->*(this->m_ptr_glSecondaryColor3us))(red,green,blue);}
inline void glVertexAttribI4uiv(GLuint index,const GLuint* v)const{(this->*(this->m_ptr_glVertexAttribI4uiv))(index,v);}
inline void glVertexAttrib4bv(GLuint index,const GLbyte* v)const{(this->*(this->m_ptr_glVertexAttrib4bv))(index,v);}
inline GLuint glGetProgramResourceIndex(GLuint program,GLenum programInterface,const GLchar* name)const{return (this->*(this->m_ptr_glGetProgramResourceIndex))(program,programInterface,name);}
inline void glSecondaryColor3ub(GLubyte red,GLubyte green,GLubyte blue)const{(this->*(this->m_ptr_glSecondaryColor3ub))(red,green,blue);}
inline void glConvolutionFilter2DEXT(GLenum target,GLenum internalformat,GLsizei width,GLsizei height,GLenum format,GLenum type,const void* image)const{(this->*(this->m_ptr_glConvolutionFilter2DEXT))(target,internalformat,width,height,format,type,image);}
inline void glSecondaryColor3ui(GLuint red,GLuint green,GLuint blue)const{(this->*(this->m_ptr_glSecondaryColor3ui))(red,green,blue);}
inline void glGetNamedBufferPointerv(GLuint buffer,GLenum pname,void** params)const{(this->*(this->m_ptr_glGetNamedBufferPointerv))(buffer,pname,params);}
inline void glLockArraysEXT(GLint first,GLsizei count)const{(this->*(this->m_ptr_glLockArraysEXT))(first,count);}
inline void glBindBufferBaseEXT(GLenum target,GLuint index,GLuint buffer)const{(this->*(this->m_ptr_glBindBufferBaseEXT))(target,index,buffer);}
inline void glProgramUniform1fEXT(GLuint program,GLint location,GLfloat v0)const{(this->*(this->m_ptr_glProgramUniform1fEXT))(program,location,v0);}
inline void glGetQueryBufferObjectui64v(GLuint id,GLuint buffer,GLenum pname,GLintptr offset)const{(this->*(this->m_ptr_glGetQueryBufferObjectui64v))(id,buffer,pname,offset);}
inline void glTextureImage3DEXT(GLuint texture,GLenum target,GLint level,GLint internalformat,GLsizei width,GLsizei height,GLsizei depth,GLint border,GLenum format,GLenum type,const void* pixels)const{(this->*(this->m_ptr_glTextureImage3DEXT))(texture,target,level,internalformat,width,height,depth,border,format,type,pixels);}
inline void glUniformMatrix2x3fv(GLint location,GLsizei count,GLboolean transpose,const GLfloat* value)const{(this->*(this->m_ptr_glUniformMatrix2x3fv))(location,count,transpose,value);}
inline void glGenTransformFeedbacks(GLsizei n,GLuint* ids)const{(this->*(this->m_ptr_glGenTransformFeedbacks))(n,ids);}
inline void glGetVertexAttribIuiv(GLuint index,GLenum pname,GLuint* params)const{(this->*(this->m_ptr_glGetVertexAttribIuiv))(index,pname,params);}
inline void glPixelTransformParameterfEXT(GLenum target,GLenum pname,GLfloat param)const{(this->*(this->m_ptr_glPixelTransformParameterfEXT))(target,pname,param);}
inline void glGetTexParameterIuivEXT(GLenum target,GLenum pname,GLuint* params)const{(this->*(this->m_ptr_glGetTexParameterIuivEXT))(target,pname,params);}
inline void glVertexArraySecondaryColorOffsetEXT(GLuint vaobj,GLuint buffer,GLint size,GLenum type,GLsizei stride,GLintptr offset)const{(this->*(this->m_ptr_glVertexArraySecondaryColorOffsetEXT))(vaobj,buffer,size,type,stride,offset);}
inline void glCompressedTexSubImage2D(GLenum target,GLint level,GLint xoffset,GLint yoffset,GLsizei width,GLsizei height,GLenum format,GLsizei imageSize,const GLvoid* data)const{(this->*(this->m_ptr_glCompressedTexSubImage2D))(target,level,xoffset,yoffset,width,height,format,imageSize,data);}
inline void glProgramBinary(GLuint program,GLenum binaryFormat,const void* binary,GLsizei length)const{(this->*(this->m_ptr_glProgramBinary))(program,binaryFormat,binary,length);}
inline void glVertexAttribI4bv(GLuint index,const GLbyte* v)const{(this->*(this->m_ptr_glVertexAttribI4bv))(index,v);}
inline void glGetTexParameterfv(GLenum target,GLenum pname,GLfloat* params)const{(this->*(this->m_ptr_glGetTexParameterfv))(target,pname,params);}
inline void glSecondaryColor3usEXT(GLushort red,GLushort green,GLushort blue)const{(this->*(this->m_ptr_glSecondaryColor3usEXT))(red,green,blue);}
inline void glGetVertexArrayIndexed64iv(GLuint vaobj,GLuint index,GLenum pname,GLint64* param)const{(this->*(this->m_ptr_glGetVertexArrayIndexed64iv))(vaobj,index,pname,param);}
inline void glTexParameterIiv(GLenum target,GLenum pname,const GLint* params)const{(this->*(this->m_ptr_glTexParameterIiv))(target,pname,params);}
inline void glVertexArrayAttribFormat(GLuint vaobj,GLuint attribindex,GLint size,GLenum type,GLboolean normalized,GLuint relativeoffset)const{(this->*(this->m_ptr_glVertexArrayAttribFormat))(vaobj,attribindex,size,type,normalized,relativeoffset);}
inline void glEndTransformFeedback()const{(this->*(this->m_ptr_glEndTransformFeedback))();}
inline void glVertexAttrib4usv(GLuint index,const GLushort* v)const{(this->*(this->m_ptr_glVertexAttrib4usv))(index,v);}
inline void glTexImage2DMultisample(GLenum target,GLsizei samples,GLenum internalformat,GLsizei width,GLsizei height,GLboolean fixedsamplelocations)const{(this->*(this->m_ptr_glTexImage2DMultisample))(target,samples,internalformat,width,height,fixedsamplelocations);}
inline void glBindTextureEXT(GLenum target,GLuint texture)const{(this->*(this->m_ptr_glBindTextureEXT))(target,texture);}
inline void glVertexAttribI1iv(GLuint index,const GLint* v)const{(this->*(this->m_ptr_glVertexAttribI1iv))(index,v);}
inline void glVertexAttribDivisor(GLuint index,GLuint divisor)const{(this->*(this->m_ptr_glVertexAttribDivisor))(index,divisor);}
inline void glSeparableFilter2D(GLenum target,GLenum internalformat,GLsizei width,GLsizei height,GLenum format,GLenum type,const GLvoid* row,const GLvoid* column)const{(this->*(this->m_ptr_glSeparableFilter2D))(target,internalformat,width,height,format,type,row,column);}
inline GLuint glBindTexGenParameterEXT(GLenum unit,GLenum coord,GLenum value)const{return (this->*(this->m_ptr_glBindTexGenParameterEXT))(unit,coord,value);}
inline void glTextureImage2DEXT(GLuint texture,GLenum target,GLint level,GLint internalformat,GLsizei width,GLsizei height,GLint border,GLenum format,GLenum type,const void* pixels)const{(this->*(this->m_ptr_glTextureImage2DEXT))(texture,target,level,internalformat,width,height,border,format,type,pixels);}
inline void glGetColorTableParameteriv(GLenum target,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetColorTableParameteriv))(target,pname,params);}
inline void glTextureStorage3D(GLuint texture,GLsizei levels,GLenum internalformat,GLsizei width,GLsizei height,GLsizei depth)const{(this->*(this->m_ptr_glTextureStorage3D))(texture,levels,internalformat,width,height,depth);}
inline void glSecondaryColor3fvEXT(const GLfloat* v)const{(this->*(this->m_ptr_glSecondaryColor3fvEXT))(v);}
inline void glUniformMatrix4x2fv(GLint location,GLsizei count,GLboolean transpose,const GLfloat* value)const{(this->*(this->m_ptr_glUniformMatrix4x2fv))(location,count,transpose,value);}
inline GLuint glGenLists(GLsizei range)const{return (this->*(this->m_ptr_glGenLists))(range);}
inline void glVertexAttrib3dv(GLuint index,const GLdouble* v)const{(this->*(this->m_ptr_glVertexAttrib3dv))(index,v);}
inline void* glMapBufferRange(GLenum target,GLintptr offset,GLsizeiptr length,GLbitfield access)const{return (this->*(this->m_ptr_glMapBufferRange))(target,offset,length,access);}
inline void glProgramUniformMatrix4x2fv(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLfloat* value)const{(this->*(this->m_ptr_glProgramUniformMatrix4x2fv))(program,location,count,transpose,value);}
inline void glGetTextureParameterIivEXT(GLuint texture,GLenum target,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetTextureParameterIivEXT))(texture,target,pname,params);}
inline void glNamedProgramLocalParametersI4uivEXT(GLuint program,GLenum target,GLuint index,GLsizei count,const GLuint* params)const{(this->*(this->m_ptr_glNamedProgramLocalParametersI4uivEXT))(program,target,index,count,params);}
inline void glEndList()const{(this->*(this->m_ptr_glEndList))();}
inline void glVertexAttribI2iv(GLuint index,const GLint* v)const{(this->*(this->m_ptr_glVertexAttribI2iv))(index,v);}
inline void glCopyMultiTexImage2DEXT(GLenum texunit,GLenum target,GLint level,GLenum internalformat,GLint x,GLint y,GLsizei width,GLsizei height,GLint border)const{(this->*(this->m_ptr_glCopyMultiTexImage2DEXT))(texunit,target,level,internalformat,x,y,width,height,border);}
inline void glGetShaderPrecisionFormat(GLenum shadertype,GLenum precisiontype,GLint* range,GLint* precision)const{(this->*(this->m_ptr_glGetShaderPrecisionFormat))(shadertype,precisiontype,range,precision);}
inline void glRasterSamplesEXT(GLuint samples,GLboolean fixedsamplelocations)const{(this->*(this->m_ptr_glRasterSamplesEXT))(samples,fixedsamplelocations);}
inline void glTextureView(GLuint texture,GLenum target,GLuint origtexture,GLenum internalformat,GLuint minlevel,GLuint numlevels,GLuint minlayer,GLuint numlayers)const{(this->*(this->m_ptr_glTextureView))(texture,target,origtexture,internalformat,minlevel,numlevels,minlayer,numlayers);}
inline GLint glGetFragDataLocationEXT(GLuint program,const GLchar* name)const{return (this->*(this->m_ptr_glGetFragDataLocationEXT))(program,name);}
inline void glGetCompressedMultiTexImageEXT(GLenum texunit,GLenum target,GLint lod,void* img)const{(this->*(this->m_ptr_glGetCompressedMultiTexImageEXT))(texunit,target,lod,img);}
inline void glIndexMask(GLuint mask)const{(this->*(this->m_ptr_glIndexMask))(mask);}
inline void glProgramUniformMatrix2x3dv(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLdouble* value)const{(this->*(this->m_ptr_glProgramUniformMatrix2x3dv))(program,location,count,transpose,value);}
inline void glShaderSource(GLuint shader,GLsizei count,const GLchar*const* string,const GLint* length)const{(this->*(this->m_ptr_glShaderSource))(shader,count,string,length);}
inline void glDeleteRenderbuffers(GLsizei n,const GLuint* renderbuffers)const{(this->*(this->m_ptr_glDeleteRenderbuffers))(n,renderbuffers);}
inline void glTexCoordP2uiv(GLenum type,const GLuint* coords)const{(this->*(this->m_ptr_glTexCoordP2uiv))(type,coords);}
inline void glUniform2f(GLint location,GLfloat v0,GLfloat v1)const{(this->*(this->m_ptr_glUniform2f))(location,v0,v1);}
inline void glGetNamedBufferParameteri64v(GLuint buffer,GLenum pname,GLint64* params)const{(this->*(this->m_ptr_glGetNamedBufferParameteri64v))(buffer,pname,params);}
inline void glTextureParameterIivEXT(GLuint texture,GLenum target,GLenum pname,const GLint* params)const{(this->*(this->m_ptr_glTextureParameterIivEXT))(texture,target,pname,params);}
inline void glMultiTexParameterfvEXT(GLenum texunit,GLenum target,GLenum pname,const GLfloat* params)const{(this->*(this->m_ptr_glMultiTexParameterfvEXT))(texunit,target,pname,params);}
inline void glVertex4d(GLdouble x,GLdouble y,GLdouble z,GLdouble w)const{(this->*(this->m_ptr_glVertex4d))(x,y,z,w);}
inline void glBufferData(GLenum target,GLsizeiptr size,const void* data,GLenum usage)const{(this->*(this->m_ptr_glBufferData))(target,size,data,usage);}
inline void glTextureImage1DEXT(GLuint texture,GLenum target,GLint level,GLint internalformat,GLsizei width,GLint border,GLenum format,GLenum type,const void* pixels)const{(this->*(this->m_ptr_glTextureImage1DEXT))(texture,target,level,internalformat,width,border,format,type,pixels);}
inline void glGetTexParameterIiv(GLenum target,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetTexParameterIiv))(target,pname,params);}
inline void glCopyTexSubImage1DEXT(GLenum target,GLint level,GLint xoffset,GLint x,GLint y,GLsizei width)const{(this->*(this->m_ptr_glCopyTexSubImage1DEXT))(target,level,xoffset,x,y,width);}
inline void glVertex4f(GLfloat x,GLfloat y,GLfloat z,GLfloat w)const{(this->*(this->m_ptr_glVertex4f))(x,y,z,w);}
inline void glTexCoordP1ui(GLenum type,GLuint coords)const{(this->*(this->m_ptr_glTexCoordP1ui))(type,coords);}
inline void glPointParameterfvEXT(GLenum pname,const GLfloat* params)const{(this->*(this->m_ptr_glPointParameterfvEXT))(pname,params);}
inline void glCopyTextureSubImage3D(GLuint texture,GLint level,GLint xoffset,GLint yoffset,GLint zoffset,GLint x,GLint y,GLsizei width,GLsizei height)const{(this->*(this->m_ptr_glCopyTextureSubImage3D))(texture,level,xoffset,yoffset,zoffset,x,y,width,height);}
inline void glMultiTexCoord2fv(GLenum target,const GLfloat* v)const{(this->*(this->m_ptr_glMultiTexCoord2fv))(target,v);}
inline void glMultiTexEnvfvEXT(GLenum texunit,GLenum target,GLenum pname,const GLfloat* params)const{(this->*(this->m_ptr_glMultiTexEnvfvEXT))(texunit,target,pname,params);}
inline void glNormalP3ui(GLenum type,GLuint coords)const{(this->*(this->m_ptr_glNormalP3ui))(type,coords);}
inline void glVertexAttribI1i(GLuint index,GLint x)const{(this->*(this->m_ptr_glVertexAttribI1i))(index,x);}
inline void glNamedProgramLocalParameters4fvEXT(GLuint program,GLenum target,GLuint index,GLsizei count,const GLfloat* params)const{(this->*(this->m_ptr_glNamedProgramLocalParameters4fvEXT))(program,target,index,count,params);}
inline void glCopyConvolutionFilter2DEXT(GLenum target,GLenum internalformat,GLint x,GLint y,GLsizei width,GLsizei height)const{(this->*(this->m_ptr_glCopyConvolutionFilter2DEXT))(target,internalformat,x,y,width,height);}
inline void glFramebufferTexture3D(GLenum target,GLenum attachment,GLenum textarget,GLuint texture,GLint level,GLint zoffset)const{(this->*(this->m_ptr_glFramebufferTexture3D))(target,attachment,textarget,texture,level,zoffset);}
inline void glCompressedTextureSubImage2DEXT(GLuint texture,GLenum target,GLint level,GLint xoffset,GLint yoffset,GLsizei width,GLsizei height,GLenum format,GLsizei imageSize,const void* bits)const{(this->*(this->m_ptr_glCompressedTextureSubImage2DEXT))(texture,target,level,xoffset,yoffset,width,height,format,imageSize,bits);}
inline void glWindowPos3dv(const GLdouble* v)const{(this->*(this->m_ptr_glWindowPos3dv))(v);}
inline void glSamplerParameterfv(GLuint sampler,GLenum pname,const GLfloat* param)const{(this->*(this->m_ptr_glSamplerParameterfv))(sampler,pname,param);}
inline void glGetMaterialiv(GLenum face,GLenum pname,GLint* params)const{(this->*(this->m_ptr_glGetMaterialiv))(face,pname,params);}
inline void glUniform1fv(GLint location,GLsizei count,const GLfloat* value)const{(this->*(this->m_ptr_glUniform1fv))(location,count,value);}
inline void glScissorIndexedv(GLuint index,const GLint* v)const{(this->*(this->m_ptr_glScissorIndexedv))(index,v);}
inline void glDisableVariantClientStateEXT(GLuint id)const{(this->*(this->m_ptr_glDisableVariantClientStateEXT))(id);}
inline void glMinmaxEXT(GLenum target,GLenum internalformat,GLboolean sink)const{(this->*(this->m_ptr_glMinmaxEXT))(target,internalformat,sink);}
inline void glNormal3s(GLshort nx,GLshort ny,GLshort nz)const{(this->*(this->m_ptr_glNormal3s))(nx,ny,nz);}
inline void glGetnPixelMapuiv(GLenum map,GLsizei bufSize,GLuint* values)const{(this->*(this->m_ptr_glGetnPixelMapuiv))(map,bufSize,values);}
inline void glNormal3i(GLint nx,GLint ny,GLint nz)const{(this->*(this->m_ptr_glNormal3i))(nx,ny,nz);}
inline void glNormal3f(GLfloat nx,GLfloat ny,GLfloat nz)const{(this->*(this->m_ptr_glNormal3f))(nx,ny,nz);}
inline void glNormal3d(GLdouble nx,GLdouble ny,GLdouble nz)const{(this->*(this->m_ptr_glNormal3d))(nx,ny,nz);}
inline void glNormal3b(GLbyte nx,GLbyte ny,GLbyte nz)const{(this->*(this->m_ptr_glNormal3b))(nx,ny,nz);}
inline GLint glGetUniformBufferSizeEXT(GLuint program,GLint location)const{return (this->*(this->m_ptr_glGetUniformBufferSizeEXT))(program,location);}
inline void glMultiTexCoord4dv(GLenum target,const GLdouble* v)const{(this->*(this->m_ptr_glMultiTexCoord4dv))(target,v);}
inline void glVertexAttrib2d(GLuint index,GLdouble x,GLdouble y)const{(this->*(this->m_ptr_glVertexAttrib2d))(index,x,y);}
inline void glVertexAttrib2f(GLuint index,GLfloat x,GLfloat y)const{(this->*(this->m_ptr_glVertexAttrib2f))(index,x,y);}
inline void glMultiDrawElementsEXT(GLenum mode,const GLsizei* count,GLenum type,const void*const* indices,GLsizei primcount)const{(this->*(this->m_ptr_glMultiDrawElementsEXT))(mode,count,type,indices,primcount);}
inline void glGetTransformFeedbackVaryingEXT(GLuint program,GLuint index,GLsizei bufSize,GLsizei* length,GLsizei* size,GLenum* type,GLchar* name)const{(this->*(this->m_ptr_glGetTransformFeedbackVaryingEXT))(program,index,bufSize,length,size,type,name);}
inline void glVertexAttrib2s(GLuint index,GLshort x,GLshort y)const{(this->*(this->m_ptr_glVertexAttrib2s))(index,x,y);}
inline void glTexImage3DMultisample(GLenum target,GLsizei samples,GLenum internalformat,GLsizei width,GLsizei height,GLsizei depth,GLboolean fixedsamplelocations)const{(this->*(this->m_ptr_glTexImage3DMultisample))(target,samples,internalformat,width,height,depth,fixedsamplelocations);}
inline GLuint glGetUniformBlockIndex(GLuint program,const GLchar* uniformBlockName)const{return (this->*(this->m_ptr_glGetUniformBlockIndex))(program,uniformBlockName);}
inline void glFrontFace(GLenum mode)const{(this->*(this->m_ptr_glFrontFace))(mode);}
inline void glDrawArraysInstancedBaseInstance(GLenum mode,GLint first,GLsizei count,GLsizei instancecount,GLuint baseinstance)const{(this->*(this->m_ptr_glDrawArraysInstancedBaseInstance))(mode,first,count,instancecount,baseinstance);}
inline void glRasterPos3sv(const GLshort* v)const{(this->*(this->m_ptr_glRasterPos3sv))(v);}
inline void glProgramEnvParameters4fvEXT(GLenum target,GLuint index,GLsizei count,const GLfloat* params)const{(this->*(this->m_ptr_glProgramEnvParameters4fvEXT))(target,index,count,params);}
