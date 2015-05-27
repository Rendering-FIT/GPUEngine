#pragma once

#include<geGL/OpenGL.h>
#include<geGL/ProgramObject.h>
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
        enum Type{
          F1,
          F2,
          F3,
          F4,
          I1,
          I2,
          I3,
          I4,
          U1,
          U2,
          U3,
          U4,
          D1,
          D2,
          D3,
          D4,
          F1V,
          F2V,
          F3V,
          F4V,
          I1V,
          I2V,
          I3V,
          I4V,
          U1V,
          U2V,
          U3V,
          U4V,
          D1V,
          D2V,
          D3V,
          D4V
        }type;
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
      inline void copyArgsToArray(T data[dim],T t){
        data[dim-1]=t;
      }
    template<unsigned dim,typename T,typename... Args>
      inline void copyArgsToArray(T data[dim],T t, Args... args){
        data[dim-1-sizeof...(args)]=t;
        copyArgsToArray<dim,T>(data,args...);
      }

    template<unsigned dim,typename T>
      class GEGL_EXPORT UniformData: public UniformDataProvider{
        public:
          T data[dim];
          template<typename...T2, typename std::enable_if<sizeof...(T2) == dim, unsigned>::type = 0>
            UniformData(T2... args){
              this->type = _getType<dim,T>();
              copyArgsToArray<dim,T>(args...);
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
              copyArgsToArray<dim,T*>(this->data,args...);
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

    namespace detail
    {
      template<unsigned... Is>
        struct seq { };

      template<unsigned N, unsigned... Is>
        struct gen_seq : gen_seq<N - 1, N - 1, Is...> { };

      template<unsigned... Is>
        struct gen_seq<0, Is...> : seq<Is...> { };
    }


    template<unsigned dim,typename T>
      class GEGL_EXPORT Uniform: public UniformCommand{
        public:
          T data[dim];
          template<class...T2, typename std::enable_if<sizeof...(T2) == dim, unsigned>::type = 0>
            Uniform(
                ge::gl::ProgramObject*program,
                std::string name,
                T2... args):UniformCommand(program,name){
              copyArgsToArray<dim,T>(this->data,args...);
            }
          template<class...T2, typename std::enable_if<sizeof...(T2) == dim, unsigned>::type = 0>
            Uniform(
                GLint location,
                T2... args):UniformCommand(location){
              copyArgsToArray<dim,T>(this->data,args...);
            }
          void apply(){
            if( typeid(T) == typeid(float  ) ||
                typeid(T) == typeid(GLfloat)){
              if(dim==1)glUniform1f(this->_location,this->data[0]);
              if(dim==2)glUniform2f(this->_location,this->data[0],this->data[1]);
              if(dim==3)glUniform3f(this->_location,this->data[0],this->data[1],this->data[2]);
              if(dim==4)glUniform4f(this->_location,this->data[0],this->data[1],this->data[2],this->data[3]);
            }
            if( typeid(T) == typeid(int  ) ||
                typeid(T) == typeid(GLint)){
              if(dim==1)glUniform1i(this->_location,this->data[0]);
              if(dim==2)glUniform2i(this->_location,this->data[0],this->data[1]);
              if(dim==3)glUniform3i(this->_location,this->data[0],this->data[1],this->data[2]);
              if(dim==4)glUniform4i(this->_location,this->data[0],this->data[1],this->data[2],this->data[3]);
            }
            if( typeid(T) == typeid(unsigned) ||
                typeid(T) == typeid(GLuint  )){
              if(dim==1)glUniform1ui(this->_location,this->data[0]);
              if(dim==2)glUniform2ui(this->_location,this->data[0],this->data[1]);
              if(dim==3)glUniform3ui(this->_location,this->data[0],this->data[1],this->data[2]);
              if(dim==4)glUniform4ui(this->_location,this->data[0],this->data[1],this->data[2],this->data[3]);
            }
            if( typeid(T) == typeid(double  ) ||
                typeid(T) == typeid(GLdouble)){
              if(dim==1)glUniform1d(this->_location,this->data[0]);
              if(dim==2)glUniform2d(this->_location,this->data[0],this->data[1]);
              if(dim==3)glUniform3d(this->_location,this->data[0],this->data[1],this->data[2]);
              if(dim==4)glUniform4d(this->_location,this->data[0],this->data[1],this->data[2],this->data[3]);
            }
          }
          template<class...T2, typename std::enable_if<sizeof...(T2) == dim, unsigned>::type = 0>
          void set(T2... args){
            copyArgsToArray<dim,T>(this->data,args...);
          }
      };
    template<unsigned dim,typename T>
      class GEGL_EXPORT UniformV: public UniformCommand{
        public:
          const T*data;
          GLsizei count;
          UniformV(
              ge::gl::ProgramObject*program,
              std::string name,
              T*data,
              GLsizei count=1):UniformCommand(program,name){
            this->data  = data;
            this->count = count;
          }
          UniformV(
              GLint location,
              const T*data,
              GLsizei count=1):UniformCommand(location){
            this->data  = data;
            this->count = count;
          }
          void apply(){
            return;
            if( typeid(T) == typeid(float  ) ||
                typeid(T) == typeid(GLfloat)){
              if(dim==1)glUniform1fv(this->_location,this->count,(const GLfloat*)this->data);
              if(dim==2)glUniform2fv(this->_location,this->count,(const GLfloat*)this->data);
              if(dim==3)glUniform3fv(this->_location,this->count,(const GLfloat*)this->data);
              if(dim==4)glUniform4fv(this->_location,this->count,(const GLfloat*)this->data);
            }
            if( typeid(T) == typeid(int  ) ||
                typeid(T) == typeid(GLint)){
              if(dim==1)glUniform1iv(this->_location,this->count,(const GLint*)this->data);
              if(dim==2)glUniform2iv(this->_location,this->count,(const GLint*)this->data);
              if(dim==3)glUniform3iv(this->_location,this->count,(const GLint*)this->data);
              if(dim==4)glUniform4iv(this->_location,this->count,(const GLint*)this->data);
            }
            if( typeid(T) == typeid(unsigned) ||
                typeid(T) == typeid(GLuint  )){
              if(dim==1)glUniform1uiv(this->_location,this->count,(const GLuint*)this->data);
              if(dim==2)glUniform2uiv(this->_location,this->count,(const GLuint*)this->data);
              if(dim==3)glUniform3uiv(this->_location,this->count,(const GLuint*)this->data);
              if(dim==4)glUniform4uiv(this->_location,this->count,(const GLuint*)this->data);
            }
            if( typeid(T) == typeid(double  ) ||
                typeid(T) == typeid(GLdouble)){
              if(dim==1)glUniform1dv(this->_location,this->count,(const GLdouble*)this->data);
              if(dim==2)glUniform2dv(this->_location,this->count,(const GLdouble*)this->data);
              if(dim==3)glUniform3dv(this->_location,this->count,(const GLdouble*)this->data);
              if(dim==4)glUniform4dv(this->_location,this->count,(const GLdouble*)this->data);
            }
          }
          void set(const T*data,GLsizei count=1){
            this->count = count;
            return;
            this->data  = data ;
          }
      };

    template<unsigned dim,typename T>
      class GEGL_EXPORT ProgramUniform: public ProgramUniformCommand{
        public:
          T data[dim];
          template<class...T2, typename std::enable_if<sizeof...(T2) == dim, unsigned>::type = 0>
            ProgramUniform(
                ge::gl::ProgramObject*program,
                std::string name,
                T2... args):ProgramUniformCommand(program,name){
              copyArgsToArray<dim,T>(this->data,args...);
            }
          template<class...T2, typename std::enable_if<sizeof...(T2) == dim, unsigned>::type = 0>
            ProgramUniform(
                GLuint program,
                GLint location,
                T2... args):ProgramUniformCommand(program,location){
              copyArgsToArray<dim,T>(this->data,args...);
            }
          void apply(){
            if( typeid(T) == typeid(float  ) ||
                typeid(T) == typeid(GLfloat)){
              if(dim==1)glProgramUniform1f(this->_program,this->_location,this->data[0]);
              if(dim==2)glProgramUniform2f(this->_program,this->_location,this->data[0],this->data[1]);
              if(dim==3)glProgramUniform3f(this->_program,this->_location,this->data[0],this->data[1],this->data[2]);
              if(dim==4)glProgramUniform4f(this->_program,this->_location,this->data[0],this->data[1],this->data[2],this->data[3]);
            }
            if( typeid(T) == typeid(int  ) ||
                typeid(T) == typeid(GLint)){
              if(dim==1)glProgramUniform1i(this->_program,this->_location,this->data[0]);
              if(dim==2)glProgramUniform2i(this->_program,this->_location,this->data[0],this->data[1]);
              if(dim==3)glProgramUniform3i(this->_program,this->_location,this->data[0],this->data[1],this->data[2]);
              if(dim==4)glProgramUniform4i(this->_program,this->_location,this->data[0],this->data[1],this->data[2],this->data[3]);
            }
            if( typeid(T) == typeid(unsigned) ||
                typeid(T) == typeid(GLuint  )){
              if(dim==1)glProgramUniform1ui(this->_program,this->_location,this->data[0]);
              if(dim==2)glProgramUniform2ui(this->_program,this->_location,this->data[0],this->data[1]);
              if(dim==3)glProgramUniform3ui(this->_program,this->_location,this->data[0],this->data[1],this->data[2]);
              if(dim==4)glProgramUniform4ui(this->_program,this->_location,this->data[0],this->data[1],this->data[2],this->data[3]);
            }
            if( typeid(T) == typeid(double  ) ||
                typeid(T) == typeid(GLdouble)){
              if(dim==1)glProgramUniform1d(this->_program,this->_location,this->data[0]);
              if(dim==2)glProgramUniform2d(this->_program,this->_location,this->data[0],this->data[1]);
              if(dim==3)glProgramUniform3d(this->_program,this->_location,this->data[0],this->data[1],this->data[2]);
              if(dim==4)glProgramUniform4d(this->_program,this->_location,this->data[0],this->data[1],this->data[2],this->data[3]);
            }
          }
      };

  }
}
