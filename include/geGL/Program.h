#pragma once

#include<iostream>
#include<memory>
#include<set>

#include<geGL/Shader.h>

namespace ge{
  namespace gl{
    class GEGL_EXPORT Program: public OpenGLObject,public std::enable_shared_from_this<Program>{
      friend class Shader;
      public:
        using ShaderPointer  = std::shared_ptr<Shader>;
        using ShaderPointers = std::vector<ShaderPointer>;
        Program(ShaderPointers const&shaders = {});
        Program(
            opengl::FunctionTablePointer const&table       ,
            ShaderPointers               const&shaders = {});
        ~Program();
        void create       ();
        void attachShaders(ShaderPointers const&shaders = {});
        void detachShaders(ShaderPointers const&shaders = {});
        void link         (ShaderPointers const&shaders = {});
        GLboolean isProgram()const;
        void use ()const;
        void validate()const;
        GLint getUniformLocation(std::string const&name)const;
        GLint getAttribLocation (std::string const&name)const;

        template<typename...ARGS>
          Program(ARGS...shaders);
        template<typename...ARGS>
          Program(
              opengl::FunctionTablePointer const&table  ,
              ARGS...                            shaders);
        template<typename...ARGS>
          void attachShaders(ARGS... shaders);
        template<typename...ARGS>
          void detachShaders(ARGS... shaders);
        template<typename...ARGS>
          void link         (ARGS... shaders);
      protected:
        std::set<ShaderPointer>_shaders;
    };

    template<typename...ARGS>
      Program::Program(ARGS...shaders):Program(ShaderPointers({shaders...})){}
    template<typename...ARGS>
      Program::Program(
          opengl::FunctionTablePointer const&table  ,
          ARGS...                            shaders):Program(table,ShaderPointers({shaders...})){}
    template<typename...ARGS>
      void Program::attachShaders(ARGS... shaders){
        this->attachShaders(ShaderPointers({shaders...}));
      }
    template<typename...ARGS>
      void Program::detachShaders(ARGS... shaders){
        this->detachShaders(ShaderPointers({shaders...}));
      }
    template<typename...ARGS>
      void Program::link(ARGS... shaders){
        this->link(ShaderPointers({shaders...}));
      }

  }
}
