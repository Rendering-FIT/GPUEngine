#pragma once

#include<geGL/OpenGL.h>
#include<cassert>

class ge::gl::Context{
  public:
    GEGL_EXPORT Context(FunctionTablePointer const&t = nullptr);
	  GEGL_EXPORT ~Context(){}
    FunctionTablePointer const&getFunctionTable()const{
      assert(this!=nullptr);
      return this->m_table;
    }
    void setFunctionTable(FunctionTablePointer const&t){
      assert(this!=nullptr);
      this->m_table = t;
    }
#include<geGL/Generated/ContextDeclarations.h>
  private:
    FunctionTablePointer m_table = nullptr;
};


