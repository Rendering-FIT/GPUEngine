#pragma once

#include<geGL/FunctionLoaderInterface.h>

namespace ge{
  namespace gl{
    class DefaultLoader: public FunctionLoaderInterface{
      public:
        /**
         * @brief constructor
         *
         * @param getProcAddress loading function like (SDL_GL_GetProcAddress, wglGetProcAddress, ...)
         */
        DefaultLoader(GET_PROC_ADDRESS getProcAddress){
          this->m_getProcAddress = getProcAddress;
        }
        ~DefaultLoader(){}
        /**
         * @brief This function loads OpenGL function using its name
         *
         * @param fceName function name of OpenGL fuction ("glUseProgram", ...)
         *
         * @return function pointer to requested OpenGL function
         */
        virtual FUNCTION_POINTER load(char const*fceName)const override{
          return ((FUNCTION_POINTER(*)(char const*))this->m_getProcAddress)(fceName);
        }
      protected:
        GET_PROC_ADDRESS m_getProcAddress = nullptr;
    };
  }
}
