#pragma once

GEGL_EXPORT void printMissingFunctionError(char const*fce){std::cerr<<"Function "<<fce<<" is nullptr"<<std::endl;}
GEGL_EXPORT const GLubyte* gegl_TrapglGetString(GLenum){printMissingFunctionError("glGetString");std::exit(1);return (const GLubyte*)0;}
GEGL_EXPORT const GLubyte* gegl_TrapglGetStringi(GLenum,GLuint){printMissingFunctionError("glGetStringi");std::exit(1);return (const GLubyte*)0;}
GEGL_EXPORT GLbitfield gegl_TrapglQueryMatrixxOES(GLfixed*,GLint*){printMissingFunctionError("glQueryMatrixxOES");std::exit(1);return (GLbitfield)0;}
GEGL_EXPORT GLboolean gegl_TrapglAreProgramsResidentNV(GLsizei,const GLuint*,GLboolean*){printMissingFunctionError("glAreProgramsResidentNV");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglAreTexturesResidentEXT(GLsizei,const GLuint*,GLboolean*){printMissingFunctionError("glAreTexturesResidentEXT");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglAreTexturesResident(GLsizei,const GLuint*,GLboolean*){printMissingFunctionError("glAreTexturesResident");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglIsAsyncMarkerSGIX(GLuint){printMissingFunctionError("glIsAsyncMarkerSGIX");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglIsBufferARB(GLuint){printMissingFunctionError("glIsBufferARB");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglIsBuffer(GLuint){printMissingFunctionError("glIsBuffer");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglIsBufferResidentNV(GLenum){printMissingFunctionError("glIsBufferResidentNV");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglIsCommandListNV(GLuint){printMissingFunctionError("glIsCommandListNV");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglIsEnabled(GLenum){printMissingFunctionError("glIsEnabled");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglIsEnabledi(GLenum,GLuint){printMissingFunctionError("glIsEnabledi");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglIsEnabledIndexedEXT(GLenum,GLuint){printMissingFunctionError("glIsEnabledIndexedEXT");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglIsFenceAPPLE(GLuint){printMissingFunctionError("glIsFenceAPPLE");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglIsFenceNV(GLuint){printMissingFunctionError("glIsFenceNV");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglIsFramebufferEXT(GLuint){printMissingFunctionError("glIsFramebufferEXT");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglIsFramebuffer(GLuint){printMissingFunctionError("glIsFramebuffer");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglIsImageHandleResidentARB(GLuint64){printMissingFunctionError("glIsImageHandleResidentARB");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglIsImageHandleResidentNV(GLuint64){printMissingFunctionError("glIsImageHandleResidentNV");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglIsList(GLuint){printMissingFunctionError("glIsList");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglIsNameAMD(GLenum,GLuint){printMissingFunctionError("glIsNameAMD");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglIsNamedBufferResidentNV(GLuint){printMissingFunctionError("glIsNamedBufferResidentNV");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglIsNamedStringARB(GLint,const GLchar*){printMissingFunctionError("glIsNamedStringARB");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglIsObjectBufferATI(GLuint){printMissingFunctionError("glIsObjectBufferATI");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglIsOcclusionQueryNV(GLuint){printMissingFunctionError("glIsOcclusionQueryNV");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglIsPathNV(GLuint){printMissingFunctionError("glIsPathNV");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglIsPointInFillPathNV(GLuint,GLuint,GLfloat,GLfloat){printMissingFunctionError("glIsPointInFillPathNV");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglIsPointInStrokePathNV(GLuint,GLfloat,GLfloat){printMissingFunctionError("glIsPointInStrokePathNV");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglIsProgramARB(GLuint){printMissingFunctionError("glIsProgramARB");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglIsProgram(GLuint){printMissingFunctionError("glIsProgram");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglIsProgramNV(GLuint){printMissingFunctionError("glIsProgramNV");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglIsProgramPipeline(GLuint){printMissingFunctionError("glIsProgramPipeline");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglIsQueryARB(GLuint){printMissingFunctionError("glIsQueryARB");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglIsQuery(GLuint){printMissingFunctionError("glIsQuery");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglIsRenderbufferEXT(GLuint){printMissingFunctionError("glIsRenderbufferEXT");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglIsRenderbuffer(GLuint){printMissingFunctionError("glIsRenderbuffer");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglIsSampler(GLuint){printMissingFunctionError("glIsSampler");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglIsShader(GLuint){printMissingFunctionError("glIsShader");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglIsStateNV(GLuint){printMissingFunctionError("glIsStateNV");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglIsSync(GLsync){printMissingFunctionError("glIsSync");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglIsTextureEXT(GLuint){printMissingFunctionError("glIsTextureEXT");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglIsTexture(GLuint){printMissingFunctionError("glIsTexture");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglIsTextureHandleResidentARB(GLuint64){printMissingFunctionError("glIsTextureHandleResidentARB");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglIsTextureHandleResidentNV(GLuint64){printMissingFunctionError("glIsTextureHandleResidentNV");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglIsTransformFeedback(GLuint){printMissingFunctionError("glIsTransformFeedback");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglIsTransformFeedbackNV(GLuint){printMissingFunctionError("glIsTransformFeedbackNV");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglIsVariantEnabledEXT(GLuint,GLenum){printMissingFunctionError("glIsVariantEnabledEXT");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglIsVertexArrayAPPLE(GLuint){printMissingFunctionError("glIsVertexArrayAPPLE");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglIsVertexArray(GLuint){printMissingFunctionError("glIsVertexArray");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglIsVertexAttribEnabledAPPLE(GLuint,GLenum){printMissingFunctionError("glIsVertexAttribEnabledAPPLE");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglPointAlongPathNV(GLuint,GLsizei,GLsizei,GLfloat,GLfloat*,GLfloat*,GLfloat*,GLfloat*){printMissingFunctionError("glPointAlongPathNV");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglTestFenceAPPLE(GLuint){printMissingFunctionError("glTestFenceAPPLE");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglTestFenceNV(GLuint){printMissingFunctionError("glTestFenceNV");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglTestObjectAPPLE(GLenum,GLuint){printMissingFunctionError("glTestObjectAPPLE");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglUnmapBufferARB(GLenum){printMissingFunctionError("glUnmapBufferARB");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglUnmapBuffer(GLenum){printMissingFunctionError("glUnmapBuffer");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglUnmapNamedBufferEXT(GLuint){printMissingFunctionError("glUnmapNamedBufferEXT");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglUnmapNamedBuffer(GLuint){printMissingFunctionError("glUnmapNamedBuffer");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean gegl_TrapglVDPAUIsSurfaceNV(GLvdpauSurfaceNV){printMissingFunctionError("glVDPAUIsSurfaceNV");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLenum gegl_TrapglCheckFramebufferStatusEXT(GLenum){printMissingFunctionError("glCheckFramebufferStatusEXT");std::exit(1);return (GLenum)0;}
GEGL_EXPORT GLenum gegl_TrapglCheckFramebufferStatus(GLenum){printMissingFunctionError("glCheckFramebufferStatus");std::exit(1);return (GLenum)0;}
GEGL_EXPORT GLenum gegl_TrapglCheckNamedFramebufferStatusEXT(GLuint,GLenum){printMissingFunctionError("glCheckNamedFramebufferStatusEXT");std::exit(1);return (GLenum)0;}
GEGL_EXPORT GLenum gegl_TrapglCheckNamedFramebufferStatus(GLuint,GLenum){printMissingFunctionError("glCheckNamedFramebufferStatus");std::exit(1);return (GLenum)0;}
GEGL_EXPORT GLenum gegl_TrapglClientWaitSync(GLsync,GLbitfield,GLuint64){printMissingFunctionError("glClientWaitSync");std::exit(1);return (GLenum)0;}
GEGL_EXPORT GLenum gegl_TrapglGetError(){printMissingFunctionError("glGetError");std::exit(1);return (GLenum)0;}
GEGL_EXPORT GLenum gegl_TrapglGetGraphicsResetStatus(){printMissingFunctionError("glGetGraphicsResetStatus");std::exit(1);return (GLenum)0;}
GEGL_EXPORT GLenum gegl_TrapglGetGraphicsResetStatusARB(){printMissingFunctionError("glGetGraphicsResetStatusARB");std::exit(1);return (GLenum)0;}
GEGL_EXPORT GLenum gegl_TrapglObjectPurgeableAPPLE(GLenum,GLuint,GLenum){printMissingFunctionError("glObjectPurgeableAPPLE");std::exit(1);return (GLenum)0;}
GEGL_EXPORT GLenum gegl_TrapglObjectUnpurgeableAPPLE(GLenum,GLuint,GLenum){printMissingFunctionError("glObjectUnpurgeableAPPLE");std::exit(1);return (GLenum)0;}
GEGL_EXPORT GLenum gegl_TrapglPathGlyphIndexArrayNV(GLuint,GLenum,const void*,GLbitfield,GLuint,GLsizei,GLuint,GLfloat){printMissingFunctionError("glPathGlyphIndexArrayNV");std::exit(1);return (GLenum)0;}
GEGL_EXPORT GLenum gegl_TrapglPathGlyphIndexRangeNV(GLenum,const void*,GLbitfield,GLuint,GLfloat,GLuint){printMissingFunctionError("glPathGlyphIndexRangeNV");std::exit(1);return (GLenum)0;}
GEGL_EXPORT GLenum gegl_TrapglPathMemoryGlyphIndexArrayNV(GLuint,GLenum,GLsizeiptr,const void*,GLsizei,GLuint,GLsizei,GLuint,GLfloat){printMissingFunctionError("glPathMemoryGlyphIndexArrayNV");std::exit(1);return (GLenum)0;}
GEGL_EXPORT GLenum gegl_TrapglVideoCaptureNV(GLuint,GLuint*,GLuint64EXT*){printMissingFunctionError("glVideoCaptureNV");std::exit(1);return (GLenum)0;}
GEGL_EXPORT GLfloat gegl_TrapglGetPathLengthNV(GLuint,GLsizei,GLsizei){printMissingFunctionError("glGetPathLengthNV");std::exit(1);return (GLfloat)0;}
GEGL_EXPORT GLhandleARB gegl_TrapglCreateProgramObjectARB(){printMissingFunctionError("glCreateProgramObjectARB");std::exit(1);return (GLhandleARB)0;}
GEGL_EXPORT GLhandleARB gegl_TrapglCreateShaderObjectARB(GLenum){printMissingFunctionError("glCreateShaderObjectARB");std::exit(1);return (GLhandleARB)0;}
GEGL_EXPORT GLhandleARB gegl_TrapglGetHandleARB(GLenum){printMissingFunctionError("glGetHandleARB");std::exit(1);return (GLhandleARB)0;}
GEGL_EXPORT GLint gegl_TrapglFinishAsyncSGIX(GLuint*){printMissingFunctionError("glFinishAsyncSGIX");std::exit(1);return (GLint)0;}
GEGL_EXPORT GLint gegl_TrapglGetAttribLocationARB(GLhandleARB,const GLcharARB*){printMissingFunctionError("glGetAttribLocationARB");std::exit(1);return (GLint)0;}
GEGL_EXPORT GLint gegl_TrapglGetAttribLocation(GLuint,const GLchar*){printMissingFunctionError("glGetAttribLocation");std::exit(1);return (GLint)0;}
GEGL_EXPORT GLint gegl_TrapglGetFragDataIndex(GLuint,const GLchar*){printMissingFunctionError("glGetFragDataIndex");std::exit(1);return (GLint)0;}
GEGL_EXPORT GLint gegl_TrapglGetFragDataLocationEXT(GLuint,const GLchar*){printMissingFunctionError("glGetFragDataLocationEXT");std::exit(1);return (GLint)0;}
GEGL_EXPORT GLint gegl_TrapglGetFragDataLocation(GLuint,const GLchar*){printMissingFunctionError("glGetFragDataLocation");std::exit(1);return (GLint)0;}
GEGL_EXPORT GLint gegl_TrapglGetInstrumentsSGIX(){printMissingFunctionError("glGetInstrumentsSGIX");std::exit(1);return (GLint)0;}
GEGL_EXPORT GLint gegl_TrapglGetProgramResourceLocation(GLuint,GLenum,const GLchar*){printMissingFunctionError("glGetProgramResourceLocation");std::exit(1);return (GLint)0;}
GEGL_EXPORT GLint gegl_TrapglGetProgramResourceLocationIndex(GLuint,GLenum,const GLchar*){printMissingFunctionError("glGetProgramResourceLocationIndex");std::exit(1);return (GLint)0;}
GEGL_EXPORT GLint gegl_TrapglGetSubroutineUniformLocation(GLuint,GLenum,const GLchar*){printMissingFunctionError("glGetSubroutineUniformLocation");std::exit(1);return (GLint)0;}
GEGL_EXPORT GLint gegl_TrapglGetUniformBufferSizeEXT(GLuint,GLint){printMissingFunctionError("glGetUniformBufferSizeEXT");std::exit(1);return (GLint)0;}
GEGL_EXPORT GLint gegl_TrapglGetUniformLocationARB(GLhandleARB,const GLcharARB*){printMissingFunctionError("glGetUniformLocationARB");std::exit(1);return (GLint)0;}
GEGL_EXPORT GLint gegl_TrapglGetUniformLocation(GLuint,const GLchar*){printMissingFunctionError("glGetUniformLocation");std::exit(1);return (GLint)0;}
GEGL_EXPORT GLint gegl_TrapglGetVaryingLocationNV(GLuint,const GLchar*){printMissingFunctionError("glGetVaryingLocationNV");std::exit(1);return (GLint)0;}
GEGL_EXPORT GLint gegl_TrapglPollAsyncSGIX(GLuint*){printMissingFunctionError("glPollAsyncSGIX");std::exit(1);return (GLint)0;}
GEGL_EXPORT GLint gegl_TrapglPollInstrumentsSGIX(GLint*){printMissingFunctionError("glPollInstrumentsSGIX");std::exit(1);return (GLint)0;}
GEGL_EXPORT GLint gegl_TrapglRenderMode(GLenum){printMissingFunctionError("glRenderMode");std::exit(1);return (GLint)0;}
GEGL_EXPORT GLintptr gegl_TrapglGetUniformOffsetEXT(GLuint,GLint){printMissingFunctionError("glGetUniformOffsetEXT");std::exit(1);return (GLintptr)0;}
GEGL_EXPORT GLsync gegl_TrapglCreateSyncFromCLeventARB(struct _cl_context*,struct _cl_event*,GLbitfield){printMissingFunctionError("glCreateSyncFromCLeventARB");std::exit(1);return (GLsync)0;}
GEGL_EXPORT GLsync gegl_TrapglFenceSync(GLenum,GLbitfield){printMissingFunctionError("glFenceSync");std::exit(1);return (GLsync)0;}
GEGL_EXPORT GLsync gegl_TrapglImportSyncEXT(GLenum,GLintptr,GLbitfield){printMissingFunctionError("glImportSyncEXT");std::exit(1);return (GLsync)0;}
GEGL_EXPORT GLuint64 gegl_TrapglGetImageHandleARB(GLuint,GLint,GLboolean,GLint,GLenum){printMissingFunctionError("glGetImageHandleARB");std::exit(1);return (GLuint64)0;}
GEGL_EXPORT GLuint64 gegl_TrapglGetImageHandleNV(GLuint,GLint,GLboolean,GLint,GLenum){printMissingFunctionError("glGetImageHandleNV");std::exit(1);return (GLuint64)0;}
GEGL_EXPORT GLuint64 gegl_TrapglGetTextureHandleARB(GLuint){printMissingFunctionError("glGetTextureHandleARB");std::exit(1);return (GLuint64)0;}
GEGL_EXPORT GLuint64 gegl_TrapglGetTextureHandleNV(GLuint){printMissingFunctionError("glGetTextureHandleNV");std::exit(1);return (GLuint64)0;}
GEGL_EXPORT GLuint64 gegl_TrapglGetTextureSamplerHandleARB(GLuint,GLuint){printMissingFunctionError("glGetTextureSamplerHandleARB");std::exit(1);return (GLuint64)0;}
GEGL_EXPORT GLuint64 gegl_TrapglGetTextureSamplerHandleNV(GLuint,GLuint){printMissingFunctionError("glGetTextureSamplerHandleNV");std::exit(1);return (GLuint64)0;}
GEGL_EXPORT GLuint gegl_TrapglBindLightParameterEXT(GLenum,GLenum){printMissingFunctionError("glBindLightParameterEXT");std::exit(1);return (GLuint)0;}
GEGL_EXPORT GLuint gegl_TrapglBindMaterialParameterEXT(GLenum,GLenum){printMissingFunctionError("glBindMaterialParameterEXT");std::exit(1);return (GLuint)0;}
GEGL_EXPORT GLuint gegl_TrapglBindParameterEXT(GLenum){printMissingFunctionError("glBindParameterEXT");std::exit(1);return (GLuint)0;}
GEGL_EXPORT GLuint gegl_TrapglBindTexGenParameterEXT(GLenum,GLenum,GLenum){printMissingFunctionError("glBindTexGenParameterEXT");std::exit(1);return (GLuint)0;}
GEGL_EXPORT GLuint gegl_TrapglBindTextureUnitParameterEXT(GLenum,GLenum){printMissingFunctionError("glBindTextureUnitParameterEXT");std::exit(1);return (GLuint)0;}
GEGL_EXPORT GLuint gegl_TrapglCreateProgram(){printMissingFunctionError("glCreateProgram");std::exit(1);return (GLuint)0;}
GEGL_EXPORT GLuint gegl_TrapglCreateShader(GLenum){printMissingFunctionError("glCreateShader");std::exit(1);return (GLuint)0;}
GEGL_EXPORT GLuint gegl_TrapglCreateShaderProgramEXT(GLenum,const GLchar*){printMissingFunctionError("glCreateShaderProgramEXT");std::exit(1);return (GLuint)0;}
GEGL_EXPORT GLuint gegl_TrapglCreateShaderProgramv(GLenum,GLsizei,const GLchar*const*){printMissingFunctionError("glCreateShaderProgramv");std::exit(1);return (GLuint)0;}
GEGL_EXPORT GLuint gegl_TrapglGenAsyncMarkersSGIX(GLsizei){printMissingFunctionError("glGenAsyncMarkersSGIX");std::exit(1);return (GLuint)0;}
GEGL_EXPORT GLuint gegl_TrapglGenFragmentShadersATI(GLuint){printMissingFunctionError("glGenFragmentShadersATI");std::exit(1);return (GLuint)0;}
GEGL_EXPORT GLuint gegl_TrapglGenLists(GLsizei){printMissingFunctionError("glGenLists");std::exit(1);return (GLuint)0;}
GEGL_EXPORT GLuint gegl_TrapglGenPathsNV(GLsizei){printMissingFunctionError("glGenPathsNV");std::exit(1);return (GLuint)0;}
GEGL_EXPORT GLuint gegl_TrapglGenSymbolsEXT(GLenum,GLenum,GLenum,GLuint){printMissingFunctionError("glGenSymbolsEXT");std::exit(1);return (GLuint)0;}
GEGL_EXPORT GLuint gegl_TrapglGenVertexShadersEXT(GLuint){printMissingFunctionError("glGenVertexShadersEXT");std::exit(1);return (GLuint)0;}
GEGL_EXPORT GLuint gegl_TrapglGetCommandHeaderNV(GLenum,GLuint){printMissingFunctionError("glGetCommandHeaderNV");std::exit(1);return (GLuint)0;}
GEGL_EXPORT GLuint gegl_TrapglGetDebugMessageLogAMD(GLuint,GLsizei,GLenum*,GLuint*,GLuint*,GLsizei*,GLchar*){printMissingFunctionError("glGetDebugMessageLogAMD");std::exit(1);return (GLuint)0;}
GEGL_EXPORT GLuint gegl_TrapglGetDebugMessageLogARB(GLuint,GLsizei,GLenum*,GLenum*,GLuint*,GLenum*,GLsizei*,GLchar*){printMissingFunctionError("glGetDebugMessageLogARB");std::exit(1);return (GLuint)0;}
GEGL_EXPORT GLuint gegl_TrapglGetDebugMessageLog(GLuint,GLsizei,GLenum*,GLenum*,GLuint*,GLenum*,GLsizei*,GLchar*){printMissingFunctionError("glGetDebugMessageLog");std::exit(1);return (GLuint)0;}
GEGL_EXPORT GLuint gegl_TrapglGetProgramResourceIndex(GLuint,GLenum,const GLchar*){printMissingFunctionError("glGetProgramResourceIndex");std::exit(1);return (GLuint)0;}
GEGL_EXPORT GLuint gegl_TrapglGetSubroutineIndex(GLuint,GLenum,const GLchar*){printMissingFunctionError("glGetSubroutineIndex");std::exit(1);return (GLuint)0;}
GEGL_EXPORT GLuint gegl_TrapglGetUniformBlockIndex(GLuint,const GLchar*){printMissingFunctionError("glGetUniformBlockIndex");std::exit(1);return (GLuint)0;}
GEGL_EXPORT GLuint gegl_TrapglNewObjectBufferATI(GLsizei,const void*,GLenum){printMissingFunctionError("glNewObjectBufferATI");std::exit(1);return (GLuint)0;}
GEGL_EXPORT GLushort gegl_TrapglGetStageIndexNV(GLenum){printMissingFunctionError("glGetStageIndexNV");std::exit(1);return (GLushort)0;}
GEGL_EXPORT GLvdpauSurfaceNV gegl_TrapglVDPAURegisterOutputSurfaceNV(const void*,GLenum,GLsizei,const GLuint*){printMissingFunctionError("glVDPAURegisterOutputSurfaceNV");std::exit(1);return (GLvdpauSurfaceNV)0;}
GEGL_EXPORT GLvdpauSurfaceNV gegl_TrapglVDPAURegisterVideoSurfaceNV(const void*,GLenum,GLsizei,const GLuint*){printMissingFunctionError("glVDPAURegisterVideoSurfaceNV");std::exit(1);return (GLvdpauSurfaceNV)0;}
GEGL_EXPORT void gegl_TrapglAccum(GLenum,GLfloat){printMissingFunctionError("glAccum");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglAccumxOES(GLenum,GLfixed){printMissingFunctionError("glAccumxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglActiveProgramEXT(GLuint){printMissingFunctionError("glActiveProgramEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglActiveShaderProgram(GLuint,GLuint){printMissingFunctionError("glActiveShaderProgram");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglActiveStencilFaceEXT(GLenum){printMissingFunctionError("glActiveStencilFaceEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglActiveTextureARB(GLenum){printMissingFunctionError("glActiveTextureARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglActiveTexture(GLenum){printMissingFunctionError("glActiveTexture");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglActiveVaryingNV(GLuint,const GLchar*){printMissingFunctionError("glActiveVaryingNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglAlphaFragmentOp1ATI(GLenum,GLuint,GLuint,GLuint,GLuint,GLuint){printMissingFunctionError("glAlphaFragmentOp1ATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglAlphaFragmentOp2ATI(GLenum,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint){printMissingFunctionError("glAlphaFragmentOp2ATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglAlphaFragmentOp3ATI(GLenum,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint){printMissingFunctionError("glAlphaFragmentOp3ATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglAlphaFunc(GLenum,GLclampf){printMissingFunctionError("glAlphaFunc");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglAlphaFuncxOES(GLenum,GLfixed){printMissingFunctionError("glAlphaFuncxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglApplyFramebufferAttachmentCMAAINTEL(){printMissingFunctionError("glApplyFramebufferAttachmentCMAAINTEL");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglApplyTextureEXT(GLenum){printMissingFunctionError("glApplyTextureEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglArrayElementEXT(GLint){printMissingFunctionError("glArrayElementEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglArrayElement(GLint){printMissingFunctionError("glArrayElement");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglArrayObjectATI(GLenum,GLint,GLenum,GLsizei,GLuint,GLuint){printMissingFunctionError("glArrayObjectATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglAsyncMarkerSGIX(GLuint){printMissingFunctionError("glAsyncMarkerSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglAttachObjectARB(GLhandleARB,GLhandleARB){printMissingFunctionError("glAttachObjectARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglAttachShader(GLuint,GLuint){printMissingFunctionError("glAttachShader");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBeginConditionalRender(GLuint,GLenum){printMissingFunctionError("glBeginConditionalRender");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBeginConditionalRenderNV(GLuint,GLenum){printMissingFunctionError("glBeginConditionalRenderNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBeginConditionalRenderNVX(GLuint){printMissingFunctionError("glBeginConditionalRenderNVX");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBeginFragmentShaderATI(){printMissingFunctionError("glBeginFragmentShaderATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBegin(GLenum){printMissingFunctionError("glBegin");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBeginOcclusionQueryNV(GLuint){printMissingFunctionError("glBeginOcclusionQueryNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBeginPerfMonitorAMD(GLuint){printMissingFunctionError("glBeginPerfMonitorAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBeginPerfQueryINTEL(GLuint){printMissingFunctionError("glBeginPerfQueryINTEL");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBeginQueryARB(GLenum,GLuint){printMissingFunctionError("glBeginQueryARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBeginQuery(GLenum,GLuint){printMissingFunctionError("glBeginQuery");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBeginQueryIndexed(GLenum,GLuint,GLuint){printMissingFunctionError("glBeginQueryIndexed");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBeginTransformFeedbackEXT(GLenum){printMissingFunctionError("glBeginTransformFeedbackEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBeginTransformFeedback(GLenum){printMissingFunctionError("glBeginTransformFeedback");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBeginTransformFeedbackNV(GLenum){printMissingFunctionError("glBeginTransformFeedbackNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBeginVertexShaderEXT(){printMissingFunctionError("glBeginVertexShaderEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBeginVideoCaptureNV(GLuint){printMissingFunctionError("glBeginVideoCaptureNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBindAttribLocationARB(GLhandleARB,GLuint,const GLcharARB*){printMissingFunctionError("glBindAttribLocationARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBindAttribLocation(GLuint,GLuint,const GLchar*){printMissingFunctionError("glBindAttribLocation");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBindBufferARB(GLenum,GLuint){printMissingFunctionError("glBindBufferARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBindBufferBaseEXT(GLenum,GLuint,GLuint){printMissingFunctionError("glBindBufferBaseEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBindBufferBase(GLenum,GLuint,GLuint){printMissingFunctionError("glBindBufferBase");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBindBufferBaseNV(GLenum,GLuint,GLuint){printMissingFunctionError("glBindBufferBaseNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBindBuffer(GLenum,GLuint){printMissingFunctionError("glBindBuffer");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBindBufferOffsetEXT(GLenum,GLuint,GLuint,GLintptr){printMissingFunctionError("glBindBufferOffsetEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBindBufferOffsetNV(GLenum,GLuint,GLuint,GLintptr){printMissingFunctionError("glBindBufferOffsetNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBindBufferRangeEXT(GLenum,GLuint,GLuint,GLintptr,GLsizeiptr){printMissingFunctionError("glBindBufferRangeEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBindBufferRange(GLenum,GLuint,GLuint,GLintptr,GLsizeiptr){printMissingFunctionError("glBindBufferRange");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBindBufferRangeNV(GLenum,GLuint,GLuint,GLintptr,GLsizeiptr){printMissingFunctionError("glBindBufferRangeNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBindBuffersBase(GLenum,GLuint,GLsizei,const GLuint*){printMissingFunctionError("glBindBuffersBase");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBindBuffersRange(GLenum,GLuint,GLsizei,const GLuint*,const GLintptr*,const GLsizeiptr*){printMissingFunctionError("glBindBuffersRange");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBindFragDataLocationEXT(GLuint,GLuint,const GLchar*){printMissingFunctionError("glBindFragDataLocationEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBindFragDataLocation(GLuint,GLuint,const GLchar*){printMissingFunctionError("glBindFragDataLocation");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBindFragDataLocationIndexed(GLuint,GLuint,GLuint,const GLchar*){printMissingFunctionError("glBindFragDataLocationIndexed");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBindFragmentShaderATI(GLuint){printMissingFunctionError("glBindFragmentShaderATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBindFramebufferEXT(GLenum,GLuint){printMissingFunctionError("glBindFramebufferEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBindFramebuffer(GLenum,GLuint){printMissingFunctionError("glBindFramebuffer");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBindImageTextureEXT(GLuint,GLuint,GLint,GLboolean,GLint,GLenum,GLint){printMissingFunctionError("glBindImageTextureEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBindImageTexture(GLuint,GLuint,GLint,GLboolean,GLint,GLenum,GLenum){printMissingFunctionError("glBindImageTexture");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBindImageTextures(GLuint,GLsizei,const GLuint*){printMissingFunctionError("glBindImageTextures");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBindMultiTextureEXT(GLenum,GLenum,GLuint){printMissingFunctionError("glBindMultiTextureEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBindProgramARB(GLenum,GLuint){printMissingFunctionError("glBindProgramARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBindProgramNV(GLenum,GLuint){printMissingFunctionError("glBindProgramNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBindProgramPipeline(GLuint){printMissingFunctionError("glBindProgramPipeline");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBindRenderbufferEXT(GLenum,GLuint){printMissingFunctionError("glBindRenderbufferEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBindRenderbuffer(GLenum,GLuint){printMissingFunctionError("glBindRenderbuffer");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBindSampler(GLuint,GLuint){printMissingFunctionError("glBindSampler");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBindSamplers(GLuint,GLsizei,const GLuint*){printMissingFunctionError("glBindSamplers");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBindTextureEXT(GLenum,GLuint){printMissingFunctionError("glBindTextureEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBindTexture(GLenum,GLuint){printMissingFunctionError("glBindTexture");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBindTextures(GLuint,GLsizei,const GLuint*){printMissingFunctionError("glBindTextures");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBindTextureUnit(GLuint,GLuint){printMissingFunctionError("glBindTextureUnit");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBindTransformFeedback(GLenum,GLuint){printMissingFunctionError("glBindTransformFeedback");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBindTransformFeedbackNV(GLenum,GLuint){printMissingFunctionError("glBindTransformFeedbackNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBindVertexArrayAPPLE(GLuint){printMissingFunctionError("glBindVertexArrayAPPLE");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBindVertexArray(GLuint){printMissingFunctionError("glBindVertexArray");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBindVertexBuffer(GLuint,GLuint,GLintptr,GLsizei){printMissingFunctionError("glBindVertexBuffer");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBindVertexBuffers(GLuint,GLsizei,const GLuint*,const GLintptr*,const GLsizei*){printMissingFunctionError("glBindVertexBuffers");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBindVertexShaderEXT(GLuint){printMissingFunctionError("glBindVertexShaderEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBindVideoCaptureStreamBufferNV(GLuint,GLuint,GLenum,GLintptrARB){printMissingFunctionError("glBindVideoCaptureStreamBufferNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBindVideoCaptureStreamTextureNV(GLuint,GLuint,GLenum,GLenum,GLuint){printMissingFunctionError("glBindVideoCaptureStreamTextureNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBinormal3bEXT(GLbyte,GLbyte,GLbyte){printMissingFunctionError("glBinormal3bEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBinormal3bvEXT(const GLbyte*){printMissingFunctionError("glBinormal3bvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBinormal3dEXT(GLdouble,GLdouble,GLdouble){printMissingFunctionError("glBinormal3dEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBinormal3dvEXT(const GLdouble*){printMissingFunctionError("glBinormal3dvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBinormal3fEXT(GLfloat,GLfloat,GLfloat){printMissingFunctionError("glBinormal3fEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBinormal3fvEXT(const GLfloat*){printMissingFunctionError("glBinormal3fvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBinormal3iEXT(GLint,GLint,GLint){printMissingFunctionError("glBinormal3iEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBinormal3ivEXT(const GLint*){printMissingFunctionError("glBinormal3ivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBinormal3sEXT(GLshort,GLshort,GLshort){printMissingFunctionError("glBinormal3sEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBinormal3svEXT(const GLshort*){printMissingFunctionError("glBinormal3svEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBinormalPointerEXT(GLenum,GLsizei,const void*){printMissingFunctionError("glBinormalPointerEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBitmap(GLsizei,GLsizei,GLfloat,GLfloat,GLfloat,GLfloat,const GLubyte*){printMissingFunctionError("glBitmap");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBitmapxOES(GLsizei,GLsizei,GLfixed,GLfixed,GLfixed,GLfixed,const GLubyte*){printMissingFunctionError("glBitmapxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBlendBarrierKHR(){printMissingFunctionError("glBlendBarrierKHR");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBlendBarrierNV(){printMissingFunctionError("glBlendBarrierNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBlendColorEXT(GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glBlendColorEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBlendColor(GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glBlendColor");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBlendColorxOES(GLfixed,GLfixed,GLfixed,GLfixed){printMissingFunctionError("glBlendColorxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBlendEquationEXT(GLenum){printMissingFunctionError("glBlendEquationEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBlendEquation(GLenum){printMissingFunctionError("glBlendEquation");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBlendEquationiARB(GLuint,GLenum){printMissingFunctionError("glBlendEquationiARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBlendEquationi(GLuint,GLenum){printMissingFunctionError("glBlendEquationi");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBlendEquationIndexedAMD(GLuint,GLenum){printMissingFunctionError("glBlendEquationIndexedAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBlendEquationSeparateATI(GLenum,GLenum){printMissingFunctionError("glBlendEquationSeparateATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBlendEquationSeparateEXT(GLenum,GLenum){printMissingFunctionError("glBlendEquationSeparateEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBlendEquationSeparate(GLenum,GLenum){printMissingFunctionError("glBlendEquationSeparate");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBlendEquationSeparateiARB(GLuint,GLenum,GLenum){printMissingFunctionError("glBlendEquationSeparateiARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBlendEquationSeparatei(GLuint,GLenum,GLenum){printMissingFunctionError("glBlendEquationSeparatei");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBlendEquationSeparateIndexedAMD(GLuint,GLenum,GLenum){printMissingFunctionError("glBlendEquationSeparateIndexedAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBlendFunc(GLenum,GLenum){printMissingFunctionError("glBlendFunc");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBlendFunciARB(GLuint,GLenum,GLenum){printMissingFunctionError("glBlendFunciARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBlendFunci(GLuint,GLenum,GLenum){printMissingFunctionError("glBlendFunci");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBlendFuncIndexedAMD(GLuint,GLenum,GLenum){printMissingFunctionError("glBlendFuncIndexedAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBlendFuncSeparateEXT(GLenum,GLenum,GLenum,GLenum){printMissingFunctionError("glBlendFuncSeparateEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBlendFuncSeparate(GLenum,GLenum,GLenum,GLenum){printMissingFunctionError("glBlendFuncSeparate");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBlendFuncSeparateiARB(GLuint,GLenum,GLenum,GLenum,GLenum){printMissingFunctionError("glBlendFuncSeparateiARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBlendFuncSeparatei(GLuint,GLenum,GLenum,GLenum,GLenum){printMissingFunctionError("glBlendFuncSeparatei");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBlendFuncSeparateIndexedAMD(GLuint,GLenum,GLenum,GLenum,GLenum){printMissingFunctionError("glBlendFuncSeparateIndexedAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBlendFuncSeparateINGR(GLenum,GLenum,GLenum,GLenum){printMissingFunctionError("glBlendFuncSeparateINGR");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBlendParameteriNV(GLenum,GLint){printMissingFunctionError("glBlendParameteriNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBlitFramebufferEXT(GLint,GLint,GLint,GLint,GLint,GLint,GLint,GLint,GLbitfield,GLenum){printMissingFunctionError("glBlitFramebufferEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBlitFramebuffer(GLint,GLint,GLint,GLint,GLint,GLint,GLint,GLint,GLbitfield,GLenum){printMissingFunctionError("glBlitFramebuffer");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBlitNamedFramebuffer(GLuint,GLuint,GLint,GLint,GLint,GLint,GLint,GLint,GLint,GLint,GLbitfield,GLenum){printMissingFunctionError("glBlitNamedFramebuffer");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBufferAddressRangeNV(GLenum,GLuint,GLuint64EXT,GLsizeiptr){printMissingFunctionError("glBufferAddressRangeNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBufferDataARB(GLenum,GLsizeiptrARB,const void*,GLenum){printMissingFunctionError("glBufferDataARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBufferData(GLenum,GLsizeiptr,const void*,GLenum){printMissingFunctionError("glBufferData");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBufferPageCommitmentARB(GLenum,GLintptr,GLsizeiptr,GLboolean){printMissingFunctionError("glBufferPageCommitmentARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBufferParameteriAPPLE(GLenum,GLenum,GLint){printMissingFunctionError("glBufferParameteriAPPLE");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBufferStorage(GLenum,GLsizeiptr,const void*,GLbitfield){printMissingFunctionError("glBufferStorage");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBufferSubDataARB(GLenum,GLintptrARB,GLsizeiptrARB,const void*){printMissingFunctionError("glBufferSubDataARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglBufferSubData(GLenum,GLintptr,GLsizeiptr,const void*){printMissingFunctionError("glBufferSubData");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCallCommandListNV(GLuint){printMissingFunctionError("glCallCommandListNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCallList(GLuint){printMissingFunctionError("glCallList");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCallLists(GLsizei,GLenum,const GLvoid*){printMissingFunctionError("glCallLists");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglClampColorARB(GLenum,GLenum){printMissingFunctionError("glClampColorARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglClampColor(GLenum,GLenum){printMissingFunctionError("glClampColor");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglClearAccum(GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glClearAccum");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglClearAccumxOES(GLfixed,GLfixed,GLfixed,GLfixed){printMissingFunctionError("glClearAccumxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglClearBufferData(GLenum,GLenum,GLenum,GLenum,const void*){printMissingFunctionError("glClearBufferData");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglClearBufferfi(GLenum,GLint,GLfloat,GLint){printMissingFunctionError("glClearBufferfi");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglClearBufferfv(GLenum,GLint,const GLfloat*){printMissingFunctionError("glClearBufferfv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglClearBufferiv(GLenum,GLint,const GLint*){printMissingFunctionError("glClearBufferiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglClearBufferSubData(GLenum,GLenum,GLintptr,GLsizeiptr,GLenum,GLenum,const void*){printMissingFunctionError("glClearBufferSubData");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglClearBufferuiv(GLenum,GLint,const GLuint*){printMissingFunctionError("glClearBufferuiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglClearColor(GLclampf,GLclampf,GLclampf,GLclampf){printMissingFunctionError("glClearColor");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglClearColorIiEXT(GLint,GLint,GLint,GLint){printMissingFunctionError("glClearColorIiEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglClearColorIuiEXT(GLuint,GLuint,GLuint,GLuint){printMissingFunctionError("glClearColorIuiEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglClearColorxOES(GLfixed,GLfixed,GLfixed,GLfixed){printMissingFunctionError("glClearColorxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglClearDepthdNV(GLdouble){printMissingFunctionError("glClearDepthdNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglClearDepthf(GLfloat){printMissingFunctionError("glClearDepthf");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglClearDepthfOES(GLclampf){printMissingFunctionError("glClearDepthfOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglClearDepth(GLclampd){printMissingFunctionError("glClearDepth");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglClearDepthxOES(GLfixed){printMissingFunctionError("glClearDepthxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglClear(GLbitfield){printMissingFunctionError("glClear");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglClearIndex(GLfloat){printMissingFunctionError("glClearIndex");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglClearNamedBufferDataEXT(GLuint,GLenum,GLenum,GLenum,const void*){printMissingFunctionError("glClearNamedBufferDataEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglClearNamedBufferData(GLuint,GLenum,GLenum,GLenum,const void*){printMissingFunctionError("glClearNamedBufferData");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglClearNamedBufferSubDataEXT(GLuint,GLenum,GLsizeiptr,GLsizeiptr,GLenum,GLenum,const void*){printMissingFunctionError("glClearNamedBufferSubDataEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglClearNamedBufferSubData(GLuint,GLenum,GLintptr,GLsizeiptr,GLenum,GLenum,const void*){printMissingFunctionError("glClearNamedBufferSubData");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglClearNamedFramebufferfi(GLuint,GLenum,GLint,GLfloat,GLint){printMissingFunctionError("glClearNamedFramebufferfi");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglClearNamedFramebufferfv(GLuint,GLenum,GLint,const GLfloat*){printMissingFunctionError("glClearNamedFramebufferfv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglClearNamedFramebufferiv(GLuint,GLenum,GLint,const GLint*){printMissingFunctionError("glClearNamedFramebufferiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglClearNamedFramebufferuiv(GLuint,GLenum,GLint,const GLuint*){printMissingFunctionError("glClearNamedFramebufferuiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglClearStencil(GLint){printMissingFunctionError("glClearStencil");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglClearTexImage(GLuint,GLint,GLenum,GLenum,const void*){printMissingFunctionError("glClearTexImage");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglClearTexSubImage(GLuint,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLenum,GLenum,const void*){printMissingFunctionError("glClearTexSubImage");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglClientActiveTextureARB(GLenum){printMissingFunctionError("glClientActiveTextureARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglClientActiveTexture(GLenum){printMissingFunctionError("glClientActiveTexture");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglClientActiveVertexStreamATI(GLenum){printMissingFunctionError("glClientActiveVertexStreamATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglClientAttribDefaultEXT(GLbitfield){printMissingFunctionError("glClientAttribDefaultEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglClipControl(GLenum,GLenum){printMissingFunctionError("glClipControl");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglClipPlanefOES(GLenum,const GLfloat*){printMissingFunctionError("glClipPlanefOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglClipPlane(GLenum,const GLdouble*){printMissingFunctionError("glClipPlane");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglClipPlanexOES(GLenum,const GLfixed*){printMissingFunctionError("glClipPlanexOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColor3b(GLbyte,GLbyte,GLbyte){printMissingFunctionError("glColor3b");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColor3bv(const GLbyte*){printMissingFunctionError("glColor3bv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColor3d(GLdouble,GLdouble,GLdouble){printMissingFunctionError("glColor3d");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColor3dv(const GLdouble*){printMissingFunctionError("glColor3dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColor3f(GLfloat,GLfloat,GLfloat){printMissingFunctionError("glColor3f");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColor3fv(const GLfloat*){printMissingFunctionError("glColor3fv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColor3fVertex3fSUN(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glColor3fVertex3fSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColor3fVertex3fvSUN(const GLfloat*,const GLfloat*){printMissingFunctionError("glColor3fVertex3fvSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColor3hNV(GLhalfNV,GLhalfNV,GLhalfNV){printMissingFunctionError("glColor3hNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColor3hvNV(const GLhalfNV*){printMissingFunctionError("glColor3hvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColor3i(GLint,GLint,GLint){printMissingFunctionError("glColor3i");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColor3iv(const GLint*){printMissingFunctionError("glColor3iv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColor3s(GLshort,GLshort,GLshort){printMissingFunctionError("glColor3s");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColor3sv(const GLshort*){printMissingFunctionError("glColor3sv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColor3ub(GLubyte,GLubyte,GLubyte){printMissingFunctionError("glColor3ub");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColor3ubv(const GLubyte*){printMissingFunctionError("glColor3ubv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColor3ui(GLuint,GLuint,GLuint){printMissingFunctionError("glColor3ui");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColor3uiv(const GLuint*){printMissingFunctionError("glColor3uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColor3us(GLushort,GLushort,GLushort){printMissingFunctionError("glColor3us");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColor3usv(const GLushort*){printMissingFunctionError("glColor3usv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColor3xOES(GLfixed,GLfixed,GLfixed){printMissingFunctionError("glColor3xOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColor3xvOES(const GLfixed*){printMissingFunctionError("glColor3xvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColor4b(GLbyte,GLbyte,GLbyte,GLbyte){printMissingFunctionError("glColor4b");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColor4bv(const GLbyte*){printMissingFunctionError("glColor4bv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColor4d(GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glColor4d");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColor4dv(const GLdouble*){printMissingFunctionError("glColor4dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColor4f(GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glColor4f");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColor4fNormal3fVertex3fSUN(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glColor4fNormal3fVertex3fSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColor4fNormal3fVertex3fvSUN(const GLfloat*,const GLfloat*,const GLfloat*){printMissingFunctionError("glColor4fNormal3fVertex3fvSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColor4fv(const GLfloat*){printMissingFunctionError("glColor4fv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColor4hNV(GLhalfNV,GLhalfNV,GLhalfNV,GLhalfNV){printMissingFunctionError("glColor4hNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColor4hvNV(const GLhalfNV*){printMissingFunctionError("glColor4hvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColor4i(GLint,GLint,GLint,GLint){printMissingFunctionError("glColor4i");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColor4iv(const GLint*){printMissingFunctionError("glColor4iv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColor4s(GLshort,GLshort,GLshort,GLshort){printMissingFunctionError("glColor4s");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColor4sv(const GLshort*){printMissingFunctionError("glColor4sv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColor4ub(GLubyte,GLubyte,GLubyte,GLubyte){printMissingFunctionError("glColor4ub");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColor4ubv(const GLubyte*){printMissingFunctionError("glColor4ubv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColor4ubVertex2fSUN(GLubyte,GLubyte,GLubyte,GLubyte,GLfloat,GLfloat){printMissingFunctionError("glColor4ubVertex2fSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColor4ubVertex2fvSUN(const GLubyte*,const GLfloat*){printMissingFunctionError("glColor4ubVertex2fvSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColor4ubVertex3fSUN(GLubyte,GLubyte,GLubyte,GLubyte,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glColor4ubVertex3fSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColor4ubVertex3fvSUN(const GLubyte*,const GLfloat*){printMissingFunctionError("glColor4ubVertex3fvSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColor4ui(GLuint,GLuint,GLuint,GLuint){printMissingFunctionError("glColor4ui");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColor4uiv(const GLuint*){printMissingFunctionError("glColor4uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColor4us(GLushort,GLushort,GLushort,GLushort){printMissingFunctionError("glColor4us");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColor4usv(const GLushort*){printMissingFunctionError("glColor4usv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColor4xOES(GLfixed,GLfixed,GLfixed,GLfixed){printMissingFunctionError("glColor4xOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColor4xvOES(const GLfixed*){printMissingFunctionError("glColor4xvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColorFormatNV(GLint,GLenum,GLsizei){printMissingFunctionError("glColorFormatNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColorFragmentOp1ATI(GLenum,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint){printMissingFunctionError("glColorFragmentOp1ATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColorFragmentOp2ATI(GLenum,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint){printMissingFunctionError("glColorFragmentOp2ATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColorFragmentOp3ATI(GLenum,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint){printMissingFunctionError("glColorFragmentOp3ATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColorMask(GLboolean,GLboolean,GLboolean,GLboolean){printMissingFunctionError("glColorMask");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColorMaski(GLuint,GLboolean,GLboolean,GLboolean,GLboolean){printMissingFunctionError("glColorMaski");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColorMaskIndexedEXT(GLuint,GLboolean,GLboolean,GLboolean,GLboolean){printMissingFunctionError("glColorMaskIndexedEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColorMaterial(GLenum,GLenum){printMissingFunctionError("glColorMaterial");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColorP3ui(GLenum,GLuint){printMissingFunctionError("glColorP3ui");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColorP3uiv(GLenum,const GLuint*){printMissingFunctionError("glColorP3uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColorP4ui(GLenum,GLuint){printMissingFunctionError("glColorP4ui");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColorP4uiv(GLenum,const GLuint*){printMissingFunctionError("glColorP4uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColorPointerEXT(GLint,GLenum,GLsizei,GLsizei,const void*){printMissingFunctionError("glColorPointerEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColorPointer(GLint,GLenum,GLsizei,const GLvoid*){printMissingFunctionError("glColorPointer");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColorPointerListIBM(GLint,GLenum,GLint,const void**,GLint){printMissingFunctionError("glColorPointerListIBM");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColorPointervINTEL(GLint,GLenum,const void**){printMissingFunctionError("glColorPointervINTEL");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColorSubTableEXT(GLenum,GLsizei,GLsizei,GLenum,GLenum,const void*){printMissingFunctionError("glColorSubTableEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColorSubTable(GLenum,GLsizei,GLsizei,GLenum,GLenum,const GLvoid*){printMissingFunctionError("glColorSubTable");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColorTableEXT(GLenum,GLenum,GLsizei,GLenum,GLenum,const void*){printMissingFunctionError("glColorTableEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColorTable(GLenum,GLenum,GLsizei,GLenum,GLenum,const GLvoid*){printMissingFunctionError("glColorTable");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColorTableParameterfv(GLenum,GLenum,const GLfloat*){printMissingFunctionError("glColorTableParameterfv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColorTableParameterfvSGI(GLenum,GLenum,const GLfloat*){printMissingFunctionError("glColorTableParameterfvSGI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColorTableParameteriv(GLenum,GLenum,const GLint*){printMissingFunctionError("glColorTableParameteriv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColorTableParameterivSGI(GLenum,GLenum,const GLint*){printMissingFunctionError("glColorTableParameterivSGI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglColorTableSGI(GLenum,GLenum,GLsizei,GLenum,GLenum,const void*){printMissingFunctionError("glColorTableSGI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCombinerInputNV(GLenum,GLenum,GLenum,GLenum,GLenum,GLenum){printMissingFunctionError("glCombinerInputNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCombinerOutputNV(GLenum,GLenum,GLenum,GLenum,GLenum,GLenum,GLenum,GLboolean,GLboolean,GLboolean){printMissingFunctionError("glCombinerOutputNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCombinerParameterfNV(GLenum,GLfloat){printMissingFunctionError("glCombinerParameterfNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCombinerParameterfvNV(GLenum,const GLfloat*){printMissingFunctionError("glCombinerParameterfvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCombinerParameteriNV(GLenum,GLint){printMissingFunctionError("glCombinerParameteriNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCombinerParameterivNV(GLenum,const GLint*){printMissingFunctionError("glCombinerParameterivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCombinerStageParameterfvNV(GLenum,GLenum,const GLfloat*){printMissingFunctionError("glCombinerStageParameterfvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCommandListSegmentsNV(GLuint,GLuint){printMissingFunctionError("glCommandListSegmentsNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCompileCommandListNV(GLuint){printMissingFunctionError("glCompileCommandListNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCompileShaderARB(GLhandleARB){printMissingFunctionError("glCompileShaderARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCompileShader(GLuint){printMissingFunctionError("glCompileShader");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCompileShaderIncludeARB(GLuint,GLsizei,const GLchar*const*,const GLint*){printMissingFunctionError("glCompileShaderIncludeARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCompressedMultiTexImage1DEXT(GLenum,GLenum,GLint,GLenum,GLsizei,GLint,GLsizei,const void*){printMissingFunctionError("glCompressedMultiTexImage1DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCompressedMultiTexImage2DEXT(GLenum,GLenum,GLint,GLenum,GLsizei,GLsizei,GLint,GLsizei,const void*){printMissingFunctionError("glCompressedMultiTexImage2DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCompressedMultiTexImage3DEXT(GLenum,GLenum,GLint,GLenum,GLsizei,GLsizei,GLsizei,GLint,GLsizei,const void*){printMissingFunctionError("glCompressedMultiTexImage3DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCompressedMultiTexSubImage1DEXT(GLenum,GLenum,GLint,GLint,GLsizei,GLenum,GLsizei,const void*){printMissingFunctionError("glCompressedMultiTexSubImage1DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCompressedMultiTexSubImage2DEXT(GLenum,GLenum,GLint,GLint,GLint,GLsizei,GLsizei,GLenum,GLsizei,const void*){printMissingFunctionError("glCompressedMultiTexSubImage2DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCompressedMultiTexSubImage3DEXT(GLenum,GLenum,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLenum,GLsizei,const void*){printMissingFunctionError("glCompressedMultiTexSubImage3DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCompressedTexImage1DARB(GLenum,GLint,GLenum,GLsizei,GLint,GLsizei,const void*){printMissingFunctionError("glCompressedTexImage1DARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCompressedTexImage1D(GLenum,GLint,GLenum,GLsizei,GLint,GLsizei,const GLvoid*){printMissingFunctionError("glCompressedTexImage1D");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCompressedTexImage2DARB(GLenum,GLint,GLenum,GLsizei,GLsizei,GLint,GLsizei,const void*){printMissingFunctionError("glCompressedTexImage2DARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCompressedTexImage2D(GLenum,GLint,GLenum,GLsizei,GLsizei,GLint,GLsizei,const GLvoid*){printMissingFunctionError("glCompressedTexImage2D");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCompressedTexImage3DARB(GLenum,GLint,GLenum,GLsizei,GLsizei,GLsizei,GLint,GLsizei,const void*){printMissingFunctionError("glCompressedTexImage3DARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCompressedTexImage3D(GLenum,GLint,GLenum,GLsizei,GLsizei,GLsizei,GLint,GLsizei,const GLvoid*){printMissingFunctionError("glCompressedTexImage3D");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCompressedTexSubImage1DARB(GLenum,GLint,GLint,GLsizei,GLenum,GLsizei,const void*){printMissingFunctionError("glCompressedTexSubImage1DARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCompressedTexSubImage1D(GLenum,GLint,GLint,GLsizei,GLenum,GLsizei,const GLvoid*){printMissingFunctionError("glCompressedTexSubImage1D");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCompressedTexSubImage2DARB(GLenum,GLint,GLint,GLint,GLsizei,GLsizei,GLenum,GLsizei,const void*){printMissingFunctionError("glCompressedTexSubImage2DARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCompressedTexSubImage2D(GLenum,GLint,GLint,GLint,GLsizei,GLsizei,GLenum,GLsizei,const GLvoid*){printMissingFunctionError("glCompressedTexSubImage2D");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCompressedTexSubImage3DARB(GLenum,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLenum,GLsizei,const void*){printMissingFunctionError("glCompressedTexSubImage3DARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCompressedTexSubImage3D(GLenum,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLenum,GLsizei,const GLvoid*){printMissingFunctionError("glCompressedTexSubImage3D");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCompressedTextureImage1DEXT(GLuint,GLenum,GLint,GLenum,GLsizei,GLint,GLsizei,const void*){printMissingFunctionError("glCompressedTextureImage1DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCompressedTextureImage2DEXT(GLuint,GLenum,GLint,GLenum,GLsizei,GLsizei,GLint,GLsizei,const void*){printMissingFunctionError("glCompressedTextureImage2DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCompressedTextureImage3DEXT(GLuint,GLenum,GLint,GLenum,GLsizei,GLsizei,GLsizei,GLint,GLsizei,const void*){printMissingFunctionError("glCompressedTextureImage3DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCompressedTextureSubImage1DEXT(GLuint,GLenum,GLint,GLint,GLsizei,GLenum,GLsizei,const void*){printMissingFunctionError("glCompressedTextureSubImage1DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCompressedTextureSubImage1D(GLuint,GLint,GLint,GLsizei,GLenum,GLsizei,const void*){printMissingFunctionError("glCompressedTextureSubImage1D");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCompressedTextureSubImage2DEXT(GLuint,GLenum,GLint,GLint,GLint,GLsizei,GLsizei,GLenum,GLsizei,const void*){printMissingFunctionError("glCompressedTextureSubImage2DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCompressedTextureSubImage2D(GLuint,GLint,GLint,GLint,GLsizei,GLsizei,GLenum,GLsizei,const void*){printMissingFunctionError("glCompressedTextureSubImage2D");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCompressedTextureSubImage3DEXT(GLuint,GLenum,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLenum,GLsizei,const void*){printMissingFunctionError("glCompressedTextureSubImage3DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCompressedTextureSubImage3D(GLuint,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLenum,GLsizei,const void*){printMissingFunctionError("glCompressedTextureSubImage3D");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglConservativeRasterParameterfNV(GLenum,GLfloat){printMissingFunctionError("glConservativeRasterParameterfNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglConvolutionFilter1DEXT(GLenum,GLenum,GLsizei,GLenum,GLenum,const void*){printMissingFunctionError("glConvolutionFilter1DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglConvolutionFilter1D(GLenum,GLenum,GLsizei,GLenum,GLenum,const GLvoid*){printMissingFunctionError("glConvolutionFilter1D");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglConvolutionFilter2DEXT(GLenum,GLenum,GLsizei,GLsizei,GLenum,GLenum,const void*){printMissingFunctionError("glConvolutionFilter2DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglConvolutionFilter2D(GLenum,GLenum,GLsizei,GLsizei,GLenum,GLenum,const GLvoid*){printMissingFunctionError("glConvolutionFilter2D");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglConvolutionParameterfEXT(GLenum,GLenum,GLfloat){printMissingFunctionError("glConvolutionParameterfEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglConvolutionParameterf(GLenum,GLenum,GLfloat){printMissingFunctionError("glConvolutionParameterf");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglConvolutionParameterfvEXT(GLenum,GLenum,const GLfloat*){printMissingFunctionError("glConvolutionParameterfvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglConvolutionParameterfv(GLenum,GLenum,const GLfloat*){printMissingFunctionError("glConvolutionParameterfv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglConvolutionParameteriEXT(GLenum,GLenum,GLint){printMissingFunctionError("glConvolutionParameteriEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglConvolutionParameteri(GLenum,GLenum,GLint){printMissingFunctionError("glConvolutionParameteri");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglConvolutionParameterivEXT(GLenum,GLenum,const GLint*){printMissingFunctionError("glConvolutionParameterivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglConvolutionParameteriv(GLenum,GLenum,const GLint*){printMissingFunctionError("glConvolutionParameteriv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglConvolutionParameterxOES(GLenum,GLenum,GLfixed){printMissingFunctionError("glConvolutionParameterxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglConvolutionParameterxvOES(GLenum,GLenum,const GLfixed*){printMissingFunctionError("glConvolutionParameterxvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCopyBufferSubData(GLenum,GLenum,GLintptr,GLintptr,GLsizeiptr){printMissingFunctionError("glCopyBufferSubData");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCopyColorSubTableEXT(GLenum,GLsizei,GLint,GLint,GLsizei){printMissingFunctionError("glCopyColorSubTableEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCopyColorSubTable(GLenum,GLsizei,GLint,GLint,GLsizei){printMissingFunctionError("glCopyColorSubTable");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCopyColorTable(GLenum,GLenum,GLint,GLint,GLsizei){printMissingFunctionError("glCopyColorTable");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCopyColorTableSGI(GLenum,GLenum,GLint,GLint,GLsizei){printMissingFunctionError("glCopyColorTableSGI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCopyConvolutionFilter1DEXT(GLenum,GLenum,GLint,GLint,GLsizei){printMissingFunctionError("glCopyConvolutionFilter1DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCopyConvolutionFilter1D(GLenum,GLenum,GLint,GLint,GLsizei){printMissingFunctionError("glCopyConvolutionFilter1D");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCopyConvolutionFilter2DEXT(GLenum,GLenum,GLint,GLint,GLsizei,GLsizei){printMissingFunctionError("glCopyConvolutionFilter2DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCopyConvolutionFilter2D(GLenum,GLenum,GLint,GLint,GLsizei,GLsizei){printMissingFunctionError("glCopyConvolutionFilter2D");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCopyImageSubData(GLuint,GLenum,GLint,GLint,GLint,GLint,GLuint,GLenum,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei){printMissingFunctionError("glCopyImageSubData");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCopyImageSubDataNV(GLuint,GLenum,GLint,GLint,GLint,GLint,GLuint,GLenum,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei){printMissingFunctionError("glCopyImageSubDataNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCopyMultiTexImage1DEXT(GLenum,GLenum,GLint,GLenum,GLint,GLint,GLsizei,GLint){printMissingFunctionError("glCopyMultiTexImage1DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCopyMultiTexImage2DEXT(GLenum,GLenum,GLint,GLenum,GLint,GLint,GLsizei,GLsizei,GLint){printMissingFunctionError("glCopyMultiTexImage2DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCopyMultiTexSubImage1DEXT(GLenum,GLenum,GLint,GLint,GLint,GLint,GLsizei){printMissingFunctionError("glCopyMultiTexSubImage1DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCopyMultiTexSubImage2DEXT(GLenum,GLenum,GLint,GLint,GLint,GLint,GLint,GLsizei,GLsizei){printMissingFunctionError("glCopyMultiTexSubImage2DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCopyMultiTexSubImage3DEXT(GLenum,GLenum,GLint,GLint,GLint,GLint,GLint,GLint,GLsizei,GLsizei){printMissingFunctionError("glCopyMultiTexSubImage3DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCopyNamedBufferSubData(GLuint,GLuint,GLintptr,GLintptr,GLsizeiptr){printMissingFunctionError("glCopyNamedBufferSubData");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCopyPathNV(GLuint,GLuint){printMissingFunctionError("glCopyPathNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCopyPixels(GLint,GLint,GLsizei,GLsizei,GLenum){printMissingFunctionError("glCopyPixels");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCopyTexImage1DEXT(GLenum,GLint,GLenum,GLint,GLint,GLsizei,GLint){printMissingFunctionError("glCopyTexImage1DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCopyTexImage1D(GLenum,GLint,GLenum,GLint,GLint,GLsizei,GLint){printMissingFunctionError("glCopyTexImage1D");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCopyTexImage2DEXT(GLenum,GLint,GLenum,GLint,GLint,GLsizei,GLsizei,GLint){printMissingFunctionError("glCopyTexImage2DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCopyTexImage2D(GLenum,GLint,GLenum,GLint,GLint,GLsizei,GLsizei,GLint){printMissingFunctionError("glCopyTexImage2D");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCopyTexSubImage1DEXT(GLenum,GLint,GLint,GLint,GLint,GLsizei){printMissingFunctionError("glCopyTexSubImage1DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCopyTexSubImage1D(GLenum,GLint,GLint,GLint,GLint,GLsizei){printMissingFunctionError("glCopyTexSubImage1D");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCopyTexSubImage2DEXT(GLenum,GLint,GLint,GLint,GLint,GLint,GLsizei,GLsizei){printMissingFunctionError("glCopyTexSubImage2DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCopyTexSubImage2D(GLenum,GLint,GLint,GLint,GLint,GLint,GLsizei,GLsizei){printMissingFunctionError("glCopyTexSubImage2D");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCopyTexSubImage3DEXT(GLenum,GLint,GLint,GLint,GLint,GLint,GLint,GLsizei,GLsizei){printMissingFunctionError("glCopyTexSubImage3DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCopyTexSubImage3D(GLenum,GLint,GLint,GLint,GLint,GLint,GLint,GLsizei,GLsizei){printMissingFunctionError("glCopyTexSubImage3D");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCopyTextureImage1DEXT(GLuint,GLenum,GLint,GLenum,GLint,GLint,GLsizei,GLint){printMissingFunctionError("glCopyTextureImage1DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCopyTextureImage2DEXT(GLuint,GLenum,GLint,GLenum,GLint,GLint,GLsizei,GLsizei,GLint){printMissingFunctionError("glCopyTextureImage2DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCopyTextureSubImage1DEXT(GLuint,GLenum,GLint,GLint,GLint,GLint,GLsizei){printMissingFunctionError("glCopyTextureSubImage1DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCopyTextureSubImage1D(GLuint,GLint,GLint,GLint,GLint,GLsizei){printMissingFunctionError("glCopyTextureSubImage1D");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCopyTextureSubImage2DEXT(GLuint,GLenum,GLint,GLint,GLint,GLint,GLint,GLsizei,GLsizei){printMissingFunctionError("glCopyTextureSubImage2DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCopyTextureSubImage2D(GLuint,GLint,GLint,GLint,GLint,GLint,GLsizei,GLsizei){printMissingFunctionError("glCopyTextureSubImage2D");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCopyTextureSubImage3DEXT(GLuint,GLenum,GLint,GLint,GLint,GLint,GLint,GLint,GLsizei,GLsizei){printMissingFunctionError("glCopyTextureSubImage3DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCopyTextureSubImage3D(GLuint,GLint,GLint,GLint,GLint,GLint,GLint,GLsizei,GLsizei){printMissingFunctionError("glCopyTextureSubImage3D");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCoverageModulationNV(GLenum){printMissingFunctionError("glCoverageModulationNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCoverageModulationTableNV(GLsizei,const GLfloat*){printMissingFunctionError("glCoverageModulationTableNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCoverFillPathInstancedNV(GLsizei,GLenum,const void*,GLuint,GLenum,GLenum,const GLfloat*){printMissingFunctionError("glCoverFillPathInstancedNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCoverFillPathNV(GLuint,GLenum){printMissingFunctionError("glCoverFillPathNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCoverStrokePathInstancedNV(GLsizei,GLenum,const void*,GLuint,GLenum,GLenum,const GLfloat*){printMissingFunctionError("glCoverStrokePathInstancedNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCoverStrokePathNV(GLuint,GLenum){printMissingFunctionError("glCoverStrokePathNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCreateBuffers(GLsizei,GLuint*){printMissingFunctionError("glCreateBuffers");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCreateCommandListsNV(GLsizei,GLuint*){printMissingFunctionError("glCreateCommandListsNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCreateFramebuffers(GLsizei,GLuint*){printMissingFunctionError("glCreateFramebuffers");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCreatePerfQueryINTEL(GLuint,GLuint*){printMissingFunctionError("glCreatePerfQueryINTEL");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCreateProgramPipelines(GLsizei,GLuint*){printMissingFunctionError("glCreateProgramPipelines");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCreateQueries(GLenum,GLsizei,GLuint*){printMissingFunctionError("glCreateQueries");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCreateRenderbuffers(GLsizei,GLuint*){printMissingFunctionError("glCreateRenderbuffers");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCreateSamplers(GLsizei,GLuint*){printMissingFunctionError("glCreateSamplers");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCreateStatesNV(GLsizei,GLuint*){printMissingFunctionError("glCreateStatesNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCreateTextures(GLenum,GLsizei,GLuint*){printMissingFunctionError("glCreateTextures");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCreateTransformFeedbacks(GLsizei,GLuint*){printMissingFunctionError("glCreateTransformFeedbacks");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCreateVertexArrays(GLsizei,GLuint*){printMissingFunctionError("glCreateVertexArrays");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCullFace(GLenum){printMissingFunctionError("glCullFace");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCullParameterdvEXT(GLenum,GLdouble*){printMissingFunctionError("glCullParameterdvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCullParameterfvEXT(GLenum,GLfloat*){printMissingFunctionError("glCullParameterfvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglCurrentPaletteMatrixARB(GLint){printMissingFunctionError("glCurrentPaletteMatrixARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDebugMessageCallbackAMD(GLDEBUGPROCAMD,void*){printMissingFunctionError("glDebugMessageCallbackAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDebugMessageCallbackARB(GLDEBUGPROCARB,const void*){printMissingFunctionError("glDebugMessageCallbackARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDebugMessageCallback(GLDEBUGPROC,const void*){printMissingFunctionError("glDebugMessageCallback");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDebugMessageControlARB(GLenum,GLenum,GLenum,GLsizei,const GLuint*,GLboolean){printMissingFunctionError("glDebugMessageControlARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDebugMessageControl(GLenum,GLenum,GLenum,GLsizei,const GLuint*,GLboolean){printMissingFunctionError("glDebugMessageControl");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDebugMessageEnableAMD(GLenum,GLenum,GLsizei,const GLuint*,GLboolean){printMissingFunctionError("glDebugMessageEnableAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDebugMessageInsertAMD(GLenum,GLenum,GLuint,GLsizei,const GLchar*){printMissingFunctionError("glDebugMessageInsertAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDebugMessageInsertARB(GLenum,GLenum,GLuint,GLenum,GLsizei,const GLchar*){printMissingFunctionError("glDebugMessageInsertARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDebugMessageInsert(GLenum,GLenum,GLuint,GLenum,GLsizei,const GLchar*){printMissingFunctionError("glDebugMessageInsert");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDeformationMap3dSGIX(GLenum,GLdouble,GLdouble,GLint,GLint,GLdouble,GLdouble,GLint,GLint,GLdouble,GLdouble,GLint,GLint,const GLdouble*){printMissingFunctionError("glDeformationMap3dSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDeformationMap3fSGIX(GLenum,GLfloat,GLfloat,GLint,GLint,GLfloat,GLfloat,GLint,GLint,GLfloat,GLfloat,GLint,GLint,const GLfloat*){printMissingFunctionError("glDeformationMap3fSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDeformSGIX(GLbitfield){printMissingFunctionError("glDeformSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDeleteAsyncMarkersSGIX(GLuint,GLsizei){printMissingFunctionError("glDeleteAsyncMarkersSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDeleteBuffersARB(GLsizei,const GLuint*){printMissingFunctionError("glDeleteBuffersARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDeleteBuffers(GLsizei,const GLuint*){printMissingFunctionError("glDeleteBuffers");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDeleteCommandListsNV(GLsizei,const GLuint*){printMissingFunctionError("glDeleteCommandListsNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDeleteFencesAPPLE(GLsizei,const GLuint*){printMissingFunctionError("glDeleteFencesAPPLE");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDeleteFencesNV(GLsizei,const GLuint*){printMissingFunctionError("glDeleteFencesNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDeleteFragmentShaderATI(GLuint){printMissingFunctionError("glDeleteFragmentShaderATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDeleteFramebuffersEXT(GLsizei,const GLuint*){printMissingFunctionError("glDeleteFramebuffersEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDeleteFramebuffers(GLsizei,const GLuint*){printMissingFunctionError("glDeleteFramebuffers");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDeleteLists(GLuint,GLsizei){printMissingFunctionError("glDeleteLists");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDeleteNamedStringARB(GLint,const GLchar*){printMissingFunctionError("glDeleteNamedStringARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDeleteNamesAMD(GLenum,GLuint,const GLuint*){printMissingFunctionError("glDeleteNamesAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDeleteObjectARB(GLhandleARB){printMissingFunctionError("glDeleteObjectARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDeleteOcclusionQueriesNV(GLsizei,const GLuint*){printMissingFunctionError("glDeleteOcclusionQueriesNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDeletePathsNV(GLuint,GLsizei){printMissingFunctionError("glDeletePathsNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDeletePerfMonitorsAMD(GLsizei,GLuint*){printMissingFunctionError("glDeletePerfMonitorsAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDeletePerfQueryINTEL(GLuint){printMissingFunctionError("glDeletePerfQueryINTEL");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDeleteProgram(GLuint){printMissingFunctionError("glDeleteProgram");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDeleteProgramPipelines(GLsizei,const GLuint*){printMissingFunctionError("glDeleteProgramPipelines");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDeleteProgramsARB(GLsizei,const GLuint*){printMissingFunctionError("glDeleteProgramsARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDeleteProgramsNV(GLsizei,const GLuint*){printMissingFunctionError("glDeleteProgramsNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDeleteQueriesARB(GLsizei,const GLuint*){printMissingFunctionError("glDeleteQueriesARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDeleteQueries(GLsizei,const GLuint*){printMissingFunctionError("glDeleteQueries");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDeleteRenderbuffersEXT(GLsizei,const GLuint*){printMissingFunctionError("glDeleteRenderbuffersEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDeleteRenderbuffers(GLsizei,const GLuint*){printMissingFunctionError("glDeleteRenderbuffers");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDeleteSamplers(GLsizei,const GLuint*){printMissingFunctionError("glDeleteSamplers");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDeleteShader(GLuint){printMissingFunctionError("glDeleteShader");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDeleteStatesNV(GLsizei,const GLuint*){printMissingFunctionError("glDeleteStatesNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDeleteSync(GLsync){printMissingFunctionError("glDeleteSync");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDeleteTexturesEXT(GLsizei,const GLuint*){printMissingFunctionError("glDeleteTexturesEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDeleteTextures(GLsizei,const GLuint*){printMissingFunctionError("glDeleteTextures");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDeleteTransformFeedbacks(GLsizei,const GLuint*){printMissingFunctionError("glDeleteTransformFeedbacks");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDeleteTransformFeedbacksNV(GLsizei,const GLuint*){printMissingFunctionError("glDeleteTransformFeedbacksNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDeleteVertexArraysAPPLE(GLsizei,const GLuint*){printMissingFunctionError("glDeleteVertexArraysAPPLE");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDeleteVertexArrays(GLsizei,const GLuint*){printMissingFunctionError("glDeleteVertexArrays");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDeleteVertexShaderEXT(GLuint){printMissingFunctionError("glDeleteVertexShaderEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDepthBoundsdNV(GLdouble,GLdouble){printMissingFunctionError("glDepthBoundsdNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDepthBoundsEXT(GLclampd,GLclampd){printMissingFunctionError("glDepthBoundsEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDepthFunc(GLenum){printMissingFunctionError("glDepthFunc");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDepthMask(GLboolean){printMissingFunctionError("glDepthMask");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDepthRangeArrayv(GLuint,GLsizei,const GLdouble*){printMissingFunctionError("glDepthRangeArrayv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDepthRangedNV(GLdouble,GLdouble){printMissingFunctionError("glDepthRangedNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDepthRangef(GLfloat,GLfloat){printMissingFunctionError("glDepthRangef");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDepthRangefOES(GLclampf,GLclampf){printMissingFunctionError("glDepthRangefOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDepthRange(GLclampd,GLclampd){printMissingFunctionError("glDepthRange");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDepthRangeIndexed(GLuint,GLdouble,GLdouble){printMissingFunctionError("glDepthRangeIndexed");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDepthRangexOES(GLfixed,GLfixed){printMissingFunctionError("glDepthRangexOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDetachObjectARB(GLhandleARB,GLhandleARB){printMissingFunctionError("glDetachObjectARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDetachShader(GLuint,GLuint){printMissingFunctionError("glDetachShader");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDetailTexFuncSGIS(GLenum,GLsizei,const GLfloat*){printMissingFunctionError("glDetailTexFuncSGIS");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDisableClientState(GLenum){printMissingFunctionError("glDisableClientState");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDisableClientStateiEXT(GLenum,GLuint){printMissingFunctionError("glDisableClientStateiEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDisableClientStateIndexedEXT(GLenum,GLuint){printMissingFunctionError("glDisableClientStateIndexedEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDisable(GLenum){printMissingFunctionError("glDisable");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDisablei(GLenum,GLuint){printMissingFunctionError("glDisablei");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDisableIndexedEXT(GLenum,GLuint){printMissingFunctionError("glDisableIndexedEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDisableVariantClientStateEXT(GLuint){printMissingFunctionError("glDisableVariantClientStateEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDisableVertexArrayAttribEXT(GLuint,GLuint){printMissingFunctionError("glDisableVertexArrayAttribEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDisableVertexArrayAttrib(GLuint,GLuint){printMissingFunctionError("glDisableVertexArrayAttrib");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDisableVertexArrayEXT(GLuint,GLenum){printMissingFunctionError("glDisableVertexArrayEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDisableVertexAttribAPPLE(GLuint,GLenum){printMissingFunctionError("glDisableVertexAttribAPPLE");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDisableVertexAttribArrayARB(GLuint){printMissingFunctionError("glDisableVertexAttribArrayARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDisableVertexAttribArray(GLuint){printMissingFunctionError("glDisableVertexAttribArray");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDispatchCompute(GLuint,GLuint,GLuint){printMissingFunctionError("glDispatchCompute");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDispatchComputeGroupSizeARB(GLuint,GLuint,GLuint,GLuint,GLuint,GLuint){printMissingFunctionError("glDispatchComputeGroupSizeARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDispatchComputeIndirect(GLintptr){printMissingFunctionError("glDispatchComputeIndirect");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDrawArraysEXT(GLenum,GLint,GLsizei){printMissingFunctionError("glDrawArraysEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDrawArrays(GLenum,GLint,GLsizei){printMissingFunctionError("glDrawArrays");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDrawArraysIndirect(GLenum,const void*){printMissingFunctionError("glDrawArraysIndirect");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDrawArraysInstancedARB(GLenum,GLint,GLsizei,GLsizei){printMissingFunctionError("glDrawArraysInstancedARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDrawArraysInstancedBaseInstance(GLenum,GLint,GLsizei,GLsizei,GLuint){printMissingFunctionError("glDrawArraysInstancedBaseInstance");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDrawArraysInstancedEXT(GLenum,GLint,GLsizei,GLsizei){printMissingFunctionError("glDrawArraysInstancedEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDrawArraysInstanced(GLenum,GLint,GLsizei,GLsizei){printMissingFunctionError("glDrawArraysInstanced");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDrawBuffer(GLenum){printMissingFunctionError("glDrawBuffer");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDrawBuffersARB(GLsizei,const GLenum*){printMissingFunctionError("glDrawBuffersARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDrawBuffersATI(GLsizei,const GLenum*){printMissingFunctionError("glDrawBuffersATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDrawBuffers(GLsizei,const GLenum*){printMissingFunctionError("glDrawBuffers");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDrawCommandsAddressNV(GLenum,const GLuint64*,const GLsizei*,GLuint){printMissingFunctionError("glDrawCommandsAddressNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDrawCommandsNV(GLenum,GLuint,const GLintptr*,const GLsizei*,GLuint){printMissingFunctionError("glDrawCommandsNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDrawCommandsStatesAddressNV(const GLuint64*,const GLsizei*,const GLuint*,const GLuint*,GLuint){printMissingFunctionError("glDrawCommandsStatesAddressNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDrawCommandsStatesNV(GLuint,const GLintptr*,const GLsizei*,const GLuint*,const GLuint*,GLuint){printMissingFunctionError("glDrawCommandsStatesNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDrawElementArrayAPPLE(GLenum,GLint,GLsizei){printMissingFunctionError("glDrawElementArrayAPPLE");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDrawElementArrayATI(GLenum,GLsizei){printMissingFunctionError("glDrawElementArrayATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDrawElementsBaseVertex(GLenum,GLsizei,GLenum,const void*,GLint){printMissingFunctionError("glDrawElementsBaseVertex");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDrawElements(GLenum,GLsizei,GLenum,const GLvoid*){printMissingFunctionError("glDrawElements");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDrawElementsIndirect(GLenum,GLenum,const void*){printMissingFunctionError("glDrawElementsIndirect");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDrawElementsInstancedARB(GLenum,GLsizei,GLenum,const void*,GLsizei){printMissingFunctionError("glDrawElementsInstancedARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDrawElementsInstancedBaseInstance(GLenum,GLsizei,GLenum,const void*,GLsizei,GLuint){printMissingFunctionError("glDrawElementsInstancedBaseInstance");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDrawElementsInstancedBaseVertexBaseInstance(GLenum,GLsizei,GLenum,const void*,GLsizei,GLint,GLuint){printMissingFunctionError("glDrawElementsInstancedBaseVertexBaseInstance");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDrawElementsInstancedBaseVertex(GLenum,GLsizei,GLenum,const void*,GLsizei,GLint){printMissingFunctionError("glDrawElementsInstancedBaseVertex");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDrawElementsInstancedEXT(GLenum,GLsizei,GLenum,const void*,GLsizei){printMissingFunctionError("glDrawElementsInstancedEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDrawElementsInstanced(GLenum,GLsizei,GLenum,const void*,GLsizei){printMissingFunctionError("glDrawElementsInstanced");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDrawMeshArraysSUN(GLenum,GLint,GLsizei,GLsizei){printMissingFunctionError("glDrawMeshArraysSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDrawPixels(GLsizei,GLsizei,GLenum,GLenum,const GLvoid*){printMissingFunctionError("glDrawPixels");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDrawRangeElementArrayAPPLE(GLenum,GLuint,GLuint,GLint,GLsizei){printMissingFunctionError("glDrawRangeElementArrayAPPLE");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDrawRangeElementArrayATI(GLenum,GLuint,GLuint,GLsizei){printMissingFunctionError("glDrawRangeElementArrayATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDrawRangeElementsBaseVertex(GLenum,GLuint,GLuint,GLsizei,GLenum,const void*,GLint){printMissingFunctionError("glDrawRangeElementsBaseVertex");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDrawRangeElementsEXT(GLenum,GLuint,GLuint,GLsizei,GLenum,const void*){printMissingFunctionError("glDrawRangeElementsEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDrawRangeElements(GLenum,GLuint,GLuint,GLsizei,GLenum,const GLvoid*){printMissingFunctionError("glDrawRangeElements");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDrawTextureNV(GLuint,GLuint,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glDrawTextureNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDrawTransformFeedback(GLenum,GLuint){printMissingFunctionError("glDrawTransformFeedback");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDrawTransformFeedbackInstanced(GLenum,GLuint,GLsizei){printMissingFunctionError("glDrawTransformFeedbackInstanced");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDrawTransformFeedbackNV(GLenum,GLuint){printMissingFunctionError("glDrawTransformFeedbackNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDrawTransformFeedbackStream(GLenum,GLuint,GLuint){printMissingFunctionError("glDrawTransformFeedbackStream");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglDrawTransformFeedbackStreamInstanced(GLenum,GLuint,GLuint,GLsizei){printMissingFunctionError("glDrawTransformFeedbackStreamInstanced");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEdgeFlagFormatNV(GLsizei){printMissingFunctionError("glEdgeFlagFormatNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEdgeFlag(GLboolean){printMissingFunctionError("glEdgeFlag");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEdgeFlagPointerEXT(GLsizei,GLsizei,const GLboolean*){printMissingFunctionError("glEdgeFlagPointerEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEdgeFlagPointer(GLsizei,const GLvoid*){printMissingFunctionError("glEdgeFlagPointer");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEdgeFlagPointerListIBM(GLint,const GLboolean**,GLint){printMissingFunctionError("glEdgeFlagPointerListIBM");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEdgeFlagv(const GLboolean*){printMissingFunctionError("glEdgeFlagv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEGLImageTargetRenderbufferStorageOES(GLenum,GLeglImageOES){printMissingFunctionError("glEGLImageTargetRenderbufferStorageOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEGLImageTargetTexture2DOES(GLenum,GLeglImageOES){printMissingFunctionError("glEGLImageTargetTexture2DOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglElementPointerAPPLE(GLenum,const void*){printMissingFunctionError("glElementPointerAPPLE");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglElementPointerATI(GLenum,const void*){printMissingFunctionError("glElementPointerATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEnableClientState(GLenum){printMissingFunctionError("glEnableClientState");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEnableClientStateiEXT(GLenum,GLuint){printMissingFunctionError("glEnableClientStateiEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEnableClientStateIndexedEXT(GLenum,GLuint){printMissingFunctionError("glEnableClientStateIndexedEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEnable(GLenum){printMissingFunctionError("glEnable");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEnablei(GLenum,GLuint){printMissingFunctionError("glEnablei");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEnableIndexedEXT(GLenum,GLuint){printMissingFunctionError("glEnableIndexedEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEnableVariantClientStateEXT(GLuint){printMissingFunctionError("glEnableVariantClientStateEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEnableVertexArrayAttribEXT(GLuint,GLuint){printMissingFunctionError("glEnableVertexArrayAttribEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEnableVertexArrayAttrib(GLuint,GLuint){printMissingFunctionError("glEnableVertexArrayAttrib");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEnableVertexArrayEXT(GLuint,GLenum){printMissingFunctionError("glEnableVertexArrayEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEnableVertexAttribAPPLE(GLuint,GLenum){printMissingFunctionError("glEnableVertexAttribAPPLE");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEnableVertexAttribArrayARB(GLuint){printMissingFunctionError("glEnableVertexAttribArrayARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEnableVertexAttribArray(GLuint){printMissingFunctionError("glEnableVertexAttribArray");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEnd(){printMissingFunctionError("glEnd");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEndConditionalRender(){printMissingFunctionError("glEndConditionalRender");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEndConditionalRenderNV(){printMissingFunctionError("glEndConditionalRenderNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEndConditionalRenderNVX(){printMissingFunctionError("glEndConditionalRenderNVX");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEndFragmentShaderATI(){printMissingFunctionError("glEndFragmentShaderATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEndList(){printMissingFunctionError("glEndList");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEndOcclusionQueryNV(){printMissingFunctionError("glEndOcclusionQueryNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEndPerfMonitorAMD(GLuint){printMissingFunctionError("glEndPerfMonitorAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEndPerfQueryINTEL(GLuint){printMissingFunctionError("glEndPerfQueryINTEL");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEndQueryARB(GLenum){printMissingFunctionError("glEndQueryARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEndQuery(GLenum){printMissingFunctionError("glEndQuery");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEndQueryIndexed(GLenum,GLuint){printMissingFunctionError("glEndQueryIndexed");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEndTransformFeedback(){printMissingFunctionError("glEndTransformFeedback");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEndTransformFeedbackEXT(){printMissingFunctionError("glEndTransformFeedbackEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEndTransformFeedbackNV(){printMissingFunctionError("glEndTransformFeedbackNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEndVertexShaderEXT(){printMissingFunctionError("glEndVertexShaderEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEndVideoCaptureNV(GLuint){printMissingFunctionError("glEndVideoCaptureNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEvalCoord1d(GLdouble){printMissingFunctionError("glEvalCoord1d");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEvalCoord1dv(const GLdouble*){printMissingFunctionError("glEvalCoord1dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEvalCoord1f(GLfloat){printMissingFunctionError("glEvalCoord1f");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEvalCoord1fv(const GLfloat*){printMissingFunctionError("glEvalCoord1fv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEvalCoord1xOES(GLfixed){printMissingFunctionError("glEvalCoord1xOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEvalCoord1xvOES(const GLfixed*){printMissingFunctionError("glEvalCoord1xvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEvalCoord2d(GLdouble,GLdouble){printMissingFunctionError("glEvalCoord2d");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEvalCoord2dv(const GLdouble*){printMissingFunctionError("glEvalCoord2dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEvalCoord2f(GLfloat,GLfloat){printMissingFunctionError("glEvalCoord2f");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEvalCoord2fv(const GLfloat*){printMissingFunctionError("glEvalCoord2fv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEvalCoord2xOES(GLfixed,GLfixed){printMissingFunctionError("glEvalCoord2xOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEvalCoord2xvOES(const GLfixed*){printMissingFunctionError("glEvalCoord2xvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEvalMapsNV(GLenum,GLenum){printMissingFunctionError("glEvalMapsNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEvalMesh1(GLenum,GLint,GLint){printMissingFunctionError("glEvalMesh1");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEvalMesh2(GLenum,GLint,GLint,GLint,GLint){printMissingFunctionError("glEvalMesh2");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEvalPoint1(GLint){printMissingFunctionError("glEvalPoint1");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEvalPoint2(GLint,GLint){printMissingFunctionError("glEvalPoint2");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglEvaluateDepthValuesARB(){printMissingFunctionError("glEvaluateDepthValuesARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglExecuteProgramNV(GLenum,GLuint,const GLfloat*){printMissingFunctionError("glExecuteProgramNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglExtractComponentEXT(GLuint,GLuint,GLuint){printMissingFunctionError("glExtractComponentEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFeedbackBuffer(GLsizei,GLenum,GLfloat*){printMissingFunctionError("glFeedbackBuffer");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFeedbackBufferxOES(GLsizei,GLenum,const GLfixed*){printMissingFunctionError("glFeedbackBufferxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFinalCombinerInputNV(GLenum,GLenum,GLenum,GLenum){printMissingFunctionError("glFinalCombinerInputNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFinish(){printMissingFunctionError("glFinish");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFinishFenceAPPLE(GLuint){printMissingFunctionError("glFinishFenceAPPLE");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFinishFenceNV(GLuint){printMissingFunctionError("glFinishFenceNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFinishObjectAPPLE(GLenum,GLint){printMissingFunctionError("glFinishObjectAPPLE");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFinishTextureSUNX(){printMissingFunctionError("glFinishTextureSUNX");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFlush(){printMissingFunctionError("glFlush");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFlushMappedBufferRangeAPPLE(GLenum,GLintptr,GLsizeiptr){printMissingFunctionError("glFlushMappedBufferRangeAPPLE");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFlushMappedBufferRange(GLenum,GLintptr,GLsizeiptr){printMissingFunctionError("glFlushMappedBufferRange");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFlushMappedNamedBufferRangeEXT(GLuint,GLintptr,GLsizeiptr){printMissingFunctionError("glFlushMappedNamedBufferRangeEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFlushMappedNamedBufferRange(GLuint,GLintptr,GLsizeiptr){printMissingFunctionError("glFlushMappedNamedBufferRange");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFlushPixelDataRangeNV(GLenum){printMissingFunctionError("glFlushPixelDataRangeNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFlushRasterSGIX(){printMissingFunctionError("glFlushRasterSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFlushStaticDataIBM(GLenum){printMissingFunctionError("glFlushStaticDataIBM");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFlushVertexArrayRangeAPPLE(GLsizei,void*){printMissingFunctionError("glFlushVertexArrayRangeAPPLE");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFlushVertexArrayRangeNV(){printMissingFunctionError("glFlushVertexArrayRangeNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFogCoorddEXT(GLdouble){printMissingFunctionError("glFogCoorddEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFogCoordd(GLdouble){printMissingFunctionError("glFogCoordd");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFogCoorddv(const GLdouble*){printMissingFunctionError("glFogCoorddv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFogCoorddvEXT(const GLdouble*){printMissingFunctionError("glFogCoorddvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFogCoordfEXT(GLfloat){printMissingFunctionError("glFogCoordfEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFogCoordf(GLfloat){printMissingFunctionError("glFogCoordf");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFogCoordFormatNV(GLenum,GLsizei){printMissingFunctionError("glFogCoordFormatNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFogCoordfv(const GLfloat*){printMissingFunctionError("glFogCoordfv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFogCoordfvEXT(const GLfloat*){printMissingFunctionError("glFogCoordfvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFogCoordhNV(GLhalfNV){printMissingFunctionError("glFogCoordhNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFogCoordhvNV(const GLhalfNV*){printMissingFunctionError("glFogCoordhvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFogCoordPointerEXT(GLenum,GLsizei,const void*){printMissingFunctionError("glFogCoordPointerEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFogCoordPointer(GLenum,GLsizei,const void*){printMissingFunctionError("glFogCoordPointer");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFogCoordPointerListIBM(GLenum,GLint,const void**,GLint){printMissingFunctionError("glFogCoordPointerListIBM");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFogf(GLenum,GLfloat){printMissingFunctionError("glFogf");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFogFuncSGIS(GLsizei,const GLfloat*){printMissingFunctionError("glFogFuncSGIS");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFogfv(GLenum,const GLfloat*){printMissingFunctionError("glFogfv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFogi(GLenum,GLint){printMissingFunctionError("glFogi");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFogiv(GLenum,const GLint*){printMissingFunctionError("glFogiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFogxOES(GLenum,GLfixed){printMissingFunctionError("glFogxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFogxvOES(GLenum,const GLfixed*){printMissingFunctionError("glFogxvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFragmentColorMaterialSGIX(GLenum,GLenum){printMissingFunctionError("glFragmentColorMaterialSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFragmentCoverageColorNV(GLuint){printMissingFunctionError("glFragmentCoverageColorNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFragmentLightfSGIX(GLenum,GLenum,GLfloat){printMissingFunctionError("glFragmentLightfSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFragmentLightfvSGIX(GLenum,GLenum,const GLfloat*){printMissingFunctionError("glFragmentLightfvSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFragmentLightiSGIX(GLenum,GLenum,GLint){printMissingFunctionError("glFragmentLightiSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFragmentLightivSGIX(GLenum,GLenum,const GLint*){printMissingFunctionError("glFragmentLightivSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFragmentLightModelfSGIX(GLenum,GLfloat){printMissingFunctionError("glFragmentLightModelfSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFragmentLightModelfvSGIX(GLenum,const GLfloat*){printMissingFunctionError("glFragmentLightModelfvSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFragmentLightModeliSGIX(GLenum,GLint){printMissingFunctionError("glFragmentLightModeliSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFragmentLightModelivSGIX(GLenum,const GLint*){printMissingFunctionError("glFragmentLightModelivSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFragmentMaterialfSGIX(GLenum,GLenum,GLfloat){printMissingFunctionError("glFragmentMaterialfSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFragmentMaterialfvSGIX(GLenum,GLenum,const GLfloat*){printMissingFunctionError("glFragmentMaterialfvSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFragmentMaterialiSGIX(GLenum,GLenum,GLint){printMissingFunctionError("glFragmentMaterialiSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFragmentMaterialivSGIX(GLenum,GLenum,const GLint*){printMissingFunctionError("glFragmentMaterialivSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFramebufferDrawBufferEXT(GLuint,GLenum){printMissingFunctionError("glFramebufferDrawBufferEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFramebufferDrawBuffersEXT(GLuint,GLsizei,const GLenum*){printMissingFunctionError("glFramebufferDrawBuffersEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFramebufferParameteri(GLenum,GLenum,GLint){printMissingFunctionError("glFramebufferParameteri");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFramebufferReadBufferEXT(GLuint,GLenum){printMissingFunctionError("glFramebufferReadBufferEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFramebufferRenderbufferEXT(GLenum,GLenum,GLenum,GLuint){printMissingFunctionError("glFramebufferRenderbufferEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFramebufferRenderbuffer(GLenum,GLenum,GLenum,GLuint){printMissingFunctionError("glFramebufferRenderbuffer");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFramebufferSampleLocationsfvARB(GLenum,GLuint,GLsizei,const GLfloat*){printMissingFunctionError("glFramebufferSampleLocationsfvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFramebufferSampleLocationsfvNV(GLenum,GLuint,GLsizei,const GLfloat*){printMissingFunctionError("glFramebufferSampleLocationsfvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFramebufferTexture1DEXT(GLenum,GLenum,GLenum,GLuint,GLint){printMissingFunctionError("glFramebufferTexture1DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFramebufferTexture1D(GLenum,GLenum,GLenum,GLuint,GLint){printMissingFunctionError("glFramebufferTexture1D");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFramebufferTexture2DEXT(GLenum,GLenum,GLenum,GLuint,GLint){printMissingFunctionError("glFramebufferTexture2DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFramebufferTexture2D(GLenum,GLenum,GLenum,GLuint,GLint){printMissingFunctionError("glFramebufferTexture2D");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFramebufferTexture3DEXT(GLenum,GLenum,GLenum,GLuint,GLint,GLint){printMissingFunctionError("glFramebufferTexture3DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFramebufferTexture3D(GLenum,GLenum,GLenum,GLuint,GLint,GLint){printMissingFunctionError("glFramebufferTexture3D");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFramebufferTextureARB(GLenum,GLenum,GLuint,GLint){printMissingFunctionError("glFramebufferTextureARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFramebufferTextureEXT(GLenum,GLenum,GLuint,GLint){printMissingFunctionError("glFramebufferTextureEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFramebufferTextureFaceARB(GLenum,GLenum,GLuint,GLint,GLenum){printMissingFunctionError("glFramebufferTextureFaceARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFramebufferTextureFaceEXT(GLenum,GLenum,GLuint,GLint,GLenum){printMissingFunctionError("glFramebufferTextureFaceEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFramebufferTexture(GLenum,GLenum,GLuint,GLint){printMissingFunctionError("glFramebufferTexture");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFramebufferTextureLayerARB(GLenum,GLenum,GLuint,GLint,GLint){printMissingFunctionError("glFramebufferTextureLayerARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFramebufferTextureLayerEXT(GLenum,GLenum,GLuint,GLint,GLint){printMissingFunctionError("glFramebufferTextureLayerEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFramebufferTextureLayer(GLenum,GLenum,GLuint,GLint,GLint){printMissingFunctionError("glFramebufferTextureLayer");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFramebufferTextureMultiviewOVR(GLenum,GLenum,GLuint,GLint,GLint,GLsizei){printMissingFunctionError("glFramebufferTextureMultiviewOVR");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFrameTerminatorGREMEDY(){printMissingFunctionError("glFrameTerminatorGREMEDY");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFrameZoomSGIX(GLint){printMissingFunctionError("glFrameZoomSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFreeObjectBufferATI(GLuint){printMissingFunctionError("glFreeObjectBufferATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFrontFace(GLenum){printMissingFunctionError("glFrontFace");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFrustumfOES(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glFrustumfOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFrustum(GLdouble,GLdouble,GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glFrustum");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglFrustumxOES(GLfixed,GLfixed,GLfixed,GLfixed,GLfixed,GLfixed){printMissingFunctionError("glFrustumxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGenBuffersARB(GLsizei,GLuint*){printMissingFunctionError("glGenBuffersARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGenBuffers(GLsizei,GLuint*){printMissingFunctionError("glGenBuffers");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGenerateMipmapEXT(GLenum){printMissingFunctionError("glGenerateMipmapEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGenerateMipmap(GLenum){printMissingFunctionError("glGenerateMipmap");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGenerateMultiTexMipmapEXT(GLenum,GLenum){printMissingFunctionError("glGenerateMultiTexMipmapEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGenerateTextureMipmapEXT(GLuint,GLenum){printMissingFunctionError("glGenerateTextureMipmapEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGenerateTextureMipmap(GLuint){printMissingFunctionError("glGenerateTextureMipmap");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGenFencesAPPLE(GLsizei,GLuint*){printMissingFunctionError("glGenFencesAPPLE");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGenFencesNV(GLsizei,GLuint*){printMissingFunctionError("glGenFencesNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGenFramebuffersEXT(GLsizei,GLuint*){printMissingFunctionError("glGenFramebuffersEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGenFramebuffers(GLsizei,GLuint*){printMissingFunctionError("glGenFramebuffers");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGenNamesAMD(GLenum,GLuint,GLuint*){printMissingFunctionError("glGenNamesAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGenOcclusionQueriesNV(GLsizei,GLuint*){printMissingFunctionError("glGenOcclusionQueriesNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGenPerfMonitorsAMD(GLsizei,GLuint*){printMissingFunctionError("glGenPerfMonitorsAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGenProgramPipelines(GLsizei,GLuint*){printMissingFunctionError("glGenProgramPipelines");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGenProgramsARB(GLsizei,GLuint*){printMissingFunctionError("glGenProgramsARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGenProgramsNV(GLsizei,GLuint*){printMissingFunctionError("glGenProgramsNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGenQueriesARB(GLsizei,GLuint*){printMissingFunctionError("glGenQueriesARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGenQueries(GLsizei,GLuint*){printMissingFunctionError("glGenQueries");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGenRenderbuffersEXT(GLsizei,GLuint*){printMissingFunctionError("glGenRenderbuffersEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGenRenderbuffers(GLsizei,GLuint*){printMissingFunctionError("glGenRenderbuffers");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGenSamplers(GLsizei,GLuint*){printMissingFunctionError("glGenSamplers");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGenTexturesEXT(GLsizei,GLuint*){printMissingFunctionError("glGenTexturesEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGenTextures(GLsizei,GLuint*){printMissingFunctionError("glGenTextures");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGenTransformFeedbacks(GLsizei,GLuint*){printMissingFunctionError("glGenTransformFeedbacks");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGenTransformFeedbacksNV(GLsizei,GLuint*){printMissingFunctionError("glGenTransformFeedbacksNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGenVertexArraysAPPLE(GLsizei,GLuint*){printMissingFunctionError("glGenVertexArraysAPPLE");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGenVertexArrays(GLsizei,GLuint*){printMissingFunctionError("glGenVertexArrays");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetActiveAtomicCounterBufferiv(GLuint,GLuint,GLenum,GLint*){printMissingFunctionError("glGetActiveAtomicCounterBufferiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetActiveAttribARB(GLhandleARB,GLuint,GLsizei,GLsizei*,GLint*,GLenum*,GLcharARB*){printMissingFunctionError("glGetActiveAttribARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetActiveAttrib(GLuint,GLuint,GLsizei,GLsizei*,GLint*,GLenum*,GLchar*){printMissingFunctionError("glGetActiveAttrib");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetActiveSubroutineName(GLuint,GLenum,GLuint,GLsizei,GLsizei*,GLchar*){printMissingFunctionError("glGetActiveSubroutineName");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetActiveSubroutineUniformiv(GLuint,GLenum,GLuint,GLenum,GLint*){printMissingFunctionError("glGetActiveSubroutineUniformiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetActiveSubroutineUniformName(GLuint,GLenum,GLuint,GLsizei,GLsizei*,GLchar*){printMissingFunctionError("glGetActiveSubroutineUniformName");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetActiveUniformARB(GLhandleARB,GLuint,GLsizei,GLsizei*,GLint*,GLenum*,GLcharARB*){printMissingFunctionError("glGetActiveUniformARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetActiveUniformBlockiv(GLuint,GLuint,GLenum,GLint*){printMissingFunctionError("glGetActiveUniformBlockiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetActiveUniformBlockName(GLuint,GLuint,GLsizei,GLsizei*,GLchar*){printMissingFunctionError("glGetActiveUniformBlockName");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetActiveUniform(GLuint,GLuint,GLsizei,GLsizei*,GLint*,GLenum*,GLchar*){printMissingFunctionError("glGetActiveUniform");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetActiveUniformName(GLuint,GLuint,GLsizei,GLsizei*,GLchar*){printMissingFunctionError("glGetActiveUniformName");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetActiveUniformsiv(GLuint,GLsizei,const GLuint*,GLenum,GLint*){printMissingFunctionError("glGetActiveUniformsiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetActiveVaryingNV(GLuint,GLuint,GLsizei,GLsizei*,GLsizei*,GLenum*,GLchar*){printMissingFunctionError("glGetActiveVaryingNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetArrayObjectfvATI(GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetArrayObjectfvATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetArrayObjectivATI(GLenum,GLenum,GLint*){printMissingFunctionError("glGetArrayObjectivATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetAttachedObjectsARB(GLhandleARB,GLsizei,GLsizei*,GLhandleARB*){printMissingFunctionError("glGetAttachedObjectsARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetAttachedShaders(GLuint,GLsizei,GLsizei*,GLuint*){printMissingFunctionError("glGetAttachedShaders");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetBooleanIndexedvEXT(GLenum,GLuint,GLboolean*){printMissingFunctionError("glGetBooleanIndexedvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetBooleani_v(GLenum,GLuint,GLboolean*){printMissingFunctionError("glGetBooleani_v");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetBooleanv(GLenum,GLboolean*){printMissingFunctionError("glGetBooleanv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetBufferParameteri64v(GLenum,GLenum,GLint64*){printMissingFunctionError("glGetBufferParameteri64v");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetBufferParameterivARB(GLenum,GLenum,GLint*){printMissingFunctionError("glGetBufferParameterivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetBufferParameteriv(GLenum,GLenum,GLint*){printMissingFunctionError("glGetBufferParameteriv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetBufferParameterui64vNV(GLenum,GLenum,GLuint64EXT*){printMissingFunctionError("glGetBufferParameterui64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetBufferPointervARB(GLenum,GLenum,void**){printMissingFunctionError("glGetBufferPointervARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetBufferPointerv(GLenum,GLenum,void**){printMissingFunctionError("glGetBufferPointerv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetBufferSubDataARB(GLenum,GLintptrARB,GLsizeiptrARB,void*){printMissingFunctionError("glGetBufferSubDataARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetBufferSubData(GLenum,GLintptr,GLsizeiptr,void*){printMissingFunctionError("glGetBufferSubData");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetClipPlanefOES(GLenum,GLfloat*){printMissingFunctionError("glGetClipPlanefOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetClipPlane(GLenum,GLdouble*){printMissingFunctionError("glGetClipPlane");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetClipPlanexOES(GLenum,GLfixed*){printMissingFunctionError("glGetClipPlanexOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetColorTableEXT(GLenum,GLenum,GLenum,void*){printMissingFunctionError("glGetColorTableEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetColorTable(GLenum,GLenum,GLenum,GLvoid*){printMissingFunctionError("glGetColorTable");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetColorTableParameterfvEXT(GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetColorTableParameterfvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetColorTableParameterfv(GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetColorTableParameterfv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetColorTableParameterfvSGI(GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetColorTableParameterfvSGI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetColorTableParameterivEXT(GLenum,GLenum,GLint*){printMissingFunctionError("glGetColorTableParameterivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetColorTableParameteriv(GLenum,GLenum,GLint*){printMissingFunctionError("glGetColorTableParameteriv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetColorTableParameterivSGI(GLenum,GLenum,GLint*){printMissingFunctionError("glGetColorTableParameterivSGI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetColorTableSGI(GLenum,GLenum,GLenum,void*){printMissingFunctionError("glGetColorTableSGI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetCombinerInputParameterfvNV(GLenum,GLenum,GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetCombinerInputParameterfvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetCombinerInputParameterivNV(GLenum,GLenum,GLenum,GLenum,GLint*){printMissingFunctionError("glGetCombinerInputParameterivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetCombinerOutputParameterfvNV(GLenum,GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetCombinerOutputParameterfvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetCombinerOutputParameterivNV(GLenum,GLenum,GLenum,GLint*){printMissingFunctionError("glGetCombinerOutputParameterivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetCombinerStageParameterfvNV(GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetCombinerStageParameterfvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetCompressedMultiTexImageEXT(GLenum,GLenum,GLint,void*){printMissingFunctionError("glGetCompressedMultiTexImageEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetCompressedTexImageARB(GLenum,GLint,void*){printMissingFunctionError("glGetCompressedTexImageARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetCompressedTexImage(GLenum,GLint,GLvoid*){printMissingFunctionError("glGetCompressedTexImage");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetCompressedTextureImageEXT(GLuint,GLenum,GLint,void*){printMissingFunctionError("glGetCompressedTextureImageEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetCompressedTextureImage(GLuint,GLint,GLsizei,void*){printMissingFunctionError("glGetCompressedTextureImage");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetCompressedTextureSubImage(GLuint,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLsizei,void*){printMissingFunctionError("glGetCompressedTextureSubImage");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetConvolutionFilterEXT(GLenum,GLenum,GLenum,void*){printMissingFunctionError("glGetConvolutionFilterEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetConvolutionFilter(GLenum,GLenum,GLenum,GLvoid*){printMissingFunctionError("glGetConvolutionFilter");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetConvolutionParameterfvEXT(GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetConvolutionParameterfvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetConvolutionParameterfv(GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetConvolutionParameterfv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetConvolutionParameterivEXT(GLenum,GLenum,GLint*){printMissingFunctionError("glGetConvolutionParameterivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetConvolutionParameteriv(GLenum,GLenum,GLint*){printMissingFunctionError("glGetConvolutionParameteriv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetConvolutionParameterxvOES(GLenum,GLenum,GLfixed*){printMissingFunctionError("glGetConvolutionParameterxvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetCoverageModulationTableNV(GLsizei,GLfloat*){printMissingFunctionError("glGetCoverageModulationTableNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetDetailTexFuncSGIS(GLenum,GLfloat*){printMissingFunctionError("glGetDetailTexFuncSGIS");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetDoubleIndexedvEXT(GLenum,GLuint,GLdouble*){printMissingFunctionError("glGetDoubleIndexedvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetDoublei_vEXT(GLenum,GLuint,GLdouble*){printMissingFunctionError("glGetDoublei_vEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetDoublei_v(GLenum,GLuint,GLdouble*){printMissingFunctionError("glGetDoublei_v");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetDoublev(GLenum,GLdouble*){printMissingFunctionError("glGetDoublev");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetFenceivNV(GLuint,GLenum,GLint*){printMissingFunctionError("glGetFenceivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetFinalCombinerInputParameterfvNV(GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetFinalCombinerInputParameterfvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetFinalCombinerInputParameterivNV(GLenum,GLenum,GLint*){printMissingFunctionError("glGetFinalCombinerInputParameterivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetFirstPerfQueryIdINTEL(GLuint*){printMissingFunctionError("glGetFirstPerfQueryIdINTEL");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetFixedvOES(GLenum,GLfixed*){printMissingFunctionError("glGetFixedvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetFloatIndexedvEXT(GLenum,GLuint,GLfloat*){printMissingFunctionError("glGetFloatIndexedvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetFloati_vEXT(GLenum,GLuint,GLfloat*){printMissingFunctionError("glGetFloati_vEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetFloati_v(GLenum,GLuint,GLfloat*){printMissingFunctionError("glGetFloati_v");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetFloatv(GLenum,GLfloat*){printMissingFunctionError("glGetFloatv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetFogFuncSGIS(GLfloat*){printMissingFunctionError("glGetFogFuncSGIS");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetFragmentLightfvSGIX(GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetFragmentLightfvSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetFragmentLightivSGIX(GLenum,GLenum,GLint*){printMissingFunctionError("glGetFragmentLightivSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetFragmentMaterialfvSGIX(GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetFragmentMaterialfvSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetFragmentMaterialivSGIX(GLenum,GLenum,GLint*){printMissingFunctionError("glGetFragmentMaterialivSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetFramebufferAttachmentParameterivEXT(GLenum,GLenum,GLenum,GLint*){printMissingFunctionError("glGetFramebufferAttachmentParameterivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetFramebufferAttachmentParameteriv(GLenum,GLenum,GLenum,GLint*){printMissingFunctionError("glGetFramebufferAttachmentParameteriv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetFramebufferParameterivEXT(GLuint,GLenum,GLint*){printMissingFunctionError("glGetFramebufferParameterivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetFramebufferParameteriv(GLenum,GLenum,GLint*){printMissingFunctionError("glGetFramebufferParameteriv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetHistogramEXT(GLenum,GLboolean,GLenum,GLenum,void*){printMissingFunctionError("glGetHistogramEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetHistogram(GLenum,GLboolean,GLenum,GLenum,GLvoid*){printMissingFunctionError("glGetHistogram");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetHistogramParameterfvEXT(GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetHistogramParameterfvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetHistogramParameterfv(GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetHistogramParameterfv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetHistogramParameterivEXT(GLenum,GLenum,GLint*){printMissingFunctionError("glGetHistogramParameterivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetHistogramParameteriv(GLenum,GLenum,GLint*){printMissingFunctionError("glGetHistogramParameteriv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetHistogramParameterxvOES(GLenum,GLenum,GLfixed*){printMissingFunctionError("glGetHistogramParameterxvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetImageTransformParameterfvHP(GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetImageTransformParameterfvHP");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetImageTransformParameterivHP(GLenum,GLenum,GLint*){printMissingFunctionError("glGetImageTransformParameterivHP");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetInfoLogARB(GLhandleARB,GLsizei,GLsizei*,GLcharARB*){printMissingFunctionError("glGetInfoLogARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetInteger64i_v(GLenum,GLuint,GLint64*){printMissingFunctionError("glGetInteger64i_v");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetInteger64v(GLenum,GLint64*){printMissingFunctionError("glGetInteger64v");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetIntegerIndexedvEXT(GLenum,GLuint,GLint*){printMissingFunctionError("glGetIntegerIndexedvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetIntegeri_v(GLenum,GLuint,GLint*){printMissingFunctionError("glGetIntegeri_v");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetIntegerui64i_vNV(GLenum,GLuint,GLuint64EXT*){printMissingFunctionError("glGetIntegerui64i_vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetIntegerui64vNV(GLenum,GLuint64EXT*){printMissingFunctionError("glGetIntegerui64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetIntegerv(GLenum,GLint*){printMissingFunctionError("glGetIntegerv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetInternalformati64v(GLenum,GLenum,GLenum,GLsizei,GLint64*){printMissingFunctionError("glGetInternalformati64v");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetInternalformativ(GLenum,GLenum,GLenum,GLsizei,GLint*){printMissingFunctionError("glGetInternalformativ");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetInternalformatSampleivNV(GLenum,GLenum,GLsizei,GLenum,GLsizei,GLint*){printMissingFunctionError("glGetInternalformatSampleivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetInvariantBooleanvEXT(GLuint,GLenum,GLboolean*){printMissingFunctionError("glGetInvariantBooleanvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetInvariantFloatvEXT(GLuint,GLenum,GLfloat*){printMissingFunctionError("glGetInvariantFloatvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetInvariantIntegervEXT(GLuint,GLenum,GLint*){printMissingFunctionError("glGetInvariantIntegervEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetLightfv(GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetLightfv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetLightiv(GLenum,GLenum,GLint*){printMissingFunctionError("glGetLightiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetLightxOES(GLenum,GLenum,GLfixed*){printMissingFunctionError("glGetLightxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetListParameterfvSGIX(GLuint,GLenum,GLfloat*){printMissingFunctionError("glGetListParameterfvSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetListParameterivSGIX(GLuint,GLenum,GLint*){printMissingFunctionError("glGetListParameterivSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetLocalConstantBooleanvEXT(GLuint,GLenum,GLboolean*){printMissingFunctionError("glGetLocalConstantBooleanvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetLocalConstantFloatvEXT(GLuint,GLenum,GLfloat*){printMissingFunctionError("glGetLocalConstantFloatvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetLocalConstantIntegervEXT(GLuint,GLenum,GLint*){printMissingFunctionError("glGetLocalConstantIntegervEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetMapAttribParameterfvNV(GLenum,GLuint,GLenum,GLfloat*){printMissingFunctionError("glGetMapAttribParameterfvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetMapAttribParameterivNV(GLenum,GLuint,GLenum,GLint*){printMissingFunctionError("glGetMapAttribParameterivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetMapControlPointsNV(GLenum,GLuint,GLenum,GLsizei,GLsizei,GLboolean,void*){printMissingFunctionError("glGetMapControlPointsNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetMapdv(GLenum,GLenum,GLdouble*){printMissingFunctionError("glGetMapdv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetMapfv(GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetMapfv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetMapiv(GLenum,GLenum,GLint*){printMissingFunctionError("glGetMapiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetMapParameterfvNV(GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetMapParameterfvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetMapParameterivNV(GLenum,GLenum,GLint*){printMissingFunctionError("glGetMapParameterivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetMapxvOES(GLenum,GLenum,GLfixed*){printMissingFunctionError("glGetMapxvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetMaterialfv(GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetMaterialfv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetMaterialiv(GLenum,GLenum,GLint*){printMissingFunctionError("glGetMaterialiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetMaterialxOES(GLenum,GLenum,GLfixed){printMissingFunctionError("glGetMaterialxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetMinmaxEXT(GLenum,GLboolean,GLenum,GLenum,void*){printMissingFunctionError("glGetMinmaxEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetMinmax(GLenum,GLboolean,GLenum,GLenum,GLvoid*){printMissingFunctionError("glGetMinmax");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetMinmaxParameterfvEXT(GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetMinmaxParameterfvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetMinmaxParameterfv(GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetMinmaxParameterfv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetMinmaxParameterivEXT(GLenum,GLenum,GLint*){printMissingFunctionError("glGetMinmaxParameterivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetMinmaxParameteriv(GLenum,GLenum,GLint*){printMissingFunctionError("glGetMinmaxParameteriv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetMultisamplefv(GLenum,GLuint,GLfloat*){printMissingFunctionError("glGetMultisamplefv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetMultisamplefvNV(GLenum,GLuint,GLfloat*){printMissingFunctionError("glGetMultisamplefvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetMultiTexEnvfvEXT(GLenum,GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetMultiTexEnvfvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetMultiTexEnvivEXT(GLenum,GLenum,GLenum,GLint*){printMissingFunctionError("glGetMultiTexEnvivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetMultiTexGendvEXT(GLenum,GLenum,GLenum,GLdouble*){printMissingFunctionError("glGetMultiTexGendvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetMultiTexGenfvEXT(GLenum,GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetMultiTexGenfvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetMultiTexGenivEXT(GLenum,GLenum,GLenum,GLint*){printMissingFunctionError("glGetMultiTexGenivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetMultiTexImageEXT(GLenum,GLenum,GLint,GLenum,GLenum,void*){printMissingFunctionError("glGetMultiTexImageEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetMultiTexLevelParameterfvEXT(GLenum,GLenum,GLint,GLenum,GLfloat*){printMissingFunctionError("glGetMultiTexLevelParameterfvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetMultiTexLevelParameterivEXT(GLenum,GLenum,GLint,GLenum,GLint*){printMissingFunctionError("glGetMultiTexLevelParameterivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetMultiTexParameterfvEXT(GLenum,GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetMultiTexParameterfvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetMultiTexParameterIivEXT(GLenum,GLenum,GLenum,GLint*){printMissingFunctionError("glGetMultiTexParameterIivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetMultiTexParameterIuivEXT(GLenum,GLenum,GLenum,GLuint*){printMissingFunctionError("glGetMultiTexParameterIuivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetMultiTexParameterivEXT(GLenum,GLenum,GLenum,GLint*){printMissingFunctionError("glGetMultiTexParameterivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetNamedBufferParameteri64v(GLuint,GLenum,GLint64*){printMissingFunctionError("glGetNamedBufferParameteri64v");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetNamedBufferParameterivEXT(GLuint,GLenum,GLint*){printMissingFunctionError("glGetNamedBufferParameterivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetNamedBufferParameteriv(GLuint,GLenum,GLint*){printMissingFunctionError("glGetNamedBufferParameteriv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetNamedBufferParameterui64vNV(GLuint,GLenum,GLuint64EXT*){printMissingFunctionError("glGetNamedBufferParameterui64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetNamedBufferPointervEXT(GLuint,GLenum,void**){printMissingFunctionError("glGetNamedBufferPointervEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetNamedBufferPointerv(GLuint,GLenum,void**){printMissingFunctionError("glGetNamedBufferPointerv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetNamedBufferSubDataEXT(GLuint,GLintptr,GLsizeiptr,void*){printMissingFunctionError("glGetNamedBufferSubDataEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetNamedBufferSubData(GLuint,GLintptr,GLsizeiptr,void*){printMissingFunctionError("glGetNamedBufferSubData");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetNamedFramebufferAttachmentParameterivEXT(GLuint,GLenum,GLenum,GLint*){printMissingFunctionError("glGetNamedFramebufferAttachmentParameterivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetNamedFramebufferAttachmentParameteriv(GLuint,GLenum,GLenum,GLint*){printMissingFunctionError("glGetNamedFramebufferAttachmentParameteriv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetNamedFramebufferParameterivEXT(GLuint,GLenum,GLint*){printMissingFunctionError("glGetNamedFramebufferParameterivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetNamedFramebufferParameteriv(GLuint,GLenum,GLint*){printMissingFunctionError("glGetNamedFramebufferParameteriv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetNamedProgramivEXT(GLuint,GLenum,GLenum,GLint*){printMissingFunctionError("glGetNamedProgramivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetNamedProgramLocalParameterdvEXT(GLuint,GLenum,GLuint,GLdouble*){printMissingFunctionError("glGetNamedProgramLocalParameterdvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetNamedProgramLocalParameterfvEXT(GLuint,GLenum,GLuint,GLfloat*){printMissingFunctionError("glGetNamedProgramLocalParameterfvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetNamedProgramLocalParameterIivEXT(GLuint,GLenum,GLuint,GLint*){printMissingFunctionError("glGetNamedProgramLocalParameterIivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetNamedProgramLocalParameterIuivEXT(GLuint,GLenum,GLuint,GLuint*){printMissingFunctionError("glGetNamedProgramLocalParameterIuivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetNamedProgramStringEXT(GLuint,GLenum,GLenum,void*){printMissingFunctionError("glGetNamedProgramStringEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetNamedRenderbufferParameterivEXT(GLuint,GLenum,GLint*){printMissingFunctionError("glGetNamedRenderbufferParameterivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetNamedRenderbufferParameteriv(GLuint,GLenum,GLint*){printMissingFunctionError("glGetNamedRenderbufferParameteriv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetNamedStringARB(GLint,const GLchar*,GLsizei,GLint*,GLchar*){printMissingFunctionError("glGetNamedStringARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetNamedStringivARB(GLint,const GLchar*,GLenum,GLint*){printMissingFunctionError("glGetNamedStringivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetnColorTableARB(GLenum,GLenum,GLenum,GLsizei,void*){printMissingFunctionError("glGetnColorTableARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetnColorTable(GLenum,GLenum,GLenum,GLsizei,void*){printMissingFunctionError("glGetnColorTable");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetnCompressedTexImageARB(GLenum,GLint,GLsizei,void*){printMissingFunctionError("glGetnCompressedTexImageARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetnCompressedTexImage(GLenum,GLint,GLsizei,void*){printMissingFunctionError("glGetnCompressedTexImage");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetnConvolutionFilterARB(GLenum,GLenum,GLenum,GLsizei,void*){printMissingFunctionError("glGetnConvolutionFilterARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetnConvolutionFilter(GLenum,GLenum,GLenum,GLsizei,void*){printMissingFunctionError("glGetnConvolutionFilter");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetNextPerfQueryIdINTEL(GLuint,GLuint*){printMissingFunctionError("glGetNextPerfQueryIdINTEL");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetnHistogramARB(GLenum,GLboolean,GLenum,GLenum,GLsizei,void*){printMissingFunctionError("glGetnHistogramARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetnHistogram(GLenum,GLboolean,GLenum,GLenum,GLsizei,void*){printMissingFunctionError("glGetnHistogram");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetnMapdvARB(GLenum,GLenum,GLsizei,GLdouble*){printMissingFunctionError("glGetnMapdvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetnMapdv(GLenum,GLenum,GLsizei,GLdouble*){printMissingFunctionError("glGetnMapdv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetnMapfvARB(GLenum,GLenum,GLsizei,GLfloat*){printMissingFunctionError("glGetnMapfvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetnMapfv(GLenum,GLenum,GLsizei,GLfloat*){printMissingFunctionError("glGetnMapfv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetnMapivARB(GLenum,GLenum,GLsizei,GLint*){printMissingFunctionError("glGetnMapivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetnMapiv(GLenum,GLenum,GLsizei,GLint*){printMissingFunctionError("glGetnMapiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetnMinmaxARB(GLenum,GLboolean,GLenum,GLenum,GLsizei,void*){printMissingFunctionError("glGetnMinmaxARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetnMinmax(GLenum,GLboolean,GLenum,GLenum,GLsizei,void*){printMissingFunctionError("glGetnMinmax");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetnPixelMapfvARB(GLenum,GLsizei,GLfloat*){printMissingFunctionError("glGetnPixelMapfvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetnPixelMapfv(GLenum,GLsizei,GLfloat*){printMissingFunctionError("glGetnPixelMapfv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetnPixelMapuivARB(GLenum,GLsizei,GLuint*){printMissingFunctionError("glGetnPixelMapuivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetnPixelMapuiv(GLenum,GLsizei,GLuint*){printMissingFunctionError("glGetnPixelMapuiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetnPixelMapusvARB(GLenum,GLsizei,GLushort*){printMissingFunctionError("glGetnPixelMapusvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetnPixelMapusv(GLenum,GLsizei,GLushort*){printMissingFunctionError("glGetnPixelMapusv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetnPolygonStippleARB(GLsizei,GLubyte*){printMissingFunctionError("glGetnPolygonStippleARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetnPolygonStipple(GLsizei,GLubyte*){printMissingFunctionError("glGetnPolygonStipple");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetnSeparableFilterARB(GLenum,GLenum,GLenum,GLsizei,void*,GLsizei,void*,void*){printMissingFunctionError("glGetnSeparableFilterARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetnSeparableFilter(GLenum,GLenum,GLenum,GLsizei,void*,GLsizei,void*,void*){printMissingFunctionError("glGetnSeparableFilter");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetnTexImageARB(GLenum,GLint,GLenum,GLenum,GLsizei,void*){printMissingFunctionError("glGetnTexImageARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetnTexImage(GLenum,GLint,GLenum,GLenum,GLsizei,void*){printMissingFunctionError("glGetnTexImage");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetnUniformdvARB(GLuint,GLint,GLsizei,GLdouble*){printMissingFunctionError("glGetnUniformdvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetnUniformdv(GLuint,GLint,GLsizei,GLdouble*){printMissingFunctionError("glGetnUniformdv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetnUniformfvARB(GLuint,GLint,GLsizei,GLfloat*){printMissingFunctionError("glGetnUniformfvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetnUniformfv(GLuint,GLint,GLsizei,GLfloat*){printMissingFunctionError("glGetnUniformfv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetnUniformi64vARB(GLuint,GLint,GLsizei,GLint64*){printMissingFunctionError("glGetnUniformi64vARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetnUniformivARB(GLuint,GLint,GLsizei,GLint*){printMissingFunctionError("glGetnUniformivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetnUniformiv(GLuint,GLint,GLsizei,GLint*){printMissingFunctionError("glGetnUniformiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetnUniformui64vARB(GLuint,GLint,GLsizei,GLuint64*){printMissingFunctionError("glGetnUniformui64vARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetnUniformuivARB(GLuint,GLint,GLsizei,GLuint*){printMissingFunctionError("glGetnUniformuivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetnUniformuiv(GLuint,GLint,GLsizei,GLuint*){printMissingFunctionError("glGetnUniformuiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetObjectBufferfvATI(GLuint,GLenum,GLfloat*){printMissingFunctionError("glGetObjectBufferfvATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetObjectBufferivATI(GLuint,GLenum,GLint*){printMissingFunctionError("glGetObjectBufferivATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetObjectLabelEXT(GLenum,GLuint,GLsizei,GLsizei*,GLchar*){printMissingFunctionError("glGetObjectLabelEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetObjectLabel(GLenum,GLuint,GLsizei,GLsizei*,GLchar*){printMissingFunctionError("glGetObjectLabel");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetObjectParameterfvARB(GLhandleARB,GLenum,GLfloat*){printMissingFunctionError("glGetObjectParameterfvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetObjectParameterivAPPLE(GLenum,GLuint,GLenum,GLint*){printMissingFunctionError("glGetObjectParameterivAPPLE");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetObjectParameterivARB(GLhandleARB,GLenum,GLint*){printMissingFunctionError("glGetObjectParameterivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetObjectPtrLabel(const void*,GLsizei,GLsizei*,GLchar*){printMissingFunctionError("glGetObjectPtrLabel");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetOcclusionQueryivNV(GLuint,GLenum,GLint*){printMissingFunctionError("glGetOcclusionQueryivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetOcclusionQueryuivNV(GLuint,GLenum,GLuint*){printMissingFunctionError("glGetOcclusionQueryuivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetPathColorGenfvNV(GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetPathColorGenfvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetPathColorGenivNV(GLenum,GLenum,GLint*){printMissingFunctionError("glGetPathColorGenivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetPathCommandsNV(GLuint,GLubyte*){printMissingFunctionError("glGetPathCommandsNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetPathCoordsNV(GLuint,GLfloat*){printMissingFunctionError("glGetPathCoordsNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetPathDashArrayNV(GLuint,GLfloat*){printMissingFunctionError("glGetPathDashArrayNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetPathMetricRangeNV(GLbitfield,GLuint,GLsizei,GLsizei,GLfloat*){printMissingFunctionError("glGetPathMetricRangeNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetPathMetricsNV(GLbitfield,GLsizei,GLenum,const void*,GLuint,GLsizei,GLfloat*){printMissingFunctionError("glGetPathMetricsNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetPathParameterfvNV(GLuint,GLenum,GLfloat*){printMissingFunctionError("glGetPathParameterfvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetPathParameterivNV(GLuint,GLenum,GLint*){printMissingFunctionError("glGetPathParameterivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetPathSpacingNV(GLenum,GLsizei,GLenum,const void*,GLuint,GLfloat,GLfloat,GLenum,GLfloat*){printMissingFunctionError("glGetPathSpacingNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetPathTexGenfvNV(GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetPathTexGenfvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetPathTexGenivNV(GLenum,GLenum,GLint*){printMissingFunctionError("glGetPathTexGenivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetPerfCounterInfoINTEL(GLuint,GLuint,GLuint,GLchar*,GLuint,GLchar*,GLuint*,GLuint*,GLuint*,GLuint*,GLuint64*){printMissingFunctionError("glGetPerfCounterInfoINTEL");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetPerfMonitorCounterDataAMD(GLuint,GLenum,GLsizei,GLuint*,GLint*){printMissingFunctionError("glGetPerfMonitorCounterDataAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetPerfMonitorCounterInfoAMD(GLuint,GLuint,GLenum,void*){printMissingFunctionError("glGetPerfMonitorCounterInfoAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetPerfMonitorCountersAMD(GLuint,GLint*,GLint*,GLsizei,GLuint*){printMissingFunctionError("glGetPerfMonitorCountersAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetPerfMonitorCounterStringAMD(GLuint,GLuint,GLsizei,GLsizei*,GLchar*){printMissingFunctionError("glGetPerfMonitorCounterStringAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetPerfMonitorGroupsAMD(GLint*,GLsizei,GLuint*){printMissingFunctionError("glGetPerfMonitorGroupsAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetPerfMonitorGroupStringAMD(GLuint,GLsizei,GLsizei*,GLchar*){printMissingFunctionError("glGetPerfMonitorGroupStringAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetPerfQueryDataINTEL(GLuint,GLuint,GLsizei,GLvoid*,GLuint*){printMissingFunctionError("glGetPerfQueryDataINTEL");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetPerfQueryIdByNameINTEL(GLchar*,GLuint*){printMissingFunctionError("glGetPerfQueryIdByNameINTEL");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetPerfQueryInfoINTEL(GLuint,GLuint,GLchar*,GLuint*,GLuint*,GLuint*,GLuint*){printMissingFunctionError("glGetPerfQueryInfoINTEL");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetPixelMapfv(GLenum,GLfloat*){printMissingFunctionError("glGetPixelMapfv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetPixelMapuiv(GLenum,GLuint*){printMissingFunctionError("glGetPixelMapuiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetPixelMapusv(GLenum,GLushort*){printMissingFunctionError("glGetPixelMapusv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetPixelMapxv(GLenum,GLint,GLfixed*){printMissingFunctionError("glGetPixelMapxv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetPixelTexGenParameterfvSGIS(GLenum,GLfloat*){printMissingFunctionError("glGetPixelTexGenParameterfvSGIS");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetPixelTexGenParameterivSGIS(GLenum,GLint*){printMissingFunctionError("glGetPixelTexGenParameterivSGIS");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetPixelTransformParameterfvEXT(GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetPixelTransformParameterfvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetPixelTransformParameterivEXT(GLenum,GLenum,GLint*){printMissingFunctionError("glGetPixelTransformParameterivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetPointerIndexedvEXT(GLenum,GLuint,void**){printMissingFunctionError("glGetPointerIndexedvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetPointeri_vEXT(GLenum,GLuint,void**){printMissingFunctionError("glGetPointeri_vEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetPointervEXT(GLenum,void**){printMissingFunctionError("glGetPointervEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetPointerv(GLenum,GLvoid**){printMissingFunctionError("glGetPointerv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetPolygonStipple(GLubyte*){printMissingFunctionError("glGetPolygonStipple");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetProgramBinary(GLuint,GLsizei,GLsizei*,GLenum*,void*){printMissingFunctionError("glGetProgramBinary");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetProgramEnvParameterdvARB(GLenum,GLuint,GLdouble*){printMissingFunctionError("glGetProgramEnvParameterdvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetProgramEnvParameterfvARB(GLenum,GLuint,GLfloat*){printMissingFunctionError("glGetProgramEnvParameterfvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetProgramEnvParameterIivNV(GLenum,GLuint,GLint*){printMissingFunctionError("glGetProgramEnvParameterIivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetProgramEnvParameterIuivNV(GLenum,GLuint,GLuint*){printMissingFunctionError("glGetProgramEnvParameterIuivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetProgramInfoLog(GLuint,GLsizei,GLsizei*,GLchar*){printMissingFunctionError("glGetProgramInfoLog");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetProgramInterfaceiv(GLuint,GLenum,GLenum,GLint*){printMissingFunctionError("glGetProgramInterfaceiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetProgramivARB(GLenum,GLenum,GLint*){printMissingFunctionError("glGetProgramivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetProgramiv(GLuint,GLenum,GLint*){printMissingFunctionError("glGetProgramiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetProgramivNV(GLuint,GLenum,GLint*){printMissingFunctionError("glGetProgramivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetProgramLocalParameterdvARB(GLenum,GLuint,GLdouble*){printMissingFunctionError("glGetProgramLocalParameterdvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetProgramLocalParameterfvARB(GLenum,GLuint,GLfloat*){printMissingFunctionError("glGetProgramLocalParameterfvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetProgramLocalParameterIivNV(GLenum,GLuint,GLint*){printMissingFunctionError("glGetProgramLocalParameterIivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetProgramLocalParameterIuivNV(GLenum,GLuint,GLuint*){printMissingFunctionError("glGetProgramLocalParameterIuivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetProgramNamedParameterdvNV(GLuint,GLsizei,const GLubyte*,GLdouble*){printMissingFunctionError("glGetProgramNamedParameterdvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetProgramNamedParameterfvNV(GLuint,GLsizei,const GLubyte*,GLfloat*){printMissingFunctionError("glGetProgramNamedParameterfvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetProgramParameterdvNV(GLenum,GLuint,GLenum,GLdouble*){printMissingFunctionError("glGetProgramParameterdvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetProgramParameterfvNV(GLenum,GLuint,GLenum,GLfloat*){printMissingFunctionError("glGetProgramParameterfvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetProgramPipelineInfoLog(GLuint,GLsizei,GLsizei*,GLchar*){printMissingFunctionError("glGetProgramPipelineInfoLog");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetProgramPipelineiv(GLuint,GLenum,GLint*){printMissingFunctionError("glGetProgramPipelineiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetProgramResourcefvNV(GLuint,GLenum,GLuint,GLsizei,const GLenum*,GLsizei,GLsizei*,GLfloat*){printMissingFunctionError("glGetProgramResourcefvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetProgramResourceiv(GLuint,GLenum,GLuint,GLsizei,const GLenum*,GLsizei,GLsizei*,GLint*){printMissingFunctionError("glGetProgramResourceiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetProgramResourceName(GLuint,GLenum,GLuint,GLsizei,GLsizei*,GLchar*){printMissingFunctionError("glGetProgramResourceName");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetProgramStageiv(GLuint,GLenum,GLenum,GLint*){printMissingFunctionError("glGetProgramStageiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetProgramStringARB(GLenum,GLenum,void*){printMissingFunctionError("glGetProgramStringARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetProgramStringNV(GLuint,GLenum,GLubyte*){printMissingFunctionError("glGetProgramStringNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetProgramSubroutineParameteruivNV(GLenum,GLuint,GLuint*){printMissingFunctionError("glGetProgramSubroutineParameteruivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetQueryBufferObjecti64v(GLuint,GLuint,GLenum,GLintptr){printMissingFunctionError("glGetQueryBufferObjecti64v");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetQueryBufferObjectiv(GLuint,GLuint,GLenum,GLintptr){printMissingFunctionError("glGetQueryBufferObjectiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetQueryBufferObjectui64v(GLuint,GLuint,GLenum,GLintptr){printMissingFunctionError("glGetQueryBufferObjectui64v");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetQueryBufferObjectuiv(GLuint,GLuint,GLenum,GLintptr){printMissingFunctionError("glGetQueryBufferObjectuiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetQueryIndexediv(GLenum,GLuint,GLenum,GLint*){printMissingFunctionError("glGetQueryIndexediv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetQueryivARB(GLenum,GLenum,GLint*){printMissingFunctionError("glGetQueryivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetQueryiv(GLenum,GLenum,GLint*){printMissingFunctionError("glGetQueryiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetQueryObjecti64vEXT(GLuint,GLenum,GLint64*){printMissingFunctionError("glGetQueryObjecti64vEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetQueryObjecti64v(GLuint,GLenum,GLint64*){printMissingFunctionError("glGetQueryObjecti64v");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetQueryObjectivARB(GLuint,GLenum,GLint*){printMissingFunctionError("glGetQueryObjectivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetQueryObjectiv(GLuint,GLenum,GLint*){printMissingFunctionError("glGetQueryObjectiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetQueryObjectui64vEXT(GLuint,GLenum,GLuint64*){printMissingFunctionError("glGetQueryObjectui64vEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetQueryObjectui64v(GLuint,GLenum,GLuint64*){printMissingFunctionError("glGetQueryObjectui64v");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetQueryObjectuivARB(GLuint,GLenum,GLuint*){printMissingFunctionError("glGetQueryObjectuivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetQueryObjectuiv(GLuint,GLenum,GLuint*){printMissingFunctionError("glGetQueryObjectuiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetRenderbufferParameterivEXT(GLenum,GLenum,GLint*){printMissingFunctionError("glGetRenderbufferParameterivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetRenderbufferParameteriv(GLenum,GLenum,GLint*){printMissingFunctionError("glGetRenderbufferParameteriv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetSamplerParameterfv(GLuint,GLenum,GLfloat*){printMissingFunctionError("glGetSamplerParameterfv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetSamplerParameterIiv(GLuint,GLenum,GLint*){printMissingFunctionError("glGetSamplerParameterIiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetSamplerParameterIuiv(GLuint,GLenum,GLuint*){printMissingFunctionError("glGetSamplerParameterIuiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetSamplerParameteriv(GLuint,GLenum,GLint*){printMissingFunctionError("glGetSamplerParameteriv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetSeparableFilterEXT(GLenum,GLenum,GLenum,void*,void*,void*){printMissingFunctionError("glGetSeparableFilterEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetSeparableFilter(GLenum,GLenum,GLenum,GLvoid*,GLvoid*,GLvoid*){printMissingFunctionError("glGetSeparableFilter");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetShaderInfoLog(GLuint,GLsizei,GLsizei*,GLchar*){printMissingFunctionError("glGetShaderInfoLog");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetShaderiv(GLuint,GLenum,GLint*){printMissingFunctionError("glGetShaderiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetShaderPrecisionFormat(GLenum,GLenum,GLint*,GLint*){printMissingFunctionError("glGetShaderPrecisionFormat");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetShaderSourceARB(GLhandleARB,GLsizei,GLsizei*,GLcharARB*){printMissingFunctionError("glGetShaderSourceARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetShaderSource(GLuint,GLsizei,GLsizei*,GLchar*){printMissingFunctionError("glGetShaderSource");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetSharpenTexFuncSGIS(GLenum,GLfloat*){printMissingFunctionError("glGetSharpenTexFuncSGIS");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetSynciv(GLsync,GLenum,GLsizei,GLsizei*,GLint*){printMissingFunctionError("glGetSynciv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetTexBumpParameterfvATI(GLenum,GLfloat*){printMissingFunctionError("glGetTexBumpParameterfvATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetTexBumpParameterivATI(GLenum,GLint*){printMissingFunctionError("glGetTexBumpParameterivATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetTexEnvfv(GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetTexEnvfv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetTexEnviv(GLenum,GLenum,GLint*){printMissingFunctionError("glGetTexEnviv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetTexEnvxvOES(GLenum,GLenum,GLfixed*){printMissingFunctionError("glGetTexEnvxvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetTexFilterFuncSGIS(GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetTexFilterFuncSGIS");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetTexGendv(GLenum,GLenum,GLdouble*){printMissingFunctionError("glGetTexGendv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetTexGenfv(GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetTexGenfv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetTexGeniv(GLenum,GLenum,GLint*){printMissingFunctionError("glGetTexGeniv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetTexGenxvOES(GLenum,GLenum,GLfixed*){printMissingFunctionError("glGetTexGenxvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetTexImage(GLenum,GLint,GLenum,GLenum,GLvoid*){printMissingFunctionError("glGetTexImage");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetTexLevelParameterfv(GLenum,GLint,GLenum,GLfloat*){printMissingFunctionError("glGetTexLevelParameterfv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetTexLevelParameteriv(GLenum,GLint,GLenum,GLint*){printMissingFunctionError("glGetTexLevelParameteriv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetTexLevelParameterxvOES(GLenum,GLint,GLenum,GLfixed*){printMissingFunctionError("glGetTexLevelParameterxvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetTexParameterfv(GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetTexParameterfv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetTexParameterIivEXT(GLenum,GLenum,GLint*){printMissingFunctionError("glGetTexParameterIivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetTexParameterIiv(GLenum,GLenum,GLint*){printMissingFunctionError("glGetTexParameterIiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetTexParameterIuivEXT(GLenum,GLenum,GLuint*){printMissingFunctionError("glGetTexParameterIuivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetTexParameterIuiv(GLenum,GLenum,GLuint*){printMissingFunctionError("glGetTexParameterIuiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetTexParameteriv(GLenum,GLenum,GLint*){printMissingFunctionError("glGetTexParameteriv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetTexParameterPointervAPPLE(GLenum,GLenum,void**){printMissingFunctionError("glGetTexParameterPointervAPPLE");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetTexParameterxvOES(GLenum,GLenum,GLfixed*){printMissingFunctionError("glGetTexParameterxvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetTextureImageEXT(GLuint,GLenum,GLint,GLenum,GLenum,void*){printMissingFunctionError("glGetTextureImageEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetTextureImage(GLuint,GLint,GLenum,GLenum,GLsizei,void*){printMissingFunctionError("glGetTextureImage");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetTextureLevelParameterfvEXT(GLuint,GLenum,GLint,GLenum,GLfloat*){printMissingFunctionError("glGetTextureLevelParameterfvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetTextureLevelParameterfv(GLuint,GLint,GLenum,GLfloat*){printMissingFunctionError("glGetTextureLevelParameterfv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetTextureLevelParameterivEXT(GLuint,GLenum,GLint,GLenum,GLint*){printMissingFunctionError("glGetTextureLevelParameterivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetTextureLevelParameteriv(GLuint,GLint,GLenum,GLint*){printMissingFunctionError("glGetTextureLevelParameteriv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetTextureParameterfvEXT(GLuint,GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetTextureParameterfvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetTextureParameterfv(GLuint,GLenum,GLfloat*){printMissingFunctionError("glGetTextureParameterfv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetTextureParameterIivEXT(GLuint,GLenum,GLenum,GLint*){printMissingFunctionError("glGetTextureParameterIivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetTextureParameterIiv(GLuint,GLenum,GLint*){printMissingFunctionError("glGetTextureParameterIiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetTextureParameterIuivEXT(GLuint,GLenum,GLenum,GLuint*){printMissingFunctionError("glGetTextureParameterIuivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetTextureParameterIuiv(GLuint,GLenum,GLuint*){printMissingFunctionError("glGetTextureParameterIuiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetTextureParameterivEXT(GLuint,GLenum,GLenum,GLint*){printMissingFunctionError("glGetTextureParameterivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetTextureParameteriv(GLuint,GLenum,GLint*){printMissingFunctionError("glGetTextureParameteriv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetTextureSubImage(GLuint,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLenum,GLenum,GLsizei,void*){printMissingFunctionError("glGetTextureSubImage");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetTrackMatrixivNV(GLenum,GLuint,GLenum,GLint*){printMissingFunctionError("glGetTrackMatrixivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetTransformFeedbacki64_v(GLuint,GLenum,GLuint,GLint64*){printMissingFunctionError("glGetTransformFeedbacki64_v");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetTransformFeedbackiv(GLuint,GLenum,GLint*){printMissingFunctionError("glGetTransformFeedbackiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetTransformFeedbacki_v(GLuint,GLenum,GLuint,GLint*){printMissingFunctionError("glGetTransformFeedbacki_v");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetTransformFeedbackVaryingEXT(GLuint,GLuint,GLsizei,GLsizei*,GLsizei*,GLenum*,GLchar*){printMissingFunctionError("glGetTransformFeedbackVaryingEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetTransformFeedbackVarying(GLuint,GLuint,GLsizei,GLsizei*,GLsizei*,GLenum*,GLchar*){printMissingFunctionError("glGetTransformFeedbackVarying");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetTransformFeedbackVaryingNV(GLuint,GLuint,GLint*){printMissingFunctionError("glGetTransformFeedbackVaryingNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetUniformdv(GLuint,GLint,GLdouble*){printMissingFunctionError("glGetUniformdv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetUniformfvARB(GLhandleARB,GLint,GLfloat*){printMissingFunctionError("glGetUniformfvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetUniformfv(GLuint,GLint,GLfloat*){printMissingFunctionError("glGetUniformfv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetUniformi64vARB(GLuint,GLint,GLint64*){printMissingFunctionError("glGetUniformi64vARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetUniformi64vNV(GLuint,GLint,GLint64EXT*){printMissingFunctionError("glGetUniformi64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetUniformIndices(GLuint,GLsizei,const GLchar*const*,GLuint*){printMissingFunctionError("glGetUniformIndices");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetUniformivARB(GLhandleARB,GLint,GLint*){printMissingFunctionError("glGetUniformivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetUniformiv(GLuint,GLint,GLint*){printMissingFunctionError("glGetUniformiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetUniformSubroutineuiv(GLenum,GLint,GLuint*){printMissingFunctionError("glGetUniformSubroutineuiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetUniformui64vARB(GLuint,GLint,GLuint64*){printMissingFunctionError("glGetUniformui64vARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetUniformui64vNV(GLuint,GLint,GLuint64EXT*){printMissingFunctionError("glGetUniformui64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetUniformuivEXT(GLuint,GLint,GLuint*){printMissingFunctionError("glGetUniformuivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetUniformuiv(GLuint,GLint,GLuint*){printMissingFunctionError("glGetUniformuiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetVariantArrayObjectfvATI(GLuint,GLenum,GLfloat*){printMissingFunctionError("glGetVariantArrayObjectfvATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetVariantArrayObjectivATI(GLuint,GLenum,GLint*){printMissingFunctionError("glGetVariantArrayObjectivATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetVariantBooleanvEXT(GLuint,GLenum,GLboolean*){printMissingFunctionError("glGetVariantBooleanvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetVariantFloatvEXT(GLuint,GLenum,GLfloat*){printMissingFunctionError("glGetVariantFloatvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetVariantIntegervEXT(GLuint,GLenum,GLint*){printMissingFunctionError("glGetVariantIntegervEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetVariantPointervEXT(GLuint,GLenum,void**){printMissingFunctionError("glGetVariantPointervEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetVertexArrayIndexed64iv(GLuint,GLuint,GLenum,GLint64*){printMissingFunctionError("glGetVertexArrayIndexed64iv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetVertexArrayIndexediv(GLuint,GLuint,GLenum,GLint*){printMissingFunctionError("glGetVertexArrayIndexediv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetVertexArrayIntegeri_vEXT(GLuint,GLuint,GLenum,GLint*){printMissingFunctionError("glGetVertexArrayIntegeri_vEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetVertexArrayIntegervEXT(GLuint,GLenum,GLint*){printMissingFunctionError("glGetVertexArrayIntegervEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetVertexArrayiv(GLuint,GLenum,GLint*){printMissingFunctionError("glGetVertexArrayiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetVertexArrayPointeri_vEXT(GLuint,GLuint,GLenum,void**){printMissingFunctionError("glGetVertexArrayPointeri_vEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetVertexArrayPointervEXT(GLuint,GLenum,void**){printMissingFunctionError("glGetVertexArrayPointervEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetVertexAttribArrayObjectfvATI(GLuint,GLenum,GLfloat*){printMissingFunctionError("glGetVertexAttribArrayObjectfvATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetVertexAttribArrayObjectivATI(GLuint,GLenum,GLint*){printMissingFunctionError("glGetVertexAttribArrayObjectivATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetVertexAttribdvARB(GLuint,GLenum,GLdouble*){printMissingFunctionError("glGetVertexAttribdvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetVertexAttribdv(GLuint,GLenum,GLdouble*){printMissingFunctionError("glGetVertexAttribdv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetVertexAttribdvNV(GLuint,GLenum,GLdouble*){printMissingFunctionError("glGetVertexAttribdvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetVertexAttribfvARB(GLuint,GLenum,GLfloat*){printMissingFunctionError("glGetVertexAttribfvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetVertexAttribfv(GLuint,GLenum,GLfloat*){printMissingFunctionError("glGetVertexAttribfv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetVertexAttribfvNV(GLuint,GLenum,GLfloat*){printMissingFunctionError("glGetVertexAttribfvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetVertexAttribIivEXT(GLuint,GLenum,GLint*){printMissingFunctionError("glGetVertexAttribIivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetVertexAttribIiv(GLuint,GLenum,GLint*){printMissingFunctionError("glGetVertexAttribIiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetVertexAttribIuivEXT(GLuint,GLenum,GLuint*){printMissingFunctionError("glGetVertexAttribIuivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetVertexAttribIuiv(GLuint,GLenum,GLuint*){printMissingFunctionError("glGetVertexAttribIuiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetVertexAttribivARB(GLuint,GLenum,GLint*){printMissingFunctionError("glGetVertexAttribivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetVertexAttribiv(GLuint,GLenum,GLint*){printMissingFunctionError("glGetVertexAttribiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetVertexAttribivNV(GLuint,GLenum,GLint*){printMissingFunctionError("glGetVertexAttribivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetVertexAttribLdvEXT(GLuint,GLenum,GLdouble*){printMissingFunctionError("glGetVertexAttribLdvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetVertexAttribLdv(GLuint,GLenum,GLdouble*){printMissingFunctionError("glGetVertexAttribLdv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetVertexAttribLi64vNV(GLuint,GLenum,GLint64EXT*){printMissingFunctionError("glGetVertexAttribLi64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetVertexAttribLui64vARB(GLuint,GLenum,GLuint64EXT*){printMissingFunctionError("glGetVertexAttribLui64vARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetVertexAttribLui64vNV(GLuint,GLenum,GLuint64EXT*){printMissingFunctionError("glGetVertexAttribLui64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetVertexAttribPointervARB(GLuint,GLenum,void**){printMissingFunctionError("glGetVertexAttribPointervARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetVertexAttribPointerv(GLuint,GLenum,void**){printMissingFunctionError("glGetVertexAttribPointerv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetVertexAttribPointervNV(GLuint,GLenum,void**){printMissingFunctionError("glGetVertexAttribPointervNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetVideoCaptureivNV(GLuint,GLenum,GLint*){printMissingFunctionError("glGetVideoCaptureivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetVideoCaptureStreamdvNV(GLuint,GLuint,GLenum,GLdouble*){printMissingFunctionError("glGetVideoCaptureStreamdvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetVideoCaptureStreamfvNV(GLuint,GLuint,GLenum,GLfloat*){printMissingFunctionError("glGetVideoCaptureStreamfvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetVideoCaptureStreamivNV(GLuint,GLuint,GLenum,GLint*){printMissingFunctionError("glGetVideoCaptureStreamivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetVideoi64vNV(GLuint,GLenum,GLint64EXT*){printMissingFunctionError("glGetVideoi64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetVideoivNV(GLuint,GLenum,GLint*){printMissingFunctionError("glGetVideoivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetVideoui64vNV(GLuint,GLenum,GLuint64EXT*){printMissingFunctionError("glGetVideoui64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGetVideouivNV(GLuint,GLenum,GLuint*){printMissingFunctionError("glGetVideouivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGlobalAlphaFactorbSUN(GLbyte){printMissingFunctionError("glGlobalAlphaFactorbSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGlobalAlphaFactordSUN(GLdouble){printMissingFunctionError("glGlobalAlphaFactordSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGlobalAlphaFactorfSUN(GLfloat){printMissingFunctionError("glGlobalAlphaFactorfSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGlobalAlphaFactoriSUN(GLint){printMissingFunctionError("glGlobalAlphaFactoriSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGlobalAlphaFactorsSUN(GLshort){printMissingFunctionError("glGlobalAlphaFactorsSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGlobalAlphaFactorubSUN(GLubyte){printMissingFunctionError("glGlobalAlphaFactorubSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGlobalAlphaFactoruiSUN(GLuint){printMissingFunctionError("glGlobalAlphaFactoruiSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglGlobalAlphaFactorusSUN(GLushort){printMissingFunctionError("glGlobalAlphaFactorusSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglHint(GLenum,GLenum){printMissingFunctionError("glHint");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglHintPGI(GLenum,GLint){printMissingFunctionError("glHintPGI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglHistogramEXT(GLenum,GLsizei,GLenum,GLboolean){printMissingFunctionError("glHistogramEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglHistogram(GLenum,GLsizei,GLenum,GLboolean){printMissingFunctionError("glHistogram");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglIglooInterfaceSGIX(GLenum,const void*){printMissingFunctionError("glIglooInterfaceSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglImageTransformParameterfHP(GLenum,GLenum,GLfloat){printMissingFunctionError("glImageTransformParameterfHP");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglImageTransformParameterfvHP(GLenum,GLenum,const GLfloat*){printMissingFunctionError("glImageTransformParameterfvHP");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglImageTransformParameteriHP(GLenum,GLenum,GLint){printMissingFunctionError("glImageTransformParameteriHP");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglImageTransformParameterivHP(GLenum,GLenum,const GLint*){printMissingFunctionError("glImageTransformParameterivHP");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglIndexd(GLdouble){printMissingFunctionError("glIndexd");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglIndexdv(const GLdouble*){printMissingFunctionError("glIndexdv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglIndexf(GLfloat){printMissingFunctionError("glIndexf");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglIndexFormatNV(GLenum,GLsizei){printMissingFunctionError("glIndexFormatNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglIndexFuncEXT(GLenum,GLclampf){printMissingFunctionError("glIndexFuncEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglIndexfv(const GLfloat*){printMissingFunctionError("glIndexfv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglIndexi(GLint){printMissingFunctionError("glIndexi");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglIndexiv(const GLint*){printMissingFunctionError("glIndexiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglIndexMask(GLuint){printMissingFunctionError("glIndexMask");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglIndexMaterialEXT(GLenum,GLenum){printMissingFunctionError("glIndexMaterialEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglIndexPointerEXT(GLenum,GLsizei,GLsizei,const void*){printMissingFunctionError("glIndexPointerEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglIndexPointer(GLenum,GLsizei,const GLvoid*){printMissingFunctionError("glIndexPointer");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglIndexPointerListIBM(GLenum,GLint,const void**,GLint){printMissingFunctionError("glIndexPointerListIBM");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglIndexs(GLshort){printMissingFunctionError("glIndexs");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglIndexsv(const GLshort*){printMissingFunctionError("glIndexsv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglIndexub(GLubyte){printMissingFunctionError("glIndexub");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglIndexubv(const GLubyte*){printMissingFunctionError("glIndexubv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglIndexxOES(GLfixed){printMissingFunctionError("glIndexxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglIndexxvOES(const GLfixed*){printMissingFunctionError("glIndexxvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglInitNames(){printMissingFunctionError("glInitNames");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglInsertComponentEXT(GLuint,GLuint,GLuint){printMissingFunctionError("glInsertComponentEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglInsertEventMarkerEXT(GLsizei,const GLchar*){printMissingFunctionError("glInsertEventMarkerEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglInstrumentsBufferSGIX(GLsizei,GLint*){printMissingFunctionError("glInstrumentsBufferSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglInterleavedArrays(GLenum,GLsizei,const GLvoid*){printMissingFunctionError("glInterleavedArrays");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglInterpolatePathsNV(GLuint,GLuint,GLuint,GLfloat){printMissingFunctionError("glInterpolatePathsNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglInvalidateBufferData(GLuint){printMissingFunctionError("glInvalidateBufferData");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglInvalidateBufferSubData(GLuint,GLintptr,GLsizeiptr){printMissingFunctionError("glInvalidateBufferSubData");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglInvalidateFramebuffer(GLenum,GLsizei,const GLenum*){printMissingFunctionError("glInvalidateFramebuffer");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglInvalidateNamedFramebufferData(GLuint,GLsizei,const GLenum*){printMissingFunctionError("glInvalidateNamedFramebufferData");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglInvalidateNamedFramebufferSubData(GLuint,GLsizei,const GLenum*,GLint,GLint,GLsizei,GLsizei){printMissingFunctionError("glInvalidateNamedFramebufferSubData");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglInvalidateSubFramebuffer(GLenum,GLsizei,const GLenum*,GLint,GLint,GLsizei,GLsizei){printMissingFunctionError("glInvalidateSubFramebuffer");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglInvalidateTexImage(GLuint,GLint){printMissingFunctionError("glInvalidateTexImage");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglInvalidateTexSubImage(GLuint,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei){printMissingFunctionError("glInvalidateTexSubImage");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglLabelObjectEXT(GLenum,GLuint,GLsizei,const GLchar*){printMissingFunctionError("glLabelObjectEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglLightEnviSGIX(GLenum,GLint){printMissingFunctionError("glLightEnviSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglLightf(GLenum,GLenum,GLfloat){printMissingFunctionError("glLightf");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglLightfv(GLenum,GLenum,const GLfloat*){printMissingFunctionError("glLightfv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglLighti(GLenum,GLenum,GLint){printMissingFunctionError("glLighti");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglLightiv(GLenum,GLenum,const GLint*){printMissingFunctionError("glLightiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglLightModelf(GLenum,GLfloat){printMissingFunctionError("glLightModelf");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglLightModelfv(GLenum,const GLfloat*){printMissingFunctionError("glLightModelfv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglLightModeli(GLenum,GLint){printMissingFunctionError("glLightModeli");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglLightModeliv(GLenum,const GLint*){printMissingFunctionError("glLightModeliv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglLightModelxOES(GLenum,GLfixed){printMissingFunctionError("glLightModelxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglLightModelxvOES(GLenum,const GLfixed*){printMissingFunctionError("glLightModelxvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglLightxOES(GLenum,GLenum,GLfixed){printMissingFunctionError("glLightxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglLightxvOES(GLenum,GLenum,const GLfixed*){printMissingFunctionError("glLightxvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglLineStipple(GLint,GLushort){printMissingFunctionError("glLineStipple");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglLineWidth(GLfloat){printMissingFunctionError("glLineWidth");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglLineWidthxOES(GLfixed){printMissingFunctionError("glLineWidthxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglLinkProgramARB(GLhandleARB){printMissingFunctionError("glLinkProgramARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglLinkProgram(GLuint){printMissingFunctionError("glLinkProgram");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglListBase(GLuint){printMissingFunctionError("glListBase");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglListDrawCommandsStatesClientNV(GLuint,GLuint,const void**,const GLsizei*,const GLuint*,const GLuint*,GLuint){printMissingFunctionError("glListDrawCommandsStatesClientNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglListParameterfSGIX(GLuint,GLenum,GLfloat){printMissingFunctionError("glListParameterfSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglListParameterfvSGIX(GLuint,GLenum,const GLfloat*){printMissingFunctionError("glListParameterfvSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglListParameteriSGIX(GLuint,GLenum,GLint){printMissingFunctionError("glListParameteriSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglListParameterivSGIX(GLuint,GLenum,const GLint*){printMissingFunctionError("glListParameterivSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglLoadIdentity(){printMissingFunctionError("glLoadIdentity");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglLoadIdentityDeformationMapSGIX(GLbitfield){printMissingFunctionError("glLoadIdentityDeformationMapSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglLoadMatrixd(const GLdouble*){printMissingFunctionError("glLoadMatrixd");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglLoadMatrixf(const GLfloat*){printMissingFunctionError("glLoadMatrixf");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglLoadMatrixxOES(const GLfixed*){printMissingFunctionError("glLoadMatrixxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglLoadName(GLuint){printMissingFunctionError("glLoadName");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglLoadProgramNV(GLenum,GLuint,GLsizei,const GLubyte*){printMissingFunctionError("glLoadProgramNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglLoadTransposeMatrixdARB(const GLdouble*){printMissingFunctionError("glLoadTransposeMatrixdARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglLoadTransposeMatrixd(const GLdouble){printMissingFunctionError("glLoadTransposeMatrixd");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglLoadTransposeMatrixfARB(const GLfloat*){printMissingFunctionError("glLoadTransposeMatrixfARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglLoadTransposeMatrixf(const GLfloat){printMissingFunctionError("glLoadTransposeMatrixf");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglLoadTransposeMatrixxOES(const GLfixed*){printMissingFunctionError("glLoadTransposeMatrixxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglLockArraysEXT(GLint,GLsizei){printMissingFunctionError("glLockArraysEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglLogicOp(GLenum){printMissingFunctionError("glLogicOp");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMakeBufferNonResidentNV(GLenum){printMissingFunctionError("glMakeBufferNonResidentNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMakeBufferResidentNV(GLenum,GLenum){printMissingFunctionError("glMakeBufferResidentNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMakeImageHandleNonResidentARB(GLuint64){printMissingFunctionError("glMakeImageHandleNonResidentARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMakeImageHandleNonResidentNV(GLuint64){printMissingFunctionError("glMakeImageHandleNonResidentNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMakeImageHandleResidentARB(GLuint64,GLenum){printMissingFunctionError("glMakeImageHandleResidentARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMakeImageHandleResidentNV(GLuint64,GLenum){printMissingFunctionError("glMakeImageHandleResidentNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMakeNamedBufferNonResidentNV(GLuint){printMissingFunctionError("glMakeNamedBufferNonResidentNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMakeNamedBufferResidentNV(GLuint,GLenum){printMissingFunctionError("glMakeNamedBufferResidentNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMakeTextureHandleNonResidentARB(GLuint64){printMissingFunctionError("glMakeTextureHandleNonResidentARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMakeTextureHandleNonResidentNV(GLuint64){printMissingFunctionError("glMakeTextureHandleNonResidentNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMakeTextureHandleResidentARB(GLuint64){printMissingFunctionError("glMakeTextureHandleResidentARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMakeTextureHandleResidentNV(GLuint64){printMissingFunctionError("glMakeTextureHandleResidentNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMap1d(GLenum,GLdouble,GLdouble,GLint,GLint,const GLdouble*){printMissingFunctionError("glMap1d");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMap1f(GLenum,GLfloat,GLfloat,GLint,GLint,const GLfloat*){printMissingFunctionError("glMap1f");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMap1xOES(GLenum,GLfixed,GLfixed,GLint,GLint,GLfixed){printMissingFunctionError("glMap1xOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMap2d(GLenum,GLdouble,GLdouble,GLint,GLint,GLdouble,GLdouble,GLint,GLint,const GLdouble*){printMissingFunctionError("glMap2d");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMap2f(GLenum,GLfloat,GLfloat,GLint,GLint,GLfloat,GLfloat,GLint,GLint,const GLfloat*){printMissingFunctionError("glMap2f");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMap2xOES(GLenum,GLfixed,GLfixed,GLint,GLint,GLfixed,GLfixed,GLint,GLint,GLfixed){printMissingFunctionError("glMap2xOES");std::exit(1);return (void)0;}
GEGL_EXPORT void* gegl_TrapglMapBufferARB(GLenum,GLenum){printMissingFunctionError("glMapBufferARB");std::exit(1);return (void*)0;}
GEGL_EXPORT void* gegl_TrapglMapBuffer(GLenum,GLenum){printMissingFunctionError("glMapBuffer");std::exit(1);return (void*)0;}
GEGL_EXPORT void* gegl_TrapglMapBufferRange(GLenum,GLintptr,GLsizeiptr,GLbitfield){printMissingFunctionError("glMapBufferRange");std::exit(1);return (void*)0;}
GEGL_EXPORT void gegl_TrapglMapControlPointsNV(GLenum,GLuint,GLenum,GLsizei,GLsizei,GLint,GLint,GLboolean,const void*){printMissingFunctionError("glMapControlPointsNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMapGrid1d(GLint,GLdouble,GLdouble){printMissingFunctionError("glMapGrid1d");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMapGrid1f(GLint,GLfloat,GLfloat){printMissingFunctionError("glMapGrid1f");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMapGrid1xOES(GLint,GLfixed,GLfixed){printMissingFunctionError("glMapGrid1xOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMapGrid2d(GLint,GLdouble,GLdouble,GLint,GLdouble,GLdouble){printMissingFunctionError("glMapGrid2d");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMapGrid2f(GLint,GLfloat,GLfloat,GLint,GLfloat,GLfloat){printMissingFunctionError("glMapGrid2f");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMapGrid2xOES(GLint,GLfixed,GLfixed,GLfixed,GLfixed){printMissingFunctionError("glMapGrid2xOES");std::exit(1);return (void)0;}
GEGL_EXPORT void* gegl_TrapglMapNamedBufferEXT(GLuint,GLenum){printMissingFunctionError("glMapNamedBufferEXT");std::exit(1);return (void*)0;}
GEGL_EXPORT void* gegl_TrapglMapNamedBuffer(GLuint,GLenum){printMissingFunctionError("glMapNamedBuffer");std::exit(1);return (void*)0;}
GEGL_EXPORT void* gegl_TrapglMapNamedBufferRangeEXT(GLuint,GLintptr,GLsizeiptr,GLbitfield){printMissingFunctionError("glMapNamedBufferRangeEXT");std::exit(1);return (void*)0;}
GEGL_EXPORT void* gegl_TrapglMapNamedBufferRange(GLuint,GLintptr,GLsizeiptr,GLbitfield){printMissingFunctionError("glMapNamedBufferRange");std::exit(1);return (void*)0;}
GEGL_EXPORT void* gegl_TrapglMapObjectBufferATI(GLuint){printMissingFunctionError("glMapObjectBufferATI");std::exit(1);return (void*)0;}
GEGL_EXPORT void gegl_TrapglMapParameterfvNV(GLenum,GLenum,const GLfloat*){printMissingFunctionError("glMapParameterfvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMapParameterivNV(GLenum,GLenum,const GLint*){printMissingFunctionError("glMapParameterivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void* gegl_TrapglMapTexture2DINTEL(GLuint,GLint,GLbitfield,GLint*,GLenum*){printMissingFunctionError("glMapTexture2DINTEL");std::exit(1);return (void*)0;}
GEGL_EXPORT void gegl_TrapglMapVertexAttrib1dAPPLE(GLuint,GLuint,GLdouble,GLdouble,GLint,GLint,const GLdouble*){printMissingFunctionError("glMapVertexAttrib1dAPPLE");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMapVertexAttrib1fAPPLE(GLuint,GLuint,GLfloat,GLfloat,GLint,GLint,const GLfloat*){printMissingFunctionError("glMapVertexAttrib1fAPPLE");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMapVertexAttrib2dAPPLE(GLuint,GLuint,GLdouble,GLdouble,GLint,GLint,GLdouble,GLdouble,GLint,GLint,const GLdouble*){printMissingFunctionError("glMapVertexAttrib2dAPPLE");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMapVertexAttrib2fAPPLE(GLuint,GLuint,GLfloat,GLfloat,GLint,GLint,GLfloat,GLfloat,GLint,GLint,const GLfloat*){printMissingFunctionError("glMapVertexAttrib2fAPPLE");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMaterialf(GLenum,GLenum,GLfloat){printMissingFunctionError("glMaterialf");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMaterialfv(GLenum,GLenum,const GLfloat*){printMissingFunctionError("glMaterialfv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMateriali(GLenum,GLenum,GLint){printMissingFunctionError("glMateriali");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMaterialiv(GLenum,GLenum,const GLint*){printMissingFunctionError("glMaterialiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMaterialxOES(GLenum,GLenum,GLfixed){printMissingFunctionError("glMaterialxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMaterialxvOES(GLenum,GLenum,const GLfixed*){printMissingFunctionError("glMaterialxvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMatrixFrustumEXT(GLenum,GLdouble,GLdouble,GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glMatrixFrustumEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMatrixIndexPointerARB(GLint,GLenum,GLsizei,const void*){printMissingFunctionError("glMatrixIndexPointerARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMatrixIndexubvARB(GLint,const GLubyte*){printMissingFunctionError("glMatrixIndexubvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMatrixIndexuivARB(GLint,const GLuint*){printMissingFunctionError("glMatrixIndexuivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMatrixIndexusvARB(GLint,const GLushort*){printMissingFunctionError("glMatrixIndexusvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMatrixLoad3x2fNV(GLenum,const GLfloat*){printMissingFunctionError("glMatrixLoad3x2fNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMatrixLoad3x3fNV(GLenum,const GLfloat*){printMissingFunctionError("glMatrixLoad3x3fNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMatrixLoaddEXT(GLenum,const GLdouble*){printMissingFunctionError("glMatrixLoaddEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMatrixLoadfEXT(GLenum,const GLfloat*){printMissingFunctionError("glMatrixLoadfEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMatrixLoadIdentityEXT(GLenum){printMissingFunctionError("glMatrixLoadIdentityEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMatrixLoadTranspose3x3fNV(GLenum,const GLfloat*){printMissingFunctionError("glMatrixLoadTranspose3x3fNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMatrixLoadTransposedEXT(GLenum,const GLdouble*){printMissingFunctionError("glMatrixLoadTransposedEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMatrixLoadTransposefEXT(GLenum,const GLfloat*){printMissingFunctionError("glMatrixLoadTransposefEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMatrixMode(GLenum){printMissingFunctionError("glMatrixMode");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMatrixMult3x2fNV(GLenum,const GLfloat*){printMissingFunctionError("glMatrixMult3x2fNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMatrixMult3x3fNV(GLenum,const GLfloat*){printMissingFunctionError("glMatrixMult3x3fNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMatrixMultdEXT(GLenum,const GLdouble*){printMissingFunctionError("glMatrixMultdEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMatrixMultfEXT(GLenum,const GLfloat*){printMissingFunctionError("glMatrixMultfEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMatrixMultTranspose3x3fNV(GLenum,const GLfloat*){printMissingFunctionError("glMatrixMultTranspose3x3fNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMatrixMultTransposedEXT(GLenum,const GLdouble*){printMissingFunctionError("glMatrixMultTransposedEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMatrixMultTransposefEXT(GLenum,const GLfloat*){printMissingFunctionError("glMatrixMultTransposefEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMatrixOrthoEXT(GLenum,GLdouble,GLdouble,GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glMatrixOrthoEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMatrixPopEXT(GLenum){printMissingFunctionError("glMatrixPopEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMatrixPushEXT(GLenum){printMissingFunctionError("glMatrixPushEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMatrixRotatedEXT(GLenum,GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glMatrixRotatedEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMatrixRotatefEXT(GLenum,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glMatrixRotatefEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMatrixScaledEXT(GLenum,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glMatrixScaledEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMatrixScalefEXT(GLenum,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glMatrixScalefEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMatrixTranslatedEXT(GLenum,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glMatrixTranslatedEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMatrixTranslatefEXT(GLenum,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glMatrixTranslatefEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMaxShaderCompilerThreadsARB(GLuint){printMissingFunctionError("glMaxShaderCompilerThreadsARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMemoryBarrierByRegion(GLbitfield){printMissingFunctionError("glMemoryBarrierByRegion");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMemoryBarrierEXT(GLbitfield){printMissingFunctionError("glMemoryBarrierEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMemoryBarrier(GLbitfield){printMissingFunctionError("glMemoryBarrier");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMinmaxEXT(GLenum,GLenum,GLboolean){printMissingFunctionError("glMinmaxEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMinmax(GLenum,GLenum,GLboolean){printMissingFunctionError("glMinmax");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMinSampleShadingARB(GLfloat){printMissingFunctionError("glMinSampleShadingARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMinSampleShading(GLfloat){printMissingFunctionError("glMinSampleShading");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiDrawArraysEXT(GLenum,const GLint*,const GLsizei*,GLsizei){printMissingFunctionError("glMultiDrawArraysEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiDrawArrays(GLenum,const GLint*,const GLsizei*,GLsizei){printMissingFunctionError("glMultiDrawArrays");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiDrawArraysIndirectAMD(GLenum,const void*,GLsizei,GLsizei){printMissingFunctionError("glMultiDrawArraysIndirectAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiDrawArraysIndirectBindlessCountNV(GLenum,const void*,GLsizei,GLsizei,GLsizei,GLint){printMissingFunctionError("glMultiDrawArraysIndirectBindlessCountNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiDrawArraysIndirectBindlessNV(GLenum,const void*,GLsizei,GLsizei,GLint){printMissingFunctionError("glMultiDrawArraysIndirectBindlessNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiDrawArraysIndirectCountARB(GLenum,GLintptr,GLintptr,GLsizei,GLsizei){printMissingFunctionError("glMultiDrawArraysIndirectCountARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiDrawArraysIndirect(GLenum,const void*,GLsizei,GLsizei){printMissingFunctionError("glMultiDrawArraysIndirect");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiDrawElementArrayAPPLE(GLenum,const GLint*,const GLsizei*,GLsizei){printMissingFunctionError("glMultiDrawElementArrayAPPLE");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiDrawElementsBaseVertex(GLenum,const GLsizei*,GLenum,const void*const*,GLsizei,const GLint*){printMissingFunctionError("glMultiDrawElementsBaseVertex");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiDrawElementsEXT(GLenum,const GLsizei*,GLenum,const void*const*,GLsizei){printMissingFunctionError("glMultiDrawElementsEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiDrawElements(GLenum,const GLsizei*,GLenum,const void*const*,GLsizei){printMissingFunctionError("glMultiDrawElements");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiDrawElementsIndirectAMD(GLenum,GLenum,const void*,GLsizei,GLsizei){printMissingFunctionError("glMultiDrawElementsIndirectAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiDrawElementsIndirectBindlessCountNV(GLenum,GLenum,const void*,GLsizei,GLsizei,GLsizei,GLint){printMissingFunctionError("glMultiDrawElementsIndirectBindlessCountNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiDrawElementsIndirectBindlessNV(GLenum,GLenum,const void*,GLsizei,GLsizei,GLint){printMissingFunctionError("glMultiDrawElementsIndirectBindlessNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiDrawElementsIndirectCountARB(GLenum,GLenum,GLintptr,GLintptr,GLsizei,GLsizei){printMissingFunctionError("glMultiDrawElementsIndirectCountARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiDrawElementsIndirect(GLenum,GLenum,const void*,GLsizei,GLsizei){printMissingFunctionError("glMultiDrawElementsIndirect");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiDrawRangeElementArrayAPPLE(GLenum,GLuint,GLuint,const GLint*,const GLsizei*,GLsizei){printMissingFunctionError("glMultiDrawRangeElementArrayAPPLE");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiModeDrawArraysIBM(const GLenum*,const GLint*,const GLsizei*,GLsizei,GLint){printMissingFunctionError("glMultiModeDrawArraysIBM");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiModeDrawElementsIBM(const GLenum*,const GLsizei*,GLenum,const void*const*,GLsizei,GLint){printMissingFunctionError("glMultiModeDrawElementsIBM");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexBufferEXT(GLenum,GLenum,GLenum,GLuint){printMissingFunctionError("glMultiTexBufferEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord1bOES(GLenum,GLbyte){printMissingFunctionError("glMultiTexCoord1bOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord1bvOES(GLenum,const GLbyte*){printMissingFunctionError("glMultiTexCoord1bvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord1dARB(GLenum,GLdouble){printMissingFunctionError("glMultiTexCoord1dARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord1d(GLenum,GLdouble){printMissingFunctionError("glMultiTexCoord1d");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord1dvARB(GLenum,const GLdouble*){printMissingFunctionError("glMultiTexCoord1dvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord1dv(GLenum,const GLdouble*){printMissingFunctionError("glMultiTexCoord1dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord1fARB(GLenum,GLfloat){printMissingFunctionError("glMultiTexCoord1fARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord1f(GLenum,GLfloat){printMissingFunctionError("glMultiTexCoord1f");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord1fvARB(GLenum,const GLfloat*){printMissingFunctionError("glMultiTexCoord1fvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord1fv(GLenum,const GLfloat*){printMissingFunctionError("glMultiTexCoord1fv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord1hNV(GLenum,GLhalfNV){printMissingFunctionError("glMultiTexCoord1hNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord1hvNV(GLenum,const GLhalfNV*){printMissingFunctionError("glMultiTexCoord1hvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord1iARB(GLenum,GLint){printMissingFunctionError("glMultiTexCoord1iARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord1i(GLenum,GLint){printMissingFunctionError("glMultiTexCoord1i");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord1ivARB(GLenum,const GLint*){printMissingFunctionError("glMultiTexCoord1ivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord1iv(GLenum,const GLint*){printMissingFunctionError("glMultiTexCoord1iv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord1sARB(GLenum,GLshort){printMissingFunctionError("glMultiTexCoord1sARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord1s(GLenum,GLshort){printMissingFunctionError("glMultiTexCoord1s");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord1svARB(GLenum,const GLshort*){printMissingFunctionError("glMultiTexCoord1svARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord1sv(GLenum,const GLshort*){printMissingFunctionError("glMultiTexCoord1sv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord1xOES(GLenum,GLfixed){printMissingFunctionError("glMultiTexCoord1xOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord1xvOES(GLenum,const GLfixed*){printMissingFunctionError("glMultiTexCoord1xvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord2bOES(GLenum,GLbyte,GLbyte){printMissingFunctionError("glMultiTexCoord2bOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord2bvOES(GLenum,const GLbyte*){printMissingFunctionError("glMultiTexCoord2bvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord2dARB(GLenum,GLdouble,GLdouble){printMissingFunctionError("glMultiTexCoord2dARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord2d(GLenum,GLdouble,GLdouble){printMissingFunctionError("glMultiTexCoord2d");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord2dvARB(GLenum,const GLdouble*){printMissingFunctionError("glMultiTexCoord2dvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord2dv(GLenum,const GLdouble*){printMissingFunctionError("glMultiTexCoord2dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord2fARB(GLenum,GLfloat,GLfloat){printMissingFunctionError("glMultiTexCoord2fARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord2f(GLenum,GLfloat,GLfloat){printMissingFunctionError("glMultiTexCoord2f");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord2fvARB(GLenum,const GLfloat*){printMissingFunctionError("glMultiTexCoord2fvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord2fv(GLenum,const GLfloat*){printMissingFunctionError("glMultiTexCoord2fv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord2hNV(GLenum,GLhalfNV,GLhalfNV){printMissingFunctionError("glMultiTexCoord2hNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord2hvNV(GLenum,const GLhalfNV*){printMissingFunctionError("glMultiTexCoord2hvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord2iARB(GLenum,GLint,GLint){printMissingFunctionError("glMultiTexCoord2iARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord2i(GLenum,GLint,GLint){printMissingFunctionError("glMultiTexCoord2i");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord2ivARB(GLenum,const GLint*){printMissingFunctionError("glMultiTexCoord2ivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord2iv(GLenum,const GLint*){printMissingFunctionError("glMultiTexCoord2iv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord2sARB(GLenum,GLshort,GLshort){printMissingFunctionError("glMultiTexCoord2sARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord2s(GLenum,GLshort,GLshort){printMissingFunctionError("glMultiTexCoord2s");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord2svARB(GLenum,const GLshort*){printMissingFunctionError("glMultiTexCoord2svARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord2sv(GLenum,const GLshort*){printMissingFunctionError("glMultiTexCoord2sv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord2xOES(GLenum,GLfixed,GLfixed){printMissingFunctionError("glMultiTexCoord2xOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord2xvOES(GLenum,const GLfixed*){printMissingFunctionError("glMultiTexCoord2xvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord3bOES(GLenum,GLbyte,GLbyte,GLbyte){printMissingFunctionError("glMultiTexCoord3bOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord3bvOES(GLenum,const GLbyte*){printMissingFunctionError("glMultiTexCoord3bvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord3dARB(GLenum,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glMultiTexCoord3dARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord3d(GLenum,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glMultiTexCoord3d");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord3dvARB(GLenum,const GLdouble*){printMissingFunctionError("glMultiTexCoord3dvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord3dv(GLenum,const GLdouble*){printMissingFunctionError("glMultiTexCoord3dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord3fARB(GLenum,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glMultiTexCoord3fARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord3f(GLenum,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glMultiTexCoord3f");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord3fvARB(GLenum,const GLfloat*){printMissingFunctionError("glMultiTexCoord3fvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord3fv(GLenum,const GLfloat*){printMissingFunctionError("glMultiTexCoord3fv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord3hNV(GLenum,GLhalfNV,GLhalfNV,GLhalfNV){printMissingFunctionError("glMultiTexCoord3hNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord3hvNV(GLenum,const GLhalfNV*){printMissingFunctionError("glMultiTexCoord3hvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord3iARB(GLenum,GLint,GLint,GLint){printMissingFunctionError("glMultiTexCoord3iARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord3i(GLenum,GLint,GLint,GLint){printMissingFunctionError("glMultiTexCoord3i");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord3ivARB(GLenum,const GLint*){printMissingFunctionError("glMultiTexCoord3ivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord3iv(GLenum,const GLint*){printMissingFunctionError("glMultiTexCoord3iv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord3sARB(GLenum,GLshort,GLshort,GLshort){printMissingFunctionError("glMultiTexCoord3sARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord3s(GLenum,GLshort,GLshort,GLshort){printMissingFunctionError("glMultiTexCoord3s");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord3svARB(GLenum,const GLshort*){printMissingFunctionError("glMultiTexCoord3svARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord3sv(GLenum,const GLshort*){printMissingFunctionError("glMultiTexCoord3sv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord3xOES(GLenum,GLfixed,GLfixed,GLfixed){printMissingFunctionError("glMultiTexCoord3xOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord3xvOES(GLenum,const GLfixed*){printMissingFunctionError("glMultiTexCoord3xvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord4bOES(GLenum,GLbyte,GLbyte,GLbyte,GLbyte){printMissingFunctionError("glMultiTexCoord4bOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord4bvOES(GLenum,const GLbyte*){printMissingFunctionError("glMultiTexCoord4bvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord4dARB(GLenum,GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glMultiTexCoord4dARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord4d(GLenum,GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glMultiTexCoord4d");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord4dvARB(GLenum,const GLdouble*){printMissingFunctionError("glMultiTexCoord4dvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord4dv(GLenum,const GLdouble*){printMissingFunctionError("glMultiTexCoord4dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord4fARB(GLenum,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glMultiTexCoord4fARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord4f(GLenum,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glMultiTexCoord4f");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord4fvARB(GLenum,const GLfloat*){printMissingFunctionError("glMultiTexCoord4fvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord4fv(GLenum,const GLfloat*){printMissingFunctionError("glMultiTexCoord4fv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord4hNV(GLenum,GLhalfNV,GLhalfNV,GLhalfNV,GLhalfNV){printMissingFunctionError("glMultiTexCoord4hNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord4hvNV(GLenum,const GLhalfNV*){printMissingFunctionError("glMultiTexCoord4hvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord4iARB(GLenum,GLint,GLint,GLint,GLint){printMissingFunctionError("glMultiTexCoord4iARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord4i(GLenum,GLint,GLint,GLint,GLint){printMissingFunctionError("glMultiTexCoord4i");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord4ivARB(GLenum,const GLint*){printMissingFunctionError("glMultiTexCoord4ivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord4iv(GLenum,const GLint*){printMissingFunctionError("glMultiTexCoord4iv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord4sARB(GLenum,GLshort,GLshort,GLshort,GLshort){printMissingFunctionError("glMultiTexCoord4sARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord4s(GLenum,GLshort,GLshort,GLshort,GLshort){printMissingFunctionError("glMultiTexCoord4s");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord4svARB(GLenum,const GLshort*){printMissingFunctionError("glMultiTexCoord4svARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord4sv(GLenum,const GLshort*){printMissingFunctionError("glMultiTexCoord4sv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord4xOES(GLenum,GLfixed,GLfixed,GLfixed,GLfixed){printMissingFunctionError("glMultiTexCoord4xOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoord4xvOES(GLenum,const GLfixed*){printMissingFunctionError("glMultiTexCoord4xvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoordP1ui(GLenum,GLenum,GLuint){printMissingFunctionError("glMultiTexCoordP1ui");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoordP1uiv(GLenum,GLenum,const GLuint*){printMissingFunctionError("glMultiTexCoordP1uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoordP2ui(GLenum,GLenum,GLuint){printMissingFunctionError("glMultiTexCoordP2ui");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoordP2uiv(GLenum,GLenum,const GLuint*){printMissingFunctionError("glMultiTexCoordP2uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoordP3ui(GLenum,GLenum,GLuint){printMissingFunctionError("glMultiTexCoordP3ui");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoordP3uiv(GLenum,GLenum,const GLuint*){printMissingFunctionError("glMultiTexCoordP3uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoordP4ui(GLenum,GLenum,GLuint){printMissingFunctionError("glMultiTexCoordP4ui");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoordP4uiv(GLenum,GLenum,const GLuint*){printMissingFunctionError("glMultiTexCoordP4uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexCoordPointerEXT(GLenum,GLint,GLenum,GLsizei,const void*){printMissingFunctionError("glMultiTexCoordPointerEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexEnvfEXT(GLenum,GLenum,GLenum,GLfloat){printMissingFunctionError("glMultiTexEnvfEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexEnvfvEXT(GLenum,GLenum,GLenum,const GLfloat*){printMissingFunctionError("glMultiTexEnvfvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexEnviEXT(GLenum,GLenum,GLenum,GLint){printMissingFunctionError("glMultiTexEnviEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexEnvivEXT(GLenum,GLenum,GLenum,const GLint*){printMissingFunctionError("glMultiTexEnvivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexGendEXT(GLenum,GLenum,GLenum,GLdouble){printMissingFunctionError("glMultiTexGendEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexGendvEXT(GLenum,GLenum,GLenum,const GLdouble*){printMissingFunctionError("glMultiTexGendvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexGenfEXT(GLenum,GLenum,GLenum,GLfloat){printMissingFunctionError("glMultiTexGenfEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexGenfvEXT(GLenum,GLenum,GLenum,const GLfloat*){printMissingFunctionError("glMultiTexGenfvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexGeniEXT(GLenum,GLenum,GLenum,GLint){printMissingFunctionError("glMultiTexGeniEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexGenivEXT(GLenum,GLenum,GLenum,const GLint*){printMissingFunctionError("glMultiTexGenivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexImage1DEXT(GLenum,GLenum,GLint,GLint,GLsizei,GLint,GLenum,GLenum,const void*){printMissingFunctionError("glMultiTexImage1DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexImage2DEXT(GLenum,GLenum,GLint,GLint,GLsizei,GLsizei,GLint,GLenum,GLenum,const void*){printMissingFunctionError("glMultiTexImage2DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexImage3DEXT(GLenum,GLenum,GLint,GLint,GLsizei,GLsizei,GLsizei,GLint,GLenum,GLenum,const void*){printMissingFunctionError("glMultiTexImage3DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexParameterfEXT(GLenum,GLenum,GLenum,GLfloat){printMissingFunctionError("glMultiTexParameterfEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexParameterfvEXT(GLenum,GLenum,GLenum,const GLfloat*){printMissingFunctionError("glMultiTexParameterfvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexParameteriEXT(GLenum,GLenum,GLenum,GLint){printMissingFunctionError("glMultiTexParameteriEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexParameterIivEXT(GLenum,GLenum,GLenum,const GLint*){printMissingFunctionError("glMultiTexParameterIivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexParameterIuivEXT(GLenum,GLenum,GLenum,const GLuint*){printMissingFunctionError("glMultiTexParameterIuivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexParameterivEXT(GLenum,GLenum,GLenum,const GLint*){printMissingFunctionError("glMultiTexParameterivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexRenderbufferEXT(GLenum,GLenum,GLuint){printMissingFunctionError("glMultiTexRenderbufferEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexSubImage1DEXT(GLenum,GLenum,GLint,GLint,GLsizei,GLenum,GLenum,const void*){printMissingFunctionError("glMultiTexSubImage1DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexSubImage2DEXT(GLenum,GLenum,GLint,GLint,GLint,GLsizei,GLsizei,GLenum,GLenum,const void*){printMissingFunctionError("glMultiTexSubImage2DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultiTexSubImage3DEXT(GLenum,GLenum,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLenum,GLenum,const void*){printMissingFunctionError("glMultiTexSubImage3DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultMatrixd(const GLdouble*){printMissingFunctionError("glMultMatrixd");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultMatrixf(const GLfloat*){printMissingFunctionError("glMultMatrixf");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultMatrixxOES(const GLfixed*){printMissingFunctionError("glMultMatrixxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultTransposeMatrixdARB(const GLdouble*){printMissingFunctionError("glMultTransposeMatrixdARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultTransposeMatrixd(const GLdouble){printMissingFunctionError("glMultTransposeMatrixd");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultTransposeMatrixfARB(const GLfloat*){printMissingFunctionError("glMultTransposeMatrixfARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultTransposeMatrixf(const GLfloat){printMissingFunctionError("glMultTransposeMatrixf");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglMultTransposeMatrixxOES(const GLfixed*){printMissingFunctionError("glMultTransposeMatrixxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNamedBufferDataEXT(GLuint,GLsizeiptr,const void*,GLenum){printMissingFunctionError("glNamedBufferDataEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNamedBufferData(GLuint,GLsizeiptr,const void*,GLenum){printMissingFunctionError("glNamedBufferData");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNamedBufferPageCommitmentARB(GLuint,GLintptr,GLsizeiptr,GLboolean){printMissingFunctionError("glNamedBufferPageCommitmentARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNamedBufferPageCommitmentEXT(GLuint,GLintptr,GLsizeiptr,GLboolean){printMissingFunctionError("glNamedBufferPageCommitmentEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNamedBufferStorageEXT(GLuint,GLsizeiptr,const void*,GLbitfield){printMissingFunctionError("glNamedBufferStorageEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNamedBufferStorage(GLuint,GLsizeiptr,const void*,GLbitfield){printMissingFunctionError("glNamedBufferStorage");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNamedBufferSubDataEXT(GLuint,GLintptr,GLsizeiptr,const void*){printMissingFunctionError("glNamedBufferSubDataEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNamedBufferSubData(GLuint,GLintptr,GLsizeiptr,const void*){printMissingFunctionError("glNamedBufferSubData");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNamedCopyBufferSubDataEXT(GLuint,GLuint,GLintptr,GLintptr,GLsizeiptr){printMissingFunctionError("glNamedCopyBufferSubDataEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNamedFramebufferDrawBuffer(GLuint,GLenum){printMissingFunctionError("glNamedFramebufferDrawBuffer");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNamedFramebufferDrawBuffers(GLuint,GLsizei,const GLenum*){printMissingFunctionError("glNamedFramebufferDrawBuffers");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNamedFramebufferParameteriEXT(GLuint,GLenum,GLint){printMissingFunctionError("glNamedFramebufferParameteriEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNamedFramebufferParameteri(GLuint,GLenum,GLint){printMissingFunctionError("glNamedFramebufferParameteri");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNamedFramebufferReadBuffer(GLuint,GLenum){printMissingFunctionError("glNamedFramebufferReadBuffer");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNamedFramebufferRenderbufferEXT(GLuint,GLenum,GLenum,GLuint){printMissingFunctionError("glNamedFramebufferRenderbufferEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNamedFramebufferRenderbuffer(GLuint,GLenum,GLenum,GLuint){printMissingFunctionError("glNamedFramebufferRenderbuffer");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNamedFramebufferSampleLocationsfvARB(GLuint,GLuint,GLsizei,const GLfloat*){printMissingFunctionError("glNamedFramebufferSampleLocationsfvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNamedFramebufferSampleLocationsfvNV(GLuint,GLuint,GLsizei,const GLfloat*){printMissingFunctionError("glNamedFramebufferSampleLocationsfvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNamedFramebufferTexture1DEXT(GLuint,GLenum,GLenum,GLuint,GLint){printMissingFunctionError("glNamedFramebufferTexture1DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNamedFramebufferTexture2DEXT(GLuint,GLenum,GLenum,GLuint,GLint){printMissingFunctionError("glNamedFramebufferTexture2DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNamedFramebufferTexture3DEXT(GLuint,GLenum,GLenum,GLuint,GLint,GLint){printMissingFunctionError("glNamedFramebufferTexture3DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNamedFramebufferTextureEXT(GLuint,GLenum,GLuint,GLint){printMissingFunctionError("glNamedFramebufferTextureEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNamedFramebufferTextureFaceEXT(GLuint,GLenum,GLuint,GLint,GLenum){printMissingFunctionError("glNamedFramebufferTextureFaceEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNamedFramebufferTexture(GLuint,GLenum,GLuint,GLint){printMissingFunctionError("glNamedFramebufferTexture");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNamedFramebufferTextureLayerEXT(GLuint,GLenum,GLuint,GLint,GLint){printMissingFunctionError("glNamedFramebufferTextureLayerEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNamedFramebufferTextureLayer(GLuint,GLenum,GLuint,GLint,GLint){printMissingFunctionError("glNamedFramebufferTextureLayer");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNamedProgramLocalParameter4dEXT(GLuint,GLenum,GLuint,GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glNamedProgramLocalParameter4dEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNamedProgramLocalParameter4dvEXT(GLuint,GLenum,GLuint,const GLdouble*){printMissingFunctionError("glNamedProgramLocalParameter4dvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNamedProgramLocalParameter4fEXT(GLuint,GLenum,GLuint,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glNamedProgramLocalParameter4fEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNamedProgramLocalParameter4fvEXT(GLuint,GLenum,GLuint,const GLfloat*){printMissingFunctionError("glNamedProgramLocalParameter4fvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNamedProgramLocalParameterI4iEXT(GLuint,GLenum,GLuint,GLint,GLint,GLint,GLint){printMissingFunctionError("glNamedProgramLocalParameterI4iEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNamedProgramLocalParameterI4ivEXT(GLuint,GLenum,GLuint,const GLint*){printMissingFunctionError("glNamedProgramLocalParameterI4ivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNamedProgramLocalParameterI4uiEXT(GLuint,GLenum,GLuint,GLuint,GLuint,GLuint,GLuint){printMissingFunctionError("glNamedProgramLocalParameterI4uiEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNamedProgramLocalParameterI4uivEXT(GLuint,GLenum,GLuint,const GLuint*){printMissingFunctionError("glNamedProgramLocalParameterI4uivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNamedProgramLocalParameters4fvEXT(GLuint,GLenum,GLuint,GLsizei,const GLfloat*){printMissingFunctionError("glNamedProgramLocalParameters4fvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNamedProgramLocalParametersI4ivEXT(GLuint,GLenum,GLuint,GLsizei,const GLint*){printMissingFunctionError("glNamedProgramLocalParametersI4ivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNamedProgramLocalParametersI4uivEXT(GLuint,GLenum,GLuint,GLsizei,const GLuint*){printMissingFunctionError("glNamedProgramLocalParametersI4uivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNamedProgramStringEXT(GLuint,GLenum,GLenum,GLsizei,const void*){printMissingFunctionError("glNamedProgramStringEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNamedRenderbufferStorageEXT(GLuint,GLenum,GLsizei,GLsizei){printMissingFunctionError("glNamedRenderbufferStorageEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNamedRenderbufferStorage(GLuint,GLenum,GLsizei,GLsizei){printMissingFunctionError("glNamedRenderbufferStorage");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNamedRenderbufferStorageMultisampleCoverageEXT(GLuint,GLsizei,GLsizei,GLenum,GLsizei,GLsizei){printMissingFunctionError("glNamedRenderbufferStorageMultisampleCoverageEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNamedRenderbufferStorageMultisampleEXT(GLuint,GLsizei,GLenum,GLsizei,GLsizei){printMissingFunctionError("glNamedRenderbufferStorageMultisampleEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNamedRenderbufferStorageMultisample(GLuint,GLsizei,GLenum,GLsizei,GLsizei){printMissingFunctionError("glNamedRenderbufferStorageMultisample");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNamedStringARB(GLenum,GLint,const GLchar*,GLint,const GLchar*){printMissingFunctionError("glNamedStringARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNewList(GLuint,GLenum){printMissingFunctionError("glNewList");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNormal3b(GLbyte,GLbyte,GLbyte){printMissingFunctionError("glNormal3b");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNormal3bv(const GLbyte*){printMissingFunctionError("glNormal3bv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNormal3d(GLdouble,GLdouble,GLdouble){printMissingFunctionError("glNormal3d");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNormal3dv(const GLdouble*){printMissingFunctionError("glNormal3dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNormal3f(GLfloat,GLfloat,GLfloat){printMissingFunctionError("glNormal3f");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNormal3fv(const GLfloat*){printMissingFunctionError("glNormal3fv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNormal3fVertex3fSUN(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glNormal3fVertex3fSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNormal3fVertex3fvSUN(const GLfloat*,const GLfloat*){printMissingFunctionError("glNormal3fVertex3fvSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNormal3hNV(GLhalfNV,GLhalfNV,GLhalfNV){printMissingFunctionError("glNormal3hNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNormal3hvNV(const GLhalfNV*){printMissingFunctionError("glNormal3hvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNormal3i(GLint,GLint,GLint){printMissingFunctionError("glNormal3i");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNormal3iv(const GLint*){printMissingFunctionError("glNormal3iv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNormal3s(GLshort,GLshort,GLshort){printMissingFunctionError("glNormal3s");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNormal3sv(const GLshort*){printMissingFunctionError("glNormal3sv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNormal3xOES(GLfixed,GLfixed,GLfixed){printMissingFunctionError("glNormal3xOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNormal3xvOES(const GLfixed*){printMissingFunctionError("glNormal3xvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNormalFormatNV(GLenum,GLsizei){printMissingFunctionError("glNormalFormatNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNormalP3ui(GLenum,GLuint){printMissingFunctionError("glNormalP3ui");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNormalP3uiv(GLenum,const GLuint*){printMissingFunctionError("glNormalP3uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNormalPointerEXT(GLenum,GLsizei,GLsizei,const void*){printMissingFunctionError("glNormalPointerEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNormalPointer(GLenum,GLsizei,const GLvoid*){printMissingFunctionError("glNormalPointer");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNormalPointerListIBM(GLenum,GLint,const void**,GLint){printMissingFunctionError("glNormalPointerListIBM");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNormalPointervINTEL(GLenum,const void**){printMissingFunctionError("glNormalPointervINTEL");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNormalStream3bATI(GLenum,GLbyte,GLbyte,GLbyte){printMissingFunctionError("glNormalStream3bATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNormalStream3bvATI(GLenum,const GLbyte*){printMissingFunctionError("glNormalStream3bvATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNormalStream3dATI(GLenum,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glNormalStream3dATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNormalStream3dvATI(GLenum,const GLdouble*){printMissingFunctionError("glNormalStream3dvATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNormalStream3fATI(GLenum,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glNormalStream3fATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNormalStream3fvATI(GLenum,const GLfloat*){printMissingFunctionError("glNormalStream3fvATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNormalStream3iATI(GLenum,GLint,GLint,GLint){printMissingFunctionError("glNormalStream3iATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNormalStream3ivATI(GLenum,const GLint*){printMissingFunctionError("glNormalStream3ivATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNormalStream3sATI(GLenum,GLshort,GLshort,GLshort){printMissingFunctionError("glNormalStream3sATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglNormalStream3svATI(GLenum,const GLshort*){printMissingFunctionError("glNormalStream3svATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglObjectLabel(GLenum,GLuint,GLsizei,const GLchar*){printMissingFunctionError("glObjectLabel");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglObjectPtrLabel(const void*,GLsizei,const GLchar*){printMissingFunctionError("glObjectPtrLabel");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglOrthofOES(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glOrthofOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglOrtho(GLdouble,GLdouble,GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glOrtho");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglOrthoxOES(GLfixed,GLfixed,GLfixed,GLfixed,GLfixed,GLfixed){printMissingFunctionError("glOrthoxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPassTexCoordATI(GLuint,GLuint,GLenum){printMissingFunctionError("glPassTexCoordATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPassThrough(GLfloat){printMissingFunctionError("glPassThrough");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPassThroughxOES(GLfixed){printMissingFunctionError("glPassThroughxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPatchParameterfv(GLenum,const GLfloat*){printMissingFunctionError("glPatchParameterfv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPatchParameteri(GLenum,GLint){printMissingFunctionError("glPatchParameteri");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPathColorGenNV(GLenum,GLenum,GLenum,const GLfloat*){printMissingFunctionError("glPathColorGenNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPathCommandsNV(GLuint,GLsizei,const GLubyte*,GLsizei,GLenum,const void*){printMissingFunctionError("glPathCommandsNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPathCoordsNV(GLuint,GLsizei,GLenum,const void*){printMissingFunctionError("glPathCoordsNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPathCoverDepthFuncNV(GLenum){printMissingFunctionError("glPathCoverDepthFuncNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPathDashArrayNV(GLuint,GLsizei,const GLfloat*){printMissingFunctionError("glPathDashArrayNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPathFogGenNV(GLenum){printMissingFunctionError("glPathFogGenNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPathGlyphRangeNV(GLuint,GLenum,const void*,GLbitfield,GLuint,GLsizei,GLenum,GLuint,GLfloat){printMissingFunctionError("glPathGlyphRangeNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPathGlyphsNV(GLuint,GLenum,const void*,GLbitfield,GLsizei,GLenum,const void*,GLenum,GLuint,GLfloat){printMissingFunctionError("glPathGlyphsNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPathParameterfNV(GLuint,GLenum,GLfloat){printMissingFunctionError("glPathParameterfNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPathParameterfvNV(GLuint,GLenum,const GLfloat*){printMissingFunctionError("glPathParameterfvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPathParameteriNV(GLuint,GLenum,GLint){printMissingFunctionError("glPathParameteriNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPathParameterivNV(GLuint,GLenum,const GLint*){printMissingFunctionError("glPathParameterivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPathStencilDepthOffsetNV(GLfloat,GLfloat){printMissingFunctionError("glPathStencilDepthOffsetNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPathStencilFuncNV(GLenum,GLint,GLuint){printMissingFunctionError("glPathStencilFuncNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPathStringNV(GLuint,GLenum,GLsizei,const void*){printMissingFunctionError("glPathStringNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPathSubCommandsNV(GLuint,GLsizei,GLsizei,GLsizei,const GLubyte*,GLsizei,GLenum,const void*){printMissingFunctionError("glPathSubCommandsNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPathSubCoordsNV(GLuint,GLsizei,GLsizei,GLenum,const void*){printMissingFunctionError("glPathSubCoordsNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPathTexGenNV(GLenum,GLenum,GLint,const GLfloat*){printMissingFunctionError("glPathTexGenNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPauseTransformFeedback(){printMissingFunctionError("glPauseTransformFeedback");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPauseTransformFeedbackNV(){printMissingFunctionError("glPauseTransformFeedbackNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPixelDataRangeNV(GLenum,GLsizei,const void*){printMissingFunctionError("glPixelDataRangeNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPixelMapfv(GLenum,GLsizei,const GLfloat*){printMissingFunctionError("glPixelMapfv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPixelMapuiv(GLenum,GLsizei,const GLuint*){printMissingFunctionError("glPixelMapuiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPixelMapusv(GLenum,GLsizei,const GLushort*){printMissingFunctionError("glPixelMapusv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPixelMapx(GLenum,GLint,const GLfixed*){printMissingFunctionError("glPixelMapx");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPixelStoref(GLenum,GLfloat){printMissingFunctionError("glPixelStoref");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPixelStorei(GLenum,GLint){printMissingFunctionError("glPixelStorei");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPixelStorex(GLenum,GLfixed){printMissingFunctionError("glPixelStorex");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPixelTexGenParameterfSGIS(GLenum,GLfloat){printMissingFunctionError("glPixelTexGenParameterfSGIS");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPixelTexGenParameterfvSGIS(GLenum,const GLfloat*){printMissingFunctionError("glPixelTexGenParameterfvSGIS");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPixelTexGenParameteriSGIS(GLenum,GLint){printMissingFunctionError("glPixelTexGenParameteriSGIS");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPixelTexGenParameterivSGIS(GLenum,const GLint*){printMissingFunctionError("glPixelTexGenParameterivSGIS");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPixelTexGenSGIX(GLenum){printMissingFunctionError("glPixelTexGenSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPixelTransferf(GLenum,GLfloat){printMissingFunctionError("glPixelTransferf");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPixelTransferi(GLenum,GLint){printMissingFunctionError("glPixelTransferi");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPixelTransferxOES(GLenum,GLfixed){printMissingFunctionError("glPixelTransferxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPixelTransformParameterfEXT(GLenum,GLenum,GLfloat){printMissingFunctionError("glPixelTransformParameterfEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPixelTransformParameterfvEXT(GLenum,GLenum,const GLfloat*){printMissingFunctionError("glPixelTransformParameterfvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPixelTransformParameteriEXT(GLenum,GLenum,GLint){printMissingFunctionError("glPixelTransformParameteriEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPixelTransformParameterivEXT(GLenum,GLenum,const GLint*){printMissingFunctionError("glPixelTransformParameterivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPixelZoom(GLfloat,GLfloat){printMissingFunctionError("glPixelZoom");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPixelZoomxOES(GLfixed,GLfixed){printMissingFunctionError("glPixelZoomxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPNTrianglesfATI(GLenum,GLfloat){printMissingFunctionError("glPNTrianglesfATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPNTrianglesiATI(GLenum,GLint){printMissingFunctionError("glPNTrianglesiATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPointParameterfARB(GLenum,GLfloat){printMissingFunctionError("glPointParameterfARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPointParameterfEXT(GLenum,GLfloat){printMissingFunctionError("glPointParameterfEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPointParameterf(GLenum,GLfloat){printMissingFunctionError("glPointParameterf");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPointParameterfSGIS(GLenum,GLfloat){printMissingFunctionError("glPointParameterfSGIS");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPointParameterfvARB(GLenum,const GLfloat*){printMissingFunctionError("glPointParameterfvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPointParameterfvEXT(GLenum,const GLfloat*){printMissingFunctionError("glPointParameterfvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPointParameterfv(GLenum,const GLfloat*){printMissingFunctionError("glPointParameterfv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPointParameterfvSGIS(GLenum,const GLfloat*){printMissingFunctionError("glPointParameterfvSGIS");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPointParameteri(GLenum,GLint){printMissingFunctionError("glPointParameteri");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPointParameteriNV(GLenum,GLint){printMissingFunctionError("glPointParameteriNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPointParameteriv(GLenum,const GLint*){printMissingFunctionError("glPointParameteriv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPointParameterivNV(GLenum,const GLint*){printMissingFunctionError("glPointParameterivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPointParameterxvOES(GLenum,const GLfixed*){printMissingFunctionError("glPointParameterxvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPointSize(GLfloat){printMissingFunctionError("glPointSize");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPointSizexOES(GLfixed){printMissingFunctionError("glPointSizexOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPolygonMode(GLenum,GLenum){printMissingFunctionError("glPolygonMode");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPolygonOffsetClampEXT(GLfloat,GLfloat,GLfloat){printMissingFunctionError("glPolygonOffsetClampEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPolygonOffsetEXT(GLfloat,GLfloat){printMissingFunctionError("glPolygonOffsetEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPolygonOffset(GLfloat,GLfloat){printMissingFunctionError("glPolygonOffset");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPolygonOffsetxOES(GLfixed,GLfixed){printMissingFunctionError("glPolygonOffsetxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPolygonStipple(const GLubyte*){printMissingFunctionError("glPolygonStipple");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPopAttrib(){printMissingFunctionError("glPopAttrib");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPopClientAttrib(){printMissingFunctionError("glPopClientAttrib");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPopDebugGroup(){printMissingFunctionError("glPopDebugGroup");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPopGroupMarkerEXT(){printMissingFunctionError("glPopGroupMarkerEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPopMatrix(){printMissingFunctionError("glPopMatrix");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPopName(){printMissingFunctionError("glPopName");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPresentFrameDualFillNV(GLuint,GLuint64EXT,GLuint,GLuint,GLenum,GLenum,GLuint,GLenum,GLuint,GLenum,GLuint,GLenum,GLuint){printMissingFunctionError("glPresentFrameDualFillNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPresentFrameKeyedNV(GLuint,GLuint64EXT,GLuint,GLuint,GLenum,GLenum,GLuint,GLuint,GLenum,GLuint,GLuint){printMissingFunctionError("glPresentFrameKeyedNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPrimitiveBoundingBoxARB(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glPrimitiveBoundingBoxARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPrimitiveRestartIndex(GLuint){printMissingFunctionError("glPrimitiveRestartIndex");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPrimitiveRestartIndexNV(GLuint){printMissingFunctionError("glPrimitiveRestartIndexNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPrimitiveRestartNV(){printMissingFunctionError("glPrimitiveRestartNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPrioritizeTexturesEXT(GLsizei,const GLuint*,const GLclampf*){printMissingFunctionError("glPrioritizeTexturesEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPrioritizeTextures(GLsizei,const GLuint*,const GLclampf*){printMissingFunctionError("glPrioritizeTextures");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPrioritizeTexturesxOES(GLsizei,const GLuint*,const GLfixed*){printMissingFunctionError("glPrioritizeTexturesxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramBinary(GLuint,GLenum,const void*,GLsizei){printMissingFunctionError("glProgramBinary");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramBufferParametersfvNV(GLenum,GLuint,GLuint,GLsizei,const GLfloat*){printMissingFunctionError("glProgramBufferParametersfvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramBufferParametersIivNV(GLenum,GLuint,GLuint,GLsizei,const GLint*){printMissingFunctionError("glProgramBufferParametersIivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramBufferParametersIuivNV(GLenum,GLuint,GLuint,GLsizei,const GLuint*){printMissingFunctionError("glProgramBufferParametersIuivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramEnvParameter4dARB(GLenum,GLuint,GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glProgramEnvParameter4dARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramEnvParameter4dvARB(GLenum,GLuint,const GLdouble*){printMissingFunctionError("glProgramEnvParameter4dvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramEnvParameter4fARB(GLenum,GLuint,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glProgramEnvParameter4fARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramEnvParameter4fvARB(GLenum,GLuint,const GLfloat*){printMissingFunctionError("glProgramEnvParameter4fvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramEnvParameterI4iNV(GLenum,GLuint,GLint,GLint,GLint,GLint){printMissingFunctionError("glProgramEnvParameterI4iNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramEnvParameterI4ivNV(GLenum,GLuint,const GLint*){printMissingFunctionError("glProgramEnvParameterI4ivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramEnvParameterI4uiNV(GLenum,GLuint,GLuint,GLuint,GLuint,GLuint){printMissingFunctionError("glProgramEnvParameterI4uiNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramEnvParameterI4uivNV(GLenum,GLuint,const GLuint*){printMissingFunctionError("glProgramEnvParameterI4uivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramEnvParameters4fvEXT(GLenum,GLuint,GLsizei,const GLfloat*){printMissingFunctionError("glProgramEnvParameters4fvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramEnvParametersI4ivNV(GLenum,GLuint,GLsizei,const GLint*){printMissingFunctionError("glProgramEnvParametersI4ivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramEnvParametersI4uivNV(GLenum,GLuint,GLsizei,const GLuint*){printMissingFunctionError("glProgramEnvParametersI4uivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramLocalParameter4dARB(GLenum,GLuint,GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glProgramLocalParameter4dARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramLocalParameter4dvARB(GLenum,GLuint,const GLdouble*){printMissingFunctionError("glProgramLocalParameter4dvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramLocalParameter4fARB(GLenum,GLuint,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glProgramLocalParameter4fARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramLocalParameter4fvARB(GLenum,GLuint,const GLfloat*){printMissingFunctionError("glProgramLocalParameter4fvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramLocalParameterI4iNV(GLenum,GLuint,GLint,GLint,GLint,GLint){printMissingFunctionError("glProgramLocalParameterI4iNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramLocalParameterI4ivNV(GLenum,GLuint,const GLint*){printMissingFunctionError("glProgramLocalParameterI4ivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramLocalParameterI4uiNV(GLenum,GLuint,GLuint,GLuint,GLuint,GLuint){printMissingFunctionError("glProgramLocalParameterI4uiNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramLocalParameterI4uivNV(GLenum,GLuint,const GLuint*){printMissingFunctionError("glProgramLocalParameterI4uivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramLocalParameters4fvEXT(GLenum,GLuint,GLsizei,const GLfloat*){printMissingFunctionError("glProgramLocalParameters4fvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramLocalParametersI4ivNV(GLenum,GLuint,GLsizei,const GLint*){printMissingFunctionError("glProgramLocalParametersI4ivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramLocalParametersI4uivNV(GLenum,GLuint,GLsizei,const GLuint*){printMissingFunctionError("glProgramLocalParametersI4uivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramNamedParameter4dNV(GLuint,GLsizei,const GLubyte*,GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glProgramNamedParameter4dNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramNamedParameter4dvNV(GLuint,GLsizei,const GLubyte*,const GLdouble*){printMissingFunctionError("glProgramNamedParameter4dvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramNamedParameter4fNV(GLuint,GLsizei,const GLubyte*,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glProgramNamedParameter4fNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramNamedParameter4fvNV(GLuint,GLsizei,const GLubyte*,const GLfloat*){printMissingFunctionError("glProgramNamedParameter4fvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramParameter4dNV(GLenum,GLuint,GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glProgramParameter4dNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramParameter4dvNV(GLenum,GLuint,const GLdouble*){printMissingFunctionError("glProgramParameter4dvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramParameter4fNV(GLenum,GLuint,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glProgramParameter4fNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramParameter4fvNV(GLenum,GLuint,const GLfloat*){printMissingFunctionError("glProgramParameter4fvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramParameteriARB(GLuint,GLenum,GLint){printMissingFunctionError("glProgramParameteriARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramParameteriEXT(GLuint,GLenum,GLint){printMissingFunctionError("glProgramParameteriEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramParameteri(GLuint,GLenum,GLint){printMissingFunctionError("glProgramParameteri");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramParameters4dvNV(GLenum,GLuint,GLsizei,const GLdouble*){printMissingFunctionError("glProgramParameters4dvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramParameters4fvNV(GLenum,GLuint,GLsizei,const GLfloat*){printMissingFunctionError("glProgramParameters4fvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramPathFragmentInputGenNV(GLuint,GLint,GLenum,GLint,const GLfloat*){printMissingFunctionError("glProgramPathFragmentInputGenNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramStringARB(GLenum,GLenum,GLsizei,const void*){printMissingFunctionError("glProgramStringARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramSubroutineParametersuivNV(GLenum,GLsizei,const GLuint*){printMissingFunctionError("glProgramSubroutineParametersuivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform1dEXT(GLuint,GLint,GLdouble){printMissingFunctionError("glProgramUniform1dEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform1d(GLuint,GLint,GLdouble){printMissingFunctionError("glProgramUniform1d");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform1dvEXT(GLuint,GLint,GLsizei,const GLdouble*){printMissingFunctionError("glProgramUniform1dvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform1dv(GLuint,GLint,GLsizei,const GLdouble*){printMissingFunctionError("glProgramUniform1dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform1fEXT(GLuint,GLint,GLfloat){printMissingFunctionError("glProgramUniform1fEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform1f(GLuint,GLint,GLfloat){printMissingFunctionError("glProgramUniform1f");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform1fvEXT(GLuint,GLint,GLsizei,const GLfloat*){printMissingFunctionError("glProgramUniform1fvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform1fv(GLuint,GLint,GLsizei,const GLfloat*){printMissingFunctionError("glProgramUniform1fv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform1i64ARB(GLuint,GLint,GLint64){printMissingFunctionError("glProgramUniform1i64ARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform1i64NV(GLuint,GLint,GLint64EXT){printMissingFunctionError("glProgramUniform1i64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform1i64vARB(GLuint,GLint,GLsizei,const GLint64*){printMissingFunctionError("glProgramUniform1i64vARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform1i64vNV(GLuint,GLint,GLsizei,const GLint64EXT*){printMissingFunctionError("glProgramUniform1i64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform1iEXT(GLuint,GLint,GLint){printMissingFunctionError("glProgramUniform1iEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform1i(GLuint,GLint,GLint){printMissingFunctionError("glProgramUniform1i");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform1ivEXT(GLuint,GLint,GLsizei,const GLint*){printMissingFunctionError("glProgramUniform1ivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform1iv(GLuint,GLint,GLsizei,const GLint*){printMissingFunctionError("glProgramUniform1iv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform1ui64ARB(GLuint,GLint,GLuint64){printMissingFunctionError("glProgramUniform1ui64ARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform1ui64NV(GLuint,GLint,GLuint64EXT){printMissingFunctionError("glProgramUniform1ui64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform1ui64vARB(GLuint,GLint,GLsizei,const GLuint64*){printMissingFunctionError("glProgramUniform1ui64vARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform1ui64vNV(GLuint,GLint,GLsizei,const GLuint64EXT*){printMissingFunctionError("glProgramUniform1ui64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform1uiEXT(GLuint,GLint,GLuint){printMissingFunctionError("glProgramUniform1uiEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform1ui(GLuint,GLint,GLuint){printMissingFunctionError("glProgramUniform1ui");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform1uivEXT(GLuint,GLint,GLsizei,const GLuint*){printMissingFunctionError("glProgramUniform1uivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform1uiv(GLuint,GLint,GLsizei,const GLuint*){printMissingFunctionError("glProgramUniform1uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform2dEXT(GLuint,GLint,GLdouble,GLdouble){printMissingFunctionError("glProgramUniform2dEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform2d(GLuint,GLint,GLdouble,GLdouble){printMissingFunctionError("glProgramUniform2d");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform2dvEXT(GLuint,GLint,GLsizei,const GLdouble*){printMissingFunctionError("glProgramUniform2dvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform2dv(GLuint,GLint,GLsizei,const GLdouble*){printMissingFunctionError("glProgramUniform2dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform2fEXT(GLuint,GLint,GLfloat,GLfloat){printMissingFunctionError("glProgramUniform2fEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform2f(GLuint,GLint,GLfloat,GLfloat){printMissingFunctionError("glProgramUniform2f");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform2fvEXT(GLuint,GLint,GLsizei,const GLfloat*){printMissingFunctionError("glProgramUniform2fvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform2fv(GLuint,GLint,GLsizei,const GLfloat*){printMissingFunctionError("glProgramUniform2fv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform2i64ARB(GLuint,GLint,GLint64,GLint64){printMissingFunctionError("glProgramUniform2i64ARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform2i64NV(GLuint,GLint,GLint64EXT,GLint64EXT){printMissingFunctionError("glProgramUniform2i64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform2i64vARB(GLuint,GLint,GLsizei,const GLint64*){printMissingFunctionError("glProgramUniform2i64vARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform2i64vNV(GLuint,GLint,GLsizei,const GLint64EXT*){printMissingFunctionError("glProgramUniform2i64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform2iEXT(GLuint,GLint,GLint,GLint){printMissingFunctionError("glProgramUniform2iEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform2i(GLuint,GLint,GLint,GLint){printMissingFunctionError("glProgramUniform2i");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform2ivEXT(GLuint,GLint,GLsizei,const GLint*){printMissingFunctionError("glProgramUniform2ivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform2iv(GLuint,GLint,GLsizei,const GLint*){printMissingFunctionError("glProgramUniform2iv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform2ui64ARB(GLuint,GLint,GLuint64,GLuint64){printMissingFunctionError("glProgramUniform2ui64ARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform2ui64NV(GLuint,GLint,GLuint64EXT,GLuint64EXT){printMissingFunctionError("glProgramUniform2ui64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform2ui64vARB(GLuint,GLint,GLsizei,const GLuint64*){printMissingFunctionError("glProgramUniform2ui64vARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform2ui64vNV(GLuint,GLint,GLsizei,const GLuint64EXT*){printMissingFunctionError("glProgramUniform2ui64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform2uiEXT(GLuint,GLint,GLuint,GLuint){printMissingFunctionError("glProgramUniform2uiEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform2ui(GLuint,GLint,GLuint,GLuint){printMissingFunctionError("glProgramUniform2ui");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform2uivEXT(GLuint,GLint,GLsizei,const GLuint*){printMissingFunctionError("glProgramUniform2uivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform2uiv(GLuint,GLint,GLsizei,const GLuint*){printMissingFunctionError("glProgramUniform2uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform3dEXT(GLuint,GLint,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glProgramUniform3dEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform3d(GLuint,GLint,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glProgramUniform3d");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform3dvEXT(GLuint,GLint,GLsizei,const GLdouble*){printMissingFunctionError("glProgramUniform3dvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform3dv(GLuint,GLint,GLsizei,const GLdouble*){printMissingFunctionError("glProgramUniform3dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform3fEXT(GLuint,GLint,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glProgramUniform3fEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform3f(GLuint,GLint,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glProgramUniform3f");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform3fvEXT(GLuint,GLint,GLsizei,const GLfloat*){printMissingFunctionError("glProgramUniform3fvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform3fv(GLuint,GLint,GLsizei,const GLfloat*){printMissingFunctionError("glProgramUniform3fv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform3i64ARB(GLuint,GLint,GLint64,GLint64,GLint64){printMissingFunctionError("glProgramUniform3i64ARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform3i64NV(GLuint,GLint,GLint64EXT,GLint64EXT,GLint64EXT){printMissingFunctionError("glProgramUniform3i64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform3i64vARB(GLuint,GLint,GLsizei,const GLint64*){printMissingFunctionError("glProgramUniform3i64vARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform3i64vNV(GLuint,GLint,GLsizei,const GLint64EXT*){printMissingFunctionError("glProgramUniform3i64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform3iEXT(GLuint,GLint,GLint,GLint,GLint){printMissingFunctionError("glProgramUniform3iEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform3i(GLuint,GLint,GLint,GLint,GLint){printMissingFunctionError("glProgramUniform3i");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform3ivEXT(GLuint,GLint,GLsizei,const GLint*){printMissingFunctionError("glProgramUniform3ivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform3iv(GLuint,GLint,GLsizei,const GLint*){printMissingFunctionError("glProgramUniform3iv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform3ui64ARB(GLuint,GLint,GLuint64,GLuint64,GLuint64){printMissingFunctionError("glProgramUniform3ui64ARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform3ui64NV(GLuint,GLint,GLuint64EXT,GLuint64EXT,GLuint64EXT){printMissingFunctionError("glProgramUniform3ui64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform3ui64vARB(GLuint,GLint,GLsizei,const GLuint64*){printMissingFunctionError("glProgramUniform3ui64vARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform3ui64vNV(GLuint,GLint,GLsizei,const GLuint64EXT*){printMissingFunctionError("glProgramUniform3ui64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform3uiEXT(GLuint,GLint,GLuint,GLuint,GLuint){printMissingFunctionError("glProgramUniform3uiEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform3ui(GLuint,GLint,GLuint,GLuint,GLuint){printMissingFunctionError("glProgramUniform3ui");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform3uivEXT(GLuint,GLint,GLsizei,const GLuint*){printMissingFunctionError("glProgramUniform3uivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform3uiv(GLuint,GLint,GLsizei,const GLuint*){printMissingFunctionError("glProgramUniform3uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform4dEXT(GLuint,GLint,GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glProgramUniform4dEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform4d(GLuint,GLint,GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glProgramUniform4d");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform4dvEXT(GLuint,GLint,GLsizei,const GLdouble*){printMissingFunctionError("glProgramUniform4dvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform4dv(GLuint,GLint,GLsizei,const GLdouble*){printMissingFunctionError("glProgramUniform4dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform4fEXT(GLuint,GLint,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glProgramUniform4fEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform4f(GLuint,GLint,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glProgramUniform4f");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform4fvEXT(GLuint,GLint,GLsizei,const GLfloat*){printMissingFunctionError("glProgramUniform4fvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform4fv(GLuint,GLint,GLsizei,const GLfloat*){printMissingFunctionError("glProgramUniform4fv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform4i64ARB(GLuint,GLint,GLint64,GLint64,GLint64,GLint64){printMissingFunctionError("glProgramUniform4i64ARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform4i64NV(GLuint,GLint,GLint64EXT,GLint64EXT,GLint64EXT,GLint64EXT){printMissingFunctionError("glProgramUniform4i64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform4i64vARB(GLuint,GLint,GLsizei,const GLint64*){printMissingFunctionError("glProgramUniform4i64vARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform4i64vNV(GLuint,GLint,GLsizei,const GLint64EXT*){printMissingFunctionError("glProgramUniform4i64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform4iEXT(GLuint,GLint,GLint,GLint,GLint,GLint){printMissingFunctionError("glProgramUniform4iEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform4i(GLuint,GLint,GLint,GLint,GLint,GLint){printMissingFunctionError("glProgramUniform4i");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform4ivEXT(GLuint,GLint,GLsizei,const GLint*){printMissingFunctionError("glProgramUniform4ivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform4iv(GLuint,GLint,GLsizei,const GLint*){printMissingFunctionError("glProgramUniform4iv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform4ui64ARB(GLuint,GLint,GLuint64,GLuint64,GLuint64,GLuint64){printMissingFunctionError("glProgramUniform4ui64ARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform4ui64NV(GLuint,GLint,GLuint64EXT,GLuint64EXT,GLuint64EXT,GLuint64EXT){printMissingFunctionError("glProgramUniform4ui64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform4ui64vARB(GLuint,GLint,GLsizei,const GLuint64*){printMissingFunctionError("glProgramUniform4ui64vARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform4ui64vNV(GLuint,GLint,GLsizei,const GLuint64EXT*){printMissingFunctionError("glProgramUniform4ui64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform4uiEXT(GLuint,GLint,GLuint,GLuint,GLuint,GLuint){printMissingFunctionError("glProgramUniform4uiEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform4ui(GLuint,GLint,GLuint,GLuint,GLuint,GLuint){printMissingFunctionError("glProgramUniform4ui");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform4uivEXT(GLuint,GLint,GLsizei,const GLuint*){printMissingFunctionError("glProgramUniform4uivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniform4uiv(GLuint,GLint,GLsizei,const GLuint*){printMissingFunctionError("glProgramUniform4uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniformHandleui64ARB(GLuint,GLint,GLuint64){printMissingFunctionError("glProgramUniformHandleui64ARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniformHandleui64NV(GLuint,GLint,GLuint64){printMissingFunctionError("glProgramUniformHandleui64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniformHandleui64vARB(GLuint,GLint,GLsizei,const GLuint64*){printMissingFunctionError("glProgramUniformHandleui64vARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniformHandleui64vNV(GLuint,GLint,GLsizei,const GLuint64*){printMissingFunctionError("glProgramUniformHandleui64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniformMatrix2dvEXT(GLuint,GLint,GLsizei,GLboolean,const GLdouble*){printMissingFunctionError("glProgramUniformMatrix2dvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniformMatrix2dv(GLuint,GLint,GLsizei,GLboolean,const GLdouble*){printMissingFunctionError("glProgramUniformMatrix2dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniformMatrix2fvEXT(GLuint,GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glProgramUniformMatrix2fvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniformMatrix2fv(GLuint,GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glProgramUniformMatrix2fv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniformMatrix2x3dvEXT(GLuint,GLint,GLsizei,GLboolean,const GLdouble*){printMissingFunctionError("glProgramUniformMatrix2x3dvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniformMatrix2x3dv(GLuint,GLint,GLsizei,GLboolean,const GLdouble*){printMissingFunctionError("glProgramUniformMatrix2x3dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniformMatrix2x3fvEXT(GLuint,GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glProgramUniformMatrix2x3fvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniformMatrix2x3fv(GLuint,GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glProgramUniformMatrix2x3fv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniformMatrix2x4dvEXT(GLuint,GLint,GLsizei,GLboolean,const GLdouble*){printMissingFunctionError("glProgramUniformMatrix2x4dvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniformMatrix2x4dv(GLuint,GLint,GLsizei,GLboolean,const GLdouble*){printMissingFunctionError("glProgramUniformMatrix2x4dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniformMatrix2x4fvEXT(GLuint,GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glProgramUniformMatrix2x4fvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniformMatrix2x4fv(GLuint,GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glProgramUniformMatrix2x4fv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniformMatrix3dvEXT(GLuint,GLint,GLsizei,GLboolean,const GLdouble*){printMissingFunctionError("glProgramUniformMatrix3dvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniformMatrix3dv(GLuint,GLint,GLsizei,GLboolean,const GLdouble*){printMissingFunctionError("glProgramUniformMatrix3dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniformMatrix3fvEXT(GLuint,GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glProgramUniformMatrix3fvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniformMatrix3fv(GLuint,GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glProgramUniformMatrix3fv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniformMatrix3x2dvEXT(GLuint,GLint,GLsizei,GLboolean,const GLdouble*){printMissingFunctionError("glProgramUniformMatrix3x2dvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniformMatrix3x2dv(GLuint,GLint,GLsizei,GLboolean,const GLdouble*){printMissingFunctionError("glProgramUniformMatrix3x2dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniformMatrix3x2fvEXT(GLuint,GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glProgramUniformMatrix3x2fvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniformMatrix3x2fv(GLuint,GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glProgramUniformMatrix3x2fv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniformMatrix3x4dvEXT(GLuint,GLint,GLsizei,GLboolean,const GLdouble*){printMissingFunctionError("glProgramUniformMatrix3x4dvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniformMatrix3x4dv(GLuint,GLint,GLsizei,GLboolean,const GLdouble*){printMissingFunctionError("glProgramUniformMatrix3x4dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniformMatrix3x4fvEXT(GLuint,GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glProgramUniformMatrix3x4fvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniformMatrix3x4fv(GLuint,GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glProgramUniformMatrix3x4fv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniformMatrix4dvEXT(GLuint,GLint,GLsizei,GLboolean,const GLdouble*){printMissingFunctionError("glProgramUniformMatrix4dvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniformMatrix4dv(GLuint,GLint,GLsizei,GLboolean,const GLdouble*){printMissingFunctionError("glProgramUniformMatrix4dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniformMatrix4fvEXT(GLuint,GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glProgramUniformMatrix4fvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniformMatrix4fv(GLuint,GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glProgramUniformMatrix4fv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniformMatrix4x2dvEXT(GLuint,GLint,GLsizei,GLboolean,const GLdouble*){printMissingFunctionError("glProgramUniformMatrix4x2dvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniformMatrix4x2dv(GLuint,GLint,GLsizei,GLboolean,const GLdouble*){printMissingFunctionError("glProgramUniformMatrix4x2dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniformMatrix4x2fvEXT(GLuint,GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glProgramUniformMatrix4x2fvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniformMatrix4x2fv(GLuint,GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glProgramUniformMatrix4x2fv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniformMatrix4x3dvEXT(GLuint,GLint,GLsizei,GLboolean,const GLdouble*){printMissingFunctionError("glProgramUniformMatrix4x3dvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniformMatrix4x3dv(GLuint,GLint,GLsizei,GLboolean,const GLdouble*){printMissingFunctionError("glProgramUniformMatrix4x3dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniformMatrix4x3fvEXT(GLuint,GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glProgramUniformMatrix4x3fvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniformMatrix4x3fv(GLuint,GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glProgramUniformMatrix4x3fv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniformui64NV(GLuint,GLint,GLuint64EXT){printMissingFunctionError("glProgramUniformui64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramUniformui64vNV(GLuint,GLint,GLsizei,const GLuint64EXT*){printMissingFunctionError("glProgramUniformui64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProgramVertexLimitNV(GLenum,GLint){printMissingFunctionError("glProgramVertexLimitNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProvokingVertexEXT(GLenum){printMissingFunctionError("glProvokingVertexEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglProvokingVertex(GLenum){printMissingFunctionError("glProvokingVertex");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPushAttrib(GLbitfield){printMissingFunctionError("glPushAttrib");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPushClientAttribDefaultEXT(GLbitfield){printMissingFunctionError("glPushClientAttribDefaultEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPushClientAttrib(GLbitfield){printMissingFunctionError("glPushClientAttrib");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPushDebugGroup(GLenum,GLuint,GLsizei,const GLchar*){printMissingFunctionError("glPushDebugGroup");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPushGroupMarkerEXT(GLsizei,const GLchar*){printMissingFunctionError("glPushGroupMarkerEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPushMatrix(){printMissingFunctionError("glPushMatrix");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglPushName(GLuint){printMissingFunctionError("glPushName");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglQueryCounter(GLuint,GLenum){printMissingFunctionError("glQueryCounter");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglQueryObjectParameteruiAMD(GLenum,GLuint,GLenum,GLuint){printMissingFunctionError("glQueryObjectParameteruiAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglRasterPos2d(GLdouble,GLdouble){printMissingFunctionError("glRasterPos2d");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglRasterPos2dv(const GLdouble*){printMissingFunctionError("glRasterPos2dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglRasterPos2f(GLfloat,GLfloat){printMissingFunctionError("glRasterPos2f");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglRasterPos2fv(const GLfloat*){printMissingFunctionError("glRasterPos2fv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglRasterPos2i(GLint,GLint){printMissingFunctionError("glRasterPos2i");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglRasterPos2iv(const GLint*){printMissingFunctionError("glRasterPos2iv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglRasterPos2s(GLshort,GLshort){printMissingFunctionError("glRasterPos2s");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglRasterPos2sv(const GLshort*){printMissingFunctionError("glRasterPos2sv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglRasterPos2xOES(GLfixed,GLfixed){printMissingFunctionError("glRasterPos2xOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglRasterPos2xvOES(const GLfixed*){printMissingFunctionError("glRasterPos2xvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglRasterPos3d(GLdouble,GLdouble,GLdouble){printMissingFunctionError("glRasterPos3d");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglRasterPos3dv(const GLdouble*){printMissingFunctionError("glRasterPos3dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglRasterPos3f(GLfloat,GLfloat,GLfloat){printMissingFunctionError("glRasterPos3f");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglRasterPos3fv(const GLfloat*){printMissingFunctionError("glRasterPos3fv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglRasterPos3i(GLint,GLint,GLint){printMissingFunctionError("glRasterPos3i");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglRasterPos3iv(const GLint*){printMissingFunctionError("glRasterPos3iv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglRasterPos3s(GLshort,GLshort,GLshort){printMissingFunctionError("glRasterPos3s");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglRasterPos3sv(const GLshort*){printMissingFunctionError("glRasterPos3sv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglRasterPos3xOES(GLfixed,GLfixed,GLfixed){printMissingFunctionError("glRasterPos3xOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglRasterPos3xvOES(const GLfixed*){printMissingFunctionError("glRasterPos3xvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglRasterPos4d(GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glRasterPos4d");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglRasterPos4dv(const GLdouble*){printMissingFunctionError("glRasterPos4dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglRasterPos4f(GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glRasterPos4f");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglRasterPos4fv(const GLfloat*){printMissingFunctionError("glRasterPos4fv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglRasterPos4i(GLint,GLint,GLint,GLint){printMissingFunctionError("glRasterPos4i");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglRasterPos4iv(const GLint*){printMissingFunctionError("glRasterPos4iv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglRasterPos4s(GLshort,GLshort,GLshort,GLshort){printMissingFunctionError("glRasterPos4s");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglRasterPos4sv(const GLshort*){printMissingFunctionError("glRasterPos4sv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglRasterPos4xOES(GLfixed,GLfixed,GLfixed,GLfixed){printMissingFunctionError("glRasterPos4xOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglRasterPos4xvOES(const GLfixed*){printMissingFunctionError("glRasterPos4xvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglRasterSamplesEXT(GLuint,GLboolean){printMissingFunctionError("glRasterSamplesEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglReadBuffer(GLenum){printMissingFunctionError("glReadBuffer");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglReadInstrumentsSGIX(GLint){printMissingFunctionError("glReadInstrumentsSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglReadnPixelsARB(GLint,GLint,GLsizei,GLsizei,GLenum,GLenum,GLsizei,void*){printMissingFunctionError("glReadnPixelsARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglReadnPixels(GLint,GLint,GLsizei,GLsizei,GLenum,GLenum,GLsizei,void*){printMissingFunctionError("glReadnPixels");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglReadPixels(GLint,GLint,GLsizei,GLsizei,GLenum,GLenum,GLvoid*){printMissingFunctionError("glReadPixels");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglRectd(GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glRectd");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglRectdv(const GLdouble*,const GLdouble*){printMissingFunctionError("glRectdv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglRectf(GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glRectf");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglRectfv(const GLfloat*,const GLfloat*){printMissingFunctionError("glRectfv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglRecti(GLint,GLint,GLint,GLint){printMissingFunctionError("glRecti");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglRectiv(const GLint*,const GLint*){printMissingFunctionError("glRectiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglRects(GLshort,GLshort,GLshort,GLshort){printMissingFunctionError("glRects");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglRectsv(const GLshort*,const GLshort*){printMissingFunctionError("glRectsv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglRectxOES(GLfixed,GLfixed,GLfixed,GLfixed){printMissingFunctionError("glRectxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglRectxvOES(const GLfixed*,const GLfixed*){printMissingFunctionError("glRectxvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglReferencePlaneSGIX(const GLdouble*){printMissingFunctionError("glReferencePlaneSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglReleaseShaderCompiler(){printMissingFunctionError("glReleaseShaderCompiler");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglRenderbufferStorageEXT(GLenum,GLenum,GLsizei,GLsizei){printMissingFunctionError("glRenderbufferStorageEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglRenderbufferStorage(GLenum,GLenum,GLsizei,GLsizei){printMissingFunctionError("glRenderbufferStorage");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglRenderbufferStorageMultisampleCoverageNV(GLenum,GLsizei,GLsizei,GLenum,GLsizei,GLsizei){printMissingFunctionError("glRenderbufferStorageMultisampleCoverageNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglRenderbufferStorageMultisampleEXT(GLenum,GLsizei,GLenum,GLsizei,GLsizei){printMissingFunctionError("glRenderbufferStorageMultisampleEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglRenderbufferStorageMultisample(GLenum,GLsizei,GLenum,GLsizei,GLsizei){printMissingFunctionError("glRenderbufferStorageMultisample");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglReplacementCodePointerSUN(GLenum,GLsizei,const void**){printMissingFunctionError("glReplacementCodePointerSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglReplacementCodeubSUN(GLubyte){printMissingFunctionError("glReplacementCodeubSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglReplacementCodeubvSUN(const GLubyte*){printMissingFunctionError("glReplacementCodeubvSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglReplacementCodeuiColor3fVertex3fSUN(GLuint,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glReplacementCodeuiColor3fVertex3fSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglReplacementCodeuiColor3fVertex3fvSUN(const GLuint*,const GLfloat*,const GLfloat*){printMissingFunctionError("glReplacementCodeuiColor3fVertex3fvSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglReplacementCodeuiColor4fNormal3fVertex3fSUN(GLuint,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glReplacementCodeuiColor4fNormal3fVertex3fSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglReplacementCodeuiColor4fNormal3fVertex3fvSUN(const GLuint*,const GLfloat*,const GLfloat*,const GLfloat*){printMissingFunctionError("glReplacementCodeuiColor4fNormal3fVertex3fvSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglReplacementCodeuiColor4ubVertex3fSUN(GLuint,GLubyte,GLubyte,GLubyte,GLubyte,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glReplacementCodeuiColor4ubVertex3fSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglReplacementCodeuiColor4ubVertex3fvSUN(const GLuint*,const GLubyte*,const GLfloat*){printMissingFunctionError("glReplacementCodeuiColor4ubVertex3fvSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglReplacementCodeuiNormal3fVertex3fSUN(GLuint,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glReplacementCodeuiNormal3fVertex3fSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglReplacementCodeuiNormal3fVertex3fvSUN(const GLuint*,const GLfloat*,const GLfloat*){printMissingFunctionError("glReplacementCodeuiNormal3fVertex3fvSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglReplacementCodeuiSUN(GLuint){printMissingFunctionError("glReplacementCodeuiSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN(GLuint,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN(const GLuint*,const GLfloat*,const GLfloat*,const GLfloat*,const GLfloat*){printMissingFunctionError("glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglReplacementCodeuiTexCoord2fNormal3fVertex3fSUN(GLuint,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN(const GLuint*,const GLfloat*,const GLfloat*,const GLfloat*){printMissingFunctionError("glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglReplacementCodeuiTexCoord2fVertex3fSUN(GLuint,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glReplacementCodeuiTexCoord2fVertex3fSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglReplacementCodeuiTexCoord2fVertex3fvSUN(const GLuint*,const GLfloat*,const GLfloat*){printMissingFunctionError("glReplacementCodeuiTexCoord2fVertex3fvSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglReplacementCodeuiVertex3fSUN(GLuint,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glReplacementCodeuiVertex3fSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglReplacementCodeuiVertex3fvSUN(const GLuint*,const GLfloat*){printMissingFunctionError("glReplacementCodeuiVertex3fvSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglReplacementCodeuivSUN(const GLuint*){printMissingFunctionError("glReplacementCodeuivSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglReplacementCodeusSUN(GLushort){printMissingFunctionError("glReplacementCodeusSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglReplacementCodeusvSUN(const GLushort*){printMissingFunctionError("glReplacementCodeusvSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglRequestResidentProgramsNV(GLsizei,const GLuint*){printMissingFunctionError("glRequestResidentProgramsNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglResetHistogramEXT(GLenum){printMissingFunctionError("glResetHistogramEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglResetHistogram(GLenum){printMissingFunctionError("glResetHistogram");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglResetMinmaxEXT(GLenum){printMissingFunctionError("glResetMinmaxEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglResetMinmax(GLenum){printMissingFunctionError("glResetMinmax");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglResizeBuffersMESA(){printMissingFunctionError("glResizeBuffersMESA");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglResolveDepthValuesNV(){printMissingFunctionError("glResolveDepthValuesNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglResumeTransformFeedback(){printMissingFunctionError("glResumeTransformFeedback");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglResumeTransformFeedbackNV(){printMissingFunctionError("glResumeTransformFeedbackNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglRotated(GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glRotated");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglRotatef(GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glRotatef");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglRotatexOES(GLfixed,GLfixed,GLfixed,GLfixed){printMissingFunctionError("glRotatexOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSampleCoverageARB(GLfloat,GLboolean){printMissingFunctionError("glSampleCoverageARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSampleCoverage(GLclampf,GLboolean){printMissingFunctionError("glSampleCoverage");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSampleMapATI(GLuint,GLuint,GLenum){printMissingFunctionError("glSampleMapATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSampleMaskEXT(GLclampf,GLboolean){printMissingFunctionError("glSampleMaskEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSampleMaski(GLuint,GLbitfield){printMissingFunctionError("glSampleMaski");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSampleMaskIndexedNV(GLuint,GLbitfield){printMissingFunctionError("glSampleMaskIndexedNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSampleMaskSGIS(GLclampf,GLboolean){printMissingFunctionError("glSampleMaskSGIS");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSamplePatternEXT(GLenum){printMissingFunctionError("glSamplePatternEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSamplePatternSGIS(GLenum){printMissingFunctionError("glSamplePatternSGIS");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSamplerParameterf(GLuint,GLenum,GLfloat){printMissingFunctionError("glSamplerParameterf");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSamplerParameterfv(GLuint,GLenum,const GLfloat*){printMissingFunctionError("glSamplerParameterfv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSamplerParameteri(GLuint,GLenum,GLint){printMissingFunctionError("glSamplerParameteri");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSamplerParameterIiv(GLuint,GLenum,const GLint*){printMissingFunctionError("glSamplerParameterIiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSamplerParameterIuiv(GLuint,GLenum,const GLuint*){printMissingFunctionError("glSamplerParameterIuiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSamplerParameteriv(GLuint,GLenum,const GLint*){printMissingFunctionError("glSamplerParameteriv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglScaled(GLdouble,GLdouble,GLdouble){printMissingFunctionError("glScaled");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglScalef(GLfloat,GLfloat,GLfloat){printMissingFunctionError("glScalef");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglScalexOES(GLfixed,GLfixed,GLfixed){printMissingFunctionError("glScalexOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglScissorArrayv(GLuint,GLsizei,const GLint*){printMissingFunctionError("glScissorArrayv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglScissor(GLint,GLint,GLsizei,GLsizei){printMissingFunctionError("glScissor");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglScissorIndexed(GLuint,GLint,GLint,GLsizei,GLsizei){printMissingFunctionError("glScissorIndexed");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglScissorIndexedv(GLuint,const GLint*){printMissingFunctionError("glScissorIndexedv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSecondaryColor3bEXT(GLbyte,GLbyte,GLbyte){printMissingFunctionError("glSecondaryColor3bEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSecondaryColor3b(GLbyte,GLbyte,GLbyte){printMissingFunctionError("glSecondaryColor3b");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSecondaryColor3bv(const GLbyte*){printMissingFunctionError("glSecondaryColor3bv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSecondaryColor3bvEXT(const GLbyte*){printMissingFunctionError("glSecondaryColor3bvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSecondaryColor3dEXT(GLdouble,GLdouble,GLdouble){printMissingFunctionError("glSecondaryColor3dEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSecondaryColor3d(GLdouble,GLdouble,GLdouble){printMissingFunctionError("glSecondaryColor3d");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSecondaryColor3dv(const GLdouble*){printMissingFunctionError("glSecondaryColor3dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSecondaryColor3dvEXT(const GLdouble*){printMissingFunctionError("glSecondaryColor3dvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSecondaryColor3fEXT(GLfloat,GLfloat,GLfloat){printMissingFunctionError("glSecondaryColor3fEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSecondaryColor3f(GLfloat,GLfloat,GLfloat){printMissingFunctionError("glSecondaryColor3f");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSecondaryColor3fv(const GLfloat*){printMissingFunctionError("glSecondaryColor3fv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSecondaryColor3fvEXT(const GLfloat*){printMissingFunctionError("glSecondaryColor3fvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSecondaryColor3hNV(GLhalfNV,GLhalfNV,GLhalfNV){printMissingFunctionError("glSecondaryColor3hNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSecondaryColor3hvNV(const GLhalfNV*){printMissingFunctionError("glSecondaryColor3hvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSecondaryColor3iEXT(GLint,GLint,GLint){printMissingFunctionError("glSecondaryColor3iEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSecondaryColor3i(GLint,GLint,GLint){printMissingFunctionError("glSecondaryColor3i");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSecondaryColor3iv(const GLint*){printMissingFunctionError("glSecondaryColor3iv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSecondaryColor3ivEXT(const GLint*){printMissingFunctionError("glSecondaryColor3ivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSecondaryColor3sEXT(GLshort,GLshort,GLshort){printMissingFunctionError("glSecondaryColor3sEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSecondaryColor3s(GLshort,GLshort,GLshort){printMissingFunctionError("glSecondaryColor3s");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSecondaryColor3sv(const GLshort*){printMissingFunctionError("glSecondaryColor3sv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSecondaryColor3svEXT(const GLshort*){printMissingFunctionError("glSecondaryColor3svEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSecondaryColor3ubEXT(GLubyte,GLubyte,GLubyte){printMissingFunctionError("glSecondaryColor3ubEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSecondaryColor3ub(GLubyte,GLubyte,GLubyte){printMissingFunctionError("glSecondaryColor3ub");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSecondaryColor3ubv(const GLubyte*){printMissingFunctionError("glSecondaryColor3ubv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSecondaryColor3ubvEXT(const GLubyte*){printMissingFunctionError("glSecondaryColor3ubvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSecondaryColor3uiEXT(GLuint,GLuint,GLuint){printMissingFunctionError("glSecondaryColor3uiEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSecondaryColor3ui(GLuint,GLuint,GLuint){printMissingFunctionError("glSecondaryColor3ui");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSecondaryColor3uiv(const GLuint*){printMissingFunctionError("glSecondaryColor3uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSecondaryColor3uivEXT(const GLuint*){printMissingFunctionError("glSecondaryColor3uivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSecondaryColor3usEXT(GLushort,GLushort,GLushort){printMissingFunctionError("glSecondaryColor3usEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSecondaryColor3us(GLushort,GLushort,GLushort){printMissingFunctionError("glSecondaryColor3us");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSecondaryColor3usv(const GLushort*){printMissingFunctionError("glSecondaryColor3usv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSecondaryColor3usvEXT(const GLushort*){printMissingFunctionError("glSecondaryColor3usvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSecondaryColorFormatNV(GLint,GLenum,GLsizei){printMissingFunctionError("glSecondaryColorFormatNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSecondaryColorP3ui(GLenum,GLuint){printMissingFunctionError("glSecondaryColorP3ui");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSecondaryColorP3uiv(GLenum,const GLuint*){printMissingFunctionError("glSecondaryColorP3uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSecondaryColorPointerEXT(GLint,GLenum,GLsizei,const void*){printMissingFunctionError("glSecondaryColorPointerEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSecondaryColorPointer(GLint,GLenum,GLsizei,const void*){printMissingFunctionError("glSecondaryColorPointer");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSecondaryColorPointerListIBM(GLint,GLenum,GLint,const void**,GLint){printMissingFunctionError("glSecondaryColorPointerListIBM");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSelectBuffer(GLsizei,GLuint*){printMissingFunctionError("glSelectBuffer");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSelectPerfMonitorCountersAMD(GLuint,GLboolean,GLuint,GLint,GLuint*){printMissingFunctionError("glSelectPerfMonitorCountersAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSeparableFilter2DEXT(GLenum,GLenum,GLsizei,GLsizei,GLenum,GLenum,const void*,const void*){printMissingFunctionError("glSeparableFilter2DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSeparableFilter2D(GLenum,GLenum,GLsizei,GLsizei,GLenum,GLenum,const GLvoid*,const GLvoid*){printMissingFunctionError("glSeparableFilter2D");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSetFenceAPPLE(GLuint){printMissingFunctionError("glSetFenceAPPLE");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSetFenceNV(GLuint,GLenum){printMissingFunctionError("glSetFenceNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSetFragmentShaderConstantATI(GLuint,const GLfloat*){printMissingFunctionError("glSetFragmentShaderConstantATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSetInvariantEXT(GLuint,GLenum,const void*){printMissingFunctionError("glSetInvariantEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSetLocalConstantEXT(GLuint,GLenum,const void*){printMissingFunctionError("glSetLocalConstantEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSetMultisamplefvAMD(GLenum,GLuint,const GLfloat*){printMissingFunctionError("glSetMultisamplefvAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglShadeModel(GLenum){printMissingFunctionError("glShadeModel");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglShaderBinary(GLsizei,const GLuint*,GLenum,const void*,GLsizei){printMissingFunctionError("glShaderBinary");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglShaderOp1EXT(GLenum,GLuint,GLuint){printMissingFunctionError("glShaderOp1EXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglShaderOp2EXT(GLenum,GLuint,GLuint,GLuint){printMissingFunctionError("glShaderOp2EXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglShaderOp3EXT(GLenum,GLuint,GLuint,GLuint,GLuint){printMissingFunctionError("glShaderOp3EXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglShaderSourceARB(GLhandleARB,GLsizei,const GLcharARB**,const GLint*){printMissingFunctionError("glShaderSourceARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglShaderSource(GLuint,GLsizei,const GLchar*const*,const GLint*){printMissingFunctionError("glShaderSource");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglShaderStorageBlockBinding(GLuint,GLuint,GLuint){printMissingFunctionError("glShaderStorageBlockBinding");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSharpenTexFuncSGIS(GLenum,GLsizei,const GLfloat*){printMissingFunctionError("glSharpenTexFuncSGIS");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSpriteParameterfSGIX(GLenum,GLfloat){printMissingFunctionError("glSpriteParameterfSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSpriteParameterfvSGIX(GLenum,const GLfloat*){printMissingFunctionError("glSpriteParameterfvSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSpriteParameteriSGIX(GLenum,GLint){printMissingFunctionError("glSpriteParameteriSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSpriteParameterivSGIX(GLenum,const GLint*){printMissingFunctionError("glSpriteParameterivSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglStartInstrumentsSGIX(){printMissingFunctionError("glStartInstrumentsSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglStateCaptureNV(GLuint,GLenum){printMissingFunctionError("glStateCaptureNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglStencilClearTagEXT(GLsizei,GLuint){printMissingFunctionError("glStencilClearTagEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglStencilFillPathInstancedNV(GLsizei,GLenum,const void*,GLuint,GLenum,GLuint,GLenum,const GLfloat*){printMissingFunctionError("glStencilFillPathInstancedNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglStencilFillPathNV(GLuint,GLenum,GLuint){printMissingFunctionError("glStencilFillPathNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglStencilFunc(GLenum,GLint,GLuint){printMissingFunctionError("glStencilFunc");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglStencilFuncSeparateATI(GLenum,GLenum,GLint,GLuint){printMissingFunctionError("glStencilFuncSeparateATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglStencilFuncSeparate(GLenum,GLenum,GLint,GLuint){printMissingFunctionError("glStencilFuncSeparate");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglStencilMask(GLuint){printMissingFunctionError("glStencilMask");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglStencilMaskSeparate(GLenum,GLuint){printMissingFunctionError("glStencilMaskSeparate");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglStencilOp(GLenum,GLenum,GLenum){printMissingFunctionError("glStencilOp");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglStencilOpSeparateATI(GLenum,GLenum,GLenum,GLenum){printMissingFunctionError("glStencilOpSeparateATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglStencilOpSeparate(GLenum,GLenum,GLenum,GLenum){printMissingFunctionError("glStencilOpSeparate");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglStencilOpValueAMD(GLenum,GLuint){printMissingFunctionError("glStencilOpValueAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglStencilStrokePathInstancedNV(GLsizei,GLenum,const void*,GLuint,GLint,GLuint,GLenum,const GLfloat*){printMissingFunctionError("glStencilStrokePathInstancedNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglStencilStrokePathNV(GLuint,GLint,GLuint){printMissingFunctionError("glStencilStrokePathNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglStencilThenCoverFillPathInstancedNV(GLsizei,GLenum,const void*,GLuint,GLenum,GLuint,GLenum,GLenum,const GLfloat*){printMissingFunctionError("glStencilThenCoverFillPathInstancedNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglStencilThenCoverFillPathNV(GLuint,GLenum,GLuint,GLenum){printMissingFunctionError("glStencilThenCoverFillPathNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglStencilThenCoverStrokePathInstancedNV(GLsizei,GLenum,const void*,GLuint,GLint,GLuint,GLenum,GLenum,const GLfloat*){printMissingFunctionError("glStencilThenCoverStrokePathInstancedNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglStencilThenCoverStrokePathNV(GLuint,GLint,GLuint,GLenum){printMissingFunctionError("glStencilThenCoverStrokePathNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglStopInstrumentsSGIX(GLint){printMissingFunctionError("glStopInstrumentsSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglStringMarkerGREMEDY(GLsizei,const void*){printMissingFunctionError("glStringMarkerGREMEDY");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSubpixelPrecisionBiasNV(GLuint,GLuint){printMissingFunctionError("glSubpixelPrecisionBiasNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSwizzleEXT(GLuint,GLuint,GLenum,GLenum,GLenum,GLenum){printMissingFunctionError("glSwizzleEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglSyncTextureINTEL(GLuint){printMissingFunctionError("glSyncTextureINTEL");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTagSampleBufferSGIX(){printMissingFunctionError("glTagSampleBufferSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTangent3bEXT(GLbyte,GLbyte,GLbyte){printMissingFunctionError("glTangent3bEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTangent3bvEXT(const GLbyte*){printMissingFunctionError("glTangent3bvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTangent3dEXT(GLdouble,GLdouble,GLdouble){printMissingFunctionError("glTangent3dEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTangent3dvEXT(const GLdouble*){printMissingFunctionError("glTangent3dvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTangent3fEXT(GLfloat,GLfloat,GLfloat){printMissingFunctionError("glTangent3fEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTangent3fvEXT(const GLfloat*){printMissingFunctionError("glTangent3fvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTangent3iEXT(GLint,GLint,GLint){printMissingFunctionError("glTangent3iEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTangent3ivEXT(const GLint*){printMissingFunctionError("glTangent3ivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTangent3sEXT(GLshort,GLshort,GLshort){printMissingFunctionError("glTangent3sEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTangent3svEXT(const GLshort*){printMissingFunctionError("glTangent3svEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTangentPointerEXT(GLenum,GLsizei,const void*){printMissingFunctionError("glTangentPointerEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTbufferMask3DFX(GLuint){printMissingFunctionError("glTbufferMask3DFX");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTessellationFactorAMD(GLfloat){printMissingFunctionError("glTessellationFactorAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTessellationModeAMD(GLenum){printMissingFunctionError("glTessellationModeAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexBufferARB(GLenum,GLenum,GLuint){printMissingFunctionError("glTexBufferARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexBufferEXT(GLenum,GLenum,GLuint){printMissingFunctionError("glTexBufferEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexBuffer(GLenum,GLenum,GLuint){printMissingFunctionError("glTexBuffer");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexBufferRange(GLenum,GLenum,GLuint,GLintptr,GLsizeiptr){printMissingFunctionError("glTexBufferRange");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexBumpParameterfvATI(GLenum,const GLfloat*){printMissingFunctionError("glTexBumpParameterfvATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexBumpParameterivATI(GLenum,const GLint*){printMissingFunctionError("glTexBumpParameterivATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord1bOES(GLbyte){printMissingFunctionError("glTexCoord1bOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord1bvOES(const GLbyte*){printMissingFunctionError("glTexCoord1bvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord1d(GLdouble){printMissingFunctionError("glTexCoord1d");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord1dv(const GLdouble*){printMissingFunctionError("glTexCoord1dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord1f(GLfloat){printMissingFunctionError("glTexCoord1f");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord1fv(const GLfloat*){printMissingFunctionError("glTexCoord1fv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord1hNV(GLhalfNV){printMissingFunctionError("glTexCoord1hNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord1hvNV(const GLhalfNV*){printMissingFunctionError("glTexCoord1hvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord1i(GLint){printMissingFunctionError("glTexCoord1i");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord1iv(const GLint*){printMissingFunctionError("glTexCoord1iv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord1s(GLshort){printMissingFunctionError("glTexCoord1s");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord1sv(const GLshort*){printMissingFunctionError("glTexCoord1sv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord1xOES(GLfixed){printMissingFunctionError("glTexCoord1xOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord1xvOES(const GLfixed*){printMissingFunctionError("glTexCoord1xvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord2bOES(GLbyte,GLbyte){printMissingFunctionError("glTexCoord2bOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord2bvOES(const GLbyte*){printMissingFunctionError("glTexCoord2bvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord2d(GLdouble,GLdouble){printMissingFunctionError("glTexCoord2d");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord2dv(const GLdouble*){printMissingFunctionError("glTexCoord2dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord2fColor3fVertex3fSUN(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glTexCoord2fColor3fVertex3fSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord2fColor3fVertex3fvSUN(const GLfloat*,const GLfloat*,const GLfloat*){printMissingFunctionError("glTexCoord2fColor3fVertex3fvSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord2fColor4fNormal3fVertex3fSUN(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glTexCoord2fColor4fNormal3fVertex3fSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord2fColor4fNormal3fVertex3fvSUN(const GLfloat*,const GLfloat*,const GLfloat*,const GLfloat*){printMissingFunctionError("glTexCoord2fColor4fNormal3fVertex3fvSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord2fColor4ubVertex3fSUN(GLfloat,GLfloat,GLubyte,GLubyte,GLubyte,GLubyte,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glTexCoord2fColor4ubVertex3fSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord2fColor4ubVertex3fvSUN(const GLfloat*,const GLubyte*,const GLfloat*){printMissingFunctionError("glTexCoord2fColor4ubVertex3fvSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord2f(GLfloat,GLfloat){printMissingFunctionError("glTexCoord2f");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord2fNormal3fVertex3fSUN(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glTexCoord2fNormal3fVertex3fSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord2fNormal3fVertex3fvSUN(const GLfloat*,const GLfloat*,const GLfloat*){printMissingFunctionError("glTexCoord2fNormal3fVertex3fvSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord2fv(const GLfloat*){printMissingFunctionError("glTexCoord2fv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord2fVertex3fSUN(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glTexCoord2fVertex3fSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord2fVertex3fvSUN(const GLfloat*,const GLfloat*){printMissingFunctionError("glTexCoord2fVertex3fvSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord2hNV(GLhalfNV,GLhalfNV){printMissingFunctionError("glTexCoord2hNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord2hvNV(const GLhalfNV*){printMissingFunctionError("glTexCoord2hvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord2i(GLint,GLint){printMissingFunctionError("glTexCoord2i");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord2iv(const GLint*){printMissingFunctionError("glTexCoord2iv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord2s(GLshort,GLshort){printMissingFunctionError("glTexCoord2s");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord2sv(const GLshort*){printMissingFunctionError("glTexCoord2sv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord2xOES(GLfixed,GLfixed){printMissingFunctionError("glTexCoord2xOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord2xvOES(const GLfixed*){printMissingFunctionError("glTexCoord2xvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord3bOES(GLbyte,GLbyte,GLbyte){printMissingFunctionError("glTexCoord3bOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord3bvOES(const GLbyte*){printMissingFunctionError("glTexCoord3bvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord3d(GLdouble,GLdouble,GLdouble){printMissingFunctionError("glTexCoord3d");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord3dv(const GLdouble*){printMissingFunctionError("glTexCoord3dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord3f(GLfloat,GLfloat,GLfloat){printMissingFunctionError("glTexCoord3f");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord3fv(const GLfloat*){printMissingFunctionError("glTexCoord3fv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord3hNV(GLhalfNV,GLhalfNV,GLhalfNV){printMissingFunctionError("glTexCoord3hNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord3hvNV(const GLhalfNV*){printMissingFunctionError("glTexCoord3hvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord3i(GLint,GLint,GLint){printMissingFunctionError("glTexCoord3i");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord3iv(const GLint*){printMissingFunctionError("glTexCoord3iv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord3s(GLshort,GLshort,GLshort){printMissingFunctionError("glTexCoord3s");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord3sv(const GLshort*){printMissingFunctionError("glTexCoord3sv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord3xOES(GLfixed,GLfixed,GLfixed){printMissingFunctionError("glTexCoord3xOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord3xvOES(const GLfixed*){printMissingFunctionError("glTexCoord3xvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord4bOES(GLbyte,GLbyte,GLbyte,GLbyte){printMissingFunctionError("glTexCoord4bOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord4bvOES(const GLbyte*){printMissingFunctionError("glTexCoord4bvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord4d(GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glTexCoord4d");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord4dv(const GLdouble*){printMissingFunctionError("glTexCoord4dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord4fColor4fNormal3fVertex4fSUN(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glTexCoord4fColor4fNormal3fVertex4fSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord4fColor4fNormal3fVertex4fvSUN(const GLfloat*,const GLfloat*,const GLfloat*,const GLfloat*){printMissingFunctionError("glTexCoord4fColor4fNormal3fVertex4fvSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord4f(GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glTexCoord4f");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord4fv(const GLfloat*){printMissingFunctionError("glTexCoord4fv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord4fVertex4fSUN(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glTexCoord4fVertex4fSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord4fVertex4fvSUN(const GLfloat*,const GLfloat*){printMissingFunctionError("glTexCoord4fVertex4fvSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord4hNV(GLhalfNV,GLhalfNV,GLhalfNV,GLhalfNV){printMissingFunctionError("glTexCoord4hNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord4hvNV(const GLhalfNV*){printMissingFunctionError("glTexCoord4hvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord4i(GLint,GLint,GLint,GLint){printMissingFunctionError("glTexCoord4i");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord4iv(const GLint*){printMissingFunctionError("glTexCoord4iv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord4s(GLshort,GLshort,GLshort,GLshort){printMissingFunctionError("glTexCoord4s");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord4sv(const GLshort*){printMissingFunctionError("glTexCoord4sv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord4xOES(GLfixed,GLfixed,GLfixed,GLfixed){printMissingFunctionError("glTexCoord4xOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoord4xvOES(const GLfixed*){printMissingFunctionError("glTexCoord4xvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoordFormatNV(GLint,GLenum,GLsizei){printMissingFunctionError("glTexCoordFormatNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoordP1ui(GLenum,GLuint){printMissingFunctionError("glTexCoordP1ui");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoordP1uiv(GLenum,const GLuint*){printMissingFunctionError("glTexCoordP1uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoordP2ui(GLenum,GLuint){printMissingFunctionError("glTexCoordP2ui");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoordP2uiv(GLenum,const GLuint*){printMissingFunctionError("glTexCoordP2uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoordP3ui(GLenum,GLuint){printMissingFunctionError("glTexCoordP3ui");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoordP3uiv(GLenum,const GLuint*){printMissingFunctionError("glTexCoordP3uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoordP4ui(GLenum,GLuint){printMissingFunctionError("glTexCoordP4ui");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoordP4uiv(GLenum,const GLuint*){printMissingFunctionError("glTexCoordP4uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoordPointerEXT(GLint,GLenum,GLsizei,GLsizei,const void*){printMissingFunctionError("glTexCoordPointerEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoordPointer(GLint,GLenum,GLsizei,const GLvoid*){printMissingFunctionError("glTexCoordPointer");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoordPointerListIBM(GLint,GLenum,GLint,const void**,GLint){printMissingFunctionError("glTexCoordPointerListIBM");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexCoordPointervINTEL(GLint,GLenum,const void**){printMissingFunctionError("glTexCoordPointervINTEL");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexEnvf(GLenum,GLenum,GLfloat){printMissingFunctionError("glTexEnvf");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexEnvfv(GLenum,GLenum,const GLfloat*){printMissingFunctionError("glTexEnvfv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexEnvi(GLenum,GLenum,GLint){printMissingFunctionError("glTexEnvi");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexEnviv(GLenum,GLenum,const GLint*){printMissingFunctionError("glTexEnviv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexEnvxOES(GLenum,GLenum,GLfixed){printMissingFunctionError("glTexEnvxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexEnvxvOES(GLenum,GLenum,const GLfixed*){printMissingFunctionError("glTexEnvxvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexFilterFuncSGIS(GLenum,GLenum,GLsizei,const GLfloat*){printMissingFunctionError("glTexFilterFuncSGIS");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexGend(GLenum,GLenum,GLdouble){printMissingFunctionError("glTexGend");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexGendv(GLenum,GLenum,const GLdouble*){printMissingFunctionError("glTexGendv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexGenf(GLenum,GLenum,GLfloat){printMissingFunctionError("glTexGenf");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexGenfv(GLenum,GLenum,const GLfloat*){printMissingFunctionError("glTexGenfv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexGeni(GLenum,GLenum,GLint){printMissingFunctionError("glTexGeni");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexGeniv(GLenum,GLenum,const GLint*){printMissingFunctionError("glTexGeniv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexGenxOES(GLenum,GLenum,GLfixed){printMissingFunctionError("glTexGenxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexGenxvOES(GLenum,GLenum,const GLfixed*){printMissingFunctionError("glTexGenxvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexImage1D(GLenum,GLint,GLint,GLsizei,GLint,GLenum,GLenum,const GLvoid*){printMissingFunctionError("glTexImage1D");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexImage2D(GLenum,GLint,GLint,GLsizei,GLsizei,GLint,GLenum,GLenum,const GLvoid*){printMissingFunctionError("glTexImage2D");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexImage2DMultisampleCoverageNV(GLenum,GLsizei,GLsizei,GLint,GLsizei,GLsizei,GLboolean){printMissingFunctionError("glTexImage2DMultisampleCoverageNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexImage2DMultisample(GLenum,GLsizei,GLenum,GLsizei,GLsizei,GLboolean){printMissingFunctionError("glTexImage2DMultisample");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexImage3DEXT(GLenum,GLint,GLenum,GLsizei,GLsizei,GLsizei,GLint,GLenum,GLenum,const void*){printMissingFunctionError("glTexImage3DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexImage3D(GLenum,GLint,GLint,GLsizei,GLsizei,GLsizei,GLint,GLenum,GLenum,const GLvoid*){printMissingFunctionError("glTexImage3D");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexImage3DMultisampleCoverageNV(GLenum,GLsizei,GLsizei,GLint,GLsizei,GLsizei,GLsizei,GLboolean){printMissingFunctionError("glTexImage3DMultisampleCoverageNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexImage3DMultisample(GLenum,GLsizei,GLenum,GLsizei,GLsizei,GLsizei,GLboolean){printMissingFunctionError("glTexImage3DMultisample");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexImage4DSGIS(GLenum,GLint,GLenum,GLsizei,GLsizei,GLsizei,GLsizei,GLint,GLenum,GLenum,const void*){printMissingFunctionError("glTexImage4DSGIS");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexPageCommitmentARB(GLenum,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLboolean){printMissingFunctionError("glTexPageCommitmentARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexParameterf(GLenum,GLenum,GLfloat){printMissingFunctionError("glTexParameterf");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexParameterfv(GLenum,GLenum,const GLfloat*){printMissingFunctionError("glTexParameterfv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexParameteri(GLenum,GLenum,GLint){printMissingFunctionError("glTexParameteri");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexParameterIivEXT(GLenum,GLenum,const GLint*){printMissingFunctionError("glTexParameterIivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexParameterIiv(GLenum,GLenum,const GLint*){printMissingFunctionError("glTexParameterIiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexParameterIuivEXT(GLenum,GLenum,const GLuint*){printMissingFunctionError("glTexParameterIuivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexParameterIuiv(GLenum,GLenum,const GLuint*){printMissingFunctionError("glTexParameterIuiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexParameteriv(GLenum,GLenum,const GLint*){printMissingFunctionError("glTexParameteriv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexParameterxOES(GLenum,GLenum,GLfixed){printMissingFunctionError("glTexParameterxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexParameterxvOES(GLenum,GLenum,const GLfixed*){printMissingFunctionError("glTexParameterxvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexRenderbufferNV(GLenum,GLuint){printMissingFunctionError("glTexRenderbufferNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexStorage1D(GLenum,GLsizei,GLenum,GLsizei){printMissingFunctionError("glTexStorage1D");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexStorage2D(GLenum,GLsizei,GLenum,GLsizei,GLsizei){printMissingFunctionError("glTexStorage2D");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexStorage2DMultisample(GLenum,GLsizei,GLenum,GLsizei,GLsizei,GLboolean){printMissingFunctionError("glTexStorage2DMultisample");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexStorage3D(GLenum,GLsizei,GLenum,GLsizei,GLsizei,GLsizei){printMissingFunctionError("glTexStorage3D");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexStorage3DMultisample(GLenum,GLsizei,GLenum,GLsizei,GLsizei,GLsizei,GLboolean){printMissingFunctionError("glTexStorage3DMultisample");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexStorageSparseAMD(GLenum,GLenum,GLsizei,GLsizei,GLsizei,GLsizei,GLbitfield){printMissingFunctionError("glTexStorageSparseAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexSubImage1DEXT(GLenum,GLint,GLint,GLsizei,GLenum,GLenum,const void*){printMissingFunctionError("glTexSubImage1DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexSubImage1D(GLenum,GLint,GLint,GLsizei,GLenum,GLenum,const GLvoid*){printMissingFunctionError("glTexSubImage1D");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexSubImage2DEXT(GLenum,GLint,GLint,GLint,GLsizei,GLsizei,GLenum,GLenum,const void*){printMissingFunctionError("glTexSubImage2DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexSubImage2D(GLenum,GLint,GLint,GLint,GLsizei,GLsizei,GLenum,GLenum,const GLvoid*){printMissingFunctionError("glTexSubImage2D");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexSubImage3DEXT(GLenum,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLenum,GLenum,const void*){printMissingFunctionError("glTexSubImage3DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexSubImage3D(GLenum,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLenum,GLenum,const GLvoid*){printMissingFunctionError("glTexSubImage3D");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexSubImage4DSGIS(GLenum,GLint,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLsizei,GLenum,GLenum,const void*){printMissingFunctionError("glTexSubImage4DSGIS");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTextureBarrier(){printMissingFunctionError("glTextureBarrier");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTextureBarrierNV(){printMissingFunctionError("glTextureBarrierNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTextureBufferEXT(GLuint,GLenum,GLenum,GLuint){printMissingFunctionError("glTextureBufferEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTextureBuffer(GLuint,GLenum,GLuint){printMissingFunctionError("glTextureBuffer");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTextureBufferRangeEXT(GLuint,GLenum,GLenum,GLuint,GLintptr,GLsizeiptr){printMissingFunctionError("glTextureBufferRangeEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTextureBufferRange(GLuint,GLenum,GLuint,GLintptr,GLsizeiptr){printMissingFunctionError("glTextureBufferRange");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTextureColorMaskSGIS(GLboolean,GLboolean,GLboolean,GLboolean){printMissingFunctionError("glTextureColorMaskSGIS");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTextureImage1DEXT(GLuint,GLenum,GLint,GLint,GLsizei,GLint,GLenum,GLenum,const void*){printMissingFunctionError("glTextureImage1DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTextureImage2DEXT(GLuint,GLenum,GLint,GLint,GLsizei,GLsizei,GLint,GLenum,GLenum,const void*){printMissingFunctionError("glTextureImage2DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTextureImage2DMultisampleCoverageNV(GLuint,GLenum,GLsizei,GLsizei,GLint,GLsizei,GLsizei,GLboolean){printMissingFunctionError("glTextureImage2DMultisampleCoverageNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTextureImage2DMultisampleNV(GLuint,GLenum,GLsizei,GLint,GLsizei,GLsizei,GLboolean){printMissingFunctionError("glTextureImage2DMultisampleNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTextureImage3DEXT(GLuint,GLenum,GLint,GLint,GLsizei,GLsizei,GLsizei,GLint,GLenum,GLenum,const void*){printMissingFunctionError("glTextureImage3DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTextureImage3DMultisampleCoverageNV(GLuint,GLenum,GLsizei,GLsizei,GLint,GLsizei,GLsizei,GLsizei,GLboolean){printMissingFunctionError("glTextureImage3DMultisampleCoverageNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTextureImage3DMultisampleNV(GLuint,GLenum,GLsizei,GLint,GLsizei,GLsizei,GLsizei,GLboolean){printMissingFunctionError("glTextureImage3DMultisampleNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTextureLightEXT(GLenum){printMissingFunctionError("glTextureLightEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTextureMaterialEXT(GLenum,GLenum){printMissingFunctionError("glTextureMaterialEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTextureNormalEXT(GLenum){printMissingFunctionError("glTextureNormalEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTexturePageCommitmentEXT(GLuint,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLboolean){printMissingFunctionError("glTexturePageCommitmentEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTextureParameterfEXT(GLuint,GLenum,GLenum,GLfloat){printMissingFunctionError("glTextureParameterfEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTextureParameterf(GLuint,GLenum,GLfloat){printMissingFunctionError("glTextureParameterf");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTextureParameterfvEXT(GLuint,GLenum,GLenum,const GLfloat*){printMissingFunctionError("glTextureParameterfvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTextureParameterfv(GLuint,GLenum,const GLfloat*){printMissingFunctionError("glTextureParameterfv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTextureParameteriEXT(GLuint,GLenum,GLenum,GLint){printMissingFunctionError("glTextureParameteriEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTextureParameteri(GLuint,GLenum,GLint){printMissingFunctionError("glTextureParameteri");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTextureParameterIivEXT(GLuint,GLenum,GLenum,const GLint*){printMissingFunctionError("glTextureParameterIivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTextureParameterIiv(GLuint,GLenum,const GLint*){printMissingFunctionError("glTextureParameterIiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTextureParameterIuivEXT(GLuint,GLenum,GLenum,const GLuint*){printMissingFunctionError("glTextureParameterIuivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTextureParameterIuiv(GLuint,GLenum,const GLuint*){printMissingFunctionError("glTextureParameterIuiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTextureParameterivEXT(GLuint,GLenum,GLenum,const GLint*){printMissingFunctionError("glTextureParameterivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTextureParameteriv(GLuint,GLenum,const GLint*){printMissingFunctionError("glTextureParameteriv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTextureRangeAPPLE(GLenum,GLsizei,const void*){printMissingFunctionError("glTextureRangeAPPLE");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTextureRenderbufferEXT(GLuint,GLenum,GLuint){printMissingFunctionError("glTextureRenderbufferEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTextureStorage1DEXT(GLuint,GLenum,GLsizei,GLenum,GLsizei){printMissingFunctionError("glTextureStorage1DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTextureStorage1D(GLuint,GLsizei,GLenum,GLsizei){printMissingFunctionError("glTextureStorage1D");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTextureStorage2DEXT(GLuint,GLenum,GLsizei,GLenum,GLsizei,GLsizei){printMissingFunctionError("glTextureStorage2DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTextureStorage2D(GLuint,GLsizei,GLenum,GLsizei,GLsizei){printMissingFunctionError("glTextureStorage2D");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTextureStorage2DMultisampleEXT(GLuint,GLenum,GLsizei,GLenum,GLsizei,GLsizei,GLboolean){printMissingFunctionError("glTextureStorage2DMultisampleEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTextureStorage2DMultisample(GLuint,GLsizei,GLenum,GLsizei,GLsizei,GLboolean){printMissingFunctionError("glTextureStorage2DMultisample");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTextureStorage3DEXT(GLuint,GLenum,GLsizei,GLenum,GLsizei,GLsizei,GLsizei){printMissingFunctionError("glTextureStorage3DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTextureStorage3D(GLuint,GLsizei,GLenum,GLsizei,GLsizei,GLsizei){printMissingFunctionError("glTextureStorage3D");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTextureStorage3DMultisampleEXT(GLuint,GLenum,GLsizei,GLenum,GLsizei,GLsizei,GLsizei,GLboolean){printMissingFunctionError("glTextureStorage3DMultisampleEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTextureStorage3DMultisample(GLuint,GLsizei,GLenum,GLsizei,GLsizei,GLsizei,GLboolean){printMissingFunctionError("glTextureStorage3DMultisample");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTextureStorageSparseAMD(GLuint,GLenum,GLenum,GLsizei,GLsizei,GLsizei,GLsizei,GLbitfield){printMissingFunctionError("glTextureStorageSparseAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTextureSubImage1DEXT(GLuint,GLenum,GLint,GLint,GLsizei,GLenum,GLenum,const void*){printMissingFunctionError("glTextureSubImage1DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTextureSubImage1D(GLuint,GLint,GLint,GLsizei,GLenum,GLenum,const void*){printMissingFunctionError("glTextureSubImage1D");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTextureSubImage2DEXT(GLuint,GLenum,GLint,GLint,GLint,GLsizei,GLsizei,GLenum,GLenum,const void*){printMissingFunctionError("glTextureSubImage2DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTextureSubImage2D(GLuint,GLint,GLint,GLint,GLsizei,GLsizei,GLenum,GLenum,const void*){printMissingFunctionError("glTextureSubImage2D");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTextureSubImage3DEXT(GLuint,GLenum,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLenum,GLenum,const void*){printMissingFunctionError("glTextureSubImage3DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTextureSubImage3D(GLuint,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLenum,GLenum,const void*){printMissingFunctionError("glTextureSubImage3D");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTextureView(GLuint,GLenum,GLuint,GLenum,GLuint,GLuint,GLuint,GLuint){printMissingFunctionError("glTextureView");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTrackMatrixNV(GLenum,GLuint,GLenum,GLenum){printMissingFunctionError("glTrackMatrixNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTransformFeedbackAttribsNV(GLsizei,const GLint*,GLenum){printMissingFunctionError("glTransformFeedbackAttribsNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTransformFeedbackBufferBase(GLuint,GLuint,GLuint){printMissingFunctionError("glTransformFeedbackBufferBase");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTransformFeedbackBufferRange(GLuint,GLuint,GLuint,GLintptr,GLsizeiptr){printMissingFunctionError("glTransformFeedbackBufferRange");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTransformFeedbackStreamAttribsNV(GLsizei,const GLint*,GLsizei,const GLint*,GLenum){printMissingFunctionError("glTransformFeedbackStreamAttribsNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTransformFeedbackVaryingsEXT(GLuint,GLsizei,const GLchar*const*,GLenum){printMissingFunctionError("glTransformFeedbackVaryingsEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTransformFeedbackVaryings(GLuint,GLsizei,const GLchar*const*,GLenum){printMissingFunctionError("glTransformFeedbackVaryings");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTransformFeedbackVaryingsNV(GLuint,GLsizei,const GLint*,GLenum){printMissingFunctionError("glTransformFeedbackVaryingsNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTransformPathNV(GLuint,GLuint,GLenum,const GLfloat*){printMissingFunctionError("glTransformPathNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTranslated(GLdouble,GLdouble,GLdouble){printMissingFunctionError("glTranslated");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTranslatef(GLfloat,GLfloat,GLfloat){printMissingFunctionError("glTranslatef");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglTranslatexOES(GLfixed,GLfixed,GLfixed){printMissingFunctionError("glTranslatexOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform1d(GLint,GLdouble){printMissingFunctionError("glUniform1d");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform1dv(GLint,GLsizei,const GLdouble*){printMissingFunctionError("glUniform1dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform1fARB(GLint,GLfloat){printMissingFunctionError("glUniform1fARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform1f(GLint,GLfloat){printMissingFunctionError("glUniform1f");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform1fvARB(GLint,GLsizei,const GLfloat*){printMissingFunctionError("glUniform1fvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform1fv(GLint,GLsizei,const GLfloat*){printMissingFunctionError("glUniform1fv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform1i64ARB(GLint,GLint64){printMissingFunctionError("glUniform1i64ARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform1i64NV(GLint,GLint64EXT){printMissingFunctionError("glUniform1i64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform1i64vARB(GLint,GLsizei,const GLint64*){printMissingFunctionError("glUniform1i64vARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform1i64vNV(GLint,GLsizei,const GLint64EXT*){printMissingFunctionError("glUniform1i64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform1iARB(GLint,GLint){printMissingFunctionError("glUniform1iARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform1i(GLint,GLint){printMissingFunctionError("glUniform1i");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform1ivARB(GLint,GLsizei,const GLint*){printMissingFunctionError("glUniform1ivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform1iv(GLint,GLsizei,const GLint*){printMissingFunctionError("glUniform1iv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform1ui64ARB(GLint,GLuint64){printMissingFunctionError("glUniform1ui64ARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform1ui64NV(GLint,GLuint64EXT){printMissingFunctionError("glUniform1ui64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform1ui64vARB(GLint,GLsizei,const GLuint64*){printMissingFunctionError("glUniform1ui64vARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform1ui64vNV(GLint,GLsizei,const GLuint64EXT*){printMissingFunctionError("glUniform1ui64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform1uiEXT(GLint,GLuint){printMissingFunctionError("glUniform1uiEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform1ui(GLint,GLuint){printMissingFunctionError("glUniform1ui");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform1uivEXT(GLint,GLsizei,const GLuint*){printMissingFunctionError("glUniform1uivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform1uiv(GLint,GLsizei,const GLuint*){printMissingFunctionError("glUniform1uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform2d(GLint,GLdouble,GLdouble){printMissingFunctionError("glUniform2d");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform2dv(GLint,GLsizei,const GLdouble*){printMissingFunctionError("glUniform2dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform2fARB(GLint,GLfloat,GLfloat){printMissingFunctionError("glUniform2fARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform2f(GLint,GLfloat,GLfloat){printMissingFunctionError("glUniform2f");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform2fvARB(GLint,GLsizei,const GLfloat*){printMissingFunctionError("glUniform2fvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform2fv(GLint,GLsizei,const GLfloat*){printMissingFunctionError("glUniform2fv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform2i64ARB(GLint,GLint64,GLint64){printMissingFunctionError("glUniform2i64ARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform2i64NV(GLint,GLint64EXT,GLint64EXT){printMissingFunctionError("glUniform2i64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform2i64vARB(GLint,GLsizei,const GLint64*){printMissingFunctionError("glUniform2i64vARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform2i64vNV(GLint,GLsizei,const GLint64EXT*){printMissingFunctionError("glUniform2i64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform2iARB(GLint,GLint,GLint){printMissingFunctionError("glUniform2iARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform2i(GLint,GLint,GLint){printMissingFunctionError("glUniform2i");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform2ivARB(GLint,GLsizei,const GLint*){printMissingFunctionError("glUniform2ivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform2iv(GLint,GLsizei,const GLint*){printMissingFunctionError("glUniform2iv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform2ui64ARB(GLint,GLuint64,GLuint64){printMissingFunctionError("glUniform2ui64ARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform2ui64NV(GLint,GLuint64EXT,GLuint64EXT){printMissingFunctionError("glUniform2ui64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform2ui64vARB(GLint,GLsizei,const GLuint64*){printMissingFunctionError("glUniform2ui64vARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform2ui64vNV(GLint,GLsizei,const GLuint64EXT*){printMissingFunctionError("glUniform2ui64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform2uiEXT(GLint,GLuint,GLuint){printMissingFunctionError("glUniform2uiEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform2ui(GLint,GLuint,GLuint){printMissingFunctionError("glUniform2ui");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform2uivEXT(GLint,GLsizei,const GLuint*){printMissingFunctionError("glUniform2uivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform2uiv(GLint,GLsizei,const GLuint*){printMissingFunctionError("glUniform2uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform3d(GLint,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glUniform3d");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform3dv(GLint,GLsizei,const GLdouble*){printMissingFunctionError("glUniform3dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform3fARB(GLint,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glUniform3fARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform3f(GLint,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glUniform3f");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform3fvARB(GLint,GLsizei,const GLfloat*){printMissingFunctionError("glUniform3fvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform3fv(GLint,GLsizei,const GLfloat*){printMissingFunctionError("glUniform3fv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform3i64ARB(GLint,GLint64,GLint64,GLint64){printMissingFunctionError("glUniform3i64ARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform3i64NV(GLint,GLint64EXT,GLint64EXT,GLint64EXT){printMissingFunctionError("glUniform3i64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform3i64vARB(GLint,GLsizei,const GLint64*){printMissingFunctionError("glUniform3i64vARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform3i64vNV(GLint,GLsizei,const GLint64EXT*){printMissingFunctionError("glUniform3i64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform3iARB(GLint,GLint,GLint,GLint){printMissingFunctionError("glUniform3iARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform3i(GLint,GLint,GLint,GLint){printMissingFunctionError("glUniform3i");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform3ivARB(GLint,GLsizei,const GLint*){printMissingFunctionError("glUniform3ivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform3iv(GLint,GLsizei,const GLint*){printMissingFunctionError("glUniform3iv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform3ui64ARB(GLint,GLuint64,GLuint64,GLuint64){printMissingFunctionError("glUniform3ui64ARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform3ui64NV(GLint,GLuint64EXT,GLuint64EXT,GLuint64EXT){printMissingFunctionError("glUniform3ui64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform3ui64vARB(GLint,GLsizei,const GLuint64*){printMissingFunctionError("glUniform3ui64vARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform3ui64vNV(GLint,GLsizei,const GLuint64EXT*){printMissingFunctionError("glUniform3ui64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform3uiEXT(GLint,GLuint,GLuint,GLuint){printMissingFunctionError("glUniform3uiEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform3ui(GLint,GLuint,GLuint,GLuint){printMissingFunctionError("glUniform3ui");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform3uivEXT(GLint,GLsizei,const GLuint*){printMissingFunctionError("glUniform3uivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform3uiv(GLint,GLsizei,const GLuint*){printMissingFunctionError("glUniform3uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform4d(GLint,GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glUniform4d");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform4dv(GLint,GLsizei,const GLdouble*){printMissingFunctionError("glUniform4dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform4fARB(GLint,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glUniform4fARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform4f(GLint,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glUniform4f");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform4fvARB(GLint,GLsizei,const GLfloat*){printMissingFunctionError("glUniform4fvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform4fv(GLint,GLsizei,const GLfloat*){printMissingFunctionError("glUniform4fv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform4i64ARB(GLint,GLint64,GLint64,GLint64,GLint64){printMissingFunctionError("glUniform4i64ARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform4i64NV(GLint,GLint64EXT,GLint64EXT,GLint64EXT,GLint64EXT){printMissingFunctionError("glUniform4i64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform4i64vARB(GLint,GLsizei,const GLint64*){printMissingFunctionError("glUniform4i64vARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform4i64vNV(GLint,GLsizei,const GLint64EXT*){printMissingFunctionError("glUniform4i64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform4iARB(GLint,GLint,GLint,GLint,GLint){printMissingFunctionError("glUniform4iARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform4i(GLint,GLint,GLint,GLint,GLint){printMissingFunctionError("glUniform4i");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform4ivARB(GLint,GLsizei,const GLint*){printMissingFunctionError("glUniform4ivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform4iv(GLint,GLsizei,const GLint*){printMissingFunctionError("glUniform4iv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform4ui64ARB(GLint,GLuint64,GLuint64,GLuint64,GLuint64){printMissingFunctionError("glUniform4ui64ARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform4ui64NV(GLint,GLuint64EXT,GLuint64EXT,GLuint64EXT,GLuint64EXT){printMissingFunctionError("glUniform4ui64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform4ui64vARB(GLint,GLsizei,const GLuint64*){printMissingFunctionError("glUniform4ui64vARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform4ui64vNV(GLint,GLsizei,const GLuint64EXT*){printMissingFunctionError("glUniform4ui64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform4uiEXT(GLint,GLuint,GLuint,GLuint,GLuint){printMissingFunctionError("glUniform4uiEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform4ui(GLint,GLuint,GLuint,GLuint,GLuint){printMissingFunctionError("glUniform4ui");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform4uivEXT(GLint,GLsizei,const GLuint*){printMissingFunctionError("glUniform4uivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniform4uiv(GLint,GLsizei,const GLuint*){printMissingFunctionError("glUniform4uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniformBlockBinding(GLuint,GLuint,GLuint){printMissingFunctionError("glUniformBlockBinding");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniformBufferEXT(GLuint,GLint,GLuint){printMissingFunctionError("glUniformBufferEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniformHandleui64ARB(GLint,GLuint64){printMissingFunctionError("glUniformHandleui64ARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniformHandleui64NV(GLint,GLuint64){printMissingFunctionError("glUniformHandleui64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniformHandleui64vARB(GLint,GLsizei,const GLuint64*){printMissingFunctionError("glUniformHandleui64vARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniformHandleui64vNV(GLint,GLsizei,const GLuint64*){printMissingFunctionError("glUniformHandleui64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniformMatrix2dv(GLint,GLsizei,GLboolean,const GLdouble*){printMissingFunctionError("glUniformMatrix2dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniformMatrix2fvARB(GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glUniformMatrix2fvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniformMatrix2fv(GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glUniformMatrix2fv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniformMatrix2x3dv(GLint,GLsizei,GLboolean,const GLdouble*){printMissingFunctionError("glUniformMatrix2x3dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniformMatrix2x3fv(GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glUniformMatrix2x3fv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniformMatrix2x4dv(GLint,GLsizei,GLboolean,const GLdouble*){printMissingFunctionError("glUniformMatrix2x4dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniformMatrix2x4fv(GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glUniformMatrix2x4fv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniformMatrix3dv(GLint,GLsizei,GLboolean,const GLdouble*){printMissingFunctionError("glUniformMatrix3dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniformMatrix3fvARB(GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glUniformMatrix3fvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniformMatrix3fv(GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glUniformMatrix3fv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniformMatrix3x2dv(GLint,GLsizei,GLboolean,const GLdouble*){printMissingFunctionError("glUniformMatrix3x2dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniformMatrix3x2fv(GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glUniformMatrix3x2fv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniformMatrix3x4dv(GLint,GLsizei,GLboolean,const GLdouble*){printMissingFunctionError("glUniformMatrix3x4dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniformMatrix3x4fv(GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glUniformMatrix3x4fv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniformMatrix4dv(GLint,GLsizei,GLboolean,const GLdouble*){printMissingFunctionError("glUniformMatrix4dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniformMatrix4fvARB(GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glUniformMatrix4fvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniformMatrix4fv(GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glUniformMatrix4fv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniformMatrix4x2dv(GLint,GLsizei,GLboolean,const GLdouble*){printMissingFunctionError("glUniformMatrix4x2dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniformMatrix4x2fv(GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glUniformMatrix4x2fv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniformMatrix4x3dv(GLint,GLsizei,GLboolean,const GLdouble*){printMissingFunctionError("glUniformMatrix4x3dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniformMatrix4x3fv(GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glUniformMatrix4x3fv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniformSubroutinesuiv(GLenum,GLsizei,const GLuint*){printMissingFunctionError("glUniformSubroutinesuiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniformui64NV(GLint,GLuint64EXT){printMissingFunctionError("glUniformui64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUniformui64vNV(GLint,GLsizei,const GLuint64EXT*){printMissingFunctionError("glUniformui64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUnlockArraysEXT(){printMissingFunctionError("glUnlockArraysEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUnmapObjectBufferATI(GLuint){printMissingFunctionError("glUnmapObjectBufferATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUnmapTexture2DINTEL(GLuint,GLint){printMissingFunctionError("glUnmapTexture2DINTEL");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUpdateObjectBufferATI(GLuint,GLuint,GLsizei,const void*,GLenum){printMissingFunctionError("glUpdateObjectBufferATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUseProgram(GLuint){printMissingFunctionError("glUseProgram");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUseProgramObjectARB(GLhandleARB){printMissingFunctionError("glUseProgramObjectARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUseProgramStages(GLuint,GLbitfield,GLuint){printMissingFunctionError("glUseProgramStages");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglUseShaderProgramEXT(GLenum,GLuint){printMissingFunctionError("glUseShaderProgramEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglValidateProgramARB(GLhandleARB){printMissingFunctionError("glValidateProgramARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglValidateProgram(GLuint){printMissingFunctionError("glValidateProgram");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglValidateProgramPipeline(GLuint){printMissingFunctionError("glValidateProgramPipeline");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVariantArrayObjectATI(GLuint,GLenum,GLsizei,GLuint,GLuint){printMissingFunctionError("glVariantArrayObjectATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVariantbvEXT(GLuint,const GLbyte*){printMissingFunctionError("glVariantbvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVariantdvEXT(GLuint,const GLdouble*){printMissingFunctionError("glVariantdvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVariantfvEXT(GLuint,const GLfloat*){printMissingFunctionError("glVariantfvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVariantivEXT(GLuint,const GLint*){printMissingFunctionError("glVariantivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVariantPointerEXT(GLuint,GLenum,GLuint,const void*){printMissingFunctionError("glVariantPointerEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVariantsvEXT(GLuint,const GLshort*){printMissingFunctionError("glVariantsvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVariantubvEXT(GLuint,const GLubyte*){printMissingFunctionError("glVariantubvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVariantuivEXT(GLuint,const GLuint*){printMissingFunctionError("glVariantuivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVariantusvEXT(GLuint,const GLushort*){printMissingFunctionError("glVariantusvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVDPAUFiniNV(){printMissingFunctionError("glVDPAUFiniNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVDPAUGetSurfaceivNV(GLvdpauSurfaceNV,GLenum,GLsizei,GLsizei*,GLint*){printMissingFunctionError("glVDPAUGetSurfaceivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVDPAUInitNV(const void*,const void*){printMissingFunctionError("glVDPAUInitNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVDPAUMapSurfacesNV(GLsizei,const GLvdpauSurfaceNV*){printMissingFunctionError("glVDPAUMapSurfacesNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVDPAUSurfaceAccessNV(GLvdpauSurfaceNV,GLenum){printMissingFunctionError("glVDPAUSurfaceAccessNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVDPAUUnmapSurfacesNV(GLsizei,const GLvdpauSurfaceNV*){printMissingFunctionError("glVDPAUUnmapSurfacesNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVDPAUUnregisterSurfaceNV(GLvdpauSurfaceNV){printMissingFunctionError("glVDPAUUnregisterSurfaceNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertex2bOES(GLbyte,GLbyte){printMissingFunctionError("glVertex2bOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertex2bvOES(const GLbyte*){printMissingFunctionError("glVertex2bvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertex2d(GLdouble,GLdouble){printMissingFunctionError("glVertex2d");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertex2dv(const GLdouble*){printMissingFunctionError("glVertex2dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertex2f(GLfloat,GLfloat){printMissingFunctionError("glVertex2f");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertex2fv(const GLfloat*){printMissingFunctionError("glVertex2fv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertex2hNV(GLhalfNV,GLhalfNV){printMissingFunctionError("glVertex2hNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertex2hvNV(const GLhalfNV*){printMissingFunctionError("glVertex2hvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertex2i(GLint,GLint){printMissingFunctionError("glVertex2i");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertex2iv(const GLint*){printMissingFunctionError("glVertex2iv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertex2s(GLshort,GLshort){printMissingFunctionError("glVertex2s");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertex2sv(const GLshort*){printMissingFunctionError("glVertex2sv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertex2xOES(GLfixed){printMissingFunctionError("glVertex2xOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertex2xvOES(const GLfixed*){printMissingFunctionError("glVertex2xvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertex3bOES(GLbyte,GLbyte,GLbyte){printMissingFunctionError("glVertex3bOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertex3bvOES(const GLbyte*){printMissingFunctionError("glVertex3bvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertex3d(GLdouble,GLdouble,GLdouble){printMissingFunctionError("glVertex3d");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertex3dv(const GLdouble*){printMissingFunctionError("glVertex3dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertex3f(GLfloat,GLfloat,GLfloat){printMissingFunctionError("glVertex3f");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertex3fv(const GLfloat*){printMissingFunctionError("glVertex3fv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertex3hNV(GLhalfNV,GLhalfNV,GLhalfNV){printMissingFunctionError("glVertex3hNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertex3hvNV(const GLhalfNV*){printMissingFunctionError("glVertex3hvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertex3i(GLint,GLint,GLint){printMissingFunctionError("glVertex3i");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertex3iv(const GLint*){printMissingFunctionError("glVertex3iv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertex3s(GLshort,GLshort,GLshort){printMissingFunctionError("glVertex3s");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertex3sv(const GLshort*){printMissingFunctionError("glVertex3sv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertex3xOES(GLfixed,GLfixed){printMissingFunctionError("glVertex3xOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertex3xvOES(const GLfixed*){printMissingFunctionError("glVertex3xvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertex4bOES(GLbyte,GLbyte,GLbyte,GLbyte){printMissingFunctionError("glVertex4bOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertex4bvOES(const GLbyte*){printMissingFunctionError("glVertex4bvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertex4d(GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glVertex4d");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertex4dv(const GLdouble*){printMissingFunctionError("glVertex4dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertex4f(GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glVertex4f");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertex4fv(const GLfloat*){printMissingFunctionError("glVertex4fv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertex4hNV(GLhalfNV,GLhalfNV,GLhalfNV,GLhalfNV){printMissingFunctionError("glVertex4hNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertex4hvNV(const GLhalfNV*){printMissingFunctionError("glVertex4hvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertex4i(GLint,GLint,GLint,GLint){printMissingFunctionError("glVertex4i");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertex4iv(const GLint*){printMissingFunctionError("glVertex4iv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertex4s(GLshort,GLshort,GLshort,GLshort){printMissingFunctionError("glVertex4s");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertex4sv(const GLshort*){printMissingFunctionError("glVertex4sv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertex4xOES(GLfixed,GLfixed,GLfixed){printMissingFunctionError("glVertex4xOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertex4xvOES(const GLfixed*){printMissingFunctionError("glVertex4xvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexArrayAttribBinding(GLuint,GLuint,GLuint){printMissingFunctionError("glVertexArrayAttribBinding");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexArrayAttribFormat(GLuint,GLuint,GLint,GLenum,GLboolean,GLuint){printMissingFunctionError("glVertexArrayAttribFormat");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexArrayAttribIFormat(GLuint,GLuint,GLint,GLenum,GLuint){printMissingFunctionError("glVertexArrayAttribIFormat");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexArrayAttribLFormat(GLuint,GLuint,GLint,GLenum,GLuint){printMissingFunctionError("glVertexArrayAttribLFormat");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexArrayBindingDivisor(GLuint,GLuint,GLuint){printMissingFunctionError("glVertexArrayBindingDivisor");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexArrayBindVertexBufferEXT(GLuint,GLuint,GLuint,GLintptr,GLsizei){printMissingFunctionError("glVertexArrayBindVertexBufferEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexArrayColorOffsetEXT(GLuint,GLuint,GLint,GLenum,GLsizei,GLintptr){printMissingFunctionError("glVertexArrayColorOffsetEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexArrayEdgeFlagOffsetEXT(GLuint,GLuint,GLsizei,GLintptr){printMissingFunctionError("glVertexArrayEdgeFlagOffsetEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexArrayElementBuffer(GLuint,GLuint){printMissingFunctionError("glVertexArrayElementBuffer");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexArrayFogCoordOffsetEXT(GLuint,GLuint,GLenum,GLsizei,GLintptr){printMissingFunctionError("glVertexArrayFogCoordOffsetEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexArrayIndexOffsetEXT(GLuint,GLuint,GLenum,GLsizei,GLintptr){printMissingFunctionError("glVertexArrayIndexOffsetEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexArrayMultiTexCoordOffsetEXT(GLuint,GLuint,GLenum,GLint,GLenum,GLsizei,GLintptr){printMissingFunctionError("glVertexArrayMultiTexCoordOffsetEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexArrayNormalOffsetEXT(GLuint,GLuint,GLenum,GLsizei,GLintptr){printMissingFunctionError("glVertexArrayNormalOffsetEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexArrayParameteriAPPLE(GLenum,GLint){printMissingFunctionError("glVertexArrayParameteriAPPLE");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexArrayRangeAPPLE(GLsizei,void*){printMissingFunctionError("glVertexArrayRangeAPPLE");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexArrayRangeNV(GLsizei,const void*){printMissingFunctionError("glVertexArrayRangeNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexArraySecondaryColorOffsetEXT(GLuint,GLuint,GLint,GLenum,GLsizei,GLintptr){printMissingFunctionError("glVertexArraySecondaryColorOffsetEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexArrayTexCoordOffsetEXT(GLuint,GLuint,GLint,GLenum,GLsizei,GLintptr){printMissingFunctionError("glVertexArrayTexCoordOffsetEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexArrayVertexAttribBindingEXT(GLuint,GLuint,GLuint){printMissingFunctionError("glVertexArrayVertexAttribBindingEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexArrayVertexAttribDivisorEXT(GLuint,GLuint,GLuint){printMissingFunctionError("glVertexArrayVertexAttribDivisorEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexArrayVertexAttribFormatEXT(GLuint,GLuint,GLint,GLenum,GLboolean,GLuint){printMissingFunctionError("glVertexArrayVertexAttribFormatEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexArrayVertexAttribIFormatEXT(GLuint,GLuint,GLint,GLenum,GLuint){printMissingFunctionError("glVertexArrayVertexAttribIFormatEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexArrayVertexAttribIOffsetEXT(GLuint,GLuint,GLuint,GLint,GLenum,GLsizei,GLintptr){printMissingFunctionError("glVertexArrayVertexAttribIOffsetEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexArrayVertexAttribLFormatEXT(GLuint,GLuint,GLint,GLenum,GLuint){printMissingFunctionError("glVertexArrayVertexAttribLFormatEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexArrayVertexAttribLOffsetEXT(GLuint,GLuint,GLuint,GLint,GLenum,GLsizei,GLintptr){printMissingFunctionError("glVertexArrayVertexAttribLOffsetEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexArrayVertexAttribOffsetEXT(GLuint,GLuint,GLuint,GLint,GLenum,GLboolean,GLsizei,GLintptr){printMissingFunctionError("glVertexArrayVertexAttribOffsetEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexArrayVertexBindingDivisorEXT(GLuint,GLuint,GLuint){printMissingFunctionError("glVertexArrayVertexBindingDivisorEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexArrayVertexBuffer(GLuint,GLuint,GLuint,GLintptr,GLsizei){printMissingFunctionError("glVertexArrayVertexBuffer");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexArrayVertexBuffers(GLuint,GLuint,GLsizei,const GLuint*,const GLintptr*,const GLsizei*){printMissingFunctionError("glVertexArrayVertexBuffers");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexArrayVertexOffsetEXT(GLuint,GLuint,GLint,GLenum,GLsizei,GLintptr){printMissingFunctionError("glVertexArrayVertexOffsetEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib1dARB(GLuint,GLdouble){printMissingFunctionError("glVertexAttrib1dARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib1d(GLuint,GLdouble){printMissingFunctionError("glVertexAttrib1d");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib1dNV(GLuint,GLdouble){printMissingFunctionError("glVertexAttrib1dNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib1dvARB(GLuint,const GLdouble*){printMissingFunctionError("glVertexAttrib1dvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib1dv(GLuint,const GLdouble*){printMissingFunctionError("glVertexAttrib1dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib1dvNV(GLuint,const GLdouble*){printMissingFunctionError("glVertexAttrib1dvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib1fARB(GLuint,GLfloat){printMissingFunctionError("glVertexAttrib1fARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib1f(GLuint,GLfloat){printMissingFunctionError("glVertexAttrib1f");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib1fNV(GLuint,GLfloat){printMissingFunctionError("glVertexAttrib1fNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib1fvARB(GLuint,const GLfloat*){printMissingFunctionError("glVertexAttrib1fvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib1fv(GLuint,const GLfloat*){printMissingFunctionError("glVertexAttrib1fv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib1fvNV(GLuint,const GLfloat*){printMissingFunctionError("glVertexAttrib1fvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib1hNV(GLuint,GLhalfNV){printMissingFunctionError("glVertexAttrib1hNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib1hvNV(GLuint,const GLhalfNV*){printMissingFunctionError("glVertexAttrib1hvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib1sARB(GLuint,GLshort){printMissingFunctionError("glVertexAttrib1sARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib1s(GLuint,GLshort){printMissingFunctionError("glVertexAttrib1s");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib1sNV(GLuint,GLshort){printMissingFunctionError("glVertexAttrib1sNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib1svARB(GLuint,const GLshort*){printMissingFunctionError("glVertexAttrib1svARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib1sv(GLuint,const GLshort*){printMissingFunctionError("glVertexAttrib1sv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib1svNV(GLuint,const GLshort*){printMissingFunctionError("glVertexAttrib1svNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib2dARB(GLuint,GLdouble,GLdouble){printMissingFunctionError("glVertexAttrib2dARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib2d(GLuint,GLdouble,GLdouble){printMissingFunctionError("glVertexAttrib2d");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib2dNV(GLuint,GLdouble,GLdouble){printMissingFunctionError("glVertexAttrib2dNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib2dvARB(GLuint,const GLdouble*){printMissingFunctionError("glVertexAttrib2dvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib2dv(GLuint,const GLdouble*){printMissingFunctionError("glVertexAttrib2dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib2dvNV(GLuint,const GLdouble*){printMissingFunctionError("glVertexAttrib2dvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib2fARB(GLuint,GLfloat,GLfloat){printMissingFunctionError("glVertexAttrib2fARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib2f(GLuint,GLfloat,GLfloat){printMissingFunctionError("glVertexAttrib2f");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib2fNV(GLuint,GLfloat,GLfloat){printMissingFunctionError("glVertexAttrib2fNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib2fvARB(GLuint,const GLfloat*){printMissingFunctionError("glVertexAttrib2fvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib2fv(GLuint,const GLfloat*){printMissingFunctionError("glVertexAttrib2fv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib2fvNV(GLuint,const GLfloat*){printMissingFunctionError("glVertexAttrib2fvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib2hNV(GLuint,GLhalfNV,GLhalfNV){printMissingFunctionError("glVertexAttrib2hNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib2hvNV(GLuint,const GLhalfNV*){printMissingFunctionError("glVertexAttrib2hvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib2sARB(GLuint,GLshort,GLshort){printMissingFunctionError("glVertexAttrib2sARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib2s(GLuint,GLshort,GLshort){printMissingFunctionError("glVertexAttrib2s");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib2sNV(GLuint,GLshort,GLshort){printMissingFunctionError("glVertexAttrib2sNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib2svARB(GLuint,const GLshort*){printMissingFunctionError("glVertexAttrib2svARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib2sv(GLuint,const GLshort*){printMissingFunctionError("glVertexAttrib2sv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib2svNV(GLuint,const GLshort*){printMissingFunctionError("glVertexAttrib2svNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib3dARB(GLuint,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glVertexAttrib3dARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib3d(GLuint,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glVertexAttrib3d");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib3dNV(GLuint,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glVertexAttrib3dNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib3dvARB(GLuint,const GLdouble*){printMissingFunctionError("glVertexAttrib3dvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib3dv(GLuint,const GLdouble*){printMissingFunctionError("glVertexAttrib3dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib3dvNV(GLuint,const GLdouble*){printMissingFunctionError("glVertexAttrib3dvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib3fARB(GLuint,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glVertexAttrib3fARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib3f(GLuint,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glVertexAttrib3f");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib3fNV(GLuint,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glVertexAttrib3fNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib3fvARB(GLuint,const GLfloat*){printMissingFunctionError("glVertexAttrib3fvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib3fv(GLuint,const GLfloat*){printMissingFunctionError("glVertexAttrib3fv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib3fvNV(GLuint,const GLfloat*){printMissingFunctionError("glVertexAttrib3fvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib3hNV(GLuint,GLhalfNV,GLhalfNV,GLhalfNV){printMissingFunctionError("glVertexAttrib3hNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib3hvNV(GLuint,const GLhalfNV*){printMissingFunctionError("glVertexAttrib3hvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib3sARB(GLuint,GLshort,GLshort,GLshort){printMissingFunctionError("glVertexAttrib3sARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib3s(GLuint,GLshort,GLshort,GLshort){printMissingFunctionError("glVertexAttrib3s");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib3sNV(GLuint,GLshort,GLshort,GLshort){printMissingFunctionError("glVertexAttrib3sNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib3svARB(GLuint,const GLshort*){printMissingFunctionError("glVertexAttrib3svARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib3sv(GLuint,const GLshort*){printMissingFunctionError("glVertexAttrib3sv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib3svNV(GLuint,const GLshort*){printMissingFunctionError("glVertexAttrib3svNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib4bvARB(GLuint,const GLbyte*){printMissingFunctionError("glVertexAttrib4bvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib4bv(GLuint,const GLbyte*){printMissingFunctionError("glVertexAttrib4bv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib4dARB(GLuint,GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glVertexAttrib4dARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib4d(GLuint,GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glVertexAttrib4d");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib4dNV(GLuint,GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glVertexAttrib4dNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib4dvARB(GLuint,const GLdouble*){printMissingFunctionError("glVertexAttrib4dvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib4dv(GLuint,const GLdouble*){printMissingFunctionError("glVertexAttrib4dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib4dvNV(GLuint,const GLdouble*){printMissingFunctionError("glVertexAttrib4dvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib4fARB(GLuint,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glVertexAttrib4fARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib4f(GLuint,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glVertexAttrib4f");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib4fNV(GLuint,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glVertexAttrib4fNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib4fvARB(GLuint,const GLfloat*){printMissingFunctionError("glVertexAttrib4fvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib4fv(GLuint,const GLfloat*){printMissingFunctionError("glVertexAttrib4fv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib4fvNV(GLuint,const GLfloat*){printMissingFunctionError("glVertexAttrib4fvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib4hNV(GLuint,GLhalfNV,GLhalfNV,GLhalfNV,GLhalfNV){printMissingFunctionError("glVertexAttrib4hNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib4hvNV(GLuint,const GLhalfNV*){printMissingFunctionError("glVertexAttrib4hvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib4ivARB(GLuint,const GLint*){printMissingFunctionError("glVertexAttrib4ivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib4iv(GLuint,const GLint*){printMissingFunctionError("glVertexAttrib4iv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib4NbvARB(GLuint,const GLbyte*){printMissingFunctionError("glVertexAttrib4NbvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib4Nbv(GLuint,const GLbyte*){printMissingFunctionError("glVertexAttrib4Nbv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib4NivARB(GLuint,const GLint*){printMissingFunctionError("glVertexAttrib4NivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib4Niv(GLuint,const GLint*){printMissingFunctionError("glVertexAttrib4Niv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib4NsvARB(GLuint,const GLshort*){printMissingFunctionError("glVertexAttrib4NsvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib4Nsv(GLuint,const GLshort*){printMissingFunctionError("glVertexAttrib4Nsv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib4NubARB(GLuint,GLubyte,GLubyte,GLubyte,GLubyte){printMissingFunctionError("glVertexAttrib4NubARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib4Nub(GLuint,GLubyte,GLubyte,GLubyte,GLubyte){printMissingFunctionError("glVertexAttrib4Nub");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib4NubvARB(GLuint,const GLubyte*){printMissingFunctionError("glVertexAttrib4NubvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib4Nubv(GLuint,const GLubyte*){printMissingFunctionError("glVertexAttrib4Nubv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib4NuivARB(GLuint,const GLuint*){printMissingFunctionError("glVertexAttrib4NuivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib4Nuiv(GLuint,const GLuint*){printMissingFunctionError("glVertexAttrib4Nuiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib4NusvARB(GLuint,const GLushort*){printMissingFunctionError("glVertexAttrib4NusvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib4Nusv(GLuint,const GLushort*){printMissingFunctionError("glVertexAttrib4Nusv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib4sARB(GLuint,GLshort,GLshort,GLshort,GLshort){printMissingFunctionError("glVertexAttrib4sARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib4s(GLuint,GLshort,GLshort,GLshort,GLshort){printMissingFunctionError("glVertexAttrib4s");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib4sNV(GLuint,GLshort,GLshort,GLshort,GLshort){printMissingFunctionError("glVertexAttrib4sNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib4svARB(GLuint,const GLshort*){printMissingFunctionError("glVertexAttrib4svARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib4sv(GLuint,const GLshort*){printMissingFunctionError("glVertexAttrib4sv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib4svNV(GLuint,const GLshort*){printMissingFunctionError("glVertexAttrib4svNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib4ubNV(GLuint,GLubyte,GLubyte,GLubyte,GLubyte){printMissingFunctionError("glVertexAttrib4ubNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib4ubvARB(GLuint,const GLubyte*){printMissingFunctionError("glVertexAttrib4ubvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib4ubv(GLuint,const GLubyte*){printMissingFunctionError("glVertexAttrib4ubv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib4ubvNV(GLuint,const GLubyte*){printMissingFunctionError("glVertexAttrib4ubvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib4uivARB(GLuint,const GLuint*){printMissingFunctionError("glVertexAttrib4uivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib4uiv(GLuint,const GLuint*){printMissingFunctionError("glVertexAttrib4uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib4usvARB(GLuint,const GLushort*){printMissingFunctionError("glVertexAttrib4usvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttrib4usv(GLuint,const GLushort*){printMissingFunctionError("glVertexAttrib4usv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribArrayObjectATI(GLuint,GLint,GLenum,GLboolean,GLsizei,GLuint,GLuint){printMissingFunctionError("glVertexAttribArrayObjectATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribBinding(GLuint,GLuint){printMissingFunctionError("glVertexAttribBinding");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribDivisorARB(GLuint,GLuint){printMissingFunctionError("glVertexAttribDivisorARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribDivisor(GLuint,GLuint){printMissingFunctionError("glVertexAttribDivisor");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribFormat(GLuint,GLint,GLenum,GLboolean,GLuint){printMissingFunctionError("glVertexAttribFormat");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribFormatNV(GLuint,GLint,GLenum,GLboolean,GLsizei){printMissingFunctionError("glVertexAttribFormatNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribI1iEXT(GLuint,GLint){printMissingFunctionError("glVertexAttribI1iEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribI1i(GLuint,GLint){printMissingFunctionError("glVertexAttribI1i");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribI1ivEXT(GLuint,const GLint*){printMissingFunctionError("glVertexAttribI1ivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribI1iv(GLuint,const GLint*){printMissingFunctionError("glVertexAttribI1iv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribI1uiEXT(GLuint,GLuint){printMissingFunctionError("glVertexAttribI1uiEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribI1ui(GLuint,GLuint){printMissingFunctionError("glVertexAttribI1ui");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribI1uivEXT(GLuint,const GLuint*){printMissingFunctionError("glVertexAttribI1uivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribI1uiv(GLuint,const GLuint*){printMissingFunctionError("glVertexAttribI1uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribI2iEXT(GLuint,GLint,GLint){printMissingFunctionError("glVertexAttribI2iEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribI2i(GLuint,GLint,GLint){printMissingFunctionError("glVertexAttribI2i");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribI2ivEXT(GLuint,const GLint*){printMissingFunctionError("glVertexAttribI2ivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribI2iv(GLuint,const GLint*){printMissingFunctionError("glVertexAttribI2iv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribI2uiEXT(GLuint,GLuint,GLuint){printMissingFunctionError("glVertexAttribI2uiEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribI2ui(GLuint,GLuint,GLuint){printMissingFunctionError("glVertexAttribI2ui");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribI2uivEXT(GLuint,const GLuint*){printMissingFunctionError("glVertexAttribI2uivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribI2uiv(GLuint,const GLuint*){printMissingFunctionError("glVertexAttribI2uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribI3iEXT(GLuint,GLint,GLint,GLint){printMissingFunctionError("glVertexAttribI3iEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribI3i(GLuint,GLint,GLint,GLint){printMissingFunctionError("glVertexAttribI3i");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribI3ivEXT(GLuint,const GLint*){printMissingFunctionError("glVertexAttribI3ivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribI3iv(GLuint,const GLint*){printMissingFunctionError("glVertexAttribI3iv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribI3uiEXT(GLuint,GLuint,GLuint,GLuint){printMissingFunctionError("glVertexAttribI3uiEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribI3ui(GLuint,GLuint,GLuint,GLuint){printMissingFunctionError("glVertexAttribI3ui");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribI3uivEXT(GLuint,const GLuint*){printMissingFunctionError("glVertexAttribI3uivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribI3uiv(GLuint,const GLuint*){printMissingFunctionError("glVertexAttribI3uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribI4bvEXT(GLuint,const GLbyte*){printMissingFunctionError("glVertexAttribI4bvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribI4bv(GLuint,const GLbyte*){printMissingFunctionError("glVertexAttribI4bv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribI4iEXT(GLuint,GLint,GLint,GLint,GLint){printMissingFunctionError("glVertexAttribI4iEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribI4i(GLuint,GLint,GLint,GLint,GLint){printMissingFunctionError("glVertexAttribI4i");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribI4ivEXT(GLuint,const GLint*){printMissingFunctionError("glVertexAttribI4ivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribI4iv(GLuint,const GLint*){printMissingFunctionError("glVertexAttribI4iv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribI4svEXT(GLuint,const GLshort*){printMissingFunctionError("glVertexAttribI4svEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribI4sv(GLuint,const GLshort*){printMissingFunctionError("glVertexAttribI4sv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribI4ubvEXT(GLuint,const GLubyte*){printMissingFunctionError("glVertexAttribI4ubvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribI4ubv(GLuint,const GLubyte*){printMissingFunctionError("glVertexAttribI4ubv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribI4uiEXT(GLuint,GLuint,GLuint,GLuint,GLuint){printMissingFunctionError("glVertexAttribI4uiEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribI4ui(GLuint,GLuint,GLuint,GLuint,GLuint){printMissingFunctionError("glVertexAttribI4ui");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribI4uivEXT(GLuint,const GLuint*){printMissingFunctionError("glVertexAttribI4uivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribI4uiv(GLuint,const GLuint*){printMissingFunctionError("glVertexAttribI4uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribI4usvEXT(GLuint,const GLushort*){printMissingFunctionError("glVertexAttribI4usvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribI4usv(GLuint,const GLushort*){printMissingFunctionError("glVertexAttribI4usv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribIFormat(GLuint,GLint,GLenum,GLuint){printMissingFunctionError("glVertexAttribIFormat");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribIFormatNV(GLuint,GLint,GLenum,GLsizei){printMissingFunctionError("glVertexAttribIFormatNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribIPointerEXT(GLuint,GLint,GLenum,GLsizei,const void*){printMissingFunctionError("glVertexAttribIPointerEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribIPointer(GLuint,GLint,GLenum,GLsizei,const void*){printMissingFunctionError("glVertexAttribIPointer");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribL1dEXT(GLuint,GLdouble){printMissingFunctionError("glVertexAttribL1dEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribL1d(GLuint,GLdouble){printMissingFunctionError("glVertexAttribL1d");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribL1dvEXT(GLuint,const GLdouble*){printMissingFunctionError("glVertexAttribL1dvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribL1dv(GLuint,const GLdouble*){printMissingFunctionError("glVertexAttribL1dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribL1i64NV(GLuint,GLint64EXT){printMissingFunctionError("glVertexAttribL1i64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribL1i64vNV(GLuint,const GLint64EXT*){printMissingFunctionError("glVertexAttribL1i64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribL1ui64ARB(GLuint,GLuint64EXT){printMissingFunctionError("glVertexAttribL1ui64ARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribL1ui64NV(GLuint,GLuint64EXT){printMissingFunctionError("glVertexAttribL1ui64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribL1ui64vARB(GLuint,const GLuint64EXT*){printMissingFunctionError("glVertexAttribL1ui64vARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribL1ui64vNV(GLuint,const GLuint64EXT*){printMissingFunctionError("glVertexAttribL1ui64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribL2dEXT(GLuint,GLdouble,GLdouble){printMissingFunctionError("glVertexAttribL2dEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribL2d(GLuint,GLdouble,GLdouble){printMissingFunctionError("glVertexAttribL2d");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribL2dvEXT(GLuint,const GLdouble*){printMissingFunctionError("glVertexAttribL2dvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribL2dv(GLuint,const GLdouble*){printMissingFunctionError("glVertexAttribL2dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribL2i64NV(GLuint,GLint64EXT,GLint64EXT){printMissingFunctionError("glVertexAttribL2i64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribL2i64vNV(GLuint,const GLint64EXT*){printMissingFunctionError("glVertexAttribL2i64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribL2ui64NV(GLuint,GLuint64EXT,GLuint64EXT){printMissingFunctionError("glVertexAttribL2ui64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribL2ui64vNV(GLuint,const GLuint64EXT*){printMissingFunctionError("glVertexAttribL2ui64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribL3dEXT(GLuint,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glVertexAttribL3dEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribL3d(GLuint,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glVertexAttribL3d");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribL3dvEXT(GLuint,const GLdouble*){printMissingFunctionError("glVertexAttribL3dvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribL3dv(GLuint,const GLdouble*){printMissingFunctionError("glVertexAttribL3dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribL3i64NV(GLuint,GLint64EXT,GLint64EXT,GLint64EXT){printMissingFunctionError("glVertexAttribL3i64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribL3i64vNV(GLuint,const GLint64EXT*){printMissingFunctionError("glVertexAttribL3i64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribL3ui64NV(GLuint,GLuint64EXT,GLuint64EXT,GLuint64EXT){printMissingFunctionError("glVertexAttribL3ui64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribL3ui64vNV(GLuint,const GLuint64EXT*){printMissingFunctionError("glVertexAttribL3ui64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribL4dEXT(GLuint,GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glVertexAttribL4dEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribL4d(GLuint,GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glVertexAttribL4d");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribL4dvEXT(GLuint,const GLdouble*){printMissingFunctionError("glVertexAttribL4dvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribL4dv(GLuint,const GLdouble*){printMissingFunctionError("glVertexAttribL4dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribL4i64NV(GLuint,GLint64EXT,GLint64EXT,GLint64EXT,GLint64EXT){printMissingFunctionError("glVertexAttribL4i64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribL4i64vNV(GLuint,const GLint64EXT*){printMissingFunctionError("glVertexAttribL4i64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribL4ui64NV(GLuint,GLuint64EXT,GLuint64EXT,GLuint64EXT,GLuint64EXT){printMissingFunctionError("glVertexAttribL4ui64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribL4ui64vNV(GLuint,const GLuint64EXT*){printMissingFunctionError("glVertexAttribL4ui64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribLFormat(GLuint,GLint,GLenum,GLuint){printMissingFunctionError("glVertexAttribLFormat");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribLFormatNV(GLuint,GLint,GLenum,GLsizei){printMissingFunctionError("glVertexAttribLFormatNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribLPointerEXT(GLuint,GLint,GLenum,GLsizei,const void*){printMissingFunctionError("glVertexAttribLPointerEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribLPointer(GLuint,GLint,GLenum,GLsizei,const void*){printMissingFunctionError("glVertexAttribLPointer");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribP1ui(GLuint,GLenum,GLboolean,GLuint){printMissingFunctionError("glVertexAttribP1ui");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribP1uiv(GLuint,GLenum,GLboolean,const GLuint*){printMissingFunctionError("glVertexAttribP1uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribP2ui(GLuint,GLenum,GLboolean,GLuint){printMissingFunctionError("glVertexAttribP2ui");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribP2uiv(GLuint,GLenum,GLboolean,const GLuint*){printMissingFunctionError("glVertexAttribP2uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribP3ui(GLuint,GLenum,GLboolean,GLuint){printMissingFunctionError("glVertexAttribP3ui");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribP3uiv(GLuint,GLenum,GLboolean,const GLuint*){printMissingFunctionError("glVertexAttribP3uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribP4ui(GLuint,GLenum,GLboolean,GLuint){printMissingFunctionError("glVertexAttribP4ui");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribP4uiv(GLuint,GLenum,GLboolean,const GLuint*){printMissingFunctionError("glVertexAttribP4uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribParameteriAMD(GLuint,GLenum,GLint){printMissingFunctionError("glVertexAttribParameteriAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribPointerARB(GLuint,GLint,GLenum,GLboolean,GLsizei,const void*){printMissingFunctionError("glVertexAttribPointerARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribPointer(GLuint,GLint,GLenum,GLboolean,GLsizei,const void*){printMissingFunctionError("glVertexAttribPointer");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribPointerNV(GLuint,GLint,GLenum,GLsizei,const void*){printMissingFunctionError("glVertexAttribPointerNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribs1dvNV(GLuint,GLsizei,const GLdouble*){printMissingFunctionError("glVertexAttribs1dvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribs1fvNV(GLuint,GLsizei,const GLfloat*){printMissingFunctionError("glVertexAttribs1fvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribs1hvNV(GLuint,GLsizei,const GLhalfNV*){printMissingFunctionError("glVertexAttribs1hvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribs1svNV(GLuint,GLsizei,const GLshort*){printMissingFunctionError("glVertexAttribs1svNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribs2dvNV(GLuint,GLsizei,const GLdouble*){printMissingFunctionError("glVertexAttribs2dvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribs2fvNV(GLuint,GLsizei,const GLfloat*){printMissingFunctionError("glVertexAttribs2fvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribs2hvNV(GLuint,GLsizei,const GLhalfNV*){printMissingFunctionError("glVertexAttribs2hvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribs2svNV(GLuint,GLsizei,const GLshort*){printMissingFunctionError("glVertexAttribs2svNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribs3dvNV(GLuint,GLsizei,const GLdouble*){printMissingFunctionError("glVertexAttribs3dvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribs3fvNV(GLuint,GLsizei,const GLfloat*){printMissingFunctionError("glVertexAttribs3fvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribs3hvNV(GLuint,GLsizei,const GLhalfNV*){printMissingFunctionError("glVertexAttribs3hvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribs3svNV(GLuint,GLsizei,const GLshort*){printMissingFunctionError("glVertexAttribs3svNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribs4dvNV(GLuint,GLsizei,const GLdouble*){printMissingFunctionError("glVertexAttribs4dvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribs4fvNV(GLuint,GLsizei,const GLfloat*){printMissingFunctionError("glVertexAttribs4fvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribs4hvNV(GLuint,GLsizei,const GLhalfNV*){printMissingFunctionError("glVertexAttribs4hvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribs4svNV(GLuint,GLsizei,const GLshort*){printMissingFunctionError("glVertexAttribs4svNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexAttribs4ubvNV(GLuint,GLsizei,const GLubyte*){printMissingFunctionError("glVertexAttribs4ubvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexBindingDivisor(GLuint,GLuint){printMissingFunctionError("glVertexBindingDivisor");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexBlendARB(GLint){printMissingFunctionError("glVertexBlendARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexBlendEnvfATI(GLenum,GLfloat){printMissingFunctionError("glVertexBlendEnvfATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexBlendEnviATI(GLenum,GLint){printMissingFunctionError("glVertexBlendEnviATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexFormatNV(GLint,GLenum,GLsizei){printMissingFunctionError("glVertexFormatNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexP2ui(GLenum,GLuint){printMissingFunctionError("glVertexP2ui");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexP2uiv(GLenum,const GLuint*){printMissingFunctionError("glVertexP2uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexP3ui(GLenum,GLuint){printMissingFunctionError("glVertexP3ui");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexP3uiv(GLenum,const GLuint*){printMissingFunctionError("glVertexP3uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexP4ui(GLenum,GLuint){printMissingFunctionError("glVertexP4ui");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexP4uiv(GLenum,const GLuint*){printMissingFunctionError("glVertexP4uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexPointerEXT(GLint,GLenum,GLsizei,GLsizei,const void*){printMissingFunctionError("glVertexPointerEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexPointer(GLint,GLenum,GLsizei,const GLvoid*){printMissingFunctionError("glVertexPointer");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexPointerListIBM(GLint,GLenum,GLint,const void**,GLint){printMissingFunctionError("glVertexPointerListIBM");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexPointervINTEL(GLint,GLenum,const void**){printMissingFunctionError("glVertexPointervINTEL");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexStream1dATI(GLenum,GLdouble){printMissingFunctionError("glVertexStream1dATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexStream1dvATI(GLenum,const GLdouble*){printMissingFunctionError("glVertexStream1dvATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexStream1fATI(GLenum,GLfloat){printMissingFunctionError("glVertexStream1fATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexStream1fvATI(GLenum,const GLfloat*){printMissingFunctionError("glVertexStream1fvATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexStream1iATI(GLenum,GLint){printMissingFunctionError("glVertexStream1iATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexStream1ivATI(GLenum,const GLint*){printMissingFunctionError("glVertexStream1ivATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexStream1sATI(GLenum,GLshort){printMissingFunctionError("glVertexStream1sATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexStream1svATI(GLenum,const GLshort*){printMissingFunctionError("glVertexStream1svATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexStream2dATI(GLenum,GLdouble,GLdouble){printMissingFunctionError("glVertexStream2dATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexStream2dvATI(GLenum,const GLdouble*){printMissingFunctionError("glVertexStream2dvATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexStream2fATI(GLenum,GLfloat,GLfloat){printMissingFunctionError("glVertexStream2fATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexStream2fvATI(GLenum,const GLfloat*){printMissingFunctionError("glVertexStream2fvATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexStream2iATI(GLenum,GLint,GLint){printMissingFunctionError("glVertexStream2iATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexStream2ivATI(GLenum,const GLint*){printMissingFunctionError("glVertexStream2ivATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexStream2sATI(GLenum,GLshort,GLshort){printMissingFunctionError("glVertexStream2sATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexStream2svATI(GLenum,const GLshort*){printMissingFunctionError("glVertexStream2svATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexStream3dATI(GLenum,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glVertexStream3dATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexStream3dvATI(GLenum,const GLdouble*){printMissingFunctionError("glVertexStream3dvATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexStream3fATI(GLenum,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glVertexStream3fATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexStream3fvATI(GLenum,const GLfloat*){printMissingFunctionError("glVertexStream3fvATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexStream3iATI(GLenum,GLint,GLint,GLint){printMissingFunctionError("glVertexStream3iATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexStream3ivATI(GLenum,const GLint*){printMissingFunctionError("glVertexStream3ivATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexStream3sATI(GLenum,GLshort,GLshort,GLshort){printMissingFunctionError("glVertexStream3sATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexStream3svATI(GLenum,const GLshort*){printMissingFunctionError("glVertexStream3svATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexStream4dATI(GLenum,GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glVertexStream4dATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexStream4dvATI(GLenum,const GLdouble*){printMissingFunctionError("glVertexStream4dvATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexStream4fATI(GLenum,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glVertexStream4fATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexStream4fvATI(GLenum,const GLfloat*){printMissingFunctionError("glVertexStream4fvATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexStream4iATI(GLenum,GLint,GLint,GLint,GLint){printMissingFunctionError("glVertexStream4iATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexStream4ivATI(GLenum,const GLint*){printMissingFunctionError("glVertexStream4ivATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexStream4sATI(GLenum,GLshort,GLshort,GLshort,GLshort){printMissingFunctionError("glVertexStream4sATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexStream4svATI(GLenum,const GLshort*){printMissingFunctionError("glVertexStream4svATI");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexWeightfEXT(GLfloat){printMissingFunctionError("glVertexWeightfEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexWeightfvEXT(const GLfloat*){printMissingFunctionError("glVertexWeightfvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexWeighthNV(GLhalfNV){printMissingFunctionError("glVertexWeighthNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexWeighthvNV(const GLhalfNV*){printMissingFunctionError("glVertexWeighthvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVertexWeightPointerEXT(GLint,GLenum,GLsizei,const void*){printMissingFunctionError("glVertexWeightPointerEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVideoCaptureStreamParameterdvNV(GLuint,GLuint,GLenum,const GLdouble*){printMissingFunctionError("glVideoCaptureStreamParameterdvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVideoCaptureStreamParameterfvNV(GLuint,GLuint,GLenum,const GLfloat*){printMissingFunctionError("glVideoCaptureStreamParameterfvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglVideoCaptureStreamParameterivNV(GLuint,GLuint,GLenum,const GLint*){printMissingFunctionError("glVideoCaptureStreamParameterivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglViewportArrayv(GLuint,GLsizei,const GLfloat*){printMissingFunctionError("glViewportArrayv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglViewport(GLint,GLint,GLsizei,GLsizei){printMissingFunctionError("glViewport");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglViewportIndexedf(GLuint,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glViewportIndexedf");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglViewportIndexedfv(GLuint,const GLfloat*){printMissingFunctionError("glViewportIndexedfv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglViewportSwizzleNV(GLuint,GLenum,GLenum,GLenum,GLenum){printMissingFunctionError("glViewportSwizzleNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWaitSync(GLsync,GLbitfield,GLuint64){printMissingFunctionError("glWaitSync");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWeightbvARB(GLint,const GLbyte*){printMissingFunctionError("glWeightbvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWeightdvARB(GLint,const GLdouble*){printMissingFunctionError("glWeightdvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWeightfvARB(GLint,const GLfloat*){printMissingFunctionError("glWeightfvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWeightivARB(GLint,const GLint*){printMissingFunctionError("glWeightivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWeightPathsNV(GLuint,GLsizei,const GLuint*,const GLfloat*){printMissingFunctionError("glWeightPathsNV");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWeightPointerARB(GLint,GLenum,GLsizei,const void*){printMissingFunctionError("glWeightPointerARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWeightsvARB(GLint,const GLshort*){printMissingFunctionError("glWeightsvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWeightubvARB(GLint,const GLubyte*){printMissingFunctionError("glWeightubvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWeightuivARB(GLint,const GLuint*){printMissingFunctionError("glWeightuivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWeightusvARB(GLint,const GLushort*){printMissingFunctionError("glWeightusvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos2dARB(GLdouble,GLdouble){printMissingFunctionError("glWindowPos2dARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos2d(GLdouble,GLdouble){printMissingFunctionError("glWindowPos2d");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos2dMESA(GLdouble,GLdouble){printMissingFunctionError("glWindowPos2dMESA");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos2dvARB(const GLdouble*){printMissingFunctionError("glWindowPos2dvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos2dv(const GLdouble*){printMissingFunctionError("glWindowPos2dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos2dvMESA(const GLdouble*){printMissingFunctionError("glWindowPos2dvMESA");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos2fARB(GLfloat,GLfloat){printMissingFunctionError("glWindowPos2fARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos2f(GLfloat,GLfloat){printMissingFunctionError("glWindowPos2f");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos2fMESA(GLfloat,GLfloat){printMissingFunctionError("glWindowPos2fMESA");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos2fvARB(const GLfloat*){printMissingFunctionError("glWindowPos2fvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos2fv(const GLfloat*){printMissingFunctionError("glWindowPos2fv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos2fvMESA(const GLfloat*){printMissingFunctionError("glWindowPos2fvMESA");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos2iARB(GLint,GLint){printMissingFunctionError("glWindowPos2iARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos2i(GLint,GLint){printMissingFunctionError("glWindowPos2i");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos2iMESA(GLint,GLint){printMissingFunctionError("glWindowPos2iMESA");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos2ivARB(const GLint*){printMissingFunctionError("glWindowPos2ivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos2iv(const GLint*){printMissingFunctionError("glWindowPos2iv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos2ivMESA(const GLint*){printMissingFunctionError("glWindowPos2ivMESA");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos2sARB(GLshort,GLshort){printMissingFunctionError("glWindowPos2sARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos2s(GLshort,GLshort){printMissingFunctionError("glWindowPos2s");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos2sMESA(GLshort,GLshort){printMissingFunctionError("glWindowPos2sMESA");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos2svARB(const GLshort*){printMissingFunctionError("glWindowPos2svARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos2sv(const GLshort*){printMissingFunctionError("glWindowPos2sv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos2svMESA(const GLshort*){printMissingFunctionError("glWindowPos2svMESA");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos3dARB(GLdouble,GLdouble,GLdouble){printMissingFunctionError("glWindowPos3dARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos3d(GLdouble,GLdouble,GLdouble){printMissingFunctionError("glWindowPos3d");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos3dMESA(GLdouble,GLdouble,GLdouble){printMissingFunctionError("glWindowPos3dMESA");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos3dvARB(const GLdouble*){printMissingFunctionError("glWindowPos3dvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos3dv(const GLdouble*){printMissingFunctionError("glWindowPos3dv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos3dvMESA(const GLdouble*){printMissingFunctionError("glWindowPos3dvMESA");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos3fARB(GLfloat,GLfloat,GLfloat){printMissingFunctionError("glWindowPos3fARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos3f(GLfloat,GLfloat,GLfloat){printMissingFunctionError("glWindowPos3f");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos3fMESA(GLfloat,GLfloat,GLfloat){printMissingFunctionError("glWindowPos3fMESA");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos3fvARB(const GLfloat*){printMissingFunctionError("glWindowPos3fvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos3fv(const GLfloat*){printMissingFunctionError("glWindowPos3fv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos3fvMESA(const GLfloat*){printMissingFunctionError("glWindowPos3fvMESA");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos3iARB(GLint,GLint,GLint){printMissingFunctionError("glWindowPos3iARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos3i(GLint,GLint,GLint){printMissingFunctionError("glWindowPos3i");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos3iMESA(GLint,GLint,GLint){printMissingFunctionError("glWindowPos3iMESA");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos3ivARB(const GLint*){printMissingFunctionError("glWindowPos3ivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos3iv(const GLint*){printMissingFunctionError("glWindowPos3iv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos3ivMESA(const GLint*){printMissingFunctionError("glWindowPos3ivMESA");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos3sARB(GLshort,GLshort,GLshort){printMissingFunctionError("glWindowPos3sARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos3s(GLshort,GLshort,GLshort){printMissingFunctionError("glWindowPos3s");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos3sMESA(GLshort,GLshort,GLshort){printMissingFunctionError("glWindowPos3sMESA");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos3svARB(const GLshort*){printMissingFunctionError("glWindowPos3svARB");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos3sv(const GLshort*){printMissingFunctionError("glWindowPos3sv");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos3svMESA(const GLshort*){printMissingFunctionError("glWindowPos3svMESA");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos4dMESA(GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glWindowPos4dMESA");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos4dvMESA(const GLdouble*){printMissingFunctionError("glWindowPos4dvMESA");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos4fMESA(GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glWindowPos4fMESA");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos4fvMESA(const GLfloat*){printMissingFunctionError("glWindowPos4fvMESA");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos4iMESA(GLint,GLint,GLint,GLint){printMissingFunctionError("glWindowPos4iMESA");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos4ivMESA(const GLint*){printMissingFunctionError("glWindowPos4ivMESA");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos4sMESA(GLshort,GLshort,GLshort,GLshort){printMissingFunctionError("glWindowPos4sMESA");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWindowPos4svMESA(const GLshort*){printMissingFunctionError("glWindowPos4svMESA");std::exit(1);return (void)0;}
GEGL_EXPORT void gegl_TrapglWriteMaskEXT(GLuint,GLuint,GLenum,GLenum,GLenum,GLenum){printMissingFunctionError("glWriteMaskEXT");std::exit(1);return (void)0;}
