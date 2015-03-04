#ifndef _DEBUGMESSAGE_H_
#define _DEBUGMESSAGE_H_

#include<geGL/OpenGL.h>
#include<iostream>

namespace ge{
  namespace gl{
    GEGL_EXPORT std::string translateDebugSource  (GLenum source  );
    GEGL_EXPORT std::string translateDebugType    (GLenum type    );
    GEGL_EXPORT std::string translateDebugSeverity(GLenum severity);
    GEGL_EXPORT void setDefaultDebugMessage();
    GEGL_EXPORT void setDebugMessage(GLDEBUGPROC fce,void*data);
  }//gl
}//ge


#endif//_DEBUGMESSAGE_H_
