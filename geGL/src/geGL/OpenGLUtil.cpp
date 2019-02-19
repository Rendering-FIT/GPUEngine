#include<geGL/OpenGLUtil.h>

using namespace ge::gl;

std::string ge::gl::translateDebugSource(GLenum source){
  switch(source){//swich over debug sources
    case GL_DEBUG_SOURCE_API            :return"GL_DEBUG_SOURCE_API"            ;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM  :return"GL_DEBUG_SOURCE_WINDOW_SYSTEM"  ;
    case GL_DEBUG_SOURCE_SHADER_COMPILER:return"GL_DEBUG_SOURCE_SHADER_COMPILER";
    case GL_DEBUG_SOURCE_THIRD_PARTY    :return"GL_DEBUG_SOURCE_THIRD_PARTY"    ;
    case GL_DEBUG_SOURCE_APPLICATION    :return"GL_DEBUG_SOURCE_APPLICATION"    ;
    case GL_DEBUG_SOURCE_OTHER          :return"GL_DEBUG_SOURCE_OTHER"          ;
    default                             :return"unknown"                        ;
  }
}
std::string ge::gl::translateDebugType(GLenum type){
  switch(type){//switch over debug types
    case GL_DEBUG_TYPE_ERROR              :return"GL_DEBUG_TYPE_ERROR"              ;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:return"GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR";
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR :return"GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR" ;
    case GL_DEBUG_TYPE_PORTABILITY        :return"GL_DEBUG_TYPE_PORTABILITY"        ;
    case GL_DEBUG_TYPE_PERFORMANCE        :return"GL_DEBUG_TYPE_PERFORMANCE"        ;
    case GL_DEBUG_TYPE_MARKER             :return"GL_DEBUG_TYPE_MARKER"             ;
    case GL_DEBUG_TYPE_PUSH_GROUP         :return"GL_DEBUG_TYPE_PUSH_GROUP"         ;
    case GL_DEBUG_TYPE_POP_GROUP          :return"GL_DEBUG_TYPE_POP_GROUP"          ;
    case GL_DEBUG_TYPE_OTHER              :return"GL_DEBUG_TYPE_OTHER"              ;
    case GL_DONT_CARE                     :return"GL_DONT_CARE"                     ;
    default                               :return"unknown"                          ;
  }
}
std::string ge::gl::translateDebugSeverity(GLenum severity){
  switch(severity){//switch over debug severities
    case GL_DEBUG_SEVERITY_LOW         :return"GL_DEBUG_SEVERITY_LOW"         ;
    case GL_DEBUG_SEVERITY_MEDIUM      :return"GL_DEBUG_SEVERITY_MEDIUM"      ;
    case GL_DEBUG_SEVERITY_HIGH        :return"GL_DEBUG_SEVERITY_HIGH"        ;
    case GL_DEBUG_SEVERITY_NOTIFICATION:return"GL_DEBUG_SEVERITY_NOTIFICATION";
    case GL_DONT_CARE                  :return"GL_DONT_CARE"                  ;
    default                            :return"unknown"                       ;
  }
}

/**
 * @brief Function translates buffer targets to strings
 *
 * @param target buffer targets
 *
 * @return string representation of target
 */
std::string ge::gl::translateBufferTarget(GLenum target){
  switch(target){
    case GL_ARRAY_BUFFER             :return "GL_ARRAY_BUFFER"             ;
    case GL_UNIFORM_BUFFER           :return "GL_UNIFORM_BUFFER"           ;
    case GL_ATOMIC_COUNTER_BUFFER    :return "GL_ATOMIC_COUNTER_BUFFER"    ;
    case GL_QUERY_BUFFER             :return "GL_QUERY_BUFFER"             ;
    case GL_COPY_READ_BUFFER         :return "GL_COPY_READ_BUFFER"         ;
    case GL_COPY_WRITE_BUFFER        :return "GL_COPY_WRITE_BUFFER"        ;
    case GL_DISPATCH_INDIRECT_BUFFER :return "GL_DISPATCH_INDIRECT_BUFFER" ;
    case GL_DRAW_INDIRECT_BUFFER     :return "GL_DRAW_INDIRECT_BUFFER"     ;
    case GL_ELEMENT_ARRAY_BUFFER     :return "GL_ELEMENT_ARRAY_BUFFER"     ;
    case GL_TEXTURE_BUFFER           :return "GL_TEXTURE_BUFFER"           ;
    case GL_PIXEL_PACK_BUFFER        :return "GL_PIXEL_PACK_BUFFER"        ;
    case GL_PIXEL_UNPACK_BUFFER      :return "GL_PIXEL_UNPACK_BUFFER"      ;
    case GL_SHADER_STORAGE_BUFFER    :return "GL_SHADER_STORAGE_BUFFER"    ;
    case GL_TRANSFORM_FEEDBACK_BUFFER:return "GL_TRANSFORM_FEEDBACK_BUFFER";
    default                          :return "unknown"                     ;
  }
}

/**
 * @brief Function translates buffer bindings to strings
 *
 * @param binding buffer binding
 *
 * @return string representation of buffer binding
 */
std::string ge::gl::translateBufferBinding(GLenum binding){
  switch(binding){
    case GL_ARRAY_BUFFER_BINDING             :return "GL_ARRAY_BUFFER_BINDING"             ;
    case GL_UNIFORM_BUFFER_BINDING           :return "GL_UNIFORM_BUFFER_BINDING"           ;
    case GL_ATOMIC_COUNTER_BUFFER_BINDING    :return "GL_ATOMIC_COUNTER_BUFFER_BINDING"    ;
    case GL_QUERY_BUFFER_BINDING             :return "GL_QUERY_BUFFER_BINDING"             ;
    case GL_COPY_READ_BUFFER_BINDING         :return "GL_COPY_READ_BUFFER_BINDING"         ;
    case GL_COPY_WRITE_BUFFER_BINDING        :return "GL_COPY_WRITE_BUFFER_BINDING"        ;
    case GL_DISPATCH_INDIRECT_BUFFER_BINDING :return "GL_DISPATCH_INDIRECT_BUFFER_BINDING" ;
    case GL_DRAW_INDIRECT_BUFFER_BINDING     :return "GL_DRAW_INDIRECT_BUFFER_BINDING"     ;
    case GL_ELEMENT_ARRAY_BUFFER_BINDING     :return "GL_ELEMENT_ARRAY_BUFFER_BINDING"     ;
    case GL_TEXTURE_BUFFER_BINDING           :return "GL_TEXTURE_BUFFER_BINDING"           ;
    case GL_PIXEL_PACK_BUFFER_BINDING        :return "GL_PIXEL_PACK_BUFFER_BINDING"        ;
    case GL_PIXEL_UNPACK_BUFFER_BINDING      :return "GL_PIXEL_UNPACK_BUFFER_BINDING"      ;
    case GL_SHADER_STORAGE_BUFFER_BINDING    :return "GL_SHADER_STORAGE_BUFFER_BINDING"    ;
    case GL_TRANSFORM_FEEDBACK_BUFFER_BINDING:return "GL_TRANSFORM_FEEDBACK_BUFFER_BINDING";
    default                                  :return "unknown"                             ;
  }
}

/**
 * @brief Function converts buffer target to buffer binding
 *
 * @param target buffer target
 *
 * @return buffer bingding for buffer target
 */
GLenum ge::gl::bufferTarget2Binding(GLenum target){
  switch(target){
    case GL_ARRAY_BUFFER             :return GL_ARRAY_BUFFER_BINDING             ;
    case GL_UNIFORM_BUFFER           :return GL_UNIFORM_BUFFER_BINDING           ;
    case GL_ATOMIC_COUNTER_BUFFER    :return GL_ATOMIC_COUNTER_BUFFER_BINDING    ;
    case GL_QUERY_BUFFER             :return GL_QUERY_BUFFER_BINDING             ;
    case GL_COPY_READ_BUFFER         :return GL_COPY_READ_BUFFER_BINDING         ;
    case GL_COPY_WRITE_BUFFER        :return GL_COPY_WRITE_BUFFER_BINDING        ;
    case GL_DISPATCH_INDIRECT_BUFFER :return GL_DISPATCH_INDIRECT_BUFFER_BINDING ;
    case GL_DRAW_INDIRECT_BUFFER     :return GL_DRAW_INDIRECT_BUFFER_BINDING     ;
    case GL_ELEMENT_ARRAY_BUFFER     :return GL_ELEMENT_ARRAY_BUFFER_BINDING     ;
    case GL_TEXTURE_BUFFER           :return GL_TEXTURE_BUFFER_BINDING           ;
    case GL_PIXEL_PACK_BUFFER        :return GL_PIXEL_PACK_BUFFER_BINDING        ;
    case GL_PIXEL_UNPACK_BUFFER      :return GL_PIXEL_UNPACK_BUFFER_BINDING      ;
    case GL_SHADER_STORAGE_BUFFER    :return GL_SHADER_STORAGE_BUFFER_BINDING    ;
    case GL_TRANSFORM_FEEDBACK_BUFFER:return GL_TRANSFORM_FEEDBACK_BUFFER_BINDING;
    default                          :return 0                                   ;
  }
}

