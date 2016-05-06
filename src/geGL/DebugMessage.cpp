#include<geGL/DebugMessage.h>
#include<string>

using namespace ge::gl;
using namespace ge::gl::opengl;

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
void defaultDebugMessage(
    GLenum        source,
    GLenum        type,
    GLuint        /*id*/,
    GLenum        severity,
    GLsizei       /*length*/,
    const GLchar *message,
    void*        /*userParam*/){
  std::cerr<<
    "source: "   <<translateDebugSource  (source  )<<
    " type: "    <<translateDebugType    (type    )<<
    " severity: "<<translateDebugSeverity(severity)<<
    " : "        <<message                         <<std::endl;
}
void lowDebugMessage( 
    GLenum        source,
    GLenum        type,
    GLuint        /*id*/,
    GLenum        severity,
    GLsizei       /*length*/,
    const GLchar *message,
    void*         /*userParam*/){
  if(severity==GL_DEBUG_SEVERITY_NOTIFICATION)return;
  std::cerr<<
    "source: "   <<translateDebugSource  (source  )<<
    " type: "    <<translateDebugType    (type    )<<
    " severity: "<<translateDebugSeverity(severity)<<
    " : "        <<message                         <<std::endl;
}
void mediumDebugMessage( 
    GLenum        source,
    GLenum        type,
    GLuint        /*id*/,
    GLenum        severity,
    GLsizei       /*length*/,
    const GLchar *message,
    void*         /*userParam*/){
  if(severity==GL_DEBUG_SEVERITY_NOTIFICATION)return;
  if(severity==GL_DEBUG_SEVERITY_LOW         )return;
  std::cerr<<
    "source: "   <<translateDebugSource  (source  )<<
    " type: "    <<translateDebugType    (type    )<<
    " severity: "<<translateDebugSeverity(severity)<<
    " : "        <<message                         <<std::endl;
}
void highDebugMessage( 
    GLenum        source,
    GLenum        type,
    GLuint        /*id*/,
    GLenum        severity,
    GLsizei       /*length*/,
    const GLchar *message,
    void*         /*userParam*/){
  if(severity==GL_DEBUG_SEVERITY_NOTIFICATION)return;
  if(severity==GL_DEBUG_SEVERITY_LOW         )return;
  if(severity==GL_DEBUG_SEVERITY_MEDIUM      )return;
  std::cerr<<
    "source: "   <<translateDebugSource  (source  )<<
    " type: "    <<translateDebugType    (type    )<<
    " severity: "<<translateDebugSeverity(severity)<<
    " : "        <<message                         <<std::endl;
}

/**
 * @brief sets debug function - it will report GL_DEBUG_SEVERITY_LOW/MEDIUM/HIGH
 */
void ge::gl::setLowAndGreaterDebugMessage(
#if defined(REPLACE_GLEW)
    FunctionProvider const&gl
#endif
    ){
#if defined(REPLACE_GLEW)
  gl.glEnable(GL_DEBUG_OUTPUT);
  gl.glDebugMessageCallback((GLDEBUGPROC)lowDebugMessage,NULL);
#else
  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback((GLDEBUGPROC)lowDebugMessage,NULL);
#endif
}

/**
 * @brief sets debug function - it will report GL_DEBUG_SEVERITY_MEDIUM/HIGH
 */
void ge::gl::setMediumAndGreaterDebugMessage(
#if defined(REPLACE_GLEW)
    FunctionProvider const&gl
#endif
    ){
#if defined(REPLACE_GLEW)
  gl.glEnable(GL_DEBUG_OUTPUT);
  gl.glDebugMessageCallback((GLDEBUGPROC)mediumDebugMessage,NULL);
#else
  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback((GLDEBUGPROC)mediumDebugMessage,NULL);
#endif
}

/**
 * @brief sets debug function - it will report only GL_DEBUG_SEVERITY_HIGH errors
 */
void ge::gl::setHighDebugMessage(
#if defined(REPLACE_GLEW)
    FunctionProvider const&gl
#endif
    ){
#if defined(REPLACE_GLEW)
  gl.glEnable(GL_DEBUG_OUTPUT);
  gl.glDebugMessageCallback((GLDEBUGPROC)highDebugMessage,NULL);
#else
  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback((GLDEBUGPROC)highDebugMessage,NULL);
#endif
}

/**
 * @brief sets default debug function - it will report everything
 */
void ge::gl::setDefaultDebugMessage(
#if defined(REPLACE_GLEW)
    FunctionProvider const&gl
#endif
    ){
#if defined(REPLACE_GLEW)
  gl.glEnable(GL_DEBUG_OUTPUT);
  gl.glDebugMessageCallback((GLDEBUGPROC)defaultDebugMessage,NULL);
#else
  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback((GLDEBUGPROC)defaultDebugMessage,NULL);
#endif
}

/**
 * @brief sets callback function for OpenGL debugging
 *
 * @param fce callback function
 * @param data callback user data
 */
void ge::gl::setDebugMessage(
#if defined(REPLACE_GLEW)
    FunctionProvider const&gl,
#endif
    GLDEBUGPROC fce,
    void*data){
#if defined(REPLACE_GLEW)
  gl.glEnable(GL_DEBUG_OUTPUT);
  gl.glDebugMessageCallback(fce,data);
#else
  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback(fce,data);
#endif
}
