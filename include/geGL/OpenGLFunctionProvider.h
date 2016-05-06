#pragma once

#include<memory>
#include<cassert>
#include<geGL/OpenGLFunctionTable.h>

namespace ge{
  namespace gl{
    namespace opengl{
      class GEGL_EXPORT FunctionProvider{
        protected:
          FunctionTablePointer _table = nullptr;
          inline FunctionTablePointer const&_getTable()const{
            assert(this->_table != nullptr);
            return this->_table;
          }
        public:
          FunctionProvider(FunctionTablePointer const&table);
          inline void setFunctionTable(FunctionTablePointer const&table){
            this->_table = table;
          }
          inline FunctionTablePointer const&getFunctionTable()const{
            return this->_table;
          }
#include<geGL/GeneratedOpenGLFunctionCalls.h>
      };
    }
  }
}


