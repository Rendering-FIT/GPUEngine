#pragma once

#include<iostream>
#include<memory>
#include<set>

#include<geGL/Shader.h>

namespace ge{
  namespace gl{
    class GEGL_EXPORT Program: public OpenGLObject{
      public:
        Program();
#if defined(REPLACE_GLEW)
        Program(opengl::FunctionTablePointer const&table);
#endif
        ~Program();
        GLboolean isProgram()const;
        void attachShader(std::shared_ptr<Shader>const&shader);
        void detachShader(std::shared_ptr<Shader>const&shader);
        void link()const;
        void use ()const;
        void validate()const;
        GLint getUniformLocation(const char*name)const;
        GLint getAttribLocation (const char*name)const;
      protected:
        std::set<std::shared_ptr<Shader>>_shaders;
    };
  }
}
