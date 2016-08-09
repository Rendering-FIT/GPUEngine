#pragma once

#include<cassert>
#include<geGL/OpenGL.h>

namespace ge{
  namespace gl{
    class FunctionTable{
      public:
        FunctionTable(){}
        virtual ~FunctionTable(){}
        bool construct(){
          assert(this!=nullptr);
          return this->m_init();
        }
        virtual bool m_init(){return true;}
#include<geGL/Generated/FunctionTableCalls.h>
#include<geGL/Generated/OpenGLPFN.h>
#include<geGL/Generated/OpenGLFunctions.h>
#include<geGL/Generated/MemberOpenGLPFN.h>
#include<geGL/Generated/MemberOpenGLFunctions.h>
    };
  }
}


