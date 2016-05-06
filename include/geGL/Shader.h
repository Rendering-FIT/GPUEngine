#pragma once

#include<geGL/OpenGLObject.h>
#include<iostream>
#include<vector>

namespace ge{
  namespace gl{
    class GEGL_EXPORT Shader: public OpenGLObject{
      public:
        using Source  = std::string;
        using Sources = std::vector<Source>;
        Shader();
        Shader(GLenum type,Sources const& sources = {});
#if defined(REPLACE_GLEW)
        Shader(opengl::FunctionTablePointer const&table);
        Shader(
            opengl::FunctionTablePointer const&table,
            GLenum type,
            Sources const& sources = {});
#endif
        virtual ~Shader();
        void        create(GLenum type,Sources const& sources = {});
        void        setSource(Sources const& sources = {});
        void        compile  (Sources const& sources = {});
        GLboolean   isShader        ()const;
        GLenum      getType         ()const;
        GLboolean   getDeleteStatus ()const;
        GLboolean   getCompileStatus()const;
        GLuint      getInfoLogLength()const;
        GLuint      getSourceLength ()const;
        std::string getInfoLog      ()const;
        Source      getSource       ()const;
      protected:
        GLint _getParam(GLenum pname)const;
    };
  }
}

