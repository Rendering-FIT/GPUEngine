#pragma once

#include<geGL/OpenGL.h>
#include<geGL/ProgramObject.h>
#include<geCore/dtemplates.h>
#include <type_traits>

namespace ge{
  namespace gl{
    class GEGL_EXPORT UniformCommand: public Command{
      protected:
        GLint _location;
      public:
        UniformCommand(GLint location);
        UniformCommand(ge::gl::ProgramObject*program,std::string name);
    };

    class GEGL_EXPORT ProgramUniformCommand: public UniformCommand{
      protected:
        GLuint _program;
      public:
        ProgramUniformCommand(GLuint program,GLint location);
        ProgramUniformCommand(ge::gl::ProgramObject*program,std::string name);
    };

    class GEGL_EXPORT UniformDataProvider{
      public:
        DEF_ENUM(Type,F1,F2,F3,F4,I1,I2,I3,I4,U1,U2,U3,U4,D1,D2,D3,D4,
            F1V,F2V,F3V,F4V,I1V,I2V,I3V,I4V,U1V,U2V,U3V,U4V,D1V,D2V,D3V,D4V);
        Type type;
    };
    
    template<unsigned dim,typename T>
      inline UniformDataProvider::Type _getType(){
        if( typeid(T) == typeid(float  ) ||
            typeid(T) == typeid(GLfloat)){
          return (UniformDataProvider::Type)(UniformDataProvider::F1+dim-1);
        }
        if( typeid(T) == typeid(int  ) ||
            typeid(T) == typeid(GLint)){
          return (UniformDataProvider::Type)(UniformDataProvider::I1+dim-1);
        }
        if( typeid(T) == typeid(unsigned) ||
            typeid(T) == typeid(GLuint  )){
          return (UniformDataProvider::Type)(UniformDataProvider::U1+dim-1);
        }
        if( typeid(T) == typeid(double  ) ||
            typeid(T) == typeid(GLdouble)){
          return (UniformDataProvider::Type)(UniformDataProvider::D1+dim-1);
        }
      }
    template<unsigned dim,typename T>
      class GEGL_EXPORT UniformData: public UniformDataProvider{
        public:
          T data[dim];
          template<typename...T2, typename std::enable_if<sizeof...(T2) == dim, unsigned>::type = 0>
            UniformData(T2... args){
              this->type = _getType<dim,T>();
              ge::core::argsToArray<dim,T>(this->data,args...);
            }
          UniformData(){
            this->type = _getType<dim,T>();
          }
      };

    template<unsigned dim,typename T>
      class GEGL_EXPORT UniformDataRef: public UniformDataProvider{
        public:
          T*data[dim];
          template<typename...T2, typename std::enable_if<sizeof...(T2) == dim, unsigned>::type = 0>
            UniformDataRef(T2*... args){
              this->type = _getType<dim,T>();
              ge::core::argsToArray<dim,T*>(this->data,args...);
            }
          UniformDataRef(){
            this->type = _getType<dim,T>();
            for(unsigned d=0;d<dim;++d)
              this->data[d]=NULL;
          }
      };
    /*
       template<unsigned dim,typename T>
       class GEGL_EXPORT UniformRef: public UniformCommand{
       public:
       UniformDataRef<dim,T>*ref;
       public:
       UniformRef(
       ge::gl::ProgramObject*program,
       std::string name,
       UniformDataRef<dim,T>*ref):UniformCommand(program,name){
       this->ref=ref;
       }
       UniformRef(
       GLint location,
       UniformDataRef<dim,T>*ref):UniformCommand(location){
       this->ref=ref;
       }
       void apply(){
       if( typeid(T) == typeid(float  ) ||
       typeid(T) == typeid(GLfloat)){
       if(dim==1)glUniform1f(this->_location,this->ref->data[0]);
       if(dim==2)glUniform2f(this->_location,this->ref->data[0],this->ref->data[1]);
       if(dim==3)glUniform3f(this->_location,this->ref->data[0],this->ref->data[1],this->ref->data[2]);
       if(dim==4)glUniform4f(this->_location,this->ref->data[0],this->ref->data[1],this->ref->data[2],this->ref->data[3]);
       }
       if( typeid(T) == typeid(int  ) ||
       typeid(T) == typeid(GLint)){
       if(dim==1)glUniform1i(this->_location,this->ref->data[0]);
       if(dim==2)glUniform2i(this->_location,this->ref->data[0],this->ref->data[1]);
       if(dim==3)glUniform3i(this->_location,this->ref->data[0],this->ref->data[1],this->ref->data[2]);
       if(dim==4)glUniform4i(this->_location,this->ref->data[0],this->ref->data[1],this->ref->data[2],this->ref->data[3]);
       }
       if( typeid(T) == typeid(unsigned) ||
       typeid(T) == typeid(GLuint  )){
       if(dim==1)glUniform1ui(this->_location,this->ref->data[0]);
       if(dim==2)glUniform2ui(this->_location,this->ref->data[0],this->ref->data[1]);
       if(dim==3)glUniform3ui(this->_location,this->ref->data[0],this->ref->data[1],this->ref->data[2]);
       if(dim==4)glUniform4ui(this->_location,this->ref->data[0],this->ref->data[1],this->ref->data[2],this->ref->data[3]);
       }
       if( typeid(T) == typeid(double  ) ||
       typeid(T) == typeid(GLdouble)){
       if(dim==1)glUniform1d(this->_location,this->ref->data[0]);
       if(dim==2)glUniform2d(this->_location,this->ref->data[0],this->ref->data[1]);
       if(dim==3)glUniform3d(this->_location,this->ref->data[0],this->ref->data[1],this->ref->data[2]);
       if(dim==4)glUniform4d(this->_location,this->ref->data[0],this->ref->data[1],this->ref->data[2],this->ref->data[3]);
       }
       }
       };
       */

#define UNIFORM_ARGS1 this->_data[0]
#define UNIFORM_ARGS2 this->_data[0],this->_data[1]
#define UNIFORM_ARGS3 this->_data[0],this->_data[1],this->_data[2]
#define UNIFORM_ARGS4 this->_data[0],this->_data[1],this->_data[2],this->_data[3]

