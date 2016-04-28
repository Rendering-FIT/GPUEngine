const GLubyte* glGetString(GLenum name) { functions()->glGetString(name); }
const GLubyte* glGetStringi(GLenum name, GLuint index) { functions()->glGetStringi(name, index); }
GLbitfield glQueryMatrixxOES(GLfixed* mantissa, GLint* exponent) { functions()->glQueryMatrixxOES(mantissa, exponent); }
GLboolean glAreProgramsResidentNV(GLsizei n, const GLuint* programs, GLboolean* residences) { functions()->glAreProgramsResidentNV(n, programs, residences); }
GLboolean glAreTexturesResidentEXT(GLsizei n, const GLuint* textures, GLboolean* residences) { functions()->glAreTexturesResidentEXT(n, textures, residences); }
GLboolean glAreTexturesResident(GLsizei n, const GLuint* textures, GLboolean* residences) { functions()->glAreTexturesResident(n, textures, residences); }
GLboolean glIsAsyncMarkerSGIX(GLuint marker) { functions()->glIsAsyncMarkerSGIX(marker); }
GLboolean glIsBufferARB(GLuint buffer) { functions()->glIsBufferARB(buffer); }
GLboolean glIsBuffer(GLuint buffer) { functions()->glIsBuffer(buffer); }
GLboolean glIsBufferResidentNV(GLenum target) { functions()->glIsBufferResidentNV(target); }
GLboolean glIsCommandListNV(GLuint list) { functions()->glIsCommandListNV(list); }
GLboolean glIsEnabled(GLenum cap) { functions()->glIsEnabled(cap); }
GLboolean glIsEnabledi(GLenum target, GLuint index) { functions()->glIsEnabledi(target, index); }
GLboolean glIsEnabledIndexedEXT(GLenum target, GLuint index) { functions()->glIsEnabledIndexedEXT(target, index); }
GLboolean glIsFenceAPPLE(GLuint fence) { functions()->glIsFenceAPPLE(fence); }
GLboolean glIsFenceNV(GLuint fence) { functions()->glIsFenceNV(fence); }
GLboolean glIsFramebufferEXT(GLuint framebuffer) { functions()->glIsFramebufferEXT(framebuffer); }
GLboolean glIsFramebuffer(GLuint framebuffer) { functions()->glIsFramebuffer(framebuffer); }
GLboolean glIsImageHandleResidentARB(GLuint64 handle) { functions()->glIsImageHandleResidentARB(handle); }
GLboolean glIsImageHandleResidentNV(GLuint64 handle) { functions()->glIsImageHandleResidentNV(handle); }
GLboolean glIsList(GLuint list) { functions()->glIsList(list); }
GLboolean glIsNameAMD(GLenum identifier, GLuint name) { functions()->glIsNameAMD(identifier, name); }
GLboolean glIsNamedBufferResidentNV(GLuint buffer) { functions()->glIsNamedBufferResidentNV(buffer); }
GLboolean glIsNamedStringARB(GLint namelen, const GLchar* name) { functions()->glIsNamedStringARB(namelen, name); }
GLboolean glIsObjectBufferATI(GLuint buffer) { functions()->glIsObjectBufferATI(buffer); }
GLboolean glIsOcclusionQueryNV(GLuint id) { functions()->glIsOcclusionQueryNV(id); }
GLboolean glIsPathNV(GLuint path) { functions()->glIsPathNV(path); }
GLboolean glIsPointInFillPathNV(GLuint path, GLuint mask, GLfloat x, GLfloat y) { functions()->glIsPointInFillPathNV(path, mask, x, y); }
GLboolean glIsPointInStrokePathNV(GLuint path, GLfloat x, GLfloat y) { functions()->glIsPointInStrokePathNV(path, x, y); }
GLboolean glIsProgramARB(GLuint program) { functions()->glIsProgramARB(program); }
GLboolean glIsProgram(GLuint program) { functions()->glIsProgram(program); }
GLboolean glIsProgramNV(GLuint id) { functions()->glIsProgramNV(id); }
GLboolean glIsProgramPipeline(GLuint pipeline) { functions()->glIsProgramPipeline(pipeline); }
GLboolean glIsQueryARB(GLuint id) { functions()->glIsQueryARB(id); }
GLboolean glIsQuery(GLuint id) { functions()->glIsQuery(id); }
GLboolean glIsRenderbufferEXT(GLuint renderbuffer) { functions()->glIsRenderbufferEXT(renderbuffer); }
GLboolean glIsRenderbuffer(GLuint renderbuffer) { functions()->glIsRenderbuffer(renderbuffer); }
GLboolean glIsSampler(GLuint sampler) { functions()->glIsSampler(sampler); }
GLboolean glIsShader(GLuint shader) { functions()->glIsShader(shader); }
GLboolean glIsStateNV(GLuint state) { functions()->glIsStateNV(state); }
GLboolean glIsSync(GLsync sync) { functions()->glIsSync(sync); }
GLboolean glIsTextureEXT(GLuint texture) { functions()->glIsTextureEXT(texture); }
GLboolean glIsTexture(GLuint texture) { functions()->glIsTexture(texture); }
GLboolean glIsTextureHandleResidentARB(GLuint64 handle) { functions()->glIsTextureHandleResidentARB(handle); }
GLboolean glIsTextureHandleResidentNV(GLuint64 handle) { functions()->glIsTextureHandleResidentNV(handle); }
GLboolean glIsTransformFeedback(GLuint id) { functions()->glIsTransformFeedback(id); }
GLboolean glIsTransformFeedbackNV(GLuint id) { functions()->glIsTransformFeedbackNV(id); }
GLboolean glIsVariantEnabledEXT(GLuint id, GLenum cap) { functions()->glIsVariantEnabledEXT(id, cap); }
GLboolean glIsVertexArrayAPPLE(GLuint array) { functions()->glIsVertexArrayAPPLE(array); }
GLboolean glIsVertexArray(GLuint array) { functions()->glIsVertexArray(array); }
GLboolean glIsVertexAttribEnabledAPPLE(GLuint index, GLenum pname) { functions()->glIsVertexAttribEnabledAPPLE(index, pname); }
GLboolean glPointAlongPathNV(GLuint path, GLsizei startSegment, GLsizei numSegments, GLfloat distance, GLfloat* x, GLfloat* y, GLfloat* tangentX, GLfloat* tangentY) { functions()->glPointAlongPathNV(path, startSegment, numSegments, distance, x, y, tangentX, tangentY); }
GLboolean glTestFenceAPPLE(GLuint fence) { functions()->glTestFenceAPPLE(fence); }
GLboolean glTestFenceNV(GLuint fence) { functions()->glTestFenceNV(fence); }
GLboolean glTestObjectAPPLE(GLenum object, GLuint name) { functions()->glTestObjectAPPLE(object, name); }
GLboolean glUnmapBufferARB(GLenum target) { functions()->glUnmapBufferARB(target); }
GLboolean glUnmapBuffer(GLenum target) { functions()->glUnmapBuffer(target); }
GLboolean glUnmapNamedBufferEXT(GLuint buffer) { functions()->glUnmapNamedBufferEXT(buffer); }
GLboolean glUnmapNamedBuffer(GLuint buffer) { functions()->glUnmapNamedBuffer(buffer); }
GLboolean glVDPAUIsSurfaceNV(GLvdpauSurfaceNV surface) { functions()->glVDPAUIsSurfaceNV(surface); }
GLenum glCheckFramebufferStatusEXT(GLenum target) { functions()->glCheckFramebufferStatusEXT(target); }
GLenum glCheckFramebufferStatus(GLenum target) { functions()->glCheckFramebufferStatus(target); }
GLenum glCheckNamedFramebufferStatusEXT(GLuint framebuffer, GLenum target) { functions()->glCheckNamedFramebufferStatusEXT(framebuffer, target); }
GLenum glCheckNamedFramebufferStatus(GLuint framebuffer, GLenum target) { functions()->glCheckNamedFramebufferStatus(framebuffer, target); }
GLenum glClientWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout) { functions()->glClientWaitSync(sync, flags, timeout); }
GLenum glGetError() { functions()->glGetError(); }
GLenum glGetGraphicsResetStatus() { functions()->glGetGraphicsResetStatus(); }
GLenum glGetGraphicsResetStatusARB() { functions()->glGetGraphicsResetStatusARB(); }
GLenum glObjectPurgeableAPPLE(GLenum objectType, GLuint name, GLenum option) { functions()->glObjectPurgeableAPPLE(objectType, name, option); }
GLenum glObjectUnpurgeableAPPLE(GLenum objectType, GLuint name, GLenum option) { functions()->glObjectUnpurgeableAPPLE(objectType, name, option); }
GLenum glPathGlyphIndexArrayNV(GLuint firstPathName, GLenum fontTarget, const void* fontName, GLbitfield fontStyle, GLuint firstGlyphIndex, GLsizei numGlyphs, GLuint pathParameterTemplate, GLfloat emScale) { functions()->glPathGlyphIndexArrayNV(firstPathName, fontTarget, fontName, fontStyle, firstGlyphIndex, numGlyphs, pathParameterTemplate, emScale); }
GLenum glPathGlyphIndexRangeNV(GLenum fontTarget, const void* fontName, GLbitfield fontStyle, GLuint pathParameterTemplate, GLfloat emScale, GLuint baseAndCount[2]) { functions()->glPathGlyphIndexRangeNV(fontTarget, fontName, fontStyle, pathParameterTemplate, emScale, baseAndCount[2]); }
GLenum glPathMemoryGlyphIndexArrayNV(GLuint firstPathName, GLenum fontTarget, GLsizeiptr fontSize, const void* fontData, GLsizei faceIndex, GLuint firstGlyphIndex, GLsizei numGlyphs, GLuint pathParameterTemplate, GLfloat emScale) { functions()->glPathMemoryGlyphIndexArrayNV(firstPathName, fontTarget, fontSize, fontData, faceIndex, firstGlyphIndex, numGlyphs, pathParameterTemplate, emScale); }
GLenum glVideoCaptureNV(GLuint video_capture_slot, GLuint* sequence_num, GLuint64EXT* capture_time) { functions()->glVideoCaptureNV(video_capture_slot, sequence_num, capture_time); }
GLfloat glGetPathLengthNV(GLuint path, GLsizei startSegment, GLsizei numSegments) { functions()->glGetPathLengthNV(path, startSegment, numSegments); }
GLhandleARB glCreateProgramObjectARB() { functions()->glCreateProgramObjectARB(); }
GLhandleARB glCreateShaderObjectARB(GLenum shaderType) { functions()->glCreateShaderObjectARB(shaderType); }
GLhandleARB glGetHandleARB(GLenum pname) { functions()->glGetHandleARB(pname); }
GLint glFinishAsyncSGIX(GLuint* markerp) { functions()->glFinishAsyncSGIX(markerp); }
GLint glGetAttribLocationARB(GLhandleARB programObj, const GLcharARB* name) { functions()->glGetAttribLocationARB(programObj, name); }
GLint glGetAttribLocation(GLuint program, const GLchar* name) { functions()->glGetAttribLocation(program, name); }
GLint glGetFragDataIndex(GLuint program, const GLchar* name) { functions()->glGetFragDataIndex(program, name); }
GLint glGetFragDataLocationEXT(GLuint program, const GLchar* name) { functions()->glGetFragDataLocationEXT(program, name); }
GLint glGetFragDataLocation(GLuint program, const GLchar* name) { functions()->glGetFragDataLocation(program, name); }
GLint glGetInstrumentsSGIX() { functions()->glGetInstrumentsSGIX(); }
GLint glGetProgramResourceLocation(GLuint program, GLenum programInterface, const GLchar* name) { functions()->glGetProgramResourceLocation(program, programInterface, name); }
GLint glGetProgramResourceLocationIndex(GLuint program, GLenum programInterface, const GLchar* name) { functions()->glGetProgramResourceLocationIndex(program, programInterface, name); }
GLint glGetSubroutineUniformLocation(GLuint program, GLenum shadertype, const GLchar* name) { functions()->glGetSubroutineUniformLocation(program, shadertype, name); }
GLint glGetUniformBufferSizeEXT(GLuint program, GLint location) { functions()->glGetUniformBufferSizeEXT(program, location); }
GLint glGetUniformLocationARB(GLhandleARB programObj, const GLcharARB* name) { functions()->glGetUniformLocationARB(programObj, name); }
GLint glGetUniformLocation(GLuint program, const GLchar* name) { functions()->glGetUniformLocation(program, name); }
GLint glGetVaryingLocationNV(GLuint program, const GLchar* name) { functions()->glGetVaryingLocationNV(program, name); }
GLint glPollAsyncSGIX(GLuint* markerp) { functions()->glPollAsyncSGIX(markerp); }
GLint glPollInstrumentsSGIX(GLint* marker_p) { functions()->glPollInstrumentsSGIX(marker_p); }
GLint glRenderMode(GLenum mode) { functions()->glRenderMode(mode); }
GLintptr glGetUniformOffsetEXT(GLuint program, GLint location) { functions()->glGetUniformOffsetEXT(program, location); }
GLsync glCreateSyncFromCLeventARB(struct _cl_context* context, struct _cl_event* event, GLbitfield flags) { functions()->glCreateSyncFromCLeventARB(context, event, flags); }
GLsync glFenceSync(GLenum condition, GLbitfield flags) { functions()->glFenceSync(condition, flags); }
GLsync glImportSyncEXT(GLenum external_sync_type, GLintptr external_sync, GLbitfield flags) { functions()->glImportSyncEXT(external_sync_type, external_sync, flags); }
GLuint64 glGetImageHandleARB(GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum format) { functions()->glGetImageHandleARB(texture, level, layered, layer, format); }
GLuint64 glGetImageHandleNV(GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum format) { functions()->glGetImageHandleNV(texture, level, layered, layer, format); }
GLuint64 glGetTextureHandleARB(GLuint texture) { functions()->glGetTextureHandleARB(texture); }
GLuint64 glGetTextureHandleNV(GLuint texture) { functions()->glGetTextureHandleNV(texture); }
GLuint64 glGetTextureSamplerHandleARB(GLuint texture, GLuint sampler) { functions()->glGetTextureSamplerHandleARB(texture, sampler); }
GLuint64 glGetTextureSamplerHandleNV(GLuint texture, GLuint sampler) { functions()->glGetTextureSamplerHandleNV(texture, sampler); }
GLuint glBindLightParameterEXT(GLenum light, GLenum value) { functions()->glBindLightParameterEXT(light, value); }
GLuint glBindMaterialParameterEXT(GLenum face, GLenum value) { functions()->glBindMaterialParameterEXT(face, value); }
GLuint glBindParameterEXT(GLenum value) { functions()->glBindParameterEXT(value); }
GLuint glBindTexGenParameterEXT(GLenum unit, GLenum coord, GLenum value) { functions()->glBindTexGenParameterEXT(unit, coord, value); }
GLuint glBindTextureUnitParameterEXT(GLenum unit, GLenum value) { functions()->glBindTextureUnitParameterEXT(unit, value); }
GLuint glCreateProgram() { functions()->glCreateProgram(); }
GLuint glCreateShader(GLenum type) { functions()->glCreateShader(type); }
GLuint glCreateShaderProgramEXT(GLenum type, const GLchar* string) { functions()->glCreateShaderProgramEXT(type, string); }
GLuint glCreateShaderProgramv(GLenum type, GLsizei count, const GLchar*const* strings) { functions()->glCreateShaderProgramv(type, count, strings); }
GLuint glGenAsyncMarkersSGIX(GLsizei range) { functions()->glGenAsyncMarkersSGIX(range); }
GLuint glGenFragmentShadersATI(GLuint range) { functions()->glGenFragmentShadersATI(range); }
GLuint glGenLists(GLsizei range) { functions()->glGenLists(range); }
GLuint glGenPathsNV(GLsizei range) { functions()->glGenPathsNV(range); }
GLuint glGenSymbolsEXT(GLenum datatype, GLenum storagetype, GLenum range, GLuint components) { functions()->glGenSymbolsEXT(datatype, storagetype, range, components); }
GLuint glGenVertexShadersEXT(GLuint range) { functions()->glGenVertexShadersEXT(range); }
GLuint glGetCommandHeaderNV(GLenum tokenID, GLuint size) { functions()->glGetCommandHeaderNV(tokenID, size); }
GLuint glGetDebugMessageLogAMD(GLuint count, GLsizei bufsize, GLenum* categories, GLuint* severities, GLuint* ids, GLsizei* lengths, GLchar* message) { functions()->glGetDebugMessageLogAMD(count, bufsize, categories, severities, ids, lengths, message); }
GLuint glGetDebugMessageLogARB(GLuint count, GLsizei bufSize, GLenum* sources, GLenum* types, GLuint* ids, GLenum* severities, GLsizei* lengths, GLchar* messageLog) { functions()->glGetDebugMessageLogARB(count, bufSize, sources, types, ids, severities, lengths, messageLog); }
GLuint glGetDebugMessageLog(GLuint count, GLsizei bufSize, GLenum* sources, GLenum* types, GLuint* ids, GLenum* severities, GLsizei* lengths, GLchar* messageLog) { functions()->glGetDebugMessageLog(count, bufSize, sources, types, ids, severities, lengths, messageLog); }
GLuint glGetProgramResourceIndex(GLuint program, GLenum programInterface, const GLchar* name) { functions()->glGetProgramResourceIndex(program, programInterface, name); }
GLuint glGetSubroutineIndex(GLuint program, GLenum shadertype, const GLchar* name) { functions()->glGetSubroutineIndex(program, shadertype, name); }
GLuint glGetUniformBlockIndex(GLuint program, const GLchar* uniformBlockName) { functions()->glGetUniformBlockIndex(program, uniformBlockName); }
GLuint glNewObjectBufferATI(GLsizei size, const void* pointer, GLenum usage) { functions()->glNewObjectBufferATI(size, pointer, usage); }
GLushort glGetStageIndexNV(GLenum shadertype) { functions()->glGetStageIndexNV(shadertype); }
GLvdpauSurfaceNV glVDPAURegisterOutputSurfaceNV(const void* vdpSurface, GLenum target, GLsizei numTextureNames, const GLuint* textureNames) { functions()->glVDPAURegisterOutputSurfaceNV(vdpSurface, target, numTextureNames, textureNames); }
GLvdpauSurfaceNV glVDPAURegisterVideoSurfaceNV(const void* vdpSurface, GLenum target, GLsizei numTextureNames, const GLuint* textureNames) { functions()->glVDPAURegisterVideoSurfaceNV(vdpSurface, target, numTextureNames, textureNames); }
void glAccum(GLenum op, GLfloat value) { functions()->glAccum(op, value); }
void glAccumxOES(GLenum op, GLfixed value) { functions()->glAccumxOES(op, value); }
void glActiveProgramEXT(GLuint program) { functions()->glActiveProgramEXT(program); }
void glActiveShaderProgram(GLuint pipeline, GLuint program) { functions()->glActiveShaderProgram(pipeline, program); }
void glActiveStencilFaceEXT(GLenum face) { functions()->glActiveStencilFaceEXT(face); }
void glActiveTextureARB(GLenum texture) { functions()->glActiveTextureARB(texture); }
void glActiveTexture(GLenum texture) { functions()->glActiveTexture(texture); }
void glActiveVaryingNV(GLuint program, const GLchar* name) { functions()->glActiveVaryingNV(program, name); }
void glAlphaFragmentOp1ATI(GLenum op, GLuint dst, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod) { functions()->glAlphaFragmentOp1ATI(op, dst, dstMod, arg1, arg1Rep, arg1Mod); }
void glAlphaFragmentOp2ATI(GLenum op, GLuint dst, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod) { functions()->glAlphaFragmentOp2ATI(op, dst, dstMod, arg1, arg1Rep, arg1Mod, arg2, arg2Rep, arg2Mod); }
void glAlphaFragmentOp3ATI(GLenum op, GLuint dst, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod, GLuint arg3, GLuint arg3Rep, GLuint arg3Mod) { functions()->glAlphaFragmentOp3ATI(op, dst, dstMod, arg1, arg1Rep, arg1Mod, arg2, arg2Rep, arg2Mod, arg3, arg3Rep, arg3Mod); }
void glAlphaFunc(GLenum func, GLclampf ref) { functions()->glAlphaFunc(func, ref); }
void glAlphaFuncxOES(GLenum func, GLfixed ref) { functions()->glAlphaFuncxOES(func, ref); }
void glApplyFramebufferAttachmentCMAAINTEL() { functions()->glApplyFramebufferAttachmentCMAAINTEL(); }
void glApplyTextureEXT(GLenum mode) { functions()->glApplyTextureEXT(mode); }
void glArrayElementEXT(GLint i) { functions()->glArrayElementEXT(i); }
void glArrayElement(GLint i) { functions()->glArrayElement(i); }
void glArrayObjectATI(GLenum array, GLint size, GLenum type, GLsizei stride, GLuint buffer, GLuint offset) { functions()->glArrayObjectATI(array, size, type, stride, buffer, offset); }
void glAsyncMarkerSGIX(GLuint marker) { functions()->glAsyncMarkerSGIX(marker); }
void glAttachObjectARB(GLhandleARB containerObj, GLhandleARB obj) { functions()->glAttachObjectARB(containerObj, obj); }
void glAttachShader(GLuint program, GLuint shader) { functions()->glAttachShader(program, shader); }
void glBeginConditionalRender(GLuint id, GLenum mode) { functions()->glBeginConditionalRender(id, mode); }
void glBeginConditionalRenderNV(GLuint id, GLenum mode) { functions()->glBeginConditionalRenderNV(id, mode); }
void glBeginConditionalRenderNVX(GLuint id) { functions()->glBeginConditionalRenderNVX(id); }
void glBeginFragmentShaderATI() { functions()->glBeginFragmentShaderATI(); }
void glBegin(GLenum mode) { functions()->glBegin(mode); }
void glBeginOcclusionQueryNV(GLuint id) { functions()->glBeginOcclusionQueryNV(id); }
void glBeginPerfMonitorAMD(GLuint monitor) { functions()->glBeginPerfMonitorAMD(monitor); }
void glBeginPerfQueryINTEL(GLuint queryHandle) { functions()->glBeginPerfQueryINTEL(queryHandle); }
void glBeginQueryARB(GLenum target, GLuint id) { functions()->glBeginQueryARB(target, id); }
void glBeginQuery(GLenum target, GLuint id) { functions()->glBeginQuery(target, id); }
void glBeginQueryIndexed(GLenum target, GLuint index, GLuint id) { functions()->glBeginQueryIndexed(target, index, id); }
void glBeginTransformFeedbackEXT(GLenum primitiveMode) { functions()->glBeginTransformFeedbackEXT(primitiveMode); }
void glBeginTransformFeedback(GLenum primitiveMode) { functions()->glBeginTransformFeedback(primitiveMode); }
void glBeginTransformFeedbackNV(GLenum primitiveMode) { functions()->glBeginTransformFeedbackNV(primitiveMode); }
void glBeginVertexShaderEXT() { functions()->glBeginVertexShaderEXT(); }
void glBeginVideoCaptureNV(GLuint video_capture_slot) { functions()->glBeginVideoCaptureNV(video_capture_slot); }
void glBindAttribLocationARB(GLhandleARB programObj, GLuint index, const GLcharARB* name) { functions()->glBindAttribLocationARB(programObj, index, name); }
void glBindAttribLocation(GLuint program, GLuint index, const GLchar* name) { functions()->glBindAttribLocation(program, index, name); }
void glBindBufferARB(GLenum target, GLuint buffer) { functions()->glBindBufferARB(target, buffer); }
void glBindBufferBaseEXT(GLenum target, GLuint index, GLuint buffer) { functions()->glBindBufferBaseEXT(target, index, buffer); }
void glBindBufferBase(GLenum target, GLuint index, GLuint buffer) { functions()->glBindBufferBase(target, index, buffer); }
void glBindBufferBaseNV(GLenum target, GLuint index, GLuint buffer) { functions()->glBindBufferBaseNV(target, index, buffer); }
void glBindBuffer(GLenum target, GLuint buffer) { functions()->glBindBuffer(target, buffer); }
void glBindBufferOffsetEXT(GLenum target, GLuint index, GLuint buffer, GLintptr offset) { functions()->glBindBufferOffsetEXT(target, index, buffer, offset); }
void glBindBufferOffsetNV(GLenum target, GLuint index, GLuint buffer, GLintptr offset) { functions()->glBindBufferOffsetNV(target, index, buffer, offset); }
void glBindBufferRangeEXT(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size) { functions()->glBindBufferRangeEXT(target, index, buffer, offset, size); }
void glBindBufferRange(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size) { functions()->glBindBufferRange(target, index, buffer, offset, size); }
void glBindBufferRangeNV(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size) { functions()->glBindBufferRangeNV(target, index, buffer, offset, size); }
void glBindBuffersBase(GLenum target, GLuint first, GLsizei count, const GLuint* buffers) { functions()->glBindBuffersBase(target, first, count, buffers); }
void glBindBuffersRange(GLenum target, GLuint first, GLsizei count, const GLuint* buffers, const GLintptr* offsets, const GLsizeiptr* sizes) { functions()->glBindBuffersRange(target, first, count, buffers, offsets, sizes); }
void glBindFragDataLocationEXT(GLuint program, GLuint color, const GLchar* name) { functions()->glBindFragDataLocationEXT(program, color, name); }
void glBindFragDataLocation(GLuint program, GLuint color, const GLchar* name) { functions()->glBindFragDataLocation(program, color, name); }
void glBindFragDataLocationIndexed(GLuint program, GLuint colorNumber, GLuint index, const GLchar* name) { functions()->glBindFragDataLocationIndexed(program, colorNumber, index, name); }
void glBindFragmentShaderATI(GLuint id) { functions()->glBindFragmentShaderATI(id); }
void glBindFramebufferEXT(GLenum target, GLuint framebuffer) { functions()->glBindFramebufferEXT(target, framebuffer); }
void glBindFramebuffer(GLenum target, GLuint framebuffer) { functions()->glBindFramebuffer(target, framebuffer); }
void glBindImageTextureEXT(GLuint index, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLint format) { functions()->glBindImageTextureEXT(index, texture, level, layered, layer, access, format); }
void glBindImageTexture(GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format) { functions()->glBindImageTexture(unit, texture, level, layered, layer, access, format); }
void glBindImageTextures(GLuint first, GLsizei count, const GLuint* textures) { functions()->glBindImageTextures(first, count, textures); }
void glBindMultiTextureEXT(GLenum texunit, GLenum target, GLuint texture) { functions()->glBindMultiTextureEXT(texunit, target, texture); }
void glBindProgramARB(GLenum target, GLuint program) { functions()->glBindProgramARB(target, program); }
void glBindProgramNV(GLenum target, GLuint id) { functions()->glBindProgramNV(target, id); }
void glBindProgramPipeline(GLuint pipeline) { functions()->glBindProgramPipeline(pipeline); }
void glBindRenderbufferEXT(GLenum target, GLuint renderbuffer) { functions()->glBindRenderbufferEXT(target, renderbuffer); }
void glBindRenderbuffer(GLenum target, GLuint renderbuffer) { functions()->glBindRenderbuffer(target, renderbuffer); }
void glBindSampler(GLuint unit, GLuint sampler) { functions()->glBindSampler(unit, sampler); }
void glBindSamplers(GLuint first, GLsizei count, const GLuint* samplers) { functions()->glBindSamplers(first, count, samplers); }
void glBindTextureEXT(GLenum target, GLuint texture) { functions()->glBindTextureEXT(target, texture); }
void glBindTexture(GLenum target, GLuint texture) { functions()->glBindTexture(target, texture); }
void glBindTextures(GLuint first, GLsizei count, const GLuint* textures) { functions()->glBindTextures(first, count, textures); }
void glBindTextureUnit(GLuint unit, GLuint texture) { functions()->glBindTextureUnit(unit, texture); }
void glBindTransformFeedback(GLenum target, GLuint id) { functions()->glBindTransformFeedback(target, id); }
void glBindTransformFeedbackNV(GLenum target, GLuint id) { functions()->glBindTransformFeedbackNV(target, id); }
void glBindVertexArrayAPPLE(GLuint array) { functions()->glBindVertexArrayAPPLE(array); }
void glBindVertexArray(GLuint array) { functions()->glBindVertexArray(array); }
void glBindVertexBuffer(GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride) { functions()->glBindVertexBuffer(bindingindex, buffer, offset, stride); }
void glBindVertexBuffers(GLuint first, GLsizei count, const GLuint* buffers, const GLintptr* offsets, const GLsizei* strides) { functions()->glBindVertexBuffers(first, count, buffers, offsets, strides); }
void glBindVertexShaderEXT(GLuint id) { functions()->glBindVertexShaderEXT(id); }
void glBindVideoCaptureStreamBufferNV(GLuint video_capture_slot, GLuint stream, GLenum frame_region, GLintptrARB offset) { functions()->glBindVideoCaptureStreamBufferNV(video_capture_slot, stream, frame_region, offset); }
void glBindVideoCaptureStreamTextureNV(GLuint video_capture_slot, GLuint stream, GLenum frame_region, GLenum target, GLuint texture) { functions()->glBindVideoCaptureStreamTextureNV(video_capture_slot, stream, frame_region, target, texture); }
void glBinormal3bEXT(GLbyte bx, GLbyte by, GLbyte bz) { functions()->glBinormal3bEXT(bx, by, bz); }
void glBinormal3bvEXT(const GLbyte* v) { functions()->glBinormal3bvEXT(v); }
void glBinormal3dEXT(GLdouble bx, GLdouble by, GLdouble bz) { functions()->glBinormal3dEXT(bx, by, bz); }
void glBinormal3dvEXT(const GLdouble* v) { functions()->glBinormal3dvEXT(v); }
void glBinormal3fEXT(GLfloat bx, GLfloat by, GLfloat bz) { functions()->glBinormal3fEXT(bx, by, bz); }
void glBinormal3fvEXT(const GLfloat* v) { functions()->glBinormal3fvEXT(v); }
void glBinormal3iEXT(GLint bx, GLint by, GLint bz) { functions()->glBinormal3iEXT(bx, by, bz); }
void glBinormal3ivEXT(const GLint* v) { functions()->glBinormal3ivEXT(v); }
void glBinormal3sEXT(GLshort bx, GLshort by, GLshort bz) { functions()->glBinormal3sEXT(bx, by, bz); }
void glBinormal3svEXT(const GLshort* v) { functions()->glBinormal3svEXT(v); }
void glBinormalPointerEXT(GLenum type, GLsizei stride, const void* pointer) { functions()->glBinormalPointerEXT(type, stride, pointer); }
void glBitmap(GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, const GLubyte* bitmap) { functions()->glBitmap(width, height, xorig, yorig, xmove, ymove, bitmap); }
void glBitmapxOES(GLsizei width, GLsizei height, GLfixed xorig, GLfixed yorig, GLfixed xmove, GLfixed ymove, const GLubyte* bitmap) { functions()->glBitmapxOES(width, height, xorig, yorig, xmove, ymove, bitmap); }
void glBlendBarrierKHR() { functions()->glBlendBarrierKHR(); }
void glBlendBarrierNV() { functions()->glBlendBarrierNV(); }
void glBlendColorEXT(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) { functions()->glBlendColorEXT(red, green, blue, alpha); }
void glBlendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) { functions()->glBlendColor(red, green, blue, alpha); }
void glBlendColorxOES(GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha) { functions()->glBlendColorxOES(red, green, blue, alpha); }
void glBlendEquationEXT(GLenum mode) { functions()->glBlendEquationEXT(mode); }
void glBlendEquation(GLenum mode) { functions()->glBlendEquation(mode); }
void glBlendEquationiARB(GLuint buf, GLenum mode) { functions()->glBlendEquationiARB(buf, mode); }
void glBlendEquationi(GLuint buf, GLenum mode) { functions()->glBlendEquationi(buf, mode); }
void glBlendEquationIndexedAMD(GLuint buf, GLenum mode) { functions()->glBlendEquationIndexedAMD(buf, mode); }
void glBlendEquationSeparateATI(GLenum modeRGB, GLenum modeA) { functions()->glBlendEquationSeparateATI(modeRGB, modeA); }
void glBlendEquationSeparateEXT(GLenum modeRGB, GLenum modeAlpha) { functions()->glBlendEquationSeparateEXT(modeRGB, modeAlpha); }
void glBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha) { functions()->glBlendEquationSeparate(modeRGB, modeAlpha); }
void glBlendEquationSeparateiARB(GLuint buf, GLenum modeRGB, GLenum modeAlpha) { functions()->glBlendEquationSeparateiARB(buf, modeRGB, modeAlpha); }
void glBlendEquationSeparatei(GLuint buf, GLenum modeRGB, GLenum modeAlpha) { functions()->glBlendEquationSeparatei(buf, modeRGB, modeAlpha); }
void glBlendEquationSeparateIndexedAMD(GLuint buf, GLenum modeRGB, GLenum modeAlpha) { functions()->glBlendEquationSeparateIndexedAMD(buf, modeRGB, modeAlpha); }
void glBlendFunc(GLenum sfactor, GLenum dfactor) { functions()->glBlendFunc(sfactor, dfactor); }
void glBlendFunciARB(GLuint buf, GLenum src, GLenum dst) { functions()->glBlendFunciARB(buf, src, dst); }
void glBlendFunci(GLuint buf, GLenum src, GLenum dst) { functions()->glBlendFunci(buf, src, dst); }
void glBlendFuncIndexedAMD(GLuint buf, GLenum src, GLenum dst) { functions()->glBlendFuncIndexedAMD(buf, src, dst); }
void glBlendFuncSeparateEXT(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha) { functions()->glBlendFuncSeparateEXT(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha); }
void glBlendFuncSeparate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha) { functions()->glBlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha); }
void glBlendFuncSeparateiARB(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha) { functions()->glBlendFuncSeparateiARB(buf, srcRGB, dstRGB, srcAlpha, dstAlpha); }
void glBlendFuncSeparatei(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha) { functions()->glBlendFuncSeparatei(buf, srcRGB, dstRGB, srcAlpha, dstAlpha); }
void glBlendFuncSeparateIndexedAMD(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha) { functions()->glBlendFuncSeparateIndexedAMD(buf, srcRGB, dstRGB, srcAlpha, dstAlpha); }
void glBlendFuncSeparateINGR(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha) { functions()->glBlendFuncSeparateINGR(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha); }
void glBlendParameteriNV(GLenum pname, GLint value) { functions()->glBlendParameteriNV(pname, value); }
void glBlitFramebufferEXT(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter) { functions()->glBlitFramebufferEXT(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter); }
void glBlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter) { functions()->glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter); }
void glBlitNamedFramebuffer(GLuint readFramebuffer, GLuint drawFramebuffer, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter) { functions()->glBlitNamedFramebuffer(readFramebuffer, drawFramebuffer, srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter); }
void glBufferAddressRangeNV(GLenum pname, GLuint index, GLuint64EXT address, GLsizeiptr length) { functions()->glBufferAddressRangeNV(pname, index, address, length); }
void glBufferDataARB(GLenum target, GLsizeiptrARB size, const void* data, GLenum usage) { functions()->glBufferDataARB(target, size, data, usage); }
void glBufferData(GLenum target, GLsizeiptr size, const void* data, GLenum usage) { functions()->glBufferData(target, size, data, usage); }
void glBufferPageCommitmentARB(GLenum target, GLintptr offset, GLsizeiptr size, GLboolean commit) { functions()->glBufferPageCommitmentARB(target, offset, size, commit); }
void glBufferParameteriAPPLE(GLenum target, GLenum pname, GLint param) { functions()->glBufferParameteriAPPLE(target, pname, param); }
void glBufferStorage(GLenum target, GLsizeiptr size, const void* data, GLbitfield flags) { functions()->glBufferStorage(target, size, data, flags); }
void glBufferSubDataARB(GLenum target, GLintptrARB offset, GLsizeiptrARB size, const void* data) { functions()->glBufferSubDataARB(target, offset, size, data); }
void glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void* data) { functions()->glBufferSubData(target, offset, size, data); }
void glCallCommandListNV(GLuint list) { functions()->glCallCommandListNV(list); }
void glCallList(GLuint list) { functions()->glCallList(list); }
void glCallLists(GLsizei n, GLenum type, const GLvoid* lists) { functions()->glCallLists(n, type, lists); }
void glClampColorARB(GLenum target, GLenum clamp) { functions()->glClampColorARB(target, clamp); }
void glClampColor(GLenum target, GLenum clamp) { functions()->glClampColor(target, clamp); }
void glClearAccum(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) { functions()->glClearAccum(red, green, blue, alpha); }
void glClearAccumxOES(GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha) { functions()->glClearAccumxOES(red, green, blue, alpha); }
void glClearBufferData(GLenum target, GLenum internalformat, GLenum format, GLenum type, const void* data) { functions()->glClearBufferData(target, internalformat, format, type, data); }
void glClearBufferfi(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil) { functions()->glClearBufferfi(buffer, drawbuffer, depth, stencil); }
void glClearBufferfv(GLenum buffer, GLint drawbuffer, const GLfloat* value) { functions()->glClearBufferfv(buffer, drawbuffer, value); }
void glClearBufferiv(GLenum buffer, GLint drawbuffer, const GLint* value) { functions()->glClearBufferiv(buffer, drawbuffer, value); }
void glClearBufferSubData(GLenum target, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void* data) { functions()->glClearBufferSubData(target, internalformat, offset, size, format, type, data); }
void glClearBufferuiv(GLenum buffer, GLint drawbuffer, const GLuint* value) { functions()->glClearBufferuiv(buffer, drawbuffer, value); }
void glClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha) { functions()->glClearColor(red, green, blue, alpha); }
void glClearColorIiEXT(GLint red, GLint green, GLint blue, GLint alpha) { functions()->glClearColorIiEXT(red, green, blue, alpha); }
void glClearColorIuiEXT(GLuint red, GLuint green, GLuint blue, GLuint alpha) { functions()->glClearColorIuiEXT(red, green, blue, alpha); }
void glClearColorxOES(GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha) { functions()->glClearColorxOES(red, green, blue, alpha); }
void glClearDepthdNV(GLdouble depth) { functions()->glClearDepthdNV(depth); }
void glClearDepthf(GLfloat d) { functions()->glClearDepthf(d); }
void glClearDepthfOES(GLclampf depth) { functions()->glClearDepthfOES(depth); }
void glClearDepth(GLclampd depth) { functions()->glClearDepth(depth); }
void glClearDepthxOES(GLfixed depth) { functions()->glClearDepthxOES(depth); }
void glClear(GLbitfield mask) { functions()->glClear(mask); }
void glClearIndex(GLfloat c) { functions()->glClearIndex(c); }
void glClearNamedBufferDataEXT(GLuint buffer, GLenum internalformat, GLenum format, GLenum type, const void* data) { functions()->glClearNamedBufferDataEXT(buffer, internalformat, format, type, data); }
void glClearNamedBufferData(GLuint buffer, GLenum internalformat, GLenum format, GLenum type, const void* data) { functions()->glClearNamedBufferData(buffer, internalformat, format, type, data); }
void glClearNamedBufferSubDataEXT(GLuint buffer, GLenum internalformat, GLsizeiptr offset, GLsizeiptr size, GLenum format, GLenum type, const void* data) { functions()->glClearNamedBufferSubDataEXT(buffer, internalformat, offset, size, format, type, data); }
void glClearNamedBufferSubData(GLuint buffer, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void* data) { functions()->glClearNamedBufferSubData(buffer, internalformat, offset, size, format, type, data); }
void glClearNamedFramebufferfi(GLuint framebuffer, GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil) { functions()->glClearNamedFramebufferfi(framebuffer, buffer, drawbuffer, depth, stencil); }
void glClearNamedFramebufferfv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLfloat* value) { functions()->glClearNamedFramebufferfv(framebuffer, buffer, drawbuffer, value); }
void glClearNamedFramebufferiv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLint* value) { functions()->glClearNamedFramebufferiv(framebuffer, buffer, drawbuffer, value); }
void glClearNamedFramebufferuiv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLuint* value) { functions()->glClearNamedFramebufferuiv(framebuffer, buffer, drawbuffer, value); }
void glClearStencil(GLint s) { functions()->glClearStencil(s); }
void glClearTexImage(GLuint texture, GLint level, GLenum format, GLenum type, const void* data) { functions()->glClearTexImage(texture, level, format, type, data); }
void glClearTexSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* data) { functions()->glClearTexSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, data); }
void glClientActiveTextureARB(GLenum texture) { functions()->glClientActiveTextureARB(texture); }
void glClientActiveTexture(GLenum texture) { functions()->glClientActiveTexture(texture); }
void glClientActiveVertexStreamATI(GLenum stream) { functions()->glClientActiveVertexStreamATI(stream); }
void glClientAttribDefaultEXT(GLbitfield mask) { functions()->glClientAttribDefaultEXT(mask); }
void glClipControl(GLenum origin, GLenum depth) { functions()->glClipControl(origin, depth); }
void glClipPlanefOES(GLenum plane, const GLfloat* equation) { functions()->glClipPlanefOES(plane, equation); }
void glClipPlane(GLenum plane, const GLdouble* equation) { functions()->glClipPlane(plane, equation); }
void glClipPlanexOES(GLenum plane, const GLfixed* equation) { functions()->glClipPlanexOES(plane, equation); }
void glColor3b(GLbyte red, GLbyte green, GLbyte blue) { functions()->glColor3b(red, green, blue); }
void glColor3bv(const GLbyte* v) { functions()->glColor3bv(v); }
void glColor3d(GLdouble red, GLdouble green, GLdouble blue) { functions()->glColor3d(red, green, blue); }
void glColor3dv(const GLdouble* v) { functions()->glColor3dv(v); }
void glColor3f(GLfloat red, GLfloat green, GLfloat blue) { functions()->glColor3f(red, green, blue); }
void glColor3fv(const GLfloat* v) { functions()->glColor3fv(v); }
void glColor3fVertex3fSUN(GLfloat r, GLfloat g, GLfloat b, GLfloat x, GLfloat y, GLfloat z) { functions()->glColor3fVertex3fSUN(r, g, b, x, y, z); }
void glColor3fVertex3fvSUN(const GLfloat* c, const GLfloat* v) { functions()->glColor3fVertex3fvSUN(c, v); }
void glColor3hNV(GLhalfNV red, GLhalfNV green, GLhalfNV blue) { functions()->glColor3hNV(red, green, blue); }
void glColor3hvNV(const GLhalfNV* v) { functions()->glColor3hvNV(v); }
void glColor3i(GLint red, GLint green, GLint blue) { functions()->glColor3i(red, green, blue); }
void glColor3iv(const GLint* v) { functions()->glColor3iv(v); }
void glColor3s(GLshort red, GLshort green, GLshort blue) { functions()->glColor3s(red, green, blue); }
void glColor3sv(const GLshort* v) { functions()->glColor3sv(v); }
void glColor3ub(GLubyte red, GLubyte green, GLubyte blue) { functions()->glColor3ub(red, green, blue); }
void glColor3ubv(const GLubyte* v) { functions()->glColor3ubv(v); }
void glColor3ui(GLuint red, GLuint green, GLuint blue) { functions()->glColor3ui(red, green, blue); }
void glColor3uiv(const GLuint* v) { functions()->glColor3uiv(v); }
void glColor3us(GLushort red, GLushort green, GLushort blue) { functions()->glColor3us(red, green, blue); }
void glColor3usv(const GLushort* v) { functions()->glColor3usv(v); }
void glColor3xOES(GLfixed red, GLfixed green, GLfixed blue) { functions()->glColor3xOES(red, green, blue); }
void glColor3xvOES(const GLfixed* components) { functions()->glColor3xvOES(components); }
void glColor4b(GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha) { functions()->glColor4b(red, green, blue, alpha); }
void glColor4bv(const GLbyte* v) { functions()->glColor4bv(v); }
void glColor4d(GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha) { functions()->glColor4d(red, green, blue, alpha); }
void glColor4dv(const GLdouble* v) { functions()->glColor4dv(v); }
void glColor4f(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) { functions()->glColor4f(red, green, blue, alpha); }
void glColor4fNormal3fVertex3fSUN(GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z) { functions()->glColor4fNormal3fVertex3fSUN(r, g, b, a, nx, ny, nz, x, y, z); }
void glColor4fNormal3fVertex3fvSUN(const GLfloat* c, const GLfloat* n, const GLfloat* v) { functions()->glColor4fNormal3fVertex3fvSUN(c, n, v); }
void glColor4fv(const GLfloat* v) { functions()->glColor4fv(v); }
void glColor4hNV(GLhalfNV red, GLhalfNV green, GLhalfNV blue, GLhalfNV alpha) { functions()->glColor4hNV(red, green, blue, alpha); }
void glColor4hvNV(const GLhalfNV* v) { functions()->glColor4hvNV(v); }
void glColor4i(GLint red, GLint green, GLint blue, GLint alpha) { functions()->glColor4i(red, green, blue, alpha); }
void glColor4iv(const GLint* v) { functions()->glColor4iv(v); }
void glColor4s(GLshort red, GLshort green, GLshort blue, GLshort alpha) { functions()->glColor4s(red, green, blue, alpha); }
void glColor4sv(const GLshort* v) { functions()->glColor4sv(v); }
void glColor4ub(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha) { functions()->glColor4ub(red, green, blue, alpha); }
void glColor4ubv(const GLubyte* v) { functions()->glColor4ubv(v); }
void glColor4ubVertex2fSUN(GLubyte r, GLubyte g, GLubyte b, GLubyte a, GLfloat x, GLfloat y) { functions()->glColor4ubVertex2fSUN(r, g, b, a, x, y); }
void glColor4ubVertex2fvSUN(const GLubyte* c, const GLfloat* v) { functions()->glColor4ubVertex2fvSUN(c, v); }
void glColor4ubVertex3fSUN(GLubyte r, GLubyte g, GLubyte b, GLubyte a, GLfloat x, GLfloat y, GLfloat z) { functions()->glColor4ubVertex3fSUN(r, g, b, a, x, y, z); }
void glColor4ubVertex3fvSUN(const GLubyte* c, const GLfloat* v) { functions()->glColor4ubVertex3fvSUN(c, v); }
void glColor4ui(GLuint red, GLuint green, GLuint blue, GLuint alpha) { functions()->glColor4ui(red, green, blue, alpha); }
void glColor4uiv(const GLuint* v) { functions()->glColor4uiv(v); }
void glColor4us(GLushort red, GLushort green, GLushort blue, GLushort alpha) { functions()->glColor4us(red, green, blue, alpha); }
void glColor4usv(const GLushort* v) { functions()->glColor4usv(v); }
void glColor4xOES(GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha) { functions()->glColor4xOES(red, green, blue, alpha); }
void glColor4xvOES(const GLfixed* components) { functions()->glColor4xvOES(components); }
void glColorFormatNV(GLint size, GLenum type, GLsizei stride) { functions()->glColorFormatNV(size, type, stride); }
void glColorFragmentOp1ATI(GLenum op, GLuint dst, GLuint dstMask, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod) { functions()->glColorFragmentOp1ATI(op, dst, dstMask, dstMod, arg1, arg1Rep, arg1Mod); }
void glColorFragmentOp2ATI(GLenum op, GLuint dst, GLuint dstMask, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod) { functions()->glColorFragmentOp2ATI(op, dst, dstMask, dstMod, arg1, arg1Rep, arg1Mod, arg2, arg2Rep, arg2Mod); }
void glColorFragmentOp3ATI(GLenum op, GLuint dst, GLuint dstMask, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod, GLuint arg3, GLuint arg3Rep, GLuint arg3Mod) { functions()->glColorFragmentOp3ATI(op, dst, dstMask, dstMod, arg1, arg1Rep, arg1Mod, arg2, arg2Rep, arg2Mod, arg3, arg3Rep, arg3Mod); }
void glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha) { functions()->glColorMask(red, green, blue, alpha); }
void glColorMaski(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a) { functions()->glColorMaski(index, r, g, b, a); }
void glColorMaskIndexedEXT(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a) { functions()->glColorMaskIndexedEXT(index, r, g, b, a); }
void glColorMaterial(GLenum face, GLenum mode) { functions()->glColorMaterial(face, mode); }
void glColorP3ui(GLenum type, GLuint color) { functions()->glColorP3ui(type, color); }
void glColorP3uiv(GLenum type, const GLuint* color) { functions()->glColorP3uiv(type, color); }
void glColorP4ui(GLenum type, GLuint color) { functions()->glColorP4ui(type, color); }
void glColorP4uiv(GLenum type, const GLuint* color) { functions()->glColorP4uiv(type, color); }
void glColorPointerEXT(GLint size, GLenum type, GLsizei stride, GLsizei count, const void* pointer) { functions()->glColorPointerEXT(size, type, stride, count, pointer); }
void glColorPointer(GLint size, GLenum type, GLsizei stride, const GLvoid* ptr) { functions()->glColorPointer(size, type, stride, ptr); }
void glColorPointerListIBM(GLint size, GLenum type, GLint stride, const void** pointer, GLint ptrstride) { functions()->glColorPointerListIBM(size, type, stride, pointer, ptrstride); }
void glColorPointervINTEL(GLint size, GLenum type, const void** pointer) { functions()->glColorPointervINTEL(size, type, pointer); }
void glColorSubTableEXT(GLenum target, GLsizei start, GLsizei count, GLenum format, GLenum type, const void* data) { functions()->glColorSubTableEXT(target, start, count, format, type, data); }
void glColorSubTable(GLenum target, GLsizei start, GLsizei count, GLenum format, GLenum type, const GLvoid* data) { functions()->glColorSubTable(target, start, count, format, type, data); }
void glColorTableEXT(GLenum target, GLenum internalFormat, GLsizei width, GLenum format, GLenum type, const void* table) { functions()->glColorTableEXT(target, internalFormat, width, format, type, table); }
void glColorTable(GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid* table) { functions()->glColorTable(target, internalformat, width, format, type, table); }
void glColorTableParameterfv(GLenum target, GLenum pname, const GLfloat* params) { functions()->glColorTableParameterfv(target, pname, params); }
void glColorTableParameterfvSGI(GLenum target, GLenum pname, const GLfloat* params) { functions()->glColorTableParameterfvSGI(target, pname, params); }
void glColorTableParameteriv(GLenum target, GLenum pname, const GLint* params) { functions()->glColorTableParameteriv(target, pname, params); }
void glColorTableParameterivSGI(GLenum target, GLenum pname, const GLint* params) { functions()->glColorTableParameterivSGI(target, pname, params); }
void glColorTableSGI(GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const void* table) { functions()->glColorTableSGI(target, internalformat, width, format, type, table); }
void glCombinerInputNV(GLenum stage, GLenum portion, GLenum variable, GLenum input, GLenum mapping, GLenum componentUsage) { functions()->glCombinerInputNV(stage, portion, variable, input, mapping, componentUsage); }
void glCombinerOutputNV(GLenum stage, GLenum portion, GLenum abOutput, GLenum cdOutput, GLenum sumOutput, GLenum scale, GLenum bias, GLboolean abDotProduct, GLboolean cdDotProduct, GLboolean muxSum) { functions()->glCombinerOutputNV(stage, portion, abOutput, cdOutput, sumOutput, scale, bias, abDotProduct, cdDotProduct, muxSum); }
void glCombinerParameterfNV(GLenum pname, GLfloat param) { functions()->glCombinerParameterfNV(pname, param); }
void glCombinerParameterfvNV(GLenum pname, const GLfloat* params) { functions()->glCombinerParameterfvNV(pname, params); }
void glCombinerParameteriNV(GLenum pname, GLint param) { functions()->glCombinerParameteriNV(pname, param); }
void glCombinerParameterivNV(GLenum pname, const GLint* params) { functions()->glCombinerParameterivNV(pname, params); }
void glCombinerStageParameterfvNV(GLenum stage, GLenum pname, const GLfloat* params) { functions()->glCombinerStageParameterfvNV(stage, pname, params); }
void glCommandListSegmentsNV(GLuint list, GLuint segments) { functions()->glCommandListSegmentsNV(list, segments); }
void glCompileCommandListNV(GLuint list) { functions()->glCompileCommandListNV(list); }
void glCompileShaderARB(GLhandleARB shaderObj) { functions()->glCompileShaderARB(shaderObj); }
void glCompileShader(GLuint shader) { functions()->glCompileShader(shader); }
void glCompileShaderIncludeARB(GLuint shader, GLsizei count, const GLchar*const* path, const GLint* length) { functions()->glCompileShaderIncludeARB(shader, count, path, length); }
void glCompressedMultiTexImage1DEXT(GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void* bits) { functions()->glCompressedMultiTexImage1DEXT(texunit, target, level, internalformat, width, border, imageSize, bits); }
void glCompressedMultiTexImage2DEXT(GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void* bits) { functions()->glCompressedMultiTexImage2DEXT(texunit, target, level, internalformat, width, height, border, imageSize, bits); }
void glCompressedMultiTexImage3DEXT(GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void* bits) { functions()->glCompressedMultiTexImage3DEXT(texunit, target, level, internalformat, width, height, depth, border, imageSize, bits); }
void glCompressedMultiTexSubImage1DEXT(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void* bits) { functions()->glCompressedMultiTexSubImage1DEXT(texunit, target, level, xoffset, width, format, imageSize, bits); }
void glCompressedMultiTexSubImage2DEXT(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void* bits) { functions()->glCompressedMultiTexSubImage2DEXT(texunit, target, level, xoffset, yoffset, width, height, format, imageSize, bits); }
void glCompressedMultiTexSubImage3DEXT(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void* bits) { functions()->glCompressedMultiTexSubImage3DEXT(texunit, target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, bits); }
void glCompressedTexImage1DARB(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void* data) { functions()->glCompressedTexImage1DARB(target, level, internalformat, width, border, imageSize, data); }
void glCompressedTexImage1D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const GLvoid* data) { functions()->glCompressedTexImage1D(target, level, internalformat, width, border, imageSize, data); }
void glCompressedTexImage2DARB(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void* data) { functions()->glCompressedTexImage2DARB(target, level, internalformat, width, height, border, imageSize, data); }
void glCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid* data) { functions()->glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data); }
void glCompressedTexImage3DARB(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void* data) { functions()->glCompressedTexImage3DARB(target, level, internalformat, width, height, depth, border, imageSize, data); }
void glCompressedTexImage3D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid* data) { functions()->glCompressedTexImage3D(target, level, internalformat, width, height, depth, border, imageSize, data); }
void glCompressedTexSubImage1DARB(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void* data) { functions()->glCompressedTexSubImage1DARB(target, level, xoffset, width, format, imageSize, data); }
void glCompressedTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const GLvoid* data) { functions()->glCompressedTexSubImage1D(target, level, xoffset, width, format, imageSize, data); }
void glCompressedTexSubImage2DARB(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void* data) { functions()->glCompressedTexSubImage2DARB(target, level, xoffset, yoffset, width, height, format, imageSize, data); }
void glCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid* data) { functions()->glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data); }
void glCompressedTexSubImage3DARB(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void* data) { functions()->glCompressedTexSubImage3DARB(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data); }
void glCompressedTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid* data) { functions()->glCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data); }
void glCompressedTextureImage1DEXT(GLuint texture, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void* bits) { functions()->glCompressedTextureImage1DEXT(texture, target, level, internalformat, width, border, imageSize, bits); }
void glCompressedTextureImage2DEXT(GLuint texture, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void* bits) { functions()->glCompressedTextureImage2DEXT(texture, target, level, internalformat, width, height, border, imageSize, bits); }
void glCompressedTextureImage3DEXT(GLuint texture, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void* bits) { functions()->glCompressedTextureImage3DEXT(texture, target, level, internalformat, width, height, depth, border, imageSize, bits); }
void glCompressedTextureSubImage1DEXT(GLuint texture, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void* bits) { functions()->glCompressedTextureSubImage1DEXT(texture, target, level, xoffset, width, format, imageSize, bits); }
void glCompressedTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void* data) { functions()->glCompressedTextureSubImage1D(texture, level, xoffset, width, format, imageSize, data); }
void glCompressedTextureSubImage2DEXT(GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void* bits) { functions()->glCompressedTextureSubImage2DEXT(texture, target, level, xoffset, yoffset, width, height, format, imageSize, bits); }
void glCompressedTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void* data) { functions()->glCompressedTextureSubImage2D(texture, level, xoffset, yoffset, width, height, format, imageSize, data); }
void glCompressedTextureSubImage3DEXT(GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void* bits) { functions()->glCompressedTextureSubImage3DEXT(texture, target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, bits); }
void glCompressedTextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void* data) { functions()->glCompressedTextureSubImage3D(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data); }
void glConservativeRasterParameterfNV(GLenum pname, GLfloat value) { functions()->glConservativeRasterParameterfNV(pname, value); }
void glConvolutionFilter1DEXT(GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const void* image) { functions()->glConvolutionFilter1DEXT(target, internalformat, width, format, type, image); }
void glConvolutionFilter1D(GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid* image) { functions()->glConvolutionFilter1D(target, internalformat, width, format, type, image); }
void glConvolutionFilter2DEXT(GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* image) { functions()->glConvolutionFilter2DEXT(target, internalformat, width, height, format, type, image); }
void glConvolutionFilter2D(GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* image) { functions()->glConvolutionFilter2D(target, internalformat, width, height, format, type, image); }
void glConvolutionParameterfEXT(GLenum target, GLenum pname, GLfloat params) { functions()->glConvolutionParameterfEXT(target, pname, params); }
void glConvolutionParameterf(GLenum target, GLenum pname, GLfloat params) { functions()->glConvolutionParameterf(target, pname, params); }
void glConvolutionParameterfvEXT(GLenum target, GLenum pname, const GLfloat* params) { functions()->glConvolutionParameterfvEXT(target, pname, params); }
void glConvolutionParameterfv(GLenum target, GLenum pname, const GLfloat* params) { functions()->glConvolutionParameterfv(target, pname, params); }
void glConvolutionParameteriEXT(GLenum target, GLenum pname, GLint params) { functions()->glConvolutionParameteriEXT(target, pname, params); }
void glConvolutionParameteri(GLenum target, GLenum pname, GLint params) { functions()->glConvolutionParameteri(target, pname, params); }
void glConvolutionParameterivEXT(GLenum target, GLenum pname, const GLint* params) { functions()->glConvolutionParameterivEXT(target, pname, params); }
void glConvolutionParameteriv(GLenum target, GLenum pname, const GLint* params) { functions()->glConvolutionParameteriv(target, pname, params); }
void glConvolutionParameterxOES(GLenum target, GLenum pname, GLfixed param) { functions()->glConvolutionParameterxOES(target, pname, param); }
void glConvolutionParameterxvOES(GLenum target, GLenum pname, const GLfixed* params) { functions()->glConvolutionParameterxvOES(target, pname, params); }
void glCopyBufferSubData(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size) { functions()->glCopyBufferSubData(readTarget, writeTarget, readOffset, writeOffset, size); }
void glCopyColorSubTableEXT(GLenum target, GLsizei start, GLint x, GLint y, GLsizei width) { functions()->glCopyColorSubTableEXT(target, start, x, y, width); }
void glCopyColorSubTable(GLenum target, GLsizei start, GLint x, GLint y, GLsizei width) { functions()->glCopyColorSubTable(target, start, x, y, width); }
void glCopyColorTable(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width) { functions()->glCopyColorTable(target, internalformat, x, y, width); }
void glCopyColorTableSGI(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width) { functions()->glCopyColorTableSGI(target, internalformat, x, y, width); }
void glCopyConvolutionFilter1DEXT(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width) { functions()->glCopyConvolutionFilter1DEXT(target, internalformat, x, y, width); }
void glCopyConvolutionFilter1D(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width) { functions()->glCopyConvolutionFilter1D(target, internalformat, x, y, width); }
void glCopyConvolutionFilter2DEXT(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height) { functions()->glCopyConvolutionFilter2DEXT(target, internalformat, x, y, width, height); }
void glCopyConvolutionFilter2D(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height) { functions()->glCopyConvolutionFilter2D(target, internalformat, x, y, width, height); }
void glCopyImageSubData(GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth) { functions()->glCopyImageSubData(srcName, srcTarget, srcLevel, srcX, srcY, srcZ, dstName, dstTarget, dstLevel, dstX, dstY, dstZ, srcWidth, srcHeight, srcDepth); }
void glCopyImageSubDataNV(GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei width, GLsizei height, GLsizei depth) { functions()->glCopyImageSubDataNV(srcName, srcTarget, srcLevel, srcX, srcY, srcZ, dstName, dstTarget, dstLevel, dstX, dstY, dstZ, width, height, depth); }
void glCopyMultiTexImage1DEXT(GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border) { functions()->glCopyMultiTexImage1DEXT(texunit, target, level, internalformat, x, y, width, border); }
void glCopyMultiTexImage2DEXT(GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border) { functions()->glCopyMultiTexImage2DEXT(texunit, target, level, internalformat, x, y, width, height, border); }
void glCopyMultiTexSubImage1DEXT(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width) { functions()->glCopyMultiTexSubImage1DEXT(texunit, target, level, xoffset, x, y, width); }
void glCopyMultiTexSubImage2DEXT(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height) { functions()->glCopyMultiTexSubImage2DEXT(texunit, target, level, xoffset, yoffset, x, y, width, height); }
void glCopyMultiTexSubImage3DEXT(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height) { functions()->glCopyMultiTexSubImage3DEXT(texunit, target, level, xoffset, yoffset, zoffset, x, y, width, height); }
void glCopyNamedBufferSubData(GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size) { functions()->glCopyNamedBufferSubData(readBuffer, writeBuffer, readOffset, writeOffset, size); }
void glCopyPathNV(GLuint resultPath, GLuint srcPath) { functions()->glCopyPathNV(resultPath, srcPath); }
void glCopyPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum type) { functions()->glCopyPixels(x, y, width, height, type); }
void glCopyTexImage1DEXT(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border) { functions()->glCopyTexImage1DEXT(target, level, internalformat, x, y, width, border); }
void glCopyTexImage1D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border) { functions()->glCopyTexImage1D(target, level, internalformat, x, y, width, border); }
void glCopyTexImage2DEXT(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border) { functions()->glCopyTexImage2DEXT(target, level, internalformat, x, y, width, height, border); }
void glCopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border) { functions()->glCopyTexImage2D(target, level, internalformat, x, y, width, height, border); }
void glCopyTexSubImage1DEXT(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width) { functions()->glCopyTexSubImage1DEXT(target, level, xoffset, x, y, width); }
void glCopyTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width) { functions()->glCopyTexSubImage1D(target, level, xoffset, x, y, width); }
void glCopyTexSubImage2DEXT(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height) { functions()->glCopyTexSubImage2DEXT(target, level, xoffset, yoffset, x, y, width, height); }
void glCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height) { functions()->glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height); }
void glCopyTexSubImage3DEXT(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height) { functions()->glCopyTexSubImage3DEXT(target, level, xoffset, yoffset, zoffset, x, y, width, height); }
void glCopyTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height) { functions()->glCopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height); }
void glCopyTextureImage1DEXT(GLuint texture, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border) { functions()->glCopyTextureImage1DEXT(texture, target, level, internalformat, x, y, width, border); }
void glCopyTextureImage2DEXT(GLuint texture, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border) { functions()->glCopyTextureImage2DEXT(texture, target, level, internalformat, x, y, width, height, border); }
void glCopyTextureSubImage1DEXT(GLuint texture, GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width) { functions()->glCopyTextureSubImage1DEXT(texture, target, level, xoffset, x, y, width); }
void glCopyTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width) { functions()->glCopyTextureSubImage1D(texture, level, xoffset, x, y, width); }
void glCopyTextureSubImage2DEXT(GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height) { functions()->glCopyTextureSubImage2DEXT(texture, target, level, xoffset, yoffset, x, y, width, height); }
void glCopyTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height) { functions()->glCopyTextureSubImage2D(texture, level, xoffset, yoffset, x, y, width, height); }
void glCopyTextureSubImage3DEXT(GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height) { functions()->glCopyTextureSubImage3DEXT(texture, target, level, xoffset, yoffset, zoffset, x, y, width, height); }
void glCopyTextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height) { functions()->glCopyTextureSubImage3D(texture, level, xoffset, yoffset, zoffset, x, y, width, height); }
void glCoverageModulationNV(GLenum components) { functions()->glCoverageModulationNV(components); }
void glCoverageModulationTableNV(GLsizei n, const GLfloat* v) { functions()->glCoverageModulationTableNV(n, v); }
void glCoverFillPathInstancedNV(GLsizei numPaths, GLenum pathNameType, const void* paths, GLuint pathBase, GLenum coverMode, GLenum transformType, const GLfloat* transformValues) { functions()->glCoverFillPathInstancedNV(numPaths, pathNameType, paths, pathBase, coverMode, transformType, transformValues); }
void glCoverFillPathNV(GLuint path, GLenum coverMode) { functions()->glCoverFillPathNV(path, coverMode); }
void glCoverStrokePathInstancedNV(GLsizei numPaths, GLenum pathNameType, const void* paths, GLuint pathBase, GLenum coverMode, GLenum transformType, const GLfloat* transformValues) { functions()->glCoverStrokePathInstancedNV(numPaths, pathNameType, paths, pathBase, coverMode, transformType, transformValues); }
void glCoverStrokePathNV(GLuint path, GLenum coverMode) { functions()->glCoverStrokePathNV(path, coverMode); }
void glCreateBuffers(GLsizei n, GLuint* buffers) { functions()->glCreateBuffers(n, buffers); }
void glCreateCommandListsNV(GLsizei n, GLuint* lists) { functions()->glCreateCommandListsNV(n, lists); }
void glCreateFramebuffers(GLsizei n, GLuint* framebuffers) { functions()->glCreateFramebuffers(n, framebuffers); }
void glCreatePerfQueryINTEL(GLuint queryId, GLuint* queryHandle) { functions()->glCreatePerfQueryINTEL(queryId, queryHandle); }
void glCreateProgramPipelines(GLsizei n, GLuint* pipelines) { functions()->glCreateProgramPipelines(n, pipelines); }
void glCreateQueries(GLenum target, GLsizei n, GLuint* ids) { functions()->glCreateQueries(target, n, ids); }
void glCreateRenderbuffers(GLsizei n, GLuint* renderbuffers) { functions()->glCreateRenderbuffers(n, renderbuffers); }
void glCreateSamplers(GLsizei n, GLuint* samplers) { functions()->glCreateSamplers(n, samplers); }
void glCreateStatesNV(GLsizei n, GLuint* states) { functions()->glCreateStatesNV(n, states); }
void glCreateTextures(GLenum target, GLsizei n, GLuint* textures) { functions()->glCreateTextures(target, n, textures); }
void glCreateTransformFeedbacks(GLsizei n, GLuint* ids) { functions()->glCreateTransformFeedbacks(n, ids); }
void glCreateVertexArrays(GLsizei n, GLuint* arrays) { functions()->glCreateVertexArrays(n, arrays); }
void glCullFace(GLenum mode) { functions()->glCullFace(mode); }
void glCullParameterdvEXT(GLenum pname, GLdouble* params) { functions()->glCullParameterdvEXT(pname, params); }
void glCullParameterfvEXT(GLenum pname, GLfloat* params) { functions()->glCullParameterfvEXT(pname, params); }
void glCurrentPaletteMatrixARB(GLint index) { functions()->glCurrentPaletteMatrixARB(index); }
void glDebugMessageCallbackAMD(GLDEBUGPROCAMD callback, void* userParam) { functions()->glDebugMessageCallbackAMD(callback, userParam); }
void glDebugMessageCallbackARB(GLDEBUGPROCARB callback, const void* userParam) { functions()->glDebugMessageCallbackARB(callback, userParam); }
void glDebugMessageCallback(GLDEBUGPROC callback, const void* userParam) { functions()->glDebugMessageCallback(callback, userParam); }
void glDebugMessageControlARB(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint* ids, GLboolean enabled) { functions()->glDebugMessageControlARB(source, type, severity, count, ids, enabled); }
void glDebugMessageControl(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint* ids, GLboolean enabled) { functions()->glDebugMessageControl(source, type, severity, count, ids, enabled); }
void glDebugMessageEnableAMD(GLenum category, GLenum severity, GLsizei count, const GLuint* ids, GLboolean enabled) { functions()->glDebugMessageEnableAMD(category, severity, count, ids, enabled); }
void glDebugMessageInsertAMD(GLenum category, GLenum severity, GLuint id, GLsizei length, const GLchar* buf) { functions()->glDebugMessageInsertAMD(category, severity, id, length, buf); }
void glDebugMessageInsertARB(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* buf) { functions()->glDebugMessageInsertARB(source, type, id, severity, length, buf); }
void glDebugMessageInsert(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* buf) { functions()->glDebugMessageInsert(source, type, id, severity, length, buf); }
void glDeformationMap3dSGIX(GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, GLdouble w1, GLdouble w2, GLint wstride, GLint worder, const GLdouble* points) { functions()->glDeformationMap3dSGIX(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, w1, w2, wstride, worder, points); }
void glDeformationMap3fSGIX(GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, GLfloat w1, GLfloat w2, GLint wstride, GLint worder, const GLfloat* points) { functions()->glDeformationMap3fSGIX(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, w1, w2, wstride, worder, points); }
void glDeformSGIX(GLbitfield mask) { functions()->glDeformSGIX(mask); }
void glDeleteAsyncMarkersSGIX(GLuint marker, GLsizei range) { functions()->glDeleteAsyncMarkersSGIX(marker, range); }
void glDeleteBuffersARB(GLsizei n, const GLuint* buffers) { functions()->glDeleteBuffersARB(n, buffers); }
void glDeleteBuffers(GLsizei n, const GLuint* buffers) { functions()->glDeleteBuffers(n, buffers); }
void glDeleteCommandListsNV(GLsizei n, const GLuint* lists) { functions()->glDeleteCommandListsNV(n, lists); }
void glDeleteFencesAPPLE(GLsizei n, const GLuint* fences) { functions()->glDeleteFencesAPPLE(n, fences); }
void glDeleteFencesNV(GLsizei n, const GLuint* fences) { functions()->glDeleteFencesNV(n, fences); }
void glDeleteFragmentShaderATI(GLuint id) { functions()->glDeleteFragmentShaderATI(id); }
void glDeleteFramebuffersEXT(GLsizei n, const GLuint* framebuffers) { functions()->glDeleteFramebuffersEXT(n, framebuffers); }
void glDeleteFramebuffers(GLsizei n, const GLuint* framebuffers) { functions()->glDeleteFramebuffers(n, framebuffers); }
void glDeleteLists(GLuint list, GLsizei range) { functions()->glDeleteLists(list, range); }
void glDeleteNamedStringARB(GLint namelen, const GLchar* name) { functions()->glDeleteNamedStringARB(namelen, name); }
void glDeleteNamesAMD(GLenum identifier, GLuint num, const GLuint* names) { functions()->glDeleteNamesAMD(identifier, num, names); }
void glDeleteObjectARB(GLhandleARB obj) { functions()->glDeleteObjectARB(obj); }
void glDeleteOcclusionQueriesNV(GLsizei n, const GLuint* ids) { functions()->glDeleteOcclusionQueriesNV(n, ids); }
void glDeletePathsNV(GLuint path, GLsizei range) { functions()->glDeletePathsNV(path, range); }
void glDeletePerfMonitorsAMD(GLsizei n, GLuint* monitors) { functions()->glDeletePerfMonitorsAMD(n, monitors); }
void glDeletePerfQueryINTEL(GLuint queryHandle) { functions()->glDeletePerfQueryINTEL(queryHandle); }
void glDeleteProgram(GLuint program) { functions()->glDeleteProgram(program); }
void glDeleteProgramPipelines(GLsizei n, const GLuint* pipelines) { functions()->glDeleteProgramPipelines(n, pipelines); }
void glDeleteProgramsARB(GLsizei n, const GLuint* programs) { functions()->glDeleteProgramsARB(n, programs); }
void glDeleteProgramsNV(GLsizei n, const GLuint* programs) { functions()->glDeleteProgramsNV(n, programs); }
void glDeleteQueriesARB(GLsizei n, const GLuint* ids) { functions()->glDeleteQueriesARB(n, ids); }
void glDeleteQueries(GLsizei n, const GLuint* ids) { functions()->glDeleteQueries(n, ids); }
void glDeleteRenderbuffersEXT(GLsizei n, const GLuint* renderbuffers) { functions()->glDeleteRenderbuffersEXT(n, renderbuffers); }
void glDeleteRenderbuffers(GLsizei n, const GLuint* renderbuffers) { functions()->glDeleteRenderbuffers(n, renderbuffers); }
void glDeleteSamplers(GLsizei count, const GLuint* samplers) { functions()->glDeleteSamplers(count, samplers); }
void glDeleteShader(GLuint shader) { functions()->glDeleteShader(shader); }
void glDeleteStatesNV(GLsizei n, const GLuint* states) { functions()->glDeleteStatesNV(n, states); }
void glDeleteSync(GLsync sync) { functions()->glDeleteSync(sync); }
void glDeleteTexturesEXT(GLsizei n, const GLuint* textures) { functions()->glDeleteTexturesEXT(n, textures); }
void glDeleteTextures(GLsizei n, const GLuint* textures) { functions()->glDeleteTextures(n, textures); }
void glDeleteTransformFeedbacks(GLsizei n, const GLuint* ids) { functions()->glDeleteTransformFeedbacks(n, ids); }
void glDeleteTransformFeedbacksNV(GLsizei n, const GLuint* ids) { functions()->glDeleteTransformFeedbacksNV(n, ids); }
void glDeleteVertexArraysAPPLE(GLsizei n, const GLuint* arrays) { functions()->glDeleteVertexArraysAPPLE(n, arrays); }
void glDeleteVertexArrays(GLsizei n, const GLuint* arrays) { functions()->glDeleteVertexArrays(n, arrays); }
void glDeleteVertexShaderEXT(GLuint id) { functions()->glDeleteVertexShaderEXT(id); }
void glDepthBoundsdNV(GLdouble zmin, GLdouble zmax) { functions()->glDepthBoundsdNV(zmin, zmax); }
void glDepthBoundsEXT(GLclampd zmin, GLclampd zmax) { functions()->glDepthBoundsEXT(zmin, zmax); }
void glDepthFunc(GLenum func) { functions()->glDepthFunc(func); }
void glDepthMask(GLboolean flag) { functions()->glDepthMask(flag); }
void glDepthRangeArrayv(GLuint first, GLsizei count, const GLdouble* v) { functions()->glDepthRangeArrayv(first, count, v); }
void glDepthRangedNV(GLdouble zNear, GLdouble zFar) { functions()->glDepthRangedNV(zNear, zFar); }
void glDepthRangef(GLfloat n, GLfloat f) { functions()->glDepthRangef(n, f); }
void glDepthRangefOES(GLclampf n, GLclampf f) { functions()->glDepthRangefOES(n, f); }
void glDepthRange(GLclampd near_val, GLclampd far_val) { functions()->glDepthRange(near_val, far_val); }
void glDepthRangeIndexed(GLuint index, GLdouble n, GLdouble f) { functions()->glDepthRangeIndexed(index, n, f); }
void glDepthRangexOES(GLfixed n, GLfixed f) { functions()->glDepthRangexOES(n, f); }
void glDetachObjectARB(GLhandleARB containerObj, GLhandleARB attachedObj) { functions()->glDetachObjectARB(containerObj, attachedObj); }
void glDetachShader(GLuint program, GLuint shader) { functions()->glDetachShader(program, shader); }
void glDetailTexFuncSGIS(GLenum target, GLsizei n, const GLfloat* points) { functions()->glDetailTexFuncSGIS(target, n, points); }
void glDisableClientState(GLenum cap) { functions()->glDisableClientState(cap); }
void glDisableClientStateiEXT(GLenum array, GLuint index) { functions()->glDisableClientStateiEXT(array, index); }
void glDisableClientStateIndexedEXT(GLenum array, GLuint index) { functions()->glDisableClientStateIndexedEXT(array, index); }
void glDisable(GLenum cap) { functions()->glDisable(cap); }
void glDisablei(GLenum target, GLuint index) { functions()->glDisablei(target, index); }
void glDisableIndexedEXT(GLenum target, GLuint index) { functions()->glDisableIndexedEXT(target, index); }
void glDisableVariantClientStateEXT(GLuint id) { functions()->glDisableVariantClientStateEXT(id); }
void glDisableVertexArrayAttribEXT(GLuint vaobj, GLuint index) { functions()->glDisableVertexArrayAttribEXT(vaobj, index); }
void glDisableVertexArrayAttrib(GLuint vaobj, GLuint index) { functions()->glDisableVertexArrayAttrib(vaobj, index); }
void glDisableVertexArrayEXT(GLuint vaobj, GLenum array) { functions()->glDisableVertexArrayEXT(vaobj, array); }
void glDisableVertexAttribAPPLE(GLuint index, GLenum pname) { functions()->glDisableVertexAttribAPPLE(index, pname); }
void glDisableVertexAttribArrayARB(GLuint index) { functions()->glDisableVertexAttribArrayARB(index); }
void glDisableVertexAttribArray(GLuint index) { functions()->glDisableVertexAttribArray(index); }
void glDispatchCompute(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z) { functions()->glDispatchCompute(num_groups_x, num_groups_y, num_groups_z); }
void glDispatchComputeGroupSizeARB(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z, GLuint group_size_x, GLuint group_size_y, GLuint group_size_z) { functions()->glDispatchComputeGroupSizeARB(num_groups_x, num_groups_y, num_groups_z, group_size_x, group_size_y, group_size_z); }
void glDispatchComputeIndirect(GLintptr indirect) { functions()->glDispatchComputeIndirect(indirect); }
void glDrawArraysEXT(GLenum mode, GLint first, GLsizei count) { functions()->glDrawArraysEXT(mode, first, count); }
void glDrawArrays(GLenum mode, GLint first, GLsizei count) { functions()->glDrawArrays(mode, first, count); }
void glDrawArraysIndirect(GLenum mode, const void* indirect) { functions()->glDrawArraysIndirect(mode, indirect); }
void glDrawArraysInstancedARB(GLenum mode, GLint first, GLsizei count, GLsizei primcount) { functions()->glDrawArraysInstancedARB(mode, first, count, primcount); }
void glDrawArraysInstancedBaseInstance(GLenum mode, GLint first, GLsizei count, GLsizei instancecount, GLuint baseinstance) { functions()->glDrawArraysInstancedBaseInstance(mode, first, count, instancecount, baseinstance); }
void glDrawArraysInstancedEXT(GLenum mode, GLint start, GLsizei count, GLsizei primcount) { functions()->glDrawArraysInstancedEXT(mode, start, count, primcount); }
void glDrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instancecount) { functions()->glDrawArraysInstanced(mode, first, count, instancecount); }
void glDrawBuffer(GLenum mode) { functions()->glDrawBuffer(mode); }
void glDrawBuffersARB(GLsizei n, const GLenum* bufs) { functions()->glDrawBuffersARB(n, bufs); }
void glDrawBuffersATI(GLsizei n, const GLenum* bufs) { functions()->glDrawBuffersATI(n, bufs); }
void glDrawBuffers(GLsizei n, const GLenum* bufs) { functions()->glDrawBuffers(n, bufs); }
void glDrawCommandsAddressNV(GLenum primitiveMode, const GLuint64* indirects, const GLsizei* sizes, GLuint count) { functions()->glDrawCommandsAddressNV(primitiveMode, indirects, sizes, count); }
void glDrawCommandsNV(GLenum primitiveMode, GLuint buffer, const GLintptr* indirects, const GLsizei* sizes, GLuint count) { functions()->glDrawCommandsNV(primitiveMode, buffer, indirects, sizes, count); }
void glDrawCommandsStatesAddressNV(const GLuint64* indirects, const GLsizei* sizes, const GLuint* states, const GLuint* fbos, GLuint count) { functions()->glDrawCommandsStatesAddressNV(indirects, sizes, states, fbos, count); }
void glDrawCommandsStatesNV(GLuint buffer, const GLintptr* indirects, const GLsizei* sizes, const GLuint* states, const GLuint* fbos, GLuint count) { functions()->glDrawCommandsStatesNV(buffer, indirects, sizes, states, fbos, count); }
void glDrawElementArrayAPPLE(GLenum mode, GLint first, GLsizei count) { functions()->glDrawElementArrayAPPLE(mode, first, count); }
void glDrawElementArrayATI(GLenum mode, GLsizei count) { functions()->glDrawElementArrayATI(mode, count); }
void glDrawElementsBaseVertex(GLenum mode, GLsizei count, GLenum type, const void* indices, GLint basevertex) { functions()->glDrawElementsBaseVertex(mode, count, type, indices, basevertex); }
void glDrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices) { functions()->glDrawElements(mode, count, type, indices); }
void glDrawElementsIndirect(GLenum mode, GLenum type, const void* indirect) { functions()->glDrawElementsIndirect(mode, type, indirect); }
void glDrawElementsInstancedARB(GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei primcount) { functions()->glDrawElementsInstancedARB(mode, count, type, indices, primcount); }
void glDrawElementsInstancedBaseInstance(GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei instancecount, GLuint baseinstance) { functions()->glDrawElementsInstancedBaseInstance(mode, count, type, indices, instancecount, baseinstance); }
void glDrawElementsInstancedBaseVertexBaseInstance(GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance) { functions()->glDrawElementsInstancedBaseVertexBaseInstance(mode, count, type, indices, instancecount, basevertex, baseinstance); }
void glDrawElementsInstancedBaseVertex(GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei instancecount, GLint basevertex) { functions()->glDrawElementsInstancedBaseVertex(mode, count, type, indices, instancecount, basevertex); }
void glDrawElementsInstancedEXT(GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei primcount) { functions()->glDrawElementsInstancedEXT(mode, count, type, indices, primcount); }
void glDrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei instancecount) { functions()->glDrawElementsInstanced(mode, count, type, indices, instancecount); }
void glDrawMeshArraysSUN(GLenum mode, GLint first, GLsizei count, GLsizei width) { functions()->glDrawMeshArraysSUN(mode, first, count, width); }
void glDrawPixels(GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels) { functions()->glDrawPixels(width, height, format, type, pixels); }
void glDrawRangeElementArrayAPPLE(GLenum mode, GLuint start, GLuint end, GLint first, GLsizei count) { functions()->glDrawRangeElementArrayAPPLE(mode, start, end, first, count); }
void glDrawRangeElementArrayATI(GLenum mode, GLuint start, GLuint end, GLsizei count) { functions()->glDrawRangeElementArrayATI(mode, start, end, count); }
void glDrawRangeElementsBaseVertex(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void* indices, GLint basevertex) { functions()->glDrawRangeElementsBaseVertex(mode, start, end, count, type, indices, basevertex); }
void glDrawRangeElementsEXT(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void* indices) { functions()->glDrawRangeElementsEXT(mode, start, end, count, type, indices); }
void glDrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid* indices) { functions()->glDrawRangeElements(mode, start, end, count, type, indices); }
void glDrawTextureNV(GLuint texture, GLuint sampler, GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1, GLfloat z, GLfloat s0, GLfloat t0, GLfloat s1, GLfloat t1) { functions()->glDrawTextureNV(texture, sampler, x0, y0, x1, y1, z, s0, t0, s1, t1); }
void glDrawTransformFeedback(GLenum mode, GLuint id) { functions()->glDrawTransformFeedback(mode, id); }
void glDrawTransformFeedbackInstanced(GLenum mode, GLuint id, GLsizei instancecount) { functions()->glDrawTransformFeedbackInstanced(mode, id, instancecount); }
void glDrawTransformFeedbackNV(GLenum mode, GLuint id) { functions()->glDrawTransformFeedbackNV(mode, id); }
void glDrawTransformFeedbackStream(GLenum mode, GLuint id, GLuint stream) { functions()->glDrawTransformFeedbackStream(mode, id, stream); }
void glDrawTransformFeedbackStreamInstanced(GLenum mode, GLuint id, GLuint stream, GLsizei instancecount) { functions()->glDrawTransformFeedbackStreamInstanced(mode, id, stream, instancecount); }
void glEdgeFlagFormatNV(GLsizei stride) { functions()->glEdgeFlagFormatNV(stride); }
void glEdgeFlag(GLboolean flag) { functions()->glEdgeFlag(flag); }
void glEdgeFlagPointerEXT(GLsizei stride, GLsizei count, const GLboolean* pointer) { functions()->glEdgeFlagPointerEXT(stride, count, pointer); }
void glEdgeFlagPointer(GLsizei stride, const GLvoid* ptr) { functions()->glEdgeFlagPointer(stride, ptr); }
void glEdgeFlagPointerListIBM(GLint stride, const GLboolean** pointer, GLint ptrstride) { functions()->glEdgeFlagPointerListIBM(stride, pointer, ptrstride); }
void glEdgeFlagv(const GLboolean* flag) { functions()->glEdgeFlagv(flag); }
void glEGLImageTargetRenderbufferStorageOES(GLenum target, GLeglImageOES image) { functions()->glEGLImageTargetRenderbufferStorageOES(target, image); }
void glEGLImageTargetTexture2DOES(GLenum target, GLeglImageOES image) { functions()->glEGLImageTargetTexture2DOES(target, image); }
void glElementPointerAPPLE(GLenum type, const void* pointer) { functions()->glElementPointerAPPLE(type, pointer); }
void glElementPointerATI(GLenum type, const void* pointer) { functions()->glElementPointerATI(type, pointer); }
void glEnableClientState(GLenum cap) { functions()->glEnableClientState(cap); }
void glEnableClientStateiEXT(GLenum array, GLuint index) { functions()->glEnableClientStateiEXT(array, index); }
void glEnableClientStateIndexedEXT(GLenum array, GLuint index) { functions()->glEnableClientStateIndexedEXT(array, index); }
void glEnable(GLenum cap) { functions()->glEnable(cap); }
void glEnablei(GLenum target, GLuint index) { functions()->glEnablei(target, index); }
void glEnableIndexedEXT(GLenum target, GLuint index) { functions()->glEnableIndexedEXT(target, index); }
void glEnableVariantClientStateEXT(GLuint id) { functions()->glEnableVariantClientStateEXT(id); }
void glEnableVertexArrayAttribEXT(GLuint vaobj, GLuint index) { functions()->glEnableVertexArrayAttribEXT(vaobj, index); }
void glEnableVertexArrayAttrib(GLuint vaobj, GLuint index) { functions()->glEnableVertexArrayAttrib(vaobj, index); }
void glEnableVertexArrayEXT(GLuint vaobj, GLenum array) { functions()->glEnableVertexArrayEXT(vaobj, array); }
void glEnableVertexAttribAPPLE(GLuint index, GLenum pname) { functions()->glEnableVertexAttribAPPLE(index, pname); }
void glEnableVertexAttribArrayARB(GLuint index) { functions()->glEnableVertexAttribArrayARB(index); }
void glEnableVertexAttribArray(GLuint index) { functions()->glEnableVertexAttribArray(index); }
void glEnd() { functions()->glEnd(); }
void glEndConditionalRender() { functions()->glEndConditionalRender(); }
void glEndConditionalRenderNV() { functions()->glEndConditionalRenderNV(); }
void glEndConditionalRenderNVX() { functions()->glEndConditionalRenderNVX(); }
void glEndFragmentShaderATI() { functions()->glEndFragmentShaderATI(); }
void glEndList() { functions()->glEndList(); }
void glEndOcclusionQueryNV() { functions()->glEndOcclusionQueryNV(); }
void glEndPerfMonitorAMD(GLuint monitor) { functions()->glEndPerfMonitorAMD(monitor); }
void glEndPerfQueryINTEL(GLuint queryHandle) { functions()->glEndPerfQueryINTEL(queryHandle); }
void glEndQueryARB(GLenum target) { functions()->glEndQueryARB(target); }
void glEndQuery(GLenum target) { functions()->glEndQuery(target); }
void glEndQueryIndexed(GLenum target, GLuint index) { functions()->glEndQueryIndexed(target, index); }
void glEndTransformFeedback() { functions()->glEndTransformFeedback(); }
void glEndTransformFeedbackEXT() { functions()->glEndTransformFeedbackEXT(); }
void glEndTransformFeedbackNV() { functions()->glEndTransformFeedbackNV(); }
void glEndVertexShaderEXT() { functions()->glEndVertexShaderEXT(); }
void glEndVideoCaptureNV(GLuint video_capture_slot) { functions()->glEndVideoCaptureNV(video_capture_slot); }
void glEvalCoord1d(GLdouble u) { functions()->glEvalCoord1d(u); }
void glEvalCoord1dv(const GLdouble* u) { functions()->glEvalCoord1dv(u); }
void glEvalCoord1f(GLfloat u) { functions()->glEvalCoord1f(u); }
void glEvalCoord1fv(const GLfloat* u) { functions()->glEvalCoord1fv(u); }
void glEvalCoord1xOES(GLfixed u) { functions()->glEvalCoord1xOES(u); }
void glEvalCoord1xvOES(const GLfixed* coords) { functions()->glEvalCoord1xvOES(coords); }
void glEvalCoord2d(GLdouble u, GLdouble v) { functions()->glEvalCoord2d(u, v); }
void glEvalCoord2dv(const GLdouble* u) { functions()->glEvalCoord2dv(u); }
void glEvalCoord2f(GLfloat u, GLfloat v) { functions()->glEvalCoord2f(u, v); }
void glEvalCoord2fv(const GLfloat* u) { functions()->glEvalCoord2fv(u); }
void glEvalCoord2xOES(GLfixed u, GLfixed v) { functions()->glEvalCoord2xOES(u, v); }
void glEvalCoord2xvOES(const GLfixed* coords) { functions()->glEvalCoord2xvOES(coords); }
void glEvalMapsNV(GLenum target, GLenum mode) { functions()->glEvalMapsNV(target, mode); }
void glEvalMesh1(GLenum mode, GLint i1, GLint i2) { functions()->glEvalMesh1(mode, i1, i2); }
void glEvalMesh2(GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2) { functions()->glEvalMesh2(mode, i1, i2, j1, j2); }
void glEvalPoint1(GLint i) { functions()->glEvalPoint1(i); }
void glEvalPoint2(GLint i, GLint j) { functions()->glEvalPoint2(i, j); }
void glEvaluateDepthValuesARB() { functions()->glEvaluateDepthValuesARB(); }
void glExecuteProgramNV(GLenum target, GLuint id, const GLfloat* params) { functions()->glExecuteProgramNV(target, id, params); }
void glExtractComponentEXT(GLuint res, GLuint src, GLuint num) { functions()->glExtractComponentEXT(res, src, num); }
void glFeedbackBuffer(GLsizei size, GLenum type, GLfloat* buffer) { functions()->glFeedbackBuffer(size, type, buffer); }
void glFeedbackBufferxOES(GLsizei n, GLenum type, const GLfixed* buffer) { functions()->glFeedbackBufferxOES(n, type, buffer); }
void glFinalCombinerInputNV(GLenum variable, GLenum input, GLenum mapping, GLenum componentUsage) { functions()->glFinalCombinerInputNV(variable, input, mapping, componentUsage); }
void glFinish() { functions()->glFinish(); }
void glFinishFenceAPPLE(GLuint fence) { functions()->glFinishFenceAPPLE(fence); }
void glFinishFenceNV(GLuint fence) { functions()->glFinishFenceNV(fence); }
void glFinishObjectAPPLE(GLenum object, GLint name) { functions()->glFinishObjectAPPLE(object, name); }
void glFinishTextureSUNX() { functions()->glFinishTextureSUNX(); }
void glFlush() { functions()->glFlush(); }
void glFlushMappedBufferRangeAPPLE(GLenum target, GLintptr offset, GLsizeiptr size) { functions()->glFlushMappedBufferRangeAPPLE(target, offset, size); }
void glFlushMappedBufferRange(GLenum target, GLintptr offset, GLsizeiptr length) { functions()->glFlushMappedBufferRange(target, offset, length); }
void glFlushMappedNamedBufferRangeEXT(GLuint buffer, GLintptr offset, GLsizeiptr length) { functions()->glFlushMappedNamedBufferRangeEXT(buffer, offset, length); }
void glFlushMappedNamedBufferRange(GLuint buffer, GLintptr offset, GLsizeiptr length) { functions()->glFlushMappedNamedBufferRange(buffer, offset, length); }
void glFlushPixelDataRangeNV(GLenum target) { functions()->glFlushPixelDataRangeNV(target); }
void glFlushRasterSGIX() { functions()->glFlushRasterSGIX(); }
void glFlushStaticDataIBM(GLenum target) { functions()->glFlushStaticDataIBM(target); }
void glFlushVertexArrayRangeAPPLE(GLsizei length, void* pointer) { functions()->glFlushVertexArrayRangeAPPLE(length, pointer); }
void glFlushVertexArrayRangeNV() { functions()->glFlushVertexArrayRangeNV(); }
void glFogCoorddEXT(GLdouble coord) { functions()->glFogCoorddEXT(coord); }
void glFogCoordd(GLdouble coord) { functions()->glFogCoordd(coord); }
void glFogCoorddv(const GLdouble* coord) { functions()->glFogCoorddv(coord); }
void glFogCoorddvEXT(const GLdouble* coord) { functions()->glFogCoorddvEXT(coord); }
void glFogCoordfEXT(GLfloat coord) { functions()->glFogCoordfEXT(coord); }
void glFogCoordf(GLfloat coord) { functions()->glFogCoordf(coord); }
void glFogCoordFormatNV(GLenum type, GLsizei stride) { functions()->glFogCoordFormatNV(type, stride); }
void glFogCoordfv(const GLfloat* coord) { functions()->glFogCoordfv(coord); }
void glFogCoordfvEXT(const GLfloat* coord) { functions()->glFogCoordfvEXT(coord); }
void glFogCoordhNV(GLhalfNV fog) { functions()->glFogCoordhNV(fog); }
void glFogCoordhvNV(const GLhalfNV* fog) { functions()->glFogCoordhvNV(fog); }
void glFogCoordPointerEXT(GLenum type, GLsizei stride, const void* pointer) { functions()->glFogCoordPointerEXT(type, stride, pointer); }
void glFogCoordPointer(GLenum type, GLsizei stride, const void* pointer) { functions()->glFogCoordPointer(type, stride, pointer); }
void glFogCoordPointerListIBM(GLenum type, GLint stride, const void** pointer, GLint ptrstride) { functions()->glFogCoordPointerListIBM(type, stride, pointer, ptrstride); }
void glFogf(GLenum pname, GLfloat param) { functions()->glFogf(pname, param); }
void glFogFuncSGIS(GLsizei n, const GLfloat* points) { functions()->glFogFuncSGIS(n, points); }
void glFogfv(GLenum pname, const GLfloat* params) { functions()->glFogfv(pname, params); }
void glFogi(GLenum pname, GLint param) { functions()->glFogi(pname, param); }
void glFogiv(GLenum pname, const GLint* params) { functions()->glFogiv(pname, params); }
void glFogxOES(GLenum pname, GLfixed param) { functions()->glFogxOES(pname, param); }
void glFogxvOES(GLenum pname, const GLfixed* param) { functions()->glFogxvOES(pname, param); }
void glFragmentColorMaterialSGIX(GLenum face, GLenum mode) { functions()->glFragmentColorMaterialSGIX(face, mode); }
void glFragmentCoverageColorNV(GLuint color) { functions()->glFragmentCoverageColorNV(color); }
void glFragmentLightfSGIX(GLenum light, GLenum pname, GLfloat param) { functions()->glFragmentLightfSGIX(light, pname, param); }
void glFragmentLightfvSGIX(GLenum light, GLenum pname, const GLfloat* params) { functions()->glFragmentLightfvSGIX(light, pname, params); }
void glFragmentLightiSGIX(GLenum light, GLenum pname, GLint param) { functions()->glFragmentLightiSGIX(light, pname, param); }
void glFragmentLightivSGIX(GLenum light, GLenum pname, const GLint* params) { functions()->glFragmentLightivSGIX(light, pname, params); }
void glFragmentLightModelfSGIX(GLenum pname, GLfloat param) { functions()->glFragmentLightModelfSGIX(pname, param); }
void glFragmentLightModelfvSGIX(GLenum pname, const GLfloat* params) { functions()->glFragmentLightModelfvSGIX(pname, params); }
void glFragmentLightModeliSGIX(GLenum pname, GLint param) { functions()->glFragmentLightModeliSGIX(pname, param); }
void glFragmentLightModelivSGIX(GLenum pname, const GLint* params) { functions()->glFragmentLightModelivSGIX(pname, params); }
void glFragmentMaterialfSGIX(GLenum face, GLenum pname, GLfloat param) { functions()->glFragmentMaterialfSGIX(face, pname, param); }
void glFragmentMaterialfvSGIX(GLenum face, GLenum pname, const GLfloat* params) { functions()->glFragmentMaterialfvSGIX(face, pname, params); }
void glFragmentMaterialiSGIX(GLenum face, GLenum pname, GLint param) { functions()->glFragmentMaterialiSGIX(face, pname, param); }
void glFragmentMaterialivSGIX(GLenum face, GLenum pname, const GLint* params) { functions()->glFragmentMaterialivSGIX(face, pname, params); }
void glFramebufferDrawBufferEXT(GLuint framebuffer, GLenum mode) { functions()->glFramebufferDrawBufferEXT(framebuffer, mode); }
void glFramebufferDrawBuffersEXT(GLuint framebuffer, GLsizei n, const GLenum* bufs) { functions()->glFramebufferDrawBuffersEXT(framebuffer, n, bufs); }
void glFramebufferParameteri(GLenum target, GLenum pname, GLint param) { functions()->glFramebufferParameteri(target, pname, param); }
void glFramebufferReadBufferEXT(GLuint framebuffer, GLenum mode) { functions()->glFramebufferReadBufferEXT(framebuffer, mode); }
void glFramebufferRenderbufferEXT(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer) { functions()->glFramebufferRenderbufferEXT(target, attachment, renderbuffertarget, renderbuffer); }
void glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer) { functions()->glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer); }
void glFramebufferSampleLocationsfvARB(GLenum target, GLuint start, GLsizei count, const GLfloat* v) { functions()->glFramebufferSampleLocationsfvARB(target, start, count, v); }
void glFramebufferSampleLocationsfvNV(GLenum target, GLuint start, GLsizei count, const GLfloat* v) { functions()->glFramebufferSampleLocationsfvNV(target, start, count, v); }
void glFramebufferTexture1DEXT(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) { functions()->glFramebufferTexture1DEXT(target, attachment, textarget, texture, level); }
void glFramebufferTexture1D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) { functions()->glFramebufferTexture1D(target, attachment, textarget, texture, level); }
void glFramebufferTexture2DEXT(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) { functions()->glFramebufferTexture2DEXT(target, attachment, textarget, texture, level); }
void glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) { functions()->glFramebufferTexture2D(target, attachment, textarget, texture, level); }
void glFramebufferTexture3DEXT(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset) { functions()->glFramebufferTexture3DEXT(target, attachment, textarget, texture, level, zoffset); }
void glFramebufferTexture3D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset) { functions()->glFramebufferTexture3D(target, attachment, textarget, texture, level, zoffset); }
void glFramebufferTextureARB(GLenum target, GLenum attachment, GLuint texture, GLint level) { functions()->glFramebufferTextureARB(target, attachment, texture, level); }
void glFramebufferTextureEXT(GLenum target, GLenum attachment, GLuint texture, GLint level) { functions()->glFramebufferTextureEXT(target, attachment, texture, level); }
void glFramebufferTextureFaceARB(GLenum target, GLenum attachment, GLuint texture, GLint level, GLenum face) { functions()->glFramebufferTextureFaceARB(target, attachment, texture, level, face); }
void glFramebufferTextureFaceEXT(GLenum target, GLenum attachment, GLuint texture, GLint level, GLenum face) { functions()->glFramebufferTextureFaceEXT(target, attachment, texture, level, face); }
void glFramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint level) { functions()->glFramebufferTexture(target, attachment, texture, level); }
void glFramebufferTextureLayerARB(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer) { functions()->glFramebufferTextureLayerARB(target, attachment, texture, level, layer); }
void glFramebufferTextureLayerEXT(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer) { functions()->glFramebufferTextureLayerEXT(target, attachment, texture, level, layer); }
void glFramebufferTextureLayer(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer) { functions()->glFramebufferTextureLayer(target, attachment, texture, level, layer); }
void glFramebufferTextureMultiviewOVR(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint baseViewIndex, GLsizei numViews) { functions()->glFramebufferTextureMultiviewOVR(target, attachment, texture, level, baseViewIndex, numViews); }
void glFrameTerminatorGREMEDY() { functions()->glFrameTerminatorGREMEDY(); }
void glFrameZoomSGIX(GLint factor) { functions()->glFrameZoomSGIX(factor); }
void glFreeObjectBufferATI(GLuint buffer) { functions()->glFreeObjectBufferATI(buffer); }
void glFrontFace(GLenum mode) { functions()->glFrontFace(mode); }
void glFrustumfOES(GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f) { functions()->glFrustumfOES(l, r, b, t, n, f); }
void glFrustum(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near_val, GLdouble far_val) { functions()->glFrustum(left, right, bottom, top, near_val, far_val); }
void glFrustumxOES(GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f) { functions()->glFrustumxOES(l, r, b, t, n, f); }
void glGenBuffersARB(GLsizei n, GLuint* buffers) { functions()->glGenBuffersARB(n, buffers); }
void glGenBuffers(GLsizei n, GLuint* buffers) { functions()->glGenBuffers(n, buffers); }
void glGenerateMipmapEXT(GLenum target) { functions()->glGenerateMipmapEXT(target); }
void glGenerateMipmap(GLenum target) { functions()->glGenerateMipmap(target); }
void glGenerateMultiTexMipmapEXT(GLenum texunit, GLenum target) { functions()->glGenerateMultiTexMipmapEXT(texunit, target); }
void glGenerateTextureMipmapEXT(GLuint texture, GLenum target) { functions()->glGenerateTextureMipmapEXT(texture, target); }
void glGenerateTextureMipmap(GLuint texture) { functions()->glGenerateTextureMipmap(texture); }
void glGenFencesAPPLE(GLsizei n, GLuint* fences) { functions()->glGenFencesAPPLE(n, fences); }
void glGenFencesNV(GLsizei n, GLuint* fences) { functions()->glGenFencesNV(n, fences); }
void glGenFramebuffersEXT(GLsizei n, GLuint* framebuffers) { functions()->glGenFramebuffersEXT(n, framebuffers); }
void glGenFramebuffers(GLsizei n, GLuint* framebuffers) { functions()->glGenFramebuffers(n, framebuffers); }
void glGenNamesAMD(GLenum identifier, GLuint num, GLuint* names) { functions()->glGenNamesAMD(identifier, num, names); }
void glGenOcclusionQueriesNV(GLsizei n, GLuint* ids) { functions()->glGenOcclusionQueriesNV(n, ids); }
void glGenPerfMonitorsAMD(GLsizei n, GLuint* monitors) { functions()->glGenPerfMonitorsAMD(n, monitors); }
void glGenProgramPipelines(GLsizei n, GLuint* pipelines) { functions()->glGenProgramPipelines(n, pipelines); }
void glGenProgramsARB(GLsizei n, GLuint* programs) { functions()->glGenProgramsARB(n, programs); }
void glGenProgramsNV(GLsizei n, GLuint* programs) { functions()->glGenProgramsNV(n, programs); }
void glGenQueriesARB(GLsizei n, GLuint* ids) { functions()->glGenQueriesARB(n, ids); }
void glGenQueries(GLsizei n, GLuint* ids) { functions()->glGenQueries(n, ids); }
void glGenRenderbuffersEXT(GLsizei n, GLuint* renderbuffers) { functions()->glGenRenderbuffersEXT(n, renderbuffers); }
void glGenRenderbuffers(GLsizei n, GLuint* renderbuffers) { functions()->glGenRenderbuffers(n, renderbuffers); }
void glGenSamplers(GLsizei count, GLuint* samplers) { functions()->glGenSamplers(count, samplers); }
void glGenTexturesEXT(GLsizei n, GLuint* textures) { functions()->glGenTexturesEXT(n, textures); }
void glGenTextures(GLsizei n, GLuint* textures) { functions()->glGenTextures(n, textures); }
void glGenTransformFeedbacks(GLsizei n, GLuint* ids) { functions()->glGenTransformFeedbacks(n, ids); }
void glGenTransformFeedbacksNV(GLsizei n, GLuint* ids) { functions()->glGenTransformFeedbacksNV(n, ids); }
void glGenVertexArraysAPPLE(GLsizei n, GLuint* arrays) { functions()->glGenVertexArraysAPPLE(n, arrays); }
void glGenVertexArrays(GLsizei n, GLuint* arrays) { functions()->glGenVertexArrays(n, arrays); }
void glGetActiveAtomicCounterBufferiv(GLuint program, GLuint bufferIndex, GLenum pname, GLint* params) { functions()->glGetActiveAtomicCounterBufferiv(program, bufferIndex, pname, params); }
void glGetActiveAttribARB(GLhandleARB programObj, GLuint index, GLsizei maxLength, GLsizei* length, GLint* size, GLenum* type, GLcharARB* name) { functions()->glGetActiveAttribARB(programObj, index, maxLength, length, size, type, name); }
void glGetActiveAttrib(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name) { functions()->glGetActiveAttrib(program, index, bufSize, length, size, type, name); }
void glGetActiveSubroutineName(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei* length, GLchar* name) { functions()->glGetActiveSubroutineName(program, shadertype, index, bufsize, length, name); }
void glGetActiveSubroutineUniformiv(GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint* values) { functions()->glGetActiveSubroutineUniformiv(program, shadertype, index, pname, values); }
void glGetActiveSubroutineUniformName(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei* length, GLchar* name) { functions()->glGetActiveSubroutineUniformName(program, shadertype, index, bufsize, length, name); }
void glGetActiveUniformARB(GLhandleARB programObj, GLuint index, GLsizei maxLength, GLsizei* length, GLint* size, GLenum* type, GLcharARB* name) { functions()->glGetActiveUniformARB(programObj, index, maxLength, length, size, type, name); }
void glGetActiveUniformBlockiv(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint* params) { functions()->glGetActiveUniformBlockiv(program, uniformBlockIndex, pname, params); }
void glGetActiveUniformBlockName(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei* length, GLchar* uniformBlockName) { functions()->glGetActiveUniformBlockName(program, uniformBlockIndex, bufSize, length, uniformBlockName); }
void glGetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name) { functions()->glGetActiveUniform(program, index, bufSize, length, size, type, name); }
void glGetActiveUniformName(GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei* length, GLchar* uniformName) { functions()->glGetActiveUniformName(program, uniformIndex, bufSize, length, uniformName); }
void glGetActiveUniformsiv(GLuint program, GLsizei uniformCount, const GLuint* uniformIndices, GLenum pname, GLint* params) { functions()->glGetActiveUniformsiv(program, uniformCount, uniformIndices, pname, params); }
void glGetActiveVaryingNV(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLsizei* size, GLenum* type, GLchar* name) { functions()->glGetActiveVaryingNV(program, index, bufSize, length, size, type, name); }
void glGetArrayObjectfvATI(GLenum array, GLenum pname, GLfloat* params) { functions()->glGetArrayObjectfvATI(array, pname, params); }
void glGetArrayObjectivATI(GLenum array, GLenum pname, GLint* params) { functions()->glGetArrayObjectivATI(array, pname, params); }
void glGetAttachedObjectsARB(GLhandleARB containerObj, GLsizei maxCount, GLsizei* count, GLhandleARB* obj) { functions()->glGetAttachedObjectsARB(containerObj, maxCount, count, obj); }
void glGetAttachedShaders(GLuint program, GLsizei maxCount, GLsizei* count, GLuint* shaders) { functions()->glGetAttachedShaders(program, maxCount, count, shaders); }
void glGetBooleanIndexedvEXT(GLenum target, GLuint index, GLboolean* data) { functions()->glGetBooleanIndexedvEXT(target, index, data); }
void glGetBooleani_v(GLenum target, GLuint index, GLboolean* data) { functions()->glGetBooleani_v(target, index, data); }
void glGetBooleanv(GLenum pname, GLboolean* params) { functions()->glGetBooleanv(pname, params); }
void glGetBufferParameteri64v(GLenum target, GLenum pname, GLint64* params) { functions()->glGetBufferParameteri64v(target, pname, params); }
void glGetBufferParameterivARB(GLenum target, GLenum pname, GLint* params) { functions()->glGetBufferParameterivARB(target, pname, params); }
void glGetBufferParameteriv(GLenum target, GLenum pname, GLint* params) { functions()->glGetBufferParameteriv(target, pname, params); }
void glGetBufferParameterui64vNV(GLenum target, GLenum pname, GLuint64EXT* params) { functions()->glGetBufferParameterui64vNV(target, pname, params); }
void glGetBufferPointervARB(GLenum target, GLenum pname, void** params) { functions()->glGetBufferPointervARB(target, pname, params); }
void glGetBufferPointerv(GLenum target, GLenum pname, void** params) { functions()->glGetBufferPointerv(target, pname, params); }
void glGetBufferSubDataARB(GLenum target, GLintptrARB offset, GLsizeiptrARB size, void* data) { functions()->glGetBufferSubDataARB(target, offset, size, data); }
void glGetBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, void* data) { functions()->glGetBufferSubData(target, offset, size, data); }
void glGetClipPlanefOES(GLenum plane, GLfloat* equation) { functions()->glGetClipPlanefOES(plane, equation); }
void glGetClipPlane(GLenum plane, GLdouble* equation) { functions()->glGetClipPlane(plane, equation); }
void glGetClipPlanexOES(GLenum plane, GLfixed* equation) { functions()->glGetClipPlanexOES(plane, equation); }
void glGetColorTableEXT(GLenum target, GLenum format, GLenum type, void* data) { functions()->glGetColorTableEXT(target, format, type, data); }
void glGetColorTable(GLenum target, GLenum format, GLenum type, GLvoid* table) { functions()->glGetColorTable(target, format, type, table); }
void glGetColorTableParameterfvEXT(GLenum target, GLenum pname, GLfloat* params) { functions()->glGetColorTableParameterfvEXT(target, pname, params); }
void glGetColorTableParameterfv(GLenum target, GLenum pname, GLfloat* params) { functions()->glGetColorTableParameterfv(target, pname, params); }
void glGetColorTableParameterfvSGI(GLenum target, GLenum pname, GLfloat* params) { functions()->glGetColorTableParameterfvSGI(target, pname, params); }
void glGetColorTableParameterivEXT(GLenum target, GLenum pname, GLint* params) { functions()->glGetColorTableParameterivEXT(target, pname, params); }
void glGetColorTableParameteriv(GLenum target, GLenum pname, GLint* params) { functions()->glGetColorTableParameteriv(target, pname, params); }
void glGetColorTableParameterivSGI(GLenum target, GLenum pname, GLint* params) { functions()->glGetColorTableParameterivSGI(target, pname, params); }
void glGetColorTableSGI(GLenum target, GLenum format, GLenum type, void* table) { functions()->glGetColorTableSGI(target, format, type, table); }
void glGetCombinerInputParameterfvNV(GLenum stage, GLenum portion, GLenum variable, GLenum pname, GLfloat* params) { functions()->glGetCombinerInputParameterfvNV(stage, portion, variable, pname, params); }
void glGetCombinerInputParameterivNV(GLenum stage, GLenum portion, GLenum variable, GLenum pname, GLint* params) { functions()->glGetCombinerInputParameterivNV(stage, portion, variable, pname, params); }
void glGetCombinerOutputParameterfvNV(GLenum stage, GLenum portion, GLenum pname, GLfloat* params) { functions()->glGetCombinerOutputParameterfvNV(stage, portion, pname, params); }
void glGetCombinerOutputParameterivNV(GLenum stage, GLenum portion, GLenum pname, GLint* params) { functions()->glGetCombinerOutputParameterivNV(stage, portion, pname, params); }
void glGetCombinerStageParameterfvNV(GLenum stage, GLenum pname, GLfloat* params) { functions()->glGetCombinerStageParameterfvNV(stage, pname, params); }
void glGetCompressedMultiTexImageEXT(GLenum texunit, GLenum target, GLint lod, void* img) { functions()->glGetCompressedMultiTexImageEXT(texunit, target, lod, img); }
void glGetCompressedTexImageARB(GLenum target, GLint level, void* img) { functions()->glGetCompressedTexImageARB(target, level, img); }
void glGetCompressedTexImage(GLenum target, GLint lod, GLvoid* img) { functions()->glGetCompressedTexImage(target, lod, img); }
void glGetCompressedTextureImageEXT(GLuint texture, GLenum target, GLint lod, void* img) { functions()->glGetCompressedTextureImageEXT(texture, target, lod, img); }
void glGetCompressedTextureImage(GLuint texture, GLint level, GLsizei bufSize, void* pixels) { functions()->glGetCompressedTextureImage(texture, level, bufSize, pixels); }
void glGetCompressedTextureSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei bufSize, void* pixels) { functions()->glGetCompressedTextureSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, bufSize, pixels); }
void glGetConvolutionFilterEXT(GLenum target, GLenum format, GLenum type, void* image) { functions()->glGetConvolutionFilterEXT(target, format, type, image); }
void glGetConvolutionFilter(GLenum target, GLenum format, GLenum type, GLvoid* image) { functions()->glGetConvolutionFilter(target, format, type, image); }
void glGetConvolutionParameterfvEXT(GLenum target, GLenum pname, GLfloat* params) { functions()->glGetConvolutionParameterfvEXT(target, pname, params); }
void glGetConvolutionParameterfv(GLenum target, GLenum pname, GLfloat* params) { functions()->glGetConvolutionParameterfv(target, pname, params); }
void glGetConvolutionParameterivEXT(GLenum target, GLenum pname, GLint* params) { functions()->glGetConvolutionParameterivEXT(target, pname, params); }
void glGetConvolutionParameteriv(GLenum target, GLenum pname, GLint* params) { functions()->glGetConvolutionParameteriv(target, pname, params); }
void glGetConvolutionParameterxvOES(GLenum target, GLenum pname, GLfixed* params) { functions()->glGetConvolutionParameterxvOES(target, pname, params); }
void glGetCoverageModulationTableNV(GLsizei bufsize, GLfloat* v) { functions()->glGetCoverageModulationTableNV(bufsize, v); }
void glGetDetailTexFuncSGIS(GLenum target, GLfloat* points) { functions()->glGetDetailTexFuncSGIS(target, points); }
void glGetDoubleIndexedvEXT(GLenum target, GLuint index, GLdouble* data) { functions()->glGetDoubleIndexedvEXT(target, index, data); }
void glGetDoublei_vEXT(GLenum pname, GLuint index, GLdouble* params) { functions()->glGetDoublei_vEXT(pname, index, params); }
void glGetDoublei_v(GLenum target, GLuint index, GLdouble* data) { functions()->glGetDoublei_v(target, index, data); }
void glGetDoublev(GLenum pname, GLdouble* params) { functions()->glGetDoublev(pname, params); }
void glGetFenceivNV(GLuint fence, GLenum pname, GLint* params) { functions()->glGetFenceivNV(fence, pname, params); }
void glGetFinalCombinerInputParameterfvNV(GLenum variable, GLenum pname, GLfloat* params) { functions()->glGetFinalCombinerInputParameterfvNV(variable, pname, params); }
void glGetFinalCombinerInputParameterivNV(GLenum variable, GLenum pname, GLint* params) { functions()->glGetFinalCombinerInputParameterivNV(variable, pname, params); }
void glGetFirstPerfQueryIdINTEL(GLuint* queryId) { functions()->glGetFirstPerfQueryIdINTEL(queryId); }
void glGetFixedvOES(GLenum pname, GLfixed* params) { functions()->glGetFixedvOES(pname, params); }
void glGetFloatIndexedvEXT(GLenum target, GLuint index, GLfloat* data) { functions()->glGetFloatIndexedvEXT(target, index, data); }
void glGetFloati_vEXT(GLenum pname, GLuint index, GLfloat* params) { functions()->glGetFloati_vEXT(pname, index, params); }
void glGetFloati_v(GLenum target, GLuint index, GLfloat* data) { functions()->glGetFloati_v(target, index, data); }
void glGetFloatv(GLenum pname, GLfloat* params) { functions()->glGetFloatv(pname, params); }
void glGetFogFuncSGIS(GLfloat* points) { functions()->glGetFogFuncSGIS(points); }
void glGetFragmentLightfvSGIX(GLenum light, GLenum pname, GLfloat* params) { functions()->glGetFragmentLightfvSGIX(light, pname, params); }
void glGetFragmentLightivSGIX(GLenum light, GLenum pname, GLint* params) { functions()->glGetFragmentLightivSGIX(light, pname, params); }
void glGetFragmentMaterialfvSGIX(GLenum face, GLenum pname, GLfloat* params) { functions()->glGetFragmentMaterialfvSGIX(face, pname, params); }
void glGetFragmentMaterialivSGIX(GLenum face, GLenum pname, GLint* params) { functions()->glGetFragmentMaterialivSGIX(face, pname, params); }
void glGetFramebufferAttachmentParameterivEXT(GLenum target, GLenum attachment, GLenum pname, GLint* params) { functions()->glGetFramebufferAttachmentParameterivEXT(target, attachment, pname, params); }
void glGetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint* params) { functions()->glGetFramebufferAttachmentParameteriv(target, attachment, pname, params); }
void glGetFramebufferParameterivEXT(GLuint framebuffer, GLenum pname, GLint* params) { functions()->glGetFramebufferParameterivEXT(framebuffer, pname, params); }
void glGetFramebufferParameteriv(GLenum target, GLenum pname, GLint* params) { functions()->glGetFramebufferParameteriv(target, pname, params); }
void glGetHistogramEXT(GLenum target, GLboolean reset, GLenum format, GLenum type, void* values) { functions()->glGetHistogramEXT(target, reset, format, type, values); }
void glGetHistogram(GLenum target, GLboolean reset, GLenum format, GLenum type, GLvoid* values) { functions()->glGetHistogram(target, reset, format, type, values); }
void glGetHistogramParameterfvEXT(GLenum target, GLenum pname, GLfloat* params) { functions()->glGetHistogramParameterfvEXT(target, pname, params); }
void glGetHistogramParameterfv(GLenum target, GLenum pname, GLfloat* params) { functions()->glGetHistogramParameterfv(target, pname, params); }
void glGetHistogramParameterivEXT(GLenum target, GLenum pname, GLint* params) { functions()->glGetHistogramParameterivEXT(target, pname, params); }
void glGetHistogramParameteriv(GLenum target, GLenum pname, GLint* params) { functions()->glGetHistogramParameteriv(target, pname, params); }
void glGetHistogramParameterxvOES(GLenum target, GLenum pname, GLfixed* params) { functions()->glGetHistogramParameterxvOES(target, pname, params); }
void glGetImageTransformParameterfvHP(GLenum target, GLenum pname, GLfloat* params) { functions()->glGetImageTransformParameterfvHP(target, pname, params); }
void glGetImageTransformParameterivHP(GLenum target, GLenum pname, GLint* params) { functions()->glGetImageTransformParameterivHP(target, pname, params); }
void glGetInfoLogARB(GLhandleARB obj, GLsizei maxLength, GLsizei* length, GLcharARB* infoLog) { functions()->glGetInfoLogARB(obj, maxLength, length, infoLog); }
void glGetInteger64i_v(GLenum target, GLuint index, GLint64* data) { functions()->glGetInteger64i_v(target, index, data); }
void glGetInteger64v(GLenum pname, GLint64* data) { functions()->glGetInteger64v(pname, data); }
void glGetIntegerIndexedvEXT(GLenum target, GLuint index, GLint* data) { functions()->glGetIntegerIndexedvEXT(target, index, data); }
void glGetIntegeri_v(GLenum target, GLuint index, GLint* data) { functions()->glGetIntegeri_v(target, index, data); }
void glGetIntegerui64i_vNV(GLenum value, GLuint index, GLuint64EXT* result) { functions()->glGetIntegerui64i_vNV(value, index, result); }
void glGetIntegerui64vNV(GLenum value, GLuint64EXT* result) { functions()->glGetIntegerui64vNV(value, result); }
void glGetIntegerv(GLenum pname, GLint* params) { functions()->glGetIntegerv(pname, params); }
void glGetInternalformati64v(GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint64* params) { functions()->glGetInternalformati64v(target, internalformat, pname, bufSize, params); }
void glGetInternalformativ(GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint* params) { functions()->glGetInternalformativ(target, internalformat, pname, bufSize, params); }
void glGetInternalformatSampleivNV(GLenum target, GLenum internalformat, GLsizei samples, GLenum pname, GLsizei bufSize, GLint* params) { functions()->glGetInternalformatSampleivNV(target, internalformat, samples, pname, bufSize, params); }
void glGetInvariantBooleanvEXT(GLuint id, GLenum value, GLboolean* data) { functions()->glGetInvariantBooleanvEXT(id, value, data); }
void glGetInvariantFloatvEXT(GLuint id, GLenum value, GLfloat* data) { functions()->glGetInvariantFloatvEXT(id, value, data); }
void glGetInvariantIntegervEXT(GLuint id, GLenum value, GLint* data) { functions()->glGetInvariantIntegervEXT(id, value, data); }
void glGetLightfv(GLenum light, GLenum pname, GLfloat* params) { functions()->glGetLightfv(light, pname, params); }
void glGetLightiv(GLenum light, GLenum pname, GLint* params) { functions()->glGetLightiv(light, pname, params); }
void glGetLightxOES(GLenum light, GLenum pname, GLfixed* params) { functions()->glGetLightxOES(light, pname, params); }
void glGetListParameterfvSGIX(GLuint list, GLenum pname, GLfloat* params) { functions()->glGetListParameterfvSGIX(list, pname, params); }
void glGetListParameterivSGIX(GLuint list, GLenum pname, GLint* params) { functions()->glGetListParameterivSGIX(list, pname, params); }
void glGetLocalConstantBooleanvEXT(GLuint id, GLenum value, GLboolean* data) { functions()->glGetLocalConstantBooleanvEXT(id, value, data); }
void glGetLocalConstantFloatvEXT(GLuint id, GLenum value, GLfloat* data) { functions()->glGetLocalConstantFloatvEXT(id, value, data); }
void glGetLocalConstantIntegervEXT(GLuint id, GLenum value, GLint* data) { functions()->glGetLocalConstantIntegervEXT(id, value, data); }
void glGetMapAttribParameterfvNV(GLenum target, GLuint index, GLenum pname, GLfloat* params) { functions()->glGetMapAttribParameterfvNV(target, index, pname, params); }
void glGetMapAttribParameterivNV(GLenum target, GLuint index, GLenum pname, GLint* params) { functions()->glGetMapAttribParameterivNV(target, index, pname, params); }
void glGetMapControlPointsNV(GLenum target, GLuint index, GLenum type, GLsizei ustride, GLsizei vstride, GLboolean packed, void* points) { functions()->glGetMapControlPointsNV(target, index, type, ustride, vstride, packed, points); }
void glGetMapdv(GLenum target, GLenum query, GLdouble* v) { functions()->glGetMapdv(target, query, v); }
void glGetMapfv(GLenum target, GLenum query, GLfloat* v) { functions()->glGetMapfv(target, query, v); }
void glGetMapiv(GLenum target, GLenum query, GLint* v) { functions()->glGetMapiv(target, query, v); }
void glGetMapParameterfvNV(GLenum target, GLenum pname, GLfloat* params) { functions()->glGetMapParameterfvNV(target, pname, params); }
void glGetMapParameterivNV(GLenum target, GLenum pname, GLint* params) { functions()->glGetMapParameterivNV(target, pname, params); }
void glGetMapxvOES(GLenum target, GLenum query, GLfixed* v) { functions()->glGetMapxvOES(target, query, v); }
void glGetMaterialfv(GLenum face, GLenum pname, GLfloat* params) { functions()->glGetMaterialfv(face, pname, params); }
void glGetMaterialiv(GLenum face, GLenum pname, GLint* params) { functions()->glGetMaterialiv(face, pname, params); }
void glGetMaterialxOES(GLenum face, GLenum pname, GLfixed param) { functions()->glGetMaterialxOES(face, pname, param); }
void glGetMinmaxEXT(GLenum target, GLboolean reset, GLenum format, GLenum type, void* values) { functions()->glGetMinmaxEXT(target, reset, format, type, values); }
void glGetMinmax(GLenum target, GLboolean reset, GLenum format, GLenum types, GLvoid* values) { functions()->glGetMinmax(target, reset, format, types, values); }
void glGetMinmaxParameterfvEXT(GLenum target, GLenum pname, GLfloat* params) { functions()->glGetMinmaxParameterfvEXT(target, pname, params); }
void glGetMinmaxParameterfv(GLenum target, GLenum pname, GLfloat* params) { functions()->glGetMinmaxParameterfv(target, pname, params); }
void glGetMinmaxParameterivEXT(GLenum target, GLenum pname, GLint* params) { functions()->glGetMinmaxParameterivEXT(target, pname, params); }
void glGetMinmaxParameteriv(GLenum target, GLenum pname, GLint* params) { functions()->glGetMinmaxParameteriv(target, pname, params); }
void glGetMultisamplefv(GLenum pname, GLuint index, GLfloat* val) { functions()->glGetMultisamplefv(pname, index, val); }
void glGetMultisamplefvNV(GLenum pname, GLuint index, GLfloat* val) { functions()->glGetMultisamplefvNV(pname, index, val); }
void glGetMultiTexEnvfvEXT(GLenum texunit, GLenum target, GLenum pname, GLfloat* params) { functions()->glGetMultiTexEnvfvEXT(texunit, target, pname, params); }
void glGetMultiTexEnvivEXT(GLenum texunit, GLenum target, GLenum pname, GLint* params) { functions()->glGetMultiTexEnvivEXT(texunit, target, pname, params); }
void glGetMultiTexGendvEXT(GLenum texunit, GLenum coord, GLenum pname, GLdouble* params) { functions()->glGetMultiTexGendvEXT(texunit, coord, pname, params); }
void glGetMultiTexGenfvEXT(GLenum texunit, GLenum coord, GLenum pname, GLfloat* params) { functions()->glGetMultiTexGenfvEXT(texunit, coord, pname, params); }
void glGetMultiTexGenivEXT(GLenum texunit, GLenum coord, GLenum pname, GLint* params) { functions()->glGetMultiTexGenivEXT(texunit, coord, pname, params); }
void glGetMultiTexImageEXT(GLenum texunit, GLenum target, GLint level, GLenum format, GLenum type, void* pixels) { functions()->glGetMultiTexImageEXT(texunit, target, level, format, type, pixels); }
void glGetMultiTexLevelParameterfvEXT(GLenum texunit, GLenum target, GLint level, GLenum pname, GLfloat* params) { functions()->glGetMultiTexLevelParameterfvEXT(texunit, target, level, pname, params); }
void glGetMultiTexLevelParameterivEXT(GLenum texunit, GLenum target, GLint level, GLenum pname, GLint* params) { functions()->glGetMultiTexLevelParameterivEXT(texunit, target, level, pname, params); }
void glGetMultiTexParameterfvEXT(GLenum texunit, GLenum target, GLenum pname, GLfloat* params) { functions()->glGetMultiTexParameterfvEXT(texunit, target, pname, params); }
void glGetMultiTexParameterIivEXT(GLenum texunit, GLenum target, GLenum pname, GLint* params) { functions()->glGetMultiTexParameterIivEXT(texunit, target, pname, params); }
void glGetMultiTexParameterIuivEXT(GLenum texunit, GLenum target, GLenum pname, GLuint* params) { functions()->glGetMultiTexParameterIuivEXT(texunit, target, pname, params); }
void glGetMultiTexParameterivEXT(GLenum texunit, GLenum target, GLenum pname, GLint* params) { functions()->glGetMultiTexParameterivEXT(texunit, target, pname, params); }
void glGetNamedBufferParameteri64v(GLuint buffer, GLenum pname, GLint64* params) { functions()->glGetNamedBufferParameteri64v(buffer, pname, params); }
void glGetNamedBufferParameterivEXT(GLuint buffer, GLenum pname, GLint* params) { functions()->glGetNamedBufferParameterivEXT(buffer, pname, params); }
void glGetNamedBufferParameteriv(GLuint buffer, GLenum pname, GLint* params) { functions()->glGetNamedBufferParameteriv(buffer, pname, params); }
void glGetNamedBufferParameterui64vNV(GLuint buffer, GLenum pname, GLuint64EXT* params) { functions()->glGetNamedBufferParameterui64vNV(buffer, pname, params); }
void glGetNamedBufferPointervEXT(GLuint buffer, GLenum pname, void** params) { functions()->glGetNamedBufferPointervEXT(buffer, pname, params); }
void glGetNamedBufferPointerv(GLuint buffer, GLenum pname, void** params) { functions()->glGetNamedBufferPointerv(buffer, pname, params); }
void glGetNamedBufferSubDataEXT(GLuint buffer, GLintptr offset, GLsizeiptr size, void* data) { functions()->glGetNamedBufferSubDataEXT(buffer, offset, size, data); }
void glGetNamedBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr size, void* data) { functions()->glGetNamedBufferSubData(buffer, offset, size, data); }
void glGetNamedFramebufferAttachmentParameterivEXT(GLuint framebuffer, GLenum attachment, GLenum pname, GLint* params) { functions()->glGetNamedFramebufferAttachmentParameterivEXT(framebuffer, attachment, pname, params); }
void glGetNamedFramebufferAttachmentParameteriv(GLuint framebuffer, GLenum attachment, GLenum pname, GLint* params) { functions()->glGetNamedFramebufferAttachmentParameteriv(framebuffer, attachment, pname, params); }
void glGetNamedFramebufferParameterivEXT(GLuint framebuffer, GLenum pname, GLint* params) { functions()->glGetNamedFramebufferParameterivEXT(framebuffer, pname, params); }
void glGetNamedFramebufferParameteriv(GLuint framebuffer, GLenum pname, GLint* param) { functions()->glGetNamedFramebufferParameteriv(framebuffer, pname, param); }
void glGetNamedProgramivEXT(GLuint program, GLenum target, GLenum pname, GLint* params) { functions()->glGetNamedProgramivEXT(program, target, pname, params); }
void glGetNamedProgramLocalParameterdvEXT(GLuint program, GLenum target, GLuint index, GLdouble* params) { functions()->glGetNamedProgramLocalParameterdvEXT(program, target, index, params); }
void glGetNamedProgramLocalParameterfvEXT(GLuint program, GLenum target, GLuint index, GLfloat* params) { functions()->glGetNamedProgramLocalParameterfvEXT(program, target, index, params); }
void glGetNamedProgramLocalParameterIivEXT(GLuint program, GLenum target, GLuint index, GLint* params) { functions()->glGetNamedProgramLocalParameterIivEXT(program, target, index, params); }
void glGetNamedProgramLocalParameterIuivEXT(GLuint program, GLenum target, GLuint index, GLuint* params) { functions()->glGetNamedProgramLocalParameterIuivEXT(program, target, index, params); }
void glGetNamedProgramStringEXT(GLuint program, GLenum target, GLenum pname, void* string) { functions()->glGetNamedProgramStringEXT(program, target, pname, string); }
void glGetNamedRenderbufferParameterivEXT(GLuint renderbuffer, GLenum pname, GLint* params) { functions()->glGetNamedRenderbufferParameterivEXT(renderbuffer, pname, params); }
void glGetNamedRenderbufferParameteriv(GLuint renderbuffer, GLenum pname, GLint* params) { functions()->glGetNamedRenderbufferParameteriv(renderbuffer, pname, params); }
void glGetNamedStringARB(GLint namelen, const GLchar* name, GLsizei bufSize, GLint* stringlen, GLchar* string) { functions()->glGetNamedStringARB(namelen, name, bufSize, stringlen, string); }
void glGetNamedStringivARB(GLint namelen, const GLchar* name, GLenum pname, GLint* params) { functions()->glGetNamedStringivARB(namelen, name, pname, params); }
void glGetnColorTableARB(GLenum target, GLenum format, GLenum type, GLsizei bufSize, void* table) { functions()->glGetnColorTableARB(target, format, type, bufSize, table); }
void glGetnColorTable(GLenum target, GLenum format, GLenum type, GLsizei bufSize, void* table) { functions()->glGetnColorTable(target, format, type, bufSize, table); }
void glGetnCompressedTexImageARB(GLenum target, GLint lod, GLsizei bufSize, void* img) { functions()->glGetnCompressedTexImageARB(target, lod, bufSize, img); }
void glGetnCompressedTexImage(GLenum target, GLint lod, GLsizei bufSize, void* pixels) { functions()->glGetnCompressedTexImage(target, lod, bufSize, pixels); }
void glGetnConvolutionFilterARB(GLenum target, GLenum format, GLenum type, GLsizei bufSize, void* image) { functions()->glGetnConvolutionFilterARB(target, format, type, bufSize, image); }
void glGetnConvolutionFilter(GLenum target, GLenum format, GLenum type, GLsizei bufSize, void* image) { functions()->glGetnConvolutionFilter(target, format, type, bufSize, image); }
void glGetNextPerfQueryIdINTEL(GLuint queryId, GLuint* nextQueryId) { functions()->glGetNextPerfQueryIdINTEL(queryId, nextQueryId); }
void glGetnHistogramARB(GLenum target, GLboolean reset, GLenum format, GLenum type, GLsizei bufSize, void* values) { functions()->glGetnHistogramARB(target, reset, format, type, bufSize, values); }
void glGetnHistogram(GLenum target, GLboolean reset, GLenum format, GLenum type, GLsizei bufSize, void* values) { functions()->glGetnHistogram(target, reset, format, type, bufSize, values); }
void glGetnMapdvARB(GLenum target, GLenum query, GLsizei bufSize, GLdouble* v) { functions()->glGetnMapdvARB(target, query, bufSize, v); }
void glGetnMapdv(GLenum target, GLenum query, GLsizei bufSize, GLdouble* v) { functions()->glGetnMapdv(target, query, bufSize, v); }
void glGetnMapfvARB(GLenum target, GLenum query, GLsizei bufSize, GLfloat* v) { functions()->glGetnMapfvARB(target, query, bufSize, v); }
void glGetnMapfv(GLenum target, GLenum query, GLsizei bufSize, GLfloat* v) { functions()->glGetnMapfv(target, query, bufSize, v); }
void glGetnMapivARB(GLenum target, GLenum query, GLsizei bufSize, GLint* v) { functions()->glGetnMapivARB(target, query, bufSize, v); }
void glGetnMapiv(GLenum target, GLenum query, GLsizei bufSize, GLint* v) { functions()->glGetnMapiv(target, query, bufSize, v); }
void glGetnMinmaxARB(GLenum target, GLboolean reset, GLenum format, GLenum type, GLsizei bufSize, void* values) { functions()->glGetnMinmaxARB(target, reset, format, type, bufSize, values); }
void glGetnMinmax(GLenum target, GLboolean reset, GLenum format, GLenum type, GLsizei bufSize, void* values) { functions()->glGetnMinmax(target, reset, format, type, bufSize, values); }
void glGetnPixelMapfvARB(GLenum map, GLsizei bufSize, GLfloat* values) { functions()->glGetnPixelMapfvARB(map, bufSize, values); }
void glGetnPixelMapfv(GLenum map, GLsizei bufSize, GLfloat* values) { functions()->glGetnPixelMapfv(map, bufSize, values); }
void glGetnPixelMapuivARB(GLenum map, GLsizei bufSize, GLuint* values) { functions()->glGetnPixelMapuivARB(map, bufSize, values); }
void glGetnPixelMapuiv(GLenum map, GLsizei bufSize, GLuint* values) { functions()->glGetnPixelMapuiv(map, bufSize, values); }
void glGetnPixelMapusvARB(GLenum map, GLsizei bufSize, GLushort* values) { functions()->glGetnPixelMapusvARB(map, bufSize, values); }
void glGetnPixelMapusv(GLenum map, GLsizei bufSize, GLushort* values) { functions()->glGetnPixelMapusv(map, bufSize, values); }
void glGetnPolygonStippleARB(GLsizei bufSize, GLubyte* pattern) { functions()->glGetnPolygonStippleARB(bufSize, pattern); }
void glGetnPolygonStipple(GLsizei bufSize, GLubyte* pattern) { functions()->glGetnPolygonStipple(bufSize, pattern); }
void glGetnSeparableFilterARB(GLenum target, GLenum format, GLenum type, GLsizei rowBufSize, void* row, GLsizei columnBufSize, void* column, void* span) { functions()->glGetnSeparableFilterARB(target, format, type, rowBufSize, row, columnBufSize, column, span); }
void glGetnSeparableFilter(GLenum target, GLenum format, GLenum type, GLsizei rowBufSize, void* row, GLsizei columnBufSize, void* column, void* span) { functions()->glGetnSeparableFilter(target, format, type, rowBufSize, row, columnBufSize, column, span); }
void glGetnTexImageARB(GLenum target, GLint level, GLenum format, GLenum type, GLsizei bufSize, void* img) { functions()->glGetnTexImageARB(target, level, format, type, bufSize, img); }
void glGetnTexImage(GLenum target, GLint level, GLenum format, GLenum type, GLsizei bufSize, void* pixels) { functions()->glGetnTexImage(target, level, format, type, bufSize, pixels); }
void glGetnUniformdvARB(GLuint program, GLint location, GLsizei bufSize, GLdouble* params) { functions()->glGetnUniformdvARB(program, location, bufSize, params); }
void glGetnUniformdv(GLuint program, GLint location, GLsizei bufSize, GLdouble* params) { functions()->glGetnUniformdv(program, location, bufSize, params); }
void glGetnUniformfvARB(GLuint program, GLint location, GLsizei bufSize, GLfloat* params) { functions()->glGetnUniformfvARB(program, location, bufSize, params); }
void glGetnUniformfv(GLuint program, GLint location, GLsizei bufSize, GLfloat* params) { functions()->glGetnUniformfv(program, location, bufSize, params); }
void glGetnUniformi64vARB(GLuint program, GLint location, GLsizei bufSize, GLint64* params) { functions()->glGetnUniformi64vARB(program, location, bufSize, params); }
void glGetnUniformivARB(GLuint program, GLint location, GLsizei bufSize, GLint* params) { functions()->glGetnUniformivARB(program, location, bufSize, params); }
void glGetnUniformiv(GLuint program, GLint location, GLsizei bufSize, GLint* params) { functions()->glGetnUniformiv(program, location, bufSize, params); }
void glGetnUniformui64vARB(GLuint program, GLint location, GLsizei bufSize, GLuint64* params) { functions()->glGetnUniformui64vARB(program, location, bufSize, params); }
void glGetnUniformuivARB(GLuint program, GLint location, GLsizei bufSize, GLuint* params) { functions()->glGetnUniformuivARB(program, location, bufSize, params); }
void glGetnUniformuiv(GLuint program, GLint location, GLsizei bufSize, GLuint* params) { functions()->glGetnUniformuiv(program, location, bufSize, params); }
void glGetObjectBufferfvATI(GLuint buffer, GLenum pname, GLfloat* params) { functions()->glGetObjectBufferfvATI(buffer, pname, params); }
void glGetObjectBufferivATI(GLuint buffer, GLenum pname, GLint* params) { functions()->glGetObjectBufferivATI(buffer, pname, params); }
void glGetObjectLabelEXT(GLenum type, GLuint object, GLsizei bufSize, GLsizei* length, GLchar* label) { functions()->glGetObjectLabelEXT(type, object, bufSize, length, label); }
void glGetObjectLabel(GLenum identifier, GLuint name, GLsizei bufSize, GLsizei* length, GLchar* label) { functions()->glGetObjectLabel(identifier, name, bufSize, length, label); }
void glGetObjectParameterfvARB(GLhandleARB obj, GLenum pname, GLfloat* params) { functions()->glGetObjectParameterfvARB(obj, pname, params); }
void glGetObjectParameterivAPPLE(GLenum objectType, GLuint name, GLenum pname, GLint* params) { functions()->glGetObjectParameterivAPPLE(objectType, name, pname, params); }
void glGetObjectParameterivARB(GLhandleARB obj, GLenum pname, GLint* params) { functions()->glGetObjectParameterivARB(obj, pname, params); }
void glGetObjectPtrLabel(const void* ptr, GLsizei bufSize, GLsizei* length, GLchar* label) { functions()->glGetObjectPtrLabel(ptr, bufSize, length, label); }
void glGetOcclusionQueryivNV(GLuint id, GLenum pname, GLint* params) { functions()->glGetOcclusionQueryivNV(id, pname, params); }
void glGetOcclusionQueryuivNV(GLuint id, GLenum pname, GLuint* params) { functions()->glGetOcclusionQueryuivNV(id, pname, params); }
void glGetPathColorGenfvNV(GLenum color, GLenum pname, GLfloat* value) { functions()->glGetPathColorGenfvNV(color, pname, value); }
void glGetPathColorGenivNV(GLenum color, GLenum pname, GLint* value) { functions()->glGetPathColorGenivNV(color, pname, value); }
void glGetPathCommandsNV(GLuint path, GLubyte* commands) { functions()->glGetPathCommandsNV(path, commands); }
void glGetPathCoordsNV(GLuint path, GLfloat* coords) { functions()->glGetPathCoordsNV(path, coords); }
void glGetPathDashArrayNV(GLuint path, GLfloat* dashArray) { functions()->glGetPathDashArrayNV(path, dashArray); }
void glGetPathMetricRangeNV(GLbitfield metricQueryMask, GLuint firstPathName, GLsizei numPaths, GLsizei stride, GLfloat* metrics) { functions()->glGetPathMetricRangeNV(metricQueryMask, firstPathName, numPaths, stride, metrics); }
void glGetPathMetricsNV(GLbitfield metricQueryMask, GLsizei numPaths, GLenum pathNameType, const void* paths, GLuint pathBase, GLsizei stride, GLfloat* metrics) { functions()->glGetPathMetricsNV(metricQueryMask, numPaths, pathNameType, paths, pathBase, stride, metrics); }
void glGetPathParameterfvNV(GLuint path, GLenum pname, GLfloat* value) { functions()->glGetPathParameterfvNV(path, pname, value); }
void glGetPathParameterivNV(GLuint path, GLenum pname, GLint* value) { functions()->glGetPathParameterivNV(path, pname, value); }
void glGetPathSpacingNV(GLenum pathListMode, GLsizei numPaths, GLenum pathNameType, const void* paths, GLuint pathBase, GLfloat advanceScale, GLfloat kerningScale, GLenum transformType, GLfloat* returnedSpacing) { functions()->glGetPathSpacingNV(pathListMode, numPaths, pathNameType, paths, pathBase, advanceScale, kerningScale, transformType, returnedSpacing); }
void glGetPathTexGenfvNV(GLenum texCoordSet, GLenum pname, GLfloat* value) { functions()->glGetPathTexGenfvNV(texCoordSet, pname, value); }
void glGetPathTexGenivNV(GLenum texCoordSet, GLenum pname, GLint* value) { functions()->glGetPathTexGenivNV(texCoordSet, pname, value); }
void glGetPerfCounterInfoINTEL(GLuint queryId, GLuint counterId, GLuint counterNameLength, GLchar* counterName, GLuint counterDescLength, GLchar* counterDesc, GLuint* counterOffset, GLuint* counterDataSize, GLuint* counterTypeEnum, GLuint* counterDataTypeEnum, GLuint64* rawCounterMaxValue) { functions()->glGetPerfCounterInfoINTEL(queryId, counterId, counterNameLength, counterName, counterDescLength, counterDesc, counterOffset, counterDataSize, counterTypeEnum, counterDataTypeEnum, rawCounterMaxValue); }
void glGetPerfMonitorCounterDataAMD(GLuint monitor, GLenum pname, GLsizei dataSize, GLuint* data, GLint* bytesWritten) { functions()->glGetPerfMonitorCounterDataAMD(monitor, pname, dataSize, data, bytesWritten); }
void glGetPerfMonitorCounterInfoAMD(GLuint group, GLuint counter, GLenum pname, void* data) { functions()->glGetPerfMonitorCounterInfoAMD(group, counter, pname, data); }
void glGetPerfMonitorCountersAMD(GLuint group, GLint* numCounters, GLint* maxActiveCounters, GLsizei counterSize, GLuint* counters) { functions()->glGetPerfMonitorCountersAMD(group, numCounters, maxActiveCounters, counterSize, counters); }
void glGetPerfMonitorCounterStringAMD(GLuint group, GLuint counter, GLsizei bufSize, GLsizei* length, GLchar* counterString) { functions()->glGetPerfMonitorCounterStringAMD(group, counter, bufSize, length, counterString); }
void glGetPerfMonitorGroupsAMD(GLint* numGroups, GLsizei groupsSize, GLuint* groups) { functions()->glGetPerfMonitorGroupsAMD(numGroups, groupsSize, groups); }
void glGetPerfMonitorGroupStringAMD(GLuint group, GLsizei bufSize, GLsizei* length, GLchar* groupString) { functions()->glGetPerfMonitorGroupStringAMD(group, bufSize, length, groupString); }
void glGetPerfQueryDataINTEL(GLuint queryHandle, GLuint flags, GLsizei dataSize, GLvoid* data, GLuint* bytesWritten) { functions()->glGetPerfQueryDataINTEL(queryHandle, flags, dataSize, data, bytesWritten); }
void glGetPerfQueryIdByNameINTEL(GLchar* queryName, GLuint* queryId) { functions()->glGetPerfQueryIdByNameINTEL(queryName, queryId); }
void glGetPerfQueryInfoINTEL(GLuint queryId, GLuint queryNameLength, GLchar* queryName, GLuint* dataSize, GLuint* noCounters, GLuint* noInstances, GLuint* capsMask) { functions()->glGetPerfQueryInfoINTEL(queryId, queryNameLength, queryName, dataSize, noCounters, noInstances, capsMask); }
void glGetPixelMapfv(GLenum map, GLfloat* values) { functions()->glGetPixelMapfv(map, values); }
void glGetPixelMapuiv(GLenum map, GLuint* values) { functions()->glGetPixelMapuiv(map, values); }
void glGetPixelMapusv(GLenum map, GLushort* values) { functions()->glGetPixelMapusv(map, values); }
void glGetPixelMapxv(GLenum map, GLint size, GLfixed* values) { functions()->glGetPixelMapxv(map, size, values); }
void glGetPixelTexGenParameterfvSGIS(GLenum pname, GLfloat* params) { functions()->glGetPixelTexGenParameterfvSGIS(pname, params); }
void glGetPixelTexGenParameterivSGIS(GLenum pname, GLint* params) { functions()->glGetPixelTexGenParameterivSGIS(pname, params); }
void glGetPixelTransformParameterfvEXT(GLenum target, GLenum pname, GLfloat* params) { functions()->glGetPixelTransformParameterfvEXT(target, pname, params); }
void glGetPixelTransformParameterivEXT(GLenum target, GLenum pname, GLint* params) { functions()->glGetPixelTransformParameterivEXT(target, pname, params); }
void glGetPointerIndexedvEXT(GLenum target, GLuint index, void** data) { functions()->glGetPointerIndexedvEXT(target, index, data); }
void glGetPointeri_vEXT(GLenum pname, GLuint index, void** params) { functions()->glGetPointeri_vEXT(pname, index, params); }
void glGetPointervEXT(GLenum pname, void** params) { functions()->glGetPointervEXT(pname, params); }
void glGetPointerv(GLenum pname, GLvoid** params) { functions()->glGetPointerv(pname, params); }
void glGetPolygonStipple(GLubyte* mask) { functions()->glGetPolygonStipple(mask); }
void glGetProgramBinary(GLuint program, GLsizei bufSize, GLsizei* length, GLenum* binaryFormat, void* binary) { functions()->glGetProgramBinary(program, bufSize, length, binaryFormat, binary); }
void glGetProgramEnvParameterdvARB(GLenum target, GLuint index, GLdouble* params) { functions()->glGetProgramEnvParameterdvARB(target, index, params); }
void glGetProgramEnvParameterfvARB(GLenum target, GLuint index, GLfloat* params) { functions()->glGetProgramEnvParameterfvARB(target, index, params); }
void glGetProgramEnvParameterIivNV(GLenum target, GLuint index, GLint* params) { functions()->glGetProgramEnvParameterIivNV(target, index, params); }
void glGetProgramEnvParameterIuivNV(GLenum target, GLuint index, GLuint* params) { functions()->glGetProgramEnvParameterIuivNV(target, index, params); }
void glGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog) { functions()->glGetProgramInfoLog(program, bufSize, length, infoLog); }
void glGetProgramInterfaceiv(GLuint program, GLenum programInterface, GLenum pname, GLint* params) { functions()->glGetProgramInterfaceiv(program, programInterface, pname, params); }
void glGetProgramivARB(GLenum target, GLenum pname, GLint* params) { functions()->glGetProgramivARB(target, pname, params); }
void glGetProgramiv(GLuint program, GLenum pname, GLint* params) { functions()->glGetProgramiv(program, pname, params); }
void glGetProgramivNV(GLuint id, GLenum pname, GLint* params) { functions()->glGetProgramivNV(id, pname, params); }
void glGetProgramLocalParameterdvARB(GLenum target, GLuint index, GLdouble* params) { functions()->glGetProgramLocalParameterdvARB(target, index, params); }
void glGetProgramLocalParameterfvARB(GLenum target, GLuint index, GLfloat* params) { functions()->glGetProgramLocalParameterfvARB(target, index, params); }
void glGetProgramLocalParameterIivNV(GLenum target, GLuint index, GLint* params) { functions()->glGetProgramLocalParameterIivNV(target, index, params); }
void glGetProgramLocalParameterIuivNV(GLenum target, GLuint index, GLuint* params) { functions()->glGetProgramLocalParameterIuivNV(target, index, params); }
void glGetProgramNamedParameterdvNV(GLuint id, GLsizei len, const GLubyte* name, GLdouble* params) { functions()->glGetProgramNamedParameterdvNV(id, len, name, params); }
void glGetProgramNamedParameterfvNV(GLuint id, GLsizei len, const GLubyte* name, GLfloat* params) { functions()->glGetProgramNamedParameterfvNV(id, len, name, params); }
void glGetProgramParameterdvNV(GLenum target, GLuint index, GLenum pname, GLdouble* params) { functions()->glGetProgramParameterdvNV(target, index, pname, params); }
void glGetProgramParameterfvNV(GLenum target, GLuint index, GLenum pname, GLfloat* params) { functions()->glGetProgramParameterfvNV(target, index, pname, params); }
void glGetProgramPipelineInfoLog(GLuint pipeline, GLsizei bufSize, GLsizei* length, GLchar* infoLog) { functions()->glGetProgramPipelineInfoLog(pipeline, bufSize, length, infoLog); }
void glGetProgramPipelineiv(GLuint pipeline, GLenum pname, GLint* params) { functions()->glGetProgramPipelineiv(pipeline, pname, params); }
void glGetProgramResourcefvNV(GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum* props, GLsizei bufSize, GLsizei* length, GLfloat* params) { functions()->glGetProgramResourcefvNV(program, programInterface, index, propCount, props, bufSize, length, params); }
void glGetProgramResourceiv(GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum* props, GLsizei bufSize, GLsizei* length, GLint* params) { functions()->glGetProgramResourceiv(program, programInterface, index, propCount, props, bufSize, length, params); }
void glGetProgramResourceName(GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei* length, GLchar* name) { functions()->glGetProgramResourceName(program, programInterface, index, bufSize, length, name); }
void glGetProgramStageiv(GLuint program, GLenum shadertype, GLenum pname, GLint* values) { functions()->glGetProgramStageiv(program, shadertype, pname, values); }
void glGetProgramStringARB(GLenum target, GLenum pname, void* string) { functions()->glGetProgramStringARB(target, pname, string); }
void glGetProgramStringNV(GLuint id, GLenum pname, GLubyte* program) { functions()->glGetProgramStringNV(id, pname, program); }
void glGetProgramSubroutineParameteruivNV(GLenum target, GLuint index, GLuint* param) { functions()->glGetProgramSubroutineParameteruivNV(target, index, param); }
void glGetQueryBufferObjecti64v(GLuint id, GLuint buffer, GLenum pname, GLintptr offset) { functions()->glGetQueryBufferObjecti64v(id, buffer, pname, offset); }
void glGetQueryBufferObjectiv(GLuint id, GLuint buffer, GLenum pname, GLintptr offset) { functions()->glGetQueryBufferObjectiv(id, buffer, pname, offset); }
void glGetQueryBufferObjectui64v(GLuint id, GLuint buffer, GLenum pname, GLintptr offset) { functions()->glGetQueryBufferObjectui64v(id, buffer, pname, offset); }
void glGetQueryBufferObjectuiv(GLuint id, GLuint buffer, GLenum pname, GLintptr offset) { functions()->glGetQueryBufferObjectuiv(id, buffer, pname, offset); }
void glGetQueryIndexediv(GLenum target, GLuint index, GLenum pname, GLint* params) { functions()->glGetQueryIndexediv(target, index, pname, params); }
void glGetQueryivARB(GLenum target, GLenum pname, GLint* params) { functions()->glGetQueryivARB(target, pname, params); }
void glGetQueryiv(GLenum target, GLenum pname, GLint* params) { functions()->glGetQueryiv(target, pname, params); }
void glGetQueryObjecti64vEXT(GLuint id, GLenum pname, GLint64* params) { functions()->glGetQueryObjecti64vEXT(id, pname, params); }
void glGetQueryObjecti64v(GLuint id, GLenum pname, GLint64* params) { functions()->glGetQueryObjecti64v(id, pname, params); }
void glGetQueryObjectivARB(GLuint id, GLenum pname, GLint* params) { functions()->glGetQueryObjectivARB(id, pname, params); }
void glGetQueryObjectiv(GLuint id, GLenum pname, GLint* params) { functions()->glGetQueryObjectiv(id, pname, params); }
void glGetQueryObjectui64vEXT(GLuint id, GLenum pname, GLuint64* params) { functions()->glGetQueryObjectui64vEXT(id, pname, params); }
void glGetQueryObjectui64v(GLuint id, GLenum pname, GLuint64* params) { functions()->glGetQueryObjectui64v(id, pname, params); }
void glGetQueryObjectuivARB(GLuint id, GLenum pname, GLuint* params) { functions()->glGetQueryObjectuivARB(id, pname, params); }
void glGetQueryObjectuiv(GLuint id, GLenum pname, GLuint* params) { functions()->glGetQueryObjectuiv(id, pname, params); }
void glGetRenderbufferParameterivEXT(GLenum target, GLenum pname, GLint* params) { functions()->glGetRenderbufferParameterivEXT(target, pname, params); }
void glGetRenderbufferParameteriv(GLenum target, GLenum pname, GLint* params) { functions()->glGetRenderbufferParameteriv(target, pname, params); }
void glGetSamplerParameterfv(GLuint sampler, GLenum pname, GLfloat* params) { functions()->glGetSamplerParameterfv(sampler, pname, params); }
void glGetSamplerParameterIiv(GLuint sampler, GLenum pname, GLint* params) { functions()->glGetSamplerParameterIiv(sampler, pname, params); }
void glGetSamplerParameterIuiv(GLuint sampler, GLenum pname, GLuint* params) { functions()->glGetSamplerParameterIuiv(sampler, pname, params); }
void glGetSamplerParameteriv(GLuint sampler, GLenum pname, GLint* params) { functions()->glGetSamplerParameteriv(sampler, pname, params); }
void glGetSeparableFilterEXT(GLenum target, GLenum format, GLenum type, void* row, void* column, void* span) { functions()->glGetSeparableFilterEXT(target, format, type, row, column, span); }
void glGetSeparableFilter(GLenum target, GLenum format, GLenum type, GLvoid* row, GLvoid* column, GLvoid* span) { functions()->glGetSeparableFilter(target, format, type, row, column, span); }
void glGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog) { functions()->glGetShaderInfoLog(shader, bufSize, length, infoLog); }
void glGetShaderiv(GLuint shader, GLenum pname, GLint* params) { functions()->glGetShaderiv(shader, pname, params); }
void glGetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint* range, GLint* precision) { functions()->glGetShaderPrecisionFormat(shadertype, precisiontype, range, precision); }
void glGetShaderSourceARB(GLhandleARB obj, GLsizei maxLength, GLsizei* length, GLcharARB* source) { functions()->glGetShaderSourceARB(obj, maxLength, length, source); }
void glGetShaderSource(GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* source) { functions()->glGetShaderSource(shader, bufSize, length, source); }
void glGetSharpenTexFuncSGIS(GLenum target, GLfloat* points) { functions()->glGetSharpenTexFuncSGIS(target, points); }
void glGetSynciv(GLsync sync, GLenum pname, GLsizei bufSize, GLsizei* length, GLint* values) { functions()->glGetSynciv(sync, pname, bufSize, length, values); }
void glGetTexBumpParameterfvATI(GLenum pname, GLfloat* param) { functions()->glGetTexBumpParameterfvATI(pname, param); }
void glGetTexBumpParameterivATI(GLenum pname, GLint* param) { functions()->glGetTexBumpParameterivATI(pname, param); }
void glGetTexEnvfv(GLenum target, GLenum pname, GLfloat* params) { functions()->glGetTexEnvfv(target, pname, params); }
void glGetTexEnviv(GLenum target, GLenum pname, GLint* params) { functions()->glGetTexEnviv(target, pname, params); }
void glGetTexEnvxvOES(GLenum target, GLenum pname, GLfixed* params) { functions()->glGetTexEnvxvOES(target, pname, params); }
void glGetTexFilterFuncSGIS(GLenum target, GLenum filter, GLfloat* weights) { functions()->glGetTexFilterFuncSGIS(target, filter, weights); }
void glGetTexGendv(GLenum coord, GLenum pname, GLdouble* params) { functions()->glGetTexGendv(coord, pname, params); }
void glGetTexGenfv(GLenum coord, GLenum pname, GLfloat* params) { functions()->glGetTexGenfv(coord, pname, params); }
void glGetTexGeniv(GLenum coord, GLenum pname, GLint* params) { functions()->glGetTexGeniv(coord, pname, params); }
void glGetTexGenxvOES(GLenum coord, GLenum pname, GLfixed* params) { functions()->glGetTexGenxvOES(coord, pname, params); }
void glGetTexImage(GLenum target, GLint level, GLenum format, GLenum type, GLvoid* pixels) { functions()->glGetTexImage(target, level, format, type, pixels); }
void glGetTexLevelParameterfv(GLenum target, GLint level, GLenum pname, GLfloat* params) { functions()->glGetTexLevelParameterfv(target, level, pname, params); }
void glGetTexLevelParameteriv(GLenum target, GLint level, GLenum pname, GLint* params) { functions()->glGetTexLevelParameteriv(target, level, pname, params); }
void glGetTexLevelParameterxvOES(GLenum target, GLint level, GLenum pname, GLfixed* params) { functions()->glGetTexLevelParameterxvOES(target, level, pname, params); }
void glGetTexParameterfv(GLenum target, GLenum pname, GLfloat* params) { functions()->glGetTexParameterfv(target, pname, params); }
void glGetTexParameterIivEXT(GLenum target, GLenum pname, GLint* params) { functions()->glGetTexParameterIivEXT(target, pname, params); }
void glGetTexParameterIiv(GLenum target, GLenum pname, GLint* params) { functions()->glGetTexParameterIiv(target, pname, params); }
void glGetTexParameterIuivEXT(GLenum target, GLenum pname, GLuint* params) { functions()->glGetTexParameterIuivEXT(target, pname, params); }
void glGetTexParameterIuiv(GLenum target, GLenum pname, GLuint* params) { functions()->glGetTexParameterIuiv(target, pname, params); }
void glGetTexParameteriv(GLenum target, GLenum pname, GLint* params) { functions()->glGetTexParameteriv(target, pname, params); }
void glGetTexParameterPointervAPPLE(GLenum target, GLenum pname, void** params) { functions()->glGetTexParameterPointervAPPLE(target, pname, params); }
void glGetTexParameterxvOES(GLenum target, GLenum pname, GLfixed* params) { functions()->glGetTexParameterxvOES(target, pname, params); }
void glGetTextureImageEXT(GLuint texture, GLenum target, GLint level, GLenum format, GLenum type, void* pixels) { functions()->glGetTextureImageEXT(texture, target, level, format, type, pixels); }
void glGetTextureImage(GLuint texture, GLint level, GLenum format, GLenum type, GLsizei bufSize, void* pixels) { functions()->glGetTextureImage(texture, level, format, type, bufSize, pixels); }
void glGetTextureLevelParameterfvEXT(GLuint texture, GLenum target, GLint level, GLenum pname, GLfloat* params) { functions()->glGetTextureLevelParameterfvEXT(texture, target, level, pname, params); }
void glGetTextureLevelParameterfv(GLuint texture, GLint level, GLenum pname, GLfloat* params) { functions()->glGetTextureLevelParameterfv(texture, level, pname, params); }
void glGetTextureLevelParameterivEXT(GLuint texture, GLenum target, GLint level, GLenum pname, GLint* params) { functions()->glGetTextureLevelParameterivEXT(texture, target, level, pname, params); }
void glGetTextureLevelParameteriv(GLuint texture, GLint level, GLenum pname, GLint* params) { functions()->glGetTextureLevelParameteriv(texture, level, pname, params); }
void glGetTextureParameterfvEXT(GLuint texture, GLenum target, GLenum pname, GLfloat* params) { functions()->glGetTextureParameterfvEXT(texture, target, pname, params); }
void glGetTextureParameterfv(GLuint texture, GLenum pname, GLfloat* params) { functions()->glGetTextureParameterfv(texture, pname, params); }
void glGetTextureParameterIivEXT(GLuint texture, GLenum target, GLenum pname, GLint* params) { functions()->glGetTextureParameterIivEXT(texture, target, pname, params); }
void glGetTextureParameterIiv(GLuint texture, GLenum pname, GLint* params) { functions()->glGetTextureParameterIiv(texture, pname, params); }
void glGetTextureParameterIuivEXT(GLuint texture, GLenum target, GLenum pname, GLuint* params) { functions()->glGetTextureParameterIuivEXT(texture, target, pname, params); }
void glGetTextureParameterIuiv(GLuint texture, GLenum pname, GLuint* params) { functions()->glGetTextureParameterIuiv(texture, pname, params); }
void glGetTextureParameterivEXT(GLuint texture, GLenum target, GLenum pname, GLint* params) { functions()->glGetTextureParameterivEXT(texture, target, pname, params); }
void glGetTextureParameteriv(GLuint texture, GLenum pname, GLint* params) { functions()->glGetTextureParameteriv(texture, pname, params); }
void glGetTextureSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLsizei bufSize, void* pixels) { functions()->glGetTextureSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, bufSize, pixels); }
void glGetTrackMatrixivNV(GLenum target, GLuint address, GLenum pname, GLint* params) { functions()->glGetTrackMatrixivNV(target, address, pname, params); }
void glGetTransformFeedbacki64_v(GLuint xfb, GLenum pname, GLuint index, GLint64* param) { functions()->glGetTransformFeedbacki64_v(xfb, pname, index, param); }
void glGetTransformFeedbackiv(GLuint xfb, GLenum pname, GLint* param) { functions()->glGetTransformFeedbackiv(xfb, pname, param); }
void glGetTransformFeedbacki_v(GLuint xfb, GLenum pname, GLuint index, GLint* param) { functions()->glGetTransformFeedbacki_v(xfb, pname, index, param); }
void glGetTransformFeedbackVaryingEXT(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLsizei* size, GLenum* type, GLchar* name) { functions()->glGetTransformFeedbackVaryingEXT(program, index, bufSize, length, size, type, name); }
void glGetTransformFeedbackVarying(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLsizei* size, GLenum* type, GLchar* name) { functions()->glGetTransformFeedbackVarying(program, index, bufSize, length, size, type, name); }
void glGetTransformFeedbackVaryingNV(GLuint program, GLuint index, GLint* location) { functions()->glGetTransformFeedbackVaryingNV(program, index, location); }
void glGetUniformdv(GLuint program, GLint location, GLdouble* params) { functions()->glGetUniformdv(program, location, params); }
void glGetUniformfvARB(GLhandleARB programObj, GLint location, GLfloat* params) { functions()->glGetUniformfvARB(programObj, location, params); }
void glGetUniformfv(GLuint program, GLint location, GLfloat* params) { functions()->glGetUniformfv(program, location, params); }
void glGetUniformi64vARB(GLuint program, GLint location, GLint64* params) { functions()->glGetUniformi64vARB(program, location, params); }
void glGetUniformi64vNV(GLuint program, GLint location, GLint64EXT* params) { functions()->glGetUniformi64vNV(program, location, params); }
void glGetUniformIndices(GLuint program, GLsizei uniformCount, const GLchar*const* uniformNames, GLuint* uniformIndices) { functions()->glGetUniformIndices(program, uniformCount, uniformNames, uniformIndices); }
void glGetUniformivARB(GLhandleARB programObj, GLint location, GLint* params) { functions()->glGetUniformivARB(programObj, location, params); }
void glGetUniformiv(GLuint program, GLint location, GLint* params) { functions()->glGetUniformiv(program, location, params); }
void glGetUniformSubroutineuiv(GLenum shadertype, GLint location, GLuint* params) { functions()->glGetUniformSubroutineuiv(shadertype, location, params); }
void glGetUniformui64vARB(GLuint program, GLint location, GLuint64* params) { functions()->glGetUniformui64vARB(program, location, params); }
void glGetUniformui64vNV(GLuint program, GLint location, GLuint64EXT* params) { functions()->glGetUniformui64vNV(program, location, params); }
void glGetUniformuivEXT(GLuint program, GLint location, GLuint* params) { functions()->glGetUniformuivEXT(program, location, params); }
void glGetUniformuiv(GLuint program, GLint location, GLuint* params) { functions()->glGetUniformuiv(program, location, params); }
void glGetVariantArrayObjectfvATI(GLuint id, GLenum pname, GLfloat* params) { functions()->glGetVariantArrayObjectfvATI(id, pname, params); }
void glGetVariantArrayObjectivATI(GLuint id, GLenum pname, GLint* params) { functions()->glGetVariantArrayObjectivATI(id, pname, params); }
void glGetVariantBooleanvEXT(GLuint id, GLenum value, GLboolean* data) { functions()->glGetVariantBooleanvEXT(id, value, data); }
void glGetVariantFloatvEXT(GLuint id, GLenum value, GLfloat* data) { functions()->glGetVariantFloatvEXT(id, value, data); }
void glGetVariantIntegervEXT(GLuint id, GLenum value, GLint* data) { functions()->glGetVariantIntegervEXT(id, value, data); }
void glGetVariantPointervEXT(GLuint id, GLenum value, void** data) { functions()->glGetVariantPointervEXT(id, value, data); }
void glGetVertexArrayIndexed64iv(GLuint vaobj, GLuint index, GLenum pname, GLint64* param) { functions()->glGetVertexArrayIndexed64iv(vaobj, index, pname, param); }
void glGetVertexArrayIndexediv(GLuint vaobj, GLuint index, GLenum pname, GLint* param) { functions()->glGetVertexArrayIndexediv(vaobj, index, pname, param); }
void glGetVertexArrayIntegeri_vEXT(GLuint vaobj, GLuint index, GLenum pname, GLint* param) { functions()->glGetVertexArrayIntegeri_vEXT(vaobj, index, pname, param); }
void glGetVertexArrayIntegervEXT(GLuint vaobj, GLenum pname, GLint* param) { functions()->glGetVertexArrayIntegervEXT(vaobj, pname, param); }
void glGetVertexArrayiv(GLuint vaobj, GLenum pname, GLint* param) { functions()->glGetVertexArrayiv(vaobj, pname, param); }
void glGetVertexArrayPointeri_vEXT(GLuint vaobj, GLuint index, GLenum pname, void** param) { functions()->glGetVertexArrayPointeri_vEXT(vaobj, index, pname, param); }
void glGetVertexArrayPointervEXT(GLuint vaobj, GLenum pname, void** param) { functions()->glGetVertexArrayPointervEXT(vaobj, pname, param); }
void glGetVertexAttribArrayObjectfvATI(GLuint index, GLenum pname, GLfloat* params) { functions()->glGetVertexAttribArrayObjectfvATI(index, pname, params); }
void glGetVertexAttribArrayObjectivATI(GLuint index, GLenum pname, GLint* params) { functions()->glGetVertexAttribArrayObjectivATI(index, pname, params); }
void glGetVertexAttribdvARB(GLuint index, GLenum pname, GLdouble* params) { functions()->glGetVertexAttribdvARB(index, pname, params); }
void glGetVertexAttribdv(GLuint index, GLenum pname, GLdouble* params) { functions()->glGetVertexAttribdv(index, pname, params); }
void glGetVertexAttribdvNV(GLuint index, GLenum pname, GLdouble* params) { functions()->glGetVertexAttribdvNV(index, pname, params); }
void glGetVertexAttribfvARB(GLuint index, GLenum pname, GLfloat* params) { functions()->glGetVertexAttribfvARB(index, pname, params); }
void glGetVertexAttribfv(GLuint index, GLenum pname, GLfloat* params) { functions()->glGetVertexAttribfv(index, pname, params); }
void glGetVertexAttribfvNV(GLuint index, GLenum pname, GLfloat* params) { functions()->glGetVertexAttribfvNV(index, pname, params); }
void glGetVertexAttribIivEXT(GLuint index, GLenum pname, GLint* params) { functions()->glGetVertexAttribIivEXT(index, pname, params); }
void glGetVertexAttribIiv(GLuint index, GLenum pname, GLint* params) { functions()->glGetVertexAttribIiv(index, pname, params); }
void glGetVertexAttribIuivEXT(GLuint index, GLenum pname, GLuint* params) { functions()->glGetVertexAttribIuivEXT(index, pname, params); }
void glGetVertexAttribIuiv(GLuint index, GLenum pname, GLuint* params) { functions()->glGetVertexAttribIuiv(index, pname, params); }
void glGetVertexAttribivARB(GLuint index, GLenum pname, GLint* params) { functions()->glGetVertexAttribivARB(index, pname, params); }
void glGetVertexAttribiv(GLuint index, GLenum pname, GLint* params) { functions()->glGetVertexAttribiv(index, pname, params); }
void glGetVertexAttribivNV(GLuint index, GLenum pname, GLint* params) { functions()->glGetVertexAttribivNV(index, pname, params); }
void glGetVertexAttribLdvEXT(GLuint index, GLenum pname, GLdouble* params) { functions()->glGetVertexAttribLdvEXT(index, pname, params); }
void glGetVertexAttribLdv(GLuint index, GLenum pname, GLdouble* params) { functions()->glGetVertexAttribLdv(index, pname, params); }
void glGetVertexAttribLi64vNV(GLuint index, GLenum pname, GLint64EXT* params) { functions()->glGetVertexAttribLi64vNV(index, pname, params); }
void glGetVertexAttribLui64vARB(GLuint index, GLenum pname, GLuint64EXT* params) { functions()->glGetVertexAttribLui64vARB(index, pname, params); }
void glGetVertexAttribLui64vNV(GLuint index, GLenum pname, GLuint64EXT* params) { functions()->glGetVertexAttribLui64vNV(index, pname, params); }
void glGetVertexAttribPointervARB(GLuint index, GLenum pname, void** pointer) { functions()->glGetVertexAttribPointervARB(index, pname, pointer); }
void glGetVertexAttribPointerv(GLuint index, GLenum pname, void** pointer) { functions()->glGetVertexAttribPointerv(index, pname, pointer); }
void glGetVertexAttribPointervNV(GLuint index, GLenum pname, void** pointer) { functions()->glGetVertexAttribPointervNV(index, pname, pointer); }
void glGetVideoCaptureivNV(GLuint video_capture_slot, GLenum pname, GLint* params) { functions()->glGetVideoCaptureivNV(video_capture_slot, pname, params); }
void glGetVideoCaptureStreamdvNV(GLuint video_capture_slot, GLuint stream, GLenum pname, GLdouble* params) { functions()->glGetVideoCaptureStreamdvNV(video_capture_slot, stream, pname, params); }
void glGetVideoCaptureStreamfvNV(GLuint video_capture_slot, GLuint stream, GLenum pname, GLfloat* params) { functions()->glGetVideoCaptureStreamfvNV(video_capture_slot, stream, pname, params); }
void glGetVideoCaptureStreamivNV(GLuint video_capture_slot, GLuint stream, GLenum pname, GLint* params) { functions()->glGetVideoCaptureStreamivNV(video_capture_slot, stream, pname, params); }
void glGetVideoi64vNV(GLuint video_slot, GLenum pname, GLint64EXT* params) { functions()->glGetVideoi64vNV(video_slot, pname, params); }
void glGetVideoivNV(GLuint video_slot, GLenum pname, GLint* params) { functions()->glGetVideoivNV(video_slot, pname, params); }
void glGetVideoui64vNV(GLuint video_slot, GLenum pname, GLuint64EXT* params) { functions()->glGetVideoui64vNV(video_slot, pname, params); }
void glGetVideouivNV(GLuint video_slot, GLenum pname, GLuint* params) { functions()->glGetVideouivNV(video_slot, pname, params); }
void glGlobalAlphaFactorbSUN(GLbyte factor) { functions()->glGlobalAlphaFactorbSUN(factor); }
void glGlobalAlphaFactordSUN(GLdouble factor) { functions()->glGlobalAlphaFactordSUN(factor); }
void glGlobalAlphaFactorfSUN(GLfloat factor) { functions()->glGlobalAlphaFactorfSUN(factor); }
void glGlobalAlphaFactoriSUN(GLint factor) { functions()->glGlobalAlphaFactoriSUN(factor); }
void glGlobalAlphaFactorsSUN(GLshort factor) { functions()->glGlobalAlphaFactorsSUN(factor); }
void glGlobalAlphaFactorubSUN(GLubyte factor) { functions()->glGlobalAlphaFactorubSUN(factor); }
void glGlobalAlphaFactoruiSUN(GLuint factor) { functions()->glGlobalAlphaFactoruiSUN(factor); }
void glGlobalAlphaFactorusSUN(GLushort factor) { functions()->glGlobalAlphaFactorusSUN(factor); }
void glHint(GLenum target, GLenum mode) { functions()->glHint(target, mode); }
void glHintPGI(GLenum target, GLint mode) { functions()->glHintPGI(target, mode); }
void glHistogramEXT(GLenum target, GLsizei width, GLenum internalformat, GLboolean sink) { functions()->glHistogramEXT(target, width, internalformat, sink); }
void glHistogram(GLenum target, GLsizei width, GLenum internalformat, GLboolean sink) { functions()->glHistogram(target, width, internalformat, sink); }
void glIglooInterfaceSGIX(GLenum pname, const void* params) { functions()->glIglooInterfaceSGIX(pname, params); }
void glImageTransformParameterfHP(GLenum target, GLenum pname, GLfloat param) { functions()->glImageTransformParameterfHP(target, pname, param); }
void glImageTransformParameterfvHP(GLenum target, GLenum pname, const GLfloat* params) { functions()->glImageTransformParameterfvHP(target, pname, params); }
void glImageTransformParameteriHP(GLenum target, GLenum pname, GLint param) { functions()->glImageTransformParameteriHP(target, pname, param); }
void glImageTransformParameterivHP(GLenum target, GLenum pname, const GLint* params) { functions()->glImageTransformParameterivHP(target, pname, params); }
void glIndexd(GLdouble c) { functions()->glIndexd(c); }
void glIndexdv(const GLdouble* c) { functions()->glIndexdv(c); }
void glIndexf(GLfloat c) { functions()->glIndexf(c); }
void glIndexFormatNV(GLenum type, GLsizei stride) { functions()->glIndexFormatNV(type, stride); }
void glIndexFuncEXT(GLenum func, GLclampf ref) { functions()->glIndexFuncEXT(func, ref); }
void glIndexfv(const GLfloat* c) { functions()->glIndexfv(c); }
void glIndexi(GLint c) { functions()->glIndexi(c); }
void glIndexiv(const GLint* c) { functions()->glIndexiv(c); }
void glIndexMask(GLuint mask) { functions()->glIndexMask(mask); }
void glIndexMaterialEXT(GLenum face, GLenum mode) { functions()->glIndexMaterialEXT(face, mode); }
void glIndexPointerEXT(GLenum type, GLsizei stride, GLsizei count, const void* pointer) { functions()->glIndexPointerEXT(type, stride, count, pointer); }
void glIndexPointer(GLenum type, GLsizei stride, const GLvoid* ptr) { functions()->glIndexPointer(type, stride, ptr); }
void glIndexPointerListIBM(GLenum type, GLint stride, const void** pointer, GLint ptrstride) { functions()->glIndexPointerListIBM(type, stride, pointer, ptrstride); }
void glIndexs(GLshort c) { functions()->glIndexs(c); }
void glIndexsv(const GLshort* c) { functions()->glIndexsv(c); }
void glIndexub(GLubyte c) { functions()->glIndexub(c); }
void glIndexubv(const GLubyte* c) { functions()->glIndexubv(c); }
void glIndexxOES(GLfixed component) { functions()->glIndexxOES(component); }
void glIndexxvOES(const GLfixed* component) { functions()->glIndexxvOES(component); }
void glInitNames() { functions()->glInitNames(); }
void glInsertComponentEXT(GLuint res, GLuint src, GLuint num) { functions()->glInsertComponentEXT(res, src, num); }
void glInsertEventMarkerEXT(GLsizei length, const GLchar* marker) { functions()->glInsertEventMarkerEXT(length, marker); }
void glInstrumentsBufferSGIX(GLsizei size, GLint* buffer) { functions()->glInstrumentsBufferSGIX(size, buffer); }
void glInterleavedArrays(GLenum format, GLsizei stride, const GLvoid* pointer) { functions()->glInterleavedArrays(format, stride, pointer); }
void glInterpolatePathsNV(GLuint resultPath, GLuint pathA, GLuint pathB, GLfloat weight) { functions()->glInterpolatePathsNV(resultPath, pathA, pathB, weight); }
void glInvalidateBufferData(GLuint buffer) { functions()->glInvalidateBufferData(buffer); }
void glInvalidateBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr length) { functions()->glInvalidateBufferSubData(buffer, offset, length); }
void glInvalidateFramebuffer(GLenum target, GLsizei numAttachments, const GLenum* attachments) { functions()->glInvalidateFramebuffer(target, numAttachments, attachments); }
void glInvalidateNamedFramebufferData(GLuint framebuffer, GLsizei numAttachments, const GLenum* attachments) { functions()->glInvalidateNamedFramebufferData(framebuffer, numAttachments, attachments); }
void glInvalidateNamedFramebufferSubData(GLuint framebuffer, GLsizei numAttachments, const GLenum* attachments, GLint x, GLint y, GLsizei width, GLsizei height) { functions()->glInvalidateNamedFramebufferSubData(framebuffer, numAttachments, attachments, x, y, width, height); }
void glInvalidateSubFramebuffer(GLenum target, GLsizei numAttachments, const GLenum* attachments, GLint x, GLint y, GLsizei width, GLsizei height) { functions()->glInvalidateSubFramebuffer(target, numAttachments, attachments, x, y, width, height); }
void glInvalidateTexImage(GLuint texture, GLint level) { functions()->glInvalidateTexImage(texture, level); }
void glInvalidateTexSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth) { functions()->glInvalidateTexSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth); }
void glLabelObjectEXT(GLenum type, GLuint object, GLsizei length, const GLchar* label) { functions()->glLabelObjectEXT(type, object, length, label); }
void glLightEnviSGIX(GLenum pname, GLint param) { functions()->glLightEnviSGIX(pname, param); }
void glLightf(GLenum light, GLenum pname, GLfloat param) { functions()->glLightf(light, pname, param); }
void glLightfv(GLenum light, GLenum pname, const GLfloat* params) { functions()->glLightfv(light, pname, params); }
void glLighti(GLenum light, GLenum pname, GLint param) { functions()->glLighti(light, pname, param); }
void glLightiv(GLenum light, GLenum pname, const GLint* params) { functions()->glLightiv(light, pname, params); }
void glLightModelf(GLenum pname, GLfloat param) { functions()->glLightModelf(pname, param); }
void glLightModelfv(GLenum pname, const GLfloat* params) { functions()->glLightModelfv(pname, params); }
void glLightModeli(GLenum pname, GLint param) { functions()->glLightModeli(pname, param); }
void glLightModeliv(GLenum pname, const GLint* params) { functions()->glLightModeliv(pname, params); }
void glLightModelxOES(GLenum pname, GLfixed param) { functions()->glLightModelxOES(pname, param); }
void glLightModelxvOES(GLenum pname, const GLfixed* param) { functions()->glLightModelxvOES(pname, param); }
void glLightxOES(GLenum light, GLenum pname, GLfixed param) { functions()->glLightxOES(light, pname, param); }
void glLightxvOES(GLenum light, GLenum pname, const GLfixed* params) { functions()->glLightxvOES(light, pname, params); }
void glLineStipple(GLint factor, GLushort pattern) { functions()->glLineStipple(factor, pattern); }
void glLineWidth(GLfloat width) { functions()->glLineWidth(width); }
void glLineWidthxOES(GLfixed width) { functions()->glLineWidthxOES(width); }
void glLinkProgramARB(GLhandleARB programObj) { functions()->glLinkProgramARB(programObj); }
void glLinkProgram(GLuint program) { functions()->glLinkProgram(program); }
void glListBase(GLuint base) { functions()->glListBase(base); }
void glListDrawCommandsStatesClientNV(GLuint list, GLuint segment, const void** indirects, const GLsizei* sizes, const GLuint* states, const GLuint* fbos, GLuint count) { functions()->glListDrawCommandsStatesClientNV(list, segment, indirects, sizes, states, fbos, count); }
void glListParameterfSGIX(GLuint list, GLenum pname, GLfloat param) { functions()->glListParameterfSGIX(list, pname, param); }
void glListParameterfvSGIX(GLuint list, GLenum pname, const GLfloat* params) { functions()->glListParameterfvSGIX(list, pname, params); }
void glListParameteriSGIX(GLuint list, GLenum pname, GLint param) { functions()->glListParameteriSGIX(list, pname, param); }
void glListParameterivSGIX(GLuint list, GLenum pname, const GLint* params) { functions()->glListParameterivSGIX(list, pname, params); }
void glLoadIdentity() { functions()->glLoadIdentity(); }
void glLoadIdentityDeformationMapSGIX(GLbitfield mask) { functions()->glLoadIdentityDeformationMapSGIX(mask); }
void glLoadMatrixd(const GLdouble* m) { functions()->glLoadMatrixd(m); }
void glLoadMatrixf(const GLfloat* m) { functions()->glLoadMatrixf(m); }
void glLoadMatrixxOES(const GLfixed* m) { functions()->glLoadMatrixxOES(m); }
void glLoadName(GLuint name) { functions()->glLoadName(name); }
void glLoadProgramNV(GLenum target, GLuint id, GLsizei len, const GLubyte* program) { functions()->glLoadProgramNV(target, id, len, program); }
void glLoadTransposeMatrixdARB(const GLdouble* m) { functions()->glLoadTransposeMatrixdARB(m); }
void glLoadTransposeMatrixd(const GLdouble m[16]) { functions()->glLoadTransposeMatrixd(m[16]); }
void glLoadTransposeMatrixfARB(const GLfloat* m) { functions()->glLoadTransposeMatrixfARB(m); }
void glLoadTransposeMatrixf(const GLfloat m[16]) { functions()->glLoadTransposeMatrixf(m[16]); }
void glLoadTransposeMatrixxOES(const GLfixed* m) { functions()->glLoadTransposeMatrixxOES(m); }
void glLockArraysEXT(GLint first, GLsizei count) { functions()->glLockArraysEXT(first, count); }
void glLogicOp(GLenum opcode) { functions()->glLogicOp(opcode); }
void glMakeBufferNonResidentNV(GLenum target) { functions()->glMakeBufferNonResidentNV(target); }
void glMakeBufferResidentNV(GLenum target, GLenum access) { functions()->glMakeBufferResidentNV(target, access); }
void glMakeImageHandleNonResidentARB(GLuint64 handle) { functions()->glMakeImageHandleNonResidentARB(handle); }
void glMakeImageHandleNonResidentNV(GLuint64 handle) { functions()->glMakeImageHandleNonResidentNV(handle); }
void glMakeImageHandleResidentARB(GLuint64 handle, GLenum access) { functions()->glMakeImageHandleResidentARB(handle, access); }
void glMakeImageHandleResidentNV(GLuint64 handle, GLenum access) { functions()->glMakeImageHandleResidentNV(handle, access); }
void glMakeNamedBufferNonResidentNV(GLuint buffer) { functions()->glMakeNamedBufferNonResidentNV(buffer); }
void glMakeNamedBufferResidentNV(GLuint buffer, GLenum access) { functions()->glMakeNamedBufferResidentNV(buffer, access); }
void glMakeTextureHandleNonResidentARB(GLuint64 handle) { functions()->glMakeTextureHandleNonResidentARB(handle); }
void glMakeTextureHandleNonResidentNV(GLuint64 handle) { functions()->glMakeTextureHandleNonResidentNV(handle); }
void glMakeTextureHandleResidentARB(GLuint64 handle) { functions()->glMakeTextureHandleResidentARB(handle); }
void glMakeTextureHandleResidentNV(GLuint64 handle) { functions()->glMakeTextureHandleResidentNV(handle); }
void glMap1d(GLenum target, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble* points) { functions()->glMap1d(target, u1, u2, stride, order, points); }
void glMap1f(GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat* points) { functions()->glMap1f(target, u1, u2, stride, order, points); }
void glMap1xOES(GLenum target, GLfixed u1, GLfixed u2, GLint stride, GLint order, GLfixed points) { functions()->glMap1xOES(target, u1, u2, stride, order, points); }
void glMap2d(GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble* points) { functions()->glMap2d(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points); }
void glMap2f(GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat* points) { functions()->glMap2f(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points); }
void glMap2xOES(GLenum target, GLfixed u1, GLfixed u2, GLint ustride, GLint uorder, GLfixed v1, GLfixed v2, GLint vstride, GLint vorder, GLfixed points) { functions()->glMap2xOES(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points); }
void* glMapBufferARB(GLenum target, GLenum access) { functions()->glMapBufferARB(target, access); }
void* glMapBuffer(GLenum target, GLenum access) { functions()->glMapBuffer(target, access); }
void* glMapBufferRange(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access) { functions()->glMapBufferRange(target, offset, length, access); }
void glMapControlPointsNV(GLenum target, GLuint index, GLenum type, GLsizei ustride, GLsizei vstride, GLint uorder, GLint vorder, GLboolean packed, const void* points) { functions()->glMapControlPointsNV(target, index, type, ustride, vstride, uorder, vorder, packed, points); }
void glMapGrid1d(GLint un, GLdouble u1, GLdouble u2) { functions()->glMapGrid1d(un, u1, u2); }
void glMapGrid1f(GLint un, GLfloat u1, GLfloat u2) { functions()->glMapGrid1f(un, u1, u2); }
void glMapGrid1xOES(GLint n, GLfixed u1, GLfixed u2) { functions()->glMapGrid1xOES(n, u1, u2); }
void glMapGrid2d(GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2) { functions()->glMapGrid2d(un, u1, u2, vn, v1, v2); }
void glMapGrid2f(GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2) { functions()->glMapGrid2f(un, u1, u2, vn, v1, v2); }
void glMapGrid2xOES(GLint n, GLfixed u1, GLfixed u2, GLfixed v1, GLfixed v2) { functions()->glMapGrid2xOES(n, u1, u2, v1, v2); }
void* glMapNamedBufferEXT(GLuint buffer, GLenum access) { functions()->glMapNamedBufferEXT(buffer, access); }
void* glMapNamedBuffer(GLuint buffer, GLenum access) { functions()->glMapNamedBuffer(buffer, access); }
void* glMapNamedBufferRangeEXT(GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access) { functions()->glMapNamedBufferRangeEXT(buffer, offset, length, access); }
void* glMapNamedBufferRange(GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access) { functions()->glMapNamedBufferRange(buffer, offset, length, access); }
void* glMapObjectBufferATI(GLuint buffer) { functions()->glMapObjectBufferATI(buffer); }
void glMapParameterfvNV(GLenum target, GLenum pname, const GLfloat* params) { functions()->glMapParameterfvNV(target, pname, params); }
void glMapParameterivNV(GLenum target, GLenum pname, const GLint* params) { functions()->glMapParameterivNV(target, pname, params); }
void* glMapTexture2DINTEL(GLuint texture, GLint level, GLbitfield access, GLint* stride, GLenum* layout) { functions()->glMapTexture2DINTEL(texture, level, access, stride, layout); }
void glMapVertexAttrib1dAPPLE(GLuint index, GLuint size, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble* points) { functions()->glMapVertexAttrib1dAPPLE(index, size, u1, u2, stride, order, points); }
void glMapVertexAttrib1fAPPLE(GLuint index, GLuint size, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat* points) { functions()->glMapVertexAttrib1fAPPLE(index, size, u1, u2, stride, order, points); }
void glMapVertexAttrib2dAPPLE(GLuint index, GLuint size, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble* points) { functions()->glMapVertexAttrib2dAPPLE(index, size, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points); }
void glMapVertexAttrib2fAPPLE(GLuint index, GLuint size, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat* points) { functions()->glMapVertexAttrib2fAPPLE(index, size, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points); }
void glMaterialf(GLenum face, GLenum pname, GLfloat param) { functions()->glMaterialf(face, pname, param); }
void glMaterialfv(GLenum face, GLenum pname, const GLfloat* params) { functions()->glMaterialfv(face, pname, params); }
void glMateriali(GLenum face, GLenum pname, GLint param) { functions()->glMateriali(face, pname, param); }
void glMaterialiv(GLenum face, GLenum pname, const GLint* params) { functions()->glMaterialiv(face, pname, params); }
void glMaterialxOES(GLenum face, GLenum pname, GLfixed param) { functions()->glMaterialxOES(face, pname, param); }
void glMaterialxvOES(GLenum face, GLenum pname, const GLfixed* param) { functions()->glMaterialxvOES(face, pname, param); }
void glMatrixFrustumEXT(GLenum mode, GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar) { functions()->glMatrixFrustumEXT(mode, left, right, bottom, top, zNear, zFar); }
void glMatrixIndexPointerARB(GLint size, GLenum type, GLsizei stride, const void* pointer) { functions()->glMatrixIndexPointerARB(size, type, stride, pointer); }
void glMatrixIndexubvARB(GLint size, const GLubyte* indices) { functions()->glMatrixIndexubvARB(size, indices); }
void glMatrixIndexuivARB(GLint size, const GLuint* indices) { functions()->glMatrixIndexuivARB(size, indices); }
void glMatrixIndexusvARB(GLint size, const GLushort* indices) { functions()->glMatrixIndexusvARB(size, indices); }
void glMatrixLoad3x2fNV(GLenum matrixMode, const GLfloat* m) { functions()->glMatrixLoad3x2fNV(matrixMode, m); }
void glMatrixLoad3x3fNV(GLenum matrixMode, const GLfloat* m) { functions()->glMatrixLoad3x3fNV(matrixMode, m); }
void glMatrixLoaddEXT(GLenum mode, const GLdouble* m) { functions()->glMatrixLoaddEXT(mode, m); }
void glMatrixLoadfEXT(GLenum mode, const GLfloat* m) { functions()->glMatrixLoadfEXT(mode, m); }
void glMatrixLoadIdentityEXT(GLenum mode) { functions()->glMatrixLoadIdentityEXT(mode); }
void glMatrixLoadTranspose3x3fNV(GLenum matrixMode, const GLfloat* m) { functions()->glMatrixLoadTranspose3x3fNV(matrixMode, m); }
void glMatrixLoadTransposedEXT(GLenum mode, const GLdouble* m) { functions()->glMatrixLoadTransposedEXT(mode, m); }
void glMatrixLoadTransposefEXT(GLenum mode, const GLfloat* m) { functions()->glMatrixLoadTransposefEXT(mode, m); }
void glMatrixMode(GLenum mode) { functions()->glMatrixMode(mode); }
void glMatrixMult3x2fNV(GLenum matrixMode, const GLfloat* m) { functions()->glMatrixMult3x2fNV(matrixMode, m); }
void glMatrixMult3x3fNV(GLenum matrixMode, const GLfloat* m) { functions()->glMatrixMult3x3fNV(matrixMode, m); }
void glMatrixMultdEXT(GLenum mode, const GLdouble* m) { functions()->glMatrixMultdEXT(mode, m); }
void glMatrixMultfEXT(GLenum mode, const GLfloat* m) { functions()->glMatrixMultfEXT(mode, m); }
void glMatrixMultTranspose3x3fNV(GLenum matrixMode, const GLfloat* m) { functions()->glMatrixMultTranspose3x3fNV(matrixMode, m); }
void glMatrixMultTransposedEXT(GLenum mode, const GLdouble* m) { functions()->glMatrixMultTransposedEXT(mode, m); }
void glMatrixMultTransposefEXT(GLenum mode, const GLfloat* m) { functions()->glMatrixMultTransposefEXT(mode, m); }
void glMatrixOrthoEXT(GLenum mode, GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar) { functions()->glMatrixOrthoEXT(mode, left, right, bottom, top, zNear, zFar); }
void glMatrixPopEXT(GLenum mode) { functions()->glMatrixPopEXT(mode); }
void glMatrixPushEXT(GLenum mode) { functions()->glMatrixPushEXT(mode); }
void glMatrixRotatedEXT(GLenum mode, GLdouble angle, GLdouble x, GLdouble y, GLdouble z) { functions()->glMatrixRotatedEXT(mode, angle, x, y, z); }
void glMatrixRotatefEXT(GLenum mode, GLfloat angle, GLfloat x, GLfloat y, GLfloat z) { functions()->glMatrixRotatefEXT(mode, angle, x, y, z); }
void glMatrixScaledEXT(GLenum mode, GLdouble x, GLdouble y, GLdouble z) { functions()->glMatrixScaledEXT(mode, x, y, z); }
void glMatrixScalefEXT(GLenum mode, GLfloat x, GLfloat y, GLfloat z) { functions()->glMatrixScalefEXT(mode, x, y, z); }
void glMatrixTranslatedEXT(GLenum mode, GLdouble x, GLdouble y, GLdouble z) { functions()->glMatrixTranslatedEXT(mode, x, y, z); }
void glMatrixTranslatefEXT(GLenum mode, GLfloat x, GLfloat y, GLfloat z) { functions()->glMatrixTranslatefEXT(mode, x, y, z); }
void glMaxShaderCompilerThreadsARB(GLuint count) { functions()->glMaxShaderCompilerThreadsARB(count); }
void glMemoryBarrierByRegion(GLbitfield barriers) { functions()->glMemoryBarrierByRegion(barriers); }
void glMemoryBarrierEXT(GLbitfield barriers) { functions()->glMemoryBarrierEXT(barriers); }
void glMemoryBarrier(GLbitfield barriers) { functions()->glMemoryBarrier(barriers); }
void glMinmaxEXT(GLenum target, GLenum internalformat, GLboolean sink) { functions()->glMinmaxEXT(target, internalformat, sink); }
void glMinmax(GLenum target, GLenum internalformat, GLboolean sink) { functions()->glMinmax(target, internalformat, sink); }
void glMinSampleShadingARB(GLfloat value) { functions()->glMinSampleShadingARB(value); }
void glMinSampleShading(GLfloat value) { functions()->glMinSampleShading(value); }
void glMultiDrawArraysEXT(GLenum mode, const GLint* first, const GLsizei* count, GLsizei primcount) { functions()->glMultiDrawArraysEXT(mode, first, count, primcount); }
void glMultiDrawArrays(GLenum mode, const GLint* first, const GLsizei* count, GLsizei drawcount) { functions()->glMultiDrawArrays(mode, first, count, drawcount); }
void glMultiDrawArraysIndirectAMD(GLenum mode, const void* indirect, GLsizei primcount, GLsizei stride) { functions()->glMultiDrawArraysIndirectAMD(mode, indirect, primcount, stride); }
void glMultiDrawArraysIndirectBindlessCountNV(GLenum mode, const void* indirect, GLsizei drawCount, GLsizei maxDrawCount, GLsizei stride, GLint vertexBufferCount) { functions()->glMultiDrawArraysIndirectBindlessCountNV(mode, indirect, drawCount, maxDrawCount, stride, vertexBufferCount); }
void glMultiDrawArraysIndirectBindlessNV(GLenum mode, const void* indirect, GLsizei drawCount, GLsizei stride, GLint vertexBufferCount) { functions()->glMultiDrawArraysIndirectBindlessNV(mode, indirect, drawCount, stride, vertexBufferCount); }
void glMultiDrawArraysIndirectCountARB(GLenum mode, GLintptr indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride) { functions()->glMultiDrawArraysIndirectCountARB(mode, indirect, drawcount, maxdrawcount, stride); }
void glMultiDrawArraysIndirect(GLenum mode, const void* indirect, GLsizei drawcount, GLsizei stride) { functions()->glMultiDrawArraysIndirect(mode, indirect, drawcount, stride); }
void glMultiDrawElementArrayAPPLE(GLenum mode, const GLint* first, const GLsizei* count, GLsizei primcount) { functions()->glMultiDrawElementArrayAPPLE(mode, first, count, primcount); }
void glMultiDrawElementsBaseVertex(GLenum mode, const GLsizei* count, GLenum type, const void*const* indices, GLsizei drawcount, const GLint* basevertex) { functions()->glMultiDrawElementsBaseVertex(mode, count, type, indices, drawcount, basevertex); }
void glMultiDrawElementsEXT(GLenum mode, const GLsizei* count, GLenum type, const void*const* indices, GLsizei primcount) { functions()->glMultiDrawElementsEXT(mode, count, type, indices, primcount); }
void glMultiDrawElements(GLenum mode, const GLsizei* count, GLenum type, const void*const* indices, GLsizei drawcount) { functions()->glMultiDrawElements(mode, count, type, indices, drawcount); }
void glMultiDrawElementsIndirectAMD(GLenum mode, GLenum type, const void* indirect, GLsizei primcount, GLsizei stride) { functions()->glMultiDrawElementsIndirectAMD(mode, type, indirect, primcount, stride); }
void glMultiDrawElementsIndirectBindlessCountNV(GLenum mode, GLenum type, const void* indirect, GLsizei drawCount, GLsizei maxDrawCount, GLsizei stride, GLint vertexBufferCount) { functions()->glMultiDrawElementsIndirectBindlessCountNV(mode, type, indirect, drawCount, maxDrawCount, stride, vertexBufferCount); }
void glMultiDrawElementsIndirectBindlessNV(GLenum mode, GLenum type, const void* indirect, GLsizei drawCount, GLsizei stride, GLint vertexBufferCount) { functions()->glMultiDrawElementsIndirectBindlessNV(mode, type, indirect, drawCount, stride, vertexBufferCount); }
void glMultiDrawElementsIndirectCountARB(GLenum mode, GLenum type, GLintptr indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride) { functions()->glMultiDrawElementsIndirectCountARB(mode, type, indirect, drawcount, maxdrawcount, stride); }
void glMultiDrawElementsIndirect(GLenum mode, GLenum type, const void* indirect, GLsizei drawcount, GLsizei stride) { functions()->glMultiDrawElementsIndirect(mode, type, indirect, drawcount, stride); }
void glMultiDrawRangeElementArrayAPPLE(GLenum mode, GLuint start, GLuint end, const GLint* first, const GLsizei* count, GLsizei primcount) { functions()->glMultiDrawRangeElementArrayAPPLE(mode, start, end, first, count, primcount); }
void glMultiModeDrawArraysIBM(const GLenum* mode, const GLint* first, const GLsizei* count, GLsizei primcount, GLint modestride) { functions()->glMultiModeDrawArraysIBM(mode, first, count, primcount, modestride); }
void glMultiModeDrawElementsIBM(const GLenum* mode, const GLsizei* count, GLenum type, const void*const* indices, GLsizei primcount, GLint modestride) { functions()->glMultiModeDrawElementsIBM(mode, count, type, indices, primcount, modestride); }
void glMultiTexBufferEXT(GLenum texunit, GLenum target, GLenum internalformat, GLuint buffer) { functions()->glMultiTexBufferEXT(texunit, target, internalformat, buffer); }
void glMultiTexCoord1bOES(GLenum texture, GLbyte s) { functions()->glMultiTexCoord1bOES(texture, s); }
void glMultiTexCoord1bvOES(GLenum texture, const GLbyte* coords) { functions()->glMultiTexCoord1bvOES(texture, coords); }
void glMultiTexCoord1dARB(GLenum target, GLdouble s) { functions()->glMultiTexCoord1dARB(target, s); }
void glMultiTexCoord1d(GLenum target, GLdouble s) { functions()->glMultiTexCoord1d(target, s); }
void glMultiTexCoord1dvARB(GLenum target, const GLdouble* v) { functions()->glMultiTexCoord1dvARB(target, v); }
void glMultiTexCoord1dv(GLenum target, const GLdouble* v) { functions()->glMultiTexCoord1dv(target, v); }
void glMultiTexCoord1fARB(GLenum target, GLfloat s) { functions()->glMultiTexCoord1fARB(target, s); }
void glMultiTexCoord1f(GLenum target, GLfloat s) { functions()->glMultiTexCoord1f(target, s); }
void glMultiTexCoord1fvARB(GLenum target, const GLfloat* v) { functions()->glMultiTexCoord1fvARB(target, v); }
void glMultiTexCoord1fv(GLenum target, const GLfloat* v) { functions()->glMultiTexCoord1fv(target, v); }
void glMultiTexCoord1hNV(GLenum target, GLhalfNV s) { functions()->glMultiTexCoord1hNV(target, s); }
void glMultiTexCoord1hvNV(GLenum target, const GLhalfNV* v) { functions()->glMultiTexCoord1hvNV(target, v); }
void glMultiTexCoord1iARB(GLenum target, GLint s) { functions()->glMultiTexCoord1iARB(target, s); }
void glMultiTexCoord1i(GLenum target, GLint s) { functions()->glMultiTexCoord1i(target, s); }
void glMultiTexCoord1ivARB(GLenum target, const GLint* v) { functions()->glMultiTexCoord1ivARB(target, v); }
void glMultiTexCoord1iv(GLenum target, const GLint* v) { functions()->glMultiTexCoord1iv(target, v); }
void glMultiTexCoord1sARB(GLenum target, GLshort s) { functions()->glMultiTexCoord1sARB(target, s); }
void glMultiTexCoord1s(GLenum target, GLshort s) { functions()->glMultiTexCoord1s(target, s); }
void glMultiTexCoord1svARB(GLenum target, const GLshort* v) { functions()->glMultiTexCoord1svARB(target, v); }
void glMultiTexCoord1sv(GLenum target, const GLshort* v) { functions()->glMultiTexCoord1sv(target, v); }
void glMultiTexCoord1xOES(GLenum texture, GLfixed s) { functions()->glMultiTexCoord1xOES(texture, s); }
void glMultiTexCoord1xvOES(GLenum texture, const GLfixed* coords) { functions()->glMultiTexCoord1xvOES(texture, coords); }
void glMultiTexCoord2bOES(GLenum texture, GLbyte s, GLbyte t) { functions()->glMultiTexCoord2bOES(texture, s, t); }
void glMultiTexCoord2bvOES(GLenum texture, const GLbyte* coords) { functions()->glMultiTexCoord2bvOES(texture, coords); }
void glMultiTexCoord2dARB(GLenum target, GLdouble s, GLdouble t) { functions()->glMultiTexCoord2dARB(target, s, t); }
void glMultiTexCoord2d(GLenum target, GLdouble s, GLdouble t) { functions()->glMultiTexCoord2d(target, s, t); }
void glMultiTexCoord2dvARB(GLenum target, const GLdouble* v) { functions()->glMultiTexCoord2dvARB(target, v); }
void glMultiTexCoord2dv(GLenum target, const GLdouble* v) { functions()->glMultiTexCoord2dv(target, v); }
void glMultiTexCoord2fARB(GLenum target, GLfloat s, GLfloat t) { functions()->glMultiTexCoord2fARB(target, s, t); }
void glMultiTexCoord2f(GLenum target, GLfloat s, GLfloat t) { functions()->glMultiTexCoord2f(target, s, t); }
void glMultiTexCoord2fvARB(GLenum target, const GLfloat* v) { functions()->glMultiTexCoord2fvARB(target, v); }
void glMultiTexCoord2fv(GLenum target, const GLfloat* v) { functions()->glMultiTexCoord2fv(target, v); }
void glMultiTexCoord2hNV(GLenum target, GLhalfNV s, GLhalfNV t) { functions()->glMultiTexCoord2hNV(target, s, t); }
void glMultiTexCoord2hvNV(GLenum target, const GLhalfNV* v) { functions()->glMultiTexCoord2hvNV(target, v); }
void glMultiTexCoord2iARB(GLenum target, GLint s, GLint t) { functions()->glMultiTexCoord2iARB(target, s, t); }
void glMultiTexCoord2i(GLenum target, GLint s, GLint t) { functions()->glMultiTexCoord2i(target, s, t); }
void glMultiTexCoord2ivARB(GLenum target, const GLint* v) { functions()->glMultiTexCoord2ivARB(target, v); }
void glMultiTexCoord2iv(GLenum target, const GLint* v) { functions()->glMultiTexCoord2iv(target, v); }
void glMultiTexCoord2sARB(GLenum target, GLshort s, GLshort t) { functions()->glMultiTexCoord2sARB(target, s, t); }
void glMultiTexCoord2s(GLenum target, GLshort s, GLshort t) { functions()->glMultiTexCoord2s(target, s, t); }
void glMultiTexCoord2svARB(GLenum target, const GLshort* v) { functions()->glMultiTexCoord2svARB(target, v); }
void glMultiTexCoord2sv(GLenum target, const GLshort* v) { functions()->glMultiTexCoord2sv(target, v); }
void glMultiTexCoord2xOES(GLenum texture, GLfixed s, GLfixed t) { functions()->glMultiTexCoord2xOES(texture, s, t); }
void glMultiTexCoord2xvOES(GLenum texture, const GLfixed* coords) { functions()->glMultiTexCoord2xvOES(texture, coords); }
void glMultiTexCoord3bOES(GLenum texture, GLbyte s, GLbyte t, GLbyte r) { functions()->glMultiTexCoord3bOES(texture, s, t, r); }
void glMultiTexCoord3bvOES(GLenum texture, const GLbyte* coords) { functions()->glMultiTexCoord3bvOES(texture, coords); }
void glMultiTexCoord3dARB(GLenum target, GLdouble s, GLdouble t, GLdouble r) { functions()->glMultiTexCoord3dARB(target, s, t, r); }
void glMultiTexCoord3d(GLenum target, GLdouble s, GLdouble t, GLdouble r) { functions()->glMultiTexCoord3d(target, s, t, r); }
void glMultiTexCoord3dvARB(GLenum target, const GLdouble* v) { functions()->glMultiTexCoord3dvARB(target, v); }
void glMultiTexCoord3dv(GLenum target, const GLdouble* v) { functions()->glMultiTexCoord3dv(target, v); }
void glMultiTexCoord3fARB(GLenum target, GLfloat s, GLfloat t, GLfloat r) { functions()->glMultiTexCoord3fARB(target, s, t, r); }
void glMultiTexCoord3f(GLenum target, GLfloat s, GLfloat t, GLfloat r) { functions()->glMultiTexCoord3f(target, s, t, r); }
void glMultiTexCoord3fvARB(GLenum target, const GLfloat* v) { functions()->glMultiTexCoord3fvARB(target, v); }
void glMultiTexCoord3fv(GLenum target, const GLfloat* v) { functions()->glMultiTexCoord3fv(target, v); }
void glMultiTexCoord3hNV(GLenum target, GLhalfNV s, GLhalfNV t, GLhalfNV r) { functions()->glMultiTexCoord3hNV(target, s, t, r); }
void glMultiTexCoord3hvNV(GLenum target, const GLhalfNV* v) { functions()->glMultiTexCoord3hvNV(target, v); }
void glMultiTexCoord3iARB(GLenum target, GLint s, GLint t, GLint r) { functions()->glMultiTexCoord3iARB(target, s, t, r); }
void glMultiTexCoord3i(GLenum target, GLint s, GLint t, GLint r) { functions()->glMultiTexCoord3i(target, s, t, r); }
void glMultiTexCoord3ivARB(GLenum target, const GLint* v) { functions()->glMultiTexCoord3ivARB(target, v); }
void glMultiTexCoord3iv(GLenum target, const GLint* v) { functions()->glMultiTexCoord3iv(target, v); }
void glMultiTexCoord3sARB(GLenum target, GLshort s, GLshort t, GLshort r) { functions()->glMultiTexCoord3sARB(target, s, t, r); }
void glMultiTexCoord3s(GLenum target, GLshort s, GLshort t, GLshort r) { functions()->glMultiTexCoord3s(target, s, t, r); }
void glMultiTexCoord3svARB(GLenum target, const GLshort* v) { functions()->glMultiTexCoord3svARB(target, v); }
void glMultiTexCoord3sv(GLenum target, const GLshort* v) { functions()->glMultiTexCoord3sv(target, v); }
void glMultiTexCoord3xOES(GLenum texture, GLfixed s, GLfixed t, GLfixed r) { functions()->glMultiTexCoord3xOES(texture, s, t, r); }
void glMultiTexCoord3xvOES(GLenum texture, const GLfixed* coords) { functions()->glMultiTexCoord3xvOES(texture, coords); }
void glMultiTexCoord4bOES(GLenum texture, GLbyte s, GLbyte t, GLbyte r, GLbyte q) { functions()->glMultiTexCoord4bOES(texture, s, t, r, q); }
void glMultiTexCoord4bvOES(GLenum texture, const GLbyte* coords) { functions()->glMultiTexCoord4bvOES(texture, coords); }
void glMultiTexCoord4dARB(GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q) { functions()->glMultiTexCoord4dARB(target, s, t, r, q); }
void glMultiTexCoord4d(GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q) { functions()->glMultiTexCoord4d(target, s, t, r, q); }
void glMultiTexCoord4dvARB(GLenum target, const GLdouble* v) { functions()->glMultiTexCoord4dvARB(target, v); }
void glMultiTexCoord4dv(GLenum target, const GLdouble* v) { functions()->glMultiTexCoord4dv(target, v); }
void glMultiTexCoord4fARB(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q) { functions()->glMultiTexCoord4fARB(target, s, t, r, q); }
void glMultiTexCoord4f(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q) { functions()->glMultiTexCoord4f(target, s, t, r, q); }
void glMultiTexCoord4fvARB(GLenum target, const GLfloat* v) { functions()->glMultiTexCoord4fvARB(target, v); }
void glMultiTexCoord4fv(GLenum target, const GLfloat* v) { functions()->glMultiTexCoord4fv(target, v); }
void glMultiTexCoord4hNV(GLenum target, GLhalfNV s, GLhalfNV t, GLhalfNV r, GLhalfNV q) { functions()->glMultiTexCoord4hNV(target, s, t, r, q); }
void glMultiTexCoord4hvNV(GLenum target, const GLhalfNV* v) { functions()->glMultiTexCoord4hvNV(target, v); }
void glMultiTexCoord4iARB(GLenum target, GLint s, GLint t, GLint r, GLint q) { functions()->glMultiTexCoord4iARB(target, s, t, r, q); }
void glMultiTexCoord4i(GLenum target, GLint s, GLint t, GLint r, GLint q) { functions()->glMultiTexCoord4i(target, s, t, r, q); }
void glMultiTexCoord4ivARB(GLenum target, const GLint* v) { functions()->glMultiTexCoord4ivARB(target, v); }
void glMultiTexCoord4iv(GLenum target, const GLint* v) { functions()->glMultiTexCoord4iv(target, v); }
void glMultiTexCoord4sARB(GLenum target, GLshort s, GLshort t, GLshort r, GLshort q) { functions()->glMultiTexCoord4sARB(target, s, t, r, q); }
void glMultiTexCoord4s(GLenum target, GLshort s, GLshort t, GLshort r, GLshort q) { functions()->glMultiTexCoord4s(target, s, t, r, q); }
void glMultiTexCoord4svARB(GLenum target, const GLshort* v) { functions()->glMultiTexCoord4svARB(target, v); }
void glMultiTexCoord4sv(GLenum target, const GLshort* v) { functions()->glMultiTexCoord4sv(target, v); }
void glMultiTexCoord4xOES(GLenum texture, GLfixed s, GLfixed t, GLfixed r, GLfixed q) { functions()->glMultiTexCoord4xOES(texture, s, t, r, q); }
void glMultiTexCoord4xvOES(GLenum texture, const GLfixed* coords) { functions()->glMultiTexCoord4xvOES(texture, coords); }
void glMultiTexCoordP1ui(GLenum texture, GLenum type, GLuint coords) { functions()->glMultiTexCoordP1ui(texture, type, coords); }
void glMultiTexCoordP1uiv(GLenum texture, GLenum type, const GLuint* coords) { functions()->glMultiTexCoordP1uiv(texture, type, coords); }
void glMultiTexCoordP2ui(GLenum texture, GLenum type, GLuint coords) { functions()->glMultiTexCoordP2ui(texture, type, coords); }
void glMultiTexCoordP2uiv(GLenum texture, GLenum type, const GLuint* coords) { functions()->glMultiTexCoordP2uiv(texture, type, coords); }
void glMultiTexCoordP3ui(GLenum texture, GLenum type, GLuint coords) { functions()->glMultiTexCoordP3ui(texture, type, coords); }
void glMultiTexCoordP3uiv(GLenum texture, GLenum type, const GLuint* coords) { functions()->glMultiTexCoordP3uiv(texture, type, coords); }
void glMultiTexCoordP4ui(GLenum texture, GLenum type, GLuint coords) { functions()->glMultiTexCoordP4ui(texture, type, coords); }
void glMultiTexCoordP4uiv(GLenum texture, GLenum type, const GLuint* coords) { functions()->glMultiTexCoordP4uiv(texture, type, coords); }
void glMultiTexCoordPointerEXT(GLenum texunit, GLint size, GLenum type, GLsizei stride, const void* pointer) { functions()->glMultiTexCoordPointerEXT(texunit, size, type, stride, pointer); }
void glMultiTexEnvfEXT(GLenum texunit, GLenum target, GLenum pname, GLfloat param) { functions()->glMultiTexEnvfEXT(texunit, target, pname, param); }
void glMultiTexEnvfvEXT(GLenum texunit, GLenum target, GLenum pname, const GLfloat* params) { functions()->glMultiTexEnvfvEXT(texunit, target, pname, params); }
void glMultiTexEnviEXT(GLenum texunit, GLenum target, GLenum pname, GLint param) { functions()->glMultiTexEnviEXT(texunit, target, pname, param); }
void glMultiTexEnvivEXT(GLenum texunit, GLenum target, GLenum pname, const GLint* params) { functions()->glMultiTexEnvivEXT(texunit, target, pname, params); }
void glMultiTexGendEXT(GLenum texunit, GLenum coord, GLenum pname, GLdouble param) { functions()->glMultiTexGendEXT(texunit, coord, pname, param); }
void glMultiTexGendvEXT(GLenum texunit, GLenum coord, GLenum pname, const GLdouble* params) { functions()->glMultiTexGendvEXT(texunit, coord, pname, params); }
void glMultiTexGenfEXT(GLenum texunit, GLenum coord, GLenum pname, GLfloat param) { functions()->glMultiTexGenfEXT(texunit, coord, pname, param); }
void glMultiTexGenfvEXT(GLenum texunit, GLenum coord, GLenum pname, const GLfloat* params) { functions()->glMultiTexGenfvEXT(texunit, coord, pname, params); }
void glMultiTexGeniEXT(GLenum texunit, GLenum coord, GLenum pname, GLint param) { functions()->glMultiTexGeniEXT(texunit, coord, pname, param); }
void glMultiTexGenivEXT(GLenum texunit, GLenum coord, GLenum pname, const GLint* params) { functions()->glMultiTexGenivEXT(texunit, coord, pname, params); }
void glMultiTexImage1DEXT(GLenum texunit, GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void* pixels) { functions()->glMultiTexImage1DEXT(texunit, target, level, internalformat, width, border, format, type, pixels); }
void glMultiTexImage2DEXT(GLenum texunit, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* pixels) { functions()->glMultiTexImage2DEXT(texunit, target, level, internalformat, width, height, border, format, type, pixels); }
void glMultiTexImage3DEXT(GLenum texunit, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void* pixels) { functions()->glMultiTexImage3DEXT(texunit, target, level, internalformat, width, height, depth, border, format, type, pixels); }
void glMultiTexParameterfEXT(GLenum texunit, GLenum target, GLenum pname, GLfloat param) { functions()->glMultiTexParameterfEXT(texunit, target, pname, param); }
void glMultiTexParameterfvEXT(GLenum texunit, GLenum target, GLenum pname, const GLfloat* params) { functions()->glMultiTexParameterfvEXT(texunit, target, pname, params); }
void glMultiTexParameteriEXT(GLenum texunit, GLenum target, GLenum pname, GLint param) { functions()->glMultiTexParameteriEXT(texunit, target, pname, param); }
void glMultiTexParameterIivEXT(GLenum texunit, GLenum target, GLenum pname, const GLint* params) { functions()->glMultiTexParameterIivEXT(texunit, target, pname, params); }
void glMultiTexParameterIuivEXT(GLenum texunit, GLenum target, GLenum pname, const GLuint* params) { functions()->glMultiTexParameterIuivEXT(texunit, target, pname, params); }
void glMultiTexParameterivEXT(GLenum texunit, GLenum target, GLenum pname, const GLint* params) { functions()->glMultiTexParameterivEXT(texunit, target, pname, params); }
void glMultiTexRenderbufferEXT(GLenum texunit, GLenum target, GLuint renderbuffer) { functions()->glMultiTexRenderbufferEXT(texunit, target, renderbuffer); }
void glMultiTexSubImage1DEXT(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void* pixels) { functions()->glMultiTexSubImage1DEXT(texunit, target, level, xoffset, width, format, type, pixels); }
void glMultiTexSubImage2DEXT(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels) { functions()->glMultiTexSubImage2DEXT(texunit, target, level, xoffset, yoffset, width, height, format, type, pixels); }
void glMultiTexSubImage3DEXT(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* pixels) { functions()->glMultiTexSubImage3DEXT(texunit, target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels); }
void glMultMatrixd(const GLdouble* m) { functions()->glMultMatrixd(m); }
void glMultMatrixf(const GLfloat* m) { functions()->glMultMatrixf(m); }
void glMultMatrixxOES(const GLfixed* m) { functions()->glMultMatrixxOES(m); }
void glMultTransposeMatrixdARB(const GLdouble* m) { functions()->glMultTransposeMatrixdARB(m); }
void glMultTransposeMatrixd(const GLdouble m[16]) { functions()->glMultTransposeMatrixd(m[16]); }
void glMultTransposeMatrixfARB(const GLfloat* m) { functions()->glMultTransposeMatrixfARB(m); }
void glMultTransposeMatrixf(const GLfloat m[16]) { functions()->glMultTransposeMatrixf(m[16]); }
void glMultTransposeMatrixxOES(const GLfixed* m) { functions()->glMultTransposeMatrixxOES(m); }
void glNamedBufferDataEXT(GLuint buffer, GLsizeiptr size, const void* data, GLenum usage) { functions()->glNamedBufferDataEXT(buffer, size, data, usage); }
void glNamedBufferData(GLuint buffer, GLsizeiptr size, const void* data, GLenum usage) { functions()->glNamedBufferData(buffer, size, data, usage); }
void glNamedBufferPageCommitmentARB(GLuint buffer, GLintptr offset, GLsizeiptr size, GLboolean commit) { functions()->glNamedBufferPageCommitmentARB(buffer, offset, size, commit); }
void glNamedBufferPageCommitmentEXT(GLuint buffer, GLintptr offset, GLsizeiptr size, GLboolean commit) { functions()->glNamedBufferPageCommitmentEXT(buffer, offset, size, commit); }
void glNamedBufferStorageEXT(GLuint buffer, GLsizeiptr size, const void* data, GLbitfield flags) { functions()->glNamedBufferStorageEXT(buffer, size, data, flags); }
void glNamedBufferStorage(GLuint buffer, GLsizeiptr size, const void* data, GLbitfield flags) { functions()->glNamedBufferStorage(buffer, size, data, flags); }
void glNamedBufferSubDataEXT(GLuint buffer, GLintptr offset, GLsizeiptr size, const void* data) { functions()->glNamedBufferSubDataEXT(buffer, offset, size, data); }
void glNamedBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr size, const void* data) { functions()->glNamedBufferSubData(buffer, offset, size, data); }
void glNamedCopyBufferSubDataEXT(GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size) { functions()->glNamedCopyBufferSubDataEXT(readBuffer, writeBuffer, readOffset, writeOffset, size); }
void glNamedFramebufferDrawBuffer(GLuint framebuffer, GLenum buf) { functions()->glNamedFramebufferDrawBuffer(framebuffer, buf); }
void glNamedFramebufferDrawBuffers(GLuint framebuffer, GLsizei n, const GLenum* bufs) { functions()->glNamedFramebufferDrawBuffers(framebuffer, n, bufs); }
void glNamedFramebufferParameteriEXT(GLuint framebuffer, GLenum pname, GLint param) { functions()->glNamedFramebufferParameteriEXT(framebuffer, pname, param); }
void glNamedFramebufferParameteri(GLuint framebuffer, GLenum pname, GLint param) { functions()->glNamedFramebufferParameteri(framebuffer, pname, param); }
void glNamedFramebufferReadBuffer(GLuint framebuffer, GLenum src) { functions()->glNamedFramebufferReadBuffer(framebuffer, src); }
void glNamedFramebufferRenderbufferEXT(GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer) { functions()->glNamedFramebufferRenderbufferEXT(framebuffer, attachment, renderbuffertarget, renderbuffer); }
void glNamedFramebufferRenderbuffer(GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer) { functions()->glNamedFramebufferRenderbuffer(framebuffer, attachment, renderbuffertarget, renderbuffer); }
void glNamedFramebufferSampleLocationsfvARB(GLuint framebuffer, GLuint start, GLsizei count, const GLfloat* v) { functions()->glNamedFramebufferSampleLocationsfvARB(framebuffer, start, count, v); }
void glNamedFramebufferSampleLocationsfvNV(GLuint framebuffer, GLuint start, GLsizei count, const GLfloat* v) { functions()->glNamedFramebufferSampleLocationsfvNV(framebuffer, start, count, v); }
void glNamedFramebufferTexture1DEXT(GLuint framebuffer, GLenum attachment, GLenum textarget, GLuint texture, GLint level) { functions()->glNamedFramebufferTexture1DEXT(framebuffer, attachment, textarget, texture, level); }
void glNamedFramebufferTexture2DEXT(GLuint framebuffer, GLenum attachment, GLenum textarget, GLuint texture, GLint level) { functions()->glNamedFramebufferTexture2DEXT(framebuffer, attachment, textarget, texture, level); }
void glNamedFramebufferTexture3DEXT(GLuint framebuffer, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset) { functions()->glNamedFramebufferTexture3DEXT(framebuffer, attachment, textarget, texture, level, zoffset); }
void glNamedFramebufferTextureEXT(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level) { functions()->glNamedFramebufferTextureEXT(framebuffer, attachment, texture, level); }
void glNamedFramebufferTextureFaceEXT(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLenum face) { functions()->glNamedFramebufferTextureFaceEXT(framebuffer, attachment, texture, level, face); }
void glNamedFramebufferTexture(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level) { functions()->glNamedFramebufferTexture(framebuffer, attachment, texture, level); }
void glNamedFramebufferTextureLayerEXT(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer) { functions()->glNamedFramebufferTextureLayerEXT(framebuffer, attachment, texture, level, layer); }
void glNamedFramebufferTextureLayer(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer) { functions()->glNamedFramebufferTextureLayer(framebuffer, attachment, texture, level, layer); }
void glNamedProgramLocalParameter4dEXT(GLuint program, GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) { functions()->glNamedProgramLocalParameter4dEXT(program, target, index, x, y, z, w); }
void glNamedProgramLocalParameter4dvEXT(GLuint program, GLenum target, GLuint index, const GLdouble* params) { functions()->glNamedProgramLocalParameter4dvEXT(program, target, index, params); }
void glNamedProgramLocalParameter4fEXT(GLuint program, GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) { functions()->glNamedProgramLocalParameter4fEXT(program, target, index, x, y, z, w); }
void glNamedProgramLocalParameter4fvEXT(GLuint program, GLenum target, GLuint index, const GLfloat* params) { functions()->glNamedProgramLocalParameter4fvEXT(program, target, index, params); }
void glNamedProgramLocalParameterI4iEXT(GLuint program, GLenum target, GLuint index, GLint x, GLint y, GLint z, GLint w) { functions()->glNamedProgramLocalParameterI4iEXT(program, target, index, x, y, z, w); }
void glNamedProgramLocalParameterI4ivEXT(GLuint program, GLenum target, GLuint index, const GLint* params) { functions()->glNamedProgramLocalParameterI4ivEXT(program, target, index, params); }
void glNamedProgramLocalParameterI4uiEXT(GLuint program, GLenum target, GLuint index, GLuint x, GLuint y, GLuint z, GLuint w) { functions()->glNamedProgramLocalParameterI4uiEXT(program, target, index, x, y, z, w); }
void glNamedProgramLocalParameterI4uivEXT(GLuint program, GLenum target, GLuint index, const GLuint* params) { functions()->glNamedProgramLocalParameterI4uivEXT(program, target, index, params); }
void glNamedProgramLocalParameters4fvEXT(GLuint program, GLenum target, GLuint index, GLsizei count, const GLfloat* params) { functions()->glNamedProgramLocalParameters4fvEXT(program, target, index, count, params); }
void glNamedProgramLocalParametersI4ivEXT(GLuint program, GLenum target, GLuint index, GLsizei count, const GLint* params) { functions()->glNamedProgramLocalParametersI4ivEXT(program, target, index, count, params); }
void glNamedProgramLocalParametersI4uivEXT(GLuint program, GLenum target, GLuint index, GLsizei count, const GLuint* params) { functions()->glNamedProgramLocalParametersI4uivEXT(program, target, index, count, params); }
void glNamedProgramStringEXT(GLuint program, GLenum target, GLenum format, GLsizei len, const void* string) { functions()->glNamedProgramStringEXT(program, target, format, len, string); }
void glNamedRenderbufferStorageEXT(GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height) { functions()->glNamedRenderbufferStorageEXT(renderbuffer, internalformat, width, height); }
void glNamedRenderbufferStorage(GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height) { functions()->glNamedRenderbufferStorage(renderbuffer, internalformat, width, height); }
void glNamedRenderbufferStorageMultisampleCoverageEXT(GLuint renderbuffer, GLsizei coverageSamples, GLsizei colorSamples, GLenum internalformat, GLsizei width, GLsizei height) { functions()->glNamedRenderbufferStorageMultisampleCoverageEXT(renderbuffer, coverageSamples, colorSamples, internalformat, width, height); }
void glNamedRenderbufferStorageMultisampleEXT(GLuint renderbuffer, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height) { functions()->glNamedRenderbufferStorageMultisampleEXT(renderbuffer, samples, internalformat, width, height); }
void glNamedRenderbufferStorageMultisample(GLuint renderbuffer, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height) { functions()->glNamedRenderbufferStorageMultisample(renderbuffer, samples, internalformat, width, height); }
void glNamedStringARB(GLenum type, GLint namelen, const GLchar* name, GLint stringlen, const GLchar* string) { functions()->glNamedStringARB(type, namelen, name, stringlen, string); }
void glNewList(GLuint list, GLenum mode) { functions()->glNewList(list, mode); }
void glNormal3b(GLbyte nx, GLbyte ny, GLbyte nz) { functions()->glNormal3b(nx, ny, nz); }
void glNormal3bv(const GLbyte* v) { functions()->glNormal3bv(v); }
void glNormal3d(GLdouble nx, GLdouble ny, GLdouble nz) { functions()->glNormal3d(nx, ny, nz); }
void glNormal3dv(const GLdouble* v) { functions()->glNormal3dv(v); }
void glNormal3f(GLfloat nx, GLfloat ny, GLfloat nz) { functions()->glNormal3f(nx, ny, nz); }
void glNormal3fv(const GLfloat* v) { functions()->glNormal3fv(v); }
void glNormal3fVertex3fSUN(GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z) { functions()->glNormal3fVertex3fSUN(nx, ny, nz, x, y, z); }
void glNormal3fVertex3fvSUN(const GLfloat* n, const GLfloat* v) { functions()->glNormal3fVertex3fvSUN(n, v); }
void glNormal3hNV(GLhalfNV nx, GLhalfNV ny, GLhalfNV nz) { functions()->glNormal3hNV(nx, ny, nz); }
void glNormal3hvNV(const GLhalfNV* v) { functions()->glNormal3hvNV(v); }
void glNormal3i(GLint nx, GLint ny, GLint nz) { functions()->glNormal3i(nx, ny, nz); }
void glNormal3iv(const GLint* v) { functions()->glNormal3iv(v); }
void glNormal3s(GLshort nx, GLshort ny, GLshort nz) { functions()->glNormal3s(nx, ny, nz); }
void glNormal3sv(const GLshort* v) { functions()->glNormal3sv(v); }
void glNormal3xOES(GLfixed nx, GLfixed ny, GLfixed nz) { functions()->glNormal3xOES(nx, ny, nz); }
void glNormal3xvOES(const GLfixed* coords) { functions()->glNormal3xvOES(coords); }
void glNormalFormatNV(GLenum type, GLsizei stride) { functions()->glNormalFormatNV(type, stride); }
void glNormalP3ui(GLenum type, GLuint coords) { functions()->glNormalP3ui(type, coords); }
void glNormalP3uiv(GLenum type, const GLuint* coords) { functions()->glNormalP3uiv(type, coords); }
void glNormalPointerEXT(GLenum type, GLsizei stride, GLsizei count, const void* pointer) { functions()->glNormalPointerEXT(type, stride, count, pointer); }
void glNormalPointer(GLenum type, GLsizei stride, const GLvoid* ptr) { functions()->glNormalPointer(type, stride, ptr); }
void glNormalPointerListIBM(GLenum type, GLint stride, const void** pointer, GLint ptrstride) { functions()->glNormalPointerListIBM(type, stride, pointer, ptrstride); }
void glNormalPointervINTEL(GLenum type, const void** pointer) { functions()->glNormalPointervINTEL(type, pointer); }
void glNormalStream3bATI(GLenum stream, GLbyte nx, GLbyte ny, GLbyte nz) { functions()->glNormalStream3bATI(stream, nx, ny, nz); }
void glNormalStream3bvATI(GLenum stream, const GLbyte* coords) { functions()->glNormalStream3bvATI(stream, coords); }
void glNormalStream3dATI(GLenum stream, GLdouble nx, GLdouble ny, GLdouble nz) { functions()->glNormalStream3dATI(stream, nx, ny, nz); }
void glNormalStream3dvATI(GLenum stream, const GLdouble* coords) { functions()->glNormalStream3dvATI(stream, coords); }
void glNormalStream3fATI(GLenum stream, GLfloat nx, GLfloat ny, GLfloat nz) { functions()->glNormalStream3fATI(stream, nx, ny, nz); }
void glNormalStream3fvATI(GLenum stream, const GLfloat* coords) { functions()->glNormalStream3fvATI(stream, coords); }
void glNormalStream3iATI(GLenum stream, GLint nx, GLint ny, GLint nz) { functions()->glNormalStream3iATI(stream, nx, ny, nz); }
void glNormalStream3ivATI(GLenum stream, const GLint* coords) { functions()->glNormalStream3ivATI(stream, coords); }
void glNormalStream3sATI(GLenum stream, GLshort nx, GLshort ny, GLshort nz) { functions()->glNormalStream3sATI(stream, nx, ny, nz); }
void glNormalStream3svATI(GLenum stream, const GLshort* coords) { functions()->glNormalStream3svATI(stream, coords); }
void glObjectLabel(GLenum identifier, GLuint name, GLsizei length, const GLchar* label) { functions()->glObjectLabel(identifier, name, length, label); }
void glObjectPtrLabel(const void* ptr, GLsizei length, const GLchar* label) { functions()->glObjectPtrLabel(ptr, length, label); }
void glOrthofOES(GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f) { functions()->glOrthofOES(l, r, b, t, n, f); }
void glOrtho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near_val, GLdouble far_val) { functions()->glOrtho(left, right, bottom, top, near_val, far_val); }
void glOrthoxOES(GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f) { functions()->glOrthoxOES(l, r, b, t, n, f); }
void glPassTexCoordATI(GLuint dst, GLuint coord, GLenum swizzle) { functions()->glPassTexCoordATI(dst, coord, swizzle); }
void glPassThrough(GLfloat token) { functions()->glPassThrough(token); }
void glPassThroughxOES(GLfixed token) { functions()->glPassThroughxOES(token); }
void glPatchParameterfv(GLenum pname, const GLfloat* values) { functions()->glPatchParameterfv(pname, values); }
void glPatchParameteri(GLenum pname, GLint value) { functions()->glPatchParameteri(pname, value); }
void glPathColorGenNV(GLenum color, GLenum genMode, GLenum colorFormat, const GLfloat* coeffs) { functions()->glPathColorGenNV(color, genMode, colorFormat, coeffs); }
void glPathCommandsNV(GLuint path, GLsizei numCommands, const GLubyte* commands, GLsizei numCoords, GLenum coordType, const void* coords) { functions()->glPathCommandsNV(path, numCommands, commands, numCoords, coordType, coords); }
void glPathCoordsNV(GLuint path, GLsizei numCoords, GLenum coordType, const void* coords) { functions()->glPathCoordsNV(path, numCoords, coordType, coords); }
void glPathCoverDepthFuncNV(GLenum func) { functions()->glPathCoverDepthFuncNV(func); }
void glPathDashArrayNV(GLuint path, GLsizei dashCount, const GLfloat* dashArray) { functions()->glPathDashArrayNV(path, dashCount, dashArray); }
void glPathFogGenNV(GLenum genMode) { functions()->glPathFogGenNV(genMode); }
void glPathGlyphRangeNV(GLuint firstPathName, GLenum fontTarget, const void* fontName, GLbitfield fontStyle, GLuint firstGlyph, GLsizei numGlyphs, GLenum handleMissingGlyphs, GLuint pathParameterTemplate, GLfloat emScale) { functions()->glPathGlyphRangeNV(firstPathName, fontTarget, fontName, fontStyle, firstGlyph, numGlyphs, handleMissingGlyphs, pathParameterTemplate, emScale); }
void glPathGlyphsNV(GLuint firstPathName, GLenum fontTarget, const void* fontName, GLbitfield fontStyle, GLsizei numGlyphs, GLenum type, const void* charcodes, GLenum handleMissingGlyphs, GLuint pathParameterTemplate, GLfloat emScale) { functions()->glPathGlyphsNV(firstPathName, fontTarget, fontName, fontStyle, numGlyphs, type, charcodes, handleMissingGlyphs, pathParameterTemplate, emScale); }
void glPathParameterfNV(GLuint path, GLenum pname, GLfloat value) { functions()->glPathParameterfNV(path, pname, value); }
void glPathParameterfvNV(GLuint path, GLenum pname, const GLfloat* value) { functions()->glPathParameterfvNV(path, pname, value); }
void glPathParameteriNV(GLuint path, GLenum pname, GLint value) { functions()->glPathParameteriNV(path, pname, value); }
void glPathParameterivNV(GLuint path, GLenum pname, const GLint* value) { functions()->glPathParameterivNV(path, pname, value); }
void glPathStencilDepthOffsetNV(GLfloat factor, GLfloat units) { functions()->glPathStencilDepthOffsetNV(factor, units); }
void glPathStencilFuncNV(GLenum func, GLint ref, GLuint mask) { functions()->glPathStencilFuncNV(func, ref, mask); }
void glPathStringNV(GLuint path, GLenum format, GLsizei length, const void* pathString) { functions()->glPathStringNV(path, format, length, pathString); }
void glPathSubCommandsNV(GLuint path, GLsizei commandStart, GLsizei commandsToDelete, GLsizei numCommands, const GLubyte* commands, GLsizei numCoords, GLenum coordType, const void* coords) { functions()->glPathSubCommandsNV(path, commandStart, commandsToDelete, numCommands, commands, numCoords, coordType, coords); }
void glPathSubCoordsNV(GLuint path, GLsizei coordStart, GLsizei numCoords, GLenum coordType, const void* coords) { functions()->glPathSubCoordsNV(path, coordStart, numCoords, coordType, coords); }
void glPathTexGenNV(GLenum texCoordSet, GLenum genMode, GLint components, const GLfloat* coeffs) { functions()->glPathTexGenNV(texCoordSet, genMode, components, coeffs); }
void glPauseTransformFeedback() { functions()->glPauseTransformFeedback(); }
void glPauseTransformFeedbackNV() { functions()->glPauseTransformFeedbackNV(); }
void glPixelDataRangeNV(GLenum target, GLsizei length, const void* pointer) { functions()->glPixelDataRangeNV(target, length, pointer); }
void glPixelMapfv(GLenum map, GLsizei mapsize, const GLfloat* values) { functions()->glPixelMapfv(map, mapsize, values); }
void glPixelMapuiv(GLenum map, GLsizei mapsize, const GLuint* values) { functions()->glPixelMapuiv(map, mapsize, values); }
void glPixelMapusv(GLenum map, GLsizei mapsize, const GLushort* values) { functions()->glPixelMapusv(map, mapsize, values); }
void glPixelMapx(GLenum map, GLint size, const GLfixed* values) { functions()->glPixelMapx(map, size, values); }
void glPixelStoref(GLenum pname, GLfloat param) { functions()->glPixelStoref(pname, param); }
void glPixelStorei(GLenum pname, GLint param) { functions()->glPixelStorei(pname, param); }
void glPixelStorex(GLenum pname, GLfixed param) { functions()->glPixelStorex(pname, param); }
void glPixelTexGenParameterfSGIS(GLenum pname, GLfloat param) { functions()->glPixelTexGenParameterfSGIS(pname, param); }
void glPixelTexGenParameterfvSGIS(GLenum pname, const GLfloat* params) { functions()->glPixelTexGenParameterfvSGIS(pname, params); }
void glPixelTexGenParameteriSGIS(GLenum pname, GLint param) { functions()->glPixelTexGenParameteriSGIS(pname, param); }
void glPixelTexGenParameterivSGIS(GLenum pname, const GLint* params) { functions()->glPixelTexGenParameterivSGIS(pname, params); }
void glPixelTexGenSGIX(GLenum mode) { functions()->glPixelTexGenSGIX(mode); }
void glPixelTransferf(GLenum pname, GLfloat param) { functions()->glPixelTransferf(pname, param); }
void glPixelTransferi(GLenum pname, GLint param) { functions()->glPixelTransferi(pname, param); }
void glPixelTransferxOES(GLenum pname, GLfixed param) { functions()->glPixelTransferxOES(pname, param); }
void glPixelTransformParameterfEXT(GLenum target, GLenum pname, GLfloat param) { functions()->glPixelTransformParameterfEXT(target, pname, param); }
void glPixelTransformParameterfvEXT(GLenum target, GLenum pname, const GLfloat* params) { functions()->glPixelTransformParameterfvEXT(target, pname, params); }
void glPixelTransformParameteriEXT(GLenum target, GLenum pname, GLint param) { functions()->glPixelTransformParameteriEXT(target, pname, param); }
void glPixelTransformParameterivEXT(GLenum target, GLenum pname, const GLint* params) { functions()->glPixelTransformParameterivEXT(target, pname, params); }
void glPixelZoom(GLfloat xfactor, GLfloat yfactor) { functions()->glPixelZoom(xfactor, yfactor); }
void glPixelZoomxOES(GLfixed xfactor, GLfixed yfactor) { functions()->glPixelZoomxOES(xfactor, yfactor); }
void glPNTrianglesfATI(GLenum pname, GLfloat param) { functions()->glPNTrianglesfATI(pname, param); }
void glPNTrianglesiATI(GLenum pname, GLint param) { functions()->glPNTrianglesiATI(pname, param); }
void glPointParameterfARB(GLenum pname, GLfloat param) { functions()->glPointParameterfARB(pname, param); }
void glPointParameterfEXT(GLenum pname, GLfloat param) { functions()->glPointParameterfEXT(pname, param); }
void glPointParameterf(GLenum pname, GLfloat param) { functions()->glPointParameterf(pname, param); }
void glPointParameterfSGIS(GLenum pname, GLfloat param) { functions()->glPointParameterfSGIS(pname, param); }
void glPointParameterfvARB(GLenum pname, const GLfloat* params) { functions()->glPointParameterfvARB(pname, params); }
void glPointParameterfvEXT(GLenum pname, const GLfloat* params) { functions()->glPointParameterfvEXT(pname, params); }
void glPointParameterfv(GLenum pname, const GLfloat* params) { functions()->glPointParameterfv(pname, params); }
void glPointParameterfvSGIS(GLenum pname, const GLfloat* params) { functions()->glPointParameterfvSGIS(pname, params); }
void glPointParameteri(GLenum pname, GLint param) { functions()->glPointParameteri(pname, param); }
void glPointParameteriNV(GLenum pname, GLint param) { functions()->glPointParameteriNV(pname, param); }
void glPointParameteriv(GLenum pname, const GLint* params) { functions()->glPointParameteriv(pname, params); }
void glPointParameterivNV(GLenum pname, const GLint* params) { functions()->glPointParameterivNV(pname, params); }
void glPointParameterxvOES(GLenum pname, const GLfixed* params) { functions()->glPointParameterxvOES(pname, params); }
void glPointSize(GLfloat size) { functions()->glPointSize(size); }
void glPointSizexOES(GLfixed size) { functions()->glPointSizexOES(size); }
void glPolygonMode(GLenum face, GLenum mode) { functions()->glPolygonMode(face, mode); }
void glPolygonOffsetClampEXT(GLfloat factor, GLfloat units, GLfloat clamp) { functions()->glPolygonOffsetClampEXT(factor, units, clamp); }
void glPolygonOffsetEXT(GLfloat factor, GLfloat bias) { functions()->glPolygonOffsetEXT(factor, bias); }
void glPolygonOffset(GLfloat factor, GLfloat units) { functions()->glPolygonOffset(factor, units); }
void glPolygonOffsetxOES(GLfixed factor, GLfixed units) { functions()->glPolygonOffsetxOES(factor, units); }
void glPolygonStipple(const GLubyte* mask) { functions()->glPolygonStipple(mask); }
void glPopAttrib() { functions()->glPopAttrib(); }
void glPopClientAttrib() { functions()->glPopClientAttrib(); }
void glPopDebugGroup() { functions()->glPopDebugGroup(); }
void glPopGroupMarkerEXT() { functions()->glPopGroupMarkerEXT(); }
void glPopMatrix() { functions()->glPopMatrix(); }
void glPopName() { functions()->glPopName(); }
void glPresentFrameDualFillNV(GLuint video_slot, GLuint64EXT minPresentTime, GLuint beginPresentTimeId, GLuint presentDurationId, GLenum type, GLenum target0, GLuint fill0, GLenum target1, GLuint fill1, GLenum target2, GLuint fill2, GLenum target3, GLuint fill3) { functions()->glPresentFrameDualFillNV(video_slot, minPresentTime, beginPresentTimeId, presentDurationId, type, target0, fill0, target1, fill1, target2, fill2, target3, fill3); }
void glPresentFrameKeyedNV(GLuint video_slot, GLuint64EXT minPresentTime, GLuint beginPresentTimeId, GLuint presentDurationId, GLenum type, GLenum target0, GLuint fill0, GLuint key0, GLenum target1, GLuint fill1, GLuint key1) { functions()->glPresentFrameKeyedNV(video_slot, minPresentTime, beginPresentTimeId, presentDurationId, type, target0, fill0, key0, target1, fill1, key1); }
void glPrimitiveBoundingBoxARB(GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW) { functions()->glPrimitiveBoundingBoxARB(minX, minY, minZ, minW, maxX, maxY, maxZ, maxW); }
void glPrimitiveRestartIndex(GLuint index) { functions()->glPrimitiveRestartIndex(index); }
void glPrimitiveRestartIndexNV(GLuint index) { functions()->glPrimitiveRestartIndexNV(index); }
void glPrimitiveRestartNV() { functions()->glPrimitiveRestartNV(); }
void glPrioritizeTexturesEXT(GLsizei n, const GLuint* textures, const GLclampf* priorities) { functions()->glPrioritizeTexturesEXT(n, textures, priorities); }
void glPrioritizeTextures(GLsizei n, const GLuint* textures, const GLclampf* priorities) { functions()->glPrioritizeTextures(n, textures, priorities); }
void glPrioritizeTexturesxOES(GLsizei n, const GLuint* textures, const GLfixed* priorities) { functions()->glPrioritizeTexturesxOES(n, textures, priorities); }
void glProgramBinary(GLuint program, GLenum binaryFormat, const void* binary, GLsizei length) { functions()->glProgramBinary(program, binaryFormat, binary, length); }
void glProgramBufferParametersfvNV(GLenum target, GLuint bindingIndex, GLuint wordIndex, GLsizei count, const GLfloat* params) { functions()->glProgramBufferParametersfvNV(target, bindingIndex, wordIndex, count, params); }
void glProgramBufferParametersIivNV(GLenum target, GLuint bindingIndex, GLuint wordIndex, GLsizei count, const GLint* params) { functions()->glProgramBufferParametersIivNV(target, bindingIndex, wordIndex, count, params); }
void glProgramBufferParametersIuivNV(GLenum target, GLuint bindingIndex, GLuint wordIndex, GLsizei count, const GLuint* params) { functions()->glProgramBufferParametersIuivNV(target, bindingIndex, wordIndex, count, params); }
void glProgramEnvParameter4dARB(GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) { functions()->glProgramEnvParameter4dARB(target, index, x, y, z, w); }
void glProgramEnvParameter4dvARB(GLenum target, GLuint index, const GLdouble* params) { functions()->glProgramEnvParameter4dvARB(target, index, params); }
void glProgramEnvParameter4fARB(GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) { functions()->glProgramEnvParameter4fARB(target, index, x, y, z, w); }
void glProgramEnvParameter4fvARB(GLenum target, GLuint index, const GLfloat* params) { functions()->glProgramEnvParameter4fvARB(target, index, params); }
void glProgramEnvParameterI4iNV(GLenum target, GLuint index, GLint x, GLint y, GLint z, GLint w) { functions()->glProgramEnvParameterI4iNV(target, index, x, y, z, w); }
void glProgramEnvParameterI4ivNV(GLenum target, GLuint index, const GLint* params) { functions()->glProgramEnvParameterI4ivNV(target, index, params); }
void glProgramEnvParameterI4uiNV(GLenum target, GLuint index, GLuint x, GLuint y, GLuint z, GLuint w) { functions()->glProgramEnvParameterI4uiNV(target, index, x, y, z, w); }
void glProgramEnvParameterI4uivNV(GLenum target, GLuint index, const GLuint* params) { functions()->glProgramEnvParameterI4uivNV(target, index, params); }
void glProgramEnvParameters4fvEXT(GLenum target, GLuint index, GLsizei count, const GLfloat* params) { functions()->glProgramEnvParameters4fvEXT(target, index, count, params); }
void glProgramEnvParametersI4ivNV(GLenum target, GLuint index, GLsizei count, const GLint* params) { functions()->glProgramEnvParametersI4ivNV(target, index, count, params); }
void glProgramEnvParametersI4uivNV(GLenum target, GLuint index, GLsizei count, const GLuint* params) { functions()->glProgramEnvParametersI4uivNV(target, index, count, params); }
void glProgramLocalParameter4dARB(GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) { functions()->glProgramLocalParameter4dARB(target, index, x, y, z, w); }
void glProgramLocalParameter4dvARB(GLenum target, GLuint index, const GLdouble* params) { functions()->glProgramLocalParameter4dvARB(target, index, params); }
void glProgramLocalParameter4fARB(GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) { functions()->glProgramLocalParameter4fARB(target, index, x, y, z, w); }
void glProgramLocalParameter4fvARB(GLenum target, GLuint index, const GLfloat* params) { functions()->glProgramLocalParameter4fvARB(target, index, params); }
void glProgramLocalParameterI4iNV(GLenum target, GLuint index, GLint x, GLint y, GLint z, GLint w) { functions()->glProgramLocalParameterI4iNV(target, index, x, y, z, w); }
void glProgramLocalParameterI4ivNV(GLenum target, GLuint index, const GLint* params) { functions()->glProgramLocalParameterI4ivNV(target, index, params); }
void glProgramLocalParameterI4uiNV(GLenum target, GLuint index, GLuint x, GLuint y, GLuint z, GLuint w) { functions()->glProgramLocalParameterI4uiNV(target, index, x, y, z, w); }
void glProgramLocalParameterI4uivNV(GLenum target, GLuint index, const GLuint* params) { functions()->glProgramLocalParameterI4uivNV(target, index, params); }
void glProgramLocalParameters4fvEXT(GLenum target, GLuint index, GLsizei count, const GLfloat* params) { functions()->glProgramLocalParameters4fvEXT(target, index, count, params); }
void glProgramLocalParametersI4ivNV(GLenum target, GLuint index, GLsizei count, const GLint* params) { functions()->glProgramLocalParametersI4ivNV(target, index, count, params); }
void glProgramLocalParametersI4uivNV(GLenum target, GLuint index, GLsizei count, const GLuint* params) { functions()->glProgramLocalParametersI4uivNV(target, index, count, params); }
void glProgramNamedParameter4dNV(GLuint id, GLsizei len, const GLubyte* name, GLdouble x, GLdouble y, GLdouble z, GLdouble w) { functions()->glProgramNamedParameter4dNV(id, len, name, x, y, z, w); }
void glProgramNamedParameter4dvNV(GLuint id, GLsizei len, const GLubyte* name, const GLdouble* v) { functions()->glProgramNamedParameter4dvNV(id, len, name, v); }
void glProgramNamedParameter4fNV(GLuint id, GLsizei len, const GLubyte* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w) { functions()->glProgramNamedParameter4fNV(id, len, name, x, y, z, w); }
void glProgramNamedParameter4fvNV(GLuint id, GLsizei len, const GLubyte* name, const GLfloat* v) { functions()->glProgramNamedParameter4fvNV(id, len, name, v); }
void glProgramParameter4dNV(GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) { functions()->glProgramParameter4dNV(target, index, x, y, z, w); }
void glProgramParameter4dvNV(GLenum target, GLuint index, const GLdouble* v) { functions()->glProgramParameter4dvNV(target, index, v); }
void glProgramParameter4fNV(GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) { functions()->glProgramParameter4fNV(target, index, x, y, z, w); }
void glProgramParameter4fvNV(GLenum target, GLuint index, const GLfloat* v) { functions()->glProgramParameter4fvNV(target, index, v); }
void glProgramParameteriARB(GLuint program, GLenum pname, GLint value) { functions()->glProgramParameteriARB(program, pname, value); }
void glProgramParameteriEXT(GLuint program, GLenum pname, GLint value) { functions()->glProgramParameteriEXT(program, pname, value); }
void glProgramParameteri(GLuint program, GLenum pname, GLint value) { functions()->glProgramParameteri(program, pname, value); }
void glProgramParameters4dvNV(GLenum target, GLuint index, GLsizei count, const GLdouble* v) { functions()->glProgramParameters4dvNV(target, index, count, v); }
void glProgramParameters4fvNV(GLenum target, GLuint index, GLsizei count, const GLfloat* v) { functions()->glProgramParameters4fvNV(target, index, count, v); }
void glProgramPathFragmentInputGenNV(GLuint program, GLint location, GLenum genMode, GLint components, const GLfloat* coeffs) { functions()->glProgramPathFragmentInputGenNV(program, location, genMode, components, coeffs); }
void glProgramStringARB(GLenum target, GLenum format, GLsizei len, const void* string) { functions()->glProgramStringARB(target, format, len, string); }
void glProgramSubroutineParametersuivNV(GLenum target, GLsizei count, const GLuint* params) { functions()->glProgramSubroutineParametersuivNV(target, count, params); }
void glProgramUniform1dEXT(GLuint program, GLint location, GLdouble x) { functions()->glProgramUniform1dEXT(program, location, x); }
void glProgramUniform1d(GLuint program, GLint location, GLdouble v0) { functions()->glProgramUniform1d(program, location, v0); }
void glProgramUniform1dvEXT(GLuint program, GLint location, GLsizei count, const GLdouble* value) { functions()->glProgramUniform1dvEXT(program, location, count, value); }
void glProgramUniform1dv(GLuint program, GLint location, GLsizei count, const GLdouble* value) { functions()->glProgramUniform1dv(program, location, count, value); }
void glProgramUniform1fEXT(GLuint program, GLint location, GLfloat v0) { functions()->glProgramUniform1fEXT(program, location, v0); }
void glProgramUniform1f(GLuint program, GLint location, GLfloat v0) { functions()->glProgramUniform1f(program, location, v0); }
void glProgramUniform1fvEXT(GLuint program, GLint location, GLsizei count, const GLfloat* value) { functions()->glProgramUniform1fvEXT(program, location, count, value); }
void glProgramUniform1fv(GLuint program, GLint location, GLsizei count, const GLfloat* value) { functions()->glProgramUniform1fv(program, location, count, value); }
void glProgramUniform1i64ARB(GLuint program, GLint location, GLint64 x) { functions()->glProgramUniform1i64ARB(program, location, x); }
void glProgramUniform1i64NV(GLuint program, GLint location, GLint64EXT x) { functions()->glProgramUniform1i64NV(program, location, x); }
void glProgramUniform1i64vARB(GLuint program, GLint location, GLsizei count, const GLint64* value) { functions()->glProgramUniform1i64vARB(program, location, count, value); }
void glProgramUniform1i64vNV(GLuint program, GLint location, GLsizei count, const GLint64EXT* value) { functions()->glProgramUniform1i64vNV(program, location, count, value); }
void glProgramUniform1iEXT(GLuint program, GLint location, GLint v0) { functions()->glProgramUniform1iEXT(program, location, v0); }
void glProgramUniform1i(GLuint program, GLint location, GLint v0) { functions()->glProgramUniform1i(program, location, v0); }
void glProgramUniform1ivEXT(GLuint program, GLint location, GLsizei count, const GLint* value) { functions()->glProgramUniform1ivEXT(program, location, count, value); }
void glProgramUniform1iv(GLuint program, GLint location, GLsizei count, const GLint* value) { functions()->glProgramUniform1iv(program, location, count, value); }
void glProgramUniform1ui64ARB(GLuint program, GLint location, GLuint64 x) { functions()->glProgramUniform1ui64ARB(program, location, x); }
void glProgramUniform1ui64NV(GLuint program, GLint location, GLuint64EXT x) { functions()->glProgramUniform1ui64NV(program, location, x); }
void glProgramUniform1ui64vARB(GLuint program, GLint location, GLsizei count, const GLuint64* value) { functions()->glProgramUniform1ui64vARB(program, location, count, value); }
void glProgramUniform1ui64vNV(GLuint program, GLint location, GLsizei count, const GLuint64EXT* value) { functions()->glProgramUniform1ui64vNV(program, location, count, value); }
void glProgramUniform1uiEXT(GLuint program, GLint location, GLuint v0) { functions()->glProgramUniform1uiEXT(program, location, v0); }
void glProgramUniform1ui(GLuint program, GLint location, GLuint v0) { functions()->glProgramUniform1ui(program, location, v0); }
void glProgramUniform1uivEXT(GLuint program, GLint location, GLsizei count, const GLuint* value) { functions()->glProgramUniform1uivEXT(program, location, count, value); }
void glProgramUniform1uiv(GLuint program, GLint location, GLsizei count, const GLuint* value) { functions()->glProgramUniform1uiv(program, location, count, value); }
void glProgramUniform2dEXT(GLuint program, GLint location, GLdouble x, GLdouble y) { functions()->glProgramUniform2dEXT(program, location, x, y); }
void glProgramUniform2d(GLuint program, GLint location, GLdouble v0, GLdouble v1) { functions()->glProgramUniform2d(program, location, v0, v1); }
void glProgramUniform2dvEXT(GLuint program, GLint location, GLsizei count, const GLdouble* value) { functions()->glProgramUniform2dvEXT(program, location, count, value); }
void glProgramUniform2dv(GLuint program, GLint location, GLsizei count, const GLdouble* value) { functions()->glProgramUniform2dv(program, location, count, value); }
void glProgramUniform2fEXT(GLuint program, GLint location, GLfloat v0, GLfloat v1) { functions()->glProgramUniform2fEXT(program, location, v0, v1); }
void glProgramUniform2f(GLuint program, GLint location, GLfloat v0, GLfloat v1) { functions()->glProgramUniform2f(program, location, v0, v1); }
void glProgramUniform2fvEXT(GLuint program, GLint location, GLsizei count, const GLfloat* value) { functions()->glProgramUniform2fvEXT(program, location, count, value); }
void glProgramUniform2fv(GLuint program, GLint location, GLsizei count, const GLfloat* value) { functions()->glProgramUniform2fv(program, location, count, value); }
void glProgramUniform2i64ARB(GLuint program, GLint location, GLint64 x, GLint64 y) { functions()->glProgramUniform2i64ARB(program, location, x, y); }
void glProgramUniform2i64NV(GLuint program, GLint location, GLint64EXT x, GLint64EXT y) { functions()->glProgramUniform2i64NV(program, location, x, y); }
void glProgramUniform2i64vARB(GLuint program, GLint location, GLsizei count, const GLint64* value) { functions()->glProgramUniform2i64vARB(program, location, count, value); }
void glProgramUniform2i64vNV(GLuint program, GLint location, GLsizei count, const GLint64EXT* value) { functions()->glProgramUniform2i64vNV(program, location, count, value); }
void glProgramUniform2iEXT(GLuint program, GLint location, GLint v0, GLint v1) { functions()->glProgramUniform2iEXT(program, location, v0, v1); }
void glProgramUniform2i(GLuint program, GLint location, GLint v0, GLint v1) { functions()->glProgramUniform2i(program, location, v0, v1); }
void glProgramUniform2ivEXT(GLuint program, GLint location, GLsizei count, const GLint* value) { functions()->glProgramUniform2ivEXT(program, location, count, value); }
void glProgramUniform2iv(GLuint program, GLint location, GLsizei count, const GLint* value) { functions()->glProgramUniform2iv(program, location, count, value); }
void glProgramUniform2ui64ARB(GLuint program, GLint location, GLuint64 x, GLuint64 y) { functions()->glProgramUniform2ui64ARB(program, location, x, y); }
void glProgramUniform2ui64NV(GLuint program, GLint location, GLuint64EXT x, GLuint64EXT y) { functions()->glProgramUniform2ui64NV(program, location, x, y); }
void glProgramUniform2ui64vARB(GLuint program, GLint location, GLsizei count, const GLuint64* value) { functions()->glProgramUniform2ui64vARB(program, location, count, value); }
void glProgramUniform2ui64vNV(GLuint program, GLint location, GLsizei count, const GLuint64EXT* value) { functions()->glProgramUniform2ui64vNV(program, location, count, value); }
void glProgramUniform2uiEXT(GLuint program, GLint location, GLuint v0, GLuint v1) { functions()->glProgramUniform2uiEXT(program, location, v0, v1); }
void glProgramUniform2ui(GLuint program, GLint location, GLuint v0, GLuint v1) { functions()->glProgramUniform2ui(program, location, v0, v1); }
void glProgramUniform2uivEXT(GLuint program, GLint location, GLsizei count, const GLuint* value) { functions()->glProgramUniform2uivEXT(program, location, count, value); }
void glProgramUniform2uiv(GLuint program, GLint location, GLsizei count, const GLuint* value) { functions()->glProgramUniform2uiv(program, location, count, value); }
void glProgramUniform3dEXT(GLuint program, GLint location, GLdouble x, GLdouble y, GLdouble z) { functions()->glProgramUniform3dEXT(program, location, x, y, z); }
void glProgramUniform3d(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2) { functions()->glProgramUniform3d(program, location, v0, v1, v2); }
void glProgramUniform3dvEXT(GLuint program, GLint location, GLsizei count, const GLdouble* value) { functions()->glProgramUniform3dvEXT(program, location, count, value); }
void glProgramUniform3dv(GLuint program, GLint location, GLsizei count, const GLdouble* value) { functions()->glProgramUniform3dv(program, location, count, value); }
void glProgramUniform3fEXT(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2) { functions()->glProgramUniform3fEXT(program, location, v0, v1, v2); }
void glProgramUniform3f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2) { functions()->glProgramUniform3f(program, location, v0, v1, v2); }
void glProgramUniform3fvEXT(GLuint program, GLint location, GLsizei count, const GLfloat* value) { functions()->glProgramUniform3fvEXT(program, location, count, value); }
void glProgramUniform3fv(GLuint program, GLint location, GLsizei count, const GLfloat* value) { functions()->glProgramUniform3fv(program, location, count, value); }
void glProgramUniform3i64ARB(GLuint program, GLint location, GLint64 x, GLint64 y, GLint64 z) { functions()->glProgramUniform3i64ARB(program, location, x, y, z); }
void glProgramUniform3i64NV(GLuint program, GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z) { functions()->glProgramUniform3i64NV(program, location, x, y, z); }
void glProgramUniform3i64vARB(GLuint program, GLint location, GLsizei count, const GLint64* value) { functions()->glProgramUniform3i64vARB(program, location, count, value); }
void glProgramUniform3i64vNV(GLuint program, GLint location, GLsizei count, const GLint64EXT* value) { functions()->glProgramUniform3i64vNV(program, location, count, value); }
void glProgramUniform3iEXT(GLuint program, GLint location, GLint v0, GLint v1, GLint v2) { functions()->glProgramUniform3iEXT(program, location, v0, v1, v2); }
void glProgramUniform3i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2) { functions()->glProgramUniform3i(program, location, v0, v1, v2); }
void glProgramUniform3ivEXT(GLuint program, GLint location, GLsizei count, const GLint* value) { functions()->glProgramUniform3ivEXT(program, location, count, value); }
void glProgramUniform3iv(GLuint program, GLint location, GLsizei count, const GLint* value) { functions()->glProgramUniform3iv(program, location, count, value); }
void glProgramUniform3ui64ARB(GLuint program, GLint location, GLuint64 x, GLuint64 y, GLuint64 z) { functions()->glProgramUniform3ui64ARB(program, location, x, y, z); }
void glProgramUniform3ui64NV(GLuint program, GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z) { functions()->glProgramUniform3ui64NV(program, location, x, y, z); }
void glProgramUniform3ui64vARB(GLuint program, GLint location, GLsizei count, const GLuint64* value) { functions()->glProgramUniform3ui64vARB(program, location, count, value); }
void glProgramUniform3ui64vNV(GLuint program, GLint location, GLsizei count, const GLuint64EXT* value) { functions()->glProgramUniform3ui64vNV(program, location, count, value); }
void glProgramUniform3uiEXT(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2) { functions()->glProgramUniform3uiEXT(program, location, v0, v1, v2); }
void glProgramUniform3ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2) { functions()->glProgramUniform3ui(program, location, v0, v1, v2); }
void glProgramUniform3uivEXT(GLuint program, GLint location, GLsizei count, const GLuint* value) { functions()->glProgramUniform3uivEXT(program, location, count, value); }
void glProgramUniform3uiv(GLuint program, GLint location, GLsizei count, const GLuint* value) { functions()->glProgramUniform3uiv(program, location, count, value); }
void glProgramUniform4dEXT(GLuint program, GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w) { functions()->glProgramUniform4dEXT(program, location, x, y, z, w); }
void glProgramUniform4d(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3) { functions()->glProgramUniform4d(program, location, v0, v1, v2, v3); }
void glProgramUniform4dvEXT(GLuint program, GLint location, GLsizei count, const GLdouble* value) { functions()->glProgramUniform4dvEXT(program, location, count, value); }
void glProgramUniform4dv(GLuint program, GLint location, GLsizei count, const GLdouble* value) { functions()->glProgramUniform4dv(program, location, count, value); }
void glProgramUniform4fEXT(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) { functions()->glProgramUniform4fEXT(program, location, v0, v1, v2, v3); }
void glProgramUniform4f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) { functions()->glProgramUniform4f(program, location, v0, v1, v2, v3); }
void glProgramUniform4fvEXT(GLuint program, GLint location, GLsizei count, const GLfloat* value) { functions()->glProgramUniform4fvEXT(program, location, count, value); }
void glProgramUniform4fv(GLuint program, GLint location, GLsizei count, const GLfloat* value) { functions()->glProgramUniform4fv(program, location, count, value); }
void glProgramUniform4i64ARB(GLuint program, GLint location, GLint64 x, GLint64 y, GLint64 z, GLint64 w) { functions()->glProgramUniform4i64ARB(program, location, x, y, z, w); }
void glProgramUniform4i64NV(GLuint program, GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w) { functions()->glProgramUniform4i64NV(program, location, x, y, z, w); }
void glProgramUniform4i64vARB(GLuint program, GLint location, GLsizei count, const GLint64* value) { functions()->glProgramUniform4i64vARB(program, location, count, value); }
void glProgramUniform4i64vNV(GLuint program, GLint location, GLsizei count, const GLint64EXT* value) { functions()->glProgramUniform4i64vNV(program, location, count, value); }
void glProgramUniform4iEXT(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3) { functions()->glProgramUniform4iEXT(program, location, v0, v1, v2, v3); }
void glProgramUniform4i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3) { functions()->glProgramUniform4i(program, location, v0, v1, v2, v3); }
void glProgramUniform4ivEXT(GLuint program, GLint location, GLsizei count, const GLint* value) { functions()->glProgramUniform4ivEXT(program, location, count, value); }
void glProgramUniform4iv(GLuint program, GLint location, GLsizei count, const GLint* value) { functions()->glProgramUniform4iv(program, location, count, value); }
void glProgramUniform4ui64ARB(GLuint program, GLint location, GLuint64 x, GLuint64 y, GLuint64 z, GLuint64 w) { functions()->glProgramUniform4ui64ARB(program, location, x, y, z, w); }
void glProgramUniform4ui64NV(GLuint program, GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w) { functions()->glProgramUniform4ui64NV(program, location, x, y, z, w); }
void glProgramUniform4ui64vARB(GLuint program, GLint location, GLsizei count, const GLuint64* value) { functions()->glProgramUniform4ui64vARB(program, location, count, value); }
void glProgramUniform4ui64vNV(GLuint program, GLint location, GLsizei count, const GLuint64EXT* value) { functions()->glProgramUniform4ui64vNV(program, location, count, value); }
void glProgramUniform4uiEXT(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3) { functions()->glProgramUniform4uiEXT(program, location, v0, v1, v2, v3); }
void glProgramUniform4ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3) { functions()->glProgramUniform4ui(program, location, v0, v1, v2, v3); }
void glProgramUniform4uivEXT(GLuint program, GLint location, GLsizei count, const GLuint* value) { functions()->glProgramUniform4uivEXT(program, location, count, value); }
void glProgramUniform4uiv(GLuint program, GLint location, GLsizei count, const GLuint* value) { functions()->glProgramUniform4uiv(program, location, count, value); }
void glProgramUniformHandleui64ARB(GLuint program, GLint location, GLuint64 value) { functions()->glProgramUniformHandleui64ARB(program, location, value); }
void glProgramUniformHandleui64NV(GLuint program, GLint location, GLuint64 value) { functions()->glProgramUniformHandleui64NV(program, location, value); }
void glProgramUniformHandleui64vARB(GLuint program, GLint location, GLsizei count, const GLuint64* values) { functions()->glProgramUniformHandleui64vARB(program, location, count, values); }
void glProgramUniformHandleui64vNV(GLuint program, GLint location, GLsizei count, const GLuint64* values) { functions()->glProgramUniformHandleui64vNV(program, location, count, values); }
void glProgramUniformMatrix2dvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) { functions()->glProgramUniformMatrix2dvEXT(program, location, count, transpose, value); }
void glProgramUniformMatrix2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) { functions()->glProgramUniformMatrix2dv(program, location, count, transpose, value); }
void glProgramUniformMatrix2fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) { functions()->glProgramUniformMatrix2fvEXT(program, location, count, transpose, value); }
void glProgramUniformMatrix2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) { functions()->glProgramUniformMatrix2fv(program, location, count, transpose, value); }
void glProgramUniformMatrix2x3dvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) { functions()->glProgramUniformMatrix2x3dvEXT(program, location, count, transpose, value); }
void glProgramUniformMatrix2x3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) { functions()->glProgramUniformMatrix2x3dv(program, location, count, transpose, value); }
void glProgramUniformMatrix2x3fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) { functions()->glProgramUniformMatrix2x3fvEXT(program, location, count, transpose, value); }
void glProgramUniformMatrix2x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) { functions()->glProgramUniformMatrix2x3fv(program, location, count, transpose, value); }
void glProgramUniformMatrix2x4dvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) { functions()->glProgramUniformMatrix2x4dvEXT(program, location, count, transpose, value); }
void glProgramUniformMatrix2x4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) { functions()->glProgramUniformMatrix2x4dv(program, location, count, transpose, value); }
void glProgramUniformMatrix2x4fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) { functions()->glProgramUniformMatrix2x4fvEXT(program, location, count, transpose, value); }
void glProgramUniformMatrix2x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) { functions()->glProgramUniformMatrix2x4fv(program, location, count, transpose, value); }
void glProgramUniformMatrix3dvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) { functions()->glProgramUniformMatrix3dvEXT(program, location, count, transpose, value); }
void glProgramUniformMatrix3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) { functions()->glProgramUniformMatrix3dv(program, location, count, transpose, value); }
void glProgramUniformMatrix3fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) { functions()->glProgramUniformMatrix3fvEXT(program, location, count, transpose, value); }
void glProgramUniformMatrix3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) { functions()->glProgramUniformMatrix3fv(program, location, count, transpose, value); }
void glProgramUniformMatrix3x2dvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) { functions()->glProgramUniformMatrix3x2dvEXT(program, location, count, transpose, value); }
void glProgramUniformMatrix3x2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) { functions()->glProgramUniformMatrix3x2dv(program, location, count, transpose, value); }
void glProgramUniformMatrix3x2fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) { functions()->glProgramUniformMatrix3x2fvEXT(program, location, count, transpose, value); }
void glProgramUniformMatrix3x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) { functions()->glProgramUniformMatrix3x2fv(program, location, count, transpose, value); }
void glProgramUniformMatrix3x4dvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) { functions()->glProgramUniformMatrix3x4dvEXT(program, location, count, transpose, value); }
void glProgramUniformMatrix3x4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) { functions()->glProgramUniformMatrix3x4dv(program, location, count, transpose, value); }
void glProgramUniformMatrix3x4fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) { functions()->glProgramUniformMatrix3x4fvEXT(program, location, count, transpose, value); }
void glProgramUniformMatrix3x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) { functions()->glProgramUniformMatrix3x4fv(program, location, count, transpose, value); }
void glProgramUniformMatrix4dvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) { functions()->glProgramUniformMatrix4dvEXT(program, location, count, transpose, value); }
void glProgramUniformMatrix4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) { functions()->glProgramUniformMatrix4dv(program, location, count, transpose, value); }
void glProgramUniformMatrix4fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) { functions()->glProgramUniformMatrix4fvEXT(program, location, count, transpose, value); }
void glProgramUniformMatrix4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) { functions()->glProgramUniformMatrix4fv(program, location, count, transpose, value); }
void glProgramUniformMatrix4x2dvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) { functions()->glProgramUniformMatrix4x2dvEXT(program, location, count, transpose, value); }
void glProgramUniformMatrix4x2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) { functions()->glProgramUniformMatrix4x2dv(program, location, count, transpose, value); }
void glProgramUniformMatrix4x2fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) { functions()->glProgramUniformMatrix4x2fvEXT(program, location, count, transpose, value); }
void glProgramUniformMatrix4x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) { functions()->glProgramUniformMatrix4x2fv(program, location, count, transpose, value); }
void glProgramUniformMatrix4x3dvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) { functions()->glProgramUniformMatrix4x3dvEXT(program, location, count, transpose, value); }
void glProgramUniformMatrix4x3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) { functions()->glProgramUniformMatrix4x3dv(program, location, count, transpose, value); }
void glProgramUniformMatrix4x3fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) { functions()->glProgramUniformMatrix4x3fvEXT(program, location, count, transpose, value); }
void glProgramUniformMatrix4x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) { functions()->glProgramUniformMatrix4x3fv(program, location, count, transpose, value); }
void glProgramUniformui64NV(GLuint program, GLint location, GLuint64EXT value) { functions()->glProgramUniformui64NV(program, location, value); }
void glProgramUniformui64vNV(GLuint program, GLint location, GLsizei count, const GLuint64EXT* value) { functions()->glProgramUniformui64vNV(program, location, count, value); }
void glProgramVertexLimitNV(GLenum target, GLint limit) { functions()->glProgramVertexLimitNV(target, limit); }
void glProvokingVertexEXT(GLenum mode) { functions()->glProvokingVertexEXT(mode); }
void glProvokingVertex(GLenum mode) { functions()->glProvokingVertex(mode); }
void glPushAttrib(GLbitfield mask) { functions()->glPushAttrib(mask); }
void glPushClientAttribDefaultEXT(GLbitfield mask) { functions()->glPushClientAttribDefaultEXT(mask); }
void glPushClientAttrib(GLbitfield mask) { functions()->glPushClientAttrib(mask); }
void glPushDebugGroup(GLenum source, GLuint id, GLsizei length, const GLchar* message) { functions()->glPushDebugGroup(source, id, length, message); }
void glPushGroupMarkerEXT(GLsizei length, const GLchar* marker) { functions()->glPushGroupMarkerEXT(length, marker); }
void glPushMatrix() { functions()->glPushMatrix(); }
void glPushName(GLuint name) { functions()->glPushName(name); }
void glQueryCounter(GLuint id, GLenum target) { functions()->glQueryCounter(id, target); }
void glQueryObjectParameteruiAMD(GLenum target, GLuint id, GLenum pname, GLuint param) { functions()->glQueryObjectParameteruiAMD(target, id, pname, param); }
void glRasterPos2d(GLdouble x, GLdouble y) { functions()->glRasterPos2d(x, y); }
void glRasterPos2dv(const GLdouble* v) { functions()->glRasterPos2dv(v); }
void glRasterPos2f(GLfloat x, GLfloat y) { functions()->glRasterPos2f(x, y); }
void glRasterPos2fv(const GLfloat* v) { functions()->glRasterPos2fv(v); }
void glRasterPos2i(GLint x, GLint y) { functions()->glRasterPos2i(x, y); }
void glRasterPos2iv(const GLint* v) { functions()->glRasterPos2iv(v); }
void glRasterPos2s(GLshort x, GLshort y) { functions()->glRasterPos2s(x, y); }
void glRasterPos2sv(const GLshort* v) { functions()->glRasterPos2sv(v); }
void glRasterPos2xOES(GLfixed x, GLfixed y) { functions()->glRasterPos2xOES(x, y); }
void glRasterPos2xvOES(const GLfixed* coords) { functions()->glRasterPos2xvOES(coords); }
void glRasterPos3d(GLdouble x, GLdouble y, GLdouble z) { functions()->glRasterPos3d(x, y, z); }
void glRasterPos3dv(const GLdouble* v) { functions()->glRasterPos3dv(v); }
void glRasterPos3f(GLfloat x, GLfloat y, GLfloat z) { functions()->glRasterPos3f(x, y, z); }
void glRasterPos3fv(const GLfloat* v) { functions()->glRasterPos3fv(v); }
void glRasterPos3i(GLint x, GLint y, GLint z) { functions()->glRasterPos3i(x, y, z); }
void glRasterPos3iv(const GLint* v) { functions()->glRasterPos3iv(v); }
void glRasterPos3s(GLshort x, GLshort y, GLshort z) { functions()->glRasterPos3s(x, y, z); }
void glRasterPos3sv(const GLshort* v) { functions()->glRasterPos3sv(v); }
void glRasterPos3xOES(GLfixed x, GLfixed y, GLfixed z) { functions()->glRasterPos3xOES(x, y, z); }
void glRasterPos3xvOES(const GLfixed* coords) { functions()->glRasterPos3xvOES(coords); }
void glRasterPos4d(GLdouble x, GLdouble y, GLdouble z, GLdouble w) { functions()->glRasterPos4d(x, y, z, w); }
void glRasterPos4dv(const GLdouble* v) { functions()->glRasterPos4dv(v); }
void glRasterPos4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w) { functions()->glRasterPos4f(x, y, z, w); }
void glRasterPos4fv(const GLfloat* v) { functions()->glRasterPos4fv(v); }
void glRasterPos4i(GLint x, GLint y, GLint z, GLint w) { functions()->glRasterPos4i(x, y, z, w); }
void glRasterPos4iv(const GLint* v) { functions()->glRasterPos4iv(v); }
void glRasterPos4s(GLshort x, GLshort y, GLshort z, GLshort w) { functions()->glRasterPos4s(x, y, z, w); }
void glRasterPos4sv(const GLshort* v) { functions()->glRasterPos4sv(v); }
void glRasterPos4xOES(GLfixed x, GLfixed y, GLfixed z, GLfixed w) { functions()->glRasterPos4xOES(x, y, z, w); }
void glRasterPos4xvOES(const GLfixed* coords) { functions()->glRasterPos4xvOES(coords); }
void glRasterSamplesEXT(GLuint samples, GLboolean fixedsamplelocations) { functions()->glRasterSamplesEXT(samples, fixedsamplelocations); }
void glReadBuffer(GLenum mode) { functions()->glReadBuffer(mode); }
void glReadInstrumentsSGIX(GLint marker) { functions()->glReadInstrumentsSGIX(marker); }
void glReadnPixelsARB(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void* data) { functions()->glReadnPixelsARB(x, y, width, height, format, type, bufSize, data); }
void glReadnPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void* data) { functions()->glReadnPixels(x, y, width, height, format, type, bufSize, data); }
void glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* pixels) { functions()->glReadPixels(x, y, width, height, format, type, pixels); }
void glRectd(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2) { functions()->glRectd(x1, y1, x2, y2); }
void glRectdv(const GLdouble* v1, const GLdouble* v2) { functions()->glRectdv(v1, v2); }
void glRectf(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2) { functions()->glRectf(x1, y1, x2, y2); }
void glRectfv(const GLfloat* v1, const GLfloat* v2) { functions()->glRectfv(v1, v2); }
void glRecti(GLint x1, GLint y1, GLint x2, GLint y2) { functions()->glRecti(x1, y1, x2, y2); }
void glRectiv(const GLint* v1, const GLint* v2) { functions()->glRectiv(v1, v2); }
void glRects(GLshort x1, GLshort y1, GLshort x2, GLshort y2) { functions()->glRects(x1, y1, x2, y2); }
void glRectsv(const GLshort* v1, const GLshort* v2) { functions()->glRectsv(v1, v2); }
void glRectxOES(GLfixed x1, GLfixed y1, GLfixed x2, GLfixed y2) { functions()->glRectxOES(x1, y1, x2, y2); }
void glRectxvOES(const GLfixed* v1, const GLfixed* v2) { functions()->glRectxvOES(v1, v2); }
void glReferencePlaneSGIX(const GLdouble* equation) { functions()->glReferencePlaneSGIX(equation); }
void glReleaseShaderCompiler() { functions()->glReleaseShaderCompiler(); }
void glRenderbufferStorageEXT(GLenum target, GLenum internalformat, GLsizei width, GLsizei height) { functions()->glRenderbufferStorageEXT(target, internalformat, width, height); }
void glRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height) { functions()->glRenderbufferStorage(target, internalformat, width, height); }
void glRenderbufferStorageMultisampleCoverageNV(GLenum target, GLsizei coverageSamples, GLsizei colorSamples, GLenum internalformat, GLsizei width, GLsizei height) { functions()->glRenderbufferStorageMultisampleCoverageNV(target, coverageSamples, colorSamples, internalformat, width, height); }
void glRenderbufferStorageMultisampleEXT(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height) { functions()->glRenderbufferStorageMultisampleEXT(target, samples, internalformat, width, height); }
void glRenderbufferStorageMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height) { functions()->glRenderbufferStorageMultisample(target, samples, internalformat, width, height); }
void glReplacementCodePointerSUN(GLenum type, GLsizei stride, const void** pointer) { functions()->glReplacementCodePointerSUN(type, stride, pointer); }
void glReplacementCodeubSUN(GLubyte code) { functions()->glReplacementCodeubSUN(code); }
void glReplacementCodeubvSUN(const GLubyte* code) { functions()->glReplacementCodeubvSUN(code); }
void glReplacementCodeuiColor3fVertex3fSUN(GLuint rc, GLfloat r, GLfloat g, GLfloat b, GLfloat x, GLfloat y, GLfloat z) { functions()->glReplacementCodeuiColor3fVertex3fSUN(rc, r, g, b, x, y, z); }
void glReplacementCodeuiColor3fVertex3fvSUN(const GLuint* rc, const GLfloat* c, const GLfloat* v) { functions()->glReplacementCodeuiColor3fVertex3fvSUN(rc, c, v); }
void glReplacementCodeuiColor4fNormal3fVertex3fSUN(GLuint rc, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z) { functions()->glReplacementCodeuiColor4fNormal3fVertex3fSUN(rc, r, g, b, a, nx, ny, nz, x, y, z); }
void glReplacementCodeuiColor4fNormal3fVertex3fvSUN(const GLuint* rc, const GLfloat* c, const GLfloat* n, const GLfloat* v) { functions()->glReplacementCodeuiColor4fNormal3fVertex3fvSUN(rc, c, n, v); }
void glReplacementCodeuiColor4ubVertex3fSUN(GLuint rc, GLubyte r, GLubyte g, GLubyte b, GLubyte a, GLfloat x, GLfloat y, GLfloat z) { functions()->glReplacementCodeuiColor4ubVertex3fSUN(rc, r, g, b, a, x, y, z); }
void glReplacementCodeuiColor4ubVertex3fvSUN(const GLuint* rc, const GLubyte* c, const GLfloat* v) { functions()->glReplacementCodeuiColor4ubVertex3fvSUN(rc, c, v); }
void glReplacementCodeuiNormal3fVertex3fSUN(GLuint rc, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z) { functions()->glReplacementCodeuiNormal3fVertex3fSUN(rc, nx, ny, nz, x, y, z); }
void glReplacementCodeuiNormal3fVertex3fvSUN(const GLuint* rc, const GLfloat* n, const GLfloat* v) { functions()->glReplacementCodeuiNormal3fVertex3fvSUN(rc, n, v); }
void glReplacementCodeuiSUN(GLuint code) { functions()->glReplacementCodeuiSUN(code); }
void glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN(GLuint rc, GLfloat s, GLfloat t, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z) { functions()->glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN(rc, s, t, r, g, b, a, nx, ny, nz, x, y, z); }
void glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN(const GLuint* rc, const GLfloat* tc, const GLfloat* c, const GLfloat* n, const GLfloat* v) { functions()->glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN(rc, tc, c, n, v); }
void glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN(GLuint rc, GLfloat s, GLfloat t, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z) { functions()->glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN(rc, s, t, nx, ny, nz, x, y, z); }
void glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN(const GLuint* rc, const GLfloat* tc, const GLfloat* n, const GLfloat* v) { functions()->glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN(rc, tc, n, v); }
void glReplacementCodeuiTexCoord2fVertex3fSUN(GLuint rc, GLfloat s, GLfloat t, GLfloat x, GLfloat y, GLfloat z) { functions()->glReplacementCodeuiTexCoord2fVertex3fSUN(rc, s, t, x, y, z); }
void glReplacementCodeuiTexCoord2fVertex3fvSUN(const GLuint* rc, const GLfloat* tc, const GLfloat* v) { functions()->glReplacementCodeuiTexCoord2fVertex3fvSUN(rc, tc, v); }
void glReplacementCodeuiVertex3fSUN(GLuint rc, GLfloat x, GLfloat y, GLfloat z) { functions()->glReplacementCodeuiVertex3fSUN(rc, x, y, z); }
void glReplacementCodeuiVertex3fvSUN(const GLuint* rc, const GLfloat* v) { functions()->glReplacementCodeuiVertex3fvSUN(rc, v); }
void glReplacementCodeuivSUN(const GLuint* code) { functions()->glReplacementCodeuivSUN(code); }
void glReplacementCodeusSUN(GLushort code) { functions()->glReplacementCodeusSUN(code); }
void glReplacementCodeusvSUN(const GLushort* code) { functions()->glReplacementCodeusvSUN(code); }
void glRequestResidentProgramsNV(GLsizei n, const GLuint* programs) { functions()->glRequestResidentProgramsNV(n, programs); }
void glResetHistogramEXT(GLenum target) { functions()->glResetHistogramEXT(target); }
void glResetHistogram(GLenum target) { functions()->glResetHistogram(target); }
void glResetMinmaxEXT(GLenum target) { functions()->glResetMinmaxEXT(target); }
void glResetMinmax(GLenum target) { functions()->glResetMinmax(target); }
void glResizeBuffersMESA() { functions()->glResizeBuffersMESA(); }
void glResolveDepthValuesNV() { functions()->glResolveDepthValuesNV(); }
void glResumeTransformFeedback() { functions()->glResumeTransformFeedback(); }
void glResumeTransformFeedbackNV() { functions()->glResumeTransformFeedbackNV(); }
void glRotated(GLdouble angle, GLdouble x, GLdouble y, GLdouble z) { functions()->glRotated(angle, x, y, z); }
void glRotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z) { functions()->glRotatef(angle, x, y, z); }
void glRotatexOES(GLfixed angle, GLfixed x, GLfixed y, GLfixed z) { functions()->glRotatexOES(angle, x, y, z); }
void glSampleCoverageARB(GLfloat value, GLboolean invert) { functions()->glSampleCoverageARB(value, invert); }
void glSampleCoverage(GLclampf value, GLboolean invert) { functions()->glSampleCoverage(value, invert); }
void glSampleMapATI(GLuint dst, GLuint interp, GLenum swizzle) { functions()->glSampleMapATI(dst, interp, swizzle); }
void glSampleMaskEXT(GLclampf value, GLboolean invert) { functions()->glSampleMaskEXT(value, invert); }
void glSampleMaski(GLuint maskNumber, GLbitfield mask) { functions()->glSampleMaski(maskNumber, mask); }
void glSampleMaskIndexedNV(GLuint index, GLbitfield mask) { functions()->glSampleMaskIndexedNV(index, mask); }
void glSampleMaskSGIS(GLclampf value, GLboolean invert) { functions()->glSampleMaskSGIS(value, invert); }
void glSamplePatternEXT(GLenum pattern) { functions()->glSamplePatternEXT(pattern); }
void glSamplePatternSGIS(GLenum pattern) { functions()->glSamplePatternSGIS(pattern); }
void glSamplerParameterf(GLuint sampler, GLenum pname, GLfloat param) { functions()->glSamplerParameterf(sampler, pname, param); }
void glSamplerParameterfv(GLuint sampler, GLenum pname, const GLfloat* param) { functions()->glSamplerParameterfv(sampler, pname, param); }
void glSamplerParameteri(GLuint sampler, GLenum pname, GLint param) { functions()->glSamplerParameteri(sampler, pname, param); }
void glSamplerParameterIiv(GLuint sampler, GLenum pname, const GLint* param) { functions()->glSamplerParameterIiv(sampler, pname, param); }
void glSamplerParameterIuiv(GLuint sampler, GLenum pname, const GLuint* param) { functions()->glSamplerParameterIuiv(sampler, pname, param); }
void glSamplerParameteriv(GLuint sampler, GLenum pname, const GLint* param) { functions()->glSamplerParameteriv(sampler, pname, param); }
void glScaled(GLdouble x, GLdouble y, GLdouble z) { functions()->glScaled(x, y, z); }
void glScalef(GLfloat x, GLfloat y, GLfloat z) { functions()->glScalef(x, y, z); }
void glScalexOES(GLfixed x, GLfixed y, GLfixed z) { functions()->glScalexOES(x, y, z); }
void glScissorArrayv(GLuint first, GLsizei count, const GLint* v) { functions()->glScissorArrayv(first, count, v); }
void glScissor(GLint x, GLint y, GLsizei width, GLsizei height) { functions()->glScissor(x, y, width, height); }
void glScissorIndexed(GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height) { functions()->glScissorIndexed(index, left, bottom, width, height); }
void glScissorIndexedv(GLuint index, const GLint* v) { functions()->glScissorIndexedv(index, v); }
void glSecondaryColor3bEXT(GLbyte red, GLbyte green, GLbyte blue) { functions()->glSecondaryColor3bEXT(red, green, blue); }
void glSecondaryColor3b(GLbyte red, GLbyte green, GLbyte blue) { functions()->glSecondaryColor3b(red, green, blue); }
void glSecondaryColor3bv(const GLbyte* v) { functions()->glSecondaryColor3bv(v); }
void glSecondaryColor3bvEXT(const GLbyte* v) { functions()->glSecondaryColor3bvEXT(v); }
void glSecondaryColor3dEXT(GLdouble red, GLdouble green, GLdouble blue) { functions()->glSecondaryColor3dEXT(red, green, blue); }
void glSecondaryColor3d(GLdouble red, GLdouble green, GLdouble blue) { functions()->glSecondaryColor3d(red, green, blue); }
void glSecondaryColor3dv(const GLdouble* v) { functions()->glSecondaryColor3dv(v); }
void glSecondaryColor3dvEXT(const GLdouble* v) { functions()->glSecondaryColor3dvEXT(v); }
void glSecondaryColor3fEXT(GLfloat red, GLfloat green, GLfloat blue) { functions()->glSecondaryColor3fEXT(red, green, blue); }
void glSecondaryColor3f(GLfloat red, GLfloat green, GLfloat blue) { functions()->glSecondaryColor3f(red, green, blue); }
void glSecondaryColor3fv(const GLfloat* v) { functions()->glSecondaryColor3fv(v); }
void glSecondaryColor3fvEXT(const GLfloat* v) { functions()->glSecondaryColor3fvEXT(v); }
void glSecondaryColor3hNV(GLhalfNV red, GLhalfNV green, GLhalfNV blue) { functions()->glSecondaryColor3hNV(red, green, blue); }
void glSecondaryColor3hvNV(const GLhalfNV* v) { functions()->glSecondaryColor3hvNV(v); }
void glSecondaryColor3iEXT(GLint red, GLint green, GLint blue) { functions()->glSecondaryColor3iEXT(red, green, blue); }
void glSecondaryColor3i(GLint red, GLint green, GLint blue) { functions()->glSecondaryColor3i(red, green, blue); }
void glSecondaryColor3iv(const GLint* v) { functions()->glSecondaryColor3iv(v); }
void glSecondaryColor3ivEXT(const GLint* v) { functions()->glSecondaryColor3ivEXT(v); }
void glSecondaryColor3sEXT(GLshort red, GLshort green, GLshort blue) { functions()->glSecondaryColor3sEXT(red, green, blue); }
void glSecondaryColor3s(GLshort red, GLshort green, GLshort blue) { functions()->glSecondaryColor3s(red, green, blue); }
void glSecondaryColor3sv(const GLshort* v) { functions()->glSecondaryColor3sv(v); }
void glSecondaryColor3svEXT(const GLshort* v) { functions()->glSecondaryColor3svEXT(v); }
void glSecondaryColor3ubEXT(GLubyte red, GLubyte green, GLubyte blue) { functions()->glSecondaryColor3ubEXT(red, green, blue); }
void glSecondaryColor3ub(GLubyte red, GLubyte green, GLubyte blue) { functions()->glSecondaryColor3ub(red, green, blue); }
void glSecondaryColor3ubv(const GLubyte* v) { functions()->glSecondaryColor3ubv(v); }
void glSecondaryColor3ubvEXT(const GLubyte* v) { functions()->glSecondaryColor3ubvEXT(v); }
void glSecondaryColor3uiEXT(GLuint red, GLuint green, GLuint blue) { functions()->glSecondaryColor3uiEXT(red, green, blue); }
void glSecondaryColor3ui(GLuint red, GLuint green, GLuint blue) { functions()->glSecondaryColor3ui(red, green, blue); }
void glSecondaryColor3uiv(const GLuint* v) { functions()->glSecondaryColor3uiv(v); }
void glSecondaryColor3uivEXT(const GLuint* v) { functions()->glSecondaryColor3uivEXT(v); }
void glSecondaryColor3usEXT(GLushort red, GLushort green, GLushort blue) { functions()->glSecondaryColor3usEXT(red, green, blue); }
void glSecondaryColor3us(GLushort red, GLushort green, GLushort blue) { functions()->glSecondaryColor3us(red, green, blue); }
void glSecondaryColor3usv(const GLushort* v) { functions()->glSecondaryColor3usv(v); }
void glSecondaryColor3usvEXT(const GLushort* v) { functions()->glSecondaryColor3usvEXT(v); }
void glSecondaryColorFormatNV(GLint size, GLenum type, GLsizei stride) { functions()->glSecondaryColorFormatNV(size, type, stride); }
void glSecondaryColorP3ui(GLenum type, GLuint color) { functions()->glSecondaryColorP3ui(type, color); }
void glSecondaryColorP3uiv(GLenum type, const GLuint* color) { functions()->glSecondaryColorP3uiv(type, color); }
void glSecondaryColorPointerEXT(GLint size, GLenum type, GLsizei stride, const void* pointer) { functions()->glSecondaryColorPointerEXT(size, type, stride, pointer); }
void glSecondaryColorPointer(GLint size, GLenum type, GLsizei stride, const void* pointer) { functions()->glSecondaryColorPointer(size, type, stride, pointer); }
void glSecondaryColorPointerListIBM(GLint size, GLenum type, GLint stride, const void** pointer, GLint ptrstride) { functions()->glSecondaryColorPointerListIBM(size, type, stride, pointer, ptrstride); }
void glSelectBuffer(GLsizei size, GLuint* buffer) { functions()->glSelectBuffer(size, buffer); }
void glSelectPerfMonitorCountersAMD(GLuint monitor, GLboolean enable, GLuint group, GLint numCounters, GLuint* counterList) { functions()->glSelectPerfMonitorCountersAMD(monitor, enable, group, numCounters, counterList); }
void glSeparableFilter2DEXT(GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* row, const void* column) { functions()->glSeparableFilter2DEXT(target, internalformat, width, height, format, type, row, column); }
void glSeparableFilter2D(GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* row, const GLvoid* column) { functions()->glSeparableFilter2D(target, internalformat, width, height, format, type, row, column); }
void glSetFenceAPPLE(GLuint fence) { functions()->glSetFenceAPPLE(fence); }
void glSetFenceNV(GLuint fence, GLenum condition) { functions()->glSetFenceNV(fence, condition); }
void glSetFragmentShaderConstantATI(GLuint dst, const GLfloat* value) { functions()->glSetFragmentShaderConstantATI(dst, value); }
void glSetInvariantEXT(GLuint id, GLenum type, const void* addr) { functions()->glSetInvariantEXT(id, type, addr); }
void glSetLocalConstantEXT(GLuint id, GLenum type, const void* addr) { functions()->glSetLocalConstantEXT(id, type, addr); }
void glSetMultisamplefvAMD(GLenum pname, GLuint index, const GLfloat* val) { functions()->glSetMultisamplefvAMD(pname, index, val); }
void glShadeModel(GLenum mode) { functions()->glShadeModel(mode); }
void glShaderBinary(GLsizei count, const GLuint* shaders, GLenum binaryformat, const void* binary, GLsizei length) { functions()->glShaderBinary(count, shaders, binaryformat, binary, length); }
void glShaderOp1EXT(GLenum op, GLuint res, GLuint arg1) { functions()->glShaderOp1EXT(op, res, arg1); }
void glShaderOp2EXT(GLenum op, GLuint res, GLuint arg1, GLuint arg2) { functions()->glShaderOp2EXT(op, res, arg1, arg2); }
void glShaderOp3EXT(GLenum op, GLuint res, GLuint arg1, GLuint arg2, GLuint arg3) { functions()->glShaderOp3EXT(op, res, arg1, arg2, arg3); }
void glShaderSourceARB(GLhandleARB shaderObj, GLsizei count, const GLcharARB** string, const GLint* length) { functions()->glShaderSourceARB(shaderObj, count, string, length); }
void glShaderSource(GLuint shader, GLsizei count, const GLchar*const* string, const GLint* length) { functions()->glShaderSource(shader, count, string, length); }
void glShaderStorageBlockBinding(GLuint program, GLuint storageBlockIndex, GLuint storageBlockBinding) { functions()->glShaderStorageBlockBinding(program, storageBlockIndex, storageBlockBinding); }
void glSharpenTexFuncSGIS(GLenum target, GLsizei n, const GLfloat* points) { functions()->glSharpenTexFuncSGIS(target, n, points); }
void glSpriteParameterfSGIX(GLenum pname, GLfloat param) { functions()->glSpriteParameterfSGIX(pname, param); }
void glSpriteParameterfvSGIX(GLenum pname, const GLfloat* params) { functions()->glSpriteParameterfvSGIX(pname, params); }
void glSpriteParameteriSGIX(GLenum pname, GLint param) { functions()->glSpriteParameteriSGIX(pname, param); }
void glSpriteParameterivSGIX(GLenum pname, const GLint* params) { functions()->glSpriteParameterivSGIX(pname, params); }
void glStartInstrumentsSGIX() { functions()->glStartInstrumentsSGIX(); }
void glStateCaptureNV(GLuint state, GLenum mode) { functions()->glStateCaptureNV(state, mode); }
void glStencilClearTagEXT(GLsizei stencilTagBits, GLuint stencilClearTag) { functions()->glStencilClearTagEXT(stencilTagBits, stencilClearTag); }
void glStencilFillPathInstancedNV(GLsizei numPaths, GLenum pathNameType, const void* paths, GLuint pathBase, GLenum fillMode, GLuint mask, GLenum transformType, const GLfloat* transformValues) { functions()->glStencilFillPathInstancedNV(numPaths, pathNameType, paths, pathBase, fillMode, mask, transformType, transformValues); }
void glStencilFillPathNV(GLuint path, GLenum fillMode, GLuint mask) { functions()->glStencilFillPathNV(path, fillMode, mask); }
void glStencilFunc(GLenum func, GLint ref, GLuint mask) { functions()->glStencilFunc(func, ref, mask); }
void glStencilFuncSeparateATI(GLenum frontfunc, GLenum backfunc, GLint ref, GLuint mask) { functions()->glStencilFuncSeparateATI(frontfunc, backfunc, ref, mask); }
void glStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask) { functions()->glStencilFuncSeparate(face, func, ref, mask); }
void glStencilMask(GLuint mask) { functions()->glStencilMask(mask); }
void glStencilMaskSeparate(GLenum face, GLuint mask) { functions()->glStencilMaskSeparate(face, mask); }
void glStencilOp(GLenum fail, GLenum zfail, GLenum zpass) { functions()->glStencilOp(fail, zfail, zpass); }
void glStencilOpSeparateATI(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass) { functions()->glStencilOpSeparateATI(face, sfail, dpfail, dppass); }
void glStencilOpSeparate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass) { functions()->glStencilOpSeparate(face, sfail, dpfail, dppass); }
void glStencilOpValueAMD(GLenum face, GLuint value) { functions()->glStencilOpValueAMD(face, value); }
void glStencilStrokePathInstancedNV(GLsizei numPaths, GLenum pathNameType, const void* paths, GLuint pathBase, GLint reference, GLuint mask, GLenum transformType, const GLfloat* transformValues) { functions()->glStencilStrokePathInstancedNV(numPaths, pathNameType, paths, pathBase, reference, mask, transformType, transformValues); }
void glStencilStrokePathNV(GLuint path, GLint reference, GLuint mask) { functions()->glStencilStrokePathNV(path, reference, mask); }
void glStencilThenCoverFillPathInstancedNV(GLsizei numPaths, GLenum pathNameType, const void* paths, GLuint pathBase, GLenum fillMode, GLuint mask, GLenum coverMode, GLenum transformType, const GLfloat* transformValues) { functions()->glStencilThenCoverFillPathInstancedNV(numPaths, pathNameType, paths, pathBase, fillMode, mask, coverMode, transformType, transformValues); }
void glStencilThenCoverFillPathNV(GLuint path, GLenum fillMode, GLuint mask, GLenum coverMode) { functions()->glStencilThenCoverFillPathNV(path, fillMode, mask, coverMode); }
void glStencilThenCoverStrokePathInstancedNV(GLsizei numPaths, GLenum pathNameType, const void* paths, GLuint pathBase, GLint reference, GLuint mask, GLenum coverMode, GLenum transformType, const GLfloat* transformValues) { functions()->glStencilThenCoverStrokePathInstancedNV(numPaths, pathNameType, paths, pathBase, reference, mask, coverMode, transformType, transformValues); }
void glStencilThenCoverStrokePathNV(GLuint path, GLint reference, GLuint mask, GLenum coverMode) { functions()->glStencilThenCoverStrokePathNV(path, reference, mask, coverMode); }
void glStopInstrumentsSGIX(GLint marker) { functions()->glStopInstrumentsSGIX(marker); }
void glStringMarkerGREMEDY(GLsizei len, const void* string) { functions()->glStringMarkerGREMEDY(len, string); }
void glSubpixelPrecisionBiasNV(GLuint xbits, GLuint ybits) { functions()->glSubpixelPrecisionBiasNV(xbits, ybits); }
void glSwizzleEXT(GLuint res, GLuint in, GLenum outX, GLenum outY, GLenum outZ, GLenum outW) { functions()->glSwizzleEXT(res, in, outX, outY, outZ, outW); }
void glSyncTextureINTEL(GLuint texture) { functions()->glSyncTextureINTEL(texture); }
void glTagSampleBufferSGIX() { functions()->glTagSampleBufferSGIX(); }
void glTangent3bEXT(GLbyte tx, GLbyte ty, GLbyte tz) { functions()->glTangent3bEXT(tx, ty, tz); }
void glTangent3bvEXT(const GLbyte* v) { functions()->glTangent3bvEXT(v); }
void glTangent3dEXT(GLdouble tx, GLdouble ty, GLdouble tz) { functions()->glTangent3dEXT(tx, ty, tz); }
void glTangent3dvEXT(const GLdouble* v) { functions()->glTangent3dvEXT(v); }
void glTangent3fEXT(GLfloat tx, GLfloat ty, GLfloat tz) { functions()->glTangent3fEXT(tx, ty, tz); }
void glTangent3fvEXT(const GLfloat* v) { functions()->glTangent3fvEXT(v); }
void glTangent3iEXT(GLint tx, GLint ty, GLint tz) { functions()->glTangent3iEXT(tx, ty, tz); }
void glTangent3ivEXT(const GLint* v) { functions()->glTangent3ivEXT(v); }
void glTangent3sEXT(GLshort tx, GLshort ty, GLshort tz) { functions()->glTangent3sEXT(tx, ty, tz); }
void glTangent3svEXT(const GLshort* v) { functions()->glTangent3svEXT(v); }
void glTangentPointerEXT(GLenum type, GLsizei stride, const void* pointer) { functions()->glTangentPointerEXT(type, stride, pointer); }
void glTbufferMask3DFX(GLuint mask) { functions()->glTbufferMask3DFX(mask); }
void glTessellationFactorAMD(GLfloat factor) { functions()->glTessellationFactorAMD(factor); }
void glTessellationModeAMD(GLenum mode) { functions()->glTessellationModeAMD(mode); }
void glTexBufferARB(GLenum target, GLenum internalformat, GLuint buffer) { functions()->glTexBufferARB(target, internalformat, buffer); }
void glTexBufferEXT(GLenum target, GLenum internalformat, GLuint buffer) { functions()->glTexBufferEXT(target, internalformat, buffer); }
void glTexBuffer(GLenum target, GLenum internalformat, GLuint buffer) { functions()->glTexBuffer(target, internalformat, buffer); }
void glTexBufferRange(GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size) { functions()->glTexBufferRange(target, internalformat, buffer, offset, size); }
void glTexBumpParameterfvATI(GLenum pname, const GLfloat* param) { functions()->glTexBumpParameterfvATI(pname, param); }
void glTexBumpParameterivATI(GLenum pname, const GLint* param) { functions()->glTexBumpParameterivATI(pname, param); }
void glTexCoord1bOES(GLbyte s) { functions()->glTexCoord1bOES(s); }
void glTexCoord1bvOES(const GLbyte* coords) { functions()->glTexCoord1bvOES(coords); }
void glTexCoord1d(GLdouble s) { functions()->glTexCoord1d(s); }
void glTexCoord1dv(const GLdouble* v) { functions()->glTexCoord1dv(v); }
void glTexCoord1f(GLfloat s) { functions()->glTexCoord1f(s); }
void glTexCoord1fv(const GLfloat* v) { functions()->glTexCoord1fv(v); }
void glTexCoord1hNV(GLhalfNV s) { functions()->glTexCoord1hNV(s); }
void glTexCoord1hvNV(const GLhalfNV* v) { functions()->glTexCoord1hvNV(v); }
void glTexCoord1i(GLint s) { functions()->glTexCoord1i(s); }
void glTexCoord1iv(const GLint* v) { functions()->glTexCoord1iv(v); }
void glTexCoord1s(GLshort s) { functions()->glTexCoord1s(s); }
void glTexCoord1sv(const GLshort* v) { functions()->glTexCoord1sv(v); }
void glTexCoord1xOES(GLfixed s) { functions()->glTexCoord1xOES(s); }
void glTexCoord1xvOES(const GLfixed* coords) { functions()->glTexCoord1xvOES(coords); }
void glTexCoord2bOES(GLbyte s, GLbyte t) { functions()->glTexCoord2bOES(s, t); }
void glTexCoord2bvOES(const GLbyte* coords) { functions()->glTexCoord2bvOES(coords); }
void glTexCoord2d(GLdouble s, GLdouble t) { functions()->glTexCoord2d(s, t); }
void glTexCoord2dv(const GLdouble* v) { functions()->glTexCoord2dv(v); }
void glTexCoord2fColor3fVertex3fSUN(GLfloat s, GLfloat t, GLfloat r, GLfloat g, GLfloat b, GLfloat x, GLfloat y, GLfloat z) { functions()->glTexCoord2fColor3fVertex3fSUN(s, t, r, g, b, x, y, z); }
void glTexCoord2fColor3fVertex3fvSUN(const GLfloat* tc, const GLfloat* c, const GLfloat* v) { functions()->glTexCoord2fColor3fVertex3fvSUN(tc, c, v); }
void glTexCoord2fColor4fNormal3fVertex3fSUN(GLfloat s, GLfloat t, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z) { functions()->glTexCoord2fColor4fNormal3fVertex3fSUN(s, t, r, g, b, a, nx, ny, nz, x, y, z); }
void glTexCoord2fColor4fNormal3fVertex3fvSUN(const GLfloat* tc, const GLfloat* c, const GLfloat* n, const GLfloat* v) { functions()->glTexCoord2fColor4fNormal3fVertex3fvSUN(tc, c, n, v); }
void glTexCoord2fColor4ubVertex3fSUN(GLfloat s, GLfloat t, GLubyte r, GLubyte g, GLubyte b, GLubyte a, GLfloat x, GLfloat y, GLfloat z) { functions()->glTexCoord2fColor4ubVertex3fSUN(s, t, r, g, b, a, x, y, z); }
void glTexCoord2fColor4ubVertex3fvSUN(const GLfloat* tc, const GLubyte* c, const GLfloat* v) { functions()->glTexCoord2fColor4ubVertex3fvSUN(tc, c, v); }
void glTexCoord2f(GLfloat s, GLfloat t) { functions()->glTexCoord2f(s, t); }
void glTexCoord2fNormal3fVertex3fSUN(GLfloat s, GLfloat t, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z) { functions()->glTexCoord2fNormal3fVertex3fSUN(s, t, nx, ny, nz, x, y, z); }
void glTexCoord2fNormal3fVertex3fvSUN(const GLfloat* tc, const GLfloat* n, const GLfloat* v) { functions()->glTexCoord2fNormal3fVertex3fvSUN(tc, n, v); }
void glTexCoord2fv(const GLfloat* v) { functions()->glTexCoord2fv(v); }
void glTexCoord2fVertex3fSUN(GLfloat s, GLfloat t, GLfloat x, GLfloat y, GLfloat z) { functions()->glTexCoord2fVertex3fSUN(s, t, x, y, z); }
void glTexCoord2fVertex3fvSUN(const GLfloat* tc, const GLfloat* v) { functions()->glTexCoord2fVertex3fvSUN(tc, v); }
void glTexCoord2hNV(GLhalfNV s, GLhalfNV t) { functions()->glTexCoord2hNV(s, t); }
void glTexCoord2hvNV(const GLhalfNV* v) { functions()->glTexCoord2hvNV(v); }
void glTexCoord2i(GLint s, GLint t) { functions()->glTexCoord2i(s, t); }
void glTexCoord2iv(const GLint* v) { functions()->glTexCoord2iv(v); }
void glTexCoord2s(GLshort s, GLshort t) { functions()->glTexCoord2s(s, t); }
void glTexCoord2sv(const GLshort* v) { functions()->glTexCoord2sv(v); }
void glTexCoord2xOES(GLfixed s, GLfixed t) { functions()->glTexCoord2xOES(s, t); }
void glTexCoord2xvOES(const GLfixed* coords) { functions()->glTexCoord2xvOES(coords); }
void glTexCoord3bOES(GLbyte s, GLbyte t, GLbyte r) { functions()->glTexCoord3bOES(s, t, r); }
void glTexCoord3bvOES(const GLbyte* coords) { functions()->glTexCoord3bvOES(coords); }
void glTexCoord3d(GLdouble s, GLdouble t, GLdouble r) { functions()->glTexCoord3d(s, t, r); }
void glTexCoord3dv(const GLdouble* v) { functions()->glTexCoord3dv(v); }
void glTexCoord3f(GLfloat s, GLfloat t, GLfloat r) { functions()->glTexCoord3f(s, t, r); }
void glTexCoord3fv(const GLfloat* v) { functions()->glTexCoord3fv(v); }
void glTexCoord3hNV(GLhalfNV s, GLhalfNV t, GLhalfNV r) { functions()->glTexCoord3hNV(s, t, r); }
void glTexCoord3hvNV(const GLhalfNV* v) { functions()->glTexCoord3hvNV(v); }
void glTexCoord3i(GLint s, GLint t, GLint r) { functions()->glTexCoord3i(s, t, r); }
void glTexCoord3iv(const GLint* v) { functions()->glTexCoord3iv(v); }
void glTexCoord3s(GLshort s, GLshort t, GLshort r) { functions()->glTexCoord3s(s, t, r); }
void glTexCoord3sv(const GLshort* v) { functions()->glTexCoord3sv(v); }
void glTexCoord3xOES(GLfixed s, GLfixed t, GLfixed r) { functions()->glTexCoord3xOES(s, t, r); }
void glTexCoord3xvOES(const GLfixed* coords) { functions()->glTexCoord3xvOES(coords); }
void glTexCoord4bOES(GLbyte s, GLbyte t, GLbyte r, GLbyte q) { functions()->glTexCoord4bOES(s, t, r, q); }
void glTexCoord4bvOES(const GLbyte* coords) { functions()->glTexCoord4bvOES(coords); }
void glTexCoord4d(GLdouble s, GLdouble t, GLdouble r, GLdouble q) { functions()->glTexCoord4d(s, t, r, q); }
void glTexCoord4dv(const GLdouble* v) { functions()->glTexCoord4dv(v); }
void glTexCoord4fColor4fNormal3fVertex4fSUN(GLfloat s, GLfloat t, GLfloat p, GLfloat q, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z, GLfloat w) { functions()->glTexCoord4fColor4fNormal3fVertex4fSUN(s, t, p, q, r, g, b, a, nx, ny, nz, x, y, z, w); }
void glTexCoord4fColor4fNormal3fVertex4fvSUN(const GLfloat* tc, const GLfloat* c, const GLfloat* n, const GLfloat* v) { functions()->glTexCoord4fColor4fNormal3fVertex4fvSUN(tc, c, n, v); }
void glTexCoord4f(GLfloat s, GLfloat t, GLfloat r, GLfloat q) { functions()->glTexCoord4f(s, t, r, q); }
void glTexCoord4fv(const GLfloat* v) { functions()->glTexCoord4fv(v); }
void glTexCoord4fVertex4fSUN(GLfloat s, GLfloat t, GLfloat p, GLfloat q, GLfloat x, GLfloat y, GLfloat z, GLfloat w) { functions()->glTexCoord4fVertex4fSUN(s, t, p, q, x, y, z, w); }
void glTexCoord4fVertex4fvSUN(const GLfloat* tc, const GLfloat* v) { functions()->glTexCoord4fVertex4fvSUN(tc, v); }
void glTexCoord4hNV(GLhalfNV s, GLhalfNV t, GLhalfNV r, GLhalfNV q) { functions()->glTexCoord4hNV(s, t, r, q); }
void glTexCoord4hvNV(const GLhalfNV* v) { functions()->glTexCoord4hvNV(v); }
void glTexCoord4i(GLint s, GLint t, GLint r, GLint q) { functions()->glTexCoord4i(s, t, r, q); }
void glTexCoord4iv(const GLint* v) { functions()->glTexCoord4iv(v); }
void glTexCoord4s(GLshort s, GLshort t, GLshort r, GLshort q) { functions()->glTexCoord4s(s, t, r, q); }
void glTexCoord4sv(const GLshort* v) { functions()->glTexCoord4sv(v); }
void glTexCoord4xOES(GLfixed s, GLfixed t, GLfixed r, GLfixed q) { functions()->glTexCoord4xOES(s, t, r, q); }
void glTexCoord4xvOES(const GLfixed* coords) { functions()->glTexCoord4xvOES(coords); }
void glTexCoordFormatNV(GLint size, GLenum type, GLsizei stride) { functions()->glTexCoordFormatNV(size, type, stride); }
void glTexCoordP1ui(GLenum type, GLuint coords) { functions()->glTexCoordP1ui(type, coords); }
void glTexCoordP1uiv(GLenum type, const GLuint* coords) { functions()->glTexCoordP1uiv(type, coords); }
void glTexCoordP2ui(GLenum type, GLuint coords) { functions()->glTexCoordP2ui(type, coords); }
void glTexCoordP2uiv(GLenum type, const GLuint* coords) { functions()->glTexCoordP2uiv(type, coords); }
void glTexCoordP3ui(GLenum type, GLuint coords) { functions()->glTexCoordP3ui(type, coords); }
void glTexCoordP3uiv(GLenum type, const GLuint* coords) { functions()->glTexCoordP3uiv(type, coords); }
void glTexCoordP4ui(GLenum type, GLuint coords) { functions()->glTexCoordP4ui(type, coords); }
void glTexCoordP4uiv(GLenum type, const GLuint* coords) { functions()->glTexCoordP4uiv(type, coords); }
void glTexCoordPointerEXT(GLint size, GLenum type, GLsizei stride, GLsizei count, const void* pointer) { functions()->glTexCoordPointerEXT(size, type, stride, count, pointer); }
void glTexCoordPointer(GLint size, GLenum type, GLsizei stride, const GLvoid* ptr) { functions()->glTexCoordPointer(size, type, stride, ptr); }
void glTexCoordPointerListIBM(GLint size, GLenum type, GLint stride, const void** pointer, GLint ptrstride) { functions()->glTexCoordPointerListIBM(size, type, stride, pointer, ptrstride); }
void glTexCoordPointervINTEL(GLint size, GLenum type, const void** pointer) { functions()->glTexCoordPointervINTEL(size, type, pointer); }
void glTexEnvf(GLenum target, GLenum pname, GLfloat param) { functions()->glTexEnvf(target, pname, param); }
void glTexEnvfv(GLenum target, GLenum pname, const GLfloat* params) { functions()->glTexEnvfv(target, pname, params); }
void glTexEnvi(GLenum target, GLenum pname, GLint param) { functions()->glTexEnvi(target, pname, param); }
void glTexEnviv(GLenum target, GLenum pname, const GLint* params) { functions()->glTexEnviv(target, pname, params); }
void glTexEnvxOES(GLenum target, GLenum pname, GLfixed param) { functions()->glTexEnvxOES(target, pname, param); }
void glTexEnvxvOES(GLenum target, GLenum pname, const GLfixed* params) { functions()->glTexEnvxvOES(target, pname, params); }
void glTexFilterFuncSGIS(GLenum target, GLenum filter, GLsizei n, const GLfloat* weights) { functions()->glTexFilterFuncSGIS(target, filter, n, weights); }
void glTexGend(GLenum coord, GLenum pname, GLdouble param) { functions()->glTexGend(coord, pname, param); }
void glTexGendv(GLenum coord, GLenum pname, const GLdouble* params) { functions()->glTexGendv(coord, pname, params); }
void glTexGenf(GLenum coord, GLenum pname, GLfloat param) { functions()->glTexGenf(coord, pname, param); }
void glTexGenfv(GLenum coord, GLenum pname, const GLfloat* params) { functions()->glTexGenfv(coord, pname, params); }
void glTexGeni(GLenum coord, GLenum pname, GLint param) { functions()->glTexGeni(coord, pname, param); }
void glTexGeniv(GLenum coord, GLenum pname, const GLint* params) { functions()->glTexGeniv(coord, pname, params); }
void glTexGenxOES(GLenum coord, GLenum pname, GLfixed param) { functions()->glTexGenxOES(coord, pname, param); }
void glTexGenxvOES(GLenum coord, GLenum pname, const GLfixed* params) { functions()->glTexGenxvOES(coord, pname, params); }
void glTexImage1D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid* pixels) { functions()->glTexImage1D(target, level, internalFormat, width, border, format, type, pixels); }
void glTexImage2D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* pixels) { functions()->glTexImage2D(target, level, internalFormat, width, height, border, format, type, pixels); }
void glTexImage2DMultisampleCoverageNV(GLenum target, GLsizei coverageSamples, GLsizei colorSamples, GLint internalFormat, GLsizei width, GLsizei height, GLboolean fixedSampleLocations) { functions()->glTexImage2DMultisampleCoverageNV(target, coverageSamples, colorSamples, internalFormat, width, height, fixedSampleLocations); }
void glTexImage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations) { functions()->glTexImage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations); }
void glTexImage3DEXT(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void* pixels) { functions()->glTexImage3DEXT(target, level, internalformat, width, height, depth, border, format, type, pixels); }
void glTexImage3D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid* pixels) { functions()->glTexImage3D(target, level, internalFormat, width, height, depth, border, format, type, pixels); }
void glTexImage3DMultisampleCoverageNV(GLenum target, GLsizei coverageSamples, GLsizei colorSamples, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedSampleLocations) { functions()->glTexImage3DMultisampleCoverageNV(target, coverageSamples, colorSamples, internalFormat, width, height, depth, fixedSampleLocations); }
void glTexImage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations) { functions()->glTexImage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations); }
void glTexImage4DSGIS(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLsizei size4d, GLint border, GLenum format, GLenum type, const void* pixels) { functions()->glTexImage4DSGIS(target, level, internalformat, width, height, depth, size4d, border, format, type, pixels); }
void glTexPageCommitmentARB(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLboolean commit) { functions()->glTexPageCommitmentARB(target, level, xoffset, yoffset, zoffset, width, height, depth, commit); }
void glTexParameterf(GLenum target, GLenum pname, GLfloat param) { functions()->glTexParameterf(target, pname, param); }
void glTexParameterfv(GLenum target, GLenum pname, const GLfloat* params) { functions()->glTexParameterfv(target, pname, params); }
void glTexParameteri(GLenum target, GLenum pname, GLint param) { functions()->glTexParameteri(target, pname, param); }
void glTexParameterIivEXT(GLenum target, GLenum pname, const GLint* params) { functions()->glTexParameterIivEXT(target, pname, params); }
void glTexParameterIiv(GLenum target, GLenum pname, const GLint* params) { functions()->glTexParameterIiv(target, pname, params); }
void glTexParameterIuivEXT(GLenum target, GLenum pname, const GLuint* params) { functions()->glTexParameterIuivEXT(target, pname, params); }
void glTexParameterIuiv(GLenum target, GLenum pname, const GLuint* params) { functions()->glTexParameterIuiv(target, pname, params); }
void glTexParameteriv(GLenum target, GLenum pname, const GLint* params) { functions()->glTexParameteriv(target, pname, params); }
void glTexParameterxOES(GLenum target, GLenum pname, GLfixed param) { functions()->glTexParameterxOES(target, pname, param); }
void glTexParameterxvOES(GLenum target, GLenum pname, const GLfixed* params) { functions()->glTexParameterxvOES(target, pname, params); }
void glTexRenderbufferNV(GLenum target, GLuint renderbuffer) { functions()->glTexRenderbufferNV(target, renderbuffer); }
void glTexStorage1D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width) { functions()->glTexStorage1D(target, levels, internalformat, width); }
void glTexStorage2D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height) { functions()->glTexStorage2D(target, levels, internalformat, width, height); }
void glTexStorage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations) { functions()->glTexStorage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations); }
void glTexStorage3D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth) { functions()->glTexStorage3D(target, levels, internalformat, width, height, depth); }
void glTexStorage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations) { functions()->glTexStorage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations); }
void glTexStorageSparseAMD(GLenum target, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLsizei layers, GLbitfield flags) { functions()->glTexStorageSparseAMD(target, internalFormat, width, height, depth, layers, flags); }
void glTexSubImage1DEXT(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void* pixels) { functions()->glTexSubImage1DEXT(target, level, xoffset, width, format, type, pixels); }
void glTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid* pixels) { functions()->glTexSubImage1D(target, level, xoffset, width, format, type, pixels); }
void glTexSubImage2DEXT(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels) { functions()->glTexSubImage2DEXT(target, level, xoffset, yoffset, width, height, format, type, pixels); }
void glTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels) { functions()->glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels); }
void glTexSubImage3DEXT(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* pixels) { functions()->glTexSubImage3DEXT(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels); }
void glTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid* pixels) { functions()->glTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels); }
void glTexSubImage4DSGIS(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint woffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei size4d, GLenum format, GLenum type, const void* pixels) { functions()->glTexSubImage4DSGIS(target, level, xoffset, yoffset, zoffset, woffset, width, height, depth, size4d, format, type, pixels); }
void glTextureBarrier() { functions()->glTextureBarrier(); }
void glTextureBarrierNV() { functions()->glTextureBarrierNV(); }
void glTextureBufferEXT(GLuint texture, GLenum target, GLenum internalformat, GLuint buffer) { functions()->glTextureBufferEXT(texture, target, internalformat, buffer); }
void glTextureBuffer(GLuint texture, GLenum internalformat, GLuint buffer) { functions()->glTextureBuffer(texture, internalformat, buffer); }
void glTextureBufferRangeEXT(GLuint texture, GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size) { functions()->glTextureBufferRangeEXT(texture, target, internalformat, buffer, offset, size); }
void glTextureBufferRange(GLuint texture, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size) { functions()->glTextureBufferRange(texture, internalformat, buffer, offset, size); }
void glTextureColorMaskSGIS(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha) { functions()->glTextureColorMaskSGIS(red, green, blue, alpha); }
void glTextureImage1DEXT(GLuint texture, GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void* pixels) { functions()->glTextureImage1DEXT(texture, target, level, internalformat, width, border, format, type, pixels); }
void glTextureImage2DEXT(GLuint texture, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* pixels) { functions()->glTextureImage2DEXT(texture, target, level, internalformat, width, height, border, format, type, pixels); }
void glTextureImage2DMultisampleCoverageNV(GLuint texture, GLenum target, GLsizei coverageSamples, GLsizei colorSamples, GLint internalFormat, GLsizei width, GLsizei height, GLboolean fixedSampleLocations) { functions()->glTextureImage2DMultisampleCoverageNV(texture, target, coverageSamples, colorSamples, internalFormat, width, height, fixedSampleLocations); }
void glTextureImage2DMultisampleNV(GLuint texture, GLenum target, GLsizei samples, GLint internalFormat, GLsizei width, GLsizei height, GLboolean fixedSampleLocations) { functions()->glTextureImage2DMultisampleNV(texture, target, samples, internalFormat, width, height, fixedSampleLocations); }
void glTextureImage3DEXT(GLuint texture, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void* pixels) { functions()->glTextureImage3DEXT(texture, target, level, internalformat, width, height, depth, border, format, type, pixels); }
void glTextureImage3DMultisampleCoverageNV(GLuint texture, GLenum target, GLsizei coverageSamples, GLsizei colorSamples, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedSampleLocations) { functions()->glTextureImage3DMultisampleCoverageNV(texture, target, coverageSamples, colorSamples, internalFormat, width, height, depth, fixedSampleLocations); }
void glTextureImage3DMultisampleNV(GLuint texture, GLenum target, GLsizei samples, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedSampleLocations) { functions()->glTextureImage3DMultisampleNV(texture, target, samples, internalFormat, width, height, depth, fixedSampleLocations); }
void glTextureLightEXT(GLenum pname) { functions()->glTextureLightEXT(pname); }
void glTextureMaterialEXT(GLenum face, GLenum mode) { functions()->glTextureMaterialEXT(face, mode); }
void glTextureNormalEXT(GLenum mode) { functions()->glTextureNormalEXT(mode); }
void glTexturePageCommitmentEXT(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLboolean commit) { functions()->glTexturePageCommitmentEXT(texture, level, xoffset, yoffset, zoffset, width, height, depth, commit); }
void glTextureParameterfEXT(GLuint texture, GLenum target, GLenum pname, GLfloat param) { functions()->glTextureParameterfEXT(texture, target, pname, param); }
void glTextureParameterf(GLuint texture, GLenum pname, GLfloat param) { functions()->glTextureParameterf(texture, pname, param); }
void glTextureParameterfvEXT(GLuint texture, GLenum target, GLenum pname, const GLfloat* params) { functions()->glTextureParameterfvEXT(texture, target, pname, params); }
void glTextureParameterfv(GLuint texture, GLenum pname, const GLfloat* param) { functions()->glTextureParameterfv(texture, pname, param); }
void glTextureParameteriEXT(GLuint texture, GLenum target, GLenum pname, GLint param) { functions()->glTextureParameteriEXT(texture, target, pname, param); }
void glTextureParameteri(GLuint texture, GLenum pname, GLint param) { functions()->glTextureParameteri(texture, pname, param); }
void glTextureParameterIivEXT(GLuint texture, GLenum target, GLenum pname, const GLint* params) { functions()->glTextureParameterIivEXT(texture, target, pname, params); }
void glTextureParameterIiv(GLuint texture, GLenum pname, const GLint* params) { functions()->glTextureParameterIiv(texture, pname, params); }
void glTextureParameterIuivEXT(GLuint texture, GLenum target, GLenum pname, const GLuint* params) { functions()->glTextureParameterIuivEXT(texture, target, pname, params); }
void glTextureParameterIuiv(GLuint texture, GLenum pname, const GLuint* params) { functions()->glTextureParameterIuiv(texture, pname, params); }
void glTextureParameterivEXT(GLuint texture, GLenum target, GLenum pname, const GLint* params) { functions()->glTextureParameterivEXT(texture, target, pname, params); }
void glTextureParameteriv(GLuint texture, GLenum pname, const GLint* param) { functions()->glTextureParameteriv(texture, pname, param); }
void glTextureRangeAPPLE(GLenum target, GLsizei length, const void* pointer) { functions()->glTextureRangeAPPLE(target, length, pointer); }
void glTextureRenderbufferEXT(GLuint texture, GLenum target, GLuint renderbuffer) { functions()->glTextureRenderbufferEXT(texture, target, renderbuffer); }
void glTextureStorage1DEXT(GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width) { functions()->glTextureStorage1DEXT(texture, target, levels, internalformat, width); }
void glTextureStorage1D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width) { functions()->glTextureStorage1D(texture, levels, internalformat, width); }
void glTextureStorage2DEXT(GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height) { functions()->glTextureStorage2DEXT(texture, target, levels, internalformat, width, height); }
void glTextureStorage2D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height) { functions()->glTextureStorage2D(texture, levels, internalformat, width, height); }
void glTextureStorage2DMultisampleEXT(GLuint texture, GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations) { functions()->glTextureStorage2DMultisampleEXT(texture, target, samples, internalformat, width, height, fixedsamplelocations); }
void glTextureStorage2DMultisample(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations) { functions()->glTextureStorage2DMultisample(texture, samples, internalformat, width, height, fixedsamplelocations); }
void glTextureStorage3DEXT(GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth) { functions()->glTextureStorage3DEXT(texture, target, levels, internalformat, width, height, depth); }
void glTextureStorage3D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth) { functions()->glTextureStorage3D(texture, levels, internalformat, width, height, depth); }
void glTextureStorage3DMultisampleEXT(GLuint texture, GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations) { functions()->glTextureStorage3DMultisampleEXT(texture, target, samples, internalformat, width, height, depth, fixedsamplelocations); }
void glTextureStorage3DMultisample(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations) { functions()->glTextureStorage3DMultisample(texture, samples, internalformat, width, height, depth, fixedsamplelocations); }
void glTextureStorageSparseAMD(GLuint texture, GLenum target, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLsizei layers, GLbitfield flags) { functions()->glTextureStorageSparseAMD(texture, target, internalFormat, width, height, depth, layers, flags); }
void glTextureSubImage1DEXT(GLuint texture, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void* pixels) { functions()->glTextureSubImage1DEXT(texture, target, level, xoffset, width, format, type, pixels); }
void glTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void* pixels) { functions()->glTextureSubImage1D(texture, level, xoffset, width, format, type, pixels); }
void glTextureSubImage2DEXT(GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels) { functions()->glTextureSubImage2DEXT(texture, target, level, xoffset, yoffset, width, height, format, type, pixels); }
void glTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels) { functions()->glTextureSubImage2D(texture, level, xoffset, yoffset, width, height, format, type, pixels); }
void glTextureSubImage3DEXT(GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* pixels) { functions()->glTextureSubImage3DEXT(texture, target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels); }
void glTextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* pixels) { functions()->glTextureSubImage3D(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels); }
void glTextureView(GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers) { functions()->glTextureView(texture, target, origtexture, internalformat, minlevel, numlevels, minlayer, numlayers); }
void glTrackMatrixNV(GLenum target, GLuint address, GLenum matrix, GLenum transform) { functions()->glTrackMatrixNV(target, address, matrix, transform); }
void glTransformFeedbackAttribsNV(GLsizei count, const GLint* attribs, GLenum bufferMode) { functions()->glTransformFeedbackAttribsNV(count, attribs, bufferMode); }
void glTransformFeedbackBufferBase(GLuint xfb, GLuint index, GLuint buffer) { functions()->glTransformFeedbackBufferBase(xfb, index, buffer); }
void glTransformFeedbackBufferRange(GLuint xfb, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size) { functions()->glTransformFeedbackBufferRange(xfb, index, buffer, offset, size); }
void glTransformFeedbackStreamAttribsNV(GLsizei count, const GLint* attribs, GLsizei nbuffers, const GLint* bufstreams, GLenum bufferMode) { functions()->glTransformFeedbackStreamAttribsNV(count, attribs, nbuffers, bufstreams, bufferMode); }
void glTransformFeedbackVaryingsEXT(GLuint program, GLsizei count, const GLchar*const* varyings, GLenum bufferMode) { functions()->glTransformFeedbackVaryingsEXT(program, count, varyings, bufferMode); }
void glTransformFeedbackVaryings(GLuint program, GLsizei count, const GLchar*const* varyings, GLenum bufferMode) { functions()->glTransformFeedbackVaryings(program, count, varyings, bufferMode); }
void glTransformFeedbackVaryingsNV(GLuint program, GLsizei count, const GLint* locations, GLenum bufferMode) { functions()->glTransformFeedbackVaryingsNV(program, count, locations, bufferMode); }
void glTransformPathNV(GLuint resultPath, GLuint srcPath, GLenum transformType, const GLfloat* transformValues) { functions()->glTransformPathNV(resultPath, srcPath, transformType, transformValues); }
void glTranslated(GLdouble x, GLdouble y, GLdouble z) { functions()->glTranslated(x, y, z); }
void glTranslatef(GLfloat x, GLfloat y, GLfloat z) { functions()->glTranslatef(x, y, z); }
void glTranslatexOES(GLfixed x, GLfixed y, GLfixed z) { functions()->glTranslatexOES(x, y, z); }
void glUniform1d(GLint location, GLdouble x) { functions()->glUniform1d(location, x); }
void glUniform1dv(GLint location, GLsizei count, const GLdouble* value) { functions()->glUniform1dv(location, count, value); }
void glUniform1fARB(GLint location, GLfloat v0) { functions()->glUniform1fARB(location, v0); }
void glUniform1f(GLint location, GLfloat v0) { functions()->glUniform1f(location, v0); }
void glUniform1fvARB(GLint location, GLsizei count, const GLfloat* value) { functions()->glUniform1fvARB(location, count, value); }
void glUniform1fv(GLint location, GLsizei count, const GLfloat* value) { functions()->glUniform1fv(location, count, value); }
void glUniform1i64ARB(GLint location, GLint64 x) { functions()->glUniform1i64ARB(location, x); }
void glUniform1i64NV(GLint location, GLint64EXT x) { functions()->glUniform1i64NV(location, x); }
void glUniform1i64vARB(GLint location, GLsizei count, const GLint64* value) { functions()->glUniform1i64vARB(location, count, value); }
void glUniform1i64vNV(GLint location, GLsizei count, const GLint64EXT* value) { functions()->glUniform1i64vNV(location, count, value); }
void glUniform1iARB(GLint location, GLint v0) { functions()->glUniform1iARB(location, v0); }
void glUniform1i(GLint location, GLint v0) { functions()->glUniform1i(location, v0); }
void glUniform1ivARB(GLint location, GLsizei count, const GLint* value) { functions()->glUniform1ivARB(location, count, value); }
void glUniform1iv(GLint location, GLsizei count, const GLint* value) { functions()->glUniform1iv(location, count, value); }
void glUniform1ui64ARB(GLint location, GLuint64 x) { functions()->glUniform1ui64ARB(location, x); }
void glUniform1ui64NV(GLint location, GLuint64EXT x) { functions()->glUniform1ui64NV(location, x); }
void glUniform1ui64vARB(GLint location, GLsizei count, const GLuint64* value) { functions()->glUniform1ui64vARB(location, count, value); }
void glUniform1ui64vNV(GLint location, GLsizei count, const GLuint64EXT* value) { functions()->glUniform1ui64vNV(location, count, value); }
void glUniform1uiEXT(GLint location, GLuint v0) { functions()->glUniform1uiEXT(location, v0); }
void glUniform1ui(GLint location, GLuint v0) { functions()->glUniform1ui(location, v0); }
void glUniform1uivEXT(GLint location, GLsizei count, const GLuint* value) { functions()->glUniform1uivEXT(location, count, value); }
void glUniform1uiv(GLint location, GLsizei count, const GLuint* value) { functions()->glUniform1uiv(location, count, value); }
void glUniform2d(GLint location, GLdouble x, GLdouble y) { functions()->glUniform2d(location, x, y); }
void glUniform2dv(GLint location, GLsizei count, const GLdouble* value) { functions()->glUniform2dv(location, count, value); }
void glUniform2fARB(GLint location, GLfloat v0, GLfloat v1) { functions()->glUniform2fARB(location, v0, v1); }
void glUniform2f(GLint location, GLfloat v0, GLfloat v1) { functions()->glUniform2f(location, v0, v1); }
void glUniform2fvARB(GLint location, GLsizei count, const GLfloat* value) { functions()->glUniform2fvARB(location, count, value); }
void glUniform2fv(GLint location, GLsizei count, const GLfloat* value) { functions()->glUniform2fv(location, count, value); }
void glUniform2i64ARB(GLint location, GLint64 x, GLint64 y) { functions()->glUniform2i64ARB(location, x, y); }
void glUniform2i64NV(GLint location, GLint64EXT x, GLint64EXT y) { functions()->glUniform2i64NV(location, x, y); }
void glUniform2i64vARB(GLint location, GLsizei count, const GLint64* value) { functions()->glUniform2i64vARB(location, count, value); }
void glUniform2i64vNV(GLint location, GLsizei count, const GLint64EXT* value) { functions()->glUniform2i64vNV(location, count, value); }
void glUniform2iARB(GLint location, GLint v0, GLint v1) { functions()->glUniform2iARB(location, v0, v1); }
void glUniform2i(GLint location, GLint v0, GLint v1) { functions()->glUniform2i(location, v0, v1); }
void glUniform2ivARB(GLint location, GLsizei count, const GLint* value) { functions()->glUniform2ivARB(location, count, value); }
void glUniform2iv(GLint location, GLsizei count, const GLint* value) { functions()->glUniform2iv(location, count, value); }
void glUniform2ui64ARB(GLint location, GLuint64 x, GLuint64 y) { functions()->glUniform2ui64ARB(location, x, y); }
void glUniform2ui64NV(GLint location, GLuint64EXT x, GLuint64EXT y) { functions()->glUniform2ui64NV(location, x, y); }
void glUniform2ui64vARB(GLint location, GLsizei count, const GLuint64* value) { functions()->glUniform2ui64vARB(location, count, value); }
void glUniform2ui64vNV(GLint location, GLsizei count, const GLuint64EXT* value) { functions()->glUniform2ui64vNV(location, count, value); }
void glUniform2uiEXT(GLint location, GLuint v0, GLuint v1) { functions()->glUniform2uiEXT(location, v0, v1); }
void glUniform2ui(GLint location, GLuint v0, GLuint v1) { functions()->glUniform2ui(location, v0, v1); }
void glUniform2uivEXT(GLint location, GLsizei count, const GLuint* value) { functions()->glUniform2uivEXT(location, count, value); }
void glUniform2uiv(GLint location, GLsizei count, const GLuint* value) { functions()->glUniform2uiv(location, count, value); }
void glUniform3d(GLint location, GLdouble x, GLdouble y, GLdouble z) { functions()->glUniform3d(location, x, y, z); }
void glUniform3dv(GLint location, GLsizei count, const GLdouble* value) { functions()->glUniform3dv(location, count, value); }
void glUniform3fARB(GLint location, GLfloat v0, GLfloat v1, GLfloat v2) { functions()->glUniform3fARB(location, v0, v1, v2); }
void glUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2) { functions()->glUniform3f(location, v0, v1, v2); }
void glUniform3fvARB(GLint location, GLsizei count, const GLfloat* value) { functions()->glUniform3fvARB(location, count, value); }
void glUniform3fv(GLint location, GLsizei count, const GLfloat* value) { functions()->glUniform3fv(location, count, value); }
void glUniform3i64ARB(GLint location, GLint64 x, GLint64 y, GLint64 z) { functions()->glUniform3i64ARB(location, x, y, z); }
void glUniform3i64NV(GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z) { functions()->glUniform3i64NV(location, x, y, z); }
void glUniform3i64vARB(GLint location, GLsizei count, const GLint64* value) { functions()->glUniform3i64vARB(location, count, value); }
void glUniform3i64vNV(GLint location, GLsizei count, const GLint64EXT* value) { functions()->glUniform3i64vNV(location, count, value); }
void glUniform3iARB(GLint location, GLint v0, GLint v1, GLint v2) { functions()->glUniform3iARB(location, v0, v1, v2); }
void glUniform3i(GLint location, GLint v0, GLint v1, GLint v2) { functions()->glUniform3i(location, v0, v1, v2); }
void glUniform3ivARB(GLint location, GLsizei count, const GLint* value) { functions()->glUniform3ivARB(location, count, value); }
void glUniform3iv(GLint location, GLsizei count, const GLint* value) { functions()->glUniform3iv(location, count, value); }
void glUniform3ui64ARB(GLint location, GLuint64 x, GLuint64 y, GLuint64 z) { functions()->glUniform3ui64ARB(location, x, y, z); }
void glUniform3ui64NV(GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z) { functions()->glUniform3ui64NV(location, x, y, z); }
void glUniform3ui64vARB(GLint location, GLsizei count, const GLuint64* value) { functions()->glUniform3ui64vARB(location, count, value); }
void glUniform3ui64vNV(GLint location, GLsizei count, const GLuint64EXT* value) { functions()->glUniform3ui64vNV(location, count, value); }
void glUniform3uiEXT(GLint location, GLuint v0, GLuint v1, GLuint v2) { functions()->glUniform3uiEXT(location, v0, v1, v2); }
void glUniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2) { functions()->glUniform3ui(location, v0, v1, v2); }
void glUniform3uivEXT(GLint location, GLsizei count, const GLuint* value) { functions()->glUniform3uivEXT(location, count, value); }
void glUniform3uiv(GLint location, GLsizei count, const GLuint* value) { functions()->glUniform3uiv(location, count, value); }
void glUniform4d(GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w) { functions()->glUniform4d(location, x, y, z, w); }
void glUniform4dv(GLint location, GLsizei count, const GLdouble* value) { functions()->glUniform4dv(location, count, value); }
void glUniform4fARB(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) { functions()->glUniform4fARB(location, v0, v1, v2, v3); }
void glUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) { functions()->glUniform4f(location, v0, v1, v2, v3); }
void glUniform4fvARB(GLint location, GLsizei count, const GLfloat* value) { functions()->glUniform4fvARB(location, count, value); }
void glUniform4fv(GLint location, GLsizei count, const GLfloat* value) { functions()->glUniform4fv(location, count, value); }
void glUniform4i64ARB(GLint location, GLint64 x, GLint64 y, GLint64 z, GLint64 w) { functions()->glUniform4i64ARB(location, x, y, z, w); }
void glUniform4i64NV(GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w) { functions()->glUniform4i64NV(location, x, y, z, w); }
void glUniform4i64vARB(GLint location, GLsizei count, const GLint64* value) { functions()->glUniform4i64vARB(location, count, value); }
void glUniform4i64vNV(GLint location, GLsizei count, const GLint64EXT* value) { functions()->glUniform4i64vNV(location, count, value); }
void glUniform4iARB(GLint location, GLint v0, GLint v1, GLint v2, GLint v3) { functions()->glUniform4iARB(location, v0, v1, v2, v3); }
void glUniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3) { functions()->glUniform4i(location, v0, v1, v2, v3); }
void glUniform4ivARB(GLint location, GLsizei count, const GLint* value) { functions()->glUniform4ivARB(location, count, value); }
void glUniform4iv(GLint location, GLsizei count, const GLint* value) { functions()->glUniform4iv(location, count, value); }
void glUniform4ui64ARB(GLint location, GLuint64 x, GLuint64 y, GLuint64 z, GLuint64 w) { functions()->glUniform4ui64ARB(location, x, y, z, w); }
void glUniform4ui64NV(GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w) { functions()->glUniform4ui64NV(location, x, y, z, w); }
void glUniform4ui64vARB(GLint location, GLsizei count, const GLuint64* value) { functions()->glUniform4ui64vARB(location, count, value); }
void glUniform4ui64vNV(GLint location, GLsizei count, const GLuint64EXT* value) { functions()->glUniform4ui64vNV(location, count, value); }
void glUniform4uiEXT(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3) { functions()->glUniform4uiEXT(location, v0, v1, v2, v3); }
void glUniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3) { functions()->glUniform4ui(location, v0, v1, v2, v3); }
void glUniform4uivEXT(GLint location, GLsizei count, const GLuint* value) { functions()->glUniform4uivEXT(location, count, value); }
void glUniform4uiv(GLint location, GLsizei count, const GLuint* value) { functions()->glUniform4uiv(location, count, value); }
void glUniformBlockBinding(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding) { functions()->glUniformBlockBinding(program, uniformBlockIndex, uniformBlockBinding); }
void glUniformBufferEXT(GLuint program, GLint location, GLuint buffer) { functions()->glUniformBufferEXT(program, location, buffer); }
void glUniformHandleui64ARB(GLint location, GLuint64 value) { functions()->glUniformHandleui64ARB(location, value); }
void glUniformHandleui64NV(GLint location, GLuint64 value) { functions()->glUniformHandleui64NV(location, value); }
void glUniformHandleui64vARB(GLint location, GLsizei count, const GLuint64* value) { functions()->glUniformHandleui64vARB(location, count, value); }
void glUniformHandleui64vNV(GLint location, GLsizei count, const GLuint64* value) { functions()->glUniformHandleui64vNV(location, count, value); }
void glUniformMatrix2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) { functions()->glUniformMatrix2dv(location, count, transpose, value); }
void glUniformMatrix2fvARB(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) { functions()->glUniformMatrix2fvARB(location, count, transpose, value); }
void glUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) { functions()->glUniformMatrix2fv(location, count, transpose, value); }
void glUniformMatrix2x3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) { functions()->glUniformMatrix2x3dv(location, count, transpose, value); }
void glUniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) { functions()->glUniformMatrix2x3fv(location, count, transpose, value); }
void glUniformMatrix2x4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) { functions()->glUniformMatrix2x4dv(location, count, transpose, value); }
void glUniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) { functions()->glUniformMatrix2x4fv(location, count, transpose, value); }
void glUniformMatrix3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) { functions()->glUniformMatrix3dv(location, count, transpose, value); }
void glUniformMatrix3fvARB(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) { functions()->glUniformMatrix3fvARB(location, count, transpose, value); }
void glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) { functions()->glUniformMatrix3fv(location, count, transpose, value); }
void glUniformMatrix3x2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) { functions()->glUniformMatrix3x2dv(location, count, transpose, value); }
void glUniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) { functions()->glUniformMatrix3x2fv(location, count, transpose, value); }
void glUniformMatrix3x4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) { functions()->glUniformMatrix3x4dv(location, count, transpose, value); }
void glUniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) { functions()->glUniformMatrix3x4fv(location, count, transpose, value); }
void glUniformMatrix4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) { functions()->glUniformMatrix4dv(location, count, transpose, value); }
void glUniformMatrix4fvARB(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) { functions()->glUniformMatrix4fvARB(location, count, transpose, value); }
void glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) { functions()->glUniformMatrix4fv(location, count, transpose, value); }
void glUniformMatrix4x2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) { functions()->glUniformMatrix4x2dv(location, count, transpose, value); }
void glUniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) { functions()->glUniformMatrix4x2fv(location, count, transpose, value); }
void glUniformMatrix4x3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) { functions()->glUniformMatrix4x3dv(location, count, transpose, value); }
void glUniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) { functions()->glUniformMatrix4x3fv(location, count, transpose, value); }
void glUniformSubroutinesuiv(GLenum shadertype, GLsizei count, const GLuint* indices) { functions()->glUniformSubroutinesuiv(shadertype, count, indices); }
void glUniformui64NV(GLint location, GLuint64EXT value) { functions()->glUniformui64NV(location, value); }
void glUniformui64vNV(GLint location, GLsizei count, const GLuint64EXT* value) { functions()->glUniformui64vNV(location, count, value); }
void glUnlockArraysEXT() { functions()->glUnlockArraysEXT(); }
void glUnmapObjectBufferATI(GLuint buffer) { functions()->glUnmapObjectBufferATI(buffer); }
void glUnmapTexture2DINTEL(GLuint texture, GLint level) { functions()->glUnmapTexture2DINTEL(texture, level); }
void glUpdateObjectBufferATI(GLuint buffer, GLuint offset, GLsizei size, const void* pointer, GLenum preserve) { functions()->glUpdateObjectBufferATI(buffer, offset, size, pointer, preserve); }
void glUseProgram(GLuint program) { functions()->glUseProgram(program); }
void glUseProgramObjectARB(GLhandleARB programObj) { functions()->glUseProgramObjectARB(programObj); }
void glUseProgramStages(GLuint pipeline, GLbitfield stages, GLuint program) { functions()->glUseProgramStages(pipeline, stages, program); }
void glUseShaderProgramEXT(GLenum type, GLuint program) { functions()->glUseShaderProgramEXT(type, program); }
void glValidateProgramARB(GLhandleARB programObj) { functions()->glValidateProgramARB(programObj); }
void glValidateProgram(GLuint program) { functions()->glValidateProgram(program); }
void glValidateProgramPipeline(GLuint pipeline) { functions()->glValidateProgramPipeline(pipeline); }
void glVariantArrayObjectATI(GLuint id, GLenum type, GLsizei stride, GLuint buffer, GLuint offset) { functions()->glVariantArrayObjectATI(id, type, stride, buffer, offset); }
void glVariantbvEXT(GLuint id, const GLbyte* addr) { functions()->glVariantbvEXT(id, addr); }
void glVariantdvEXT(GLuint id, const GLdouble* addr) { functions()->glVariantdvEXT(id, addr); }
void glVariantfvEXT(GLuint id, const GLfloat* addr) { functions()->glVariantfvEXT(id, addr); }
void glVariantivEXT(GLuint id, const GLint* addr) { functions()->glVariantivEXT(id, addr); }
void glVariantPointerEXT(GLuint id, GLenum type, GLuint stride, const void* addr) { functions()->glVariantPointerEXT(id, type, stride, addr); }
void glVariantsvEXT(GLuint id, const GLshort* addr) { functions()->glVariantsvEXT(id, addr); }
void glVariantubvEXT(GLuint id, const GLubyte* addr) { functions()->glVariantubvEXT(id, addr); }
void glVariantuivEXT(GLuint id, const GLuint* addr) { functions()->glVariantuivEXT(id, addr); }
void glVariantusvEXT(GLuint id, const GLushort* addr) { functions()->glVariantusvEXT(id, addr); }
void glVDPAUFiniNV() { functions()->glVDPAUFiniNV(); }
void glVDPAUGetSurfaceivNV(GLvdpauSurfaceNV surface, GLenum pname, GLsizei bufSize, GLsizei* length, GLint* values) { functions()->glVDPAUGetSurfaceivNV(surface, pname, bufSize, length, values); }
void glVDPAUInitNV(const void* vdpDevice, const void* getProcAddress) { functions()->glVDPAUInitNV(vdpDevice, getProcAddress); }
void glVDPAUMapSurfacesNV(GLsizei numSurfaces, const GLvdpauSurfaceNV* surfaces) { functions()->glVDPAUMapSurfacesNV(numSurfaces, surfaces); }
void glVDPAUSurfaceAccessNV(GLvdpauSurfaceNV surface, GLenum access) { functions()->glVDPAUSurfaceAccessNV(surface, access); }
void glVDPAUUnmapSurfacesNV(GLsizei numSurface, const GLvdpauSurfaceNV* surfaces) { functions()->glVDPAUUnmapSurfacesNV(numSurface, surfaces); }
void glVDPAUUnregisterSurfaceNV(GLvdpauSurfaceNV surface) { functions()->glVDPAUUnregisterSurfaceNV(surface); }
void glVertex2bOES(GLbyte x, GLbyte y) { functions()->glVertex2bOES(x, y); }
void glVertex2bvOES(const GLbyte* coords) { functions()->glVertex2bvOES(coords); }
void glVertex2d(GLdouble x, GLdouble y) { functions()->glVertex2d(x, y); }
void glVertex2dv(const GLdouble* v) { functions()->glVertex2dv(v); }
void glVertex2f(GLfloat x, GLfloat y) { functions()->glVertex2f(x, y); }
void glVertex2fv(const GLfloat* v) { functions()->glVertex2fv(v); }
void glVertex2hNV(GLhalfNV x, GLhalfNV y) { functions()->glVertex2hNV(x, y); }
void glVertex2hvNV(const GLhalfNV* v) { functions()->glVertex2hvNV(v); }
void glVertex2i(GLint x, GLint y) { functions()->glVertex2i(x, y); }
void glVertex2iv(const GLint* v) { functions()->glVertex2iv(v); }
void glVertex2s(GLshort x, GLshort y) { functions()->glVertex2s(x, y); }
void glVertex2sv(const GLshort* v) { functions()->glVertex2sv(v); }
void glVertex2xOES(GLfixed x) { functions()->glVertex2xOES(x); }
void glVertex2xvOES(const GLfixed* coords) { functions()->glVertex2xvOES(coords); }
void glVertex3bOES(GLbyte x, GLbyte y, GLbyte z) { functions()->glVertex3bOES(x, y, z); }
void glVertex3bvOES(const GLbyte* coords) { functions()->glVertex3bvOES(coords); }
void glVertex3d(GLdouble x, GLdouble y, GLdouble z) { functions()->glVertex3d(x, y, z); }
void glVertex3dv(const GLdouble* v) { functions()->glVertex3dv(v); }
void glVertex3f(GLfloat x, GLfloat y, GLfloat z) { functions()->glVertex3f(x, y, z); }
void glVertex3fv(const GLfloat* v) { functions()->glVertex3fv(v); }
void glVertex3hNV(GLhalfNV x, GLhalfNV y, GLhalfNV z) { functions()->glVertex3hNV(x, y, z); }
void glVertex3hvNV(const GLhalfNV* v) { functions()->glVertex3hvNV(v); }
void glVertex3i(GLint x, GLint y, GLint z) { functions()->glVertex3i(x, y, z); }
void glVertex3iv(const GLint* v) { functions()->glVertex3iv(v); }
void glVertex3s(GLshort x, GLshort y, GLshort z) { functions()->glVertex3s(x, y, z); }
void glVertex3sv(const GLshort* v) { functions()->glVertex3sv(v); }
void glVertex3xOES(GLfixed x, GLfixed y) { functions()->glVertex3xOES(x, y); }
void glVertex3xvOES(const GLfixed* coords) { functions()->glVertex3xvOES(coords); }
void glVertex4bOES(GLbyte x, GLbyte y, GLbyte z, GLbyte w) { functions()->glVertex4bOES(x, y, z, w); }
void glVertex4bvOES(const GLbyte* coords) { functions()->glVertex4bvOES(coords); }
void glVertex4d(GLdouble x, GLdouble y, GLdouble z, GLdouble w) { functions()->glVertex4d(x, y, z, w); }
void glVertex4dv(const GLdouble* v) { functions()->glVertex4dv(v); }
void glVertex4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w) { functions()->glVertex4f(x, y, z, w); }
void glVertex4fv(const GLfloat* v) { functions()->glVertex4fv(v); }
void glVertex4hNV(GLhalfNV x, GLhalfNV y, GLhalfNV z, GLhalfNV w) { functions()->glVertex4hNV(x, y, z, w); }
void glVertex4hvNV(const GLhalfNV* v) { functions()->glVertex4hvNV(v); }
void glVertex4i(GLint x, GLint y, GLint z, GLint w) { functions()->glVertex4i(x, y, z, w); }
void glVertex4iv(const GLint* v) { functions()->glVertex4iv(v); }
void glVertex4s(GLshort x, GLshort y, GLshort z, GLshort w) { functions()->glVertex4s(x, y, z, w); }
void glVertex4sv(const GLshort* v) { functions()->glVertex4sv(v); }
void glVertex4xOES(GLfixed x, GLfixed y, GLfixed z) { functions()->glVertex4xOES(x, y, z); }
void glVertex4xvOES(const GLfixed* coords) { functions()->glVertex4xvOES(coords); }
void glVertexArrayAttribBinding(GLuint vaobj, GLuint attribindex, GLuint bindingindex) { functions()->glVertexArrayAttribBinding(vaobj, attribindex, bindingindex); }
void glVertexArrayAttribFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset) { functions()->glVertexArrayAttribFormat(vaobj, attribindex, size, type, normalized, relativeoffset); }
void glVertexArrayAttribIFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset) { functions()->glVertexArrayAttribIFormat(vaobj, attribindex, size, type, relativeoffset); }
void glVertexArrayAttribLFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset) { functions()->glVertexArrayAttribLFormat(vaobj, attribindex, size, type, relativeoffset); }
void glVertexArrayBindingDivisor(GLuint vaobj, GLuint bindingindex, GLuint divisor) { functions()->glVertexArrayBindingDivisor(vaobj, bindingindex, divisor); }
void glVertexArrayBindVertexBufferEXT(GLuint vaobj, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride) { functions()->glVertexArrayBindVertexBufferEXT(vaobj, bindingindex, buffer, offset, stride); }
void glVertexArrayColorOffsetEXT(GLuint vaobj, GLuint buffer, GLint size, GLenum type, GLsizei stride, GLintptr offset) { functions()->glVertexArrayColorOffsetEXT(vaobj, buffer, size, type, stride, offset); }
void glVertexArrayEdgeFlagOffsetEXT(GLuint vaobj, GLuint buffer, GLsizei stride, GLintptr offset) { functions()->glVertexArrayEdgeFlagOffsetEXT(vaobj, buffer, stride, offset); }
void glVertexArrayElementBuffer(GLuint vaobj, GLuint buffer) { functions()->glVertexArrayElementBuffer(vaobj, buffer); }
void glVertexArrayFogCoordOffsetEXT(GLuint vaobj, GLuint buffer, GLenum type, GLsizei stride, GLintptr offset) { functions()->glVertexArrayFogCoordOffsetEXT(vaobj, buffer, type, stride, offset); }
void glVertexArrayIndexOffsetEXT(GLuint vaobj, GLuint buffer, GLenum type, GLsizei stride, GLintptr offset) { functions()->glVertexArrayIndexOffsetEXT(vaobj, buffer, type, stride, offset); }
void glVertexArrayMultiTexCoordOffsetEXT(GLuint vaobj, GLuint buffer, GLenum texunit, GLint size, GLenum type, GLsizei stride, GLintptr offset) { functions()->glVertexArrayMultiTexCoordOffsetEXT(vaobj, buffer, texunit, size, type, stride, offset); }
void glVertexArrayNormalOffsetEXT(GLuint vaobj, GLuint buffer, GLenum type, GLsizei stride, GLintptr offset) { functions()->glVertexArrayNormalOffsetEXT(vaobj, buffer, type, stride, offset); }
void glVertexArrayParameteriAPPLE(GLenum pname, GLint param) { functions()->glVertexArrayParameteriAPPLE(pname, param); }
void glVertexArrayRangeAPPLE(GLsizei length, void* pointer) { functions()->glVertexArrayRangeAPPLE(length, pointer); }
void glVertexArrayRangeNV(GLsizei length, const void* pointer) { functions()->glVertexArrayRangeNV(length, pointer); }
void glVertexArraySecondaryColorOffsetEXT(GLuint vaobj, GLuint buffer, GLint size, GLenum type, GLsizei stride, GLintptr offset) { functions()->glVertexArraySecondaryColorOffsetEXT(vaobj, buffer, size, type, stride, offset); }
void glVertexArrayTexCoordOffsetEXT(GLuint vaobj, GLuint buffer, GLint size, GLenum type, GLsizei stride, GLintptr offset) { functions()->glVertexArrayTexCoordOffsetEXT(vaobj, buffer, size, type, stride, offset); }
void glVertexArrayVertexAttribBindingEXT(GLuint vaobj, GLuint attribindex, GLuint bindingindex) { functions()->glVertexArrayVertexAttribBindingEXT(vaobj, attribindex, bindingindex); }
void glVertexArrayVertexAttribDivisorEXT(GLuint vaobj, GLuint index, GLuint divisor) { functions()->glVertexArrayVertexAttribDivisorEXT(vaobj, index, divisor); }
void glVertexArrayVertexAttribFormatEXT(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset) { functions()->glVertexArrayVertexAttribFormatEXT(vaobj, attribindex, size, type, normalized, relativeoffset); }
void glVertexArrayVertexAttribIFormatEXT(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset) { functions()->glVertexArrayVertexAttribIFormatEXT(vaobj, attribindex, size, type, relativeoffset); }
void glVertexArrayVertexAttribIOffsetEXT(GLuint vaobj, GLuint buffer, GLuint index, GLint size, GLenum type, GLsizei stride, GLintptr offset) { functions()->glVertexArrayVertexAttribIOffsetEXT(vaobj, buffer, index, size, type, stride, offset); }
void glVertexArrayVertexAttribLFormatEXT(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset) { functions()->glVertexArrayVertexAttribLFormatEXT(vaobj, attribindex, size, type, relativeoffset); }
void glVertexArrayVertexAttribLOffsetEXT(GLuint vaobj, GLuint buffer, GLuint index, GLint size, GLenum type, GLsizei stride, GLintptr offset) { functions()->glVertexArrayVertexAttribLOffsetEXT(vaobj, buffer, index, size, type, stride, offset); }
void glVertexArrayVertexAttribOffsetEXT(GLuint vaobj, GLuint buffer, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLintptr offset) { functions()->glVertexArrayVertexAttribOffsetEXT(vaobj, buffer, index, size, type, normalized, stride, offset); }
void glVertexArrayVertexBindingDivisorEXT(GLuint vaobj, GLuint bindingindex, GLuint divisor) { functions()->glVertexArrayVertexBindingDivisorEXT(vaobj, bindingindex, divisor); }
void glVertexArrayVertexBuffer(GLuint vaobj, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride) { functions()->glVertexArrayVertexBuffer(vaobj, bindingindex, buffer, offset, stride); }
void glVertexArrayVertexBuffers(GLuint vaobj, GLuint first, GLsizei count, const GLuint* buffers, const GLintptr* offsets, const GLsizei* strides) { functions()->glVertexArrayVertexBuffers(vaobj, first, count, buffers, offsets, strides); }
void glVertexArrayVertexOffsetEXT(GLuint vaobj, GLuint buffer, GLint size, GLenum type, GLsizei stride, GLintptr offset) { functions()->glVertexArrayVertexOffsetEXT(vaobj, buffer, size, type, stride, offset); }
void glVertexAttrib1dARB(GLuint index, GLdouble x) { functions()->glVertexAttrib1dARB(index, x); }
void glVertexAttrib1d(GLuint index, GLdouble x) { functions()->glVertexAttrib1d(index, x); }
void glVertexAttrib1dNV(GLuint index, GLdouble x) { functions()->glVertexAttrib1dNV(index, x); }
void glVertexAttrib1dvARB(GLuint index, const GLdouble* v) { functions()->glVertexAttrib1dvARB(index, v); }
void glVertexAttrib1dv(GLuint index, const GLdouble* v) { functions()->glVertexAttrib1dv(index, v); }
void glVertexAttrib1dvNV(GLuint index, const GLdouble* v) { functions()->glVertexAttrib1dvNV(index, v); }
void glVertexAttrib1fARB(GLuint index, GLfloat x) { functions()->glVertexAttrib1fARB(index, x); }
void glVertexAttrib1f(GLuint index, GLfloat x) { functions()->glVertexAttrib1f(index, x); }
void glVertexAttrib1fNV(GLuint index, GLfloat x) { functions()->glVertexAttrib1fNV(index, x); }
void glVertexAttrib1fvARB(GLuint index, const GLfloat* v) { functions()->glVertexAttrib1fvARB(index, v); }
void glVertexAttrib1fv(GLuint index, const GLfloat* v) { functions()->glVertexAttrib1fv(index, v); }
void glVertexAttrib1fvNV(GLuint index, const GLfloat* v) { functions()->glVertexAttrib1fvNV(index, v); }
void glVertexAttrib1hNV(GLuint index, GLhalfNV x) { functions()->glVertexAttrib1hNV(index, x); }
void glVertexAttrib1hvNV(GLuint index, const GLhalfNV* v) { functions()->glVertexAttrib1hvNV(index, v); }
void glVertexAttrib1sARB(GLuint index, GLshort x) { functions()->glVertexAttrib1sARB(index, x); }
void glVertexAttrib1s(GLuint index, GLshort x) { functions()->glVertexAttrib1s(index, x); }
void glVertexAttrib1sNV(GLuint index, GLshort x) { functions()->glVertexAttrib1sNV(index, x); }
void glVertexAttrib1svARB(GLuint index, const GLshort* v) { functions()->glVertexAttrib1svARB(index, v); }
void glVertexAttrib1sv(GLuint index, const GLshort* v) { functions()->glVertexAttrib1sv(index, v); }
void glVertexAttrib1svNV(GLuint index, const GLshort* v) { functions()->glVertexAttrib1svNV(index, v); }
void glVertexAttrib2dARB(GLuint index, GLdouble x, GLdouble y) { functions()->glVertexAttrib2dARB(index, x, y); }
void glVertexAttrib2d(GLuint index, GLdouble x, GLdouble y) { functions()->glVertexAttrib2d(index, x, y); }
void glVertexAttrib2dNV(GLuint index, GLdouble x, GLdouble y) { functions()->glVertexAttrib2dNV(index, x, y); }
void glVertexAttrib2dvARB(GLuint index, const GLdouble* v) { functions()->glVertexAttrib2dvARB(index, v); }
void glVertexAttrib2dv(GLuint index, const GLdouble* v) { functions()->glVertexAttrib2dv(index, v); }
void glVertexAttrib2dvNV(GLuint index, const GLdouble* v) { functions()->glVertexAttrib2dvNV(index, v); }
void glVertexAttrib2fARB(GLuint index, GLfloat x, GLfloat y) { functions()->glVertexAttrib2fARB(index, x, y); }
void glVertexAttrib2f(GLuint index, GLfloat x, GLfloat y) { functions()->glVertexAttrib2f(index, x, y); }
void glVertexAttrib2fNV(GLuint index, GLfloat x, GLfloat y) { functions()->glVertexAttrib2fNV(index, x, y); }
void glVertexAttrib2fvARB(GLuint index, const GLfloat* v) { functions()->glVertexAttrib2fvARB(index, v); }
void glVertexAttrib2fv(GLuint index, const GLfloat* v) { functions()->glVertexAttrib2fv(index, v); }
void glVertexAttrib2fvNV(GLuint index, const GLfloat* v) { functions()->glVertexAttrib2fvNV(index, v); }
void glVertexAttrib2hNV(GLuint index, GLhalfNV x, GLhalfNV y) { functions()->glVertexAttrib2hNV(index, x, y); }
void glVertexAttrib2hvNV(GLuint index, const GLhalfNV* v) { functions()->glVertexAttrib2hvNV(index, v); }
void glVertexAttrib2sARB(GLuint index, GLshort x, GLshort y) { functions()->glVertexAttrib2sARB(index, x, y); }
void glVertexAttrib2s(GLuint index, GLshort x, GLshort y) { functions()->glVertexAttrib2s(index, x, y); }
void glVertexAttrib2sNV(GLuint index, GLshort x, GLshort y) { functions()->glVertexAttrib2sNV(index, x, y); }
void glVertexAttrib2svARB(GLuint index, const GLshort* v) { functions()->glVertexAttrib2svARB(index, v); }
void glVertexAttrib2sv(GLuint index, const GLshort* v) { functions()->glVertexAttrib2sv(index, v); }
void glVertexAttrib2svNV(GLuint index, const GLshort* v) { functions()->glVertexAttrib2svNV(index, v); }
void glVertexAttrib3dARB(GLuint index, GLdouble x, GLdouble y, GLdouble z) { functions()->glVertexAttrib3dARB(index, x, y, z); }
void glVertexAttrib3d(GLuint index, GLdouble x, GLdouble y, GLdouble z) { functions()->glVertexAttrib3d(index, x, y, z); }
void glVertexAttrib3dNV(GLuint index, GLdouble x, GLdouble y, GLdouble z) { functions()->glVertexAttrib3dNV(index, x, y, z); }
void glVertexAttrib3dvARB(GLuint index, const GLdouble* v) { functions()->glVertexAttrib3dvARB(index, v); }
void glVertexAttrib3dv(GLuint index, const GLdouble* v) { functions()->glVertexAttrib3dv(index, v); }
void glVertexAttrib3dvNV(GLuint index, const GLdouble* v) { functions()->glVertexAttrib3dvNV(index, v); }
void glVertexAttrib3fARB(GLuint index, GLfloat x, GLfloat y, GLfloat z) { functions()->glVertexAttrib3fARB(index, x, y, z); }
void glVertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z) { functions()->glVertexAttrib3f(index, x, y, z); }
void glVertexAttrib3fNV(GLuint index, GLfloat x, GLfloat y, GLfloat z) { functions()->glVertexAttrib3fNV(index, x, y, z); }
void glVertexAttrib3fvARB(GLuint index, const GLfloat* v) { functions()->glVertexAttrib3fvARB(index, v); }
void glVertexAttrib3fv(GLuint index, const GLfloat* v) { functions()->glVertexAttrib3fv(index, v); }
void glVertexAttrib3fvNV(GLuint index, const GLfloat* v) { functions()->glVertexAttrib3fvNV(index, v); }
void glVertexAttrib3hNV(GLuint index, GLhalfNV x, GLhalfNV y, GLhalfNV z) { functions()->glVertexAttrib3hNV(index, x, y, z); }
void glVertexAttrib3hvNV(GLuint index, const GLhalfNV* v) { functions()->glVertexAttrib3hvNV(index, v); }
void glVertexAttrib3sARB(GLuint index, GLshort x, GLshort y, GLshort z) { functions()->glVertexAttrib3sARB(index, x, y, z); }
void glVertexAttrib3s(GLuint index, GLshort x, GLshort y, GLshort z) { functions()->glVertexAttrib3s(index, x, y, z); }
void glVertexAttrib3sNV(GLuint index, GLshort x, GLshort y, GLshort z) { functions()->glVertexAttrib3sNV(index, x, y, z); }
void glVertexAttrib3svARB(GLuint index, const GLshort* v) { functions()->glVertexAttrib3svARB(index, v); }
void glVertexAttrib3sv(GLuint index, const GLshort* v) { functions()->glVertexAttrib3sv(index, v); }
void glVertexAttrib3svNV(GLuint index, const GLshort* v) { functions()->glVertexAttrib3svNV(index, v); }
void glVertexAttrib4bvARB(GLuint index, const GLbyte* v) { functions()->glVertexAttrib4bvARB(index, v); }
void glVertexAttrib4bv(GLuint index, const GLbyte* v) { functions()->glVertexAttrib4bv(index, v); }
void glVertexAttrib4dARB(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) { functions()->glVertexAttrib4dARB(index, x, y, z, w); }
void glVertexAttrib4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) { functions()->glVertexAttrib4d(index, x, y, z, w); }
void glVertexAttrib4dNV(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) { functions()->glVertexAttrib4dNV(index, x, y, z, w); }
void glVertexAttrib4dvARB(GLuint index, const GLdouble* v) { functions()->glVertexAttrib4dvARB(index, v); }
void glVertexAttrib4dv(GLuint index, const GLdouble* v) { functions()->glVertexAttrib4dv(index, v); }
void glVertexAttrib4dvNV(GLuint index, const GLdouble* v) { functions()->glVertexAttrib4dvNV(index, v); }
void glVertexAttrib4fARB(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) { functions()->glVertexAttrib4fARB(index, x, y, z, w); }
void glVertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) { functions()->glVertexAttrib4f(index, x, y, z, w); }
void glVertexAttrib4fNV(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) { functions()->glVertexAttrib4fNV(index, x, y, z, w); }
void glVertexAttrib4fvARB(GLuint index, const GLfloat* v) { functions()->glVertexAttrib4fvARB(index, v); }
void glVertexAttrib4fv(GLuint index, const GLfloat* v) { functions()->glVertexAttrib4fv(index, v); }
void glVertexAttrib4fvNV(GLuint index, const GLfloat* v) { functions()->glVertexAttrib4fvNV(index, v); }
void glVertexAttrib4hNV(GLuint index, GLhalfNV x, GLhalfNV y, GLhalfNV z, GLhalfNV w) { functions()->glVertexAttrib4hNV(index, x, y, z, w); }
void glVertexAttrib4hvNV(GLuint index, const GLhalfNV* v) { functions()->glVertexAttrib4hvNV(index, v); }
void glVertexAttrib4ivARB(GLuint index, const GLint* v) { functions()->glVertexAttrib4ivARB(index, v); }
void glVertexAttrib4iv(GLuint index, const GLint* v) { functions()->glVertexAttrib4iv(index, v); }
void glVertexAttrib4NbvARB(GLuint index, const GLbyte* v) { functions()->glVertexAttrib4NbvARB(index, v); }
void glVertexAttrib4Nbv(GLuint index, const GLbyte* v) { functions()->glVertexAttrib4Nbv(index, v); }
void glVertexAttrib4NivARB(GLuint index, const GLint* v) { functions()->glVertexAttrib4NivARB(index, v); }
void glVertexAttrib4Niv(GLuint index, const GLint* v) { functions()->glVertexAttrib4Niv(index, v); }
void glVertexAttrib4NsvARB(GLuint index, const GLshort* v) { functions()->glVertexAttrib4NsvARB(index, v); }
void glVertexAttrib4Nsv(GLuint index, const GLshort* v) { functions()->glVertexAttrib4Nsv(index, v); }
void glVertexAttrib4NubARB(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w) { functions()->glVertexAttrib4NubARB(index, x, y, z, w); }
void glVertexAttrib4Nub(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w) { functions()->glVertexAttrib4Nub(index, x, y, z, w); }
void glVertexAttrib4NubvARB(GLuint index, const GLubyte* v) { functions()->glVertexAttrib4NubvARB(index, v); }
void glVertexAttrib4Nubv(GLuint index, const GLubyte* v) { functions()->glVertexAttrib4Nubv(index, v); }
void glVertexAttrib4NuivARB(GLuint index, const GLuint* v) { functions()->glVertexAttrib4NuivARB(index, v); }
void glVertexAttrib4Nuiv(GLuint index, const GLuint* v) { functions()->glVertexAttrib4Nuiv(index, v); }
void glVertexAttrib4NusvARB(GLuint index, const GLushort* v) { functions()->glVertexAttrib4NusvARB(index, v); }
void glVertexAttrib4Nusv(GLuint index, const GLushort* v) { functions()->glVertexAttrib4Nusv(index, v); }
void glVertexAttrib4sARB(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w) { functions()->glVertexAttrib4sARB(index, x, y, z, w); }
void glVertexAttrib4s(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w) { functions()->glVertexAttrib4s(index, x, y, z, w); }
void glVertexAttrib4sNV(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w) { functions()->glVertexAttrib4sNV(index, x, y, z, w); }
void glVertexAttrib4svARB(GLuint index, const GLshort* v) { functions()->glVertexAttrib4svARB(index, v); }
void glVertexAttrib4sv(GLuint index, const GLshort* v) { functions()->glVertexAttrib4sv(index, v); }
void glVertexAttrib4svNV(GLuint index, const GLshort* v) { functions()->glVertexAttrib4svNV(index, v); }
void glVertexAttrib4ubNV(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w) { functions()->glVertexAttrib4ubNV(index, x, y, z, w); }
void glVertexAttrib4ubvARB(GLuint index, const GLubyte* v) { functions()->glVertexAttrib4ubvARB(index, v); }
void glVertexAttrib4ubv(GLuint index, const GLubyte* v) { functions()->glVertexAttrib4ubv(index, v); }
void glVertexAttrib4ubvNV(GLuint index, const GLubyte* v) { functions()->glVertexAttrib4ubvNV(index, v); }
void glVertexAttrib4uivARB(GLuint index, const GLuint* v) { functions()->glVertexAttrib4uivARB(index, v); }
void glVertexAttrib4uiv(GLuint index, const GLuint* v) { functions()->glVertexAttrib4uiv(index, v); }
void glVertexAttrib4usvARB(GLuint index, const GLushort* v) { functions()->glVertexAttrib4usvARB(index, v); }
void glVertexAttrib4usv(GLuint index, const GLushort* v) { functions()->glVertexAttrib4usv(index, v); }
void glVertexAttribArrayObjectATI(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLuint buffer, GLuint offset) { functions()->glVertexAttribArrayObjectATI(index, size, type, normalized, stride, buffer, offset); }
void glVertexAttribBinding(GLuint attribindex, GLuint bindingindex) { functions()->glVertexAttribBinding(attribindex, bindingindex); }
void glVertexAttribDivisorARB(GLuint index, GLuint divisor) { functions()->glVertexAttribDivisorARB(index, divisor); }
void glVertexAttribDivisor(GLuint index, GLuint divisor) { functions()->glVertexAttribDivisor(index, divisor); }
void glVertexAttribFormat(GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset) { functions()->glVertexAttribFormat(attribindex, size, type, normalized, relativeoffset); }
void glVertexAttribFormatNV(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride) { functions()->glVertexAttribFormatNV(index, size, type, normalized, stride); }
void glVertexAttribI1iEXT(GLuint index, GLint x) { functions()->glVertexAttribI1iEXT(index, x); }
void glVertexAttribI1i(GLuint index, GLint x) { functions()->glVertexAttribI1i(index, x); }
void glVertexAttribI1ivEXT(GLuint index, const GLint* v) { functions()->glVertexAttribI1ivEXT(index, v); }
void glVertexAttribI1iv(GLuint index, const GLint* v) { functions()->glVertexAttribI1iv(index, v); }
void glVertexAttribI1uiEXT(GLuint index, GLuint x) { functions()->glVertexAttribI1uiEXT(index, x); }
void glVertexAttribI1ui(GLuint index, GLuint x) { functions()->glVertexAttribI1ui(index, x); }
void glVertexAttribI1uivEXT(GLuint index, const GLuint* v) { functions()->glVertexAttribI1uivEXT(index, v); }
void glVertexAttribI1uiv(GLuint index, const GLuint* v) { functions()->glVertexAttribI1uiv(index, v); }
void glVertexAttribI2iEXT(GLuint index, GLint x, GLint y) { functions()->glVertexAttribI2iEXT(index, x, y); }
void glVertexAttribI2i(GLuint index, GLint x, GLint y) { functions()->glVertexAttribI2i(index, x, y); }
void glVertexAttribI2ivEXT(GLuint index, const GLint* v) { functions()->glVertexAttribI2ivEXT(index, v); }
void glVertexAttribI2iv(GLuint index, const GLint* v) { functions()->glVertexAttribI2iv(index, v); }
void glVertexAttribI2uiEXT(GLuint index, GLuint x, GLuint y) { functions()->glVertexAttribI2uiEXT(index, x, y); }
void glVertexAttribI2ui(GLuint index, GLuint x, GLuint y) { functions()->glVertexAttribI2ui(index, x, y); }
void glVertexAttribI2uivEXT(GLuint index, const GLuint* v) { functions()->glVertexAttribI2uivEXT(index, v); }
void glVertexAttribI2uiv(GLuint index, const GLuint* v) { functions()->glVertexAttribI2uiv(index, v); }
void glVertexAttribI3iEXT(GLuint index, GLint x, GLint y, GLint z) { functions()->glVertexAttribI3iEXT(index, x, y, z); }
void glVertexAttribI3i(GLuint index, GLint x, GLint y, GLint z) { functions()->glVertexAttribI3i(index, x, y, z); }
void glVertexAttribI3ivEXT(GLuint index, const GLint* v) { functions()->glVertexAttribI3ivEXT(index, v); }
void glVertexAttribI3iv(GLuint index, const GLint* v) { functions()->glVertexAttribI3iv(index, v); }
void glVertexAttribI3uiEXT(GLuint index, GLuint x, GLuint y, GLuint z) { functions()->glVertexAttribI3uiEXT(index, x, y, z); }
void glVertexAttribI3ui(GLuint index, GLuint x, GLuint y, GLuint z) { functions()->glVertexAttribI3ui(index, x, y, z); }
void glVertexAttribI3uivEXT(GLuint index, const GLuint* v) { functions()->glVertexAttribI3uivEXT(index, v); }
void glVertexAttribI3uiv(GLuint index, const GLuint* v) { functions()->glVertexAttribI3uiv(index, v); }
void glVertexAttribI4bvEXT(GLuint index, const GLbyte* v) { functions()->glVertexAttribI4bvEXT(index, v); }
void glVertexAttribI4bv(GLuint index, const GLbyte* v) { functions()->glVertexAttribI4bv(index, v); }
void glVertexAttribI4iEXT(GLuint index, GLint x, GLint y, GLint z, GLint w) { functions()->glVertexAttribI4iEXT(index, x, y, z, w); }
void glVertexAttribI4i(GLuint index, GLint x, GLint y, GLint z, GLint w) { functions()->glVertexAttribI4i(index, x, y, z, w); }
void glVertexAttribI4ivEXT(GLuint index, const GLint* v) { functions()->glVertexAttribI4ivEXT(index, v); }
void glVertexAttribI4iv(GLuint index, const GLint* v) { functions()->glVertexAttribI4iv(index, v); }
void glVertexAttribI4svEXT(GLuint index, const GLshort* v) { functions()->glVertexAttribI4svEXT(index, v); }
void glVertexAttribI4sv(GLuint index, const GLshort* v) { functions()->glVertexAttribI4sv(index, v); }
void glVertexAttribI4ubvEXT(GLuint index, const GLubyte* v) { functions()->glVertexAttribI4ubvEXT(index, v); }
void glVertexAttribI4ubv(GLuint index, const GLubyte* v) { functions()->glVertexAttribI4ubv(index, v); }
void glVertexAttribI4uiEXT(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w) { functions()->glVertexAttribI4uiEXT(index, x, y, z, w); }
void glVertexAttribI4ui(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w) { functions()->glVertexAttribI4ui(index, x, y, z, w); }
void glVertexAttribI4uivEXT(GLuint index, const GLuint* v) { functions()->glVertexAttribI4uivEXT(index, v); }
void glVertexAttribI4uiv(GLuint index, const GLuint* v) { functions()->glVertexAttribI4uiv(index, v); }
void glVertexAttribI4usvEXT(GLuint index, const GLushort* v) { functions()->glVertexAttribI4usvEXT(index, v); }
void glVertexAttribI4usv(GLuint index, const GLushort* v) { functions()->glVertexAttribI4usv(index, v); }
void glVertexAttribIFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset) { functions()->glVertexAttribIFormat(attribindex, size, type, relativeoffset); }
void glVertexAttribIFormatNV(GLuint index, GLint size, GLenum type, GLsizei stride) { functions()->glVertexAttribIFormatNV(index, size, type, stride); }
void glVertexAttribIPointerEXT(GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer) { functions()->glVertexAttribIPointerEXT(index, size, type, stride, pointer); }
void glVertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer) { functions()->glVertexAttribIPointer(index, size, type, stride, pointer); }
void glVertexAttribL1dEXT(GLuint index, GLdouble x) { functions()->glVertexAttribL1dEXT(index, x); }
void glVertexAttribL1d(GLuint index, GLdouble x) { functions()->glVertexAttribL1d(index, x); }
void glVertexAttribL1dvEXT(GLuint index, const GLdouble* v) { functions()->glVertexAttribL1dvEXT(index, v); }
void glVertexAttribL1dv(GLuint index, const GLdouble* v) { functions()->glVertexAttribL1dv(index, v); }
void glVertexAttribL1i64NV(GLuint index, GLint64EXT x) { functions()->glVertexAttribL1i64NV(index, x); }
void glVertexAttribL1i64vNV(GLuint index, const GLint64EXT* v) { functions()->glVertexAttribL1i64vNV(index, v); }
void glVertexAttribL1ui64ARB(GLuint index, GLuint64EXT x) { functions()->glVertexAttribL1ui64ARB(index, x); }
void glVertexAttribL1ui64NV(GLuint index, GLuint64EXT x) { functions()->glVertexAttribL1ui64NV(index, x); }
void glVertexAttribL1ui64vARB(GLuint index, const GLuint64EXT* v) { functions()->glVertexAttribL1ui64vARB(index, v); }
void glVertexAttribL1ui64vNV(GLuint index, const GLuint64EXT* v) { functions()->glVertexAttribL1ui64vNV(index, v); }
void glVertexAttribL2dEXT(GLuint index, GLdouble x, GLdouble y) { functions()->glVertexAttribL2dEXT(index, x, y); }
void glVertexAttribL2d(GLuint index, GLdouble x, GLdouble y) { functions()->glVertexAttribL2d(index, x, y); }
void glVertexAttribL2dvEXT(GLuint index, const GLdouble* v) { functions()->glVertexAttribL2dvEXT(index, v); }
void glVertexAttribL2dv(GLuint index, const GLdouble* v) { functions()->glVertexAttribL2dv(index, v); }
void glVertexAttribL2i64NV(GLuint index, GLint64EXT x, GLint64EXT y) { functions()->glVertexAttribL2i64NV(index, x, y); }
void glVertexAttribL2i64vNV(GLuint index, const GLint64EXT* v) { functions()->glVertexAttribL2i64vNV(index, v); }
void glVertexAttribL2ui64NV(GLuint index, GLuint64EXT x, GLuint64EXT y) { functions()->glVertexAttribL2ui64NV(index, x, y); }
void glVertexAttribL2ui64vNV(GLuint index, const GLuint64EXT* v) { functions()->glVertexAttribL2ui64vNV(index, v); }
void glVertexAttribL3dEXT(GLuint index, GLdouble x, GLdouble y, GLdouble z) { functions()->glVertexAttribL3dEXT(index, x, y, z); }
void glVertexAttribL3d(GLuint index, GLdouble x, GLdouble y, GLdouble z) { functions()->glVertexAttribL3d(index, x, y, z); }
void glVertexAttribL3dvEXT(GLuint index, const GLdouble* v) { functions()->glVertexAttribL3dvEXT(index, v); }
void glVertexAttribL3dv(GLuint index, const GLdouble* v) { functions()->glVertexAttribL3dv(index, v); }
void glVertexAttribL3i64NV(GLuint index, GLint64EXT x, GLint64EXT y, GLint64EXT z) { functions()->glVertexAttribL3i64NV(index, x, y, z); }
void glVertexAttribL3i64vNV(GLuint index, const GLint64EXT* v) { functions()->glVertexAttribL3i64vNV(index, v); }
void glVertexAttribL3ui64NV(GLuint index, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z) { functions()->glVertexAttribL3ui64NV(index, x, y, z); }
void glVertexAttribL3ui64vNV(GLuint index, const GLuint64EXT* v) { functions()->glVertexAttribL3ui64vNV(index, v); }
void glVertexAttribL4dEXT(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) { functions()->glVertexAttribL4dEXT(index, x, y, z, w); }
void glVertexAttribL4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) { functions()->glVertexAttribL4d(index, x, y, z, w); }
void glVertexAttribL4dvEXT(GLuint index, const GLdouble* v) { functions()->glVertexAttribL4dvEXT(index, v); }
void glVertexAttribL4dv(GLuint index, const GLdouble* v) { functions()->glVertexAttribL4dv(index, v); }
void glVertexAttribL4i64NV(GLuint index, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w) { functions()->glVertexAttribL4i64NV(index, x, y, z, w); }
void glVertexAttribL4i64vNV(GLuint index, const GLint64EXT* v) { functions()->glVertexAttribL4i64vNV(index, v); }
void glVertexAttribL4ui64NV(GLuint index, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w) { functions()->glVertexAttribL4ui64NV(index, x, y, z, w); }
void glVertexAttribL4ui64vNV(GLuint index, const GLuint64EXT* v) { functions()->glVertexAttribL4ui64vNV(index, v); }
void glVertexAttribLFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset) { functions()->glVertexAttribLFormat(attribindex, size, type, relativeoffset); }
void glVertexAttribLFormatNV(GLuint index, GLint size, GLenum type, GLsizei stride) { functions()->glVertexAttribLFormatNV(index, size, type, stride); }
void glVertexAttribLPointerEXT(GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer) { functions()->glVertexAttribLPointerEXT(index, size, type, stride, pointer); }
void glVertexAttribLPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer) { functions()->glVertexAttribLPointer(index, size, type, stride, pointer); }
void glVertexAttribP1ui(GLuint index, GLenum type, GLboolean normalized, GLuint value) { functions()->glVertexAttribP1ui(index, type, normalized, value); }
void glVertexAttribP1uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint* value) { functions()->glVertexAttribP1uiv(index, type, normalized, value); }
void glVertexAttribP2ui(GLuint index, GLenum type, GLboolean normalized, GLuint value) { functions()->glVertexAttribP2ui(index, type, normalized, value); }
void glVertexAttribP2uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint* value) { functions()->glVertexAttribP2uiv(index, type, normalized, value); }
void glVertexAttribP3ui(GLuint index, GLenum type, GLboolean normalized, GLuint value) { functions()->glVertexAttribP3ui(index, type, normalized, value); }
void glVertexAttribP3uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint* value) { functions()->glVertexAttribP3uiv(index, type, normalized, value); }
void glVertexAttribP4ui(GLuint index, GLenum type, GLboolean normalized, GLuint value) { functions()->glVertexAttribP4ui(index, type, normalized, value); }
void glVertexAttribP4uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint* value) { functions()->glVertexAttribP4uiv(index, type, normalized, value); }
void glVertexAttribParameteriAMD(GLuint index, GLenum pname, GLint param) { functions()->glVertexAttribParameteriAMD(index, pname, param); }
void glVertexAttribPointerARB(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) { functions()->glVertexAttribPointerARB(index, size, type, normalized, stride, pointer); }
void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) { functions()->glVertexAttribPointer(index, size, type, normalized, stride, pointer); }
void glVertexAttribPointerNV(GLuint index, GLint fsize, GLenum type, GLsizei stride, const void* pointer) { functions()->glVertexAttribPointerNV(index, fsize, type, stride, pointer); }
void glVertexAttribs1dvNV(GLuint index, GLsizei count, const GLdouble* v) { functions()->glVertexAttribs1dvNV(index, count, v); }
void glVertexAttribs1fvNV(GLuint index, GLsizei count, const GLfloat* v) { functions()->glVertexAttribs1fvNV(index, count, v); }
void glVertexAttribs1hvNV(GLuint index, GLsizei n, const GLhalfNV* v) { functions()->glVertexAttribs1hvNV(index, n, v); }
void glVertexAttribs1svNV(GLuint index, GLsizei count, const GLshort* v) { functions()->glVertexAttribs1svNV(index, count, v); }
void glVertexAttribs2dvNV(GLuint index, GLsizei count, const GLdouble* v) { functions()->glVertexAttribs2dvNV(index, count, v); }
void glVertexAttribs2fvNV(GLuint index, GLsizei count, const GLfloat* v) { functions()->glVertexAttribs2fvNV(index, count, v); }
void glVertexAttribs2hvNV(GLuint index, GLsizei n, const GLhalfNV* v) { functions()->glVertexAttribs2hvNV(index, n, v); }
void glVertexAttribs2svNV(GLuint index, GLsizei count, const GLshort* v) { functions()->glVertexAttribs2svNV(index, count, v); }
void glVertexAttribs3dvNV(GLuint index, GLsizei count, const GLdouble* v) { functions()->glVertexAttribs3dvNV(index, count, v); }
void glVertexAttribs3fvNV(GLuint index, GLsizei count, const GLfloat* v) { functions()->glVertexAttribs3fvNV(index, count, v); }
void glVertexAttribs3hvNV(GLuint index, GLsizei n, const GLhalfNV* v) { functions()->glVertexAttribs3hvNV(index, n, v); }
void glVertexAttribs3svNV(GLuint index, GLsizei count, const GLshort* v) { functions()->glVertexAttribs3svNV(index, count, v); }
void glVertexAttribs4dvNV(GLuint index, GLsizei count, const GLdouble* v) { functions()->glVertexAttribs4dvNV(index, count, v); }
void glVertexAttribs4fvNV(GLuint index, GLsizei count, const GLfloat* v) { functions()->glVertexAttribs4fvNV(index, count, v); }
void glVertexAttribs4hvNV(GLuint index, GLsizei n, const GLhalfNV* v) { functions()->glVertexAttribs4hvNV(index, n, v); }
void glVertexAttribs4svNV(GLuint index, GLsizei count, const GLshort* v) { functions()->glVertexAttribs4svNV(index, count, v); }
void glVertexAttribs4ubvNV(GLuint index, GLsizei count, const GLubyte* v) { functions()->glVertexAttribs4ubvNV(index, count, v); }
void glVertexBindingDivisor(GLuint bindingindex, GLuint divisor) { functions()->glVertexBindingDivisor(bindingindex, divisor); }
void glVertexBlendARB(GLint count) { functions()->glVertexBlendARB(count); }
void glVertexBlendEnvfATI(GLenum pname, GLfloat param) { functions()->glVertexBlendEnvfATI(pname, param); }
void glVertexBlendEnviATI(GLenum pname, GLint param) { functions()->glVertexBlendEnviATI(pname, param); }
void glVertexFormatNV(GLint size, GLenum type, GLsizei stride) { functions()->glVertexFormatNV(size, type, stride); }
void glVertexP2ui(GLenum type, GLuint value) { functions()->glVertexP2ui(type, value); }
void glVertexP2uiv(GLenum type, const GLuint* value) { functions()->glVertexP2uiv(type, value); }
void glVertexP3ui(GLenum type, GLuint value) { functions()->glVertexP3ui(type, value); }
void glVertexP3uiv(GLenum type, const GLuint* value) { functions()->glVertexP3uiv(type, value); }
void glVertexP4ui(GLenum type, GLuint value) { functions()->glVertexP4ui(type, value); }
void glVertexP4uiv(GLenum type, const GLuint* value) { functions()->glVertexP4uiv(type, value); }
void glVertexPointerEXT(GLint size, GLenum type, GLsizei stride, GLsizei count, const void* pointer) { functions()->glVertexPointerEXT(size, type, stride, count, pointer); }
void glVertexPointer(GLint size, GLenum type, GLsizei stride, const GLvoid* ptr) { functions()->glVertexPointer(size, type, stride, ptr); }
void glVertexPointerListIBM(GLint size, GLenum type, GLint stride, const void** pointer, GLint ptrstride) { functions()->glVertexPointerListIBM(size, type, stride, pointer, ptrstride); }
void glVertexPointervINTEL(GLint size, GLenum type, const void** pointer) { functions()->glVertexPointervINTEL(size, type, pointer); }
void glVertexStream1dATI(GLenum stream, GLdouble x) { functions()->glVertexStream1dATI(stream, x); }
void glVertexStream1dvATI(GLenum stream, const GLdouble* coords) { functions()->glVertexStream1dvATI(stream, coords); }
void glVertexStream1fATI(GLenum stream, GLfloat x) { functions()->glVertexStream1fATI(stream, x); }
void glVertexStream1fvATI(GLenum stream, const GLfloat* coords) { functions()->glVertexStream1fvATI(stream, coords); }
void glVertexStream1iATI(GLenum stream, GLint x) { functions()->glVertexStream1iATI(stream, x); }
void glVertexStream1ivATI(GLenum stream, const GLint* coords) { functions()->glVertexStream1ivATI(stream, coords); }
void glVertexStream1sATI(GLenum stream, GLshort x) { functions()->glVertexStream1sATI(stream, x); }
void glVertexStream1svATI(GLenum stream, const GLshort* coords) { functions()->glVertexStream1svATI(stream, coords); }
void glVertexStream2dATI(GLenum stream, GLdouble x, GLdouble y) { functions()->glVertexStream2dATI(stream, x, y); }
void glVertexStream2dvATI(GLenum stream, const GLdouble* coords) { functions()->glVertexStream2dvATI(stream, coords); }
void glVertexStream2fATI(GLenum stream, GLfloat x, GLfloat y) { functions()->glVertexStream2fATI(stream, x, y); }
void glVertexStream2fvATI(GLenum stream, const GLfloat* coords) { functions()->glVertexStream2fvATI(stream, coords); }
void glVertexStream2iATI(GLenum stream, GLint x, GLint y) { functions()->glVertexStream2iATI(stream, x, y); }
void glVertexStream2ivATI(GLenum stream, const GLint* coords) { functions()->glVertexStream2ivATI(stream, coords); }
void glVertexStream2sATI(GLenum stream, GLshort x, GLshort y) { functions()->glVertexStream2sATI(stream, x, y); }
void glVertexStream2svATI(GLenum stream, const GLshort* coords) { functions()->glVertexStream2svATI(stream, coords); }
void glVertexStream3dATI(GLenum stream, GLdouble x, GLdouble y, GLdouble z) { functions()->glVertexStream3dATI(stream, x, y, z); }
void glVertexStream3dvATI(GLenum stream, const GLdouble* coords) { functions()->glVertexStream3dvATI(stream, coords); }
void glVertexStream3fATI(GLenum stream, GLfloat x, GLfloat y, GLfloat z) { functions()->glVertexStream3fATI(stream, x, y, z); }
void glVertexStream3fvATI(GLenum stream, const GLfloat* coords) { functions()->glVertexStream3fvATI(stream, coords); }
void glVertexStream3iATI(GLenum stream, GLint x, GLint y, GLint z) { functions()->glVertexStream3iATI(stream, x, y, z); }
void glVertexStream3ivATI(GLenum stream, const GLint* coords) { functions()->glVertexStream3ivATI(stream, coords); }
void glVertexStream3sATI(GLenum stream, GLshort x, GLshort y, GLshort z) { functions()->glVertexStream3sATI(stream, x, y, z); }
void glVertexStream3svATI(GLenum stream, const GLshort* coords) { functions()->glVertexStream3svATI(stream, coords); }
void glVertexStream4dATI(GLenum stream, GLdouble x, GLdouble y, GLdouble z, GLdouble w) { functions()->glVertexStream4dATI(stream, x, y, z, w); }
void glVertexStream4dvATI(GLenum stream, const GLdouble* coords) { functions()->glVertexStream4dvATI(stream, coords); }
void glVertexStream4fATI(GLenum stream, GLfloat x, GLfloat y, GLfloat z, GLfloat w) { functions()->glVertexStream4fATI(stream, x, y, z, w); }
void glVertexStream4fvATI(GLenum stream, const GLfloat* coords) { functions()->glVertexStream4fvATI(stream, coords); }
void glVertexStream4iATI(GLenum stream, GLint x, GLint y, GLint z, GLint w) { functions()->glVertexStream4iATI(stream, x, y, z, w); }
void glVertexStream4ivATI(GLenum stream, const GLint* coords) { functions()->glVertexStream4ivATI(stream, coords); }
void glVertexStream4sATI(GLenum stream, GLshort x, GLshort y, GLshort z, GLshort w) { functions()->glVertexStream4sATI(stream, x, y, z, w); }
void glVertexStream4svATI(GLenum stream, const GLshort* coords) { functions()->glVertexStream4svATI(stream, coords); }
void glVertexWeightfEXT(GLfloat weight) { functions()->glVertexWeightfEXT(weight); }
void glVertexWeightfvEXT(const GLfloat* weight) { functions()->glVertexWeightfvEXT(weight); }
void glVertexWeighthNV(GLhalfNV weight) { functions()->glVertexWeighthNV(weight); }
void glVertexWeighthvNV(const GLhalfNV* weight) { functions()->glVertexWeighthvNV(weight); }
void glVertexWeightPointerEXT(GLint size, GLenum type, GLsizei stride, const void* pointer) { functions()->glVertexWeightPointerEXT(size, type, stride, pointer); }
void glVideoCaptureStreamParameterdvNV(GLuint video_capture_slot, GLuint stream, GLenum pname, const GLdouble* params) { functions()->glVideoCaptureStreamParameterdvNV(video_capture_slot, stream, pname, params); }
void glVideoCaptureStreamParameterfvNV(GLuint video_capture_slot, GLuint stream, GLenum pname, const GLfloat* params) { functions()->glVideoCaptureStreamParameterfvNV(video_capture_slot, stream, pname, params); }
void glVideoCaptureStreamParameterivNV(GLuint video_capture_slot, GLuint stream, GLenum pname, const GLint* params) { functions()->glVideoCaptureStreamParameterivNV(video_capture_slot, stream, pname, params); }
void glViewportArrayv(GLuint first, GLsizei count, const GLfloat* v) { functions()->glViewportArrayv(first, count, v); }
void glViewport(GLint x, GLint y, GLsizei width, GLsizei height) { functions()->glViewport(x, y, width, height); }
void glViewportIndexedf(GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h) { functions()->glViewportIndexedf(index, x, y, w, h); }
void glViewportIndexedfv(GLuint index, const GLfloat* v) { functions()->glViewportIndexedfv(index, v); }
void glViewportSwizzleNV(GLuint index, GLenum swizzlex, GLenum swizzley, GLenum swizzlez, GLenum swizzlew) { functions()->glViewportSwizzleNV(index, swizzlex, swizzley, swizzlez, swizzlew); }
void glWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout) { functions()->glWaitSync(sync, flags, timeout); }
void glWeightbvARB(GLint size, const GLbyte* weights) { functions()->glWeightbvARB(size, weights); }
void glWeightdvARB(GLint size, const GLdouble* weights) { functions()->glWeightdvARB(size, weights); }
void glWeightfvARB(GLint size, const GLfloat* weights) { functions()->glWeightfvARB(size, weights); }
void glWeightivARB(GLint size, const GLint* weights) { functions()->glWeightivARB(size, weights); }
void glWeightPathsNV(GLuint resultPath, GLsizei numPaths, const GLuint* paths, const GLfloat* weights) { functions()->glWeightPathsNV(resultPath, numPaths, paths, weights); }
void glWeightPointerARB(GLint size, GLenum type, GLsizei stride, const void* pointer) { functions()->glWeightPointerARB(size, type, stride, pointer); }
void glWeightsvARB(GLint size, const GLshort* weights) { functions()->glWeightsvARB(size, weights); }
void glWeightubvARB(GLint size, const GLubyte* weights) { functions()->glWeightubvARB(size, weights); }
void glWeightuivARB(GLint size, const GLuint* weights) { functions()->glWeightuivARB(size, weights); }
void glWeightusvARB(GLint size, const GLushort* weights) { functions()->glWeightusvARB(size, weights); }
void glWindowPos2dARB(GLdouble x, GLdouble y) { functions()->glWindowPos2dARB(x, y); }
void glWindowPos2d(GLdouble x, GLdouble y) { functions()->glWindowPos2d(x, y); }
void glWindowPos2dMESA(GLdouble x, GLdouble y) { functions()->glWindowPos2dMESA(x, y); }
void glWindowPos2dvARB(const GLdouble* v) { functions()->glWindowPos2dvARB(v); }
void glWindowPos2dv(const GLdouble* v) { functions()->glWindowPos2dv(v); }
void glWindowPos2dvMESA(const GLdouble* v) { functions()->glWindowPos2dvMESA(v); }
void glWindowPos2fARB(GLfloat x, GLfloat y) { functions()->glWindowPos2fARB(x, y); }
void glWindowPos2f(GLfloat x, GLfloat y) { functions()->glWindowPos2f(x, y); }
void glWindowPos2fMESA(GLfloat x, GLfloat y) { functions()->glWindowPos2fMESA(x, y); }
void glWindowPos2fvARB(const GLfloat* v) { functions()->glWindowPos2fvARB(v); }
void glWindowPos2fv(const GLfloat* v) { functions()->glWindowPos2fv(v); }
void glWindowPos2fvMESA(const GLfloat* v) { functions()->glWindowPos2fvMESA(v); }
void glWindowPos2iARB(GLint x, GLint y) { functions()->glWindowPos2iARB(x, y); }
void glWindowPos2i(GLint x, GLint y) { functions()->glWindowPos2i(x, y); }
void glWindowPos2iMESA(GLint x, GLint y) { functions()->glWindowPos2iMESA(x, y); }
void glWindowPos2ivARB(const GLint* v) { functions()->glWindowPos2ivARB(v); }
void glWindowPos2iv(const GLint* v) { functions()->glWindowPos2iv(v); }
void glWindowPos2ivMESA(const GLint* v) { functions()->glWindowPos2ivMESA(v); }
void glWindowPos2sARB(GLshort x, GLshort y) { functions()->glWindowPos2sARB(x, y); }
void glWindowPos2s(GLshort x, GLshort y) { functions()->glWindowPos2s(x, y); }
void glWindowPos2sMESA(GLshort x, GLshort y) { functions()->glWindowPos2sMESA(x, y); }
void glWindowPos2svARB(const GLshort* v) { functions()->glWindowPos2svARB(v); }
void glWindowPos2sv(const GLshort* v) { functions()->glWindowPos2sv(v); }
void glWindowPos2svMESA(const GLshort* v) { functions()->glWindowPos2svMESA(v); }
void glWindowPos3dARB(GLdouble x, GLdouble y, GLdouble z) { functions()->glWindowPos3dARB(x, y, z); }
void glWindowPos3d(GLdouble x, GLdouble y, GLdouble z) { functions()->glWindowPos3d(x, y, z); }
void glWindowPos3dMESA(GLdouble x, GLdouble y, GLdouble z) { functions()->glWindowPos3dMESA(x, y, z); }
void glWindowPos3dvARB(const GLdouble* v) { functions()->glWindowPos3dvARB(v); }
void glWindowPos3dv(const GLdouble* v) { functions()->glWindowPos3dv(v); }
void glWindowPos3dvMESA(const GLdouble* v) { functions()->glWindowPos3dvMESA(v); }
void glWindowPos3fARB(GLfloat x, GLfloat y, GLfloat z) { functions()->glWindowPos3fARB(x, y, z); }
void glWindowPos3f(GLfloat x, GLfloat y, GLfloat z) { functions()->glWindowPos3f(x, y, z); }
void glWindowPos3fMESA(GLfloat x, GLfloat y, GLfloat z) { functions()->glWindowPos3fMESA(x, y, z); }
void glWindowPos3fvARB(const GLfloat* v) { functions()->glWindowPos3fvARB(v); }
void glWindowPos3fv(const GLfloat* v) { functions()->glWindowPos3fv(v); }
void glWindowPos3fvMESA(const GLfloat* v) { functions()->glWindowPos3fvMESA(v); }
void glWindowPos3iARB(GLint x, GLint y, GLint z) { functions()->glWindowPos3iARB(x, y, z); }
void glWindowPos3i(GLint x, GLint y, GLint z) { functions()->glWindowPos3i(x, y, z); }
void glWindowPos3iMESA(GLint x, GLint y, GLint z) { functions()->glWindowPos3iMESA(x, y, z); }
void glWindowPos3ivARB(const GLint* v) { functions()->glWindowPos3ivARB(v); }
void glWindowPos3iv(const GLint* v) { functions()->glWindowPos3iv(v); }
void glWindowPos3ivMESA(const GLint* v) { functions()->glWindowPos3ivMESA(v); }
void glWindowPos3sARB(GLshort x, GLshort y, GLshort z) { functions()->glWindowPos3sARB(x, y, z); }
void glWindowPos3s(GLshort x, GLshort y, GLshort z) { functions()->glWindowPos3s(x, y, z); }
void glWindowPos3sMESA(GLshort x, GLshort y, GLshort z) { functions()->glWindowPos3sMESA(x, y, z); }
void glWindowPos3svARB(const GLshort* v) { functions()->glWindowPos3svARB(v); }
void glWindowPos3sv(const GLshort* v) { functions()->glWindowPos3sv(v); }
void glWindowPos3svMESA(const GLshort* v) { functions()->glWindowPos3svMESA(v); }
void glWindowPos4dMESA(GLdouble x, GLdouble y, GLdouble z, GLdouble w) { functions()->glWindowPos4dMESA(x, y, z, w); }
void glWindowPos4dvMESA(const GLdouble* v) { functions()->glWindowPos4dvMESA(v); }
void glWindowPos4fMESA(GLfloat x, GLfloat y, GLfloat z, GLfloat w) { functions()->glWindowPos4fMESA(x, y, z, w); }
void glWindowPos4fvMESA(const GLfloat* v) { functions()->glWindowPos4fvMESA(v); }
void glWindowPos4iMESA(GLint x, GLint y, GLint z, GLint w) { functions()->glWindowPos4iMESA(x, y, z, w); }
void glWindowPos4ivMESA(const GLint* v) { functions()->glWindowPos4ivMESA(v); }
void glWindowPos4sMESA(GLshort x, GLshort y, GLshort z, GLshort w) { functions()->glWindowPos4sMESA(x, y, z, w); }
void glWindowPos4svMESA(const GLshort* v) { functions()->glWindowPos4svMESA(v); }
void glWriteMaskEXT(GLuint res, GLuint in, GLenum outX, GLenum outY, GLenum outZ, GLenum outW) { functions()->glWriteMaskEXT(res, in, outX, outY, outZ, outW); }