/**
 * @brief Function convertes buffer binding to buffer target
 *
 * @param binding buffer binding
 *
 * @return buffer target of buffer binding
 */
GLenum ge::gl::bufferBinding2Target(GLenum binding){
  switch(binding){
    case GL_ARRAY_BUFFER_BINDING             :return GL_ARRAY_BUFFER             ;
    case GL_UNIFORM_BUFFER_BINDING           :return GL_UNIFORM_BUFFER           ;
    case GL_ATOMIC_COUNTER_BUFFER_BINDING    :return GL_ATOMIC_COUNTER_BUFFER    ;
    case GL_QUERY_BUFFER_BINDING             :return GL_QUERY_BUFFER             ;
    case GL_COPY_READ_BUFFER_BINDING         :return GL_COPY_READ_BUFFER         ;
    case GL_COPY_WRITE_BUFFER_BINDING        :return GL_COPY_WRITE_BUFFER        ;
    case GL_DISPATCH_INDIRECT_BUFFER_BINDING :return GL_DISPATCH_INDIRECT_BUFFER ;
    case GL_DRAW_INDIRECT_BUFFER_BINDING     :return GL_DRAW_INDIRECT_BUFFER     ;
    case GL_ELEMENT_ARRAY_BUFFER_BINDING     :return GL_ELEMENT_ARRAY_BUFFER     ;
    case GL_TEXTURE_BUFFER_BINDING           :return GL_TEXTURE_BUFFER           ;
    case GL_PIXEL_PACK_BUFFER_BINDING        :return GL_PIXEL_PACK_BUFFER        ;
    case GL_PIXEL_UNPACK_BUFFER_BINDING      :return GL_PIXEL_UNPACK_BUFFER      ;
    case GL_SHADER_STORAGE_BUFFER_BINDING    :return GL_SHADER_STORAGE_BUFFER    ;
    case GL_TRANSFORM_FEEDBACK_BUFFER_BINDING:return GL_TRANSFORM_FEEDBACK_BUFFER;
    default                                  :return 0                           ;
  }
}

/**
 * @brief detetermines if flags are mutable
 *
 * @param flags flags
 *
 * @return true if flags are combination of GL_{STATIC|STREAM|DYNAMIC}_{DRAW_COPY_READ}
 */
bool ge::gl::areBufferFlagsMutable(GLbitfield flags){
  return 
    flags == GL_STATIC_DRAW ||
    flags == GL_STATIC_COPY ||
    flags == GL_STATIC_READ ||
    flags == GL_STREAM_DRAW ||
    flags == GL_STREAM_COPY ||
    flags == GL_STREAM_READ ||
    flags == GL_DYNAMIC_DRAW||
    flags == GL_DYNAMIC_COPY||
    flags == GL_DYNAMIC_READ;
}

std::string ge::gl::translateFramebufferComponentType(GLenum type){
  switch(type){
    case GL_FLOAT              :return"GL_FLOAT"              ;
    case GL_INT                :return"GL_INT"                ;
    case GL_UNSIGNED_INT       :return"GL_UNSIGNED_INT"       ;
    case GL_SIGNED_NORMALIZED  :return"GL_SIGNED_NORMALIZED"  ;
    case GL_UNSIGNED_NORMALIZED:return"GL_UNSIGNED_NORMALIZED";
    default                    :return"unknown"               ;
  }
}

std::string ge::gl::translateFramebufferType(GLenum type){
  switch(type){
    case GL_NONE               :return"GL_NONE"               ;
    case GL_FRAMEBUFFER_DEFAULT:return"GL_FRAMEBUFFER_DEFAULT";
    case GL_TEXTURE            :return"GL_TEXTURE"            ;
    case GL_RENDERBUFFER       :return"GL_RENDERBUFFER"       ;
    default                    :return"unknown"               ;
  }
}

std::string ge::gl::translateFramebufferAttachment(GLenum attachment){
  switch(attachment){
    case GL_DEPTH_ATTACHMENT  :return"GL_DEPTH_ATTACHMENT"  ;
    case GL_STENCIL_ATTACHMENT:return"GL_STENCIL_ATTACHMENT";
    case GL_COLOR_ATTACHMENT0 :return"GL_COLOR_ATTACHMENT0" ;
    case GL_COLOR_ATTACHMENT1 :return"GL_COLOR_ATTACHMENT1" ;
    case GL_COLOR_ATTACHMENT2 :return"GL_COLOR_ATTACHMENT2" ;
    case GL_COLOR_ATTACHMENT3 :return"GL_COLOR_ATTACHMENT3" ;
    case GL_COLOR_ATTACHMENT4 :return"GL_COLOR_ATTACHMENT4" ;
    case GL_COLOR_ATTACHMENT5 :return"GL_COLOR_ATTACHMENT5" ;
    case GL_COLOR_ATTACHMENT6 :return"GL_COLOR_ATTACHMENT6" ;
    case GL_COLOR_ATTACHMENT7 :return"GL_COLOR_ATTACHMENT7" ;
    case GL_COLOR_ATTACHMENT8 :return"GL_COLOR_ATTACHMENT8" ;
    case GL_COLOR_ATTACHMENT9 :return"GL_COLOR_ATTACHMENT8" ;
    case GL_COLOR_ATTACHMENT10:return"GL_COLOR_ATTACHMENT10";
    case GL_COLOR_ATTACHMENT11:return"GL_COLOR_ATTACHMENT11";
    case GL_COLOR_ATTACHMENT12:return"GL_COLOR_ATTACHMENT12";
    case GL_COLOR_ATTACHMENT13:return"GL_COLOR_ATTACHMENT13";
    case GL_COLOR_ATTACHMENT14:return"GL_COLOR_ATTACHMENT14";
    case GL_COLOR_ATTACHMENT15:return"GL_COLOR_ATTACHMENT15";
    default:                   return"unknown"              ;
  }
}

std::string ge::gl::translateFramebufferColorEncoding(GLenum type){
  switch(type){
    case GL_LINEAR:return"GL_LINEAR";
    case GL_SRGB  :return"GL_SRGB"  ;
    default       :return"unknown"  ;
  }
}

std::string ge::gl::translateCubeMapFace(GLenum face){
  switch(face){
    case GL_TEXTURE_CUBE_MAP_NEGATIVE_X:return"GL_TEXTURE_CUBE_MAP_NEGATIVE_X";
    case GL_TEXTURE_CUBE_MAP_POSITIVE_X:return"GL_TEXTURE_CUBE_MAP_POSITIVE_X";
    case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y:return"GL_TEXTURE_CUBE_MAP_NEGATIVE_Y";
    case GL_TEXTURE_CUBE_MAP_POSITIVE_Y:return"GL_TEXTURE_CUBE_MAP_POSITIVE_Y";
    case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z:return"GL_TEXTURE_CUBE_MAP_NEGATIVE_Z";
    case GL_TEXTURE_CUBE_MAP_POSITIVE_Z:return"GL_TEXTURE_CUBE_MAP_POSITIVE_Z";
    default                            :return"unknown";
  }
}

GLenum ge::gl::textureTarget2Binding(GLenum target){
  switch(target){
    case GL_TEXTURE_1D                  :return GL_TEXTURE_BINDING_1D                  ;
    case GL_TEXTURE_1D_ARRAY            :return GL_TEXTURE_BINDING_1D_ARRAY            ;
    case GL_TEXTURE_2D                  :return GL_TEXTURE_BINDING_2D                  ;
    case GL_TEXTURE_2D_ARRAY            :return GL_TEXTURE_BINDING_2D_ARRAY            ;
    case GL_TEXTURE_2D_MULTISAMPLE      :return GL_TEXTURE_BINDING_2D_MULTISAMPLE      ;
    case GL_TEXTURE_2D_MULTISAMPLE_ARRAY:return GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY;
    case GL_TEXTURE_3D                  :return GL_TEXTURE_BINDING_3D                  ;
    case GL_TEXTURE_BUFFER              :return GL_TEXTURE_BINDING_BUFFER              ;
    case GL_TEXTURE_CUBE_MAP            :return GL_TEXTURE_BINDING_CUBE_MAP            ;
    case GL_TEXTURE_RECTANGLE           :return GL_TEXTURE_BINDING_RECTANGLE           ;
    default                             :return 0                                      ;
  }
}

