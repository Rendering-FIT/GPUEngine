#pragma once

#include<geGL/OpenGLObject.h>
#include<iostream>

namespace ge{
  namespace gl{
    class GEGL_EXPORT Shader: public OpenGLObject{
      public:
        Shader();
        Shader(GLenum type,std::string source="");
#if defined(REPLACE_GLEW)
        Shader(std::shared_ptr<OpenGLFunctionTable>const&table);
        Shader(
            std::shared_ptr<OpenGLFunctionTable>const&table,
            GLenum type,
            std::string source="");
#endif
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
      protected:
        GLint _getParam(GLenum pname)const;
    };
  }
}

