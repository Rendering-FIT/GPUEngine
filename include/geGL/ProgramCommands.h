#pragma once

#include<geCore/Command.h>
#include<geGL/Export.h>
#include<GL/glew.h>
#include<geGL/AllAttribs.h>

namespace ge{
  namespace gl{
    template<
      typename PROGRAM_TYPE = GLuint>
    class UseProgram:
        public ge::core::Command,
        public at::Program<PROGRAM_TYPE>{
      public:
        UseProgram(
            PROGRAM_TYPE const&program):
          at::Program<PROGRAM_TYPE>(program){}
        virtual~UseProgram(){}
        virtual void operator()(){
          glUseProgram(
            ge::core::convertTo<GLuint>(this->at::Program<PROGRAM_TYPE>::_value)
          );
        }
    };

    template<
      typename PROGRAM_TYPE          = GLuint       ,
      typename PROGRAMINTERFACE_TYPE = GLenum       ,
      typename INDEX_TYPE            = GLuint       ,
      typename PROPCOUNT_TYPE        = GLsizei      ,
      typename PROPS_TYPE            = const GLenum*,
      typename BUFSIZE_TYPE          = GLsizei      ,
      typename LENGTH_TYPE           = GLsizei*     ,
      typename PARAMS_TYPE           = GLint*       >
    class GetProgramResourceiv:
        public ge::core::Command,
        public at::Program         <PROGRAM_TYPE         >,
        public at::ProgramInterface<PROGRAMINTERFACE_TYPE>,
        public at::Index           <INDEX_TYPE           >,
        public at::PropCount       <PROPCOUNT_TYPE       >,
        public at::Props           <PROPS_TYPE           >,
        public at::BufSize         <BUFSIZE_TYPE         >,
        public at::Length          <LENGTH_TYPE          >,
        public at::Params          <PARAMS_TYPE          >{
      public:
        GetProgramResourceiv(
            PROGRAM_TYPE          const&program         ,
            PROGRAMINTERFACE_TYPE const&programInterface,
            INDEX_TYPE            const&index           ,
            PROPCOUNT_TYPE        const&propCount       ,
            PROPS_TYPE            const&props           ,
            BUFSIZE_TYPE          const&bufSize         ,
            LENGTH_TYPE           const&length          ,
            PARAMS_TYPE           const&params          ):
          at::Program         <PROGRAM_TYPE         >(program         ),
          at::ProgramInterface<PROGRAMINTERFACE_TYPE>(programInterface),
          at::Index           <INDEX_TYPE           >(index           ),
          at::PropCount       <PROPCOUNT_TYPE       >(propCount       ),
          at::Props           <PROPS_TYPE           >(props           ),
          at::BufSize         <BUFSIZE_TYPE         >(bufSize         ),
          at::Length          <LENGTH_TYPE          >(length          ),
          at::Params          <PARAMS_TYPE          >(params          ){}
        virtual~GetProgramResourceiv(){}
        virtual void operator()(){
          glGetProgramResourceiv(
            ge::core::convertTo<GLuint       >(this->at::Program         <PROGRAM_TYPE         >::_value),
            ge::core::convertTo<GLenum       >(this->at::ProgramInterface<PROGRAMINTERFACE_TYPE>::_value),
            ge::core::convertTo<GLuint       >(this->at::Index           <INDEX_TYPE           >::_value),
            ge::core::convertTo<GLsizei      >(this->at::PropCount       <PROPCOUNT_TYPE       >::_value),
            ge::core::convertTo<const GLenum*>(this->at::Props           <PROPS_TYPE           >::_value),
            ge::core::convertTo<GLsizei      >(this->at::BufSize         <BUFSIZE_TYPE         >::_value),
            ge::core::convertTo<GLsizei*     >(this->at::Length          <LENGTH_TYPE          >::_value),
            ge::core::convertTo<GLint*       >(this->at::Params          <PARAMS_TYPE          >::_value)
          );
        }
    };

    template<
      typename PROGRAM_TYPE      = GLuint  ,
      typename BUFSIZE_TYPE      = GLsizei ,
      typename LENGTH_TYPE       = GLsizei*,
      typename BINARYFORMAT_TYPE = GLenum* ,
      typename BINARY_TYPE       = void*   >
    class GetProgramBinary:
        public ge::core::Command,
        public at::Program     <PROGRAM_TYPE     >,
        public at::BufSize     <BUFSIZE_TYPE     >,
        public at::Length      <LENGTH_TYPE      >,
        public at::BinaryFormat<BINARYFORMAT_TYPE>,
        public at::Binary      <BINARY_TYPE      >{
      public:
        GetProgramBinary(
            PROGRAM_TYPE      const&program     ,
            BUFSIZE_TYPE      const&bufSize     ,
            LENGTH_TYPE       const&length      ,
            BINARYFORMAT_TYPE const&binaryFormat,
            BINARY_TYPE       const&binary      ):
          at::Program     <PROGRAM_TYPE     >(program     ),
          at::BufSize     <BUFSIZE_TYPE     >(bufSize     ),
          at::Length      <LENGTH_TYPE      >(length      ),
          at::BinaryFormat<BINARYFORMAT_TYPE>(binaryFormat),
          at::Binary      <BINARY_TYPE      >(binary      ){}
        virtual~GetProgramBinary(){}
        virtual void operator()(){
          glGetProgramBinary(
            ge::core::convertTo<GLuint  >(this->at::Program     <PROGRAM_TYPE     >::_value),
            ge::core::convertTo<GLsizei >(this->at::BufSize     <BUFSIZE_TYPE     >::_value),
            ge::core::convertTo<GLsizei*>(this->at::Length      <LENGTH_TYPE      >::_value),
            ge::core::convertTo<GLenum* >(this->at::BinaryFormat<BINARYFORMAT_TYPE>::_value),
            ge::core::convertTo<void*   >(this->at::Binary      <BINARY_TYPE      >::_value)
          );
        }
    };