GLenum ge::gl::textureBinding2Target(GLenum binding){
  switch(binding){
    case GL_TEXTURE_BINDING_1D                  :return GL_TEXTURE_1D                  ;
    case GL_TEXTURE_BINDING_1D_ARRAY            :return GL_TEXTURE_1D_ARRAY            ;
    case GL_TEXTURE_BINDING_2D                  :return GL_TEXTURE_2D                  ;
    case GL_TEXTURE_BINDING_2D_ARRAY            :return GL_TEXTURE_2D_ARRAY            ;
    case GL_TEXTURE_BINDING_2D_MULTISAMPLE      :return GL_TEXTURE_2D_MULTISAMPLE      ;
    case GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY:return GL_TEXTURE_2D_MULTISAMPLE_ARRAY;
    case GL_TEXTURE_BINDING_3D                  :return GL_TEXTURE_3D                  ;
    case GL_TEXTURE_BINDING_BUFFER              :return GL_TEXTURE_BUFFER              ;
    case GL_TEXTURE_BINDING_CUBE_MAP            :return GL_TEXTURE_CUBE_MAP            ;
    case GL_TEXTURE_BINDING_RECTANGLE           :return GL_TEXTURE_RECTANGLE           ;
    default                                     :return 0                              ;
  }
}

std::string ge::gl::translateTextureTarget(GLenum target){
  switch(target){
    case GL_TEXTURE_1D                  :return "GL_TEXTURE_1D"                  ;
    case GL_TEXTURE_1D_ARRAY            :return "GL_TEXTURE_1D_ARRAY"            ;
    case GL_TEXTURE_2D                  :return "GL_TEXTURE_2D"                  ;
    case GL_TEXTURE_2D_ARRAY            :return "GL_TEXTURE_2D_ARRAY"            ;
    case GL_TEXTURE_2D_MULTISAMPLE      :return "GL_TEXTURE_2D_MULTISAMPLE"      ;
    case GL_TEXTURE_2D_MULTISAMPLE_ARRAY:return "GL_TEXTURE_2D_MULTISAMPLE_ARRAY";
    case GL_TEXTURE_3D                  :return "GL_TEXTURE_3D"                  ;
    case GL_TEXTURE_BUFFER              :return "GL_TEXTURE_BUFFER"              ;
    case GL_TEXTURE_CUBE_MAP            :return "GL_TEXTURE_CUBE_MAP"            ;
    case GL_TEXTURE_RECTANGLE           :return "GL_TEXTURE_RECTANGLE"           ;
    default                             :return "unknown"                        ;
  }
}

std::string ge::gl::translateTextureBinding(GLenum binding){
  switch(binding){
    case GL_TEXTURE_BINDING_1D                  :return "GL_TEXTURE_BINDING_1D"                  ;
    case GL_TEXTURE_BINDING_1D_ARRAY            :return "GL_TEXTURE_BINDING_1D_ARRAY"            ;
    case GL_TEXTURE_BINDING_2D                  :return "GL_TEXTURE_BINDING_2D"                  ;
    case GL_TEXTURE_BINDING_2D_ARRAY            :return "GL_TEXTURE_BINDING_2D_ARRAY"            ;
    case GL_TEXTURE_BINDING_2D_MULTISAMPLE      :return "GL_TEXTURE_BINDING_2D_MULTISAMPLE"      ;
    case GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY:return "GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY";
    case GL_TEXTURE_BINDING_3D                  :return "GL_TEXTURE_BINDING_3D"                  ;
    case GL_TEXTURE_BINDING_BUFFER              :return "GL_TEXTURE_BINDING_BUFFER"              ;
    case GL_TEXTURE_BINDING_CUBE_MAP            :return "GL_TEXTURE_BINDING_CUBE_MAP"            ;
    case GL_TEXTURE_BINDING_RECTANGLE           :return "GL_TEXTURE_BINDING_RECTANGLE"           ;
    default                                     :return "unknown"                                ;
  }
}
std::string ge::gl::translateTextureSwizzle(GLint swizzle){
  switch(swizzle){
    case GL_RED  :return"GL_RED"  ;
    case GL_GREEN:return"GL_GREEN";
    case GL_BLUE :return"GL_BLUE" ;
    case GL_ALPHA:return"GL_ALPHA";
    default      :return"unknown" ;
  }
}

std::string ge::gl::translateTextureWrap(GLint wrap){
  switch(wrap){
    case GL_CLAMP_TO_EDGE       :return"GL_CLAMP_TO_EDGE"       ;
    case GL_CLAMP_TO_BORDER     :return"GL_CLAMP_TO_BORDER"     ;
    case GL_MIRRORED_REPEAT     :return"GL_MIRRORED_REPEAT"     ;
    case GL_REPEAT              :return"GL_REPEAT"              ;
    case GL_MIRROR_CLAMP_TO_EDGE:return"GL_MIRROR_CLAMP_TO_EDGE";
    default                     :return"unknown"                ;
  }
}

std::string ge::gl::translateTextureFilter(GLint filter){
  switch(filter){
    case GL_NEAREST               :return"GL_NEAREST"               ;
    case GL_LINEAR                :return"GL_LINEAR"                ;
    case GL_NEAREST_MIPMAP_NEAREST:return"GL_NEAREST_MIPMAP_NEAREST";
    case GL_LINEAR_MIPMAP_NEAREST :return"GL_LINEAR_MIPMAP_NEAREST" ;
    case GL_NEAREST_MIPMAP_LINEAR :return"GL_NEAREST_MIPMAP_LINEAR" ;
    case GL_LINEAR_MIPMAP_LINEAR  :return"GL_LINEAR_MIPMAP_LINEAR"  ;
    default                       :return"unknown"                  ;
  }
}
std::string ge::gl::translateTextureCompareFunc(GLint func){
  switch(func){
    case GL_LEQUAL  :return"GL_LEQUAL"  ;
    case GL_GEQUAL  :return"GL_GEQUAL"  ;
    case GL_LESS    :return"GL_LESS"    ;
    case GL_GREATER :return"GL_GREATER" ;
    case GL_EQUAL   :return"GL_EQUAL"   ;
    case GL_NOTEQUAL:return"GL_NOTEQUAL";
    case GL_ALWAYS  :return"GL_ALWAYS"  ;
    case GL_NEVER   :return"GL_NEVER"   ;
    default         :return"unknown"    ;
  }
}
std::string ge::gl::translateTextureCompareMode(GLint mode){
  switch(mode){
    case GL_COMPARE_REF_TO_TEXTURE:return"GL_COMPARE_REF_TO_TEXTURE";
    case GL_NONE                  :return"GL_NONE"                  ;
    default                       :return"unknown"                  ;
  }
}

std::string ge::gl::translateTextureChannelType(GLenum type){
  switch(type){
    case GL_NONE               :return"GL_NONE"               ;
    case GL_SIGNED_NORMALIZED  :return"GL_SIGNED_NORMALIZED"  ;
    case GL_UNSIGNED_NORMALIZED:return"GL_UNSIGNED_NORMALIZED";
    case GL_FLOAT              :return"GL_FLOAT"              ;
    case GL_INT                :return"GL_INT"                ;
    case GL_UNSIGNED_INT       :return"GL_UNSIGNED_INT"       ;
    default                    :return"unknown"               ;
  }
}

