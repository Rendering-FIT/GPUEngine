#pragma once

#include<geGL/OpenGLObject.h>
#include<iostream>
#include<vector>
#include<set>
#include<memory>

namespace ge{
  namespace gl{
    class Program;
    class GEGL_EXPORT Shader:public OpenGLObject{
      friend class Program;
      public:
        using Source  = std::string;
        using Sources = std::vector<Source>;
        Shader();
        Shader(GLenum type,Sources const& sources = {});
        Shader(opengl::FunctionTablePointer const&table);
        Shader(
            opengl::FunctionTablePointer const&table       ,
            GLenum                       const&type        ,
            Sources                      const&sources = {});
        virtual ~Shader();
        void        create(GLenum type);
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
        template<typename...ARGS>
          Shader(GLenum type,ARGS...args);
        template<typename...ARGS>
          Shader(
              opengl::FunctionTablePointer const&table       ,
              GLenum                       const&type        ,
              ARGS...                            sources     );
        template<typename...ARGS>
          void        setSource(ARGS... sources);
        template<typename...ARGS>
          void        compile  (ARGS... sources);
      protected:
        GLint _getParam(GLenum pname)const;
        std::set<Program*>_programs;
    };

    template<typename...ARGS>
      Shader::Shader(GLenum type,ARGS...args):
        Shader(type,Sources({args...})){}
    template<typename...ARGS>
      Shader::Shader(
          opengl::FunctionTablePointer const&table  ,
          GLenum                       const&type   ,
          ARGS...                            sources):
        Shader(table,type,Sources({sources...})){}
    template<typename...ARGS>
      void Shader::setSource(ARGS... sources){
        this->setSource(Sources({sources...}));
      }
    template<typename...ARGS>
      void Shader::compile(ARGS... sources){
        this->compile(Sources({sources...}));
      }
  }
}

