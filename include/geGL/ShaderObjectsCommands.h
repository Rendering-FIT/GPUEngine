#pragma once

#include<geCore/Command.h>
#include<geGL/Export.h>
#include<GL/glew.h>
#include<memory>

namespace ge{
  namespace gl{
    class GEGL_EXPORT SharedShader{
      protected:
        std::shared_ptr<GLuint>_shader;
      public:
        SharedShader(std::shared_ptr<GLuint>shader);
        std::shared_ptr<GLuint>getShader();
    };

    class GEGL_EXPORT CreateShader: public ge::core::Command, public SharedShader{
      private:
        std::shared_ptr<GLenum>_type;
      public:
        CreateShader(std::shared_ptr<GLuint>shader,std::shared_ptr<GLenum>type);
        void operator()();
        std::shared_ptr<GLenum>getType();
    };

    class ShaderSourceData{
      protected:
        GLsizei             _count ;
        const GLchar*const* _string;
        const GLint*        _length;
      public:
        ShaderSourceData(
            GLsizei             count  = 0   ,
            const GLchar*const* string = NULL,
            const GLint*        length = 0   );
        void set(
            GLsizei             count  = 0   ,
            const GLchar*const* string = NULL,
            const GLint*        length = 0   );
        GLsizei getCount();
        const GLchar*const*getString();
        const GLint*getLength();
    };

    class GEGL_EXPORT ShaderSource: public ge::core::Command, public SharedShader{
      protected:
        std::shared_ptr<ShaderSourceData>_data  ;
      public:
        ShaderSource(
            std::shared_ptr<GLuint>shader        ,
            std::shared_ptr<ShaderSourceData>data);
        void operator()();
        std::shared_ptr<ShaderSourceData>getData();
    };

    class GEGL_EXPORT CompileShader: public ge::core::Command, public SharedShader{
      public:
        CompileShader(std::shared_ptr<GLuint>shader);
        void operator()();
    };

    class GEGL_EXPORT ReleaseShaderCompiler: public ge::core::Command{
      public:
        ReleaseShaderCompiler();
        void operator()();
    };

    class GEGL_EXPORT DeleteShader: public ge::core::Command, public SharedShader{
      public:
        DeleteShader(std::shared_ptr<GLuint>shader);
        void operator()();
    };

    class GEGL_EXPORT IsShader: public ge::core::Command, public SharedShader{
      protected:
        std::shared_ptr<GLboolean>_is;
      public:
        IsShader(std::shared_ptr<GLboolean>is,std::shared_ptr<GLuint>shader);
        void operator()();
        std::shared_ptr<GLboolean>getIs();
    };

    class ShaderBinaryData{
      private:
        GLenum       _format;
        const GLvoid*_binary;
        GLsizei      _length;
      public:
        ShaderBinaryData(
            GLenum       format = 0   ,
            const GLvoid*binary = NULL,
            GLsizei      length = 0   );
        void set(
            GLenum       format = 0   ,
            const GLvoid*binary = NULL,
            GLsizei      length = 0   );
        GLenum getFormat();
        const GLvoid*getBinary();
        GLsizei getLength();
    };

    class GEGL_EXPORT ShaderBinary: public ge::core::Command{
      protected:
        std::shared_ptr<GLsizei>         _count  ;
        std::shared_ptr<GLuint>          _shaders;
        std::shared_ptr<ShaderBinaryData>_binary ;
      public:
        ShaderBinary(
            std::shared_ptr<GLsizei>         count  ,
            std::shared_ptr<GLuint>          shaders,
            std::shared_ptr<ShaderBinaryData>binary );
        void operator()();
        std::shared_ptr<GLsizei>         getCount  ();
        std::shared_ptr<GLuint>          getShaders();
        std::shared_ptr<ShaderBinaryData>getBinary ();
    };
  }//ogl
}//ge