    template<
      typename RET_TYPE = GLuint>
    class CreateProgram:
        public ge::core::Command,
        public at::Ret<RET_TYPE>{
      public:
        CreateProgram(
            RET_TYPE const&ret):
          at::Ret<RET_TYPE>(ret){}
        virtual~CreateProgram(){}
        virtual void operator()(){
          ge::core::convertFrom<GLuint>(this->at::Ret<RET_TYPE>::_value,glCreateProgram()
          );
        }
    };

    template<
      typename RET_TYPE              = GLint        ,
      typename PROGRAM_TYPE          = GLuint       ,
      typename PROGRAMINTERFACE_TYPE = GLenum       ,
      typename NAME_TYPE             = const GLchar*>
    class GetProgramResourceLocation:
        public ge::core::Command,
        public at::Ret             <RET_TYPE             >,
        public at::Program         <PROGRAM_TYPE         >,
        public at::ProgramInterface<PROGRAMINTERFACE_TYPE>,
        public at::Name            <NAME_TYPE            >{
      public:
        GetProgramResourceLocation(
            RET_TYPE              const&ret             ,
            PROGRAM_TYPE          const&program         ,
            PROGRAMINTERFACE_TYPE const&programInterface,
            NAME_TYPE             const&name            ):
          at::Ret             <RET_TYPE             >(ret             ),
          at::Program         <PROGRAM_TYPE         >(program         ),
          at::ProgramInterface<PROGRAMINTERFACE_TYPE>(programInterface),
          at::Name            <NAME_TYPE            >(name            ){}
        virtual~GetProgramResourceLocation(){}
        virtual void operator()(){
          ge::core::convertFrom<GLint>(this->at::Ret<RET_TYPE>::_value,glGetProgramResourceLocation(
              ge::core::convertTo<GLuint       >(this->at::Program         <PROGRAM_TYPE         >::_value),
              ge::core::convertTo<GLenum       >(this->at::ProgramInterface<PROGRAMINTERFACE_TYPE>::_value),
              ge::core::convertTo<const GLchar*>(this->at::Name            <NAME_TYPE            >::_value))
          );
        }
    };

    template<
      typename PROGRAM_TYPE = GLuint  ,
      typename BUFSIZE_TYPE = GLsizei ,
      typename LENGTH_TYPE  = GLsizei*,
      typename INFOLOG_TYPE = GLchar* >
    class GetProgramInfoLog:
        public ge::core::Command,
        public at::Program<PROGRAM_TYPE>,
        public at::BufSize<BUFSIZE_TYPE>,
        public at::Length <LENGTH_TYPE >,
        public at::InfoLog<INFOLOG_TYPE>{
      public:
        GetProgramInfoLog(
            PROGRAM_TYPE const&program,
            BUFSIZE_TYPE const&bufSize,
            LENGTH_TYPE  const&length ,
            INFOLOG_TYPE const&infoLog):
          at::Program<PROGRAM_TYPE>(program),
          at::BufSize<BUFSIZE_TYPE>(bufSize),
          at::Length <LENGTH_TYPE >(length ),
          at::InfoLog<INFOLOG_TYPE>(infoLog){}
        virtual~GetProgramInfoLog(){}
        virtual void operator()(){
          glGetProgramInfoLog(
            ge::core::convertTo<GLuint  >(this->at::Program<PROGRAM_TYPE>::_value),
            ge::core::convertTo<GLsizei >(this->at::BufSize<BUFSIZE_TYPE>::_value),
            ge::core::convertTo<GLsizei*>(this->at::Length <LENGTH_TYPE >::_value),
            ge::core::convertTo<GLchar* >(this->at::InfoLog<INFOLOG_TYPE>::_value)
          );
        }
    };

    template<
      typename PROGRAM_TYPE = GLuint>
    class ValidateProgram:
        public ge::core::Command,
        public at::Program<PROGRAM_TYPE>{
      public:
        ValidateProgram(
            PROGRAM_TYPE const&program):
          at::Program<PROGRAM_TYPE>(program){}
        virtual~ValidateProgram(){}
        virtual void operator()(){
          glValidateProgram(
            ge::core::convertTo<GLuint>(this->at::Program<PROGRAM_TYPE>::_value)
          );
        }
    };

    template<
      typename PROGRAM_TYPE    = GLuint,
      typename SHADERTYPE_TYPE = GLenum,
      typename PNAME_TYPE      = GLenum,
      typename VALUES_TYPE     = GLint*>
    class GetProgramStageiv:
        public ge::core::Command,
        public at::Program   <PROGRAM_TYPE   >,
        public at::Shadertype<SHADERTYPE_TYPE>,
        public at::Pname     <PNAME_TYPE     >,
        public at::Values    <VALUES_TYPE    >{
      public:
        GetProgramStageiv(
            PROGRAM_TYPE    const&program   ,
            SHADERTYPE_TYPE const&shadertype,
            PNAME_TYPE      const&pname     ,
            VALUES_TYPE     const&values    ):
          at::Program   <PROGRAM_TYPE   >(program   ),
          at::Shadertype<SHADERTYPE_TYPE>(shadertype),
          at::Pname     <PNAME_TYPE     >(pname     ),
          at::Values    <VALUES_TYPE    >(values    ){}
        virtual~GetProgramStageiv(){}
        virtual void operator()(){
          glGetProgramStageiv(
            ge::core::convertTo<GLuint>(this->at::Program   <PROGRAM_TYPE   >::_value),
            ge::core::convertTo<GLenum>(this->at::Shadertype<SHADERTYPE_TYPE>::_value),
            ge::core::convertTo<GLenum>(this->at::Pname     <PNAME_TYPE     >::_value),
            ge::core::convertTo<GLint*>(this->at::Values    <VALUES_TYPE    >::_value)
          );
        }
    };

