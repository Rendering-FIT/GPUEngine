#ifndef _DEBUGMESSAGE_H_
#define _DEBUGMESSAGE_H_

#include<geGL/OpenGL.h>
#include<iostream>

namespace ge{
  namespace gl{
    std::string translateDebugSource  (GLenum source  );
    std::string translateDebugType    (GLenum type    );
    std::string translateDebugSeverity(GLenum severity);
    void setDefaultDebugMessage();
    void setDebugMessage(GLDEBUGPROC fce,void*data);
  }//gl
}//ge


#endif//_DEBUGMESSAGE_H_