std::string ge::gl::translateInternalFormat(GLenum internalFormat){
  switch(internalFormat){
    case GL_R8:return "GL_R8";
    case GL_R8_SNORM:return "GL_R8_SNORM";
    case GL_R16:return "GL_R16";
    case GL_R16_SNORM:return "GL_R16_SNORM";
    case GL_RG8:return "GL_RG8";
    case GL_RG8_SNORM:return "GL_RG8_SNORM";
    case GL_RG16:return "GL_RG16";
    case GL_RG16_SNORM:return "GL_RG16_SNORM";
    case GL_R3_G3_B2:return "GL_R3_G3_B2";
    case GL_RGB4:return "GL_RGB4";
    case GL_RGB5:return "GL_RGB5";
    case GL_RGB8:return "GL_RGB8";
    case GL_RGB8_SNORM:return "GL_RGB8_SNORM";
    case GL_RGB10:return "GL_RGB10";
    case GL_RGB12:return "GL_RGB12";
    case GL_RGB16_SNORM:return "GL_RGB16_SNORM";
    case GL_RGBA2:return "GL_RGBA2";
    case GL_RGBA4:return "GL_RGBA4";
    case GL_RGB5_A1:return "GL_RGB5_A1";
    case GL_RGBA8:return "GL_RGBA8";
    case GL_RGBA8_SNORM:return "GL_RGBA8_SNORM";
    case GL_RGB10_A2:return "GL_RGB10_A2";
    case GL_RGB10_A2UI:return "GL_RGB10_A2UI";
    case GL_RGBA12:return "GL_RGBA12";
    case GL_RGBA16:return "GL_RGBA16";
    case GL_SRGB8:return "GL_SRGB8";
    case GL_SRGB8_ALPHA8:return "GL_SRGB8_ALPHA8";
    case GL_R16F:return "GL_R16F";
    case GL_RG16F:return "GL_RG16F";
    case GL_RGB16F:return "GL_RGB16F";
    case GL_RGBA16F:return "GL_RGBA16F";
    case GL_R32F:return "GL_R32F";
    case GL_RG32F:return "GL_RG32F";
    case GL_RGB32F:return "GL_RGB32F";
    case GL_RGBA32F:return "GL_RGBA32F";
    case GL_R11F_G11F_B10F:return "GL_R11F_G11F_B10F";
    case GL_RGB9_E5:return "GL_RGB9_E5";
    case GL_R8I:return "GL_R8I";
    case GL_R8UI:return "GL_R8UI";
    case GL_R16I:return "GL_R16I";
    case GL_R16UI:return "GL_R16UI";
    case GL_R32I:return "GL_R32I";
    case GL_R32UI:return "GL_R32UI";
    case GL_RG8I:return "GL_RG8I";
    case GL_RG8UI:return "GL_RG8UI";
    case GL_RG16I:return "GL_RG16I";
    case GL_RG16UI:return "GL_RG16UI";
    case GL_RG32I:return "GL_RG32I";
    case GL_RG32UI:return "GL_RG32UI";
    case GL_RGB8I:return "GL_RGB8I";
    case GL_RGB8UI:return "GL_RGB8UI";
    case GL_RGB16I:return "GL_RGB16I";
    case GL_RGB16UI:return "GL_RGB16UI";
    case GL_RGB32I:return "GL_RGB32I";
    case GL_RGB32UI:return "GL_RGB32UI";
    case GL_RGBA8I:return "GL_RGBA8I";
    case GL_RGBA8UI:return "GL_RGBA8UI";
    case GL_RGBA16I:return "GL_RGBA16I";
    case GL_RGBA16UI:return "GL_RGBA16UI";
    case GL_RGBA32I:return "GL_RGBA32I";
    case GL_RGBA32UI:return "GL_RGBA32UI";
    case GL_COMPRESSED_RED:return "GL_COMPRESSED_RED";
    case GL_COMPRESSED_RG:return "GL_COMPRESSED_RG";
    case GL_COMPRESSED_RGB:return "GL_COMPRESSED_RGB";
    case GL_COMPRESSED_RGBA:return "GL_COMPRESSED_RGBA";
    case GL_COMPRESSED_SRGB:return "GL_COMPRESSED_SRGB";
    case GL_COMPRESSED_SRGB_ALPHA:return "GL_COMPRESSED_SRGB_ALPHA";
    case GL_COMPRESSED_RED_RGTC1:return "GL_COMPRESSED_RED_RGTC1";
    case GL_COMPRESSED_SIGNED_RED_RGTC1:return "GL_COMPRESSED_SIGNED_RED_RGTC1";
    case GL_COMPRESSED_RG_RGTC2:return "GL_COMPRESSED_RG_RGTC2";
    case GL_COMPRESSED_SIGNED_RG_RGTC2:return "GL_COMPRESSED_SIGNED_RG_RGTC2";
    case GL_COMPRESSED_RGBA_BPTC_UNORM:return "GL_COMPRESSED_RGBA_BPTC_UNORM";
    case GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM:return "GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM";
    case GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT:return "GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT";
    case GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT:return "GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT";
    case GL_RGBA:return "GL_RGBA";
    case GL_RGB:return "GL_RGB";
    case GL_RG:return "GL_RG";
    default:return"unknown"              ;
  };
}

std::string ge::gl::translateImageFormatCompatibilityType(GLenum type){
  switch(type){
    case GL_IMAGE_FORMAT_COMPATIBILITY_BY_SIZE :return "GL_IMAGE_FORMAT_COMPATIBILITY_BY_SIZE" ;
    case GL_IMAGE_FORMAT_COMPATIBILITY_BY_CLASS:return "GL_IMAGE_FORMAT_COMPATIBILITY_BY_CLASS";
    case GL_NONE                               :return "GL_NONE"                               ;
    default                                    :return "unknown"                               ;
  }
}


unsigned ge::gl::internalFormatSize(GLenum internalFormat){
  switch(internalFormat){
    case GL_STENCIL_INDEX1:
      return 1;
    case GL_STENCIL_INDEX4:
      return 4;
    case GL_R8            :
    case GL_R8UI          :
    case GL_R8I           :
    case GL_R8_SNORM      :
    case GL_R3_G3_B2      :
    case GL_RGBA2         :
    case GL_STENCIL_INDEX8:
      return 8;

    case GL_RGB4:
      return 12;
    case GL_RGB5:
      return 16;//TODO CHECK

    case GL_R16              :
    case GL_R16F             :
    case GL_R16UI            :
    case GL_R16I             :
    case GL_R16_SNORM        :
    case GL_RG8              :
    case GL_RG8UI            :
    case GL_RG8I             :
    case GL_RGB565           :
    case GL_RGB5_A1          :
    case GL_RGBA4            :
    case GL_DEPTH_COMPONENT16:
    case GL_STENCIL_INDEX16  :
      return 16;

    case GL_RGB8             :
    case GL_RGB8_SNORM       :
    case GL_RGB8UI           :
    case GL_RGB8I            :
    case GL_DEPTH_COMPONENT24:
    case GL_SRGB8            :
      return 24;

    case GL_SRGB8_ALPHA8      :
    case GL_RG16              :
    case GL_RG16_SNORM        :
    case GL_DEPTH24_STENCIL8  :
    case GL_DEPTH_COMPONENT32F:
    case GL_DEPTH_COMPONENT32 :
      return 32;
    case GL_DEPTH32F_STENCIL8:
      return 32+8;
    case GL_RGB16F:
    case GL_RGB16I:
    case GL_RGB16UI:
      return 3*16;
    case GL_RGBA16F:
    case GL_RGBA16I:
    case GL_RGBA16UI:
      return 4*16;
    case GL_RGBA32F :
    case GL_RGBA32UI:
    case GL_RGBA32I :
      return 4*32;
  }
  return 32;//TODO
}

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

bool ge::gl::isSamplerType(GLenum type){
  switch(type){
    case GL_SAMPLER_1D                               :
    case GL_SAMPLER_2D                               :
    case GL_SAMPLER_3D                               :
    case GL_SAMPLER_CUBE                             :
    case GL_SAMPLER_1D_SHADOW                        :
    case GL_SAMPLER_2D_SHADOW                        :
    case GL_SAMPLER_1D_ARRAY                         :
    case GL_SAMPLER_2D_ARRAY                         :
    case GL_SAMPLER_1D_ARRAY_SHADOW                  :
    case GL_SAMPLER_2D_ARRAY_SHADOW                  :
    case GL_SAMPLER_2D_MULTISAMPLE                   :
    case GL_SAMPLER_2D_MULTISAMPLE_ARRAY             :
    case GL_SAMPLER_CUBE_SHADOW                      :
    case GL_SAMPLER_BUFFER                           :
    case GL_SAMPLER_2D_RECT                          :
    case GL_SAMPLER_2D_RECT_SHADOW                   :
    case GL_INT_SAMPLER_1D                           :
    case GL_INT_SAMPLER_2D                           :
    case GL_INT_SAMPLER_3D                           :
    case GL_INT_SAMPLER_CUBE                         :
    case GL_INT_SAMPLER_1D_ARRAY                     :
    case GL_INT_SAMPLER_2D_ARRAY                     :
    case GL_INT_SAMPLER_2D_MULTISAMPLE               :
    case GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY         :
    case GL_INT_SAMPLER_BUFFER                       :
    case GL_INT_SAMPLER_2D_RECT                      :
    case GL_UNSIGNED_INT_SAMPLER_1D                  :
    case GL_UNSIGNED_INT_SAMPLER_2D                  :
    case GL_UNSIGNED_INT_SAMPLER_3D                  :
    case GL_UNSIGNED_INT_SAMPLER_CUBE                :
    case GL_UNSIGNED_INT_SAMPLER_1D_ARRAY            :
    case GL_UNSIGNED_INT_SAMPLER_2D_ARRAY            :
    case GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE      :
    case GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY:
    case GL_UNSIGNED_INT_SAMPLER_BUFFER              :
    case GL_UNSIGNED_INT_SAMPLER_2D_RECT             :
      return true;
    default:
      return false;
  }
}

