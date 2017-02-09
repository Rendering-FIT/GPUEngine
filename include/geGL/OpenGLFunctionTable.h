#pragma once

#include<cassert>
#include<geGL/OpenGL.h>

#include<geGL/Generated/NumberOfFunctions.h>

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
#include<geGL/Generated/FunctionTableCalls.h>
#include<geGL/Generated/OpenGLPFN.h>
        //Deu to MSVS2013 and its slow compilation, this has to be done this way...
        union{
          FUNCTION_POINTER baseFunctions[GE_GL_NOF_OPENGL_FUNCTIONS];
          struct {
            #include<geGL/Generated/OpenGLFunctions.h>
          };//functionsStruct;
        };//functionsUnion;
#include<geGL/Generated/MemberOpenGLPFN.h>
        //Due to MSVS2013 and its slow compilation, this has to be done this way...
        union{
          MEMBER_FUNCTION_POINTER memberFunctions[GE_GL_NOF_OPENGL_FUNCTIONS];
          struct {
            #include<geGL/Generated/MemberOpenGLFunctions.h>
          };//memberFunctionsStruct;
        };//memberFunctionsUnion;
    };
  }
}


