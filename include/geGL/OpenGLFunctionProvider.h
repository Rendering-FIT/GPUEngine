#pragma once

#include<memory>
#include<cassert>
#include<geGL/OpenGL.h>
#include<geGL/OpenGLCapabilities.h>

namespace ge{
  namespace gl{
    namespace opengl{
      class GEGL_EXPORT FunctionProvider{
        public:
          FunctionProvider(FunctionTablePointer const&t);
          ~FunctionProvider(){}
          FunctionTablePointer const&getFunctionTable()const{return this->m_table;}
          void setFunctionTable(FunctionTablePointer const&t){this->m_table = t;}
#include<geGL/Generated/FunctionProviderDeclarations.h>
        protected:
          FunctionTablePointer m_table = nullptr;
      };
      using FunctionProviderPointer = std::shared_ptr<FunctionProvider>;

    }
  }
}