    template<
      typename RET_TYPE     = GLboolean,
      typename PROGRAM_TYPE = GLuint   >
    class IsProgram:
        public ge::core::Command,
        public at::Ret    <RET_TYPE    >,
        public at::Program<PROGRAM_TYPE>{
      public:
        IsProgram(
            RET_TYPE     const&ret    ,
            PROGRAM_TYPE const&program):
          at::Ret    <RET_TYPE    >(ret    ),
          at::Program<PROGRAM_TYPE>(program){}
        virtual~IsProgram(){}
        virtual void operator()(){
          ge::core::convertFrom<GLboolean>(this->at::Ret<RET_TYPE>::_value,glIsProgram(
              ge::core::convertTo<GLuint   >(this->at::Program<PROGRAM_TYPE>::_value))
          );
        }
    };

    template<
      typename PROGRAM_TYPE          = GLuint,
      typename PROGRAMINTERFACE_TYPE = GLenum,
      typename PNAME_TYPE            = GLenum,
      typename PARAMS_TYPE           = GLint*>
    class GetProgramInterfaceiv:
        public ge::core::Command,
        public at::Program         <PROGRAM_TYPE         >,
        public at::ProgramInterface<PROGRAMINTERFACE_TYPE>,
        public at::Pname           <PNAME_TYPE           >,
        public at::Params          <PARAMS_TYPE          >{
      public:
        GetProgramInterfaceiv(
            PROGRAM_TYPE          const&program         ,
            PROGRAMINTERFACE_TYPE const&programInterface,
            PNAME_TYPE            const&pname           ,
            PARAMS_TYPE           const&params          ):
          at::Program         <PROGRAM_TYPE         >(program         ),
          at::ProgramInterface<PROGRAMINTERFACE_TYPE>(programInterface),
          at::Pname           <PNAME_TYPE           >(pname           ),
          at::Params          <PARAMS_TYPE          >(params          ){}
        virtual~GetProgramInterfaceiv(){}
        virtual void operator()(){
          glGetProgramInterfaceiv(
            ge::core::convertTo<GLuint>(this->at::Program         <PROGRAM_TYPE         >::_value),
            ge::core::convertTo<GLenum>(this->at::ProgramInterface<PROGRAMINTERFACE_TYPE>::_value),
            ge::core::convertTo<GLenum>(this->at::Pname           <PNAME_TYPE           >::_value),
            ge::core::convertTo<GLint*>(this->at::Params          <PARAMS_TYPE          >::_value)
          );
        }
    };

    template<
      typename PROGRAM_TYPE = GLuint,
      typename PNAME_TYPE   = GLenum,
      typename PARAMS_TYPE  = GLint*>
    class GetProgramiv:
        public ge::core::Command,
        public at::Program<PROGRAM_TYPE>,
        public at::Pname  <PNAME_TYPE  >,
        public at::Params <PARAMS_TYPE >{
      public:
        GetProgramiv(
            PROGRAM_TYPE const&program,
            PNAME_TYPE   const&pname  ,
            PARAMS_TYPE  const&params ):
          at::Program<PROGRAM_TYPE>(program),
          at::Pname  <PNAME_TYPE  >(pname  ),
          at::Params <PARAMS_TYPE >(params ){}
        virtual~GetProgramiv(){}
        virtual void operator()(){
          glGetProgramiv(
            ge::core::convertTo<GLuint>(this->at::Program<PROGRAM_TYPE>::_value),
            ge::core::convertTo<GLenum>(this->at::Pname  <PNAME_TYPE  >::_value),
            ge::core::convertTo<GLint*>(this->at::Params <PARAMS_TYPE >::_value)
          );
        }
    };

    template<
      typename PIPELINE_TYPE = GLuint,
      typename PROGRAM_TYPE  = GLuint>
    class ActiveShaderProgram:
        public ge::core::Command,
        public at::Pipeline<PIPELINE_TYPE>,
        public at::Program <PROGRAM_TYPE >{
      public:
        ActiveShaderProgram(
            PIPELINE_TYPE const&pipeline,
            PROGRAM_TYPE  const&program ):
          at::Pipeline<PIPELINE_TYPE>(pipeline),
          at::Program <PROGRAM_TYPE >(program ){}
        virtual~ActiveShaderProgram(){}
        virtual void operator()(){
          glActiveShaderProgram(
            ge::core::convertTo<GLuint>(this->at::Pipeline<PIPELINE_TYPE>::_value),
            ge::core::convertTo<GLuint>(this->at::Program <PROGRAM_TYPE >::_value)
          );
        }
    };

