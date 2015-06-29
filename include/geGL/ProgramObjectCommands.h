#pragma once

#include<geCore/Command.h>
#include<geGL/Export.h>
#include<GL/glew.h>
#include<geGL/ProgramObject.h>
#include<geCore/dtemplates.h>

namespace ge{
  namespace gl{
    namespace po{
      class GEGL_EXPORT Use: public ge::core::Command{
        private:
          std::shared_ptr<ProgramObject>_program;
        public:
          Use(std::shared_ptr<ProgramObject>&program);
          virtual void operator()();
          std::shared_ptr<ProgramObject>&getProgram();
      };
      static const GLenum DEFAULT_SHADER = ge::core::nonof(
          GL_VERTEX_SHADER         ,
          GL_TESS_CONTROL_SHADER   ,
          GL_TESS_EVALUATION_SHADER,
          GL_GEOMETRY_SHADER       ,
          GL_FRAGMENT_SHADER       ,
          GL_COMPUTE_SHADER        );

      class GEGL_EXPORT SetVersion: public ge::core::Command{
        public:
          class Data{
            protected:
              unsigned    _version;
              std::string _profile;
              GLenum      _shader ;
            public:
              Data(
                  unsigned    version                 ,
                  std::string profile                 ,
                  GLenum      shader  = DEFAULT_SHADER);
              unsigned    getVersion();
              std::string getProfile();
              GLenum      getShader ();
              void        setVersion(unsigned    version);
              void        setProfile(std::string profile);
              void        setShader(GLenum shader = DEFAULT_SHADER);
          };
        private:
          std::shared_ptr<ProgramObject>_program;
          std::shared_ptr<Data>         _data   ;
        public:
          SetVersion(std::shared_ptr<ProgramObject>&program,std::shared_ptr<Data>&data);
          virtual void operator()();
          std::shared_ptr<ProgramObject>&getProgram();
          std::shared_ptr<Data>         &getData   ();
      };

      class GEGL_EXPORT Append: public ge::core::Command{
        public:
          class Data{
            protected:
              std::string _defs  ;
              GLenum      _shader;
            public:
              Data(
                  std::string defs                   ,
                  GLenum      shader = DEFAULT_SHADER);
              std::string getDefs  ();
              GLenum      getShader();
              void        setDefs  (std::string defs                   );
              void        setShader(GLenum      shader = DEFAULT_SHADER);
          };
        protected:
          std::shared_ptr<Data         >_data   ;
          std::shared_ptr<ProgramObject>_program;
        public:
          Append(std::shared_ptr<ProgramObject>&program,std::shared_ptr<Data>&data);
          virtual void operator()();
          std::shared_ptr<ProgramObject>&getProgram();
          std::shared_ptr<Data         >&getData();
      };

      template<unsigned DIM,typename T>
      class SetData{
        protected:
          T _data[DIM];
        public:
          template<typename...ARGS, typename std::enable_if<sizeof...(ARGS) == DIM, unsigned>::type = 0>
          SetData(ARGS... args){
            this->set(args...);
          }
          inline const T*get(){
            return this->_data;
          }
          void set(const T*data){
            std::memcpy(this->_data,data,DIM*sizeof(T));
          }
          template<typename...ARGS, typename std::enable_if<sizeof...(ARGS) == DIM, unsigned>::type = 0>
          void set(ARGS... args){
            ge::core::argsToArray<DIM,T>(this->_data,args...);
          }
      };

      template<unsigned DIM,typename T>
      class Set{
        protected:
          std::shared_ptr<ProgramObject> _program;
          std::string                    _name   ;
          std::shared_ptr<SetData<DIM,T>>_data   ;
        public:
          Set(
              std::shared_ptr<ProgramObject> &program,
              std::string                     name   ,
              std::shared_ptr<SetData<DIM,T>>&data   ){
            this->_program = program;
            this->_name    = name   ;
            this->_data    = data   ;
          }
          virtual void operator()();
          std::shared_ptr<ProgramObject> &getProgram(){
            return this->_program;
          }
          std::shared_ptr<SetData<DIM,T>>&getData   (){
            return this->_data;
          }
          std::string                     getName   (){
            return this->_name;
          }
          void setProgram(std::shared_ptr<ProgramObject>&program){
            this->_program = program;
          }
          void setName   (std::string name){
            this->_name = name;
          }
          void setData   (std::shared_ptr<SetData<DIM,T>>&data){
            this->_data = data;
          }
          
