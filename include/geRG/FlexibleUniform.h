#ifndef GE_FLEXIBLE_UNIFORM_H
#define GE_FLEXIBLE_UNIFORM_H

#include <memory>
#include <string>
#include <geGL/OpenGLCommands.h>
#include <geRG/Export.h>

namespace ge
{
   namespace rg
   {

      class GERG_EXPORT FlexibleUseProgram
            : public ge::gl::UseProgram<std::shared_ptr<ge::gl::ProgramObject>>
            , public std::enable_shared_from_this<FlexibleUseProgram> {
         typedef ge::gl::UseProgram<std::shared_ptr<ge::gl::ProgramObject>> inherited;
      protected:

         struct NoExport { // workaround for MSVC 2015: thread_local variables can not have DLL-export interface,
                           // solution: nested structures are not DLL-exported and do not inherit DLL-export of parent class
            static thread_local std::shared_ptr<ge::gl::ProgramObject> _activeProgram;
         };

      public:

         inline FlexibleUseProgram(const std::shared_ptr<ge::gl::ProgramObject>& program);
         virtual void operator()();

         static inline std::shared_ptr<ge::gl::ProgramObject>& activeProgram();
         static inline void setActiveProgram(const std::shared_ptr<ge::gl::ProgramObject>& programObject);

      };


      class GERG_EXPORT FlexibleLocation {
      protected:
         std::string _name;
      public:
         inline FlexibleLocation() {}
         inline FlexibleLocation(const std::string &name) : _name(name) {}
         inline operator int() const  { return FlexibleUseProgram::activeProgram()->getUniform(_name).getLocation(); }
      };


      template<typename GEGL_UNIFORM,class ...ARGS>
      class GERG_EXPORT FlexibleUniform : public GEGL_UNIFORM {
      public:

         inline FlexibleUniform(const std::string &name,ARGS... args) : GEGL_UNIFORM(FlexibleLocation(name),args...) {}

      };