    template<
      typename RET_TYPE              = GLuint       ,
      typename PROGRAM_TYPE          = GLuint       ,
      typename PROGRAMINTERFACE_TYPE = GLenum       ,
      typename NAME_TYPE             = const GLchar*>
    class GetProgramResourceIndex:
        public ge::core::Command,
        public at::Ret             <RET_TYPE             >,
        public at::Program         <PROGRAM_TYPE         >,
        public at::ProgramInterface<PROGRAMINTERFACE_TYPE>,
        public at::Name            <NAME_TYPE            >{
      public:
        GetProgramResourceIndex(
            RET_TYPE              const&ret             ,
            PROGRAM_TYPE          const&program         ,
            PROGRAMINTERFACE_TYPE const&programInterface,
            NAME_TYPE             const&name            ):
          at::Ret             <RET_TYPE             >(ret             ),
          at::Program         <PROGRAM_TYPE         >(program         ),
          at::ProgramInterface<PROGRAMINTERFACE_TYPE>(programInterface),
          at::Name            <NAME_TYPE            >(name            ){}
        virtual~GetProgramResourceIndex(){}
        virtual void operator()(){
          ge::core::convertFrom<GLuint>(this->at::Ret<RET_TYPE>::_value,glGetProgramResourceIndex(
              ge::core::convertTo<GLuint       >(this->at::Program         <PROGRAM_TYPE         >::_value),
              ge::core::convertTo<GLenum       >(this->at::ProgramInterface<PROGRAMINTERFACE_TYPE>::_value),
              ge::core::convertTo<const GLchar*>(this->at::Name            <NAME_TYPE            >::_value))
          );
        }
    };

    template<
      typename PROGRAM_TYPE = GLuint>
    class LinkProgram:
        public ge::core::Command,
        public at::Program<PROGRAM_TYPE>{
      public:
        LinkProgram(
            PROGRAM_TYPE const&program):
          at::Program<PROGRAM_TYPE>(program){}
        virtual~LinkProgram(){}
        virtual void operator()(){
          glLinkProgram(
            ge::core::convertTo<GLuint>(this->at::Program<PROGRAM_TYPE>::_value)
          );
        }
    };

    template<
      typename RET_TYPE              = GLint        ,
      typename PROGRAM_TYPE          = GLuint       ,
      typename PROGRAMINTERFACE_TYPE = GLenum       ,
      typename NAME_TYPE             = const GLchar*>
    class GetProgramResourceLocationIndex:
        public ge::core::Command,
        public at::Ret             <RET_TYPE             >,
        public at::Program         <PROGRAM_TYPE         >,
        public at::ProgramInterface<PROGRAMINTERFACE_TYPE>,
        public at::Name            <NAME_TYPE            >{
      public:
        GetProgramResourceLocationIndex(
            RET_TYPE              const&ret             ,
            PROGRAM_TYPE          const&program         ,
            PROGRAMINTERFACE_TYPE const&programInterface,
            NAME_TYPE             const&name            ):
          at::Ret             <RET_TYPE             >(ret             ),
          at::Program         <PROGRAM_TYPE         >(program         ),
          at::ProgramInterface<PROGRAMINTERFACE_TYPE>(programInterface),
          at::Name            <NAME_TYPE            >(name            ){}
        virtual~GetProgramResourceLocationIndex(){}
        virtual void operator()(){
          ge::core::convertFrom<GLint>(this->at::Ret<RET_TYPE>::_value,glGetProgramResourceLocationIndex(
              ge::core::convertTo<GLuint       >(this->at::Program         <PROGRAM_TYPE         >::_value),
              ge::core::convertTo<GLenum       >(this->at::ProgramInterface<PROGRAMINTERFACE_TYPE>::_value),
              ge::core::convertTo<const GLchar*>(this->at::Name            <NAME_TYPE            >::_value))
          );
        }
    };

    template<
      typename RET_TYPE     = GLuint             ,
      typename TYPE_TYPE    = GLenum             ,
      typename COUNT_TYPE   = GLsizei            ,
      typename STRINGS_TYPE = const GLchar*const*>
    class CreateShaderProgramv:
        public ge::core::Command,
        public at::Ret    <RET_TYPE    >,
        public at::Type   <TYPE_TYPE   >,
        public at::Count  <COUNT_TYPE  >,
        public at::Strings<STRINGS_TYPE>{
      public:
        CreateShaderProgramv(
            RET_TYPE     const&ret    ,
            TYPE_TYPE    const&type   ,
            COUNT_TYPE   const&count  ,
            STRINGS_TYPE const&strings):
          at::Ret    <RET_TYPE    >(ret    ),
          at::Type   <TYPE_TYPE   >(type   ),
          at::Count  <COUNT_TYPE  >(count  ),
          at::Strings<STRINGS_TYPE>(strings){}
        virtual~CreateShaderProgramv(){}
        virtual void operator()(){
          ge::core::convertFrom<GLuint>(this->at::Ret<RET_TYPE>::_value,glCreateShaderProgramv(
              ge::core::convertTo<GLenum             >(this->at::Type   <TYPE_TYPE   >::_value),
              ge::core::convertTo<GLsizei            >(this->at::Count  <COUNT_TYPE  >::_value),
              ge::core::convertTo<const GLchar*const*>(this->at::Strings<STRINGS_TYPE>::_value))
          );
        }
    };

