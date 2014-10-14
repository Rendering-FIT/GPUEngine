#include<geGL/ShaderObjectsCommands.h>

namespace ge
{
  namespace gl
  {
    CreateShader::CreateShader(
        GLuint *shader,
        GLenum type){
      this->shader = shader;
      this->type   = type;
    }
    void CreateShader::apply(){
      *this->shader = glCreateShader(this->type);
    }
    ShaderSource::ShaderSource(
        GLuint   *shader,
        GLsizei   count,
        GLchar  **string,
        GLint    *length){
      this->shader = shader;
      this->count  = count;
      this->string = string;
      this->length = length;
    }
    ShaderSource::~ShaderSource(){
      if(this->string){
        for(GLsizei i=0;i<this->count;++i)
          if(this->string[i]){
            delete[]this->string[i];
            this->string[i]=NULL;
          }
        delete[]this->string;
        this->string=NULL;
      }
    }
    void ShaderSource::apply(){
      glShaderSource(
          *this->shader,
          this->count,
          (const GLchar**)this->string,
          this->length);
    }
    CompileShader::CompileShader(
        GLuint *shader){
      this->shader = shader;
    }
    void CompileShader::apply(){
      glCompileShader(*this->shader);
    }
    ReleaseShaderCompiler::ReleaseShaderCompiler(){};
    void ReleaseShaderCompiler::apply(){
      glReleaseShaderCompiler();
    }
    DeleteShader::DeleteShader(GLuint *shader){
      this->shader = shader;
    }
    void DeleteShader::apply(){
      glDeleteShader(*this->shader);
    }
    IsShader::IsShader(GLboolean *is,GLuint *shader){
      this->is     = is;
      this->shader = shader;
    }
    void IsShader::apply(){
      *this->is = glIsShader(*this->shader);
    }
    ShaderBinary::ShaderBinary(
        GLsizei   count,
        GLuint  **shaders,
        GLenum    binaryFormat,
        GLvoid   *binary,
        GLsizei   length){
      this->count        = count;
      this->shaders      = shaders;
      this->binaryFormat = binaryFormat;
      this->binary       = binary;
      this->length       = length;
    }
    void ShaderBinary::apply(){
      glShaderBinary(
          this->count,
          *this->shaders,
          this->binaryFormat,
          this->binary,
          this->length);
    }
  }//ogl
}//ge

