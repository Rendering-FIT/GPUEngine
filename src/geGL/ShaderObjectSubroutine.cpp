#include<geGL/ShaderObjectSubroutine.h>
namespace ge{
  namespace gl{
    ShaderObjectSubroutine::~ShaderObjectSubroutine(){
      if(this->Indices)
        delete[]this->Indices;
    }
    ShaderObjectSubroutine::ShaderObjectSubroutine(){
      this->Indices=NULL;
    }
  }
}

