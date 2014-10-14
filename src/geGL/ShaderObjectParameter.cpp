#include<geGL/ShaderObjectParameter.h>

namespace ge{
  namespace gl{
    ShaderObjectParameter::ShaderObjectParameter(
        GLint       location,
        GLenum      type,
        std::string name,
        GLint       size){
      this->location = location;//parameter id
      this->type     = type;//parameter type
      this->name     = name;//parameter name
      this->size     = size;//parameter size
    }
  }
}