/**
 * @brief translates enum to string for uniform types
 *
 * @param type uniform type
 *
 * @return string representation
 */
std::string ge::gl::translateUniformType(GLenum type){
  switch(type){
    case GL_FLOAT                                    :return"GL_FLOAT"                                    ;
    case GL_FLOAT_VEC2                               :return"GL_FLOAT_VEC2"                               ;
    case GL_FLOAT_VEC3                               :return"GL_FLOAT_VEC3"                               ;
    case GL_FLOAT_VEC4                               :return"GL_FLOAT_VEC4"                               ;
    case GL_DOUBLE                                   :return"GL_DOUBLE"                                   ;
    case GL_DOUBLE_VEC2                              :return"GL_DOUBLE_VEC2"                              ;
    case GL_DOUBLE_VEC3                              :return"GL_DOUBLE_VEC3"                              ;
    case GL_DOUBLE_VEC4                              :return"GL_DOUBLE_VEC4"                              ;
    case GL_INT                                      :return"GL_INT"                                      ;
    case GL_INT_VEC2                                 :return"GL_INT_VEC2"                                 ;
    case GL_INT_VEC3                                 :return"GL_INT_VEC3"                                 ;
    case GL_INT_VEC4                                 :return"GL_INT_VEC4"                                 ;
    case GL_UNSIGNED_INT                             :return"GL_UNSIGNED_INT"                             ;
    case GL_UNSIGNED_INT_VEC2                        :return"GL_UNSIGNED_INT_VEC2"                        ;
    case GL_UNSIGNED_INT_VEC3                        :return"GL_UNSIGNED_INT_VEC3"                        ;
    case GL_UNSIGNED_INT_VEC4                        :return"GL_UNSIGNED_INT_VEC4"                        ;
    case GL_BOOL                                     :return"GL_BOOL"                                     ;
    case GL_BOOL_VEC2                                :return"GL_BOOL_VEC2"                                ;
    case GL_BOOL_VEC3                                :return"GL_BOOL_VEC3"                                ;
    case GL_BOOL_VEC4                                :return"GL_BOOL_VEC4"                                ;
    case GL_FLOAT_MAT2                               :return"GL_FLOAT_MAT2"                               ;
    case GL_FLOAT_MAT3                               :return"GL_FLOAT_MAT3"                               ;
    case GL_FLOAT_MAT4                               :return"GL_FLOAT_MAT4"                               ;
    case GL_FLOAT_MAT2x3                             :return"GL_FLOAT_MAT2x3"                             ;
    case GL_FLOAT_MAT2x4                             :return"GL_FLOAT_MAT2x4"                             ;
    case GL_FLOAT_MAT3x2                             :return"GL_FLOAT_MAT3x2"                             ;
    case GL_FLOAT_MAT3x4                             :return"GL_FLOAT_MAT3x4"                             ;
    case GL_FLOAT_MAT4x2                             :return"GL_FLOAT_MAT4x2"                             ;
    case GL_FLOAT_MAT4x3                             :return"GL_FLOAT_MAT4x3"                             ;
    case GL_DOUBLE_MAT2                              :return"GL_DOUBLE_MAT2"                              ;
    case GL_DOUBLE_MAT3                              :return"GL_DOUBLE_MAT3"                              ;
    case GL_DOUBLE_MAT4                              :return"GL_DOUBLE_MAT4"                              ;
    case GL_DOUBLE_MAT2x3                            :return"GL_DOUBLE_MAT2x3"                            ;
    case GL_DOUBLE_MAT2x4                            :return"GL_DOUBLE_MAT2x4"                            ;
    case GL_DOUBLE_MAT3x2                            :return"GL_DOUBLE_MAT3x2"                            ;
    case GL_DOUBLE_MAT3x4                            :return"GL_DOUBLE_MAT3x4"                            ;
    case GL_DOUBLE_MAT4x2                            :return"GL_DOUBLE_MAT4x2"                            ;
    case GL_DOUBLE_MAT4x3                            :return"GL_DOUBLE_MAT4x3"                            ;
    case GL_SAMPLER_1D                               :return"GL_SAMPLER_1D"                               ;
    case GL_SAMPLER_2D                               :return"GL_SAMPLER_2D"                               ;
    case GL_SAMPLER_3D                               :return"GL_SAMPLER_3D"                               ;
    case GL_SAMPLER_CUBE                             :return"GL_SAMPLER_CUBE"                             ;
    case GL_SAMPLER_1D_SHADOW                        :return"GL_SAMPLER_1D_SHADOW"                        ;
    case GL_SAMPLER_2D_SHADOW                        :return"GL_SAMPLER_2D_SHADOW"                        ;
    case GL_SAMPLER_1D_ARRAY                         :return"GL_SAMPLER_1D_ARRAY"                         ;
    case GL_SAMPLER_2D_ARRAY                         :return"GL_SAMPLER_2D_ARRAY"                         ;
    case GL_SAMPLER_1D_ARRAY_SHADOW                  :return"GL_SAMPLER_1D_ARRAY_SHADOW"                  ;
    case GL_SAMPLER_2D_ARRAY_SHADOW                  :return"GL_SAMPLER_2D_ARRAY_SHADOW"                  ;
    case GL_SAMPLER_2D_MULTISAMPLE                   :return"GL_SAMPLER_2D_MULTISAMPLE"                   ;
    case GL_SAMPLER_2D_MULTISAMPLE_ARRAY             :return"GL_SAMPLER_2D_MULTISAMPLE_ARRAY"             ;
    case GL_SAMPLER_CUBE_SHADOW                      :return"GL_SAMPLER_CUBE_SHADOW"                      ;
    case GL_SAMPLER_BUFFER                           :return"GL_SAMPLER_BUFFER"                           ;
    case GL_SAMPLER_2D_RECT                          :return"GL_SAMPLER_2D_RECT"                          ;
    case GL_SAMPLER_2D_RECT_SHADOW                   :return"GL_SAMPLER_2D_RECT_SHADOW"                   ;
    case GL_INT_SAMPLER_1D                           :return"GL_INT_SAMPLER_1D"                           ;
    case GL_INT_SAMPLER_2D                           :return"GL_INT_SAMPLER_2D"                           ;
    case GL_INT_SAMPLER_3D                           :return"GL_INT_SAMPLER_3D"                           ;
    case GL_INT_SAMPLER_CUBE                         :return"GL_INT_SAMPLER_CUBE"                         ;
    case GL_INT_SAMPLER_1D_ARRAY                     :return"GL_INT_SAMPLER_1D_ARRAY"                     ;
    case GL_INT_SAMPLER_2D_ARRAY                     :return"GL_INT_SAMPLER_2D_ARRAY"                     ;
    case GL_INT_SAMPLER_2D_MULTISAMPLE               :return"GL_INT_SAMPLER_2D_MULTISAMPLE"               ;
    case GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY         :return"GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY"         ;
    case GL_INT_SAMPLER_BUFFER                       :return"GL_INT_SAMPLER_BUFFER"                       ;
    case GL_INT_SAMPLER_2D_RECT                      :return"GL_INT_SAMPLER_2D_RECT"                      ;
    case GL_UNSIGNED_INT_SAMPLER_1D                  :return"GL_UNSIGNED_INT_SAMPLER_1D"                  ;
    case GL_UNSIGNED_INT_SAMPLER_2D                  :return"GL_UNSIGNED_INT_SAMPLER_2D"                  ;
    case GL_UNSIGNED_INT_SAMPLER_3D                  :return"GL_UNSIGNED_INT_SAMPLER_3D"                  ;
    case GL_UNSIGNED_INT_SAMPLER_CUBE                :return"GL_UNSIGNED_INT_SAMPLER_CUBE"                ;
    case GL_UNSIGNED_INT_SAMPLER_1D_ARRAY            :return"GL_UNSIGNED_INT_SAMPLER_1D_ARRAY"            ;
    case GL_UNSIGNED_INT_SAMPLER_2D_ARRAY            :return"GL_UNSIGNED_INT_SAMPLER_2D_ARRAY"            ;
    case GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE      :return"GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE"      ;
    case GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY:return"GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY";
    case GL_UNSIGNED_INT_SAMPLER_BUFFER              :return"GL_UNSIGNED_INT_SAMPLER_BUFFER"              ;
    case GL_UNSIGNED_INT_SAMPLER_2D_RECT             :return"GL_UNSIGNED_INT_SAMPLER_2D_RECT"             ;
    default                                          :return"unknown"                                     ;
  }
}

