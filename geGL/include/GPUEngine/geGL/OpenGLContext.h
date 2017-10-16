#pragma once

#include<GPUEngine/geGL/OpenGL.h>
#include<cassert>

class GEGL_EXPORT ge::gl::Context{
  public:
    Context(FunctionTablePointer const&t = nullptr);
    ~Context(){}
    FunctionTablePointer const&getFunctionTable()const{
      assert(this!=nullptr);
      return this->m_table;
    }
    void setFunctionTable(FunctionTablePointer const&t){
      assert(this!=nullptr);
      this->m_table = t;
    }
#include<GPUEngine/geGL/Generated/ContextDeclarations.h>
  protected:
    FunctionTablePointer m_table = nullptr;
};


