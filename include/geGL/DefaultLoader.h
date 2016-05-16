#pragma once

#include<geGL/FunctionLoaderInterface.h>

namespace ge{
  namespace gl{
    namespace opengl{
      class DefaultLoader: public FunctionLoaderInterface{
        public:
          DefaultLoader(GET_PROC_ADDRESS getProcAddress){
            this->m_getProcAddress = getProcAddress;
          }
          ~DefaultLoader(){}
          virtual FUNCTION_POINTER load(char const*fceName)const{
            return this->m_getProcAddress(fceName);
          }
        protected:
          ge::gl::opengl::GET_PROC_ADDRESS m_getProcAddress = nullptr;
      };
    }
  }
}