/**
 * @brief translates enum to string for buffer property types
 *
 * @param property buffer property type
 *
 * @return string representation
 */
std::string ge::gl::translateBufferProperty(GLenum property){
  switch(property){
    case GL_TYPE                                :return"GL_TYPE"                                ;
    case GL_ARRAY_SIZE                          :return"GL_ARRAY_SIZE"                          ;
    case GL_OFFSET                              :return"GL_OFFSET"                              ;
    case GL_BLOCK_INDEX                         :return"GL_BLOCK_INDEX"                         ;
    case GL_ARRAY_STRIDE                        :return"GL_ARRAY_STRIDE"                        ;
    case GL_MATRIX_STRIDE                       :return"GL_MATRIX_STRIDE"                       ;
    case GL_IS_ROW_MAJOR                        :return"GL_IS_ROW_MAJOR"                        ;
    case GL_REFERENCED_BY_VERTEX_SHADER         :return"GL_REFERENCED_BY_VERTEX_SHADER"         ;
    case GL_REFERENCED_BY_TESS_CONTROL_SHADER   :return"GL_REFERENCED_BY_TESS_CONTROL_SHADER"   ;
    case GL_REFERENCED_BY_TESS_EVALUATION_SHADER:return"GL_REFERENCED_BY_TESS_EVALUATION_SHADER";
    case GL_REFERENCED_BY_GEOMETRY_SHADER       :return"GL_REFERENCED_BY_GEOMETRY_SHADER"       ;
    case GL_REFERENCED_BY_FRAGMENT_SHADER       :return"GL_REFERENCED_BY_FRAGMENT_SHADER"       ;
    case GL_REFERENCED_BY_COMPUTE_SHADER        :return"GL_REFERENCED_BY_COMPUTE_SHADER"        ;
    case GL_TOP_LEVEL_ARRAY_SIZE                :return"GL_TOP_LEVEL_ARRAY_SIZE"                ;
    case GL_TOP_LEVEL_ARRAY_STRIDE              :return"GL_TOP_LEVEL_ARRAY_STRIDE"              ;
    default                                     :return"unknown"                                ;
  }
}



template<size_t TO>
size_t convertComplexShaderType(size_t what){
  using Element = std::tuple<GLenum,GLenum,GLint>;
  const std::array<Element,20>elements = {
    Element(GL_FLOAT            ,GL_FLOAT       ,1),
    Element(GL_FLOAT_VEC2       ,GL_FLOAT       ,2),
    Element(GL_FLOAT_VEC3       ,GL_FLOAT       ,3),
    Element(GL_FLOAT_VEC4       ,GL_FLOAT       ,4),
    Element(GL_DOUBLE           ,GL_DOUBLE      ,1),
    Element(GL_DOUBLE_VEC2      ,GL_DOUBLE      ,2),
    Element(GL_DOUBLE_VEC3      ,GL_DOUBLE      ,3),
    Element(GL_DOUBLE_VEC4      ,GL_DOUBLE      ,4),
    Element(GL_INT              ,GL_INT         ,1),
    Element(GL_INT_VEC2         ,GL_INT         ,2),
    Element(GL_INT_VEC3         ,GL_INT         ,3),
    Element(GL_INT_VEC4         ,GL_INT         ,4),
    Element(GL_UNSIGNED_INT     ,GL_UNSIGNED_INT,1),
    Element(GL_UNSIGNED_INT_VEC2,GL_UNSIGNED_INT,2),
    Element(GL_UNSIGNED_INT_VEC3,GL_UNSIGNED_INT,3),
    Element(GL_UNSIGNED_INT_VEC4,GL_UNSIGNED_INT,4),
    Element(GL_BOOL             ,GL_BOOL        ,1),
    Element(GL_BOOL_VEC2        ,GL_BOOL        ,2),
    Element(GL_BOOL_VEC3        ,GL_BOOL        ,3),
    Element(GL_BOOL_VEC4        ,GL_BOOL        ,4),
  };
  for(auto const&x:elements)
    if(std::get<0>(x)==what)return std::get<TO>(x);
  return -1;
}

bool depthInternalFormatTable(DepthInternalFormatElement&info,GLenum internalFormat){
  DepthInternalFormatElement const static elements[] = {
    {GL_DEPTH_COMPONENT16 ,"GL_DEPTH_COMPONENT16"," ",GL_DEPTH_COMPONENT,16,false,0 ,true ,},
    {GL_DEPTH_COMPONENT24 ,"GL_DEPTH_COMPONENT24"," ",GL_DEPTH_COMPONENT,24,false,0 ,true ,},
    {GL_DEPTH_COMPONENT32 ,"GL_DEPTH_COMPONENT32"," ",GL_DEPTH_COMPONENT,32,false,0 ,false,},
    {GL_DEPTH_COMPONENT32F,"GL_DEPTH_COMPONENT32F","",GL_DEPTH_COMPONENT,32,true ,0 ,true ,},
    {GL_DEPTH24_STENCIL8  ,"GL_DEPTH24_STENCIL8","  ",GL_DEPTH_STENCIL  ,24,false,8 ,true ,},
    {GL_DEPTH32F_STENCIL8 ,"GL_DEPTH32F_STENCIL8"," ",GL_DEPTH_STENCIL  ,32,true ,8 ,true ,},
    {GL_STENCIL_INDEX1    ,"GL_STENCIL_INDEX1","    ",GL_STENCIL_INDEX  ,0 ,false,1 ,false,},
    {GL_STENCIL_INDEX4    ,"GL_STENCIL_INDEX4","    ",GL_STENCIL_INDEX  ,0 ,false,4 ,false,},
    {GL_STENCIL_INDEX8    ,"GL_STENCIL_INDEX8","    ",GL_STENCIL_INDEX  ,0 ,false,8 ,true ,},
    {GL_STENCIL_INDEX16   ,"GL_STENCIL_INDEX16","   ",GL_STENCIL_INDEX  ,0 ,false,16,false,},
  };
  for(auto const&i:elements)
    if(i.format == internalFormat){
      info = i;
      return true;
    }
  return false;
}

bool ge::gl::isInternalFormatDepth(GLenum internalFormat){
  DepthInternalFormatElement info;
  return depthInternalFormatTable(info,internalFormat);
}

DepthInternalFormatElement ge::gl::getDepthInternalFormatInformation(GLenum internalFormat){
  DepthInternalFormatElement info;
  depthInternalFormatTable(info,internalFormat);
  return info;
}

