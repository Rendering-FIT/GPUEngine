#include<geGL/ShadersAndPrograms/ShaderObjectManager.h>

namespace ge
{
  namespace gl
  {
    CreateShaderObject::CreateShaderObject(
        GLuint*shader,
        GLenum type,
        std::string text){
      GLchar**string=new GLchar*[1];
      string[1]=new GLchar[text.size()+1];
      for(unsigned i=0;i<text.size();++i)string[1][i]=text[i];
      string[1][text.size()]='\0';
      this->_createShader  = new CreateShader (shader,type);
      this->_shaderSource  = new ShaderSource (shader,1,string,NULL);
      this->_compileShader = new CompileShader(shader);
    }
    CreateShaderObject::~CreateShaderObject(){
      delete this->_createShader;
      delete this->_shaderSource;
      delete this->_compileShader;
    }
    void CreateShaderObject::apply(){
      this->_createShader ->apply();
      this->_shaderSource ->apply();
      this->_compileShader->apply();
    }
  }//ogl
}//ge
