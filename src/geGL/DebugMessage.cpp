#include<geGL/DebugMessage.h>

namespace ge{
  namespace gl{
    std::string translateDebugSource(GLenum source){
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
    std::string translateDebugType(GLenum type){
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
    std::string translateDebugSeverity(GLenum severity){
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
        GLuint        id,
        GLenum        severity,
        GLsizei       length,
        const GLchar *message,
        void         *userParam){
      std::cerr<<
        "source: "   <<translateDebugSource  (source  )<<
        " type: "    <<translateDebugType    (type    )<<
        " severity: "<<translateDebugSeverity(severity)<<
        " : "        <<message                         <<std::endl;
    }
    void setDefaultDebugMessage(){
      glEnable(GL_DEBUG_OUTPUT);
      glDebugMessageCallback((GLDEBUGPROC)defaultDebugMessage,NULL);
    }
    void setDebugMessage(GLDEBUGPROC fce,void*data){
      glEnable(GL_DEBUG_OUTPUT);
      glDebugMessageCallback(fce,data);
    }
  }//gl
}//ge