      typedef FlexibleUniform<ge::gl::Uniform1i <FlexibleLocation,int>,     int>      FlexibleUniform1i;
      typedef FlexibleUniform<ge::gl::Uniform1ui<FlexibleLocation,unsigned>,unsigned> FlexibleUniform1ui;
      typedef FlexibleUniform<ge::gl::Uniform1f <FlexibleLocation,float>,   float>    FlexibleUniform1f;
      typedef FlexibleUniform<ge::gl::Uniform1d <FlexibleLocation,double>,  double>   FlexibleUniform1d;
      typedef FlexibleUniform<ge::gl::Uniform2i <FlexibleLocation,int,     int>,     int,     int>      FlexibleUniform2i;
      typedef FlexibleUniform<ge::gl::Uniform2ui<FlexibleLocation,unsigned,unsigned>,unsigned,unsigned> FlexibleUniform2ui;
      typedef FlexibleUniform<ge::gl::Uniform2f <FlexibleLocation,float,   float>,   float,   float>    FlexibleUniform2f;
      typedef FlexibleUniform<ge::gl::Uniform2d <FlexibleLocation,double,  double>,  double,  double>   FlexibleUniform2d;
      typedef FlexibleUniform<ge::gl::Uniform3i <FlexibleLocation,int,     int,     int>,     int,     int,     int>      FlexibleUniform3i;
      typedef FlexibleUniform<ge::gl::Uniform3ui<FlexibleLocation,unsigned,unsigned,unsigned>,unsigned,unsigned,unsigned> FlexibleUniform3ui;
      typedef FlexibleUniform<ge::gl::Uniform3f <FlexibleLocation,float,   float,   float>,   float,   float,   float>    FlexibleUniform3f;
      typedef FlexibleUniform<ge::gl::Uniform3d <FlexibleLocation,double,  double,  double>,  double,  double,  double>   FlexibleUniform3d;
      typedef FlexibleUniform<ge::gl::Uniform4i <FlexibleLocation,int,     int,     int,     int>,     int,     int,     int,     int>      FlexibleUniform4i;
      typedef FlexibleUniform<ge::gl::Uniform4ui<FlexibleLocation,unsigned,unsigned,unsigned,unsigned>,unsigned,unsigned,unsigned,unsigned> FlexibleUniform4ui;
      typedef FlexibleUniform<ge::gl::Uniform4f <FlexibleLocation,float,   float,   float,   float>,   float,   float,   float,   float>    FlexibleUniform4f;
      typedef FlexibleUniform<ge::gl::Uniform4d <FlexibleLocation,double,  double,  double,  double>,  double,  double,  double,  double>   FlexibleUniform4d;
      template<typename T> class FlexibleUniform1iv : public FlexibleUniform<ge::gl::Uniform1iv <FlexibleLocation,GLsizei,T>,GLsizei,T> {};
      template<typename T> class FlexibleUniform1uiv: public FlexibleUniform<ge::gl::Uniform1uiv<FlexibleLocation,GLsizei,T>,GLsizei,T> {};
      template<typename T> class FlexibleUniform1fv : public FlexibleUniform<ge::gl::Uniform1fv <FlexibleLocation,GLsizei,T>,GLsizei,T> {};
      template<typename T> class FlexibleUniform1dv : public FlexibleUniform<ge::gl::Uniform1dv <FlexibleLocation,GLsizei,T>,GLsizei,T> {};
      template<typename T> class FlexibleUniform2iv : public FlexibleUniform<ge::gl::Uniform2iv <FlexibleLocation,GLsizei,T>,GLsizei,T> {};
      template<typename T> class FlexibleUniform2uiv: public FlexibleUniform<ge::gl::Uniform2uiv<FlexibleLocation,GLsizei,T>,GLsizei,T> {};
      template<typename T> class FlexibleUniform2fv : public FlexibleUniform<ge::gl::Uniform2fv <FlexibleLocation,GLsizei,T>,GLsizei,T> {};
      template<typename T> class FlexibleUniform2dv : public FlexibleUniform<ge::gl::Uniform2dv <FlexibleLocation,GLsizei,T>,GLsizei,T> {};
      template<typename T> class FlexibleUniform3iv : public FlexibleUniform<ge::gl::Uniform3iv <FlexibleLocation,GLsizei,T>,GLsizei,T> {};
      template<typename T> class FlexibleUniform3uiv: public FlexibleUniform<ge::gl::Uniform3uiv<FlexibleLocation,GLsizei,T>,GLsizei,T> {};
      template<typename T> class FlexibleUniform3fv : public FlexibleUniform<ge::gl::Uniform3fv <FlexibleLocation,GLsizei,T>,GLsizei,T> {};
      template<typename T> class FlexibleUniform3dv : public FlexibleUniform<ge::gl::Uniform3dv <FlexibleLocation,GLsizei,T>,GLsizei,T> {};
      template<typename T> class FlexibleUniform4iv : public FlexibleUniform<ge::gl::Uniform4iv <FlexibleLocation,GLsizei,T>,GLsizei,T> {};
      template<typename T> class FlexibleUniform4uiv: public FlexibleUniform<ge::gl::Uniform4uiv<FlexibleLocation,GLsizei,T>,GLsizei,T> {};
      template<typename T> class FlexibleUniform4fv : public FlexibleUniform<ge::gl::Uniform4fv <FlexibleLocation,GLsizei,T>,GLsizei,T> {};
      template<typename T> class FlexibleUniform4dv : public FlexibleUniform<ge::gl::Uniform4dv <FlexibleLocation,GLsizei,T>,GLsizei,T> {};
      template<typename T> class FlexibleUniformMatrix2f : public FlexibleUniform<ge::gl::UniformMatrix2fv<FlexibleLocation,GLsizei,GLboolean,T>,GLsizei,GLboolean,T> {};
      template<typename T> class FlexibleUniformMatrix2d : public FlexibleUniform<ge::gl::UniformMatrix2dv<FlexibleLocation,GLsizei,GLboolean,T>,GLsizei,GLboolean,T> {};
      template<typename T> class FlexibleUniformMatrix3f : public FlexibleUniform<ge::gl::UniformMatrix3fv<FlexibleLocation,GLsizei,GLboolean,T>,GLsizei,GLboolean,T> {};
      template<typename T> class FlexibleUniformMatrix3d : public FlexibleUniform<ge::gl::UniformMatrix3dv<FlexibleLocation,GLsizei,GLboolean,T>,GLsizei,GLboolean,T> {};
      template<typename T> class FlexibleUniformMatrix4f : public FlexibleUniform<ge::gl::UniformMatrix4fv<FlexibleLocation,GLsizei,GLboolean,T>,GLsizei,GLboolean,T> {};
      template<typename T> class FlexibleUniformMatrix4d : public FlexibleUniform<ge::gl::UniformMatrix4dv<FlexibleLocation,GLsizei,GLboolean,T>,GLsizei,GLboolean,T> {};
      template<typename T> class FlexibleUniformMatrix2x3f : public FlexibleUniform<ge::gl::UniformMatrix2x3fv<FlexibleLocation,GLsizei,GLboolean,T>,GLsizei,GLboolean,T> {};
      template<typename T> class FlexibleUniformMatrix2x3d : public FlexibleUniform<ge::gl::UniformMatrix2x3dv<FlexibleLocation,GLsizei,GLboolean,T>,GLsizei,GLboolean,T> {};
      template<typename T> class FlexibleUniformMatrix2x4f : public FlexibleUniform<ge::gl::UniformMatrix2x4fv<FlexibleLocation,GLsizei,GLboolean,T>,GLsizei,GLboolean,T> {};
      template<typename T> class FlexibleUniformMatrix2x4d : public FlexibleUniform<ge::gl::UniformMatrix2x4dv<FlexibleLocation,GLsizei,GLboolean,T>,GLsizei,GLboolean,T> {};
      template<typename T> class FlexibleUniformMatrix3x2f : public FlexibleUniform<ge::gl::UniformMatrix3x2fv<FlexibleLocation,GLsizei,GLboolean,T>,GLsizei,GLboolean,T> {};
      template<typename T> class FlexibleUniformMatrix3x2d : public FlexibleUniform<ge::gl::UniformMatrix3x2dv<FlexibleLocation,GLsizei,GLboolean,T>,GLsizei,GLboolean,T> {};
      template<typename T> class FlexibleUniformMatrix3x4f : public FlexibleUniform<ge::gl::UniformMatrix3x4fv<FlexibleLocation,GLsizei,GLboolean,T>,GLsizei,GLboolean,T> {};
      template<typename T> class FlexibleUniformMatrix3x4d : public FlexibleUniform<ge::gl::UniformMatrix3x4dv<FlexibleLocation,GLsizei,GLboolean,T>,GLsizei,GLboolean,T> {};
      template<typename T> class FlexibleUniformMatrix4x2f : public FlexibleUniform<ge::gl::UniformMatrix4x2fv<FlexibleLocation,GLsizei,GLboolean,T>,GLsizei,GLboolean,T> {};
      template<typename T> class FlexibleUniformMatrix4x2d : public FlexibleUniform<ge::gl::UniformMatrix4x2dv<FlexibleLocation,GLsizei,GLboolean,T>,GLsizei,GLboolean,T> {};
      template<typename T> class FlexibleUniformMatrix4x3f : public FlexibleUniform<ge::gl::UniformMatrix4x3fv<FlexibleLocation,GLsizei,GLboolean,T>,GLsizei,GLboolean,T> {};
      template<typename T> class FlexibleUniformMatrix4x3d : public FlexibleUniform<ge::gl::UniformMatrix4x3dv<FlexibleLocation,GLsizei,GLboolean,T>,GLsizei,GLboolean,T> {};



      // inline methods
      inline FlexibleUseProgram::FlexibleUseProgram(const std::shared_ptr<ge::gl::ProgramObject>& program) : ge::gl::UseProgram<std::shared_ptr<ge::gl::ProgramObject>>(program) {}
      inline std::shared_ptr<ge::gl::ProgramObject>& FlexibleUseProgram::activeProgram()  { return NoExport::_activeProgram; }
      inline void FlexibleUseProgram::setActiveProgram(const std::shared_ptr<ge::gl::ProgramObject>& programObject)  { NoExport::_activeProgram=programObject; }

   }
}

#endif /* GE_FLEXIBLE_UNIFORM_H */