bool compressedInternalFormatTable(CompressedInternalFormatElement&info,GLenum internalFormat){
  CompressedInternalFormatElement const static elements[] = {
    {GL_COMPRESSED_RED                           ,"GL_COMPRESSED_RED","                           ",GL_RED ,true ,CompressedInternalFormatElement::UNORM,},
    {GL_COMPRESSED_RG                            ,"GL_COMPRESSED_RG","                            ",GL_RG  ,true ,CompressedInternalFormatElement::UNORM,},
    {GL_COMPRESSED_RGB                           ,"GL_COMPRESSED_RGB","                           ",GL_RGB ,true ,CompressedInternalFormatElement::UNORM,},
    {GL_COMPRESSED_RGBA                          ,"GL_COMPRESSED_RGBA","                          ",GL_RGBA,true ,CompressedInternalFormatElement::UNORM,},
    {GL_COMPRESSED_SRGB                          ,"GL_COMPRESSED_SRGB","                          ",GL_RGB ,true ,CompressedInternalFormatElement::UNORM,},
    {GL_COMPRESSED_SRGB_ALPHA                    ,"GL_COMPRESSED_SRGB_ALPHA","                    ",GL_RGBA,true ,CompressedInternalFormatElement::UNORM,},
    {GL_COMPRESSED_RED_RGTC1                     ,"GL_COMPRESSED_RED_RGTC1","                     ",GL_RED ,false,CompressedInternalFormatElement::UNORM,},
    {GL_COMPRESSED_SIGNED_RED_RGTC1              ,"GL_COMPRESSED_SIGNED_RED_RGTC1","              ",GL_RED ,false,CompressedInternalFormatElement::SNORM,},
    {GL_COMPRESSED_RG_RGTC2                      ,"GL_COMPRESSED_RG_RGTC2","                      ",GL_RG  ,false,CompressedInternalFormatElement::UNORM,},
    {GL_COMPRESSED_SIGNED_RG_RGTC2               ,"GL_COMPRESSED_SIGNED_RG_RGTC2","               ",GL_RG  ,false,CompressedInternalFormatElement::SNORM,},
    {GL_COMPRESSED_RGBA_BPTC_UNORM               ,"GL_COMPRESSED_RGBA_BPTC_UNORM","               ",GL_RGBA,false,CompressedInternalFormatElement::UNORM,},
    {GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM         ,"GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM","         ",GL_RGBA,false,CompressedInternalFormatElement::UNORM,},
    {GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT         ,"GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT","         ",GL_RGB ,false,CompressedInternalFormatElement::FLOAT,},
    {GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT       ,"GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT","       ",GL_RGB ,false,CompressedInternalFormatElement::FLOAT,},
    {GL_COMPRESSED_RGB8_ETC2                     ,"GL_COMPRESSED_RGB8_ETC2","                     ",GL_RGB ,false,CompressedInternalFormatElement::UNORM,},
    {GL_COMPRESSED_SRGB8_ETC2                    ,"GL_COMPRESSED_SRGB8_ETC2","                    ",GL_RGB ,false,CompressedInternalFormatElement::UNORM,},
    {GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2 ,"GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2"," ",GL_RGB ,false,CompressedInternalFormatElement::UNORM,},
    {GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2,"GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2","",GL_RGB ,false,CompressedInternalFormatElement::UNORM,},
    {GL_COMPRESSED_RGBA8_ETC2_EAC                ,"GL_COMPRESSED_RGBA8_ETC2_EAC","                ",GL_RGBA,false,CompressedInternalFormatElement::UNORM,},
    {GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC         ,"GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC","         ",GL_RGBA,false,CompressedInternalFormatElement::UNORM,},
    {GL_COMPRESSED_R11_EAC                       ,"GL_COMPRESSED_R11_EAC","                       ",GL_RED ,false,CompressedInternalFormatElement::UNORM,},
    {GL_COMPRESSED_SIGNED_R11_EAC                ,"GL_COMPRESSED_SIGNED_R11_EAC","                ",GL_RED ,false,CompressedInternalFormatElement::SNORM,},
    {GL_COMPRESSED_RG11_EAC                      ,"GL_COMPRESSED_RG11_EAC","                      ",GL_RG  ,false,CompressedInternalFormatElement::UNORM,},
    {GL_COMPRESSED_SIGNED_RG11_EAC               ,"GL_COMPRESSED_SIGNED_RG11_EAC","               ",GL_RG  ,false,CompressedInternalFormatElement::SNORM,},
  };
  for(auto const&i:elements)
    if(i.format == internalFormat){
      info = i;
      return true;
    }
  return false;
}

bool ge::gl::isInternalFormatCompressed(GLenum internalFormat){
  CompressedInternalFormatElement info;
  return compressedInternalFormatTable(info,internalFormat);
}

CompressedInternalFormatElement ge::gl::getCompressedInternalFormatInformation(GLenum internalFormat){
  CompressedInternalFormatElement info;
  compressedInternalFormatTable(info,internalFormat);
  return info;
}