    template<unsigned dim,typename T>
      class GEGL_EXPORT Uniform: public UniformCommand{
        protected:
          T _data[dim];
        public:
          template<class...T2, typename std::enable_if<sizeof...(T2) == dim, unsigned>::type = 0>
            Uniform(
                ge::gl::ProgramObject*program,
                std::string name,
                T2... args):UniformCommand(program,name){
              this->set(args...);
            }
          template<class...T2, typename std::enable_if<sizeof...(T2) == dim, unsigned>::type = 0>
            Uniform(
                GLint location,
                T2... args):UniformCommand(location){
              this->set(args...);
            }
          void apply(){
            if( typeid(T) == typeid(float  ) ||
                typeid(T) == typeid(GLfloat)){
              if(dim==1)glUniform1f(this->_location,UNIFORM_ARGS1);
              if(dim==2)glUniform2f(this->_location,UNIFORM_ARGS2);
              if(dim==3)glUniform3f(this->_location,UNIFORM_ARGS3);
              if(dim==4)glUniform4f(this->_location,UNIFORM_ARGS4);
            }
            if( typeid(T) == typeid(int  ) ||
                typeid(T) == typeid(GLint)){
              if(dim==1)glUniform1i(this->_location,UNIFORM_ARGS1);
              if(dim==2)glUniform2i(this->_location,UNIFORM_ARGS2);
              if(dim==3)glUniform3i(this->_location,UNIFORM_ARGS3);
              if(dim==4)glUniform4i(this->_location,UNIFORM_ARGS4);
            }
            if( typeid(T) == typeid(unsigned) ||
                typeid(T) == typeid(GLuint  )){
              if(dim==1)glUniform1ui(this->_location,UNIFORM_ARGS1);
              if(dim==2)glUniform2ui(this->_location,UNIFORM_ARGS2);
              if(dim==3)glUniform3ui(this->_location,UNIFORM_ARGS3);
              if(dim==4)glUniform4ui(this->_location,UNIFORM_ARGS4);
            }
            if( typeid(T) == typeid(double  ) ||
                typeid(T) == typeid(GLdouble)){
              if(dim==1)glUniform1d(this->_location,UNIFORM_ARGS1);
              if(dim==2)glUniform2d(this->_location,UNIFORM_ARGS2);
              if(dim==3)glUniform3d(this->_location,UNIFORM_ARGS3);
              if(dim==4)glUniform4d(this->_location,UNIFORM_ARGS4);
            }
          }
          template<class...T2, typename std::enable_if<sizeof...(T2) == dim, unsigned>::type = 0>
          void set(T2... args){
            ge::core::argsToArray<dim,T>(this->_data,args...);
          }
      };
    template<unsigned dim,typename T>
      class GEGL_EXPORT UniformV: public UniformCommand{
        protected:
          const T*_data;
          GLsizei _count;
        public:
          UniformV(
              ge::gl::ProgramObject*program  ,
              std::string           name     ,
              const T*              data     ,
              GLsizei               count = 1):UniformCommand(program,name){
            this->set(data,count);
          }
          UniformV(
              GLint   location ,
              const T*data     ,
              GLsizei count = 1):UniformCommand(location){
            this->set(data,count);
          }
          void apply(){
            if( typeid(T) == typeid(float  ) ||
                typeid(T) == typeid(GLfloat)){
              if(dim==1)glUniform1fv(this->_location,this->_count,(const GLfloat*)this->_data);
              if(dim==2)glUniform2fv(this->_location,this->_count,(const GLfloat*)this->_data);
              if(dim==3)glUniform3fv(this->_location,this->_count,(const GLfloat*)this->_data);
              if(dim==4)glUniform4fv(this->_location,this->_count,(const GLfloat*)this->_data);
            }
            if( typeid(T) == typeid(int  ) ||
                typeid(T) == typeid(GLint)){
              if(dim==1)glUniform1iv(this->_location,this->_count,(const GLint*)this->_data);
              if(dim==2)glUniform2iv(this->_location,this->_count,(const GLint*)this->_data);
              if(dim==3)glUniform3iv(this->_location,this->_count,(const GLint*)this->_data);
              if(dim==4)glUniform4iv(this->_location,this->_count,(const GLint*)this->_data);
            }
            if( typeid(T) == typeid(unsigned) ||
                typeid(T) == typeid(GLuint  )){
              if(dim==1)glUniform1uiv(this->_location,this->_count,(const GLuint*)this->_data);
              if(dim==2)glUniform2uiv(this->_location,this->_count,(const GLuint*)this->_data);
              if(dim==3)glUniform3uiv(this->_location,this->_count,(const GLuint*)this->_data);
              if(dim==4)glUniform4uiv(this->_location,this->_count,(const GLuint*)this->_data);
            }
            if( typeid(T) == typeid(double  ) ||
                typeid(T) == typeid(GLdouble)){
              if(dim==1)glUniform1dv(this->_location,this->_count,(const GLdouble*)this->_data);
              if(dim==2)glUniform2dv(this->_location,this->_count,(const GLdouble*)this->_data);
              if(dim==3)glUniform3dv(this->_location,this->_count,(const GLdouble*)this->_data);
              if(dim==4)glUniform4dv(this->_location,this->_count,(const GLdouble*)this->_data);
            }
          }
          void set(const T*data,GLsizei count=1){
            this->_data  = data ;
            this->_count = count;
          }
      };

#define UNIFORM_MATRIX_ARGS(T)this->_location,this->_count,this->_transpose,(const T*)this->_data

