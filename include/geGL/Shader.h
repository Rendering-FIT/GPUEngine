#pragma once

#include<geGL/OpenGL.h>
#include<geGL/OpenGLObject.h>
#include<iostream>

namespace ge{
  namespace gl{
    class GEGL_EXPORT Shader: public OpenGLObject{
      protected:
        GLint _getParam(GLenum pname)const;
      public:
        Shader();
        Shader(GLenum type,std::string source="");
        virtual ~Shader();
        void        create(GLenum type,std::string source="");
        void        setSource(std::string source   );
        void        compile  (std::string source="");
        GLboolean   isShader        ()const;
        GLenum      getType         ()const;
        GLboolean   getDeleteStatus ()const;
        GLboolean   getCompileStatus()const;
        GLuint      getInfoLogLength()const;
        GLuint      getSourceLength ()const;
        std::string getInfoLog      ()const;
        std::string getSource       ()const;
    };
  }
}

