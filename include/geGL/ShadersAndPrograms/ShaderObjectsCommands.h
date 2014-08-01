#ifndef _SHADEROBJECTSCOMMANDS_H_
#define _SHADEROBJECTSCOMMANDS_H_

#include <geGL/Standard/OpenGL.h>

namespace ge
{
  namespace gl
  {
    class GE_EXPORT CreateShader: public Command
    {
      public:
        GLenum  type;
        GLuint *shader;
        CreateShader(GLuint*shader,GLenum type);
        void apply();
    };
    class GE_EXPORT ShaderSource: public Command
    {
      public:
        GLuint   *shader;
        GLsizei   count;
        GLchar  **string;
        GLint    *length;
        ShaderSource(
            GLuint   *shader,
            GLsizei   count,
            GLchar  **string,
            GLint    *length);
        ~ShaderSource();
        void apply();
    };
    class GE_EXPORT CompileShader: public Command
    {
      public:
        GLuint *shader;
        CompileShader(
            GLuint *shader);
        void apply();
    };
    class GE_EXPORT ReleaseShaderCompiler: public Command
    {
      public:
        ReleaseShaderCompiler();
        void apply();
    };
    class GE_EXPORT DeleteShader: public Command
    {
      public:
        GLuint *shader;
        DeleteShader(GLuint *shader);
        void apply();
    };
    class GE_EXPORT IsShader: public Command
    {
      public:
        GLuint    *shader;
        GLboolean *is;
        IsShader(GLboolean *is,GLuint *shader);
        void apply();
    };
    class GE_EXPORT ShaderBinary: public Command
    {
      public:
        GLsizei   count;
        GLuint  **shaders;
        GLenum    binaryFormat;
        GLvoid   *binary;
        GLsizei   length;
        ShaderBinary(
            GLsizei   count,
            GLuint  **shaders,
            GLenum    binaryFormat,
            GLvoid   *binary,
            GLsizei   length);
        void apply();
    };
  }//ogl
}//ge

#endif//_SHADEROBJECTSCOMMANDS_H_