bool basicInternalFormatTable(BasicInternalFormatElement&info,GLenum internalFormat){
  BasicInternalFormatElement const static elements[] = {
    {GL_R8            ,"GL_R8","            ",GL_RED ,1,{8 ,0 ,0 ,0 ,},true ,true ,true ,BasicInternalFormatElement::UNSIGNED_FIXED_POINT}, 
    {GL_R8_SNORM      ,"GL_R8_SNORM","      ",GL_RED ,1,{8 ,0 ,0 ,0 ,},true ,false,true ,BasicInternalFormatElement::FIXED_POINT         }, 
    {GL_R16           ,"GL_R16","           ",GL_RED ,1,{16,0 ,0 ,0 ,},true ,true ,true ,BasicInternalFormatElement::UNSIGNED_FIXED_POINT}, 
    {GL_R16_SNORM     ,"GL_R16_SNORM","     ",GL_RED ,1,{16,0 ,0 ,0 ,},true ,false,true ,BasicInternalFormatElement::FIXED_POINT         }, 
    {GL_RG8           ,"GL_RG8","           ",GL_RG  ,2,{8 ,8 ,0 ,0 ,},true ,true ,true ,BasicInternalFormatElement::UNSIGNED_FIXED_POINT}, 
    {GL_RG8_SNORM     ,"GL_RG8_SNORM","     ",GL_RG  ,2,{8 ,8 ,0 ,0 ,},true ,false,true ,BasicInternalFormatElement::FIXED_POINT         }, 
    {GL_RG16          ,"GL_RG16","          ",GL_RG  ,2,{16,16,0 ,0 ,},true ,true ,true ,BasicInternalFormatElement::UNSIGNED_FIXED_POINT}, 
    {GL_RG16_SNORM    ,"GL_RG16_SNORM","    ",GL_RG  ,2,{16,16,0 ,0 ,},true ,false,true ,BasicInternalFormatElement::FIXED_POINT         }, 
    {GL_R3_G3_B2      ,"GL_R3_G3_B2","      ",GL_RGB ,3,{3 ,3 ,2 ,0 ,},true ,false,true ,BasicInternalFormatElement::UNSIGNED_FIXED_POINT}, 
    {GL_RGB4          ,"GL_RGB4","          ",GL_RGB ,3,{4 ,4 ,4 ,0 ,},true ,false,true ,BasicInternalFormatElement::UNSIGNED_FIXED_POINT}, 
    {GL_RGB5          ,"GL_RGB5","          ",GL_RGB ,3,{5 ,5 ,5 ,0 ,},true ,false,true ,BasicInternalFormatElement::UNSIGNED_FIXED_POINT}, 
    {GL_RGB565        ,"GL_RGB565","        ",GL_RGB ,3,{5 ,6 ,5 ,0 ,},true ,true ,true ,BasicInternalFormatElement::UNSIGNED_FIXED_POINT}, 
    {GL_RGB8          ,"GL_RGB8","          ",GL_RGB ,3,{8 ,8 ,8 ,0 ,},true ,false,true ,BasicInternalFormatElement::UNSIGNED_FIXED_POINT}, 
    {GL_RGB8_SNORM    ,"GL_RGB8_SNORM","    ",GL_RGB ,3,{8 ,8 ,8 ,0 ,},true ,false,true ,BasicInternalFormatElement::FIXED_POINT         }, 
    {GL_RGB10         ,"GL_RGB10","         ",GL_RGB ,3,{10,10,10,0 ,},true ,false,true ,BasicInternalFormatElement::UNSIGNED_FIXED_POINT}, 
    {GL_RGB12         ,"GL_RGB12","         ",GL_RGB ,3,{12,12,12,0 ,},true ,false,true ,BasicInternalFormatElement::UNSIGNED_FIXED_POINT}, 
    {GL_RGB16         ,"GL_RGB16","         ",GL_RGB ,3,{16,16,16,0 ,},true ,false,true ,BasicInternalFormatElement::UNSIGNED_FIXED_POINT}, 
    {GL_RGB16_SNORM   ,"GL_RGB16_SNORM","   ",GL_RGB ,3,{16,16,16,0 ,},true ,false,true ,BasicInternalFormatElement::FIXED_POINT         }, 
    {GL_RGBA2         ,"GL_RGBA2","         ",GL_RGBA,4,{2 ,2 ,2 ,2 ,},true ,false,true ,BasicInternalFormatElement::UNSIGNED_FIXED_POINT}, 
    {GL_RGBA4         ,"GL_RGBA4","         ",GL_RGBA,4,{4 ,4 ,4 ,4 ,},true ,true ,true ,BasicInternalFormatElement::UNSIGNED_FIXED_POINT}, 
    {GL_RGB5_A1       ,"GL_RGB5_A1","       ",GL_RGBA,4,{5 ,5 ,5 ,1 ,},true ,true ,true ,BasicInternalFormatElement::UNSIGNED_FIXED_POINT}, 

    {GL_RGBA8         ,"GL_RGBA8","         ",GL_RGBA,4,{8 ,8 ,8 ,8 ,},true ,true ,true ,BasicInternalFormatElement::UNSIGNED_FIXED_POINT},   
    {GL_RGBA8_SNORM   ,"GL_RGBA8_SNORM","   ",GL_RGBA,4,{8 ,8 ,8 ,8 ,},true ,false,true ,BasicInternalFormatElement::FIXED_POINT},   
    {GL_RGB10_A2      ,"GL_RGB10_A2","      ",GL_RGBA,4,{10,10,10,2 ,},true ,true ,true ,BasicInternalFormatElement::UNSIGNED_FIXED_POINT},   
    {GL_RGB10_A2UI    ,"GL_RGB10_A2UI","    ",GL_RGBA,4,{10,10,10,2 ,},true ,true ,true ,BasicInternalFormatElement::UNSIGNED_INT},   
    {GL_RGBA12        ,"GL_RGBA12","        ",GL_RGBA,4,{12,12,12,12,},true ,false,true ,BasicInternalFormatElement::UNSIGNED_FIXED_POINT},   
    {GL_RGBA16        ,"GL_RGBA16","        ",GL_RGBA,4,{16,16,16,16,},true ,true ,true ,BasicInternalFormatElement::UNSIGNED_FIXED_POINT},   
    {GL_RGBA16_SNORM  ,"GL_RGBA16_SNORM","  ",GL_RGBA,4,{16,16,16,16,},true ,false,true ,BasicInternalFormatElement::FIXED_POINT}, 
    {GL_SRGB8         ,"GL_SRGB8","         ",GL_RGB ,3,{8 ,8 ,8 ,0 ,},true ,false,true ,BasicInternalFormatElement::UNSIGNED_FIXED_POINT}, 
    {GL_SRGB8_ALPHA8  ,"GL_SRGB8_ALPHA8","  ",GL_RGBA,4,{8 ,8 ,8 ,8 ,},true ,true ,true ,BasicInternalFormatElement::UNSIGNED_FIXED_POINT}, 
    {GL_R16F          ,"GL_R16F","          ",GL_RED ,1,{16,0 ,0 ,0 ,},true ,true ,true ,BasicInternalFormatElement::FLOAT               }, 
    {GL_RG16F         ,"GL_RG16F","         ",GL_RG  ,2,{16,16,0 ,0 ,},true ,true ,true ,BasicInternalFormatElement::FLOAT               }, 
    {GL_RGB16F        ,"GL_RGB16F","        ",GL_RGB ,3,{16,16,16,0 ,},true ,false,true ,BasicInternalFormatElement::FLOAT               }, 
    {GL_RGBA16F       ,"GL_RGBA16F","       ",GL_RGBA,4,{16,16,16,16,},true ,true ,true ,BasicInternalFormatElement::FLOAT               }, 
    {GL_R32F          ,"GL_R32F","          ",GL_RED ,1,{32,0 ,0 ,0 ,},true ,true ,true ,BasicInternalFormatElement::FLOAT               }, 
    {GL_RG32F         ,"GL_RG32F","         ",GL_RG  ,2,{32,32,0 ,0 ,},true ,true ,true ,BasicInternalFormatElement::FLOAT               }, 
    {GL_RGB32F        ,"GL_RGB32F","        ",GL_RGB ,3,{32,32,32,0 ,},true ,false,true ,BasicInternalFormatElement::FLOAT               }, 
    {GL_RGBA32F       ,"GL_RGBA32F","       ",GL_RGBA,4,{32,32,32,32,},true ,true ,true ,BasicInternalFormatElement::FLOAT               }, 
    {GL_R11F_G11F_B10F,"GL_R11F_G11F_B10F","",GL_RGB ,3,{11,11,10,0 ,},true ,true ,true ,BasicInternalFormatElement::FLOAT               },
    {GL_RGB9_E5       ,"GL_RGB9_E5","       ",GL_RGB ,4,{9 ,9 ,9 ,5 ,},false,false,true ,BasicInternalFormatElement::UNSIGNED_FIXED_POINT}, 
    {GL_R8I           ,"GL_R8I","           ",GL_RED ,1,{8 ,0 ,0 ,0 ,},true ,true ,true ,BasicInternalFormatElement::INT                 }, 
    {GL_R8UI          ,"GL_R8UI","          ",GL_RED ,1,{8 ,0 ,0 ,0 ,},true ,true ,true ,BasicInternalFormatElement::UNSIGNED_INT        }, 
    {GL_R16I          ,"GL_R16I","          ",GL_RED ,1,{16,0 ,0 ,0 ,},true ,true ,true ,BasicInternalFormatElement::INT                 }, 
    {GL_R16UI         ,"GL_R16UI","         ",GL_RED ,1,{16,0 ,0 ,0 ,},true ,true ,true ,BasicInternalFormatElement::UNSIGNED_INT        }, 
    {GL_R32I          ,"GL_R32I","          ",GL_RED ,1,{32,0 ,0 ,0 ,},true ,true ,true ,BasicInternalFormatElement::INT                 }, 
    {GL_R32UI         ,"GL_R32UI","         ",GL_RED ,1,{32,0 ,0 ,0 ,},true ,true ,true ,BasicInternalFormatElement::UNSIGNED_INT        }, 
    {GL_RG8I          ,"GL_RG8I","          ",GL_RG  ,2,{8 ,8 ,0 ,0 ,},true ,true ,true ,BasicInternalFormatElement::INT                 }, 
    {GL_RG8UI         ,"GL_RG8UI","         ",GL_RG  ,2,{8 ,8 ,0 ,0 ,},true ,true ,true ,BasicInternalFormatElement::UNSIGNED_INT        }, 
    {GL_RG16I         ,"GL_RG16I","         ",GL_RG  ,2,{16,16,0 ,0 ,},true ,true ,true ,BasicInternalFormatElement::INT                 }, 
    {GL_RG16UI        ,"GL_RG16UI","        ",GL_RG  ,2,{16,16,0 ,0 ,},true ,true ,true ,BasicInternalFormatElement::UNSIGNED_INT        }, 
    {GL_RG32I         ,"GL_RG32I","         ",GL_RG  ,2,{32,32,0 ,0 ,},true ,true ,true ,BasicInternalFormatElement::INT                 }, 
    {GL_RG32UI        ,"GL_RG32UI","        ",GL_RG  ,2,{32,32,0 ,0 ,},true ,true ,true ,BasicInternalFormatElement::UNSIGNED_INT        }, 
    {GL_RGB8I         ,"GL_RGB8I","         ",GL_RGB ,3,{8 ,8 ,8 ,0 ,},true ,false,true ,BasicInternalFormatElement::INT                 }, 
    {GL_RGB8UI        ,"GL_RGB8UI","        ",GL_RGB ,3,{8 ,8 ,8 ,0 ,},true ,false,true ,BasicInternalFormatElement::UNSIGNED_INT        }, 
    
    {GL_RGB16I        ,"GL_RGB16I","        ",GL_RGB ,3,{16,16,16,0 ,},true ,false,true ,BasicInternalFormatElement::INT                 },
    {GL_RGB16UI       ,"GL_RGB16UI","       ",GL_RGB ,3,{16,16,16,0 ,},true ,false,true ,BasicInternalFormatElement::UNSIGNED_INT        },
    {GL_RGB32I        ,"GL_RGB32I","        ",GL_RGB ,3,{32,32,32,0 ,},true ,false,true ,BasicInternalFormatElement::INT                 },
    {GL_RGB32UI       ,"GL_RGB32UI","       ",GL_RGB ,3,{32,32,32,0 ,},true ,false,true ,BasicInternalFormatElement::UNSIGNED_INT        },
    {GL_RGBA8I        ,"GL_RGBA8I","        ",GL_RGBA,4,{8 ,8 ,8 ,8 ,},true ,true ,true ,BasicInternalFormatElement::INT                 },
    {GL_RGBA8UI       ,"GL_RGBA8UI","       ",GL_RGBA,4,{8 ,8 ,8 ,8 ,},true ,true ,true ,BasicInternalFormatElement::UNSIGNED_INT        },
    {GL_RGBA16I       ,"GL_RGBA16I","       ",GL_RGBA,4,{16,16,16,16,},true ,true ,true ,BasicInternalFormatElement::INT                 },
    {GL_RGBA16UI      ,"GL_RGBA16UI","      ",GL_RGBA,4,{16,16,16,16,},true ,true ,true ,BasicInternalFormatElement::UNSIGNED_INT        },
    {GL_RGBA32I       ,"GL_RGBA32I","       ",GL_RGBA,4,{32,32,32,32,},true ,true ,true ,BasicInternalFormatElement::INT                 },
    {GL_RGBA32UI      ,"GL_RGBA32UI","      ",GL_RGBA,4,{32,32,32,32,},true ,true ,true ,BasicInternalFormatElement::UNSIGNED_INT        },
  };
  for(auto const&i:elements)
    if(i.format == internalFormat){
      info = i;
      return true;
    }
  return false;
}

bool ge::gl::isInternalFormatBasic(GLenum internalFormat){
  BasicInternalFormatElement info;
  return basicInternalFormatTable(info,internalFormat);
}

BasicInternalFormatElement ge::gl::getBasicInternalFormatInformation(GLenum internalFormat){
  BasicInternalFormatElement info;
  basicInternalFormatTable(info,internalFormat);
  return info;
}

