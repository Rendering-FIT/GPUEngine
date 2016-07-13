#pragma once

GEGL_EXPORT void printMissingFunctionError(char const*fce){std::cerr<<"Function "<<fce<<" is nullptr"<<std::endl;}
GEGL_EXPORT const GLubyte* geglTrapglGetString(GLenum){printMissingFunctionError("glGetString");std::exit(1);return (const GLubyte*)0;}
GEGL_EXPORT const GLubyte* geglTrapglGetStringi(GLenum,GLuint){printMissingFunctionError("glGetStringi");std::exit(1);return (const GLubyte*)0;}
GEGL_EXPORT GLbitfield geglTrapglQueryMatrixxOES(GLfixed*,GLint*){printMissingFunctionError("glQueryMatrixxOES");std::exit(1);return (GLbitfield)0;}
GEGL_EXPORT GLboolean geglTrapglAreProgramsResidentNV(GLsizei,const GLuint*,GLboolean*){printMissingFunctionError("glAreProgramsResidentNV");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglAreTexturesResidentEXT(GLsizei,const GLuint*,GLboolean*){printMissingFunctionError("glAreTexturesResidentEXT");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglAreTexturesResident(GLsizei,const GLuint*,GLboolean*){printMissingFunctionError("glAreTexturesResident");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglIsAsyncMarkerSGIX(GLuint){printMissingFunctionError("glIsAsyncMarkerSGIX");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglIsBufferARB(GLuint){printMissingFunctionError("glIsBufferARB");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglIsBuffer(GLuint){printMissingFunctionError("glIsBuffer");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglIsBufferResidentNV(GLenum){printMissingFunctionError("glIsBufferResidentNV");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglIsCommandListNV(GLuint){printMissingFunctionError("glIsCommandListNV");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglIsEnabled(GLenum){printMissingFunctionError("glIsEnabled");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglIsEnabledi(GLenum,GLuint){printMissingFunctionError("glIsEnabledi");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglIsEnabledIndexedEXT(GLenum,GLuint){printMissingFunctionError("glIsEnabledIndexedEXT");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglIsFenceAPPLE(GLuint){printMissingFunctionError("glIsFenceAPPLE");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglIsFenceNV(GLuint){printMissingFunctionError("glIsFenceNV");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglIsFramebufferEXT(GLuint){printMissingFunctionError("glIsFramebufferEXT");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglIsFramebuffer(GLuint){printMissingFunctionError("glIsFramebuffer");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglIsImageHandleResidentARB(GLuint64){printMissingFunctionError("glIsImageHandleResidentARB");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglIsImageHandleResidentNV(GLuint64){printMissingFunctionError("glIsImageHandleResidentNV");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglIsList(GLuint){printMissingFunctionError("glIsList");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglIsNameAMD(GLenum,GLuint){printMissingFunctionError("glIsNameAMD");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglIsNamedBufferResidentNV(GLuint){printMissingFunctionError("glIsNamedBufferResidentNV");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglIsNamedStringARB(GLint,const GLchar*){printMissingFunctionError("glIsNamedStringARB");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglIsObjectBufferATI(GLuint){printMissingFunctionError("glIsObjectBufferATI");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglIsOcclusionQueryNV(GLuint){printMissingFunctionError("glIsOcclusionQueryNV");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglIsPathNV(GLuint){printMissingFunctionError("glIsPathNV");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglIsPointInFillPathNV(GLuint,GLuint,GLfloat,GLfloat){printMissingFunctionError("glIsPointInFillPathNV");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglIsPointInStrokePathNV(GLuint,GLfloat,GLfloat){printMissingFunctionError("glIsPointInStrokePathNV");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglIsProgramARB(GLuint){printMissingFunctionError("glIsProgramARB");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglIsProgram(GLuint){printMissingFunctionError("glIsProgram");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglIsProgramNV(GLuint){printMissingFunctionError("glIsProgramNV");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglIsProgramPipeline(GLuint){printMissingFunctionError("glIsProgramPipeline");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglIsQueryARB(GLuint){printMissingFunctionError("glIsQueryARB");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglIsQuery(GLuint){printMissingFunctionError("glIsQuery");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglIsRenderbufferEXT(GLuint){printMissingFunctionError("glIsRenderbufferEXT");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglIsRenderbuffer(GLuint){printMissingFunctionError("glIsRenderbuffer");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglIsSampler(GLuint){printMissingFunctionError("glIsSampler");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglIsShader(GLuint){printMissingFunctionError("glIsShader");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglIsStateNV(GLuint){printMissingFunctionError("glIsStateNV");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglIsSync(GLsync){printMissingFunctionError("glIsSync");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglIsTextureEXT(GLuint){printMissingFunctionError("glIsTextureEXT");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglIsTexture(GLuint){printMissingFunctionError("glIsTexture");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglIsTextureHandleResidentARB(GLuint64){printMissingFunctionError("glIsTextureHandleResidentARB");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglIsTextureHandleResidentNV(GLuint64){printMissingFunctionError("glIsTextureHandleResidentNV");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglIsTransformFeedback(GLuint){printMissingFunctionError("glIsTransformFeedback");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglIsTransformFeedbackNV(GLuint){printMissingFunctionError("glIsTransformFeedbackNV");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglIsVariantEnabledEXT(GLuint,GLenum){printMissingFunctionError("glIsVariantEnabledEXT");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglIsVertexArrayAPPLE(GLuint){printMissingFunctionError("glIsVertexArrayAPPLE");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglIsVertexArray(GLuint){printMissingFunctionError("glIsVertexArray");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglIsVertexAttribEnabledAPPLE(GLuint,GLenum){printMissingFunctionError("glIsVertexAttribEnabledAPPLE");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglPointAlongPathNV(GLuint,GLsizei,GLsizei,GLfloat,GLfloat*,GLfloat*,GLfloat*,GLfloat*){printMissingFunctionError("glPointAlongPathNV");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglTestFenceAPPLE(GLuint){printMissingFunctionError("glTestFenceAPPLE");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglTestFenceNV(GLuint){printMissingFunctionError("glTestFenceNV");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglTestObjectAPPLE(GLenum,GLuint){printMissingFunctionError("glTestObjectAPPLE");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglUnmapBufferARB(GLenum){printMissingFunctionError("glUnmapBufferARB");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglUnmapBuffer(GLenum){printMissingFunctionError("glUnmapBuffer");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglUnmapNamedBufferEXT(GLuint){printMissingFunctionError("glUnmapNamedBufferEXT");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglUnmapNamedBuffer(GLuint){printMissingFunctionError("glUnmapNamedBuffer");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLboolean geglTrapglVDPAUIsSurfaceNV(GLvdpauSurfaceNV){printMissingFunctionError("glVDPAUIsSurfaceNV");std::exit(1);return (GLboolean)0;}
GEGL_EXPORT GLenum geglTrapglCheckFramebufferStatusEXT(GLenum){printMissingFunctionError("glCheckFramebufferStatusEXT");std::exit(1);return (GLenum)0;}
GEGL_EXPORT GLenum geglTrapglCheckFramebufferStatus(GLenum){printMissingFunctionError("glCheckFramebufferStatus");std::exit(1);return (GLenum)0;}
GEGL_EXPORT GLenum geglTrapglCheckNamedFramebufferStatusEXT(GLuint,GLenum){printMissingFunctionError("glCheckNamedFramebufferStatusEXT");std::exit(1);return (GLenum)0;}
GEGL_EXPORT GLenum geglTrapglCheckNamedFramebufferStatus(GLuint,GLenum){printMissingFunctionError("glCheckNamedFramebufferStatus");std::exit(1);return (GLenum)0;}
GEGL_EXPORT GLenum geglTrapglClientWaitSync(GLsync,GLbitfield,GLuint64){printMissingFunctionError("glClientWaitSync");std::exit(1);return (GLenum)0;}
GEGL_EXPORT GLenum geglTrapglGetError(){printMissingFunctionError("glGetError");std::exit(1);return (GLenum)0;}
GEGL_EXPORT GLenum geglTrapglGetGraphicsResetStatus(){printMissingFunctionError("glGetGraphicsResetStatus");std::exit(1);return (GLenum)0;}
GEGL_EXPORT GLenum geglTrapglGetGraphicsResetStatusARB(){printMissingFunctionError("glGetGraphicsResetStatusARB");std::exit(1);return (GLenum)0;}
GEGL_EXPORT GLenum geglTrapglObjectPurgeableAPPLE(GLenum,GLuint,GLenum){printMissingFunctionError("glObjectPurgeableAPPLE");std::exit(1);return (GLenum)0;}
GEGL_EXPORT GLenum geglTrapglObjectUnpurgeableAPPLE(GLenum,GLuint,GLenum){printMissingFunctionError("glObjectUnpurgeableAPPLE");std::exit(1);return (GLenum)0;}
GEGL_EXPORT GLenum geglTrapglPathGlyphIndexArrayNV(GLuint,GLenum,const void*,GLbitfield,GLuint,GLsizei,GLuint,GLfloat){printMissingFunctionError("glPathGlyphIndexArrayNV");std::exit(1);return (GLenum)0;}
GEGL_EXPORT GLenum geglTrapglPathGlyphIndexRangeNV(GLenum,const void*,GLbitfield,GLuint,GLfloat,GLuint){printMissingFunctionError("glPathGlyphIndexRangeNV");std::exit(1);return (GLenum)0;}
GEGL_EXPORT GLenum geglTrapglPathMemoryGlyphIndexArrayNV(GLuint,GLenum,GLsizeiptr,const void*,GLsizei,GLuint,GLsizei,GLuint,GLfloat){printMissingFunctionError("glPathMemoryGlyphIndexArrayNV");std::exit(1);return (GLenum)0;}
GEGL_EXPORT GLenum geglTrapglVideoCaptureNV(GLuint,GLuint*,GLuint64EXT*){printMissingFunctionError("glVideoCaptureNV");std::exit(1);return (GLenum)0;}
GEGL_EXPORT GLfloat geglTrapglGetPathLengthNV(GLuint,GLsizei,GLsizei){printMissingFunctionError("glGetPathLengthNV");std::exit(1);return (GLfloat)0;}
GEGL_EXPORT GLhandleARB geglTrapglCreateProgramObjectARB(){printMissingFunctionError("glCreateProgramObjectARB");std::exit(1);return (GLhandleARB)0;}
GEGL_EXPORT GLhandleARB geglTrapglCreateShaderObjectARB(GLenum){printMissingFunctionError("glCreateShaderObjectARB");std::exit(1);return (GLhandleARB)0;}
GEGL_EXPORT GLhandleARB geglTrapglGetHandleARB(GLenum){printMissingFunctionError("glGetHandleARB");std::exit(1);return (GLhandleARB)0;}
GEGL_EXPORT GLint geglTrapglFinishAsyncSGIX(GLuint*){printMissingFunctionError("glFinishAsyncSGIX");std::exit(1);return (GLint)0;}
GEGL_EXPORT GLint geglTrapglGetAttribLocationARB(GLhandleARB,const GLcharARB*){printMissingFunctionError("glGetAttribLocationARB");std::exit(1);return (GLint)0;}
GEGL_EXPORT GLint geglTrapglGetAttribLocation(GLuint,const GLchar*){printMissingFunctionError("glGetAttribLocation");std::exit(1);return (GLint)0;}
GEGL_EXPORT GLint geglTrapglGetFragDataIndex(GLuint,const GLchar*){printMissingFunctionError("glGetFragDataIndex");std::exit(1);return (GLint)0;}
GEGL_EXPORT GLint geglTrapglGetFragDataLocationEXT(GLuint,const GLchar*){printMissingFunctionError("glGetFragDataLocationEXT");std::exit(1);return (GLint)0;}
GEGL_EXPORT GLint geglTrapglGetFragDataLocation(GLuint,const GLchar*){printMissingFunctionError("glGetFragDataLocation");std::exit(1);return (GLint)0;}
GEGL_EXPORT GLint geglTrapglGetInstrumentsSGIX(){printMissingFunctionError("glGetInstrumentsSGIX");std::exit(1);return (GLint)0;}
GEGL_EXPORT GLint geglTrapglGetProgramResourceLocation(GLuint,GLenum,const GLchar*){printMissingFunctionError("glGetProgramResourceLocation");std::exit(1);return (GLint)0;}
GEGL_EXPORT GLint geglTrapglGetProgramResourceLocationIndex(GLuint,GLenum,const GLchar*){printMissingFunctionError("glGetProgramResourceLocationIndex");std::exit(1);return (GLint)0;}
GEGL_EXPORT GLint geglTrapglGetSubroutineUniformLocation(GLuint,GLenum,const GLchar*){printMissingFunctionError("glGetSubroutineUniformLocation");std::exit(1);return (GLint)0;}
GEGL_EXPORT GLint geglTrapglGetUniformBufferSizeEXT(GLuint,GLint){printMissingFunctionError("glGetUniformBufferSizeEXT");std::exit(1);return (GLint)0;}
GEGL_EXPORT GLint geglTrapglGetUniformLocationARB(GLhandleARB,const GLcharARB*){printMissingFunctionError("glGetUniformLocationARB");std::exit(1);return (GLint)0;}
GEGL_EXPORT GLint geglTrapglGetUniformLocation(GLuint,const GLchar*){printMissingFunctionError("glGetUniformLocation");std::exit(1);return (GLint)0;}
GEGL_EXPORT GLint geglTrapglGetVaryingLocationNV(GLuint,const GLchar*){printMissingFunctionError("glGetVaryingLocationNV");std::exit(1);return (GLint)0;}
GEGL_EXPORT GLint geglTrapglPollAsyncSGIX(GLuint*){printMissingFunctionError("glPollAsyncSGIX");std::exit(1);return (GLint)0;}
GEGL_EXPORT GLint geglTrapglPollInstrumentsSGIX(GLint*){printMissingFunctionError("glPollInstrumentsSGIX");std::exit(1);return (GLint)0;}
GEGL_EXPORT GLint geglTrapglRenderMode(GLenum){printMissingFunctionError("glRenderMode");std::exit(1);return (GLint)0;}
GEGL_EXPORT GLintptr geglTrapglGetUniformOffsetEXT(GLuint,GLint){printMissingFunctionError("glGetUniformOffsetEXT");std::exit(1);return (GLintptr)0;}
GEGL_EXPORT GLsync geglTrapglCreateSyncFromCLeventARB(struct _cl_context*,struct _cl_event*,GLbitfield){printMissingFunctionError("glCreateSyncFromCLeventARB");std::exit(1);return (GLsync)0;}
GEGL_EXPORT GLsync geglTrapglFenceSync(GLenum,GLbitfield){printMissingFunctionError("glFenceSync");std::exit(1);return (GLsync)0;}
GEGL_EXPORT GLsync geglTrapglImportSyncEXT(GLenum,GLintptr,GLbitfield){printMissingFunctionError("glImportSyncEXT");std::exit(1);return (GLsync)0;}
GEGL_EXPORT GLuint64 geglTrapglGetImageHandleARB(GLuint,GLint,GLboolean,GLint,GLenum){printMissingFunctionError("glGetImageHandleARB");std::exit(1);return (GLuint64)0;}
GEGL_EXPORT GLuint64 geglTrapglGetImageHandleNV(GLuint,GLint,GLboolean,GLint,GLenum){printMissingFunctionError("glGetImageHandleNV");std::exit(1);return (GLuint64)0;}
GEGL_EXPORT GLuint64 geglTrapglGetTextureHandleARB(GLuint){printMissingFunctionError("glGetTextureHandleARB");std::exit(1);return (GLuint64)0;}
GEGL_EXPORT GLuint64 geglTrapglGetTextureHandleNV(GLuint){printMissingFunctionError("glGetTextureHandleNV");std::exit(1);return (GLuint64)0;}
GEGL_EXPORT GLuint64 geglTrapglGetTextureSamplerHandleARB(GLuint,GLuint){printMissingFunctionError("glGetTextureSamplerHandleARB");std::exit(1);return (GLuint64)0;}
GEGL_EXPORT GLuint64 geglTrapglGetTextureSamplerHandleNV(GLuint,GLuint){printMissingFunctionError("glGetTextureSamplerHandleNV");std::exit(1);return (GLuint64)0;}
GEGL_EXPORT GLuint geglTrapglBindLightParameterEXT(GLenum,GLenum){printMissingFunctionError("glBindLightParameterEXT");std::exit(1);return (GLuint)0;}
GEGL_EXPORT GLuint geglTrapglBindMaterialParameterEXT(GLenum,GLenum){printMissingFunctionError("glBindMaterialParameterEXT");std::exit(1);return (GLuint)0;}
GEGL_EXPORT GLuint geglTrapglBindParameterEXT(GLenum){printMissingFunctionError("glBindParameterEXT");std::exit(1);return (GLuint)0;}
GEGL_EXPORT GLuint geglTrapglBindTexGenParameterEXT(GLenum,GLenum,GLenum){printMissingFunctionError("glBindTexGenParameterEXT");std::exit(1);return (GLuint)0;}
GEGL_EXPORT GLuint geglTrapglBindTextureUnitParameterEXT(GLenum,GLenum){printMissingFunctionError("glBindTextureUnitParameterEXT");std::exit(1);return (GLuint)0;}
GEGL_EXPORT GLuint geglTrapglCreateProgram(){printMissingFunctionError("glCreateProgram");std::exit(1);return (GLuint)0;}
GEGL_EXPORT GLuint geglTrapglCreateShader(GLenum){printMissingFunctionError("glCreateShader");std::exit(1);return (GLuint)0;}
GEGL_EXPORT GLuint geglTrapglCreateShaderProgramEXT(GLenum,const GLchar*){printMissingFunctionError("glCreateShaderProgramEXT");std::exit(1);return (GLuint)0;}
GEGL_EXPORT GLuint geglTrapglCreateShaderProgramv(GLenum,GLsizei,const GLchar*const*){printMissingFunctionError("glCreateShaderProgramv");std::exit(1);return (GLuint)0;}
GEGL_EXPORT GLuint geglTrapglGenAsyncMarkersSGIX(GLsizei){printMissingFunctionError("glGenAsyncMarkersSGIX");std::exit(1);return (GLuint)0;}
GEGL_EXPORT GLuint geglTrapglGenFragmentShadersATI(GLuint){printMissingFunctionError("glGenFragmentShadersATI");std::exit(1);return (GLuint)0;}
GEGL_EXPORT GLuint geglTrapglGenLists(GLsizei){printMissingFunctionError("glGenLists");std::exit(1);return (GLuint)0;}
GEGL_EXPORT GLuint geglTrapglGenPathsNV(GLsizei){printMissingFunctionError("glGenPathsNV");std::exit(1);return (GLuint)0;}
GEGL_EXPORT GLuint geglTrapglGenSymbolsEXT(GLenum,GLenum,GLenum,GLuint){printMissingFunctionError("glGenSymbolsEXT");std::exit(1);return (GLuint)0;}
GEGL_EXPORT GLuint geglTrapglGenVertexShadersEXT(GLuint){printMissingFunctionError("glGenVertexShadersEXT");std::exit(1);return (GLuint)0;}
GEGL_EXPORT GLuint geglTrapglGetCommandHeaderNV(GLenum,GLuint){printMissingFunctionError("glGetCommandHeaderNV");std::exit(1);return (GLuint)0;}
GEGL_EXPORT GLuint geglTrapglGetDebugMessageLogAMD(GLuint,GLsizei,GLenum*,GLuint*,GLuint*,GLsizei*,GLchar*){printMissingFunctionError("glGetDebugMessageLogAMD");std::exit(1);return (GLuint)0;}
GEGL_EXPORT GLuint geglTrapglGetDebugMessageLogARB(GLuint,GLsizei,GLenum*,GLenum*,GLuint*,GLenum*,GLsizei*,GLchar*){printMissingFunctionError("glGetDebugMessageLogARB");std::exit(1);return (GLuint)0;}
GEGL_EXPORT GLuint geglTrapglGetDebugMessageLog(GLuint,GLsizei,GLenum*,GLenum*,GLuint*,GLenum*,GLsizei*,GLchar*){printMissingFunctionError("glGetDebugMessageLog");std::exit(1);return (GLuint)0;}
GEGL_EXPORT GLuint geglTrapglGetProgramResourceIndex(GLuint,GLenum,const GLchar*){printMissingFunctionError("glGetProgramResourceIndex");std::exit(1);return (GLuint)0;}
GEGL_EXPORT GLuint geglTrapglGetSubroutineIndex(GLuint,GLenum,const GLchar*){printMissingFunctionError("glGetSubroutineIndex");std::exit(1);return (GLuint)0;}
GEGL_EXPORT GLuint geglTrapglGetUniformBlockIndex(GLuint,const GLchar*){printMissingFunctionError("glGetUniformBlockIndex");std::exit(1);return (GLuint)0;}
GEGL_EXPORT GLuint geglTrapglNewObjectBufferATI(GLsizei,const void*,GLenum){printMissingFunctionError("glNewObjectBufferATI");std::exit(1);return (GLuint)0;}
GEGL_EXPORT GLushort geglTrapglGetStageIndexNV(GLenum){printMissingFunctionError("glGetStageIndexNV");std::exit(1);return (GLushort)0;}
GEGL_EXPORT GLvdpauSurfaceNV geglTrapglVDPAURegisterOutputSurfaceNV(const void*,GLenum,GLsizei,const GLuint*){printMissingFunctionError("glVDPAURegisterOutputSurfaceNV");std::exit(1);return (GLvdpauSurfaceNV)0;}
GEGL_EXPORT GLvdpauSurfaceNV geglTrapglVDPAURegisterVideoSurfaceNV(const void*,GLenum,GLsizei,const GLuint*){printMissingFunctionError("glVDPAURegisterVideoSurfaceNV");std::exit(1);return (GLvdpauSurfaceNV)0;}
GEGL_EXPORT void geglTrapglAccum(GLenum,GLfloat){printMissingFunctionError("glAccum");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglAccumxOES(GLenum,GLfixed){printMissingFunctionError("glAccumxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglActiveProgramEXT(GLuint){printMissingFunctionError("glActiveProgramEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglActiveShaderProgram(GLuint,GLuint){printMissingFunctionError("glActiveShaderProgram");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglActiveStencilFaceEXT(GLenum){printMissingFunctionError("glActiveStencilFaceEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglActiveTextureARB(GLenum){printMissingFunctionError("glActiveTextureARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglActiveTexture(GLenum){printMissingFunctionError("glActiveTexture");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglActiveVaryingNV(GLuint,const GLchar*){printMissingFunctionError("glActiveVaryingNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglAlphaFragmentOp1ATI(GLenum,GLuint,GLuint,GLuint,GLuint,GLuint){printMissingFunctionError("glAlphaFragmentOp1ATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglAlphaFragmentOp2ATI(GLenum,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint){printMissingFunctionError("glAlphaFragmentOp2ATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglAlphaFragmentOp3ATI(GLenum,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint){printMissingFunctionError("glAlphaFragmentOp3ATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglAlphaFunc(GLenum,GLclampf){printMissingFunctionError("glAlphaFunc");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglAlphaFuncxOES(GLenum,GLfixed){printMissingFunctionError("glAlphaFuncxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglApplyFramebufferAttachmentCMAAINTEL(){printMissingFunctionError("glApplyFramebufferAttachmentCMAAINTEL");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglApplyTextureEXT(GLenum){printMissingFunctionError("glApplyTextureEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglArrayElementEXT(GLint){printMissingFunctionError("glArrayElementEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglArrayElement(GLint){printMissingFunctionError("glArrayElement");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglArrayObjectATI(GLenum,GLint,GLenum,GLsizei,GLuint,GLuint){printMissingFunctionError("glArrayObjectATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglAsyncMarkerSGIX(GLuint){printMissingFunctionError("glAsyncMarkerSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglAttachObjectARB(GLhandleARB,GLhandleARB){printMissingFunctionError("glAttachObjectARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglAttachShader(GLuint,GLuint){printMissingFunctionError("glAttachShader");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBeginConditionalRender(GLuint,GLenum){printMissingFunctionError("glBeginConditionalRender");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBeginConditionalRenderNV(GLuint,GLenum){printMissingFunctionError("glBeginConditionalRenderNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBeginConditionalRenderNVX(GLuint){printMissingFunctionError("glBeginConditionalRenderNVX");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBeginFragmentShaderATI(){printMissingFunctionError("glBeginFragmentShaderATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBegin(GLenum){printMissingFunctionError("glBegin");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBeginOcclusionQueryNV(GLuint){printMissingFunctionError("glBeginOcclusionQueryNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBeginPerfMonitorAMD(GLuint){printMissingFunctionError("glBeginPerfMonitorAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBeginPerfQueryINTEL(GLuint){printMissingFunctionError("glBeginPerfQueryINTEL");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBeginQueryARB(GLenum,GLuint){printMissingFunctionError("glBeginQueryARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBeginQuery(GLenum,GLuint){printMissingFunctionError("glBeginQuery");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBeginQueryIndexed(GLenum,GLuint,GLuint){printMissingFunctionError("glBeginQueryIndexed");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBeginTransformFeedbackEXT(GLenum){printMissingFunctionError("glBeginTransformFeedbackEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBeginTransformFeedback(GLenum){printMissingFunctionError("glBeginTransformFeedback");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBeginTransformFeedbackNV(GLenum){printMissingFunctionError("glBeginTransformFeedbackNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBeginVertexShaderEXT(){printMissingFunctionError("glBeginVertexShaderEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBeginVideoCaptureNV(GLuint){printMissingFunctionError("glBeginVideoCaptureNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBindAttribLocationARB(GLhandleARB,GLuint,const GLcharARB*){printMissingFunctionError("glBindAttribLocationARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBindAttribLocation(GLuint,GLuint,const GLchar*){printMissingFunctionError("glBindAttribLocation");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBindBufferARB(GLenum,GLuint){printMissingFunctionError("glBindBufferARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBindBufferBaseEXT(GLenum,GLuint,GLuint){printMissingFunctionError("glBindBufferBaseEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBindBufferBase(GLenum,GLuint,GLuint){printMissingFunctionError("glBindBufferBase");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBindBufferBaseNV(GLenum,GLuint,GLuint){printMissingFunctionError("glBindBufferBaseNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBindBuffer(GLenum,GLuint){printMissingFunctionError("glBindBuffer");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBindBufferOffsetEXT(GLenum,GLuint,GLuint,GLintptr){printMissingFunctionError("glBindBufferOffsetEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBindBufferOffsetNV(GLenum,GLuint,GLuint,GLintptr){printMissingFunctionError("glBindBufferOffsetNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBindBufferRangeEXT(GLenum,GLuint,GLuint,GLintptr,GLsizeiptr){printMissingFunctionError("glBindBufferRangeEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBindBufferRange(GLenum,GLuint,GLuint,GLintptr,GLsizeiptr){printMissingFunctionError("glBindBufferRange");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBindBufferRangeNV(GLenum,GLuint,GLuint,GLintptr,GLsizeiptr){printMissingFunctionError("glBindBufferRangeNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBindBuffersBase(GLenum,GLuint,GLsizei,const GLuint*){printMissingFunctionError("glBindBuffersBase");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBindBuffersRange(GLenum,GLuint,GLsizei,const GLuint*,const GLintptr*,const GLsizeiptr*){printMissingFunctionError("glBindBuffersRange");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBindFragDataLocationEXT(GLuint,GLuint,const GLchar*){printMissingFunctionError("glBindFragDataLocationEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBindFragDataLocation(GLuint,GLuint,const GLchar*){printMissingFunctionError("glBindFragDataLocation");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBindFragDataLocationIndexed(GLuint,GLuint,GLuint,const GLchar*){printMissingFunctionError("glBindFragDataLocationIndexed");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBindFragmentShaderATI(GLuint){printMissingFunctionError("glBindFragmentShaderATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBindFramebufferEXT(GLenum,GLuint){printMissingFunctionError("glBindFramebufferEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBindFramebuffer(GLenum,GLuint){printMissingFunctionError("glBindFramebuffer");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBindImageTextureEXT(GLuint,GLuint,GLint,GLboolean,GLint,GLenum,GLint){printMissingFunctionError("glBindImageTextureEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBindImageTexture(GLuint,GLuint,GLint,GLboolean,GLint,GLenum,GLenum){printMissingFunctionError("glBindImageTexture");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBindImageTextures(GLuint,GLsizei,const GLuint*){printMissingFunctionError("glBindImageTextures");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBindMultiTextureEXT(GLenum,GLenum,GLuint){printMissingFunctionError("glBindMultiTextureEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBindProgramARB(GLenum,GLuint){printMissingFunctionError("glBindProgramARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBindProgramNV(GLenum,GLuint){printMissingFunctionError("glBindProgramNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBindProgramPipeline(GLuint){printMissingFunctionError("glBindProgramPipeline");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBindRenderbufferEXT(GLenum,GLuint){printMissingFunctionError("glBindRenderbufferEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBindRenderbuffer(GLenum,GLuint){printMissingFunctionError("glBindRenderbuffer");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBindSampler(GLuint,GLuint){printMissingFunctionError("glBindSampler");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBindSamplers(GLuint,GLsizei,const GLuint*){printMissingFunctionError("glBindSamplers");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBindTextureEXT(GLenum,GLuint){printMissingFunctionError("glBindTextureEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBindTexture(GLenum,GLuint){printMissingFunctionError("glBindTexture");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBindTextures(GLuint,GLsizei,const GLuint*){printMissingFunctionError("glBindTextures");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBindTextureUnit(GLuint,GLuint){printMissingFunctionError("glBindTextureUnit");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBindTransformFeedback(GLenum,GLuint){printMissingFunctionError("glBindTransformFeedback");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBindTransformFeedbackNV(GLenum,GLuint){printMissingFunctionError("glBindTransformFeedbackNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBindVertexArrayAPPLE(GLuint){printMissingFunctionError("glBindVertexArrayAPPLE");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBindVertexArray(GLuint){printMissingFunctionError("glBindVertexArray");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBindVertexBuffer(GLuint,GLuint,GLintptr,GLsizei){printMissingFunctionError("glBindVertexBuffer");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBindVertexBuffers(GLuint,GLsizei,const GLuint*,const GLintptr*,const GLsizei*){printMissingFunctionError("glBindVertexBuffers");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBindVertexShaderEXT(GLuint){printMissingFunctionError("glBindVertexShaderEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBindVideoCaptureStreamBufferNV(GLuint,GLuint,GLenum,GLintptrARB){printMissingFunctionError("glBindVideoCaptureStreamBufferNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBindVideoCaptureStreamTextureNV(GLuint,GLuint,GLenum,GLenum,GLuint){printMissingFunctionError("glBindVideoCaptureStreamTextureNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBinormal3bEXT(GLbyte,GLbyte,GLbyte){printMissingFunctionError("glBinormal3bEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBinormal3bvEXT(const GLbyte*){printMissingFunctionError("glBinormal3bvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBinormal3dEXT(GLdouble,GLdouble,GLdouble){printMissingFunctionError("glBinormal3dEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBinormal3dvEXT(const GLdouble*){printMissingFunctionError("glBinormal3dvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBinormal3fEXT(GLfloat,GLfloat,GLfloat){printMissingFunctionError("glBinormal3fEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBinormal3fvEXT(const GLfloat*){printMissingFunctionError("glBinormal3fvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBinormal3iEXT(GLint,GLint,GLint){printMissingFunctionError("glBinormal3iEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBinormal3ivEXT(const GLint*){printMissingFunctionError("glBinormal3ivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBinormal3sEXT(GLshort,GLshort,GLshort){printMissingFunctionError("glBinormal3sEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBinormal3svEXT(const GLshort*){printMissingFunctionError("glBinormal3svEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBinormalPointerEXT(GLenum,GLsizei,const void*){printMissingFunctionError("glBinormalPointerEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBitmap(GLsizei,GLsizei,GLfloat,GLfloat,GLfloat,GLfloat,const GLubyte*){printMissingFunctionError("glBitmap");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBitmapxOES(GLsizei,GLsizei,GLfixed,GLfixed,GLfixed,GLfixed,const GLubyte*){printMissingFunctionError("glBitmapxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBlendBarrierKHR(){printMissingFunctionError("glBlendBarrierKHR");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBlendBarrierNV(){printMissingFunctionError("glBlendBarrierNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBlendColorEXT(GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glBlendColorEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBlendColor(GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glBlendColor");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBlendColorxOES(GLfixed,GLfixed,GLfixed,GLfixed){printMissingFunctionError("glBlendColorxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBlendEquationEXT(GLenum){printMissingFunctionError("glBlendEquationEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBlendEquation(GLenum){printMissingFunctionError("glBlendEquation");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBlendEquationiARB(GLuint,GLenum){printMissingFunctionError("glBlendEquationiARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBlendEquationi(GLuint,GLenum){printMissingFunctionError("glBlendEquationi");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBlendEquationIndexedAMD(GLuint,GLenum){printMissingFunctionError("glBlendEquationIndexedAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBlendEquationSeparateATI(GLenum,GLenum){printMissingFunctionError("glBlendEquationSeparateATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBlendEquationSeparateEXT(GLenum,GLenum){printMissingFunctionError("glBlendEquationSeparateEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBlendEquationSeparate(GLenum,GLenum){printMissingFunctionError("glBlendEquationSeparate");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBlendEquationSeparateiARB(GLuint,GLenum,GLenum){printMissingFunctionError("glBlendEquationSeparateiARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBlendEquationSeparatei(GLuint,GLenum,GLenum){printMissingFunctionError("glBlendEquationSeparatei");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBlendEquationSeparateIndexedAMD(GLuint,GLenum,GLenum){printMissingFunctionError("glBlendEquationSeparateIndexedAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBlendFunc(GLenum,GLenum){printMissingFunctionError("glBlendFunc");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBlendFunciARB(GLuint,GLenum,GLenum){printMissingFunctionError("glBlendFunciARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBlendFunci(GLuint,GLenum,GLenum){printMissingFunctionError("glBlendFunci");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBlendFuncIndexedAMD(GLuint,GLenum,GLenum){printMissingFunctionError("glBlendFuncIndexedAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBlendFuncSeparateEXT(GLenum,GLenum,GLenum,GLenum){printMissingFunctionError("glBlendFuncSeparateEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBlendFuncSeparate(GLenum,GLenum,GLenum,GLenum){printMissingFunctionError("glBlendFuncSeparate");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBlendFuncSeparateiARB(GLuint,GLenum,GLenum,GLenum,GLenum){printMissingFunctionError("glBlendFuncSeparateiARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBlendFuncSeparatei(GLuint,GLenum,GLenum,GLenum,GLenum){printMissingFunctionError("glBlendFuncSeparatei");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBlendFuncSeparateIndexedAMD(GLuint,GLenum,GLenum,GLenum,GLenum){printMissingFunctionError("glBlendFuncSeparateIndexedAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBlendFuncSeparateINGR(GLenum,GLenum,GLenum,GLenum){printMissingFunctionError("glBlendFuncSeparateINGR");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBlendParameteriNV(GLenum,GLint){printMissingFunctionError("glBlendParameteriNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBlitFramebufferEXT(GLint,GLint,GLint,GLint,GLint,GLint,GLint,GLint,GLbitfield,GLenum){printMissingFunctionError("glBlitFramebufferEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBlitFramebuffer(GLint,GLint,GLint,GLint,GLint,GLint,GLint,GLint,GLbitfield,GLenum){printMissingFunctionError("glBlitFramebuffer");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBlitNamedFramebuffer(GLuint,GLuint,GLint,GLint,GLint,GLint,GLint,GLint,GLint,GLint,GLbitfield,GLenum){printMissingFunctionError("glBlitNamedFramebuffer");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBufferAddressRangeNV(GLenum,GLuint,GLuint64EXT,GLsizeiptr){printMissingFunctionError("glBufferAddressRangeNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBufferDataARB(GLenum,GLsizeiptrARB,const void*,GLenum){printMissingFunctionError("glBufferDataARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBufferData(GLenum,GLsizeiptr,const void*,GLenum){printMissingFunctionError("glBufferData");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBufferPageCommitmentARB(GLenum,GLintptr,GLsizeiptr,GLboolean){printMissingFunctionError("glBufferPageCommitmentARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBufferParameteriAPPLE(GLenum,GLenum,GLint){printMissingFunctionError("glBufferParameteriAPPLE");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBufferStorage(GLenum,GLsizeiptr,const void*,GLbitfield){printMissingFunctionError("glBufferStorage");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBufferSubDataARB(GLenum,GLintptrARB,GLsizeiptrARB,const void*){printMissingFunctionError("glBufferSubDataARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglBufferSubData(GLenum,GLintptr,GLsizeiptr,const void*){printMissingFunctionError("glBufferSubData");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCallCommandListNV(GLuint){printMissingFunctionError("glCallCommandListNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCallList(GLuint){printMissingFunctionError("glCallList");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCallLists(GLsizei,GLenum,const GLvoid*){printMissingFunctionError("glCallLists");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglClampColorARB(GLenum,GLenum){printMissingFunctionError("glClampColorARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglClampColor(GLenum,GLenum){printMissingFunctionError("glClampColor");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglClearAccum(GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glClearAccum");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglClearAccumxOES(GLfixed,GLfixed,GLfixed,GLfixed){printMissingFunctionError("glClearAccumxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglClearBufferData(GLenum,GLenum,GLenum,GLenum,const void*){printMissingFunctionError("glClearBufferData");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglClearBufferfi(GLenum,GLint,GLfloat,GLint){printMissingFunctionError("glClearBufferfi");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglClearBufferfv(GLenum,GLint,const GLfloat*){printMissingFunctionError("glClearBufferfv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglClearBufferiv(GLenum,GLint,const GLint*){printMissingFunctionError("glClearBufferiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglClearBufferSubData(GLenum,GLenum,GLintptr,GLsizeiptr,GLenum,GLenum,const void*){printMissingFunctionError("glClearBufferSubData");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglClearBufferuiv(GLenum,GLint,const GLuint*){printMissingFunctionError("glClearBufferuiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglClearColor(GLclampf,GLclampf,GLclampf,GLclampf){printMissingFunctionError("glClearColor");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglClearColorIiEXT(GLint,GLint,GLint,GLint){printMissingFunctionError("glClearColorIiEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglClearColorIuiEXT(GLuint,GLuint,GLuint,GLuint){printMissingFunctionError("glClearColorIuiEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglClearColorxOES(GLfixed,GLfixed,GLfixed,GLfixed){printMissingFunctionError("glClearColorxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglClearDepthdNV(GLdouble){printMissingFunctionError("glClearDepthdNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglClearDepthf(GLfloat){printMissingFunctionError("glClearDepthf");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglClearDepthfOES(GLclampf){printMissingFunctionError("glClearDepthfOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglClearDepth(GLclampd){printMissingFunctionError("glClearDepth");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglClearDepthxOES(GLfixed){printMissingFunctionError("glClearDepthxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglClear(GLbitfield){printMissingFunctionError("glClear");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglClearIndex(GLfloat){printMissingFunctionError("glClearIndex");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglClearNamedBufferDataEXT(GLuint,GLenum,GLenum,GLenum,const void*){printMissingFunctionError("glClearNamedBufferDataEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglClearNamedBufferData(GLuint,GLenum,GLenum,GLenum,const void*){printMissingFunctionError("glClearNamedBufferData");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglClearNamedBufferSubDataEXT(GLuint,GLenum,GLsizeiptr,GLsizeiptr,GLenum,GLenum,const void*){printMissingFunctionError("glClearNamedBufferSubDataEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglClearNamedBufferSubData(GLuint,GLenum,GLintptr,GLsizeiptr,GLenum,GLenum,const void*){printMissingFunctionError("glClearNamedBufferSubData");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglClearNamedFramebufferfi(GLuint,GLenum,GLint,GLfloat,GLint){printMissingFunctionError("glClearNamedFramebufferfi");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglClearNamedFramebufferfv(GLuint,GLenum,GLint,const GLfloat*){printMissingFunctionError("glClearNamedFramebufferfv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglClearNamedFramebufferiv(GLuint,GLenum,GLint,const GLint*){printMissingFunctionError("glClearNamedFramebufferiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglClearNamedFramebufferuiv(GLuint,GLenum,GLint,const GLuint*){printMissingFunctionError("glClearNamedFramebufferuiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglClearStencil(GLint){printMissingFunctionError("glClearStencil");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglClearTexImage(GLuint,GLint,GLenum,GLenum,const void*){printMissingFunctionError("glClearTexImage");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglClearTexSubImage(GLuint,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLenum,GLenum,const void*){printMissingFunctionError("glClearTexSubImage");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglClientActiveTextureARB(GLenum){printMissingFunctionError("glClientActiveTextureARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglClientActiveTexture(GLenum){printMissingFunctionError("glClientActiveTexture");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglClientActiveVertexStreamATI(GLenum){printMissingFunctionError("glClientActiveVertexStreamATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglClientAttribDefaultEXT(GLbitfield){printMissingFunctionError("glClientAttribDefaultEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglClipControl(GLenum,GLenum){printMissingFunctionError("glClipControl");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglClipPlanefOES(GLenum,const GLfloat*){printMissingFunctionError("glClipPlanefOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglClipPlane(GLenum,const GLdouble*){printMissingFunctionError("glClipPlane");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglClipPlanexOES(GLenum,const GLfixed*){printMissingFunctionError("glClipPlanexOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColor3b(GLbyte,GLbyte,GLbyte){printMissingFunctionError("glColor3b");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColor3bv(const GLbyte*){printMissingFunctionError("glColor3bv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColor3d(GLdouble,GLdouble,GLdouble){printMissingFunctionError("glColor3d");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColor3dv(const GLdouble*){printMissingFunctionError("glColor3dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColor3f(GLfloat,GLfloat,GLfloat){printMissingFunctionError("glColor3f");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColor3fv(const GLfloat*){printMissingFunctionError("glColor3fv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColor3fVertex3fSUN(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glColor3fVertex3fSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColor3fVertex3fvSUN(const GLfloat*,const GLfloat*){printMissingFunctionError("glColor3fVertex3fvSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColor3hNV(GLhalfNV,GLhalfNV,GLhalfNV){printMissingFunctionError("glColor3hNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColor3hvNV(const GLhalfNV*){printMissingFunctionError("glColor3hvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColor3i(GLint,GLint,GLint){printMissingFunctionError("glColor3i");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColor3iv(const GLint*){printMissingFunctionError("glColor3iv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColor3s(GLshort,GLshort,GLshort){printMissingFunctionError("glColor3s");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColor3sv(const GLshort*){printMissingFunctionError("glColor3sv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColor3ub(GLubyte,GLubyte,GLubyte){printMissingFunctionError("glColor3ub");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColor3ubv(const GLubyte*){printMissingFunctionError("glColor3ubv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColor3ui(GLuint,GLuint,GLuint){printMissingFunctionError("glColor3ui");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColor3uiv(const GLuint*){printMissingFunctionError("glColor3uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColor3us(GLushort,GLushort,GLushort){printMissingFunctionError("glColor3us");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColor3usv(const GLushort*){printMissingFunctionError("glColor3usv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColor3xOES(GLfixed,GLfixed,GLfixed){printMissingFunctionError("glColor3xOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColor3xvOES(const GLfixed*){printMissingFunctionError("glColor3xvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColor4b(GLbyte,GLbyte,GLbyte,GLbyte){printMissingFunctionError("glColor4b");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColor4bv(const GLbyte*){printMissingFunctionError("glColor4bv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColor4d(GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glColor4d");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColor4dv(const GLdouble*){printMissingFunctionError("glColor4dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColor4f(GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glColor4f");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColor4fNormal3fVertex3fSUN(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glColor4fNormal3fVertex3fSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColor4fNormal3fVertex3fvSUN(const GLfloat*,const GLfloat*,const GLfloat*){printMissingFunctionError("glColor4fNormal3fVertex3fvSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColor4fv(const GLfloat*){printMissingFunctionError("glColor4fv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColor4hNV(GLhalfNV,GLhalfNV,GLhalfNV,GLhalfNV){printMissingFunctionError("glColor4hNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColor4hvNV(const GLhalfNV*){printMissingFunctionError("glColor4hvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColor4i(GLint,GLint,GLint,GLint){printMissingFunctionError("glColor4i");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColor4iv(const GLint*){printMissingFunctionError("glColor4iv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColor4s(GLshort,GLshort,GLshort,GLshort){printMissingFunctionError("glColor4s");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColor4sv(const GLshort*){printMissingFunctionError("glColor4sv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColor4ub(GLubyte,GLubyte,GLubyte,GLubyte){printMissingFunctionError("glColor4ub");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColor4ubv(const GLubyte*){printMissingFunctionError("glColor4ubv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColor4ubVertex2fSUN(GLubyte,GLubyte,GLubyte,GLubyte,GLfloat,GLfloat){printMissingFunctionError("glColor4ubVertex2fSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColor4ubVertex2fvSUN(const GLubyte*,const GLfloat*){printMissingFunctionError("glColor4ubVertex2fvSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColor4ubVertex3fSUN(GLubyte,GLubyte,GLubyte,GLubyte,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glColor4ubVertex3fSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColor4ubVertex3fvSUN(const GLubyte*,const GLfloat*){printMissingFunctionError("glColor4ubVertex3fvSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColor4ui(GLuint,GLuint,GLuint,GLuint){printMissingFunctionError("glColor4ui");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColor4uiv(const GLuint*){printMissingFunctionError("glColor4uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColor4us(GLushort,GLushort,GLushort,GLushort){printMissingFunctionError("glColor4us");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColor4usv(const GLushort*){printMissingFunctionError("glColor4usv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColor4xOES(GLfixed,GLfixed,GLfixed,GLfixed){printMissingFunctionError("glColor4xOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColor4xvOES(const GLfixed*){printMissingFunctionError("glColor4xvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColorFormatNV(GLint,GLenum,GLsizei){printMissingFunctionError("glColorFormatNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColorFragmentOp1ATI(GLenum,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint){printMissingFunctionError("glColorFragmentOp1ATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColorFragmentOp2ATI(GLenum,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint){printMissingFunctionError("glColorFragmentOp2ATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColorFragmentOp3ATI(GLenum,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint){printMissingFunctionError("glColorFragmentOp3ATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColorMask(GLboolean,GLboolean,GLboolean,GLboolean){printMissingFunctionError("glColorMask");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColorMaski(GLuint,GLboolean,GLboolean,GLboolean,GLboolean){printMissingFunctionError("glColorMaski");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColorMaskIndexedEXT(GLuint,GLboolean,GLboolean,GLboolean,GLboolean){printMissingFunctionError("glColorMaskIndexedEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColorMaterial(GLenum,GLenum){printMissingFunctionError("glColorMaterial");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColorP3ui(GLenum,GLuint){printMissingFunctionError("glColorP3ui");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColorP3uiv(GLenum,const GLuint*){printMissingFunctionError("glColorP3uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColorP4ui(GLenum,GLuint){printMissingFunctionError("glColorP4ui");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColorP4uiv(GLenum,const GLuint*){printMissingFunctionError("glColorP4uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColorPointerEXT(GLint,GLenum,GLsizei,GLsizei,const void*){printMissingFunctionError("glColorPointerEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColorPointer(GLint,GLenum,GLsizei,const GLvoid*){printMissingFunctionError("glColorPointer");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColorPointerListIBM(GLint,GLenum,GLint,const void**,GLint){printMissingFunctionError("glColorPointerListIBM");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColorPointervINTEL(GLint,GLenum,const void**){printMissingFunctionError("glColorPointervINTEL");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColorSubTableEXT(GLenum,GLsizei,GLsizei,GLenum,GLenum,const void*){printMissingFunctionError("glColorSubTableEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColorSubTable(GLenum,GLsizei,GLsizei,GLenum,GLenum,const GLvoid*){printMissingFunctionError("glColorSubTable");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColorTableEXT(GLenum,GLenum,GLsizei,GLenum,GLenum,const void*){printMissingFunctionError("glColorTableEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColorTable(GLenum,GLenum,GLsizei,GLenum,GLenum,const GLvoid*){printMissingFunctionError("glColorTable");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColorTableParameterfv(GLenum,GLenum,const GLfloat*){printMissingFunctionError("glColorTableParameterfv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColorTableParameterfvSGI(GLenum,GLenum,const GLfloat*){printMissingFunctionError("glColorTableParameterfvSGI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColorTableParameteriv(GLenum,GLenum,const GLint*){printMissingFunctionError("glColorTableParameteriv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColorTableParameterivSGI(GLenum,GLenum,const GLint*){printMissingFunctionError("glColorTableParameterivSGI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglColorTableSGI(GLenum,GLenum,GLsizei,GLenum,GLenum,const void*){printMissingFunctionError("glColorTableSGI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCombinerInputNV(GLenum,GLenum,GLenum,GLenum,GLenum,GLenum){printMissingFunctionError("glCombinerInputNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCombinerOutputNV(GLenum,GLenum,GLenum,GLenum,GLenum,GLenum,GLenum,GLboolean,GLboolean,GLboolean){printMissingFunctionError("glCombinerOutputNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCombinerParameterfNV(GLenum,GLfloat){printMissingFunctionError("glCombinerParameterfNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCombinerParameterfvNV(GLenum,const GLfloat*){printMissingFunctionError("glCombinerParameterfvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCombinerParameteriNV(GLenum,GLint){printMissingFunctionError("glCombinerParameteriNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCombinerParameterivNV(GLenum,const GLint*){printMissingFunctionError("glCombinerParameterivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCombinerStageParameterfvNV(GLenum,GLenum,const GLfloat*){printMissingFunctionError("glCombinerStageParameterfvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCommandListSegmentsNV(GLuint,GLuint){printMissingFunctionError("glCommandListSegmentsNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCompileCommandListNV(GLuint){printMissingFunctionError("glCompileCommandListNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCompileShaderARB(GLhandleARB){printMissingFunctionError("glCompileShaderARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCompileShader(GLuint){printMissingFunctionError("glCompileShader");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCompileShaderIncludeARB(GLuint,GLsizei,const GLchar*const*,const GLint*){printMissingFunctionError("glCompileShaderIncludeARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCompressedMultiTexImage1DEXT(GLenum,GLenum,GLint,GLenum,GLsizei,GLint,GLsizei,const void*){printMissingFunctionError("glCompressedMultiTexImage1DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCompressedMultiTexImage2DEXT(GLenum,GLenum,GLint,GLenum,GLsizei,GLsizei,GLint,GLsizei,const void*){printMissingFunctionError("glCompressedMultiTexImage2DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCompressedMultiTexImage3DEXT(GLenum,GLenum,GLint,GLenum,GLsizei,GLsizei,GLsizei,GLint,GLsizei,const void*){printMissingFunctionError("glCompressedMultiTexImage3DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCompressedMultiTexSubImage1DEXT(GLenum,GLenum,GLint,GLint,GLsizei,GLenum,GLsizei,const void*){printMissingFunctionError("glCompressedMultiTexSubImage1DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCompressedMultiTexSubImage2DEXT(GLenum,GLenum,GLint,GLint,GLint,GLsizei,GLsizei,GLenum,GLsizei,const void*){printMissingFunctionError("glCompressedMultiTexSubImage2DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCompressedMultiTexSubImage3DEXT(GLenum,GLenum,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLenum,GLsizei,const void*){printMissingFunctionError("glCompressedMultiTexSubImage3DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCompressedTexImage1DARB(GLenum,GLint,GLenum,GLsizei,GLint,GLsizei,const void*){printMissingFunctionError("glCompressedTexImage1DARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCompressedTexImage1D(GLenum,GLint,GLenum,GLsizei,GLint,GLsizei,const GLvoid*){printMissingFunctionError("glCompressedTexImage1D");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCompressedTexImage2DARB(GLenum,GLint,GLenum,GLsizei,GLsizei,GLint,GLsizei,const void*){printMissingFunctionError("glCompressedTexImage2DARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCompressedTexImage2D(GLenum,GLint,GLenum,GLsizei,GLsizei,GLint,GLsizei,const GLvoid*){printMissingFunctionError("glCompressedTexImage2D");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCompressedTexImage3DARB(GLenum,GLint,GLenum,GLsizei,GLsizei,GLsizei,GLint,GLsizei,const void*){printMissingFunctionError("glCompressedTexImage3DARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCompressedTexImage3D(GLenum,GLint,GLenum,GLsizei,GLsizei,GLsizei,GLint,GLsizei,const GLvoid*){printMissingFunctionError("glCompressedTexImage3D");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCompressedTexSubImage1DARB(GLenum,GLint,GLint,GLsizei,GLenum,GLsizei,const void*){printMissingFunctionError("glCompressedTexSubImage1DARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCompressedTexSubImage1D(GLenum,GLint,GLint,GLsizei,GLenum,GLsizei,const GLvoid*){printMissingFunctionError("glCompressedTexSubImage1D");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCompressedTexSubImage2DARB(GLenum,GLint,GLint,GLint,GLsizei,GLsizei,GLenum,GLsizei,const void*){printMissingFunctionError("glCompressedTexSubImage2DARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCompressedTexSubImage2D(GLenum,GLint,GLint,GLint,GLsizei,GLsizei,GLenum,GLsizei,const GLvoid*){printMissingFunctionError("glCompressedTexSubImage2D");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCompressedTexSubImage3DARB(GLenum,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLenum,GLsizei,const void*){printMissingFunctionError("glCompressedTexSubImage3DARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCompressedTexSubImage3D(GLenum,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLenum,GLsizei,const GLvoid*){printMissingFunctionError("glCompressedTexSubImage3D");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCompressedTextureImage1DEXT(GLuint,GLenum,GLint,GLenum,GLsizei,GLint,GLsizei,const void*){printMissingFunctionError("glCompressedTextureImage1DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCompressedTextureImage2DEXT(GLuint,GLenum,GLint,GLenum,GLsizei,GLsizei,GLint,GLsizei,const void*){printMissingFunctionError("glCompressedTextureImage2DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCompressedTextureImage3DEXT(GLuint,GLenum,GLint,GLenum,GLsizei,GLsizei,GLsizei,GLint,GLsizei,const void*){printMissingFunctionError("glCompressedTextureImage3DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCompressedTextureSubImage1DEXT(GLuint,GLenum,GLint,GLint,GLsizei,GLenum,GLsizei,const void*){printMissingFunctionError("glCompressedTextureSubImage1DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCompressedTextureSubImage1D(GLuint,GLint,GLint,GLsizei,GLenum,GLsizei,const void*){printMissingFunctionError("glCompressedTextureSubImage1D");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCompressedTextureSubImage2DEXT(GLuint,GLenum,GLint,GLint,GLint,GLsizei,GLsizei,GLenum,GLsizei,const void*){printMissingFunctionError("glCompressedTextureSubImage2DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCompressedTextureSubImage2D(GLuint,GLint,GLint,GLint,GLsizei,GLsizei,GLenum,GLsizei,const void*){printMissingFunctionError("glCompressedTextureSubImage2D");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCompressedTextureSubImage3DEXT(GLuint,GLenum,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLenum,GLsizei,const void*){printMissingFunctionError("glCompressedTextureSubImage3DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCompressedTextureSubImage3D(GLuint,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLenum,GLsizei,const void*){printMissingFunctionError("glCompressedTextureSubImage3D");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglConservativeRasterParameterfNV(GLenum,GLfloat){printMissingFunctionError("glConservativeRasterParameterfNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglConvolutionFilter1DEXT(GLenum,GLenum,GLsizei,GLenum,GLenum,const void*){printMissingFunctionError("glConvolutionFilter1DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglConvolutionFilter1D(GLenum,GLenum,GLsizei,GLenum,GLenum,const GLvoid*){printMissingFunctionError("glConvolutionFilter1D");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglConvolutionFilter2DEXT(GLenum,GLenum,GLsizei,GLsizei,GLenum,GLenum,const void*){printMissingFunctionError("glConvolutionFilter2DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglConvolutionFilter2D(GLenum,GLenum,GLsizei,GLsizei,GLenum,GLenum,const GLvoid*){printMissingFunctionError("glConvolutionFilter2D");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglConvolutionParameterfEXT(GLenum,GLenum,GLfloat){printMissingFunctionError("glConvolutionParameterfEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglConvolutionParameterf(GLenum,GLenum,GLfloat){printMissingFunctionError("glConvolutionParameterf");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglConvolutionParameterfvEXT(GLenum,GLenum,const GLfloat*){printMissingFunctionError("glConvolutionParameterfvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglConvolutionParameterfv(GLenum,GLenum,const GLfloat*){printMissingFunctionError("glConvolutionParameterfv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglConvolutionParameteriEXT(GLenum,GLenum,GLint){printMissingFunctionError("glConvolutionParameteriEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglConvolutionParameteri(GLenum,GLenum,GLint){printMissingFunctionError("glConvolutionParameteri");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglConvolutionParameterivEXT(GLenum,GLenum,const GLint*){printMissingFunctionError("glConvolutionParameterivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglConvolutionParameteriv(GLenum,GLenum,const GLint*){printMissingFunctionError("glConvolutionParameteriv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglConvolutionParameterxOES(GLenum,GLenum,GLfixed){printMissingFunctionError("glConvolutionParameterxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglConvolutionParameterxvOES(GLenum,GLenum,const GLfixed*){printMissingFunctionError("glConvolutionParameterxvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCopyBufferSubData(GLenum,GLenum,GLintptr,GLintptr,GLsizeiptr){printMissingFunctionError("glCopyBufferSubData");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCopyColorSubTableEXT(GLenum,GLsizei,GLint,GLint,GLsizei){printMissingFunctionError("glCopyColorSubTableEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCopyColorSubTable(GLenum,GLsizei,GLint,GLint,GLsizei){printMissingFunctionError("glCopyColorSubTable");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCopyColorTable(GLenum,GLenum,GLint,GLint,GLsizei){printMissingFunctionError("glCopyColorTable");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCopyColorTableSGI(GLenum,GLenum,GLint,GLint,GLsizei){printMissingFunctionError("glCopyColorTableSGI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCopyConvolutionFilter1DEXT(GLenum,GLenum,GLint,GLint,GLsizei){printMissingFunctionError("glCopyConvolutionFilter1DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCopyConvolutionFilter1D(GLenum,GLenum,GLint,GLint,GLsizei){printMissingFunctionError("glCopyConvolutionFilter1D");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCopyConvolutionFilter2DEXT(GLenum,GLenum,GLint,GLint,GLsizei,GLsizei){printMissingFunctionError("glCopyConvolutionFilter2DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCopyConvolutionFilter2D(GLenum,GLenum,GLint,GLint,GLsizei,GLsizei){printMissingFunctionError("glCopyConvolutionFilter2D");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCopyImageSubData(GLuint,GLenum,GLint,GLint,GLint,GLint,GLuint,GLenum,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei){printMissingFunctionError("glCopyImageSubData");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCopyImageSubDataNV(GLuint,GLenum,GLint,GLint,GLint,GLint,GLuint,GLenum,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei){printMissingFunctionError("glCopyImageSubDataNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCopyMultiTexImage1DEXT(GLenum,GLenum,GLint,GLenum,GLint,GLint,GLsizei,GLint){printMissingFunctionError("glCopyMultiTexImage1DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCopyMultiTexImage2DEXT(GLenum,GLenum,GLint,GLenum,GLint,GLint,GLsizei,GLsizei,GLint){printMissingFunctionError("glCopyMultiTexImage2DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCopyMultiTexSubImage1DEXT(GLenum,GLenum,GLint,GLint,GLint,GLint,GLsizei){printMissingFunctionError("glCopyMultiTexSubImage1DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCopyMultiTexSubImage2DEXT(GLenum,GLenum,GLint,GLint,GLint,GLint,GLint,GLsizei,GLsizei){printMissingFunctionError("glCopyMultiTexSubImage2DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCopyMultiTexSubImage3DEXT(GLenum,GLenum,GLint,GLint,GLint,GLint,GLint,GLint,GLsizei,GLsizei){printMissingFunctionError("glCopyMultiTexSubImage3DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCopyNamedBufferSubData(GLuint,GLuint,GLintptr,GLintptr,GLsizeiptr){printMissingFunctionError("glCopyNamedBufferSubData");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCopyPathNV(GLuint,GLuint){printMissingFunctionError("glCopyPathNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCopyPixels(GLint,GLint,GLsizei,GLsizei,GLenum){printMissingFunctionError("glCopyPixels");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCopyTexImage1DEXT(GLenum,GLint,GLenum,GLint,GLint,GLsizei,GLint){printMissingFunctionError("glCopyTexImage1DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCopyTexImage1D(GLenum,GLint,GLenum,GLint,GLint,GLsizei,GLint){printMissingFunctionError("glCopyTexImage1D");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCopyTexImage2DEXT(GLenum,GLint,GLenum,GLint,GLint,GLsizei,GLsizei,GLint){printMissingFunctionError("glCopyTexImage2DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCopyTexImage2D(GLenum,GLint,GLenum,GLint,GLint,GLsizei,GLsizei,GLint){printMissingFunctionError("glCopyTexImage2D");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCopyTexSubImage1DEXT(GLenum,GLint,GLint,GLint,GLint,GLsizei){printMissingFunctionError("glCopyTexSubImage1DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCopyTexSubImage1D(GLenum,GLint,GLint,GLint,GLint,GLsizei){printMissingFunctionError("glCopyTexSubImage1D");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCopyTexSubImage2DEXT(GLenum,GLint,GLint,GLint,GLint,GLint,GLsizei,GLsizei){printMissingFunctionError("glCopyTexSubImage2DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCopyTexSubImage2D(GLenum,GLint,GLint,GLint,GLint,GLint,GLsizei,GLsizei){printMissingFunctionError("glCopyTexSubImage2D");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCopyTexSubImage3DEXT(GLenum,GLint,GLint,GLint,GLint,GLint,GLint,GLsizei,GLsizei){printMissingFunctionError("glCopyTexSubImage3DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCopyTexSubImage3D(GLenum,GLint,GLint,GLint,GLint,GLint,GLint,GLsizei,GLsizei){printMissingFunctionError("glCopyTexSubImage3D");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCopyTextureImage1DEXT(GLuint,GLenum,GLint,GLenum,GLint,GLint,GLsizei,GLint){printMissingFunctionError("glCopyTextureImage1DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCopyTextureImage2DEXT(GLuint,GLenum,GLint,GLenum,GLint,GLint,GLsizei,GLsizei,GLint){printMissingFunctionError("glCopyTextureImage2DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCopyTextureSubImage1DEXT(GLuint,GLenum,GLint,GLint,GLint,GLint,GLsizei){printMissingFunctionError("glCopyTextureSubImage1DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCopyTextureSubImage1D(GLuint,GLint,GLint,GLint,GLint,GLsizei){printMissingFunctionError("glCopyTextureSubImage1D");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCopyTextureSubImage2DEXT(GLuint,GLenum,GLint,GLint,GLint,GLint,GLint,GLsizei,GLsizei){printMissingFunctionError("glCopyTextureSubImage2DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCopyTextureSubImage2D(GLuint,GLint,GLint,GLint,GLint,GLint,GLsizei,GLsizei){printMissingFunctionError("glCopyTextureSubImage2D");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCopyTextureSubImage3DEXT(GLuint,GLenum,GLint,GLint,GLint,GLint,GLint,GLint,GLsizei,GLsizei){printMissingFunctionError("glCopyTextureSubImage3DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCopyTextureSubImage3D(GLuint,GLint,GLint,GLint,GLint,GLint,GLint,GLsizei,GLsizei){printMissingFunctionError("glCopyTextureSubImage3D");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCoverageModulationNV(GLenum){printMissingFunctionError("glCoverageModulationNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCoverageModulationTableNV(GLsizei,const GLfloat*){printMissingFunctionError("glCoverageModulationTableNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCoverFillPathInstancedNV(GLsizei,GLenum,const void*,GLuint,GLenum,GLenum,const GLfloat*){printMissingFunctionError("glCoverFillPathInstancedNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCoverFillPathNV(GLuint,GLenum){printMissingFunctionError("glCoverFillPathNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCoverStrokePathInstancedNV(GLsizei,GLenum,const void*,GLuint,GLenum,GLenum,const GLfloat*){printMissingFunctionError("glCoverStrokePathInstancedNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCoverStrokePathNV(GLuint,GLenum){printMissingFunctionError("glCoverStrokePathNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCreateBuffers(GLsizei,GLuint*){printMissingFunctionError("glCreateBuffers");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCreateCommandListsNV(GLsizei,GLuint*){printMissingFunctionError("glCreateCommandListsNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCreateFramebuffers(GLsizei,GLuint*){printMissingFunctionError("glCreateFramebuffers");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCreatePerfQueryINTEL(GLuint,GLuint*){printMissingFunctionError("glCreatePerfQueryINTEL");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCreateProgramPipelines(GLsizei,GLuint*){printMissingFunctionError("glCreateProgramPipelines");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCreateQueries(GLenum,GLsizei,GLuint*){printMissingFunctionError("glCreateQueries");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCreateRenderbuffers(GLsizei,GLuint*){printMissingFunctionError("glCreateRenderbuffers");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCreateSamplers(GLsizei,GLuint*){printMissingFunctionError("glCreateSamplers");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCreateStatesNV(GLsizei,GLuint*){printMissingFunctionError("glCreateStatesNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCreateTextures(GLenum,GLsizei,GLuint*){printMissingFunctionError("glCreateTextures");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCreateTransformFeedbacks(GLsizei,GLuint*){printMissingFunctionError("glCreateTransformFeedbacks");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCreateVertexArrays(GLsizei,GLuint*){printMissingFunctionError("glCreateVertexArrays");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCullFace(GLenum){printMissingFunctionError("glCullFace");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCullParameterdvEXT(GLenum,GLdouble*){printMissingFunctionError("glCullParameterdvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCullParameterfvEXT(GLenum,GLfloat*){printMissingFunctionError("glCullParameterfvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglCurrentPaletteMatrixARB(GLint){printMissingFunctionError("glCurrentPaletteMatrixARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDebugMessageCallbackAMD(GLDEBUGPROCAMD,void*){printMissingFunctionError("glDebugMessageCallbackAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDebugMessageCallbackARB(GLDEBUGPROCARB,const void*){printMissingFunctionError("glDebugMessageCallbackARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDebugMessageCallback(GLDEBUGPROC,const void*){printMissingFunctionError("glDebugMessageCallback");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDebugMessageControlARB(GLenum,GLenum,GLenum,GLsizei,const GLuint*,GLboolean){printMissingFunctionError("glDebugMessageControlARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDebugMessageControl(GLenum,GLenum,GLenum,GLsizei,const GLuint*,GLboolean){printMissingFunctionError("glDebugMessageControl");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDebugMessageEnableAMD(GLenum,GLenum,GLsizei,const GLuint*,GLboolean){printMissingFunctionError("glDebugMessageEnableAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDebugMessageInsertAMD(GLenum,GLenum,GLuint,GLsizei,const GLchar*){printMissingFunctionError("glDebugMessageInsertAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDebugMessageInsertARB(GLenum,GLenum,GLuint,GLenum,GLsizei,const GLchar*){printMissingFunctionError("glDebugMessageInsertARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDebugMessageInsert(GLenum,GLenum,GLuint,GLenum,GLsizei,const GLchar*){printMissingFunctionError("glDebugMessageInsert");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDeformationMap3dSGIX(GLenum,GLdouble,GLdouble,GLint,GLint,GLdouble,GLdouble,GLint,GLint,GLdouble,GLdouble,GLint,GLint,const GLdouble*){printMissingFunctionError("glDeformationMap3dSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDeformationMap3fSGIX(GLenum,GLfloat,GLfloat,GLint,GLint,GLfloat,GLfloat,GLint,GLint,GLfloat,GLfloat,GLint,GLint,const GLfloat*){printMissingFunctionError("glDeformationMap3fSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDeformSGIX(GLbitfield){printMissingFunctionError("glDeformSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDeleteAsyncMarkersSGIX(GLuint,GLsizei){printMissingFunctionError("glDeleteAsyncMarkersSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDeleteBuffersARB(GLsizei,const GLuint*){printMissingFunctionError("glDeleteBuffersARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDeleteBuffers(GLsizei,const GLuint*){printMissingFunctionError("glDeleteBuffers");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDeleteCommandListsNV(GLsizei,const GLuint*){printMissingFunctionError("glDeleteCommandListsNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDeleteFencesAPPLE(GLsizei,const GLuint*){printMissingFunctionError("glDeleteFencesAPPLE");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDeleteFencesNV(GLsizei,const GLuint*){printMissingFunctionError("glDeleteFencesNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDeleteFragmentShaderATI(GLuint){printMissingFunctionError("glDeleteFragmentShaderATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDeleteFramebuffersEXT(GLsizei,const GLuint*){printMissingFunctionError("glDeleteFramebuffersEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDeleteFramebuffers(GLsizei,const GLuint*){printMissingFunctionError("glDeleteFramebuffers");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDeleteLists(GLuint,GLsizei){printMissingFunctionError("glDeleteLists");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDeleteNamedStringARB(GLint,const GLchar*){printMissingFunctionError("glDeleteNamedStringARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDeleteNamesAMD(GLenum,GLuint,const GLuint*){printMissingFunctionError("glDeleteNamesAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDeleteObjectARB(GLhandleARB){printMissingFunctionError("glDeleteObjectARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDeleteOcclusionQueriesNV(GLsizei,const GLuint*){printMissingFunctionError("glDeleteOcclusionQueriesNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDeletePathsNV(GLuint,GLsizei){printMissingFunctionError("glDeletePathsNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDeletePerfMonitorsAMD(GLsizei,GLuint*){printMissingFunctionError("glDeletePerfMonitorsAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDeletePerfQueryINTEL(GLuint){printMissingFunctionError("glDeletePerfQueryINTEL");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDeleteProgram(GLuint){printMissingFunctionError("glDeleteProgram");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDeleteProgramPipelines(GLsizei,const GLuint*){printMissingFunctionError("glDeleteProgramPipelines");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDeleteProgramsARB(GLsizei,const GLuint*){printMissingFunctionError("glDeleteProgramsARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDeleteProgramsNV(GLsizei,const GLuint*){printMissingFunctionError("glDeleteProgramsNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDeleteQueriesARB(GLsizei,const GLuint*){printMissingFunctionError("glDeleteQueriesARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDeleteQueries(GLsizei,const GLuint*){printMissingFunctionError("glDeleteQueries");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDeleteRenderbuffersEXT(GLsizei,const GLuint*){printMissingFunctionError("glDeleteRenderbuffersEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDeleteRenderbuffers(GLsizei,const GLuint*){printMissingFunctionError("glDeleteRenderbuffers");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDeleteSamplers(GLsizei,const GLuint*){printMissingFunctionError("glDeleteSamplers");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDeleteShader(GLuint){printMissingFunctionError("glDeleteShader");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDeleteStatesNV(GLsizei,const GLuint*){printMissingFunctionError("glDeleteStatesNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDeleteSync(GLsync){printMissingFunctionError("glDeleteSync");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDeleteTexturesEXT(GLsizei,const GLuint*){printMissingFunctionError("glDeleteTexturesEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDeleteTextures(GLsizei,const GLuint*){printMissingFunctionError("glDeleteTextures");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDeleteTransformFeedbacks(GLsizei,const GLuint*){printMissingFunctionError("glDeleteTransformFeedbacks");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDeleteTransformFeedbacksNV(GLsizei,const GLuint*){printMissingFunctionError("glDeleteTransformFeedbacksNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDeleteVertexArraysAPPLE(GLsizei,const GLuint*){printMissingFunctionError("glDeleteVertexArraysAPPLE");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDeleteVertexArrays(GLsizei,const GLuint*){printMissingFunctionError("glDeleteVertexArrays");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDeleteVertexShaderEXT(GLuint){printMissingFunctionError("glDeleteVertexShaderEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDepthBoundsdNV(GLdouble,GLdouble){printMissingFunctionError("glDepthBoundsdNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDepthBoundsEXT(GLclampd,GLclampd){printMissingFunctionError("glDepthBoundsEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDepthFunc(GLenum){printMissingFunctionError("glDepthFunc");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDepthMask(GLboolean){printMissingFunctionError("glDepthMask");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDepthRangeArrayv(GLuint,GLsizei,const GLdouble*){printMissingFunctionError("glDepthRangeArrayv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDepthRangedNV(GLdouble,GLdouble){printMissingFunctionError("glDepthRangedNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDepthRangef(GLfloat,GLfloat){printMissingFunctionError("glDepthRangef");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDepthRangefOES(GLclampf,GLclampf){printMissingFunctionError("glDepthRangefOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDepthRange(GLclampd,GLclampd){printMissingFunctionError("glDepthRange");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDepthRangeIndexed(GLuint,GLdouble,GLdouble){printMissingFunctionError("glDepthRangeIndexed");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDepthRangexOES(GLfixed,GLfixed){printMissingFunctionError("glDepthRangexOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDetachObjectARB(GLhandleARB,GLhandleARB){printMissingFunctionError("glDetachObjectARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDetachShader(GLuint,GLuint){printMissingFunctionError("glDetachShader");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDetailTexFuncSGIS(GLenum,GLsizei,const GLfloat*){printMissingFunctionError("glDetailTexFuncSGIS");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDisableClientState(GLenum){printMissingFunctionError("glDisableClientState");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDisableClientStateiEXT(GLenum,GLuint){printMissingFunctionError("glDisableClientStateiEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDisableClientStateIndexedEXT(GLenum,GLuint){printMissingFunctionError("glDisableClientStateIndexedEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDisable(GLenum){printMissingFunctionError("glDisable");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDisablei(GLenum,GLuint){printMissingFunctionError("glDisablei");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDisableIndexedEXT(GLenum,GLuint){printMissingFunctionError("glDisableIndexedEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDisableVariantClientStateEXT(GLuint){printMissingFunctionError("glDisableVariantClientStateEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDisableVertexArrayAttribEXT(GLuint,GLuint){printMissingFunctionError("glDisableVertexArrayAttribEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDisableVertexArrayAttrib(GLuint,GLuint){printMissingFunctionError("glDisableVertexArrayAttrib");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDisableVertexArrayEXT(GLuint,GLenum){printMissingFunctionError("glDisableVertexArrayEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDisableVertexAttribAPPLE(GLuint,GLenum){printMissingFunctionError("glDisableVertexAttribAPPLE");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDisableVertexAttribArrayARB(GLuint){printMissingFunctionError("glDisableVertexAttribArrayARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDisableVertexAttribArray(GLuint){printMissingFunctionError("glDisableVertexAttribArray");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDispatchCompute(GLuint,GLuint,GLuint){printMissingFunctionError("glDispatchCompute");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDispatchComputeGroupSizeARB(GLuint,GLuint,GLuint,GLuint,GLuint,GLuint){printMissingFunctionError("glDispatchComputeGroupSizeARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDispatchComputeIndirect(GLintptr){printMissingFunctionError("glDispatchComputeIndirect");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDrawArraysEXT(GLenum,GLint,GLsizei){printMissingFunctionError("glDrawArraysEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDrawArrays(GLenum,GLint,GLsizei){printMissingFunctionError("glDrawArrays");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDrawArraysIndirect(GLenum,const void*){printMissingFunctionError("glDrawArraysIndirect");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDrawArraysInstancedARB(GLenum,GLint,GLsizei,GLsizei){printMissingFunctionError("glDrawArraysInstancedARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDrawArraysInstancedBaseInstance(GLenum,GLint,GLsizei,GLsizei,GLuint){printMissingFunctionError("glDrawArraysInstancedBaseInstance");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDrawArraysInstancedEXT(GLenum,GLint,GLsizei,GLsizei){printMissingFunctionError("glDrawArraysInstancedEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDrawArraysInstanced(GLenum,GLint,GLsizei,GLsizei){printMissingFunctionError("glDrawArraysInstanced");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDrawBuffer(GLenum){printMissingFunctionError("glDrawBuffer");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDrawBuffersARB(GLsizei,const GLenum*){printMissingFunctionError("glDrawBuffersARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDrawBuffersATI(GLsizei,const GLenum*){printMissingFunctionError("glDrawBuffersATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDrawBuffers(GLsizei,const GLenum*){printMissingFunctionError("glDrawBuffers");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDrawCommandsAddressNV(GLenum,const GLuint64*,const GLsizei*,GLuint){printMissingFunctionError("glDrawCommandsAddressNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDrawCommandsNV(GLenum,GLuint,const GLintptr*,const GLsizei*,GLuint){printMissingFunctionError("glDrawCommandsNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDrawCommandsStatesAddressNV(const GLuint64*,const GLsizei*,const GLuint*,const GLuint*,GLuint){printMissingFunctionError("glDrawCommandsStatesAddressNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDrawCommandsStatesNV(GLuint,const GLintptr*,const GLsizei*,const GLuint*,const GLuint*,GLuint){printMissingFunctionError("glDrawCommandsStatesNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDrawElementArrayAPPLE(GLenum,GLint,GLsizei){printMissingFunctionError("glDrawElementArrayAPPLE");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDrawElementArrayATI(GLenum,GLsizei){printMissingFunctionError("glDrawElementArrayATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDrawElementsBaseVertex(GLenum,GLsizei,GLenum,const void*,GLint){printMissingFunctionError("glDrawElementsBaseVertex");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDrawElements(GLenum,GLsizei,GLenum,const GLvoid*){printMissingFunctionError("glDrawElements");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDrawElementsIndirect(GLenum,GLenum,const void*){printMissingFunctionError("glDrawElementsIndirect");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDrawElementsInstancedARB(GLenum,GLsizei,GLenum,const void*,GLsizei){printMissingFunctionError("glDrawElementsInstancedARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDrawElementsInstancedBaseInstance(GLenum,GLsizei,GLenum,const void*,GLsizei,GLuint){printMissingFunctionError("glDrawElementsInstancedBaseInstance");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDrawElementsInstancedBaseVertexBaseInstance(GLenum,GLsizei,GLenum,const void*,GLsizei,GLint,GLuint){printMissingFunctionError("glDrawElementsInstancedBaseVertexBaseInstance");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDrawElementsInstancedBaseVertex(GLenum,GLsizei,GLenum,const void*,GLsizei,GLint){printMissingFunctionError("glDrawElementsInstancedBaseVertex");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDrawElementsInstancedEXT(GLenum,GLsizei,GLenum,const void*,GLsizei){printMissingFunctionError("glDrawElementsInstancedEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDrawElementsInstanced(GLenum,GLsizei,GLenum,const void*,GLsizei){printMissingFunctionError("glDrawElementsInstanced");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDrawMeshArraysSUN(GLenum,GLint,GLsizei,GLsizei){printMissingFunctionError("glDrawMeshArraysSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDrawPixels(GLsizei,GLsizei,GLenum,GLenum,const GLvoid*){printMissingFunctionError("glDrawPixels");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDrawRangeElementArrayAPPLE(GLenum,GLuint,GLuint,GLint,GLsizei){printMissingFunctionError("glDrawRangeElementArrayAPPLE");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDrawRangeElementArrayATI(GLenum,GLuint,GLuint,GLsizei){printMissingFunctionError("glDrawRangeElementArrayATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDrawRangeElementsBaseVertex(GLenum,GLuint,GLuint,GLsizei,GLenum,const void*,GLint){printMissingFunctionError("glDrawRangeElementsBaseVertex");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDrawRangeElementsEXT(GLenum,GLuint,GLuint,GLsizei,GLenum,const void*){printMissingFunctionError("glDrawRangeElementsEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDrawRangeElements(GLenum,GLuint,GLuint,GLsizei,GLenum,const GLvoid*){printMissingFunctionError("glDrawRangeElements");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDrawTextureNV(GLuint,GLuint,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glDrawTextureNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDrawTransformFeedback(GLenum,GLuint){printMissingFunctionError("glDrawTransformFeedback");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDrawTransformFeedbackInstanced(GLenum,GLuint,GLsizei){printMissingFunctionError("glDrawTransformFeedbackInstanced");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDrawTransformFeedbackNV(GLenum,GLuint){printMissingFunctionError("glDrawTransformFeedbackNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDrawTransformFeedbackStream(GLenum,GLuint,GLuint){printMissingFunctionError("glDrawTransformFeedbackStream");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglDrawTransformFeedbackStreamInstanced(GLenum,GLuint,GLuint,GLsizei){printMissingFunctionError("glDrawTransformFeedbackStreamInstanced");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEdgeFlagFormatNV(GLsizei){printMissingFunctionError("glEdgeFlagFormatNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEdgeFlag(GLboolean){printMissingFunctionError("glEdgeFlag");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEdgeFlagPointerEXT(GLsizei,GLsizei,const GLboolean*){printMissingFunctionError("glEdgeFlagPointerEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEdgeFlagPointer(GLsizei,const GLvoid*){printMissingFunctionError("glEdgeFlagPointer");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEdgeFlagPointerListIBM(GLint,const GLboolean**,GLint){printMissingFunctionError("glEdgeFlagPointerListIBM");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEdgeFlagv(const GLboolean*){printMissingFunctionError("glEdgeFlagv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEGLImageTargetRenderbufferStorageOES(GLenum,GLeglImageOES){printMissingFunctionError("glEGLImageTargetRenderbufferStorageOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEGLImageTargetTexture2DOES(GLenum,GLeglImageOES){printMissingFunctionError("glEGLImageTargetTexture2DOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglElementPointerAPPLE(GLenum,const void*){printMissingFunctionError("glElementPointerAPPLE");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglElementPointerATI(GLenum,const void*){printMissingFunctionError("glElementPointerATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEnableClientState(GLenum){printMissingFunctionError("glEnableClientState");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEnableClientStateiEXT(GLenum,GLuint){printMissingFunctionError("glEnableClientStateiEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEnableClientStateIndexedEXT(GLenum,GLuint){printMissingFunctionError("glEnableClientStateIndexedEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEnable(GLenum){printMissingFunctionError("glEnable");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEnablei(GLenum,GLuint){printMissingFunctionError("glEnablei");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEnableIndexedEXT(GLenum,GLuint){printMissingFunctionError("glEnableIndexedEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEnableVariantClientStateEXT(GLuint){printMissingFunctionError("glEnableVariantClientStateEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEnableVertexArrayAttribEXT(GLuint,GLuint){printMissingFunctionError("glEnableVertexArrayAttribEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEnableVertexArrayAttrib(GLuint,GLuint){printMissingFunctionError("glEnableVertexArrayAttrib");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEnableVertexArrayEXT(GLuint,GLenum){printMissingFunctionError("glEnableVertexArrayEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEnableVertexAttribAPPLE(GLuint,GLenum){printMissingFunctionError("glEnableVertexAttribAPPLE");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEnableVertexAttribArrayARB(GLuint){printMissingFunctionError("glEnableVertexAttribArrayARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEnableVertexAttribArray(GLuint){printMissingFunctionError("glEnableVertexAttribArray");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEnd(){printMissingFunctionError("glEnd");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEndConditionalRender(){printMissingFunctionError("glEndConditionalRender");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEndConditionalRenderNV(){printMissingFunctionError("glEndConditionalRenderNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEndConditionalRenderNVX(){printMissingFunctionError("glEndConditionalRenderNVX");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEndFragmentShaderATI(){printMissingFunctionError("glEndFragmentShaderATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEndList(){printMissingFunctionError("glEndList");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEndOcclusionQueryNV(){printMissingFunctionError("glEndOcclusionQueryNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEndPerfMonitorAMD(GLuint){printMissingFunctionError("glEndPerfMonitorAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEndPerfQueryINTEL(GLuint){printMissingFunctionError("glEndPerfQueryINTEL");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEndQueryARB(GLenum){printMissingFunctionError("glEndQueryARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEndQuery(GLenum){printMissingFunctionError("glEndQuery");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEndQueryIndexed(GLenum,GLuint){printMissingFunctionError("glEndQueryIndexed");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEndTransformFeedback(){printMissingFunctionError("glEndTransformFeedback");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEndTransformFeedbackEXT(){printMissingFunctionError("glEndTransformFeedbackEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEndTransformFeedbackNV(){printMissingFunctionError("glEndTransformFeedbackNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEndVertexShaderEXT(){printMissingFunctionError("glEndVertexShaderEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEndVideoCaptureNV(GLuint){printMissingFunctionError("glEndVideoCaptureNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEvalCoord1d(GLdouble){printMissingFunctionError("glEvalCoord1d");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEvalCoord1dv(const GLdouble*){printMissingFunctionError("glEvalCoord1dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEvalCoord1f(GLfloat){printMissingFunctionError("glEvalCoord1f");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEvalCoord1fv(const GLfloat*){printMissingFunctionError("glEvalCoord1fv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEvalCoord1xOES(GLfixed){printMissingFunctionError("glEvalCoord1xOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEvalCoord1xvOES(const GLfixed*){printMissingFunctionError("glEvalCoord1xvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEvalCoord2d(GLdouble,GLdouble){printMissingFunctionError("glEvalCoord2d");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEvalCoord2dv(const GLdouble*){printMissingFunctionError("glEvalCoord2dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEvalCoord2f(GLfloat,GLfloat){printMissingFunctionError("glEvalCoord2f");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEvalCoord2fv(const GLfloat*){printMissingFunctionError("glEvalCoord2fv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEvalCoord2xOES(GLfixed,GLfixed){printMissingFunctionError("glEvalCoord2xOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEvalCoord2xvOES(const GLfixed*){printMissingFunctionError("glEvalCoord2xvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEvalMapsNV(GLenum,GLenum){printMissingFunctionError("glEvalMapsNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEvalMesh1(GLenum,GLint,GLint){printMissingFunctionError("glEvalMesh1");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEvalMesh2(GLenum,GLint,GLint,GLint,GLint){printMissingFunctionError("glEvalMesh2");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEvalPoint1(GLint){printMissingFunctionError("glEvalPoint1");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEvalPoint2(GLint,GLint){printMissingFunctionError("glEvalPoint2");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglEvaluateDepthValuesARB(){printMissingFunctionError("glEvaluateDepthValuesARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglExecuteProgramNV(GLenum,GLuint,const GLfloat*){printMissingFunctionError("glExecuteProgramNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglExtractComponentEXT(GLuint,GLuint,GLuint){printMissingFunctionError("glExtractComponentEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFeedbackBuffer(GLsizei,GLenum,GLfloat*){printMissingFunctionError("glFeedbackBuffer");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFeedbackBufferxOES(GLsizei,GLenum,const GLfixed*){printMissingFunctionError("glFeedbackBufferxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFinalCombinerInputNV(GLenum,GLenum,GLenum,GLenum){printMissingFunctionError("glFinalCombinerInputNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFinish(){printMissingFunctionError("glFinish");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFinishFenceAPPLE(GLuint){printMissingFunctionError("glFinishFenceAPPLE");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFinishFenceNV(GLuint){printMissingFunctionError("glFinishFenceNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFinishObjectAPPLE(GLenum,GLint){printMissingFunctionError("glFinishObjectAPPLE");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFinishTextureSUNX(){printMissingFunctionError("glFinishTextureSUNX");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFlush(){printMissingFunctionError("glFlush");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFlushMappedBufferRangeAPPLE(GLenum,GLintptr,GLsizeiptr){printMissingFunctionError("glFlushMappedBufferRangeAPPLE");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFlushMappedBufferRange(GLenum,GLintptr,GLsizeiptr){printMissingFunctionError("glFlushMappedBufferRange");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFlushMappedNamedBufferRangeEXT(GLuint,GLintptr,GLsizeiptr){printMissingFunctionError("glFlushMappedNamedBufferRangeEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFlushMappedNamedBufferRange(GLuint,GLintptr,GLsizeiptr){printMissingFunctionError("glFlushMappedNamedBufferRange");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFlushPixelDataRangeNV(GLenum){printMissingFunctionError("glFlushPixelDataRangeNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFlushRasterSGIX(){printMissingFunctionError("glFlushRasterSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFlushStaticDataIBM(GLenum){printMissingFunctionError("glFlushStaticDataIBM");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFlushVertexArrayRangeAPPLE(GLsizei,void*){printMissingFunctionError("glFlushVertexArrayRangeAPPLE");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFlushVertexArrayRangeNV(){printMissingFunctionError("glFlushVertexArrayRangeNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFogCoorddEXT(GLdouble){printMissingFunctionError("glFogCoorddEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFogCoordd(GLdouble){printMissingFunctionError("glFogCoordd");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFogCoorddv(const GLdouble*){printMissingFunctionError("glFogCoorddv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFogCoorddvEXT(const GLdouble*){printMissingFunctionError("glFogCoorddvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFogCoordfEXT(GLfloat){printMissingFunctionError("glFogCoordfEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFogCoordf(GLfloat){printMissingFunctionError("glFogCoordf");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFogCoordFormatNV(GLenum,GLsizei){printMissingFunctionError("glFogCoordFormatNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFogCoordfv(const GLfloat*){printMissingFunctionError("glFogCoordfv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFogCoordfvEXT(const GLfloat*){printMissingFunctionError("glFogCoordfvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFogCoordhNV(GLhalfNV){printMissingFunctionError("glFogCoordhNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFogCoordhvNV(const GLhalfNV*){printMissingFunctionError("glFogCoordhvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFogCoordPointerEXT(GLenum,GLsizei,const void*){printMissingFunctionError("glFogCoordPointerEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFogCoordPointer(GLenum,GLsizei,const void*){printMissingFunctionError("glFogCoordPointer");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFogCoordPointerListIBM(GLenum,GLint,const void**,GLint){printMissingFunctionError("glFogCoordPointerListIBM");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFogf(GLenum,GLfloat){printMissingFunctionError("glFogf");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFogFuncSGIS(GLsizei,const GLfloat*){printMissingFunctionError("glFogFuncSGIS");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFogfv(GLenum,const GLfloat*){printMissingFunctionError("glFogfv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFogi(GLenum,GLint){printMissingFunctionError("glFogi");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFogiv(GLenum,const GLint*){printMissingFunctionError("glFogiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFogxOES(GLenum,GLfixed){printMissingFunctionError("glFogxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFogxvOES(GLenum,const GLfixed*){printMissingFunctionError("glFogxvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFragmentColorMaterialSGIX(GLenum,GLenum){printMissingFunctionError("glFragmentColorMaterialSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFragmentCoverageColorNV(GLuint){printMissingFunctionError("glFragmentCoverageColorNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFragmentLightfSGIX(GLenum,GLenum,GLfloat){printMissingFunctionError("glFragmentLightfSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFragmentLightfvSGIX(GLenum,GLenum,const GLfloat*){printMissingFunctionError("glFragmentLightfvSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFragmentLightiSGIX(GLenum,GLenum,GLint){printMissingFunctionError("glFragmentLightiSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFragmentLightivSGIX(GLenum,GLenum,const GLint*){printMissingFunctionError("glFragmentLightivSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFragmentLightModelfSGIX(GLenum,GLfloat){printMissingFunctionError("glFragmentLightModelfSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFragmentLightModelfvSGIX(GLenum,const GLfloat*){printMissingFunctionError("glFragmentLightModelfvSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFragmentLightModeliSGIX(GLenum,GLint){printMissingFunctionError("glFragmentLightModeliSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFragmentLightModelivSGIX(GLenum,const GLint*){printMissingFunctionError("glFragmentLightModelivSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFragmentMaterialfSGIX(GLenum,GLenum,GLfloat){printMissingFunctionError("glFragmentMaterialfSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFragmentMaterialfvSGIX(GLenum,GLenum,const GLfloat*){printMissingFunctionError("glFragmentMaterialfvSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFragmentMaterialiSGIX(GLenum,GLenum,GLint){printMissingFunctionError("glFragmentMaterialiSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFragmentMaterialivSGIX(GLenum,GLenum,const GLint*){printMissingFunctionError("glFragmentMaterialivSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFramebufferDrawBufferEXT(GLuint,GLenum){printMissingFunctionError("glFramebufferDrawBufferEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFramebufferDrawBuffersEXT(GLuint,GLsizei,const GLenum*){printMissingFunctionError("glFramebufferDrawBuffersEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFramebufferParameteri(GLenum,GLenum,GLint){printMissingFunctionError("glFramebufferParameteri");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFramebufferReadBufferEXT(GLuint,GLenum){printMissingFunctionError("glFramebufferReadBufferEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFramebufferRenderbufferEXT(GLenum,GLenum,GLenum,GLuint){printMissingFunctionError("glFramebufferRenderbufferEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFramebufferRenderbuffer(GLenum,GLenum,GLenum,GLuint){printMissingFunctionError("glFramebufferRenderbuffer");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFramebufferSampleLocationsfvARB(GLenum,GLuint,GLsizei,const GLfloat*){printMissingFunctionError("glFramebufferSampleLocationsfvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFramebufferSampleLocationsfvNV(GLenum,GLuint,GLsizei,const GLfloat*){printMissingFunctionError("glFramebufferSampleLocationsfvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFramebufferTexture1DEXT(GLenum,GLenum,GLenum,GLuint,GLint){printMissingFunctionError("glFramebufferTexture1DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFramebufferTexture1D(GLenum,GLenum,GLenum,GLuint,GLint){printMissingFunctionError("glFramebufferTexture1D");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFramebufferTexture2DEXT(GLenum,GLenum,GLenum,GLuint,GLint){printMissingFunctionError("glFramebufferTexture2DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFramebufferTexture2D(GLenum,GLenum,GLenum,GLuint,GLint){printMissingFunctionError("glFramebufferTexture2D");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFramebufferTexture3DEXT(GLenum,GLenum,GLenum,GLuint,GLint,GLint){printMissingFunctionError("glFramebufferTexture3DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFramebufferTexture3D(GLenum,GLenum,GLenum,GLuint,GLint,GLint){printMissingFunctionError("glFramebufferTexture3D");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFramebufferTextureARB(GLenum,GLenum,GLuint,GLint){printMissingFunctionError("glFramebufferTextureARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFramebufferTextureEXT(GLenum,GLenum,GLuint,GLint){printMissingFunctionError("glFramebufferTextureEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFramebufferTextureFaceARB(GLenum,GLenum,GLuint,GLint,GLenum){printMissingFunctionError("glFramebufferTextureFaceARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFramebufferTextureFaceEXT(GLenum,GLenum,GLuint,GLint,GLenum){printMissingFunctionError("glFramebufferTextureFaceEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFramebufferTexture(GLenum,GLenum,GLuint,GLint){printMissingFunctionError("glFramebufferTexture");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFramebufferTextureLayerARB(GLenum,GLenum,GLuint,GLint,GLint){printMissingFunctionError("glFramebufferTextureLayerARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFramebufferTextureLayerEXT(GLenum,GLenum,GLuint,GLint,GLint){printMissingFunctionError("glFramebufferTextureLayerEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFramebufferTextureLayer(GLenum,GLenum,GLuint,GLint,GLint){printMissingFunctionError("glFramebufferTextureLayer");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFramebufferTextureMultiviewOVR(GLenum,GLenum,GLuint,GLint,GLint,GLsizei){printMissingFunctionError("glFramebufferTextureMultiviewOVR");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFrameTerminatorGREMEDY(){printMissingFunctionError("glFrameTerminatorGREMEDY");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFrameZoomSGIX(GLint){printMissingFunctionError("glFrameZoomSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFreeObjectBufferATI(GLuint){printMissingFunctionError("glFreeObjectBufferATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFrontFace(GLenum){printMissingFunctionError("glFrontFace");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFrustumfOES(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glFrustumfOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFrustum(GLdouble,GLdouble,GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glFrustum");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglFrustumxOES(GLfixed,GLfixed,GLfixed,GLfixed,GLfixed,GLfixed){printMissingFunctionError("glFrustumxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGenBuffersARB(GLsizei,GLuint*){printMissingFunctionError("glGenBuffersARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGenBuffers(GLsizei,GLuint*){printMissingFunctionError("glGenBuffers");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGenerateMipmapEXT(GLenum){printMissingFunctionError("glGenerateMipmapEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGenerateMipmap(GLenum){printMissingFunctionError("glGenerateMipmap");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGenerateMultiTexMipmapEXT(GLenum,GLenum){printMissingFunctionError("glGenerateMultiTexMipmapEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGenerateTextureMipmapEXT(GLuint,GLenum){printMissingFunctionError("glGenerateTextureMipmapEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGenerateTextureMipmap(GLuint){printMissingFunctionError("glGenerateTextureMipmap");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGenFencesAPPLE(GLsizei,GLuint*){printMissingFunctionError("glGenFencesAPPLE");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGenFencesNV(GLsizei,GLuint*){printMissingFunctionError("glGenFencesNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGenFramebuffersEXT(GLsizei,GLuint*){printMissingFunctionError("glGenFramebuffersEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGenFramebuffers(GLsizei,GLuint*){printMissingFunctionError("glGenFramebuffers");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGenNamesAMD(GLenum,GLuint,GLuint*){printMissingFunctionError("glGenNamesAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGenOcclusionQueriesNV(GLsizei,GLuint*){printMissingFunctionError("glGenOcclusionQueriesNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGenPerfMonitorsAMD(GLsizei,GLuint*){printMissingFunctionError("glGenPerfMonitorsAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGenProgramPipelines(GLsizei,GLuint*){printMissingFunctionError("glGenProgramPipelines");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGenProgramsARB(GLsizei,GLuint*){printMissingFunctionError("glGenProgramsARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGenProgramsNV(GLsizei,GLuint*){printMissingFunctionError("glGenProgramsNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGenQueriesARB(GLsizei,GLuint*){printMissingFunctionError("glGenQueriesARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGenQueries(GLsizei,GLuint*){printMissingFunctionError("glGenQueries");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGenRenderbuffersEXT(GLsizei,GLuint*){printMissingFunctionError("glGenRenderbuffersEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGenRenderbuffers(GLsizei,GLuint*){printMissingFunctionError("glGenRenderbuffers");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGenSamplers(GLsizei,GLuint*){printMissingFunctionError("glGenSamplers");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGenTexturesEXT(GLsizei,GLuint*){printMissingFunctionError("glGenTexturesEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGenTextures(GLsizei,GLuint*){printMissingFunctionError("glGenTextures");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGenTransformFeedbacks(GLsizei,GLuint*){printMissingFunctionError("glGenTransformFeedbacks");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGenTransformFeedbacksNV(GLsizei,GLuint*){printMissingFunctionError("glGenTransformFeedbacksNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGenVertexArraysAPPLE(GLsizei,GLuint*){printMissingFunctionError("glGenVertexArraysAPPLE");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGenVertexArrays(GLsizei,GLuint*){printMissingFunctionError("glGenVertexArrays");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetActiveAtomicCounterBufferiv(GLuint,GLuint,GLenum,GLint*){printMissingFunctionError("glGetActiveAtomicCounterBufferiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetActiveAttribARB(GLhandleARB,GLuint,GLsizei,GLsizei*,GLint*,GLenum*,GLcharARB*){printMissingFunctionError("glGetActiveAttribARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetActiveAttrib(GLuint,GLuint,GLsizei,GLsizei*,GLint*,GLenum*,GLchar*){printMissingFunctionError("glGetActiveAttrib");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetActiveSubroutineName(GLuint,GLenum,GLuint,GLsizei,GLsizei*,GLchar*){printMissingFunctionError("glGetActiveSubroutineName");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetActiveSubroutineUniformiv(GLuint,GLenum,GLuint,GLenum,GLint*){printMissingFunctionError("glGetActiveSubroutineUniformiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetActiveSubroutineUniformName(GLuint,GLenum,GLuint,GLsizei,GLsizei*,GLchar*){printMissingFunctionError("glGetActiveSubroutineUniformName");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetActiveUniformARB(GLhandleARB,GLuint,GLsizei,GLsizei*,GLint*,GLenum*,GLcharARB*){printMissingFunctionError("glGetActiveUniformARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetActiveUniformBlockiv(GLuint,GLuint,GLenum,GLint*){printMissingFunctionError("glGetActiveUniformBlockiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetActiveUniformBlockName(GLuint,GLuint,GLsizei,GLsizei*,GLchar*){printMissingFunctionError("glGetActiveUniformBlockName");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetActiveUniform(GLuint,GLuint,GLsizei,GLsizei*,GLint*,GLenum*,GLchar*){printMissingFunctionError("glGetActiveUniform");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetActiveUniformName(GLuint,GLuint,GLsizei,GLsizei*,GLchar*){printMissingFunctionError("glGetActiveUniformName");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetActiveUniformsiv(GLuint,GLsizei,const GLuint*,GLenum,GLint*){printMissingFunctionError("glGetActiveUniformsiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetActiveVaryingNV(GLuint,GLuint,GLsizei,GLsizei*,GLsizei*,GLenum*,GLchar*){printMissingFunctionError("glGetActiveVaryingNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetArrayObjectfvATI(GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetArrayObjectfvATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetArrayObjectivATI(GLenum,GLenum,GLint*){printMissingFunctionError("glGetArrayObjectivATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetAttachedObjectsARB(GLhandleARB,GLsizei,GLsizei*,GLhandleARB*){printMissingFunctionError("glGetAttachedObjectsARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetAttachedShaders(GLuint,GLsizei,GLsizei*,GLuint*){printMissingFunctionError("glGetAttachedShaders");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetBooleanIndexedvEXT(GLenum,GLuint,GLboolean*){printMissingFunctionError("glGetBooleanIndexedvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetBooleani_v(GLenum,GLuint,GLboolean*){printMissingFunctionError("glGetBooleani_v");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetBooleanv(GLenum,GLboolean*){printMissingFunctionError("glGetBooleanv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetBufferParameteri64v(GLenum,GLenum,GLint64*){printMissingFunctionError("glGetBufferParameteri64v");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetBufferParameterivARB(GLenum,GLenum,GLint*){printMissingFunctionError("glGetBufferParameterivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetBufferParameteriv(GLenum,GLenum,GLint*){printMissingFunctionError("glGetBufferParameteriv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetBufferParameterui64vNV(GLenum,GLenum,GLuint64EXT*){printMissingFunctionError("glGetBufferParameterui64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetBufferPointervARB(GLenum,GLenum,void**){printMissingFunctionError("glGetBufferPointervARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetBufferPointerv(GLenum,GLenum,void**){printMissingFunctionError("glGetBufferPointerv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetBufferSubDataARB(GLenum,GLintptrARB,GLsizeiptrARB,void*){printMissingFunctionError("glGetBufferSubDataARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetBufferSubData(GLenum,GLintptr,GLsizeiptr,void*){printMissingFunctionError("glGetBufferSubData");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetClipPlanefOES(GLenum,GLfloat*){printMissingFunctionError("glGetClipPlanefOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetClipPlane(GLenum,GLdouble*){printMissingFunctionError("glGetClipPlane");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetClipPlanexOES(GLenum,GLfixed*){printMissingFunctionError("glGetClipPlanexOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetColorTableEXT(GLenum,GLenum,GLenum,void*){printMissingFunctionError("glGetColorTableEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetColorTable(GLenum,GLenum,GLenum,GLvoid*){printMissingFunctionError("glGetColorTable");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetColorTableParameterfvEXT(GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetColorTableParameterfvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetColorTableParameterfv(GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetColorTableParameterfv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetColorTableParameterfvSGI(GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetColorTableParameterfvSGI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetColorTableParameterivEXT(GLenum,GLenum,GLint*){printMissingFunctionError("glGetColorTableParameterivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetColorTableParameteriv(GLenum,GLenum,GLint*){printMissingFunctionError("glGetColorTableParameteriv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetColorTableParameterivSGI(GLenum,GLenum,GLint*){printMissingFunctionError("glGetColorTableParameterivSGI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetColorTableSGI(GLenum,GLenum,GLenum,void*){printMissingFunctionError("glGetColorTableSGI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetCombinerInputParameterfvNV(GLenum,GLenum,GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetCombinerInputParameterfvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetCombinerInputParameterivNV(GLenum,GLenum,GLenum,GLenum,GLint*){printMissingFunctionError("glGetCombinerInputParameterivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetCombinerOutputParameterfvNV(GLenum,GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetCombinerOutputParameterfvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetCombinerOutputParameterivNV(GLenum,GLenum,GLenum,GLint*){printMissingFunctionError("glGetCombinerOutputParameterivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetCombinerStageParameterfvNV(GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetCombinerStageParameterfvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetCompressedMultiTexImageEXT(GLenum,GLenum,GLint,void*){printMissingFunctionError("glGetCompressedMultiTexImageEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetCompressedTexImageARB(GLenum,GLint,void*){printMissingFunctionError("glGetCompressedTexImageARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetCompressedTexImage(GLenum,GLint,GLvoid*){printMissingFunctionError("glGetCompressedTexImage");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetCompressedTextureImageEXT(GLuint,GLenum,GLint,void*){printMissingFunctionError("glGetCompressedTextureImageEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetCompressedTextureImage(GLuint,GLint,GLsizei,void*){printMissingFunctionError("glGetCompressedTextureImage");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetCompressedTextureSubImage(GLuint,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLsizei,void*){printMissingFunctionError("glGetCompressedTextureSubImage");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetConvolutionFilterEXT(GLenum,GLenum,GLenum,void*){printMissingFunctionError("glGetConvolutionFilterEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetConvolutionFilter(GLenum,GLenum,GLenum,GLvoid*){printMissingFunctionError("glGetConvolutionFilter");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetConvolutionParameterfvEXT(GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetConvolutionParameterfvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetConvolutionParameterfv(GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetConvolutionParameterfv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetConvolutionParameterivEXT(GLenum,GLenum,GLint*){printMissingFunctionError("glGetConvolutionParameterivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetConvolutionParameteriv(GLenum,GLenum,GLint*){printMissingFunctionError("glGetConvolutionParameteriv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetConvolutionParameterxvOES(GLenum,GLenum,GLfixed*){printMissingFunctionError("glGetConvolutionParameterxvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetCoverageModulationTableNV(GLsizei,GLfloat*){printMissingFunctionError("glGetCoverageModulationTableNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetDetailTexFuncSGIS(GLenum,GLfloat*){printMissingFunctionError("glGetDetailTexFuncSGIS");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetDoubleIndexedvEXT(GLenum,GLuint,GLdouble*){printMissingFunctionError("glGetDoubleIndexedvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetDoublei_vEXT(GLenum,GLuint,GLdouble*){printMissingFunctionError("glGetDoublei_vEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetDoublei_v(GLenum,GLuint,GLdouble*){printMissingFunctionError("glGetDoublei_v");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetDoublev(GLenum,GLdouble*){printMissingFunctionError("glGetDoublev");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetFenceivNV(GLuint,GLenum,GLint*){printMissingFunctionError("glGetFenceivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetFinalCombinerInputParameterfvNV(GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetFinalCombinerInputParameterfvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetFinalCombinerInputParameterivNV(GLenum,GLenum,GLint*){printMissingFunctionError("glGetFinalCombinerInputParameterivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetFirstPerfQueryIdINTEL(GLuint*){printMissingFunctionError("glGetFirstPerfQueryIdINTEL");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetFixedvOES(GLenum,GLfixed*){printMissingFunctionError("glGetFixedvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetFloatIndexedvEXT(GLenum,GLuint,GLfloat*){printMissingFunctionError("glGetFloatIndexedvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetFloati_vEXT(GLenum,GLuint,GLfloat*){printMissingFunctionError("glGetFloati_vEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetFloati_v(GLenum,GLuint,GLfloat*){printMissingFunctionError("glGetFloati_v");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetFloatv(GLenum,GLfloat*){printMissingFunctionError("glGetFloatv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetFogFuncSGIS(GLfloat*){printMissingFunctionError("glGetFogFuncSGIS");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetFragmentLightfvSGIX(GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetFragmentLightfvSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetFragmentLightivSGIX(GLenum,GLenum,GLint*){printMissingFunctionError("glGetFragmentLightivSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetFragmentMaterialfvSGIX(GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetFragmentMaterialfvSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetFragmentMaterialivSGIX(GLenum,GLenum,GLint*){printMissingFunctionError("glGetFragmentMaterialivSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetFramebufferAttachmentParameterivEXT(GLenum,GLenum,GLenum,GLint*){printMissingFunctionError("glGetFramebufferAttachmentParameterivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetFramebufferAttachmentParameteriv(GLenum,GLenum,GLenum,GLint*){printMissingFunctionError("glGetFramebufferAttachmentParameteriv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetFramebufferParameterivEXT(GLuint,GLenum,GLint*){printMissingFunctionError("glGetFramebufferParameterivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetFramebufferParameteriv(GLenum,GLenum,GLint*){printMissingFunctionError("glGetFramebufferParameteriv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetHistogramEXT(GLenum,GLboolean,GLenum,GLenum,void*){printMissingFunctionError("glGetHistogramEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetHistogram(GLenum,GLboolean,GLenum,GLenum,GLvoid*){printMissingFunctionError("glGetHistogram");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetHistogramParameterfvEXT(GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetHistogramParameterfvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetHistogramParameterfv(GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetHistogramParameterfv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetHistogramParameterivEXT(GLenum,GLenum,GLint*){printMissingFunctionError("glGetHistogramParameterivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetHistogramParameteriv(GLenum,GLenum,GLint*){printMissingFunctionError("glGetHistogramParameteriv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetHistogramParameterxvOES(GLenum,GLenum,GLfixed*){printMissingFunctionError("glGetHistogramParameterxvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetImageTransformParameterfvHP(GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetImageTransformParameterfvHP");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetImageTransformParameterivHP(GLenum,GLenum,GLint*){printMissingFunctionError("glGetImageTransformParameterivHP");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetInfoLogARB(GLhandleARB,GLsizei,GLsizei*,GLcharARB*){printMissingFunctionError("glGetInfoLogARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetInteger64i_v(GLenum,GLuint,GLint64*){printMissingFunctionError("glGetInteger64i_v");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetInteger64v(GLenum,GLint64*){printMissingFunctionError("glGetInteger64v");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetIntegerIndexedvEXT(GLenum,GLuint,GLint*){printMissingFunctionError("glGetIntegerIndexedvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetIntegeri_v(GLenum,GLuint,GLint*){printMissingFunctionError("glGetIntegeri_v");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetIntegerui64i_vNV(GLenum,GLuint,GLuint64EXT*){printMissingFunctionError("glGetIntegerui64i_vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetIntegerui64vNV(GLenum,GLuint64EXT*){printMissingFunctionError("glGetIntegerui64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetIntegerv(GLenum,GLint*){printMissingFunctionError("glGetIntegerv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetInternalformati64v(GLenum,GLenum,GLenum,GLsizei,GLint64*){printMissingFunctionError("glGetInternalformati64v");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetInternalformativ(GLenum,GLenum,GLenum,GLsizei,GLint*){printMissingFunctionError("glGetInternalformativ");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetInternalformatSampleivNV(GLenum,GLenum,GLsizei,GLenum,GLsizei,GLint*){printMissingFunctionError("glGetInternalformatSampleivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetInvariantBooleanvEXT(GLuint,GLenum,GLboolean*){printMissingFunctionError("glGetInvariantBooleanvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetInvariantFloatvEXT(GLuint,GLenum,GLfloat*){printMissingFunctionError("glGetInvariantFloatvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetInvariantIntegervEXT(GLuint,GLenum,GLint*){printMissingFunctionError("glGetInvariantIntegervEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetLightfv(GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetLightfv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetLightiv(GLenum,GLenum,GLint*){printMissingFunctionError("glGetLightiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetLightxOES(GLenum,GLenum,GLfixed*){printMissingFunctionError("glGetLightxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetListParameterfvSGIX(GLuint,GLenum,GLfloat*){printMissingFunctionError("glGetListParameterfvSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetListParameterivSGIX(GLuint,GLenum,GLint*){printMissingFunctionError("glGetListParameterivSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetLocalConstantBooleanvEXT(GLuint,GLenum,GLboolean*){printMissingFunctionError("glGetLocalConstantBooleanvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetLocalConstantFloatvEXT(GLuint,GLenum,GLfloat*){printMissingFunctionError("glGetLocalConstantFloatvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetLocalConstantIntegervEXT(GLuint,GLenum,GLint*){printMissingFunctionError("glGetLocalConstantIntegervEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetMapAttribParameterfvNV(GLenum,GLuint,GLenum,GLfloat*){printMissingFunctionError("glGetMapAttribParameterfvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetMapAttribParameterivNV(GLenum,GLuint,GLenum,GLint*){printMissingFunctionError("glGetMapAttribParameterivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetMapControlPointsNV(GLenum,GLuint,GLenum,GLsizei,GLsizei,GLboolean,void*){printMissingFunctionError("glGetMapControlPointsNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetMapdv(GLenum,GLenum,GLdouble*){printMissingFunctionError("glGetMapdv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetMapfv(GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetMapfv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetMapiv(GLenum,GLenum,GLint*){printMissingFunctionError("glGetMapiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetMapParameterfvNV(GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetMapParameterfvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetMapParameterivNV(GLenum,GLenum,GLint*){printMissingFunctionError("glGetMapParameterivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetMapxvOES(GLenum,GLenum,GLfixed*){printMissingFunctionError("glGetMapxvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetMaterialfv(GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetMaterialfv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetMaterialiv(GLenum,GLenum,GLint*){printMissingFunctionError("glGetMaterialiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetMaterialxOES(GLenum,GLenum,GLfixed){printMissingFunctionError("glGetMaterialxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetMinmaxEXT(GLenum,GLboolean,GLenum,GLenum,void*){printMissingFunctionError("glGetMinmaxEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetMinmax(GLenum,GLboolean,GLenum,GLenum,GLvoid*){printMissingFunctionError("glGetMinmax");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetMinmaxParameterfvEXT(GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetMinmaxParameterfvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetMinmaxParameterfv(GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetMinmaxParameterfv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetMinmaxParameterivEXT(GLenum,GLenum,GLint*){printMissingFunctionError("glGetMinmaxParameterivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetMinmaxParameteriv(GLenum,GLenum,GLint*){printMissingFunctionError("glGetMinmaxParameteriv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetMultisamplefv(GLenum,GLuint,GLfloat*){printMissingFunctionError("glGetMultisamplefv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetMultisamplefvNV(GLenum,GLuint,GLfloat*){printMissingFunctionError("glGetMultisamplefvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetMultiTexEnvfvEXT(GLenum,GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetMultiTexEnvfvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetMultiTexEnvivEXT(GLenum,GLenum,GLenum,GLint*){printMissingFunctionError("glGetMultiTexEnvivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetMultiTexGendvEXT(GLenum,GLenum,GLenum,GLdouble*){printMissingFunctionError("glGetMultiTexGendvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetMultiTexGenfvEXT(GLenum,GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetMultiTexGenfvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetMultiTexGenivEXT(GLenum,GLenum,GLenum,GLint*){printMissingFunctionError("glGetMultiTexGenivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetMultiTexImageEXT(GLenum,GLenum,GLint,GLenum,GLenum,void*){printMissingFunctionError("glGetMultiTexImageEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetMultiTexLevelParameterfvEXT(GLenum,GLenum,GLint,GLenum,GLfloat*){printMissingFunctionError("glGetMultiTexLevelParameterfvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetMultiTexLevelParameterivEXT(GLenum,GLenum,GLint,GLenum,GLint*){printMissingFunctionError("glGetMultiTexLevelParameterivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetMultiTexParameterfvEXT(GLenum,GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetMultiTexParameterfvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetMultiTexParameterIivEXT(GLenum,GLenum,GLenum,GLint*){printMissingFunctionError("glGetMultiTexParameterIivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetMultiTexParameterIuivEXT(GLenum,GLenum,GLenum,GLuint*){printMissingFunctionError("glGetMultiTexParameterIuivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetMultiTexParameterivEXT(GLenum,GLenum,GLenum,GLint*){printMissingFunctionError("glGetMultiTexParameterivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetNamedBufferParameteri64v(GLuint,GLenum,GLint64*){printMissingFunctionError("glGetNamedBufferParameteri64v");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetNamedBufferParameterivEXT(GLuint,GLenum,GLint*){printMissingFunctionError("glGetNamedBufferParameterivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetNamedBufferParameteriv(GLuint,GLenum,GLint*){printMissingFunctionError("glGetNamedBufferParameteriv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetNamedBufferParameterui64vNV(GLuint,GLenum,GLuint64EXT*){printMissingFunctionError("glGetNamedBufferParameterui64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetNamedBufferPointervEXT(GLuint,GLenum,void**){printMissingFunctionError("glGetNamedBufferPointervEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetNamedBufferPointerv(GLuint,GLenum,void**){printMissingFunctionError("glGetNamedBufferPointerv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetNamedBufferSubDataEXT(GLuint,GLintptr,GLsizeiptr,void*){printMissingFunctionError("glGetNamedBufferSubDataEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetNamedBufferSubData(GLuint,GLintptr,GLsizeiptr,void*){printMissingFunctionError("glGetNamedBufferSubData");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetNamedFramebufferAttachmentParameterivEXT(GLuint,GLenum,GLenum,GLint*){printMissingFunctionError("glGetNamedFramebufferAttachmentParameterivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetNamedFramebufferAttachmentParameteriv(GLuint,GLenum,GLenum,GLint*){printMissingFunctionError("glGetNamedFramebufferAttachmentParameteriv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetNamedFramebufferParameterivEXT(GLuint,GLenum,GLint*){printMissingFunctionError("glGetNamedFramebufferParameterivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetNamedFramebufferParameteriv(GLuint,GLenum,GLint*){printMissingFunctionError("glGetNamedFramebufferParameteriv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetNamedProgramivEXT(GLuint,GLenum,GLenum,GLint*){printMissingFunctionError("glGetNamedProgramivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetNamedProgramLocalParameterdvEXT(GLuint,GLenum,GLuint,GLdouble*){printMissingFunctionError("glGetNamedProgramLocalParameterdvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetNamedProgramLocalParameterfvEXT(GLuint,GLenum,GLuint,GLfloat*){printMissingFunctionError("glGetNamedProgramLocalParameterfvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetNamedProgramLocalParameterIivEXT(GLuint,GLenum,GLuint,GLint*){printMissingFunctionError("glGetNamedProgramLocalParameterIivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetNamedProgramLocalParameterIuivEXT(GLuint,GLenum,GLuint,GLuint*){printMissingFunctionError("glGetNamedProgramLocalParameterIuivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetNamedProgramStringEXT(GLuint,GLenum,GLenum,void*){printMissingFunctionError("glGetNamedProgramStringEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetNamedRenderbufferParameterivEXT(GLuint,GLenum,GLint*){printMissingFunctionError("glGetNamedRenderbufferParameterivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetNamedRenderbufferParameteriv(GLuint,GLenum,GLint*){printMissingFunctionError("glGetNamedRenderbufferParameteriv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetNamedStringARB(GLint,const GLchar*,GLsizei,GLint*,GLchar*){printMissingFunctionError("glGetNamedStringARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetNamedStringivARB(GLint,const GLchar*,GLenum,GLint*){printMissingFunctionError("glGetNamedStringivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetnColorTableARB(GLenum,GLenum,GLenum,GLsizei,void*){printMissingFunctionError("glGetnColorTableARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetnColorTable(GLenum,GLenum,GLenum,GLsizei,void*){printMissingFunctionError("glGetnColorTable");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetnCompressedTexImageARB(GLenum,GLint,GLsizei,void*){printMissingFunctionError("glGetnCompressedTexImageARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetnCompressedTexImage(GLenum,GLint,GLsizei,void*){printMissingFunctionError("glGetnCompressedTexImage");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetnConvolutionFilterARB(GLenum,GLenum,GLenum,GLsizei,void*){printMissingFunctionError("glGetnConvolutionFilterARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetnConvolutionFilter(GLenum,GLenum,GLenum,GLsizei,void*){printMissingFunctionError("glGetnConvolutionFilter");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetNextPerfQueryIdINTEL(GLuint,GLuint*){printMissingFunctionError("glGetNextPerfQueryIdINTEL");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetnHistogramARB(GLenum,GLboolean,GLenum,GLenum,GLsizei,void*){printMissingFunctionError("glGetnHistogramARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetnHistogram(GLenum,GLboolean,GLenum,GLenum,GLsizei,void*){printMissingFunctionError("glGetnHistogram");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetnMapdvARB(GLenum,GLenum,GLsizei,GLdouble*){printMissingFunctionError("glGetnMapdvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetnMapdv(GLenum,GLenum,GLsizei,GLdouble*){printMissingFunctionError("glGetnMapdv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetnMapfvARB(GLenum,GLenum,GLsizei,GLfloat*){printMissingFunctionError("glGetnMapfvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetnMapfv(GLenum,GLenum,GLsizei,GLfloat*){printMissingFunctionError("glGetnMapfv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetnMapivARB(GLenum,GLenum,GLsizei,GLint*){printMissingFunctionError("glGetnMapivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetnMapiv(GLenum,GLenum,GLsizei,GLint*){printMissingFunctionError("glGetnMapiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetnMinmaxARB(GLenum,GLboolean,GLenum,GLenum,GLsizei,void*){printMissingFunctionError("glGetnMinmaxARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetnMinmax(GLenum,GLboolean,GLenum,GLenum,GLsizei,void*){printMissingFunctionError("glGetnMinmax");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetnPixelMapfvARB(GLenum,GLsizei,GLfloat*){printMissingFunctionError("glGetnPixelMapfvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetnPixelMapfv(GLenum,GLsizei,GLfloat*){printMissingFunctionError("glGetnPixelMapfv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetnPixelMapuivARB(GLenum,GLsizei,GLuint*){printMissingFunctionError("glGetnPixelMapuivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetnPixelMapuiv(GLenum,GLsizei,GLuint*){printMissingFunctionError("glGetnPixelMapuiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetnPixelMapusvARB(GLenum,GLsizei,GLushort*){printMissingFunctionError("glGetnPixelMapusvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetnPixelMapusv(GLenum,GLsizei,GLushort*){printMissingFunctionError("glGetnPixelMapusv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetnPolygonStippleARB(GLsizei,GLubyte*){printMissingFunctionError("glGetnPolygonStippleARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetnPolygonStipple(GLsizei,GLubyte*){printMissingFunctionError("glGetnPolygonStipple");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetnSeparableFilterARB(GLenum,GLenum,GLenum,GLsizei,void*,GLsizei,void*,void*){printMissingFunctionError("glGetnSeparableFilterARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetnSeparableFilter(GLenum,GLenum,GLenum,GLsizei,void*,GLsizei,void*,void*){printMissingFunctionError("glGetnSeparableFilter");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetnTexImageARB(GLenum,GLint,GLenum,GLenum,GLsizei,void*){printMissingFunctionError("glGetnTexImageARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetnTexImage(GLenum,GLint,GLenum,GLenum,GLsizei,void*){printMissingFunctionError("glGetnTexImage");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetnUniformdvARB(GLuint,GLint,GLsizei,GLdouble*){printMissingFunctionError("glGetnUniformdvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetnUniformdv(GLuint,GLint,GLsizei,GLdouble*){printMissingFunctionError("glGetnUniformdv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetnUniformfvARB(GLuint,GLint,GLsizei,GLfloat*){printMissingFunctionError("glGetnUniformfvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetnUniformfv(GLuint,GLint,GLsizei,GLfloat*){printMissingFunctionError("glGetnUniformfv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetnUniformi64vARB(GLuint,GLint,GLsizei,GLint64*){printMissingFunctionError("glGetnUniformi64vARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetnUniformivARB(GLuint,GLint,GLsizei,GLint*){printMissingFunctionError("glGetnUniformivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetnUniformiv(GLuint,GLint,GLsizei,GLint*){printMissingFunctionError("glGetnUniformiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetnUniformui64vARB(GLuint,GLint,GLsizei,GLuint64*){printMissingFunctionError("glGetnUniformui64vARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetnUniformuivARB(GLuint,GLint,GLsizei,GLuint*){printMissingFunctionError("glGetnUniformuivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetnUniformuiv(GLuint,GLint,GLsizei,GLuint*){printMissingFunctionError("glGetnUniformuiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetObjectBufferfvATI(GLuint,GLenum,GLfloat*){printMissingFunctionError("glGetObjectBufferfvATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetObjectBufferivATI(GLuint,GLenum,GLint*){printMissingFunctionError("glGetObjectBufferivATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetObjectLabelEXT(GLenum,GLuint,GLsizei,GLsizei*,GLchar*){printMissingFunctionError("glGetObjectLabelEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetObjectLabel(GLenum,GLuint,GLsizei,GLsizei*,GLchar*){printMissingFunctionError("glGetObjectLabel");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetObjectParameterfvARB(GLhandleARB,GLenum,GLfloat*){printMissingFunctionError("glGetObjectParameterfvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetObjectParameterivAPPLE(GLenum,GLuint,GLenum,GLint*){printMissingFunctionError("glGetObjectParameterivAPPLE");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetObjectParameterivARB(GLhandleARB,GLenum,GLint*){printMissingFunctionError("glGetObjectParameterivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetObjectPtrLabel(const void*,GLsizei,GLsizei*,GLchar*){printMissingFunctionError("glGetObjectPtrLabel");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetOcclusionQueryivNV(GLuint,GLenum,GLint*){printMissingFunctionError("glGetOcclusionQueryivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetOcclusionQueryuivNV(GLuint,GLenum,GLuint*){printMissingFunctionError("glGetOcclusionQueryuivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetPathColorGenfvNV(GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetPathColorGenfvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetPathColorGenivNV(GLenum,GLenum,GLint*){printMissingFunctionError("glGetPathColorGenivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetPathCommandsNV(GLuint,GLubyte*){printMissingFunctionError("glGetPathCommandsNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetPathCoordsNV(GLuint,GLfloat*){printMissingFunctionError("glGetPathCoordsNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetPathDashArrayNV(GLuint,GLfloat*){printMissingFunctionError("glGetPathDashArrayNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetPathMetricRangeNV(GLbitfield,GLuint,GLsizei,GLsizei,GLfloat*){printMissingFunctionError("glGetPathMetricRangeNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetPathMetricsNV(GLbitfield,GLsizei,GLenum,const void*,GLuint,GLsizei,GLfloat*){printMissingFunctionError("glGetPathMetricsNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetPathParameterfvNV(GLuint,GLenum,GLfloat*){printMissingFunctionError("glGetPathParameterfvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetPathParameterivNV(GLuint,GLenum,GLint*){printMissingFunctionError("glGetPathParameterivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetPathSpacingNV(GLenum,GLsizei,GLenum,const void*,GLuint,GLfloat,GLfloat,GLenum,GLfloat*){printMissingFunctionError("glGetPathSpacingNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetPathTexGenfvNV(GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetPathTexGenfvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetPathTexGenivNV(GLenum,GLenum,GLint*){printMissingFunctionError("glGetPathTexGenivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetPerfCounterInfoINTEL(GLuint,GLuint,GLuint,GLchar*,GLuint,GLchar*,GLuint*,GLuint*,GLuint*,GLuint*,GLuint64*){printMissingFunctionError("glGetPerfCounterInfoINTEL");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetPerfMonitorCounterDataAMD(GLuint,GLenum,GLsizei,GLuint*,GLint*){printMissingFunctionError("glGetPerfMonitorCounterDataAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetPerfMonitorCounterInfoAMD(GLuint,GLuint,GLenum,void*){printMissingFunctionError("glGetPerfMonitorCounterInfoAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetPerfMonitorCountersAMD(GLuint,GLint*,GLint*,GLsizei,GLuint*){printMissingFunctionError("glGetPerfMonitorCountersAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetPerfMonitorCounterStringAMD(GLuint,GLuint,GLsizei,GLsizei*,GLchar*){printMissingFunctionError("glGetPerfMonitorCounterStringAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetPerfMonitorGroupsAMD(GLint*,GLsizei,GLuint*){printMissingFunctionError("glGetPerfMonitorGroupsAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetPerfMonitorGroupStringAMD(GLuint,GLsizei,GLsizei*,GLchar*){printMissingFunctionError("glGetPerfMonitorGroupStringAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetPerfQueryDataINTEL(GLuint,GLuint,GLsizei,GLvoid*,GLuint*){printMissingFunctionError("glGetPerfQueryDataINTEL");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetPerfQueryIdByNameINTEL(GLchar*,GLuint*){printMissingFunctionError("glGetPerfQueryIdByNameINTEL");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetPerfQueryInfoINTEL(GLuint,GLuint,GLchar*,GLuint*,GLuint*,GLuint*,GLuint*){printMissingFunctionError("glGetPerfQueryInfoINTEL");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetPixelMapfv(GLenum,GLfloat*){printMissingFunctionError("glGetPixelMapfv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetPixelMapuiv(GLenum,GLuint*){printMissingFunctionError("glGetPixelMapuiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetPixelMapusv(GLenum,GLushort*){printMissingFunctionError("glGetPixelMapusv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetPixelMapxv(GLenum,GLint,GLfixed*){printMissingFunctionError("glGetPixelMapxv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetPixelTexGenParameterfvSGIS(GLenum,GLfloat*){printMissingFunctionError("glGetPixelTexGenParameterfvSGIS");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetPixelTexGenParameterivSGIS(GLenum,GLint*){printMissingFunctionError("glGetPixelTexGenParameterivSGIS");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetPixelTransformParameterfvEXT(GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetPixelTransformParameterfvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetPixelTransformParameterivEXT(GLenum,GLenum,GLint*){printMissingFunctionError("glGetPixelTransformParameterivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetPointerIndexedvEXT(GLenum,GLuint,void**){printMissingFunctionError("glGetPointerIndexedvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetPointeri_vEXT(GLenum,GLuint,void**){printMissingFunctionError("glGetPointeri_vEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetPointervEXT(GLenum,void**){printMissingFunctionError("glGetPointervEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetPointerv(GLenum,GLvoid**){printMissingFunctionError("glGetPointerv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetPolygonStipple(GLubyte*){printMissingFunctionError("glGetPolygonStipple");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetProgramBinary(GLuint,GLsizei,GLsizei*,GLenum*,void*){printMissingFunctionError("glGetProgramBinary");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetProgramEnvParameterdvARB(GLenum,GLuint,GLdouble*){printMissingFunctionError("glGetProgramEnvParameterdvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetProgramEnvParameterfvARB(GLenum,GLuint,GLfloat*){printMissingFunctionError("glGetProgramEnvParameterfvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetProgramEnvParameterIivNV(GLenum,GLuint,GLint*){printMissingFunctionError("glGetProgramEnvParameterIivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetProgramEnvParameterIuivNV(GLenum,GLuint,GLuint*){printMissingFunctionError("glGetProgramEnvParameterIuivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetProgramInfoLog(GLuint,GLsizei,GLsizei*,GLchar*){printMissingFunctionError("glGetProgramInfoLog");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetProgramInterfaceiv(GLuint,GLenum,GLenum,GLint*){printMissingFunctionError("glGetProgramInterfaceiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetProgramivARB(GLenum,GLenum,GLint*){printMissingFunctionError("glGetProgramivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetProgramiv(GLuint,GLenum,GLint*){printMissingFunctionError("glGetProgramiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetProgramivNV(GLuint,GLenum,GLint*){printMissingFunctionError("glGetProgramivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetProgramLocalParameterdvARB(GLenum,GLuint,GLdouble*){printMissingFunctionError("glGetProgramLocalParameterdvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetProgramLocalParameterfvARB(GLenum,GLuint,GLfloat*){printMissingFunctionError("glGetProgramLocalParameterfvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetProgramLocalParameterIivNV(GLenum,GLuint,GLint*){printMissingFunctionError("glGetProgramLocalParameterIivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetProgramLocalParameterIuivNV(GLenum,GLuint,GLuint*){printMissingFunctionError("glGetProgramLocalParameterIuivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetProgramNamedParameterdvNV(GLuint,GLsizei,const GLubyte*,GLdouble*){printMissingFunctionError("glGetProgramNamedParameterdvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetProgramNamedParameterfvNV(GLuint,GLsizei,const GLubyte*,GLfloat*){printMissingFunctionError("glGetProgramNamedParameterfvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetProgramParameterdvNV(GLenum,GLuint,GLenum,GLdouble*){printMissingFunctionError("glGetProgramParameterdvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetProgramParameterfvNV(GLenum,GLuint,GLenum,GLfloat*){printMissingFunctionError("glGetProgramParameterfvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetProgramPipelineInfoLog(GLuint,GLsizei,GLsizei*,GLchar*){printMissingFunctionError("glGetProgramPipelineInfoLog");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetProgramPipelineiv(GLuint,GLenum,GLint*){printMissingFunctionError("glGetProgramPipelineiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetProgramResourcefvNV(GLuint,GLenum,GLuint,GLsizei,const GLenum*,GLsizei,GLsizei*,GLfloat*){printMissingFunctionError("glGetProgramResourcefvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetProgramResourceiv(GLuint,GLenum,GLuint,GLsizei,const GLenum*,GLsizei,GLsizei*,GLint*){printMissingFunctionError("glGetProgramResourceiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetProgramResourceName(GLuint,GLenum,GLuint,GLsizei,GLsizei*,GLchar*){printMissingFunctionError("glGetProgramResourceName");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetProgramStageiv(GLuint,GLenum,GLenum,GLint*){printMissingFunctionError("glGetProgramStageiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetProgramStringARB(GLenum,GLenum,void*){printMissingFunctionError("glGetProgramStringARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetProgramStringNV(GLuint,GLenum,GLubyte*){printMissingFunctionError("glGetProgramStringNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetProgramSubroutineParameteruivNV(GLenum,GLuint,GLuint*){printMissingFunctionError("glGetProgramSubroutineParameteruivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetQueryBufferObjecti64v(GLuint,GLuint,GLenum,GLintptr){printMissingFunctionError("glGetQueryBufferObjecti64v");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetQueryBufferObjectiv(GLuint,GLuint,GLenum,GLintptr){printMissingFunctionError("glGetQueryBufferObjectiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetQueryBufferObjectui64v(GLuint,GLuint,GLenum,GLintptr){printMissingFunctionError("glGetQueryBufferObjectui64v");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetQueryBufferObjectuiv(GLuint,GLuint,GLenum,GLintptr){printMissingFunctionError("glGetQueryBufferObjectuiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetQueryIndexediv(GLenum,GLuint,GLenum,GLint*){printMissingFunctionError("glGetQueryIndexediv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetQueryivARB(GLenum,GLenum,GLint*){printMissingFunctionError("glGetQueryivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetQueryiv(GLenum,GLenum,GLint*){printMissingFunctionError("glGetQueryiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetQueryObjecti64vEXT(GLuint,GLenum,GLint64*){printMissingFunctionError("glGetQueryObjecti64vEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetQueryObjecti64v(GLuint,GLenum,GLint64*){printMissingFunctionError("glGetQueryObjecti64v");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetQueryObjectivARB(GLuint,GLenum,GLint*){printMissingFunctionError("glGetQueryObjectivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetQueryObjectiv(GLuint,GLenum,GLint*){printMissingFunctionError("glGetQueryObjectiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetQueryObjectui64vEXT(GLuint,GLenum,GLuint64*){printMissingFunctionError("glGetQueryObjectui64vEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetQueryObjectui64v(GLuint,GLenum,GLuint64*){printMissingFunctionError("glGetQueryObjectui64v");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetQueryObjectuivARB(GLuint,GLenum,GLuint*){printMissingFunctionError("glGetQueryObjectuivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetQueryObjectuiv(GLuint,GLenum,GLuint*){printMissingFunctionError("glGetQueryObjectuiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetRenderbufferParameterivEXT(GLenum,GLenum,GLint*){printMissingFunctionError("glGetRenderbufferParameterivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetRenderbufferParameteriv(GLenum,GLenum,GLint*){printMissingFunctionError("glGetRenderbufferParameteriv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetSamplerParameterfv(GLuint,GLenum,GLfloat*){printMissingFunctionError("glGetSamplerParameterfv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetSamplerParameterIiv(GLuint,GLenum,GLint*){printMissingFunctionError("glGetSamplerParameterIiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetSamplerParameterIuiv(GLuint,GLenum,GLuint*){printMissingFunctionError("glGetSamplerParameterIuiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetSamplerParameteriv(GLuint,GLenum,GLint*){printMissingFunctionError("glGetSamplerParameteriv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetSeparableFilterEXT(GLenum,GLenum,GLenum,void*,void*,void*){printMissingFunctionError("glGetSeparableFilterEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetSeparableFilter(GLenum,GLenum,GLenum,GLvoid*,GLvoid*,GLvoid*){printMissingFunctionError("glGetSeparableFilter");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetShaderInfoLog(GLuint,GLsizei,GLsizei*,GLchar*){printMissingFunctionError("glGetShaderInfoLog");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetShaderiv(GLuint,GLenum,GLint*){printMissingFunctionError("glGetShaderiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetShaderPrecisionFormat(GLenum,GLenum,GLint*,GLint*){printMissingFunctionError("glGetShaderPrecisionFormat");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetShaderSourceARB(GLhandleARB,GLsizei,GLsizei*,GLcharARB*){printMissingFunctionError("glGetShaderSourceARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetShaderSource(GLuint,GLsizei,GLsizei*,GLchar*){printMissingFunctionError("glGetShaderSource");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetSharpenTexFuncSGIS(GLenum,GLfloat*){printMissingFunctionError("glGetSharpenTexFuncSGIS");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetSynciv(GLsync,GLenum,GLsizei,GLsizei*,GLint*){printMissingFunctionError("glGetSynciv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetTexBumpParameterfvATI(GLenum,GLfloat*){printMissingFunctionError("glGetTexBumpParameterfvATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetTexBumpParameterivATI(GLenum,GLint*){printMissingFunctionError("glGetTexBumpParameterivATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetTexEnvfv(GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetTexEnvfv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetTexEnviv(GLenum,GLenum,GLint*){printMissingFunctionError("glGetTexEnviv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetTexEnvxvOES(GLenum,GLenum,GLfixed*){printMissingFunctionError("glGetTexEnvxvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetTexFilterFuncSGIS(GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetTexFilterFuncSGIS");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetTexGendv(GLenum,GLenum,GLdouble*){printMissingFunctionError("glGetTexGendv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetTexGenfv(GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetTexGenfv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetTexGeniv(GLenum,GLenum,GLint*){printMissingFunctionError("glGetTexGeniv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetTexGenxvOES(GLenum,GLenum,GLfixed*){printMissingFunctionError("glGetTexGenxvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetTexImage(GLenum,GLint,GLenum,GLenum,GLvoid*){printMissingFunctionError("glGetTexImage");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetTexLevelParameterfv(GLenum,GLint,GLenum,GLfloat*){printMissingFunctionError("glGetTexLevelParameterfv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetTexLevelParameteriv(GLenum,GLint,GLenum,GLint*){printMissingFunctionError("glGetTexLevelParameteriv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetTexLevelParameterxvOES(GLenum,GLint,GLenum,GLfixed*){printMissingFunctionError("glGetTexLevelParameterxvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetTexParameterfv(GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetTexParameterfv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetTexParameterIivEXT(GLenum,GLenum,GLint*){printMissingFunctionError("glGetTexParameterIivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetTexParameterIiv(GLenum,GLenum,GLint*){printMissingFunctionError("glGetTexParameterIiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetTexParameterIuivEXT(GLenum,GLenum,GLuint*){printMissingFunctionError("glGetTexParameterIuivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetTexParameterIuiv(GLenum,GLenum,GLuint*){printMissingFunctionError("glGetTexParameterIuiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetTexParameteriv(GLenum,GLenum,GLint*){printMissingFunctionError("glGetTexParameteriv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetTexParameterPointervAPPLE(GLenum,GLenum,void**){printMissingFunctionError("glGetTexParameterPointervAPPLE");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetTexParameterxvOES(GLenum,GLenum,GLfixed*){printMissingFunctionError("glGetTexParameterxvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetTextureImageEXT(GLuint,GLenum,GLint,GLenum,GLenum,void*){printMissingFunctionError("glGetTextureImageEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetTextureImage(GLuint,GLint,GLenum,GLenum,GLsizei,void*){printMissingFunctionError("glGetTextureImage");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetTextureLevelParameterfvEXT(GLuint,GLenum,GLint,GLenum,GLfloat*){printMissingFunctionError("glGetTextureLevelParameterfvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetTextureLevelParameterfv(GLuint,GLint,GLenum,GLfloat*){printMissingFunctionError("glGetTextureLevelParameterfv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetTextureLevelParameterivEXT(GLuint,GLenum,GLint,GLenum,GLint*){printMissingFunctionError("glGetTextureLevelParameterivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetTextureLevelParameteriv(GLuint,GLint,GLenum,GLint*){printMissingFunctionError("glGetTextureLevelParameteriv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetTextureParameterfvEXT(GLuint,GLenum,GLenum,GLfloat*){printMissingFunctionError("glGetTextureParameterfvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetTextureParameterfv(GLuint,GLenum,GLfloat*){printMissingFunctionError("glGetTextureParameterfv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetTextureParameterIivEXT(GLuint,GLenum,GLenum,GLint*){printMissingFunctionError("glGetTextureParameterIivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetTextureParameterIiv(GLuint,GLenum,GLint*){printMissingFunctionError("glGetTextureParameterIiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetTextureParameterIuivEXT(GLuint,GLenum,GLenum,GLuint*){printMissingFunctionError("glGetTextureParameterIuivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetTextureParameterIuiv(GLuint,GLenum,GLuint*){printMissingFunctionError("glGetTextureParameterIuiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetTextureParameterivEXT(GLuint,GLenum,GLenum,GLint*){printMissingFunctionError("glGetTextureParameterivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetTextureParameteriv(GLuint,GLenum,GLint*){printMissingFunctionError("glGetTextureParameteriv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetTextureSubImage(GLuint,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLenum,GLenum,GLsizei,void*){printMissingFunctionError("glGetTextureSubImage");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetTrackMatrixivNV(GLenum,GLuint,GLenum,GLint*){printMissingFunctionError("glGetTrackMatrixivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetTransformFeedbacki64_v(GLuint,GLenum,GLuint,GLint64*){printMissingFunctionError("glGetTransformFeedbacki64_v");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetTransformFeedbackiv(GLuint,GLenum,GLint*){printMissingFunctionError("glGetTransformFeedbackiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetTransformFeedbacki_v(GLuint,GLenum,GLuint,GLint*){printMissingFunctionError("glGetTransformFeedbacki_v");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetTransformFeedbackVaryingEXT(GLuint,GLuint,GLsizei,GLsizei*,GLsizei*,GLenum*,GLchar*){printMissingFunctionError("glGetTransformFeedbackVaryingEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetTransformFeedbackVarying(GLuint,GLuint,GLsizei,GLsizei*,GLsizei*,GLenum*,GLchar*){printMissingFunctionError("glGetTransformFeedbackVarying");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetTransformFeedbackVaryingNV(GLuint,GLuint,GLint*){printMissingFunctionError("glGetTransformFeedbackVaryingNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetUniformdv(GLuint,GLint,GLdouble*){printMissingFunctionError("glGetUniformdv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetUniformfvARB(GLhandleARB,GLint,GLfloat*){printMissingFunctionError("glGetUniformfvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetUniformfv(GLuint,GLint,GLfloat*){printMissingFunctionError("glGetUniformfv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetUniformi64vARB(GLuint,GLint,GLint64*){printMissingFunctionError("glGetUniformi64vARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetUniformi64vNV(GLuint,GLint,GLint64EXT*){printMissingFunctionError("glGetUniformi64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetUniformIndices(GLuint,GLsizei,const GLchar*const*,GLuint*){printMissingFunctionError("glGetUniformIndices");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetUniformivARB(GLhandleARB,GLint,GLint*){printMissingFunctionError("glGetUniformivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetUniformiv(GLuint,GLint,GLint*){printMissingFunctionError("glGetUniformiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetUniformSubroutineuiv(GLenum,GLint,GLuint*){printMissingFunctionError("glGetUniformSubroutineuiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetUniformui64vARB(GLuint,GLint,GLuint64*){printMissingFunctionError("glGetUniformui64vARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetUniformui64vNV(GLuint,GLint,GLuint64EXT*){printMissingFunctionError("glGetUniformui64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetUniformuivEXT(GLuint,GLint,GLuint*){printMissingFunctionError("glGetUniformuivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetUniformuiv(GLuint,GLint,GLuint*){printMissingFunctionError("glGetUniformuiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetVariantArrayObjectfvATI(GLuint,GLenum,GLfloat*){printMissingFunctionError("glGetVariantArrayObjectfvATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetVariantArrayObjectivATI(GLuint,GLenum,GLint*){printMissingFunctionError("glGetVariantArrayObjectivATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetVariantBooleanvEXT(GLuint,GLenum,GLboolean*){printMissingFunctionError("glGetVariantBooleanvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetVariantFloatvEXT(GLuint,GLenum,GLfloat*){printMissingFunctionError("glGetVariantFloatvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetVariantIntegervEXT(GLuint,GLenum,GLint*){printMissingFunctionError("glGetVariantIntegervEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetVariantPointervEXT(GLuint,GLenum,void**){printMissingFunctionError("glGetVariantPointervEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetVertexArrayIndexed64iv(GLuint,GLuint,GLenum,GLint64*){printMissingFunctionError("glGetVertexArrayIndexed64iv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetVertexArrayIndexediv(GLuint,GLuint,GLenum,GLint*){printMissingFunctionError("glGetVertexArrayIndexediv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetVertexArrayIntegeri_vEXT(GLuint,GLuint,GLenum,GLint*){printMissingFunctionError("glGetVertexArrayIntegeri_vEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetVertexArrayIntegervEXT(GLuint,GLenum,GLint*){printMissingFunctionError("glGetVertexArrayIntegervEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetVertexArrayiv(GLuint,GLenum,GLint*){printMissingFunctionError("glGetVertexArrayiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetVertexArrayPointeri_vEXT(GLuint,GLuint,GLenum,void**){printMissingFunctionError("glGetVertexArrayPointeri_vEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetVertexArrayPointervEXT(GLuint,GLenum,void**){printMissingFunctionError("glGetVertexArrayPointervEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetVertexAttribArrayObjectfvATI(GLuint,GLenum,GLfloat*){printMissingFunctionError("glGetVertexAttribArrayObjectfvATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetVertexAttribArrayObjectivATI(GLuint,GLenum,GLint*){printMissingFunctionError("glGetVertexAttribArrayObjectivATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetVertexAttribdvARB(GLuint,GLenum,GLdouble*){printMissingFunctionError("glGetVertexAttribdvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetVertexAttribdv(GLuint,GLenum,GLdouble*){printMissingFunctionError("glGetVertexAttribdv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetVertexAttribdvNV(GLuint,GLenum,GLdouble*){printMissingFunctionError("glGetVertexAttribdvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetVertexAttribfvARB(GLuint,GLenum,GLfloat*){printMissingFunctionError("glGetVertexAttribfvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetVertexAttribfv(GLuint,GLenum,GLfloat*){printMissingFunctionError("glGetVertexAttribfv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetVertexAttribfvNV(GLuint,GLenum,GLfloat*){printMissingFunctionError("glGetVertexAttribfvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetVertexAttribIivEXT(GLuint,GLenum,GLint*){printMissingFunctionError("glGetVertexAttribIivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetVertexAttribIiv(GLuint,GLenum,GLint*){printMissingFunctionError("glGetVertexAttribIiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetVertexAttribIuivEXT(GLuint,GLenum,GLuint*){printMissingFunctionError("glGetVertexAttribIuivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetVertexAttribIuiv(GLuint,GLenum,GLuint*){printMissingFunctionError("glGetVertexAttribIuiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetVertexAttribivARB(GLuint,GLenum,GLint*){printMissingFunctionError("glGetVertexAttribivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetVertexAttribiv(GLuint,GLenum,GLint*){printMissingFunctionError("glGetVertexAttribiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetVertexAttribivNV(GLuint,GLenum,GLint*){printMissingFunctionError("glGetVertexAttribivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetVertexAttribLdvEXT(GLuint,GLenum,GLdouble*){printMissingFunctionError("glGetVertexAttribLdvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetVertexAttribLdv(GLuint,GLenum,GLdouble*){printMissingFunctionError("glGetVertexAttribLdv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetVertexAttribLi64vNV(GLuint,GLenum,GLint64EXT*){printMissingFunctionError("glGetVertexAttribLi64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetVertexAttribLui64vARB(GLuint,GLenum,GLuint64EXT*){printMissingFunctionError("glGetVertexAttribLui64vARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetVertexAttribLui64vNV(GLuint,GLenum,GLuint64EXT*){printMissingFunctionError("glGetVertexAttribLui64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetVertexAttribPointervARB(GLuint,GLenum,void**){printMissingFunctionError("glGetVertexAttribPointervARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetVertexAttribPointerv(GLuint,GLenum,void**){printMissingFunctionError("glGetVertexAttribPointerv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetVertexAttribPointervNV(GLuint,GLenum,void**){printMissingFunctionError("glGetVertexAttribPointervNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetVideoCaptureivNV(GLuint,GLenum,GLint*){printMissingFunctionError("glGetVideoCaptureivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetVideoCaptureStreamdvNV(GLuint,GLuint,GLenum,GLdouble*){printMissingFunctionError("glGetVideoCaptureStreamdvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetVideoCaptureStreamfvNV(GLuint,GLuint,GLenum,GLfloat*){printMissingFunctionError("glGetVideoCaptureStreamfvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetVideoCaptureStreamivNV(GLuint,GLuint,GLenum,GLint*){printMissingFunctionError("glGetVideoCaptureStreamivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetVideoi64vNV(GLuint,GLenum,GLint64EXT*){printMissingFunctionError("glGetVideoi64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetVideoivNV(GLuint,GLenum,GLint*){printMissingFunctionError("glGetVideoivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetVideoui64vNV(GLuint,GLenum,GLuint64EXT*){printMissingFunctionError("glGetVideoui64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGetVideouivNV(GLuint,GLenum,GLuint*){printMissingFunctionError("glGetVideouivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGlobalAlphaFactorbSUN(GLbyte){printMissingFunctionError("glGlobalAlphaFactorbSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGlobalAlphaFactordSUN(GLdouble){printMissingFunctionError("glGlobalAlphaFactordSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGlobalAlphaFactorfSUN(GLfloat){printMissingFunctionError("glGlobalAlphaFactorfSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGlobalAlphaFactoriSUN(GLint){printMissingFunctionError("glGlobalAlphaFactoriSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGlobalAlphaFactorsSUN(GLshort){printMissingFunctionError("glGlobalAlphaFactorsSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGlobalAlphaFactorubSUN(GLubyte){printMissingFunctionError("glGlobalAlphaFactorubSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGlobalAlphaFactoruiSUN(GLuint){printMissingFunctionError("glGlobalAlphaFactoruiSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglGlobalAlphaFactorusSUN(GLushort){printMissingFunctionError("glGlobalAlphaFactorusSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglHint(GLenum,GLenum){printMissingFunctionError("glHint");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglHintPGI(GLenum,GLint){printMissingFunctionError("glHintPGI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglHistogramEXT(GLenum,GLsizei,GLenum,GLboolean){printMissingFunctionError("glHistogramEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglHistogram(GLenum,GLsizei,GLenum,GLboolean){printMissingFunctionError("glHistogram");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglIglooInterfaceSGIX(GLenum,const void*){printMissingFunctionError("glIglooInterfaceSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglImageTransformParameterfHP(GLenum,GLenum,GLfloat){printMissingFunctionError("glImageTransformParameterfHP");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglImageTransformParameterfvHP(GLenum,GLenum,const GLfloat*){printMissingFunctionError("glImageTransformParameterfvHP");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglImageTransformParameteriHP(GLenum,GLenum,GLint){printMissingFunctionError("glImageTransformParameteriHP");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglImageTransformParameterivHP(GLenum,GLenum,const GLint*){printMissingFunctionError("glImageTransformParameterivHP");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglIndexd(GLdouble){printMissingFunctionError("glIndexd");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglIndexdv(const GLdouble*){printMissingFunctionError("glIndexdv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglIndexf(GLfloat){printMissingFunctionError("glIndexf");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglIndexFormatNV(GLenum,GLsizei){printMissingFunctionError("glIndexFormatNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglIndexFuncEXT(GLenum,GLclampf){printMissingFunctionError("glIndexFuncEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglIndexfv(const GLfloat*){printMissingFunctionError("glIndexfv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglIndexi(GLint){printMissingFunctionError("glIndexi");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglIndexiv(const GLint*){printMissingFunctionError("glIndexiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglIndexMask(GLuint){printMissingFunctionError("glIndexMask");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglIndexMaterialEXT(GLenum,GLenum){printMissingFunctionError("glIndexMaterialEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglIndexPointerEXT(GLenum,GLsizei,GLsizei,const void*){printMissingFunctionError("glIndexPointerEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglIndexPointer(GLenum,GLsizei,const GLvoid*){printMissingFunctionError("glIndexPointer");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglIndexPointerListIBM(GLenum,GLint,const void**,GLint){printMissingFunctionError("glIndexPointerListIBM");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglIndexs(GLshort){printMissingFunctionError("glIndexs");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglIndexsv(const GLshort*){printMissingFunctionError("glIndexsv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglIndexub(GLubyte){printMissingFunctionError("glIndexub");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglIndexubv(const GLubyte*){printMissingFunctionError("glIndexubv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglIndexxOES(GLfixed){printMissingFunctionError("glIndexxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglIndexxvOES(const GLfixed*){printMissingFunctionError("glIndexxvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglInitNames(){printMissingFunctionError("glInitNames");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglInsertComponentEXT(GLuint,GLuint,GLuint){printMissingFunctionError("glInsertComponentEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglInsertEventMarkerEXT(GLsizei,const GLchar*){printMissingFunctionError("glInsertEventMarkerEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglInstrumentsBufferSGIX(GLsizei,GLint*){printMissingFunctionError("glInstrumentsBufferSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglInterleavedArrays(GLenum,GLsizei,const GLvoid*){printMissingFunctionError("glInterleavedArrays");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglInterpolatePathsNV(GLuint,GLuint,GLuint,GLfloat){printMissingFunctionError("glInterpolatePathsNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglInvalidateBufferData(GLuint){printMissingFunctionError("glInvalidateBufferData");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglInvalidateBufferSubData(GLuint,GLintptr,GLsizeiptr){printMissingFunctionError("glInvalidateBufferSubData");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglInvalidateFramebuffer(GLenum,GLsizei,const GLenum*){printMissingFunctionError("glInvalidateFramebuffer");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglInvalidateNamedFramebufferData(GLuint,GLsizei,const GLenum*){printMissingFunctionError("glInvalidateNamedFramebufferData");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglInvalidateNamedFramebufferSubData(GLuint,GLsizei,const GLenum*,GLint,GLint,GLsizei,GLsizei){printMissingFunctionError("glInvalidateNamedFramebufferSubData");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglInvalidateSubFramebuffer(GLenum,GLsizei,const GLenum*,GLint,GLint,GLsizei,GLsizei){printMissingFunctionError("glInvalidateSubFramebuffer");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglInvalidateTexImage(GLuint,GLint){printMissingFunctionError("glInvalidateTexImage");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglInvalidateTexSubImage(GLuint,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei){printMissingFunctionError("glInvalidateTexSubImage");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglLabelObjectEXT(GLenum,GLuint,GLsizei,const GLchar*){printMissingFunctionError("glLabelObjectEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglLightEnviSGIX(GLenum,GLint){printMissingFunctionError("glLightEnviSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglLightf(GLenum,GLenum,GLfloat){printMissingFunctionError("glLightf");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglLightfv(GLenum,GLenum,const GLfloat*){printMissingFunctionError("glLightfv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglLighti(GLenum,GLenum,GLint){printMissingFunctionError("glLighti");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglLightiv(GLenum,GLenum,const GLint*){printMissingFunctionError("glLightiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglLightModelf(GLenum,GLfloat){printMissingFunctionError("glLightModelf");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglLightModelfv(GLenum,const GLfloat*){printMissingFunctionError("glLightModelfv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglLightModeli(GLenum,GLint){printMissingFunctionError("glLightModeli");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglLightModeliv(GLenum,const GLint*){printMissingFunctionError("glLightModeliv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglLightModelxOES(GLenum,GLfixed){printMissingFunctionError("glLightModelxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglLightModelxvOES(GLenum,const GLfixed*){printMissingFunctionError("glLightModelxvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglLightxOES(GLenum,GLenum,GLfixed){printMissingFunctionError("glLightxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglLightxvOES(GLenum,GLenum,const GLfixed*){printMissingFunctionError("glLightxvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglLineStipple(GLint,GLushort){printMissingFunctionError("glLineStipple");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglLineWidth(GLfloat){printMissingFunctionError("glLineWidth");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglLineWidthxOES(GLfixed){printMissingFunctionError("glLineWidthxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglLinkProgramARB(GLhandleARB){printMissingFunctionError("glLinkProgramARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglLinkProgram(GLuint){printMissingFunctionError("glLinkProgram");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglListBase(GLuint){printMissingFunctionError("glListBase");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglListDrawCommandsStatesClientNV(GLuint,GLuint,const void**,const GLsizei*,const GLuint*,const GLuint*,GLuint){printMissingFunctionError("glListDrawCommandsStatesClientNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglListParameterfSGIX(GLuint,GLenum,GLfloat){printMissingFunctionError("glListParameterfSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglListParameterfvSGIX(GLuint,GLenum,const GLfloat*){printMissingFunctionError("glListParameterfvSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglListParameteriSGIX(GLuint,GLenum,GLint){printMissingFunctionError("glListParameteriSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglListParameterivSGIX(GLuint,GLenum,const GLint*){printMissingFunctionError("glListParameterivSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglLoadIdentity(){printMissingFunctionError("glLoadIdentity");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglLoadIdentityDeformationMapSGIX(GLbitfield){printMissingFunctionError("glLoadIdentityDeformationMapSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglLoadMatrixd(const GLdouble*){printMissingFunctionError("glLoadMatrixd");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglLoadMatrixf(const GLfloat*){printMissingFunctionError("glLoadMatrixf");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglLoadMatrixxOES(const GLfixed*){printMissingFunctionError("glLoadMatrixxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglLoadName(GLuint){printMissingFunctionError("glLoadName");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglLoadProgramNV(GLenum,GLuint,GLsizei,const GLubyte*){printMissingFunctionError("glLoadProgramNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglLoadTransposeMatrixdARB(const GLdouble*){printMissingFunctionError("glLoadTransposeMatrixdARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglLoadTransposeMatrixd(const GLdouble){printMissingFunctionError("glLoadTransposeMatrixd");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglLoadTransposeMatrixfARB(const GLfloat*){printMissingFunctionError("glLoadTransposeMatrixfARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglLoadTransposeMatrixf(const GLfloat){printMissingFunctionError("glLoadTransposeMatrixf");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglLoadTransposeMatrixxOES(const GLfixed*){printMissingFunctionError("glLoadTransposeMatrixxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglLockArraysEXT(GLint,GLsizei){printMissingFunctionError("glLockArraysEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglLogicOp(GLenum){printMissingFunctionError("glLogicOp");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMakeBufferNonResidentNV(GLenum){printMissingFunctionError("glMakeBufferNonResidentNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMakeBufferResidentNV(GLenum,GLenum){printMissingFunctionError("glMakeBufferResidentNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMakeImageHandleNonResidentARB(GLuint64){printMissingFunctionError("glMakeImageHandleNonResidentARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMakeImageHandleNonResidentNV(GLuint64){printMissingFunctionError("glMakeImageHandleNonResidentNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMakeImageHandleResidentARB(GLuint64,GLenum){printMissingFunctionError("glMakeImageHandleResidentARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMakeImageHandleResidentNV(GLuint64,GLenum){printMissingFunctionError("glMakeImageHandleResidentNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMakeNamedBufferNonResidentNV(GLuint){printMissingFunctionError("glMakeNamedBufferNonResidentNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMakeNamedBufferResidentNV(GLuint,GLenum){printMissingFunctionError("glMakeNamedBufferResidentNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMakeTextureHandleNonResidentARB(GLuint64){printMissingFunctionError("glMakeTextureHandleNonResidentARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMakeTextureHandleNonResidentNV(GLuint64){printMissingFunctionError("glMakeTextureHandleNonResidentNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMakeTextureHandleResidentARB(GLuint64){printMissingFunctionError("glMakeTextureHandleResidentARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMakeTextureHandleResidentNV(GLuint64){printMissingFunctionError("glMakeTextureHandleResidentNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMap1d(GLenum,GLdouble,GLdouble,GLint,GLint,const GLdouble*){printMissingFunctionError("glMap1d");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMap1f(GLenum,GLfloat,GLfloat,GLint,GLint,const GLfloat*){printMissingFunctionError("glMap1f");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMap1xOES(GLenum,GLfixed,GLfixed,GLint,GLint,GLfixed){printMissingFunctionError("glMap1xOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMap2d(GLenum,GLdouble,GLdouble,GLint,GLint,GLdouble,GLdouble,GLint,GLint,const GLdouble*){printMissingFunctionError("glMap2d");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMap2f(GLenum,GLfloat,GLfloat,GLint,GLint,GLfloat,GLfloat,GLint,GLint,const GLfloat*){printMissingFunctionError("glMap2f");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMap2xOES(GLenum,GLfixed,GLfixed,GLint,GLint,GLfixed,GLfixed,GLint,GLint,GLfixed){printMissingFunctionError("glMap2xOES");std::exit(1);return (void)0;}
GEGL_EXPORT void* geglTrapglMapBufferARB(GLenum,GLenum){printMissingFunctionError("glMapBufferARB");std::exit(1);return (void*)0;}
GEGL_EXPORT void* geglTrapglMapBuffer(GLenum,GLenum){printMissingFunctionError("glMapBuffer");std::exit(1);return (void*)0;}
GEGL_EXPORT void* geglTrapglMapBufferRange(GLenum,GLintptr,GLsizeiptr,GLbitfield){printMissingFunctionError("glMapBufferRange");std::exit(1);return (void*)0;}
GEGL_EXPORT void geglTrapglMapControlPointsNV(GLenum,GLuint,GLenum,GLsizei,GLsizei,GLint,GLint,GLboolean,const void*){printMissingFunctionError("glMapControlPointsNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMapGrid1d(GLint,GLdouble,GLdouble){printMissingFunctionError("glMapGrid1d");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMapGrid1f(GLint,GLfloat,GLfloat){printMissingFunctionError("glMapGrid1f");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMapGrid1xOES(GLint,GLfixed,GLfixed){printMissingFunctionError("glMapGrid1xOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMapGrid2d(GLint,GLdouble,GLdouble,GLint,GLdouble,GLdouble){printMissingFunctionError("glMapGrid2d");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMapGrid2f(GLint,GLfloat,GLfloat,GLint,GLfloat,GLfloat){printMissingFunctionError("glMapGrid2f");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMapGrid2xOES(GLint,GLfixed,GLfixed,GLfixed,GLfixed){printMissingFunctionError("glMapGrid2xOES");std::exit(1);return (void)0;}
GEGL_EXPORT void* geglTrapglMapNamedBufferEXT(GLuint,GLenum){printMissingFunctionError("glMapNamedBufferEXT");std::exit(1);return (void*)0;}
GEGL_EXPORT void* geglTrapglMapNamedBuffer(GLuint,GLenum){printMissingFunctionError("glMapNamedBuffer");std::exit(1);return (void*)0;}
GEGL_EXPORT void* geglTrapglMapNamedBufferRangeEXT(GLuint,GLintptr,GLsizeiptr,GLbitfield){printMissingFunctionError("glMapNamedBufferRangeEXT");std::exit(1);return (void*)0;}
GEGL_EXPORT void* geglTrapglMapNamedBufferRange(GLuint,GLintptr,GLsizeiptr,GLbitfield){printMissingFunctionError("glMapNamedBufferRange");std::exit(1);return (void*)0;}
GEGL_EXPORT void* geglTrapglMapObjectBufferATI(GLuint){printMissingFunctionError("glMapObjectBufferATI");std::exit(1);return (void*)0;}
GEGL_EXPORT void geglTrapglMapParameterfvNV(GLenum,GLenum,const GLfloat*){printMissingFunctionError("glMapParameterfvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMapParameterivNV(GLenum,GLenum,const GLint*){printMissingFunctionError("glMapParameterivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void* geglTrapglMapTexture2DINTEL(GLuint,GLint,GLbitfield,GLint*,GLenum*){printMissingFunctionError("glMapTexture2DINTEL");std::exit(1);return (void*)0;}
GEGL_EXPORT void geglTrapglMapVertexAttrib1dAPPLE(GLuint,GLuint,GLdouble,GLdouble,GLint,GLint,const GLdouble*){printMissingFunctionError("glMapVertexAttrib1dAPPLE");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMapVertexAttrib1fAPPLE(GLuint,GLuint,GLfloat,GLfloat,GLint,GLint,const GLfloat*){printMissingFunctionError("glMapVertexAttrib1fAPPLE");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMapVertexAttrib2dAPPLE(GLuint,GLuint,GLdouble,GLdouble,GLint,GLint,GLdouble,GLdouble,GLint,GLint,const GLdouble*){printMissingFunctionError("glMapVertexAttrib2dAPPLE");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMapVertexAttrib2fAPPLE(GLuint,GLuint,GLfloat,GLfloat,GLint,GLint,GLfloat,GLfloat,GLint,GLint,const GLfloat*){printMissingFunctionError("glMapVertexAttrib2fAPPLE");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMaterialf(GLenum,GLenum,GLfloat){printMissingFunctionError("glMaterialf");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMaterialfv(GLenum,GLenum,const GLfloat*){printMissingFunctionError("glMaterialfv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMateriali(GLenum,GLenum,GLint){printMissingFunctionError("glMateriali");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMaterialiv(GLenum,GLenum,const GLint*){printMissingFunctionError("glMaterialiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMaterialxOES(GLenum,GLenum,GLfixed){printMissingFunctionError("glMaterialxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMaterialxvOES(GLenum,GLenum,const GLfixed*){printMissingFunctionError("glMaterialxvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMatrixFrustumEXT(GLenum,GLdouble,GLdouble,GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glMatrixFrustumEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMatrixIndexPointerARB(GLint,GLenum,GLsizei,const void*){printMissingFunctionError("glMatrixIndexPointerARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMatrixIndexubvARB(GLint,const GLubyte*){printMissingFunctionError("glMatrixIndexubvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMatrixIndexuivARB(GLint,const GLuint*){printMissingFunctionError("glMatrixIndexuivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMatrixIndexusvARB(GLint,const GLushort*){printMissingFunctionError("glMatrixIndexusvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMatrixLoad3x2fNV(GLenum,const GLfloat*){printMissingFunctionError("glMatrixLoad3x2fNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMatrixLoad3x3fNV(GLenum,const GLfloat*){printMissingFunctionError("glMatrixLoad3x3fNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMatrixLoaddEXT(GLenum,const GLdouble*){printMissingFunctionError("glMatrixLoaddEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMatrixLoadfEXT(GLenum,const GLfloat*){printMissingFunctionError("glMatrixLoadfEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMatrixLoadIdentityEXT(GLenum){printMissingFunctionError("glMatrixLoadIdentityEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMatrixLoadTranspose3x3fNV(GLenum,const GLfloat*){printMissingFunctionError("glMatrixLoadTranspose3x3fNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMatrixLoadTransposedEXT(GLenum,const GLdouble*){printMissingFunctionError("glMatrixLoadTransposedEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMatrixLoadTransposefEXT(GLenum,const GLfloat*){printMissingFunctionError("glMatrixLoadTransposefEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMatrixMode(GLenum){printMissingFunctionError("glMatrixMode");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMatrixMult3x2fNV(GLenum,const GLfloat*){printMissingFunctionError("glMatrixMult3x2fNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMatrixMult3x3fNV(GLenum,const GLfloat*){printMissingFunctionError("glMatrixMult3x3fNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMatrixMultdEXT(GLenum,const GLdouble*){printMissingFunctionError("glMatrixMultdEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMatrixMultfEXT(GLenum,const GLfloat*){printMissingFunctionError("glMatrixMultfEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMatrixMultTranspose3x3fNV(GLenum,const GLfloat*){printMissingFunctionError("glMatrixMultTranspose3x3fNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMatrixMultTransposedEXT(GLenum,const GLdouble*){printMissingFunctionError("glMatrixMultTransposedEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMatrixMultTransposefEXT(GLenum,const GLfloat*){printMissingFunctionError("glMatrixMultTransposefEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMatrixOrthoEXT(GLenum,GLdouble,GLdouble,GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glMatrixOrthoEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMatrixPopEXT(GLenum){printMissingFunctionError("glMatrixPopEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMatrixPushEXT(GLenum){printMissingFunctionError("glMatrixPushEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMatrixRotatedEXT(GLenum,GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glMatrixRotatedEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMatrixRotatefEXT(GLenum,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glMatrixRotatefEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMatrixScaledEXT(GLenum,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glMatrixScaledEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMatrixScalefEXT(GLenum,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glMatrixScalefEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMatrixTranslatedEXT(GLenum,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glMatrixTranslatedEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMatrixTranslatefEXT(GLenum,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glMatrixTranslatefEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMaxShaderCompilerThreadsARB(GLuint){printMissingFunctionError("glMaxShaderCompilerThreadsARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMemoryBarrierByRegion(GLbitfield){printMissingFunctionError("glMemoryBarrierByRegion");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMemoryBarrierEXT(GLbitfield){printMissingFunctionError("glMemoryBarrierEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMemoryBarrier(GLbitfield){printMissingFunctionError("glMemoryBarrier");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMinmaxEXT(GLenum,GLenum,GLboolean){printMissingFunctionError("glMinmaxEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMinmax(GLenum,GLenum,GLboolean){printMissingFunctionError("glMinmax");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMinSampleShadingARB(GLfloat){printMissingFunctionError("glMinSampleShadingARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMinSampleShading(GLfloat){printMissingFunctionError("glMinSampleShading");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiDrawArraysEXT(GLenum,const GLint*,const GLsizei*,GLsizei){printMissingFunctionError("glMultiDrawArraysEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiDrawArrays(GLenum,const GLint*,const GLsizei*,GLsizei){printMissingFunctionError("glMultiDrawArrays");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiDrawArraysIndirectAMD(GLenum,const void*,GLsizei,GLsizei){printMissingFunctionError("glMultiDrawArraysIndirectAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiDrawArraysIndirectBindlessCountNV(GLenum,const void*,GLsizei,GLsizei,GLsizei,GLint){printMissingFunctionError("glMultiDrawArraysIndirectBindlessCountNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiDrawArraysIndirectBindlessNV(GLenum,const void*,GLsizei,GLsizei,GLint){printMissingFunctionError("glMultiDrawArraysIndirectBindlessNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiDrawArraysIndirectCountARB(GLenum,GLintptr,GLintptr,GLsizei,GLsizei){printMissingFunctionError("glMultiDrawArraysIndirectCountARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiDrawArraysIndirect(GLenum,const void*,GLsizei,GLsizei){printMissingFunctionError("glMultiDrawArraysIndirect");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiDrawElementArrayAPPLE(GLenum,const GLint*,const GLsizei*,GLsizei){printMissingFunctionError("glMultiDrawElementArrayAPPLE");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiDrawElementsBaseVertex(GLenum,const GLsizei*,GLenum,const void*const*,GLsizei,const GLint*){printMissingFunctionError("glMultiDrawElementsBaseVertex");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiDrawElementsEXT(GLenum,const GLsizei*,GLenum,const void*const*,GLsizei){printMissingFunctionError("glMultiDrawElementsEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiDrawElements(GLenum,const GLsizei*,GLenum,const void*const*,GLsizei){printMissingFunctionError("glMultiDrawElements");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiDrawElementsIndirectAMD(GLenum,GLenum,const void*,GLsizei,GLsizei){printMissingFunctionError("glMultiDrawElementsIndirectAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiDrawElementsIndirectBindlessCountNV(GLenum,GLenum,const void*,GLsizei,GLsizei,GLsizei,GLint){printMissingFunctionError("glMultiDrawElementsIndirectBindlessCountNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiDrawElementsIndirectBindlessNV(GLenum,GLenum,const void*,GLsizei,GLsizei,GLint){printMissingFunctionError("glMultiDrawElementsIndirectBindlessNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiDrawElementsIndirectCountARB(GLenum,GLenum,GLintptr,GLintptr,GLsizei,GLsizei){printMissingFunctionError("glMultiDrawElementsIndirectCountARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiDrawElementsIndirect(GLenum,GLenum,const void*,GLsizei,GLsizei){printMissingFunctionError("glMultiDrawElementsIndirect");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiDrawRangeElementArrayAPPLE(GLenum,GLuint,GLuint,const GLint*,const GLsizei*,GLsizei){printMissingFunctionError("glMultiDrawRangeElementArrayAPPLE");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiModeDrawArraysIBM(const GLenum*,const GLint*,const GLsizei*,GLsizei,GLint){printMissingFunctionError("glMultiModeDrawArraysIBM");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiModeDrawElementsIBM(const GLenum*,const GLsizei*,GLenum,const void*const*,GLsizei,GLint){printMissingFunctionError("glMultiModeDrawElementsIBM");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexBufferEXT(GLenum,GLenum,GLenum,GLuint){printMissingFunctionError("glMultiTexBufferEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord1bOES(GLenum,GLbyte){printMissingFunctionError("glMultiTexCoord1bOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord1bvOES(GLenum,const GLbyte*){printMissingFunctionError("glMultiTexCoord1bvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord1dARB(GLenum,GLdouble){printMissingFunctionError("glMultiTexCoord1dARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord1d(GLenum,GLdouble){printMissingFunctionError("glMultiTexCoord1d");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord1dvARB(GLenum,const GLdouble*){printMissingFunctionError("glMultiTexCoord1dvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord1dv(GLenum,const GLdouble*){printMissingFunctionError("glMultiTexCoord1dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord1fARB(GLenum,GLfloat){printMissingFunctionError("glMultiTexCoord1fARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord1f(GLenum,GLfloat){printMissingFunctionError("glMultiTexCoord1f");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord1fvARB(GLenum,const GLfloat*){printMissingFunctionError("glMultiTexCoord1fvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord1fv(GLenum,const GLfloat*){printMissingFunctionError("glMultiTexCoord1fv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord1hNV(GLenum,GLhalfNV){printMissingFunctionError("glMultiTexCoord1hNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord1hvNV(GLenum,const GLhalfNV*){printMissingFunctionError("glMultiTexCoord1hvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord1iARB(GLenum,GLint){printMissingFunctionError("glMultiTexCoord1iARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord1i(GLenum,GLint){printMissingFunctionError("glMultiTexCoord1i");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord1ivARB(GLenum,const GLint*){printMissingFunctionError("glMultiTexCoord1ivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord1iv(GLenum,const GLint*){printMissingFunctionError("glMultiTexCoord1iv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord1sARB(GLenum,GLshort){printMissingFunctionError("glMultiTexCoord1sARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord1s(GLenum,GLshort){printMissingFunctionError("glMultiTexCoord1s");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord1svARB(GLenum,const GLshort*){printMissingFunctionError("glMultiTexCoord1svARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord1sv(GLenum,const GLshort*){printMissingFunctionError("glMultiTexCoord1sv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord1xOES(GLenum,GLfixed){printMissingFunctionError("glMultiTexCoord1xOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord1xvOES(GLenum,const GLfixed*){printMissingFunctionError("glMultiTexCoord1xvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord2bOES(GLenum,GLbyte,GLbyte){printMissingFunctionError("glMultiTexCoord2bOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord2bvOES(GLenum,const GLbyte*){printMissingFunctionError("glMultiTexCoord2bvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord2dARB(GLenum,GLdouble,GLdouble){printMissingFunctionError("glMultiTexCoord2dARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord2d(GLenum,GLdouble,GLdouble){printMissingFunctionError("glMultiTexCoord2d");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord2dvARB(GLenum,const GLdouble*){printMissingFunctionError("glMultiTexCoord2dvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord2dv(GLenum,const GLdouble*){printMissingFunctionError("glMultiTexCoord2dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord2fARB(GLenum,GLfloat,GLfloat){printMissingFunctionError("glMultiTexCoord2fARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord2f(GLenum,GLfloat,GLfloat){printMissingFunctionError("glMultiTexCoord2f");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord2fvARB(GLenum,const GLfloat*){printMissingFunctionError("glMultiTexCoord2fvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord2fv(GLenum,const GLfloat*){printMissingFunctionError("glMultiTexCoord2fv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord2hNV(GLenum,GLhalfNV,GLhalfNV){printMissingFunctionError("glMultiTexCoord2hNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord2hvNV(GLenum,const GLhalfNV*){printMissingFunctionError("glMultiTexCoord2hvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord2iARB(GLenum,GLint,GLint){printMissingFunctionError("glMultiTexCoord2iARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord2i(GLenum,GLint,GLint){printMissingFunctionError("glMultiTexCoord2i");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord2ivARB(GLenum,const GLint*){printMissingFunctionError("glMultiTexCoord2ivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord2iv(GLenum,const GLint*){printMissingFunctionError("glMultiTexCoord2iv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord2sARB(GLenum,GLshort,GLshort){printMissingFunctionError("glMultiTexCoord2sARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord2s(GLenum,GLshort,GLshort){printMissingFunctionError("glMultiTexCoord2s");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord2svARB(GLenum,const GLshort*){printMissingFunctionError("glMultiTexCoord2svARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord2sv(GLenum,const GLshort*){printMissingFunctionError("glMultiTexCoord2sv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord2xOES(GLenum,GLfixed,GLfixed){printMissingFunctionError("glMultiTexCoord2xOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord2xvOES(GLenum,const GLfixed*){printMissingFunctionError("glMultiTexCoord2xvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord3bOES(GLenum,GLbyte,GLbyte,GLbyte){printMissingFunctionError("glMultiTexCoord3bOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord3bvOES(GLenum,const GLbyte*){printMissingFunctionError("glMultiTexCoord3bvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord3dARB(GLenum,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glMultiTexCoord3dARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord3d(GLenum,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glMultiTexCoord3d");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord3dvARB(GLenum,const GLdouble*){printMissingFunctionError("glMultiTexCoord3dvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord3dv(GLenum,const GLdouble*){printMissingFunctionError("glMultiTexCoord3dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord3fARB(GLenum,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glMultiTexCoord3fARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord3f(GLenum,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glMultiTexCoord3f");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord3fvARB(GLenum,const GLfloat*){printMissingFunctionError("glMultiTexCoord3fvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord3fv(GLenum,const GLfloat*){printMissingFunctionError("glMultiTexCoord3fv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord3hNV(GLenum,GLhalfNV,GLhalfNV,GLhalfNV){printMissingFunctionError("glMultiTexCoord3hNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord3hvNV(GLenum,const GLhalfNV*){printMissingFunctionError("glMultiTexCoord3hvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord3iARB(GLenum,GLint,GLint,GLint){printMissingFunctionError("glMultiTexCoord3iARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord3i(GLenum,GLint,GLint,GLint){printMissingFunctionError("glMultiTexCoord3i");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord3ivARB(GLenum,const GLint*){printMissingFunctionError("glMultiTexCoord3ivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord3iv(GLenum,const GLint*){printMissingFunctionError("glMultiTexCoord3iv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord3sARB(GLenum,GLshort,GLshort,GLshort){printMissingFunctionError("glMultiTexCoord3sARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord3s(GLenum,GLshort,GLshort,GLshort){printMissingFunctionError("glMultiTexCoord3s");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord3svARB(GLenum,const GLshort*){printMissingFunctionError("glMultiTexCoord3svARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord3sv(GLenum,const GLshort*){printMissingFunctionError("glMultiTexCoord3sv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord3xOES(GLenum,GLfixed,GLfixed,GLfixed){printMissingFunctionError("glMultiTexCoord3xOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord3xvOES(GLenum,const GLfixed*){printMissingFunctionError("glMultiTexCoord3xvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord4bOES(GLenum,GLbyte,GLbyte,GLbyte,GLbyte){printMissingFunctionError("glMultiTexCoord4bOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord4bvOES(GLenum,const GLbyte*){printMissingFunctionError("glMultiTexCoord4bvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord4dARB(GLenum,GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glMultiTexCoord4dARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord4d(GLenum,GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glMultiTexCoord4d");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord4dvARB(GLenum,const GLdouble*){printMissingFunctionError("glMultiTexCoord4dvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord4dv(GLenum,const GLdouble*){printMissingFunctionError("glMultiTexCoord4dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord4fARB(GLenum,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glMultiTexCoord4fARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord4f(GLenum,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glMultiTexCoord4f");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord4fvARB(GLenum,const GLfloat*){printMissingFunctionError("glMultiTexCoord4fvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord4fv(GLenum,const GLfloat*){printMissingFunctionError("glMultiTexCoord4fv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord4hNV(GLenum,GLhalfNV,GLhalfNV,GLhalfNV,GLhalfNV){printMissingFunctionError("glMultiTexCoord4hNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord4hvNV(GLenum,const GLhalfNV*){printMissingFunctionError("glMultiTexCoord4hvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord4iARB(GLenum,GLint,GLint,GLint,GLint){printMissingFunctionError("glMultiTexCoord4iARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord4i(GLenum,GLint,GLint,GLint,GLint){printMissingFunctionError("glMultiTexCoord4i");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord4ivARB(GLenum,const GLint*){printMissingFunctionError("glMultiTexCoord4ivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord4iv(GLenum,const GLint*){printMissingFunctionError("glMultiTexCoord4iv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord4sARB(GLenum,GLshort,GLshort,GLshort,GLshort){printMissingFunctionError("glMultiTexCoord4sARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord4s(GLenum,GLshort,GLshort,GLshort,GLshort){printMissingFunctionError("glMultiTexCoord4s");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord4svARB(GLenum,const GLshort*){printMissingFunctionError("glMultiTexCoord4svARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord4sv(GLenum,const GLshort*){printMissingFunctionError("glMultiTexCoord4sv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord4xOES(GLenum,GLfixed,GLfixed,GLfixed,GLfixed){printMissingFunctionError("glMultiTexCoord4xOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoord4xvOES(GLenum,const GLfixed*){printMissingFunctionError("glMultiTexCoord4xvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoordP1ui(GLenum,GLenum,GLuint){printMissingFunctionError("glMultiTexCoordP1ui");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoordP1uiv(GLenum,GLenum,const GLuint*){printMissingFunctionError("glMultiTexCoordP1uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoordP2ui(GLenum,GLenum,GLuint){printMissingFunctionError("glMultiTexCoordP2ui");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoordP2uiv(GLenum,GLenum,const GLuint*){printMissingFunctionError("glMultiTexCoordP2uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoordP3ui(GLenum,GLenum,GLuint){printMissingFunctionError("glMultiTexCoordP3ui");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoordP3uiv(GLenum,GLenum,const GLuint*){printMissingFunctionError("glMultiTexCoordP3uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoordP4ui(GLenum,GLenum,GLuint){printMissingFunctionError("glMultiTexCoordP4ui");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoordP4uiv(GLenum,GLenum,const GLuint*){printMissingFunctionError("glMultiTexCoordP4uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexCoordPointerEXT(GLenum,GLint,GLenum,GLsizei,const void*){printMissingFunctionError("glMultiTexCoordPointerEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexEnvfEXT(GLenum,GLenum,GLenum,GLfloat){printMissingFunctionError("glMultiTexEnvfEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexEnvfvEXT(GLenum,GLenum,GLenum,const GLfloat*){printMissingFunctionError("glMultiTexEnvfvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexEnviEXT(GLenum,GLenum,GLenum,GLint){printMissingFunctionError("glMultiTexEnviEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexEnvivEXT(GLenum,GLenum,GLenum,const GLint*){printMissingFunctionError("glMultiTexEnvivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexGendEXT(GLenum,GLenum,GLenum,GLdouble){printMissingFunctionError("glMultiTexGendEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexGendvEXT(GLenum,GLenum,GLenum,const GLdouble*){printMissingFunctionError("glMultiTexGendvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexGenfEXT(GLenum,GLenum,GLenum,GLfloat){printMissingFunctionError("glMultiTexGenfEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexGenfvEXT(GLenum,GLenum,GLenum,const GLfloat*){printMissingFunctionError("glMultiTexGenfvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexGeniEXT(GLenum,GLenum,GLenum,GLint){printMissingFunctionError("glMultiTexGeniEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexGenivEXT(GLenum,GLenum,GLenum,const GLint*){printMissingFunctionError("glMultiTexGenivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexImage1DEXT(GLenum,GLenum,GLint,GLint,GLsizei,GLint,GLenum,GLenum,const void*){printMissingFunctionError("glMultiTexImage1DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexImage2DEXT(GLenum,GLenum,GLint,GLint,GLsizei,GLsizei,GLint,GLenum,GLenum,const void*){printMissingFunctionError("glMultiTexImage2DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexImage3DEXT(GLenum,GLenum,GLint,GLint,GLsizei,GLsizei,GLsizei,GLint,GLenum,GLenum,const void*){printMissingFunctionError("glMultiTexImage3DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexParameterfEXT(GLenum,GLenum,GLenum,GLfloat){printMissingFunctionError("glMultiTexParameterfEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexParameterfvEXT(GLenum,GLenum,GLenum,const GLfloat*){printMissingFunctionError("glMultiTexParameterfvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexParameteriEXT(GLenum,GLenum,GLenum,GLint){printMissingFunctionError("glMultiTexParameteriEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexParameterIivEXT(GLenum,GLenum,GLenum,const GLint*){printMissingFunctionError("glMultiTexParameterIivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexParameterIuivEXT(GLenum,GLenum,GLenum,const GLuint*){printMissingFunctionError("glMultiTexParameterIuivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexParameterivEXT(GLenum,GLenum,GLenum,const GLint*){printMissingFunctionError("glMultiTexParameterivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexRenderbufferEXT(GLenum,GLenum,GLuint){printMissingFunctionError("glMultiTexRenderbufferEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexSubImage1DEXT(GLenum,GLenum,GLint,GLint,GLsizei,GLenum,GLenum,const void*){printMissingFunctionError("glMultiTexSubImage1DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexSubImage2DEXT(GLenum,GLenum,GLint,GLint,GLint,GLsizei,GLsizei,GLenum,GLenum,const void*){printMissingFunctionError("glMultiTexSubImage2DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultiTexSubImage3DEXT(GLenum,GLenum,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLenum,GLenum,const void*){printMissingFunctionError("glMultiTexSubImage3DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultMatrixd(const GLdouble*){printMissingFunctionError("glMultMatrixd");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultMatrixf(const GLfloat*){printMissingFunctionError("glMultMatrixf");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultMatrixxOES(const GLfixed*){printMissingFunctionError("glMultMatrixxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultTransposeMatrixdARB(const GLdouble*){printMissingFunctionError("glMultTransposeMatrixdARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultTransposeMatrixd(const GLdouble){printMissingFunctionError("glMultTransposeMatrixd");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultTransposeMatrixfARB(const GLfloat*){printMissingFunctionError("glMultTransposeMatrixfARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultTransposeMatrixf(const GLfloat){printMissingFunctionError("glMultTransposeMatrixf");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglMultTransposeMatrixxOES(const GLfixed*){printMissingFunctionError("glMultTransposeMatrixxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNamedBufferDataEXT(GLuint,GLsizeiptr,const void*,GLenum){printMissingFunctionError("glNamedBufferDataEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNamedBufferData(GLuint,GLsizeiptr,const void*,GLenum){printMissingFunctionError("glNamedBufferData");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNamedBufferPageCommitmentARB(GLuint,GLintptr,GLsizeiptr,GLboolean){printMissingFunctionError("glNamedBufferPageCommitmentARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNamedBufferPageCommitmentEXT(GLuint,GLintptr,GLsizeiptr,GLboolean){printMissingFunctionError("glNamedBufferPageCommitmentEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNamedBufferStorageEXT(GLuint,GLsizeiptr,const void*,GLbitfield){printMissingFunctionError("glNamedBufferStorageEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNamedBufferStorage(GLuint,GLsizeiptr,const void*,GLbitfield){printMissingFunctionError("glNamedBufferStorage");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNamedBufferSubDataEXT(GLuint,GLintptr,GLsizeiptr,const void*){printMissingFunctionError("glNamedBufferSubDataEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNamedBufferSubData(GLuint,GLintptr,GLsizeiptr,const void*){printMissingFunctionError("glNamedBufferSubData");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNamedCopyBufferSubDataEXT(GLuint,GLuint,GLintptr,GLintptr,GLsizeiptr){printMissingFunctionError("glNamedCopyBufferSubDataEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNamedFramebufferDrawBuffer(GLuint,GLenum){printMissingFunctionError("glNamedFramebufferDrawBuffer");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNamedFramebufferDrawBuffers(GLuint,GLsizei,const GLenum*){printMissingFunctionError("glNamedFramebufferDrawBuffers");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNamedFramebufferParameteriEXT(GLuint,GLenum,GLint){printMissingFunctionError("glNamedFramebufferParameteriEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNamedFramebufferParameteri(GLuint,GLenum,GLint){printMissingFunctionError("glNamedFramebufferParameteri");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNamedFramebufferReadBuffer(GLuint,GLenum){printMissingFunctionError("glNamedFramebufferReadBuffer");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNamedFramebufferRenderbufferEXT(GLuint,GLenum,GLenum,GLuint){printMissingFunctionError("glNamedFramebufferRenderbufferEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNamedFramebufferRenderbuffer(GLuint,GLenum,GLenum,GLuint){printMissingFunctionError("glNamedFramebufferRenderbuffer");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNamedFramebufferSampleLocationsfvARB(GLuint,GLuint,GLsizei,const GLfloat*){printMissingFunctionError("glNamedFramebufferSampleLocationsfvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNamedFramebufferSampleLocationsfvNV(GLuint,GLuint,GLsizei,const GLfloat*){printMissingFunctionError("glNamedFramebufferSampleLocationsfvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNamedFramebufferTexture1DEXT(GLuint,GLenum,GLenum,GLuint,GLint){printMissingFunctionError("glNamedFramebufferTexture1DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNamedFramebufferTexture2DEXT(GLuint,GLenum,GLenum,GLuint,GLint){printMissingFunctionError("glNamedFramebufferTexture2DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNamedFramebufferTexture3DEXT(GLuint,GLenum,GLenum,GLuint,GLint,GLint){printMissingFunctionError("glNamedFramebufferTexture3DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNamedFramebufferTextureEXT(GLuint,GLenum,GLuint,GLint){printMissingFunctionError("glNamedFramebufferTextureEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNamedFramebufferTextureFaceEXT(GLuint,GLenum,GLuint,GLint,GLenum){printMissingFunctionError("glNamedFramebufferTextureFaceEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNamedFramebufferTexture(GLuint,GLenum,GLuint,GLint){printMissingFunctionError("glNamedFramebufferTexture");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNamedFramebufferTextureLayerEXT(GLuint,GLenum,GLuint,GLint,GLint){printMissingFunctionError("glNamedFramebufferTextureLayerEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNamedFramebufferTextureLayer(GLuint,GLenum,GLuint,GLint,GLint){printMissingFunctionError("glNamedFramebufferTextureLayer");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNamedProgramLocalParameter4dEXT(GLuint,GLenum,GLuint,GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glNamedProgramLocalParameter4dEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNamedProgramLocalParameter4dvEXT(GLuint,GLenum,GLuint,const GLdouble*){printMissingFunctionError("glNamedProgramLocalParameter4dvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNamedProgramLocalParameter4fEXT(GLuint,GLenum,GLuint,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glNamedProgramLocalParameter4fEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNamedProgramLocalParameter4fvEXT(GLuint,GLenum,GLuint,const GLfloat*){printMissingFunctionError("glNamedProgramLocalParameter4fvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNamedProgramLocalParameterI4iEXT(GLuint,GLenum,GLuint,GLint,GLint,GLint,GLint){printMissingFunctionError("glNamedProgramLocalParameterI4iEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNamedProgramLocalParameterI4ivEXT(GLuint,GLenum,GLuint,const GLint*){printMissingFunctionError("glNamedProgramLocalParameterI4ivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNamedProgramLocalParameterI4uiEXT(GLuint,GLenum,GLuint,GLuint,GLuint,GLuint,GLuint){printMissingFunctionError("glNamedProgramLocalParameterI4uiEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNamedProgramLocalParameterI4uivEXT(GLuint,GLenum,GLuint,const GLuint*){printMissingFunctionError("glNamedProgramLocalParameterI4uivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNamedProgramLocalParameters4fvEXT(GLuint,GLenum,GLuint,GLsizei,const GLfloat*){printMissingFunctionError("glNamedProgramLocalParameters4fvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNamedProgramLocalParametersI4ivEXT(GLuint,GLenum,GLuint,GLsizei,const GLint*){printMissingFunctionError("glNamedProgramLocalParametersI4ivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNamedProgramLocalParametersI4uivEXT(GLuint,GLenum,GLuint,GLsizei,const GLuint*){printMissingFunctionError("glNamedProgramLocalParametersI4uivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNamedProgramStringEXT(GLuint,GLenum,GLenum,GLsizei,const void*){printMissingFunctionError("glNamedProgramStringEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNamedRenderbufferStorageEXT(GLuint,GLenum,GLsizei,GLsizei){printMissingFunctionError("glNamedRenderbufferStorageEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNamedRenderbufferStorage(GLuint,GLenum,GLsizei,GLsizei){printMissingFunctionError("glNamedRenderbufferStorage");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNamedRenderbufferStorageMultisampleCoverageEXT(GLuint,GLsizei,GLsizei,GLenum,GLsizei,GLsizei){printMissingFunctionError("glNamedRenderbufferStorageMultisampleCoverageEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNamedRenderbufferStorageMultisampleEXT(GLuint,GLsizei,GLenum,GLsizei,GLsizei){printMissingFunctionError("glNamedRenderbufferStorageMultisampleEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNamedRenderbufferStorageMultisample(GLuint,GLsizei,GLenum,GLsizei,GLsizei){printMissingFunctionError("glNamedRenderbufferStorageMultisample");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNamedStringARB(GLenum,GLint,const GLchar*,GLint,const GLchar*){printMissingFunctionError("glNamedStringARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNewList(GLuint,GLenum){printMissingFunctionError("glNewList");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNormal3b(GLbyte,GLbyte,GLbyte){printMissingFunctionError("glNormal3b");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNormal3bv(const GLbyte*){printMissingFunctionError("glNormal3bv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNormal3d(GLdouble,GLdouble,GLdouble){printMissingFunctionError("glNormal3d");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNormal3dv(const GLdouble*){printMissingFunctionError("glNormal3dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNormal3f(GLfloat,GLfloat,GLfloat){printMissingFunctionError("glNormal3f");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNormal3fv(const GLfloat*){printMissingFunctionError("glNormal3fv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNormal3fVertex3fSUN(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glNormal3fVertex3fSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNormal3fVertex3fvSUN(const GLfloat*,const GLfloat*){printMissingFunctionError("glNormal3fVertex3fvSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNormal3hNV(GLhalfNV,GLhalfNV,GLhalfNV){printMissingFunctionError("glNormal3hNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNormal3hvNV(const GLhalfNV*){printMissingFunctionError("glNormal3hvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNormal3i(GLint,GLint,GLint){printMissingFunctionError("glNormal3i");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNormal3iv(const GLint*){printMissingFunctionError("glNormal3iv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNormal3s(GLshort,GLshort,GLshort){printMissingFunctionError("glNormal3s");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNormal3sv(const GLshort*){printMissingFunctionError("glNormal3sv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNormal3xOES(GLfixed,GLfixed,GLfixed){printMissingFunctionError("glNormal3xOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNormal3xvOES(const GLfixed*){printMissingFunctionError("glNormal3xvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNormalFormatNV(GLenum,GLsizei){printMissingFunctionError("glNormalFormatNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNormalP3ui(GLenum,GLuint){printMissingFunctionError("glNormalP3ui");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNormalP3uiv(GLenum,const GLuint*){printMissingFunctionError("glNormalP3uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNormalPointerEXT(GLenum,GLsizei,GLsizei,const void*){printMissingFunctionError("glNormalPointerEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNormalPointer(GLenum,GLsizei,const GLvoid*){printMissingFunctionError("glNormalPointer");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNormalPointerListIBM(GLenum,GLint,const void**,GLint){printMissingFunctionError("glNormalPointerListIBM");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNormalPointervINTEL(GLenum,const void**){printMissingFunctionError("glNormalPointervINTEL");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNormalStream3bATI(GLenum,GLbyte,GLbyte,GLbyte){printMissingFunctionError("glNormalStream3bATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNormalStream3bvATI(GLenum,const GLbyte*){printMissingFunctionError("glNormalStream3bvATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNormalStream3dATI(GLenum,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glNormalStream3dATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNormalStream3dvATI(GLenum,const GLdouble*){printMissingFunctionError("glNormalStream3dvATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNormalStream3fATI(GLenum,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glNormalStream3fATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNormalStream3fvATI(GLenum,const GLfloat*){printMissingFunctionError("glNormalStream3fvATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNormalStream3iATI(GLenum,GLint,GLint,GLint){printMissingFunctionError("glNormalStream3iATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNormalStream3ivATI(GLenum,const GLint*){printMissingFunctionError("glNormalStream3ivATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNormalStream3sATI(GLenum,GLshort,GLshort,GLshort){printMissingFunctionError("glNormalStream3sATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglNormalStream3svATI(GLenum,const GLshort*){printMissingFunctionError("glNormalStream3svATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglObjectLabel(GLenum,GLuint,GLsizei,const GLchar*){printMissingFunctionError("glObjectLabel");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglObjectPtrLabel(const void*,GLsizei,const GLchar*){printMissingFunctionError("glObjectPtrLabel");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglOrthofOES(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glOrthofOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglOrtho(GLdouble,GLdouble,GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glOrtho");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglOrthoxOES(GLfixed,GLfixed,GLfixed,GLfixed,GLfixed,GLfixed){printMissingFunctionError("glOrthoxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPassTexCoordATI(GLuint,GLuint,GLenum){printMissingFunctionError("glPassTexCoordATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPassThrough(GLfloat){printMissingFunctionError("glPassThrough");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPassThroughxOES(GLfixed){printMissingFunctionError("glPassThroughxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPatchParameterfv(GLenum,const GLfloat*){printMissingFunctionError("glPatchParameterfv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPatchParameteri(GLenum,GLint){printMissingFunctionError("glPatchParameteri");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPathColorGenNV(GLenum,GLenum,GLenum,const GLfloat*){printMissingFunctionError("glPathColorGenNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPathCommandsNV(GLuint,GLsizei,const GLubyte*,GLsizei,GLenum,const void*){printMissingFunctionError("glPathCommandsNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPathCoordsNV(GLuint,GLsizei,GLenum,const void*){printMissingFunctionError("glPathCoordsNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPathCoverDepthFuncNV(GLenum){printMissingFunctionError("glPathCoverDepthFuncNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPathDashArrayNV(GLuint,GLsizei,const GLfloat*){printMissingFunctionError("glPathDashArrayNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPathFogGenNV(GLenum){printMissingFunctionError("glPathFogGenNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPathGlyphRangeNV(GLuint,GLenum,const void*,GLbitfield,GLuint,GLsizei,GLenum,GLuint,GLfloat){printMissingFunctionError("glPathGlyphRangeNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPathGlyphsNV(GLuint,GLenum,const void*,GLbitfield,GLsizei,GLenum,const void*,GLenum,GLuint,GLfloat){printMissingFunctionError("glPathGlyphsNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPathParameterfNV(GLuint,GLenum,GLfloat){printMissingFunctionError("glPathParameterfNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPathParameterfvNV(GLuint,GLenum,const GLfloat*){printMissingFunctionError("glPathParameterfvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPathParameteriNV(GLuint,GLenum,GLint){printMissingFunctionError("glPathParameteriNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPathParameterivNV(GLuint,GLenum,const GLint*){printMissingFunctionError("glPathParameterivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPathStencilDepthOffsetNV(GLfloat,GLfloat){printMissingFunctionError("glPathStencilDepthOffsetNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPathStencilFuncNV(GLenum,GLint,GLuint){printMissingFunctionError("glPathStencilFuncNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPathStringNV(GLuint,GLenum,GLsizei,const void*){printMissingFunctionError("glPathStringNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPathSubCommandsNV(GLuint,GLsizei,GLsizei,GLsizei,const GLubyte*,GLsizei,GLenum,const void*){printMissingFunctionError("glPathSubCommandsNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPathSubCoordsNV(GLuint,GLsizei,GLsizei,GLenum,const void*){printMissingFunctionError("glPathSubCoordsNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPathTexGenNV(GLenum,GLenum,GLint,const GLfloat*){printMissingFunctionError("glPathTexGenNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPauseTransformFeedback(){printMissingFunctionError("glPauseTransformFeedback");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPauseTransformFeedbackNV(){printMissingFunctionError("glPauseTransformFeedbackNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPixelDataRangeNV(GLenum,GLsizei,const void*){printMissingFunctionError("glPixelDataRangeNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPixelMapfv(GLenum,GLsizei,const GLfloat*){printMissingFunctionError("glPixelMapfv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPixelMapuiv(GLenum,GLsizei,const GLuint*){printMissingFunctionError("glPixelMapuiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPixelMapusv(GLenum,GLsizei,const GLushort*){printMissingFunctionError("glPixelMapusv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPixelMapx(GLenum,GLint,const GLfixed*){printMissingFunctionError("glPixelMapx");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPixelStoref(GLenum,GLfloat){printMissingFunctionError("glPixelStoref");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPixelStorei(GLenum,GLint){printMissingFunctionError("glPixelStorei");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPixelStorex(GLenum,GLfixed){printMissingFunctionError("glPixelStorex");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPixelTexGenParameterfSGIS(GLenum,GLfloat){printMissingFunctionError("glPixelTexGenParameterfSGIS");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPixelTexGenParameterfvSGIS(GLenum,const GLfloat*){printMissingFunctionError("glPixelTexGenParameterfvSGIS");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPixelTexGenParameteriSGIS(GLenum,GLint){printMissingFunctionError("glPixelTexGenParameteriSGIS");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPixelTexGenParameterivSGIS(GLenum,const GLint*){printMissingFunctionError("glPixelTexGenParameterivSGIS");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPixelTexGenSGIX(GLenum){printMissingFunctionError("glPixelTexGenSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPixelTransferf(GLenum,GLfloat){printMissingFunctionError("glPixelTransferf");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPixelTransferi(GLenum,GLint){printMissingFunctionError("glPixelTransferi");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPixelTransferxOES(GLenum,GLfixed){printMissingFunctionError("glPixelTransferxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPixelTransformParameterfEXT(GLenum,GLenum,GLfloat){printMissingFunctionError("glPixelTransformParameterfEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPixelTransformParameterfvEXT(GLenum,GLenum,const GLfloat*){printMissingFunctionError("glPixelTransformParameterfvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPixelTransformParameteriEXT(GLenum,GLenum,GLint){printMissingFunctionError("glPixelTransformParameteriEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPixelTransformParameterivEXT(GLenum,GLenum,const GLint*){printMissingFunctionError("glPixelTransformParameterivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPixelZoom(GLfloat,GLfloat){printMissingFunctionError("glPixelZoom");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPixelZoomxOES(GLfixed,GLfixed){printMissingFunctionError("glPixelZoomxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPNTrianglesfATI(GLenum,GLfloat){printMissingFunctionError("glPNTrianglesfATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPNTrianglesiATI(GLenum,GLint){printMissingFunctionError("glPNTrianglesiATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPointParameterfARB(GLenum,GLfloat){printMissingFunctionError("glPointParameterfARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPointParameterfEXT(GLenum,GLfloat){printMissingFunctionError("glPointParameterfEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPointParameterf(GLenum,GLfloat){printMissingFunctionError("glPointParameterf");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPointParameterfSGIS(GLenum,GLfloat){printMissingFunctionError("glPointParameterfSGIS");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPointParameterfvARB(GLenum,const GLfloat*){printMissingFunctionError("glPointParameterfvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPointParameterfvEXT(GLenum,const GLfloat*){printMissingFunctionError("glPointParameterfvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPointParameterfv(GLenum,const GLfloat*){printMissingFunctionError("glPointParameterfv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPointParameterfvSGIS(GLenum,const GLfloat*){printMissingFunctionError("glPointParameterfvSGIS");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPointParameteri(GLenum,GLint){printMissingFunctionError("glPointParameteri");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPointParameteriNV(GLenum,GLint){printMissingFunctionError("glPointParameteriNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPointParameteriv(GLenum,const GLint*){printMissingFunctionError("glPointParameteriv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPointParameterivNV(GLenum,const GLint*){printMissingFunctionError("glPointParameterivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPointParameterxvOES(GLenum,const GLfixed*){printMissingFunctionError("glPointParameterxvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPointSize(GLfloat){printMissingFunctionError("glPointSize");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPointSizexOES(GLfixed){printMissingFunctionError("glPointSizexOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPolygonMode(GLenum,GLenum){printMissingFunctionError("glPolygonMode");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPolygonOffsetClampEXT(GLfloat,GLfloat,GLfloat){printMissingFunctionError("glPolygonOffsetClampEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPolygonOffsetEXT(GLfloat,GLfloat){printMissingFunctionError("glPolygonOffsetEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPolygonOffset(GLfloat,GLfloat){printMissingFunctionError("glPolygonOffset");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPolygonOffsetxOES(GLfixed,GLfixed){printMissingFunctionError("glPolygonOffsetxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPolygonStipple(const GLubyte*){printMissingFunctionError("glPolygonStipple");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPopAttrib(){printMissingFunctionError("glPopAttrib");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPopClientAttrib(){printMissingFunctionError("glPopClientAttrib");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPopDebugGroup(){printMissingFunctionError("glPopDebugGroup");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPopGroupMarkerEXT(){printMissingFunctionError("glPopGroupMarkerEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPopMatrix(){printMissingFunctionError("glPopMatrix");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPopName(){printMissingFunctionError("glPopName");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPresentFrameDualFillNV(GLuint,GLuint64EXT,GLuint,GLuint,GLenum,GLenum,GLuint,GLenum,GLuint,GLenum,GLuint,GLenum,GLuint){printMissingFunctionError("glPresentFrameDualFillNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPresentFrameKeyedNV(GLuint,GLuint64EXT,GLuint,GLuint,GLenum,GLenum,GLuint,GLuint,GLenum,GLuint,GLuint){printMissingFunctionError("glPresentFrameKeyedNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPrimitiveBoundingBoxARB(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glPrimitiveBoundingBoxARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPrimitiveRestartIndex(GLuint){printMissingFunctionError("glPrimitiveRestartIndex");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPrimitiveRestartIndexNV(GLuint){printMissingFunctionError("glPrimitiveRestartIndexNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPrimitiveRestartNV(){printMissingFunctionError("glPrimitiveRestartNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPrioritizeTexturesEXT(GLsizei,const GLuint*,const GLclampf*){printMissingFunctionError("glPrioritizeTexturesEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPrioritizeTextures(GLsizei,const GLuint*,const GLclampf*){printMissingFunctionError("glPrioritizeTextures");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPrioritizeTexturesxOES(GLsizei,const GLuint*,const GLfixed*){printMissingFunctionError("glPrioritizeTexturesxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramBinary(GLuint,GLenum,const void*,GLsizei){printMissingFunctionError("glProgramBinary");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramBufferParametersfvNV(GLenum,GLuint,GLuint,GLsizei,const GLfloat*){printMissingFunctionError("glProgramBufferParametersfvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramBufferParametersIivNV(GLenum,GLuint,GLuint,GLsizei,const GLint*){printMissingFunctionError("glProgramBufferParametersIivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramBufferParametersIuivNV(GLenum,GLuint,GLuint,GLsizei,const GLuint*){printMissingFunctionError("glProgramBufferParametersIuivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramEnvParameter4dARB(GLenum,GLuint,GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glProgramEnvParameter4dARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramEnvParameter4dvARB(GLenum,GLuint,const GLdouble*){printMissingFunctionError("glProgramEnvParameter4dvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramEnvParameter4fARB(GLenum,GLuint,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glProgramEnvParameter4fARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramEnvParameter4fvARB(GLenum,GLuint,const GLfloat*){printMissingFunctionError("glProgramEnvParameter4fvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramEnvParameterI4iNV(GLenum,GLuint,GLint,GLint,GLint,GLint){printMissingFunctionError("glProgramEnvParameterI4iNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramEnvParameterI4ivNV(GLenum,GLuint,const GLint*){printMissingFunctionError("glProgramEnvParameterI4ivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramEnvParameterI4uiNV(GLenum,GLuint,GLuint,GLuint,GLuint,GLuint){printMissingFunctionError("glProgramEnvParameterI4uiNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramEnvParameterI4uivNV(GLenum,GLuint,const GLuint*){printMissingFunctionError("glProgramEnvParameterI4uivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramEnvParameters4fvEXT(GLenum,GLuint,GLsizei,const GLfloat*){printMissingFunctionError("glProgramEnvParameters4fvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramEnvParametersI4ivNV(GLenum,GLuint,GLsizei,const GLint*){printMissingFunctionError("glProgramEnvParametersI4ivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramEnvParametersI4uivNV(GLenum,GLuint,GLsizei,const GLuint*){printMissingFunctionError("glProgramEnvParametersI4uivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramLocalParameter4dARB(GLenum,GLuint,GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glProgramLocalParameter4dARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramLocalParameter4dvARB(GLenum,GLuint,const GLdouble*){printMissingFunctionError("glProgramLocalParameter4dvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramLocalParameter4fARB(GLenum,GLuint,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glProgramLocalParameter4fARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramLocalParameter4fvARB(GLenum,GLuint,const GLfloat*){printMissingFunctionError("glProgramLocalParameter4fvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramLocalParameterI4iNV(GLenum,GLuint,GLint,GLint,GLint,GLint){printMissingFunctionError("glProgramLocalParameterI4iNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramLocalParameterI4ivNV(GLenum,GLuint,const GLint*){printMissingFunctionError("glProgramLocalParameterI4ivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramLocalParameterI4uiNV(GLenum,GLuint,GLuint,GLuint,GLuint,GLuint){printMissingFunctionError("glProgramLocalParameterI4uiNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramLocalParameterI4uivNV(GLenum,GLuint,const GLuint*){printMissingFunctionError("glProgramLocalParameterI4uivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramLocalParameters4fvEXT(GLenum,GLuint,GLsizei,const GLfloat*){printMissingFunctionError("glProgramLocalParameters4fvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramLocalParametersI4ivNV(GLenum,GLuint,GLsizei,const GLint*){printMissingFunctionError("glProgramLocalParametersI4ivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramLocalParametersI4uivNV(GLenum,GLuint,GLsizei,const GLuint*){printMissingFunctionError("glProgramLocalParametersI4uivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramNamedParameter4dNV(GLuint,GLsizei,const GLubyte*,GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glProgramNamedParameter4dNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramNamedParameter4dvNV(GLuint,GLsizei,const GLubyte*,const GLdouble*){printMissingFunctionError("glProgramNamedParameter4dvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramNamedParameter4fNV(GLuint,GLsizei,const GLubyte*,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glProgramNamedParameter4fNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramNamedParameter4fvNV(GLuint,GLsizei,const GLubyte*,const GLfloat*){printMissingFunctionError("glProgramNamedParameter4fvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramParameter4dNV(GLenum,GLuint,GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glProgramParameter4dNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramParameter4dvNV(GLenum,GLuint,const GLdouble*){printMissingFunctionError("glProgramParameter4dvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramParameter4fNV(GLenum,GLuint,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glProgramParameter4fNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramParameter4fvNV(GLenum,GLuint,const GLfloat*){printMissingFunctionError("glProgramParameter4fvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramParameteriARB(GLuint,GLenum,GLint){printMissingFunctionError("glProgramParameteriARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramParameteriEXT(GLuint,GLenum,GLint){printMissingFunctionError("glProgramParameteriEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramParameteri(GLuint,GLenum,GLint){printMissingFunctionError("glProgramParameteri");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramParameters4dvNV(GLenum,GLuint,GLsizei,const GLdouble*){printMissingFunctionError("glProgramParameters4dvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramParameters4fvNV(GLenum,GLuint,GLsizei,const GLfloat*){printMissingFunctionError("glProgramParameters4fvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramPathFragmentInputGenNV(GLuint,GLint,GLenum,GLint,const GLfloat*){printMissingFunctionError("glProgramPathFragmentInputGenNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramStringARB(GLenum,GLenum,GLsizei,const void*){printMissingFunctionError("glProgramStringARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramSubroutineParametersuivNV(GLenum,GLsizei,const GLuint*){printMissingFunctionError("glProgramSubroutineParametersuivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform1dEXT(GLuint,GLint,GLdouble){printMissingFunctionError("glProgramUniform1dEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform1d(GLuint,GLint,GLdouble){printMissingFunctionError("glProgramUniform1d");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform1dvEXT(GLuint,GLint,GLsizei,const GLdouble*){printMissingFunctionError("glProgramUniform1dvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform1dv(GLuint,GLint,GLsizei,const GLdouble*){printMissingFunctionError("glProgramUniform1dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform1fEXT(GLuint,GLint,GLfloat){printMissingFunctionError("glProgramUniform1fEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform1f(GLuint,GLint,GLfloat){printMissingFunctionError("glProgramUniform1f");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform1fvEXT(GLuint,GLint,GLsizei,const GLfloat*){printMissingFunctionError("glProgramUniform1fvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform1fv(GLuint,GLint,GLsizei,const GLfloat*){printMissingFunctionError("glProgramUniform1fv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform1i64ARB(GLuint,GLint,GLint64){printMissingFunctionError("glProgramUniform1i64ARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform1i64NV(GLuint,GLint,GLint64EXT){printMissingFunctionError("glProgramUniform1i64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform1i64vARB(GLuint,GLint,GLsizei,const GLint64*){printMissingFunctionError("glProgramUniform1i64vARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform1i64vNV(GLuint,GLint,GLsizei,const GLint64EXT*){printMissingFunctionError("glProgramUniform1i64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform1iEXT(GLuint,GLint,GLint){printMissingFunctionError("glProgramUniform1iEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform1i(GLuint,GLint,GLint){printMissingFunctionError("glProgramUniform1i");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform1ivEXT(GLuint,GLint,GLsizei,const GLint*){printMissingFunctionError("glProgramUniform1ivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform1iv(GLuint,GLint,GLsizei,const GLint*){printMissingFunctionError("glProgramUniform1iv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform1ui64ARB(GLuint,GLint,GLuint64){printMissingFunctionError("glProgramUniform1ui64ARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform1ui64NV(GLuint,GLint,GLuint64EXT){printMissingFunctionError("glProgramUniform1ui64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform1ui64vARB(GLuint,GLint,GLsizei,const GLuint64*){printMissingFunctionError("glProgramUniform1ui64vARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform1ui64vNV(GLuint,GLint,GLsizei,const GLuint64EXT*){printMissingFunctionError("glProgramUniform1ui64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform1uiEXT(GLuint,GLint,GLuint){printMissingFunctionError("glProgramUniform1uiEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform1ui(GLuint,GLint,GLuint){printMissingFunctionError("glProgramUniform1ui");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform1uivEXT(GLuint,GLint,GLsizei,const GLuint*){printMissingFunctionError("glProgramUniform1uivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform1uiv(GLuint,GLint,GLsizei,const GLuint*){printMissingFunctionError("glProgramUniform1uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform2dEXT(GLuint,GLint,GLdouble,GLdouble){printMissingFunctionError("glProgramUniform2dEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform2d(GLuint,GLint,GLdouble,GLdouble){printMissingFunctionError("glProgramUniform2d");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform2dvEXT(GLuint,GLint,GLsizei,const GLdouble*){printMissingFunctionError("glProgramUniform2dvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform2dv(GLuint,GLint,GLsizei,const GLdouble*){printMissingFunctionError("glProgramUniform2dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform2fEXT(GLuint,GLint,GLfloat,GLfloat){printMissingFunctionError("glProgramUniform2fEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform2f(GLuint,GLint,GLfloat,GLfloat){printMissingFunctionError("glProgramUniform2f");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform2fvEXT(GLuint,GLint,GLsizei,const GLfloat*){printMissingFunctionError("glProgramUniform2fvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform2fv(GLuint,GLint,GLsizei,const GLfloat*){printMissingFunctionError("glProgramUniform2fv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform2i64ARB(GLuint,GLint,GLint64,GLint64){printMissingFunctionError("glProgramUniform2i64ARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform2i64NV(GLuint,GLint,GLint64EXT,GLint64EXT){printMissingFunctionError("glProgramUniform2i64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform2i64vARB(GLuint,GLint,GLsizei,const GLint64*){printMissingFunctionError("glProgramUniform2i64vARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform2i64vNV(GLuint,GLint,GLsizei,const GLint64EXT*){printMissingFunctionError("glProgramUniform2i64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform2iEXT(GLuint,GLint,GLint,GLint){printMissingFunctionError("glProgramUniform2iEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform2i(GLuint,GLint,GLint,GLint){printMissingFunctionError("glProgramUniform2i");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform2ivEXT(GLuint,GLint,GLsizei,const GLint*){printMissingFunctionError("glProgramUniform2ivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform2iv(GLuint,GLint,GLsizei,const GLint*){printMissingFunctionError("glProgramUniform2iv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform2ui64ARB(GLuint,GLint,GLuint64,GLuint64){printMissingFunctionError("glProgramUniform2ui64ARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform2ui64NV(GLuint,GLint,GLuint64EXT,GLuint64EXT){printMissingFunctionError("glProgramUniform2ui64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform2ui64vARB(GLuint,GLint,GLsizei,const GLuint64*){printMissingFunctionError("glProgramUniform2ui64vARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform2ui64vNV(GLuint,GLint,GLsizei,const GLuint64EXT*){printMissingFunctionError("glProgramUniform2ui64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform2uiEXT(GLuint,GLint,GLuint,GLuint){printMissingFunctionError("glProgramUniform2uiEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform2ui(GLuint,GLint,GLuint,GLuint){printMissingFunctionError("glProgramUniform2ui");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform2uivEXT(GLuint,GLint,GLsizei,const GLuint*){printMissingFunctionError("glProgramUniform2uivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform2uiv(GLuint,GLint,GLsizei,const GLuint*){printMissingFunctionError("glProgramUniform2uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform3dEXT(GLuint,GLint,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glProgramUniform3dEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform3d(GLuint,GLint,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glProgramUniform3d");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform3dvEXT(GLuint,GLint,GLsizei,const GLdouble*){printMissingFunctionError("glProgramUniform3dvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform3dv(GLuint,GLint,GLsizei,const GLdouble*){printMissingFunctionError("glProgramUniform3dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform3fEXT(GLuint,GLint,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glProgramUniform3fEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform3f(GLuint,GLint,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glProgramUniform3f");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform3fvEXT(GLuint,GLint,GLsizei,const GLfloat*){printMissingFunctionError("glProgramUniform3fvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform3fv(GLuint,GLint,GLsizei,const GLfloat*){printMissingFunctionError("glProgramUniform3fv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform3i64ARB(GLuint,GLint,GLint64,GLint64,GLint64){printMissingFunctionError("glProgramUniform3i64ARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform3i64NV(GLuint,GLint,GLint64EXT,GLint64EXT,GLint64EXT){printMissingFunctionError("glProgramUniform3i64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform3i64vARB(GLuint,GLint,GLsizei,const GLint64*){printMissingFunctionError("glProgramUniform3i64vARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform3i64vNV(GLuint,GLint,GLsizei,const GLint64EXT*){printMissingFunctionError("glProgramUniform3i64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform3iEXT(GLuint,GLint,GLint,GLint,GLint){printMissingFunctionError("glProgramUniform3iEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform3i(GLuint,GLint,GLint,GLint,GLint){printMissingFunctionError("glProgramUniform3i");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform3ivEXT(GLuint,GLint,GLsizei,const GLint*){printMissingFunctionError("glProgramUniform3ivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform3iv(GLuint,GLint,GLsizei,const GLint*){printMissingFunctionError("glProgramUniform3iv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform3ui64ARB(GLuint,GLint,GLuint64,GLuint64,GLuint64){printMissingFunctionError("glProgramUniform3ui64ARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform3ui64NV(GLuint,GLint,GLuint64EXT,GLuint64EXT,GLuint64EXT){printMissingFunctionError("glProgramUniform3ui64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform3ui64vARB(GLuint,GLint,GLsizei,const GLuint64*){printMissingFunctionError("glProgramUniform3ui64vARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform3ui64vNV(GLuint,GLint,GLsizei,const GLuint64EXT*){printMissingFunctionError("glProgramUniform3ui64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform3uiEXT(GLuint,GLint,GLuint,GLuint,GLuint){printMissingFunctionError("glProgramUniform3uiEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform3ui(GLuint,GLint,GLuint,GLuint,GLuint){printMissingFunctionError("glProgramUniform3ui");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform3uivEXT(GLuint,GLint,GLsizei,const GLuint*){printMissingFunctionError("glProgramUniform3uivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform3uiv(GLuint,GLint,GLsizei,const GLuint*){printMissingFunctionError("glProgramUniform3uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform4dEXT(GLuint,GLint,GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glProgramUniform4dEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform4d(GLuint,GLint,GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glProgramUniform4d");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform4dvEXT(GLuint,GLint,GLsizei,const GLdouble*){printMissingFunctionError("glProgramUniform4dvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform4dv(GLuint,GLint,GLsizei,const GLdouble*){printMissingFunctionError("glProgramUniform4dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform4fEXT(GLuint,GLint,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glProgramUniform4fEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform4f(GLuint,GLint,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glProgramUniform4f");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform4fvEXT(GLuint,GLint,GLsizei,const GLfloat*){printMissingFunctionError("glProgramUniform4fvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform4fv(GLuint,GLint,GLsizei,const GLfloat*){printMissingFunctionError("glProgramUniform4fv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform4i64ARB(GLuint,GLint,GLint64,GLint64,GLint64,GLint64){printMissingFunctionError("glProgramUniform4i64ARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform4i64NV(GLuint,GLint,GLint64EXT,GLint64EXT,GLint64EXT,GLint64EXT){printMissingFunctionError("glProgramUniform4i64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform4i64vARB(GLuint,GLint,GLsizei,const GLint64*){printMissingFunctionError("glProgramUniform4i64vARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform4i64vNV(GLuint,GLint,GLsizei,const GLint64EXT*){printMissingFunctionError("glProgramUniform4i64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform4iEXT(GLuint,GLint,GLint,GLint,GLint,GLint){printMissingFunctionError("glProgramUniform4iEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform4i(GLuint,GLint,GLint,GLint,GLint,GLint){printMissingFunctionError("glProgramUniform4i");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform4ivEXT(GLuint,GLint,GLsizei,const GLint*){printMissingFunctionError("glProgramUniform4ivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform4iv(GLuint,GLint,GLsizei,const GLint*){printMissingFunctionError("glProgramUniform4iv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform4ui64ARB(GLuint,GLint,GLuint64,GLuint64,GLuint64,GLuint64){printMissingFunctionError("glProgramUniform4ui64ARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform4ui64NV(GLuint,GLint,GLuint64EXT,GLuint64EXT,GLuint64EXT,GLuint64EXT){printMissingFunctionError("glProgramUniform4ui64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform4ui64vARB(GLuint,GLint,GLsizei,const GLuint64*){printMissingFunctionError("glProgramUniform4ui64vARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform4ui64vNV(GLuint,GLint,GLsizei,const GLuint64EXT*){printMissingFunctionError("glProgramUniform4ui64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform4uiEXT(GLuint,GLint,GLuint,GLuint,GLuint,GLuint){printMissingFunctionError("glProgramUniform4uiEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform4ui(GLuint,GLint,GLuint,GLuint,GLuint,GLuint){printMissingFunctionError("glProgramUniform4ui");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform4uivEXT(GLuint,GLint,GLsizei,const GLuint*){printMissingFunctionError("glProgramUniform4uivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniform4uiv(GLuint,GLint,GLsizei,const GLuint*){printMissingFunctionError("glProgramUniform4uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniformHandleui64ARB(GLuint,GLint,GLuint64){printMissingFunctionError("glProgramUniformHandleui64ARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniformHandleui64NV(GLuint,GLint,GLuint64){printMissingFunctionError("glProgramUniformHandleui64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniformHandleui64vARB(GLuint,GLint,GLsizei,const GLuint64*){printMissingFunctionError("glProgramUniformHandleui64vARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniformHandleui64vNV(GLuint,GLint,GLsizei,const GLuint64*){printMissingFunctionError("glProgramUniformHandleui64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniformMatrix2dvEXT(GLuint,GLint,GLsizei,GLboolean,const GLdouble*){printMissingFunctionError("glProgramUniformMatrix2dvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniformMatrix2dv(GLuint,GLint,GLsizei,GLboolean,const GLdouble*){printMissingFunctionError("glProgramUniformMatrix2dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniformMatrix2fvEXT(GLuint,GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glProgramUniformMatrix2fvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniformMatrix2fv(GLuint,GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glProgramUniformMatrix2fv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniformMatrix2x3dvEXT(GLuint,GLint,GLsizei,GLboolean,const GLdouble*){printMissingFunctionError("glProgramUniformMatrix2x3dvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniformMatrix2x3dv(GLuint,GLint,GLsizei,GLboolean,const GLdouble*){printMissingFunctionError("glProgramUniformMatrix2x3dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniformMatrix2x3fvEXT(GLuint,GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glProgramUniformMatrix2x3fvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniformMatrix2x3fv(GLuint,GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glProgramUniformMatrix2x3fv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniformMatrix2x4dvEXT(GLuint,GLint,GLsizei,GLboolean,const GLdouble*){printMissingFunctionError("glProgramUniformMatrix2x4dvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniformMatrix2x4dv(GLuint,GLint,GLsizei,GLboolean,const GLdouble*){printMissingFunctionError("glProgramUniformMatrix2x4dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniformMatrix2x4fvEXT(GLuint,GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glProgramUniformMatrix2x4fvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniformMatrix2x4fv(GLuint,GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glProgramUniformMatrix2x4fv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniformMatrix3dvEXT(GLuint,GLint,GLsizei,GLboolean,const GLdouble*){printMissingFunctionError("glProgramUniformMatrix3dvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniformMatrix3dv(GLuint,GLint,GLsizei,GLboolean,const GLdouble*){printMissingFunctionError("glProgramUniformMatrix3dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniformMatrix3fvEXT(GLuint,GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glProgramUniformMatrix3fvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniformMatrix3fv(GLuint,GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glProgramUniformMatrix3fv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniformMatrix3x2dvEXT(GLuint,GLint,GLsizei,GLboolean,const GLdouble*){printMissingFunctionError("glProgramUniformMatrix3x2dvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniformMatrix3x2dv(GLuint,GLint,GLsizei,GLboolean,const GLdouble*){printMissingFunctionError("glProgramUniformMatrix3x2dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniformMatrix3x2fvEXT(GLuint,GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glProgramUniformMatrix3x2fvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniformMatrix3x2fv(GLuint,GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glProgramUniformMatrix3x2fv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniformMatrix3x4dvEXT(GLuint,GLint,GLsizei,GLboolean,const GLdouble*){printMissingFunctionError("glProgramUniformMatrix3x4dvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniformMatrix3x4dv(GLuint,GLint,GLsizei,GLboolean,const GLdouble*){printMissingFunctionError("glProgramUniformMatrix3x4dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniformMatrix3x4fvEXT(GLuint,GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glProgramUniformMatrix3x4fvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniformMatrix3x4fv(GLuint,GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glProgramUniformMatrix3x4fv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniformMatrix4dvEXT(GLuint,GLint,GLsizei,GLboolean,const GLdouble*){printMissingFunctionError("glProgramUniformMatrix4dvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniformMatrix4dv(GLuint,GLint,GLsizei,GLboolean,const GLdouble*){printMissingFunctionError("glProgramUniformMatrix4dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniformMatrix4fvEXT(GLuint,GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glProgramUniformMatrix4fvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniformMatrix4fv(GLuint,GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glProgramUniformMatrix4fv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniformMatrix4x2dvEXT(GLuint,GLint,GLsizei,GLboolean,const GLdouble*){printMissingFunctionError("glProgramUniformMatrix4x2dvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniformMatrix4x2dv(GLuint,GLint,GLsizei,GLboolean,const GLdouble*){printMissingFunctionError("glProgramUniformMatrix4x2dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniformMatrix4x2fvEXT(GLuint,GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glProgramUniformMatrix4x2fvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniformMatrix4x2fv(GLuint,GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glProgramUniformMatrix4x2fv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniformMatrix4x3dvEXT(GLuint,GLint,GLsizei,GLboolean,const GLdouble*){printMissingFunctionError("glProgramUniformMatrix4x3dvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniformMatrix4x3dv(GLuint,GLint,GLsizei,GLboolean,const GLdouble*){printMissingFunctionError("glProgramUniformMatrix4x3dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniformMatrix4x3fvEXT(GLuint,GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glProgramUniformMatrix4x3fvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniformMatrix4x3fv(GLuint,GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glProgramUniformMatrix4x3fv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniformui64NV(GLuint,GLint,GLuint64EXT){printMissingFunctionError("glProgramUniformui64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramUniformui64vNV(GLuint,GLint,GLsizei,const GLuint64EXT*){printMissingFunctionError("glProgramUniformui64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProgramVertexLimitNV(GLenum,GLint){printMissingFunctionError("glProgramVertexLimitNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProvokingVertexEXT(GLenum){printMissingFunctionError("glProvokingVertexEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglProvokingVertex(GLenum){printMissingFunctionError("glProvokingVertex");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPushAttrib(GLbitfield){printMissingFunctionError("glPushAttrib");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPushClientAttribDefaultEXT(GLbitfield){printMissingFunctionError("glPushClientAttribDefaultEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPushClientAttrib(GLbitfield){printMissingFunctionError("glPushClientAttrib");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPushDebugGroup(GLenum,GLuint,GLsizei,const GLchar*){printMissingFunctionError("glPushDebugGroup");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPushGroupMarkerEXT(GLsizei,const GLchar*){printMissingFunctionError("glPushGroupMarkerEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPushMatrix(){printMissingFunctionError("glPushMatrix");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglPushName(GLuint){printMissingFunctionError("glPushName");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglQueryCounter(GLuint,GLenum){printMissingFunctionError("glQueryCounter");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglQueryObjectParameteruiAMD(GLenum,GLuint,GLenum,GLuint){printMissingFunctionError("glQueryObjectParameteruiAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglRasterPos2d(GLdouble,GLdouble){printMissingFunctionError("glRasterPos2d");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglRasterPos2dv(const GLdouble*){printMissingFunctionError("glRasterPos2dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglRasterPos2f(GLfloat,GLfloat){printMissingFunctionError("glRasterPos2f");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglRasterPos2fv(const GLfloat*){printMissingFunctionError("glRasterPos2fv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglRasterPos2i(GLint,GLint){printMissingFunctionError("glRasterPos2i");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglRasterPos2iv(const GLint*){printMissingFunctionError("glRasterPos2iv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglRasterPos2s(GLshort,GLshort){printMissingFunctionError("glRasterPos2s");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglRasterPos2sv(const GLshort*){printMissingFunctionError("glRasterPos2sv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglRasterPos2xOES(GLfixed,GLfixed){printMissingFunctionError("glRasterPos2xOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglRasterPos2xvOES(const GLfixed*){printMissingFunctionError("glRasterPos2xvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglRasterPos3d(GLdouble,GLdouble,GLdouble){printMissingFunctionError("glRasterPos3d");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglRasterPos3dv(const GLdouble*){printMissingFunctionError("glRasterPos3dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglRasterPos3f(GLfloat,GLfloat,GLfloat){printMissingFunctionError("glRasterPos3f");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglRasterPos3fv(const GLfloat*){printMissingFunctionError("glRasterPos3fv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglRasterPos3i(GLint,GLint,GLint){printMissingFunctionError("glRasterPos3i");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglRasterPos3iv(const GLint*){printMissingFunctionError("glRasterPos3iv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglRasterPos3s(GLshort,GLshort,GLshort){printMissingFunctionError("glRasterPos3s");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglRasterPos3sv(const GLshort*){printMissingFunctionError("glRasterPos3sv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglRasterPos3xOES(GLfixed,GLfixed,GLfixed){printMissingFunctionError("glRasterPos3xOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglRasterPos3xvOES(const GLfixed*){printMissingFunctionError("glRasterPos3xvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglRasterPos4d(GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glRasterPos4d");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglRasterPos4dv(const GLdouble*){printMissingFunctionError("glRasterPos4dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglRasterPos4f(GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glRasterPos4f");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglRasterPos4fv(const GLfloat*){printMissingFunctionError("glRasterPos4fv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglRasterPos4i(GLint,GLint,GLint,GLint){printMissingFunctionError("glRasterPos4i");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglRasterPos4iv(const GLint*){printMissingFunctionError("glRasterPos4iv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglRasterPos4s(GLshort,GLshort,GLshort,GLshort){printMissingFunctionError("glRasterPos4s");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglRasterPos4sv(const GLshort*){printMissingFunctionError("glRasterPos4sv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglRasterPos4xOES(GLfixed,GLfixed,GLfixed,GLfixed){printMissingFunctionError("glRasterPos4xOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglRasterPos4xvOES(const GLfixed*){printMissingFunctionError("glRasterPos4xvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglRasterSamplesEXT(GLuint,GLboolean){printMissingFunctionError("glRasterSamplesEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglReadBuffer(GLenum){printMissingFunctionError("glReadBuffer");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglReadInstrumentsSGIX(GLint){printMissingFunctionError("glReadInstrumentsSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglReadnPixelsARB(GLint,GLint,GLsizei,GLsizei,GLenum,GLenum,GLsizei,void*){printMissingFunctionError("glReadnPixelsARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglReadnPixels(GLint,GLint,GLsizei,GLsizei,GLenum,GLenum,GLsizei,void*){printMissingFunctionError("glReadnPixels");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglReadPixels(GLint,GLint,GLsizei,GLsizei,GLenum,GLenum,GLvoid*){printMissingFunctionError("glReadPixels");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglRectd(GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glRectd");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglRectdv(const GLdouble*,const GLdouble*){printMissingFunctionError("glRectdv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglRectf(GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glRectf");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglRectfv(const GLfloat*,const GLfloat*){printMissingFunctionError("glRectfv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglRecti(GLint,GLint,GLint,GLint){printMissingFunctionError("glRecti");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglRectiv(const GLint*,const GLint*){printMissingFunctionError("glRectiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglRects(GLshort,GLshort,GLshort,GLshort){printMissingFunctionError("glRects");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglRectsv(const GLshort*,const GLshort*){printMissingFunctionError("glRectsv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglRectxOES(GLfixed,GLfixed,GLfixed,GLfixed){printMissingFunctionError("glRectxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglRectxvOES(const GLfixed*,const GLfixed*){printMissingFunctionError("glRectxvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglReferencePlaneSGIX(const GLdouble*){printMissingFunctionError("glReferencePlaneSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglReleaseShaderCompiler(){printMissingFunctionError("glReleaseShaderCompiler");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglRenderbufferStorageEXT(GLenum,GLenum,GLsizei,GLsizei){printMissingFunctionError("glRenderbufferStorageEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglRenderbufferStorage(GLenum,GLenum,GLsizei,GLsizei){printMissingFunctionError("glRenderbufferStorage");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglRenderbufferStorageMultisampleCoverageNV(GLenum,GLsizei,GLsizei,GLenum,GLsizei,GLsizei){printMissingFunctionError("glRenderbufferStorageMultisampleCoverageNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglRenderbufferStorageMultisampleEXT(GLenum,GLsizei,GLenum,GLsizei,GLsizei){printMissingFunctionError("glRenderbufferStorageMultisampleEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglRenderbufferStorageMultisample(GLenum,GLsizei,GLenum,GLsizei,GLsizei){printMissingFunctionError("glRenderbufferStorageMultisample");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglReplacementCodePointerSUN(GLenum,GLsizei,const void**){printMissingFunctionError("glReplacementCodePointerSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglReplacementCodeubSUN(GLubyte){printMissingFunctionError("glReplacementCodeubSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglReplacementCodeubvSUN(const GLubyte*){printMissingFunctionError("glReplacementCodeubvSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglReplacementCodeuiColor3fVertex3fSUN(GLuint,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glReplacementCodeuiColor3fVertex3fSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglReplacementCodeuiColor3fVertex3fvSUN(const GLuint*,const GLfloat*,const GLfloat*){printMissingFunctionError("glReplacementCodeuiColor3fVertex3fvSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglReplacementCodeuiColor4fNormal3fVertex3fSUN(GLuint,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glReplacementCodeuiColor4fNormal3fVertex3fSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglReplacementCodeuiColor4fNormal3fVertex3fvSUN(const GLuint*,const GLfloat*,const GLfloat*,const GLfloat*){printMissingFunctionError("glReplacementCodeuiColor4fNormal3fVertex3fvSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglReplacementCodeuiColor4ubVertex3fSUN(GLuint,GLubyte,GLubyte,GLubyte,GLubyte,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glReplacementCodeuiColor4ubVertex3fSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglReplacementCodeuiColor4ubVertex3fvSUN(const GLuint*,const GLubyte*,const GLfloat*){printMissingFunctionError("glReplacementCodeuiColor4ubVertex3fvSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglReplacementCodeuiNormal3fVertex3fSUN(GLuint,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glReplacementCodeuiNormal3fVertex3fSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglReplacementCodeuiNormal3fVertex3fvSUN(const GLuint*,const GLfloat*,const GLfloat*){printMissingFunctionError("glReplacementCodeuiNormal3fVertex3fvSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglReplacementCodeuiSUN(GLuint){printMissingFunctionError("glReplacementCodeuiSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN(GLuint,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN(const GLuint*,const GLfloat*,const GLfloat*,const GLfloat*,const GLfloat*){printMissingFunctionError("glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglReplacementCodeuiTexCoord2fNormal3fVertex3fSUN(GLuint,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN(const GLuint*,const GLfloat*,const GLfloat*,const GLfloat*){printMissingFunctionError("glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglReplacementCodeuiTexCoord2fVertex3fSUN(GLuint,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glReplacementCodeuiTexCoord2fVertex3fSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglReplacementCodeuiTexCoord2fVertex3fvSUN(const GLuint*,const GLfloat*,const GLfloat*){printMissingFunctionError("glReplacementCodeuiTexCoord2fVertex3fvSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglReplacementCodeuiVertex3fSUN(GLuint,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glReplacementCodeuiVertex3fSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglReplacementCodeuiVertex3fvSUN(const GLuint*,const GLfloat*){printMissingFunctionError("glReplacementCodeuiVertex3fvSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglReplacementCodeuivSUN(const GLuint*){printMissingFunctionError("glReplacementCodeuivSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglReplacementCodeusSUN(GLushort){printMissingFunctionError("glReplacementCodeusSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglReplacementCodeusvSUN(const GLushort*){printMissingFunctionError("glReplacementCodeusvSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglRequestResidentProgramsNV(GLsizei,const GLuint*){printMissingFunctionError("glRequestResidentProgramsNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglResetHistogramEXT(GLenum){printMissingFunctionError("glResetHistogramEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglResetHistogram(GLenum){printMissingFunctionError("glResetHistogram");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglResetMinmaxEXT(GLenum){printMissingFunctionError("glResetMinmaxEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglResetMinmax(GLenum){printMissingFunctionError("glResetMinmax");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglResizeBuffersMESA(){printMissingFunctionError("glResizeBuffersMESA");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglResolveDepthValuesNV(){printMissingFunctionError("glResolveDepthValuesNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglResumeTransformFeedback(){printMissingFunctionError("glResumeTransformFeedback");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglResumeTransformFeedbackNV(){printMissingFunctionError("glResumeTransformFeedbackNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglRotated(GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glRotated");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglRotatef(GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glRotatef");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglRotatexOES(GLfixed,GLfixed,GLfixed,GLfixed){printMissingFunctionError("glRotatexOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSampleCoverageARB(GLfloat,GLboolean){printMissingFunctionError("glSampleCoverageARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSampleCoverage(GLclampf,GLboolean){printMissingFunctionError("glSampleCoverage");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSampleMapATI(GLuint,GLuint,GLenum){printMissingFunctionError("glSampleMapATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSampleMaskEXT(GLclampf,GLboolean){printMissingFunctionError("glSampleMaskEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSampleMaski(GLuint,GLbitfield){printMissingFunctionError("glSampleMaski");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSampleMaskIndexedNV(GLuint,GLbitfield){printMissingFunctionError("glSampleMaskIndexedNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSampleMaskSGIS(GLclampf,GLboolean){printMissingFunctionError("glSampleMaskSGIS");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSamplePatternEXT(GLenum){printMissingFunctionError("glSamplePatternEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSamplePatternSGIS(GLenum){printMissingFunctionError("glSamplePatternSGIS");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSamplerParameterf(GLuint,GLenum,GLfloat){printMissingFunctionError("glSamplerParameterf");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSamplerParameterfv(GLuint,GLenum,const GLfloat*){printMissingFunctionError("glSamplerParameterfv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSamplerParameteri(GLuint,GLenum,GLint){printMissingFunctionError("glSamplerParameteri");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSamplerParameterIiv(GLuint,GLenum,const GLint*){printMissingFunctionError("glSamplerParameterIiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSamplerParameterIuiv(GLuint,GLenum,const GLuint*){printMissingFunctionError("glSamplerParameterIuiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSamplerParameteriv(GLuint,GLenum,const GLint*){printMissingFunctionError("glSamplerParameteriv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglScaled(GLdouble,GLdouble,GLdouble){printMissingFunctionError("glScaled");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglScalef(GLfloat,GLfloat,GLfloat){printMissingFunctionError("glScalef");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglScalexOES(GLfixed,GLfixed,GLfixed){printMissingFunctionError("glScalexOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglScissorArrayv(GLuint,GLsizei,const GLint*){printMissingFunctionError("glScissorArrayv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglScissor(GLint,GLint,GLsizei,GLsizei){printMissingFunctionError("glScissor");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglScissorIndexed(GLuint,GLint,GLint,GLsizei,GLsizei){printMissingFunctionError("glScissorIndexed");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglScissorIndexedv(GLuint,const GLint*){printMissingFunctionError("glScissorIndexedv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSecondaryColor3bEXT(GLbyte,GLbyte,GLbyte){printMissingFunctionError("glSecondaryColor3bEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSecondaryColor3b(GLbyte,GLbyte,GLbyte){printMissingFunctionError("glSecondaryColor3b");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSecondaryColor3bv(const GLbyte*){printMissingFunctionError("glSecondaryColor3bv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSecondaryColor3bvEXT(const GLbyte*){printMissingFunctionError("glSecondaryColor3bvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSecondaryColor3dEXT(GLdouble,GLdouble,GLdouble){printMissingFunctionError("glSecondaryColor3dEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSecondaryColor3d(GLdouble,GLdouble,GLdouble){printMissingFunctionError("glSecondaryColor3d");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSecondaryColor3dv(const GLdouble*){printMissingFunctionError("glSecondaryColor3dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSecondaryColor3dvEXT(const GLdouble*){printMissingFunctionError("glSecondaryColor3dvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSecondaryColor3fEXT(GLfloat,GLfloat,GLfloat){printMissingFunctionError("glSecondaryColor3fEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSecondaryColor3f(GLfloat,GLfloat,GLfloat){printMissingFunctionError("glSecondaryColor3f");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSecondaryColor3fv(const GLfloat*){printMissingFunctionError("glSecondaryColor3fv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSecondaryColor3fvEXT(const GLfloat*){printMissingFunctionError("glSecondaryColor3fvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSecondaryColor3hNV(GLhalfNV,GLhalfNV,GLhalfNV){printMissingFunctionError("glSecondaryColor3hNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSecondaryColor3hvNV(const GLhalfNV*){printMissingFunctionError("glSecondaryColor3hvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSecondaryColor3iEXT(GLint,GLint,GLint){printMissingFunctionError("glSecondaryColor3iEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSecondaryColor3i(GLint,GLint,GLint){printMissingFunctionError("glSecondaryColor3i");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSecondaryColor3iv(const GLint*){printMissingFunctionError("glSecondaryColor3iv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSecondaryColor3ivEXT(const GLint*){printMissingFunctionError("glSecondaryColor3ivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSecondaryColor3sEXT(GLshort,GLshort,GLshort){printMissingFunctionError("glSecondaryColor3sEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSecondaryColor3s(GLshort,GLshort,GLshort){printMissingFunctionError("glSecondaryColor3s");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSecondaryColor3sv(const GLshort*){printMissingFunctionError("glSecondaryColor3sv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSecondaryColor3svEXT(const GLshort*){printMissingFunctionError("glSecondaryColor3svEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSecondaryColor3ubEXT(GLubyte,GLubyte,GLubyte){printMissingFunctionError("glSecondaryColor3ubEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSecondaryColor3ub(GLubyte,GLubyte,GLubyte){printMissingFunctionError("glSecondaryColor3ub");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSecondaryColor3ubv(const GLubyte*){printMissingFunctionError("glSecondaryColor3ubv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSecondaryColor3ubvEXT(const GLubyte*){printMissingFunctionError("glSecondaryColor3ubvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSecondaryColor3uiEXT(GLuint,GLuint,GLuint){printMissingFunctionError("glSecondaryColor3uiEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSecondaryColor3ui(GLuint,GLuint,GLuint){printMissingFunctionError("glSecondaryColor3ui");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSecondaryColor3uiv(const GLuint*){printMissingFunctionError("glSecondaryColor3uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSecondaryColor3uivEXT(const GLuint*){printMissingFunctionError("glSecondaryColor3uivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSecondaryColor3usEXT(GLushort,GLushort,GLushort){printMissingFunctionError("glSecondaryColor3usEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSecondaryColor3us(GLushort,GLushort,GLushort){printMissingFunctionError("glSecondaryColor3us");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSecondaryColor3usv(const GLushort*){printMissingFunctionError("glSecondaryColor3usv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSecondaryColor3usvEXT(const GLushort*){printMissingFunctionError("glSecondaryColor3usvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSecondaryColorFormatNV(GLint,GLenum,GLsizei){printMissingFunctionError("glSecondaryColorFormatNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSecondaryColorP3ui(GLenum,GLuint){printMissingFunctionError("glSecondaryColorP3ui");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSecondaryColorP3uiv(GLenum,const GLuint*){printMissingFunctionError("glSecondaryColorP3uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSecondaryColorPointerEXT(GLint,GLenum,GLsizei,const void*){printMissingFunctionError("glSecondaryColorPointerEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSecondaryColorPointer(GLint,GLenum,GLsizei,const void*){printMissingFunctionError("glSecondaryColorPointer");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSecondaryColorPointerListIBM(GLint,GLenum,GLint,const void**,GLint){printMissingFunctionError("glSecondaryColorPointerListIBM");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSelectBuffer(GLsizei,GLuint*){printMissingFunctionError("glSelectBuffer");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSelectPerfMonitorCountersAMD(GLuint,GLboolean,GLuint,GLint,GLuint*){printMissingFunctionError("glSelectPerfMonitorCountersAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSeparableFilter2DEXT(GLenum,GLenum,GLsizei,GLsizei,GLenum,GLenum,const void*,const void*){printMissingFunctionError("glSeparableFilter2DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSeparableFilter2D(GLenum,GLenum,GLsizei,GLsizei,GLenum,GLenum,const GLvoid*,const GLvoid*){printMissingFunctionError("glSeparableFilter2D");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSetFenceAPPLE(GLuint){printMissingFunctionError("glSetFenceAPPLE");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSetFenceNV(GLuint,GLenum){printMissingFunctionError("glSetFenceNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSetFragmentShaderConstantATI(GLuint,const GLfloat*){printMissingFunctionError("glSetFragmentShaderConstantATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSetInvariantEXT(GLuint,GLenum,const void*){printMissingFunctionError("glSetInvariantEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSetLocalConstantEXT(GLuint,GLenum,const void*){printMissingFunctionError("glSetLocalConstantEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSetMultisamplefvAMD(GLenum,GLuint,const GLfloat*){printMissingFunctionError("glSetMultisamplefvAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglShadeModel(GLenum){printMissingFunctionError("glShadeModel");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglShaderBinary(GLsizei,const GLuint*,GLenum,const void*,GLsizei){printMissingFunctionError("glShaderBinary");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglShaderOp1EXT(GLenum,GLuint,GLuint){printMissingFunctionError("glShaderOp1EXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglShaderOp2EXT(GLenum,GLuint,GLuint,GLuint){printMissingFunctionError("glShaderOp2EXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglShaderOp3EXT(GLenum,GLuint,GLuint,GLuint,GLuint){printMissingFunctionError("glShaderOp3EXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglShaderSourceARB(GLhandleARB,GLsizei,const GLcharARB**,const GLint*){printMissingFunctionError("glShaderSourceARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglShaderSource(GLuint,GLsizei,const GLchar*const*,const GLint*){printMissingFunctionError("glShaderSource");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglShaderStorageBlockBinding(GLuint,GLuint,GLuint){printMissingFunctionError("glShaderStorageBlockBinding");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSharpenTexFuncSGIS(GLenum,GLsizei,const GLfloat*){printMissingFunctionError("glSharpenTexFuncSGIS");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSpriteParameterfSGIX(GLenum,GLfloat){printMissingFunctionError("glSpriteParameterfSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSpriteParameterfvSGIX(GLenum,const GLfloat*){printMissingFunctionError("glSpriteParameterfvSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSpriteParameteriSGIX(GLenum,GLint){printMissingFunctionError("glSpriteParameteriSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSpriteParameterivSGIX(GLenum,const GLint*){printMissingFunctionError("glSpriteParameterivSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglStartInstrumentsSGIX(){printMissingFunctionError("glStartInstrumentsSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglStateCaptureNV(GLuint,GLenum){printMissingFunctionError("glStateCaptureNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglStencilClearTagEXT(GLsizei,GLuint){printMissingFunctionError("glStencilClearTagEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglStencilFillPathInstancedNV(GLsizei,GLenum,const void*,GLuint,GLenum,GLuint,GLenum,const GLfloat*){printMissingFunctionError("glStencilFillPathInstancedNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglStencilFillPathNV(GLuint,GLenum,GLuint){printMissingFunctionError("glStencilFillPathNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglStencilFunc(GLenum,GLint,GLuint){printMissingFunctionError("glStencilFunc");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglStencilFuncSeparateATI(GLenum,GLenum,GLint,GLuint){printMissingFunctionError("glStencilFuncSeparateATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglStencilFuncSeparate(GLenum,GLenum,GLint,GLuint){printMissingFunctionError("glStencilFuncSeparate");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglStencilMask(GLuint){printMissingFunctionError("glStencilMask");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglStencilMaskSeparate(GLenum,GLuint){printMissingFunctionError("glStencilMaskSeparate");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglStencilOp(GLenum,GLenum,GLenum){printMissingFunctionError("glStencilOp");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglStencilOpSeparateATI(GLenum,GLenum,GLenum,GLenum){printMissingFunctionError("glStencilOpSeparateATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglStencilOpSeparate(GLenum,GLenum,GLenum,GLenum){printMissingFunctionError("glStencilOpSeparate");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglStencilOpValueAMD(GLenum,GLuint){printMissingFunctionError("glStencilOpValueAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglStencilStrokePathInstancedNV(GLsizei,GLenum,const void*,GLuint,GLint,GLuint,GLenum,const GLfloat*){printMissingFunctionError("glStencilStrokePathInstancedNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglStencilStrokePathNV(GLuint,GLint,GLuint){printMissingFunctionError("glStencilStrokePathNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglStencilThenCoverFillPathInstancedNV(GLsizei,GLenum,const void*,GLuint,GLenum,GLuint,GLenum,GLenum,const GLfloat*){printMissingFunctionError("glStencilThenCoverFillPathInstancedNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglStencilThenCoverFillPathNV(GLuint,GLenum,GLuint,GLenum){printMissingFunctionError("glStencilThenCoverFillPathNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglStencilThenCoverStrokePathInstancedNV(GLsizei,GLenum,const void*,GLuint,GLint,GLuint,GLenum,GLenum,const GLfloat*){printMissingFunctionError("glStencilThenCoverStrokePathInstancedNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglStencilThenCoverStrokePathNV(GLuint,GLint,GLuint,GLenum){printMissingFunctionError("glStencilThenCoverStrokePathNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglStopInstrumentsSGIX(GLint){printMissingFunctionError("glStopInstrumentsSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglStringMarkerGREMEDY(GLsizei,const void*){printMissingFunctionError("glStringMarkerGREMEDY");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSubpixelPrecisionBiasNV(GLuint,GLuint){printMissingFunctionError("glSubpixelPrecisionBiasNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSwizzleEXT(GLuint,GLuint,GLenum,GLenum,GLenum,GLenum){printMissingFunctionError("glSwizzleEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglSyncTextureINTEL(GLuint){printMissingFunctionError("glSyncTextureINTEL");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTagSampleBufferSGIX(){printMissingFunctionError("glTagSampleBufferSGIX");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTangent3bEXT(GLbyte,GLbyte,GLbyte){printMissingFunctionError("glTangent3bEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTangent3bvEXT(const GLbyte*){printMissingFunctionError("glTangent3bvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTangent3dEXT(GLdouble,GLdouble,GLdouble){printMissingFunctionError("glTangent3dEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTangent3dvEXT(const GLdouble*){printMissingFunctionError("glTangent3dvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTangent3fEXT(GLfloat,GLfloat,GLfloat){printMissingFunctionError("glTangent3fEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTangent3fvEXT(const GLfloat*){printMissingFunctionError("glTangent3fvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTangent3iEXT(GLint,GLint,GLint){printMissingFunctionError("glTangent3iEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTangent3ivEXT(const GLint*){printMissingFunctionError("glTangent3ivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTangent3sEXT(GLshort,GLshort,GLshort){printMissingFunctionError("glTangent3sEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTangent3svEXT(const GLshort*){printMissingFunctionError("glTangent3svEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTangentPointerEXT(GLenum,GLsizei,const void*){printMissingFunctionError("glTangentPointerEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTbufferMask3DFX(GLuint){printMissingFunctionError("glTbufferMask3DFX");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTessellationFactorAMD(GLfloat){printMissingFunctionError("glTessellationFactorAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTessellationModeAMD(GLenum){printMissingFunctionError("glTessellationModeAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexBufferARB(GLenum,GLenum,GLuint){printMissingFunctionError("glTexBufferARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexBufferEXT(GLenum,GLenum,GLuint){printMissingFunctionError("glTexBufferEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexBuffer(GLenum,GLenum,GLuint){printMissingFunctionError("glTexBuffer");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexBufferRange(GLenum,GLenum,GLuint,GLintptr,GLsizeiptr){printMissingFunctionError("glTexBufferRange");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexBumpParameterfvATI(GLenum,const GLfloat*){printMissingFunctionError("glTexBumpParameterfvATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexBumpParameterivATI(GLenum,const GLint*){printMissingFunctionError("glTexBumpParameterivATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord1bOES(GLbyte){printMissingFunctionError("glTexCoord1bOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord1bvOES(const GLbyte*){printMissingFunctionError("glTexCoord1bvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord1d(GLdouble){printMissingFunctionError("glTexCoord1d");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord1dv(const GLdouble*){printMissingFunctionError("glTexCoord1dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord1f(GLfloat){printMissingFunctionError("glTexCoord1f");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord1fv(const GLfloat*){printMissingFunctionError("glTexCoord1fv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord1hNV(GLhalfNV){printMissingFunctionError("glTexCoord1hNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord1hvNV(const GLhalfNV*){printMissingFunctionError("glTexCoord1hvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord1i(GLint){printMissingFunctionError("glTexCoord1i");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord1iv(const GLint*){printMissingFunctionError("glTexCoord1iv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord1s(GLshort){printMissingFunctionError("glTexCoord1s");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord1sv(const GLshort*){printMissingFunctionError("glTexCoord1sv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord1xOES(GLfixed){printMissingFunctionError("glTexCoord1xOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord1xvOES(const GLfixed*){printMissingFunctionError("glTexCoord1xvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord2bOES(GLbyte,GLbyte){printMissingFunctionError("glTexCoord2bOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord2bvOES(const GLbyte*){printMissingFunctionError("glTexCoord2bvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord2d(GLdouble,GLdouble){printMissingFunctionError("glTexCoord2d");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord2dv(const GLdouble*){printMissingFunctionError("glTexCoord2dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord2fColor3fVertex3fSUN(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glTexCoord2fColor3fVertex3fSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord2fColor3fVertex3fvSUN(const GLfloat*,const GLfloat*,const GLfloat*){printMissingFunctionError("glTexCoord2fColor3fVertex3fvSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord2fColor4fNormal3fVertex3fSUN(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glTexCoord2fColor4fNormal3fVertex3fSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord2fColor4fNormal3fVertex3fvSUN(const GLfloat*,const GLfloat*,const GLfloat*,const GLfloat*){printMissingFunctionError("glTexCoord2fColor4fNormal3fVertex3fvSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord2fColor4ubVertex3fSUN(GLfloat,GLfloat,GLubyte,GLubyte,GLubyte,GLubyte,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glTexCoord2fColor4ubVertex3fSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord2fColor4ubVertex3fvSUN(const GLfloat*,const GLubyte*,const GLfloat*){printMissingFunctionError("glTexCoord2fColor4ubVertex3fvSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord2f(GLfloat,GLfloat){printMissingFunctionError("glTexCoord2f");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord2fNormal3fVertex3fSUN(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glTexCoord2fNormal3fVertex3fSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord2fNormal3fVertex3fvSUN(const GLfloat*,const GLfloat*,const GLfloat*){printMissingFunctionError("glTexCoord2fNormal3fVertex3fvSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord2fv(const GLfloat*){printMissingFunctionError("glTexCoord2fv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord2fVertex3fSUN(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glTexCoord2fVertex3fSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord2fVertex3fvSUN(const GLfloat*,const GLfloat*){printMissingFunctionError("glTexCoord2fVertex3fvSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord2hNV(GLhalfNV,GLhalfNV){printMissingFunctionError("glTexCoord2hNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord2hvNV(const GLhalfNV*){printMissingFunctionError("glTexCoord2hvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord2i(GLint,GLint){printMissingFunctionError("glTexCoord2i");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord2iv(const GLint*){printMissingFunctionError("glTexCoord2iv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord2s(GLshort,GLshort){printMissingFunctionError("glTexCoord2s");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord2sv(const GLshort*){printMissingFunctionError("glTexCoord2sv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord2xOES(GLfixed,GLfixed){printMissingFunctionError("glTexCoord2xOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord2xvOES(const GLfixed*){printMissingFunctionError("glTexCoord2xvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord3bOES(GLbyte,GLbyte,GLbyte){printMissingFunctionError("glTexCoord3bOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord3bvOES(const GLbyte*){printMissingFunctionError("glTexCoord3bvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord3d(GLdouble,GLdouble,GLdouble){printMissingFunctionError("glTexCoord3d");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord3dv(const GLdouble*){printMissingFunctionError("glTexCoord3dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord3f(GLfloat,GLfloat,GLfloat){printMissingFunctionError("glTexCoord3f");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord3fv(const GLfloat*){printMissingFunctionError("glTexCoord3fv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord3hNV(GLhalfNV,GLhalfNV,GLhalfNV){printMissingFunctionError("glTexCoord3hNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord3hvNV(const GLhalfNV*){printMissingFunctionError("glTexCoord3hvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord3i(GLint,GLint,GLint){printMissingFunctionError("glTexCoord3i");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord3iv(const GLint*){printMissingFunctionError("glTexCoord3iv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord3s(GLshort,GLshort,GLshort){printMissingFunctionError("glTexCoord3s");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord3sv(const GLshort*){printMissingFunctionError("glTexCoord3sv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord3xOES(GLfixed,GLfixed,GLfixed){printMissingFunctionError("glTexCoord3xOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord3xvOES(const GLfixed*){printMissingFunctionError("glTexCoord3xvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord4bOES(GLbyte,GLbyte,GLbyte,GLbyte){printMissingFunctionError("glTexCoord4bOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord4bvOES(const GLbyte*){printMissingFunctionError("glTexCoord4bvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord4d(GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glTexCoord4d");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord4dv(const GLdouble*){printMissingFunctionError("glTexCoord4dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord4fColor4fNormal3fVertex4fSUN(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glTexCoord4fColor4fNormal3fVertex4fSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord4fColor4fNormal3fVertex4fvSUN(const GLfloat*,const GLfloat*,const GLfloat*,const GLfloat*){printMissingFunctionError("glTexCoord4fColor4fNormal3fVertex4fvSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord4f(GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glTexCoord4f");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord4fv(const GLfloat*){printMissingFunctionError("glTexCoord4fv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord4fVertex4fSUN(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glTexCoord4fVertex4fSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord4fVertex4fvSUN(const GLfloat*,const GLfloat*){printMissingFunctionError("glTexCoord4fVertex4fvSUN");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord4hNV(GLhalfNV,GLhalfNV,GLhalfNV,GLhalfNV){printMissingFunctionError("glTexCoord4hNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord4hvNV(const GLhalfNV*){printMissingFunctionError("glTexCoord4hvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord4i(GLint,GLint,GLint,GLint){printMissingFunctionError("glTexCoord4i");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord4iv(const GLint*){printMissingFunctionError("glTexCoord4iv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord4s(GLshort,GLshort,GLshort,GLshort){printMissingFunctionError("glTexCoord4s");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord4sv(const GLshort*){printMissingFunctionError("glTexCoord4sv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord4xOES(GLfixed,GLfixed,GLfixed,GLfixed){printMissingFunctionError("glTexCoord4xOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoord4xvOES(const GLfixed*){printMissingFunctionError("glTexCoord4xvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoordFormatNV(GLint,GLenum,GLsizei){printMissingFunctionError("glTexCoordFormatNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoordP1ui(GLenum,GLuint){printMissingFunctionError("glTexCoordP1ui");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoordP1uiv(GLenum,const GLuint*){printMissingFunctionError("glTexCoordP1uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoordP2ui(GLenum,GLuint){printMissingFunctionError("glTexCoordP2ui");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoordP2uiv(GLenum,const GLuint*){printMissingFunctionError("glTexCoordP2uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoordP3ui(GLenum,GLuint){printMissingFunctionError("glTexCoordP3ui");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoordP3uiv(GLenum,const GLuint*){printMissingFunctionError("glTexCoordP3uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoordP4ui(GLenum,GLuint){printMissingFunctionError("glTexCoordP4ui");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoordP4uiv(GLenum,const GLuint*){printMissingFunctionError("glTexCoordP4uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoordPointerEXT(GLint,GLenum,GLsizei,GLsizei,const void*){printMissingFunctionError("glTexCoordPointerEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoordPointer(GLint,GLenum,GLsizei,const GLvoid*){printMissingFunctionError("glTexCoordPointer");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoordPointerListIBM(GLint,GLenum,GLint,const void**,GLint){printMissingFunctionError("glTexCoordPointerListIBM");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexCoordPointervINTEL(GLint,GLenum,const void**){printMissingFunctionError("glTexCoordPointervINTEL");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexEnvf(GLenum,GLenum,GLfloat){printMissingFunctionError("glTexEnvf");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexEnvfv(GLenum,GLenum,const GLfloat*){printMissingFunctionError("glTexEnvfv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexEnvi(GLenum,GLenum,GLint){printMissingFunctionError("glTexEnvi");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexEnviv(GLenum,GLenum,const GLint*){printMissingFunctionError("glTexEnviv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexEnvxOES(GLenum,GLenum,GLfixed){printMissingFunctionError("glTexEnvxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexEnvxvOES(GLenum,GLenum,const GLfixed*){printMissingFunctionError("glTexEnvxvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexFilterFuncSGIS(GLenum,GLenum,GLsizei,const GLfloat*){printMissingFunctionError("glTexFilterFuncSGIS");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexGend(GLenum,GLenum,GLdouble){printMissingFunctionError("glTexGend");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexGendv(GLenum,GLenum,const GLdouble*){printMissingFunctionError("glTexGendv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexGenf(GLenum,GLenum,GLfloat){printMissingFunctionError("glTexGenf");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexGenfv(GLenum,GLenum,const GLfloat*){printMissingFunctionError("glTexGenfv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexGeni(GLenum,GLenum,GLint){printMissingFunctionError("glTexGeni");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexGeniv(GLenum,GLenum,const GLint*){printMissingFunctionError("glTexGeniv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexGenxOES(GLenum,GLenum,GLfixed){printMissingFunctionError("glTexGenxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexGenxvOES(GLenum,GLenum,const GLfixed*){printMissingFunctionError("glTexGenxvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexImage1D(GLenum,GLint,GLint,GLsizei,GLint,GLenum,GLenum,const GLvoid*){printMissingFunctionError("glTexImage1D");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexImage2D(GLenum,GLint,GLint,GLsizei,GLsizei,GLint,GLenum,GLenum,const GLvoid*){printMissingFunctionError("glTexImage2D");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexImage2DMultisampleCoverageNV(GLenum,GLsizei,GLsizei,GLint,GLsizei,GLsizei,GLboolean){printMissingFunctionError("glTexImage2DMultisampleCoverageNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexImage2DMultisample(GLenum,GLsizei,GLenum,GLsizei,GLsizei,GLboolean){printMissingFunctionError("glTexImage2DMultisample");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexImage3DEXT(GLenum,GLint,GLenum,GLsizei,GLsizei,GLsizei,GLint,GLenum,GLenum,const void*){printMissingFunctionError("glTexImage3DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexImage3D(GLenum,GLint,GLint,GLsizei,GLsizei,GLsizei,GLint,GLenum,GLenum,const GLvoid*){printMissingFunctionError("glTexImage3D");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexImage3DMultisampleCoverageNV(GLenum,GLsizei,GLsizei,GLint,GLsizei,GLsizei,GLsizei,GLboolean){printMissingFunctionError("glTexImage3DMultisampleCoverageNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexImage3DMultisample(GLenum,GLsizei,GLenum,GLsizei,GLsizei,GLsizei,GLboolean){printMissingFunctionError("glTexImage3DMultisample");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexImage4DSGIS(GLenum,GLint,GLenum,GLsizei,GLsizei,GLsizei,GLsizei,GLint,GLenum,GLenum,const void*){printMissingFunctionError("glTexImage4DSGIS");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexPageCommitmentARB(GLenum,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLboolean){printMissingFunctionError("glTexPageCommitmentARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexParameterf(GLenum,GLenum,GLfloat){printMissingFunctionError("glTexParameterf");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexParameterfv(GLenum,GLenum,const GLfloat*){printMissingFunctionError("glTexParameterfv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexParameteri(GLenum,GLenum,GLint){printMissingFunctionError("glTexParameteri");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexParameterIivEXT(GLenum,GLenum,const GLint*){printMissingFunctionError("glTexParameterIivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexParameterIiv(GLenum,GLenum,const GLint*){printMissingFunctionError("glTexParameterIiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexParameterIuivEXT(GLenum,GLenum,const GLuint*){printMissingFunctionError("glTexParameterIuivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexParameterIuiv(GLenum,GLenum,const GLuint*){printMissingFunctionError("glTexParameterIuiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexParameteriv(GLenum,GLenum,const GLint*){printMissingFunctionError("glTexParameteriv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexParameterxOES(GLenum,GLenum,GLfixed){printMissingFunctionError("glTexParameterxOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexParameterxvOES(GLenum,GLenum,const GLfixed*){printMissingFunctionError("glTexParameterxvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexRenderbufferNV(GLenum,GLuint){printMissingFunctionError("glTexRenderbufferNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexStorage1D(GLenum,GLsizei,GLenum,GLsizei){printMissingFunctionError("glTexStorage1D");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexStorage2D(GLenum,GLsizei,GLenum,GLsizei,GLsizei){printMissingFunctionError("glTexStorage2D");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexStorage2DMultisample(GLenum,GLsizei,GLenum,GLsizei,GLsizei,GLboolean){printMissingFunctionError("glTexStorage2DMultisample");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexStorage3D(GLenum,GLsizei,GLenum,GLsizei,GLsizei,GLsizei){printMissingFunctionError("glTexStorage3D");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexStorage3DMultisample(GLenum,GLsizei,GLenum,GLsizei,GLsizei,GLsizei,GLboolean){printMissingFunctionError("glTexStorage3DMultisample");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexStorageSparseAMD(GLenum,GLenum,GLsizei,GLsizei,GLsizei,GLsizei,GLbitfield){printMissingFunctionError("glTexStorageSparseAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexSubImage1DEXT(GLenum,GLint,GLint,GLsizei,GLenum,GLenum,const void*){printMissingFunctionError("glTexSubImage1DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexSubImage1D(GLenum,GLint,GLint,GLsizei,GLenum,GLenum,const GLvoid*){printMissingFunctionError("glTexSubImage1D");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexSubImage2DEXT(GLenum,GLint,GLint,GLint,GLsizei,GLsizei,GLenum,GLenum,const void*){printMissingFunctionError("glTexSubImage2DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexSubImage2D(GLenum,GLint,GLint,GLint,GLsizei,GLsizei,GLenum,GLenum,const GLvoid*){printMissingFunctionError("glTexSubImage2D");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexSubImage3DEXT(GLenum,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLenum,GLenum,const void*){printMissingFunctionError("glTexSubImage3DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexSubImage3D(GLenum,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLenum,GLenum,const GLvoid*){printMissingFunctionError("glTexSubImage3D");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexSubImage4DSGIS(GLenum,GLint,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLsizei,GLenum,GLenum,const void*){printMissingFunctionError("glTexSubImage4DSGIS");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTextureBarrier(){printMissingFunctionError("glTextureBarrier");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTextureBarrierNV(){printMissingFunctionError("glTextureBarrierNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTextureBufferEXT(GLuint,GLenum,GLenum,GLuint){printMissingFunctionError("glTextureBufferEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTextureBuffer(GLuint,GLenum,GLuint){printMissingFunctionError("glTextureBuffer");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTextureBufferRangeEXT(GLuint,GLenum,GLenum,GLuint,GLintptr,GLsizeiptr){printMissingFunctionError("glTextureBufferRangeEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTextureBufferRange(GLuint,GLenum,GLuint,GLintptr,GLsizeiptr){printMissingFunctionError("glTextureBufferRange");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTextureColorMaskSGIS(GLboolean,GLboolean,GLboolean,GLboolean){printMissingFunctionError("glTextureColorMaskSGIS");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTextureImage1DEXT(GLuint,GLenum,GLint,GLint,GLsizei,GLint,GLenum,GLenum,const void*){printMissingFunctionError("glTextureImage1DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTextureImage2DEXT(GLuint,GLenum,GLint,GLint,GLsizei,GLsizei,GLint,GLenum,GLenum,const void*){printMissingFunctionError("glTextureImage2DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTextureImage2DMultisampleCoverageNV(GLuint,GLenum,GLsizei,GLsizei,GLint,GLsizei,GLsizei,GLboolean){printMissingFunctionError("glTextureImage2DMultisampleCoverageNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTextureImage2DMultisampleNV(GLuint,GLenum,GLsizei,GLint,GLsizei,GLsizei,GLboolean){printMissingFunctionError("glTextureImage2DMultisampleNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTextureImage3DEXT(GLuint,GLenum,GLint,GLint,GLsizei,GLsizei,GLsizei,GLint,GLenum,GLenum,const void*){printMissingFunctionError("glTextureImage3DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTextureImage3DMultisampleCoverageNV(GLuint,GLenum,GLsizei,GLsizei,GLint,GLsizei,GLsizei,GLsizei,GLboolean){printMissingFunctionError("glTextureImage3DMultisampleCoverageNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTextureImage3DMultisampleNV(GLuint,GLenum,GLsizei,GLint,GLsizei,GLsizei,GLsizei,GLboolean){printMissingFunctionError("glTextureImage3DMultisampleNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTextureLightEXT(GLenum){printMissingFunctionError("glTextureLightEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTextureMaterialEXT(GLenum,GLenum){printMissingFunctionError("glTextureMaterialEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTextureNormalEXT(GLenum){printMissingFunctionError("glTextureNormalEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTexturePageCommitmentEXT(GLuint,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLboolean){printMissingFunctionError("glTexturePageCommitmentEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTextureParameterfEXT(GLuint,GLenum,GLenum,GLfloat){printMissingFunctionError("glTextureParameterfEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTextureParameterf(GLuint,GLenum,GLfloat){printMissingFunctionError("glTextureParameterf");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTextureParameterfvEXT(GLuint,GLenum,GLenum,const GLfloat*){printMissingFunctionError("glTextureParameterfvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTextureParameterfv(GLuint,GLenum,const GLfloat*){printMissingFunctionError("glTextureParameterfv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTextureParameteriEXT(GLuint,GLenum,GLenum,GLint){printMissingFunctionError("glTextureParameteriEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTextureParameteri(GLuint,GLenum,GLint){printMissingFunctionError("glTextureParameteri");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTextureParameterIivEXT(GLuint,GLenum,GLenum,const GLint*){printMissingFunctionError("glTextureParameterIivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTextureParameterIiv(GLuint,GLenum,const GLint*){printMissingFunctionError("glTextureParameterIiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTextureParameterIuivEXT(GLuint,GLenum,GLenum,const GLuint*){printMissingFunctionError("glTextureParameterIuivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTextureParameterIuiv(GLuint,GLenum,const GLuint*){printMissingFunctionError("glTextureParameterIuiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTextureParameterivEXT(GLuint,GLenum,GLenum,const GLint*){printMissingFunctionError("glTextureParameterivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTextureParameteriv(GLuint,GLenum,const GLint*){printMissingFunctionError("glTextureParameteriv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTextureRangeAPPLE(GLenum,GLsizei,const void*){printMissingFunctionError("glTextureRangeAPPLE");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTextureRenderbufferEXT(GLuint,GLenum,GLuint){printMissingFunctionError("glTextureRenderbufferEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTextureStorage1DEXT(GLuint,GLenum,GLsizei,GLenum,GLsizei){printMissingFunctionError("glTextureStorage1DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTextureStorage1D(GLuint,GLsizei,GLenum,GLsizei){printMissingFunctionError("glTextureStorage1D");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTextureStorage2DEXT(GLuint,GLenum,GLsizei,GLenum,GLsizei,GLsizei){printMissingFunctionError("glTextureStorage2DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTextureStorage2D(GLuint,GLsizei,GLenum,GLsizei,GLsizei){printMissingFunctionError("glTextureStorage2D");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTextureStorage2DMultisampleEXT(GLuint,GLenum,GLsizei,GLenum,GLsizei,GLsizei,GLboolean){printMissingFunctionError("glTextureStorage2DMultisampleEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTextureStorage2DMultisample(GLuint,GLsizei,GLenum,GLsizei,GLsizei,GLboolean){printMissingFunctionError("glTextureStorage2DMultisample");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTextureStorage3DEXT(GLuint,GLenum,GLsizei,GLenum,GLsizei,GLsizei,GLsizei){printMissingFunctionError("glTextureStorage3DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTextureStorage3D(GLuint,GLsizei,GLenum,GLsizei,GLsizei,GLsizei){printMissingFunctionError("glTextureStorage3D");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTextureStorage3DMultisampleEXT(GLuint,GLenum,GLsizei,GLenum,GLsizei,GLsizei,GLsizei,GLboolean){printMissingFunctionError("glTextureStorage3DMultisampleEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTextureStorage3DMultisample(GLuint,GLsizei,GLenum,GLsizei,GLsizei,GLsizei,GLboolean){printMissingFunctionError("glTextureStorage3DMultisample");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTextureStorageSparseAMD(GLuint,GLenum,GLenum,GLsizei,GLsizei,GLsizei,GLsizei,GLbitfield){printMissingFunctionError("glTextureStorageSparseAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTextureSubImage1DEXT(GLuint,GLenum,GLint,GLint,GLsizei,GLenum,GLenum,const void*){printMissingFunctionError("glTextureSubImage1DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTextureSubImage1D(GLuint,GLint,GLint,GLsizei,GLenum,GLenum,const void*){printMissingFunctionError("glTextureSubImage1D");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTextureSubImage2DEXT(GLuint,GLenum,GLint,GLint,GLint,GLsizei,GLsizei,GLenum,GLenum,const void*){printMissingFunctionError("glTextureSubImage2DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTextureSubImage2D(GLuint,GLint,GLint,GLint,GLsizei,GLsizei,GLenum,GLenum,const void*){printMissingFunctionError("glTextureSubImage2D");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTextureSubImage3DEXT(GLuint,GLenum,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLenum,GLenum,const void*){printMissingFunctionError("glTextureSubImage3DEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTextureSubImage3D(GLuint,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLenum,GLenum,const void*){printMissingFunctionError("glTextureSubImage3D");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTextureView(GLuint,GLenum,GLuint,GLenum,GLuint,GLuint,GLuint,GLuint){printMissingFunctionError("glTextureView");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTrackMatrixNV(GLenum,GLuint,GLenum,GLenum){printMissingFunctionError("glTrackMatrixNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTransformFeedbackAttribsNV(GLsizei,const GLint*,GLenum){printMissingFunctionError("glTransformFeedbackAttribsNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTransformFeedbackBufferBase(GLuint,GLuint,GLuint){printMissingFunctionError("glTransformFeedbackBufferBase");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTransformFeedbackBufferRange(GLuint,GLuint,GLuint,GLintptr,GLsizeiptr){printMissingFunctionError("glTransformFeedbackBufferRange");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTransformFeedbackStreamAttribsNV(GLsizei,const GLint*,GLsizei,const GLint*,GLenum){printMissingFunctionError("glTransformFeedbackStreamAttribsNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTransformFeedbackVaryingsEXT(GLuint,GLsizei,const GLchar*const*,GLenum){printMissingFunctionError("glTransformFeedbackVaryingsEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTransformFeedbackVaryings(GLuint,GLsizei,const GLchar*const*,GLenum){printMissingFunctionError("glTransformFeedbackVaryings");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTransformFeedbackVaryingsNV(GLuint,GLsizei,const GLint*,GLenum){printMissingFunctionError("glTransformFeedbackVaryingsNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTransformPathNV(GLuint,GLuint,GLenum,const GLfloat*){printMissingFunctionError("glTransformPathNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTranslated(GLdouble,GLdouble,GLdouble){printMissingFunctionError("glTranslated");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTranslatef(GLfloat,GLfloat,GLfloat){printMissingFunctionError("glTranslatef");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglTranslatexOES(GLfixed,GLfixed,GLfixed){printMissingFunctionError("glTranslatexOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform1d(GLint,GLdouble){printMissingFunctionError("glUniform1d");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform1dv(GLint,GLsizei,const GLdouble*){printMissingFunctionError("glUniform1dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform1fARB(GLint,GLfloat){printMissingFunctionError("glUniform1fARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform1f(GLint,GLfloat){printMissingFunctionError("glUniform1f");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform1fvARB(GLint,GLsizei,const GLfloat*){printMissingFunctionError("glUniform1fvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform1fv(GLint,GLsizei,const GLfloat*){printMissingFunctionError("glUniform1fv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform1i64ARB(GLint,GLint64){printMissingFunctionError("glUniform1i64ARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform1i64NV(GLint,GLint64EXT){printMissingFunctionError("glUniform1i64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform1i64vARB(GLint,GLsizei,const GLint64*){printMissingFunctionError("glUniform1i64vARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform1i64vNV(GLint,GLsizei,const GLint64EXT*){printMissingFunctionError("glUniform1i64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform1iARB(GLint,GLint){printMissingFunctionError("glUniform1iARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform1i(GLint,GLint){printMissingFunctionError("glUniform1i");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform1ivARB(GLint,GLsizei,const GLint*){printMissingFunctionError("glUniform1ivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform1iv(GLint,GLsizei,const GLint*){printMissingFunctionError("glUniform1iv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform1ui64ARB(GLint,GLuint64){printMissingFunctionError("glUniform1ui64ARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform1ui64NV(GLint,GLuint64EXT){printMissingFunctionError("glUniform1ui64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform1ui64vARB(GLint,GLsizei,const GLuint64*){printMissingFunctionError("glUniform1ui64vARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform1ui64vNV(GLint,GLsizei,const GLuint64EXT*){printMissingFunctionError("glUniform1ui64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform1uiEXT(GLint,GLuint){printMissingFunctionError("glUniform1uiEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform1ui(GLint,GLuint){printMissingFunctionError("glUniform1ui");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform1uivEXT(GLint,GLsizei,const GLuint*){printMissingFunctionError("glUniform1uivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform1uiv(GLint,GLsizei,const GLuint*){printMissingFunctionError("glUniform1uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform2d(GLint,GLdouble,GLdouble){printMissingFunctionError("glUniform2d");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform2dv(GLint,GLsizei,const GLdouble*){printMissingFunctionError("glUniform2dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform2fARB(GLint,GLfloat,GLfloat){printMissingFunctionError("glUniform2fARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform2f(GLint,GLfloat,GLfloat){printMissingFunctionError("glUniform2f");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform2fvARB(GLint,GLsizei,const GLfloat*){printMissingFunctionError("glUniform2fvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform2fv(GLint,GLsizei,const GLfloat*){printMissingFunctionError("glUniform2fv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform2i64ARB(GLint,GLint64,GLint64){printMissingFunctionError("glUniform2i64ARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform2i64NV(GLint,GLint64EXT,GLint64EXT){printMissingFunctionError("glUniform2i64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform2i64vARB(GLint,GLsizei,const GLint64*){printMissingFunctionError("glUniform2i64vARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform2i64vNV(GLint,GLsizei,const GLint64EXT*){printMissingFunctionError("glUniform2i64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform2iARB(GLint,GLint,GLint){printMissingFunctionError("glUniform2iARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform2i(GLint,GLint,GLint){printMissingFunctionError("glUniform2i");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform2ivARB(GLint,GLsizei,const GLint*){printMissingFunctionError("glUniform2ivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform2iv(GLint,GLsizei,const GLint*){printMissingFunctionError("glUniform2iv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform2ui64ARB(GLint,GLuint64,GLuint64){printMissingFunctionError("glUniform2ui64ARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform2ui64NV(GLint,GLuint64EXT,GLuint64EXT){printMissingFunctionError("glUniform2ui64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform2ui64vARB(GLint,GLsizei,const GLuint64*){printMissingFunctionError("glUniform2ui64vARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform2ui64vNV(GLint,GLsizei,const GLuint64EXT*){printMissingFunctionError("glUniform2ui64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform2uiEXT(GLint,GLuint,GLuint){printMissingFunctionError("glUniform2uiEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform2ui(GLint,GLuint,GLuint){printMissingFunctionError("glUniform2ui");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform2uivEXT(GLint,GLsizei,const GLuint*){printMissingFunctionError("glUniform2uivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform2uiv(GLint,GLsizei,const GLuint*){printMissingFunctionError("glUniform2uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform3d(GLint,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glUniform3d");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform3dv(GLint,GLsizei,const GLdouble*){printMissingFunctionError("glUniform3dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform3fARB(GLint,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glUniform3fARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform3f(GLint,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glUniform3f");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform3fvARB(GLint,GLsizei,const GLfloat*){printMissingFunctionError("glUniform3fvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform3fv(GLint,GLsizei,const GLfloat*){printMissingFunctionError("glUniform3fv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform3i64ARB(GLint,GLint64,GLint64,GLint64){printMissingFunctionError("glUniform3i64ARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform3i64NV(GLint,GLint64EXT,GLint64EXT,GLint64EXT){printMissingFunctionError("glUniform3i64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform3i64vARB(GLint,GLsizei,const GLint64*){printMissingFunctionError("glUniform3i64vARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform3i64vNV(GLint,GLsizei,const GLint64EXT*){printMissingFunctionError("glUniform3i64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform3iARB(GLint,GLint,GLint,GLint){printMissingFunctionError("glUniform3iARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform3i(GLint,GLint,GLint,GLint){printMissingFunctionError("glUniform3i");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform3ivARB(GLint,GLsizei,const GLint*){printMissingFunctionError("glUniform3ivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform3iv(GLint,GLsizei,const GLint*){printMissingFunctionError("glUniform3iv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform3ui64ARB(GLint,GLuint64,GLuint64,GLuint64){printMissingFunctionError("glUniform3ui64ARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform3ui64NV(GLint,GLuint64EXT,GLuint64EXT,GLuint64EXT){printMissingFunctionError("glUniform3ui64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform3ui64vARB(GLint,GLsizei,const GLuint64*){printMissingFunctionError("glUniform3ui64vARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform3ui64vNV(GLint,GLsizei,const GLuint64EXT*){printMissingFunctionError("glUniform3ui64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform3uiEXT(GLint,GLuint,GLuint,GLuint){printMissingFunctionError("glUniform3uiEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform3ui(GLint,GLuint,GLuint,GLuint){printMissingFunctionError("glUniform3ui");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform3uivEXT(GLint,GLsizei,const GLuint*){printMissingFunctionError("glUniform3uivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform3uiv(GLint,GLsizei,const GLuint*){printMissingFunctionError("glUniform3uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform4d(GLint,GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glUniform4d");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform4dv(GLint,GLsizei,const GLdouble*){printMissingFunctionError("glUniform4dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform4fARB(GLint,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glUniform4fARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform4f(GLint,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glUniform4f");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform4fvARB(GLint,GLsizei,const GLfloat*){printMissingFunctionError("glUniform4fvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform4fv(GLint,GLsizei,const GLfloat*){printMissingFunctionError("glUniform4fv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform4i64ARB(GLint,GLint64,GLint64,GLint64,GLint64){printMissingFunctionError("glUniform4i64ARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform4i64NV(GLint,GLint64EXT,GLint64EXT,GLint64EXT,GLint64EXT){printMissingFunctionError("glUniform4i64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform4i64vARB(GLint,GLsizei,const GLint64*){printMissingFunctionError("glUniform4i64vARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform4i64vNV(GLint,GLsizei,const GLint64EXT*){printMissingFunctionError("glUniform4i64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform4iARB(GLint,GLint,GLint,GLint,GLint){printMissingFunctionError("glUniform4iARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform4i(GLint,GLint,GLint,GLint,GLint){printMissingFunctionError("glUniform4i");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform4ivARB(GLint,GLsizei,const GLint*){printMissingFunctionError("glUniform4ivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform4iv(GLint,GLsizei,const GLint*){printMissingFunctionError("glUniform4iv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform4ui64ARB(GLint,GLuint64,GLuint64,GLuint64,GLuint64){printMissingFunctionError("glUniform4ui64ARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform4ui64NV(GLint,GLuint64EXT,GLuint64EXT,GLuint64EXT,GLuint64EXT){printMissingFunctionError("glUniform4ui64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform4ui64vARB(GLint,GLsizei,const GLuint64*){printMissingFunctionError("glUniform4ui64vARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform4ui64vNV(GLint,GLsizei,const GLuint64EXT*){printMissingFunctionError("glUniform4ui64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform4uiEXT(GLint,GLuint,GLuint,GLuint,GLuint){printMissingFunctionError("glUniform4uiEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform4ui(GLint,GLuint,GLuint,GLuint,GLuint){printMissingFunctionError("glUniform4ui");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform4uivEXT(GLint,GLsizei,const GLuint*){printMissingFunctionError("glUniform4uivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniform4uiv(GLint,GLsizei,const GLuint*){printMissingFunctionError("glUniform4uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniformBlockBinding(GLuint,GLuint,GLuint){printMissingFunctionError("glUniformBlockBinding");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniformBufferEXT(GLuint,GLint,GLuint){printMissingFunctionError("glUniformBufferEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniformHandleui64ARB(GLint,GLuint64){printMissingFunctionError("glUniformHandleui64ARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniformHandleui64NV(GLint,GLuint64){printMissingFunctionError("glUniformHandleui64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniformHandleui64vARB(GLint,GLsizei,const GLuint64*){printMissingFunctionError("glUniformHandleui64vARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniformHandleui64vNV(GLint,GLsizei,const GLuint64*){printMissingFunctionError("glUniformHandleui64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniformMatrix2dv(GLint,GLsizei,GLboolean,const GLdouble*){printMissingFunctionError("glUniformMatrix2dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniformMatrix2fvARB(GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glUniformMatrix2fvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniformMatrix2fv(GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glUniformMatrix2fv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniformMatrix2x3dv(GLint,GLsizei,GLboolean,const GLdouble*){printMissingFunctionError("glUniformMatrix2x3dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniformMatrix2x3fv(GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glUniformMatrix2x3fv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniformMatrix2x4dv(GLint,GLsizei,GLboolean,const GLdouble*){printMissingFunctionError("glUniformMatrix2x4dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniformMatrix2x4fv(GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glUniformMatrix2x4fv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniformMatrix3dv(GLint,GLsizei,GLboolean,const GLdouble*){printMissingFunctionError("glUniformMatrix3dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniformMatrix3fvARB(GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glUniformMatrix3fvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniformMatrix3fv(GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glUniformMatrix3fv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniformMatrix3x2dv(GLint,GLsizei,GLboolean,const GLdouble*){printMissingFunctionError("glUniformMatrix3x2dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniformMatrix3x2fv(GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glUniformMatrix3x2fv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniformMatrix3x4dv(GLint,GLsizei,GLboolean,const GLdouble*){printMissingFunctionError("glUniformMatrix3x4dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniformMatrix3x4fv(GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glUniformMatrix3x4fv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniformMatrix4dv(GLint,GLsizei,GLboolean,const GLdouble*){printMissingFunctionError("glUniformMatrix4dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniformMatrix4fvARB(GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glUniformMatrix4fvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniformMatrix4fv(GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glUniformMatrix4fv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniformMatrix4x2dv(GLint,GLsizei,GLboolean,const GLdouble*){printMissingFunctionError("glUniformMatrix4x2dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniformMatrix4x2fv(GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glUniformMatrix4x2fv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniformMatrix4x3dv(GLint,GLsizei,GLboolean,const GLdouble*){printMissingFunctionError("glUniformMatrix4x3dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniformMatrix4x3fv(GLint,GLsizei,GLboolean,const GLfloat*){printMissingFunctionError("glUniformMatrix4x3fv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniformSubroutinesuiv(GLenum,GLsizei,const GLuint*){printMissingFunctionError("glUniformSubroutinesuiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniformui64NV(GLint,GLuint64EXT){printMissingFunctionError("glUniformui64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUniformui64vNV(GLint,GLsizei,const GLuint64EXT*){printMissingFunctionError("glUniformui64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUnlockArraysEXT(){printMissingFunctionError("glUnlockArraysEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUnmapObjectBufferATI(GLuint){printMissingFunctionError("glUnmapObjectBufferATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUnmapTexture2DINTEL(GLuint,GLint){printMissingFunctionError("glUnmapTexture2DINTEL");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUpdateObjectBufferATI(GLuint,GLuint,GLsizei,const void*,GLenum){printMissingFunctionError("glUpdateObjectBufferATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUseProgram(GLuint){printMissingFunctionError("glUseProgram");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUseProgramObjectARB(GLhandleARB){printMissingFunctionError("glUseProgramObjectARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUseProgramStages(GLuint,GLbitfield,GLuint){printMissingFunctionError("glUseProgramStages");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglUseShaderProgramEXT(GLenum,GLuint){printMissingFunctionError("glUseShaderProgramEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglValidateProgramARB(GLhandleARB){printMissingFunctionError("glValidateProgramARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglValidateProgram(GLuint){printMissingFunctionError("glValidateProgram");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglValidateProgramPipeline(GLuint){printMissingFunctionError("glValidateProgramPipeline");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVariantArrayObjectATI(GLuint,GLenum,GLsizei,GLuint,GLuint){printMissingFunctionError("glVariantArrayObjectATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVariantbvEXT(GLuint,const GLbyte*){printMissingFunctionError("glVariantbvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVariantdvEXT(GLuint,const GLdouble*){printMissingFunctionError("glVariantdvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVariantfvEXT(GLuint,const GLfloat*){printMissingFunctionError("glVariantfvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVariantivEXT(GLuint,const GLint*){printMissingFunctionError("glVariantivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVariantPointerEXT(GLuint,GLenum,GLuint,const void*){printMissingFunctionError("glVariantPointerEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVariantsvEXT(GLuint,const GLshort*){printMissingFunctionError("glVariantsvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVariantubvEXT(GLuint,const GLubyte*){printMissingFunctionError("glVariantubvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVariantuivEXT(GLuint,const GLuint*){printMissingFunctionError("glVariantuivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVariantusvEXT(GLuint,const GLushort*){printMissingFunctionError("glVariantusvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVDPAUFiniNV(){printMissingFunctionError("glVDPAUFiniNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVDPAUGetSurfaceivNV(GLvdpauSurfaceNV,GLenum,GLsizei,GLsizei*,GLint*){printMissingFunctionError("glVDPAUGetSurfaceivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVDPAUInitNV(const void*,const void*){printMissingFunctionError("glVDPAUInitNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVDPAUMapSurfacesNV(GLsizei,const GLvdpauSurfaceNV*){printMissingFunctionError("glVDPAUMapSurfacesNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVDPAUSurfaceAccessNV(GLvdpauSurfaceNV,GLenum){printMissingFunctionError("glVDPAUSurfaceAccessNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVDPAUUnmapSurfacesNV(GLsizei,const GLvdpauSurfaceNV*){printMissingFunctionError("glVDPAUUnmapSurfacesNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVDPAUUnregisterSurfaceNV(GLvdpauSurfaceNV){printMissingFunctionError("glVDPAUUnregisterSurfaceNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertex2bOES(GLbyte,GLbyte){printMissingFunctionError("glVertex2bOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertex2bvOES(const GLbyte*){printMissingFunctionError("glVertex2bvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertex2d(GLdouble,GLdouble){printMissingFunctionError("glVertex2d");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertex2dv(const GLdouble*){printMissingFunctionError("glVertex2dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertex2f(GLfloat,GLfloat){printMissingFunctionError("glVertex2f");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertex2fv(const GLfloat*){printMissingFunctionError("glVertex2fv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertex2hNV(GLhalfNV,GLhalfNV){printMissingFunctionError("glVertex2hNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertex2hvNV(const GLhalfNV*){printMissingFunctionError("glVertex2hvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertex2i(GLint,GLint){printMissingFunctionError("glVertex2i");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertex2iv(const GLint*){printMissingFunctionError("glVertex2iv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertex2s(GLshort,GLshort){printMissingFunctionError("glVertex2s");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertex2sv(const GLshort*){printMissingFunctionError("glVertex2sv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertex2xOES(GLfixed){printMissingFunctionError("glVertex2xOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertex2xvOES(const GLfixed*){printMissingFunctionError("glVertex2xvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertex3bOES(GLbyte,GLbyte,GLbyte){printMissingFunctionError("glVertex3bOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertex3bvOES(const GLbyte*){printMissingFunctionError("glVertex3bvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertex3d(GLdouble,GLdouble,GLdouble){printMissingFunctionError("glVertex3d");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertex3dv(const GLdouble*){printMissingFunctionError("glVertex3dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertex3f(GLfloat,GLfloat,GLfloat){printMissingFunctionError("glVertex3f");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertex3fv(const GLfloat*){printMissingFunctionError("glVertex3fv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertex3hNV(GLhalfNV,GLhalfNV,GLhalfNV){printMissingFunctionError("glVertex3hNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertex3hvNV(const GLhalfNV*){printMissingFunctionError("glVertex3hvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertex3i(GLint,GLint,GLint){printMissingFunctionError("glVertex3i");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertex3iv(const GLint*){printMissingFunctionError("glVertex3iv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertex3s(GLshort,GLshort,GLshort){printMissingFunctionError("glVertex3s");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertex3sv(const GLshort*){printMissingFunctionError("glVertex3sv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertex3xOES(GLfixed,GLfixed){printMissingFunctionError("glVertex3xOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertex3xvOES(const GLfixed*){printMissingFunctionError("glVertex3xvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertex4bOES(GLbyte,GLbyte,GLbyte,GLbyte){printMissingFunctionError("glVertex4bOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertex4bvOES(const GLbyte*){printMissingFunctionError("glVertex4bvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertex4d(GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glVertex4d");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertex4dv(const GLdouble*){printMissingFunctionError("glVertex4dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertex4f(GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glVertex4f");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertex4fv(const GLfloat*){printMissingFunctionError("glVertex4fv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertex4hNV(GLhalfNV,GLhalfNV,GLhalfNV,GLhalfNV){printMissingFunctionError("glVertex4hNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertex4hvNV(const GLhalfNV*){printMissingFunctionError("glVertex4hvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertex4i(GLint,GLint,GLint,GLint){printMissingFunctionError("glVertex4i");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertex4iv(const GLint*){printMissingFunctionError("glVertex4iv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertex4s(GLshort,GLshort,GLshort,GLshort){printMissingFunctionError("glVertex4s");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertex4sv(const GLshort*){printMissingFunctionError("glVertex4sv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertex4xOES(GLfixed,GLfixed,GLfixed){printMissingFunctionError("glVertex4xOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertex4xvOES(const GLfixed*){printMissingFunctionError("glVertex4xvOES");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexArrayAttribBinding(GLuint,GLuint,GLuint){printMissingFunctionError("glVertexArrayAttribBinding");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexArrayAttribFormat(GLuint,GLuint,GLint,GLenum,GLboolean,GLuint){printMissingFunctionError("glVertexArrayAttribFormat");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexArrayAttribIFormat(GLuint,GLuint,GLint,GLenum,GLuint){printMissingFunctionError("glVertexArrayAttribIFormat");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexArrayAttribLFormat(GLuint,GLuint,GLint,GLenum,GLuint){printMissingFunctionError("glVertexArrayAttribLFormat");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexArrayBindingDivisor(GLuint,GLuint,GLuint){printMissingFunctionError("glVertexArrayBindingDivisor");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexArrayBindVertexBufferEXT(GLuint,GLuint,GLuint,GLintptr,GLsizei){printMissingFunctionError("glVertexArrayBindVertexBufferEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexArrayColorOffsetEXT(GLuint,GLuint,GLint,GLenum,GLsizei,GLintptr){printMissingFunctionError("glVertexArrayColorOffsetEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexArrayEdgeFlagOffsetEXT(GLuint,GLuint,GLsizei,GLintptr){printMissingFunctionError("glVertexArrayEdgeFlagOffsetEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexArrayElementBuffer(GLuint,GLuint){printMissingFunctionError("glVertexArrayElementBuffer");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexArrayFogCoordOffsetEXT(GLuint,GLuint,GLenum,GLsizei,GLintptr){printMissingFunctionError("glVertexArrayFogCoordOffsetEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexArrayIndexOffsetEXT(GLuint,GLuint,GLenum,GLsizei,GLintptr){printMissingFunctionError("glVertexArrayIndexOffsetEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexArrayMultiTexCoordOffsetEXT(GLuint,GLuint,GLenum,GLint,GLenum,GLsizei,GLintptr){printMissingFunctionError("glVertexArrayMultiTexCoordOffsetEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexArrayNormalOffsetEXT(GLuint,GLuint,GLenum,GLsizei,GLintptr){printMissingFunctionError("glVertexArrayNormalOffsetEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexArrayParameteriAPPLE(GLenum,GLint){printMissingFunctionError("glVertexArrayParameteriAPPLE");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexArrayRangeAPPLE(GLsizei,void*){printMissingFunctionError("glVertexArrayRangeAPPLE");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexArrayRangeNV(GLsizei,const void*){printMissingFunctionError("glVertexArrayRangeNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexArraySecondaryColorOffsetEXT(GLuint,GLuint,GLint,GLenum,GLsizei,GLintptr){printMissingFunctionError("glVertexArraySecondaryColorOffsetEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexArrayTexCoordOffsetEXT(GLuint,GLuint,GLint,GLenum,GLsizei,GLintptr){printMissingFunctionError("glVertexArrayTexCoordOffsetEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexArrayVertexAttribBindingEXT(GLuint,GLuint,GLuint){printMissingFunctionError("glVertexArrayVertexAttribBindingEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexArrayVertexAttribDivisorEXT(GLuint,GLuint,GLuint){printMissingFunctionError("glVertexArrayVertexAttribDivisorEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexArrayVertexAttribFormatEXT(GLuint,GLuint,GLint,GLenum,GLboolean,GLuint){printMissingFunctionError("glVertexArrayVertexAttribFormatEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexArrayVertexAttribIFormatEXT(GLuint,GLuint,GLint,GLenum,GLuint){printMissingFunctionError("glVertexArrayVertexAttribIFormatEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexArrayVertexAttribIOffsetEXT(GLuint,GLuint,GLuint,GLint,GLenum,GLsizei,GLintptr){printMissingFunctionError("glVertexArrayVertexAttribIOffsetEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexArrayVertexAttribLFormatEXT(GLuint,GLuint,GLint,GLenum,GLuint){printMissingFunctionError("glVertexArrayVertexAttribLFormatEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexArrayVertexAttribLOffsetEXT(GLuint,GLuint,GLuint,GLint,GLenum,GLsizei,GLintptr){printMissingFunctionError("glVertexArrayVertexAttribLOffsetEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexArrayVertexAttribOffsetEXT(GLuint,GLuint,GLuint,GLint,GLenum,GLboolean,GLsizei,GLintptr){printMissingFunctionError("glVertexArrayVertexAttribOffsetEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexArrayVertexBindingDivisorEXT(GLuint,GLuint,GLuint){printMissingFunctionError("glVertexArrayVertexBindingDivisorEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexArrayVertexBuffer(GLuint,GLuint,GLuint,GLintptr,GLsizei){printMissingFunctionError("glVertexArrayVertexBuffer");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexArrayVertexBuffers(GLuint,GLuint,GLsizei,const GLuint*,const GLintptr*,const GLsizei*){printMissingFunctionError("glVertexArrayVertexBuffers");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexArrayVertexOffsetEXT(GLuint,GLuint,GLint,GLenum,GLsizei,GLintptr){printMissingFunctionError("glVertexArrayVertexOffsetEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib1dARB(GLuint,GLdouble){printMissingFunctionError("glVertexAttrib1dARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib1d(GLuint,GLdouble){printMissingFunctionError("glVertexAttrib1d");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib1dNV(GLuint,GLdouble){printMissingFunctionError("glVertexAttrib1dNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib1dvARB(GLuint,const GLdouble*){printMissingFunctionError("glVertexAttrib1dvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib1dv(GLuint,const GLdouble*){printMissingFunctionError("glVertexAttrib1dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib1dvNV(GLuint,const GLdouble*){printMissingFunctionError("glVertexAttrib1dvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib1fARB(GLuint,GLfloat){printMissingFunctionError("glVertexAttrib1fARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib1f(GLuint,GLfloat){printMissingFunctionError("glVertexAttrib1f");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib1fNV(GLuint,GLfloat){printMissingFunctionError("glVertexAttrib1fNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib1fvARB(GLuint,const GLfloat*){printMissingFunctionError("glVertexAttrib1fvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib1fv(GLuint,const GLfloat*){printMissingFunctionError("glVertexAttrib1fv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib1fvNV(GLuint,const GLfloat*){printMissingFunctionError("glVertexAttrib1fvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib1hNV(GLuint,GLhalfNV){printMissingFunctionError("glVertexAttrib1hNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib1hvNV(GLuint,const GLhalfNV*){printMissingFunctionError("glVertexAttrib1hvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib1sARB(GLuint,GLshort){printMissingFunctionError("glVertexAttrib1sARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib1s(GLuint,GLshort){printMissingFunctionError("glVertexAttrib1s");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib1sNV(GLuint,GLshort){printMissingFunctionError("glVertexAttrib1sNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib1svARB(GLuint,const GLshort*){printMissingFunctionError("glVertexAttrib1svARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib1sv(GLuint,const GLshort*){printMissingFunctionError("glVertexAttrib1sv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib1svNV(GLuint,const GLshort*){printMissingFunctionError("glVertexAttrib1svNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib2dARB(GLuint,GLdouble,GLdouble){printMissingFunctionError("glVertexAttrib2dARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib2d(GLuint,GLdouble,GLdouble){printMissingFunctionError("glVertexAttrib2d");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib2dNV(GLuint,GLdouble,GLdouble){printMissingFunctionError("glVertexAttrib2dNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib2dvARB(GLuint,const GLdouble*){printMissingFunctionError("glVertexAttrib2dvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib2dv(GLuint,const GLdouble*){printMissingFunctionError("glVertexAttrib2dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib2dvNV(GLuint,const GLdouble*){printMissingFunctionError("glVertexAttrib2dvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib2fARB(GLuint,GLfloat,GLfloat){printMissingFunctionError("glVertexAttrib2fARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib2f(GLuint,GLfloat,GLfloat){printMissingFunctionError("glVertexAttrib2f");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib2fNV(GLuint,GLfloat,GLfloat){printMissingFunctionError("glVertexAttrib2fNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib2fvARB(GLuint,const GLfloat*){printMissingFunctionError("glVertexAttrib2fvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib2fv(GLuint,const GLfloat*){printMissingFunctionError("glVertexAttrib2fv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib2fvNV(GLuint,const GLfloat*){printMissingFunctionError("glVertexAttrib2fvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib2hNV(GLuint,GLhalfNV,GLhalfNV){printMissingFunctionError("glVertexAttrib2hNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib2hvNV(GLuint,const GLhalfNV*){printMissingFunctionError("glVertexAttrib2hvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib2sARB(GLuint,GLshort,GLshort){printMissingFunctionError("glVertexAttrib2sARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib2s(GLuint,GLshort,GLshort){printMissingFunctionError("glVertexAttrib2s");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib2sNV(GLuint,GLshort,GLshort){printMissingFunctionError("glVertexAttrib2sNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib2svARB(GLuint,const GLshort*){printMissingFunctionError("glVertexAttrib2svARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib2sv(GLuint,const GLshort*){printMissingFunctionError("glVertexAttrib2sv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib2svNV(GLuint,const GLshort*){printMissingFunctionError("glVertexAttrib2svNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib3dARB(GLuint,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glVertexAttrib3dARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib3d(GLuint,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glVertexAttrib3d");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib3dNV(GLuint,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glVertexAttrib3dNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib3dvARB(GLuint,const GLdouble*){printMissingFunctionError("glVertexAttrib3dvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib3dv(GLuint,const GLdouble*){printMissingFunctionError("glVertexAttrib3dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib3dvNV(GLuint,const GLdouble*){printMissingFunctionError("glVertexAttrib3dvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib3fARB(GLuint,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glVertexAttrib3fARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib3f(GLuint,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glVertexAttrib3f");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib3fNV(GLuint,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glVertexAttrib3fNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib3fvARB(GLuint,const GLfloat*){printMissingFunctionError("glVertexAttrib3fvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib3fv(GLuint,const GLfloat*){printMissingFunctionError("glVertexAttrib3fv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib3fvNV(GLuint,const GLfloat*){printMissingFunctionError("glVertexAttrib3fvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib3hNV(GLuint,GLhalfNV,GLhalfNV,GLhalfNV){printMissingFunctionError("glVertexAttrib3hNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib3hvNV(GLuint,const GLhalfNV*){printMissingFunctionError("glVertexAttrib3hvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib3sARB(GLuint,GLshort,GLshort,GLshort){printMissingFunctionError("glVertexAttrib3sARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib3s(GLuint,GLshort,GLshort,GLshort){printMissingFunctionError("glVertexAttrib3s");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib3sNV(GLuint,GLshort,GLshort,GLshort){printMissingFunctionError("glVertexAttrib3sNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib3svARB(GLuint,const GLshort*){printMissingFunctionError("glVertexAttrib3svARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib3sv(GLuint,const GLshort*){printMissingFunctionError("glVertexAttrib3sv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib3svNV(GLuint,const GLshort*){printMissingFunctionError("glVertexAttrib3svNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib4bvARB(GLuint,const GLbyte*){printMissingFunctionError("glVertexAttrib4bvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib4bv(GLuint,const GLbyte*){printMissingFunctionError("glVertexAttrib4bv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib4dARB(GLuint,GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glVertexAttrib4dARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib4d(GLuint,GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glVertexAttrib4d");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib4dNV(GLuint,GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glVertexAttrib4dNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib4dvARB(GLuint,const GLdouble*){printMissingFunctionError("glVertexAttrib4dvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib4dv(GLuint,const GLdouble*){printMissingFunctionError("glVertexAttrib4dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib4dvNV(GLuint,const GLdouble*){printMissingFunctionError("glVertexAttrib4dvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib4fARB(GLuint,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glVertexAttrib4fARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib4f(GLuint,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glVertexAttrib4f");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib4fNV(GLuint,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glVertexAttrib4fNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib4fvARB(GLuint,const GLfloat*){printMissingFunctionError("glVertexAttrib4fvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib4fv(GLuint,const GLfloat*){printMissingFunctionError("glVertexAttrib4fv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib4fvNV(GLuint,const GLfloat*){printMissingFunctionError("glVertexAttrib4fvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib4hNV(GLuint,GLhalfNV,GLhalfNV,GLhalfNV,GLhalfNV){printMissingFunctionError("glVertexAttrib4hNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib4hvNV(GLuint,const GLhalfNV*){printMissingFunctionError("glVertexAttrib4hvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib4ivARB(GLuint,const GLint*){printMissingFunctionError("glVertexAttrib4ivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib4iv(GLuint,const GLint*){printMissingFunctionError("glVertexAttrib4iv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib4NbvARB(GLuint,const GLbyte*){printMissingFunctionError("glVertexAttrib4NbvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib4Nbv(GLuint,const GLbyte*){printMissingFunctionError("glVertexAttrib4Nbv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib4NivARB(GLuint,const GLint*){printMissingFunctionError("glVertexAttrib4NivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib4Niv(GLuint,const GLint*){printMissingFunctionError("glVertexAttrib4Niv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib4NsvARB(GLuint,const GLshort*){printMissingFunctionError("glVertexAttrib4NsvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib4Nsv(GLuint,const GLshort*){printMissingFunctionError("glVertexAttrib4Nsv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib4NubARB(GLuint,GLubyte,GLubyte,GLubyte,GLubyte){printMissingFunctionError("glVertexAttrib4NubARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib4Nub(GLuint,GLubyte,GLubyte,GLubyte,GLubyte){printMissingFunctionError("glVertexAttrib4Nub");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib4NubvARB(GLuint,const GLubyte*){printMissingFunctionError("glVertexAttrib4NubvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib4Nubv(GLuint,const GLubyte*){printMissingFunctionError("glVertexAttrib4Nubv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib4NuivARB(GLuint,const GLuint*){printMissingFunctionError("glVertexAttrib4NuivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib4Nuiv(GLuint,const GLuint*){printMissingFunctionError("glVertexAttrib4Nuiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib4NusvARB(GLuint,const GLushort*){printMissingFunctionError("glVertexAttrib4NusvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib4Nusv(GLuint,const GLushort*){printMissingFunctionError("glVertexAttrib4Nusv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib4sARB(GLuint,GLshort,GLshort,GLshort,GLshort){printMissingFunctionError("glVertexAttrib4sARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib4s(GLuint,GLshort,GLshort,GLshort,GLshort){printMissingFunctionError("glVertexAttrib4s");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib4sNV(GLuint,GLshort,GLshort,GLshort,GLshort){printMissingFunctionError("glVertexAttrib4sNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib4svARB(GLuint,const GLshort*){printMissingFunctionError("glVertexAttrib4svARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib4sv(GLuint,const GLshort*){printMissingFunctionError("glVertexAttrib4sv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib4svNV(GLuint,const GLshort*){printMissingFunctionError("glVertexAttrib4svNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib4ubNV(GLuint,GLubyte,GLubyte,GLubyte,GLubyte){printMissingFunctionError("glVertexAttrib4ubNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib4ubvARB(GLuint,const GLubyte*){printMissingFunctionError("glVertexAttrib4ubvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib4ubv(GLuint,const GLubyte*){printMissingFunctionError("glVertexAttrib4ubv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib4ubvNV(GLuint,const GLubyte*){printMissingFunctionError("glVertexAttrib4ubvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib4uivARB(GLuint,const GLuint*){printMissingFunctionError("glVertexAttrib4uivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib4uiv(GLuint,const GLuint*){printMissingFunctionError("glVertexAttrib4uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib4usvARB(GLuint,const GLushort*){printMissingFunctionError("glVertexAttrib4usvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttrib4usv(GLuint,const GLushort*){printMissingFunctionError("glVertexAttrib4usv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribArrayObjectATI(GLuint,GLint,GLenum,GLboolean,GLsizei,GLuint,GLuint){printMissingFunctionError("glVertexAttribArrayObjectATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribBinding(GLuint,GLuint){printMissingFunctionError("glVertexAttribBinding");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribDivisorARB(GLuint,GLuint){printMissingFunctionError("glVertexAttribDivisorARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribDivisor(GLuint,GLuint){printMissingFunctionError("glVertexAttribDivisor");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribFormat(GLuint,GLint,GLenum,GLboolean,GLuint){printMissingFunctionError("glVertexAttribFormat");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribFormatNV(GLuint,GLint,GLenum,GLboolean,GLsizei){printMissingFunctionError("glVertexAttribFormatNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribI1iEXT(GLuint,GLint){printMissingFunctionError("glVertexAttribI1iEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribI1i(GLuint,GLint){printMissingFunctionError("glVertexAttribI1i");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribI1ivEXT(GLuint,const GLint*){printMissingFunctionError("glVertexAttribI1ivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribI1iv(GLuint,const GLint*){printMissingFunctionError("glVertexAttribI1iv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribI1uiEXT(GLuint,GLuint){printMissingFunctionError("glVertexAttribI1uiEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribI1ui(GLuint,GLuint){printMissingFunctionError("glVertexAttribI1ui");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribI1uivEXT(GLuint,const GLuint*){printMissingFunctionError("glVertexAttribI1uivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribI1uiv(GLuint,const GLuint*){printMissingFunctionError("glVertexAttribI1uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribI2iEXT(GLuint,GLint,GLint){printMissingFunctionError("glVertexAttribI2iEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribI2i(GLuint,GLint,GLint){printMissingFunctionError("glVertexAttribI2i");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribI2ivEXT(GLuint,const GLint*){printMissingFunctionError("glVertexAttribI2ivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribI2iv(GLuint,const GLint*){printMissingFunctionError("glVertexAttribI2iv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribI2uiEXT(GLuint,GLuint,GLuint){printMissingFunctionError("glVertexAttribI2uiEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribI2ui(GLuint,GLuint,GLuint){printMissingFunctionError("glVertexAttribI2ui");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribI2uivEXT(GLuint,const GLuint*){printMissingFunctionError("glVertexAttribI2uivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribI2uiv(GLuint,const GLuint*){printMissingFunctionError("glVertexAttribI2uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribI3iEXT(GLuint,GLint,GLint,GLint){printMissingFunctionError("glVertexAttribI3iEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribI3i(GLuint,GLint,GLint,GLint){printMissingFunctionError("glVertexAttribI3i");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribI3ivEXT(GLuint,const GLint*){printMissingFunctionError("glVertexAttribI3ivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribI3iv(GLuint,const GLint*){printMissingFunctionError("glVertexAttribI3iv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribI3uiEXT(GLuint,GLuint,GLuint,GLuint){printMissingFunctionError("glVertexAttribI3uiEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribI3ui(GLuint,GLuint,GLuint,GLuint){printMissingFunctionError("glVertexAttribI3ui");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribI3uivEXT(GLuint,const GLuint*){printMissingFunctionError("glVertexAttribI3uivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribI3uiv(GLuint,const GLuint*){printMissingFunctionError("glVertexAttribI3uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribI4bvEXT(GLuint,const GLbyte*){printMissingFunctionError("glVertexAttribI4bvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribI4bv(GLuint,const GLbyte*){printMissingFunctionError("glVertexAttribI4bv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribI4iEXT(GLuint,GLint,GLint,GLint,GLint){printMissingFunctionError("glVertexAttribI4iEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribI4i(GLuint,GLint,GLint,GLint,GLint){printMissingFunctionError("glVertexAttribI4i");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribI4ivEXT(GLuint,const GLint*){printMissingFunctionError("glVertexAttribI4ivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribI4iv(GLuint,const GLint*){printMissingFunctionError("glVertexAttribI4iv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribI4svEXT(GLuint,const GLshort*){printMissingFunctionError("glVertexAttribI4svEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribI4sv(GLuint,const GLshort*){printMissingFunctionError("glVertexAttribI4sv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribI4ubvEXT(GLuint,const GLubyte*){printMissingFunctionError("glVertexAttribI4ubvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribI4ubv(GLuint,const GLubyte*){printMissingFunctionError("glVertexAttribI4ubv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribI4uiEXT(GLuint,GLuint,GLuint,GLuint,GLuint){printMissingFunctionError("glVertexAttribI4uiEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribI4ui(GLuint,GLuint,GLuint,GLuint,GLuint){printMissingFunctionError("glVertexAttribI4ui");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribI4uivEXT(GLuint,const GLuint*){printMissingFunctionError("glVertexAttribI4uivEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribI4uiv(GLuint,const GLuint*){printMissingFunctionError("glVertexAttribI4uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribI4usvEXT(GLuint,const GLushort*){printMissingFunctionError("glVertexAttribI4usvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribI4usv(GLuint,const GLushort*){printMissingFunctionError("glVertexAttribI4usv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribIFormat(GLuint,GLint,GLenum,GLuint){printMissingFunctionError("glVertexAttribIFormat");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribIFormatNV(GLuint,GLint,GLenum,GLsizei){printMissingFunctionError("glVertexAttribIFormatNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribIPointerEXT(GLuint,GLint,GLenum,GLsizei,const void*){printMissingFunctionError("glVertexAttribIPointerEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribIPointer(GLuint,GLint,GLenum,GLsizei,const void*){printMissingFunctionError("glVertexAttribIPointer");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribL1dEXT(GLuint,GLdouble){printMissingFunctionError("glVertexAttribL1dEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribL1d(GLuint,GLdouble){printMissingFunctionError("glVertexAttribL1d");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribL1dvEXT(GLuint,const GLdouble*){printMissingFunctionError("glVertexAttribL1dvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribL1dv(GLuint,const GLdouble*){printMissingFunctionError("glVertexAttribL1dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribL1i64NV(GLuint,GLint64EXT){printMissingFunctionError("glVertexAttribL1i64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribL1i64vNV(GLuint,const GLint64EXT*){printMissingFunctionError("glVertexAttribL1i64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribL1ui64ARB(GLuint,GLuint64EXT){printMissingFunctionError("glVertexAttribL1ui64ARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribL1ui64NV(GLuint,GLuint64EXT){printMissingFunctionError("glVertexAttribL1ui64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribL1ui64vARB(GLuint,const GLuint64EXT*){printMissingFunctionError("glVertexAttribL1ui64vARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribL1ui64vNV(GLuint,const GLuint64EXT*){printMissingFunctionError("glVertexAttribL1ui64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribL2dEXT(GLuint,GLdouble,GLdouble){printMissingFunctionError("glVertexAttribL2dEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribL2d(GLuint,GLdouble,GLdouble){printMissingFunctionError("glVertexAttribL2d");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribL2dvEXT(GLuint,const GLdouble*){printMissingFunctionError("glVertexAttribL2dvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribL2dv(GLuint,const GLdouble*){printMissingFunctionError("glVertexAttribL2dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribL2i64NV(GLuint,GLint64EXT,GLint64EXT){printMissingFunctionError("glVertexAttribL2i64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribL2i64vNV(GLuint,const GLint64EXT*){printMissingFunctionError("glVertexAttribL2i64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribL2ui64NV(GLuint,GLuint64EXT,GLuint64EXT){printMissingFunctionError("glVertexAttribL2ui64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribL2ui64vNV(GLuint,const GLuint64EXT*){printMissingFunctionError("glVertexAttribL2ui64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribL3dEXT(GLuint,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glVertexAttribL3dEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribL3d(GLuint,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glVertexAttribL3d");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribL3dvEXT(GLuint,const GLdouble*){printMissingFunctionError("glVertexAttribL3dvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribL3dv(GLuint,const GLdouble*){printMissingFunctionError("glVertexAttribL3dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribL3i64NV(GLuint,GLint64EXT,GLint64EXT,GLint64EXT){printMissingFunctionError("glVertexAttribL3i64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribL3i64vNV(GLuint,const GLint64EXT*){printMissingFunctionError("glVertexAttribL3i64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribL3ui64NV(GLuint,GLuint64EXT,GLuint64EXT,GLuint64EXT){printMissingFunctionError("glVertexAttribL3ui64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribL3ui64vNV(GLuint,const GLuint64EXT*){printMissingFunctionError("glVertexAttribL3ui64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribL4dEXT(GLuint,GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glVertexAttribL4dEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribL4d(GLuint,GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glVertexAttribL4d");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribL4dvEXT(GLuint,const GLdouble*){printMissingFunctionError("glVertexAttribL4dvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribL4dv(GLuint,const GLdouble*){printMissingFunctionError("glVertexAttribL4dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribL4i64NV(GLuint,GLint64EXT,GLint64EXT,GLint64EXT,GLint64EXT){printMissingFunctionError("glVertexAttribL4i64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribL4i64vNV(GLuint,const GLint64EXT*){printMissingFunctionError("glVertexAttribL4i64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribL4ui64NV(GLuint,GLuint64EXT,GLuint64EXT,GLuint64EXT,GLuint64EXT){printMissingFunctionError("glVertexAttribL4ui64NV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribL4ui64vNV(GLuint,const GLuint64EXT*){printMissingFunctionError("glVertexAttribL4ui64vNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribLFormat(GLuint,GLint,GLenum,GLuint){printMissingFunctionError("glVertexAttribLFormat");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribLFormatNV(GLuint,GLint,GLenum,GLsizei){printMissingFunctionError("glVertexAttribLFormatNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribLPointerEXT(GLuint,GLint,GLenum,GLsizei,const void*){printMissingFunctionError("glVertexAttribLPointerEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribLPointer(GLuint,GLint,GLenum,GLsizei,const void*){printMissingFunctionError("glVertexAttribLPointer");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribP1ui(GLuint,GLenum,GLboolean,GLuint){printMissingFunctionError("glVertexAttribP1ui");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribP1uiv(GLuint,GLenum,GLboolean,const GLuint*){printMissingFunctionError("glVertexAttribP1uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribP2ui(GLuint,GLenum,GLboolean,GLuint){printMissingFunctionError("glVertexAttribP2ui");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribP2uiv(GLuint,GLenum,GLboolean,const GLuint*){printMissingFunctionError("glVertexAttribP2uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribP3ui(GLuint,GLenum,GLboolean,GLuint){printMissingFunctionError("glVertexAttribP3ui");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribP3uiv(GLuint,GLenum,GLboolean,const GLuint*){printMissingFunctionError("glVertexAttribP3uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribP4ui(GLuint,GLenum,GLboolean,GLuint){printMissingFunctionError("glVertexAttribP4ui");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribP4uiv(GLuint,GLenum,GLboolean,const GLuint*){printMissingFunctionError("glVertexAttribP4uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribParameteriAMD(GLuint,GLenum,GLint){printMissingFunctionError("glVertexAttribParameteriAMD");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribPointerARB(GLuint,GLint,GLenum,GLboolean,GLsizei,const void*){printMissingFunctionError("glVertexAttribPointerARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribPointer(GLuint,GLint,GLenum,GLboolean,GLsizei,const void*){printMissingFunctionError("glVertexAttribPointer");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribPointerNV(GLuint,GLint,GLenum,GLsizei,const void*){printMissingFunctionError("glVertexAttribPointerNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribs1dvNV(GLuint,GLsizei,const GLdouble*){printMissingFunctionError("glVertexAttribs1dvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribs1fvNV(GLuint,GLsizei,const GLfloat*){printMissingFunctionError("glVertexAttribs1fvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribs1hvNV(GLuint,GLsizei,const GLhalfNV*){printMissingFunctionError("glVertexAttribs1hvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribs1svNV(GLuint,GLsizei,const GLshort*){printMissingFunctionError("glVertexAttribs1svNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribs2dvNV(GLuint,GLsizei,const GLdouble*){printMissingFunctionError("glVertexAttribs2dvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribs2fvNV(GLuint,GLsizei,const GLfloat*){printMissingFunctionError("glVertexAttribs2fvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribs2hvNV(GLuint,GLsizei,const GLhalfNV*){printMissingFunctionError("glVertexAttribs2hvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribs2svNV(GLuint,GLsizei,const GLshort*){printMissingFunctionError("glVertexAttribs2svNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribs3dvNV(GLuint,GLsizei,const GLdouble*){printMissingFunctionError("glVertexAttribs3dvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribs3fvNV(GLuint,GLsizei,const GLfloat*){printMissingFunctionError("glVertexAttribs3fvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribs3hvNV(GLuint,GLsizei,const GLhalfNV*){printMissingFunctionError("glVertexAttribs3hvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribs3svNV(GLuint,GLsizei,const GLshort*){printMissingFunctionError("glVertexAttribs3svNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribs4dvNV(GLuint,GLsizei,const GLdouble*){printMissingFunctionError("glVertexAttribs4dvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribs4fvNV(GLuint,GLsizei,const GLfloat*){printMissingFunctionError("glVertexAttribs4fvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribs4hvNV(GLuint,GLsizei,const GLhalfNV*){printMissingFunctionError("glVertexAttribs4hvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribs4svNV(GLuint,GLsizei,const GLshort*){printMissingFunctionError("glVertexAttribs4svNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexAttribs4ubvNV(GLuint,GLsizei,const GLubyte*){printMissingFunctionError("glVertexAttribs4ubvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexBindingDivisor(GLuint,GLuint){printMissingFunctionError("glVertexBindingDivisor");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexBlendARB(GLint){printMissingFunctionError("glVertexBlendARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexBlendEnvfATI(GLenum,GLfloat){printMissingFunctionError("glVertexBlendEnvfATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexBlendEnviATI(GLenum,GLint){printMissingFunctionError("glVertexBlendEnviATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexFormatNV(GLint,GLenum,GLsizei){printMissingFunctionError("glVertexFormatNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexP2ui(GLenum,GLuint){printMissingFunctionError("glVertexP2ui");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexP2uiv(GLenum,const GLuint*){printMissingFunctionError("glVertexP2uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexP3ui(GLenum,GLuint){printMissingFunctionError("glVertexP3ui");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexP3uiv(GLenum,const GLuint*){printMissingFunctionError("glVertexP3uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexP4ui(GLenum,GLuint){printMissingFunctionError("glVertexP4ui");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexP4uiv(GLenum,const GLuint*){printMissingFunctionError("glVertexP4uiv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexPointerEXT(GLint,GLenum,GLsizei,GLsizei,const void*){printMissingFunctionError("glVertexPointerEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexPointer(GLint,GLenum,GLsizei,const GLvoid*){printMissingFunctionError("glVertexPointer");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexPointerListIBM(GLint,GLenum,GLint,const void**,GLint){printMissingFunctionError("glVertexPointerListIBM");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexPointervINTEL(GLint,GLenum,const void**){printMissingFunctionError("glVertexPointervINTEL");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexStream1dATI(GLenum,GLdouble){printMissingFunctionError("glVertexStream1dATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexStream1dvATI(GLenum,const GLdouble*){printMissingFunctionError("glVertexStream1dvATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexStream1fATI(GLenum,GLfloat){printMissingFunctionError("glVertexStream1fATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexStream1fvATI(GLenum,const GLfloat*){printMissingFunctionError("glVertexStream1fvATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexStream1iATI(GLenum,GLint){printMissingFunctionError("glVertexStream1iATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexStream1ivATI(GLenum,const GLint*){printMissingFunctionError("glVertexStream1ivATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexStream1sATI(GLenum,GLshort){printMissingFunctionError("glVertexStream1sATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexStream1svATI(GLenum,const GLshort*){printMissingFunctionError("glVertexStream1svATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexStream2dATI(GLenum,GLdouble,GLdouble){printMissingFunctionError("glVertexStream2dATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexStream2dvATI(GLenum,const GLdouble*){printMissingFunctionError("glVertexStream2dvATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexStream2fATI(GLenum,GLfloat,GLfloat){printMissingFunctionError("glVertexStream2fATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexStream2fvATI(GLenum,const GLfloat*){printMissingFunctionError("glVertexStream2fvATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexStream2iATI(GLenum,GLint,GLint){printMissingFunctionError("glVertexStream2iATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexStream2ivATI(GLenum,const GLint*){printMissingFunctionError("glVertexStream2ivATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexStream2sATI(GLenum,GLshort,GLshort){printMissingFunctionError("glVertexStream2sATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexStream2svATI(GLenum,const GLshort*){printMissingFunctionError("glVertexStream2svATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexStream3dATI(GLenum,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glVertexStream3dATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexStream3dvATI(GLenum,const GLdouble*){printMissingFunctionError("glVertexStream3dvATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexStream3fATI(GLenum,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glVertexStream3fATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexStream3fvATI(GLenum,const GLfloat*){printMissingFunctionError("glVertexStream3fvATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexStream3iATI(GLenum,GLint,GLint,GLint){printMissingFunctionError("glVertexStream3iATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexStream3ivATI(GLenum,const GLint*){printMissingFunctionError("glVertexStream3ivATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexStream3sATI(GLenum,GLshort,GLshort,GLshort){printMissingFunctionError("glVertexStream3sATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexStream3svATI(GLenum,const GLshort*){printMissingFunctionError("glVertexStream3svATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexStream4dATI(GLenum,GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glVertexStream4dATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexStream4dvATI(GLenum,const GLdouble*){printMissingFunctionError("glVertexStream4dvATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexStream4fATI(GLenum,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glVertexStream4fATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexStream4fvATI(GLenum,const GLfloat*){printMissingFunctionError("glVertexStream4fvATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexStream4iATI(GLenum,GLint,GLint,GLint,GLint){printMissingFunctionError("glVertexStream4iATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexStream4ivATI(GLenum,const GLint*){printMissingFunctionError("glVertexStream4ivATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexStream4sATI(GLenum,GLshort,GLshort,GLshort,GLshort){printMissingFunctionError("glVertexStream4sATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexStream4svATI(GLenum,const GLshort*){printMissingFunctionError("glVertexStream4svATI");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexWeightfEXT(GLfloat){printMissingFunctionError("glVertexWeightfEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexWeightfvEXT(const GLfloat*){printMissingFunctionError("glVertexWeightfvEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexWeighthNV(GLhalfNV){printMissingFunctionError("glVertexWeighthNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexWeighthvNV(const GLhalfNV*){printMissingFunctionError("glVertexWeighthvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVertexWeightPointerEXT(GLint,GLenum,GLsizei,const void*){printMissingFunctionError("glVertexWeightPointerEXT");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVideoCaptureStreamParameterdvNV(GLuint,GLuint,GLenum,const GLdouble*){printMissingFunctionError("glVideoCaptureStreamParameterdvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVideoCaptureStreamParameterfvNV(GLuint,GLuint,GLenum,const GLfloat*){printMissingFunctionError("glVideoCaptureStreamParameterfvNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglVideoCaptureStreamParameterivNV(GLuint,GLuint,GLenum,const GLint*){printMissingFunctionError("glVideoCaptureStreamParameterivNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglViewportArrayv(GLuint,GLsizei,const GLfloat*){printMissingFunctionError("glViewportArrayv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglViewport(GLint,GLint,GLsizei,GLsizei){printMissingFunctionError("glViewport");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglViewportIndexedf(GLuint,GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glViewportIndexedf");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglViewportIndexedfv(GLuint,const GLfloat*){printMissingFunctionError("glViewportIndexedfv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglViewportSwizzleNV(GLuint,GLenum,GLenum,GLenum,GLenum){printMissingFunctionError("glViewportSwizzleNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWaitSync(GLsync,GLbitfield,GLuint64){printMissingFunctionError("glWaitSync");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWeightbvARB(GLint,const GLbyte*){printMissingFunctionError("glWeightbvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWeightdvARB(GLint,const GLdouble*){printMissingFunctionError("glWeightdvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWeightfvARB(GLint,const GLfloat*){printMissingFunctionError("glWeightfvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWeightivARB(GLint,const GLint*){printMissingFunctionError("glWeightivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWeightPathsNV(GLuint,GLsizei,const GLuint*,const GLfloat*){printMissingFunctionError("glWeightPathsNV");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWeightPointerARB(GLint,GLenum,GLsizei,const void*){printMissingFunctionError("glWeightPointerARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWeightsvARB(GLint,const GLshort*){printMissingFunctionError("glWeightsvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWeightubvARB(GLint,const GLubyte*){printMissingFunctionError("glWeightubvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWeightuivARB(GLint,const GLuint*){printMissingFunctionError("glWeightuivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWeightusvARB(GLint,const GLushort*){printMissingFunctionError("glWeightusvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos2dARB(GLdouble,GLdouble){printMissingFunctionError("glWindowPos2dARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos2d(GLdouble,GLdouble){printMissingFunctionError("glWindowPos2d");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos2dMESA(GLdouble,GLdouble){printMissingFunctionError("glWindowPos2dMESA");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos2dvARB(const GLdouble*){printMissingFunctionError("glWindowPos2dvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos2dv(const GLdouble*){printMissingFunctionError("glWindowPos2dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos2dvMESA(const GLdouble*){printMissingFunctionError("glWindowPos2dvMESA");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos2fARB(GLfloat,GLfloat){printMissingFunctionError("glWindowPos2fARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos2f(GLfloat,GLfloat){printMissingFunctionError("glWindowPos2f");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos2fMESA(GLfloat,GLfloat){printMissingFunctionError("glWindowPos2fMESA");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos2fvARB(const GLfloat*){printMissingFunctionError("glWindowPos2fvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos2fv(const GLfloat*){printMissingFunctionError("glWindowPos2fv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos2fvMESA(const GLfloat*){printMissingFunctionError("glWindowPos2fvMESA");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos2iARB(GLint,GLint){printMissingFunctionError("glWindowPos2iARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos2i(GLint,GLint){printMissingFunctionError("glWindowPos2i");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos2iMESA(GLint,GLint){printMissingFunctionError("glWindowPos2iMESA");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos2ivARB(const GLint*){printMissingFunctionError("glWindowPos2ivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos2iv(const GLint*){printMissingFunctionError("glWindowPos2iv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos2ivMESA(const GLint*){printMissingFunctionError("glWindowPos2ivMESA");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos2sARB(GLshort,GLshort){printMissingFunctionError("glWindowPos2sARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos2s(GLshort,GLshort){printMissingFunctionError("glWindowPos2s");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos2sMESA(GLshort,GLshort){printMissingFunctionError("glWindowPos2sMESA");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos2svARB(const GLshort*){printMissingFunctionError("glWindowPos2svARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos2sv(const GLshort*){printMissingFunctionError("glWindowPos2sv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos2svMESA(const GLshort*){printMissingFunctionError("glWindowPos2svMESA");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos3dARB(GLdouble,GLdouble,GLdouble){printMissingFunctionError("glWindowPos3dARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos3d(GLdouble,GLdouble,GLdouble){printMissingFunctionError("glWindowPos3d");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos3dMESA(GLdouble,GLdouble,GLdouble){printMissingFunctionError("glWindowPos3dMESA");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos3dvARB(const GLdouble*){printMissingFunctionError("glWindowPos3dvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos3dv(const GLdouble*){printMissingFunctionError("glWindowPos3dv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos3dvMESA(const GLdouble*){printMissingFunctionError("glWindowPos3dvMESA");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos3fARB(GLfloat,GLfloat,GLfloat){printMissingFunctionError("glWindowPos3fARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos3f(GLfloat,GLfloat,GLfloat){printMissingFunctionError("glWindowPos3f");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos3fMESA(GLfloat,GLfloat,GLfloat){printMissingFunctionError("glWindowPos3fMESA");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos3fvARB(const GLfloat*){printMissingFunctionError("glWindowPos3fvARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos3fv(const GLfloat*){printMissingFunctionError("glWindowPos3fv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos3fvMESA(const GLfloat*){printMissingFunctionError("glWindowPos3fvMESA");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos3iARB(GLint,GLint,GLint){printMissingFunctionError("glWindowPos3iARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos3i(GLint,GLint,GLint){printMissingFunctionError("glWindowPos3i");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos3iMESA(GLint,GLint,GLint){printMissingFunctionError("glWindowPos3iMESA");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos3ivARB(const GLint*){printMissingFunctionError("glWindowPos3ivARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos3iv(const GLint*){printMissingFunctionError("glWindowPos3iv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos3ivMESA(const GLint*){printMissingFunctionError("glWindowPos3ivMESA");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos3sARB(GLshort,GLshort,GLshort){printMissingFunctionError("glWindowPos3sARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos3s(GLshort,GLshort,GLshort){printMissingFunctionError("glWindowPos3s");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos3sMESA(GLshort,GLshort,GLshort){printMissingFunctionError("glWindowPos3sMESA");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos3svARB(const GLshort*){printMissingFunctionError("glWindowPos3svARB");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos3sv(const GLshort*){printMissingFunctionError("glWindowPos3sv");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos3svMESA(const GLshort*){printMissingFunctionError("glWindowPos3svMESA");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos4dMESA(GLdouble,GLdouble,GLdouble,GLdouble){printMissingFunctionError("glWindowPos4dMESA");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos4dvMESA(const GLdouble*){printMissingFunctionError("glWindowPos4dvMESA");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos4fMESA(GLfloat,GLfloat,GLfloat,GLfloat){printMissingFunctionError("glWindowPos4fMESA");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos4fvMESA(const GLfloat*){printMissingFunctionError("glWindowPos4fvMESA");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos4iMESA(GLint,GLint,GLint,GLint){printMissingFunctionError("glWindowPos4iMESA");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos4ivMESA(const GLint*){printMissingFunctionError("glWindowPos4ivMESA");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos4sMESA(GLshort,GLshort,GLshort,GLshort){printMissingFunctionError("glWindowPos4sMESA");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWindowPos4svMESA(const GLshort*){printMissingFunctionError("glWindowPos4svMESA");std::exit(1);return (void)0;}
GEGL_EXPORT void geglTrapglWriteMaskEXT(GLuint,GLuint,GLenum,GLenum,GLenum,GLenum){printMissingFunctionError("glWriteMaskEXT");std::exit(1);return (void)0;}
