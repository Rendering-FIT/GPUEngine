#ifndef _SHADEROBJECTSCOMMANDS_H_
#define _SHADEROBJECTSCOMMANDS_H_

#include <geGL/OpenGL.h>

namespace ge
{
  namespace gl
  {
    class GEGL_EXPORT CreateShader: public Command
    {
      public:
        GLenum  type;
        GLuint *shader;
        CreateShader(GLuint*shader,GLenum type);
        void apply();
    };
    class GEGL_EXPORT ShaderSource: public Command
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
    class GEGL_EXPORT CompileShader: public Command
    {
      public:
        GLuint *shader;
        CompileShader(
            GLuint *shader);
        void apply();
    };
    class GEGL_EXPORT ReleaseShaderCompiler: public Command
    {
      public:
        ReleaseShaderCompiler();
        void apply();
    };
    class GEGL_EXPORT DeleteShader: public Command
    {
      public:
        GLuint *shader;
        DeleteShader(GLuint *shader);
        void apply();
    };
    class GEGL_EXPORT IsShader: public Command
    {
      public:
        GLuint    *shader;
        GLboolean *is;
        IsShader(GLboolean *is,GLuint *shader);
        void apply();
    };
    class GEGL_EXPORT ShaderBinary: public Command
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
