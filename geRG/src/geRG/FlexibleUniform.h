#ifndef GE_FLEXIBLE_UNIFORM_H
#define GE_FLEXIBLE_UNIFORM_H

#include <memory>
#include <string>
#include <geRG/Export.h>
#include <geGL/Program.h>
#include <geCore/Command.h>
#include <geCore/Dtemplates.h>

namespace ge
{
   namespace rg
   {

      class GERG_EXPORT FlexibleUseProgram : public ge::core::Command {
      protected:

         std::shared_ptr<ge::gl::Program> _program;

         struct NoExport { // workaround for MSVC 2015: thread_local variables can not have DLL-export interface,
                           // solution: nested structures are not DLL-exported and do not inherit DLL-export of parent class
            static thread_local std::shared_ptr<ge::gl::Program> _activeProgram;
         };

      public:

         inline FlexibleUseProgram(const std::shared_ptr<ge::gl::Program>& program);
         virtual void operator()() override;

         inline const std::shared_ptr<ge::gl::Program>& program() const;
         inline void setProgram(const std::shared_ptr<ge::gl::Program>& program);

         static inline std::shared_ptr<ge::gl::Program>& activeProgram();
         static inline void setActiveProgram(const std::shared_ptr<ge::gl::Program>& program);

      };


      template<class ...ARGS>
      class FlexibleUniform : public ge::core::Command {
      protected:

         std::string _name;
         std::tuple<ARGS...> _values;

      public:

         const std::tuple<ARGS...>& values() const  { return _values; }
         void setValues(ARGS... values)  { _values=std::tuple<ARGS...>(values...); }

         inline FlexibleUniform(const std::string &name,ARGS... values) : _name(name), _values(values...)  {}
         virtual void operator()() override {
            callProviderMethod(_name,_values,typename ge::core::make_index_sequence<sizeof...(ARGS)>::type{});
         }

      protected:

         template<typename...ARGS2,std::size_t...I>
         void callProviderMethod(const std::string &name,std::tuple<ARGS2...>const& args,ge::core::index_sequence<I...>)
         {
            FlexibleUseProgram::activeProgram()->set(name,(std::get<I>(args))...);
         }

      };