    template<
      typename PROGRAM_TYPE          = GLuint  ,
      typename PROGRAMINTERFACE_TYPE = GLenum  ,
      typename INDEX_TYPE            = GLuint  ,
      typename BUFSIZE_TYPE          = GLsizei ,
      typename LENGTH_TYPE           = GLsizei*,
      typename NAME_TYPE             = GLchar* >
    class GetProgramResourceName:
        public ge::core::Command,
        public at::Program         <PROGRAM_TYPE         >,
        public at::ProgramInterface<PROGRAMINTERFACE_TYPE>,
        public at::Index           <INDEX_TYPE           >,
        public at::BufSize         <BUFSIZE_TYPE         >,
        public at::Length          <LENGTH_TYPE          >,
        public at::Name            <NAME_TYPE            >{
      public:
        GetProgramResourceName(
            PROGRAM_TYPE          const&program         ,
            PROGRAMINTERFACE_TYPE const&programInterface,
            INDEX_TYPE            const&index           ,
            BUFSIZE_TYPE          const&bufSize         ,
            LENGTH_TYPE           const&length          ,
            NAME_TYPE             const&name            ):
          at::Program         <PROGRAM_TYPE         >(program         ),
          at::ProgramInterface<PROGRAMINTERFACE_TYPE>(programInterface),
          at::Index           <INDEX_TYPE           >(index           ),
          at::BufSize         <BUFSIZE_TYPE         >(bufSize         ),
          at::Length          <LENGTH_TYPE          >(length          ),
          at::Name            <NAME_TYPE            >(name            ){}
        virtual~GetProgramResourceName(){}
        virtual void operator()(){
          glGetProgramResourceName(
            ge::core::convertTo<GLuint  >(this->at::Program         <PROGRAM_TYPE         >::_value),
            ge::core::convertTo<GLenum  >(this->at::ProgramInterface<PROGRAMINTERFACE_TYPE>::_value),
            ge::core::convertTo<GLuint  >(this->at::Index           <INDEX_TYPE           >::_value),
            ge::core::convertTo<GLsizei >(this->at::BufSize         <BUFSIZE_TYPE         >::_value),
            ge::core::convertTo<GLsizei*>(this->at::Length          <LENGTH_TYPE          >::_value),
            ge::core::convertTo<GLchar* >(this->at::Name            <NAME_TYPE            >::_value)
          );
        }
    };

    template<
      typename PROGRAM_TYPE      = GLuint     ,
      typename BINARYFORMAT_TYPE = GLenum     ,
      typename BINARY_TYPE       = const void*,
      typename LENGTH_TYPE       = GLsizei    >
    class ProgramBinary:
        public ge::core::Command,
        public at::Program     <PROGRAM_TYPE     >,
        public at::BinaryFormat<BINARYFORMAT_TYPE>,
        public at::Binary      <BINARY_TYPE      >,
        public at::Length      <LENGTH_TYPE      >{
      public:
        ProgramBinary(
            PROGRAM_TYPE      const&program     ,
            BINARYFORMAT_TYPE const&binaryFormat,
            BINARY_TYPE       const&binary      ,
            LENGTH_TYPE       const&length      ):
          at::Program     <PROGRAM_TYPE     >(program     ),
          at::BinaryFormat<BINARYFORMAT_TYPE>(binaryFormat),
          at::Binary      <BINARY_TYPE      >(binary      ),
          at::Length      <LENGTH_TYPE      >(length      ){}
        virtual~ProgramBinary(){}
        virtual void operator()(){
          glProgramBinary(
            ge::core::convertTo<GLuint     >(this->at::Program     <PROGRAM_TYPE     >::_value),
            ge::core::convertTo<GLenum     >(this->at::BinaryFormat<BINARYFORMAT_TYPE>::_value),
            ge::core::convertTo<const void*>(this->at::Binary      <BINARY_TYPE      >::_value),
            ge::core::convertTo<GLsizei    >(this->at::Length      <LENGTH_TYPE      >::_value)
          );
        }
    };

    template<
      typename PIPELINE_TYPE = GLuint    ,
      typename STAGES_TYPE   = GLbitfield,
      typename PROGRAM_TYPE  = GLuint    >
    class UseProgramStages:
        public ge::core::Command,
        public at::Pipeline<PIPELINE_TYPE>,
        public at::Stages  <STAGES_TYPE  >,
        public at::Program <PROGRAM_TYPE >{
      public:
        UseProgramStages(
            PIPELINE_TYPE const&pipeline,
            STAGES_TYPE   const&stages  ,
            PROGRAM_TYPE  const&program ):
          at::Pipeline<PIPELINE_TYPE>(pipeline),
          at::Stages  <STAGES_TYPE  >(stages  ),
          at::Program <PROGRAM_TYPE >(program ){}
        virtual~UseProgramStages(){}
        virtual void operator()(){
          glUseProgramStages(
            ge::core::convertTo<GLuint    >(this->at::Pipeline<PIPELINE_TYPE>::_value),
            ge::core::convertTo<GLbitfield>(this->at::Stages  <STAGES_TYPE  >::_value),
            ge::core::convertTo<GLuint    >(this->at::Program <PROGRAM_TYPE >::_value)
          );
        }
    };

    template<
      typename PROGRAM_TYPE = GLuint>
    class DeleteProgram:
        public ge::core::Command,
        public at::Program<PROGRAM_TYPE>{
      public:
        DeleteProgram(
            PROGRAM_TYPE const&program):
          at::Program<PROGRAM_TYPE>(program){}
        virtual~DeleteProgram(){}
        virtual void operator()(){
          glDeleteProgram(
            ge::core::convertTo<GLuint>(this->at::Program<PROGRAM_TYPE>::_value)
          );
        }
    };

