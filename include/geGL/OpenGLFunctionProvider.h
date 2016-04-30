#pragma once

#include<memory>
#include<cassert>
#include<geGL/OpenGLFunctionTable.h>

namespace ge{
  namespace gl{
    class GEGL_EXPORT OpenGLFunctionProvider{
      protected:
        std::shared_ptr<OpenGLFunctionTable>_table = nullptr;
        inline std::shared_ptr<OpenGLFunctionTable>const&_getTable()const{
          assert(this->_table != nullptr);
          return this->_table;
        }
      public:
        OpenGLFunctionProvider(std::shared_ptr<OpenGLFunctionTable>const&table){
          this->_table = table;
        }
        inline void setOpenGLFunctionTable(std::shared_ptr<OpenGLFunctionTable>const&table){
          this->_table = table;
        }
        inline std::shared_ptr<OpenGLFunctionTable>const&getOpenGLFunctionTable()const{
          return this->_table;
        }
#include<geGL/GeneratedOpenGLFunctionCalls.h>
    };
  }
}


