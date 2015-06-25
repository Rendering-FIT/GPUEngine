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
    }
  }
}