    template<unsigned X,unsigned Y,typename T>
    class GEGL_EXPORT UniformMatrix: public UniformCommand{
      protected:
        const T*  _data;
        GLsizei   _count;
        GLboolean _transpose;
      public:
        UniformMatrix(
            ge::gl::ProgramObject*program             ,
            std::string           name                ,
            const T*              data                ,
            GLsizei               count     = 1       ,
            GLboolean             transpose = GL_FALSE):UniformCommand(program,name){
          this->set(data,count,transpose);
        }
        UniformMatrix(
            GLint     location            ,
            const T*  data                ,
            GLsizei   count     = 1       ,
            GLboolean transpose = GL_FALSE):UniformCommand(location){
          this->set(data,count,transpose);
        }
        void apply(){
          if (typeid(T) == typeid(float  ) ||
              typeid(T) == typeid(GLfloat)){
            if(X==2&&Y==2)glUniformMatrix2fv  (UNIFORM_MATRIX_ARGS(GLfloat));
            if(X==3&&Y==3)glUniformMatrix3fv  (UNIFORM_MATRIX_ARGS(GLfloat));
            if(X==4&&Y==4)glUniformMatrix4fv  (UNIFORM_MATRIX_ARGS(GLfloat));
            if(X==2&&Y==3)glUniformMatrix2x3fv(UNIFORM_MATRIX_ARGS(GLfloat));
            if(X==3&&Y==2)glUniformMatrix3x2fv(UNIFORM_MATRIX_ARGS(GLfloat));
            if(X==2&&Y==4)glUniformMatrix2x4fv(UNIFORM_MATRIX_ARGS(GLfloat));
            if(X==4&&Y==2)glUniformMatrix4x2fv(UNIFORM_MATRIX_ARGS(GLfloat));
            if(X==3&&Y==4)glUniformMatrix3x4fv(UNIFORM_MATRIX_ARGS(GLfloat));
            if(X==4&&Y==3)glUniformMatrix4x3fv(UNIFORM_MATRIX_ARGS(GLfloat));
          }
          if (typeid(T) == typeid(double  ) ||
              typeid(T) == typeid(GLdouble)){
            if(X==2&&Y==2)glUniformMatrix2dv  (UNIFORM_MATRIX_ARGS(GLdouble));
            if(X==3&&Y==3)glUniformMatrix3dv  (UNIFORM_MATRIX_ARGS(GLdouble));
            if(X==4&&Y==4)glUniformMatrix4dv  (UNIFORM_MATRIX_ARGS(GLdouble));
            if(X==2&&Y==3)glUniformMatrix2x3dv(UNIFORM_MATRIX_ARGS(GLdouble));
            if(X==3&&Y==2)glUniformMatrix3x2dv(UNIFORM_MATRIX_ARGS(GLdouble));
            if(X==2&&Y==4)glUniformMatrix2x4dv(UNIFORM_MATRIX_ARGS(GLdouble));
            if(X==4&&Y==2)glUniformMatrix4x2dv(UNIFORM_MATRIX_ARGS(GLdouble));
            if(X==3&&Y==4)glUniformMatrix3x4dv(UNIFORM_MATRIX_ARGS(GLdouble));
            if(X==4&&Y==3)glUniformMatrix4x3dv(UNIFORM_MATRIX_ARGS(GLdouble));
          }
        }
        void set(const T*data,GLsizei count=1,GLboolean transpose=GL_FALSE){
          this->_data      = data     ;
          this->_count     = count    ;
          this->_transpose = transpose;
        }
    };

#define PROGRAM_UNIFORM_MATRIX_ARGS(T)this->_program,UNIFORM_MATRIX_ARGS(T)