      typedef FlexibleUniform<int>      FlexibleUniform1i;
      typedef FlexibleUniform<unsigned> FlexibleUniform1ui;
      typedef FlexibleUniform<float>    FlexibleUniform1f;
      typedef FlexibleUniform<double>   FlexibleUniform1d;
      typedef FlexibleUniform<int,     int>      FlexibleUniform2i;
      typedef FlexibleUniform<unsigned,unsigned> FlexibleUniform2ui;
      typedef FlexibleUniform<float,   float>    FlexibleUniform2f;
      typedef FlexibleUniform<double,  double>   FlexibleUniform2d;
      typedef FlexibleUniform<int,     int,     int>      FlexibleUniform3i;
      typedef FlexibleUniform<unsigned,unsigned,unsigned> FlexibleUniform3ui;
      typedef FlexibleUniform<float,   float,   float>    FlexibleUniform3f;
      typedef FlexibleUniform<double,  double,  double>   FlexibleUniform3d;
      typedef FlexibleUniform<int,     int,     int,     int>      FlexibleUniform4i;
      typedef FlexibleUniform<unsigned,unsigned,unsigned,unsigned> FlexibleUniform4ui;
      typedef FlexibleUniform<float,   float,   float,   float>    FlexibleUniform4f;
      typedef FlexibleUniform<double,  double,  double,  double>   FlexibleUniform4d;
//       template<typename T> class FlexibleUniformMatrix2f : public FlexibleUniform<ge::gl::UniformMatrix2fv<FlexibleLocation,GLsizei,GLboolean,T>,GLsizei,GLboolean,T> {};
//       template<typename T> class FlexibleUniformMatrix2d : public FlexibleUniform<ge::gl::UniformMatrix2dv<FlexibleLocation,GLsizei,GLboolean,T>,GLsizei,GLboolean,T> {};
//       template<typename T> class FlexibleUniformMatrix3f : public FlexibleUniform<ge::gl::UniformMatrix3fv<FlexibleLocation,GLsizei,GLboolean,T>,GLsizei,GLboolean,T> {};
//       template<typename T> class FlexibleUniformMatrix3d : public FlexibleUniform<ge::gl::UniformMatrix3dv<FlexibleLocation,GLsizei,GLboolean,T>,GLsizei,GLboolean,T> {};
//       template<typename T> class FlexibleUniformMatrix4f : public FlexibleUniform<ge::gl::UniformMatrix4fv<FlexibleLocation,GLsizei,GLboolean,T>,GLsizei,GLboolean,T> {};
//       template<typename T> class FlexibleUniformMatrix4d : public FlexibleUniform<ge::gl::UniformMatrix4dv<FlexibleLocation,GLsizei,GLboolean,T>,GLsizei,GLboolean,T> {};
//       template<typename T> class FlexibleUniformMatrix2x3f : public FlexibleUniform<ge::gl::UniformMatrix2x3fv<FlexibleLocation,GLsizei,GLboolean,T>,GLsizei,GLboolean,T> {};
//       template<typename T> class FlexibleUniformMatrix2x3d : public FlexibleUniform<ge::gl::UniformMatrix2x3dv<FlexibleLocation,GLsizei,GLboolean,T>,GLsizei,GLboolean,T> {};
//       template<typename T> class FlexibleUniformMatrix2x4f : public FlexibleUniform<ge::gl::UniformMatrix2x4fv<FlexibleLocation,GLsizei,GLboolean,T>,GLsizei,GLboolean,T> {};
//       template<typename T> class FlexibleUniformMatrix2x4d : public FlexibleUniform<ge::gl::UniformMatrix2x4dv<FlexibleLocation,GLsizei,GLboolean,T>,GLsizei,GLboolean,T> {};
//       template<typename T> class FlexibleUniformMatrix3x2f : public FlexibleUniform<ge::gl::UniformMatrix3x2fv<FlexibleLocation,GLsizei,GLboolean,T>,GLsizei,GLboolean,T> {};
//       template<typename T> class FlexibleUniformMatrix3x2d : public FlexibleUniform<ge::gl::UniformMatrix3x2dv<FlexibleLocation,GLsizei,GLboolean,T>,GLsizei,GLboolean,T> {};
//       template<typename T> class FlexibleUniformMatrix3x4f : public FlexibleUniform<ge::gl::UniformMatrix3x4fv<FlexibleLocation,GLsizei,GLboolean,T>,GLsizei,GLboolean,T> {};
//       template<typename T> class FlexibleUniformMatrix3x4d : public FlexibleUniform<ge::gl::UniformMatrix3x4dv<FlexibleLocation,GLsizei,GLboolean,T>,GLsizei,GLboolean,T> {};
//       template<typename T> class FlexibleUniformMatrix4x2f : public FlexibleUniform<ge::gl::UniformMatrix4x2fv<FlexibleLocation,GLsizei,GLboolean,T>,GLsizei,GLboolean,T> {};
//       template<typename T> class FlexibleUniformMatrix4x2d : public FlexibleUniform<ge::gl::UniformMatrix4x2dv<FlexibleLocation,GLsizei,GLboolean,T>,GLsizei,GLboolean,T> {};
//       template<typename T> class FlexibleUniformMatrix4x3f : public FlexibleUniform<ge::gl::UniformMatrix4x3fv<FlexibleLocation,GLsizei,GLboolean,T>,GLsizei,GLboolean,T> {};
//       template<typename T> class FlexibleUniformMatrix4x3d : public FlexibleUniform<ge::gl::UniformMatrix4x3dv<FlexibleLocation,GLsizei,GLboolean,T>,GLsizei,GLboolean,T> {};


      // inline methods
      inline FlexibleUseProgram::FlexibleUseProgram(const std::shared_ptr<ge::gl::Program>& program) : _program(program) {}
      inline const std::shared_ptr<ge::gl::Program>& FlexibleUseProgram::program() const  { return _program; }
      inline void FlexibleUseProgram::setProgram(const std::shared_ptr<ge::gl::Program>& program)  { _program=program; }
      inline std::shared_ptr<ge::gl::Program>& FlexibleUseProgram::activeProgram()  { return NoExport::_activeProgram; }
      inline void FlexibleUseProgram::setActiveProgram(const std::shared_ptr<ge::gl::Program>& program)  { NoExport::_activeProgram=program; }

   }
}

#endif /* GE_FLEXIBLE_UNIFORM_H */