    template<
      typename PROGRAM_TYPE = GLuint,
      typename PNAME_TYPE   = GLenum,
      typename VALUE_TYPE   = GLint >
    class ProgramParameteri:
        public ge::core::Command,
        public at::Program<PROGRAM_TYPE>,
        public at::Pname  <PNAME_TYPE  >,
        public at::Value  <VALUE_TYPE  >{
      public:
        ProgramParameteri(
            PROGRAM_TYPE const&program,
            PNAME_TYPE   const&pname  ,
            VALUE_TYPE   const&value  ):
          at::Program<PROGRAM_TYPE>(program),
          at::Pname  <PNAME_TYPE  >(pname  ),
          at::Value  <VALUE_TYPE  >(value  ){}
        virtual~ProgramParameteri(){}
        virtual void operator()(){
          glProgramParameteri(
            ge::core::convertTo<GLuint>(this->at::Program<PROGRAM_TYPE>::_value),
            ge::core::convertTo<GLenum>(this->at::Pname  <PNAME_TYPE  >::_value),
            ge::core::convertTo<GLint >(this->at::Value  <VALUE_TYPE  >::_value)
          );
        }
    };

    template<
      typename PROGRAM_TYPE = GLuint>
    inline UseProgram<
      PROGRAM_TYPE>* newUseProgram(
        PROGRAM_TYPE const&program){
        return new UseProgram<
          PROGRAM_TYPE>(
              program);
    }
    template<
      typename PROGRAM_TYPE          = GLuint       ,
      typename PROGRAMINTERFACE_TYPE = GLenum       ,
      typename INDEX_TYPE            = GLuint       ,
      typename PROPCOUNT_TYPE        = GLsizei      ,
      typename PROPS_TYPE            = const GLenum*,
      typename BUFSIZE_TYPE          = GLsizei      ,
      typename LENGTH_TYPE           = GLsizei*     ,
      typename PARAMS_TYPE           = GLint*       >
    inline GetProgramResourceiv<
      PROGRAM_TYPE         ,
      PROGRAMINTERFACE_TYPE,
      INDEX_TYPE           ,
      PROPCOUNT_TYPE       ,
      PROPS_TYPE           ,
      BUFSIZE_TYPE         ,
      LENGTH_TYPE          ,
      PARAMS_TYPE          >* newGetProgramResourceiv(
        PROGRAM_TYPE          const&program         ,
        PROGRAMINTERFACE_TYPE const&programInterface,
        INDEX_TYPE            const&index           ,
        PROPCOUNT_TYPE        const&propCount       ,
        PROPS_TYPE            const&props           ,
        BUFSIZE_TYPE          const&bufSize         ,
        LENGTH_TYPE           const&length          ,
        PARAMS_TYPE           const&params          ){
        return new GetProgramResourceiv<
          PROGRAM_TYPE         ,
          PROGRAMINTERFACE_TYPE,
          INDEX_TYPE           ,
          PROPCOUNT_TYPE       ,
          PROPS_TYPE           ,
          BUFSIZE_TYPE         ,
          LENGTH_TYPE          ,
          PARAMS_TYPE          >(
              program         ,
              programInterface,
              index           ,
              propCount       ,
              props           ,
              bufSize         ,
              length          ,
              params          );
    }
    template<
      typename PROGRAM_TYPE      = GLuint  ,
      typename BUFSIZE_TYPE      = GLsizei ,
      typename LENGTH_TYPE       = GLsizei*,
      typename BINARYFORMAT_TYPE = GLenum* ,
      typename BINARY_TYPE       = void*   >
    inline GetProgramBinary<
      PROGRAM_TYPE     ,
      BUFSIZE_TYPE     ,
      LENGTH_TYPE      ,
      BINARYFORMAT_TYPE,
      BINARY_TYPE      >* newGetProgramBinary(
        PROGRAM_TYPE      const&program     ,
        BUFSIZE_TYPE      const&bufSize     ,
        LENGTH_TYPE       const&length      ,
        BINARYFORMAT_TYPE const&binaryFormat,
        BINARY_TYPE       const&binary      ){
        return new GetProgramBinary<
          PROGRAM_TYPE     ,
          BUFSIZE_TYPE     ,
          LENGTH_TYPE      ,
          BINARYFORMAT_TYPE,
          BINARY_TYPE      >(
              program     ,
              bufSize     ,
              length      ,
              binaryFormat,
              binary      );
    }
    template<
      typename RET_TYPE = GLuint>
    inline CreateProgram<
      RET_TYPE>* newCreateProgram(
        RET_TYPE const&ret){
        return new CreateProgram<
          RET_TYPE>(
              ret);
    }
    template<
      typename RET_TYPE              = GLint        ,
      typename PROGRAM_TYPE          = GLuint       ,
      typename PROGRAMINTERFACE_TYPE = GLenum       ,
      typename NAME_TYPE             = const GLchar*>
    inline GetProgramResourceLocation<
      RET_TYPE             ,
      PROGRAM_TYPE         ,
      PROGRAMINTERFACE_TYPE,
      NAME_TYPE            >* newGetProgramResourceLocation(
        RET_TYPE              const&ret             ,
        PROGRAM_TYPE          const&program         ,
        PROGRAMINTERFACE_TYPE const&programInterface,
        NAME_TYPE             const&name            ){
        return new GetProgramResourceLocation<
          RET_TYPE             ,
          PROGRAM_TYPE         ,
          PROGRAMINTERFACE_TYPE,
          NAME_TYPE            >(
              ret             ,
              program         ,
              programInterface,
              name            );
    }
    template<
      typename PROGRAM_TYPE = GLuint  ,
      typename BUFSIZE_TYPE = GLsizei ,
      typename LENGTH_TYPE  = GLsizei*,
      typename INFOLOG_TYPE = GLchar* >
    inline GetProgramInfoLog<
      PROGRAM_TYPE,
      BUFSIZE_TYPE,
      LENGTH_TYPE ,
      INFOLOG_TYPE>* newGetProgramInfoLog(
        PROGRAM_TYPE const&program,
        BUFSIZE_TYPE const&bufSize,
        LENGTH_TYPE  const&length ,
        INFOLOG_TYPE const&infoLog){
        return new GetProgramInfoLog<
          PROGRAM_TYPE,
          BUFSIZE_TYPE,
          LENGTH_TYPE ,
          INFOLOG_TYPE>(
              program,
              bufSize,
              length ,
              infoLog);
    }
    template<
      typename PROGRAM_TYPE = GLuint>
    inline ValidateProgram<
      PROGRAM_TYPE>* newValidateProgram(
        PROGRAM_TYPE const&program){
        return new ValidateProgram<
          PROGRAM_TYPE>(
              program);
    }
    template<
      typename PROGRAM_TYPE    = GLuint,
      typename SHADERTYPE_TYPE = GLenum,
      typename PNAME_TYPE      = GLenum,
      typename VALUES_TYPE     = GLint*>
    inline GetProgramStageiv<
      PROGRAM_TYPE   ,
      SHADERTYPE_TYPE,
      PNAME_TYPE     ,
      VALUES_TYPE    >* newGetProgramStageiv(
        PROGRAM_TYPE    const&program   ,
        SHADERTYPE_TYPE const&shadertype,
        PNAME_TYPE      const&pname     ,
        VALUES_TYPE     const&values    ){
        return new GetProgramStageiv<
          PROGRAM_TYPE   ,
          SHADERTYPE_TYPE,
          PNAME_TYPE     ,
          VALUES_TYPE    >(
              program   ,
              shadertype,
              pname     ,
              values    );
    }
    template<
      typename RET_TYPE     = GLboolean,
      typename PROGRAM_TYPE = GLuint   >
    inline IsProgram<
      RET_TYPE    ,
      PROGRAM_TYPE>* newIsProgram(
        RET_TYPE     const&ret    ,
        PROGRAM_TYPE const&program){
        return new IsProgram<
          RET_TYPE    ,
          PROGRAM_TYPE>(
              ret    ,
              program);
    }
    template<
      typename PROGRAM_TYPE          = GLuint,
      typename PROGRAMINTERFACE_TYPE = GLenum,
      typename PNAME_TYPE            = GLenum,
      typename PARAMS_TYPE           = GLint*>
    inline GetProgramInterfaceiv<
      PROGRAM_TYPE         ,
      PROGRAMINTERFACE_TYPE,
      PNAME_TYPE           ,
      PARAMS_TYPE          >* newGetProgramInterfaceiv(
        PROGRAM_TYPE          const&program         ,
        PROGRAMINTERFACE_TYPE const&programInterface,
        PNAME_TYPE            const&pname           ,
        PARAMS_TYPE           const&params          ){
        return new GetProgramInterfaceiv<
          PROGRAM_TYPE         ,
          PROGRAMINTERFACE_TYPE,
          PNAME_TYPE           ,
          PARAMS_TYPE          >(
              program         ,
              programInterface,
              pname           ,
              params          );
    }
    template<
      typename PROGRAM_TYPE = GLuint,
      typename PNAME_TYPE   = GLenum,
      typename PARAMS_TYPE  = GLint*>
    inline GetProgramiv<
      PROGRAM_TYPE,
      PNAME_TYPE  ,
      PARAMS_TYPE >* newGetProgramiv(
        PROGRAM_TYPE const&program,
        PNAME_TYPE   const&pname  ,
        PARAMS_TYPE  const&params ){
        return new GetProgramiv<
          PROGRAM_TYPE,
          PNAME_TYPE  ,
          PARAMS_TYPE >(
              program,
              pname  ,
              params );
    }
    template<
      typename PIPELINE_TYPE = GLuint,
      typename PROGRAM_TYPE  = GLuint>
    inline ActiveShaderProgram<
      PIPELINE_TYPE,
      PROGRAM_TYPE >* newActiveShaderProgram(
        PIPELINE_TYPE const&pipeline,
        PROGRAM_TYPE  const&program ){
        return new ActiveShaderProgram<
          PIPELINE_TYPE,
          PROGRAM_TYPE >(
              pipeline,
              program );
    }
    template<
      typename RET_TYPE              = GLuint       ,
      typename PROGRAM_TYPE          = GLuint       ,
      typename PROGRAMINTERFACE_TYPE = GLenum       ,
      typename NAME_TYPE             = const GLchar*>
    inline GetProgramResourceIndex<
      RET_TYPE             ,
      PROGRAM_TYPE         ,
      PROGRAMINTERFACE_TYPE,
      NAME_TYPE            >* newGetProgramResourceIndex(
        RET_TYPE              const&ret             ,
        PROGRAM_TYPE          const&program         ,
        PROGRAMINTERFACE_TYPE const&programInterface,
        NAME_TYPE             const&name            ){
        return new GetProgramResourceIndex<
          RET_TYPE             ,
          PROGRAM_TYPE         ,
          PROGRAMINTERFACE_TYPE,
          NAME_TYPE            >(
              ret             ,
              program         ,
              programInterface,
              name            );
    }
    template<
      typename PROGRAM_TYPE = GLuint>
    inline LinkProgram<
      PROGRAM_TYPE>* newLinkProgram(
        PROGRAM_TYPE const&program){
        return new LinkProgram<
          PROGRAM_TYPE>(
              program);
    }
    template<
      typename RET_TYPE              = GLint        ,
      typename PROGRAM_TYPE          = GLuint       ,
      typename PROGRAMINTERFACE_TYPE = GLenum       ,
      typename NAME_TYPE             = const GLchar*>
    inline GetProgramResourceLocationIndex<
      RET_TYPE             ,
      PROGRAM_TYPE         ,
      PROGRAMINTERFACE_TYPE,
      NAME_TYPE            >* newGetProgramResourceLocationIndex(
        RET_TYPE              const&ret             ,
        PROGRAM_TYPE          const&program         ,
        PROGRAMINTERFACE_TYPE const&programInterface,
        NAME_TYPE             const&name            ){
        return new GetProgramResourceLocationIndex<
          RET_TYPE             ,
          PROGRAM_TYPE         ,
          PROGRAMINTERFACE_TYPE,
          NAME_TYPE            >(
              ret             ,
              program         ,
              programInterface,
              name            );
    }
    template<
      typename RET_TYPE     = GLuint             ,
      typename TYPE_TYPE    = GLenum             ,
      typename COUNT_TYPE   = GLsizei            ,
      typename STRINGS_TYPE = const GLchar*const*>
    inline CreateShaderProgramv<
      RET_TYPE    ,
      TYPE_TYPE   ,
      COUNT_TYPE  ,
      STRINGS_TYPE>* newCreateShaderProgramv(
        RET_TYPE     const&ret    ,
        TYPE_TYPE    const&type   ,
        COUNT_TYPE   const&count  ,
        STRINGS_TYPE const&strings){
        return new CreateShaderProgramv<
          RET_TYPE    ,
          TYPE_TYPE   ,
          COUNT_TYPE  ,
          STRINGS_TYPE>(
              ret    ,
              type   ,
              count  ,
              strings);
    }
    template<
      typename PROGRAM_TYPE          = GLuint  ,
      typename PROGRAMINTERFACE_TYPE = GLenum  ,
      typename INDEX_TYPE            = GLuint  ,
      typename BUFSIZE_TYPE          = GLsizei ,
      typename LENGTH_TYPE           = GLsizei*,
      typename NAME_TYPE             = GLchar* >
    inline GetProgramResourceName<
      PROGRAM_TYPE         ,
      PROGRAMINTERFACE_TYPE,
      INDEX_TYPE           ,
      BUFSIZE_TYPE         ,
      LENGTH_TYPE          ,
      NAME_TYPE            >* newGetProgramResourceName(
        PROGRAM_TYPE          const&program         ,
        PROGRAMINTERFACE_TYPE const&programInterface,
        INDEX_TYPE            const&index           ,
        BUFSIZE_TYPE          const&bufSize         ,
        LENGTH_TYPE           const&length          ,
        NAME_TYPE             const&name            ){
        return new GetProgramResourceName<
          PROGRAM_TYPE         ,
          PROGRAMINTERFACE_TYPE,
          INDEX_TYPE           ,
          BUFSIZE_TYPE         ,
          LENGTH_TYPE          ,
          NAME_TYPE            >(
              program         ,
              programInterface,
              index           ,
              bufSize         ,
              length          ,
              name            );
    }
    template<
      typename PROGRAM_TYPE      = GLuint     ,
      typename BINARYFORMAT_TYPE = GLenum     ,
      typename BINARY_TYPE       = const void*,
      typename LENGTH_TYPE       = GLsizei    >
    inline ProgramBinary<
      PROGRAM_TYPE     ,
      BINARYFORMAT_TYPE,
      BINARY_TYPE      ,
      LENGTH_TYPE      >* newProgramBinary(
        PROGRAM_TYPE      const&program     ,
        BINARYFORMAT_TYPE const&binaryFormat,
        BINARY_TYPE       const&binary      ,
        LENGTH_TYPE       const&length      ){
        return new ProgramBinary<
          PROGRAM_TYPE     ,
          BINARYFORMAT_TYPE,
          BINARY_TYPE      ,
          LENGTH_TYPE      >(
              program     ,
              binaryFormat,
              binary      ,
              length      );
    }
    template<
      typename PIPELINE_TYPE = GLuint    ,
      typename STAGES_TYPE   = GLbitfield,
      typename PROGRAM_TYPE  = GLuint    >
    inline UseProgramStages<
      PIPELINE_TYPE,
      STAGES_TYPE  ,
      PROGRAM_TYPE >* newUseProgramStages(
        PIPELINE_TYPE const&pipeline,
        STAGES_TYPE   const&stages  ,
        PROGRAM_TYPE  const&program ){
        return new UseProgramStages<
          PIPELINE_TYPE,
          STAGES_TYPE  ,
          PROGRAM_TYPE >(
              pipeline,
              stages  ,
              program );
    }
    template<
      typename PROGRAM_TYPE = GLuint>
    inline DeleteProgram<
      PROGRAM_TYPE>* newDeleteProgram(
        PROGRAM_TYPE const&program){
        return new DeleteProgram<
          PROGRAM_TYPE>(
              program);
    }
    template<
      typename PROGRAM_TYPE = GLuint,
      typename PNAME_TYPE   = GLenum,
      typename VALUE_TYPE   = GLint >
    inline ProgramParameteri<
      PROGRAM_TYPE,
      PNAME_TYPE  ,
      VALUE_TYPE  >* newProgramParameteri(
        PROGRAM_TYPE const&program,
        PNAME_TYPE   const&pname  ,
        VALUE_TYPE   const&value  ){
        return new ProgramParameteri<
          PROGRAM_TYPE,
          PNAME_TYPE  ,
          VALUE_TYPE  >(
              program,
              pname  ,
              value  );
    }
  }
}
