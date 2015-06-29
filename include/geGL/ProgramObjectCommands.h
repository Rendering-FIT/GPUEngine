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
          Use(std::shared_ptr<ProgramObject> program);
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
      class Set: public ge::core::Command{
        public:
          class Data{
            protected:
              T _data[DIM];
            public:
#ifndef _MSC_VER
              template<typename...ARGS, typename std::enable_if<sizeof...(ARGS) == DIM, unsigned>::type = 0>
#else
              template<typename...ARGS>
#endif//immature Visual Studio compiler...
                Data(ARGS... args){
                  this->set(args...);
                }
              inline const T*get(){
                return this->_data;
              }
              void set(const T*data){
                std::memcpy(this->_data,data,DIM*sizeof(T));
              }

#ifndef _MSC_VER
              template<typename...ARGS, typename std::enable_if<sizeof...(ARGS) == DIM, unsigned>::type = 0>
#else
              template<typename...ARGS>
#endif//immature Visual Studio compiler...
                void set(ARGS... args){
                  ge::core::argsToArray<DIM,T>(this->_data,args...);
                }
          };
        protected:
          std::shared_ptr<ProgramObject> _program;
          std::string                    _name   ;
          std::shared_ptr<Data>          _data   ;
          template<unsigned... Is>
            inline void _iind(ge::core::seq<Is...>){
              const T*v=this->_data->get();
              this->_program->set(this->_name,v[Is]...);
            }
        public:
          Set(
              std::shared_ptr<ProgramObject> &program,
              std::string                     name   ,
              std::shared_ptr<Data>&data   ){
            this->_program = program;
            this->_name    = name   ;
            this->_data    = data   ;
          }

#ifndef _MSC_VER
              template<typename...ARGS, typename std::enable_if<sizeof...(ARGS) == DIM, unsigned>::type = 0>
#else
              template<typename...ARGS>
#endif//immature Visual Studio compiler...
            Set(
                std::shared_ptr<ProgramObject> &program,
                std::string                     name   ,
                ARGS...                         args   ){
              this->_program = program;
              this->_name    = name   ;
              this->_data    = std::make_shared<Data>(args...);
            }

          virtual void operator()(){
            this->_iind(ge::core::gen_seq<DIM>{});
          }
          std::shared_ptr<ProgramObject> &getProgram(){
            return this->_program;
          }
          std::shared_ptr<Data>&getData   (){
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
          void setData   (std::shared_ptr<Data>&data){
            this->_data = data;
          }
      };
      template<unsigned DIM,typename T>
      class SetV: public ge::core::Command{
        public:
          class Data{
            protected:
              T*      _data ;
              GLuint  _count;
            public:
              Data(GLuint count=1,const T*data=NULL){
                this->_count = count;
                this->_data = new T[this->getCount()*DIM];
                if(data)this->copy(data);
              }
              ~Data(){
                delete this->_data;
              }
              inline const T*get(){
                return this->_data;
              }
              inline GLuint getCount(){
                return this->_count;
              }
              void copy(const T*data,unsigned size=0,unsigned writeOffset=0){
                if(size==0)std::memcpy(this->_data,data,DIM*sizeof(T)*this->getCount());
                else std::memcpy(
                    ((char*)this->_data)+writeOffset,
                    ((char*)data       ),
                    DIM*sizeof(T)*this->getCount());
              }
          };
        protected:
          std::shared_ptr<ProgramObject> _program;
          std::string                    _name   ;
          std::shared_ptr<Data>          _data   ;
        public:
          SetV(
              std::shared_ptr<ProgramObject> &program,
              std::string                     name   ,
              std::shared_ptr<Data>&data             ){
            this->_program = program;
            this->_name    = name   ;
            this->_data    = data   ;
          }
          SetV(
              std::shared_ptr<ProgramObject> &program       ,
              std::string                     name          ,
              GLuint                          count   = 1   ,
              const T*                        data    = NULL){
            this->_program = program                           ;
            this->_name    = name                              ;
            this->_data    = std::make_shared<Data>(count,data);
          }
          virtual void operator()(){
            this->_program->set(this->_name,this->_data->getCount(),this->_data->get());
          }
          std::shared_ptr<ProgramObject> &getProgram(){
            return this->_program;
          }
          std::shared_ptr<Data>&getData   (){
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
          void setData   (std::shared_ptr<Data>&data){
            this->_data = data;
          }
      };

    }
  }
}

