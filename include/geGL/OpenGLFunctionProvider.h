#pragma once

#include<geGL/OpenGL.h>
#include<cassert>

namespace ge{
  namespace gl{
    namespace opengl{
      class GEGL_EXPORT FunctionProvider{
        public:
          FunctionProvider(FunctionTablePointer const&t = nullptr);
          ~FunctionProvider(){}
          FunctionTablePointer const&getFunctionTable()const{
            assert(this!=nullptr);
            return this->m_table;
          }
          void setFunctionTable(FunctionTablePointer const&t){
            assert(this!=nullptr);
            this->m_table = t;
          }
#include<geGL/Generated/FunctionProviderDeclarations.h>
        protected:
          FunctionTablePointer m_table = nullptr;
      };
    }
  }
}


