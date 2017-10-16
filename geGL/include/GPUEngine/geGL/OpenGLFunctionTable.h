#pragma once

#include<cassert>
#include<GPUEngine/geGL/OpenGL.h>

#include<GPUEngine/geGL/Generated/NumberOfFunctions.h>

namespace ge{
  namespace gl{
    class FunctionTable{
      public:
        using FUNCTION_POINTER = void(*)();
        using MEMBER_FUNCTION_POINTER = void(FunctionTable::*)();
        FunctionTable(){}
        virtual ~FunctionTable(){}
        bool construct(){
          assert(this!=nullptr);
          return this->m_init();
        }
        virtual bool m_init(){return true;}
#include<GPUEngine/geGL/Generated/FunctionTableCalls.h>
#include<GPUEngine/geGL/Generated/OpenGLPFN.h>
#include<GPUEngine/geGL/Generated/OpenGLFunctions.h>
#include<GPUEngine/geGL/Generated/MemberOpenGLPFN.h>
#include<GPUEngine/geGL/Generated/MemberOpenGLFunctions.h>
    };
  }
}


