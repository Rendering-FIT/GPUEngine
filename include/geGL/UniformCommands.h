#pragma once

#include<geCore/Command.h>
#include<geGL/Export.h>
#include<GL/glew.h>

#include<geCore/dtemplates.h>
#include <type_traits>

namespace ge{
  namespace gl{
    class GEGL_EXPORT UniformCommand: public ge::core::Command{
      protected:
        GLint _location;
      public:
        UniformCommand(GLint location);
    };

    class GEGL_EXPORT ProgramUniformCommand: public UniformCommand{
      protected:
        GLuint _program;
      public:
        ProgramUniformCommand(GLuint program,GLint location);
    };

    template<unsigned dim,typename T>
      class GEGL_EXPORT Uniform: public UniformCommand{
        protected:
          T _data[dim];
        public:
          template<class...T2, typename std::enable_if<sizeof...(T2) == dim, unsigned>::type = 0>
            Uniform(
                GLint location,
                T2... args):UniformCommand(location){
              this->set(args...);
            }
          virtual void operator()();
          template<class...T2, typename std::enable_if<sizeof...(T2) == dim, unsigned>::type = 0>
          void set(T2... args){
            ge::core::argsToArray<dim,T>(this->_data,args...);
          }
      };

    template<>void Uniform<1,GLfloat >::operator()();
    template<>void Uniform<2,GLfloat >::operator()();
    template<>void Uniform<3,GLfloat >::operator()();
    template<>void Uniform<4,GLfloat >::operator()();
    template<>void Uniform<1,GLint   >::operator()();
    template<>void Uniform<2,GLint   >::operator()();
    template<>void Uniform<3,GLint   >::operator()();
    template<>void Uniform<4,GLint   >::operator()();
    template<>void Uniform<1,GLuint  >::operator()();
    template<>void Uniform<2,GLuint  >::operator()();
    template<>void Uniform<3,GLuint  >::operator()();
    template<>void Uniform<4,GLuint  >::operator()();
    template<>void Uniform<1,GLdouble>::operator()();
    template<>void Uniform<2,GLdouble>::operator()();
    template<>void Uniform<3,GLdouble>::operator()();
    template<>void Uniform<4,GLdouble>::operator()();

    template<unsigned dim,typename T>
      class UniformV: public UniformCommand{
        protected:
          const T*_data;
          GLsizei _count;
        public:
          UniformV(
              GLint   location ,
              const T*data     ,
              GLsizei count = 1):UniformCommand(location){
            this->set(data,count);
          }
          virtual void operator()();
          void set(const T*data,GLsizei count=1){
            this->_data  = data ;
            this->_count = count;
          }
      };

    template<>void UniformV<1,GLfloat >::operator()();
    template<>void UniformV<2,GLfloat >::operator()();
    template<>void UniformV<3,GLfloat >::operator()();
    template<>void UniformV<4,GLfloat >::operator()();
    template<>void UniformV<1,GLint   >::operator()();
    template<>void UniformV<2,GLint   >::operator()();
    template<>void UniformV<3,GLint   >::operator()();
    template<>void UniformV<4,GLint   >::operator()();
    template<>void UniformV<1,GLuint  >::operator()();
    template<>void UniformV<2,GLuint  >::operator()();
    template<>void UniformV<3,GLuint  >::operator()();
    template<>void UniformV<4,GLuint  >::operator()();
    template<>void UniformV<1,GLdouble>::operator()();
    template<>void UniformV<2,GLdouble>::operator()();
    template<>void UniformV<3,GLdouble>::operator()();
    template<>void UniformV<4,GLdouble>::operator()();

    template<unsigned X,unsigned Y,typename T>
    class GEGL_EXPORT UniformMatrix: public UniformCommand{
      protected:
        const T*  _data;
        GLsizei   _count;
        GLboolean _transpose;
      public:
        UniformMatrix(
            GLint     location            ,
            const T*  data                ,
            GLsizei   count     = 1       ,
            GLboolean transpose = GL_FALSE):UniformCommand(location){
          this->set(data,count,transpose);
        }
        virtual void operator()();
        void set(const T*data,GLsizei count=1,GLboolean transpose=GL_FALSE){
          this->_data      = data     ;
          this->_count     = count    ;
          this->_transpose = transpose;
        }
    };