    template<unsigned X,unsigned Y,typename T>
    class GEGL_EXPORT ProgramUniformMatrix: public ProgramUniformCommand{
      protected:
        const T*  _data;
        GLsizei   _count;
        GLboolean _transpose;
      public:
        ProgramUniformMatrix(
            ge::gl::ProgramObject*program             ,
            std::string           name                ,
            const T*              data                ,
            GLsizei               count     = 1       ,
            GLboolean             transpose = GL_FALSE):ProgramUniformCommand(program,name){
          this->set(data,count,transpose);
        }
        ProgramUniformMatrix(
            GLuint    program             ,
            GLint     location            ,
            const T*  data                ,
            GLsizei   count     = 1       ,
            GLboolean transpose = GL_FALSE):ProgramUniformCommand(location){
          this->set(data,count,transpose);
        }
        void apply(){
          if (typeid(T) == typeid(float  ) ||
              typeid(T) == typeid(GLfloat)){
            if(X==2&&Y==2)glProgramUniformMatrix2fv  (PROGRAM_UNIFORM_MATRIX_ARGS(GLfloat));
            if(X==3&&Y==3)glProgramUniformMatrix3fv  (PROGRAM_UNIFORM_MATRIX_ARGS(GLfloat));
            if(X==4&&Y==4)glProgramUniformMatrix4fv  (PROGRAM_UNIFORM_MATRIX_ARGS(GLfloat));
            if(X==2&&Y==3)glProgramUniformMatrix2x3fv(PROGRAM_UNIFORM_MATRIX_ARGS(GLfloat));
            if(X==3&&Y==2)glProgramUniformMatrix3x2fv(PROGRAM_UNIFORM_MATRIX_ARGS(GLfloat));
            if(X==2&&Y==4)glProgramUniformMatrix2x4fv(PROGRAM_UNIFORM_MATRIX_ARGS(GLfloat));
            if(X==4&&Y==2)glProgramUniformMatrix4x2fv(PROGRAM_UNIFORM_MATRIX_ARGS(GLfloat));
            if(X==3&&Y==4)glProgramUniformMatrix3x4fv(PROGRAM_UNIFORM_MATRIX_ARGS(GLfloat));
            if(X==4&&Y==3)glProgramUniformMatrix4x3fv(PROGRAM_UNIFORM_MATRIX_ARGS(GLfloat));
          }
          if (typeid(T) == typeid(double  ) ||
              typeid(T) == typeid(GLdouble)){
            if(X==2&&Y==2)glProgramUniformMatrix2dv  (PROGRAM_UNIFORM_MATRIX_ARGS(GLdouble));
            if(X==3&&Y==3)glProgramUniformMatrix3dv  (PROGRAM_UNIFORM_MATRIX_ARGS(GLdouble));
            if(X==4&&Y==4)glProgramUniformMatrix4dv  (PROGRAM_UNIFORM_MATRIX_ARGS(GLdouble));
            if(X==2&&Y==3)glProgramUniformMatrix2x3dv(PROGRAM_UNIFORM_MATRIX_ARGS(GLdouble));
            if(X==3&&Y==2)glProgramUniformMatrix3x2dv(PROGRAM_UNIFORM_MATRIX_ARGS(GLdouble));
            if(X==2&&Y==4)glProgramUniformMatrix2x4dv(PROGRAM_UNIFORM_MATRIX_ARGS(GLdouble));
            if(X==4&&Y==2)glProgramUniformMatrix4x2dv(PROGRAM_UNIFORM_MATRIX_ARGS(GLdouble));
            if(X==3&&Y==4)glProgramUniformMatrix3x4dv(PROGRAM_UNIFORM_MATRIX_ARGS(GLdouble));
            if(X==4&&Y==3)glProgramUniformMatrix4x3dv(PROGRAM_UNIFORM_MATRIX_ARGS(GLdouble));
          }
        }
        void set(const T*data,GLsizei count=1,GLboolean transpose=GL_FALSE){
          this->_data      = data     ;
          this->_count     = count    ;
          this->_transpose = transpose;
        }
    };