          template<unsigned... IND>
          inline void _ind(){
            const T*v=this->_data->get();
            this->_program->set(this->_name,v[IND]...);
          }
          template<unsigned D>
          inline void _iind(ge::core::gen_seq<D>Is){
            const T*v=this->_data->get();
            this->_program->set(this->_name,v[Is]);
          }
          
      };
      template<>void Set<1,GLfloat>::operator()(){this->_ind<0>();}
      template<>void Set<2,GLfloat>::operator()(){this->_ind<0,1>();}
      template<>void Set<3,GLfloat>::operator()(){this->_ind<0,1,2>();}
      template<>void Set<4,GLfloat>::operator()(){this->_ind<0,1,2,3>();}

      /*
      template<>
        void Set<2,GLfloat>::operator()(){
          const GLfloat*v=this->_data->get();
          this->_program->set(this->_name,v[0],v[1]);
        }
      template<>
        void Set<3,GLfloat>::operator()(){
          const GLfloat*v=this->_data->get();
          this->_program->set(this->_name,v[0],v[1],v[2]);
        }
      template<>
        void Set<4,GLfloat>::operator()(){
          const GLfloat*v=this->_data->get();
          this->_program->set(this->_name,v[0],v[1],v[3],v[4]);
        }
      template<>
        void Set<1,GLdouble>::operator()(){
          const GLdouble*v=this->_data->get();
          this->_program->set(this->_name,v[0]);
        }
      template<>
        void Set<2,GLdouble>::operator()(){
          const GLdouble*v=this->_data->get();
          this->_program->set(this->_name,v[0],v[1]);
        }
      template<>
        void Set<3,GLdouble>::operator()(){
          const GLdouble*v=this->_data->get();
          this->_program->set(this->_name,v[0],v[1],v[2]);
        }
      template<>
        void Set<4,GLdouble>::operator()(){
          const GLdouble*v=this->_data->get();
          this->_program->set(this->_name,v[0],v[1],v[3],v[4]);
        }
      template<>
        void Set<1,GLint>::operator()(){
          const GLint*v=this->_data->get();
          this->_program->set(this->_name,v[0]);
        }
      template<>
        void Set<2,GLint>::operator()(){
          const GLint*v=this->_data->get();
          this->_program->set(this->_name,v[0],v[1]);
        }
      template<>
        void Set<3,GLint>::operator()(){
          const GLint*v=this->_data->get();
          this->_program->set(this->_name,v[0],v[1],v[2]);
        }
      template<>
        void Set<4,GLint>::operator()(){
          const GLint*v=this->_data->get();
          this->_program->set(this->_name,v[0],v[1],v[3],v[4]);
        }
      template<>
        void Set<1,GLuint>::operator()(){
          const GLuint*v=this->_data->get();
          this->_program->set(this->_name,v[0]);
        }
      template<>
        void Set<2,GLuint>::operator()(){
          const GLuint*v=this->_data->get();
          this->_program->set(this->_name,v[0],v[1]);
        }
      template<>
        void Set<3,GLuint>::operator()(){
          const GLuint*v=this->_data->get();
          this->_program->set(this->_name,v[0],v[1],v[2]);
        }
      template<>
        void Set<4,GLuint>::operator()(){
          const GLuint*v=this->_data->get();
          this->_program->set(this->_name,v[0],v[1],v[3],v[4]);
        }
      template<>
        void Set<1,GLboolean>::operator()(){
          const GLboolean*v=this->_data->get();
          this->_program->set(this->_name,v[0]);
        }
      template<>
        void Set<2,GLboolean>::operator()(){
          const GLboolean*v=this->_data->get();
          this->_program->set(this->_name,v[0],v[1]);
        }
      template<>
        void Set<3,GLboolean>::operator()(){
          const GLboolean*v=this->_data->get();
          this->_program->set(this->_name,v[0],v[1],v[2]);
        }
      template<>
        void Set<4,GLboolean>::operator()(){
          const GLboolean*v=this->_data->get();
          this->_program->set(this->_name,v[0],v[1],v[3],v[4]);
        }*/
    }
  }
}

