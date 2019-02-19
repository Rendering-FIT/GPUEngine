#include<geGL/DebugMessage.h>
#include<geGL/OpenGLUtil.h>
#include<string>
#include<cassert>

using namespace ge::gl;

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

ge::gl::ContextPointer const&getContext(ge::gl::ContextPointer const&gl){
  if(gl!=nullptr)return gl;
  return ge::gl::getDefaultContext();
}

/**
 * @brief sets debug function - it will report GL_DEBUG_SEVERITY_LOW/MEDIUM/HIGH
 */
void ge::gl::setLowAndGreaterDebugMessage(
    ContextPointer const&ogl){
  auto gl = getContext(ogl);
  assert(gl!=nullptr);
  gl->glEnable(GL_DEBUG_OUTPUT);
  gl->glDebugMessageCallback((GLDEBUGPROC)lowDebugMessage,NULL);
}

/**
 * @brief sets debug function - it will report GL_DEBUG_SEVERITY_MEDIUM/HIGH
 */
void ge::gl::setMediumAndGreaterDebugMessage(
    ContextPointer const&ogl){
  auto gl = getContext(ogl);
  assert(gl!=nullptr);
  gl->glEnable(GL_DEBUG_OUTPUT);
  gl->glDebugMessageCallback((GLDEBUGPROC)mediumDebugMessage,NULL);
}

/**
 * @brief sets debug function - it will report only GL_DEBUG_SEVERITY_HIGH errors
 */
void ge::gl::setHighDebugMessage(
    ContextPointer const&ogl){
  auto gl = getContext(ogl);
  assert(gl!=nullptr);
  gl->glEnable(GL_DEBUG_OUTPUT);
  gl->glDebugMessageCallback((GLDEBUGPROC)highDebugMessage,NULL);
}

/**
 * @brief sets default debug function - it will report everything
 */
void ge::gl::setDefaultDebugMessage(
    ContextPointer const&ogl){
  auto gl = getContext(ogl);
  assert(gl!=nullptr);
  gl->glEnable(GL_DEBUG_OUTPUT);
  gl->glDebugMessageCallback((GLDEBUGPROC)defaultDebugMessage,NULL);
}

/**
 * @brief sets callback function for OpenGL debugging
 *
 * @param fce callback function
 * @param data callback user data
 */
void ge::gl::setDebugMessage(
    GLDEBUGPROC fce,
    void*data,
    ContextPointer const&ogl){
  auto gl = getContext(ogl);
  assert(gl!=nullptr);
  gl->glEnable(GL_DEBUG_OUTPUT);
  gl->glDebugMessageCallback(fce,data);
}
