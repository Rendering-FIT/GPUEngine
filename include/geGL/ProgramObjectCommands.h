#pragma once

#include<geCore/Command.h>
#include<geGL/Export.h>
#include<GL/glew.h>
#include<geGL/ProgramObject.h>
#include<geGL/Definitions.h>
#include<geCore/dtemplates.h>
#include<geGL/ObjectCommands.h>

namespace ge{
  namespace gl{
    namespace po{
      /*
      class GEGL_EXPORT SharedProgram{
        protected:
          std::shared_ptr<ProgramObject>_object;
        public:
          SharedProgram(const std::shared_ptr<ProgramObject>&program);
          std::shared_ptr<ProgramObject>&getProgram();
          void setProgram(const std::shared_ptr<ProgramObject>&program);
      };*/

      class GEGL_EXPORT Use: public ge::core::Command, public Shared<ProgramObject>{
        public:
          Use(const std::shared_ptr<ProgramObject>&program);
          virtual void operator()();
      };

      static const GLenum DEFAULT_SHADER = ge::core::nonof(
          GL_VERTEX_SHADER         ,
          GL_TESS_CONTROL_SHADER   ,
          GL_TESS_EVALUATION_SHADER,
          GL_GEOMETRY_SHADER       ,
          GL_FRAGMENT_SHADER       ,
          GL_COMPUTE_SHADER        );

      class GEGL_EXPORT SetVersion: public ge::core::Command, public Shared<ProgramObject>{
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
        protected:
          std::shared_ptr<Data>_data;
        public:
          SetVersion(
              const std::shared_ptr<ProgramObject>&program,
              const std::shared_ptr<Data         >&data   );
          virtual void operator()();
          std::shared_ptr<Data>&getData();
          void setData(const std::shared_ptr<Data>&data);
      };

      class GEGL_EXPORT Append: public ge::core::Command, public Shared<ProgramObject>{
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
          std::shared_ptr<Data>_data   ;
        public:
          Append(
              const std::shared_ptr<ProgramObject>&program,
              const std::shared_ptr<Data         >&data   );
          virtual void operator()();
          std::shared_ptr<Data>&getData();
          void setData(const std::shared_ptr<Data>&data);
      };

      class Location: public Shared<ProgramObject>{
        protected:
          std::string _name;
        public:
          Location(
              const std::shared_ptr<ProgramObject>&program,
              std::string                          name   );
          std::string getName();
          void setName   (std::string name);
      };

      template<unsigned DIM,typename T>
        class Set: public ge::core::Command, public Location{
          public:
            class Data{
              protected:
                T _data[DIM];
              public:
                template<SIZED_VARIADIC_PARAMS(ARGS,DIM)>
                  Data(ARGS... args){
                    this->set(args...);
                  }
                inline const T*get(){
                  return this->_data;
                }
                void set(const T*data){
                  std::memcpy(this->_data,data,DIM*sizeof(T));
                }
                template<SIZED_VARIADIC_PARAMS(ARGS,DIM)>
                  void set(ARGS... args){
                    ge::core::argsToArray<DIM,T>(this->_data,args...);
                  }
            };
          protected:
            std::shared_ptr<Data>_data;
            template<unsigned... Is>
              inline void _iind(ge::core::seq<Is...>){
                const T*v=this->_data->get();
                this->_object->set(this->_name,v[Is]...);
              }
          public:
            Set(
                const std::shared_ptr<ProgramObject>&program,
                std::string                          name   ,
                const std::shared_ptr<Data         >&data   ):Location(program,name){
              this->_data    = data   ;
            }
            template<SIZED_VARIADIC_PARAMS(ARGS,DIM)>
              Set(
                  const std::shared_ptr<ProgramObject>&program,
                  std::string                          name   ,
                  ARGS...                              args   ):Location(program,name){
                this->setData(std::make_shared<Data>(args...));
              }
            virtual void operator()(){
              this->_iind(ge::core::gen_seq<DIM>{});
            }
            std::shared_ptr<Data>&getData(){
              return this->_data;
            }
            void setData(const std::shared_ptr<Data>&data){
              this->_data = data;
            }
        };

      template<typename T,unsigned COMPONENTS>
        class UniformVData{
          protected:
            T*     _data ;
            GLuint _count;
          public:
            UniformVData(GLuint count=1,const T*data=NULL){
              this->_count = count;
              this->_data  = new T[this->getCount()*COMPONENTS];
              if(data)this->copy(data);
            }
            ~UniformVData(){
              delete[]this->_data;
            }
            inline const T*get(){
              return this->_data;
            }
            inline GLuint getCount(){
              return this->_count;
            }
            void copy(const T*data,unsigned size=0,unsigned writeOffset=0){
              if(size==0)std::memcpy(this->_data,data,COMPONENTS*sizeof(T)*this->getCount());
              else std::memcpy(
                  ((char*)this->_data)+writeOffset,
                  ((char*)data       ),
                  COMPONENTS*sizeof(T)*this->getCount());
            }
        };

      template<unsigned DIM,typename T>
        class SetV: public ge::core::Command, public Location{
          public:
            class Data: public UniformVData<T,DIM>{
              public:
                Data(GLuint count=1,const T*data=NULL):UniformVData<T,DIM>(count,data){}
            };
          protected:
            std::shared_ptr<Data>_data;
          public:
            SetV(
                const std::shared_ptr<ProgramObject>&program,
                std::string                    name         ,
                const std::shared_ptr<Data         >&data   ):Location(program,name){
              this->_data = data   ;
            }
            SetV(
                const std::shared_ptr<ProgramObject>&program       ,
                std::string                          name          ,
                GLuint                               count   = 1   ,
                const T*                             data    = NULL):Location(program,name){
              this->_data = std::make_shared<Data>(count,data);
            }
            virtual void operator()(){
              this->_object->set(this->_name,this->_data->getCount(),this->_data->get());
            }
            std::shared_ptr<Data>&getData(){
              return this->_data;
            }
            void setData(const std::shared_ptr<Data>&data){
              this->_data = data;
            }
        };

      template<unsigned X,unsigned Y,typename T>
        class SetMatrix: public ge::core::Command, public Location{
          public:
            class Data: public UniformVData<T,X*Y>{
              protected:
                GLboolean _transpose;
              public:
                Data(
                    GLsizei   count     = 1       ,
                    const T*  data      = NULL    ,
                    GLboolean transpose = GL_FALSE):UniformVData<T,X*Y>(count,data){
                  this->setTranspose(transpose);
                }
                GLboolean getTranspose(){
                  return this->_transpose;
                }
                void setTranspose(GLboolean transpose){
                  this->_transpose = transpose;
                }
            };
          protected:
            std::shared_ptr<Data>_data;
          public:
            SetMatrix(
                const std::shared_ptr<ProgramObject>&program,
                std::string                          name   ,
                const std::shared_ptr<Data         >&data   ):Location(program,name){
              this->setData(data);
            }
            virtual void operator()(){
              this->_object->set(
                  this->_name                    ,
                  this->getData()->getCount    (),
                  this->getData()->getTranspose(),
                  this->getData()->get         ());
            }
            inline std::shared_ptr<Data>&getData(){
              return this->_data;
            }
            inline void setData(const std::shared_ptr<Data>&data){
              this->_data = data;
            }
        };
    }
  }
}