    template<>void UniformMatrix<2,2,GLfloat >::operator()();
    template<>void UniformMatrix<3,3,GLfloat >::operator()();
    template<>void UniformMatrix<4,4,GLfloat >::operator()();
    template<>void UniformMatrix<2,3,GLfloat >::operator()();
    template<>void UniformMatrix<3,2,GLfloat >::operator()();
    template<>void UniformMatrix<2,4,GLfloat >::operator()();
    template<>void UniformMatrix<4,2,GLfloat >::operator()();
    template<>void UniformMatrix<3,4,GLfloat >::operator()();
    template<>void UniformMatrix<4,3,GLfloat >::operator()();
    template<>void UniformMatrix<2,2,GLdouble>::operator()();
    template<>void UniformMatrix<3,3,GLdouble>::operator()();
    template<>void UniformMatrix<4,4,GLdouble>::operator()();
    template<>void UniformMatrix<2,3,GLdouble>::operator()();
    template<>void UniformMatrix<3,2,GLdouble>::operator()();
    template<>void UniformMatrix<2,4,GLdouble>::operator()();
    template<>void UniformMatrix<4,2,GLdouble>::operator()();
    template<>void UniformMatrix<3,4,GLdouble>::operator()();
    template<>void UniformMatrix<4,3,GLdouble>::operator()();


    template<unsigned X,unsigned Y,typename T>
    class GEGL_EXPORT ProgramUniformMatrix: public ProgramUniformCommand{
      protected:
        const T*  _data;
        GLsizei   _count;
        GLboolean _transpose;
      public:
        ProgramUniformMatrix(
            GLuint    program             ,
            GLint     location            ,
            const T*  data                ,
            GLsizei   count     = 1       ,
            GLboolean transpose = GL_FALSE):ProgramUniformCommand(location){
          this->set(data,count,transpose);
        }
        virtual void operator()();
        void set(const T*data,GLsizei count=1,GLboolean transpose=GL_FALSE){
          this->_data      = data     ;
          this->_count     = count    ;
          this->_transpose = transpose;
        }
    };

    template<>void ProgramUniformMatrix<2,2,GLfloat >::operator()();
    template<>void ProgramUniformMatrix<3,3,GLfloat >::operator()();
    template<>void ProgramUniformMatrix<4,4,GLfloat >::operator()();
    template<>void ProgramUniformMatrix<2,3,GLfloat >::operator()();
    template<>void ProgramUniformMatrix<3,2,GLfloat >::operator()();
    template<>void ProgramUniformMatrix<2,4,GLfloat >::operator()();
    template<>void ProgramUniformMatrix<4,2,GLfloat >::operator()();
    template<>void ProgramUniformMatrix<3,4,GLfloat >::operator()();
    template<>void ProgramUniformMatrix<4,3,GLfloat >::operator()();
    template<>void ProgramUniformMatrix<2,2,GLdouble>::operator()();
    template<>void ProgramUniformMatrix<3,3,GLdouble>::operator()();
    template<>void ProgramUniformMatrix<4,4,GLdouble>::operator()();
    template<>void ProgramUniformMatrix<2,3,GLdouble>::operator()();
    template<>void ProgramUniformMatrix<3,2,GLdouble>::operator()();
    template<>void ProgramUniformMatrix<2,4,GLdouble>::operator()();
    template<>void ProgramUniformMatrix<4,2,GLdouble>::operator()();
    template<>void ProgramUniformMatrix<3,4,GLdouble>::operator()();
    template<>void ProgramUniformMatrix<4,3,GLdouble>::operator()();

    template<unsigned dim,typename T>
      class GEGL_EXPORT ProgramUniform: public ProgramUniformCommand{
        protected:
          T _data[dim];
        public:
          template<class...T2, typename std::enable_if<sizeof...(T2) == dim, unsigned>::type = 0>
            ProgramUniform(
                GLuint program,
                GLint location,
                T2... args):ProgramUniformCommand(program,location){
              this->set(args...);
            }
          virtual void operator()();
          template<class...T2, typename std::enable_if<sizeof...(T2) == dim, unsigned>::type = 0>
            void set(T2... args){
              ge::core::argsToArray<dim,T>(this->_data,args...);
            }

      };

    template<>void ProgramUniform<1,GLfloat >::operator()();
    template<>void ProgramUniform<2,GLfloat >::operator()();
    template<>void ProgramUniform<3,GLfloat >::operator()();
    template<>void ProgramUniform<4,GLfloat >::operator()();
    template<>void ProgramUniform<1,GLint   >::operator()();
    template<>void ProgramUniform<2,GLint   >::operator()();
    template<>void ProgramUniform<3,GLint   >::operator()();
    template<>void ProgramUniform<4,GLint   >::operator()();
    template<>void ProgramUniform<1,GLuint  >::operator()();
    template<>void ProgramUniform<2,GLuint  >::operator()();
    template<>void ProgramUniform<3,GLuint  >::operator()();
    template<>void ProgramUniform<4,GLuint  >::operator()();
    template<>void ProgramUniform<1,GLdouble>::operator()();
    template<>void ProgramUniform<2,GLdouble>::operator()();
    template<>void ProgramUniform<3,GLdouble>::operator()();
    template<>void ProgramUniform<4,GLdouble>::operator()();
  }
}