    template<unsigned dim,typename T>
      class GEGL_EXPORT ProgramUniform: public ProgramUniformCommand{
        protected:
          T _data[dim];
        public:
          template<class...T2, typename std::enable_if<sizeof...(T2) == dim, unsigned>::type = 0>
            ProgramUniform(
                ge::gl::ProgramObject*program,
                std::string name,
                T2... args):ProgramUniformCommand(program,name){
              this->set(args...);
            }
          template<class...T2, typename std::enable_if<sizeof...(T2) == dim, unsigned>::type = 0>
            ProgramUniform(
                GLuint program,
                GLint location,
                T2... args):ProgramUniformCommand(program,location){
              this->set(args...);
            }
          void apply(){
            if( typeid(T) == typeid(float  ) ||
                typeid(T) == typeid(GLfloat)){
              if(dim==1)glProgramUniform1f(this->_program,this->_location,UNIFORM_ARGS1);
              if(dim==2)glProgramUniform2f(this->_program,this->_location,UNIFORM_ARGS2);
              if(dim==3)glProgramUniform3f(this->_program,this->_location,UNIFORM_ARGS3);
              if(dim==4)glProgramUniform4f(this->_program,this->_location,UNIFORM_ARGS4);
            }
            if( typeid(T) == typeid(int  ) ||
                typeid(T) == typeid(GLint)){
              if(dim==1)glProgramUniform1i(this->_program,this->_location,UNIFORM_ARGS1);
              if(dim==2)glProgramUniform2i(this->_program,this->_location,UNIFORM_ARGS2);
              if(dim==3)glProgramUniform3i(this->_program,this->_location,UNIFORM_ARGS3);
              if(dim==4)glProgramUniform4i(this->_program,this->_location,UNIFORM_ARGS4);
            }
            if( typeid(T) == typeid(unsigned) ||
                typeid(T) == typeid(GLuint  )){
              if(dim==1)glProgramUniform1ui(this->_program,this->_location,UNIFORM_ARGS1);
              if(dim==2)glProgramUniform2ui(this->_program,this->_location,UNIFORM_ARGS2);
              if(dim==3)glProgramUniform3ui(this->_program,this->_location,UNIFORM_ARGS3);
              if(dim==4)glProgramUniform4ui(this->_program,this->_location,UNIFORM_ARGS4);
            }
            if( typeid(T) == typeid(double  ) ||
                typeid(T) == typeid(GLdouble)){
              if(dim==1)glProgramUniform1d(this->_program,this->_location,UNIFORM_ARGS1);
              if(dim==2)glProgramUniform2d(this->_program,this->_location,UNIFORM_ARGS2);
              if(dim==3)glProgramUniform3d(this->_program,this->_location,UNIFORM_ARGS3);
              if(dim==4)glProgramUniform4d(this->_program,this->_location,UNIFORM_ARGS4);
            }
          }
          template<class...T2, typename std::enable_if<sizeof...(T2) == dim, unsigned>::type = 0>
            void set(T2... args){
              ge::core::argsToArray<dim,T>(this->_data,args...);
            }

      };

  }
}
