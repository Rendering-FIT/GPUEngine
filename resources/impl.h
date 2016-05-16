#pragma once

inline const GLubyte* glGetString(GLenum name){return this->_getTable()->glGetString(name);}
inline const GLubyte* glGetStringi(GLenum name,GLuint index){return this->_getTable()->glGetStringi(name,index);}
inline GLbitfield glQueryMatrixxOES(GLfixed* mantissa,GLint* exponent){return this->_getTable()->glQueryMatrixxOES(mantissa,exponent);}
inline GLboolean glAreProgramsResidentNV(GLsizei n,const GLuint* programs,GLboolean* residences){return this->_getTable()->glAreProgramsResidentNV(n,programs,residences);}
inline GLboolean glAreTexturesResidentEXT(GLsizei n,const GLuint* textures,GLboolean* residences){return this->_getTable()->glAreTexturesResidentEXT(n,textures,residences);}
inline GLboolean glAreTexturesResident(GLsizei n,const GLuint* textures,GLboolean* residences){return this->_getTable()->glAreTexturesResident(n,textures,residences);}
inline GLboolean glIsAsyncMarkerSGIX(GLuint marker){return this->_getTable()->glIsAsyncMarkerSGIX(marker);}
inline GLboolean glIsBufferARB(GLuint buffer){return this->_getTable()->glIsBufferARB(buffer);}
inline GLboolean glIsBuffer(GLuint buffer){return this->_getTable()->glIsBuffer(buffer);}
inline GLboolean glIsBufferResidentNV(GLenum target){return this->_getTable()->glIsBufferResidentNV(target);}
inline GLboolean glIsCommandListNV(GLuint list){return this->_getTable()->glIsCommandListNV(list);}
inline GLboolean glIsEnabled(GLenum cap){return this->_getTable()->glIsEnabled(cap);}
inline GLboolean glIsEnabledi(GLenum target,GLuint index){return this->_getTable()->glIsEnabledi(target,index);}
inline GLboolean glIsEnabledIndexedEXT(GLenum target,GLuint index){return this->_getTable()->glIsEnabledIndexedEXT(target,index);}
inline GLboolean glIsFenceAPPLE(GLuint fence){return this->_getTable()->glIsFenceAPPLE(fence);}
inline GLboolean glIsFenceNV(GLuint fence){return this->_getTable()->glIsFenceNV(fence);}
inline GLboolean glIsFramebufferEXT(GLuint framebuffer){return this->_getTable()->glIsFramebufferEXT(framebuffer);}
inline GLboolean glIsFramebuffer(GLuint framebuffer){return this->_getTable()->glIsFramebuffer(framebuffer);}
inline GLboolean glIsImageHandleResidentARB(GLuint64 handle){return this->_getTable()->glIsImageHandleResidentARB(handle);}
inline GLboolean glIsImageHandleResidentNV(GLuint64 handle){return this->_getTable()->glIsImageHandleResidentNV(handle);}
inline GLboolean glIsList(GLuint list){return this->_getTable()->glIsList(list);}
inline GLboolean glIsNameAMD(GLenum identifier,GLuint name){return this->_getTable()->glIsNameAMD(identifier,name);}
inline GLboolean glIsNamedBufferResidentNV(GLuint buffer){return this->_getTable()->glIsNamedBufferResidentNV(buffer);}
inline GLboolean glIsNamedStringARB(GLint namelen,const GLchar* name){return this->_getTable()->glIsNamedStringARB(namelen,name);}
inline GLboolean glIsObjectBufferATI(GLuint buffer){return this->_getTable()->glIsObjectBufferATI(buffer);}
inline GLboolean glIsOcclusionQueryNV(GLuint id){return this->_getTable()->glIsOcclusionQueryNV(id);}
inline GLboolean glIsPathNV(GLuint path){return this->_getTable()->glIsPathNV(path);}
inline GLboolean glIsPointInFillPathNV(GLuint path,GLuint mask,GLfloat x,GLfloat y){return this->_getTable()->glIsPointInFillPathNV(path,mask,x,y);}
inline GLboolean glIsPointInStrokePathNV(GLuint path,GLfloat x,GLfloat y){return this->_getTable()->glIsPointInStrokePathNV(path,x,y);}
inline GLboolean glIsProgramARB(GLuint program){return this->_getTable()->glIsProgramARB(program);}
inline GLboolean glIsProgram(GLuint program){return this->_getTable()->glIsProgram(program);}
inline GLboolean glIsProgramNV(GLuint id){return this->_getTable()->glIsProgramNV(id);}
inline GLboolean glIsProgramPipeline(GLuint pipeline){return this->_getTable()->glIsProgramPipeline(pipeline);}
inline GLboolean glIsQueryARB(GLuint id){return this->_getTable()->glIsQueryARB(id);}
inline GLboolean glIsQuery(GLuint id){return this->_getTable()->glIsQuery(id);}
inline GLboolean glIsRenderbufferEXT(GLuint renderbuffer){return this->_getTable()->glIsRenderbufferEXT(renderbuffer);}
inline GLboolean glIsRenderbuffer(GLuint renderbuffer){return this->_getTable()->glIsRenderbuffer(renderbuffer);}
inline GLboolean glIsSampler(GLuint sampler){return this->_getTable()->glIsSampler(sampler);}
inline GLboolean glIsShader(GLuint shader){return this->_getTable()->glIsShader(shader);}
inline GLboolean glIsStateNV(GLuint state){return this->_getTable()->glIsStateNV(state);}
inline GLboolean glIsSync(GLsync sync){return this->_getTable()->glIsSync(sync);}
inline GLboolean glIsTextureEXT(GLuint texture){return this->_getTable()->glIsTextureEXT(texture);}
inline GLboolean glIsTexture(GLuint texture){return this->_getTable()->glIsTexture(texture);}
inline GLboolean glIsTextureHandleResidentARB(GLuint64 handle){return this->_getTable()->glIsTextureHandleResidentARB(handle);}
inline GLboolean glIsTextureHandleResidentNV(GLuint64 handle){return this->_getTable()->glIsTextureHandleResidentNV(handle);}
inline GLboolean glIsTransformFeedback(GLuint id){return this->_getTable()->glIsTransformFeedback(id);}
inline GLboolean glIsTransformFeedbackNV(GLuint id){return this->_getTable()->glIsTransformFeedbackNV(id);}
inline GLboolean glIsVariantEnabledEXT(GLuint id,GLenum cap){return this->_getTable()->glIsVariantEnabledEXT(id,cap);}
inline GLboolean glIsVertexArrayAPPLE(GLuint array){return this->_getTable()->glIsVertexArrayAPPLE(array);}
inline GLboolean glIsVertexArray(GLuint array){return this->_getTable()->glIsVertexArray(array);}
inline GLboolean glIsVertexAttribEnabledAPPLE(GLuint index,GLenum pname){return this->_getTable()->glIsVertexAttribEnabledAPPLE(index,pname);}
inline GLboolean glPointAlongPathNV(GLuint path,GLsizei startSegment,GLsizei numSegments,GLfloat distance,GLfloat* x,GLfloat* y,GLfloat* tangentX,GLfloat* tangentY){return this->_getTable()->glPointAlongPathNV(path,startSegment,numSegments,distance,x,y,tangentX,tangentY);}
inline GLboolean glTestFenceAPPLE(GLuint fence){return this->_getTable()->glTestFenceAPPLE(fence);}
inline GLboolean glTestFenceNV(GLuint fence){return this->_getTable()->glTestFenceNV(fence);}
inline GLboolean glTestObjectAPPLE(GLenum object,GLuint name){return this->_getTable()->glTestObjectAPPLE(object,name);}
inline GLboolean glUnmapBufferARB(GLenum target){return this->_getTable()->glUnmapBufferARB(target);}
inline GLboolean glUnmapBuffer(GLenum target){return this->_getTable()->glUnmapBuffer(target);}
inline GLboolean glUnmapNamedBufferEXT(GLuint buffer){return this->_getTable()->glUnmapNamedBufferEXT(buffer);}
inline GLboolean glUnmapNamedBuffer(GLuint buffer){return this->_getTable()->glUnmapNamedBuffer(buffer);}
inline GLboolean glVDPAUIsSurfaceNV(GLvdpauSurfaceNV surface){return this->_getTable()->glVDPAUIsSurfaceNV(surface);}
inline GLenum glCheckFramebufferStatusEXT(GLenum target){return this->_getTable()->glCheckFramebufferStatusEXT(target);}
inline GLenum glCheckFramebufferStatus(GLenum target){return this->_getTable()->glCheckFramebufferStatus(target);}
inline GLenum glCheckNamedFramebufferStatusEXT(GLuint framebuffer,GLenum target){return this->_getTable()->glCheckNamedFramebufferStatusEXT(framebuffer,target);}
inline GLenum glCheckNamedFramebufferStatus(GLuint framebuffer,GLenum target){return this->_getTable()->glCheckNamedFramebufferStatus(framebuffer,target);}
inline GLenum glClientWaitSync(GLsync sync,GLbitfield flags,GLuint64 timeout){return this->_getTable()->glClientWaitSync(sync,flags,timeout);}
inline GLenum glGetError(){return this->_getTable()->glGetError();}
inline GLenum glGetGraphicsResetStatus(){return this->_getTable()->glGetGraphicsResetStatus();}
inline GLenum glGetGraphicsResetStatusARB(){return this->_getTable()->glGetGraphicsResetStatusARB();}
inline GLenum glObjectPurgeableAPPLE(GLenum objectType,GLuint name,GLenum option){return this->_getTable()->glObjectPurgeableAPPLE(objectType,name,option);}
inline GLenum glObjectUnpurgeableAPPLE(GLenum objectType,GLuint name,GLenum option){return this->_getTable()->glObjectUnpurgeableAPPLE(objectType,name,option);}
inline GLenum glPathGlyphIndexArrayNV(GLuint firstPathName,GLenum fontTarget,const void* fontName,GLbitfield fontStyle,GLuint firstGlyphIndex,GLsizei numGlyphs,GLuint pathParameterTemplate,GLfloat emScale){return this->_getTable()->glPathGlyphIndexArrayNV(firstPathName,fontTarget,fontName,fontStyle,firstGlyphIndex,numGlyphs,pathParameterTemplate,emScale);}
inline GLenum glPathGlyphIndexRangeNV(GLenum fontTarget,const void* fontName,GLbitfield fontStyle,GLuint pathParameterTemplate,GLfloat emScale,GLuint baseAndCount[2]){return this->_getTable()->glPathGlyphIndexRangeNV(fontTarget,fontName,fontStyle,pathParameterTemplate,emScale,baseAndCount[2]);}
inline GLenum glPathMemoryGlyphIndexArrayNV(GLuint firstPathName,GLenum fontTarget,GLsizeiptr fontSize,const void* fontData,GLsizei faceIndex,GLuint firstGlyphIndex,GLsizei numGlyphs,GLuint pathParameterTemplate,GLfloat emScale){return this->_getTable()->glPathMemoryGlyphIndexArrayNV(firstPathName,fontTarget,fontSize,fontData,faceIndex,firstGlyphIndex,numGlyphs,pathParameterTemplate,emScale);}
inline GLenum glVideoCaptureNV(GLuint video_capture_slot,GLuint* sequence_num,GLuint64EXT* capture_time){return this->_getTable()->glVideoCaptureNV(video_capture_slot,sequence_num,capture_time);}
inline GLfloat glGetPathLengthNV(GLuint path,GLsizei startSegment,GLsizei numSegments){return this->_getTable()->glGetPathLengthNV(path,startSegment,numSegments);}
inline GLhandleARB glCreateProgramObjectARB(){return this->_getTable()->glCreateProgramObjectARB();}
inline GLhandleARB glCreateShaderObjectARB(GLenum shaderType){return this->_getTable()->glCreateShaderObjectARB(shaderType);}
inline GLhandleARB glGetHandleARB(GLenum pname){return this->_getTable()->glGetHandleARB(pname);}
inline GLint glFinishAsyncSGIX(GLuint* markerp){return this->_getTable()->glFinishAsyncSGIX(markerp);}
inline GLint glGetAttribLocationARB(GLhandleARB programObj,const GLcharARB* name){return this->_getTable()->glGetAttribLocationARB(programObj,name);}
inline GLint glGetAttribLocation(GLuint program,const GLchar* name){return this->_getTable()->glGetAttribLocation(program,name);}
inline GLint glGetFragDataIndex(GLuint program,const GLchar* name){return this->_getTable()->glGetFragDataIndex(program,name);}
inline GLint glGetFragDataLocationEXT(GLuint program,const GLchar* name){return this->_getTable()->glGetFragDataLocationEXT(program,name);}
inline GLint glGetFragDataLocation(GLuint program,const GLchar* name){return this->_getTable()->glGetFragDataLocation(program,name);}
inline GLint glGetInstrumentsSGIX(){return this->_getTable()->glGetInstrumentsSGIX();}
inline GLint glGetProgramResourceLocation(GLuint program,GLenum programInterface,const GLchar* name){return this->_getTable()->glGetProgramResourceLocation(program,programInterface,name);}
inline GLint glGetProgramResourceLocationIndex(GLuint program,GLenum programInterface,const GLchar* name){return this->_getTable()->glGetProgramResourceLocationIndex(program,programInterface,name);}
inline GLint glGetSubroutineUniformLocation(GLuint program,GLenum shadertype,const GLchar* name){return this->_getTable()->glGetSubroutineUniformLocation(program,shadertype,name);}
inline GLint glGetUniformBufferSizeEXT(GLuint program,GLint location){return this->_getTable()->glGetUniformBufferSizeEXT(program,location);}
inline GLint glGetUniformLocationARB(GLhandleARB programObj,const GLcharARB* name){return this->_getTable()->glGetUniformLocationARB(programObj,name);}
inline GLint glGetUniformLocation(GLuint program,const GLchar* name){return this->_getTable()->glGetUniformLocation(program,name);}
inline GLint glGetVaryingLocationNV(GLuint program,const GLchar* name){return this->_getTable()->glGetVaryingLocationNV(program,name);}
inline GLint glPollAsyncSGIX(GLuint* markerp){return this->_getTable()->glPollAsyncSGIX(markerp);}
inline GLint glPollInstrumentsSGIX(GLint* marker_p){return this->_getTable()->glPollInstrumentsSGIX(marker_p);}
inline GLint glRenderMode(GLenum mode){return this->_getTable()->glRenderMode(mode);}
inline GLintptr glGetUniformOffsetEXT(GLuint program,GLint location){return this->_getTable()->glGetUniformOffsetEXT(program,location);}
inline GLsync glCreateSyncFromCLeventARB(struct _cl_context* context,struct _cl_event* event,GLbitfield flags){return this->_getTable()->glCreateSyncFromCLeventARB(context,event,flags);}
inline GLsync glFenceSync(GLenum condition,GLbitfield flags){return this->_getTable()->glFenceSync(condition,flags);}
inline GLsync glImportSyncEXT(GLenum external_sync_type,GLintptr external_sync,GLbitfield flags){return this->_getTable()->glImportSyncEXT(external_sync_type,external_sync,flags);}
inline GLuint64 glGetImageHandleARB(GLuint texture,GLint level,GLboolean layered,GLint layer,GLenum format){return this->_getTable()->glGetImageHandleARB(texture,level,layered,layer,format);}
inline GLuint64 glGetImageHandleNV(GLuint texture,GLint level,GLboolean layered,GLint layer,GLenum format){return this->_getTable()->glGetImageHandleNV(texture,level,layered,layer,format);}
inline GLuint64 glGetTextureHandleARB(GLuint texture){return this->_getTable()->glGetTextureHandleARB(texture);}
inline GLuint64 glGetTextureHandleNV(GLuint texture){return this->_getTable()->glGetTextureHandleNV(texture);}
inline GLuint64 glGetTextureSamplerHandleARB(GLuint texture,GLuint sampler){return this->_getTable()->glGetTextureSamplerHandleARB(texture,sampler);}
inline GLuint64 glGetTextureSamplerHandleNV(GLuint texture,GLuint sampler){return this->_getTable()->glGetTextureSamplerHandleNV(texture,sampler);}
inline GLuint glBindLightParameterEXT(GLenum light,GLenum value){return this->_getTable()->glBindLightParameterEXT(light,value);}
inline GLuint glBindMaterialParameterEXT(GLenum face,GLenum value){return this->_getTable()->glBindMaterialParameterEXT(face,value);}
inline GLuint glBindParameterEXT(GLenum value){return this->_getTable()->glBindParameterEXT(value);}
inline GLuint glBindTexGenParameterEXT(GLenum unit,GLenum coord,GLenum value){return this->_getTable()->glBindTexGenParameterEXT(unit,coord,value);}
inline GLuint glBindTextureUnitParameterEXT(GLenum unit,GLenum value){return this->_getTable()->glBindTextureUnitParameterEXT(unit,value);}
inline GLuint glCreateProgram(){return this->_getTable()->glCreateProgram();}
inline GLuint glCreateShader(GLenum type){return this->_getTable()->glCreateShader(type);}
inline GLuint glCreateShaderProgramEXT(GLenum type,const GLchar* string){return this->_getTable()->glCreateShaderProgramEXT(type,string);}
inline GLuint glCreateShaderProgramv(GLenum type,GLsizei count,const GLchar*const* strings){return this->_getTable()->glCreateShaderProgramv(type,count,strings);}
inline GLuint glGenAsyncMarkersSGIX(GLsizei range){return this->_getTable()->glGenAsyncMarkersSGIX(range);}
inline GLuint glGenFragmentShadersATI(GLuint range){return this->_getTable()->glGenFragmentShadersATI(range);}
inline GLuint glGenLists(GLsizei range){return this->_getTable()->glGenLists(range);}
inline GLuint glGenPathsNV(GLsizei range){return this->_getTable()->glGenPathsNV(range);}
inline GLuint glGenSymbolsEXT(GLenum datatype,GLenum storagetype,GLenum range,GLuint components){return this->_getTable()->glGenSymbolsEXT(datatype,storagetype,range,components);}
inline GLuint glGenVertexShadersEXT(GLuint range){return this->_getTable()->glGenVertexShadersEXT(range);}
inline GLuint glGetCommandHeaderNV(GLenum tokenID,GLuint size){return this->_getTable()->glGetCommandHeaderNV(tokenID,size);}
inline GLuint glGetDebugMessageLogAMD(GLuint count,GLsizei bufsize,GLenum* categories,GLuint* severities,GLuint* ids,GLsizei* lengths,GLchar* message){return this->_getTable()->glGetDebugMessageLogAMD(count,bufsize,categories,severities,ids,lengths,message);}
inline GLuint glGetDebugMessageLogARB(GLuint count,GLsizei bufSize,GLenum* sources,GLenum* types,GLuint* ids,GLenum* severities,GLsizei* lengths,GLchar* messageLog){return this->_getTable()->glGetDebugMessageLogARB(count,bufSize,sources,types,ids,severities,lengths,messageLog);}
inline GLuint glGetDebugMessageLog(GLuint count,GLsizei bufSize,GLenum* sources,GLenum* types,GLuint* ids,GLenum* severities,GLsizei* lengths,GLchar* messageLog){return this->_getTable()->glGetDebugMessageLog(count,bufSize,sources,types,ids,severities,lengths,messageLog);}
inline GLuint glGetProgramResourceIndex(GLuint program,GLenum programInterface,const GLchar* name){return this->_getTable()->glGetProgramResourceIndex(program,programInterface,name);}
inline GLuint glGetSubroutineIndex(GLuint program,GLenum shadertype,const GLchar* name){return this->_getTable()->glGetSubroutineIndex(program,shadertype,name);}
inline GLuint glGetUniformBlockIndex(GLuint program,const GLchar* uniformBlockName){return this->_getTable()->glGetUniformBlockIndex(program,uniformBlockName);}
inline GLuint glNewObjectBufferATI(GLsizei size,const void* pointer,GLenum usage){return this->_getTable()->glNewObjectBufferATI(size,pointer,usage);}
inline GLushort glGetStageIndexNV(GLenum shadertype){return this->_getTable()->glGetStageIndexNV(shadertype);}
inline GLvdpauSurfaceNV glVDPAURegisterOutputSurfaceNV(const void* vdpSurface,GLenum target,GLsizei numTextureNames,const GLuint* textureNames){return this->_getTable()->glVDPAURegisterOutputSurfaceNV(vdpSurface,target,numTextureNames,textureNames);}
inline GLvdpauSurfaceNV glVDPAURegisterVideoSurfaceNV(const void* vdpSurface,GLenum target,GLsizei numTextureNames,const GLuint* textureNames){return this->_getTable()->glVDPAURegisterVideoSurfaceNV(vdpSurface,target,numTextureNames,textureNames);}
inline void glAccum(GLenum op,GLfloat value){this->_getTable()->glAccum(op,value);}
inline void glAccumxOES(GLenum op,GLfixed value){this->_getTable()->glAccumxOES(op,value);}
inline void glActiveProgramEXT(GLuint program){this->_getTable()->glActiveProgramEXT(program);}
inline void glActiveShaderProgram(GLuint pipeline,GLuint program){this->_getTable()->glActiveShaderProgram(pipeline,program);}
inline void glActiveStencilFaceEXT(GLenum face){this->_getTable()->glActiveStencilFaceEXT(face);}
inline void glActiveTextureARB(GLenum texture){this->_getTable()->glActiveTextureARB(texture);}
inline void glActiveTexture(GLenum texture){this->_getTable()->glActiveTexture(texture);}
inline void glActiveVaryingNV(GLuint program,const GLchar* name){this->_getTable()->glActiveVaryingNV(program,name);}
inline void glAlphaFragmentOp1ATI(GLenum op,GLuint dst,GLuint dstMod,GLuint arg1,GLuint arg1Rep,GLuint arg1Mod){this->_getTable()->glAlphaFragmentOp1ATI(op,dst,dstMod,arg1,arg1Rep,arg1Mod);}
inline void glAlphaFragmentOp2ATI(GLenum op,GLuint dst,GLuint dstMod,GLuint arg1,GLuint arg1Rep,GLuint arg1Mod,GLuint arg2,GLuint arg2Rep,GLuint arg2Mod){this->_getTable()->glAlphaFragmentOp2ATI(op,dst,dstMod,arg1,arg1Rep,arg1Mod,arg2,arg2Rep,arg2Mod);}
inline void glAlphaFragmentOp3ATI(GLenum op,GLuint dst,GLuint dstMod,GLuint arg1,GLuint arg1Rep,GLuint arg1Mod,GLuint arg2,GLuint arg2Rep,GLuint arg2Mod,GLuint arg3,GLuint arg3Rep,GLuint arg3Mod){this->_getTable()->glAlphaFragmentOp3ATI(op,dst,dstMod,arg1,arg1Rep,arg1Mod,arg2,arg2Rep,arg2Mod,arg3,arg3Rep,arg3Mod);}
inline void glAlphaFunc(GLenum func,GLclampf ref){this->_getTable()->glAlphaFunc(func,ref);}
inline void glAlphaFuncxOES(GLenum func,GLfixed ref){this->_getTable()->glAlphaFuncxOES(func,ref);}
inline void glApplyFramebufferAttachmentCMAAINTEL(){this->_getTable()->glApplyFramebufferAttachmentCMAAINTEL();}
inline void glApplyTextureEXT(GLenum mode){this->_getTable()->glApplyTextureEXT(mode);}
inline void glArrayElementEXT(GLint i){this->_getTable()->glArrayElementEXT(i);}
inline void glArrayElement(GLint i){this->_getTable()->glArrayElement(i);}
inline void glArrayObjectATI(GLenum array,GLint size,GLenum type,GLsizei stride,GLuint buffer,GLuint offset){this->_getTable()->glArrayObjectATI(array,size,type,stride,buffer,offset);}
inline void glAsyncMarkerSGIX(GLuint marker){this->_getTable()->glAsyncMarkerSGIX(marker);}
inline void glAttachObjectARB(GLhandleARB containerObj,GLhandleARB obj){this->_getTable()->glAttachObjectARB(containerObj,obj);}
inline void glAttachShader(GLuint program,GLuint shader){this->_getTable()->glAttachShader(program,shader);}
inline void glBeginConditionalRender(GLuint id,GLenum mode){this->_getTable()->glBeginConditionalRender(id,mode);}
inline void glBeginConditionalRenderNV(GLuint id,GLenum mode){this->_getTable()->glBeginConditionalRenderNV(id,mode);}
inline void glBeginConditionalRenderNVX(GLuint id){this->_getTable()->glBeginConditionalRenderNVX(id);}
inline void glBeginFragmentShaderATI(){this->_getTable()->glBeginFragmentShaderATI();}
inline void glBegin(GLenum mode){this->_getTable()->glBegin(mode);}
inline void glBeginOcclusionQueryNV(GLuint id){this->_getTable()->glBeginOcclusionQueryNV(id);}
inline void glBeginPerfMonitorAMD(GLuint monitor){this->_getTable()->glBeginPerfMonitorAMD(monitor);}
inline void glBeginPerfQueryINTEL(GLuint queryHandle){this->_getTable()->glBeginPerfQueryINTEL(queryHandle);}
inline void glBeginQueryARB(GLenum target,GLuint id){this->_getTable()->glBeginQueryARB(target,id);}
inline void glBeginQuery(GLenum target,GLuint id){this->_getTable()->glBeginQuery(target,id);}
inline void glBeginQueryIndexed(GLenum target,GLuint index,GLuint id){this->_getTable()->glBeginQueryIndexed(target,index,id);}
inline void glBeginTransformFeedbackEXT(GLenum primitiveMode){this->_getTable()->glBeginTransformFeedbackEXT(primitiveMode);}
inline void glBeginTransformFeedback(GLenum primitiveMode){this->_getTable()->glBeginTransformFeedback(primitiveMode);}
inline void glBeginTransformFeedbackNV(GLenum primitiveMode){this->_getTable()->glBeginTransformFeedbackNV(primitiveMode);}
inline void glBeginVertexShaderEXT(){this->_getTable()->glBeginVertexShaderEXT();}
inline void glBeginVideoCaptureNV(GLuint video_capture_slot){this->_getTable()->glBeginVideoCaptureNV(video_capture_slot);}
inline void glBindAttribLocationARB(GLhandleARB programObj,GLuint index,const GLcharARB* name){this->_getTable()->glBindAttribLocationARB(programObj,index,name);}
inline void glBindAttribLocation(GLuint program,GLuint index,const GLchar* name){this->_getTable()->glBindAttribLocation(program,index,name);}
inline void glBindBufferARB(GLenum target,GLuint buffer){this->_getTable()->glBindBufferARB(target,buffer);}
inline void glBindBufferBaseEXT(GLenum target,GLuint index,GLuint buffer){this->_getTable()->glBindBufferBaseEXT(target,index,buffer);}
inline void glBindBufferBase(GLenum target,GLuint index,GLuint buffer){this->_getTable()->glBindBufferBase(target,index,buffer);}
inline void glBindBufferBaseNV(GLenum target,GLuint index,GLuint buffer){this->_getTable()->glBindBufferBaseNV(target,index,buffer);}
inline void glBindBuffer(GLenum target,GLuint buffer){this->_getTable()->glBindBuffer(target,buffer);}
inline void glBindBufferOffsetEXT(GLenum target,GLuint index,GLuint buffer,GLintptr offset){this->_getTable()->glBindBufferOffsetEXT(target,index,buffer,offset);}
inline void glBindBufferOffsetNV(GLenum target,GLuint index,GLuint buffer,GLintptr offset){this->_getTable()->glBindBufferOffsetNV(target,index,buffer,offset);}
inline void glBindBufferRangeEXT(GLenum target,GLuint index,GLuint buffer,GLintptr offset,GLsizeiptr size){this->_getTable()->glBindBufferRangeEXT(target,index,buffer,offset,size);}
inline void glBindBufferRange(GLenum target,GLuint index,GLuint buffer,GLintptr offset,GLsizeiptr size){this->_getTable()->glBindBufferRange(target,index,buffer,offset,size);}
inline void glBindBufferRangeNV(GLenum target,GLuint index,GLuint buffer,GLintptr offset,GLsizeiptr size){this->_getTable()->glBindBufferRangeNV(target,index,buffer,offset,size);}
inline void glBindBuffersBase(GLenum target,GLuint first,GLsizei count,const GLuint* buffers){this->_getTable()->glBindBuffersBase(target,first,count,buffers);}
inline void glBindBuffersRange(GLenum target,GLuint first,GLsizei count,const GLuint* buffers,const GLintptr* offsets,const GLsizeiptr* sizes){this->_getTable()->glBindBuffersRange(target,first,count,buffers,offsets,sizes);}
inline void glBindFragDataLocationEXT(GLuint program,GLuint color,const GLchar* name){this->_getTable()->glBindFragDataLocationEXT(program,color,name);}
inline void glBindFragDataLocation(GLuint program,GLuint color,const GLchar* name){this->_getTable()->glBindFragDataLocation(program,color,name);}
inline void glBindFragDataLocationIndexed(GLuint program,GLuint colorNumber,GLuint index,const GLchar* name){this->_getTable()->glBindFragDataLocationIndexed(program,colorNumber,index,name);}
inline void glBindFragmentShaderATI(GLuint id){this->_getTable()->glBindFragmentShaderATI(id);}
inline void glBindFramebufferEXT(GLenum target,GLuint framebuffer){this->_getTable()->glBindFramebufferEXT(target,framebuffer);}
inline void glBindFramebuffer(GLenum target,GLuint framebuffer){this->_getTable()->glBindFramebuffer(target,framebuffer);}
inline void glBindImageTextureEXT(GLuint index,GLuint texture,GLint level,GLboolean layered,GLint layer,GLenum access,GLint format){this->_getTable()->glBindImageTextureEXT(index,texture,level,layered,layer,access,format);}
inline void glBindImageTexture(GLuint unit,GLuint texture,GLint level,GLboolean layered,GLint layer,GLenum access,GLenum format){this->_getTable()->glBindImageTexture(unit,texture,level,layered,layer,access,format);}
inline void glBindImageTextures(GLuint first,GLsizei count,const GLuint* textures){this->_getTable()->glBindImageTextures(first,count,textures);}
inline void glBindMultiTextureEXT(GLenum texunit,GLenum target,GLuint texture){this->_getTable()->glBindMultiTextureEXT(texunit,target,texture);}
inline void glBindProgramARB(GLenum target,GLuint program){this->_getTable()->glBindProgramARB(target,program);}
inline void glBindProgramNV(GLenum target,GLuint id){this->_getTable()->glBindProgramNV(target,id);}
inline void glBindProgramPipeline(GLuint pipeline){this->_getTable()->glBindProgramPipeline(pipeline);}
inline void glBindRenderbufferEXT(GLenum target,GLuint renderbuffer){this->_getTable()->glBindRenderbufferEXT(target,renderbuffer);}
inline void glBindRenderbuffer(GLenum target,GLuint renderbuffer){this->_getTable()->glBindRenderbuffer(target,renderbuffer);}
inline void glBindSampler(GLuint unit,GLuint sampler){this->_getTable()->glBindSampler(unit,sampler);}
inline void glBindSamplers(GLuint first,GLsizei count,const GLuint* samplers){this->_getTable()->glBindSamplers(first,count,samplers);}
inline void glBindTextureEXT(GLenum target,GLuint texture){this->_getTable()->glBindTextureEXT(target,texture);}
inline void glBindTexture(GLenum target,GLuint texture){this->_getTable()->glBindTexture(target,texture);}
inline void glBindTextures(GLuint first,GLsizei count,const GLuint* textures){this->_getTable()->glBindTextures(first,count,textures);}
inline void glBindTextureUnit(GLuint unit,GLuint texture){this->_getTable()->glBindTextureUnit(unit,texture);}
inline void glBindTransformFeedback(GLenum target,GLuint id){this->_getTable()->glBindTransformFeedback(target,id);}
inline void glBindTransformFeedbackNV(GLenum target,GLuint id){this->_getTable()->glBindTransformFeedbackNV(target,id);}
inline void glBindVertexArrayAPPLE(GLuint array){this->_getTable()->glBindVertexArrayAPPLE(array);}
inline void glBindVertexArray(GLuint array){this->_getTable()->glBindVertexArray(array);}
inline void glBindVertexBuffer(GLuint bindingindex,GLuint buffer,GLintptr offset,GLsizei stride){this->_getTable()->glBindVertexBuffer(bindingindex,buffer,offset,stride);}
inline void glBindVertexBuffers(GLuint first,GLsizei count,const GLuint* buffers,const GLintptr* offsets,const GLsizei* strides){this->_getTable()->glBindVertexBuffers(first,count,buffers,offsets,strides);}
inline void glBindVertexShaderEXT(GLuint id){this->_getTable()->glBindVertexShaderEXT(id);}
inline void glBindVideoCaptureStreamBufferNV(GLuint video_capture_slot,GLuint stream,GLenum frame_region,GLintptrARB offset){this->_getTable()->glBindVideoCaptureStreamBufferNV(video_capture_slot,stream,frame_region,offset);}
inline void glBindVideoCaptureStreamTextureNV(GLuint video_capture_slot,GLuint stream,GLenum frame_region,GLenum target,GLuint texture){this->_getTable()->glBindVideoCaptureStreamTextureNV(video_capture_slot,stream,frame_region,target,texture);}
inline void glBinormal3bEXT(GLbyte bx,GLbyte by,GLbyte bz){this->_getTable()->glBinormal3bEXT(bx,by,bz);}
inline void glBinormal3bvEXT(const GLbyte* v){this->_getTable()->glBinormal3bvEXT(v);}
inline void glBinormal3dEXT(GLdouble bx,GLdouble by,GLdouble bz){this->_getTable()->glBinormal3dEXT(bx,by,bz);}
inline void glBinormal3dvEXT(const GLdouble* v){this->_getTable()->glBinormal3dvEXT(v);}
inline void glBinormal3fEXT(GLfloat bx,GLfloat by,GLfloat bz){this->_getTable()->glBinormal3fEXT(bx,by,bz);}
inline void glBinormal3fvEXT(const GLfloat* v){this->_getTable()->glBinormal3fvEXT(v);}
inline void glBinormal3iEXT(GLint bx,GLint by,GLint bz){this->_getTable()->glBinormal3iEXT(bx,by,bz);}
inline void glBinormal3ivEXT(const GLint* v){this->_getTable()->glBinormal3ivEXT(v);}
inline void glBinormal3sEXT(GLshort bx,GLshort by,GLshort bz){this->_getTable()->glBinormal3sEXT(bx,by,bz);}
inline void glBinormal3svEXT(const GLshort* v){this->_getTable()->glBinormal3svEXT(v);}
inline void glBinormalPointerEXT(GLenum type,GLsizei stride,const void* pointer){this->_getTable()->glBinormalPointerEXT(type,stride,pointer);}
inline void glBitmap(GLsizei width,GLsizei height,GLfloat xorig,GLfloat yorig,GLfloat xmove,GLfloat ymove,const GLubyte* bitmap){this->_getTable()->glBitmap(width,height,xorig,yorig,xmove,ymove,bitmap);}
inline void glBitmapxOES(GLsizei width,GLsizei height,GLfixed xorig,GLfixed yorig,GLfixed xmove,GLfixed ymove,const GLubyte* bitmap){this->_getTable()->glBitmapxOES(width,height,xorig,yorig,xmove,ymove,bitmap);}
inline void glBlendBarrierKHR(){this->_getTable()->glBlendBarrierKHR();}
inline void glBlendBarrierNV(){this->_getTable()->glBlendBarrierNV();}
inline void glBlendColorEXT(GLfloat red,GLfloat green,GLfloat blue,GLfloat alpha){this->_getTable()->glBlendColorEXT(red,green,blue,alpha);}
inline void glBlendColor(GLfloat red,GLfloat green,GLfloat blue,GLfloat alpha){this->_getTable()->glBlendColor(red,green,blue,alpha);}
inline void glBlendColorxOES(GLfixed red,GLfixed green,GLfixed blue,GLfixed alpha){this->_getTable()->glBlendColorxOES(red,green,blue,alpha);}
inline void glBlendEquationEXT(GLenum mode){this->_getTable()->glBlendEquationEXT(mode);}
inline void glBlendEquation(GLenum mode){this->_getTable()->glBlendEquation(mode);}
inline void glBlendEquationiARB(GLuint buf,GLenum mode){this->_getTable()->glBlendEquationiARB(buf,mode);}
inline void glBlendEquationi(GLuint buf,GLenum mode){this->_getTable()->glBlendEquationi(buf,mode);}
inline void glBlendEquationIndexedAMD(GLuint buf,GLenum mode){this->_getTable()->glBlendEquationIndexedAMD(buf,mode);}
inline void glBlendEquationSeparateATI(GLenum modeRGB,GLenum modeA){this->_getTable()->glBlendEquationSeparateATI(modeRGB,modeA);}
inline void glBlendEquationSeparateEXT(GLenum modeRGB,GLenum modeAlpha){this->_getTable()->glBlendEquationSeparateEXT(modeRGB,modeAlpha);}
inline void glBlendEquationSeparate(GLenum modeRGB,GLenum modeAlpha){this->_getTable()->glBlendEquationSeparate(modeRGB,modeAlpha);}
inline void glBlendEquationSeparateiARB(GLuint buf,GLenum modeRGB,GLenum modeAlpha){this->_getTable()->glBlendEquationSeparateiARB(buf,modeRGB,modeAlpha);}
inline void glBlendEquationSeparatei(GLuint buf,GLenum modeRGB,GLenum modeAlpha){this->_getTable()->glBlendEquationSeparatei(buf,modeRGB,modeAlpha);}
inline void glBlendEquationSeparateIndexedAMD(GLuint buf,GLenum modeRGB,GLenum modeAlpha){this->_getTable()->glBlendEquationSeparateIndexedAMD(buf,modeRGB,modeAlpha);}
inline void glBlendFunc(GLenum sfactor,GLenum dfactor){this->_getTable()->glBlendFunc(sfactor,dfactor);}
inline void glBlendFunciARB(GLuint buf,GLenum src,GLenum dst){this->_getTable()->glBlendFunciARB(buf,src,dst);}
inline void glBlendFunci(GLuint buf,GLenum src,GLenum dst){this->_getTable()->glBlendFunci(buf,src,dst);}
inline void glBlendFuncIndexedAMD(GLuint buf,GLenum src,GLenum dst){this->_getTable()->glBlendFuncIndexedAMD(buf,src,dst);}
inline void glBlendFuncSeparateEXT(GLenum sfactorRGB,GLenum dfactorRGB,GLenum sfactorAlpha,GLenum dfactorAlpha){this->_getTable()->glBlendFuncSeparateEXT(sfactorRGB,dfactorRGB,sfactorAlpha,dfactorAlpha);}
inline void glBlendFuncSeparate(GLenum sfactorRGB,GLenum dfactorRGB,GLenum sfactorAlpha,GLenum dfactorAlpha){this->_getTable()->glBlendFuncSeparate(sfactorRGB,dfactorRGB,sfactorAlpha,dfactorAlpha);}
inline void glBlendFuncSeparateiARB(GLuint buf,GLenum srcRGB,GLenum dstRGB,GLenum srcAlpha,GLenum dstAlpha){this->_getTable()->glBlendFuncSeparateiARB(buf,srcRGB,dstRGB,srcAlpha,dstAlpha);}
inline void glBlendFuncSeparatei(GLuint buf,GLenum srcRGB,GLenum dstRGB,GLenum srcAlpha,GLenum dstAlpha){this->_getTable()->glBlendFuncSeparatei(buf,srcRGB,dstRGB,srcAlpha,dstAlpha);}
inline void glBlendFuncSeparateIndexedAMD(GLuint buf,GLenum srcRGB,GLenum dstRGB,GLenum srcAlpha,GLenum dstAlpha){this->_getTable()->glBlendFuncSeparateIndexedAMD(buf,srcRGB,dstRGB,srcAlpha,dstAlpha);}
inline void glBlendFuncSeparateINGR(GLenum sfactorRGB,GLenum dfactorRGB,GLenum sfactorAlpha,GLenum dfactorAlpha){this->_getTable()->glBlendFuncSeparateINGR(sfactorRGB,dfactorRGB,sfactorAlpha,dfactorAlpha);}
inline void glBlendParameteriNV(GLenum pname,GLint value){this->_getTable()->glBlendParameteriNV(pname,value);}
inline void glBlitFramebufferEXT(GLint srcX0,GLint srcY0,GLint srcX1,GLint srcY1,GLint dstX0,GLint dstY0,GLint dstX1,GLint dstY1,GLbitfield mask,GLenum filter){this->_getTable()->glBlitFramebufferEXT(srcX0,srcY0,srcX1,srcY1,dstX0,dstY0,dstX1,dstY1,mask,filter);}
inline void glBlitFramebuffer(GLint srcX0,GLint srcY0,GLint srcX1,GLint srcY1,GLint dstX0,GLint dstY0,GLint dstX1,GLint dstY1,GLbitfield mask,GLenum filter){this->_getTable()->glBlitFramebuffer(srcX0,srcY0,srcX1,srcY1,dstX0,dstY0,dstX1,dstY1,mask,filter);}
inline void glBlitNamedFramebuffer(GLuint readFramebuffer,GLuint drawFramebuffer,GLint srcX0,GLint srcY0,GLint srcX1,GLint srcY1,GLint dstX0,GLint dstY0,GLint dstX1,GLint dstY1,GLbitfield mask,GLenum filter){this->_getTable()->glBlitNamedFramebuffer(readFramebuffer,drawFramebuffer,srcX0,srcY0,srcX1,srcY1,dstX0,dstY0,dstX1,dstY1,mask,filter);}
inline void glBufferAddressRangeNV(GLenum pname,GLuint index,GLuint64EXT address,GLsizeiptr length){this->_getTable()->glBufferAddressRangeNV(pname,index,address,length);}
inline void glBufferDataARB(GLenum target,GLsizeiptrARB size,const void* data,GLenum usage){this->_getTable()->glBufferDataARB(target,size,data,usage);}
inline void glBufferData(GLenum target,GLsizeiptr size,const void* data,GLenum usage){this->_getTable()->glBufferData(target,size,data,usage);}
inline void glBufferPageCommitmentARB(GLenum target,GLintptr offset,GLsizeiptr size,GLboolean commit){this->_getTable()->glBufferPageCommitmentARB(target,offset,size,commit);}
inline void glBufferParameteriAPPLE(GLenum target,GLenum pname,GLint param){this->_getTable()->glBufferParameteriAPPLE(target,pname,param);}
inline void glBufferStorage(GLenum target,GLsizeiptr size,const void* data,GLbitfield flags){this->_getTable()->glBufferStorage(target,size,data,flags);}
inline void glBufferSubDataARB(GLenum target,GLintptrARB offset,GLsizeiptrARB size,const void* data){this->_getTable()->glBufferSubDataARB(target,offset,size,data);}
inline void glBufferSubData(GLenum target,GLintptr offset,GLsizeiptr size,const void* data){this->_getTable()->glBufferSubData(target,offset,size,data);}
inline void glCallCommandListNV(GLuint list){this->_getTable()->glCallCommandListNV(list);}
inline void glCallList(GLuint list){this->_getTable()->glCallList(list);}
inline void glCallLists(GLsizei n,GLenum type,const GLvoid* lists){this->_getTable()->glCallLists(n,type,lists);}
inline void glClampColorARB(GLenum target,GLenum clamp){this->_getTable()->glClampColorARB(target,clamp);}
inline void glClampColor(GLenum target,GLenum clamp){this->_getTable()->glClampColor(target,clamp);}
inline void glClearAccum(GLfloat red,GLfloat green,GLfloat blue,GLfloat alpha){this->_getTable()->glClearAccum(red,green,blue,alpha);}
inline void glClearAccumxOES(GLfixed red,GLfixed green,GLfixed blue,GLfixed alpha){this->_getTable()->glClearAccumxOES(red,green,blue,alpha);}
inline void glClearBufferData(GLenum target,GLenum internalformat,GLenum format,GLenum type,const void* data){this->_getTable()->glClearBufferData(target,internalformat,format,type,data);}
inline void glClearBufferfi(GLenum buffer,GLint drawbuffer,GLfloat depth,GLint stencil){this->_getTable()->glClearBufferfi(buffer,drawbuffer,depth,stencil);}
inline void glClearBufferfv(GLenum buffer,GLint drawbuffer,const GLfloat* value){this->_getTable()->glClearBufferfv(buffer,drawbuffer,value);}
inline void glClearBufferiv(GLenum buffer,GLint drawbuffer,const GLint* value){this->_getTable()->glClearBufferiv(buffer,drawbuffer,value);}
inline void glClearBufferSubData(GLenum target,GLenum internalformat,GLintptr offset,GLsizeiptr size,GLenum format,GLenum type,const void* data){this->_getTable()->glClearBufferSubData(target,internalformat,offset,size,format,type,data);}
inline void glClearBufferuiv(GLenum buffer,GLint drawbuffer,const GLuint* value){this->_getTable()->glClearBufferuiv(buffer,drawbuffer,value);}
inline void glClearColor(GLclampf red,GLclampf green,GLclampf blue,GLclampf alpha){this->_getTable()->glClearColor(red,green,blue,alpha);}
inline void glClearColorIiEXT(GLint red,GLint green,GLint blue,GLint alpha){this->_getTable()->glClearColorIiEXT(red,green,blue,alpha);}
inline void glClearColorIuiEXT(GLuint red,GLuint green,GLuint blue,GLuint alpha){this->_getTable()->glClearColorIuiEXT(red,green,blue,alpha);}
inline void glClearColorxOES(GLfixed red,GLfixed green,GLfixed blue,GLfixed alpha){this->_getTable()->glClearColorxOES(red,green,blue,alpha);}
inline void glClearDepthdNV(GLdouble depth){this->_getTable()->glClearDepthdNV(depth);}
inline void glClearDepthf(GLfloat d){this->_getTable()->glClearDepthf(d);}
inline void glClearDepthfOES(GLclampf depth){this->_getTable()->glClearDepthfOES(depth);}
inline void glClearDepth(GLclampd depth){this->_getTable()->glClearDepth(depth);}
inline void glClearDepthxOES(GLfixed depth){this->_getTable()->glClearDepthxOES(depth);}
inline void glClear(GLbitfield mask){this->_getTable()->glClear(mask);}
inline void glClearIndex(GLfloat c){this->_getTable()->glClearIndex(c);}
inline void glClearNamedBufferDataEXT(GLuint buffer,GLenum internalformat,GLenum format,GLenum type,const void* data){this->_getTable()->glClearNamedBufferDataEXT(buffer,internalformat,format,type,data);}
inline void glClearNamedBufferData(GLuint buffer,GLenum internalformat,GLenum format,GLenum type,const void* data){this->_getTable()->glClearNamedBufferData(buffer,internalformat,format,type,data);}
inline void glClearNamedBufferSubDataEXT(GLuint buffer,GLenum internalformat,GLsizeiptr offset,GLsizeiptr size,GLenum format,GLenum type,const void* data){this->_getTable()->glClearNamedBufferSubDataEXT(buffer,internalformat,offset,size,format,type,data);}
inline void glClearNamedBufferSubData(GLuint buffer,GLenum internalformat,GLintptr offset,GLsizeiptr size,GLenum format,GLenum type,const void* data){this->_getTable()->glClearNamedBufferSubData(buffer,internalformat,offset,size,format,type,data);}
inline void glClearNamedFramebufferfi(GLuint framebuffer,GLenum buffer,GLint drawbuffer,GLfloat depth,GLint stencil){this->_getTable()->glClearNamedFramebufferfi(framebuffer,buffer,drawbuffer,depth,stencil);}
inline void glClearNamedFramebufferfv(GLuint framebuffer,GLenum buffer,GLint drawbuffer,const GLfloat* value){this->_getTable()->glClearNamedFramebufferfv(framebuffer,buffer,drawbuffer,value);}
inline void glClearNamedFramebufferiv(GLuint framebuffer,GLenum buffer,GLint drawbuffer,const GLint* value){this->_getTable()->glClearNamedFramebufferiv(framebuffer,buffer,drawbuffer,value);}
inline void glClearNamedFramebufferuiv(GLuint framebuffer,GLenum buffer,GLint drawbuffer,const GLuint* value){this->_getTable()->glClearNamedFramebufferuiv(framebuffer,buffer,drawbuffer,value);}
inline void glClearStencil(GLint s){this->_getTable()->glClearStencil(s);}
inline void glClearTexImage(GLuint texture,GLint level,GLenum format,GLenum type,const void* data){this->_getTable()->glClearTexImage(texture,level,format,type,data);}
inline void glClearTexSubImage(GLuint texture,GLint level,GLint xoffset,GLint yoffset,GLint zoffset,GLsizei width,GLsizei height,GLsizei depth,GLenum format,GLenum type,const void* data){this->_getTable()->glClearTexSubImage(texture,level,xoffset,yoffset,zoffset,width,height,depth,format,type,data);}
inline void glClientActiveTextureARB(GLenum texture){this->_getTable()->glClientActiveTextureARB(texture);}
inline void glClientActiveTexture(GLenum texture){this->_getTable()->glClientActiveTexture(texture);}
inline void glClientActiveVertexStreamATI(GLenum stream){this->_getTable()->glClientActiveVertexStreamATI(stream);}
inline void glClientAttribDefaultEXT(GLbitfield mask){this->_getTable()->glClientAttribDefaultEXT(mask);}
inline void glClipControl(GLenum origin,GLenum depth){this->_getTable()->glClipControl(origin,depth);}
inline void glClipPlanefOES(GLenum plane,const GLfloat* equation){this->_getTable()->glClipPlanefOES(plane,equation);}
inline void glClipPlane(GLenum plane,const GLdouble* equation){this->_getTable()->glClipPlane(plane,equation);}
inline void glClipPlanexOES(GLenum plane,const GLfixed* equation){this->_getTable()->glClipPlanexOES(plane,equation);}
inline void glColor3b(GLbyte red,GLbyte green,GLbyte blue){this->_getTable()->glColor3b(red,green,blue);}
inline void glColor3bv(const GLbyte* v){this->_getTable()->glColor3bv(v);}
inline void glColor3d(GLdouble red,GLdouble green,GLdouble blue){this->_getTable()->glColor3d(red,green,blue);}
inline void glColor3dv(const GLdouble* v){this->_getTable()->glColor3dv(v);}
inline void glColor3f(GLfloat red,GLfloat green,GLfloat blue){this->_getTable()->glColor3f(red,green,blue);}
inline void glColor3fv(const GLfloat* v){this->_getTable()->glColor3fv(v);}
inline void glColor3fVertex3fSUN(GLfloat r,GLfloat g,GLfloat b,GLfloat x,GLfloat y,GLfloat z){this->_getTable()->glColor3fVertex3fSUN(r,g,b,x,y,z);}
inline void glColor3fVertex3fvSUN(const GLfloat* c,const GLfloat* v){this->_getTable()->glColor3fVertex3fvSUN(c,v);}
inline void glColor3hNV(GLhalfNV red,GLhalfNV green,GLhalfNV blue){this->_getTable()->glColor3hNV(red,green,blue);}
inline void glColor3hvNV(const GLhalfNV* v){this->_getTable()->glColor3hvNV(v);}
inline void glColor3i(GLint red,GLint green,GLint blue){this->_getTable()->glColor3i(red,green,blue);}
inline void glColor3iv(const GLint* v){this->_getTable()->glColor3iv(v);}
inline void glColor3s(GLshort red,GLshort green,GLshort blue){this->_getTable()->glColor3s(red,green,blue);}
inline void glColor3sv(const GLshort* v){this->_getTable()->glColor3sv(v);}
inline void glColor3ub(GLubyte red,GLubyte green,GLubyte blue){this->_getTable()->glColor3ub(red,green,blue);}
inline void glColor3ubv(const GLubyte* v){this->_getTable()->glColor3ubv(v);}
inline void glColor3ui(GLuint red,GLuint green,GLuint blue){this->_getTable()->glColor3ui(red,green,blue);}
inline void glColor3uiv(const GLuint* v){this->_getTable()->glColor3uiv(v);}
inline void glColor3us(GLushort red,GLushort green,GLushort blue){this->_getTable()->glColor3us(red,green,blue);}
inline void glColor3usv(const GLushort* v){this->_getTable()->glColor3usv(v);}
inline void glColor3xOES(GLfixed red,GLfixed green,GLfixed blue){this->_getTable()->glColor3xOES(red,green,blue);}
inline void glColor3xvOES(const GLfixed* components){this->_getTable()->glColor3xvOES(components);}
inline void glColor4b(GLbyte red,GLbyte green,GLbyte blue,GLbyte alpha){this->_getTable()->glColor4b(red,green,blue,alpha);}
inline void glColor4bv(const GLbyte* v){this->_getTable()->glColor4bv(v);}
inline void glColor4d(GLdouble red,GLdouble green,GLdouble blue,GLdouble alpha){this->_getTable()->glColor4d(red,green,blue,alpha);}
inline void glColor4dv(const GLdouble* v){this->_getTable()->glColor4dv(v);}
inline void glColor4f(GLfloat red,GLfloat green,GLfloat blue,GLfloat alpha){this->_getTable()->glColor4f(red,green,blue,alpha);}
inline void glColor4fNormal3fVertex3fSUN(GLfloat r,GLfloat g,GLfloat b,GLfloat a,GLfloat nx,GLfloat ny,GLfloat nz,GLfloat x,GLfloat y,GLfloat z){this->_getTable()->glColor4fNormal3fVertex3fSUN(r,g,b,a,nx,ny,nz,x,y,z);}
inline void glColor4fNormal3fVertex3fvSUN(const GLfloat* c,const GLfloat* n,const GLfloat* v){this->_getTable()->glColor4fNormal3fVertex3fvSUN(c,n,v);}
inline void glColor4fv(const GLfloat* v){this->_getTable()->glColor4fv(v);}
inline void glColor4hNV(GLhalfNV red,GLhalfNV green,GLhalfNV blue,GLhalfNV alpha){this->_getTable()->glColor4hNV(red,green,blue,alpha);}
inline void glColor4hvNV(const GLhalfNV* v){this->_getTable()->glColor4hvNV(v);}
inline void glColor4i(GLint red,GLint green,GLint blue,GLint alpha){this->_getTable()->glColor4i(red,green,blue,alpha);}
inline void glColor4iv(const GLint* v){this->_getTable()->glColor4iv(v);}
inline void glColor4s(GLshort red,GLshort green,GLshort blue,GLshort alpha){this->_getTable()->glColor4s(red,green,blue,alpha);}
inline void glColor4sv(const GLshort* v){this->_getTable()->glColor4sv(v);}
inline void glColor4ub(GLubyte red,GLubyte green,GLubyte blue,GLubyte alpha){this->_getTable()->glColor4ub(red,green,blue,alpha);}
inline void glColor4ubv(const GLubyte* v){this->_getTable()->glColor4ubv(v);}
inline void glColor4ubVertex2fSUN(GLubyte r,GLubyte g,GLubyte b,GLubyte a,GLfloat x,GLfloat y){this->_getTable()->glColor4ubVertex2fSUN(r,g,b,a,x,y);}
inline void glColor4ubVertex2fvSUN(const GLubyte* c,const GLfloat* v){this->_getTable()->glColor4ubVertex2fvSUN(c,v);}
inline void glColor4ubVertex3fSUN(GLubyte r,GLubyte g,GLubyte b,GLubyte a,GLfloat x,GLfloat y,GLfloat z){this->_getTable()->glColor4ubVertex3fSUN(r,g,b,a,x,y,z);}
inline void glColor4ubVertex3fvSUN(const GLubyte* c,const GLfloat* v){this->_getTable()->glColor4ubVertex3fvSUN(c,v);}
inline void glColor4ui(GLuint red,GLuint green,GLuint blue,GLuint alpha){this->_getTable()->glColor4ui(red,green,blue,alpha);}
inline void glColor4uiv(const GLuint* v){this->_getTable()->glColor4uiv(v);}
inline void glColor4us(GLushort red,GLushort green,GLushort blue,GLushort alpha){this->_getTable()->glColor4us(red,green,blue,alpha);}
inline void glColor4usv(const GLushort* v){this->_getTable()->glColor4usv(v);}
inline void glColor4xOES(GLfixed red,GLfixed green,GLfixed blue,GLfixed alpha){this->_getTable()->glColor4xOES(red,green,blue,alpha);}
inline void glColor4xvOES(const GLfixed* components){this->_getTable()->glColor4xvOES(components);}
inline void glColorFormatNV(GLint size,GLenum type,GLsizei stride){this->_getTable()->glColorFormatNV(size,type,stride);}
inline void glColorFragmentOp1ATI(GLenum op,GLuint dst,GLuint dstMask,GLuint dstMod,GLuint arg1,GLuint arg1Rep,GLuint arg1Mod){this->_getTable()->glColorFragmentOp1ATI(op,dst,dstMask,dstMod,arg1,arg1Rep,arg1Mod);}
inline void glColorFragmentOp2ATI(GLenum op,GLuint dst,GLuint dstMask,GLuint dstMod,GLuint arg1,GLuint arg1Rep,GLuint arg1Mod,GLuint arg2,GLuint arg2Rep,GLuint arg2Mod){this->_getTable()->glColorFragmentOp2ATI(op,dst,dstMask,dstMod,arg1,arg1Rep,arg1Mod,arg2,arg2Rep,arg2Mod);}
inline void glColorFragmentOp3ATI(GLenum op,GLuint dst,GLuint dstMask,GLuint dstMod,GLuint arg1,GLuint arg1Rep,GLuint arg1Mod,GLuint arg2,GLuint arg2Rep,GLuint arg2Mod,GLuint arg3,GLuint arg3Rep,GLuint arg3Mod){this->_getTable()->glColorFragmentOp3ATI(op,dst,dstMask,dstMod,arg1,arg1Rep,arg1Mod,arg2,arg2Rep,arg2Mod,arg3,arg3Rep,arg3Mod);}
inline void glColorMask(GLboolean red,GLboolean green,GLboolean blue,GLboolean alpha){this->_getTable()->glColorMask(red,green,blue,alpha);}
inline void glColorMaski(GLuint index,GLboolean r,GLboolean g,GLboolean b,GLboolean a){this->_getTable()->glColorMaski(index,r,g,b,a);}
inline void glColorMaskIndexedEXT(GLuint index,GLboolean r,GLboolean g,GLboolean b,GLboolean a){this->_getTable()->glColorMaskIndexedEXT(index,r,g,b,a);}
inline void glColorMaterial(GLenum face,GLenum mode){this->_getTable()->glColorMaterial(face,mode);}
inline void glColorP3ui(GLenum type,GLuint color){this->_getTable()->glColorP3ui(type,color);}
inline void glColorP3uiv(GLenum type,const GLuint* color){this->_getTable()->glColorP3uiv(type,color);}
inline void glColorP4ui(GLenum type,GLuint color){this->_getTable()->glColorP4ui(type,color);}
inline void glColorP4uiv(GLenum type,const GLuint* color){this->_getTable()->glColorP4uiv(type,color);}
inline void glColorPointerEXT(GLint size,GLenum type,GLsizei stride,GLsizei count,const void* pointer){this->_getTable()->glColorPointerEXT(size,type,stride,count,pointer);}
inline void glColorPointer(GLint size,GLenum type,GLsizei stride,const GLvoid* ptr){this->_getTable()->glColorPointer(size,type,stride,ptr);}
inline void glColorPointerListIBM(GLint size,GLenum type,GLint stride,const void** pointer,GLint ptrstride){this->_getTable()->glColorPointerListIBM(size,type,stride,pointer,ptrstride);}
inline void glColorPointervINTEL(GLint size,GLenum type,const void** pointer){this->_getTable()->glColorPointervINTEL(size,type,pointer);}
inline void glColorSubTableEXT(GLenum target,GLsizei start,GLsizei count,GLenum format,GLenum type,const void* data){this->_getTable()->glColorSubTableEXT(target,start,count,format,type,data);}
inline void glColorSubTable(GLenum target,GLsizei start,GLsizei count,GLenum format,GLenum type,const GLvoid* data){this->_getTable()->glColorSubTable(target,start,count,format,type,data);}
inline void glColorTableEXT(GLenum target,GLenum internalFormat,GLsizei width,GLenum format,GLenum type,const void* table){this->_getTable()->glColorTableEXT(target,internalFormat,width,format,type,table);}
inline void glColorTable(GLenum target,GLenum internalformat,GLsizei width,GLenum format,GLenum type,const GLvoid* table){this->_getTable()->glColorTable(target,internalformat,width,format,type,table);}
inline void glColorTableParameterfv(GLenum target,GLenum pname,const GLfloat* params){this->_getTable()->glColorTableParameterfv(target,pname,params);}
inline void glColorTableParameterfvSGI(GLenum target,GLenum pname,const GLfloat* params){this->_getTable()->glColorTableParameterfvSGI(target,pname,params);}
inline void glColorTableParameteriv(GLenum target,GLenum pname,const GLint* params){this->_getTable()->glColorTableParameteriv(target,pname,params);}
inline void glColorTableParameterivSGI(GLenum target,GLenum pname,const GLint* params){this->_getTable()->glColorTableParameterivSGI(target,pname,params);}
inline void glColorTableSGI(GLenum target,GLenum internalformat,GLsizei width,GLenum format,GLenum type,const void* table){this->_getTable()->glColorTableSGI(target,internalformat,width,format,type,table);}
inline void glCombinerInputNV(GLenum stage,GLenum portion,GLenum variable,GLenum input,GLenum mapping,GLenum componentUsage){this->_getTable()->glCombinerInputNV(stage,portion,variable,input,mapping,componentUsage);}
inline void glCombinerOutputNV(GLenum stage,GLenum portion,GLenum abOutput,GLenum cdOutput,GLenum sumOutput,GLenum scale,GLenum bias,GLboolean abDotProduct,GLboolean cdDotProduct,GLboolean muxSum){this->_getTable()->glCombinerOutputNV(stage,portion,abOutput,cdOutput,sumOutput,scale,bias,abDotProduct,cdDotProduct,muxSum);}
inline void glCombinerParameterfNV(GLenum pname,GLfloat param){this->_getTable()->glCombinerParameterfNV(pname,param);}
inline void glCombinerParameterfvNV(GLenum pname,const GLfloat* params){this->_getTable()->glCombinerParameterfvNV(pname,params);}
inline void glCombinerParameteriNV(GLenum pname,GLint param){this->_getTable()->glCombinerParameteriNV(pname,param);}
inline void glCombinerParameterivNV(GLenum pname,const GLint* params){this->_getTable()->glCombinerParameterivNV(pname,params);}
inline void glCombinerStageParameterfvNV(GLenum stage,GLenum pname,const GLfloat* params){this->_getTable()->glCombinerStageParameterfvNV(stage,pname,params);}
inline void glCommandListSegmentsNV(GLuint list,GLuint segments){this->_getTable()->glCommandListSegmentsNV(list,segments);}
inline void glCompileCommandListNV(GLuint list){this->_getTable()->glCompileCommandListNV(list);}
inline void glCompileShaderARB(GLhandleARB shaderObj){this->_getTable()->glCompileShaderARB(shaderObj);}
inline void glCompileShader(GLuint shader){this->_getTable()->glCompileShader(shader);}
inline void glCompileShaderIncludeARB(GLuint shader,GLsizei count,const GLchar*const* path,const GLint* length){this->_getTable()->glCompileShaderIncludeARB(shader,count,path,length);}
inline void glCompressedMultiTexImage1DEXT(GLenum texunit,GLenum target,GLint level,GLenum internalformat,GLsizei width,GLint border,GLsizei imageSize,const void* bits){this->_getTable()->glCompressedMultiTexImage1DEXT(texunit,target,level,internalformat,width,border,imageSize,bits);}
inline void glCompressedMultiTexImage2DEXT(GLenum texunit,GLenum target,GLint level,GLenum internalformat,GLsizei width,GLsizei height,GLint border,GLsizei imageSize,const void* bits){this->_getTable()->glCompressedMultiTexImage2DEXT(texunit,target,level,internalformat,width,height,border,imageSize,bits);}
inline void glCompressedMultiTexImage3DEXT(GLenum texunit,GLenum target,GLint level,GLenum internalformat,GLsizei width,GLsizei height,GLsizei depth,GLint border,GLsizei imageSize,const void* bits){this->_getTable()->glCompressedMultiTexImage3DEXT(texunit,target,level,internalformat,width,height,depth,border,imageSize,bits);}
inline void glCompressedMultiTexSubImage1DEXT(GLenum texunit,GLenum target,GLint level,GLint xoffset,GLsizei width,GLenum format,GLsizei imageSize,const void* bits){this->_getTable()->glCompressedMultiTexSubImage1DEXT(texunit,target,level,xoffset,width,format,imageSize,bits);}
inline void glCompressedMultiTexSubImage2DEXT(GLenum texunit,GLenum target,GLint level,GLint xoffset,GLint yoffset,GLsizei width,GLsizei height,GLenum format,GLsizei imageSize,const void* bits){this->_getTable()->glCompressedMultiTexSubImage2DEXT(texunit,target,level,xoffset,yoffset,width,height,format,imageSize,bits);}
inline void glCompressedMultiTexSubImage3DEXT(GLenum texunit,GLenum target,GLint level,GLint xoffset,GLint yoffset,GLint zoffset,GLsizei width,GLsizei height,GLsizei depth,GLenum format,GLsizei imageSize,const void* bits){this->_getTable()->glCompressedMultiTexSubImage3DEXT(texunit,target,level,xoffset,yoffset,zoffset,width,height,depth,format,imageSize,bits);}
inline void glCompressedTexImage1DARB(GLenum target,GLint level,GLenum internalformat,GLsizei width,GLint border,GLsizei imageSize,const void* data){this->_getTable()->glCompressedTexImage1DARB(target,level,internalformat,width,border,imageSize,data);}
inline void glCompressedTexImage1D(GLenum target,GLint level,GLenum internalformat,GLsizei width,GLint border,GLsizei imageSize,const GLvoid* data){this->_getTable()->glCompressedTexImage1D(target,level,internalformat,width,border,imageSize,data);}
inline void glCompressedTexImage2DARB(GLenum target,GLint level,GLenum internalformat,GLsizei width,GLsizei height,GLint border,GLsizei imageSize,const void* data){this->_getTable()->glCompressedTexImage2DARB(target,level,internalformat,width,height,border,imageSize,data);}
inline void glCompressedTexImage2D(GLenum target,GLint level,GLenum internalformat,GLsizei width,GLsizei height,GLint border,GLsizei imageSize,const GLvoid* data){this->_getTable()->glCompressedTexImage2D(target,level,internalformat,width,height,border,imageSize,data);}
inline void glCompressedTexImage3DARB(GLenum target,GLint level,GLenum internalformat,GLsizei width,GLsizei height,GLsizei depth,GLint border,GLsizei imageSize,const void* data){this->_getTable()->glCompressedTexImage3DARB(target,level,internalformat,width,height,depth,border,imageSize,data);}
inline void glCompressedTexImage3D(GLenum target,GLint level,GLenum internalformat,GLsizei width,GLsizei height,GLsizei depth,GLint border,GLsizei imageSize,const GLvoid* data){this->_getTable()->glCompressedTexImage3D(target,level,internalformat,width,height,depth,border,imageSize,data);}
inline void glCompressedTexSubImage1DARB(GLenum target,GLint level,GLint xoffset,GLsizei width,GLenum format,GLsizei imageSize,const void* data){this->_getTable()->glCompressedTexSubImage1DARB(target,level,xoffset,width,format,imageSize,data);}
inline void glCompressedTexSubImage1D(GLenum target,GLint level,GLint xoffset,GLsizei width,GLenum format,GLsizei imageSize,const GLvoid* data){this->_getTable()->glCompressedTexSubImage1D(target,level,xoffset,width,format,imageSize,data);}
inline void glCompressedTexSubImage2DARB(GLenum target,GLint level,GLint xoffset,GLint yoffset,GLsizei width,GLsizei height,GLenum format,GLsizei imageSize,const void* data){this->_getTable()->glCompressedTexSubImage2DARB(target,level,xoffset,yoffset,width,height,format,imageSize,data);}
inline void glCompressedTexSubImage2D(GLenum target,GLint level,GLint xoffset,GLint yoffset,GLsizei width,GLsizei height,GLenum format,GLsizei imageSize,const GLvoid* data){this->_getTable()->glCompressedTexSubImage2D(target,level,xoffset,yoffset,width,height,format,imageSize,data);}
inline void glCompressedTexSubImage3DARB(GLenum target,GLint level,GLint xoffset,GLint yoffset,GLint zoffset,GLsizei width,GLsizei height,GLsizei depth,GLenum format,GLsizei imageSize,const void* data){this->_getTable()->glCompressedTexSubImage3DARB(target,level,xoffset,yoffset,zoffset,width,height,depth,format,imageSize,data);}
inline void glCompressedTexSubImage3D(GLenum target,GLint level,GLint xoffset,GLint yoffset,GLint zoffset,GLsizei width,GLsizei height,GLsizei depth,GLenum format,GLsizei imageSize,const GLvoid* data){this->_getTable()->glCompressedTexSubImage3D(target,level,xoffset,yoffset,zoffset,width,height,depth,format,imageSize,data);}
inline void glCompressedTextureImage1DEXT(GLuint texture,GLenum target,GLint level,GLenum internalformat,GLsizei width,GLint border,GLsizei imageSize,const void* bits){this->_getTable()->glCompressedTextureImage1DEXT(texture,target,level,internalformat,width,border,imageSize,bits);}
inline void glCompressedTextureImage2DEXT(GLuint texture,GLenum target,GLint level,GLenum internalformat,GLsizei width,GLsizei height,GLint border,GLsizei imageSize,const void* bits){this->_getTable()->glCompressedTextureImage2DEXT(texture,target,level,internalformat,width,height,border,imageSize,bits);}
inline void glCompressedTextureImage3DEXT(GLuint texture,GLenum target,GLint level,GLenum internalformat,GLsizei width,GLsizei height,GLsizei depth,GLint border,GLsizei imageSize,const void* bits){this->_getTable()->glCompressedTextureImage3DEXT(texture,target,level,internalformat,width,height,depth,border,imageSize,bits);}
inline void glCompressedTextureSubImage1DEXT(GLuint texture,GLenum target,GLint level,GLint xoffset,GLsizei width,GLenum format,GLsizei imageSize,const void* bits){this->_getTable()->glCompressedTextureSubImage1DEXT(texture,target,level,xoffset,width,format,imageSize,bits);}
inline void glCompressedTextureSubImage1D(GLuint texture,GLint level,GLint xoffset,GLsizei width,GLenum format,GLsizei imageSize,const void* data){this->_getTable()->glCompressedTextureSubImage1D(texture,level,xoffset,width,format,imageSize,data);}
inline void glCompressedTextureSubImage2DEXT(GLuint texture,GLenum target,GLint level,GLint xoffset,GLint yoffset,GLsizei width,GLsizei height,GLenum format,GLsizei imageSize,const void* bits){this->_getTable()->glCompressedTextureSubImage2DEXT(texture,target,level,xoffset,yoffset,width,height,format,imageSize,bits);}
inline void glCompressedTextureSubImage2D(GLuint texture,GLint level,GLint xoffset,GLint yoffset,GLsizei width,GLsizei height,GLenum format,GLsizei imageSize,const void* data){this->_getTable()->glCompressedTextureSubImage2D(texture,level,xoffset,yoffset,width,height,format,imageSize,data);}
inline void glCompressedTextureSubImage3DEXT(GLuint texture,GLenum target,GLint level,GLint xoffset,GLint yoffset,GLint zoffset,GLsizei width,GLsizei height,GLsizei depth,GLenum format,GLsizei imageSize,const void* bits){this->_getTable()->glCompressedTextureSubImage3DEXT(texture,target,level,xoffset,yoffset,zoffset,width,height,depth,format,imageSize,bits);}
inline void glCompressedTextureSubImage3D(GLuint texture,GLint level,GLint xoffset,GLint yoffset,GLint zoffset,GLsizei width,GLsizei height,GLsizei depth,GLenum format,GLsizei imageSize,const void* data){this->_getTable()->glCompressedTextureSubImage3D(texture,level,xoffset,yoffset,zoffset,width,height,depth,format,imageSize,data);}
inline void glConservativeRasterParameterfNV(GLenum pname,GLfloat value){this->_getTable()->glConservativeRasterParameterfNV(pname,value);}
inline void glConvolutionFilter1DEXT(GLenum target,GLenum internalformat,GLsizei width,GLenum format,GLenum type,const void* image){this->_getTable()->glConvolutionFilter1DEXT(target,internalformat,width,format,type,image);}
inline void glConvolutionFilter1D(GLenum target,GLenum internalformat,GLsizei width,GLenum format,GLenum type,const GLvoid* image){this->_getTable()->glConvolutionFilter1D(target,internalformat,width,format,type,image);}
inline void glConvolutionFilter2DEXT(GLenum target,GLenum internalformat,GLsizei width,GLsizei height,GLenum format,GLenum type,const void* image){this->_getTable()->glConvolutionFilter2DEXT(target,internalformat,width,height,format,type,image);}
inline void glConvolutionFilter2D(GLenum target,GLenum internalformat,GLsizei width,GLsizei height,GLenum format,GLenum type,const GLvoid* image){this->_getTable()->glConvolutionFilter2D(target,internalformat,width,height,format,type,image);}
inline void glConvolutionParameterfEXT(GLenum target,GLenum pname,GLfloat params){this->_getTable()->glConvolutionParameterfEXT(target,pname,params);}
inline void glConvolutionParameterf(GLenum target,GLenum pname,GLfloat params){this->_getTable()->glConvolutionParameterf(target,pname,params);}
inline void glConvolutionParameterfvEXT(GLenum target,GLenum pname,const GLfloat* params){this->_getTable()->glConvolutionParameterfvEXT(target,pname,params);}
inline void glConvolutionParameterfv(GLenum target,GLenum pname,const GLfloat* params){this->_getTable()->glConvolutionParameterfv(target,pname,params);}
inline void glConvolutionParameteriEXT(GLenum target,GLenum pname,GLint params){this->_getTable()->glConvolutionParameteriEXT(target,pname,params);}
inline void glConvolutionParameteri(GLenum target,GLenum pname,GLint params){this->_getTable()->glConvolutionParameteri(target,pname,params);}
inline void glConvolutionParameterivEXT(GLenum target,GLenum pname,const GLint* params){this->_getTable()->glConvolutionParameterivEXT(target,pname,params);}
inline void glConvolutionParameteriv(GLenum target,GLenum pname,const GLint* params){this->_getTable()->glConvolutionParameteriv(target,pname,params);}
inline void glConvolutionParameterxOES(GLenum target,GLenum pname,GLfixed param){this->_getTable()->glConvolutionParameterxOES(target,pname,param);}
inline void glConvolutionParameterxvOES(GLenum target,GLenum pname,const GLfixed* params){this->_getTable()->glConvolutionParameterxvOES(target,pname,params);}
inline void glCopyBufferSubData(GLenum readTarget,GLenum writeTarget,GLintptr readOffset,GLintptr writeOffset,GLsizeiptr size){this->_getTable()->glCopyBufferSubData(readTarget,writeTarget,readOffset,writeOffset,size);}
inline void glCopyColorSubTableEXT(GLenum target,GLsizei start,GLint x,GLint y,GLsizei width){this->_getTable()->glCopyColorSubTableEXT(target,start,x,y,width);}
inline void glCopyColorSubTable(GLenum target,GLsizei start,GLint x,GLint y,GLsizei width){this->_getTable()->glCopyColorSubTable(target,start,x,y,width);}
inline void glCopyColorTable(GLenum target,GLenum internalformat,GLint x,GLint y,GLsizei width){this->_getTable()->glCopyColorTable(target,internalformat,x,y,width);}
inline void glCopyColorTableSGI(GLenum target,GLenum internalformat,GLint x,GLint y,GLsizei width){this->_getTable()->glCopyColorTableSGI(target,internalformat,x,y,width);}
inline void glCopyConvolutionFilter1DEXT(GLenum target,GLenum internalformat,GLint x,GLint y,GLsizei width){this->_getTable()->glCopyConvolutionFilter1DEXT(target,internalformat,x,y,width);}
inline void glCopyConvolutionFilter1D(GLenum target,GLenum internalformat,GLint x,GLint y,GLsizei width){this->_getTable()->glCopyConvolutionFilter1D(target,internalformat,x,y,width);}
inline void glCopyConvolutionFilter2DEXT(GLenum target,GLenum internalformat,GLint x,GLint y,GLsizei width,GLsizei height){this->_getTable()->glCopyConvolutionFilter2DEXT(target,internalformat,x,y,width,height);}
inline void glCopyConvolutionFilter2D(GLenum target,GLenum internalformat,GLint x,GLint y,GLsizei width,GLsizei height){this->_getTable()->glCopyConvolutionFilter2D(target,internalformat,x,y,width,height);}
inline void glCopyImageSubData(GLuint srcName,GLenum srcTarget,GLint srcLevel,GLint srcX,GLint srcY,GLint srcZ,GLuint dstName,GLenum dstTarget,GLint dstLevel,GLint dstX,GLint dstY,GLint dstZ,GLsizei srcWidth,GLsizei srcHeight,GLsizei srcDepth){this->_getTable()->glCopyImageSubData(srcName,srcTarget,srcLevel,srcX,srcY,srcZ,dstName,dstTarget,dstLevel,dstX,dstY,dstZ,srcWidth,srcHeight,srcDepth);}
inline void glCopyImageSubDataNV(GLuint srcName,GLenum srcTarget,GLint srcLevel,GLint srcX,GLint srcY,GLint srcZ,GLuint dstName,GLenum dstTarget,GLint dstLevel,GLint dstX,GLint dstY,GLint dstZ,GLsizei width,GLsizei height,GLsizei depth){this->_getTable()->glCopyImageSubDataNV(srcName,srcTarget,srcLevel,srcX,srcY,srcZ,dstName,dstTarget,dstLevel,dstX,dstY,dstZ,width,height,depth);}
inline void glCopyMultiTexImage1DEXT(GLenum texunit,GLenum target,GLint level,GLenum internalformat,GLint x,GLint y,GLsizei width,GLint border){this->_getTable()->glCopyMultiTexImage1DEXT(texunit,target,level,internalformat,x,y,width,border);}
inline void glCopyMultiTexImage2DEXT(GLenum texunit,GLenum target,GLint level,GLenum internalformat,GLint x,GLint y,GLsizei width,GLsizei height,GLint border){this->_getTable()->glCopyMultiTexImage2DEXT(texunit,target,level,internalformat,x,y,width,height,border);}
inline void glCopyMultiTexSubImage1DEXT(GLenum texunit,GLenum target,GLint level,GLint xoffset,GLint x,GLint y,GLsizei width){this->_getTable()->glCopyMultiTexSubImage1DEXT(texunit,target,level,xoffset,x,y,width);}
inline void glCopyMultiTexSubImage2DEXT(GLenum texunit,GLenum target,GLint level,GLint xoffset,GLint yoffset,GLint x,GLint y,GLsizei width,GLsizei height){this->_getTable()->glCopyMultiTexSubImage2DEXT(texunit,target,level,xoffset,yoffset,x,y,width,height);}
inline void glCopyMultiTexSubImage3DEXT(GLenum texunit,GLenum target,GLint level,GLint xoffset,GLint yoffset,GLint zoffset,GLint x,GLint y,GLsizei width,GLsizei height){this->_getTable()->glCopyMultiTexSubImage3DEXT(texunit,target,level,xoffset,yoffset,zoffset,x,y,width,height);}
inline void glCopyNamedBufferSubData(GLuint readBuffer,GLuint writeBuffer,GLintptr readOffset,GLintptr writeOffset,GLsizeiptr size){this->_getTable()->glCopyNamedBufferSubData(readBuffer,writeBuffer,readOffset,writeOffset,size);}
inline void glCopyPathNV(GLuint resultPath,GLuint srcPath){this->_getTable()->glCopyPathNV(resultPath,srcPath);}
inline void glCopyPixels(GLint x,GLint y,GLsizei width,GLsizei height,GLenum type){this->_getTable()->glCopyPixels(x,y,width,height,type);}
inline void glCopyTexImage1DEXT(GLenum target,GLint level,GLenum internalformat,GLint x,GLint y,GLsizei width,GLint border){this->_getTable()->glCopyTexImage1DEXT(target,level,internalformat,x,y,width,border);}
inline void glCopyTexImage1D(GLenum target,GLint level,GLenum internalformat,GLint x,GLint y,GLsizei width,GLint border){this->_getTable()->glCopyTexImage1D(target,level,internalformat,x,y,width,border);}
inline void glCopyTexImage2DEXT(GLenum target,GLint level,GLenum internalformat,GLint x,GLint y,GLsizei width,GLsizei height,GLint border){this->_getTable()->glCopyTexImage2DEXT(target,level,internalformat,x,y,width,height,border);}
inline void glCopyTexImage2D(GLenum target,GLint level,GLenum internalformat,GLint x,GLint y,GLsizei width,GLsizei height,GLint border){this->_getTable()->glCopyTexImage2D(target,level,internalformat,x,y,width,height,border);}
inline void glCopyTexSubImage1DEXT(GLenum target,GLint level,GLint xoffset,GLint x,GLint y,GLsizei width){this->_getTable()->glCopyTexSubImage1DEXT(target,level,xoffset,x,y,width);}
inline void glCopyTexSubImage1D(GLenum target,GLint level,GLint xoffset,GLint x,GLint y,GLsizei width){this->_getTable()->glCopyTexSubImage1D(target,level,xoffset,x,y,width);}
inline void glCopyTexSubImage2DEXT(GLenum target,GLint level,GLint xoffset,GLint yoffset,GLint x,GLint y,GLsizei width,GLsizei height){this->_getTable()->glCopyTexSubImage2DEXT(target,level,xoffset,yoffset,x,y,width,height);}
inline void glCopyTexSubImage2D(GLenum target,GLint level,GLint xoffset,GLint yoffset,GLint x,GLint y,GLsizei width,GLsizei height){this->_getTable()->glCopyTexSubImage2D(target,level,xoffset,yoffset,x,y,width,height);}
inline void glCopyTexSubImage3DEXT(GLenum target,GLint level,GLint xoffset,GLint yoffset,GLint zoffset,GLint x,GLint y,GLsizei width,GLsizei height){this->_getTable()->glCopyTexSubImage3DEXT(target,level,xoffset,yoffset,zoffset,x,y,width,height);}
inline void glCopyTexSubImage3D(GLenum target,GLint level,GLint xoffset,GLint yoffset,GLint zoffset,GLint x,GLint y,GLsizei width,GLsizei height){this->_getTable()->glCopyTexSubImage3D(target,level,xoffset,yoffset,zoffset,x,y,width,height);}
inline void glCopyTextureImage1DEXT(GLuint texture,GLenum target,GLint level,GLenum internalformat,GLint x,GLint y,GLsizei width,GLint border){this->_getTable()->glCopyTextureImage1DEXT(texture,target,level,internalformat,x,y,width,border);}
inline void glCopyTextureImage2DEXT(GLuint texture,GLenum target,GLint level,GLenum internalformat,GLint x,GLint y,GLsizei width,GLsizei height,GLint border){this->_getTable()->glCopyTextureImage2DEXT(texture,target,level,internalformat,x,y,width,height,border);}
inline void glCopyTextureSubImage1DEXT(GLuint texture,GLenum target,GLint level,GLint xoffset,GLint x,GLint y,GLsizei width){this->_getTable()->glCopyTextureSubImage1DEXT(texture,target,level,xoffset,x,y,width);}
inline void glCopyTextureSubImage1D(GLuint texture,GLint level,GLint xoffset,GLint x,GLint y,GLsizei width){this->_getTable()->glCopyTextureSubImage1D(texture,level,xoffset,x,y,width);}
inline void glCopyTextureSubImage2DEXT(GLuint texture,GLenum target,GLint level,GLint xoffset,GLint yoffset,GLint x,GLint y,GLsizei width,GLsizei height){this->_getTable()->glCopyTextureSubImage2DEXT(texture,target,level,xoffset,yoffset,x,y,width,height);}
inline void glCopyTextureSubImage2D(GLuint texture,GLint level,GLint xoffset,GLint yoffset,GLint x,GLint y,GLsizei width,GLsizei height){this->_getTable()->glCopyTextureSubImage2D(texture,level,xoffset,yoffset,x,y,width,height);}
inline void glCopyTextureSubImage3DEXT(GLuint texture,GLenum target,GLint level,GLint xoffset,GLint yoffset,GLint zoffset,GLint x,GLint y,GLsizei width,GLsizei height){this->_getTable()->glCopyTextureSubImage3DEXT(texture,target,level,xoffset,yoffset,zoffset,x,y,width,height);}
inline void glCopyTextureSubImage3D(GLuint texture,GLint level,GLint xoffset,GLint yoffset,GLint zoffset,GLint x,GLint y,GLsizei width,GLsizei height){this->_getTable()->glCopyTextureSubImage3D(texture,level,xoffset,yoffset,zoffset,x,y,width,height);}
inline void glCoverageModulationNV(GLenum components){this->_getTable()->glCoverageModulationNV(components);}
inline void glCoverageModulationTableNV(GLsizei n,const GLfloat* v){this->_getTable()->glCoverageModulationTableNV(n,v);}
inline void glCoverFillPathInstancedNV(GLsizei numPaths,GLenum pathNameType,const void* paths,GLuint pathBase,GLenum coverMode,GLenum transformType,const GLfloat* transformValues){this->_getTable()->glCoverFillPathInstancedNV(numPaths,pathNameType,paths,pathBase,coverMode,transformType,transformValues);}
inline void glCoverFillPathNV(GLuint path,GLenum coverMode){this->_getTable()->glCoverFillPathNV(path,coverMode);}
inline void glCoverStrokePathInstancedNV(GLsizei numPaths,GLenum pathNameType,const void* paths,GLuint pathBase,GLenum coverMode,GLenum transformType,const GLfloat* transformValues){this->_getTable()->glCoverStrokePathInstancedNV(numPaths,pathNameType,paths,pathBase,coverMode,transformType,transformValues);}
inline void glCoverStrokePathNV(GLuint path,GLenum coverMode){this->_getTable()->glCoverStrokePathNV(path,coverMode);}
inline void glCreateBuffers(GLsizei n,GLuint* buffers){this->_getTable()->glCreateBuffers(n,buffers);}
inline void glCreateCommandListsNV(GLsizei n,GLuint* lists){this->_getTable()->glCreateCommandListsNV(n,lists);}
inline void glCreateFramebuffers(GLsizei n,GLuint* framebuffers){this->_getTable()->glCreateFramebuffers(n,framebuffers);}
inline void glCreatePerfQueryINTEL(GLuint queryId,GLuint* queryHandle){this->_getTable()->glCreatePerfQueryINTEL(queryId,queryHandle);}
inline void glCreateProgramPipelines(GLsizei n,GLuint* pipelines){this->_getTable()->glCreateProgramPipelines(n,pipelines);}
inline void glCreateQueries(GLenum target,GLsizei n,GLuint* ids){this->_getTable()->glCreateQueries(target,n,ids);}
inline void glCreateRenderbuffers(GLsizei n,GLuint* renderbuffers){this->_getTable()->glCreateRenderbuffers(n,renderbuffers);}
inline void glCreateSamplers(GLsizei n,GLuint* samplers){this->_getTable()->glCreateSamplers(n,samplers);}
inline void glCreateStatesNV(GLsizei n,GLuint* states){this->_getTable()->glCreateStatesNV(n,states);}
inline void glCreateTextures(GLenum target,GLsizei n,GLuint* textures){this->_getTable()->glCreateTextures(target,n,textures);}
inline void glCreateTransformFeedbacks(GLsizei n,GLuint* ids){this->_getTable()->glCreateTransformFeedbacks(n,ids);}
inline void glCreateVertexArrays(GLsizei n,GLuint* arrays){this->_getTable()->glCreateVertexArrays(n,arrays);}
inline void glCullFace(GLenum mode){this->_getTable()->glCullFace(mode);}
inline void glCullParameterdvEXT(GLenum pname,GLdouble* params){this->_getTable()->glCullParameterdvEXT(pname,params);}
inline void glCullParameterfvEXT(GLenum pname,GLfloat* params){this->_getTable()->glCullParameterfvEXT(pname,params);}
inline void glCurrentPaletteMatrixARB(GLint index){this->_getTable()->glCurrentPaletteMatrixARB(index);}
inline void glDebugMessageCallbackAMD(GLDEBUGPROCAMD callback,void* userParam){this->_getTable()->glDebugMessageCallbackAMD(callback,userParam);}
inline void glDebugMessageCallbackARB(GLDEBUGPROCARB callback,const void* userParam){this->_getTable()->glDebugMessageCallbackARB(callback,userParam);}
inline void glDebugMessageCallback(GLDEBUGPROC callback,const void* userParam){this->_getTable()->glDebugMessageCallback(callback,userParam);}
inline void glDebugMessageControlARB(GLenum source,GLenum type,GLenum severity,GLsizei count,const GLuint* ids,GLboolean enabled){this->_getTable()->glDebugMessageControlARB(source,type,severity,count,ids,enabled);}
inline void glDebugMessageControl(GLenum source,GLenum type,GLenum severity,GLsizei count,const GLuint* ids,GLboolean enabled){this->_getTable()->glDebugMessageControl(source,type,severity,count,ids,enabled);}
inline void glDebugMessageEnableAMD(GLenum category,GLenum severity,GLsizei count,const GLuint* ids,GLboolean enabled){this->_getTable()->glDebugMessageEnableAMD(category,severity,count,ids,enabled);}
inline void glDebugMessageInsertAMD(GLenum category,GLenum severity,GLuint id,GLsizei length,const GLchar* buf){this->_getTable()->glDebugMessageInsertAMD(category,severity,id,length,buf);}
inline void glDebugMessageInsertARB(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar* buf){this->_getTable()->glDebugMessageInsertARB(source,type,id,severity,length,buf);}
inline void glDebugMessageInsert(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar* buf){this->_getTable()->glDebugMessageInsert(source,type,id,severity,length,buf);}
inline void glDeformationMap3dSGIX(GLenum target,GLdouble u1,GLdouble u2,GLint ustride,GLint uorder,GLdouble v1,GLdouble v2,GLint vstride,GLint vorder,GLdouble w1,GLdouble w2,GLint wstride,GLint worder,const GLdouble* points){this->_getTable()->glDeformationMap3dSGIX(target,u1,u2,ustride,uorder,v1,v2,vstride,vorder,w1,w2,wstride,worder,points);}
inline void glDeformationMap3fSGIX(GLenum target,GLfloat u1,GLfloat u2,GLint ustride,GLint uorder,GLfloat v1,GLfloat v2,GLint vstride,GLint vorder,GLfloat w1,GLfloat w2,GLint wstride,GLint worder,const GLfloat* points){this->_getTable()->glDeformationMap3fSGIX(target,u1,u2,ustride,uorder,v1,v2,vstride,vorder,w1,w2,wstride,worder,points);}
inline void glDeformSGIX(GLbitfield mask){this->_getTable()->glDeformSGIX(mask);}
inline void glDeleteAsyncMarkersSGIX(GLuint marker,GLsizei range){this->_getTable()->glDeleteAsyncMarkersSGIX(marker,range);}
inline void glDeleteBuffersARB(GLsizei n,const GLuint* buffers){this->_getTable()->glDeleteBuffersARB(n,buffers);}
inline void glDeleteBuffers(GLsizei n,const GLuint* buffers){this->_getTable()->glDeleteBuffers(n,buffers);}
inline void glDeleteCommandListsNV(GLsizei n,const GLuint* lists){this->_getTable()->glDeleteCommandListsNV(n,lists);}
inline void glDeleteFencesAPPLE(GLsizei n,const GLuint* fences){this->_getTable()->glDeleteFencesAPPLE(n,fences);}
inline void glDeleteFencesNV(GLsizei n,const GLuint* fences){this->_getTable()->glDeleteFencesNV(n,fences);}
inline void glDeleteFragmentShaderATI(GLuint id){this->_getTable()->glDeleteFragmentShaderATI(id);}
inline void glDeleteFramebuffersEXT(GLsizei n,const GLuint* framebuffers){this->_getTable()->glDeleteFramebuffersEXT(n,framebuffers);}
inline void glDeleteFramebuffers(GLsizei n,const GLuint* framebuffers){this->_getTable()->glDeleteFramebuffers(n,framebuffers);}
inline void glDeleteLists(GLuint list,GLsizei range){this->_getTable()->glDeleteLists(list,range);}
inline void glDeleteNamedStringARB(GLint namelen,const GLchar* name){this->_getTable()->glDeleteNamedStringARB(namelen,name);}
inline void glDeleteNamesAMD(GLenum identifier,GLuint num,const GLuint* names){this->_getTable()->glDeleteNamesAMD(identifier,num,names);}
inline void glDeleteObjectARB(GLhandleARB obj){this->_getTable()->glDeleteObjectARB(obj);}
inline void glDeleteOcclusionQueriesNV(GLsizei n,const GLuint* ids){this->_getTable()->glDeleteOcclusionQueriesNV(n,ids);}
inline void glDeletePathsNV(GLuint path,GLsizei range){this->_getTable()->glDeletePathsNV(path,range);}
inline void glDeletePerfMonitorsAMD(GLsizei n,GLuint* monitors){this->_getTable()->glDeletePerfMonitorsAMD(n,monitors);}
inline void glDeletePerfQueryINTEL(GLuint queryHandle){this->_getTable()->glDeletePerfQueryINTEL(queryHandle);}
inline void glDeleteProgram(GLuint program){this->_getTable()->glDeleteProgram(program);}
inline void glDeleteProgramPipelines(GLsizei n,const GLuint* pipelines){this->_getTable()->glDeleteProgramPipelines(n,pipelines);}
inline void glDeleteProgramsARB(GLsizei n,const GLuint* programs){this->_getTable()->glDeleteProgramsARB(n,programs);}
inline void glDeleteProgramsNV(GLsizei n,const GLuint* programs){this->_getTable()->glDeleteProgramsNV(n,programs);}
inline void glDeleteQueriesARB(GLsizei n,const GLuint* ids){this->_getTable()->glDeleteQueriesARB(n,ids);}
inline void glDeleteQueries(GLsizei n,const GLuint* ids){this->_getTable()->glDeleteQueries(n,ids);}
inline void glDeleteRenderbuffersEXT(GLsizei n,const GLuint* renderbuffers){this->_getTable()->glDeleteRenderbuffersEXT(n,renderbuffers);}
inline void glDeleteRenderbuffers(GLsizei n,const GLuint* renderbuffers){this->_getTable()->glDeleteRenderbuffers(n,renderbuffers);}
inline void glDeleteSamplers(GLsizei count,const GLuint* samplers){this->_getTable()->glDeleteSamplers(count,samplers);}
inline void glDeleteShader(GLuint shader){this->_getTable()->glDeleteShader(shader);}
inline void glDeleteStatesNV(GLsizei n,const GLuint* states){this->_getTable()->glDeleteStatesNV(n,states);}
inline void glDeleteSync(GLsync sync){this->_getTable()->glDeleteSync(sync);}
inline void glDeleteTexturesEXT(GLsizei n,const GLuint* textures){this->_getTable()->glDeleteTexturesEXT(n,textures);}
inline void glDeleteTextures(GLsizei n,const GLuint* textures){this->_getTable()->glDeleteTextures(n,textures);}
inline void glDeleteTransformFeedbacks(GLsizei n,const GLuint* ids){this->_getTable()->glDeleteTransformFeedbacks(n,ids);}
inline void glDeleteTransformFeedbacksNV(GLsizei n,const GLuint* ids){this->_getTable()->glDeleteTransformFeedbacksNV(n,ids);}
inline void glDeleteVertexArraysAPPLE(GLsizei n,const GLuint* arrays){this->_getTable()->glDeleteVertexArraysAPPLE(n,arrays);}
inline void glDeleteVertexArrays(GLsizei n,const GLuint* arrays){this->_getTable()->glDeleteVertexArrays(n,arrays);}
inline void glDeleteVertexShaderEXT(GLuint id){this->_getTable()->glDeleteVertexShaderEXT(id);}
inline void glDepthBoundsdNV(GLdouble zmin,GLdouble zmax){this->_getTable()->glDepthBoundsdNV(zmin,zmax);}
inline void glDepthBoundsEXT(GLclampd zmin,GLclampd zmax){this->_getTable()->glDepthBoundsEXT(zmin,zmax);}
inline void glDepthFunc(GLenum func){this->_getTable()->glDepthFunc(func);}
inline void glDepthMask(GLboolean flag){this->_getTable()->glDepthMask(flag);}
inline void glDepthRangeArrayv(GLuint first,GLsizei count,const GLdouble* v){this->_getTable()->glDepthRangeArrayv(first,count,v);}
inline void glDepthRangedNV(GLdouble zNear,GLdouble zFar){this->_getTable()->glDepthRangedNV(zNear,zFar);}
inline void glDepthRangef(GLfloat n,GLfloat f){this->_getTable()->glDepthRangef(n,f);}
inline void glDepthRangefOES(GLclampf n,GLclampf f){this->_getTable()->glDepthRangefOES(n,f);}
inline void glDepthRange(GLclampd near_val,GLclampd far_val){this->_getTable()->glDepthRange(near_val,far_val);}
inline void glDepthRangeIndexed(GLuint index,GLdouble n,GLdouble f){this->_getTable()->glDepthRangeIndexed(index,n,f);}
inline void glDepthRangexOES(GLfixed n,GLfixed f){this->_getTable()->glDepthRangexOES(n,f);}
inline void glDetachObjectARB(GLhandleARB containerObj,GLhandleARB attachedObj){this->_getTable()->glDetachObjectARB(containerObj,attachedObj);}
inline void glDetachShader(GLuint program,GLuint shader){this->_getTable()->glDetachShader(program,shader);}
inline void glDetailTexFuncSGIS(GLenum target,GLsizei n,const GLfloat* points){this->_getTable()->glDetailTexFuncSGIS(target,n,points);}
inline void glDisableClientState(GLenum cap){this->_getTable()->glDisableClientState(cap);}
inline void glDisableClientStateiEXT(GLenum array,GLuint index){this->_getTable()->glDisableClientStateiEXT(array,index);}
inline void glDisableClientStateIndexedEXT(GLenum array,GLuint index){this->_getTable()->glDisableClientStateIndexedEXT(array,index);}
inline void glDisable(GLenum cap){this->_getTable()->glDisable(cap);}
inline void glDisablei(GLenum target,GLuint index){this->_getTable()->glDisablei(target,index);}
inline void glDisableIndexedEXT(GLenum target,GLuint index){this->_getTable()->glDisableIndexedEXT(target,index);}
inline void glDisableVariantClientStateEXT(GLuint id){this->_getTable()->glDisableVariantClientStateEXT(id);}
inline void glDisableVertexArrayAttribEXT(GLuint vaobj,GLuint index){this->_getTable()->glDisableVertexArrayAttribEXT(vaobj,index);}
inline void glDisableVertexArrayAttrib(GLuint vaobj,GLuint index){this->_getTable()->glDisableVertexArrayAttrib(vaobj,index);}
inline void glDisableVertexArrayEXT(GLuint vaobj,GLenum array){this->_getTable()->glDisableVertexArrayEXT(vaobj,array);}
inline void glDisableVertexAttribAPPLE(GLuint index,GLenum pname){this->_getTable()->glDisableVertexAttribAPPLE(index,pname);}
inline void glDisableVertexAttribArrayARB(GLuint index){this->_getTable()->glDisableVertexAttribArrayARB(index);}
inline void glDisableVertexAttribArray(GLuint index){this->_getTable()->glDisableVertexAttribArray(index);}
inline void glDispatchCompute(GLuint num_groups_x,GLuint num_groups_y,GLuint num_groups_z){this->_getTable()->glDispatchCompute(num_groups_x,num_groups_y,num_groups_z);}
inline void glDispatchComputeGroupSizeARB(GLuint num_groups_x,GLuint num_groups_y,GLuint num_groups_z,GLuint group_size_x,GLuint group_size_y,GLuint group_size_z){this->_getTable()->glDispatchComputeGroupSizeARB(num_groups_x,num_groups_y,num_groups_z,group_size_x,group_size_y,group_size_z);}
inline void glDispatchComputeIndirect(GLintptr indirect){this->_getTable()->glDispatchComputeIndirect(indirect);}
inline void glDrawArraysEXT(GLenum mode,GLint first,GLsizei count){this->_getTable()->glDrawArraysEXT(mode,first,count);}
inline void glDrawArrays(GLenum mode,GLint first,GLsizei count){this->_getTable()->glDrawArrays(mode,first,count);}
inline void glDrawArraysIndirect(GLenum mode,const void* indirect){this->_getTable()->glDrawArraysIndirect(mode,indirect);}
inline void glDrawArraysInstancedARB(GLenum mode,GLint first,GLsizei count,GLsizei primcount){this->_getTable()->glDrawArraysInstancedARB(mode,first,count,primcount);}
inline void glDrawArraysInstancedBaseInstance(GLenum mode,GLint first,GLsizei count,GLsizei instancecount,GLuint baseinstance){this->_getTable()->glDrawArraysInstancedBaseInstance(mode,first,count,instancecount,baseinstance);}
inline void glDrawArraysInstancedEXT(GLenum mode,GLint start,GLsizei count,GLsizei primcount){this->_getTable()->glDrawArraysInstancedEXT(mode,start,count,primcount);}
inline void glDrawArraysInstanced(GLenum mode,GLint first,GLsizei count,GLsizei instancecount){this->_getTable()->glDrawArraysInstanced(mode,first,count,instancecount);}
inline void glDrawBuffer(GLenum mode){this->_getTable()->glDrawBuffer(mode);}
inline void glDrawBuffersARB(GLsizei n,const GLenum* bufs){this->_getTable()->glDrawBuffersARB(n,bufs);}
inline void glDrawBuffersATI(GLsizei n,const GLenum* bufs){this->_getTable()->glDrawBuffersATI(n,bufs);}
inline void glDrawBuffers(GLsizei n,const GLenum* bufs){this->_getTable()->glDrawBuffers(n,bufs);}
inline void glDrawCommandsAddressNV(GLenum primitiveMode,const GLuint64* indirects,const GLsizei* sizes,GLuint count){this->_getTable()->glDrawCommandsAddressNV(primitiveMode,indirects,sizes,count);}
inline void glDrawCommandsNV(GLenum primitiveMode,GLuint buffer,const GLintptr* indirects,const GLsizei* sizes,GLuint count){this->_getTable()->glDrawCommandsNV(primitiveMode,buffer,indirects,sizes,count);}
inline void glDrawCommandsStatesAddressNV(const GLuint64* indirects,const GLsizei* sizes,const GLuint* states,const GLuint* fbos,GLuint count){this->_getTable()->glDrawCommandsStatesAddressNV(indirects,sizes,states,fbos,count);}
inline void glDrawCommandsStatesNV(GLuint buffer,const GLintptr* indirects,const GLsizei* sizes,const GLuint* states,const GLuint* fbos,GLuint count){this->_getTable()->glDrawCommandsStatesNV(buffer,indirects,sizes,states,fbos,count);}
inline void glDrawElementArrayAPPLE(GLenum mode,GLint first,GLsizei count){this->_getTable()->glDrawElementArrayAPPLE(mode,first,count);}
inline void glDrawElementArrayATI(GLenum mode,GLsizei count){this->_getTable()->glDrawElementArrayATI(mode,count);}
inline void glDrawElementsBaseVertex(GLenum mode,GLsizei count,GLenum type,const void* indices,GLint basevertex){this->_getTable()->glDrawElementsBaseVertex(mode,count,type,indices,basevertex);}
inline void glDrawElements(GLenum mode,GLsizei count,GLenum type,const GLvoid* indices){this->_getTable()->glDrawElements(mode,count,type,indices);}
inline void glDrawElementsIndirect(GLenum mode,GLenum type,const void* indirect){this->_getTable()->glDrawElementsIndirect(mode,type,indirect);}
inline void glDrawElementsInstancedARB(GLenum mode,GLsizei count,GLenum type,const void* indices,GLsizei primcount){this->_getTable()->glDrawElementsInstancedARB(mode,count,type,indices,primcount);}
inline void glDrawElementsInstancedBaseInstance(GLenum mode,GLsizei count,GLenum type,const void* indices,GLsizei instancecount,GLuint baseinstance){this->_getTable()->glDrawElementsInstancedBaseInstance(mode,count,type,indices,instancecount,baseinstance);}
inline void glDrawElementsInstancedBaseVertexBaseInstance(GLenum mode,GLsizei count,GLenum type,const void* indices,GLsizei instancecount,GLint basevertex,GLuint baseinstance){this->_getTable()->glDrawElementsInstancedBaseVertexBaseInstance(mode,count,type,indices,instancecount,basevertex,baseinstance);}
inline void glDrawElementsInstancedBaseVertex(GLenum mode,GLsizei count,GLenum type,const void* indices,GLsizei instancecount,GLint basevertex){this->_getTable()->glDrawElementsInstancedBaseVertex(mode,count,type,indices,instancecount,basevertex);}
inline void glDrawElementsInstancedEXT(GLenum mode,GLsizei count,GLenum type,const void* indices,GLsizei primcount){this->_getTable()->glDrawElementsInstancedEXT(mode,count,type,indices,primcount);}
inline void glDrawElementsInstanced(GLenum mode,GLsizei count,GLenum type,const void* indices,GLsizei instancecount){this->_getTable()->glDrawElementsInstanced(mode,count,type,indices,instancecount);}
inline void glDrawMeshArraysSUN(GLenum mode,GLint first,GLsizei count,GLsizei width){this->_getTable()->glDrawMeshArraysSUN(mode,first,count,width);}
inline void glDrawPixels(GLsizei width,GLsizei height,GLenum format,GLenum type,const GLvoid* pixels){this->_getTable()->glDrawPixels(width,height,format,type,pixels);}
inline void glDrawRangeElementArrayAPPLE(GLenum mode,GLuint start,GLuint end,GLint first,GLsizei count){this->_getTable()->glDrawRangeElementArrayAPPLE(mode,start,end,first,count);}
inline void glDrawRangeElementArrayATI(GLenum mode,GLuint start,GLuint end,GLsizei count){this->_getTable()->glDrawRangeElementArrayATI(mode,start,end,count);}
inline void glDrawRangeElementsBaseVertex(GLenum mode,GLuint start,GLuint end,GLsizei count,GLenum type,const void* indices,GLint basevertex){this->_getTable()->glDrawRangeElementsBaseVertex(mode,start,end,count,type,indices,basevertex);}
inline void glDrawRangeElementsEXT(GLenum mode,GLuint start,GLuint end,GLsizei count,GLenum type,const void* indices){this->_getTable()->glDrawRangeElementsEXT(mode,start,end,count,type,indices);}
inline void glDrawRangeElements(GLenum mode,GLuint start,GLuint end,GLsizei count,GLenum type,const GLvoid* indices){this->_getTable()->glDrawRangeElements(mode,start,end,count,type,indices);}
inline void glDrawTextureNV(GLuint texture,GLuint sampler,GLfloat x0,GLfloat y0,GLfloat x1,GLfloat y1,GLfloat z,GLfloat s0,GLfloat t0,GLfloat s1,GLfloat t1){this->_getTable()->glDrawTextureNV(texture,sampler,x0,y0,x1,y1,z,s0,t0,s1,t1);}
inline void glDrawTransformFeedback(GLenum mode,GLuint id){this->_getTable()->glDrawTransformFeedback(mode,id);}
inline void glDrawTransformFeedbackInstanced(GLenum mode,GLuint id,GLsizei instancecount){this->_getTable()->glDrawTransformFeedbackInstanced(mode,id,instancecount);}
inline void glDrawTransformFeedbackNV(GLenum mode,GLuint id){this->_getTable()->glDrawTransformFeedbackNV(mode,id);}
inline void glDrawTransformFeedbackStream(GLenum mode,GLuint id,GLuint stream){this->_getTable()->glDrawTransformFeedbackStream(mode,id,stream);}
inline void glDrawTransformFeedbackStreamInstanced(GLenum mode,GLuint id,GLuint stream,GLsizei instancecount){this->_getTable()->glDrawTransformFeedbackStreamInstanced(mode,id,stream,instancecount);}
inline void glEdgeFlagFormatNV(GLsizei stride){this->_getTable()->glEdgeFlagFormatNV(stride);}
inline void glEdgeFlag(GLboolean flag){this->_getTable()->glEdgeFlag(flag);}
inline void glEdgeFlagPointerEXT(GLsizei stride,GLsizei count,const GLboolean* pointer){this->_getTable()->glEdgeFlagPointerEXT(stride,count,pointer);}
inline void glEdgeFlagPointer(GLsizei stride,const GLvoid* ptr){this->_getTable()->glEdgeFlagPointer(stride,ptr);}
inline void glEdgeFlagPointerListIBM(GLint stride,const GLboolean** pointer,GLint ptrstride){this->_getTable()->glEdgeFlagPointerListIBM(stride,pointer,ptrstride);}
inline void glEdgeFlagv(const GLboolean* flag){this->_getTable()->glEdgeFlagv(flag);}
inline void glEGLImageTargetRenderbufferStorageOES(GLenum target,GLeglImageOES image){this->_getTable()->glEGLImageTargetRenderbufferStorageOES(target,image);}
inline void glEGLImageTargetTexture2DOES(GLenum target,GLeglImageOES image){this->_getTable()->glEGLImageTargetTexture2DOES(target,image);}
inline void glElementPointerAPPLE(GLenum type,const void* pointer){this->_getTable()->glElementPointerAPPLE(type,pointer);}
inline void glElementPointerATI(GLenum type,const void* pointer){this->_getTable()->glElementPointerATI(type,pointer);}
inline void glEnableClientState(GLenum cap){this->_getTable()->glEnableClientState(cap);}
inline void glEnableClientStateiEXT(GLenum array,GLuint index){this->_getTable()->glEnableClientStateiEXT(array,index);}
inline void glEnableClientStateIndexedEXT(GLenum array,GLuint index){this->_getTable()->glEnableClientStateIndexedEXT(array,index);}
inline void glEnable(GLenum cap){this->_getTable()->glEnable(cap);}
inline void glEnablei(GLenum target,GLuint index){this->_getTable()->glEnablei(target,index);}
inline void glEnableIndexedEXT(GLenum target,GLuint index){this->_getTable()->glEnableIndexedEXT(target,index);}
inline void glEnableVariantClientStateEXT(GLuint id){this->_getTable()->glEnableVariantClientStateEXT(id);}
inline void glEnableVertexArrayAttribEXT(GLuint vaobj,GLuint index){this->_getTable()->glEnableVertexArrayAttribEXT(vaobj,index);}
inline void glEnableVertexArrayAttrib(GLuint vaobj,GLuint index){this->_getTable()->glEnableVertexArrayAttrib(vaobj,index);}
inline void glEnableVertexArrayEXT(GLuint vaobj,GLenum array){this->_getTable()->glEnableVertexArrayEXT(vaobj,array);}
inline void glEnableVertexAttribAPPLE(GLuint index,GLenum pname){this->_getTable()->glEnableVertexAttribAPPLE(index,pname);}
inline void glEnableVertexAttribArrayARB(GLuint index){this->_getTable()->glEnableVertexAttribArrayARB(index);}
inline void glEnableVertexAttribArray(GLuint index){this->_getTable()->glEnableVertexAttribArray(index);}
inline void glEnd(){this->_getTable()->glEnd();}
inline void glEndConditionalRender(){this->_getTable()->glEndConditionalRender();}
inline void glEndConditionalRenderNV(){this->_getTable()->glEndConditionalRenderNV();}
inline void glEndConditionalRenderNVX(){this->_getTable()->glEndConditionalRenderNVX();}
inline void glEndFragmentShaderATI(){this->_getTable()->glEndFragmentShaderATI();}
inline void glEndList(){this->_getTable()->glEndList();}
inline void glEndOcclusionQueryNV(){this->_getTable()->glEndOcclusionQueryNV();}
inline void glEndPerfMonitorAMD(GLuint monitor){this->_getTable()->glEndPerfMonitorAMD(monitor);}
inline void glEndPerfQueryINTEL(GLuint queryHandle){this->_getTable()->glEndPerfQueryINTEL(queryHandle);}
inline void glEndQueryARB(GLenum target){this->_getTable()->glEndQueryARB(target);}
inline void glEndQuery(GLenum target){this->_getTable()->glEndQuery(target);}
inline void glEndQueryIndexed(GLenum target,GLuint index){this->_getTable()->glEndQueryIndexed(target,index);}
inline void glEndTransformFeedback(){this->_getTable()->glEndTransformFeedback();}
inline void glEndTransformFeedbackEXT(){this->_getTable()->glEndTransformFeedbackEXT();}
inline void glEndTransformFeedbackNV(){this->_getTable()->glEndTransformFeedbackNV();}
inline void glEndVertexShaderEXT(){this->_getTable()->glEndVertexShaderEXT();}
inline void glEndVideoCaptureNV(GLuint video_capture_slot){this->_getTable()->glEndVideoCaptureNV(video_capture_slot);}
inline void glEvalCoord1d(GLdouble u){this->_getTable()->glEvalCoord1d(u);}
inline void glEvalCoord1dv(const GLdouble* u){this->_getTable()->glEvalCoord1dv(u);}
inline void glEvalCoord1f(GLfloat u){this->_getTable()->glEvalCoord1f(u);}
inline void glEvalCoord1fv(const GLfloat* u){this->_getTable()->glEvalCoord1fv(u);}
inline void glEvalCoord1xOES(GLfixed u){this->_getTable()->glEvalCoord1xOES(u);}
inline void glEvalCoord1xvOES(const GLfixed* coords){this->_getTable()->glEvalCoord1xvOES(coords);}
inline void glEvalCoord2d(GLdouble u,GLdouble v){this->_getTable()->glEvalCoord2d(u,v);}
inline void glEvalCoord2dv(const GLdouble* u){this->_getTable()->glEvalCoord2dv(u);}
inline void glEvalCoord2f(GLfloat u,GLfloat v){this->_getTable()->glEvalCoord2f(u,v);}
inline void glEvalCoord2fv(const GLfloat* u){this->_getTable()->glEvalCoord2fv(u);}
inline void glEvalCoord2xOES(GLfixed u,GLfixed v){this->_getTable()->glEvalCoord2xOES(u,v);}
inline void glEvalCoord2xvOES(const GLfixed* coords){this->_getTable()->glEvalCoord2xvOES(coords);}
inline void glEvalMapsNV(GLenum target,GLenum mode){this->_getTable()->glEvalMapsNV(target,mode);}
inline void glEvalMesh1(GLenum mode,GLint i1,GLint i2){this->_getTable()->glEvalMesh1(mode,i1,i2);}
inline void glEvalMesh2(GLenum mode,GLint i1,GLint i2,GLint j1,GLint j2){this->_getTable()->glEvalMesh2(mode,i1,i2,j1,j2);}
inline void glEvalPoint1(GLint i){this->_getTable()->glEvalPoint1(i);}
inline void glEvalPoint2(GLint i,GLint j){this->_getTable()->glEvalPoint2(i,j);}
inline void glEvaluateDepthValuesARB(){this->_getTable()->glEvaluateDepthValuesARB();}
inline void glExecuteProgramNV(GLenum target,GLuint id,const GLfloat* params){this->_getTable()->glExecuteProgramNV(target,id,params);}
inline void glExtractComponentEXT(GLuint res,GLuint src,GLuint num){this->_getTable()->glExtractComponentEXT(res,src,num);}
inline void glFeedbackBuffer(GLsizei size,GLenum type,GLfloat* buffer){this->_getTable()->glFeedbackBuffer(size,type,buffer);}
inline void glFeedbackBufferxOES(GLsizei n,GLenum type,const GLfixed* buffer){this->_getTable()->glFeedbackBufferxOES(n,type,buffer);}
inline void glFinalCombinerInputNV(GLenum variable,GLenum input,GLenum mapping,GLenum componentUsage){this->_getTable()->glFinalCombinerInputNV(variable,input,mapping,componentUsage);}
inline void glFinish(){this->_getTable()->glFinish();}
inline void glFinishFenceAPPLE(GLuint fence){this->_getTable()->glFinishFenceAPPLE(fence);}
inline void glFinishFenceNV(GLuint fence){this->_getTable()->glFinishFenceNV(fence);}
inline void glFinishObjectAPPLE(GLenum object,GLint name){this->_getTable()->glFinishObjectAPPLE(object,name);}
inline void glFinishTextureSUNX(){this->_getTable()->glFinishTextureSUNX();}
inline void glFlush(){this->_getTable()->glFlush();}
inline void glFlushMappedBufferRangeAPPLE(GLenum target,GLintptr offset,GLsizeiptr size){this->_getTable()->glFlushMappedBufferRangeAPPLE(target,offset,size);}
inline void glFlushMappedBufferRange(GLenum target,GLintptr offset,GLsizeiptr length){this->_getTable()->glFlushMappedBufferRange(target,offset,length);}
inline void glFlushMappedNamedBufferRangeEXT(GLuint buffer,GLintptr offset,GLsizeiptr length){this->_getTable()->glFlushMappedNamedBufferRangeEXT(buffer,offset,length);}
inline void glFlushMappedNamedBufferRange(GLuint buffer,GLintptr offset,GLsizeiptr length){this->_getTable()->glFlushMappedNamedBufferRange(buffer,offset,length);}
inline void glFlushPixelDataRangeNV(GLenum target){this->_getTable()->glFlushPixelDataRangeNV(target);}
inline void glFlushRasterSGIX(){this->_getTable()->glFlushRasterSGIX();}
inline void glFlushStaticDataIBM(GLenum target){this->_getTable()->glFlushStaticDataIBM(target);}
inline void glFlushVertexArrayRangeAPPLE(GLsizei length,void* pointer){this->_getTable()->glFlushVertexArrayRangeAPPLE(length,pointer);}
inline void glFlushVertexArrayRangeNV(){this->_getTable()->glFlushVertexArrayRangeNV();}
inline void glFogCoorddEXT(GLdouble coord){this->_getTable()->glFogCoorddEXT(coord);}
inline void glFogCoordd(GLdouble coord){this->_getTable()->glFogCoordd(coord);}
inline void glFogCoorddv(const GLdouble* coord){this->_getTable()->glFogCoorddv(coord);}
inline void glFogCoorddvEXT(const GLdouble* coord){this->_getTable()->glFogCoorddvEXT(coord);}
inline void glFogCoordfEXT(GLfloat coord){this->_getTable()->glFogCoordfEXT(coord);}
inline void glFogCoordf(GLfloat coord){this->_getTable()->glFogCoordf(coord);}
inline void glFogCoordFormatNV(GLenum type,GLsizei stride){this->_getTable()->glFogCoordFormatNV(type,stride);}
inline void glFogCoordfv(const GLfloat* coord){this->_getTable()->glFogCoordfv(coord);}
inline void glFogCoordfvEXT(const GLfloat* coord){this->_getTable()->glFogCoordfvEXT(coord);}
inline void glFogCoordhNV(GLhalfNV fog){this->_getTable()->glFogCoordhNV(fog);}
inline void glFogCoordhvNV(const GLhalfNV* fog){this->_getTable()->glFogCoordhvNV(fog);}
inline void glFogCoordPointerEXT(GLenum type,GLsizei stride,const void* pointer){this->_getTable()->glFogCoordPointerEXT(type,stride,pointer);}
inline void glFogCoordPointer(GLenum type,GLsizei stride,const void* pointer){this->_getTable()->glFogCoordPointer(type,stride,pointer);}
inline void glFogCoordPointerListIBM(GLenum type,GLint stride,const void** pointer,GLint ptrstride){this->_getTable()->glFogCoordPointerListIBM(type,stride,pointer,ptrstride);}
inline void glFogf(GLenum pname,GLfloat param){this->_getTable()->glFogf(pname,param);}
inline void glFogFuncSGIS(GLsizei n,const GLfloat* points){this->_getTable()->glFogFuncSGIS(n,points);}
inline void glFogfv(GLenum pname,const GLfloat* params){this->_getTable()->glFogfv(pname,params);}
inline void glFogi(GLenum pname,GLint param){this->_getTable()->glFogi(pname,param);}
inline void glFogiv(GLenum pname,const GLint* params){this->_getTable()->glFogiv(pname,params);}
inline void glFogxOES(GLenum pname,GLfixed param){this->_getTable()->glFogxOES(pname,param);}
inline void glFogxvOES(GLenum pname,const GLfixed* param){this->_getTable()->glFogxvOES(pname,param);}
inline void glFragmentColorMaterialSGIX(GLenum face,GLenum mode){this->_getTable()->glFragmentColorMaterialSGIX(face,mode);}
inline void glFragmentCoverageColorNV(GLuint color){this->_getTable()->glFragmentCoverageColorNV(color);}
inline void glFragmentLightfSGIX(GLenum light,GLenum pname,GLfloat param){this->_getTable()->glFragmentLightfSGIX(light,pname,param);}
inline void glFragmentLightfvSGIX(GLenum light,GLenum pname,const GLfloat* params){this->_getTable()->glFragmentLightfvSGIX(light,pname,params);}
inline void glFragmentLightiSGIX(GLenum light,GLenum pname,GLint param){this->_getTable()->glFragmentLightiSGIX(light,pname,param);}
inline void glFragmentLightivSGIX(GLenum light,GLenum pname,const GLint* params){this->_getTable()->glFragmentLightivSGIX(light,pname,params);}
inline void glFragmentLightModelfSGIX(GLenum pname,GLfloat param){this->_getTable()->glFragmentLightModelfSGIX(pname,param);}
inline void glFragmentLightModelfvSGIX(GLenum pname,const GLfloat* params){this->_getTable()->glFragmentLightModelfvSGIX(pname,params);}
inline void glFragmentLightModeliSGIX(GLenum pname,GLint param){this->_getTable()->glFragmentLightModeliSGIX(pname,param);}
inline void glFragmentLightModelivSGIX(GLenum pname,const GLint* params){this->_getTable()->glFragmentLightModelivSGIX(pname,params);}
inline void glFragmentMaterialfSGIX(GLenum face,GLenum pname,GLfloat param){this->_getTable()->glFragmentMaterialfSGIX(face,pname,param);}
inline void glFragmentMaterialfvSGIX(GLenum face,GLenum pname,const GLfloat* params){this->_getTable()->glFragmentMaterialfvSGIX(face,pname,params);}
inline void glFragmentMaterialiSGIX(GLenum face,GLenum pname,GLint param){this->_getTable()->glFragmentMaterialiSGIX(face,pname,param);}
inline void glFragmentMaterialivSGIX(GLenum face,GLenum pname,const GLint* params){this->_getTable()->glFragmentMaterialivSGIX(face,pname,params);}
inline void glFramebufferDrawBufferEXT(GLuint framebuffer,GLenum mode){this->_getTable()->glFramebufferDrawBufferEXT(framebuffer,mode);}
inline void glFramebufferDrawBuffersEXT(GLuint framebuffer,GLsizei n,const GLenum* bufs){this->_getTable()->glFramebufferDrawBuffersEXT(framebuffer,n,bufs);}
inline void glFramebufferParameteri(GLenum target,GLenum pname,GLint param){this->_getTable()->glFramebufferParameteri(target,pname,param);}
inline void glFramebufferReadBufferEXT(GLuint framebuffer,GLenum mode){this->_getTable()->glFramebufferReadBufferEXT(framebuffer,mode);}
inline void glFramebufferRenderbufferEXT(GLenum target,GLenum attachment,GLenum renderbuffertarget,GLuint renderbuffer){this->_getTable()->glFramebufferRenderbufferEXT(target,attachment,renderbuffertarget,renderbuffer);}
inline void glFramebufferRenderbuffer(GLenum target,GLenum attachment,GLenum renderbuffertarget,GLuint renderbuffer){this->_getTable()->glFramebufferRenderbuffer(target,attachment,renderbuffertarget,renderbuffer);}
inline void glFramebufferSampleLocationsfvARB(GLenum target,GLuint start,GLsizei count,const GLfloat* v){this->_getTable()->glFramebufferSampleLocationsfvARB(target,start,count,v);}
inline void glFramebufferSampleLocationsfvNV(GLenum target,GLuint start,GLsizei count,const GLfloat* v){this->_getTable()->glFramebufferSampleLocationsfvNV(target,start,count,v);}
inline void glFramebufferTexture1DEXT(GLenum target,GLenum attachment,GLenum textarget,GLuint texture,GLint level){this->_getTable()->glFramebufferTexture1DEXT(target,attachment,textarget,texture,level);}
inline void glFramebufferTexture1D(GLenum target,GLenum attachment,GLenum textarget,GLuint texture,GLint level){this->_getTable()->glFramebufferTexture1D(target,attachment,textarget,texture,level);}
inline void glFramebufferTexture2DEXT(GLenum target,GLenum attachment,GLenum textarget,GLuint texture,GLint level){this->_getTable()->glFramebufferTexture2DEXT(target,attachment,textarget,texture,level);}
inline void glFramebufferTexture2D(GLenum target,GLenum attachment,GLenum textarget,GLuint texture,GLint level){this->_getTable()->glFramebufferTexture2D(target,attachment,textarget,texture,level);}
inline void glFramebufferTexture3DEXT(GLenum target,GLenum attachment,GLenum textarget,GLuint texture,GLint level,GLint zoffset){this->_getTable()->glFramebufferTexture3DEXT(target,attachment,textarget,texture,level,zoffset);}
inline void glFramebufferTexture3D(GLenum target,GLenum attachment,GLenum textarget,GLuint texture,GLint level,GLint zoffset){this->_getTable()->glFramebufferTexture3D(target,attachment,textarget,texture,level,zoffset);}
inline void glFramebufferTextureARB(GLenum target,GLenum attachment,GLuint texture,GLint level){this->_getTable()->glFramebufferTextureARB(target,attachment,texture,level);}
inline void glFramebufferTextureEXT(GLenum target,GLenum attachment,GLuint texture,GLint level){this->_getTable()->glFramebufferTextureEXT(target,attachment,texture,level);}
inline void glFramebufferTextureFaceARB(GLenum target,GLenum attachment,GLuint texture,GLint level,GLenum face){this->_getTable()->glFramebufferTextureFaceARB(target,attachment,texture,level,face);}
inline void glFramebufferTextureFaceEXT(GLenum target,GLenum attachment,GLuint texture,GLint level,GLenum face){this->_getTable()->glFramebufferTextureFaceEXT(target,attachment,texture,level,face);}
inline void glFramebufferTexture(GLenum target,GLenum attachment,GLuint texture,GLint level){this->_getTable()->glFramebufferTexture(target,attachment,texture,level);}
inline void glFramebufferTextureLayerARB(GLenum target,GLenum attachment,GLuint texture,GLint level,GLint layer){this->_getTable()->glFramebufferTextureLayerARB(target,attachment,texture,level,layer);}
inline void glFramebufferTextureLayerEXT(GLenum target,GLenum attachment,GLuint texture,GLint level,GLint layer){this->_getTable()->glFramebufferTextureLayerEXT(target,attachment,texture,level,layer);}
inline void glFramebufferTextureLayer(GLenum target,GLenum attachment,GLuint texture,GLint level,GLint layer){this->_getTable()->glFramebufferTextureLayer(target,attachment,texture,level,layer);}
inline void glFramebufferTextureMultiviewOVR(GLenum target,GLenum attachment,GLuint texture,GLint level,GLint baseViewIndex,GLsizei numViews){this->_getTable()->glFramebufferTextureMultiviewOVR(target,attachment,texture,level,baseViewIndex,numViews);}
inline void glFrameTerminatorGREMEDY(){this->_getTable()->glFrameTerminatorGREMEDY();}
inline void glFrameZoomSGIX(GLint factor){this->_getTable()->glFrameZoomSGIX(factor);}
inline void glFreeObjectBufferATI(GLuint buffer){this->_getTable()->glFreeObjectBufferATI(buffer);}
inline void glFrontFace(GLenum mode){this->_getTable()->glFrontFace(mode);}
inline void glFrustumfOES(GLfloat l,GLfloat r,GLfloat b,GLfloat t,GLfloat n,GLfloat f){this->_getTable()->glFrustumfOES(l,r,b,t,n,f);}
inline void glFrustum(GLdouble left,GLdouble right,GLdouble bottom,GLdouble top,GLdouble near_val,GLdouble far_val){this->_getTable()->glFrustum(left,right,bottom,top,near_val,far_val);}
inline void glFrustumxOES(GLfixed l,GLfixed r,GLfixed b,GLfixed t,GLfixed n,GLfixed f){this->_getTable()->glFrustumxOES(l,r,b,t,n,f);}
inline void glGenBuffersARB(GLsizei n,GLuint* buffers){this->_getTable()->glGenBuffersARB(n,buffers);}
inline void glGenBuffers(GLsizei n,GLuint* buffers){this->_getTable()->glGenBuffers(n,buffers);}
inline void glGenerateMipmapEXT(GLenum target){this->_getTable()->glGenerateMipmapEXT(target);}
inline void glGenerateMipmap(GLenum target){this->_getTable()->glGenerateMipmap(target);}
inline void glGenerateMultiTexMipmapEXT(GLenum texunit,GLenum target){this->_getTable()->glGenerateMultiTexMipmapEXT(texunit,target);}
inline void glGenerateTextureMipmapEXT(GLuint texture,GLenum target){this->_getTable()->glGenerateTextureMipmapEXT(texture,target);}
inline void glGenerateTextureMipmap(GLuint texture){this->_getTable()->glGenerateTextureMipmap(texture);}
inline void glGenFencesAPPLE(GLsizei n,GLuint* fences){this->_getTable()->glGenFencesAPPLE(n,fences);}
inline void glGenFencesNV(GLsizei n,GLuint* fences){this->_getTable()->glGenFencesNV(n,fences);}
inline void glGenFramebuffersEXT(GLsizei n,GLuint* framebuffers){this->_getTable()->glGenFramebuffersEXT(n,framebuffers);}
inline void glGenFramebuffers(GLsizei n,GLuint* framebuffers){this->_getTable()->glGenFramebuffers(n,framebuffers);}
inline void glGenNamesAMD(GLenum identifier,GLuint num,GLuint* names){this->_getTable()->glGenNamesAMD(identifier,num,names);}
inline void glGenOcclusionQueriesNV(GLsizei n,GLuint* ids){this->_getTable()->glGenOcclusionQueriesNV(n,ids);}
inline void glGenPerfMonitorsAMD(GLsizei n,GLuint* monitors){this->_getTable()->glGenPerfMonitorsAMD(n,monitors);}
inline void glGenProgramPipelines(GLsizei n,GLuint* pipelines){this->_getTable()->glGenProgramPipelines(n,pipelines);}
inline void glGenProgramsARB(GLsizei n,GLuint* programs){this->_getTable()->glGenProgramsARB(n,programs);}
inline void glGenProgramsNV(GLsizei n,GLuint* programs){this->_getTable()->glGenProgramsNV(n,programs);}
inline void glGenQueriesARB(GLsizei n,GLuint* ids){this->_getTable()->glGenQueriesARB(n,ids);}
inline void glGenQueries(GLsizei n,GLuint* ids){this->_getTable()->glGenQueries(n,ids);}
inline void glGenRenderbuffersEXT(GLsizei n,GLuint* renderbuffers){this->_getTable()->glGenRenderbuffersEXT(n,renderbuffers);}
inline void glGenRenderbuffers(GLsizei n,GLuint* renderbuffers){this->_getTable()->glGenRenderbuffers(n,renderbuffers);}
inline void glGenSamplers(GLsizei count,GLuint* samplers){this->_getTable()->glGenSamplers(count,samplers);}
inline void glGenTexturesEXT(GLsizei n,GLuint* textures){this->_getTable()->glGenTexturesEXT(n,textures);}
inline void glGenTextures(GLsizei n,GLuint* textures){this->_getTable()->glGenTextures(n,textures);}
inline void glGenTransformFeedbacks(GLsizei n,GLuint* ids){this->_getTable()->glGenTransformFeedbacks(n,ids);}
inline void glGenTransformFeedbacksNV(GLsizei n,GLuint* ids){this->_getTable()->glGenTransformFeedbacksNV(n,ids);}
inline void glGenVertexArraysAPPLE(GLsizei n,GLuint* arrays){this->_getTable()->glGenVertexArraysAPPLE(n,arrays);}
inline void glGenVertexArrays(GLsizei n,GLuint* arrays){this->_getTable()->glGenVertexArrays(n,arrays);}
inline void glGetActiveAtomicCounterBufferiv(GLuint program,GLuint bufferIndex,GLenum pname,GLint* params){this->_getTable()->glGetActiveAtomicCounterBufferiv(program,bufferIndex,pname,params);}
inline void glGetActiveAttribARB(GLhandleARB programObj,GLuint index,GLsizei maxLength,GLsizei* length,GLint* size,GLenum* type,GLcharARB* name){this->_getTable()->glGetActiveAttribARB(programObj,index,maxLength,length,size,type,name);}
inline void glGetActiveAttrib(GLuint program,GLuint index,GLsizei bufSize,GLsizei* length,GLint* size,GLenum* type,GLchar* name){this->_getTable()->glGetActiveAttrib(program,index,bufSize,length,size,type,name);}
inline void glGetActiveSubroutineName(GLuint program,GLenum shadertype,GLuint index,GLsizei bufsize,GLsizei* length,GLchar* name){this->_getTable()->glGetActiveSubroutineName(program,shadertype,index,bufsize,length,name);}
inline void glGetActiveSubroutineUniformiv(GLuint program,GLenum shadertype,GLuint index,GLenum pname,GLint* values){this->_getTable()->glGetActiveSubroutineUniformiv(program,shadertype,index,pname,values);}
inline void glGetActiveSubroutineUniformName(GLuint program,GLenum shadertype,GLuint index,GLsizei bufsize,GLsizei* length,GLchar* name){this->_getTable()->glGetActiveSubroutineUniformName(program,shadertype,index,bufsize,length,name);}
inline void glGetActiveUniformARB(GLhandleARB programObj,GLuint index,GLsizei maxLength,GLsizei* length,GLint* size,GLenum* type,GLcharARB* name){this->_getTable()->glGetActiveUniformARB(programObj,index,maxLength,length,size,type,name);}
inline void glGetActiveUniformBlockiv(GLuint program,GLuint uniformBlockIndex,GLenum pname,GLint* params){this->_getTable()->glGetActiveUniformBlockiv(program,uniformBlockIndex,pname,params);}
inline void glGetActiveUniformBlockName(GLuint program,GLuint uniformBlockIndex,GLsizei bufSize,GLsizei* length,GLchar* uniformBlockName){this->_getTable()->glGetActiveUniformBlockName(program,uniformBlockIndex,bufSize,length,uniformBlockName);}
inline void glGetActiveUniform(GLuint program,GLuint index,GLsizei bufSize,GLsizei* length,GLint* size,GLenum* type,GLchar* name){this->_getTable()->glGetActiveUniform(program,index,bufSize,length,size,type,name);}
inline void glGetActiveUniformName(GLuint program,GLuint uniformIndex,GLsizei bufSize,GLsizei* length,GLchar* uniformName){this->_getTable()->glGetActiveUniformName(program,uniformIndex,bufSize,length,uniformName);}
inline void glGetActiveUniformsiv(GLuint program,GLsizei uniformCount,const GLuint* uniformIndices,GLenum pname,GLint* params){this->_getTable()->glGetActiveUniformsiv(program,uniformCount,uniformIndices,pname,params);}
inline void glGetActiveVaryingNV(GLuint program,GLuint index,GLsizei bufSize,GLsizei* length,GLsizei* size,GLenum* type,GLchar* name){this->_getTable()->glGetActiveVaryingNV(program,index,bufSize,length,size,type,name);}
inline void glGetArrayObjectfvATI(GLenum array,GLenum pname,GLfloat* params){this->_getTable()->glGetArrayObjectfvATI(array,pname,params);}
inline void glGetArrayObjectivATI(GLenum array,GLenum pname,GLint* params){this->_getTable()->glGetArrayObjectivATI(array,pname,params);}
inline void glGetAttachedObjectsARB(GLhandleARB containerObj,GLsizei maxCount,GLsizei* count,GLhandleARB* obj){this->_getTable()->glGetAttachedObjectsARB(containerObj,maxCount,count,obj);}
inline void glGetAttachedShaders(GLuint program,GLsizei maxCount,GLsizei* count,GLuint* shaders){this->_getTable()->glGetAttachedShaders(program,maxCount,count,shaders);}
inline void glGetBooleanIndexedvEXT(GLenum target,GLuint index,GLboolean* data){this->_getTable()->glGetBooleanIndexedvEXT(target,index,data);}
inline void glGetBooleani_v(GLenum target,GLuint index,GLboolean* data){this->_getTable()->glGetBooleani_v(target,index,data);}
inline void glGetBooleanv(GLenum pname,GLboolean* params){this->_getTable()->glGetBooleanv(pname,params);}
inline void glGetBufferParameteri64v(GLenum target,GLenum pname,GLint64* params){this->_getTable()->glGetBufferParameteri64v(target,pname,params);}
inline void glGetBufferParameterivARB(GLenum target,GLenum pname,GLint* params){this->_getTable()->glGetBufferParameterivARB(target,pname,params);}
inline void glGetBufferParameteriv(GLenum target,GLenum pname,GLint* params){this->_getTable()->glGetBufferParameteriv(target,pname,params);}
inline void glGetBufferParameterui64vNV(GLenum target,GLenum pname,GLuint64EXT* params){this->_getTable()->glGetBufferParameterui64vNV(target,pname,params);}
inline void glGetBufferPointervARB(GLenum target,GLenum pname,void** params){this->_getTable()->glGetBufferPointervARB(target,pname,params);}
inline void glGetBufferPointerv(GLenum target,GLenum pname,void** params){this->_getTable()->glGetBufferPointerv(target,pname,params);}
inline void glGetBufferSubDataARB(GLenum target,GLintptrARB offset,GLsizeiptrARB size,void* data){this->_getTable()->glGetBufferSubDataARB(target,offset,size,data);}
inline void glGetBufferSubData(GLenum target,GLintptr offset,GLsizeiptr size,void* data){this->_getTable()->glGetBufferSubData(target,offset,size,data);}
inline void glGetClipPlanefOES(GLenum plane,GLfloat* equation){this->_getTable()->glGetClipPlanefOES(plane,equation);}
inline void glGetClipPlane(GLenum plane,GLdouble* equation){this->_getTable()->glGetClipPlane(plane,equation);}
inline void glGetClipPlanexOES(GLenum plane,GLfixed* equation){this->_getTable()->glGetClipPlanexOES(plane,equation);}
inline void glGetColorTableEXT(GLenum target,GLenum format,GLenum type,void* data){this->_getTable()->glGetColorTableEXT(target,format,type,data);}
inline void glGetColorTable(GLenum target,GLenum format,GLenum type,GLvoid* table){this->_getTable()->glGetColorTable(target,format,type,table);}
inline void glGetColorTableParameterfvEXT(GLenum target,GLenum pname,GLfloat* params){this->_getTable()->glGetColorTableParameterfvEXT(target,pname,params);}
inline void glGetColorTableParameterfv(GLenum target,GLenum pname,GLfloat* params){this->_getTable()->glGetColorTableParameterfv(target,pname,params);}
inline void glGetColorTableParameterfvSGI(GLenum target,GLenum pname,GLfloat* params){this->_getTable()->glGetColorTableParameterfvSGI(target,pname,params);}
inline void glGetColorTableParameterivEXT(GLenum target,GLenum pname,GLint* params){this->_getTable()->glGetColorTableParameterivEXT(target,pname,params);}
inline void glGetColorTableParameteriv(GLenum target,GLenum pname,GLint* params){this->_getTable()->glGetColorTableParameteriv(target,pname,params);}
inline void glGetColorTableParameterivSGI(GLenum target,GLenum pname,GLint* params){this->_getTable()->glGetColorTableParameterivSGI(target,pname,params);}
inline void glGetColorTableSGI(GLenum target,GLenum format,GLenum type,void* table){this->_getTable()->glGetColorTableSGI(target,format,type,table);}
inline void glGetCombinerInputParameterfvNV(GLenum stage,GLenum portion,GLenum variable,GLenum pname,GLfloat* params){this->_getTable()->glGetCombinerInputParameterfvNV(stage,portion,variable,pname,params);}
inline void glGetCombinerInputParameterivNV(GLenum stage,GLenum portion,GLenum variable,GLenum pname,GLint* params){this->_getTable()->glGetCombinerInputParameterivNV(stage,portion,variable,pname,params);}
inline void glGetCombinerOutputParameterfvNV(GLenum stage,GLenum portion,GLenum pname,GLfloat* params){this->_getTable()->glGetCombinerOutputParameterfvNV(stage,portion,pname,params);}
inline void glGetCombinerOutputParameterivNV(GLenum stage,GLenum portion,GLenum pname,GLint* params){this->_getTable()->glGetCombinerOutputParameterivNV(stage,portion,pname,params);}
inline void glGetCombinerStageParameterfvNV(GLenum stage,GLenum pname,GLfloat* params){this->_getTable()->glGetCombinerStageParameterfvNV(stage,pname,params);}
inline void glGetCompressedMultiTexImageEXT(GLenum texunit,GLenum target,GLint lod,void* img){this->_getTable()->glGetCompressedMultiTexImageEXT(texunit,target,lod,img);}
inline void glGetCompressedTexImageARB(GLenum target,GLint level,void* img){this->_getTable()->glGetCompressedTexImageARB(target,level,img);}
inline void glGetCompressedTexImage(GLenum target,GLint lod,GLvoid* img){this->_getTable()->glGetCompressedTexImage(target,lod,img);}
inline void glGetCompressedTextureImageEXT(GLuint texture,GLenum target,GLint lod,void* img){this->_getTable()->glGetCompressedTextureImageEXT(texture,target,lod,img);}
inline void glGetCompressedTextureImage(GLuint texture,GLint level,GLsizei bufSize,void* pixels){this->_getTable()->glGetCompressedTextureImage(texture,level,bufSize,pixels);}
inline void glGetCompressedTextureSubImage(GLuint texture,GLint level,GLint xoffset,GLint yoffset,GLint zoffset,GLsizei width,GLsizei height,GLsizei depth,GLsizei bufSize,void* pixels){this->_getTable()->glGetCompressedTextureSubImage(texture,level,xoffset,yoffset,zoffset,width,height,depth,bufSize,pixels);}
inline void glGetConvolutionFilterEXT(GLenum target,GLenum format,GLenum type,void* image){this->_getTable()->glGetConvolutionFilterEXT(target,format,type,image);}
inline void glGetConvolutionFilter(GLenum target,GLenum format,GLenum type,GLvoid* image){this->_getTable()->glGetConvolutionFilter(target,format,type,image);}
inline void glGetConvolutionParameterfvEXT(GLenum target,GLenum pname,GLfloat* params){this->_getTable()->glGetConvolutionParameterfvEXT(target,pname,params);}
inline void glGetConvolutionParameterfv(GLenum target,GLenum pname,GLfloat* params){this->_getTable()->glGetConvolutionParameterfv(target,pname,params);}
inline void glGetConvolutionParameterivEXT(GLenum target,GLenum pname,GLint* params){this->_getTable()->glGetConvolutionParameterivEXT(target,pname,params);}
inline void glGetConvolutionParameteriv(GLenum target,GLenum pname,GLint* params){this->_getTable()->glGetConvolutionParameteriv(target,pname,params);}
inline void glGetConvolutionParameterxvOES(GLenum target,GLenum pname,GLfixed* params){this->_getTable()->glGetConvolutionParameterxvOES(target,pname,params);}
inline void glGetCoverageModulationTableNV(GLsizei bufsize,GLfloat* v){this->_getTable()->glGetCoverageModulationTableNV(bufsize,v);}
inline void glGetDetailTexFuncSGIS(GLenum target,GLfloat* points){this->_getTable()->glGetDetailTexFuncSGIS(target,points);}
inline void glGetDoubleIndexedvEXT(GLenum target,GLuint index,GLdouble* data){this->_getTable()->glGetDoubleIndexedvEXT(target,index,data);}
inline void glGetDoublei_vEXT(GLenum pname,GLuint index,GLdouble* params){this->_getTable()->glGetDoublei_vEXT(pname,index,params);}
inline void glGetDoublei_v(GLenum target,GLuint index,GLdouble* data){this->_getTable()->glGetDoublei_v(target,index,data);}
inline void glGetDoublev(GLenum pname,GLdouble* params){this->_getTable()->glGetDoublev(pname,params);}
inline void glGetFenceivNV(GLuint fence,GLenum pname,GLint* params){this->_getTable()->glGetFenceivNV(fence,pname,params);}
inline void glGetFinalCombinerInputParameterfvNV(GLenum variable,GLenum pname,GLfloat* params){this->_getTable()->glGetFinalCombinerInputParameterfvNV(variable,pname,params);}
inline void glGetFinalCombinerInputParameterivNV(GLenum variable,GLenum pname,GLint* params){this->_getTable()->glGetFinalCombinerInputParameterivNV(variable,pname,params);}
inline void glGetFirstPerfQueryIdINTEL(GLuint* queryId){this->_getTable()->glGetFirstPerfQueryIdINTEL(queryId);}
inline void glGetFixedvOES(GLenum pname,GLfixed* params){this->_getTable()->glGetFixedvOES(pname,params);}
inline void glGetFloatIndexedvEXT(GLenum target,GLuint index,GLfloat* data){this->_getTable()->glGetFloatIndexedvEXT(target,index,data);}
inline void glGetFloati_vEXT(GLenum pname,GLuint index,GLfloat* params){this->_getTable()->glGetFloati_vEXT(pname,index,params);}
inline void glGetFloati_v(GLenum target,GLuint index,GLfloat* data){this->_getTable()->glGetFloati_v(target,index,data);}
inline void glGetFloatv(GLenum pname,GLfloat* params){this->_getTable()->glGetFloatv(pname,params);}
inline void glGetFogFuncSGIS(GLfloat* points){this->_getTable()->glGetFogFuncSGIS(points);}
inline void glGetFragmentLightfvSGIX(GLenum light,GLenum pname,GLfloat* params){this->_getTable()->glGetFragmentLightfvSGIX(light,pname,params);}
inline void glGetFragmentLightivSGIX(GLenum light,GLenum pname,GLint* params){this->_getTable()->glGetFragmentLightivSGIX(light,pname,params);}
inline void glGetFragmentMaterialfvSGIX(GLenum face,GLenum pname,GLfloat* params){this->_getTable()->glGetFragmentMaterialfvSGIX(face,pname,params);}
inline void glGetFragmentMaterialivSGIX(GLenum face,GLenum pname,GLint* params){this->_getTable()->glGetFragmentMaterialivSGIX(face,pname,params);}
inline void glGetFramebufferAttachmentParameterivEXT(GLenum target,GLenum attachment,GLenum pname,GLint* params){this->_getTable()->glGetFramebufferAttachmentParameterivEXT(target,attachment,pname,params);}
inline void glGetFramebufferAttachmentParameteriv(GLenum target,GLenum attachment,GLenum pname,GLint* params){this->_getTable()->glGetFramebufferAttachmentParameteriv(target,attachment,pname,params);}
inline void glGetFramebufferParameterivEXT(GLuint framebuffer,GLenum pname,GLint* params){this->_getTable()->glGetFramebufferParameterivEXT(framebuffer,pname,params);}
inline void glGetFramebufferParameteriv(GLenum target,GLenum pname,GLint* params){this->_getTable()->glGetFramebufferParameteriv(target,pname,params);}
inline void glGetHistogramEXT(GLenum target,GLboolean reset,GLenum format,GLenum type,void* values){this->_getTable()->glGetHistogramEXT(target,reset,format,type,values);}
inline void glGetHistogram(GLenum target,GLboolean reset,GLenum format,GLenum type,GLvoid* values){this->_getTable()->glGetHistogram(target,reset,format,type,values);}
inline void glGetHistogramParameterfvEXT(GLenum target,GLenum pname,GLfloat* params){this->_getTable()->glGetHistogramParameterfvEXT(target,pname,params);}
inline void glGetHistogramParameterfv(GLenum target,GLenum pname,GLfloat* params){this->_getTable()->glGetHistogramParameterfv(target,pname,params);}
inline void glGetHistogramParameterivEXT(GLenum target,GLenum pname,GLint* params){this->_getTable()->glGetHistogramParameterivEXT(target,pname,params);}
inline void glGetHistogramParameteriv(GLenum target,GLenum pname,GLint* params){this->_getTable()->glGetHistogramParameteriv(target,pname,params);}
inline void glGetHistogramParameterxvOES(GLenum target,GLenum pname,GLfixed* params){this->_getTable()->glGetHistogramParameterxvOES(target,pname,params);}
inline void glGetImageTransformParameterfvHP(GLenum target,GLenum pname,GLfloat* params){this->_getTable()->glGetImageTransformParameterfvHP(target,pname,params);}
inline void glGetImageTransformParameterivHP(GLenum target,GLenum pname,GLint* params){this->_getTable()->glGetImageTransformParameterivHP(target,pname,params);}
inline void glGetInfoLogARB(GLhandleARB obj,GLsizei maxLength,GLsizei* length,GLcharARB* infoLog){this->_getTable()->glGetInfoLogARB(obj,maxLength,length,infoLog);}
inline void glGetInteger64i_v(GLenum target,GLuint index,GLint64* data){this->_getTable()->glGetInteger64i_v(target,index,data);}
inline void glGetInteger64v(GLenum pname,GLint64* data){this->_getTable()->glGetInteger64v(pname,data);}
inline void glGetIntegerIndexedvEXT(GLenum target,GLuint index,GLint* data){this->_getTable()->glGetIntegerIndexedvEXT(target,index,data);}
inline void glGetIntegeri_v(GLenum target,GLuint index,GLint* data){this->_getTable()->glGetIntegeri_v(target,index,data);}
inline void glGetIntegerui64i_vNV(GLenum value,GLuint index,GLuint64EXT* result){this->_getTable()->glGetIntegerui64i_vNV(value,index,result);}
inline void glGetIntegerui64vNV(GLenum value,GLuint64EXT* result){this->_getTable()->glGetIntegerui64vNV(value,result);}
inline void glGetIntegerv(GLenum pname,GLint* params){this->_getTable()->glGetIntegerv(pname,params);}
inline void glGetInternalformati64v(GLenum target,GLenum internalformat,GLenum pname,GLsizei bufSize,GLint64* params){this->_getTable()->glGetInternalformati64v(target,internalformat,pname,bufSize,params);}
inline void glGetInternalformativ(GLenum target,GLenum internalformat,GLenum pname,GLsizei bufSize,GLint* params){this->_getTable()->glGetInternalformativ(target,internalformat,pname,bufSize,params);}
inline void glGetInternalformatSampleivNV(GLenum target,GLenum internalformat,GLsizei samples,GLenum pname,GLsizei bufSize,GLint* params){this->_getTable()->glGetInternalformatSampleivNV(target,internalformat,samples,pname,bufSize,params);}
inline void glGetInvariantBooleanvEXT(GLuint id,GLenum value,GLboolean* data){this->_getTable()->glGetInvariantBooleanvEXT(id,value,data);}
inline void glGetInvariantFloatvEXT(GLuint id,GLenum value,GLfloat* data){this->_getTable()->glGetInvariantFloatvEXT(id,value,data);}
inline void glGetInvariantIntegervEXT(GLuint id,GLenum value,GLint* data){this->_getTable()->glGetInvariantIntegervEXT(id,value,data);}
inline void glGetLightfv(GLenum light,GLenum pname,GLfloat* params){this->_getTable()->glGetLightfv(light,pname,params);}
inline void glGetLightiv(GLenum light,GLenum pname,GLint* params){this->_getTable()->glGetLightiv(light,pname,params);}
inline void glGetLightxOES(GLenum light,GLenum pname,GLfixed* params){this->_getTable()->glGetLightxOES(light,pname,params);}
inline void glGetListParameterfvSGIX(GLuint list,GLenum pname,GLfloat* params){this->_getTable()->glGetListParameterfvSGIX(list,pname,params);}
inline void glGetListParameterivSGIX(GLuint list,GLenum pname,GLint* params){this->_getTable()->glGetListParameterivSGIX(list,pname,params);}
inline void glGetLocalConstantBooleanvEXT(GLuint id,GLenum value,GLboolean* data){this->_getTable()->glGetLocalConstantBooleanvEXT(id,value,data);}
inline void glGetLocalConstantFloatvEXT(GLuint id,GLenum value,GLfloat* data){this->_getTable()->glGetLocalConstantFloatvEXT(id,value,data);}
inline void glGetLocalConstantIntegervEXT(GLuint id,GLenum value,GLint* data){this->_getTable()->glGetLocalConstantIntegervEXT(id,value,data);}
inline void glGetMapAttribParameterfvNV(GLenum target,GLuint index,GLenum pname,GLfloat* params){this->_getTable()->glGetMapAttribParameterfvNV(target,index,pname,params);}
inline void glGetMapAttribParameterivNV(GLenum target,GLuint index,GLenum pname,GLint* params){this->_getTable()->glGetMapAttribParameterivNV(target,index,pname,params);}
inline void glGetMapControlPointsNV(GLenum target,GLuint index,GLenum type,GLsizei ustride,GLsizei vstride,GLboolean packed,void* points){this->_getTable()->glGetMapControlPointsNV(target,index,type,ustride,vstride,packed,points);}
inline void glGetMapdv(GLenum target,GLenum query,GLdouble* v){this->_getTable()->glGetMapdv(target,query,v);}
inline void glGetMapfv(GLenum target,GLenum query,GLfloat* v){this->_getTable()->glGetMapfv(target,query,v);}
inline void glGetMapiv(GLenum target,GLenum query,GLint* v){this->_getTable()->glGetMapiv(target,query,v);}
inline void glGetMapParameterfvNV(GLenum target,GLenum pname,GLfloat* params){this->_getTable()->glGetMapParameterfvNV(target,pname,params);}
inline void glGetMapParameterivNV(GLenum target,GLenum pname,GLint* params){this->_getTable()->glGetMapParameterivNV(target,pname,params);}
inline void glGetMapxvOES(GLenum target,GLenum query,GLfixed* v){this->_getTable()->glGetMapxvOES(target,query,v);}
inline void glGetMaterialfv(GLenum face,GLenum pname,GLfloat* params){this->_getTable()->glGetMaterialfv(face,pname,params);}
inline void glGetMaterialiv(GLenum face,GLenum pname,GLint* params){this->_getTable()->glGetMaterialiv(face,pname,params);}
inline void glGetMaterialxOES(GLenum face,GLenum pname,GLfixed param){this->_getTable()->glGetMaterialxOES(face,pname,param);}
inline void glGetMinmaxEXT(GLenum target,GLboolean reset,GLenum format,GLenum type,void* values){this->_getTable()->glGetMinmaxEXT(target,reset,format,type,values);}
inline void glGetMinmax(GLenum target,GLboolean reset,GLenum format,GLenum types,GLvoid* values){this->_getTable()->glGetMinmax(target,reset,format,types,values);}
inline void glGetMinmaxParameterfvEXT(GLenum target,GLenum pname,GLfloat* params){this->_getTable()->glGetMinmaxParameterfvEXT(target,pname,params);}
inline void glGetMinmaxParameterfv(GLenum target,GLenum pname,GLfloat* params){this->_getTable()->glGetMinmaxParameterfv(target,pname,params);}
inline void glGetMinmaxParameterivEXT(GLenum target,GLenum pname,GLint* params){this->_getTable()->glGetMinmaxParameterivEXT(target,pname,params);}
inline void glGetMinmaxParameteriv(GLenum target,GLenum pname,GLint* params){this->_getTable()->glGetMinmaxParameteriv(target,pname,params);}
inline void glGetMultisamplefv(GLenum pname,GLuint index,GLfloat* val){this->_getTable()->glGetMultisamplefv(pname,index,val);}
inline void glGetMultisamplefvNV(GLenum pname,GLuint index,GLfloat* val){this->_getTable()->glGetMultisamplefvNV(pname,index,val);}
inline void glGetMultiTexEnvfvEXT(GLenum texunit,GLenum target,GLenum pname,GLfloat* params){this->_getTable()->glGetMultiTexEnvfvEXT(texunit,target,pname,params);}
inline void glGetMultiTexEnvivEXT(GLenum texunit,GLenum target,GLenum pname,GLint* params){this->_getTable()->glGetMultiTexEnvivEXT(texunit,target,pname,params);}
inline void glGetMultiTexGendvEXT(GLenum texunit,GLenum coord,GLenum pname,GLdouble* params){this->_getTable()->glGetMultiTexGendvEXT(texunit,coord,pname,params);}
inline void glGetMultiTexGenfvEXT(GLenum texunit,GLenum coord,GLenum pname,GLfloat* params){this->_getTable()->glGetMultiTexGenfvEXT(texunit,coord,pname,params);}
inline void glGetMultiTexGenivEXT(GLenum texunit,GLenum coord,GLenum pname,GLint* params){this->_getTable()->glGetMultiTexGenivEXT(texunit,coord,pname,params);}
inline void glGetMultiTexImageEXT(GLenum texunit,GLenum target,GLint level,GLenum format,GLenum type,void* pixels){this->_getTable()->glGetMultiTexImageEXT(texunit,target,level,format,type,pixels);}
inline void glGetMultiTexLevelParameterfvEXT(GLenum texunit,GLenum target,GLint level,GLenum pname,GLfloat* params){this->_getTable()->glGetMultiTexLevelParameterfvEXT(texunit,target,level,pname,params);}
inline void glGetMultiTexLevelParameterivEXT(GLenum texunit,GLenum target,GLint level,GLenum pname,GLint* params){this->_getTable()->glGetMultiTexLevelParameterivEXT(texunit,target,level,pname,params);}
inline void glGetMultiTexParameterfvEXT(GLenum texunit,GLenum target,GLenum pname,GLfloat* params){this->_getTable()->glGetMultiTexParameterfvEXT(texunit,target,pname,params);}
inline void glGetMultiTexParameterIivEXT(GLenum texunit,GLenum target,GLenum pname,GLint* params){this->_getTable()->glGetMultiTexParameterIivEXT(texunit,target,pname,params);}
inline void glGetMultiTexParameterIuivEXT(GLenum texunit,GLenum target,GLenum pname,GLuint* params){this->_getTable()->glGetMultiTexParameterIuivEXT(texunit,target,pname,params);}
inline void glGetMultiTexParameterivEXT(GLenum texunit,GLenum target,GLenum pname,GLint* params){this->_getTable()->glGetMultiTexParameterivEXT(texunit,target,pname,params);}
inline void glGetNamedBufferParameteri64v(GLuint buffer,GLenum pname,GLint64* params){this->_getTable()->glGetNamedBufferParameteri64v(buffer,pname,params);}
inline void glGetNamedBufferParameterivEXT(GLuint buffer,GLenum pname,GLint* params){this->_getTable()->glGetNamedBufferParameterivEXT(buffer,pname,params);}
inline void glGetNamedBufferParameteriv(GLuint buffer,GLenum pname,GLint* params){this->_getTable()->glGetNamedBufferParameteriv(buffer,pname,params);}
inline void glGetNamedBufferParameterui64vNV(GLuint buffer,GLenum pname,GLuint64EXT* params){this->_getTable()->glGetNamedBufferParameterui64vNV(buffer,pname,params);}
inline void glGetNamedBufferPointervEXT(GLuint buffer,GLenum pname,void** params){this->_getTable()->glGetNamedBufferPointervEXT(buffer,pname,params);}
inline void glGetNamedBufferPointerv(GLuint buffer,GLenum pname,void** params){this->_getTable()->glGetNamedBufferPointerv(buffer,pname,params);}
inline void glGetNamedBufferSubDataEXT(GLuint buffer,GLintptr offset,GLsizeiptr size,void* data){this->_getTable()->glGetNamedBufferSubDataEXT(buffer,offset,size,data);}
inline void glGetNamedBufferSubData(GLuint buffer,GLintptr offset,GLsizeiptr size,void* data){this->_getTable()->glGetNamedBufferSubData(buffer,offset,size,data);}
inline void glGetNamedFramebufferAttachmentParameterivEXT(GLuint framebuffer,GLenum attachment,GLenum pname,GLint* params){this->_getTable()->glGetNamedFramebufferAttachmentParameterivEXT(framebuffer,attachment,pname,params);}
inline void glGetNamedFramebufferAttachmentParameteriv(GLuint framebuffer,GLenum attachment,GLenum pname,GLint* params){this->_getTable()->glGetNamedFramebufferAttachmentParameteriv(framebuffer,attachment,pname,params);}
inline void glGetNamedFramebufferParameterivEXT(GLuint framebuffer,GLenum pname,GLint* params){this->_getTable()->glGetNamedFramebufferParameterivEXT(framebuffer,pname,params);}
inline void glGetNamedFramebufferParameteriv(GLuint framebuffer,GLenum pname,GLint* param){this->_getTable()->glGetNamedFramebufferParameteriv(framebuffer,pname,param);}
inline void glGetNamedProgramivEXT(GLuint program,GLenum target,GLenum pname,GLint* params){this->_getTable()->glGetNamedProgramivEXT(program,target,pname,params);}
inline void glGetNamedProgramLocalParameterdvEXT(GLuint program,GLenum target,GLuint index,GLdouble* params){this->_getTable()->glGetNamedProgramLocalParameterdvEXT(program,target,index,params);}
inline void glGetNamedProgramLocalParameterfvEXT(GLuint program,GLenum target,GLuint index,GLfloat* params){this->_getTable()->glGetNamedProgramLocalParameterfvEXT(program,target,index,params);}
inline void glGetNamedProgramLocalParameterIivEXT(GLuint program,GLenum target,GLuint index,GLint* params){this->_getTable()->glGetNamedProgramLocalParameterIivEXT(program,target,index,params);}
inline void glGetNamedProgramLocalParameterIuivEXT(GLuint program,GLenum target,GLuint index,GLuint* params){this->_getTable()->glGetNamedProgramLocalParameterIuivEXT(program,target,index,params);}
inline void glGetNamedProgramStringEXT(GLuint program,GLenum target,GLenum pname,void* string){this->_getTable()->glGetNamedProgramStringEXT(program,target,pname,string);}
inline void glGetNamedRenderbufferParameterivEXT(GLuint renderbuffer,GLenum pname,GLint* params){this->_getTable()->glGetNamedRenderbufferParameterivEXT(renderbuffer,pname,params);}
inline void glGetNamedRenderbufferParameteriv(GLuint renderbuffer,GLenum pname,GLint* params){this->_getTable()->glGetNamedRenderbufferParameteriv(renderbuffer,pname,params);}
inline void glGetNamedStringARB(GLint namelen,const GLchar* name,GLsizei bufSize,GLint* stringlen,GLchar* string){this->_getTable()->glGetNamedStringARB(namelen,name,bufSize,stringlen,string);}
inline void glGetNamedStringivARB(GLint namelen,const GLchar* name,GLenum pname,GLint* params){this->_getTable()->glGetNamedStringivARB(namelen,name,pname,params);}
inline void glGetnColorTableARB(GLenum target,GLenum format,GLenum type,GLsizei bufSize,void* table){this->_getTable()->glGetnColorTableARB(target,format,type,bufSize,table);}
inline void glGetnColorTable(GLenum target,GLenum format,GLenum type,GLsizei bufSize,void* table){this->_getTable()->glGetnColorTable(target,format,type,bufSize,table);}
inline void glGetnCompressedTexImageARB(GLenum target,GLint lod,GLsizei bufSize,void* img){this->_getTable()->glGetnCompressedTexImageARB(target,lod,bufSize,img);}
inline void glGetnCompressedTexImage(GLenum target,GLint lod,GLsizei bufSize,void* pixels){this->_getTable()->glGetnCompressedTexImage(target,lod,bufSize,pixels);}
inline void glGetnConvolutionFilterARB(GLenum target,GLenum format,GLenum type,GLsizei bufSize,void* image){this->_getTable()->glGetnConvolutionFilterARB(target,format,type,bufSize,image);}
inline void glGetnConvolutionFilter(GLenum target,GLenum format,GLenum type,GLsizei bufSize,void* image){this->_getTable()->glGetnConvolutionFilter(target,format,type,bufSize,image);}
inline void glGetNextPerfQueryIdINTEL(GLuint queryId,GLuint* nextQueryId){this->_getTable()->glGetNextPerfQueryIdINTEL(queryId,nextQueryId);}
inline void glGetnHistogramARB(GLenum target,GLboolean reset,GLenum format,GLenum type,GLsizei bufSize,void* values){this->_getTable()->glGetnHistogramARB(target,reset,format,type,bufSize,values);}
inline void glGetnHistogram(GLenum target,GLboolean reset,GLenum format,GLenum type,GLsizei bufSize,void* values){this->_getTable()->glGetnHistogram(target,reset,format,type,bufSize,values);}
inline void glGetnMapdvARB(GLenum target,GLenum query,GLsizei bufSize,GLdouble* v){this->_getTable()->glGetnMapdvARB(target,query,bufSize,v);}
inline void glGetnMapdv(GLenum target,GLenum query,GLsizei bufSize,GLdouble* v){this->_getTable()->glGetnMapdv(target,query,bufSize,v);}
inline void glGetnMapfvARB(GLenum target,GLenum query,GLsizei bufSize,GLfloat* v){this->_getTable()->glGetnMapfvARB(target,query,bufSize,v);}
inline void glGetnMapfv(GLenum target,GLenum query,GLsizei bufSize,GLfloat* v){this->_getTable()->glGetnMapfv(target,query,bufSize,v);}
inline void glGetnMapivARB(GLenum target,GLenum query,GLsizei bufSize,GLint* v){this->_getTable()->glGetnMapivARB(target,query,bufSize,v);}
inline void glGetnMapiv(GLenum target,GLenum query,GLsizei bufSize,GLint* v){this->_getTable()->glGetnMapiv(target,query,bufSize,v);}
inline void glGetnMinmaxARB(GLenum target,GLboolean reset,GLenum format,GLenum type,GLsizei bufSize,void* values){this->_getTable()->glGetnMinmaxARB(target,reset,format,type,bufSize,values);}
inline void glGetnMinmax(GLenum target,GLboolean reset,GLenum format,GLenum type,GLsizei bufSize,void* values){this->_getTable()->glGetnMinmax(target,reset,format,type,bufSize,values);}
inline void glGetnPixelMapfvARB(GLenum map,GLsizei bufSize,GLfloat* values){this->_getTable()->glGetnPixelMapfvARB(map,bufSize,values);}
inline void glGetnPixelMapfv(GLenum map,GLsizei bufSize,GLfloat* values){this->_getTable()->glGetnPixelMapfv(map,bufSize,values);}
inline void glGetnPixelMapuivARB(GLenum map,GLsizei bufSize,GLuint* values){this->_getTable()->glGetnPixelMapuivARB(map,bufSize,values);}
inline void glGetnPixelMapuiv(GLenum map,GLsizei bufSize,GLuint* values){this->_getTable()->glGetnPixelMapuiv(map,bufSize,values);}
inline void glGetnPixelMapusvARB(GLenum map,GLsizei bufSize,GLushort* values){this->_getTable()->glGetnPixelMapusvARB(map,bufSize,values);}
inline void glGetnPixelMapusv(GLenum map,GLsizei bufSize,GLushort* values){this->_getTable()->glGetnPixelMapusv(map,bufSize,values);}
inline void glGetnPolygonStippleARB(GLsizei bufSize,GLubyte* pattern){this->_getTable()->glGetnPolygonStippleARB(bufSize,pattern);}
inline void glGetnPolygonStipple(GLsizei bufSize,GLubyte* pattern){this->_getTable()->glGetnPolygonStipple(bufSize,pattern);}
inline void glGetnSeparableFilterARB(GLenum target,GLenum format,GLenum type,GLsizei rowBufSize,void* row,GLsizei columnBufSize,void* column,void* span){this->_getTable()->glGetnSeparableFilterARB(target,format,type,rowBufSize,row,columnBufSize,column,span);}
inline void glGetnSeparableFilter(GLenum target,GLenum format,GLenum type,GLsizei rowBufSize,void* row,GLsizei columnBufSize,void* column,void* span){this->_getTable()->glGetnSeparableFilter(target,format,type,rowBufSize,row,columnBufSize,column,span);}
inline void glGetnTexImageARB(GLenum target,GLint level,GLenum format,GLenum type,GLsizei bufSize,void* img){this->_getTable()->glGetnTexImageARB(target,level,format,type,bufSize,img);}
inline void glGetnTexImage(GLenum target,GLint level,GLenum format,GLenum type,GLsizei bufSize,void* pixels){this->_getTable()->glGetnTexImage(target,level,format,type,bufSize,pixels);}
inline void glGetnUniformdvARB(GLuint program,GLint location,GLsizei bufSize,GLdouble* params){this->_getTable()->glGetnUniformdvARB(program,location,bufSize,params);}
inline void glGetnUniformdv(GLuint program,GLint location,GLsizei bufSize,GLdouble* params){this->_getTable()->glGetnUniformdv(program,location,bufSize,params);}
inline void glGetnUniformfvARB(GLuint program,GLint location,GLsizei bufSize,GLfloat* params){this->_getTable()->glGetnUniformfvARB(program,location,bufSize,params);}
inline void glGetnUniformfv(GLuint program,GLint location,GLsizei bufSize,GLfloat* params){this->_getTable()->glGetnUniformfv(program,location,bufSize,params);}
inline void glGetnUniformi64vARB(GLuint program,GLint location,GLsizei bufSize,GLint64* params){this->_getTable()->glGetnUniformi64vARB(program,location,bufSize,params);}
inline void glGetnUniformivARB(GLuint program,GLint location,GLsizei bufSize,GLint* params){this->_getTable()->glGetnUniformivARB(program,location,bufSize,params);}
inline void glGetnUniformiv(GLuint program,GLint location,GLsizei bufSize,GLint* params){this->_getTable()->glGetnUniformiv(program,location,bufSize,params);}
inline void glGetnUniformui64vARB(GLuint program,GLint location,GLsizei bufSize,GLuint64* params){this->_getTable()->glGetnUniformui64vARB(program,location,bufSize,params);}
inline void glGetnUniformuivARB(GLuint program,GLint location,GLsizei bufSize,GLuint* params){this->_getTable()->glGetnUniformuivARB(program,location,bufSize,params);}
inline void glGetnUniformuiv(GLuint program,GLint location,GLsizei bufSize,GLuint* params){this->_getTable()->glGetnUniformuiv(program,location,bufSize,params);}
inline void glGetObjectBufferfvATI(GLuint buffer,GLenum pname,GLfloat* params){this->_getTable()->glGetObjectBufferfvATI(buffer,pname,params);}
inline void glGetObjectBufferivATI(GLuint buffer,GLenum pname,GLint* params){this->_getTable()->glGetObjectBufferivATI(buffer,pname,params);}
inline void glGetObjectLabelEXT(GLenum type,GLuint object,GLsizei bufSize,GLsizei* length,GLchar* label){this->_getTable()->glGetObjectLabelEXT(type,object,bufSize,length,label);}
inline void glGetObjectLabel(GLenum identifier,GLuint name,GLsizei bufSize,GLsizei* length,GLchar* label){this->_getTable()->glGetObjectLabel(identifier,name,bufSize,length,label);}
inline void glGetObjectParameterfvARB(GLhandleARB obj,GLenum pname,GLfloat* params){this->_getTable()->glGetObjectParameterfvARB(obj,pname,params);}
inline void glGetObjectParameterivAPPLE(GLenum objectType,GLuint name,GLenum pname,GLint* params){this->_getTable()->glGetObjectParameterivAPPLE(objectType,name,pname,params);}
inline void glGetObjectParameterivARB(GLhandleARB obj,GLenum pname,GLint* params){this->_getTable()->glGetObjectParameterivARB(obj,pname,params);}
inline void glGetObjectPtrLabel(const void* ptr,GLsizei bufSize,GLsizei* length,GLchar* label){this->_getTable()->glGetObjectPtrLabel(ptr,bufSize,length,label);}
inline void glGetOcclusionQueryivNV(GLuint id,GLenum pname,GLint* params){this->_getTable()->glGetOcclusionQueryivNV(id,pname,params);}
inline void glGetOcclusionQueryuivNV(GLuint id,GLenum pname,GLuint* params){this->_getTable()->glGetOcclusionQueryuivNV(id,pname,params);}
inline void glGetPathColorGenfvNV(GLenum color,GLenum pname,GLfloat* value){this->_getTable()->glGetPathColorGenfvNV(color,pname,value);}
inline void glGetPathColorGenivNV(GLenum color,GLenum pname,GLint* value){this->_getTable()->glGetPathColorGenivNV(color,pname,value);}
inline void glGetPathCommandsNV(GLuint path,GLubyte* commands){this->_getTable()->glGetPathCommandsNV(path,commands);}
inline void glGetPathCoordsNV(GLuint path,GLfloat* coords){this->_getTable()->glGetPathCoordsNV(path,coords);}
inline void glGetPathDashArrayNV(GLuint path,GLfloat* dashArray){this->_getTable()->glGetPathDashArrayNV(path,dashArray);}
inline void glGetPathMetricRangeNV(GLbitfield metricQueryMask,GLuint firstPathName,GLsizei numPaths,GLsizei stride,GLfloat* metrics){this->_getTable()->glGetPathMetricRangeNV(metricQueryMask,firstPathName,numPaths,stride,metrics);}
inline void glGetPathMetricsNV(GLbitfield metricQueryMask,GLsizei numPaths,GLenum pathNameType,const void* paths,GLuint pathBase,GLsizei stride,GLfloat* metrics){this->_getTable()->glGetPathMetricsNV(metricQueryMask,numPaths,pathNameType,paths,pathBase,stride,metrics);}
inline void glGetPathParameterfvNV(GLuint path,GLenum pname,GLfloat* value){this->_getTable()->glGetPathParameterfvNV(path,pname,value);}
inline void glGetPathParameterivNV(GLuint path,GLenum pname,GLint* value){this->_getTable()->glGetPathParameterivNV(path,pname,value);}
inline void glGetPathSpacingNV(GLenum pathListMode,GLsizei numPaths,GLenum pathNameType,const void* paths,GLuint pathBase,GLfloat advanceScale,GLfloat kerningScale,GLenum transformType,GLfloat* returnedSpacing){this->_getTable()->glGetPathSpacingNV(pathListMode,numPaths,pathNameType,paths,pathBase,advanceScale,kerningScale,transformType,returnedSpacing);}
inline void glGetPathTexGenfvNV(GLenum texCoordSet,GLenum pname,GLfloat* value){this->_getTable()->glGetPathTexGenfvNV(texCoordSet,pname,value);}
inline void glGetPathTexGenivNV(GLenum texCoordSet,GLenum pname,GLint* value){this->_getTable()->glGetPathTexGenivNV(texCoordSet,pname,value);}
inline void glGetPerfCounterInfoINTEL(GLuint queryId,GLuint counterId,GLuint counterNameLength,GLchar* counterName,GLuint counterDescLength,GLchar* counterDesc,GLuint* counterOffset,GLuint* counterDataSize,GLuint* counterTypeEnum,GLuint* counterDataTypeEnum,GLuint64* rawCounterMaxValue){this->_getTable()->glGetPerfCounterInfoINTEL(queryId,counterId,counterNameLength,counterName,counterDescLength,counterDesc,counterOffset,counterDataSize,counterTypeEnum,counterDataTypeEnum,rawCounterMaxValue);}
inline void glGetPerfMonitorCounterDataAMD(GLuint monitor,GLenum pname,GLsizei dataSize,GLuint* data,GLint* bytesWritten){this->_getTable()->glGetPerfMonitorCounterDataAMD(monitor,pname,dataSize,data,bytesWritten);}
inline void glGetPerfMonitorCounterInfoAMD(GLuint group,GLuint counter,GLenum pname,void* data){this->_getTable()->glGetPerfMonitorCounterInfoAMD(group,counter,pname,data);}
inline void glGetPerfMonitorCountersAMD(GLuint group,GLint* numCounters,GLint* maxActiveCounters,GLsizei counterSize,GLuint* counters){this->_getTable()->glGetPerfMonitorCountersAMD(group,numCounters,maxActiveCounters,counterSize,counters);}
inline void glGetPerfMonitorCounterStringAMD(GLuint group,GLuint counter,GLsizei bufSize,GLsizei* length,GLchar* counterString){this->_getTable()->glGetPerfMonitorCounterStringAMD(group,counter,bufSize,length,counterString);}
inline void glGetPerfMonitorGroupsAMD(GLint* numGroups,GLsizei groupsSize,GLuint* groups){this->_getTable()->glGetPerfMonitorGroupsAMD(numGroups,groupsSize,groups);}
inline void glGetPerfMonitorGroupStringAMD(GLuint group,GLsizei bufSize,GLsizei* length,GLchar* groupString){this->_getTable()->glGetPerfMonitorGroupStringAMD(group,bufSize,length,groupString);}
inline void glGetPerfQueryDataINTEL(GLuint queryHandle,GLuint flags,GLsizei dataSize,GLvoid* data,GLuint* bytesWritten){this->_getTable()->glGetPerfQueryDataINTEL(queryHandle,flags,dataSize,data,bytesWritten);}
inline void glGetPerfQueryIdByNameINTEL(GLchar* queryName,GLuint* queryId){this->_getTable()->glGetPerfQueryIdByNameINTEL(queryName,queryId);}
inline void glGetPerfQueryInfoINTEL(GLuint queryId,GLuint queryNameLength,GLchar* queryName,GLuint* dataSize,GLuint* noCounters,GLuint* noInstances,GLuint* capsMask){this->_getTable()->glGetPerfQueryInfoINTEL(queryId,queryNameLength,queryName,dataSize,noCounters,noInstances,capsMask);}
inline void glGetPixelMapfv(GLenum map,GLfloat* values){this->_getTable()->glGetPixelMapfv(map,values);}
inline void glGetPixelMapuiv(GLenum map,GLuint* values){this->_getTable()->glGetPixelMapuiv(map,values);}
inline void glGetPixelMapusv(GLenum map,GLushort* values){this->_getTable()->glGetPixelMapusv(map,values);}
inline void glGetPixelMapxv(GLenum map,GLint size,GLfixed* values){this->_getTable()->glGetPixelMapxv(map,size,values);}
inline void glGetPixelTexGenParameterfvSGIS(GLenum pname,GLfloat* params){this->_getTable()->glGetPixelTexGenParameterfvSGIS(pname,params);}
inline void glGetPixelTexGenParameterivSGIS(GLenum pname,GLint* params){this->_getTable()->glGetPixelTexGenParameterivSGIS(pname,params);}
inline void glGetPixelTransformParameterfvEXT(GLenum target,GLenum pname,GLfloat* params){this->_getTable()->glGetPixelTransformParameterfvEXT(target,pname,params);}
inline void glGetPixelTransformParameterivEXT(GLenum target,GLenum pname,GLint* params){this->_getTable()->glGetPixelTransformParameterivEXT(target,pname,params);}
inline void glGetPointerIndexedvEXT(GLenum target,GLuint index,void** data){this->_getTable()->glGetPointerIndexedvEXT(target,index,data);}
inline void glGetPointeri_vEXT(GLenum pname,GLuint index,void** params){this->_getTable()->glGetPointeri_vEXT(pname,index,params);}
inline void glGetPointervEXT(GLenum pname,void** params){this->_getTable()->glGetPointervEXT(pname,params);}
inline void glGetPointerv(GLenum pname,GLvoid** params){this->_getTable()->glGetPointerv(pname,params);}
inline void glGetPolygonStipple(GLubyte* mask){this->_getTable()->glGetPolygonStipple(mask);}
inline void glGetProgramBinary(GLuint program,GLsizei bufSize,GLsizei* length,GLenum* binaryFormat,void* binary){this->_getTable()->glGetProgramBinary(program,bufSize,length,binaryFormat,binary);}
inline void glGetProgramEnvParameterdvARB(GLenum target,GLuint index,GLdouble* params){this->_getTable()->glGetProgramEnvParameterdvARB(target,index,params);}
inline void glGetProgramEnvParameterfvARB(GLenum target,GLuint index,GLfloat* params){this->_getTable()->glGetProgramEnvParameterfvARB(target,index,params);}
inline void glGetProgramEnvParameterIivNV(GLenum target,GLuint index,GLint* params){this->_getTable()->glGetProgramEnvParameterIivNV(target,index,params);}
inline void glGetProgramEnvParameterIuivNV(GLenum target,GLuint index,GLuint* params){this->_getTable()->glGetProgramEnvParameterIuivNV(target,index,params);}
inline void glGetProgramInfoLog(GLuint program,GLsizei bufSize,GLsizei* length,GLchar* infoLog){this->_getTable()->glGetProgramInfoLog(program,bufSize,length,infoLog);}
inline void glGetProgramInterfaceiv(GLuint program,GLenum programInterface,GLenum pname,GLint* params){this->_getTable()->glGetProgramInterfaceiv(program,programInterface,pname,params);}
inline void glGetProgramivARB(GLenum target,GLenum pname,GLint* params){this->_getTable()->glGetProgramivARB(target,pname,params);}
inline void glGetProgramiv(GLuint program,GLenum pname,GLint* params){this->_getTable()->glGetProgramiv(program,pname,params);}
inline void glGetProgramivNV(GLuint id,GLenum pname,GLint* params){this->_getTable()->glGetProgramivNV(id,pname,params);}
inline void glGetProgramLocalParameterdvARB(GLenum target,GLuint index,GLdouble* params){this->_getTable()->glGetProgramLocalParameterdvARB(target,index,params);}
inline void glGetProgramLocalParameterfvARB(GLenum target,GLuint index,GLfloat* params){this->_getTable()->glGetProgramLocalParameterfvARB(target,index,params);}
inline void glGetProgramLocalParameterIivNV(GLenum target,GLuint index,GLint* params){this->_getTable()->glGetProgramLocalParameterIivNV(target,index,params);}
inline void glGetProgramLocalParameterIuivNV(GLenum target,GLuint index,GLuint* params){this->_getTable()->glGetProgramLocalParameterIuivNV(target,index,params);}
inline void glGetProgramNamedParameterdvNV(GLuint id,GLsizei len,const GLubyte* name,GLdouble* params){this->_getTable()->glGetProgramNamedParameterdvNV(id,len,name,params);}
inline void glGetProgramNamedParameterfvNV(GLuint id,GLsizei len,const GLubyte* name,GLfloat* params){this->_getTable()->glGetProgramNamedParameterfvNV(id,len,name,params);}
inline void glGetProgramParameterdvNV(GLenum target,GLuint index,GLenum pname,GLdouble* params){this->_getTable()->glGetProgramParameterdvNV(target,index,pname,params);}
inline void glGetProgramParameterfvNV(GLenum target,GLuint index,GLenum pname,GLfloat* params){this->_getTable()->glGetProgramParameterfvNV(target,index,pname,params);}
inline void glGetProgramPipelineInfoLog(GLuint pipeline,GLsizei bufSize,GLsizei* length,GLchar* infoLog){this->_getTable()->glGetProgramPipelineInfoLog(pipeline,bufSize,length,infoLog);}
inline void glGetProgramPipelineiv(GLuint pipeline,GLenum pname,GLint* params){this->_getTable()->glGetProgramPipelineiv(pipeline,pname,params);}
inline void glGetProgramResourcefvNV(GLuint program,GLenum programInterface,GLuint index,GLsizei propCount,const GLenum* props,GLsizei bufSize,GLsizei* length,GLfloat* params){this->_getTable()->glGetProgramResourcefvNV(program,programInterface,index,propCount,props,bufSize,length,params);}
inline void glGetProgramResourceiv(GLuint program,GLenum programInterface,GLuint index,GLsizei propCount,const GLenum* props,GLsizei bufSize,GLsizei* length,GLint* params){this->_getTable()->glGetProgramResourceiv(program,programInterface,index,propCount,props,bufSize,length,params);}
inline void glGetProgramResourceName(GLuint program,GLenum programInterface,GLuint index,GLsizei bufSize,GLsizei* length,GLchar* name){this->_getTable()->glGetProgramResourceName(program,programInterface,index,bufSize,length,name);}
inline void glGetProgramStageiv(GLuint program,GLenum shadertype,GLenum pname,GLint* values){this->_getTable()->glGetProgramStageiv(program,shadertype,pname,values);}
inline void glGetProgramStringARB(GLenum target,GLenum pname,void* string){this->_getTable()->glGetProgramStringARB(target,pname,string);}
inline void glGetProgramStringNV(GLuint id,GLenum pname,GLubyte* program){this->_getTable()->glGetProgramStringNV(id,pname,program);}
inline void glGetProgramSubroutineParameteruivNV(GLenum target,GLuint index,GLuint* param){this->_getTable()->glGetProgramSubroutineParameteruivNV(target,index,param);}
inline void glGetQueryBufferObjecti64v(GLuint id,GLuint buffer,GLenum pname,GLintptr offset){this->_getTable()->glGetQueryBufferObjecti64v(id,buffer,pname,offset);}
inline void glGetQueryBufferObjectiv(GLuint id,GLuint buffer,GLenum pname,GLintptr offset){this->_getTable()->glGetQueryBufferObjectiv(id,buffer,pname,offset);}
inline void glGetQueryBufferObjectui64v(GLuint id,GLuint buffer,GLenum pname,GLintptr offset){this->_getTable()->glGetQueryBufferObjectui64v(id,buffer,pname,offset);}
inline void glGetQueryBufferObjectuiv(GLuint id,GLuint buffer,GLenum pname,GLintptr offset){this->_getTable()->glGetQueryBufferObjectuiv(id,buffer,pname,offset);}
inline void glGetQueryIndexediv(GLenum target,GLuint index,GLenum pname,GLint* params){this->_getTable()->glGetQueryIndexediv(target,index,pname,params);}
inline void glGetQueryivARB(GLenum target,GLenum pname,GLint* params){this->_getTable()->glGetQueryivARB(target,pname,params);}
inline void glGetQueryiv(GLenum target,GLenum pname,GLint* params){this->_getTable()->glGetQueryiv(target,pname,params);}
inline void glGetQueryObjecti64vEXT(GLuint id,GLenum pname,GLint64* params){this->_getTable()->glGetQueryObjecti64vEXT(id,pname,params);}
inline void glGetQueryObjecti64v(GLuint id,GLenum pname,GLint64* params){this->_getTable()->glGetQueryObjecti64v(id,pname,params);}
inline void glGetQueryObjectivARB(GLuint id,GLenum pname,GLint* params){this->_getTable()->glGetQueryObjectivARB(id,pname,params);}
inline void glGetQueryObjectiv(GLuint id,GLenum pname,GLint* params){this->_getTable()->glGetQueryObjectiv(id,pname,params);}
inline void glGetQueryObjectui64vEXT(GLuint id,GLenum pname,GLuint64* params){this->_getTable()->glGetQueryObjectui64vEXT(id,pname,params);}
inline void glGetQueryObjectui64v(GLuint id,GLenum pname,GLuint64* params){this->_getTable()->glGetQueryObjectui64v(id,pname,params);}
inline void glGetQueryObjectuivARB(GLuint id,GLenum pname,GLuint* params){this->_getTable()->glGetQueryObjectuivARB(id,pname,params);}
inline void glGetQueryObjectuiv(GLuint id,GLenum pname,GLuint* params){this->_getTable()->glGetQueryObjectuiv(id,pname,params);}
inline void glGetRenderbufferParameterivEXT(GLenum target,GLenum pname,GLint* params){this->_getTable()->glGetRenderbufferParameterivEXT(target,pname,params);}
inline void glGetRenderbufferParameteriv(GLenum target,GLenum pname,GLint* params){this->_getTable()->glGetRenderbufferParameteriv(target,pname,params);}
inline void glGetSamplerParameterfv(GLuint sampler,GLenum pname,GLfloat* params){this->_getTable()->glGetSamplerParameterfv(sampler,pname,params);}
inline void glGetSamplerParameterIiv(GLuint sampler,GLenum pname,GLint* params){this->_getTable()->glGetSamplerParameterIiv(sampler,pname,params);}
inline void glGetSamplerParameterIuiv(GLuint sampler,GLenum pname,GLuint* params){this->_getTable()->glGetSamplerParameterIuiv(sampler,pname,params);}
inline void glGetSamplerParameteriv(GLuint sampler,GLenum pname,GLint* params){this->_getTable()->glGetSamplerParameteriv(sampler,pname,params);}
inline void glGetSeparableFilterEXT(GLenum target,GLenum format,GLenum type,void* row,void* column,void* span){this->_getTable()->glGetSeparableFilterEXT(target,format,type,row,column,span);}
inline void glGetSeparableFilter(GLenum target,GLenum format,GLenum type,GLvoid* row,GLvoid* column,GLvoid* span){this->_getTable()->glGetSeparableFilter(target,format,type,row,column,span);}
inline void glGetShaderInfoLog(GLuint shader,GLsizei bufSize,GLsizei* length,GLchar* infoLog){this->_getTable()->glGetShaderInfoLog(shader,bufSize,length,infoLog);}
inline void glGetShaderiv(GLuint shader,GLenum pname,GLint* params){this->_getTable()->glGetShaderiv(shader,pname,params);}
inline void glGetShaderPrecisionFormat(GLenum shadertype,GLenum precisiontype,GLint* range,GLint* precision){this->_getTable()->glGetShaderPrecisionFormat(shadertype,precisiontype,range,precision);}
inline void glGetShaderSourceARB(GLhandleARB obj,GLsizei maxLength,GLsizei* length,GLcharARB* source){this->_getTable()->glGetShaderSourceARB(obj,maxLength,length,source);}
inline void glGetShaderSource(GLuint shader,GLsizei bufSize,GLsizei* length,GLchar* source){this->_getTable()->glGetShaderSource(shader,bufSize,length,source);}
inline void glGetSharpenTexFuncSGIS(GLenum target,GLfloat* points){this->_getTable()->glGetSharpenTexFuncSGIS(target,points);}
inline void glGetSynciv(GLsync sync,GLenum pname,GLsizei bufSize,GLsizei* length,GLint* values){this->_getTable()->glGetSynciv(sync,pname,bufSize,length,values);}
inline void glGetTexBumpParameterfvATI(GLenum pname,GLfloat* param){this->_getTable()->glGetTexBumpParameterfvATI(pname,param);}
inline void glGetTexBumpParameterivATI(GLenum pname,GLint* param){this->_getTable()->glGetTexBumpParameterivATI(pname,param);}
inline void glGetTexEnvfv(GLenum target,GLenum pname,GLfloat* params){this->_getTable()->glGetTexEnvfv(target,pname,params);}
inline void glGetTexEnviv(GLenum target,GLenum pname,GLint* params){this->_getTable()->glGetTexEnviv(target,pname,params);}
inline void glGetTexEnvxvOES(GLenum target,GLenum pname,GLfixed* params){this->_getTable()->glGetTexEnvxvOES(target,pname,params);}
inline void glGetTexFilterFuncSGIS(GLenum target,GLenum filter,GLfloat* weights){this->_getTable()->glGetTexFilterFuncSGIS(target,filter,weights);}
inline void glGetTexGendv(GLenum coord,GLenum pname,GLdouble* params){this->_getTable()->glGetTexGendv(coord,pname,params);}
inline void glGetTexGenfv(GLenum coord,GLenum pname,GLfloat* params){this->_getTable()->glGetTexGenfv(coord,pname,params);}
inline void glGetTexGeniv(GLenum coord,GLenum pname,GLint* params){this->_getTable()->glGetTexGeniv(coord,pname,params);}
inline void glGetTexGenxvOES(GLenum coord,GLenum pname,GLfixed* params){this->_getTable()->glGetTexGenxvOES(coord,pname,params);}
inline void glGetTexImage(GLenum target,GLint level,GLenum format,GLenum type,GLvoid* pixels){this->_getTable()->glGetTexImage(target,level,format,type,pixels);}
inline void glGetTexLevelParameterfv(GLenum target,GLint level,GLenum pname,GLfloat* params){this->_getTable()->glGetTexLevelParameterfv(target,level,pname,params);}
inline void glGetTexLevelParameteriv(GLenum target,GLint level,GLenum pname,GLint* params){this->_getTable()->glGetTexLevelParameteriv(target,level,pname,params);}
inline void glGetTexLevelParameterxvOES(GLenum target,GLint level,GLenum pname,GLfixed* params){this->_getTable()->glGetTexLevelParameterxvOES(target,level,pname,params);}
inline void glGetTexParameterfv(GLenum target,GLenum pname,GLfloat* params){this->_getTable()->glGetTexParameterfv(target,pname,params);}
inline void glGetTexParameterIivEXT(GLenum target,GLenum pname,GLint* params){this->_getTable()->glGetTexParameterIivEXT(target,pname,params);}
inline void glGetTexParameterIiv(GLenum target,GLenum pname,GLint* params){this->_getTable()->glGetTexParameterIiv(target,pname,params);}
inline void glGetTexParameterIuivEXT(GLenum target,GLenum pname,GLuint* params){this->_getTable()->glGetTexParameterIuivEXT(target,pname,params);}
inline void glGetTexParameterIuiv(GLenum target,GLenum pname,GLuint* params){this->_getTable()->glGetTexParameterIuiv(target,pname,params);}
inline void glGetTexParameteriv(GLenum target,GLenum pname,GLint* params){this->_getTable()->glGetTexParameteriv(target,pname,params);}
inline void glGetTexParameterPointervAPPLE(GLenum target,GLenum pname,void** params){this->_getTable()->glGetTexParameterPointervAPPLE(target,pname,params);}
inline void glGetTexParameterxvOES(GLenum target,GLenum pname,GLfixed* params){this->_getTable()->glGetTexParameterxvOES(target,pname,params);}
inline void glGetTextureImageEXT(GLuint texture,GLenum target,GLint level,GLenum format,GLenum type,void* pixels){this->_getTable()->glGetTextureImageEXT(texture,target,level,format,type,pixels);}
inline void glGetTextureImage(GLuint texture,GLint level,GLenum format,GLenum type,GLsizei bufSize,void* pixels){this->_getTable()->glGetTextureImage(texture,level,format,type,bufSize,pixels);}
inline void glGetTextureLevelParameterfvEXT(GLuint texture,GLenum target,GLint level,GLenum pname,GLfloat* params){this->_getTable()->glGetTextureLevelParameterfvEXT(texture,target,level,pname,params);}
inline void glGetTextureLevelParameterfv(GLuint texture,GLint level,GLenum pname,GLfloat* params){this->_getTable()->glGetTextureLevelParameterfv(texture,level,pname,params);}
inline void glGetTextureLevelParameterivEXT(GLuint texture,GLenum target,GLint level,GLenum pname,GLint* params){this->_getTable()->glGetTextureLevelParameterivEXT(texture,target,level,pname,params);}
inline void glGetTextureLevelParameteriv(GLuint texture,GLint level,GLenum pname,GLint* params){this->_getTable()->glGetTextureLevelParameteriv(texture,level,pname,params);}
inline void glGetTextureParameterfvEXT(GLuint texture,GLenum target,GLenum pname,GLfloat* params){this->_getTable()->glGetTextureParameterfvEXT(texture,target,pname,params);}
inline void glGetTextureParameterfv(GLuint texture,GLenum pname,GLfloat* params){this->_getTable()->glGetTextureParameterfv(texture,pname,params);}
inline void glGetTextureParameterIivEXT(GLuint texture,GLenum target,GLenum pname,GLint* params){this->_getTable()->glGetTextureParameterIivEXT(texture,target,pname,params);}
inline void glGetTextureParameterIiv(GLuint texture,GLenum pname,GLint* params){this->_getTable()->glGetTextureParameterIiv(texture,pname,params);}
inline void glGetTextureParameterIuivEXT(GLuint texture,GLenum target,GLenum pname,GLuint* params){this->_getTable()->glGetTextureParameterIuivEXT(texture,target,pname,params);}
inline void glGetTextureParameterIuiv(GLuint texture,GLenum pname,GLuint* params){this->_getTable()->glGetTextureParameterIuiv(texture,pname,params);}
inline void glGetTextureParameterivEXT(GLuint texture,GLenum target,GLenum pname,GLint* params){this->_getTable()->glGetTextureParameterivEXT(texture,target,pname,params);}
inline void glGetTextureParameteriv(GLuint texture,GLenum pname,GLint* params){this->_getTable()->glGetTextureParameteriv(texture,pname,params);}
inline void glGetTextureSubImage(GLuint texture,GLint level,GLint xoffset,GLint yoffset,GLint zoffset,GLsizei width,GLsizei height,GLsizei depth,GLenum format,GLenum type,GLsizei bufSize,void* pixels){this->_getTable()->glGetTextureSubImage(texture,level,xoffset,yoffset,zoffset,width,height,depth,format,type,bufSize,pixels);}
inline void glGetTrackMatrixivNV(GLenum target,GLuint address,GLenum pname,GLint* params){this->_getTable()->glGetTrackMatrixivNV(target,address,pname,params);}
inline void glGetTransformFeedbacki64_v(GLuint xfb,GLenum pname,GLuint index,GLint64* param){this->_getTable()->glGetTransformFeedbacki64_v(xfb,pname,index,param);}
inline void glGetTransformFeedbackiv(GLuint xfb,GLenum pname,GLint* param){this->_getTable()->glGetTransformFeedbackiv(xfb,pname,param);}
inline void glGetTransformFeedbacki_v(GLuint xfb,GLenum pname,GLuint index,GLint* param){this->_getTable()->glGetTransformFeedbacki_v(xfb,pname,index,param);}
inline void glGetTransformFeedbackVaryingEXT(GLuint program,GLuint index,GLsizei bufSize,GLsizei* length,GLsizei* size,GLenum* type,GLchar* name){this->_getTable()->glGetTransformFeedbackVaryingEXT(program,index,bufSize,length,size,type,name);}
inline void glGetTransformFeedbackVarying(GLuint program,GLuint index,GLsizei bufSize,GLsizei* length,GLsizei* size,GLenum* type,GLchar* name){this->_getTable()->glGetTransformFeedbackVarying(program,index,bufSize,length,size,type,name);}
inline void glGetTransformFeedbackVaryingNV(GLuint program,GLuint index,GLint* location){this->_getTable()->glGetTransformFeedbackVaryingNV(program,index,location);}
inline void glGetUniformdv(GLuint program,GLint location,GLdouble* params){this->_getTable()->glGetUniformdv(program,location,params);}
inline void glGetUniformfvARB(GLhandleARB programObj,GLint location,GLfloat* params){this->_getTable()->glGetUniformfvARB(programObj,location,params);}
inline void glGetUniformfv(GLuint program,GLint location,GLfloat* params){this->_getTable()->glGetUniformfv(program,location,params);}
inline void glGetUniformi64vARB(GLuint program,GLint location,GLint64* params){this->_getTable()->glGetUniformi64vARB(program,location,params);}
inline void glGetUniformi64vNV(GLuint program,GLint location,GLint64EXT* params){this->_getTable()->glGetUniformi64vNV(program,location,params);}
inline void glGetUniformIndices(GLuint program,GLsizei uniformCount,const GLchar*const* uniformNames,GLuint* uniformIndices){this->_getTable()->glGetUniformIndices(program,uniformCount,uniformNames,uniformIndices);}
inline void glGetUniformivARB(GLhandleARB programObj,GLint location,GLint* params){this->_getTable()->glGetUniformivARB(programObj,location,params);}
inline void glGetUniformiv(GLuint program,GLint location,GLint* params){this->_getTable()->glGetUniformiv(program,location,params);}
inline void glGetUniformSubroutineuiv(GLenum shadertype,GLint location,GLuint* params){this->_getTable()->glGetUniformSubroutineuiv(shadertype,location,params);}
inline void glGetUniformui64vARB(GLuint program,GLint location,GLuint64* params){this->_getTable()->glGetUniformui64vARB(program,location,params);}
inline void glGetUniformui64vNV(GLuint program,GLint location,GLuint64EXT* params){this->_getTable()->glGetUniformui64vNV(program,location,params);}
inline void glGetUniformuivEXT(GLuint program,GLint location,GLuint* params){this->_getTable()->glGetUniformuivEXT(program,location,params);}
inline void glGetUniformuiv(GLuint program,GLint location,GLuint* params){this->_getTable()->glGetUniformuiv(program,location,params);}
inline void glGetVariantArrayObjectfvATI(GLuint id,GLenum pname,GLfloat* params){this->_getTable()->glGetVariantArrayObjectfvATI(id,pname,params);}
inline void glGetVariantArrayObjectivATI(GLuint id,GLenum pname,GLint* params){this->_getTable()->glGetVariantArrayObjectivATI(id,pname,params);}
inline void glGetVariantBooleanvEXT(GLuint id,GLenum value,GLboolean* data){this->_getTable()->glGetVariantBooleanvEXT(id,value,data);}
inline void glGetVariantFloatvEXT(GLuint id,GLenum value,GLfloat* data){this->_getTable()->glGetVariantFloatvEXT(id,value,data);}
inline void glGetVariantIntegervEXT(GLuint id,GLenum value,GLint* data){this->_getTable()->glGetVariantIntegervEXT(id,value,data);}
inline void glGetVariantPointervEXT(GLuint id,GLenum value,void** data){this->_getTable()->glGetVariantPointervEXT(id,value,data);}
inline void glGetVertexArrayIndexed64iv(GLuint vaobj,GLuint index,GLenum pname,GLint64* param){this->_getTable()->glGetVertexArrayIndexed64iv(vaobj,index,pname,param);}
inline void glGetVertexArrayIndexediv(GLuint vaobj,GLuint index,GLenum pname,GLint* param){this->_getTable()->glGetVertexArrayIndexediv(vaobj,index,pname,param);}
inline void glGetVertexArrayIntegeri_vEXT(GLuint vaobj,GLuint index,GLenum pname,GLint* param){this->_getTable()->glGetVertexArrayIntegeri_vEXT(vaobj,index,pname,param);}
inline void glGetVertexArrayIntegervEXT(GLuint vaobj,GLenum pname,GLint* param){this->_getTable()->glGetVertexArrayIntegervEXT(vaobj,pname,param);}
inline void glGetVertexArrayiv(GLuint vaobj,GLenum pname,GLint* param){this->_getTable()->glGetVertexArrayiv(vaobj,pname,param);}
inline void glGetVertexArrayPointeri_vEXT(GLuint vaobj,GLuint index,GLenum pname,void** param){this->_getTable()->glGetVertexArrayPointeri_vEXT(vaobj,index,pname,param);}
inline void glGetVertexArrayPointervEXT(GLuint vaobj,GLenum pname,void** param){this->_getTable()->glGetVertexArrayPointervEXT(vaobj,pname,param);}
inline void glGetVertexAttribArrayObjectfvATI(GLuint index,GLenum pname,GLfloat* params){this->_getTable()->glGetVertexAttribArrayObjectfvATI(index,pname,params);}
inline void glGetVertexAttribArrayObjectivATI(GLuint index,GLenum pname,GLint* params){this->_getTable()->glGetVertexAttribArrayObjectivATI(index,pname,params);}
inline void glGetVertexAttribdvARB(GLuint index,GLenum pname,GLdouble* params){this->_getTable()->glGetVertexAttribdvARB(index,pname,params);}
inline void glGetVertexAttribdv(GLuint index,GLenum pname,GLdouble* params){this->_getTable()->glGetVertexAttribdv(index,pname,params);}
inline void glGetVertexAttribdvNV(GLuint index,GLenum pname,GLdouble* params){this->_getTable()->glGetVertexAttribdvNV(index,pname,params);}
inline void glGetVertexAttribfvARB(GLuint index,GLenum pname,GLfloat* params){this->_getTable()->glGetVertexAttribfvARB(index,pname,params);}
inline void glGetVertexAttribfv(GLuint index,GLenum pname,GLfloat* params){this->_getTable()->glGetVertexAttribfv(index,pname,params);}
inline void glGetVertexAttribfvNV(GLuint index,GLenum pname,GLfloat* params){this->_getTable()->glGetVertexAttribfvNV(index,pname,params);}
inline void glGetVertexAttribIivEXT(GLuint index,GLenum pname,GLint* params){this->_getTable()->glGetVertexAttribIivEXT(index,pname,params);}
inline void glGetVertexAttribIiv(GLuint index,GLenum pname,GLint* params){this->_getTable()->glGetVertexAttribIiv(index,pname,params);}
inline void glGetVertexAttribIuivEXT(GLuint index,GLenum pname,GLuint* params){this->_getTable()->glGetVertexAttribIuivEXT(index,pname,params);}
inline void glGetVertexAttribIuiv(GLuint index,GLenum pname,GLuint* params){this->_getTable()->glGetVertexAttribIuiv(index,pname,params);}
inline void glGetVertexAttribivARB(GLuint index,GLenum pname,GLint* params){this->_getTable()->glGetVertexAttribivARB(index,pname,params);}
inline void glGetVertexAttribiv(GLuint index,GLenum pname,GLint* params){this->_getTable()->glGetVertexAttribiv(index,pname,params);}
inline void glGetVertexAttribivNV(GLuint index,GLenum pname,GLint* params){this->_getTable()->glGetVertexAttribivNV(index,pname,params);}
inline void glGetVertexAttribLdvEXT(GLuint index,GLenum pname,GLdouble* params){this->_getTable()->glGetVertexAttribLdvEXT(index,pname,params);}
inline void glGetVertexAttribLdv(GLuint index,GLenum pname,GLdouble* params){this->_getTable()->glGetVertexAttribLdv(index,pname,params);}
inline void glGetVertexAttribLi64vNV(GLuint index,GLenum pname,GLint64EXT* params){this->_getTable()->glGetVertexAttribLi64vNV(index,pname,params);}
inline void glGetVertexAttribLui64vARB(GLuint index,GLenum pname,GLuint64EXT* params){this->_getTable()->glGetVertexAttribLui64vARB(index,pname,params);}
inline void glGetVertexAttribLui64vNV(GLuint index,GLenum pname,GLuint64EXT* params){this->_getTable()->glGetVertexAttribLui64vNV(index,pname,params);}
inline void glGetVertexAttribPointervARB(GLuint index,GLenum pname,void** pointer){this->_getTable()->glGetVertexAttribPointervARB(index,pname,pointer);}
inline void glGetVertexAttribPointerv(GLuint index,GLenum pname,void** pointer){this->_getTable()->glGetVertexAttribPointerv(index,pname,pointer);}
inline void glGetVertexAttribPointervNV(GLuint index,GLenum pname,void** pointer){this->_getTable()->glGetVertexAttribPointervNV(index,pname,pointer);}
inline void glGetVideoCaptureivNV(GLuint video_capture_slot,GLenum pname,GLint* params){this->_getTable()->glGetVideoCaptureivNV(video_capture_slot,pname,params);}
inline void glGetVideoCaptureStreamdvNV(GLuint video_capture_slot,GLuint stream,GLenum pname,GLdouble* params){this->_getTable()->glGetVideoCaptureStreamdvNV(video_capture_slot,stream,pname,params);}
inline void glGetVideoCaptureStreamfvNV(GLuint video_capture_slot,GLuint stream,GLenum pname,GLfloat* params){this->_getTable()->glGetVideoCaptureStreamfvNV(video_capture_slot,stream,pname,params);}
inline void glGetVideoCaptureStreamivNV(GLuint video_capture_slot,GLuint stream,GLenum pname,GLint* params){this->_getTable()->glGetVideoCaptureStreamivNV(video_capture_slot,stream,pname,params);}
inline void glGetVideoi64vNV(GLuint video_slot,GLenum pname,GLint64EXT* params){this->_getTable()->glGetVideoi64vNV(video_slot,pname,params);}
inline void glGetVideoivNV(GLuint video_slot,GLenum pname,GLint* params){this->_getTable()->glGetVideoivNV(video_slot,pname,params);}
inline void glGetVideoui64vNV(GLuint video_slot,GLenum pname,GLuint64EXT* params){this->_getTable()->glGetVideoui64vNV(video_slot,pname,params);}
inline void glGetVideouivNV(GLuint video_slot,GLenum pname,GLuint* params){this->_getTable()->glGetVideouivNV(video_slot,pname,params);}
inline void glGlobalAlphaFactorbSUN(GLbyte factor){this->_getTable()->glGlobalAlphaFactorbSUN(factor);}
inline void glGlobalAlphaFactordSUN(GLdouble factor){this->_getTable()->glGlobalAlphaFactordSUN(factor);}
inline void glGlobalAlphaFactorfSUN(GLfloat factor){this->_getTable()->glGlobalAlphaFactorfSUN(factor);}
inline void glGlobalAlphaFactoriSUN(GLint factor){this->_getTable()->glGlobalAlphaFactoriSUN(factor);}
inline void glGlobalAlphaFactorsSUN(GLshort factor){this->_getTable()->glGlobalAlphaFactorsSUN(factor);}
inline void glGlobalAlphaFactorubSUN(GLubyte factor){this->_getTable()->glGlobalAlphaFactorubSUN(factor);}
inline void glGlobalAlphaFactoruiSUN(GLuint factor){this->_getTable()->glGlobalAlphaFactoruiSUN(factor);}
inline void glGlobalAlphaFactorusSUN(GLushort factor){this->_getTable()->glGlobalAlphaFactorusSUN(factor);}
inline void glHint(GLenum target,GLenum mode){this->_getTable()->glHint(target,mode);}
inline void glHintPGI(GLenum target,GLint mode){this->_getTable()->glHintPGI(target,mode);}
inline void glHistogramEXT(GLenum target,GLsizei width,GLenum internalformat,GLboolean sink){this->_getTable()->glHistogramEXT(target,width,internalformat,sink);}
inline void glHistogram(GLenum target,GLsizei width,GLenum internalformat,GLboolean sink){this->_getTable()->glHistogram(target,width,internalformat,sink);}
inline void glIglooInterfaceSGIX(GLenum pname,const void* params){this->_getTable()->glIglooInterfaceSGIX(pname,params);}
inline void glImageTransformParameterfHP(GLenum target,GLenum pname,GLfloat param){this->_getTable()->glImageTransformParameterfHP(target,pname,param);}
inline void glImageTransformParameterfvHP(GLenum target,GLenum pname,const GLfloat* params){this->_getTable()->glImageTransformParameterfvHP(target,pname,params);}
inline void glImageTransformParameteriHP(GLenum target,GLenum pname,GLint param){this->_getTable()->glImageTransformParameteriHP(target,pname,param);}
inline void glImageTransformParameterivHP(GLenum target,GLenum pname,const GLint* params){this->_getTable()->glImageTransformParameterivHP(target,pname,params);}
inline void glIndexd(GLdouble c){this->_getTable()->glIndexd(c);}
inline void glIndexdv(const GLdouble* c){this->_getTable()->glIndexdv(c);}
inline void glIndexf(GLfloat c){this->_getTable()->glIndexf(c);}
inline void glIndexFormatNV(GLenum type,GLsizei stride){this->_getTable()->glIndexFormatNV(type,stride);}
inline void glIndexFuncEXT(GLenum func,GLclampf ref){this->_getTable()->glIndexFuncEXT(func,ref);}
inline void glIndexfv(const GLfloat* c){this->_getTable()->glIndexfv(c);}
inline void glIndexi(GLint c){this->_getTable()->glIndexi(c);}
inline void glIndexiv(const GLint* c){this->_getTable()->glIndexiv(c);}
inline void glIndexMask(GLuint mask){this->_getTable()->glIndexMask(mask);}
inline void glIndexMaterialEXT(GLenum face,GLenum mode){this->_getTable()->glIndexMaterialEXT(face,mode);}
inline void glIndexPointerEXT(GLenum type,GLsizei stride,GLsizei count,const void* pointer){this->_getTable()->glIndexPointerEXT(type,stride,count,pointer);}
inline void glIndexPointer(GLenum type,GLsizei stride,const GLvoid* ptr){this->_getTable()->glIndexPointer(type,stride,ptr);}
inline void glIndexPointerListIBM(GLenum type,GLint stride,const void** pointer,GLint ptrstride){this->_getTable()->glIndexPointerListIBM(type,stride,pointer,ptrstride);}
inline void glIndexs(GLshort c){this->_getTable()->glIndexs(c);}
inline void glIndexsv(const GLshort* c){this->_getTable()->glIndexsv(c);}
inline void glIndexub(GLubyte c){this->_getTable()->glIndexub(c);}
inline void glIndexubv(const GLubyte* c){this->_getTable()->glIndexubv(c);}
inline void glIndexxOES(GLfixed component){this->_getTable()->glIndexxOES(component);}
inline void glIndexxvOES(const GLfixed* component){this->_getTable()->glIndexxvOES(component);}
inline void glInitNames(){this->_getTable()->glInitNames();}
inline void glInsertComponentEXT(GLuint res,GLuint src,GLuint num){this->_getTable()->glInsertComponentEXT(res,src,num);}
inline void glInsertEventMarkerEXT(GLsizei length,const GLchar* marker){this->_getTable()->glInsertEventMarkerEXT(length,marker);}
inline void glInstrumentsBufferSGIX(GLsizei size,GLint* buffer){this->_getTable()->glInstrumentsBufferSGIX(size,buffer);}
inline void glInterleavedArrays(GLenum format,GLsizei stride,const GLvoid* pointer){this->_getTable()->glInterleavedArrays(format,stride,pointer);}
inline void glInterpolatePathsNV(GLuint resultPath,GLuint pathA,GLuint pathB,GLfloat weight){this->_getTable()->glInterpolatePathsNV(resultPath,pathA,pathB,weight);}
inline void glInvalidateBufferData(GLuint buffer){this->_getTable()->glInvalidateBufferData(buffer);}
inline void glInvalidateBufferSubData(GLuint buffer,GLintptr offset,GLsizeiptr length){this->_getTable()->glInvalidateBufferSubData(buffer,offset,length);}
inline void glInvalidateFramebuffer(GLenum target,GLsizei numAttachments,const GLenum* attachments){this->_getTable()->glInvalidateFramebuffer(target,numAttachments,attachments);}
inline void glInvalidateNamedFramebufferData(GLuint framebuffer,GLsizei numAttachments,const GLenum* attachments){this->_getTable()->glInvalidateNamedFramebufferData(framebuffer,numAttachments,attachments);}
inline void glInvalidateNamedFramebufferSubData(GLuint framebuffer,GLsizei numAttachments,const GLenum* attachments,GLint x,GLint y,GLsizei width,GLsizei height){this->_getTable()->glInvalidateNamedFramebufferSubData(framebuffer,numAttachments,attachments,x,y,width,height);}
inline void glInvalidateSubFramebuffer(GLenum target,GLsizei numAttachments,const GLenum* attachments,GLint x,GLint y,GLsizei width,GLsizei height){this->_getTable()->glInvalidateSubFramebuffer(target,numAttachments,attachments,x,y,width,height);}
inline void glInvalidateTexImage(GLuint texture,GLint level){this->_getTable()->glInvalidateTexImage(texture,level);}
inline void glInvalidateTexSubImage(GLuint texture,GLint level,GLint xoffset,GLint yoffset,GLint zoffset,GLsizei width,GLsizei height,GLsizei depth){this->_getTable()->glInvalidateTexSubImage(texture,level,xoffset,yoffset,zoffset,width,height,depth);}
inline void glLabelObjectEXT(GLenum type,GLuint object,GLsizei length,const GLchar* label){this->_getTable()->glLabelObjectEXT(type,object,length,label);}
inline void glLightEnviSGIX(GLenum pname,GLint param){this->_getTable()->glLightEnviSGIX(pname,param);}
inline void glLightf(GLenum light,GLenum pname,GLfloat param){this->_getTable()->glLightf(light,pname,param);}
inline void glLightfv(GLenum light,GLenum pname,const GLfloat* params){this->_getTable()->glLightfv(light,pname,params);}
inline void glLighti(GLenum light,GLenum pname,GLint param){this->_getTable()->glLighti(light,pname,param);}
inline void glLightiv(GLenum light,GLenum pname,const GLint* params){this->_getTable()->glLightiv(light,pname,params);}
inline void glLightModelf(GLenum pname,GLfloat param){this->_getTable()->glLightModelf(pname,param);}
inline void glLightModelfv(GLenum pname,const GLfloat* params){this->_getTable()->glLightModelfv(pname,params);}
inline void glLightModeli(GLenum pname,GLint param){this->_getTable()->glLightModeli(pname,param);}
inline void glLightModeliv(GLenum pname,const GLint* params){this->_getTable()->glLightModeliv(pname,params);}
inline void glLightModelxOES(GLenum pname,GLfixed param){this->_getTable()->glLightModelxOES(pname,param);}
inline void glLightModelxvOES(GLenum pname,const GLfixed* param){this->_getTable()->glLightModelxvOES(pname,param);}
inline void glLightxOES(GLenum light,GLenum pname,GLfixed param){this->_getTable()->glLightxOES(light,pname,param);}
inline void glLightxvOES(GLenum light,GLenum pname,const GLfixed* params){this->_getTable()->glLightxvOES(light,pname,params);}
inline void glLineStipple(GLint factor,GLushort pattern){this->_getTable()->glLineStipple(factor,pattern);}
inline void glLineWidth(GLfloat width){this->_getTable()->glLineWidth(width);}
inline void glLineWidthxOES(GLfixed width){this->_getTable()->glLineWidthxOES(width);}
inline void glLinkProgramARB(GLhandleARB programObj){this->_getTable()->glLinkProgramARB(programObj);}
inline void glLinkProgram(GLuint program){this->_getTable()->glLinkProgram(program);}
inline void glListBase(GLuint base){this->_getTable()->glListBase(base);}
inline void glListDrawCommandsStatesClientNV(GLuint list,GLuint segment,const void** indirects,const GLsizei* sizes,const GLuint* states,const GLuint* fbos,GLuint count){this->_getTable()->glListDrawCommandsStatesClientNV(list,segment,indirects,sizes,states,fbos,count);}
inline void glListParameterfSGIX(GLuint list,GLenum pname,GLfloat param){this->_getTable()->glListParameterfSGIX(list,pname,param);}
inline void glListParameterfvSGIX(GLuint list,GLenum pname,const GLfloat* params){this->_getTable()->glListParameterfvSGIX(list,pname,params);}
inline void glListParameteriSGIX(GLuint list,GLenum pname,GLint param){this->_getTable()->glListParameteriSGIX(list,pname,param);}
inline void glListParameterivSGIX(GLuint list,GLenum pname,const GLint* params){this->_getTable()->glListParameterivSGIX(list,pname,params);}
inline void glLoadIdentity(){this->_getTable()->glLoadIdentity();}
inline void glLoadIdentityDeformationMapSGIX(GLbitfield mask){this->_getTable()->glLoadIdentityDeformationMapSGIX(mask);}
inline void glLoadMatrixd(const GLdouble* m){this->_getTable()->glLoadMatrixd(m);}
inline void glLoadMatrixf(const GLfloat* m){this->_getTable()->glLoadMatrixf(m);}
inline void glLoadMatrixxOES(const GLfixed* m){this->_getTable()->glLoadMatrixxOES(m);}
inline void glLoadName(GLuint name){this->_getTable()->glLoadName(name);}
inline void glLoadProgramNV(GLenum target,GLuint id,GLsizei len,const GLubyte* program){this->_getTable()->glLoadProgramNV(target,id,len,program);}
inline void glLoadTransposeMatrixdARB(const GLdouble* m){this->_getTable()->glLoadTransposeMatrixdARB(m);}
inline void glLoadTransposeMatrixd(const GLdouble m[16]){this->_getTable()->glLoadTransposeMatrixd(m[16]);}
inline void glLoadTransposeMatrixfARB(const GLfloat* m){this->_getTable()->glLoadTransposeMatrixfARB(m);}
inline void glLoadTransposeMatrixf(const GLfloat m[16]){this->_getTable()->glLoadTransposeMatrixf(m[16]);}
inline void glLoadTransposeMatrixxOES(const GLfixed* m){this->_getTable()->glLoadTransposeMatrixxOES(m);}
inline void glLockArraysEXT(GLint first,GLsizei count){this->_getTable()->glLockArraysEXT(first,count);}
inline void glLogicOp(GLenum opcode){this->_getTable()->glLogicOp(opcode);}
inline void glMakeBufferNonResidentNV(GLenum target){this->_getTable()->glMakeBufferNonResidentNV(target);}
inline void glMakeBufferResidentNV(GLenum target,GLenum access){this->_getTable()->glMakeBufferResidentNV(target,access);}
inline void glMakeImageHandleNonResidentARB(GLuint64 handle){this->_getTable()->glMakeImageHandleNonResidentARB(handle);}
inline void glMakeImageHandleNonResidentNV(GLuint64 handle){this->_getTable()->glMakeImageHandleNonResidentNV(handle);}
inline void glMakeImageHandleResidentARB(GLuint64 handle,GLenum access){this->_getTable()->glMakeImageHandleResidentARB(handle,access);}
inline void glMakeImageHandleResidentNV(GLuint64 handle,GLenum access){this->_getTable()->glMakeImageHandleResidentNV(handle,access);}
inline void glMakeNamedBufferNonResidentNV(GLuint buffer){this->_getTable()->glMakeNamedBufferNonResidentNV(buffer);}
inline void glMakeNamedBufferResidentNV(GLuint buffer,GLenum access){this->_getTable()->glMakeNamedBufferResidentNV(buffer,access);}
inline void glMakeTextureHandleNonResidentARB(GLuint64 handle){this->_getTable()->glMakeTextureHandleNonResidentARB(handle);}
inline void glMakeTextureHandleNonResidentNV(GLuint64 handle){this->_getTable()->glMakeTextureHandleNonResidentNV(handle);}
inline void glMakeTextureHandleResidentARB(GLuint64 handle){this->_getTable()->glMakeTextureHandleResidentARB(handle);}
inline void glMakeTextureHandleResidentNV(GLuint64 handle){this->_getTable()->glMakeTextureHandleResidentNV(handle);}
inline void glMap1d(GLenum target,GLdouble u1,GLdouble u2,GLint stride,GLint order,const GLdouble* points){this->_getTable()->glMap1d(target,u1,u2,stride,order,points);}
inline void glMap1f(GLenum target,GLfloat u1,GLfloat u2,GLint stride,GLint order,const GLfloat* points){this->_getTable()->glMap1f(target,u1,u2,stride,order,points);}
inline void glMap1xOES(GLenum target,GLfixed u1,GLfixed u2,GLint stride,GLint order,GLfixed points){this->_getTable()->glMap1xOES(target,u1,u2,stride,order,points);}
inline void glMap2d(GLenum target,GLdouble u1,GLdouble u2,GLint ustride,GLint uorder,GLdouble v1,GLdouble v2,GLint vstride,GLint vorder,const GLdouble* points){this->_getTable()->glMap2d(target,u1,u2,ustride,uorder,v1,v2,vstride,vorder,points);}
inline void glMap2f(GLenum target,GLfloat u1,GLfloat u2,GLint ustride,GLint uorder,GLfloat v1,GLfloat v2,GLint vstride,GLint vorder,const GLfloat* points){this->_getTable()->glMap2f(target,u1,u2,ustride,uorder,v1,v2,vstride,vorder,points);}
inline void glMap2xOES(GLenum target,GLfixed u1,GLfixed u2,GLint ustride,GLint uorder,GLfixed v1,GLfixed v2,GLint vstride,GLint vorder,GLfixed points){this->_getTable()->glMap2xOES(target,u1,u2,ustride,uorder,v1,v2,vstride,vorder,points);}
inline void* glMapBufferARB(GLenum target,GLenum access){return this->_getTable()->glMapBufferARB(target,access);}
inline void* glMapBuffer(GLenum target,GLenum access){return this->_getTable()->glMapBuffer(target,access);}
inline void* glMapBufferRange(GLenum target,GLintptr offset,GLsizeiptr length,GLbitfield access){return this->_getTable()->glMapBufferRange(target,offset,length,access);}
inline void glMapControlPointsNV(GLenum target,GLuint index,GLenum type,GLsizei ustride,GLsizei vstride,GLint uorder,GLint vorder,GLboolean packed,const void* points){this->_getTable()->glMapControlPointsNV(target,index,type,ustride,vstride,uorder,vorder,packed,points);}
inline void glMapGrid1d(GLint un,GLdouble u1,GLdouble u2){this->_getTable()->glMapGrid1d(un,u1,u2);}
inline void glMapGrid1f(GLint un,GLfloat u1,GLfloat u2){this->_getTable()->glMapGrid1f(un,u1,u2);}
inline void glMapGrid1xOES(GLint n,GLfixed u1,GLfixed u2){this->_getTable()->glMapGrid1xOES(n,u1,u2);}
inline void glMapGrid2d(GLint un,GLdouble u1,GLdouble u2,GLint vn,GLdouble v1,GLdouble v2){this->_getTable()->glMapGrid2d(un,u1,u2,vn,v1,v2);}
inline void glMapGrid2f(GLint un,GLfloat u1,GLfloat u2,GLint vn,GLfloat v1,GLfloat v2){this->_getTable()->glMapGrid2f(un,u1,u2,vn,v1,v2);}
inline void glMapGrid2xOES(GLint n,GLfixed u1,GLfixed u2,GLfixed v1,GLfixed v2){this->_getTable()->glMapGrid2xOES(n,u1,u2,v1,v2);}
inline void* glMapNamedBufferEXT(GLuint buffer,GLenum access){return this->_getTable()->glMapNamedBufferEXT(buffer,access);}
inline void* glMapNamedBuffer(GLuint buffer,GLenum access){return this->_getTable()->glMapNamedBuffer(buffer,access);}
inline void* glMapNamedBufferRangeEXT(GLuint buffer,GLintptr offset,GLsizeiptr length,GLbitfield access){return this->_getTable()->glMapNamedBufferRangeEXT(buffer,offset,length,access);}
inline void* glMapNamedBufferRange(GLuint buffer,GLintptr offset,GLsizeiptr length,GLbitfield access){return this->_getTable()->glMapNamedBufferRange(buffer,offset,length,access);}
inline void* glMapObjectBufferATI(GLuint buffer){return this->_getTable()->glMapObjectBufferATI(buffer);}
inline void glMapParameterfvNV(GLenum target,GLenum pname,const GLfloat* params){this->_getTable()->glMapParameterfvNV(target,pname,params);}
inline void glMapParameterivNV(GLenum target,GLenum pname,const GLint* params){this->_getTable()->glMapParameterivNV(target,pname,params);}
inline void* glMapTexture2DINTEL(GLuint texture,GLint level,GLbitfield access,GLint* stride,GLenum* layout){return this->_getTable()->glMapTexture2DINTEL(texture,level,access,stride,layout);}
inline void glMapVertexAttrib1dAPPLE(GLuint index,GLuint size,GLdouble u1,GLdouble u2,GLint stride,GLint order,const GLdouble* points){this->_getTable()->glMapVertexAttrib1dAPPLE(index,size,u1,u2,stride,order,points);}
inline void glMapVertexAttrib1fAPPLE(GLuint index,GLuint size,GLfloat u1,GLfloat u2,GLint stride,GLint order,const GLfloat* points){this->_getTable()->glMapVertexAttrib1fAPPLE(index,size,u1,u2,stride,order,points);}
inline void glMapVertexAttrib2dAPPLE(GLuint index,GLuint size,GLdouble u1,GLdouble u2,GLint ustride,GLint uorder,GLdouble v1,GLdouble v2,GLint vstride,GLint vorder,const GLdouble* points){this->_getTable()->glMapVertexAttrib2dAPPLE(index,size,u1,u2,ustride,uorder,v1,v2,vstride,vorder,points);}
inline void glMapVertexAttrib2fAPPLE(GLuint index,GLuint size,GLfloat u1,GLfloat u2,GLint ustride,GLint uorder,GLfloat v1,GLfloat v2,GLint vstride,GLint vorder,const GLfloat* points){this->_getTable()->glMapVertexAttrib2fAPPLE(index,size,u1,u2,ustride,uorder,v1,v2,vstride,vorder,points);}
inline void glMaterialf(GLenum face,GLenum pname,GLfloat param){this->_getTable()->glMaterialf(face,pname,param);}
inline void glMaterialfv(GLenum face,GLenum pname,const GLfloat* params){this->_getTable()->glMaterialfv(face,pname,params);}
inline void glMateriali(GLenum face,GLenum pname,GLint param){this->_getTable()->glMateriali(face,pname,param);}
inline void glMaterialiv(GLenum face,GLenum pname,const GLint* params){this->_getTable()->glMaterialiv(face,pname,params);}
inline void glMaterialxOES(GLenum face,GLenum pname,GLfixed param){this->_getTable()->glMaterialxOES(face,pname,param);}
inline void glMaterialxvOES(GLenum face,GLenum pname,const GLfixed* param){this->_getTable()->glMaterialxvOES(face,pname,param);}
inline void glMatrixFrustumEXT(GLenum mode,GLdouble left,GLdouble right,GLdouble bottom,GLdouble top,GLdouble zNear,GLdouble zFar){this->_getTable()->glMatrixFrustumEXT(mode,left,right,bottom,top,zNear,zFar);}
inline void glMatrixIndexPointerARB(GLint size,GLenum type,GLsizei stride,const void* pointer){this->_getTable()->glMatrixIndexPointerARB(size,type,stride,pointer);}
inline void glMatrixIndexubvARB(GLint size,const GLubyte* indices){this->_getTable()->glMatrixIndexubvARB(size,indices);}
inline void glMatrixIndexuivARB(GLint size,const GLuint* indices){this->_getTable()->glMatrixIndexuivARB(size,indices);}
inline void glMatrixIndexusvARB(GLint size,const GLushort* indices){this->_getTable()->glMatrixIndexusvARB(size,indices);}
inline void glMatrixLoad3x2fNV(GLenum matrixMode,const GLfloat* m){this->_getTable()->glMatrixLoad3x2fNV(matrixMode,m);}
inline void glMatrixLoad3x3fNV(GLenum matrixMode,const GLfloat* m){this->_getTable()->glMatrixLoad3x3fNV(matrixMode,m);}
inline void glMatrixLoaddEXT(GLenum mode,const GLdouble* m){this->_getTable()->glMatrixLoaddEXT(mode,m);}
inline void glMatrixLoadfEXT(GLenum mode,const GLfloat* m){this->_getTable()->glMatrixLoadfEXT(mode,m);}
inline void glMatrixLoadIdentityEXT(GLenum mode){this->_getTable()->glMatrixLoadIdentityEXT(mode);}
inline void glMatrixLoadTranspose3x3fNV(GLenum matrixMode,const GLfloat* m){this->_getTable()->glMatrixLoadTranspose3x3fNV(matrixMode,m);}
inline void glMatrixLoadTransposedEXT(GLenum mode,const GLdouble* m){this->_getTable()->glMatrixLoadTransposedEXT(mode,m);}
inline void glMatrixLoadTransposefEXT(GLenum mode,const GLfloat* m){this->_getTable()->glMatrixLoadTransposefEXT(mode,m);}
inline void glMatrixMode(GLenum mode){this->_getTable()->glMatrixMode(mode);}
inline void glMatrixMult3x2fNV(GLenum matrixMode,const GLfloat* m){this->_getTable()->glMatrixMult3x2fNV(matrixMode,m);}
inline void glMatrixMult3x3fNV(GLenum matrixMode,const GLfloat* m){this->_getTable()->glMatrixMult3x3fNV(matrixMode,m);}
inline void glMatrixMultdEXT(GLenum mode,const GLdouble* m){this->_getTable()->glMatrixMultdEXT(mode,m);}
inline void glMatrixMultfEXT(GLenum mode,const GLfloat* m){this->_getTable()->glMatrixMultfEXT(mode,m);}
inline void glMatrixMultTranspose3x3fNV(GLenum matrixMode,const GLfloat* m){this->_getTable()->glMatrixMultTranspose3x3fNV(matrixMode,m);}
inline void glMatrixMultTransposedEXT(GLenum mode,const GLdouble* m){this->_getTable()->glMatrixMultTransposedEXT(mode,m);}
inline void glMatrixMultTransposefEXT(GLenum mode,const GLfloat* m){this->_getTable()->glMatrixMultTransposefEXT(mode,m);}
inline void glMatrixOrthoEXT(GLenum mode,GLdouble left,GLdouble right,GLdouble bottom,GLdouble top,GLdouble zNear,GLdouble zFar){this->_getTable()->glMatrixOrthoEXT(mode,left,right,bottom,top,zNear,zFar);}
inline void glMatrixPopEXT(GLenum mode){this->_getTable()->glMatrixPopEXT(mode);}
inline void glMatrixPushEXT(GLenum mode){this->_getTable()->glMatrixPushEXT(mode);}
inline void glMatrixRotatedEXT(GLenum mode,GLdouble angle,GLdouble x,GLdouble y,GLdouble z){this->_getTable()->glMatrixRotatedEXT(mode,angle,x,y,z);}
inline void glMatrixRotatefEXT(GLenum mode,GLfloat angle,GLfloat x,GLfloat y,GLfloat z){this->_getTable()->glMatrixRotatefEXT(mode,angle,x,y,z);}
inline void glMatrixScaledEXT(GLenum mode,GLdouble x,GLdouble y,GLdouble z){this->_getTable()->glMatrixScaledEXT(mode,x,y,z);}
inline void glMatrixScalefEXT(GLenum mode,GLfloat x,GLfloat y,GLfloat z){this->_getTable()->glMatrixScalefEXT(mode,x,y,z);}
inline void glMatrixTranslatedEXT(GLenum mode,GLdouble x,GLdouble y,GLdouble z){this->_getTable()->glMatrixTranslatedEXT(mode,x,y,z);}
inline void glMatrixTranslatefEXT(GLenum mode,GLfloat x,GLfloat y,GLfloat z){this->_getTable()->glMatrixTranslatefEXT(mode,x,y,z);}
inline void glMaxShaderCompilerThreadsARB(GLuint count){this->_getTable()->glMaxShaderCompilerThreadsARB(count);}
inline void glMemoryBarrierByRegion(GLbitfield barriers){this->_getTable()->glMemoryBarrierByRegion(barriers);}
inline void glMemoryBarrierEXT(GLbitfield barriers){this->_getTable()->glMemoryBarrierEXT(barriers);}
inline void glMemoryBarrier(GLbitfield barriers){this->_getTable()->glMemoryBarrier(barriers);}
inline void glMinmaxEXT(GLenum target,GLenum internalformat,GLboolean sink){this->_getTable()->glMinmaxEXT(target,internalformat,sink);}
inline void glMinmax(GLenum target,GLenum internalformat,GLboolean sink){this->_getTable()->glMinmax(target,internalformat,sink);}
inline void glMinSampleShadingARB(GLfloat value){this->_getTable()->glMinSampleShadingARB(value);}
inline void glMinSampleShading(GLfloat value){this->_getTable()->glMinSampleShading(value);}
inline void glMultiDrawArraysEXT(GLenum mode,const GLint* first,const GLsizei* count,GLsizei primcount){this->_getTable()->glMultiDrawArraysEXT(mode,first,count,primcount);}
inline void glMultiDrawArrays(GLenum mode,const GLint* first,const GLsizei* count,GLsizei drawcount){this->_getTable()->glMultiDrawArrays(mode,first,count,drawcount);}
inline void glMultiDrawArraysIndirectAMD(GLenum mode,const void* indirect,GLsizei primcount,GLsizei stride){this->_getTable()->glMultiDrawArraysIndirectAMD(mode,indirect,primcount,stride);}
inline void glMultiDrawArraysIndirectBindlessCountNV(GLenum mode,const void* indirect,GLsizei drawCount,GLsizei maxDrawCount,GLsizei stride,GLint vertexBufferCount){this->_getTable()->glMultiDrawArraysIndirectBindlessCountNV(mode,indirect,drawCount,maxDrawCount,stride,vertexBufferCount);}
inline void glMultiDrawArraysIndirectBindlessNV(GLenum mode,const void* indirect,GLsizei drawCount,GLsizei stride,GLint vertexBufferCount){this->_getTable()->glMultiDrawArraysIndirectBindlessNV(mode,indirect,drawCount,stride,vertexBufferCount);}
inline void glMultiDrawArraysIndirectCountARB(GLenum mode,GLintptr indirect,GLintptr drawcount,GLsizei maxdrawcount,GLsizei stride){this->_getTable()->glMultiDrawArraysIndirectCountARB(mode,indirect,drawcount,maxdrawcount,stride);}
inline void glMultiDrawArraysIndirect(GLenum mode,const void* indirect,GLsizei drawcount,GLsizei stride){this->_getTable()->glMultiDrawArraysIndirect(mode,indirect,drawcount,stride);}
inline void glMultiDrawElementArrayAPPLE(GLenum mode,const GLint* first,const GLsizei* count,GLsizei primcount){this->_getTable()->glMultiDrawElementArrayAPPLE(mode,first,count,primcount);}
inline void glMultiDrawElementsBaseVertex(GLenum mode,const GLsizei* count,GLenum type,const void*const* indices,GLsizei drawcount,const GLint* basevertex){this->_getTable()->glMultiDrawElementsBaseVertex(mode,count,type,indices,drawcount,basevertex);}
inline void glMultiDrawElementsEXT(GLenum mode,const GLsizei* count,GLenum type,const void*const* indices,GLsizei primcount){this->_getTable()->glMultiDrawElementsEXT(mode,count,type,indices,primcount);}
inline void glMultiDrawElements(GLenum mode,const GLsizei* count,GLenum type,const void*const* indices,GLsizei drawcount){this->_getTable()->glMultiDrawElements(mode,count,type,indices,drawcount);}
inline void glMultiDrawElementsIndirectAMD(GLenum mode,GLenum type,const void* indirect,GLsizei primcount,GLsizei stride){this->_getTable()->glMultiDrawElementsIndirectAMD(mode,type,indirect,primcount,stride);}
inline void glMultiDrawElementsIndirectBindlessCountNV(GLenum mode,GLenum type,const void* indirect,GLsizei drawCount,GLsizei maxDrawCount,GLsizei stride,GLint vertexBufferCount){this->_getTable()->glMultiDrawElementsIndirectBindlessCountNV(mode,type,indirect,drawCount,maxDrawCount,stride,vertexBufferCount);}
inline void glMultiDrawElementsIndirectBindlessNV(GLenum mode,GLenum type,const void* indirect,GLsizei drawCount,GLsizei stride,GLint vertexBufferCount){this->_getTable()->glMultiDrawElementsIndirectBindlessNV(mode,type,indirect,drawCount,stride,vertexBufferCount);}
inline void glMultiDrawElementsIndirectCountARB(GLenum mode,GLenum type,GLintptr indirect,GLintptr drawcount,GLsizei maxdrawcount,GLsizei stride){this->_getTable()->glMultiDrawElementsIndirectCountARB(mode,type,indirect,drawcount,maxdrawcount,stride);}
inline void glMultiDrawElementsIndirect(GLenum mode,GLenum type,const void* indirect,GLsizei drawcount,GLsizei stride){this->_getTable()->glMultiDrawElementsIndirect(mode,type,indirect,drawcount,stride);}
inline void glMultiDrawRangeElementArrayAPPLE(GLenum mode,GLuint start,GLuint end,const GLint* first,const GLsizei* count,GLsizei primcount){this->_getTable()->glMultiDrawRangeElementArrayAPPLE(mode,start,end,first,count,primcount);}
inline void glMultiModeDrawArraysIBM(const GLenum* mode,const GLint* first,const GLsizei* count,GLsizei primcount,GLint modestride){this->_getTable()->glMultiModeDrawArraysIBM(mode,first,count,primcount,modestride);}
inline void glMultiModeDrawElementsIBM(const GLenum* mode,const GLsizei* count,GLenum type,const void*const* indices,GLsizei primcount,GLint modestride){this->_getTable()->glMultiModeDrawElementsIBM(mode,count,type,indices,primcount,modestride);}
inline void glMultiTexBufferEXT(GLenum texunit,GLenum target,GLenum internalformat,GLuint buffer){this->_getTable()->glMultiTexBufferEXT(texunit,target,internalformat,buffer);}
inline void glMultiTexCoord1bOES(GLenum texture,GLbyte s){this->_getTable()->glMultiTexCoord1bOES(texture,s);}
inline void glMultiTexCoord1bvOES(GLenum texture,const GLbyte* coords){this->_getTable()->glMultiTexCoord1bvOES(texture,coords);}
inline void glMultiTexCoord1dARB(GLenum target,GLdouble s){this->_getTable()->glMultiTexCoord1dARB(target,s);}
inline void glMultiTexCoord1d(GLenum target,GLdouble s){this->_getTable()->glMultiTexCoord1d(target,s);}
inline void glMultiTexCoord1dvARB(GLenum target,const GLdouble* v){this->_getTable()->glMultiTexCoord1dvARB(target,v);}
inline void glMultiTexCoord1dv(GLenum target,const GLdouble* v){this->_getTable()->glMultiTexCoord1dv(target,v);}
inline void glMultiTexCoord1fARB(GLenum target,GLfloat s){this->_getTable()->glMultiTexCoord1fARB(target,s);}
inline void glMultiTexCoord1f(GLenum target,GLfloat s){this->_getTable()->glMultiTexCoord1f(target,s);}
inline void glMultiTexCoord1fvARB(GLenum target,const GLfloat* v){this->_getTable()->glMultiTexCoord1fvARB(target,v);}
inline void glMultiTexCoord1fv(GLenum target,const GLfloat* v){this->_getTable()->glMultiTexCoord1fv(target,v);}
inline void glMultiTexCoord1hNV(GLenum target,GLhalfNV s){this->_getTable()->glMultiTexCoord1hNV(target,s);}
inline void glMultiTexCoord1hvNV(GLenum target,const GLhalfNV* v){this->_getTable()->glMultiTexCoord1hvNV(target,v);}
inline void glMultiTexCoord1iARB(GLenum target,GLint s){this->_getTable()->glMultiTexCoord1iARB(target,s);}
inline void glMultiTexCoord1i(GLenum target,GLint s){this->_getTable()->glMultiTexCoord1i(target,s);}
inline void glMultiTexCoord1ivARB(GLenum target,const GLint* v){this->_getTable()->glMultiTexCoord1ivARB(target,v);}
inline void glMultiTexCoord1iv(GLenum target,const GLint* v){this->_getTable()->glMultiTexCoord1iv(target,v);}
inline void glMultiTexCoord1sARB(GLenum target,GLshort s){this->_getTable()->glMultiTexCoord1sARB(target,s);}
inline void glMultiTexCoord1s(GLenum target,GLshort s){this->_getTable()->glMultiTexCoord1s(target,s);}
inline void glMultiTexCoord1svARB(GLenum target,const GLshort* v){this->_getTable()->glMultiTexCoord1svARB(target,v);}
inline void glMultiTexCoord1sv(GLenum target,const GLshort* v){this->_getTable()->glMultiTexCoord1sv(target,v);}
inline void glMultiTexCoord1xOES(GLenum texture,GLfixed s){this->_getTable()->glMultiTexCoord1xOES(texture,s);}
inline void glMultiTexCoord1xvOES(GLenum texture,const GLfixed* coords){this->_getTable()->glMultiTexCoord1xvOES(texture,coords);}
inline void glMultiTexCoord2bOES(GLenum texture,GLbyte s,GLbyte t){this->_getTable()->glMultiTexCoord2bOES(texture,s,t);}
inline void glMultiTexCoord2bvOES(GLenum texture,const GLbyte* coords){this->_getTable()->glMultiTexCoord2bvOES(texture,coords);}
inline void glMultiTexCoord2dARB(GLenum target,GLdouble s,GLdouble t){this->_getTable()->glMultiTexCoord2dARB(target,s,t);}
inline void glMultiTexCoord2d(GLenum target,GLdouble s,GLdouble t){this->_getTable()->glMultiTexCoord2d(target,s,t);}
inline void glMultiTexCoord2dvARB(GLenum target,const GLdouble* v){this->_getTable()->glMultiTexCoord2dvARB(target,v);}
inline void glMultiTexCoord2dv(GLenum target,const GLdouble* v){this->_getTable()->glMultiTexCoord2dv(target,v);}
inline void glMultiTexCoord2fARB(GLenum target,GLfloat s,GLfloat t){this->_getTable()->glMultiTexCoord2fARB(target,s,t);}
inline void glMultiTexCoord2f(GLenum target,GLfloat s,GLfloat t){this->_getTable()->glMultiTexCoord2f(target,s,t);}
inline void glMultiTexCoord2fvARB(GLenum target,const GLfloat* v){this->_getTable()->glMultiTexCoord2fvARB(target,v);}
inline void glMultiTexCoord2fv(GLenum target,const GLfloat* v){this->_getTable()->glMultiTexCoord2fv(target,v);}
inline void glMultiTexCoord2hNV(GLenum target,GLhalfNV s,GLhalfNV t){this->_getTable()->glMultiTexCoord2hNV(target,s,t);}
inline void glMultiTexCoord2hvNV(GLenum target,const GLhalfNV* v){this->_getTable()->glMultiTexCoord2hvNV(target,v);}
inline void glMultiTexCoord2iARB(GLenum target,GLint s,GLint t){this->_getTable()->glMultiTexCoord2iARB(target,s,t);}
inline void glMultiTexCoord2i(GLenum target,GLint s,GLint t){this->_getTable()->glMultiTexCoord2i(target,s,t);}
inline void glMultiTexCoord2ivARB(GLenum target,const GLint* v){this->_getTable()->glMultiTexCoord2ivARB(target,v);}
inline void glMultiTexCoord2iv(GLenum target,const GLint* v){this->_getTable()->glMultiTexCoord2iv(target,v);}
inline void glMultiTexCoord2sARB(GLenum target,GLshort s,GLshort t){this->_getTable()->glMultiTexCoord2sARB(target,s,t);}
inline void glMultiTexCoord2s(GLenum target,GLshort s,GLshort t){this->_getTable()->glMultiTexCoord2s(target,s,t);}
inline void glMultiTexCoord2svARB(GLenum target,const GLshort* v){this->_getTable()->glMultiTexCoord2svARB(target,v);}
inline void glMultiTexCoord2sv(GLenum target,const GLshort* v){this->_getTable()->glMultiTexCoord2sv(target,v);}
inline void glMultiTexCoord2xOES(GLenum texture,GLfixed s,GLfixed t){this->_getTable()->glMultiTexCoord2xOES(texture,s,t);}
inline void glMultiTexCoord2xvOES(GLenum texture,const GLfixed* coords){this->_getTable()->glMultiTexCoord2xvOES(texture,coords);}
inline void glMultiTexCoord3bOES(GLenum texture,GLbyte s,GLbyte t,GLbyte r){this->_getTable()->glMultiTexCoord3bOES(texture,s,t,r);}
inline void glMultiTexCoord3bvOES(GLenum texture,const GLbyte* coords){this->_getTable()->glMultiTexCoord3bvOES(texture,coords);}
inline void glMultiTexCoord3dARB(GLenum target,GLdouble s,GLdouble t,GLdouble r){this->_getTable()->glMultiTexCoord3dARB(target,s,t,r);}
inline void glMultiTexCoord3d(GLenum target,GLdouble s,GLdouble t,GLdouble r){this->_getTable()->glMultiTexCoord3d(target,s,t,r);}
inline void glMultiTexCoord3dvARB(GLenum target,const GLdouble* v){this->_getTable()->glMultiTexCoord3dvARB(target,v);}
inline void glMultiTexCoord3dv(GLenum target,const GLdouble* v){this->_getTable()->glMultiTexCoord3dv(target,v);}
inline void glMultiTexCoord3fARB(GLenum target,GLfloat s,GLfloat t,GLfloat r){this->_getTable()->glMultiTexCoord3fARB(target,s,t,r);}
inline void glMultiTexCoord3f(GLenum target,GLfloat s,GLfloat t,GLfloat r){this->_getTable()->glMultiTexCoord3f(target,s,t,r);}
inline void glMultiTexCoord3fvARB(GLenum target,const GLfloat* v){this->_getTable()->glMultiTexCoord3fvARB(target,v);}
inline void glMultiTexCoord3fv(GLenum target,const GLfloat* v){this->_getTable()->glMultiTexCoord3fv(target,v);}
inline void glMultiTexCoord3hNV(GLenum target,GLhalfNV s,GLhalfNV t,GLhalfNV r){this->_getTable()->glMultiTexCoord3hNV(target,s,t,r);}
inline void glMultiTexCoord3hvNV(GLenum target,const GLhalfNV* v){this->_getTable()->glMultiTexCoord3hvNV(target,v);}
inline void glMultiTexCoord3iARB(GLenum target,GLint s,GLint t,GLint r){this->_getTable()->glMultiTexCoord3iARB(target,s,t,r);}
inline void glMultiTexCoord3i(GLenum target,GLint s,GLint t,GLint r){this->_getTable()->glMultiTexCoord3i(target,s,t,r);}
inline void glMultiTexCoord3ivARB(GLenum target,const GLint* v){this->_getTable()->glMultiTexCoord3ivARB(target,v);}
inline void glMultiTexCoord3iv(GLenum target,const GLint* v){this->_getTable()->glMultiTexCoord3iv(target,v);}
inline void glMultiTexCoord3sARB(GLenum target,GLshort s,GLshort t,GLshort r){this->_getTable()->glMultiTexCoord3sARB(target,s,t,r);}
inline void glMultiTexCoord3s(GLenum target,GLshort s,GLshort t,GLshort r){this->_getTable()->glMultiTexCoord3s(target,s,t,r);}
inline void glMultiTexCoord3svARB(GLenum target,const GLshort* v){this->_getTable()->glMultiTexCoord3svARB(target,v);}
inline void glMultiTexCoord3sv(GLenum target,const GLshort* v){this->_getTable()->glMultiTexCoord3sv(target,v);}
inline void glMultiTexCoord3xOES(GLenum texture,GLfixed s,GLfixed t,GLfixed r){this->_getTable()->glMultiTexCoord3xOES(texture,s,t,r);}
inline void glMultiTexCoord3xvOES(GLenum texture,const GLfixed* coords){this->_getTable()->glMultiTexCoord3xvOES(texture,coords);}
inline void glMultiTexCoord4bOES(GLenum texture,GLbyte s,GLbyte t,GLbyte r,GLbyte q){this->_getTable()->glMultiTexCoord4bOES(texture,s,t,r,q);}
inline void glMultiTexCoord4bvOES(GLenum texture,const GLbyte* coords){this->_getTable()->glMultiTexCoord4bvOES(texture,coords);}
inline void glMultiTexCoord4dARB(GLenum target,GLdouble s,GLdouble t,GLdouble r,GLdouble q){this->_getTable()->glMultiTexCoord4dARB(target,s,t,r,q);}
inline void glMultiTexCoord4d(GLenum target,GLdouble s,GLdouble t,GLdouble r,GLdouble q){this->_getTable()->glMultiTexCoord4d(target,s,t,r,q);}
inline void glMultiTexCoord4dvARB(GLenum target,const GLdouble* v){this->_getTable()->glMultiTexCoord4dvARB(target,v);}
inline void glMultiTexCoord4dv(GLenum target,const GLdouble* v){this->_getTable()->glMultiTexCoord4dv(target,v);}
inline void glMultiTexCoord4fARB(GLenum target,GLfloat s,GLfloat t,GLfloat r,GLfloat q){this->_getTable()->glMultiTexCoord4fARB(target,s,t,r,q);}
inline void glMultiTexCoord4f(GLenum target,GLfloat s,GLfloat t,GLfloat r,GLfloat q){this->_getTable()->glMultiTexCoord4f(target,s,t,r,q);}
inline void glMultiTexCoord4fvARB(GLenum target,const GLfloat* v){this->_getTable()->glMultiTexCoord4fvARB(target,v);}
inline void glMultiTexCoord4fv(GLenum target,const GLfloat* v){this->_getTable()->glMultiTexCoord4fv(target,v);}
inline void glMultiTexCoord4hNV(GLenum target,GLhalfNV s,GLhalfNV t,GLhalfNV r,GLhalfNV q){this->_getTable()->glMultiTexCoord4hNV(target,s,t,r,q);}
inline void glMultiTexCoord4hvNV(GLenum target,const GLhalfNV* v){this->_getTable()->glMultiTexCoord4hvNV(target,v);}
inline void glMultiTexCoord4iARB(GLenum target,GLint s,GLint t,GLint r,GLint q){this->_getTable()->glMultiTexCoord4iARB(target,s,t,r,q);}
inline void glMultiTexCoord4i(GLenum target,GLint s,GLint t,GLint r,GLint q){this->_getTable()->glMultiTexCoord4i(target,s,t,r,q);}
inline void glMultiTexCoord4ivARB(GLenum target,const GLint* v){this->_getTable()->glMultiTexCoord4ivARB(target,v);}
inline void glMultiTexCoord4iv(GLenum target,const GLint* v){this->_getTable()->glMultiTexCoord4iv(target,v);}
inline void glMultiTexCoord4sARB(GLenum target,GLshort s,GLshort t,GLshort r,GLshort q){this->_getTable()->glMultiTexCoord4sARB(target,s,t,r,q);}
inline void glMultiTexCoord4s(GLenum target,GLshort s,GLshort t,GLshort r,GLshort q){this->_getTable()->glMultiTexCoord4s(target,s,t,r,q);}
inline void glMultiTexCoord4svARB(GLenum target,const GLshort* v){this->_getTable()->glMultiTexCoord4svARB(target,v);}
inline void glMultiTexCoord4sv(GLenum target,const GLshort* v){this->_getTable()->glMultiTexCoord4sv(target,v);}
inline void glMultiTexCoord4xOES(GLenum texture,GLfixed s,GLfixed t,GLfixed r,GLfixed q){this->_getTable()->glMultiTexCoord4xOES(texture,s,t,r,q);}
inline void glMultiTexCoord4xvOES(GLenum texture,const GLfixed* coords){this->_getTable()->glMultiTexCoord4xvOES(texture,coords);}
inline void glMultiTexCoordP1ui(GLenum texture,GLenum type,GLuint coords){this->_getTable()->glMultiTexCoordP1ui(texture,type,coords);}
inline void glMultiTexCoordP1uiv(GLenum texture,GLenum type,const GLuint* coords){this->_getTable()->glMultiTexCoordP1uiv(texture,type,coords);}
inline void glMultiTexCoordP2ui(GLenum texture,GLenum type,GLuint coords){this->_getTable()->glMultiTexCoordP2ui(texture,type,coords);}
inline void glMultiTexCoordP2uiv(GLenum texture,GLenum type,const GLuint* coords){this->_getTable()->glMultiTexCoordP2uiv(texture,type,coords);}
inline void glMultiTexCoordP3ui(GLenum texture,GLenum type,GLuint coords){this->_getTable()->glMultiTexCoordP3ui(texture,type,coords);}
inline void glMultiTexCoordP3uiv(GLenum texture,GLenum type,const GLuint* coords){this->_getTable()->glMultiTexCoordP3uiv(texture,type,coords);}
inline void glMultiTexCoordP4ui(GLenum texture,GLenum type,GLuint coords){this->_getTable()->glMultiTexCoordP4ui(texture,type,coords);}
inline void glMultiTexCoordP4uiv(GLenum texture,GLenum type,const GLuint* coords){this->_getTable()->glMultiTexCoordP4uiv(texture,type,coords);}
inline void glMultiTexCoordPointerEXT(GLenum texunit,GLint size,GLenum type,GLsizei stride,const void* pointer){this->_getTable()->glMultiTexCoordPointerEXT(texunit,size,type,stride,pointer);}
inline void glMultiTexEnvfEXT(GLenum texunit,GLenum target,GLenum pname,GLfloat param){this->_getTable()->glMultiTexEnvfEXT(texunit,target,pname,param);}
inline void glMultiTexEnvfvEXT(GLenum texunit,GLenum target,GLenum pname,const GLfloat* params){this->_getTable()->glMultiTexEnvfvEXT(texunit,target,pname,params);}
inline void glMultiTexEnviEXT(GLenum texunit,GLenum target,GLenum pname,GLint param){this->_getTable()->glMultiTexEnviEXT(texunit,target,pname,param);}
inline void glMultiTexEnvivEXT(GLenum texunit,GLenum target,GLenum pname,const GLint* params){this->_getTable()->glMultiTexEnvivEXT(texunit,target,pname,params);}
inline void glMultiTexGendEXT(GLenum texunit,GLenum coord,GLenum pname,GLdouble param){this->_getTable()->glMultiTexGendEXT(texunit,coord,pname,param);}
inline void glMultiTexGendvEXT(GLenum texunit,GLenum coord,GLenum pname,const GLdouble* params){this->_getTable()->glMultiTexGendvEXT(texunit,coord,pname,params);}
inline void glMultiTexGenfEXT(GLenum texunit,GLenum coord,GLenum pname,GLfloat param){this->_getTable()->glMultiTexGenfEXT(texunit,coord,pname,param);}
inline void glMultiTexGenfvEXT(GLenum texunit,GLenum coord,GLenum pname,const GLfloat* params){this->_getTable()->glMultiTexGenfvEXT(texunit,coord,pname,params);}
inline void glMultiTexGeniEXT(GLenum texunit,GLenum coord,GLenum pname,GLint param){this->_getTable()->glMultiTexGeniEXT(texunit,coord,pname,param);}
inline void glMultiTexGenivEXT(GLenum texunit,GLenum coord,GLenum pname,const GLint* params){this->_getTable()->glMultiTexGenivEXT(texunit,coord,pname,params);}
inline void glMultiTexImage1DEXT(GLenum texunit,GLenum target,GLint level,GLint internalformat,GLsizei width,GLint border,GLenum format,GLenum type,const void* pixels){this->_getTable()->glMultiTexImage1DEXT(texunit,target,level,internalformat,width,border,format,type,pixels);}
inline void glMultiTexImage2DEXT(GLenum texunit,GLenum target,GLint level,GLint internalformat,GLsizei width,GLsizei height,GLint border,GLenum format,GLenum type,const void* pixels){this->_getTable()->glMultiTexImage2DEXT(texunit,target,level,internalformat,width,height,border,format,type,pixels);}
inline void glMultiTexImage3DEXT(GLenum texunit,GLenum target,GLint level,GLint internalformat,GLsizei width,GLsizei height,GLsizei depth,GLint border,GLenum format,GLenum type,const void* pixels){this->_getTable()->glMultiTexImage3DEXT(texunit,target,level,internalformat,width,height,depth,border,format,type,pixels);}
inline void glMultiTexParameterfEXT(GLenum texunit,GLenum target,GLenum pname,GLfloat param){this->_getTable()->glMultiTexParameterfEXT(texunit,target,pname,param);}
inline void glMultiTexParameterfvEXT(GLenum texunit,GLenum target,GLenum pname,const GLfloat* params){this->_getTable()->glMultiTexParameterfvEXT(texunit,target,pname,params);}
inline void glMultiTexParameteriEXT(GLenum texunit,GLenum target,GLenum pname,GLint param){this->_getTable()->glMultiTexParameteriEXT(texunit,target,pname,param);}
inline void glMultiTexParameterIivEXT(GLenum texunit,GLenum target,GLenum pname,const GLint* params){this->_getTable()->glMultiTexParameterIivEXT(texunit,target,pname,params);}
inline void glMultiTexParameterIuivEXT(GLenum texunit,GLenum target,GLenum pname,const GLuint* params){this->_getTable()->glMultiTexParameterIuivEXT(texunit,target,pname,params);}
inline void glMultiTexParameterivEXT(GLenum texunit,GLenum target,GLenum pname,const GLint* params){this->_getTable()->glMultiTexParameterivEXT(texunit,target,pname,params);}
inline void glMultiTexRenderbufferEXT(GLenum texunit,GLenum target,GLuint renderbuffer){this->_getTable()->glMultiTexRenderbufferEXT(texunit,target,renderbuffer);}
inline void glMultiTexSubImage1DEXT(GLenum texunit,GLenum target,GLint level,GLint xoffset,GLsizei width,GLenum format,GLenum type,const void* pixels){this->_getTable()->glMultiTexSubImage1DEXT(texunit,target,level,xoffset,width,format,type,pixels);}
inline void glMultiTexSubImage2DEXT(GLenum texunit,GLenum target,GLint level,GLint xoffset,GLint yoffset,GLsizei width,GLsizei height,GLenum format,GLenum type,const void* pixels){this->_getTable()->glMultiTexSubImage2DEXT(texunit,target,level,xoffset,yoffset,width,height,format,type,pixels);}
inline void glMultiTexSubImage3DEXT(GLenum texunit,GLenum target,GLint level,GLint xoffset,GLint yoffset,GLint zoffset,GLsizei width,GLsizei height,GLsizei depth,GLenum format,GLenum type,const void* pixels){this->_getTable()->glMultiTexSubImage3DEXT(texunit,target,level,xoffset,yoffset,zoffset,width,height,depth,format,type,pixels);}
inline void glMultMatrixd(const GLdouble* m){this->_getTable()->glMultMatrixd(m);}
inline void glMultMatrixf(const GLfloat* m){this->_getTable()->glMultMatrixf(m);}
inline void glMultMatrixxOES(const GLfixed* m){this->_getTable()->glMultMatrixxOES(m);}
inline void glMultTransposeMatrixdARB(const GLdouble* m){this->_getTable()->glMultTransposeMatrixdARB(m);}
inline void glMultTransposeMatrixd(const GLdouble m[16]){this->_getTable()->glMultTransposeMatrixd(m[16]);}
inline void glMultTransposeMatrixfARB(const GLfloat* m){this->_getTable()->glMultTransposeMatrixfARB(m);}
inline void glMultTransposeMatrixf(const GLfloat m[16]){this->_getTable()->glMultTransposeMatrixf(m[16]);}
inline void glMultTransposeMatrixxOES(const GLfixed* m){this->_getTable()->glMultTransposeMatrixxOES(m);}
inline void glNamedBufferDataEXT(GLuint buffer,GLsizeiptr size,const void* data,GLenum usage){this->_getTable()->glNamedBufferDataEXT(buffer,size,data,usage);}
inline void glNamedBufferData(GLuint buffer,GLsizeiptr size,const void* data,GLenum usage){this->_getTable()->glNamedBufferData(buffer,size,data,usage);}
inline void glNamedBufferPageCommitmentARB(GLuint buffer,GLintptr offset,GLsizeiptr size,GLboolean commit){this->_getTable()->glNamedBufferPageCommitmentARB(buffer,offset,size,commit);}
inline void glNamedBufferPageCommitmentEXT(GLuint buffer,GLintptr offset,GLsizeiptr size,GLboolean commit){this->_getTable()->glNamedBufferPageCommitmentEXT(buffer,offset,size,commit);}
inline void glNamedBufferStorageEXT(GLuint buffer,GLsizeiptr size,const void* data,GLbitfield flags){this->_getTable()->glNamedBufferStorageEXT(buffer,size,data,flags);}
inline void glNamedBufferStorage(GLuint buffer,GLsizeiptr size,const void* data,GLbitfield flags){this->_getTable()->glNamedBufferStorage(buffer,size,data,flags);}
inline void glNamedBufferSubDataEXT(GLuint buffer,GLintptr offset,GLsizeiptr size,const void* data){this->_getTable()->glNamedBufferSubDataEXT(buffer,offset,size,data);}
inline void glNamedBufferSubData(GLuint buffer,GLintptr offset,GLsizeiptr size,const void* data){this->_getTable()->glNamedBufferSubData(buffer,offset,size,data);}
inline void glNamedCopyBufferSubDataEXT(GLuint readBuffer,GLuint writeBuffer,GLintptr readOffset,GLintptr writeOffset,GLsizeiptr size){this->_getTable()->glNamedCopyBufferSubDataEXT(readBuffer,writeBuffer,readOffset,writeOffset,size);}
inline void glNamedFramebufferDrawBuffer(GLuint framebuffer,GLenum buf){this->_getTable()->glNamedFramebufferDrawBuffer(framebuffer,buf);}
inline void glNamedFramebufferDrawBuffers(GLuint framebuffer,GLsizei n,const GLenum* bufs){this->_getTable()->glNamedFramebufferDrawBuffers(framebuffer,n,bufs);}
inline void glNamedFramebufferParameteriEXT(GLuint framebuffer,GLenum pname,GLint param){this->_getTable()->glNamedFramebufferParameteriEXT(framebuffer,pname,param);}
inline void glNamedFramebufferParameteri(GLuint framebuffer,GLenum pname,GLint param){this->_getTable()->glNamedFramebufferParameteri(framebuffer,pname,param);}
inline void glNamedFramebufferReadBuffer(GLuint framebuffer,GLenum src){this->_getTable()->glNamedFramebufferReadBuffer(framebuffer,src);}
inline void glNamedFramebufferRenderbufferEXT(GLuint framebuffer,GLenum attachment,GLenum renderbuffertarget,GLuint renderbuffer){this->_getTable()->glNamedFramebufferRenderbufferEXT(framebuffer,attachment,renderbuffertarget,renderbuffer);}
inline void glNamedFramebufferRenderbuffer(GLuint framebuffer,GLenum attachment,GLenum renderbuffertarget,GLuint renderbuffer){this->_getTable()->glNamedFramebufferRenderbuffer(framebuffer,attachment,renderbuffertarget,renderbuffer);}
inline void glNamedFramebufferSampleLocationsfvARB(GLuint framebuffer,GLuint start,GLsizei count,const GLfloat* v){this->_getTable()->glNamedFramebufferSampleLocationsfvARB(framebuffer,start,count,v);}
inline void glNamedFramebufferSampleLocationsfvNV(GLuint framebuffer,GLuint start,GLsizei count,const GLfloat* v){this->_getTable()->glNamedFramebufferSampleLocationsfvNV(framebuffer,start,count,v);}
inline void glNamedFramebufferTexture1DEXT(GLuint framebuffer,GLenum attachment,GLenum textarget,GLuint texture,GLint level){this->_getTable()->glNamedFramebufferTexture1DEXT(framebuffer,attachment,textarget,texture,level);}
inline void glNamedFramebufferTexture2DEXT(GLuint framebuffer,GLenum attachment,GLenum textarget,GLuint texture,GLint level){this->_getTable()->glNamedFramebufferTexture2DEXT(framebuffer,attachment,textarget,texture,level);}
inline void glNamedFramebufferTexture3DEXT(GLuint framebuffer,GLenum attachment,GLenum textarget,GLuint texture,GLint level,GLint zoffset){this->_getTable()->glNamedFramebufferTexture3DEXT(framebuffer,attachment,textarget,texture,level,zoffset);}
inline void glNamedFramebufferTextureEXT(GLuint framebuffer,GLenum attachment,GLuint texture,GLint level){this->_getTable()->glNamedFramebufferTextureEXT(framebuffer,attachment,texture,level);}
inline void glNamedFramebufferTextureFaceEXT(GLuint framebuffer,GLenum attachment,GLuint texture,GLint level,GLenum face){this->_getTable()->glNamedFramebufferTextureFaceEXT(framebuffer,attachment,texture,level,face);}
inline void glNamedFramebufferTexture(GLuint framebuffer,GLenum attachment,GLuint texture,GLint level){this->_getTable()->glNamedFramebufferTexture(framebuffer,attachment,texture,level);}
inline void glNamedFramebufferTextureLayerEXT(GLuint framebuffer,GLenum attachment,GLuint texture,GLint level,GLint layer){this->_getTable()->glNamedFramebufferTextureLayerEXT(framebuffer,attachment,texture,level,layer);}
inline void glNamedFramebufferTextureLayer(GLuint framebuffer,GLenum attachment,GLuint texture,GLint level,GLint layer){this->_getTable()->glNamedFramebufferTextureLayer(framebuffer,attachment,texture,level,layer);}
inline void glNamedProgramLocalParameter4dEXT(GLuint program,GLenum target,GLuint index,GLdouble x,GLdouble y,GLdouble z,GLdouble w){this->_getTable()->glNamedProgramLocalParameter4dEXT(program,target,index,x,y,z,w);}
inline void glNamedProgramLocalParameter4dvEXT(GLuint program,GLenum target,GLuint index,const GLdouble* params){this->_getTable()->glNamedProgramLocalParameter4dvEXT(program,target,index,params);}
inline void glNamedProgramLocalParameter4fEXT(GLuint program,GLenum target,GLuint index,GLfloat x,GLfloat y,GLfloat z,GLfloat w){this->_getTable()->glNamedProgramLocalParameter4fEXT(program,target,index,x,y,z,w);}
inline void glNamedProgramLocalParameter4fvEXT(GLuint program,GLenum target,GLuint index,const GLfloat* params){this->_getTable()->glNamedProgramLocalParameter4fvEXT(program,target,index,params);}
inline void glNamedProgramLocalParameterI4iEXT(GLuint program,GLenum target,GLuint index,GLint x,GLint y,GLint z,GLint w){this->_getTable()->glNamedProgramLocalParameterI4iEXT(program,target,index,x,y,z,w);}
inline void glNamedProgramLocalParameterI4ivEXT(GLuint program,GLenum target,GLuint index,const GLint* params){this->_getTable()->glNamedProgramLocalParameterI4ivEXT(program,target,index,params);}
inline void glNamedProgramLocalParameterI4uiEXT(GLuint program,GLenum target,GLuint index,GLuint x,GLuint y,GLuint z,GLuint w){this->_getTable()->glNamedProgramLocalParameterI4uiEXT(program,target,index,x,y,z,w);}
inline void glNamedProgramLocalParameterI4uivEXT(GLuint program,GLenum target,GLuint index,const GLuint* params){this->_getTable()->glNamedProgramLocalParameterI4uivEXT(program,target,index,params);}
inline void glNamedProgramLocalParameters4fvEXT(GLuint program,GLenum target,GLuint index,GLsizei count,const GLfloat* params){this->_getTable()->glNamedProgramLocalParameters4fvEXT(program,target,index,count,params);}
inline void glNamedProgramLocalParametersI4ivEXT(GLuint program,GLenum target,GLuint index,GLsizei count,const GLint* params){this->_getTable()->glNamedProgramLocalParametersI4ivEXT(program,target,index,count,params);}
inline void glNamedProgramLocalParametersI4uivEXT(GLuint program,GLenum target,GLuint index,GLsizei count,const GLuint* params){this->_getTable()->glNamedProgramLocalParametersI4uivEXT(program,target,index,count,params);}
inline void glNamedProgramStringEXT(GLuint program,GLenum target,GLenum format,GLsizei len,const void* string){this->_getTable()->glNamedProgramStringEXT(program,target,format,len,string);}
inline void glNamedRenderbufferStorageEXT(GLuint renderbuffer,GLenum internalformat,GLsizei width,GLsizei height){this->_getTable()->glNamedRenderbufferStorageEXT(renderbuffer,internalformat,width,height);}
inline void glNamedRenderbufferStorage(GLuint renderbuffer,GLenum internalformat,GLsizei width,GLsizei height){this->_getTable()->glNamedRenderbufferStorage(renderbuffer,internalformat,width,height);}
inline void glNamedRenderbufferStorageMultisampleCoverageEXT(GLuint renderbuffer,GLsizei coverageSamples,GLsizei colorSamples,GLenum internalformat,GLsizei width,GLsizei height){this->_getTable()->glNamedRenderbufferStorageMultisampleCoverageEXT(renderbuffer,coverageSamples,colorSamples,internalformat,width,height);}
inline void glNamedRenderbufferStorageMultisampleEXT(GLuint renderbuffer,GLsizei samples,GLenum internalformat,GLsizei width,GLsizei height){this->_getTable()->glNamedRenderbufferStorageMultisampleEXT(renderbuffer,samples,internalformat,width,height);}
inline void glNamedRenderbufferStorageMultisample(GLuint renderbuffer,GLsizei samples,GLenum internalformat,GLsizei width,GLsizei height){this->_getTable()->glNamedRenderbufferStorageMultisample(renderbuffer,samples,internalformat,width,height);}
inline void glNamedStringARB(GLenum type,GLint namelen,const GLchar* name,GLint stringlen,const GLchar* string){this->_getTable()->glNamedStringARB(type,namelen,name,stringlen,string);}
inline void glNewList(GLuint list,GLenum mode){this->_getTable()->glNewList(list,mode);}
inline void glNormal3b(GLbyte nx,GLbyte ny,GLbyte nz){this->_getTable()->glNormal3b(nx,ny,nz);}
inline void glNormal3bv(const GLbyte* v){this->_getTable()->glNormal3bv(v);}
inline void glNormal3d(GLdouble nx,GLdouble ny,GLdouble nz){this->_getTable()->glNormal3d(nx,ny,nz);}
inline void glNormal3dv(const GLdouble* v){this->_getTable()->glNormal3dv(v);}
inline void glNormal3f(GLfloat nx,GLfloat ny,GLfloat nz){this->_getTable()->glNormal3f(nx,ny,nz);}
inline void glNormal3fv(const GLfloat* v){this->_getTable()->glNormal3fv(v);}
inline void glNormal3fVertex3fSUN(GLfloat nx,GLfloat ny,GLfloat nz,GLfloat x,GLfloat y,GLfloat z){this->_getTable()->glNormal3fVertex3fSUN(nx,ny,nz,x,y,z);}
inline void glNormal3fVertex3fvSUN(const GLfloat* n,const GLfloat* v){this->_getTable()->glNormal3fVertex3fvSUN(n,v);}
inline void glNormal3hNV(GLhalfNV nx,GLhalfNV ny,GLhalfNV nz){this->_getTable()->glNormal3hNV(nx,ny,nz);}
inline void glNormal3hvNV(const GLhalfNV* v){this->_getTable()->glNormal3hvNV(v);}
inline void glNormal3i(GLint nx,GLint ny,GLint nz){this->_getTable()->glNormal3i(nx,ny,nz);}
inline void glNormal3iv(const GLint* v){this->_getTable()->glNormal3iv(v);}
inline void glNormal3s(GLshort nx,GLshort ny,GLshort nz){this->_getTable()->glNormal3s(nx,ny,nz);}
inline void glNormal3sv(const GLshort* v){this->_getTable()->glNormal3sv(v);}
inline void glNormal3xOES(GLfixed nx,GLfixed ny,GLfixed nz){this->_getTable()->glNormal3xOES(nx,ny,nz);}
inline void glNormal3xvOES(const GLfixed* coords){this->_getTable()->glNormal3xvOES(coords);}
inline void glNormalFormatNV(GLenum type,GLsizei stride){this->_getTable()->glNormalFormatNV(type,stride);}
inline void glNormalP3ui(GLenum type,GLuint coords){this->_getTable()->glNormalP3ui(type,coords);}
inline void glNormalP3uiv(GLenum type,const GLuint* coords){this->_getTable()->glNormalP3uiv(type,coords);}
inline void glNormalPointerEXT(GLenum type,GLsizei stride,GLsizei count,const void* pointer){this->_getTable()->glNormalPointerEXT(type,stride,count,pointer);}
inline void glNormalPointer(GLenum type,GLsizei stride,const GLvoid* ptr){this->_getTable()->glNormalPointer(type,stride,ptr);}
inline void glNormalPointerListIBM(GLenum type,GLint stride,const void** pointer,GLint ptrstride){this->_getTable()->glNormalPointerListIBM(type,stride,pointer,ptrstride);}
inline void glNormalPointervINTEL(GLenum type,const void** pointer){this->_getTable()->glNormalPointervINTEL(type,pointer);}
inline void glNormalStream3bATI(GLenum stream,GLbyte nx,GLbyte ny,GLbyte nz){this->_getTable()->glNormalStream3bATI(stream,nx,ny,nz);}
inline void glNormalStream3bvATI(GLenum stream,const GLbyte* coords){this->_getTable()->glNormalStream3bvATI(stream,coords);}
inline void glNormalStream3dATI(GLenum stream,GLdouble nx,GLdouble ny,GLdouble nz){this->_getTable()->glNormalStream3dATI(stream,nx,ny,nz);}
inline void glNormalStream3dvATI(GLenum stream,const GLdouble* coords){this->_getTable()->glNormalStream3dvATI(stream,coords);}
inline void glNormalStream3fATI(GLenum stream,GLfloat nx,GLfloat ny,GLfloat nz){this->_getTable()->glNormalStream3fATI(stream,nx,ny,nz);}
inline void glNormalStream3fvATI(GLenum stream,const GLfloat* coords){this->_getTable()->glNormalStream3fvATI(stream,coords);}
inline void glNormalStream3iATI(GLenum stream,GLint nx,GLint ny,GLint nz){this->_getTable()->glNormalStream3iATI(stream,nx,ny,nz);}
inline void glNormalStream3ivATI(GLenum stream,const GLint* coords){this->_getTable()->glNormalStream3ivATI(stream,coords);}
inline void glNormalStream3sATI(GLenum stream,GLshort nx,GLshort ny,GLshort nz){this->_getTable()->glNormalStream3sATI(stream,nx,ny,nz);}
inline void glNormalStream3svATI(GLenum stream,const GLshort* coords){this->_getTable()->glNormalStream3svATI(stream,coords);}
inline void glObjectLabel(GLenum identifier,GLuint name,GLsizei length,const GLchar* label){this->_getTable()->glObjectLabel(identifier,name,length,label);}
inline void glObjectPtrLabel(const void* ptr,GLsizei length,const GLchar* label){this->_getTable()->glObjectPtrLabel(ptr,length,label);}
inline void glOrthofOES(GLfloat l,GLfloat r,GLfloat b,GLfloat t,GLfloat n,GLfloat f){this->_getTable()->glOrthofOES(l,r,b,t,n,f);}
inline void glOrtho(GLdouble left,GLdouble right,GLdouble bottom,GLdouble top,GLdouble near_val,GLdouble far_val){this->_getTable()->glOrtho(left,right,bottom,top,near_val,far_val);}
inline void glOrthoxOES(GLfixed l,GLfixed r,GLfixed b,GLfixed t,GLfixed n,GLfixed f){this->_getTable()->glOrthoxOES(l,r,b,t,n,f);}
inline void glPassTexCoordATI(GLuint dst,GLuint coord,GLenum swizzle){this->_getTable()->glPassTexCoordATI(dst,coord,swizzle);}
inline void glPassThrough(GLfloat token){this->_getTable()->glPassThrough(token);}
inline void glPassThroughxOES(GLfixed token){this->_getTable()->glPassThroughxOES(token);}
inline void glPatchParameterfv(GLenum pname,const GLfloat* values){this->_getTable()->glPatchParameterfv(pname,values);}
inline void glPatchParameteri(GLenum pname,GLint value){this->_getTable()->glPatchParameteri(pname,value);}
inline void glPathColorGenNV(GLenum color,GLenum genMode,GLenum colorFormat,const GLfloat* coeffs){this->_getTable()->glPathColorGenNV(color,genMode,colorFormat,coeffs);}
inline void glPathCommandsNV(GLuint path,GLsizei numCommands,const GLubyte* commands,GLsizei numCoords,GLenum coordType,const void* coords){this->_getTable()->glPathCommandsNV(path,numCommands,commands,numCoords,coordType,coords);}
inline void glPathCoordsNV(GLuint path,GLsizei numCoords,GLenum coordType,const void* coords){this->_getTable()->glPathCoordsNV(path,numCoords,coordType,coords);}
inline void glPathCoverDepthFuncNV(GLenum func){this->_getTable()->glPathCoverDepthFuncNV(func);}
inline void glPathDashArrayNV(GLuint path,GLsizei dashCount,const GLfloat* dashArray){this->_getTable()->glPathDashArrayNV(path,dashCount,dashArray);}
inline void glPathFogGenNV(GLenum genMode){this->_getTable()->glPathFogGenNV(genMode);}
inline void glPathGlyphRangeNV(GLuint firstPathName,GLenum fontTarget,const void* fontName,GLbitfield fontStyle,GLuint firstGlyph,GLsizei numGlyphs,GLenum handleMissingGlyphs,GLuint pathParameterTemplate,GLfloat emScale){this->_getTable()->glPathGlyphRangeNV(firstPathName,fontTarget,fontName,fontStyle,firstGlyph,numGlyphs,handleMissingGlyphs,pathParameterTemplate,emScale);}
inline void glPathGlyphsNV(GLuint firstPathName,GLenum fontTarget,const void* fontName,GLbitfield fontStyle,GLsizei numGlyphs,GLenum type,const void* charcodes,GLenum handleMissingGlyphs,GLuint pathParameterTemplate,GLfloat emScale){this->_getTable()->glPathGlyphsNV(firstPathName,fontTarget,fontName,fontStyle,numGlyphs,type,charcodes,handleMissingGlyphs,pathParameterTemplate,emScale);}
inline void glPathParameterfNV(GLuint path,GLenum pname,GLfloat value){this->_getTable()->glPathParameterfNV(path,pname,value);}
inline void glPathParameterfvNV(GLuint path,GLenum pname,const GLfloat* value){this->_getTable()->glPathParameterfvNV(path,pname,value);}
inline void glPathParameteriNV(GLuint path,GLenum pname,GLint value){this->_getTable()->glPathParameteriNV(path,pname,value);}
inline void glPathParameterivNV(GLuint path,GLenum pname,const GLint* value){this->_getTable()->glPathParameterivNV(path,pname,value);}
inline void glPathStencilDepthOffsetNV(GLfloat factor,GLfloat units){this->_getTable()->glPathStencilDepthOffsetNV(factor,units);}
inline void glPathStencilFuncNV(GLenum func,GLint ref,GLuint mask){this->_getTable()->glPathStencilFuncNV(func,ref,mask);}
inline void glPathStringNV(GLuint path,GLenum format,GLsizei length,const void* pathString){this->_getTable()->glPathStringNV(path,format,length,pathString);}
inline void glPathSubCommandsNV(GLuint path,GLsizei commandStart,GLsizei commandsToDelete,GLsizei numCommands,const GLubyte* commands,GLsizei numCoords,GLenum coordType,const void* coords){this->_getTable()->glPathSubCommandsNV(path,commandStart,commandsToDelete,numCommands,commands,numCoords,coordType,coords);}
inline void glPathSubCoordsNV(GLuint path,GLsizei coordStart,GLsizei numCoords,GLenum coordType,const void* coords){this->_getTable()->glPathSubCoordsNV(path,coordStart,numCoords,coordType,coords);}
inline void glPathTexGenNV(GLenum texCoordSet,GLenum genMode,GLint components,const GLfloat* coeffs){this->_getTable()->glPathTexGenNV(texCoordSet,genMode,components,coeffs);}
inline void glPauseTransformFeedback(){this->_getTable()->glPauseTransformFeedback();}
inline void glPauseTransformFeedbackNV(){this->_getTable()->glPauseTransformFeedbackNV();}
inline void glPixelDataRangeNV(GLenum target,GLsizei length,const void* pointer){this->_getTable()->glPixelDataRangeNV(target,length,pointer);}
inline void glPixelMapfv(GLenum map,GLsizei mapsize,const GLfloat* values){this->_getTable()->glPixelMapfv(map,mapsize,values);}
inline void glPixelMapuiv(GLenum map,GLsizei mapsize,const GLuint* values){this->_getTable()->glPixelMapuiv(map,mapsize,values);}
inline void glPixelMapusv(GLenum map,GLsizei mapsize,const GLushort* values){this->_getTable()->glPixelMapusv(map,mapsize,values);}
inline void glPixelMapx(GLenum map,GLint size,const GLfixed* values){this->_getTable()->glPixelMapx(map,size,values);}
inline void glPixelStoref(GLenum pname,GLfloat param){this->_getTable()->glPixelStoref(pname,param);}
inline void glPixelStorei(GLenum pname,GLint param){this->_getTable()->glPixelStorei(pname,param);}
inline void glPixelStorex(GLenum pname,GLfixed param){this->_getTable()->glPixelStorex(pname,param);}
inline void glPixelTexGenParameterfSGIS(GLenum pname,GLfloat param){this->_getTable()->glPixelTexGenParameterfSGIS(pname,param);}
inline void glPixelTexGenParameterfvSGIS(GLenum pname,const GLfloat* params){this->_getTable()->glPixelTexGenParameterfvSGIS(pname,params);}
inline void glPixelTexGenParameteriSGIS(GLenum pname,GLint param){this->_getTable()->glPixelTexGenParameteriSGIS(pname,param);}
inline void glPixelTexGenParameterivSGIS(GLenum pname,const GLint* params){this->_getTable()->glPixelTexGenParameterivSGIS(pname,params);}
inline void glPixelTexGenSGIX(GLenum mode){this->_getTable()->glPixelTexGenSGIX(mode);}
inline void glPixelTransferf(GLenum pname,GLfloat param){this->_getTable()->glPixelTransferf(pname,param);}
inline void glPixelTransferi(GLenum pname,GLint param){this->_getTable()->glPixelTransferi(pname,param);}
inline void glPixelTransferxOES(GLenum pname,GLfixed param){this->_getTable()->glPixelTransferxOES(pname,param);}
inline void glPixelTransformParameterfEXT(GLenum target,GLenum pname,GLfloat param){this->_getTable()->glPixelTransformParameterfEXT(target,pname,param);}
inline void glPixelTransformParameterfvEXT(GLenum target,GLenum pname,const GLfloat* params){this->_getTable()->glPixelTransformParameterfvEXT(target,pname,params);}
inline void glPixelTransformParameteriEXT(GLenum target,GLenum pname,GLint param){this->_getTable()->glPixelTransformParameteriEXT(target,pname,param);}
inline void glPixelTransformParameterivEXT(GLenum target,GLenum pname,const GLint* params){this->_getTable()->glPixelTransformParameterivEXT(target,pname,params);}
inline void glPixelZoom(GLfloat xfactor,GLfloat yfactor){this->_getTable()->glPixelZoom(xfactor,yfactor);}
inline void glPixelZoomxOES(GLfixed xfactor,GLfixed yfactor){this->_getTable()->glPixelZoomxOES(xfactor,yfactor);}
inline void glPNTrianglesfATI(GLenum pname,GLfloat param){this->_getTable()->glPNTrianglesfATI(pname,param);}
inline void glPNTrianglesiATI(GLenum pname,GLint param){this->_getTable()->glPNTrianglesiATI(pname,param);}
inline void glPointParameterfARB(GLenum pname,GLfloat param){this->_getTable()->glPointParameterfARB(pname,param);}
inline void glPointParameterfEXT(GLenum pname,GLfloat param){this->_getTable()->glPointParameterfEXT(pname,param);}
inline void glPointParameterf(GLenum pname,GLfloat param){this->_getTable()->glPointParameterf(pname,param);}
inline void glPointParameterfSGIS(GLenum pname,GLfloat param){this->_getTable()->glPointParameterfSGIS(pname,param);}
inline void glPointParameterfvARB(GLenum pname,const GLfloat* params){this->_getTable()->glPointParameterfvARB(pname,params);}
inline void glPointParameterfvEXT(GLenum pname,const GLfloat* params){this->_getTable()->glPointParameterfvEXT(pname,params);}
inline void glPointParameterfv(GLenum pname,const GLfloat* params){this->_getTable()->glPointParameterfv(pname,params);}
inline void glPointParameterfvSGIS(GLenum pname,const GLfloat* params){this->_getTable()->glPointParameterfvSGIS(pname,params);}
inline void glPointParameteri(GLenum pname,GLint param){this->_getTable()->glPointParameteri(pname,param);}
inline void glPointParameteriNV(GLenum pname,GLint param){this->_getTable()->glPointParameteriNV(pname,param);}
inline void glPointParameteriv(GLenum pname,const GLint* params){this->_getTable()->glPointParameteriv(pname,params);}
inline void glPointParameterivNV(GLenum pname,const GLint* params){this->_getTable()->glPointParameterivNV(pname,params);}
inline void glPointParameterxvOES(GLenum pname,const GLfixed* params){this->_getTable()->glPointParameterxvOES(pname,params);}
inline void glPointSize(GLfloat size){this->_getTable()->glPointSize(size);}
inline void glPointSizexOES(GLfixed size){this->_getTable()->glPointSizexOES(size);}
inline void glPolygonMode(GLenum face,GLenum mode){this->_getTable()->glPolygonMode(face,mode);}
inline void glPolygonOffsetClampEXT(GLfloat factor,GLfloat units,GLfloat clamp){this->_getTable()->glPolygonOffsetClampEXT(factor,units,clamp);}
inline void glPolygonOffsetEXT(GLfloat factor,GLfloat bias){this->_getTable()->glPolygonOffsetEXT(factor,bias);}
inline void glPolygonOffset(GLfloat factor,GLfloat units){this->_getTable()->glPolygonOffset(factor,units);}
inline void glPolygonOffsetxOES(GLfixed factor,GLfixed units){this->_getTable()->glPolygonOffsetxOES(factor,units);}
inline void glPolygonStipple(const GLubyte* mask){this->_getTable()->glPolygonStipple(mask);}
inline void glPopAttrib(){this->_getTable()->glPopAttrib();}
inline void glPopClientAttrib(){this->_getTable()->glPopClientAttrib();}
inline void glPopDebugGroup(){this->_getTable()->glPopDebugGroup();}
inline void glPopGroupMarkerEXT(){this->_getTable()->glPopGroupMarkerEXT();}
inline void glPopMatrix(){this->_getTable()->glPopMatrix();}
inline void glPopName(){this->_getTable()->glPopName();}
inline void glPresentFrameDualFillNV(GLuint video_slot,GLuint64EXT minPresentTime,GLuint beginPresentTimeId,GLuint presentDurationId,GLenum type,GLenum target0,GLuint fill0,GLenum target1,GLuint fill1,GLenum target2,GLuint fill2,GLenum target3,GLuint fill3){this->_getTable()->glPresentFrameDualFillNV(video_slot,minPresentTime,beginPresentTimeId,presentDurationId,type,target0,fill0,target1,fill1,target2,fill2,target3,fill3);}
inline void glPresentFrameKeyedNV(GLuint video_slot,GLuint64EXT minPresentTime,GLuint beginPresentTimeId,GLuint presentDurationId,GLenum type,GLenum target0,GLuint fill0,GLuint key0,GLenum target1,GLuint fill1,GLuint key1){this->_getTable()->glPresentFrameKeyedNV(video_slot,minPresentTime,beginPresentTimeId,presentDurationId,type,target0,fill0,key0,target1,fill1,key1);}
inline void glPrimitiveBoundingBoxARB(GLfloat minX,GLfloat minY,GLfloat minZ,GLfloat minW,GLfloat maxX,GLfloat maxY,GLfloat maxZ,GLfloat maxW){this->_getTable()->glPrimitiveBoundingBoxARB(minX,minY,minZ,minW,maxX,maxY,maxZ,maxW);}
inline void glPrimitiveRestartIndex(GLuint index){this->_getTable()->glPrimitiveRestartIndex(index);}
inline void glPrimitiveRestartIndexNV(GLuint index){this->_getTable()->glPrimitiveRestartIndexNV(index);}
inline void glPrimitiveRestartNV(){this->_getTable()->glPrimitiveRestartNV();}
inline void glPrioritizeTexturesEXT(GLsizei n,const GLuint* textures,const GLclampf* priorities){this->_getTable()->glPrioritizeTexturesEXT(n,textures,priorities);}
inline void glPrioritizeTextures(GLsizei n,const GLuint* textures,const GLclampf* priorities){this->_getTable()->glPrioritizeTextures(n,textures,priorities);}
inline void glPrioritizeTexturesxOES(GLsizei n,const GLuint* textures,const GLfixed* priorities){this->_getTable()->glPrioritizeTexturesxOES(n,textures,priorities);}
inline void glProgramBinary(GLuint program,GLenum binaryFormat,const void* binary,GLsizei length){this->_getTable()->glProgramBinary(program,binaryFormat,binary,length);}
inline void glProgramBufferParametersfvNV(GLenum target,GLuint bindingIndex,GLuint wordIndex,GLsizei count,const GLfloat* params){this->_getTable()->glProgramBufferParametersfvNV(target,bindingIndex,wordIndex,count,params);}
inline void glProgramBufferParametersIivNV(GLenum target,GLuint bindingIndex,GLuint wordIndex,GLsizei count,const GLint* params){this->_getTable()->glProgramBufferParametersIivNV(target,bindingIndex,wordIndex,count,params);}
inline void glProgramBufferParametersIuivNV(GLenum target,GLuint bindingIndex,GLuint wordIndex,GLsizei count,const GLuint* params){this->_getTable()->glProgramBufferParametersIuivNV(target,bindingIndex,wordIndex,count,params);}
inline void glProgramEnvParameter4dARB(GLenum target,GLuint index,GLdouble x,GLdouble y,GLdouble z,GLdouble w){this->_getTable()->glProgramEnvParameter4dARB(target,index,x,y,z,w);}
inline void glProgramEnvParameter4dvARB(GLenum target,GLuint index,const GLdouble* params){this->_getTable()->glProgramEnvParameter4dvARB(target,index,params);}
inline void glProgramEnvParameter4fARB(GLenum target,GLuint index,GLfloat x,GLfloat y,GLfloat z,GLfloat w){this->_getTable()->glProgramEnvParameter4fARB(target,index,x,y,z,w);}
inline void glProgramEnvParameter4fvARB(GLenum target,GLuint index,const GLfloat* params){this->_getTable()->glProgramEnvParameter4fvARB(target,index,params);}
inline void glProgramEnvParameterI4iNV(GLenum target,GLuint index,GLint x,GLint y,GLint z,GLint w){this->_getTable()->glProgramEnvParameterI4iNV(target,index,x,y,z,w);}
inline void glProgramEnvParameterI4ivNV(GLenum target,GLuint index,const GLint* params){this->_getTable()->glProgramEnvParameterI4ivNV(target,index,params);}
inline void glProgramEnvParameterI4uiNV(GLenum target,GLuint index,GLuint x,GLuint y,GLuint z,GLuint w){this->_getTable()->glProgramEnvParameterI4uiNV(target,index,x,y,z,w);}
inline void glProgramEnvParameterI4uivNV(GLenum target,GLuint index,const GLuint* params){this->_getTable()->glProgramEnvParameterI4uivNV(target,index,params);}
inline void glProgramEnvParameters4fvEXT(GLenum target,GLuint index,GLsizei count,const GLfloat* params){this->_getTable()->glProgramEnvParameters4fvEXT(target,index,count,params);}
inline void glProgramEnvParametersI4ivNV(GLenum target,GLuint index,GLsizei count,const GLint* params){this->_getTable()->glProgramEnvParametersI4ivNV(target,index,count,params);}
inline void glProgramEnvParametersI4uivNV(GLenum target,GLuint index,GLsizei count,const GLuint* params){this->_getTable()->glProgramEnvParametersI4uivNV(target,index,count,params);}
inline void glProgramLocalParameter4dARB(GLenum target,GLuint index,GLdouble x,GLdouble y,GLdouble z,GLdouble w){this->_getTable()->glProgramLocalParameter4dARB(target,index,x,y,z,w);}
inline void glProgramLocalParameter4dvARB(GLenum target,GLuint index,const GLdouble* params){this->_getTable()->glProgramLocalParameter4dvARB(target,index,params);}
inline void glProgramLocalParameter4fARB(GLenum target,GLuint index,GLfloat x,GLfloat y,GLfloat z,GLfloat w){this->_getTable()->glProgramLocalParameter4fARB(target,index,x,y,z,w);}
inline void glProgramLocalParameter4fvARB(GLenum target,GLuint index,const GLfloat* params){this->_getTable()->glProgramLocalParameter4fvARB(target,index,params);}
inline void glProgramLocalParameterI4iNV(GLenum target,GLuint index,GLint x,GLint y,GLint z,GLint w){this->_getTable()->glProgramLocalParameterI4iNV(target,index,x,y,z,w);}
inline void glProgramLocalParameterI4ivNV(GLenum target,GLuint index,const GLint* params){this->_getTable()->glProgramLocalParameterI4ivNV(target,index,params);}
inline void glProgramLocalParameterI4uiNV(GLenum target,GLuint index,GLuint x,GLuint y,GLuint z,GLuint w){this->_getTable()->glProgramLocalParameterI4uiNV(target,index,x,y,z,w);}
inline void glProgramLocalParameterI4uivNV(GLenum target,GLuint index,const GLuint* params){this->_getTable()->glProgramLocalParameterI4uivNV(target,index,params);}
inline void glProgramLocalParameters4fvEXT(GLenum target,GLuint index,GLsizei count,const GLfloat* params){this->_getTable()->glProgramLocalParameters4fvEXT(target,index,count,params);}
inline void glProgramLocalParametersI4ivNV(GLenum target,GLuint index,GLsizei count,const GLint* params){this->_getTable()->glProgramLocalParametersI4ivNV(target,index,count,params);}
inline void glProgramLocalParametersI4uivNV(GLenum target,GLuint index,GLsizei count,const GLuint* params){this->_getTable()->glProgramLocalParametersI4uivNV(target,index,count,params);}
inline void glProgramNamedParameter4dNV(GLuint id,GLsizei len,const GLubyte* name,GLdouble x,GLdouble y,GLdouble z,GLdouble w){this->_getTable()->glProgramNamedParameter4dNV(id,len,name,x,y,z,w);}
inline void glProgramNamedParameter4dvNV(GLuint id,GLsizei len,const GLubyte* name,const GLdouble* v){this->_getTable()->glProgramNamedParameter4dvNV(id,len,name,v);}
inline void glProgramNamedParameter4fNV(GLuint id,GLsizei len,const GLubyte* name,GLfloat x,GLfloat y,GLfloat z,GLfloat w){this->_getTable()->glProgramNamedParameter4fNV(id,len,name,x,y,z,w);}
inline void glProgramNamedParameter4fvNV(GLuint id,GLsizei len,const GLubyte* name,const GLfloat* v){this->_getTable()->glProgramNamedParameter4fvNV(id,len,name,v);}
inline void glProgramParameter4dNV(GLenum target,GLuint index,GLdouble x,GLdouble y,GLdouble z,GLdouble w){this->_getTable()->glProgramParameter4dNV(target,index,x,y,z,w);}
inline void glProgramParameter4dvNV(GLenum target,GLuint index,const GLdouble* v){this->_getTable()->glProgramParameter4dvNV(target,index,v);}
inline void glProgramParameter4fNV(GLenum target,GLuint index,GLfloat x,GLfloat y,GLfloat z,GLfloat w){this->_getTable()->glProgramParameter4fNV(target,index,x,y,z,w);}
inline void glProgramParameter4fvNV(GLenum target,GLuint index,const GLfloat* v){this->_getTable()->glProgramParameter4fvNV(target,index,v);}
inline void glProgramParameteriARB(GLuint program,GLenum pname,GLint value){this->_getTable()->glProgramParameteriARB(program,pname,value);}
inline void glProgramParameteriEXT(GLuint program,GLenum pname,GLint value){this->_getTable()->glProgramParameteriEXT(program,pname,value);}
inline void glProgramParameteri(GLuint program,GLenum pname,GLint value){this->_getTable()->glProgramParameteri(program,pname,value);}
inline void glProgramParameters4dvNV(GLenum target,GLuint index,GLsizei count,const GLdouble* v){this->_getTable()->glProgramParameters4dvNV(target,index,count,v);}
inline void glProgramParameters4fvNV(GLenum target,GLuint index,GLsizei count,const GLfloat* v){this->_getTable()->glProgramParameters4fvNV(target,index,count,v);}
inline void glProgramPathFragmentInputGenNV(GLuint program,GLint location,GLenum genMode,GLint components,const GLfloat* coeffs){this->_getTable()->glProgramPathFragmentInputGenNV(program,location,genMode,components,coeffs);}
inline void glProgramStringARB(GLenum target,GLenum format,GLsizei len,const void* string){this->_getTable()->glProgramStringARB(target,format,len,string);}
inline void glProgramSubroutineParametersuivNV(GLenum target,GLsizei count,const GLuint* params){this->_getTable()->glProgramSubroutineParametersuivNV(target,count,params);}
inline void glProgramUniform1dEXT(GLuint program,GLint location,GLdouble x){this->_getTable()->glProgramUniform1dEXT(program,location,x);}
inline void glProgramUniform1d(GLuint program,GLint location,GLdouble v0){this->_getTable()->glProgramUniform1d(program,location,v0);}
inline void glProgramUniform1dvEXT(GLuint program,GLint location,GLsizei count,const GLdouble* value){this->_getTable()->glProgramUniform1dvEXT(program,location,count,value);}
inline void glProgramUniform1dv(GLuint program,GLint location,GLsizei count,const GLdouble* value){this->_getTable()->glProgramUniform1dv(program,location,count,value);}
inline void glProgramUniform1fEXT(GLuint program,GLint location,GLfloat v0){this->_getTable()->glProgramUniform1fEXT(program,location,v0);}
inline void glProgramUniform1f(GLuint program,GLint location,GLfloat v0){this->_getTable()->glProgramUniform1f(program,location,v0);}
inline void glProgramUniform1fvEXT(GLuint program,GLint location,GLsizei count,const GLfloat* value){this->_getTable()->glProgramUniform1fvEXT(program,location,count,value);}
inline void glProgramUniform1fv(GLuint program,GLint location,GLsizei count,const GLfloat* value){this->_getTable()->glProgramUniform1fv(program,location,count,value);}
inline void glProgramUniform1i64ARB(GLuint program,GLint location,GLint64 x){this->_getTable()->glProgramUniform1i64ARB(program,location,x);}
inline void glProgramUniform1i64NV(GLuint program,GLint location,GLint64EXT x){this->_getTable()->glProgramUniform1i64NV(program,location,x);}
inline void glProgramUniform1i64vARB(GLuint program,GLint location,GLsizei count,const GLint64* value){this->_getTable()->glProgramUniform1i64vARB(program,location,count,value);}
inline void glProgramUniform1i64vNV(GLuint program,GLint location,GLsizei count,const GLint64EXT* value){this->_getTable()->glProgramUniform1i64vNV(program,location,count,value);}
inline void glProgramUniform1iEXT(GLuint program,GLint location,GLint v0){this->_getTable()->glProgramUniform1iEXT(program,location,v0);}
inline void glProgramUniform1i(GLuint program,GLint location,GLint v0){this->_getTable()->glProgramUniform1i(program,location,v0);}
inline void glProgramUniform1ivEXT(GLuint program,GLint location,GLsizei count,const GLint* value){this->_getTable()->glProgramUniform1ivEXT(program,location,count,value);}
inline void glProgramUniform1iv(GLuint program,GLint location,GLsizei count,const GLint* value){this->_getTable()->glProgramUniform1iv(program,location,count,value);}
inline void glProgramUniform1ui64ARB(GLuint program,GLint location,GLuint64 x){this->_getTable()->glProgramUniform1ui64ARB(program,location,x);}
inline void glProgramUniform1ui64NV(GLuint program,GLint location,GLuint64EXT x){this->_getTable()->glProgramUniform1ui64NV(program,location,x);}
inline void glProgramUniform1ui64vARB(GLuint program,GLint location,GLsizei count,const GLuint64* value){this->_getTable()->glProgramUniform1ui64vARB(program,location,count,value);}
inline void glProgramUniform1ui64vNV(GLuint program,GLint location,GLsizei count,const GLuint64EXT* value){this->_getTable()->glProgramUniform1ui64vNV(program,location,count,value);}
inline void glProgramUniform1uiEXT(GLuint program,GLint location,GLuint v0){this->_getTable()->glProgramUniform1uiEXT(program,location,v0);}
inline void glProgramUniform1ui(GLuint program,GLint location,GLuint v0){this->_getTable()->glProgramUniform1ui(program,location,v0);}
inline void glProgramUniform1uivEXT(GLuint program,GLint location,GLsizei count,const GLuint* value){this->_getTable()->glProgramUniform1uivEXT(program,location,count,value);}
inline void glProgramUniform1uiv(GLuint program,GLint location,GLsizei count,const GLuint* value){this->_getTable()->glProgramUniform1uiv(program,location,count,value);}
inline void glProgramUniform2dEXT(GLuint program,GLint location,GLdouble x,GLdouble y){this->_getTable()->glProgramUniform2dEXT(program,location,x,y);}
inline void glProgramUniform2d(GLuint program,GLint location,GLdouble v0,GLdouble v1){this->_getTable()->glProgramUniform2d(program,location,v0,v1);}
inline void glProgramUniform2dvEXT(GLuint program,GLint location,GLsizei count,const GLdouble* value){this->_getTable()->glProgramUniform2dvEXT(program,location,count,value);}
inline void glProgramUniform2dv(GLuint program,GLint location,GLsizei count,const GLdouble* value){this->_getTable()->glProgramUniform2dv(program,location,count,value);}
inline void glProgramUniform2fEXT(GLuint program,GLint location,GLfloat v0,GLfloat v1){this->_getTable()->glProgramUniform2fEXT(program,location,v0,v1);}
inline void glProgramUniform2f(GLuint program,GLint location,GLfloat v0,GLfloat v1){this->_getTable()->glProgramUniform2f(program,location,v0,v1);}
inline void glProgramUniform2fvEXT(GLuint program,GLint location,GLsizei count,const GLfloat* value){this->_getTable()->glProgramUniform2fvEXT(program,location,count,value);}
inline void glProgramUniform2fv(GLuint program,GLint location,GLsizei count,const GLfloat* value){this->_getTable()->glProgramUniform2fv(program,location,count,value);}
inline void glProgramUniform2i64ARB(GLuint program,GLint location,GLint64 x,GLint64 y){this->_getTable()->glProgramUniform2i64ARB(program,location,x,y);}
inline void glProgramUniform2i64NV(GLuint program,GLint location,GLint64EXT x,GLint64EXT y){this->_getTable()->glProgramUniform2i64NV(program,location,x,y);}
inline void glProgramUniform2i64vARB(GLuint program,GLint location,GLsizei count,const GLint64* value){this->_getTable()->glProgramUniform2i64vARB(program,location,count,value);}
inline void glProgramUniform2i64vNV(GLuint program,GLint location,GLsizei count,const GLint64EXT* value){this->_getTable()->glProgramUniform2i64vNV(program,location,count,value);}
inline void glProgramUniform2iEXT(GLuint program,GLint location,GLint v0,GLint v1){this->_getTable()->glProgramUniform2iEXT(program,location,v0,v1);}
inline void glProgramUniform2i(GLuint program,GLint location,GLint v0,GLint v1){this->_getTable()->glProgramUniform2i(program,location,v0,v1);}
inline void glProgramUniform2ivEXT(GLuint program,GLint location,GLsizei count,const GLint* value){this->_getTable()->glProgramUniform2ivEXT(program,location,count,value);}
inline void glProgramUniform2iv(GLuint program,GLint location,GLsizei count,const GLint* value){this->_getTable()->glProgramUniform2iv(program,location,count,value);}
inline void glProgramUniform2ui64ARB(GLuint program,GLint location,GLuint64 x,GLuint64 y){this->_getTable()->glProgramUniform2ui64ARB(program,location,x,y);}
inline void glProgramUniform2ui64NV(GLuint program,GLint location,GLuint64EXT x,GLuint64EXT y){this->_getTable()->glProgramUniform2ui64NV(program,location,x,y);}
inline void glProgramUniform2ui64vARB(GLuint program,GLint location,GLsizei count,const GLuint64* value){this->_getTable()->glProgramUniform2ui64vARB(program,location,count,value);}
inline void glProgramUniform2ui64vNV(GLuint program,GLint location,GLsizei count,const GLuint64EXT* value){this->_getTable()->glProgramUniform2ui64vNV(program,location,count,value);}
inline void glProgramUniform2uiEXT(GLuint program,GLint location,GLuint v0,GLuint v1){this->_getTable()->glProgramUniform2uiEXT(program,location,v0,v1);}
inline void glProgramUniform2ui(GLuint program,GLint location,GLuint v0,GLuint v1){this->_getTable()->glProgramUniform2ui(program,location,v0,v1);}
inline void glProgramUniform2uivEXT(GLuint program,GLint location,GLsizei count,const GLuint* value){this->_getTable()->glProgramUniform2uivEXT(program,location,count,value);}
inline void glProgramUniform2uiv(GLuint program,GLint location,GLsizei count,const GLuint* value){this->_getTable()->glProgramUniform2uiv(program,location,count,value);}
inline void glProgramUniform3dEXT(GLuint program,GLint location,GLdouble x,GLdouble y,GLdouble z){this->_getTable()->glProgramUniform3dEXT(program,location,x,y,z);}
inline void glProgramUniform3d(GLuint program,GLint location,GLdouble v0,GLdouble v1,GLdouble v2){this->_getTable()->glProgramUniform3d(program,location,v0,v1,v2);}
inline void glProgramUniform3dvEXT(GLuint program,GLint location,GLsizei count,const GLdouble* value){this->_getTable()->glProgramUniform3dvEXT(program,location,count,value);}
inline void glProgramUniform3dv(GLuint program,GLint location,GLsizei count,const GLdouble* value){this->_getTable()->glProgramUniform3dv(program,location,count,value);}
inline void glProgramUniform3fEXT(GLuint program,GLint location,GLfloat v0,GLfloat v1,GLfloat v2){this->_getTable()->glProgramUniform3fEXT(program,location,v0,v1,v2);}
inline void glProgramUniform3f(GLuint program,GLint location,GLfloat v0,GLfloat v1,GLfloat v2){this->_getTable()->glProgramUniform3f(program,location,v0,v1,v2);}
inline void glProgramUniform3fvEXT(GLuint program,GLint location,GLsizei count,const GLfloat* value){this->_getTable()->glProgramUniform3fvEXT(program,location,count,value);}
inline void glProgramUniform3fv(GLuint program,GLint location,GLsizei count,const GLfloat* value){this->_getTable()->glProgramUniform3fv(program,location,count,value);}
inline void glProgramUniform3i64ARB(GLuint program,GLint location,GLint64 x,GLint64 y,GLint64 z){this->_getTable()->glProgramUniform3i64ARB(program,location,x,y,z);}
inline void glProgramUniform3i64NV(GLuint program,GLint location,GLint64EXT x,GLint64EXT y,GLint64EXT z){this->_getTable()->glProgramUniform3i64NV(program,location,x,y,z);}
inline void glProgramUniform3i64vARB(GLuint program,GLint location,GLsizei count,const GLint64* value){this->_getTable()->glProgramUniform3i64vARB(program,location,count,value);}
inline void glProgramUniform3i64vNV(GLuint program,GLint location,GLsizei count,const GLint64EXT* value){this->_getTable()->glProgramUniform3i64vNV(program,location,count,value);}
inline void glProgramUniform3iEXT(GLuint program,GLint location,GLint v0,GLint v1,GLint v2){this->_getTable()->glProgramUniform3iEXT(program,location,v0,v1,v2);}
inline void glProgramUniform3i(GLuint program,GLint location,GLint v0,GLint v1,GLint v2){this->_getTable()->glProgramUniform3i(program,location,v0,v1,v2);}
inline void glProgramUniform3ivEXT(GLuint program,GLint location,GLsizei count,const GLint* value){this->_getTable()->glProgramUniform3ivEXT(program,location,count,value);}
inline void glProgramUniform3iv(GLuint program,GLint location,GLsizei count,const GLint* value){this->_getTable()->glProgramUniform3iv(program,location,count,value);}
inline void glProgramUniform3ui64ARB(GLuint program,GLint location,GLuint64 x,GLuint64 y,GLuint64 z){this->_getTable()->glProgramUniform3ui64ARB(program,location,x,y,z);}
inline void glProgramUniform3ui64NV(GLuint program,GLint location,GLuint64EXT x,GLuint64EXT y,GLuint64EXT z){this->_getTable()->glProgramUniform3ui64NV(program,location,x,y,z);}
inline void glProgramUniform3ui64vARB(GLuint program,GLint location,GLsizei count,const GLuint64* value){this->_getTable()->glProgramUniform3ui64vARB(program,location,count,value);}
inline void glProgramUniform3ui64vNV(GLuint program,GLint location,GLsizei count,const GLuint64EXT* value){this->_getTable()->glProgramUniform3ui64vNV(program,location,count,value);}
inline void glProgramUniform3uiEXT(GLuint program,GLint location,GLuint v0,GLuint v1,GLuint v2){this->_getTable()->glProgramUniform3uiEXT(program,location,v0,v1,v2);}
inline void glProgramUniform3ui(GLuint program,GLint location,GLuint v0,GLuint v1,GLuint v2){this->_getTable()->glProgramUniform3ui(program,location,v0,v1,v2);}
inline void glProgramUniform3uivEXT(GLuint program,GLint location,GLsizei count,const GLuint* value){this->_getTable()->glProgramUniform3uivEXT(program,location,count,value);}
inline void glProgramUniform3uiv(GLuint program,GLint location,GLsizei count,const GLuint* value){this->_getTable()->glProgramUniform3uiv(program,location,count,value);}
inline void glProgramUniform4dEXT(GLuint program,GLint location,GLdouble x,GLdouble y,GLdouble z,GLdouble w){this->_getTable()->glProgramUniform4dEXT(program,location,x,y,z,w);}
inline void glProgramUniform4d(GLuint program,GLint location,GLdouble v0,GLdouble v1,GLdouble v2,GLdouble v3){this->_getTable()->glProgramUniform4d(program,location,v0,v1,v2,v3);}
inline void glProgramUniform4dvEXT(GLuint program,GLint location,GLsizei count,const GLdouble* value){this->_getTable()->glProgramUniform4dvEXT(program,location,count,value);}
inline void glProgramUniform4dv(GLuint program,GLint location,GLsizei count,const GLdouble* value){this->_getTable()->glProgramUniform4dv(program,location,count,value);}
inline void glProgramUniform4fEXT(GLuint program,GLint location,GLfloat v0,GLfloat v1,GLfloat v2,GLfloat v3){this->_getTable()->glProgramUniform4fEXT(program,location,v0,v1,v2,v3);}
inline void glProgramUniform4f(GLuint program,GLint location,GLfloat v0,GLfloat v1,GLfloat v2,GLfloat v3){this->_getTable()->glProgramUniform4f(program,location,v0,v1,v2,v3);}
inline void glProgramUniform4fvEXT(GLuint program,GLint location,GLsizei count,const GLfloat* value){this->_getTable()->glProgramUniform4fvEXT(program,location,count,value);}
inline void glProgramUniform4fv(GLuint program,GLint location,GLsizei count,const GLfloat* value){this->_getTable()->glProgramUniform4fv(program,location,count,value);}
inline void glProgramUniform4i64ARB(GLuint program,GLint location,GLint64 x,GLint64 y,GLint64 z,GLint64 w){this->_getTable()->glProgramUniform4i64ARB(program,location,x,y,z,w);}
inline void glProgramUniform4i64NV(GLuint program,GLint location,GLint64EXT x,GLint64EXT y,GLint64EXT z,GLint64EXT w){this->_getTable()->glProgramUniform4i64NV(program,location,x,y,z,w);}
inline void glProgramUniform4i64vARB(GLuint program,GLint location,GLsizei count,const GLint64* value){this->_getTable()->glProgramUniform4i64vARB(program,location,count,value);}
inline void glProgramUniform4i64vNV(GLuint program,GLint location,GLsizei count,const GLint64EXT* value){this->_getTable()->glProgramUniform4i64vNV(program,location,count,value);}
inline void glProgramUniform4iEXT(GLuint program,GLint location,GLint v0,GLint v1,GLint v2,GLint v3){this->_getTable()->glProgramUniform4iEXT(program,location,v0,v1,v2,v3);}
inline void glProgramUniform4i(GLuint program,GLint location,GLint v0,GLint v1,GLint v2,GLint v3){this->_getTable()->glProgramUniform4i(program,location,v0,v1,v2,v3);}
inline void glProgramUniform4ivEXT(GLuint program,GLint location,GLsizei count,const GLint* value){this->_getTable()->glProgramUniform4ivEXT(program,location,count,value);}
inline void glProgramUniform4iv(GLuint program,GLint location,GLsizei count,const GLint* value){this->_getTable()->glProgramUniform4iv(program,location,count,value);}
inline void glProgramUniform4ui64ARB(GLuint program,GLint location,GLuint64 x,GLuint64 y,GLuint64 z,GLuint64 w){this->_getTable()->glProgramUniform4ui64ARB(program,location,x,y,z,w);}
inline void glProgramUniform4ui64NV(GLuint program,GLint location,GLuint64EXT x,GLuint64EXT y,GLuint64EXT z,GLuint64EXT w){this->_getTable()->glProgramUniform4ui64NV(program,location,x,y,z,w);}
inline void glProgramUniform4ui64vARB(GLuint program,GLint location,GLsizei count,const GLuint64* value){this->_getTable()->glProgramUniform4ui64vARB(program,location,count,value);}
inline void glProgramUniform4ui64vNV(GLuint program,GLint location,GLsizei count,const GLuint64EXT* value){this->_getTable()->glProgramUniform4ui64vNV(program,location,count,value);}
inline void glProgramUniform4uiEXT(GLuint program,GLint location,GLuint v0,GLuint v1,GLuint v2,GLuint v3){this->_getTable()->glProgramUniform4uiEXT(program,location,v0,v1,v2,v3);}
inline void glProgramUniform4ui(GLuint program,GLint location,GLuint v0,GLuint v1,GLuint v2,GLuint v3){this->_getTable()->glProgramUniform4ui(program,location,v0,v1,v2,v3);}
inline void glProgramUniform4uivEXT(GLuint program,GLint location,GLsizei count,const GLuint* value){this->_getTable()->glProgramUniform4uivEXT(program,location,count,value);}
inline void glProgramUniform4uiv(GLuint program,GLint location,GLsizei count,const GLuint* value){this->_getTable()->glProgramUniform4uiv(program,location,count,value);}
inline void glProgramUniformHandleui64ARB(GLuint program,GLint location,GLuint64 value){this->_getTable()->glProgramUniformHandleui64ARB(program,location,value);}
inline void glProgramUniformHandleui64NV(GLuint program,GLint location,GLuint64 value){this->_getTable()->glProgramUniformHandleui64NV(program,location,value);}
inline void glProgramUniformHandleui64vARB(GLuint program,GLint location,GLsizei count,const GLuint64* values){this->_getTable()->glProgramUniformHandleui64vARB(program,location,count,values);}
inline void glProgramUniformHandleui64vNV(GLuint program,GLint location,GLsizei count,const GLuint64* values){this->_getTable()->glProgramUniformHandleui64vNV(program,location,count,values);}
inline void glProgramUniformMatrix2dvEXT(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLdouble* value){this->_getTable()->glProgramUniformMatrix2dvEXT(program,location,count,transpose,value);}
inline void glProgramUniformMatrix2dv(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLdouble* value){this->_getTable()->glProgramUniformMatrix2dv(program,location,count,transpose,value);}
inline void glProgramUniformMatrix2fvEXT(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLfloat* value){this->_getTable()->glProgramUniformMatrix2fvEXT(program,location,count,transpose,value);}
inline void glProgramUniformMatrix2fv(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLfloat* value){this->_getTable()->glProgramUniformMatrix2fv(program,location,count,transpose,value);}
inline void glProgramUniformMatrix2x3dvEXT(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLdouble* value){this->_getTable()->glProgramUniformMatrix2x3dvEXT(program,location,count,transpose,value);}
inline void glProgramUniformMatrix2x3dv(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLdouble* value){this->_getTable()->glProgramUniformMatrix2x3dv(program,location,count,transpose,value);}
inline void glProgramUniformMatrix2x3fvEXT(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLfloat* value){this->_getTable()->glProgramUniformMatrix2x3fvEXT(program,location,count,transpose,value);}
inline void glProgramUniformMatrix2x3fv(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLfloat* value){this->_getTable()->glProgramUniformMatrix2x3fv(program,location,count,transpose,value);}
inline void glProgramUniformMatrix2x4dvEXT(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLdouble* value){this->_getTable()->glProgramUniformMatrix2x4dvEXT(program,location,count,transpose,value);}
inline void glProgramUniformMatrix2x4dv(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLdouble* value){this->_getTable()->glProgramUniformMatrix2x4dv(program,location,count,transpose,value);}
inline void glProgramUniformMatrix2x4fvEXT(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLfloat* value){this->_getTable()->glProgramUniformMatrix2x4fvEXT(program,location,count,transpose,value);}
inline void glProgramUniformMatrix2x4fv(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLfloat* value){this->_getTable()->glProgramUniformMatrix2x4fv(program,location,count,transpose,value);}
inline void glProgramUniformMatrix3dvEXT(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLdouble* value){this->_getTable()->glProgramUniformMatrix3dvEXT(program,location,count,transpose,value);}
inline void glProgramUniformMatrix3dv(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLdouble* value){this->_getTable()->glProgramUniformMatrix3dv(program,location,count,transpose,value);}
inline void glProgramUniformMatrix3fvEXT(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLfloat* value){this->_getTable()->glProgramUniformMatrix3fvEXT(program,location,count,transpose,value);}
inline void glProgramUniformMatrix3fv(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLfloat* value){this->_getTable()->glProgramUniformMatrix3fv(program,location,count,transpose,value);}
inline void glProgramUniformMatrix3x2dvEXT(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLdouble* value){this->_getTable()->glProgramUniformMatrix3x2dvEXT(program,location,count,transpose,value);}
inline void glProgramUniformMatrix3x2dv(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLdouble* value){this->_getTable()->glProgramUniformMatrix3x2dv(program,location,count,transpose,value);}
inline void glProgramUniformMatrix3x2fvEXT(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLfloat* value){this->_getTable()->glProgramUniformMatrix3x2fvEXT(program,location,count,transpose,value);}
inline void glProgramUniformMatrix3x2fv(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLfloat* value){this->_getTable()->glProgramUniformMatrix3x2fv(program,location,count,transpose,value);}
inline void glProgramUniformMatrix3x4dvEXT(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLdouble* value){this->_getTable()->glProgramUniformMatrix3x4dvEXT(program,location,count,transpose,value);}
inline void glProgramUniformMatrix3x4dv(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLdouble* value){this->_getTable()->glProgramUniformMatrix3x4dv(program,location,count,transpose,value);}
inline void glProgramUniformMatrix3x4fvEXT(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLfloat* value){this->_getTable()->glProgramUniformMatrix3x4fvEXT(program,location,count,transpose,value);}
inline void glProgramUniformMatrix3x4fv(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLfloat* value){this->_getTable()->glProgramUniformMatrix3x4fv(program,location,count,transpose,value);}
inline void glProgramUniformMatrix4dvEXT(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLdouble* value){this->_getTable()->glProgramUniformMatrix4dvEXT(program,location,count,transpose,value);}
inline void glProgramUniformMatrix4dv(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLdouble* value){this->_getTable()->glProgramUniformMatrix4dv(program,location,count,transpose,value);}
inline void glProgramUniformMatrix4fvEXT(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLfloat* value){this->_getTable()->glProgramUniformMatrix4fvEXT(program,location,count,transpose,value);}
inline void glProgramUniformMatrix4fv(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLfloat* value){this->_getTable()->glProgramUniformMatrix4fv(program,location,count,transpose,value);}
inline void glProgramUniformMatrix4x2dvEXT(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLdouble* value){this->_getTable()->glProgramUniformMatrix4x2dvEXT(program,location,count,transpose,value);}
inline void glProgramUniformMatrix4x2dv(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLdouble* value){this->_getTable()->glProgramUniformMatrix4x2dv(program,location,count,transpose,value);}
inline void glProgramUniformMatrix4x2fvEXT(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLfloat* value){this->_getTable()->glProgramUniformMatrix4x2fvEXT(program,location,count,transpose,value);}
inline void glProgramUniformMatrix4x2fv(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLfloat* value){this->_getTable()->glProgramUniformMatrix4x2fv(program,location,count,transpose,value);}
inline void glProgramUniformMatrix4x3dvEXT(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLdouble* value){this->_getTable()->glProgramUniformMatrix4x3dvEXT(program,location,count,transpose,value);}
inline void glProgramUniformMatrix4x3dv(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLdouble* value){this->_getTable()->glProgramUniformMatrix4x3dv(program,location,count,transpose,value);}
inline void glProgramUniformMatrix4x3fvEXT(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLfloat* value){this->_getTable()->glProgramUniformMatrix4x3fvEXT(program,location,count,transpose,value);}
inline void glProgramUniformMatrix4x3fv(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLfloat* value){this->_getTable()->glProgramUniformMatrix4x3fv(program,location,count,transpose,value);}
inline void glProgramUniformui64NV(GLuint program,GLint location,GLuint64EXT value){this->_getTable()->glProgramUniformui64NV(program,location,value);}
inline void glProgramUniformui64vNV(GLuint program,GLint location,GLsizei count,const GLuint64EXT* value){this->_getTable()->glProgramUniformui64vNV(program,location,count,value);}
inline void glProgramVertexLimitNV(GLenum target,GLint limit){this->_getTable()->glProgramVertexLimitNV(target,limit);}
inline void glProvokingVertexEXT(GLenum mode){this->_getTable()->glProvokingVertexEXT(mode);}
inline void glProvokingVertex(GLenum mode){this->_getTable()->glProvokingVertex(mode);}
inline void glPushAttrib(GLbitfield mask){this->_getTable()->glPushAttrib(mask);}
inline void glPushClientAttribDefaultEXT(GLbitfield mask){this->_getTable()->glPushClientAttribDefaultEXT(mask);}
inline void glPushClientAttrib(GLbitfield mask){this->_getTable()->glPushClientAttrib(mask);}
inline void glPushDebugGroup(GLenum source,GLuint id,GLsizei length,const GLchar* message){this->_getTable()->glPushDebugGroup(source,id,length,message);}
inline void glPushGroupMarkerEXT(GLsizei length,const GLchar* marker){this->_getTable()->glPushGroupMarkerEXT(length,marker);}
inline void glPushMatrix(){this->_getTable()->glPushMatrix();}
inline void glPushName(GLuint name){this->_getTable()->glPushName(name);}
inline void glQueryCounter(GLuint id,GLenum target){this->_getTable()->glQueryCounter(id,target);}
inline void glQueryObjectParameteruiAMD(GLenum target,GLuint id,GLenum pname,GLuint param){this->_getTable()->glQueryObjectParameteruiAMD(target,id,pname,param);}
inline void glRasterPos2d(GLdouble x,GLdouble y){this->_getTable()->glRasterPos2d(x,y);}
inline void glRasterPos2dv(const GLdouble* v){this->_getTable()->glRasterPos2dv(v);}
inline void glRasterPos2f(GLfloat x,GLfloat y){this->_getTable()->glRasterPos2f(x,y);}
inline void glRasterPos2fv(const GLfloat* v){this->_getTable()->glRasterPos2fv(v);}
inline void glRasterPos2i(GLint x,GLint y){this->_getTable()->glRasterPos2i(x,y);}
inline void glRasterPos2iv(const GLint* v){this->_getTable()->glRasterPos2iv(v);}
inline void glRasterPos2s(GLshort x,GLshort y){this->_getTable()->glRasterPos2s(x,y);}
inline void glRasterPos2sv(const GLshort* v){this->_getTable()->glRasterPos2sv(v);}
inline void glRasterPos2xOES(GLfixed x,GLfixed y){this->_getTable()->glRasterPos2xOES(x,y);}
inline void glRasterPos2xvOES(const GLfixed* coords){this->_getTable()->glRasterPos2xvOES(coords);}
inline void glRasterPos3d(GLdouble x,GLdouble y,GLdouble z){this->_getTable()->glRasterPos3d(x,y,z);}
inline void glRasterPos3dv(const GLdouble* v){this->_getTable()->glRasterPos3dv(v);}
inline void glRasterPos3f(GLfloat x,GLfloat y,GLfloat z){this->_getTable()->glRasterPos3f(x,y,z);}
inline void glRasterPos3fv(const GLfloat* v){this->_getTable()->glRasterPos3fv(v);}
inline void glRasterPos3i(GLint x,GLint y,GLint z){this->_getTable()->glRasterPos3i(x,y,z);}
inline void glRasterPos3iv(const GLint* v){this->_getTable()->glRasterPos3iv(v);}
inline void glRasterPos3s(GLshort x,GLshort y,GLshort z){this->_getTable()->glRasterPos3s(x,y,z);}
inline void glRasterPos3sv(const GLshort* v){this->_getTable()->glRasterPos3sv(v);}
inline void glRasterPos3xOES(GLfixed x,GLfixed y,GLfixed z){this->_getTable()->glRasterPos3xOES(x,y,z);}
inline void glRasterPos3xvOES(const GLfixed* coords){this->_getTable()->glRasterPos3xvOES(coords);}
inline void glRasterPos4d(GLdouble x,GLdouble y,GLdouble z,GLdouble w){this->_getTable()->glRasterPos4d(x,y,z,w);}
inline void glRasterPos4dv(const GLdouble* v){this->_getTable()->glRasterPos4dv(v);}
inline void glRasterPos4f(GLfloat x,GLfloat y,GLfloat z,GLfloat w){this->_getTable()->glRasterPos4f(x,y,z,w);}
inline void glRasterPos4fv(const GLfloat* v){this->_getTable()->glRasterPos4fv(v);}
inline void glRasterPos4i(GLint x,GLint y,GLint z,GLint w){this->_getTable()->glRasterPos4i(x,y,z,w);}
inline void glRasterPos4iv(const GLint* v){this->_getTable()->glRasterPos4iv(v);}
inline void glRasterPos4s(GLshort x,GLshort y,GLshort z,GLshort w){this->_getTable()->glRasterPos4s(x,y,z,w);}
inline void glRasterPos4sv(const GLshort* v){this->_getTable()->glRasterPos4sv(v);}
inline void glRasterPos4xOES(GLfixed x,GLfixed y,GLfixed z,GLfixed w){this->_getTable()->glRasterPos4xOES(x,y,z,w);}
inline void glRasterPos4xvOES(const GLfixed* coords){this->_getTable()->glRasterPos4xvOES(coords);}
inline void glRasterSamplesEXT(GLuint samples,GLboolean fixedsamplelocations){this->_getTable()->glRasterSamplesEXT(samples,fixedsamplelocations);}
inline void glReadBuffer(GLenum mode){this->_getTable()->glReadBuffer(mode);}
inline void glReadInstrumentsSGIX(GLint marker){this->_getTable()->glReadInstrumentsSGIX(marker);}
inline void glReadnPixelsARB(GLint x,GLint y,GLsizei width,GLsizei height,GLenum format,GLenum type,GLsizei bufSize,void* data){this->_getTable()->glReadnPixelsARB(x,y,width,height,format,type,bufSize,data);}
inline void glReadnPixels(GLint x,GLint y,GLsizei width,GLsizei height,GLenum format,GLenum type,GLsizei bufSize,void* data){this->_getTable()->glReadnPixels(x,y,width,height,format,type,bufSize,data);}
inline void glReadPixels(GLint x,GLint y,GLsizei width,GLsizei height,GLenum format,GLenum type,GLvoid* pixels){this->_getTable()->glReadPixels(x,y,width,height,format,type,pixels);}
inline void glRectd(GLdouble x1,GLdouble y1,GLdouble x2,GLdouble y2){this->_getTable()->glRectd(x1,y1,x2,y2);}
inline void glRectdv(const GLdouble* v1,const GLdouble* v2){this->_getTable()->glRectdv(v1,v2);}
inline void glRectf(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2){this->_getTable()->glRectf(x1,y1,x2,y2);}
inline void glRectfv(const GLfloat* v1,const GLfloat* v2){this->_getTable()->glRectfv(v1,v2);}
inline void glRecti(GLint x1,GLint y1,GLint x2,GLint y2){this->_getTable()->glRecti(x1,y1,x2,y2);}
inline void glRectiv(const GLint* v1,const GLint* v2){this->_getTable()->glRectiv(v1,v2);}
inline void glRects(GLshort x1,GLshort y1,GLshort x2,GLshort y2){this->_getTable()->glRects(x1,y1,x2,y2);}
inline void glRectsv(const GLshort* v1,const GLshort* v2){this->_getTable()->glRectsv(v1,v2);}
inline void glRectxOES(GLfixed x1,GLfixed y1,GLfixed x2,GLfixed y2){this->_getTable()->glRectxOES(x1,y1,x2,y2);}
inline void glRectxvOES(const GLfixed* v1,const GLfixed* v2){this->_getTable()->glRectxvOES(v1,v2);}
inline void glReferencePlaneSGIX(const GLdouble* equation){this->_getTable()->glReferencePlaneSGIX(equation);}
inline void glReleaseShaderCompiler(){this->_getTable()->glReleaseShaderCompiler();}
inline void glRenderbufferStorageEXT(GLenum target,GLenum internalformat,GLsizei width,GLsizei height){this->_getTable()->glRenderbufferStorageEXT(target,internalformat,width,height);}
inline void glRenderbufferStorage(GLenum target,GLenum internalformat,GLsizei width,GLsizei height){this->_getTable()->glRenderbufferStorage(target,internalformat,width,height);}
inline void glRenderbufferStorageMultisampleCoverageNV(GLenum target,GLsizei coverageSamples,GLsizei colorSamples,GLenum internalformat,GLsizei width,GLsizei height){this->_getTable()->glRenderbufferStorageMultisampleCoverageNV(target,coverageSamples,colorSamples,internalformat,width,height);}
inline void glRenderbufferStorageMultisampleEXT(GLenum target,GLsizei samples,GLenum internalformat,GLsizei width,GLsizei height){this->_getTable()->glRenderbufferStorageMultisampleEXT(target,samples,internalformat,width,height);}
inline void glRenderbufferStorageMultisample(GLenum target,GLsizei samples,GLenum internalformat,GLsizei width,GLsizei height){this->_getTable()->glRenderbufferStorageMultisample(target,samples,internalformat,width,height);}
inline void glReplacementCodePointerSUN(GLenum type,GLsizei stride,const void** pointer){this->_getTable()->glReplacementCodePointerSUN(type,stride,pointer);}
inline void glReplacementCodeubSUN(GLubyte code){this->_getTable()->glReplacementCodeubSUN(code);}
inline void glReplacementCodeubvSUN(const GLubyte* code){this->_getTable()->glReplacementCodeubvSUN(code);}
inline void glReplacementCodeuiColor3fVertex3fSUN(GLuint rc,GLfloat r,GLfloat g,GLfloat b,GLfloat x,GLfloat y,GLfloat z){this->_getTable()->glReplacementCodeuiColor3fVertex3fSUN(rc,r,g,b,x,y,z);}
inline void glReplacementCodeuiColor3fVertex3fvSUN(const GLuint* rc,const GLfloat* c,const GLfloat* v){this->_getTable()->glReplacementCodeuiColor3fVertex3fvSUN(rc,c,v);}
inline void glReplacementCodeuiColor4fNormal3fVertex3fSUN(GLuint rc,GLfloat r,GLfloat g,GLfloat b,GLfloat a,GLfloat nx,GLfloat ny,GLfloat nz,GLfloat x,GLfloat y,GLfloat z){this->_getTable()->glReplacementCodeuiColor4fNormal3fVertex3fSUN(rc,r,g,b,a,nx,ny,nz,x,y,z);}
inline void glReplacementCodeuiColor4fNormal3fVertex3fvSUN(const GLuint* rc,const GLfloat* c,const GLfloat* n,const GLfloat* v){this->_getTable()->glReplacementCodeuiColor4fNormal3fVertex3fvSUN(rc,c,n,v);}
inline void glReplacementCodeuiColor4ubVertex3fSUN(GLuint rc,GLubyte r,GLubyte g,GLubyte b,GLubyte a,GLfloat x,GLfloat y,GLfloat z){this->_getTable()->glReplacementCodeuiColor4ubVertex3fSUN(rc,r,g,b,a,x,y,z);}
inline void glReplacementCodeuiColor4ubVertex3fvSUN(const GLuint* rc,const GLubyte* c,const GLfloat* v){this->_getTable()->glReplacementCodeuiColor4ubVertex3fvSUN(rc,c,v);}
inline void glReplacementCodeuiNormal3fVertex3fSUN(GLuint rc,GLfloat nx,GLfloat ny,GLfloat nz,GLfloat x,GLfloat y,GLfloat z){this->_getTable()->glReplacementCodeuiNormal3fVertex3fSUN(rc,nx,ny,nz,x,y,z);}
inline void glReplacementCodeuiNormal3fVertex3fvSUN(const GLuint* rc,const GLfloat* n,const GLfloat* v){this->_getTable()->glReplacementCodeuiNormal3fVertex3fvSUN(rc,n,v);}
inline void glReplacementCodeuiSUN(GLuint code){this->_getTable()->glReplacementCodeuiSUN(code);}
inline void glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN(GLuint rc,GLfloat s,GLfloat t,GLfloat r,GLfloat g,GLfloat b,GLfloat a,GLfloat nx,GLfloat ny,GLfloat nz,GLfloat x,GLfloat y,GLfloat z){this->_getTable()->glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN(rc,s,t,r,g,b,a,nx,ny,nz,x,y,z);}
inline void glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN(const GLuint* rc,const GLfloat* tc,const GLfloat* c,const GLfloat* n,const GLfloat* v){this->_getTable()->glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN(rc,tc,c,n,v);}
inline void glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN(GLuint rc,GLfloat s,GLfloat t,GLfloat nx,GLfloat ny,GLfloat nz,GLfloat x,GLfloat y,GLfloat z){this->_getTable()->glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN(rc,s,t,nx,ny,nz,x,y,z);}
inline void glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN(const GLuint* rc,const GLfloat* tc,const GLfloat* n,const GLfloat* v){this->_getTable()->glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN(rc,tc,n,v);}
inline void glReplacementCodeuiTexCoord2fVertex3fSUN(GLuint rc,GLfloat s,GLfloat t,GLfloat x,GLfloat y,GLfloat z){this->_getTable()->glReplacementCodeuiTexCoord2fVertex3fSUN(rc,s,t,x,y,z);}
inline void glReplacementCodeuiTexCoord2fVertex3fvSUN(const GLuint* rc,const GLfloat* tc,const GLfloat* v){this->_getTable()->glReplacementCodeuiTexCoord2fVertex3fvSUN(rc,tc,v);}
inline void glReplacementCodeuiVertex3fSUN(GLuint rc,GLfloat x,GLfloat y,GLfloat z){this->_getTable()->glReplacementCodeuiVertex3fSUN(rc,x,y,z);}
inline void glReplacementCodeuiVertex3fvSUN(const GLuint* rc,const GLfloat* v){this->_getTable()->glReplacementCodeuiVertex3fvSUN(rc,v);}
inline void glReplacementCodeuivSUN(const GLuint* code){this->_getTable()->glReplacementCodeuivSUN(code);}
inline void glReplacementCodeusSUN(GLushort code){this->_getTable()->glReplacementCodeusSUN(code);}
inline void glReplacementCodeusvSUN(const GLushort* code){this->_getTable()->glReplacementCodeusvSUN(code);}
inline void glRequestResidentProgramsNV(GLsizei n,const GLuint* programs){this->_getTable()->glRequestResidentProgramsNV(n,programs);}
inline void glResetHistogramEXT(GLenum target){this->_getTable()->glResetHistogramEXT(target);}
inline void glResetHistogram(GLenum target){this->_getTable()->glResetHistogram(target);}
inline void glResetMinmaxEXT(GLenum target){this->_getTable()->glResetMinmaxEXT(target);}
inline void glResetMinmax(GLenum target){this->_getTable()->glResetMinmax(target);}
inline void glResizeBuffersMESA(){this->_getTable()->glResizeBuffersMESA();}
inline void glResolveDepthValuesNV(){this->_getTable()->glResolveDepthValuesNV();}
inline void glResumeTransformFeedback(){this->_getTable()->glResumeTransformFeedback();}
inline void glResumeTransformFeedbackNV(){this->_getTable()->glResumeTransformFeedbackNV();}
inline void glRotated(GLdouble angle,GLdouble x,GLdouble y,GLdouble z){this->_getTable()->glRotated(angle,x,y,z);}
inline void glRotatef(GLfloat angle,GLfloat x,GLfloat y,GLfloat z){this->_getTable()->glRotatef(angle,x,y,z);}
inline void glRotatexOES(GLfixed angle,GLfixed x,GLfixed y,GLfixed z){this->_getTable()->glRotatexOES(angle,x,y,z);}
inline void glSampleCoverageARB(GLfloat value,GLboolean invert){this->_getTable()->glSampleCoverageARB(value,invert);}
inline void glSampleCoverage(GLclampf value,GLboolean invert){this->_getTable()->glSampleCoverage(value,invert);}
inline void glSampleMapATI(GLuint dst,GLuint interp,GLenum swizzle){this->_getTable()->glSampleMapATI(dst,interp,swizzle);}
inline void glSampleMaskEXT(GLclampf value,GLboolean invert){this->_getTable()->glSampleMaskEXT(value,invert);}
inline void glSampleMaski(GLuint maskNumber,GLbitfield mask){this->_getTable()->glSampleMaski(maskNumber,mask);}
inline void glSampleMaskIndexedNV(GLuint index,GLbitfield mask){this->_getTable()->glSampleMaskIndexedNV(index,mask);}
inline void glSampleMaskSGIS(GLclampf value,GLboolean invert){this->_getTable()->glSampleMaskSGIS(value,invert);}
inline void glSamplePatternEXT(GLenum pattern){this->_getTable()->glSamplePatternEXT(pattern);}
inline void glSamplePatternSGIS(GLenum pattern){this->_getTable()->glSamplePatternSGIS(pattern);}
inline void glSamplerParameterf(GLuint sampler,GLenum pname,GLfloat param){this->_getTable()->glSamplerParameterf(sampler,pname,param);}
inline void glSamplerParameterfv(GLuint sampler,GLenum pname,const GLfloat* param){this->_getTable()->glSamplerParameterfv(sampler,pname,param);}
inline void glSamplerParameteri(GLuint sampler,GLenum pname,GLint param){this->_getTable()->glSamplerParameteri(sampler,pname,param);}
inline void glSamplerParameterIiv(GLuint sampler,GLenum pname,const GLint* param){this->_getTable()->glSamplerParameterIiv(sampler,pname,param);}
inline void glSamplerParameterIuiv(GLuint sampler,GLenum pname,const GLuint* param){this->_getTable()->glSamplerParameterIuiv(sampler,pname,param);}
inline void glSamplerParameteriv(GLuint sampler,GLenum pname,const GLint* param){this->_getTable()->glSamplerParameteriv(sampler,pname,param);}
inline void glScaled(GLdouble x,GLdouble y,GLdouble z){this->_getTable()->glScaled(x,y,z);}
inline void glScalef(GLfloat x,GLfloat y,GLfloat z){this->_getTable()->glScalef(x,y,z);}
inline void glScalexOES(GLfixed x,GLfixed y,GLfixed z){this->_getTable()->glScalexOES(x,y,z);}
inline void glScissorArrayv(GLuint first,GLsizei count,const GLint* v){this->_getTable()->glScissorArrayv(first,count,v);}
inline void glScissor(GLint x,GLint y,GLsizei width,GLsizei height){this->_getTable()->glScissor(x,y,width,height);}
inline void glScissorIndexed(GLuint index,GLint left,GLint bottom,GLsizei width,GLsizei height){this->_getTable()->glScissorIndexed(index,left,bottom,width,height);}
inline void glScissorIndexedv(GLuint index,const GLint* v){this->_getTable()->glScissorIndexedv(index,v);}
inline void glSecondaryColor3bEXT(GLbyte red,GLbyte green,GLbyte blue){this->_getTable()->glSecondaryColor3bEXT(red,green,blue);}
inline void glSecondaryColor3b(GLbyte red,GLbyte green,GLbyte blue){this->_getTable()->glSecondaryColor3b(red,green,blue);}
inline void glSecondaryColor3bv(const GLbyte* v){this->_getTable()->glSecondaryColor3bv(v);}
inline void glSecondaryColor3bvEXT(const GLbyte* v){this->_getTable()->glSecondaryColor3bvEXT(v);}
inline void glSecondaryColor3dEXT(GLdouble red,GLdouble green,GLdouble blue){this->_getTable()->glSecondaryColor3dEXT(red,green,blue);}
inline void glSecondaryColor3d(GLdouble red,GLdouble green,GLdouble blue){this->_getTable()->glSecondaryColor3d(red,green,blue);}
inline void glSecondaryColor3dv(const GLdouble* v){this->_getTable()->glSecondaryColor3dv(v);}
inline void glSecondaryColor3dvEXT(const GLdouble* v){this->_getTable()->glSecondaryColor3dvEXT(v);}
inline void glSecondaryColor3fEXT(GLfloat red,GLfloat green,GLfloat blue){this->_getTable()->glSecondaryColor3fEXT(red,green,blue);}
inline void glSecondaryColor3f(GLfloat red,GLfloat green,GLfloat blue){this->_getTable()->glSecondaryColor3f(red,green,blue);}
inline void glSecondaryColor3fv(const GLfloat* v){this->_getTable()->glSecondaryColor3fv(v);}
inline void glSecondaryColor3fvEXT(const GLfloat* v){this->_getTable()->glSecondaryColor3fvEXT(v);}
inline void glSecondaryColor3hNV(GLhalfNV red,GLhalfNV green,GLhalfNV blue){this->_getTable()->glSecondaryColor3hNV(red,green,blue);}
inline void glSecondaryColor3hvNV(const GLhalfNV* v){this->_getTable()->glSecondaryColor3hvNV(v);}
inline void glSecondaryColor3iEXT(GLint red,GLint green,GLint blue){this->_getTable()->glSecondaryColor3iEXT(red,green,blue);}
inline void glSecondaryColor3i(GLint red,GLint green,GLint blue){this->_getTable()->glSecondaryColor3i(red,green,blue);}
inline void glSecondaryColor3iv(const GLint* v){this->_getTable()->glSecondaryColor3iv(v);}
inline void glSecondaryColor3ivEXT(const GLint* v){this->_getTable()->glSecondaryColor3ivEXT(v);}
inline void glSecondaryColor3sEXT(GLshort red,GLshort green,GLshort blue){this->_getTable()->glSecondaryColor3sEXT(red,green,blue);}
inline void glSecondaryColor3s(GLshort red,GLshort green,GLshort blue){this->_getTable()->glSecondaryColor3s(red,green,blue);}
inline void glSecondaryColor3sv(const GLshort* v){this->_getTable()->glSecondaryColor3sv(v);}
inline void glSecondaryColor3svEXT(const GLshort* v){this->_getTable()->glSecondaryColor3svEXT(v);}
inline void glSecondaryColor3ubEXT(GLubyte red,GLubyte green,GLubyte blue){this->_getTable()->glSecondaryColor3ubEXT(red,green,blue);}
inline void glSecondaryColor3ub(GLubyte red,GLubyte green,GLubyte blue){this->_getTable()->glSecondaryColor3ub(red,green,blue);}
inline void glSecondaryColor3ubv(const GLubyte* v){this->_getTable()->glSecondaryColor3ubv(v);}
inline void glSecondaryColor3ubvEXT(const GLubyte* v){this->_getTable()->glSecondaryColor3ubvEXT(v);}
inline void glSecondaryColor3uiEXT(GLuint red,GLuint green,GLuint blue){this->_getTable()->glSecondaryColor3uiEXT(red,green,blue);}
inline void glSecondaryColor3ui(GLuint red,GLuint green,GLuint blue){this->_getTable()->glSecondaryColor3ui(red,green,blue);}
inline void glSecondaryColor3uiv(const GLuint* v){this->_getTable()->glSecondaryColor3uiv(v);}
inline void glSecondaryColor3uivEXT(const GLuint* v){this->_getTable()->glSecondaryColor3uivEXT(v);}
inline void glSecondaryColor3usEXT(GLushort red,GLushort green,GLushort blue){this->_getTable()->glSecondaryColor3usEXT(red,green,blue);}
inline void glSecondaryColor3us(GLushort red,GLushort green,GLushort blue){this->_getTable()->glSecondaryColor3us(red,green,blue);}
inline void glSecondaryColor3usv(const GLushort* v){this->_getTable()->glSecondaryColor3usv(v);}
inline void glSecondaryColor3usvEXT(const GLushort* v){this->_getTable()->glSecondaryColor3usvEXT(v);}
inline void glSecondaryColorFormatNV(GLint size,GLenum type,GLsizei stride){this->_getTable()->glSecondaryColorFormatNV(size,type,stride);}
inline void glSecondaryColorP3ui(GLenum type,GLuint color){this->_getTable()->glSecondaryColorP3ui(type,color);}
inline void glSecondaryColorP3uiv(GLenum type,const GLuint* color){this->_getTable()->glSecondaryColorP3uiv(type,color);}
inline void glSecondaryColorPointerEXT(GLint size,GLenum type,GLsizei stride,const void* pointer){this->_getTable()->glSecondaryColorPointerEXT(size,type,stride,pointer);}
inline void glSecondaryColorPointer(GLint size,GLenum type,GLsizei stride,const void* pointer){this->_getTable()->glSecondaryColorPointer(size,type,stride,pointer);}
inline void glSecondaryColorPointerListIBM(GLint size,GLenum type,GLint stride,const void** pointer,GLint ptrstride){this->_getTable()->glSecondaryColorPointerListIBM(size,type,stride,pointer,ptrstride);}
inline void glSelectBuffer(GLsizei size,GLuint* buffer){this->_getTable()->glSelectBuffer(size,buffer);}
inline void glSelectPerfMonitorCountersAMD(GLuint monitor,GLboolean enable,GLuint group,GLint numCounters,GLuint* counterList){this->_getTable()->glSelectPerfMonitorCountersAMD(monitor,enable,group,numCounters,counterList);}
inline void glSeparableFilter2DEXT(GLenum target,GLenum internalformat,GLsizei width,GLsizei height,GLenum format,GLenum type,const void* row,const void* column){this->_getTable()->glSeparableFilter2DEXT(target,internalformat,width,height,format,type,row,column);}
inline void glSeparableFilter2D(GLenum target,GLenum internalformat,GLsizei width,GLsizei height,GLenum format,GLenum type,const GLvoid* row,const GLvoid* column){this->_getTable()->glSeparableFilter2D(target,internalformat,width,height,format,type,row,column);}
inline void glSetFenceAPPLE(GLuint fence){this->_getTable()->glSetFenceAPPLE(fence);}
inline void glSetFenceNV(GLuint fence,GLenum condition){this->_getTable()->glSetFenceNV(fence,condition);}
inline void glSetFragmentShaderConstantATI(GLuint dst,const GLfloat* value){this->_getTable()->glSetFragmentShaderConstantATI(dst,value);}
inline void glSetInvariantEXT(GLuint id,GLenum type,const void* addr){this->_getTable()->glSetInvariantEXT(id,type,addr);}
inline void glSetLocalConstantEXT(GLuint id,GLenum type,const void* addr){this->_getTable()->glSetLocalConstantEXT(id,type,addr);}
inline void glSetMultisamplefvAMD(GLenum pname,GLuint index,const GLfloat* val){this->_getTable()->glSetMultisamplefvAMD(pname,index,val);}
inline void glShadeModel(GLenum mode){this->_getTable()->glShadeModel(mode);}
inline void glShaderBinary(GLsizei count,const GLuint* shaders,GLenum binaryformat,const void* binary,GLsizei length){this->_getTable()->glShaderBinary(count,shaders,binaryformat,binary,length);}
inline void glShaderOp1EXT(GLenum op,GLuint res,GLuint arg1){this->_getTable()->glShaderOp1EXT(op,res,arg1);}
inline void glShaderOp2EXT(GLenum op,GLuint res,GLuint arg1,GLuint arg2){this->_getTable()->glShaderOp2EXT(op,res,arg1,arg2);}
inline void glShaderOp3EXT(GLenum op,GLuint res,GLuint arg1,GLuint arg2,GLuint arg3){this->_getTable()->glShaderOp3EXT(op,res,arg1,arg2,arg3);}
inline void glShaderSourceARB(GLhandleARB shaderObj,GLsizei count,const GLcharARB** string,const GLint* length){this->_getTable()->glShaderSourceARB(shaderObj,count,string,length);}
inline void glShaderSource(GLuint shader,GLsizei count,const GLchar*const* string,const GLint* length){this->_getTable()->glShaderSource(shader,count,string,length);}
inline void glShaderStorageBlockBinding(GLuint program,GLuint storageBlockIndex,GLuint storageBlockBinding){this->_getTable()->glShaderStorageBlockBinding(program,storageBlockIndex,storageBlockBinding);}
inline void glSharpenTexFuncSGIS(GLenum target,GLsizei n,const GLfloat* points){this->_getTable()->glSharpenTexFuncSGIS(target,n,points);}
inline void glSpriteParameterfSGIX(GLenum pname,GLfloat param){this->_getTable()->glSpriteParameterfSGIX(pname,param);}
inline void glSpriteParameterfvSGIX(GLenum pname,const GLfloat* params){this->_getTable()->glSpriteParameterfvSGIX(pname,params);}
inline void glSpriteParameteriSGIX(GLenum pname,GLint param){this->_getTable()->glSpriteParameteriSGIX(pname,param);}
inline void glSpriteParameterivSGIX(GLenum pname,const GLint* params){this->_getTable()->glSpriteParameterivSGIX(pname,params);}
inline void glStartInstrumentsSGIX(){this->_getTable()->glStartInstrumentsSGIX();}
inline void glStateCaptureNV(GLuint state,GLenum mode){this->_getTable()->glStateCaptureNV(state,mode);}
inline void glStencilClearTagEXT(GLsizei stencilTagBits,GLuint stencilClearTag){this->_getTable()->glStencilClearTagEXT(stencilTagBits,stencilClearTag);}
inline void glStencilFillPathInstancedNV(GLsizei numPaths,GLenum pathNameType,const void* paths,GLuint pathBase,GLenum fillMode,GLuint mask,GLenum transformType,const GLfloat* transformValues){this->_getTable()->glStencilFillPathInstancedNV(numPaths,pathNameType,paths,pathBase,fillMode,mask,transformType,transformValues);}
inline void glStencilFillPathNV(GLuint path,GLenum fillMode,GLuint mask){this->_getTable()->glStencilFillPathNV(path,fillMode,mask);}
inline void glStencilFunc(GLenum func,GLint ref,GLuint mask){this->_getTable()->glStencilFunc(func,ref,mask);}
inline void glStencilFuncSeparateATI(GLenum frontfunc,GLenum backfunc,GLint ref,GLuint mask){this->_getTable()->glStencilFuncSeparateATI(frontfunc,backfunc,ref,mask);}
inline void glStencilFuncSeparate(GLenum face,GLenum func,GLint ref,GLuint mask){this->_getTable()->glStencilFuncSeparate(face,func,ref,mask);}
inline void glStencilMask(GLuint mask){this->_getTable()->glStencilMask(mask);}
inline void glStencilMaskSeparate(GLenum face,GLuint mask){this->_getTable()->glStencilMaskSeparate(face,mask);}
inline void glStencilOp(GLenum fail,GLenum zfail,GLenum zpass){this->_getTable()->glStencilOp(fail,zfail,zpass);}
inline void glStencilOpSeparateATI(GLenum face,GLenum sfail,GLenum dpfail,GLenum dppass){this->_getTable()->glStencilOpSeparateATI(face,sfail,dpfail,dppass);}
inline void glStencilOpSeparate(GLenum face,GLenum sfail,GLenum dpfail,GLenum dppass){this->_getTable()->glStencilOpSeparate(face,sfail,dpfail,dppass);}
inline void glStencilOpValueAMD(GLenum face,GLuint value){this->_getTable()->glStencilOpValueAMD(face,value);}
inline void glStencilStrokePathInstancedNV(GLsizei numPaths,GLenum pathNameType,const void* paths,GLuint pathBase,GLint reference,GLuint mask,GLenum transformType,const GLfloat* transformValues){this->_getTable()->glStencilStrokePathInstancedNV(numPaths,pathNameType,paths,pathBase,reference,mask,transformType,transformValues);}
inline void glStencilStrokePathNV(GLuint path,GLint reference,GLuint mask){this->_getTable()->glStencilStrokePathNV(path,reference,mask);}
inline void glStencilThenCoverFillPathInstancedNV(GLsizei numPaths,GLenum pathNameType,const void* paths,GLuint pathBase,GLenum fillMode,GLuint mask,GLenum coverMode,GLenum transformType,const GLfloat* transformValues){this->_getTable()->glStencilThenCoverFillPathInstancedNV(numPaths,pathNameType,paths,pathBase,fillMode,mask,coverMode,transformType,transformValues);}
inline void glStencilThenCoverFillPathNV(GLuint path,GLenum fillMode,GLuint mask,GLenum coverMode){this->_getTable()->glStencilThenCoverFillPathNV(path,fillMode,mask,coverMode);}
inline void glStencilThenCoverStrokePathInstancedNV(GLsizei numPaths,GLenum pathNameType,const void* paths,GLuint pathBase,GLint reference,GLuint mask,GLenum coverMode,GLenum transformType,const GLfloat* transformValues){this->_getTable()->glStencilThenCoverStrokePathInstancedNV(numPaths,pathNameType,paths,pathBase,reference,mask,coverMode,transformType,transformValues);}
inline void glStencilThenCoverStrokePathNV(GLuint path,GLint reference,GLuint mask,GLenum coverMode){this->_getTable()->glStencilThenCoverStrokePathNV(path,reference,mask,coverMode);}
inline void glStopInstrumentsSGIX(GLint marker){this->_getTable()->glStopInstrumentsSGIX(marker);}
inline void glStringMarkerGREMEDY(GLsizei len,const void* string){this->_getTable()->glStringMarkerGREMEDY(len,string);}
inline void glSubpixelPrecisionBiasNV(GLuint xbits,GLuint ybits){this->_getTable()->glSubpixelPrecisionBiasNV(xbits,ybits);}
inline void glSwizzleEXT(GLuint res,GLuint in,GLenum outX,GLenum outY,GLenum outZ,GLenum outW){this->_getTable()->glSwizzleEXT(res,in,outX,outY,outZ,outW);}
inline void glSyncTextureINTEL(GLuint texture){this->_getTable()->glSyncTextureINTEL(texture);}
inline void glTagSampleBufferSGIX(){this->_getTable()->glTagSampleBufferSGIX();}
inline void glTangent3bEXT(GLbyte tx,GLbyte ty,GLbyte tz){this->_getTable()->glTangent3bEXT(tx,ty,tz);}
inline void glTangent3bvEXT(const GLbyte* v){this->_getTable()->glTangent3bvEXT(v);}
inline void glTangent3dEXT(GLdouble tx,GLdouble ty,GLdouble tz){this->_getTable()->glTangent3dEXT(tx,ty,tz);}
inline void glTangent3dvEXT(const GLdouble* v){this->_getTable()->glTangent3dvEXT(v);}
inline void glTangent3fEXT(GLfloat tx,GLfloat ty,GLfloat tz){this->_getTable()->glTangent3fEXT(tx,ty,tz);}
inline void glTangent3fvEXT(const GLfloat* v){this->_getTable()->glTangent3fvEXT(v);}
inline void glTangent3iEXT(GLint tx,GLint ty,GLint tz){this->_getTable()->glTangent3iEXT(tx,ty,tz);}
inline void glTangent3ivEXT(const GLint* v){this->_getTable()->glTangent3ivEXT(v);}
inline void glTangent3sEXT(GLshort tx,GLshort ty,GLshort tz){this->_getTable()->glTangent3sEXT(tx,ty,tz);}
inline void glTangent3svEXT(const GLshort* v){this->_getTable()->glTangent3svEXT(v);}
inline void glTangentPointerEXT(GLenum type,GLsizei stride,const void* pointer){this->_getTable()->glTangentPointerEXT(type,stride,pointer);}
inline void glTbufferMask3DFX(GLuint mask){this->_getTable()->glTbufferMask3DFX(mask);}
inline void glTessellationFactorAMD(GLfloat factor){this->_getTable()->glTessellationFactorAMD(factor);}
inline void glTessellationModeAMD(GLenum mode){this->_getTable()->glTessellationModeAMD(mode);}
inline void glTexBufferARB(GLenum target,GLenum internalformat,GLuint buffer){this->_getTable()->glTexBufferARB(target,internalformat,buffer);}
inline void glTexBufferEXT(GLenum target,GLenum internalformat,GLuint buffer){this->_getTable()->glTexBufferEXT(target,internalformat,buffer);}
inline void glTexBuffer(GLenum target,GLenum internalformat,GLuint buffer){this->_getTable()->glTexBuffer(target,internalformat,buffer);}
inline void glTexBufferRange(GLenum target,GLenum internalformat,GLuint buffer,GLintptr offset,GLsizeiptr size){this->_getTable()->glTexBufferRange(target,internalformat,buffer,offset,size);}
inline void glTexBumpParameterfvATI(GLenum pname,const GLfloat* param){this->_getTable()->glTexBumpParameterfvATI(pname,param);}
inline void glTexBumpParameterivATI(GLenum pname,const GLint* param){this->_getTable()->glTexBumpParameterivATI(pname,param);}
inline void glTexCoord1bOES(GLbyte s){this->_getTable()->glTexCoord1bOES(s);}
inline void glTexCoord1bvOES(const GLbyte* coords){this->_getTable()->glTexCoord1bvOES(coords);}
inline void glTexCoord1d(GLdouble s){this->_getTable()->glTexCoord1d(s);}
inline void glTexCoord1dv(const GLdouble* v){this->_getTable()->glTexCoord1dv(v);}
inline void glTexCoord1f(GLfloat s){this->_getTable()->glTexCoord1f(s);}
inline void glTexCoord1fv(const GLfloat* v){this->_getTable()->glTexCoord1fv(v);}
inline void glTexCoord1hNV(GLhalfNV s){this->_getTable()->glTexCoord1hNV(s);}
inline void glTexCoord1hvNV(const GLhalfNV* v){this->_getTable()->glTexCoord1hvNV(v);}
inline void glTexCoord1i(GLint s){this->_getTable()->glTexCoord1i(s);}
inline void glTexCoord1iv(const GLint* v){this->_getTable()->glTexCoord1iv(v);}
inline void glTexCoord1s(GLshort s){this->_getTable()->glTexCoord1s(s);}
inline void glTexCoord1sv(const GLshort* v){this->_getTable()->glTexCoord1sv(v);}
inline void glTexCoord1xOES(GLfixed s){this->_getTable()->glTexCoord1xOES(s);}
inline void glTexCoord1xvOES(const GLfixed* coords){this->_getTable()->glTexCoord1xvOES(coords);}
inline void glTexCoord2bOES(GLbyte s,GLbyte t){this->_getTable()->glTexCoord2bOES(s,t);}
inline void glTexCoord2bvOES(const GLbyte* coords){this->_getTable()->glTexCoord2bvOES(coords);}
inline void glTexCoord2d(GLdouble s,GLdouble t){this->_getTable()->glTexCoord2d(s,t);}
inline void glTexCoord2dv(const GLdouble* v){this->_getTable()->glTexCoord2dv(v);}
inline void glTexCoord2fColor3fVertex3fSUN(GLfloat s,GLfloat t,GLfloat r,GLfloat g,GLfloat b,GLfloat x,GLfloat y,GLfloat z){this->_getTable()->glTexCoord2fColor3fVertex3fSUN(s,t,r,g,b,x,y,z);}
inline void glTexCoord2fColor3fVertex3fvSUN(const GLfloat* tc,const GLfloat* c,const GLfloat* v){this->_getTable()->glTexCoord2fColor3fVertex3fvSUN(tc,c,v);}
inline void glTexCoord2fColor4fNormal3fVertex3fSUN(GLfloat s,GLfloat t,GLfloat r,GLfloat g,GLfloat b,GLfloat a,GLfloat nx,GLfloat ny,GLfloat nz,GLfloat x,GLfloat y,GLfloat z){this->_getTable()->glTexCoord2fColor4fNormal3fVertex3fSUN(s,t,r,g,b,a,nx,ny,nz,x,y,z);}
inline void glTexCoord2fColor4fNormal3fVertex3fvSUN(const GLfloat* tc,const GLfloat* c,const GLfloat* n,const GLfloat* v){this->_getTable()->glTexCoord2fColor4fNormal3fVertex3fvSUN(tc,c,n,v);}
inline void glTexCoord2fColor4ubVertex3fSUN(GLfloat s,GLfloat t,GLubyte r,GLubyte g,GLubyte b,GLubyte a,GLfloat x,GLfloat y,GLfloat z){this->_getTable()->glTexCoord2fColor4ubVertex3fSUN(s,t,r,g,b,a,x,y,z);}
inline void glTexCoord2fColor4ubVertex3fvSUN(const GLfloat* tc,const GLubyte* c,const GLfloat* v){this->_getTable()->glTexCoord2fColor4ubVertex3fvSUN(tc,c,v);}
inline void glTexCoord2f(GLfloat s,GLfloat t){this->_getTable()->glTexCoord2f(s,t);}
inline void glTexCoord2fNormal3fVertex3fSUN(GLfloat s,GLfloat t,GLfloat nx,GLfloat ny,GLfloat nz,GLfloat x,GLfloat y,GLfloat z){this->_getTable()->glTexCoord2fNormal3fVertex3fSUN(s,t,nx,ny,nz,x,y,z);}
inline void glTexCoord2fNormal3fVertex3fvSUN(const GLfloat* tc,const GLfloat* n,const GLfloat* v){this->_getTable()->glTexCoord2fNormal3fVertex3fvSUN(tc,n,v);}
inline void glTexCoord2fv(const GLfloat* v){this->_getTable()->glTexCoord2fv(v);}
inline void glTexCoord2fVertex3fSUN(GLfloat s,GLfloat t,GLfloat x,GLfloat y,GLfloat z){this->_getTable()->glTexCoord2fVertex3fSUN(s,t,x,y,z);}
inline void glTexCoord2fVertex3fvSUN(const GLfloat* tc,const GLfloat* v){this->_getTable()->glTexCoord2fVertex3fvSUN(tc,v);}
inline void glTexCoord2hNV(GLhalfNV s,GLhalfNV t){this->_getTable()->glTexCoord2hNV(s,t);}
inline void glTexCoord2hvNV(const GLhalfNV* v){this->_getTable()->glTexCoord2hvNV(v);}
inline void glTexCoord2i(GLint s,GLint t){this->_getTable()->glTexCoord2i(s,t);}
inline void glTexCoord2iv(const GLint* v){this->_getTable()->glTexCoord2iv(v);}
inline void glTexCoord2s(GLshort s,GLshort t){this->_getTable()->glTexCoord2s(s,t);}
inline void glTexCoord2sv(const GLshort* v){this->_getTable()->glTexCoord2sv(v);}
inline void glTexCoord2xOES(GLfixed s,GLfixed t){this->_getTable()->glTexCoord2xOES(s,t);}
inline void glTexCoord2xvOES(const GLfixed* coords){this->_getTable()->glTexCoord2xvOES(coords);}
inline void glTexCoord3bOES(GLbyte s,GLbyte t,GLbyte r){this->_getTable()->glTexCoord3bOES(s,t,r);}
inline void glTexCoord3bvOES(const GLbyte* coords){this->_getTable()->glTexCoord3bvOES(coords);}
inline void glTexCoord3d(GLdouble s,GLdouble t,GLdouble r){this->_getTable()->glTexCoord3d(s,t,r);}
inline void glTexCoord3dv(const GLdouble* v){this->_getTable()->glTexCoord3dv(v);}
inline void glTexCoord3f(GLfloat s,GLfloat t,GLfloat r){this->_getTable()->glTexCoord3f(s,t,r);}
inline void glTexCoord3fv(const GLfloat* v){this->_getTable()->glTexCoord3fv(v);}
inline void glTexCoord3hNV(GLhalfNV s,GLhalfNV t,GLhalfNV r){this->_getTable()->glTexCoord3hNV(s,t,r);}
inline void glTexCoord3hvNV(const GLhalfNV* v){this->_getTable()->glTexCoord3hvNV(v);}
inline void glTexCoord3i(GLint s,GLint t,GLint r){this->_getTable()->glTexCoord3i(s,t,r);}
inline void glTexCoord3iv(const GLint* v){this->_getTable()->glTexCoord3iv(v);}
inline void glTexCoord3s(GLshort s,GLshort t,GLshort r){this->_getTable()->glTexCoord3s(s,t,r);}
inline void glTexCoord3sv(const GLshort* v){this->_getTable()->glTexCoord3sv(v);}
inline void glTexCoord3xOES(GLfixed s,GLfixed t,GLfixed r){this->_getTable()->glTexCoord3xOES(s,t,r);}
inline void glTexCoord3xvOES(const GLfixed* coords){this->_getTable()->glTexCoord3xvOES(coords);}
inline void glTexCoord4bOES(GLbyte s,GLbyte t,GLbyte r,GLbyte q){this->_getTable()->glTexCoord4bOES(s,t,r,q);}
inline void glTexCoord4bvOES(const GLbyte* coords){this->_getTable()->glTexCoord4bvOES(coords);}
inline void glTexCoord4d(GLdouble s,GLdouble t,GLdouble r,GLdouble q){this->_getTable()->glTexCoord4d(s,t,r,q);}
inline void glTexCoord4dv(const GLdouble* v){this->_getTable()->glTexCoord4dv(v);}
inline void glTexCoord4fColor4fNormal3fVertex4fSUN(GLfloat s,GLfloat t,GLfloat p,GLfloat q,GLfloat r,GLfloat g,GLfloat b,GLfloat a,GLfloat nx,GLfloat ny,GLfloat nz,GLfloat x,GLfloat y,GLfloat z,GLfloat w){this->_getTable()->glTexCoord4fColor4fNormal3fVertex4fSUN(s,t,p,q,r,g,b,a,nx,ny,nz,x,y,z,w);}
inline void glTexCoord4fColor4fNormal3fVertex4fvSUN(const GLfloat* tc,const GLfloat* c,const GLfloat* n,const GLfloat* v){this->_getTable()->glTexCoord4fColor4fNormal3fVertex4fvSUN(tc,c,n,v);}
inline void glTexCoord4f(GLfloat s,GLfloat t,GLfloat r,GLfloat q){this->_getTable()->glTexCoord4f(s,t,r,q);}
inline void glTexCoord4fv(const GLfloat* v){this->_getTable()->glTexCoord4fv(v);}
inline void glTexCoord4fVertex4fSUN(GLfloat s,GLfloat t,GLfloat p,GLfloat q,GLfloat x,GLfloat y,GLfloat z,GLfloat w){this->_getTable()->glTexCoord4fVertex4fSUN(s,t,p,q,x,y,z,w);}
inline void glTexCoord4fVertex4fvSUN(const GLfloat* tc,const GLfloat* v){this->_getTable()->glTexCoord4fVertex4fvSUN(tc,v);}
inline void glTexCoord4hNV(GLhalfNV s,GLhalfNV t,GLhalfNV r,GLhalfNV q){this->_getTable()->glTexCoord4hNV(s,t,r,q);}
inline void glTexCoord4hvNV(const GLhalfNV* v){this->_getTable()->glTexCoord4hvNV(v);}
inline void glTexCoord4i(GLint s,GLint t,GLint r,GLint q){this->_getTable()->glTexCoord4i(s,t,r,q);}
inline void glTexCoord4iv(const GLint* v){this->_getTable()->glTexCoord4iv(v);}
inline void glTexCoord4s(GLshort s,GLshort t,GLshort r,GLshort q){this->_getTable()->glTexCoord4s(s,t,r,q);}
inline void glTexCoord4sv(const GLshort* v){this->_getTable()->glTexCoord4sv(v);}
inline void glTexCoord4xOES(GLfixed s,GLfixed t,GLfixed r,GLfixed q){this->_getTable()->glTexCoord4xOES(s,t,r,q);}
inline void glTexCoord4xvOES(const GLfixed* coords){this->_getTable()->glTexCoord4xvOES(coords);}
inline void glTexCoordFormatNV(GLint size,GLenum type,GLsizei stride){this->_getTable()->glTexCoordFormatNV(size,type,stride);}
inline void glTexCoordP1ui(GLenum type,GLuint coords){this->_getTable()->glTexCoordP1ui(type,coords);}
inline void glTexCoordP1uiv(GLenum type,const GLuint* coords){this->_getTable()->glTexCoordP1uiv(type,coords);}
inline void glTexCoordP2ui(GLenum type,GLuint coords){this->_getTable()->glTexCoordP2ui(type,coords);}
inline void glTexCoordP2uiv(GLenum type,const GLuint* coords){this->_getTable()->glTexCoordP2uiv(type,coords);}
inline void glTexCoordP3ui(GLenum type,GLuint coords){this->_getTable()->glTexCoordP3ui(type,coords);}
inline void glTexCoordP3uiv(GLenum type,const GLuint* coords){this->_getTable()->glTexCoordP3uiv(type,coords);}
inline void glTexCoordP4ui(GLenum type,GLuint coords){this->_getTable()->glTexCoordP4ui(type,coords);}
inline void glTexCoordP4uiv(GLenum type,const GLuint* coords){this->_getTable()->glTexCoordP4uiv(type,coords);}
inline void glTexCoordPointerEXT(GLint size,GLenum type,GLsizei stride,GLsizei count,const void* pointer){this->_getTable()->glTexCoordPointerEXT(size,type,stride,count,pointer);}
inline void glTexCoordPointer(GLint size,GLenum type,GLsizei stride,const GLvoid* ptr){this->_getTable()->glTexCoordPointer(size,type,stride,ptr);}
inline void glTexCoordPointerListIBM(GLint size,GLenum type,GLint stride,const void** pointer,GLint ptrstride){this->_getTable()->glTexCoordPointerListIBM(size,type,stride,pointer,ptrstride);}
inline void glTexCoordPointervINTEL(GLint size,GLenum type,const void** pointer){this->_getTable()->glTexCoordPointervINTEL(size,type,pointer);}
inline void glTexEnvf(GLenum target,GLenum pname,GLfloat param){this->_getTable()->glTexEnvf(target,pname,param);}
inline void glTexEnvfv(GLenum target,GLenum pname,const GLfloat* params){this->_getTable()->glTexEnvfv(target,pname,params);}
inline void glTexEnvi(GLenum target,GLenum pname,GLint param){this->_getTable()->glTexEnvi(target,pname,param);}
inline void glTexEnviv(GLenum target,GLenum pname,const GLint* params){this->_getTable()->glTexEnviv(target,pname,params);}
inline void glTexEnvxOES(GLenum target,GLenum pname,GLfixed param){this->_getTable()->glTexEnvxOES(target,pname,param);}
inline void glTexEnvxvOES(GLenum target,GLenum pname,const GLfixed* params){this->_getTable()->glTexEnvxvOES(target,pname,params);}
inline void glTexFilterFuncSGIS(GLenum target,GLenum filter,GLsizei n,const GLfloat* weights){this->_getTable()->glTexFilterFuncSGIS(target,filter,n,weights);}
inline void glTexGend(GLenum coord,GLenum pname,GLdouble param){this->_getTable()->glTexGend(coord,pname,param);}
inline void glTexGendv(GLenum coord,GLenum pname,const GLdouble* params){this->_getTable()->glTexGendv(coord,pname,params);}
inline void glTexGenf(GLenum coord,GLenum pname,GLfloat param){this->_getTable()->glTexGenf(coord,pname,param);}
inline void glTexGenfv(GLenum coord,GLenum pname,const GLfloat* params){this->_getTable()->glTexGenfv(coord,pname,params);}
inline void glTexGeni(GLenum coord,GLenum pname,GLint param){this->_getTable()->glTexGeni(coord,pname,param);}
inline void glTexGeniv(GLenum coord,GLenum pname,const GLint* params){this->_getTable()->glTexGeniv(coord,pname,params);}
inline void glTexGenxOES(GLenum coord,GLenum pname,GLfixed param){this->_getTable()->glTexGenxOES(coord,pname,param);}
inline void glTexGenxvOES(GLenum coord,GLenum pname,const GLfixed* params){this->_getTable()->glTexGenxvOES(coord,pname,params);}
inline void glTexImage1D(GLenum target,GLint level,GLint internalFormat,GLsizei width,GLint border,GLenum format,GLenum type,const GLvoid* pixels){this->_getTable()->glTexImage1D(target,level,internalFormat,width,border,format,type,pixels);}
inline void glTexImage2D(GLenum target,GLint level,GLint internalFormat,GLsizei width,GLsizei height,GLint border,GLenum format,GLenum type,const GLvoid* pixels){this->_getTable()->glTexImage2D(target,level,internalFormat,width,height,border,format,type,pixels);}
inline void glTexImage2DMultisampleCoverageNV(GLenum target,GLsizei coverageSamples,GLsizei colorSamples,GLint internalFormat,GLsizei width,GLsizei height,GLboolean fixedSampleLocations){this->_getTable()->glTexImage2DMultisampleCoverageNV(target,coverageSamples,colorSamples,internalFormat,width,height,fixedSampleLocations);}
inline void glTexImage2DMultisample(GLenum target,GLsizei samples,GLenum internalformat,GLsizei width,GLsizei height,GLboolean fixedsamplelocations){this->_getTable()->glTexImage2DMultisample(target,samples,internalformat,width,height,fixedsamplelocations);}
inline void glTexImage3DEXT(GLenum target,GLint level,GLenum internalformat,GLsizei width,GLsizei height,GLsizei depth,GLint border,GLenum format,GLenum type,const void* pixels){this->_getTable()->glTexImage3DEXT(target,level,internalformat,width,height,depth,border,format,type,pixels);}
inline void glTexImage3D(GLenum target,GLint level,GLint internalFormat,GLsizei width,GLsizei height,GLsizei depth,GLint border,GLenum format,GLenum type,const GLvoid* pixels){this->_getTable()->glTexImage3D(target,level,internalFormat,width,height,depth,border,format,type,pixels);}
inline void glTexImage3DMultisampleCoverageNV(GLenum target,GLsizei coverageSamples,GLsizei colorSamples,GLint internalFormat,GLsizei width,GLsizei height,GLsizei depth,GLboolean fixedSampleLocations){this->_getTable()->glTexImage3DMultisampleCoverageNV(target,coverageSamples,colorSamples,internalFormat,width,height,depth,fixedSampleLocations);}
inline void glTexImage3DMultisample(GLenum target,GLsizei samples,GLenum internalformat,GLsizei width,GLsizei height,GLsizei depth,GLboolean fixedsamplelocations){this->_getTable()->glTexImage3DMultisample(target,samples,internalformat,width,height,depth,fixedsamplelocations);}
inline void glTexImage4DSGIS(GLenum target,GLint level,GLenum internalformat,GLsizei width,GLsizei height,GLsizei depth,GLsizei size4d,GLint border,GLenum format,GLenum type,const void* pixels){this->_getTable()->glTexImage4DSGIS(target,level,internalformat,width,height,depth,size4d,border,format,type,pixels);}
inline void glTexPageCommitmentARB(GLenum target,GLint level,GLint xoffset,GLint yoffset,GLint zoffset,GLsizei width,GLsizei height,GLsizei depth,GLboolean commit){this->_getTable()->glTexPageCommitmentARB(target,level,xoffset,yoffset,zoffset,width,height,depth,commit);}
inline void glTexParameterf(GLenum target,GLenum pname,GLfloat param){this->_getTable()->glTexParameterf(target,pname,param);}
inline void glTexParameterfv(GLenum target,GLenum pname,const GLfloat* params){this->_getTable()->glTexParameterfv(target,pname,params);}
inline void glTexParameteri(GLenum target,GLenum pname,GLint param){this->_getTable()->glTexParameteri(target,pname,param);}
inline void glTexParameterIivEXT(GLenum target,GLenum pname,const GLint* params){this->_getTable()->glTexParameterIivEXT(target,pname,params);}
inline void glTexParameterIiv(GLenum target,GLenum pname,const GLint* params){this->_getTable()->glTexParameterIiv(target,pname,params);}
inline void glTexParameterIuivEXT(GLenum target,GLenum pname,const GLuint* params){this->_getTable()->glTexParameterIuivEXT(target,pname,params);}
inline void glTexParameterIuiv(GLenum target,GLenum pname,const GLuint* params){this->_getTable()->glTexParameterIuiv(target,pname,params);}
inline void glTexParameteriv(GLenum target,GLenum pname,const GLint* params){this->_getTable()->glTexParameteriv(target,pname,params);}
inline void glTexParameterxOES(GLenum target,GLenum pname,GLfixed param){this->_getTable()->glTexParameterxOES(target,pname,param);}
inline void glTexParameterxvOES(GLenum target,GLenum pname,const GLfixed* params){this->_getTable()->glTexParameterxvOES(target,pname,params);}
inline void glTexRenderbufferNV(GLenum target,GLuint renderbuffer){this->_getTable()->glTexRenderbufferNV(target,renderbuffer);}
inline void glTexStorage1D(GLenum target,GLsizei levels,GLenum internalformat,GLsizei width){this->_getTable()->glTexStorage1D(target,levels,internalformat,width);}
inline void glTexStorage2D(GLenum target,GLsizei levels,GLenum internalformat,GLsizei width,GLsizei height){this->_getTable()->glTexStorage2D(target,levels,internalformat,width,height);}
inline void glTexStorage2DMultisample(GLenum target,GLsizei samples,GLenum internalformat,GLsizei width,GLsizei height,GLboolean fixedsamplelocations){this->_getTable()->glTexStorage2DMultisample(target,samples,internalformat,width,height,fixedsamplelocations);}
inline void glTexStorage3D(GLenum target,GLsizei levels,GLenum internalformat,GLsizei width,GLsizei height,GLsizei depth){this->_getTable()->glTexStorage3D(target,levels,internalformat,width,height,depth);}
inline void glTexStorage3DMultisample(GLenum target,GLsizei samples,GLenum internalformat,GLsizei width,GLsizei height,GLsizei depth,GLboolean fixedsamplelocations){this->_getTable()->glTexStorage3DMultisample(target,samples,internalformat,width,height,depth,fixedsamplelocations);}
inline void glTexStorageSparseAMD(GLenum target,GLenum internalFormat,GLsizei width,GLsizei height,GLsizei depth,GLsizei layers,GLbitfield flags){this->_getTable()->glTexStorageSparseAMD(target,internalFormat,width,height,depth,layers,flags);}
inline void glTexSubImage1DEXT(GLenum target,GLint level,GLint xoffset,GLsizei width,GLenum format,GLenum type,const void* pixels){this->_getTable()->glTexSubImage1DEXT(target,level,xoffset,width,format,type,pixels);}
inline void glTexSubImage1D(GLenum target,GLint level,GLint xoffset,GLsizei width,GLenum format,GLenum type,const GLvoid* pixels){this->_getTable()->glTexSubImage1D(target,level,xoffset,width,format,type,pixels);}
inline void glTexSubImage2DEXT(GLenum target,GLint level,GLint xoffset,GLint yoffset,GLsizei width,GLsizei height,GLenum format,GLenum type,const void* pixels){this->_getTable()->glTexSubImage2DEXT(target,level,xoffset,yoffset,width,height,format,type,pixels);}
inline void glTexSubImage2D(GLenum target,GLint level,GLint xoffset,GLint yoffset,GLsizei width,GLsizei height,GLenum format,GLenum type,const GLvoid* pixels){this->_getTable()->glTexSubImage2D(target,level,xoffset,yoffset,width,height,format,type,pixels);}
inline void glTexSubImage3DEXT(GLenum target,GLint level,GLint xoffset,GLint yoffset,GLint zoffset,GLsizei width,GLsizei height,GLsizei depth,GLenum format,GLenum type,const void* pixels){this->_getTable()->glTexSubImage3DEXT(target,level,xoffset,yoffset,zoffset,width,height,depth,format,type,pixels);}
inline void glTexSubImage3D(GLenum target,GLint level,GLint xoffset,GLint yoffset,GLint zoffset,GLsizei width,GLsizei height,GLsizei depth,GLenum format,GLenum type,const GLvoid* pixels){this->_getTable()->glTexSubImage3D(target,level,xoffset,yoffset,zoffset,width,height,depth,format,type,pixels);}
inline void glTexSubImage4DSGIS(GLenum target,GLint level,GLint xoffset,GLint yoffset,GLint zoffset,GLint woffset,GLsizei width,GLsizei height,GLsizei depth,GLsizei size4d,GLenum format,GLenum type,const void* pixels){this->_getTable()->glTexSubImage4DSGIS(target,level,xoffset,yoffset,zoffset,woffset,width,height,depth,size4d,format,type,pixels);}
inline void glTextureBarrier(){this->_getTable()->glTextureBarrier();}
inline void glTextureBarrierNV(){this->_getTable()->glTextureBarrierNV();}
inline void glTextureBufferEXT(GLuint texture,GLenum target,GLenum internalformat,GLuint buffer){this->_getTable()->glTextureBufferEXT(texture,target,internalformat,buffer);}
inline void glTextureBuffer(GLuint texture,GLenum internalformat,GLuint buffer){this->_getTable()->glTextureBuffer(texture,internalformat,buffer);}
inline void glTextureBufferRangeEXT(GLuint texture,GLenum target,GLenum internalformat,GLuint buffer,GLintptr offset,GLsizeiptr size){this->_getTable()->glTextureBufferRangeEXT(texture,target,internalformat,buffer,offset,size);}
inline void glTextureBufferRange(GLuint texture,GLenum internalformat,GLuint buffer,GLintptr offset,GLsizeiptr size){this->_getTable()->glTextureBufferRange(texture,internalformat,buffer,offset,size);}
inline void glTextureColorMaskSGIS(GLboolean red,GLboolean green,GLboolean blue,GLboolean alpha){this->_getTable()->glTextureColorMaskSGIS(red,green,blue,alpha);}
inline void glTextureImage1DEXT(GLuint texture,GLenum target,GLint level,GLint internalformat,GLsizei width,GLint border,GLenum format,GLenum type,const void* pixels){this->_getTable()->glTextureImage1DEXT(texture,target,level,internalformat,width,border,format,type,pixels);}
inline void glTextureImage2DEXT(GLuint texture,GLenum target,GLint level,GLint internalformat,GLsizei width,GLsizei height,GLint border,GLenum format,GLenum type,const void* pixels){this->_getTable()->glTextureImage2DEXT(texture,target,level,internalformat,width,height,border,format,type,pixels);}
inline void glTextureImage2DMultisampleCoverageNV(GLuint texture,GLenum target,GLsizei coverageSamples,GLsizei colorSamples,GLint internalFormat,GLsizei width,GLsizei height,GLboolean fixedSampleLocations){this->_getTable()->glTextureImage2DMultisampleCoverageNV(texture,target,coverageSamples,colorSamples,internalFormat,width,height,fixedSampleLocations);}
inline void glTextureImage2DMultisampleNV(GLuint texture,GLenum target,GLsizei samples,GLint internalFormat,GLsizei width,GLsizei height,GLboolean fixedSampleLocations){this->_getTable()->glTextureImage2DMultisampleNV(texture,target,samples,internalFormat,width,height,fixedSampleLocations);}
inline void glTextureImage3DEXT(GLuint texture,GLenum target,GLint level,GLint internalformat,GLsizei width,GLsizei height,GLsizei depth,GLint border,GLenum format,GLenum type,const void* pixels){this->_getTable()->glTextureImage3DEXT(texture,target,level,internalformat,width,height,depth,border,format,type,pixels);}
inline void glTextureImage3DMultisampleCoverageNV(GLuint texture,GLenum target,GLsizei coverageSamples,GLsizei colorSamples,GLint internalFormat,GLsizei width,GLsizei height,GLsizei depth,GLboolean fixedSampleLocations){this->_getTable()->glTextureImage3DMultisampleCoverageNV(texture,target,coverageSamples,colorSamples,internalFormat,width,height,depth,fixedSampleLocations);}
inline void glTextureImage3DMultisampleNV(GLuint texture,GLenum target,GLsizei samples,GLint internalFormat,GLsizei width,GLsizei height,GLsizei depth,GLboolean fixedSampleLocations){this->_getTable()->glTextureImage3DMultisampleNV(texture,target,samples,internalFormat,width,height,depth,fixedSampleLocations);}
inline void glTextureLightEXT(GLenum pname){this->_getTable()->glTextureLightEXT(pname);}
inline void glTextureMaterialEXT(GLenum face,GLenum mode){this->_getTable()->glTextureMaterialEXT(face,mode);}
inline void glTextureNormalEXT(GLenum mode){this->_getTable()->glTextureNormalEXT(mode);}
inline void glTexturePageCommitmentEXT(GLuint texture,GLint level,GLint xoffset,GLint yoffset,GLint zoffset,GLsizei width,GLsizei height,GLsizei depth,GLboolean commit){this->_getTable()->glTexturePageCommitmentEXT(texture,level,xoffset,yoffset,zoffset,width,height,depth,commit);}
inline void glTextureParameterfEXT(GLuint texture,GLenum target,GLenum pname,GLfloat param){this->_getTable()->glTextureParameterfEXT(texture,target,pname,param);}
inline void glTextureParameterf(GLuint texture,GLenum pname,GLfloat param){this->_getTable()->glTextureParameterf(texture,pname,param);}
inline void glTextureParameterfvEXT(GLuint texture,GLenum target,GLenum pname,const GLfloat* params){this->_getTable()->glTextureParameterfvEXT(texture,target,pname,params);}
inline void glTextureParameterfv(GLuint texture,GLenum pname,const GLfloat* param){this->_getTable()->glTextureParameterfv(texture,pname,param);}
inline void glTextureParameteriEXT(GLuint texture,GLenum target,GLenum pname,GLint param){this->_getTable()->glTextureParameteriEXT(texture,target,pname,param);}
inline void glTextureParameteri(GLuint texture,GLenum pname,GLint param){this->_getTable()->glTextureParameteri(texture,pname,param);}
inline void glTextureParameterIivEXT(GLuint texture,GLenum target,GLenum pname,const GLint* params){this->_getTable()->glTextureParameterIivEXT(texture,target,pname,params);}
inline void glTextureParameterIiv(GLuint texture,GLenum pname,const GLint* params){this->_getTable()->glTextureParameterIiv(texture,pname,params);}
inline void glTextureParameterIuivEXT(GLuint texture,GLenum target,GLenum pname,const GLuint* params){this->_getTable()->glTextureParameterIuivEXT(texture,target,pname,params);}
inline void glTextureParameterIuiv(GLuint texture,GLenum pname,const GLuint* params){this->_getTable()->glTextureParameterIuiv(texture,pname,params);}
inline void glTextureParameterivEXT(GLuint texture,GLenum target,GLenum pname,const GLint* params){this->_getTable()->glTextureParameterivEXT(texture,target,pname,params);}
inline void glTextureParameteriv(GLuint texture,GLenum pname,const GLint* param){this->_getTable()->glTextureParameteriv(texture,pname,param);}
inline void glTextureRangeAPPLE(GLenum target,GLsizei length,const void* pointer){this->_getTable()->glTextureRangeAPPLE(target,length,pointer);}
inline void glTextureRenderbufferEXT(GLuint texture,GLenum target,GLuint renderbuffer){this->_getTable()->glTextureRenderbufferEXT(texture,target,renderbuffer);}
inline void glTextureStorage1DEXT(GLuint texture,GLenum target,GLsizei levels,GLenum internalformat,GLsizei width){this->_getTable()->glTextureStorage1DEXT(texture,target,levels,internalformat,width);}
inline void glTextureStorage1D(GLuint texture,GLsizei levels,GLenum internalformat,GLsizei width){this->_getTable()->glTextureStorage1D(texture,levels,internalformat,width);}
inline void glTextureStorage2DEXT(GLuint texture,GLenum target,GLsizei levels,GLenum internalformat,GLsizei width,GLsizei height){this->_getTable()->glTextureStorage2DEXT(texture,target,levels,internalformat,width,height);}
inline void glTextureStorage2D(GLuint texture,GLsizei levels,GLenum internalformat,GLsizei width,GLsizei height){this->_getTable()->glTextureStorage2D(texture,levels,internalformat,width,height);}
inline void glTextureStorage2DMultisampleEXT(GLuint texture,GLenum target,GLsizei samples,GLenum internalformat,GLsizei width,GLsizei height,GLboolean fixedsamplelocations){this->_getTable()->glTextureStorage2DMultisampleEXT(texture,target,samples,internalformat,width,height,fixedsamplelocations);}
inline void glTextureStorage2DMultisample(GLuint texture,GLsizei samples,GLenum internalformat,GLsizei width,GLsizei height,GLboolean fixedsamplelocations){this->_getTable()->glTextureStorage2DMultisample(texture,samples,internalformat,width,height,fixedsamplelocations);}
inline void glTextureStorage3DEXT(GLuint texture,GLenum target,GLsizei levels,GLenum internalformat,GLsizei width,GLsizei height,GLsizei depth){this->_getTable()->glTextureStorage3DEXT(texture,target,levels,internalformat,width,height,depth);}
inline void glTextureStorage3D(GLuint texture,GLsizei levels,GLenum internalformat,GLsizei width,GLsizei height,GLsizei depth){this->_getTable()->glTextureStorage3D(texture,levels,internalformat,width,height,depth);}
inline void glTextureStorage3DMultisampleEXT(GLuint texture,GLenum target,GLsizei samples,GLenum internalformat,GLsizei width,GLsizei height,GLsizei depth,GLboolean fixedsamplelocations){this->_getTable()->glTextureStorage3DMultisampleEXT(texture,target,samples,internalformat,width,height,depth,fixedsamplelocations);}
inline void glTextureStorage3DMultisample(GLuint texture,GLsizei samples,GLenum internalformat,GLsizei width,GLsizei height,GLsizei depth,GLboolean fixedsamplelocations){this->_getTable()->glTextureStorage3DMultisample(texture,samples,internalformat,width,height,depth,fixedsamplelocations);}
inline void glTextureStorageSparseAMD(GLuint texture,GLenum target,GLenum internalFormat,GLsizei width,GLsizei height,GLsizei depth,GLsizei layers,GLbitfield flags){this->_getTable()->glTextureStorageSparseAMD(texture,target,internalFormat,width,height,depth,layers,flags);}
inline void glTextureSubImage1DEXT(GLuint texture,GLenum target,GLint level,GLint xoffset,GLsizei width,GLenum format,GLenum type,const void* pixels){this->_getTable()->glTextureSubImage1DEXT(texture,target,level,xoffset,width,format,type,pixels);}
inline void glTextureSubImage1D(GLuint texture,GLint level,GLint xoffset,GLsizei width,GLenum format,GLenum type,const void* pixels){this->_getTable()->glTextureSubImage1D(texture,level,xoffset,width,format,type,pixels);}
inline void glTextureSubImage2DEXT(GLuint texture,GLenum target,GLint level,GLint xoffset,GLint yoffset,GLsizei width,GLsizei height,GLenum format,GLenum type,const void* pixels){this->_getTable()->glTextureSubImage2DEXT(texture,target,level,xoffset,yoffset,width,height,format,type,pixels);}
inline void glTextureSubImage2D(GLuint texture,GLint level,GLint xoffset,GLint yoffset,GLsizei width,GLsizei height,GLenum format,GLenum type,const void* pixels){this->_getTable()->glTextureSubImage2D(texture,level,xoffset,yoffset,width,height,format,type,pixels);}
inline void glTextureSubImage3DEXT(GLuint texture,GLenum target,GLint level,GLint xoffset,GLint yoffset,GLint zoffset,GLsizei width,GLsizei height,GLsizei depth,GLenum format,GLenum type,const void* pixels){this->_getTable()->glTextureSubImage3DEXT(texture,target,level,xoffset,yoffset,zoffset,width,height,depth,format,type,pixels);}
inline void glTextureSubImage3D(GLuint texture,GLint level,GLint xoffset,GLint yoffset,GLint zoffset,GLsizei width,GLsizei height,GLsizei depth,GLenum format,GLenum type,const void* pixels){this->_getTable()->glTextureSubImage3D(texture,level,xoffset,yoffset,zoffset,width,height,depth,format,type,pixels);}
inline void glTextureView(GLuint texture,GLenum target,GLuint origtexture,GLenum internalformat,GLuint minlevel,GLuint numlevels,GLuint minlayer,GLuint numlayers){this->_getTable()->glTextureView(texture,target,origtexture,internalformat,minlevel,numlevels,minlayer,numlayers);}
inline void glTrackMatrixNV(GLenum target,GLuint address,GLenum matrix,GLenum transform){this->_getTable()->glTrackMatrixNV(target,address,matrix,transform);}
inline void glTransformFeedbackAttribsNV(GLsizei count,const GLint* attribs,GLenum bufferMode){this->_getTable()->glTransformFeedbackAttribsNV(count,attribs,bufferMode);}
inline void glTransformFeedbackBufferBase(GLuint xfb,GLuint index,GLuint buffer){this->_getTable()->glTransformFeedbackBufferBase(xfb,index,buffer);}
inline void glTransformFeedbackBufferRange(GLuint xfb,GLuint index,GLuint buffer,GLintptr offset,GLsizeiptr size){this->_getTable()->glTransformFeedbackBufferRange(xfb,index,buffer,offset,size);}
inline void glTransformFeedbackStreamAttribsNV(GLsizei count,const GLint* attribs,GLsizei nbuffers,const GLint* bufstreams,GLenum bufferMode){this->_getTable()->glTransformFeedbackStreamAttribsNV(count,attribs,nbuffers,bufstreams,bufferMode);}
inline void glTransformFeedbackVaryingsEXT(GLuint program,GLsizei count,const GLchar*const* varyings,GLenum bufferMode){this->_getTable()->glTransformFeedbackVaryingsEXT(program,count,varyings,bufferMode);}
inline void glTransformFeedbackVaryings(GLuint program,GLsizei count,const GLchar*const* varyings,GLenum bufferMode){this->_getTable()->glTransformFeedbackVaryings(program,count,varyings,bufferMode);}
inline void glTransformFeedbackVaryingsNV(GLuint program,GLsizei count,const GLint* locations,GLenum bufferMode){this->_getTable()->glTransformFeedbackVaryingsNV(program,count,locations,bufferMode);}
inline void glTransformPathNV(GLuint resultPath,GLuint srcPath,GLenum transformType,const GLfloat* transformValues){this->_getTable()->glTransformPathNV(resultPath,srcPath,transformType,transformValues);}
inline void glTranslated(GLdouble x,GLdouble y,GLdouble z){this->_getTable()->glTranslated(x,y,z);}
inline void glTranslatef(GLfloat x,GLfloat y,GLfloat z){this->_getTable()->glTranslatef(x,y,z);}
inline void glTranslatexOES(GLfixed x,GLfixed y,GLfixed z){this->_getTable()->glTranslatexOES(x,y,z);}
inline void glUniform1d(GLint location,GLdouble x){this->_getTable()->glUniform1d(location,x);}
inline void glUniform1dv(GLint location,GLsizei count,const GLdouble* value){this->_getTable()->glUniform1dv(location,count,value);}
inline void glUniform1fARB(GLint location,GLfloat v0){this->_getTable()->glUniform1fARB(location,v0);}
inline void glUniform1f(GLint location,GLfloat v0){this->_getTable()->glUniform1f(location,v0);}
inline void glUniform1fvARB(GLint location,GLsizei count,const GLfloat* value){this->_getTable()->glUniform1fvARB(location,count,value);}
inline void glUniform1fv(GLint location,GLsizei count,const GLfloat* value){this->_getTable()->glUniform1fv(location,count,value);}
inline void glUniform1i64ARB(GLint location,GLint64 x){this->_getTable()->glUniform1i64ARB(location,x);}
inline void glUniform1i64NV(GLint location,GLint64EXT x){this->_getTable()->glUniform1i64NV(location,x);}
inline void glUniform1i64vARB(GLint location,GLsizei count,const GLint64* value){this->_getTable()->glUniform1i64vARB(location,count,value);}
inline void glUniform1i64vNV(GLint location,GLsizei count,const GLint64EXT* value){this->_getTable()->glUniform1i64vNV(location,count,value);}
inline void glUniform1iARB(GLint location,GLint v0){this->_getTable()->glUniform1iARB(location,v0);}
inline void glUniform1i(GLint location,GLint v0){this->_getTable()->glUniform1i(location,v0);}
inline void glUniform1ivARB(GLint location,GLsizei count,const GLint* value){this->_getTable()->glUniform1ivARB(location,count,value);}
inline void glUniform1iv(GLint location,GLsizei count,const GLint* value){this->_getTable()->glUniform1iv(location,count,value);}
inline void glUniform1ui64ARB(GLint location,GLuint64 x){this->_getTable()->glUniform1ui64ARB(location,x);}
inline void glUniform1ui64NV(GLint location,GLuint64EXT x){this->_getTable()->glUniform1ui64NV(location,x);}
inline void glUniform1ui64vARB(GLint location,GLsizei count,const GLuint64* value){this->_getTable()->glUniform1ui64vARB(location,count,value);}
inline void glUniform1ui64vNV(GLint location,GLsizei count,const GLuint64EXT* value){this->_getTable()->glUniform1ui64vNV(location,count,value);}
inline void glUniform1uiEXT(GLint location,GLuint v0){this->_getTable()->glUniform1uiEXT(location,v0);}
inline void glUniform1ui(GLint location,GLuint v0){this->_getTable()->glUniform1ui(location,v0);}
inline void glUniform1uivEXT(GLint location,GLsizei count,const GLuint* value){this->_getTable()->glUniform1uivEXT(location,count,value);}
inline void glUniform1uiv(GLint location,GLsizei count,const GLuint* value){this->_getTable()->glUniform1uiv(location,count,value);}
inline void glUniform2d(GLint location,GLdouble x,GLdouble y){this->_getTable()->glUniform2d(location,x,y);}
inline void glUniform2dv(GLint location,GLsizei count,const GLdouble* value){this->_getTable()->glUniform2dv(location,count,value);}
inline void glUniform2fARB(GLint location,GLfloat v0,GLfloat v1){this->_getTable()->glUniform2fARB(location,v0,v1);}
inline void glUniform2f(GLint location,GLfloat v0,GLfloat v1){this->_getTable()->glUniform2f(location,v0,v1);}
inline void glUniform2fvARB(GLint location,GLsizei count,const GLfloat* value){this->_getTable()->glUniform2fvARB(location,count,value);}
inline void glUniform2fv(GLint location,GLsizei count,const GLfloat* value){this->_getTable()->glUniform2fv(location,count,value);}
inline void glUniform2i64ARB(GLint location,GLint64 x,GLint64 y){this->_getTable()->glUniform2i64ARB(location,x,y);}
inline void glUniform2i64NV(GLint location,GLint64EXT x,GLint64EXT y){this->_getTable()->glUniform2i64NV(location,x,y);}
inline void glUniform2i64vARB(GLint location,GLsizei count,const GLint64* value){this->_getTable()->glUniform2i64vARB(location,count,value);}
inline void glUniform2i64vNV(GLint location,GLsizei count,const GLint64EXT* value){this->_getTable()->glUniform2i64vNV(location,count,value);}
inline void glUniform2iARB(GLint location,GLint v0,GLint v1){this->_getTable()->glUniform2iARB(location,v0,v1);}
inline void glUniform2i(GLint location,GLint v0,GLint v1){this->_getTable()->glUniform2i(location,v0,v1);}
inline void glUniform2ivARB(GLint location,GLsizei count,const GLint* value){this->_getTable()->glUniform2ivARB(location,count,value);}
inline void glUniform2iv(GLint location,GLsizei count,const GLint* value){this->_getTable()->glUniform2iv(location,count,value);}
inline void glUniform2ui64ARB(GLint location,GLuint64 x,GLuint64 y){this->_getTable()->glUniform2ui64ARB(location,x,y);}
inline void glUniform2ui64NV(GLint location,GLuint64EXT x,GLuint64EXT y){this->_getTable()->glUniform2ui64NV(location,x,y);}
inline void glUniform2ui64vARB(GLint location,GLsizei count,const GLuint64* value){this->_getTable()->glUniform2ui64vARB(location,count,value);}
inline void glUniform2ui64vNV(GLint location,GLsizei count,const GLuint64EXT* value){this->_getTable()->glUniform2ui64vNV(location,count,value);}
inline void glUniform2uiEXT(GLint location,GLuint v0,GLuint v1){this->_getTable()->glUniform2uiEXT(location,v0,v1);}
inline void glUniform2ui(GLint location,GLuint v0,GLuint v1){this->_getTable()->glUniform2ui(location,v0,v1);}
inline void glUniform2uivEXT(GLint location,GLsizei count,const GLuint* value){this->_getTable()->glUniform2uivEXT(location,count,value);}
inline void glUniform2uiv(GLint location,GLsizei count,const GLuint* value){this->_getTable()->glUniform2uiv(location,count,value);}
inline void glUniform3d(GLint location,GLdouble x,GLdouble y,GLdouble z){this->_getTable()->glUniform3d(location,x,y,z);}
inline void glUniform3dv(GLint location,GLsizei count,const GLdouble* value){this->_getTable()->glUniform3dv(location,count,value);}
inline void glUniform3fARB(GLint location,GLfloat v0,GLfloat v1,GLfloat v2){this->_getTable()->glUniform3fARB(location,v0,v1,v2);}
inline void glUniform3f(GLint location,GLfloat v0,GLfloat v1,GLfloat v2){this->_getTable()->glUniform3f(location,v0,v1,v2);}
inline void glUniform3fvARB(GLint location,GLsizei count,const GLfloat* value){this->_getTable()->glUniform3fvARB(location,count,value);}
inline void glUniform3fv(GLint location,GLsizei count,const GLfloat* value){this->_getTable()->glUniform3fv(location,count,value);}
inline void glUniform3i64ARB(GLint location,GLint64 x,GLint64 y,GLint64 z){this->_getTable()->glUniform3i64ARB(location,x,y,z);}
inline void glUniform3i64NV(GLint location,GLint64EXT x,GLint64EXT y,GLint64EXT z){this->_getTable()->glUniform3i64NV(location,x,y,z);}
inline void glUniform3i64vARB(GLint location,GLsizei count,const GLint64* value){this->_getTable()->glUniform3i64vARB(location,count,value);}
inline void glUniform3i64vNV(GLint location,GLsizei count,const GLint64EXT* value){this->_getTable()->glUniform3i64vNV(location,count,value);}
inline void glUniform3iARB(GLint location,GLint v0,GLint v1,GLint v2){this->_getTable()->glUniform3iARB(location,v0,v1,v2);}
inline void glUniform3i(GLint location,GLint v0,GLint v1,GLint v2){this->_getTable()->glUniform3i(location,v0,v1,v2);}
inline void glUniform3ivARB(GLint location,GLsizei count,const GLint* value){this->_getTable()->glUniform3ivARB(location,count,value);}
inline void glUniform3iv(GLint location,GLsizei count,const GLint* value){this->_getTable()->glUniform3iv(location,count,value);}
inline void glUniform3ui64ARB(GLint location,GLuint64 x,GLuint64 y,GLuint64 z){this->_getTable()->glUniform3ui64ARB(location,x,y,z);}
inline void glUniform3ui64NV(GLint location,GLuint64EXT x,GLuint64EXT y,GLuint64EXT z){this->_getTable()->glUniform3ui64NV(location,x,y,z);}
inline void glUniform3ui64vARB(GLint location,GLsizei count,const GLuint64* value){this->_getTable()->glUniform3ui64vARB(location,count,value);}
inline void glUniform3ui64vNV(GLint location,GLsizei count,const GLuint64EXT* value){this->_getTable()->glUniform3ui64vNV(location,count,value);}
inline void glUniform3uiEXT(GLint location,GLuint v0,GLuint v1,GLuint v2){this->_getTable()->glUniform3uiEXT(location,v0,v1,v2);}
inline void glUniform3ui(GLint location,GLuint v0,GLuint v1,GLuint v2){this->_getTable()->glUniform3ui(location,v0,v1,v2);}
inline void glUniform3uivEXT(GLint location,GLsizei count,const GLuint* value){this->_getTable()->glUniform3uivEXT(location,count,value);}
inline void glUniform3uiv(GLint location,GLsizei count,const GLuint* value){this->_getTable()->glUniform3uiv(location,count,value);}
inline void glUniform4d(GLint location,GLdouble x,GLdouble y,GLdouble z,GLdouble w){this->_getTable()->glUniform4d(location,x,y,z,w);}
inline void glUniform4dv(GLint location,GLsizei count,const GLdouble* value){this->_getTable()->glUniform4dv(location,count,value);}
inline void glUniform4fARB(GLint location,GLfloat v0,GLfloat v1,GLfloat v2,GLfloat v3){this->_getTable()->glUniform4fARB(location,v0,v1,v2,v3);}
inline void glUniform4f(GLint location,GLfloat v0,GLfloat v1,GLfloat v2,GLfloat v3){this->_getTable()->glUniform4f(location,v0,v1,v2,v3);}
inline void glUniform4fvARB(GLint location,GLsizei count,const GLfloat* value){this->_getTable()->glUniform4fvARB(location,count,value);}
inline void glUniform4fv(GLint location,GLsizei count,const GLfloat* value){this->_getTable()->glUniform4fv(location,count,value);}
inline void glUniform4i64ARB(GLint location,GLint64 x,GLint64 y,GLint64 z,GLint64 w){this->_getTable()->glUniform4i64ARB(location,x,y,z,w);}
inline void glUniform4i64NV(GLint location,GLint64EXT x,GLint64EXT y,GLint64EXT z,GLint64EXT w){this->_getTable()->glUniform4i64NV(location,x,y,z,w);}
inline void glUniform4i64vARB(GLint location,GLsizei count,const GLint64* value){this->_getTable()->glUniform4i64vARB(location,count,value);}
inline void glUniform4i64vNV(GLint location,GLsizei count,const GLint64EXT* value){this->_getTable()->glUniform4i64vNV(location,count,value);}
inline void glUniform4iARB(GLint location,GLint v0,GLint v1,GLint v2,GLint v3){this->_getTable()->glUniform4iARB(location,v0,v1,v2,v3);}
inline void glUniform4i(GLint location,GLint v0,GLint v1,GLint v2,GLint v3){this->_getTable()->glUniform4i(location,v0,v1,v2,v3);}
inline void glUniform4ivARB(GLint location,GLsizei count,const GLint* value){this->_getTable()->glUniform4ivARB(location,count,value);}
inline void glUniform4iv(GLint location,GLsizei count,const GLint* value){this->_getTable()->glUniform4iv(location,count,value);}
inline void glUniform4ui64ARB(GLint location,GLuint64 x,GLuint64 y,GLuint64 z,GLuint64 w){this->_getTable()->glUniform4ui64ARB(location,x,y,z,w);}
inline void glUniform4ui64NV(GLint location,GLuint64EXT x,GLuint64EXT y,GLuint64EXT z,GLuint64EXT w){this->_getTable()->glUniform4ui64NV(location,x,y,z,w);}
inline void glUniform4ui64vARB(GLint location,GLsizei count,const GLuint64* value){this->_getTable()->glUniform4ui64vARB(location,count,value);}
inline void glUniform4ui64vNV(GLint location,GLsizei count,const GLuint64EXT* value){this->_getTable()->glUniform4ui64vNV(location,count,value);}
inline void glUniform4uiEXT(GLint location,GLuint v0,GLuint v1,GLuint v2,GLuint v3){this->_getTable()->glUniform4uiEXT(location,v0,v1,v2,v3);}
inline void glUniform4ui(GLint location,GLuint v0,GLuint v1,GLuint v2,GLuint v3){this->_getTable()->glUniform4ui(location,v0,v1,v2,v3);}
inline void glUniform4uivEXT(GLint location,GLsizei count,const GLuint* value){this->_getTable()->glUniform4uivEXT(location,count,value);}
inline void glUniform4uiv(GLint location,GLsizei count,const GLuint* value){this->_getTable()->glUniform4uiv(location,count,value);}
inline void glUniformBlockBinding(GLuint program,GLuint uniformBlockIndex,GLuint uniformBlockBinding){this->_getTable()->glUniformBlockBinding(program,uniformBlockIndex,uniformBlockBinding);}
inline void glUniformBufferEXT(GLuint program,GLint location,GLuint buffer){this->_getTable()->glUniformBufferEXT(program,location,buffer);}
inline void glUniformHandleui64ARB(GLint location,GLuint64 value){this->_getTable()->glUniformHandleui64ARB(location,value);}
inline void glUniformHandleui64NV(GLint location,GLuint64 value){this->_getTable()->glUniformHandleui64NV(location,value);}
inline void glUniformHandleui64vARB(GLint location,GLsizei count,const GLuint64* value){this->_getTable()->glUniformHandleui64vARB(location,count,value);}
inline void glUniformHandleui64vNV(GLint location,GLsizei count,const GLuint64* value){this->_getTable()->glUniformHandleui64vNV(location,count,value);}
inline void glUniformMatrix2dv(GLint location,GLsizei count,GLboolean transpose,const GLdouble* value){this->_getTable()->glUniformMatrix2dv(location,count,transpose,value);}
inline void glUniformMatrix2fvARB(GLint location,GLsizei count,GLboolean transpose,const GLfloat* value){this->_getTable()->glUniformMatrix2fvARB(location,count,transpose,value);}
inline void glUniformMatrix2fv(GLint location,GLsizei count,GLboolean transpose,const GLfloat* value){this->_getTable()->glUniformMatrix2fv(location,count,transpose,value);}
inline void glUniformMatrix2x3dv(GLint location,GLsizei count,GLboolean transpose,const GLdouble* value){this->_getTable()->glUniformMatrix2x3dv(location,count,transpose,value);}
inline void glUniformMatrix2x3fv(GLint location,GLsizei count,GLboolean transpose,const GLfloat* value){this->_getTable()->glUniformMatrix2x3fv(location,count,transpose,value);}
inline void glUniformMatrix2x4dv(GLint location,GLsizei count,GLboolean transpose,const GLdouble* value){this->_getTable()->glUniformMatrix2x4dv(location,count,transpose,value);}
inline void glUniformMatrix2x4fv(GLint location,GLsizei count,GLboolean transpose,const GLfloat* value){this->_getTable()->glUniformMatrix2x4fv(location,count,transpose,value);}
inline void glUniformMatrix3dv(GLint location,GLsizei count,GLboolean transpose,const GLdouble* value){this->_getTable()->glUniformMatrix3dv(location,count,transpose,value);}
inline void glUniformMatrix3fvARB(GLint location,GLsizei count,GLboolean transpose,const GLfloat* value){this->_getTable()->glUniformMatrix3fvARB(location,count,transpose,value);}
inline void glUniformMatrix3fv(GLint location,GLsizei count,GLboolean transpose,const GLfloat* value){this->_getTable()->glUniformMatrix3fv(location,count,transpose,value);}
inline void glUniformMatrix3x2dv(GLint location,GLsizei count,GLboolean transpose,const GLdouble* value){this->_getTable()->glUniformMatrix3x2dv(location,count,transpose,value);}
inline void glUniformMatrix3x2fv(GLint location,GLsizei count,GLboolean transpose,const GLfloat* value){this->_getTable()->glUniformMatrix3x2fv(location,count,transpose,value);}
inline void glUniformMatrix3x4dv(GLint location,GLsizei count,GLboolean transpose,const GLdouble* value){this->_getTable()->glUniformMatrix3x4dv(location,count,transpose,value);}
inline void glUniformMatrix3x4fv(GLint location,GLsizei count,GLboolean transpose,const GLfloat* value){this->_getTable()->glUniformMatrix3x4fv(location,count,transpose,value);}
inline void glUniformMatrix4dv(GLint location,GLsizei count,GLboolean transpose,const GLdouble* value){this->_getTable()->glUniformMatrix4dv(location,count,transpose,value);}
inline void glUniformMatrix4fvARB(GLint location,GLsizei count,GLboolean transpose,const GLfloat* value){this->_getTable()->glUniformMatrix4fvARB(location,count,transpose,value);}
inline void glUniformMatrix4fv(GLint location,GLsizei count,GLboolean transpose,const GLfloat* value){this->_getTable()->glUniformMatrix4fv(location,count,transpose,value);}
inline void glUniformMatrix4x2dv(GLint location,GLsizei count,GLboolean transpose,const GLdouble* value){this->_getTable()->glUniformMatrix4x2dv(location,count,transpose,value);}
inline void glUniformMatrix4x2fv(GLint location,GLsizei count,GLboolean transpose,const GLfloat* value){this->_getTable()->glUniformMatrix4x2fv(location,count,transpose,value);}
inline void glUniformMatrix4x3dv(GLint location,GLsizei count,GLboolean transpose,const GLdouble* value){this->_getTable()->glUniformMatrix4x3dv(location,count,transpose,value);}
inline void glUniformMatrix4x3fv(GLint location,GLsizei count,GLboolean transpose,const GLfloat* value){this->_getTable()->glUniformMatrix4x3fv(location,count,transpose,value);}
inline void glUniformSubroutinesuiv(GLenum shadertype,GLsizei count,const GLuint* indices){this->_getTable()->glUniformSubroutinesuiv(shadertype,count,indices);}
inline void glUniformui64NV(GLint location,GLuint64EXT value){this->_getTable()->glUniformui64NV(location,value);}
inline void glUniformui64vNV(GLint location,GLsizei count,const GLuint64EXT* value){this->_getTable()->glUniformui64vNV(location,count,value);}
inline void glUnlockArraysEXT(){this->_getTable()->glUnlockArraysEXT();}
inline void glUnmapObjectBufferATI(GLuint buffer){this->_getTable()->glUnmapObjectBufferATI(buffer);}
inline void glUnmapTexture2DINTEL(GLuint texture,GLint level){this->_getTable()->glUnmapTexture2DINTEL(texture,level);}
inline void glUpdateObjectBufferATI(GLuint buffer,GLuint offset,GLsizei size,const void* pointer,GLenum preserve){this->_getTable()->glUpdateObjectBufferATI(buffer,offset,size,pointer,preserve);}
inline void glUseProgram(GLuint program){this->_getTable()->glUseProgram(program);}
inline void glUseProgramObjectARB(GLhandleARB programObj){this->_getTable()->glUseProgramObjectARB(programObj);}
inline void glUseProgramStages(GLuint pipeline,GLbitfield stages,GLuint program){this->_getTable()->glUseProgramStages(pipeline,stages,program);}
inline void glUseShaderProgramEXT(GLenum type,GLuint program){this->_getTable()->glUseShaderProgramEXT(type,program);}
inline void glValidateProgramARB(GLhandleARB programObj){this->_getTable()->glValidateProgramARB(programObj);}
inline void glValidateProgram(GLuint program){this->_getTable()->glValidateProgram(program);}
inline void glValidateProgramPipeline(GLuint pipeline){this->_getTable()->glValidateProgramPipeline(pipeline);}
inline void glVariantArrayObjectATI(GLuint id,GLenum type,GLsizei stride,GLuint buffer,GLuint offset){this->_getTable()->glVariantArrayObjectATI(id,type,stride,buffer,offset);}
inline void glVariantbvEXT(GLuint id,const GLbyte* addr){this->_getTable()->glVariantbvEXT(id,addr);}
inline void glVariantdvEXT(GLuint id,const GLdouble* addr){this->_getTable()->glVariantdvEXT(id,addr);}
inline void glVariantfvEXT(GLuint id,const GLfloat* addr){this->_getTable()->glVariantfvEXT(id,addr);}
inline void glVariantivEXT(GLuint id,const GLint* addr){this->_getTable()->glVariantivEXT(id,addr);}
inline void glVariantPointerEXT(GLuint id,GLenum type,GLuint stride,const void* addr){this->_getTable()->glVariantPointerEXT(id,type,stride,addr);}
inline void glVariantsvEXT(GLuint id,const GLshort* addr){this->_getTable()->glVariantsvEXT(id,addr);}
inline void glVariantubvEXT(GLuint id,const GLubyte* addr){this->_getTable()->glVariantubvEXT(id,addr);}
inline void glVariantuivEXT(GLuint id,const GLuint* addr){this->_getTable()->glVariantuivEXT(id,addr);}
inline void glVariantusvEXT(GLuint id,const GLushort* addr){this->_getTable()->glVariantusvEXT(id,addr);}
inline void glVDPAUFiniNV(){this->_getTable()->glVDPAUFiniNV();}
inline void glVDPAUGetSurfaceivNV(GLvdpauSurfaceNV surface,GLenum pname,GLsizei bufSize,GLsizei* length,GLint* values){this->_getTable()->glVDPAUGetSurfaceivNV(surface,pname,bufSize,length,values);}
inline void glVDPAUInitNV(const void* vdpDevice,const void* getProcAddress){this->_getTable()->glVDPAUInitNV(vdpDevice,getProcAddress);}
inline void glVDPAUMapSurfacesNV(GLsizei numSurfaces,const GLvdpauSurfaceNV* surfaces){this->_getTable()->glVDPAUMapSurfacesNV(numSurfaces,surfaces);}
inline void glVDPAUSurfaceAccessNV(GLvdpauSurfaceNV surface,GLenum access){this->_getTable()->glVDPAUSurfaceAccessNV(surface,access);}
inline void glVDPAUUnmapSurfacesNV(GLsizei numSurface,const GLvdpauSurfaceNV* surfaces){this->_getTable()->glVDPAUUnmapSurfacesNV(numSurface,surfaces);}
inline void glVDPAUUnregisterSurfaceNV(GLvdpauSurfaceNV surface){this->_getTable()->glVDPAUUnregisterSurfaceNV(surface);}
inline void glVertex2bOES(GLbyte x,GLbyte y){this->_getTable()->glVertex2bOES(x,y);}
inline void glVertex2bvOES(const GLbyte* coords){this->_getTable()->glVertex2bvOES(coords);}
inline void glVertex2d(GLdouble x,GLdouble y){this->_getTable()->glVertex2d(x,y);}
inline void glVertex2dv(const GLdouble* v){this->_getTable()->glVertex2dv(v);}
inline void glVertex2f(GLfloat x,GLfloat y){this->_getTable()->glVertex2f(x,y);}
inline void glVertex2fv(const GLfloat* v){this->_getTable()->glVertex2fv(v);}
inline void glVertex2hNV(GLhalfNV x,GLhalfNV y){this->_getTable()->glVertex2hNV(x,y);}
inline void glVertex2hvNV(const GLhalfNV* v){this->_getTable()->glVertex2hvNV(v);}
inline void glVertex2i(GLint x,GLint y){this->_getTable()->glVertex2i(x,y);}
inline void glVertex2iv(const GLint* v){this->_getTable()->glVertex2iv(v);}
inline void glVertex2s(GLshort x,GLshort y){this->_getTable()->glVertex2s(x,y);}
inline void glVertex2sv(const GLshort* v){this->_getTable()->glVertex2sv(v);}
inline void glVertex2xOES(GLfixed x){this->_getTable()->glVertex2xOES(x);}
inline void glVertex2xvOES(const GLfixed* coords){this->_getTable()->glVertex2xvOES(coords);}
inline void glVertex3bOES(GLbyte x,GLbyte y,GLbyte z){this->_getTable()->glVertex3bOES(x,y,z);}
inline void glVertex3bvOES(const GLbyte* coords){this->_getTable()->glVertex3bvOES(coords);}
inline void glVertex3d(GLdouble x,GLdouble y,GLdouble z){this->_getTable()->glVertex3d(x,y,z);}
inline void glVertex3dv(const GLdouble* v){this->_getTable()->glVertex3dv(v);}
inline void glVertex3f(GLfloat x,GLfloat y,GLfloat z){this->_getTable()->glVertex3f(x,y,z);}
inline void glVertex3fv(const GLfloat* v){this->_getTable()->glVertex3fv(v);}
inline void glVertex3hNV(GLhalfNV x,GLhalfNV y,GLhalfNV z){this->_getTable()->glVertex3hNV(x,y,z);}
inline void glVertex3hvNV(const GLhalfNV* v){this->_getTable()->glVertex3hvNV(v);}
inline void glVertex3i(GLint x,GLint y,GLint z){this->_getTable()->glVertex3i(x,y,z);}
inline void glVertex3iv(const GLint* v){this->_getTable()->glVertex3iv(v);}
inline void glVertex3s(GLshort x,GLshort y,GLshort z){this->_getTable()->glVertex3s(x,y,z);}
inline void glVertex3sv(const GLshort* v){this->_getTable()->glVertex3sv(v);}
inline void glVertex3xOES(GLfixed x,GLfixed y){this->_getTable()->glVertex3xOES(x,y);}
inline void glVertex3xvOES(const GLfixed* coords){this->_getTable()->glVertex3xvOES(coords);}
inline void glVertex4bOES(GLbyte x,GLbyte y,GLbyte z,GLbyte w){this->_getTable()->glVertex4bOES(x,y,z,w);}
inline void glVertex4bvOES(const GLbyte* coords){this->_getTable()->glVertex4bvOES(coords);}
inline void glVertex4d(GLdouble x,GLdouble y,GLdouble z,GLdouble w){this->_getTable()->glVertex4d(x,y,z,w);}
inline void glVertex4dv(const GLdouble* v){this->_getTable()->glVertex4dv(v);}
inline void glVertex4f(GLfloat x,GLfloat y,GLfloat z,GLfloat w){this->_getTable()->glVertex4f(x,y,z,w);}
inline void glVertex4fv(const GLfloat* v){this->_getTable()->glVertex4fv(v);}
inline void glVertex4hNV(GLhalfNV x,GLhalfNV y,GLhalfNV z,GLhalfNV w){this->_getTable()->glVertex4hNV(x,y,z,w);}
inline void glVertex4hvNV(const GLhalfNV* v){this->_getTable()->glVertex4hvNV(v);}
inline void glVertex4i(GLint x,GLint y,GLint z,GLint w){this->_getTable()->glVertex4i(x,y,z,w);}
inline void glVertex4iv(const GLint* v){this->_getTable()->glVertex4iv(v);}
inline void glVertex4s(GLshort x,GLshort y,GLshort z,GLshort w){this->_getTable()->glVertex4s(x,y,z,w);}
inline void glVertex4sv(const GLshort* v){this->_getTable()->glVertex4sv(v);}
inline void glVertex4xOES(GLfixed x,GLfixed y,GLfixed z){this->_getTable()->glVertex4xOES(x,y,z);}
inline void glVertex4xvOES(const GLfixed* coords){this->_getTable()->glVertex4xvOES(coords);}
inline void glVertexArrayAttribBinding(GLuint vaobj,GLuint attribindex,GLuint bindingindex){this->_getTable()->glVertexArrayAttribBinding(vaobj,attribindex,bindingindex);}
inline void glVertexArrayAttribFormat(GLuint vaobj,GLuint attribindex,GLint size,GLenum type,GLboolean normalized,GLuint relativeoffset){this->_getTable()->glVertexArrayAttribFormat(vaobj,attribindex,size,type,normalized,relativeoffset);}
inline void glVertexArrayAttribIFormat(GLuint vaobj,GLuint attribindex,GLint size,GLenum type,GLuint relativeoffset){this->_getTable()->glVertexArrayAttribIFormat(vaobj,attribindex,size,type,relativeoffset);}
inline void glVertexArrayAttribLFormat(GLuint vaobj,GLuint attribindex,GLint size,GLenum type,GLuint relativeoffset){this->_getTable()->glVertexArrayAttribLFormat(vaobj,attribindex,size,type,relativeoffset);}
inline void glVertexArrayBindingDivisor(GLuint vaobj,GLuint bindingindex,GLuint divisor){this->_getTable()->glVertexArrayBindingDivisor(vaobj,bindingindex,divisor);}
inline void glVertexArrayBindVertexBufferEXT(GLuint vaobj,GLuint bindingindex,GLuint buffer,GLintptr offset,GLsizei stride){this->_getTable()->glVertexArrayBindVertexBufferEXT(vaobj,bindingindex,buffer,offset,stride);}
inline void glVertexArrayColorOffsetEXT(GLuint vaobj,GLuint buffer,GLint size,GLenum type,GLsizei stride,GLintptr offset){this->_getTable()->glVertexArrayColorOffsetEXT(vaobj,buffer,size,type,stride,offset);}
inline void glVertexArrayEdgeFlagOffsetEXT(GLuint vaobj,GLuint buffer,GLsizei stride,GLintptr offset){this->_getTable()->glVertexArrayEdgeFlagOffsetEXT(vaobj,buffer,stride,offset);}
inline void glVertexArrayElementBuffer(GLuint vaobj,GLuint buffer){this->_getTable()->glVertexArrayElementBuffer(vaobj,buffer);}
inline void glVertexArrayFogCoordOffsetEXT(GLuint vaobj,GLuint buffer,GLenum type,GLsizei stride,GLintptr offset){this->_getTable()->glVertexArrayFogCoordOffsetEXT(vaobj,buffer,type,stride,offset);}
inline void glVertexArrayIndexOffsetEXT(GLuint vaobj,GLuint buffer,GLenum type,GLsizei stride,GLintptr offset){this->_getTable()->glVertexArrayIndexOffsetEXT(vaobj,buffer,type,stride,offset);}
inline void glVertexArrayMultiTexCoordOffsetEXT(GLuint vaobj,GLuint buffer,GLenum texunit,GLint size,GLenum type,GLsizei stride,GLintptr offset){this->_getTable()->glVertexArrayMultiTexCoordOffsetEXT(vaobj,buffer,texunit,size,type,stride,offset);}
inline void glVertexArrayNormalOffsetEXT(GLuint vaobj,GLuint buffer,GLenum type,GLsizei stride,GLintptr offset){this->_getTable()->glVertexArrayNormalOffsetEXT(vaobj,buffer,type,stride,offset);}
inline void glVertexArrayParameteriAPPLE(GLenum pname,GLint param){this->_getTable()->glVertexArrayParameteriAPPLE(pname,param);}
inline void glVertexArrayRangeAPPLE(GLsizei length,void* pointer){this->_getTable()->glVertexArrayRangeAPPLE(length,pointer);}
inline void glVertexArrayRangeNV(GLsizei length,const void* pointer){this->_getTable()->glVertexArrayRangeNV(length,pointer);}
inline void glVertexArraySecondaryColorOffsetEXT(GLuint vaobj,GLuint buffer,GLint size,GLenum type,GLsizei stride,GLintptr offset){this->_getTable()->glVertexArraySecondaryColorOffsetEXT(vaobj,buffer,size,type,stride,offset);}
inline void glVertexArrayTexCoordOffsetEXT(GLuint vaobj,GLuint buffer,GLint size,GLenum type,GLsizei stride,GLintptr offset){this->_getTable()->glVertexArrayTexCoordOffsetEXT(vaobj,buffer,size,type,stride,offset);}
inline void glVertexArrayVertexAttribBindingEXT(GLuint vaobj,GLuint attribindex,GLuint bindingindex){this->_getTable()->glVertexArrayVertexAttribBindingEXT(vaobj,attribindex,bindingindex);}
inline void glVertexArrayVertexAttribDivisorEXT(GLuint vaobj,GLuint index,GLuint divisor){this->_getTable()->glVertexArrayVertexAttribDivisorEXT(vaobj,index,divisor);}
inline void glVertexArrayVertexAttribFormatEXT(GLuint vaobj,GLuint attribindex,GLint size,GLenum type,GLboolean normalized,GLuint relativeoffset){this->_getTable()->glVertexArrayVertexAttribFormatEXT(vaobj,attribindex,size,type,normalized,relativeoffset);}
inline void glVertexArrayVertexAttribIFormatEXT(GLuint vaobj,GLuint attribindex,GLint size,GLenum type,GLuint relativeoffset){this->_getTable()->glVertexArrayVertexAttribIFormatEXT(vaobj,attribindex,size,type,relativeoffset);}
inline void glVertexArrayVertexAttribIOffsetEXT(GLuint vaobj,GLuint buffer,GLuint index,GLint size,GLenum type,GLsizei stride,GLintptr offset){this->_getTable()->glVertexArrayVertexAttribIOffsetEXT(vaobj,buffer,index,size,type,stride,offset);}
inline void glVertexArrayVertexAttribLFormatEXT(GLuint vaobj,GLuint attribindex,GLint size,GLenum type,GLuint relativeoffset){this->_getTable()->glVertexArrayVertexAttribLFormatEXT(vaobj,attribindex,size,type,relativeoffset);}
inline void glVertexArrayVertexAttribLOffsetEXT(GLuint vaobj,GLuint buffer,GLuint index,GLint size,GLenum type,GLsizei stride,GLintptr offset){this->_getTable()->glVertexArrayVertexAttribLOffsetEXT(vaobj,buffer,index,size,type,stride,offset);}
inline void glVertexArrayVertexAttribOffsetEXT(GLuint vaobj,GLuint buffer,GLuint index,GLint size,GLenum type,GLboolean normalized,GLsizei stride,GLintptr offset){this->_getTable()->glVertexArrayVertexAttribOffsetEXT(vaobj,buffer,index,size,type,normalized,stride,offset);}
inline void glVertexArrayVertexBindingDivisorEXT(GLuint vaobj,GLuint bindingindex,GLuint divisor){this->_getTable()->glVertexArrayVertexBindingDivisorEXT(vaobj,bindingindex,divisor);}
inline void glVertexArrayVertexBuffer(GLuint vaobj,GLuint bindingindex,GLuint buffer,GLintptr offset,GLsizei stride){this->_getTable()->glVertexArrayVertexBuffer(vaobj,bindingindex,buffer,offset,stride);}
inline void glVertexArrayVertexBuffers(GLuint vaobj,GLuint first,GLsizei count,const GLuint* buffers,const GLintptr* offsets,const GLsizei* strides){this->_getTable()->glVertexArrayVertexBuffers(vaobj,first,count,buffers,offsets,strides);}
inline void glVertexArrayVertexOffsetEXT(GLuint vaobj,GLuint buffer,GLint size,GLenum type,GLsizei stride,GLintptr offset){this->_getTable()->glVertexArrayVertexOffsetEXT(vaobj,buffer,size,type,stride,offset);}
inline void glVertexAttrib1dARB(GLuint index,GLdouble x){this->_getTable()->glVertexAttrib1dARB(index,x);}
inline void glVertexAttrib1d(GLuint index,GLdouble x){this->_getTable()->glVertexAttrib1d(index,x);}
inline void glVertexAttrib1dNV(GLuint index,GLdouble x){this->_getTable()->glVertexAttrib1dNV(index,x);}
inline void glVertexAttrib1dvARB(GLuint index,const GLdouble* v){this->_getTable()->glVertexAttrib1dvARB(index,v);}
inline void glVertexAttrib1dv(GLuint index,const GLdouble* v){this->_getTable()->glVertexAttrib1dv(index,v);}
inline void glVertexAttrib1dvNV(GLuint index,const GLdouble* v){this->_getTable()->glVertexAttrib1dvNV(index,v);}
inline void glVertexAttrib1fARB(GLuint index,GLfloat x){this->_getTable()->glVertexAttrib1fARB(index,x);}
inline void glVertexAttrib1f(GLuint index,GLfloat x){this->_getTable()->glVertexAttrib1f(index,x);}
inline void glVertexAttrib1fNV(GLuint index,GLfloat x){this->_getTable()->glVertexAttrib1fNV(index,x);}
inline void glVertexAttrib1fvARB(GLuint index,const GLfloat* v){this->_getTable()->glVertexAttrib1fvARB(index,v);}
inline void glVertexAttrib1fv(GLuint index,const GLfloat* v){this->_getTable()->glVertexAttrib1fv(index,v);}
inline void glVertexAttrib1fvNV(GLuint index,const GLfloat* v){this->_getTable()->glVertexAttrib1fvNV(index,v);}
inline void glVertexAttrib1hNV(GLuint index,GLhalfNV x){this->_getTable()->glVertexAttrib1hNV(index,x);}
inline void glVertexAttrib1hvNV(GLuint index,const GLhalfNV* v){this->_getTable()->glVertexAttrib1hvNV(index,v);}
inline void glVertexAttrib1sARB(GLuint index,GLshort x){this->_getTable()->glVertexAttrib1sARB(index,x);}
inline void glVertexAttrib1s(GLuint index,GLshort x){this->_getTable()->glVertexAttrib1s(index,x);}
inline void glVertexAttrib1sNV(GLuint index,GLshort x){this->_getTable()->glVertexAttrib1sNV(index,x);}
inline void glVertexAttrib1svARB(GLuint index,const GLshort* v){this->_getTable()->glVertexAttrib1svARB(index,v);}
inline void glVertexAttrib1sv(GLuint index,const GLshort* v){this->_getTable()->glVertexAttrib1sv(index,v);}
inline void glVertexAttrib1svNV(GLuint index,const GLshort* v){this->_getTable()->glVertexAttrib1svNV(index,v);}
inline void glVertexAttrib2dARB(GLuint index,GLdouble x,GLdouble y){this->_getTable()->glVertexAttrib2dARB(index,x,y);}
inline void glVertexAttrib2d(GLuint index,GLdouble x,GLdouble y){this->_getTable()->glVertexAttrib2d(index,x,y);}
inline void glVertexAttrib2dNV(GLuint index,GLdouble x,GLdouble y){this->_getTable()->glVertexAttrib2dNV(index,x,y);}
inline void glVertexAttrib2dvARB(GLuint index,const GLdouble* v){this->_getTable()->glVertexAttrib2dvARB(index,v);}
inline void glVertexAttrib2dv(GLuint index,const GLdouble* v){this->_getTable()->glVertexAttrib2dv(index,v);}
inline void glVertexAttrib2dvNV(GLuint index,const GLdouble* v){this->_getTable()->glVertexAttrib2dvNV(index,v);}
inline void glVertexAttrib2fARB(GLuint index,GLfloat x,GLfloat y){this->_getTable()->glVertexAttrib2fARB(index,x,y);}
inline void glVertexAttrib2f(GLuint index,GLfloat x,GLfloat y){this->_getTable()->glVertexAttrib2f(index,x,y);}
inline void glVertexAttrib2fNV(GLuint index,GLfloat x,GLfloat y){this->_getTable()->glVertexAttrib2fNV(index,x,y);}
inline void glVertexAttrib2fvARB(GLuint index,const GLfloat* v){this->_getTable()->glVertexAttrib2fvARB(index,v);}
inline void glVertexAttrib2fv(GLuint index,const GLfloat* v){this->_getTable()->glVertexAttrib2fv(index,v);}
inline void glVertexAttrib2fvNV(GLuint index,const GLfloat* v){this->_getTable()->glVertexAttrib2fvNV(index,v);}
inline void glVertexAttrib2hNV(GLuint index,GLhalfNV x,GLhalfNV y){this->_getTable()->glVertexAttrib2hNV(index,x,y);}
inline void glVertexAttrib2hvNV(GLuint index,const GLhalfNV* v){this->_getTable()->glVertexAttrib2hvNV(index,v);}
inline void glVertexAttrib2sARB(GLuint index,GLshort x,GLshort y){this->_getTable()->glVertexAttrib2sARB(index,x,y);}
inline void glVertexAttrib2s(GLuint index,GLshort x,GLshort y){this->_getTable()->glVertexAttrib2s(index,x,y);}
inline void glVertexAttrib2sNV(GLuint index,GLshort x,GLshort y){this->_getTable()->glVertexAttrib2sNV(index,x,y);}
inline void glVertexAttrib2svARB(GLuint index,const GLshort* v){this->_getTable()->glVertexAttrib2svARB(index,v);}
inline void glVertexAttrib2sv(GLuint index,const GLshort* v){this->_getTable()->glVertexAttrib2sv(index,v);}
inline void glVertexAttrib2svNV(GLuint index,const GLshort* v){this->_getTable()->glVertexAttrib2svNV(index,v);}
inline void glVertexAttrib3dARB(GLuint index,GLdouble x,GLdouble y,GLdouble z){this->_getTable()->glVertexAttrib3dARB(index,x,y,z);}
inline void glVertexAttrib3d(GLuint index,GLdouble x,GLdouble y,GLdouble z){this->_getTable()->glVertexAttrib3d(index,x,y,z);}
inline void glVertexAttrib3dNV(GLuint index,GLdouble x,GLdouble y,GLdouble z){this->_getTable()->glVertexAttrib3dNV(index,x,y,z);}
inline void glVertexAttrib3dvARB(GLuint index,const GLdouble* v){this->_getTable()->glVertexAttrib3dvARB(index,v);}
inline void glVertexAttrib3dv(GLuint index,const GLdouble* v){this->_getTable()->glVertexAttrib3dv(index,v);}
inline void glVertexAttrib3dvNV(GLuint index,const GLdouble* v){this->_getTable()->glVertexAttrib3dvNV(index,v);}
inline void glVertexAttrib3fARB(GLuint index,GLfloat x,GLfloat y,GLfloat z){this->_getTable()->glVertexAttrib3fARB(index,x,y,z);}
inline void glVertexAttrib3f(GLuint index,GLfloat x,GLfloat y,GLfloat z){this->_getTable()->glVertexAttrib3f(index,x,y,z);}
inline void glVertexAttrib3fNV(GLuint index,GLfloat x,GLfloat y,GLfloat z){this->_getTable()->glVertexAttrib3fNV(index,x,y,z);}
inline void glVertexAttrib3fvARB(GLuint index,const GLfloat* v){this->_getTable()->glVertexAttrib3fvARB(index,v);}
inline void glVertexAttrib3fv(GLuint index,const GLfloat* v){this->_getTable()->glVertexAttrib3fv(index,v);}
inline void glVertexAttrib3fvNV(GLuint index,const GLfloat* v){this->_getTable()->glVertexAttrib3fvNV(index,v);}
inline void glVertexAttrib3hNV(GLuint index,GLhalfNV x,GLhalfNV y,GLhalfNV z){this->_getTable()->glVertexAttrib3hNV(index,x,y,z);}
inline void glVertexAttrib3hvNV(GLuint index,const GLhalfNV* v){this->_getTable()->glVertexAttrib3hvNV(index,v);}
inline void glVertexAttrib3sARB(GLuint index,GLshort x,GLshort y,GLshort z){this->_getTable()->glVertexAttrib3sARB(index,x,y,z);}
inline void glVertexAttrib3s(GLuint index,GLshort x,GLshort y,GLshort z){this->_getTable()->glVertexAttrib3s(index,x,y,z);}
inline void glVertexAttrib3sNV(GLuint index,GLshort x,GLshort y,GLshort z){this->_getTable()->glVertexAttrib3sNV(index,x,y,z);}
inline void glVertexAttrib3svARB(GLuint index,const GLshort* v){this->_getTable()->glVertexAttrib3svARB(index,v);}
inline void glVertexAttrib3sv(GLuint index,const GLshort* v){this->_getTable()->glVertexAttrib3sv(index,v);}
inline void glVertexAttrib3svNV(GLuint index,const GLshort* v){this->_getTable()->glVertexAttrib3svNV(index,v);}
inline void glVertexAttrib4bvARB(GLuint index,const GLbyte* v){this->_getTable()->glVertexAttrib4bvARB(index,v);}
inline void glVertexAttrib4bv(GLuint index,const GLbyte* v){this->_getTable()->glVertexAttrib4bv(index,v);}
inline void glVertexAttrib4dARB(GLuint index,GLdouble x,GLdouble y,GLdouble z,GLdouble w){this->_getTable()->glVertexAttrib4dARB(index,x,y,z,w);}
inline void glVertexAttrib4d(GLuint index,GLdouble x,GLdouble y,GLdouble z,GLdouble w){this->_getTable()->glVertexAttrib4d(index,x,y,z,w);}
inline void glVertexAttrib4dNV(GLuint index,GLdouble x,GLdouble y,GLdouble z,GLdouble w){this->_getTable()->glVertexAttrib4dNV(index,x,y,z,w);}
inline void glVertexAttrib4dvARB(GLuint index,const GLdouble* v){this->_getTable()->glVertexAttrib4dvARB(index,v);}
inline void glVertexAttrib4dv(GLuint index,const GLdouble* v){this->_getTable()->glVertexAttrib4dv(index,v);}
inline void glVertexAttrib4dvNV(GLuint index,const GLdouble* v){this->_getTable()->glVertexAttrib4dvNV(index,v);}
inline void glVertexAttrib4fARB(GLuint index,GLfloat x,GLfloat y,GLfloat z,GLfloat w){this->_getTable()->glVertexAttrib4fARB(index,x,y,z,w);}
inline void glVertexAttrib4f(GLuint index,GLfloat x,GLfloat y,GLfloat z,GLfloat w){this->_getTable()->glVertexAttrib4f(index,x,y,z,w);}
inline void glVertexAttrib4fNV(GLuint index,GLfloat x,GLfloat y,GLfloat z,GLfloat w){this->_getTable()->glVertexAttrib4fNV(index,x,y,z,w);}
inline void glVertexAttrib4fvARB(GLuint index,const GLfloat* v){this->_getTable()->glVertexAttrib4fvARB(index,v);}
inline void glVertexAttrib4fv(GLuint index,const GLfloat* v){this->_getTable()->glVertexAttrib4fv(index,v);}
inline void glVertexAttrib4fvNV(GLuint index,const GLfloat* v){this->_getTable()->glVertexAttrib4fvNV(index,v);}
inline void glVertexAttrib4hNV(GLuint index,GLhalfNV x,GLhalfNV y,GLhalfNV z,GLhalfNV w){this->_getTable()->glVertexAttrib4hNV(index,x,y,z,w);}
inline void glVertexAttrib4hvNV(GLuint index,const GLhalfNV* v){this->_getTable()->glVertexAttrib4hvNV(index,v);}
inline void glVertexAttrib4ivARB(GLuint index,const GLint* v){this->_getTable()->glVertexAttrib4ivARB(index,v);}
inline void glVertexAttrib4iv(GLuint index,const GLint* v){this->_getTable()->glVertexAttrib4iv(index,v);}
inline void glVertexAttrib4NbvARB(GLuint index,const GLbyte* v){this->_getTable()->glVertexAttrib4NbvARB(index,v);}
inline void glVertexAttrib4Nbv(GLuint index,const GLbyte* v){this->_getTable()->glVertexAttrib4Nbv(index,v);}
inline void glVertexAttrib4NivARB(GLuint index,const GLint* v){this->_getTable()->glVertexAttrib4NivARB(index,v);}
inline void glVertexAttrib4Niv(GLuint index,const GLint* v){this->_getTable()->glVertexAttrib4Niv(index,v);}
inline void glVertexAttrib4NsvARB(GLuint index,const GLshort* v){this->_getTable()->glVertexAttrib4NsvARB(index,v);}
inline void glVertexAttrib4Nsv(GLuint index,const GLshort* v){this->_getTable()->glVertexAttrib4Nsv(index,v);}
inline void glVertexAttrib4NubARB(GLuint index,GLubyte x,GLubyte y,GLubyte z,GLubyte w){this->_getTable()->glVertexAttrib4NubARB(index,x,y,z,w);}
inline void glVertexAttrib4Nub(GLuint index,GLubyte x,GLubyte y,GLubyte z,GLubyte w){this->_getTable()->glVertexAttrib4Nub(index,x,y,z,w);}
inline void glVertexAttrib4NubvARB(GLuint index,const GLubyte* v){this->_getTable()->glVertexAttrib4NubvARB(index,v);}
inline void glVertexAttrib4Nubv(GLuint index,const GLubyte* v){this->_getTable()->glVertexAttrib4Nubv(index,v);}
inline void glVertexAttrib4NuivARB(GLuint index,const GLuint* v){this->_getTable()->glVertexAttrib4NuivARB(index,v);}
inline void glVertexAttrib4Nuiv(GLuint index,const GLuint* v){this->_getTable()->glVertexAttrib4Nuiv(index,v);}
inline void glVertexAttrib4NusvARB(GLuint index,const GLushort* v){this->_getTable()->glVertexAttrib4NusvARB(index,v);}
inline void glVertexAttrib4Nusv(GLuint index,const GLushort* v){this->_getTable()->glVertexAttrib4Nusv(index,v);}
inline void glVertexAttrib4sARB(GLuint index,GLshort x,GLshort y,GLshort z,GLshort w){this->_getTable()->glVertexAttrib4sARB(index,x,y,z,w);}
inline void glVertexAttrib4s(GLuint index,GLshort x,GLshort y,GLshort z,GLshort w){this->_getTable()->glVertexAttrib4s(index,x,y,z,w);}
inline void glVertexAttrib4sNV(GLuint index,GLshort x,GLshort y,GLshort z,GLshort w){this->_getTable()->glVertexAttrib4sNV(index,x,y,z,w);}
inline void glVertexAttrib4svARB(GLuint index,const GLshort* v){this->_getTable()->glVertexAttrib4svARB(index,v);}
inline void glVertexAttrib4sv(GLuint index,const GLshort* v){this->_getTable()->glVertexAttrib4sv(index,v);}
inline void glVertexAttrib4svNV(GLuint index,const GLshort* v){this->_getTable()->glVertexAttrib4svNV(index,v);}
inline void glVertexAttrib4ubNV(GLuint index,GLubyte x,GLubyte y,GLubyte z,GLubyte w){this->_getTable()->glVertexAttrib4ubNV(index,x,y,z,w);}
inline void glVertexAttrib4ubvARB(GLuint index,const GLubyte* v){this->_getTable()->glVertexAttrib4ubvARB(index,v);}
inline void glVertexAttrib4ubv(GLuint index,const GLubyte* v){this->_getTable()->glVertexAttrib4ubv(index,v);}
inline void glVertexAttrib4ubvNV(GLuint index,const GLubyte* v){this->_getTable()->glVertexAttrib4ubvNV(index,v);}
inline void glVertexAttrib4uivARB(GLuint index,const GLuint* v){this->_getTable()->glVertexAttrib4uivARB(index,v);}
inline void glVertexAttrib4uiv(GLuint index,const GLuint* v){this->_getTable()->glVertexAttrib4uiv(index,v);}
inline void glVertexAttrib4usvARB(GLuint index,const GLushort* v){this->_getTable()->glVertexAttrib4usvARB(index,v);}
inline void glVertexAttrib4usv(GLuint index,const GLushort* v){this->_getTable()->glVertexAttrib4usv(index,v);}
inline void glVertexAttribArrayObjectATI(GLuint index,GLint size,GLenum type,GLboolean normalized,GLsizei stride,GLuint buffer,GLuint offset){this->_getTable()->glVertexAttribArrayObjectATI(index,size,type,normalized,stride,buffer,offset);}
inline void glVertexAttribBinding(GLuint attribindex,GLuint bindingindex){this->_getTable()->glVertexAttribBinding(attribindex,bindingindex);}
inline void glVertexAttribDivisorARB(GLuint index,GLuint divisor){this->_getTable()->glVertexAttribDivisorARB(index,divisor);}
inline void glVertexAttribDivisor(GLuint index,GLuint divisor){this->_getTable()->glVertexAttribDivisor(index,divisor);}
inline void glVertexAttribFormat(GLuint attribindex,GLint size,GLenum type,GLboolean normalized,GLuint relativeoffset){this->_getTable()->glVertexAttribFormat(attribindex,size,type,normalized,relativeoffset);}
inline void glVertexAttribFormatNV(GLuint index,GLint size,GLenum type,GLboolean normalized,GLsizei stride){this->_getTable()->glVertexAttribFormatNV(index,size,type,normalized,stride);}
inline void glVertexAttribI1iEXT(GLuint index,GLint x){this->_getTable()->glVertexAttribI1iEXT(index,x);}
inline void glVertexAttribI1i(GLuint index,GLint x){this->_getTable()->glVertexAttribI1i(index,x);}
inline void glVertexAttribI1ivEXT(GLuint index,const GLint* v){this->_getTable()->glVertexAttribI1ivEXT(index,v);}
inline void glVertexAttribI1iv(GLuint index,const GLint* v){this->_getTable()->glVertexAttribI1iv(index,v);}
inline void glVertexAttribI1uiEXT(GLuint index,GLuint x){this->_getTable()->glVertexAttribI1uiEXT(index,x);}
inline void glVertexAttribI1ui(GLuint index,GLuint x){this->_getTable()->glVertexAttribI1ui(index,x);}
inline void glVertexAttribI1uivEXT(GLuint index,const GLuint* v){this->_getTable()->glVertexAttribI1uivEXT(index,v);}
inline void glVertexAttribI1uiv(GLuint index,const GLuint* v){this->_getTable()->glVertexAttribI1uiv(index,v);}
inline void glVertexAttribI2iEXT(GLuint index,GLint x,GLint y){this->_getTable()->glVertexAttribI2iEXT(index,x,y);}
inline void glVertexAttribI2i(GLuint index,GLint x,GLint y){this->_getTable()->glVertexAttribI2i(index,x,y);}
inline void glVertexAttribI2ivEXT(GLuint index,const GLint* v){this->_getTable()->glVertexAttribI2ivEXT(index,v);}
inline void glVertexAttribI2iv(GLuint index,const GLint* v){this->_getTable()->glVertexAttribI2iv(index,v);}
inline void glVertexAttribI2uiEXT(GLuint index,GLuint x,GLuint y){this->_getTable()->glVertexAttribI2uiEXT(index,x,y);}
inline void glVertexAttribI2ui(GLuint index,GLuint x,GLuint y){this->_getTable()->glVertexAttribI2ui(index,x,y);}
inline void glVertexAttribI2uivEXT(GLuint index,const GLuint* v){this->_getTable()->glVertexAttribI2uivEXT(index,v);}
inline void glVertexAttribI2uiv(GLuint index,const GLuint* v){this->_getTable()->glVertexAttribI2uiv(index,v);}
inline void glVertexAttribI3iEXT(GLuint index,GLint x,GLint y,GLint z){this->_getTable()->glVertexAttribI3iEXT(index,x,y,z);}
inline void glVertexAttribI3i(GLuint index,GLint x,GLint y,GLint z){this->_getTable()->glVertexAttribI3i(index,x,y,z);}
inline void glVertexAttribI3ivEXT(GLuint index,const GLint* v){this->_getTable()->glVertexAttribI3ivEXT(index,v);}
inline void glVertexAttribI3iv(GLuint index,const GLint* v){this->_getTable()->glVertexAttribI3iv(index,v);}
inline void glVertexAttribI3uiEXT(GLuint index,GLuint x,GLuint y,GLuint z){this->_getTable()->glVertexAttribI3uiEXT(index,x,y,z);}
inline void glVertexAttribI3ui(GLuint index,GLuint x,GLuint y,GLuint z){this->_getTable()->glVertexAttribI3ui(index,x,y,z);}
inline void glVertexAttribI3uivEXT(GLuint index,const GLuint* v){this->_getTable()->glVertexAttribI3uivEXT(index,v);}
inline void glVertexAttribI3uiv(GLuint index,const GLuint* v){this->_getTable()->glVertexAttribI3uiv(index,v);}
inline void glVertexAttribI4bvEXT(GLuint index,const GLbyte* v){this->_getTable()->glVertexAttribI4bvEXT(index,v);}
inline void glVertexAttribI4bv(GLuint index,const GLbyte* v){this->_getTable()->glVertexAttribI4bv(index,v);}
inline void glVertexAttribI4iEXT(GLuint index,GLint x,GLint y,GLint z,GLint w){this->_getTable()->glVertexAttribI4iEXT(index,x,y,z,w);}
inline void glVertexAttribI4i(GLuint index,GLint x,GLint y,GLint z,GLint w){this->_getTable()->glVertexAttribI4i(index,x,y,z,w);}
inline void glVertexAttribI4ivEXT(GLuint index,const GLint* v){this->_getTable()->glVertexAttribI4ivEXT(index,v);}
inline void glVertexAttribI4iv(GLuint index,const GLint* v){this->_getTable()->glVertexAttribI4iv(index,v);}
inline void glVertexAttribI4svEXT(GLuint index,const GLshort* v){this->_getTable()->glVertexAttribI4svEXT(index,v);}
inline void glVertexAttribI4sv(GLuint index,const GLshort* v){this->_getTable()->glVertexAttribI4sv(index,v);}
inline void glVertexAttribI4ubvEXT(GLuint index,const GLubyte* v){this->_getTable()->glVertexAttribI4ubvEXT(index,v);}
inline void glVertexAttribI4ubv(GLuint index,const GLubyte* v){this->_getTable()->glVertexAttribI4ubv(index,v);}
inline void glVertexAttribI4uiEXT(GLuint index,GLuint x,GLuint y,GLuint z,GLuint w){this->_getTable()->glVertexAttribI4uiEXT(index,x,y,z,w);}
inline void glVertexAttribI4ui(GLuint index,GLuint x,GLuint y,GLuint z,GLuint w){this->_getTable()->glVertexAttribI4ui(index,x,y,z,w);}
inline void glVertexAttribI4uivEXT(GLuint index,const GLuint* v){this->_getTable()->glVertexAttribI4uivEXT(index,v);}
inline void glVertexAttribI4uiv(GLuint index,const GLuint* v){this->_getTable()->glVertexAttribI4uiv(index,v);}
inline void glVertexAttribI4usvEXT(GLuint index,const GLushort* v){this->_getTable()->glVertexAttribI4usvEXT(index,v);}
inline void glVertexAttribI4usv(GLuint index,const GLushort* v){this->_getTable()->glVertexAttribI4usv(index,v);}
inline void glVertexAttribIFormat(GLuint attribindex,GLint size,GLenum type,GLuint relativeoffset){this->_getTable()->glVertexAttribIFormat(attribindex,size,type,relativeoffset);}
inline void glVertexAttribIFormatNV(GLuint index,GLint size,GLenum type,GLsizei stride){this->_getTable()->glVertexAttribIFormatNV(index,size,type,stride);}
inline void glVertexAttribIPointerEXT(GLuint index,GLint size,GLenum type,GLsizei stride,const void* pointer){this->_getTable()->glVertexAttribIPointerEXT(index,size,type,stride,pointer);}
inline void glVertexAttribIPointer(GLuint index,GLint size,GLenum type,GLsizei stride,const void* pointer){this->_getTable()->glVertexAttribIPointer(index,size,type,stride,pointer);}
inline void glVertexAttribL1dEXT(GLuint index,GLdouble x){this->_getTable()->glVertexAttribL1dEXT(index,x);}
inline void glVertexAttribL1d(GLuint index,GLdouble x){this->_getTable()->glVertexAttribL1d(index,x);}
inline void glVertexAttribL1dvEXT(GLuint index,const GLdouble* v){this->_getTable()->glVertexAttribL1dvEXT(index,v);}
inline void glVertexAttribL1dv(GLuint index,const GLdouble* v){this->_getTable()->glVertexAttribL1dv(index,v);}
inline void glVertexAttribL1i64NV(GLuint index,GLint64EXT x){this->_getTable()->glVertexAttribL1i64NV(index,x);}
inline void glVertexAttribL1i64vNV(GLuint index,const GLint64EXT* v){this->_getTable()->glVertexAttribL1i64vNV(index,v);}
inline void glVertexAttribL1ui64ARB(GLuint index,GLuint64EXT x){this->_getTable()->glVertexAttribL1ui64ARB(index,x);}
inline void glVertexAttribL1ui64NV(GLuint index,GLuint64EXT x){this->_getTable()->glVertexAttribL1ui64NV(index,x);}
inline void glVertexAttribL1ui64vARB(GLuint index,const GLuint64EXT* v){this->_getTable()->glVertexAttribL1ui64vARB(index,v);}
inline void glVertexAttribL1ui64vNV(GLuint index,const GLuint64EXT* v){this->_getTable()->glVertexAttribL1ui64vNV(index,v);}
inline void glVertexAttribL2dEXT(GLuint index,GLdouble x,GLdouble y){this->_getTable()->glVertexAttribL2dEXT(index,x,y);}
inline void glVertexAttribL2d(GLuint index,GLdouble x,GLdouble y){this->_getTable()->glVertexAttribL2d(index,x,y);}
inline void glVertexAttribL2dvEXT(GLuint index,const GLdouble* v){this->_getTable()->glVertexAttribL2dvEXT(index,v);}
inline void glVertexAttribL2dv(GLuint index,const GLdouble* v){this->_getTable()->glVertexAttribL2dv(index,v);}
inline void glVertexAttribL2i64NV(GLuint index,GLint64EXT x,GLint64EXT y){this->_getTable()->glVertexAttribL2i64NV(index,x,y);}
inline void glVertexAttribL2i64vNV(GLuint index,const GLint64EXT* v){this->_getTable()->glVertexAttribL2i64vNV(index,v);}
inline void glVertexAttribL2ui64NV(GLuint index,GLuint64EXT x,GLuint64EXT y){this->_getTable()->glVertexAttribL2ui64NV(index,x,y);}
inline void glVertexAttribL2ui64vNV(GLuint index,const GLuint64EXT* v){this->_getTable()->glVertexAttribL2ui64vNV(index,v);}
inline void glVertexAttribL3dEXT(GLuint index,GLdouble x,GLdouble y,GLdouble z){this->_getTable()->glVertexAttribL3dEXT(index,x,y,z);}
inline void glVertexAttribL3d(GLuint index,GLdouble x,GLdouble y,GLdouble z){this->_getTable()->glVertexAttribL3d(index,x,y,z);}
inline void glVertexAttribL3dvEXT(GLuint index,const GLdouble* v){this->_getTable()->glVertexAttribL3dvEXT(index,v);}
inline void glVertexAttribL3dv(GLuint index,const GLdouble* v){this->_getTable()->glVertexAttribL3dv(index,v);}
inline void glVertexAttribL3i64NV(GLuint index,GLint64EXT x,GLint64EXT y,GLint64EXT z){this->_getTable()->glVertexAttribL3i64NV(index,x,y,z);}
inline void glVertexAttribL3i64vNV(GLuint index,const GLint64EXT* v){this->_getTable()->glVertexAttribL3i64vNV(index,v);}
inline void glVertexAttribL3ui64NV(GLuint index,GLuint64EXT x,GLuint64EXT y,GLuint64EXT z){this->_getTable()->glVertexAttribL3ui64NV(index,x,y,z);}
inline void glVertexAttribL3ui64vNV(GLuint index,const GLuint64EXT* v){this->_getTable()->glVertexAttribL3ui64vNV(index,v);}
inline void glVertexAttribL4dEXT(GLuint index,GLdouble x,GLdouble y,GLdouble z,GLdouble w){this->_getTable()->glVertexAttribL4dEXT(index,x,y,z,w);}
inline void glVertexAttribL4d(GLuint index,GLdouble x,GLdouble y,GLdouble z,GLdouble w){this->_getTable()->glVertexAttribL4d(index,x,y,z,w);}
inline void glVertexAttribL4dvEXT(GLuint index,const GLdouble* v){this->_getTable()->glVertexAttribL4dvEXT(index,v);}
inline void glVertexAttribL4dv(GLuint index,const GLdouble* v){this->_getTable()->glVertexAttribL4dv(index,v);}
inline void glVertexAttribL4i64NV(GLuint index,GLint64EXT x,GLint64EXT y,GLint64EXT z,GLint64EXT w){this->_getTable()->glVertexAttribL4i64NV(index,x,y,z,w);}
inline void glVertexAttribL4i64vNV(GLuint index,const GLint64EXT* v){this->_getTable()->glVertexAttribL4i64vNV(index,v);}
inline void glVertexAttribL4ui64NV(GLuint index,GLuint64EXT x,GLuint64EXT y,GLuint64EXT z,GLuint64EXT w){this->_getTable()->glVertexAttribL4ui64NV(index,x,y,z,w);}
inline void glVertexAttribL4ui64vNV(GLuint index,const GLuint64EXT* v){this->_getTable()->glVertexAttribL4ui64vNV(index,v);}
inline void glVertexAttribLFormat(GLuint attribindex,GLint size,GLenum type,GLuint relativeoffset){this->_getTable()->glVertexAttribLFormat(attribindex,size,type,relativeoffset);}
inline void glVertexAttribLFormatNV(GLuint index,GLint size,GLenum type,GLsizei stride){this->_getTable()->glVertexAttribLFormatNV(index,size,type,stride);}
inline void glVertexAttribLPointerEXT(GLuint index,GLint size,GLenum type,GLsizei stride,const void* pointer){this->_getTable()->glVertexAttribLPointerEXT(index,size,type,stride,pointer);}
inline void glVertexAttribLPointer(GLuint index,GLint size,GLenum type,GLsizei stride,const void* pointer){this->_getTable()->glVertexAttribLPointer(index,size,type,stride,pointer);}
inline void glVertexAttribP1ui(GLuint index,GLenum type,GLboolean normalized,GLuint value){this->_getTable()->glVertexAttribP1ui(index,type,normalized,value);}
inline void glVertexAttribP1uiv(GLuint index,GLenum type,GLboolean normalized,const GLuint* value){this->_getTable()->glVertexAttribP1uiv(index,type,normalized,value);}
inline void glVertexAttribP2ui(GLuint index,GLenum type,GLboolean normalized,GLuint value){this->_getTable()->glVertexAttribP2ui(index,type,normalized,value);}
inline void glVertexAttribP2uiv(GLuint index,GLenum type,GLboolean normalized,const GLuint* value){this->_getTable()->glVertexAttribP2uiv(index,type,normalized,value);}
inline void glVertexAttribP3ui(GLuint index,GLenum type,GLboolean normalized,GLuint value){this->_getTable()->glVertexAttribP3ui(index,type,normalized,value);}
inline void glVertexAttribP3uiv(GLuint index,GLenum type,GLboolean normalized,const GLuint* value){this->_getTable()->glVertexAttribP3uiv(index,type,normalized,value);}
inline void glVertexAttribP4ui(GLuint index,GLenum type,GLboolean normalized,GLuint value){this->_getTable()->glVertexAttribP4ui(index,type,normalized,value);}
inline void glVertexAttribP4uiv(GLuint index,GLenum type,GLboolean normalized,const GLuint* value){this->_getTable()->glVertexAttribP4uiv(index,type,normalized,value);}
inline void glVertexAttribParameteriAMD(GLuint index,GLenum pname,GLint param){this->_getTable()->glVertexAttribParameteriAMD(index,pname,param);}
inline void glVertexAttribPointerARB(GLuint index,GLint size,GLenum type,GLboolean normalized,GLsizei stride,const void* pointer){this->_getTable()->glVertexAttribPointerARB(index,size,type,normalized,stride,pointer);}
inline void glVertexAttribPointer(GLuint index,GLint size,GLenum type,GLboolean normalized,GLsizei stride,const void* pointer){this->_getTable()->glVertexAttribPointer(index,size,type,normalized,stride,pointer);}
inline void glVertexAttribPointerNV(GLuint index,GLint fsize,GLenum type,GLsizei stride,const void* pointer){this->_getTable()->glVertexAttribPointerNV(index,fsize,type,stride,pointer);}
inline void glVertexAttribs1dvNV(GLuint index,GLsizei count,const GLdouble* v){this->_getTable()->glVertexAttribs1dvNV(index,count,v);}
inline void glVertexAttribs1fvNV(GLuint index,GLsizei count,const GLfloat* v){this->_getTable()->glVertexAttribs1fvNV(index,count,v);}
inline void glVertexAttribs1hvNV(GLuint index,GLsizei n,const GLhalfNV* v){this->_getTable()->glVertexAttribs1hvNV(index,n,v);}
inline void glVertexAttribs1svNV(GLuint index,GLsizei count,const GLshort* v){this->_getTable()->glVertexAttribs1svNV(index,count,v);}
inline void glVertexAttribs2dvNV(GLuint index,GLsizei count,const GLdouble* v){this->_getTable()->glVertexAttribs2dvNV(index,count,v);}
inline void glVertexAttribs2fvNV(GLuint index,GLsizei count,const GLfloat* v){this->_getTable()->glVertexAttribs2fvNV(index,count,v);}
inline void glVertexAttribs2hvNV(GLuint index,GLsizei n,const GLhalfNV* v){this->_getTable()->glVertexAttribs2hvNV(index,n,v);}
inline void glVertexAttribs2svNV(GLuint index,GLsizei count,const GLshort* v){this->_getTable()->glVertexAttribs2svNV(index,count,v);}
inline void glVertexAttribs3dvNV(GLuint index,GLsizei count,const GLdouble* v){this->_getTable()->glVertexAttribs3dvNV(index,count,v);}
inline void glVertexAttribs3fvNV(GLuint index,GLsizei count,const GLfloat* v){this->_getTable()->glVertexAttribs3fvNV(index,count,v);}
inline void glVertexAttribs3hvNV(GLuint index,GLsizei n,const GLhalfNV* v){this->_getTable()->glVertexAttribs3hvNV(index,n,v);}
inline void glVertexAttribs3svNV(GLuint index,GLsizei count,const GLshort* v){this->_getTable()->glVertexAttribs3svNV(index,count,v);}
inline void glVertexAttribs4dvNV(GLuint index,GLsizei count,const GLdouble* v){this->_getTable()->glVertexAttribs4dvNV(index,count,v);}
inline void glVertexAttribs4fvNV(GLuint index,GLsizei count,const GLfloat* v){this->_getTable()->glVertexAttribs4fvNV(index,count,v);}
inline void glVertexAttribs4hvNV(GLuint index,GLsizei n,const GLhalfNV* v){this->_getTable()->glVertexAttribs4hvNV(index,n,v);}
inline void glVertexAttribs4svNV(GLuint index,GLsizei count,const GLshort* v){this->_getTable()->glVertexAttribs4svNV(index,count,v);}
inline void glVertexAttribs4ubvNV(GLuint index,GLsizei count,const GLubyte* v){this->_getTable()->glVertexAttribs4ubvNV(index,count,v);}
inline void glVertexBindingDivisor(GLuint bindingindex,GLuint divisor){this->_getTable()->glVertexBindingDivisor(bindingindex,divisor);}
inline void glVertexBlendARB(GLint count){this->_getTable()->glVertexBlendARB(count);}
inline void glVertexBlendEnvfATI(GLenum pname,GLfloat param){this->_getTable()->glVertexBlendEnvfATI(pname,param);}
inline void glVertexBlendEnviATI(GLenum pname,GLint param){this->_getTable()->glVertexBlendEnviATI(pname,param);}
inline void glVertexFormatNV(GLint size,GLenum type,GLsizei stride){this->_getTable()->glVertexFormatNV(size,type,stride);}
inline void glVertexP2ui(GLenum type,GLuint value){this->_getTable()->glVertexP2ui(type,value);}
inline void glVertexP2uiv(GLenum type,const GLuint* value){this->_getTable()->glVertexP2uiv(type,value);}
inline void glVertexP3ui(GLenum type,GLuint value){this->_getTable()->glVertexP3ui(type,value);}
inline void glVertexP3uiv(GLenum type,const GLuint* value){this->_getTable()->glVertexP3uiv(type,value);}
inline void glVertexP4ui(GLenum type,GLuint value){this->_getTable()->glVertexP4ui(type,value);}
inline void glVertexP4uiv(GLenum type,const GLuint* value){this->_getTable()->glVertexP4uiv(type,value);}
inline void glVertexPointerEXT(GLint size,GLenum type,GLsizei stride,GLsizei count,const void* pointer){this->_getTable()->glVertexPointerEXT(size,type,stride,count,pointer);}
inline void glVertexPointer(GLint size,GLenum type,GLsizei stride,const GLvoid* ptr){this->_getTable()->glVertexPointer(size,type,stride,ptr);}
inline void glVertexPointerListIBM(GLint size,GLenum type,GLint stride,const void** pointer,GLint ptrstride){this->_getTable()->glVertexPointerListIBM(size,type,stride,pointer,ptrstride);}
inline void glVertexPointervINTEL(GLint size,GLenum type,const void** pointer){this->_getTable()->glVertexPointervINTEL(size,type,pointer);}
inline void glVertexStream1dATI(GLenum stream,GLdouble x){this->_getTable()->glVertexStream1dATI(stream,x);}
inline void glVertexStream1dvATI(GLenum stream,const GLdouble* coords){this->_getTable()->glVertexStream1dvATI(stream,coords);}
inline void glVertexStream1fATI(GLenum stream,GLfloat x){this->_getTable()->glVertexStream1fATI(stream,x);}
inline void glVertexStream1fvATI(GLenum stream,const GLfloat* coords){this->_getTable()->glVertexStream1fvATI(stream,coords);}
inline void glVertexStream1iATI(GLenum stream,GLint x){this->_getTable()->glVertexStream1iATI(stream,x);}
inline void glVertexStream1ivATI(GLenum stream,const GLint* coords){this->_getTable()->glVertexStream1ivATI(stream,coords);}
inline void glVertexStream1sATI(GLenum stream,GLshort x){this->_getTable()->glVertexStream1sATI(stream,x);}
inline void glVertexStream1svATI(GLenum stream,const GLshort* coords){this->_getTable()->glVertexStream1svATI(stream,coords);}
inline void glVertexStream2dATI(GLenum stream,GLdouble x,GLdouble y){this->_getTable()->glVertexStream2dATI(stream,x,y);}
inline void glVertexStream2dvATI(GLenum stream,const GLdouble* coords){this->_getTable()->glVertexStream2dvATI(stream,coords);}
inline void glVertexStream2fATI(GLenum stream,GLfloat x,GLfloat y){this->_getTable()->glVertexStream2fATI(stream,x,y);}
inline void glVertexStream2fvATI(GLenum stream,const GLfloat* coords){this->_getTable()->glVertexStream2fvATI(stream,coords);}
inline void glVertexStream2iATI(GLenum stream,GLint x,GLint y){this->_getTable()->glVertexStream2iATI(stream,x,y);}
inline void glVertexStream2ivATI(GLenum stream,const GLint* coords){this->_getTable()->glVertexStream2ivATI(stream,coords);}
inline void glVertexStream2sATI(GLenum stream,GLshort x,GLshort y){this->_getTable()->glVertexStream2sATI(stream,x,y);}
inline void glVertexStream2svATI(GLenum stream,const GLshort* coords){this->_getTable()->glVertexStream2svATI(stream,coords);}
inline void glVertexStream3dATI(GLenum stream,GLdouble x,GLdouble y,GLdouble z){this->_getTable()->glVertexStream3dATI(stream,x,y,z);}
inline void glVertexStream3dvATI(GLenum stream,const GLdouble* coords){this->_getTable()->glVertexStream3dvATI(stream,coords);}
inline void glVertexStream3fATI(GLenum stream,GLfloat x,GLfloat y,GLfloat z){this->_getTable()->glVertexStream3fATI(stream,x,y,z);}
inline void glVertexStream3fvATI(GLenum stream,const GLfloat* coords){this->_getTable()->glVertexStream3fvATI(stream,coords);}
inline void glVertexStream3iATI(GLenum stream,GLint x,GLint y,GLint z){this->_getTable()->glVertexStream3iATI(stream,x,y,z);}
inline void glVertexStream3ivATI(GLenum stream,const GLint* coords){this->_getTable()->glVertexStream3ivATI(stream,coords);}
inline void glVertexStream3sATI(GLenum stream,GLshort x,GLshort y,GLshort z){this->_getTable()->glVertexStream3sATI(stream,x,y,z);}
inline void glVertexStream3svATI(GLenum stream,const GLshort* coords){this->_getTable()->glVertexStream3svATI(stream,coords);}
inline void glVertexStream4dATI(GLenum stream,GLdouble x,GLdouble y,GLdouble z,GLdouble w){this->_getTable()->glVertexStream4dATI(stream,x,y,z,w);}
inline void glVertexStream4dvATI(GLenum stream,const GLdouble* coords){this->_getTable()->glVertexStream4dvATI(stream,coords);}
inline void glVertexStream4fATI(GLenum stream,GLfloat x,GLfloat y,GLfloat z,GLfloat w){this->_getTable()->glVertexStream4fATI(stream,x,y,z,w);}
inline void glVertexStream4fvATI(GLenum stream,const GLfloat* coords){this->_getTable()->glVertexStream4fvATI(stream,coords);}
inline void glVertexStream4iATI(GLenum stream,GLint x,GLint y,GLint z,GLint w){this->_getTable()->glVertexStream4iATI(stream,x,y,z,w);}
inline void glVertexStream4ivATI(GLenum stream,const GLint* coords){this->_getTable()->glVertexStream4ivATI(stream,coords);}
inline void glVertexStream4sATI(GLenum stream,GLshort x,GLshort y,GLshort z,GLshort w){this->_getTable()->glVertexStream4sATI(stream,x,y,z,w);}
inline void glVertexStream4svATI(GLenum stream,const GLshort* coords){this->_getTable()->glVertexStream4svATI(stream,coords);}
inline void glVertexWeightfEXT(GLfloat weight){this->_getTable()->glVertexWeightfEXT(weight);}
inline void glVertexWeightfvEXT(const GLfloat* weight){this->_getTable()->glVertexWeightfvEXT(weight);}
inline void glVertexWeighthNV(GLhalfNV weight){this->_getTable()->glVertexWeighthNV(weight);}
inline void glVertexWeighthvNV(const GLhalfNV* weight){this->_getTable()->glVertexWeighthvNV(weight);}
inline void glVertexWeightPointerEXT(GLint size,GLenum type,GLsizei stride,const void* pointer){this->_getTable()->glVertexWeightPointerEXT(size,type,stride,pointer);}
inline void glVideoCaptureStreamParameterdvNV(GLuint video_capture_slot,GLuint stream,GLenum pname,const GLdouble* params){this->_getTable()->glVideoCaptureStreamParameterdvNV(video_capture_slot,stream,pname,params);}
inline void glVideoCaptureStreamParameterfvNV(GLuint video_capture_slot,GLuint stream,GLenum pname,const GLfloat* params){this->_getTable()->glVideoCaptureStreamParameterfvNV(video_capture_slot,stream,pname,params);}
inline void glVideoCaptureStreamParameterivNV(GLuint video_capture_slot,GLuint stream,GLenum pname,const GLint* params){this->_getTable()->glVideoCaptureStreamParameterivNV(video_capture_slot,stream,pname,params);}
inline void glViewportArrayv(GLuint first,GLsizei count,const GLfloat* v){this->_getTable()->glViewportArrayv(first,count,v);}
inline void glViewport(GLint x,GLint y,GLsizei width,GLsizei height){this->_getTable()->glViewport(x,y,width,height);}
inline void glViewportIndexedf(GLuint index,GLfloat x,GLfloat y,GLfloat w,GLfloat h){this->_getTable()->glViewportIndexedf(index,x,y,w,h);}
inline void glViewportIndexedfv(GLuint index,const GLfloat* v){this->_getTable()->glViewportIndexedfv(index,v);}
inline void glViewportSwizzleNV(GLuint index,GLenum swizzlex,GLenum swizzley,GLenum swizzlez,GLenum swizzlew){this->_getTable()->glViewportSwizzleNV(index,swizzlex,swizzley,swizzlez,swizzlew);}
inline void glWaitSync(GLsync sync,GLbitfield flags,GLuint64 timeout){this->_getTable()->glWaitSync(sync,flags,timeout);}
inline void glWeightbvARB(GLint size,const GLbyte* weights){this->_getTable()->glWeightbvARB(size,weights);}
inline void glWeightdvARB(GLint size,const GLdouble* weights){this->_getTable()->glWeightdvARB(size,weights);}
inline void glWeightfvARB(GLint size,const GLfloat* weights){this->_getTable()->glWeightfvARB(size,weights);}
inline void glWeightivARB(GLint size,const GLint* weights){this->_getTable()->glWeightivARB(size,weights);}
inline void glWeightPathsNV(GLuint resultPath,GLsizei numPaths,const GLuint* paths,const GLfloat* weights){this->_getTable()->glWeightPathsNV(resultPath,numPaths,paths,weights);}
inline void glWeightPointerARB(GLint size,GLenum type,GLsizei stride,const void* pointer){this->_getTable()->glWeightPointerARB(size,type,stride,pointer);}
inline void glWeightsvARB(GLint size,const GLshort* weights){this->_getTable()->glWeightsvARB(size,weights);}
inline void glWeightubvARB(GLint size,const GLubyte* weights){this->_getTable()->glWeightubvARB(size,weights);}
inline void glWeightuivARB(GLint size,const GLuint* weights){this->_getTable()->glWeightuivARB(size,weights);}
inline void glWeightusvARB(GLint size,const GLushort* weights){this->_getTable()->glWeightusvARB(size,weights);}
inline void glWindowPos2dARB(GLdouble x,GLdouble y){this->_getTable()->glWindowPos2dARB(x,y);}
inline void glWindowPos2d(GLdouble x,GLdouble y){this->_getTable()->glWindowPos2d(x,y);}
inline void glWindowPos2dMESA(GLdouble x,GLdouble y){this->_getTable()->glWindowPos2dMESA(x,y);}
inline void glWindowPos2dvARB(const GLdouble* v){this->_getTable()->glWindowPos2dvARB(v);}
inline void glWindowPos2dv(const GLdouble* v){this->_getTable()->glWindowPos2dv(v);}
inline void glWindowPos2dvMESA(const GLdouble* v){this->_getTable()->glWindowPos2dvMESA(v);}
inline void glWindowPos2fARB(GLfloat x,GLfloat y){this->_getTable()->glWindowPos2fARB(x,y);}
inline void glWindowPos2f(GLfloat x,GLfloat y){this->_getTable()->glWindowPos2f(x,y);}
inline void glWindowPos2fMESA(GLfloat x,GLfloat y){this->_getTable()->glWindowPos2fMESA(x,y);}
inline void glWindowPos2fvARB(const GLfloat* v){this->_getTable()->glWindowPos2fvARB(v);}
inline void glWindowPos2fv(const GLfloat* v){this->_getTable()->glWindowPos2fv(v);}
inline void glWindowPos2fvMESA(const GLfloat* v){this->_getTable()->glWindowPos2fvMESA(v);}
inline void glWindowPos2iARB(GLint x,GLint y){this->_getTable()->glWindowPos2iARB(x,y);}
inline void glWindowPos2i(GLint x,GLint y){this->_getTable()->glWindowPos2i(x,y);}
inline void glWindowPos2iMESA(GLint x,GLint y){this->_getTable()->glWindowPos2iMESA(x,y);}
inline void glWindowPos2ivARB(const GLint* v){this->_getTable()->glWindowPos2ivARB(v);}
inline void glWindowPos2iv(const GLint* v){this->_getTable()->glWindowPos2iv(v);}
inline void glWindowPos2ivMESA(const GLint* v){this->_getTable()->glWindowPos2ivMESA(v);}
inline void glWindowPos2sARB(GLshort x,GLshort y){this->_getTable()->glWindowPos2sARB(x,y);}
inline void glWindowPos2s(GLshort x,GLshort y){this->_getTable()->glWindowPos2s(x,y);}
inline void glWindowPos2sMESA(GLshort x,GLshort y){this->_getTable()->glWindowPos2sMESA(x,y);}
inline void glWindowPos2svARB(const GLshort* v){this->_getTable()->glWindowPos2svARB(v);}
inline void glWindowPos2sv(const GLshort* v){this->_getTable()->glWindowPos2sv(v);}
inline void glWindowPos2svMESA(const GLshort* v){this->_getTable()->glWindowPos2svMESA(v);}
inline void glWindowPos3dARB(GLdouble x,GLdouble y,GLdouble z){this->_getTable()->glWindowPos3dARB(x,y,z);}
inline void glWindowPos3d(GLdouble x,GLdouble y,GLdouble z){this->_getTable()->glWindowPos3d(x,y,z);}
inline void glWindowPos3dMESA(GLdouble x,GLdouble y,GLdouble z){this->_getTable()->glWindowPos3dMESA(x,y,z);}
inline void glWindowPos3dvARB(const GLdouble* v){this->_getTable()->glWindowPos3dvARB(v);}
inline void glWindowPos3dv(const GLdouble* v){this->_getTable()->glWindowPos3dv(v);}
inline void glWindowPos3dvMESA(const GLdouble* v){this->_getTable()->glWindowPos3dvMESA(v);}
inline void glWindowPos3fARB(GLfloat x,GLfloat y,GLfloat z){this->_getTable()->glWindowPos3fARB(x,y,z);}
inline void glWindowPos3f(GLfloat x,GLfloat y,GLfloat z){this->_getTable()->glWindowPos3f(x,y,z);}
inline void glWindowPos3fMESA(GLfloat x,GLfloat y,GLfloat z){this->_getTable()->glWindowPos3fMESA(x,y,z);}
inline void glWindowPos3fvARB(const GLfloat* v){this->_getTable()->glWindowPos3fvARB(v);}
inline void glWindowPos3fv(const GLfloat* v){this->_getTable()->glWindowPos3fv(v);}
inline void glWindowPos3fvMESA(const GLfloat* v){this->_getTable()->glWindowPos3fvMESA(v);}
inline void glWindowPos3iARB(GLint x,GLint y,GLint z){this->_getTable()->glWindowPos3iARB(x,y,z);}
inline void glWindowPos3i(GLint x,GLint y,GLint z){this->_getTable()->glWindowPos3i(x,y,z);}
inline void glWindowPos3iMESA(GLint x,GLint y,GLint z){this->_getTable()->glWindowPos3iMESA(x,y,z);}
inline void glWindowPos3ivARB(const GLint* v){this->_getTable()->glWindowPos3ivARB(v);}
inline void glWindowPos3iv(const GLint* v){this->_getTable()->glWindowPos3iv(v);}
inline void glWindowPos3ivMESA(const GLint* v){this->_getTable()->glWindowPos3ivMESA(v);}
inline void glWindowPos3sARB(GLshort x,GLshort y,GLshort z){this->_getTable()->glWindowPos3sARB(x,y,z);}
inline void glWindowPos3s(GLshort x,GLshort y,GLshort z){this->_getTable()->glWindowPos3s(x,y,z);}
inline void glWindowPos3sMESA(GLshort x,GLshort y,GLshort z){this->_getTable()->glWindowPos3sMESA(x,y,z);}
inline void glWindowPos3svARB(const GLshort* v){this->_getTable()->glWindowPos3svARB(v);}
inline void glWindowPos3sv(const GLshort* v){this->_getTable()->glWindowPos3sv(v);}
inline void glWindowPos3svMESA(const GLshort* v){this->_getTable()->glWindowPos3svMESA(v);}
inline void glWindowPos4dMESA(GLdouble x,GLdouble y,GLdouble z,GLdouble w){this->_getTable()->glWindowPos4dMESA(x,y,z,w);}
inline void glWindowPos4dvMESA(const GLdouble* v){this->_getTable()->glWindowPos4dvMESA(v);}
inline void glWindowPos4fMESA(GLfloat x,GLfloat y,GLfloat z,GLfloat w){this->_getTable()->glWindowPos4fMESA(x,y,z,w);}
inline void glWindowPos4fvMESA(const GLfloat* v){this->_getTable()->glWindowPos4fvMESA(v);}
inline void glWindowPos4iMESA(GLint x,GLint y,GLint z,GLint w){this->_getTable()->glWindowPos4iMESA(x,y,z,w);}
inline void glWindowPos4ivMESA(const GLint* v){this->_getTable()->glWindowPos4ivMESA(v);}
inline void glWindowPos4sMESA(GLshort x,GLshort y,GLshort z,GLshort w){this->_getTable()->glWindowPos4sMESA(x,y,z,w);}
inline void glWindowPos4svMESA(const GLshort* v){this->_getTable()->glWindowPos4svMESA(v);}
inline void glWriteMaskEXT(GLuint res,GLuint in,GLenum outX,GLenum outY,GLenum outZ,GLenum outW){this->_getTable()->glWriteMaskEXT(res,in,outX,outY,outZ,outW);}
