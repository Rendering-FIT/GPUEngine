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
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program")return(void*)&this->program;
          return NULL;
        }
      public:
        PROGRAM_TYPE program;
        UseProgram(
            PROGRAM_TYPE const&program){
          this->program = program;
        }
        virtual~UseProgram(){}
        virtual void operator()(){
          glUseProgram(
            ge::core::convertTo<GLuint>(this->program)
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
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program"         )return(void*)&this->program         ;
          if(name == "programInterface")return(void*)&this->programInterface;
          if(name == "index"           )return(void*)&this->index           ;
          if(name == "propCount"       )return(void*)&this->propCount       ;
          if(name == "props"           )return(void*)&this->props           ;
          if(name == "bufSize"         )return(void*)&this->bufSize         ;
          if(name == "length"          )return(void*)&this->length          ;
          if(name == "params"          )return(void*)&this->params          ;
          return NULL;
        }
      public:
        PROGRAM_TYPE          program         ;
        PROGRAMINTERFACE_TYPE programInterface;
        INDEX_TYPE            index           ;
        PROPCOUNT_TYPE        propCount       ;
        PROPS_TYPE            props           ;
        BUFSIZE_TYPE          bufSize         ;
        LENGTH_TYPE           length          ;
        PARAMS_TYPE           params          ;
        GetProgramResourceiv(
            PROGRAM_TYPE          const&program         ,
            PROGRAMINTERFACE_TYPE const&programInterface,
            INDEX_TYPE            const&index           ,
            PROPCOUNT_TYPE        const&propCount       ,
            PROPS_TYPE            const&props           ,
            BUFSIZE_TYPE          const&bufSize         ,
            LENGTH_TYPE           const&length          ,
            PARAMS_TYPE           const&params          ){
          this->program          = program         ;
          this->programInterface = programInterface;
          this->index            = index           ;
          this->propCount        = propCount       ;
          this->props            = props           ;
          this->bufSize          = bufSize         ;
          this->length           = length          ;
          this->params           = params          ;
        }
        virtual~GetProgramResourceiv(){}
        virtual void operator()(){
          glGetProgramResourceiv(
            ge::core::convertTo<GLuint       >(this->program         ),
            ge::core::convertTo<GLenum       >(this->programInterface),
            ge::core::convertTo<GLuint       >(this->index           ),
            ge::core::convertTo<GLsizei      >(this->propCount       ),
            ge::core::convertTo<const GLenum*>(this->props           ),
            ge::core::convertTo<GLsizei      >(this->bufSize         ),
            ge::core::convertTo<GLsizei*     >(this->length          ),
            ge::core::convertTo<GLint*       >(this->params          )
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
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program"     )return(void*)&this->program     ;
          if(name == "bufSize"     )return(void*)&this->bufSize     ;
          if(name == "length"      )return(void*)&this->length      ;
          if(name == "binaryFormat")return(void*)&this->binaryFormat;
          if(name == "binary"      )return(void*)&this->binary      ;
          return NULL;
        }
      public:
        PROGRAM_TYPE      program     ;
        BUFSIZE_TYPE      bufSize     ;
        LENGTH_TYPE       length      ;
        BINARYFORMAT_TYPE binaryFormat;
        BINARY_TYPE       binary      ;
        GetProgramBinary(
            PROGRAM_TYPE      const&program     ,
            BUFSIZE_TYPE      const&bufSize     ,
            LENGTH_TYPE       const&length      ,
            BINARYFORMAT_TYPE const&binaryFormat,
            BINARY_TYPE       const&binary      ){
          this->program      = program     ;
          this->bufSize      = bufSize     ;
          this->length       = length      ;
          this->binaryFormat = binaryFormat;
          this->binary       = binary      ;
        }
        virtual~GetProgramBinary(){}
        virtual void operator()(){
          glGetProgramBinary(
            ge::core::convertTo<GLuint  >(this->program     ),
            ge::core::convertTo<GLsizei >(this->bufSize     ),
            ge::core::convertTo<GLsizei*>(this->length      ),
            ge::core::convertTo<GLenum* >(this->binaryFormat),
            ge::core::convertTo<void*   >(this->binary      )
          );
        }
    };

    template<
      typename RET_TYPE = GLuint>
    class CreateProgram:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "ret")return(void*)&this->ret;
          return NULL;
        }
      public:
        RET_TYPE ret;
        CreateProgram(
            RET_TYPE const&ret){
          this->ret = ret;
        }
        virtual~CreateProgram(){}
        virtual void operator()(){
          ge::core::convertFrom<GLuint>(this->ret,glCreateProgram()
          );
        }
    };

    template<
      typename RET_TYPE              = GLint        ,
      typename PROGRAM_TYPE          = GLuint       ,
      typename PROGRAMINTERFACE_TYPE = GLenum       ,
      typename NAME_TYPE             = const GLchar*>
    class GetProgramResourceLocation:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "ret"             )return(void*)&this->ret             ;
          if(name == "program"         )return(void*)&this->program         ;
          if(name == "programInterface")return(void*)&this->programInterface;
          if(name == "name"            )return(void*)&this->name            ;
          return NULL;
        }
      public:
        RET_TYPE              ret             ;
        PROGRAM_TYPE          program         ;
        PROGRAMINTERFACE_TYPE programInterface;
        NAME_TYPE             name            ;
        GetProgramResourceLocation(
            RET_TYPE              const&ret             ,
            PROGRAM_TYPE          const&program         ,
            PROGRAMINTERFACE_TYPE const&programInterface,
            NAME_TYPE             const&name            ){
          this->ret              = ret             ;
          this->program          = program         ;
          this->programInterface = programInterface;
          this->name             = name            ;
        }
        virtual~GetProgramResourceLocation(){}
        virtual void operator()(){
          ge::core::convertFrom<GLint>(this->ret,glGetProgramResourceLocation(
              ge::core::convertTo<GLuint       >(this->program         ),
              ge::core::convertTo<GLenum       >(this->programInterface),
              ge::core::convertTo<const GLchar*>(this->name            ))
          );
        }
    };

    template<
      typename PROGRAM_TYPE = GLuint  ,
      typename BUFSIZE_TYPE = GLsizei ,
      typename LENGTH_TYPE  = GLsizei*,
      typename INFOLOG_TYPE = GLchar* >
    class GetProgramInfoLog:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program")return(void*)&this->program;
          if(name == "bufSize")return(void*)&this->bufSize;
          if(name == "length" )return(void*)&this->length ;
          if(name == "infoLog")return(void*)&this->infoLog;
          return NULL;
        }
      public:
        PROGRAM_TYPE program;
        BUFSIZE_TYPE bufSize;
        LENGTH_TYPE  length ;
        INFOLOG_TYPE infoLog;
        GetProgramInfoLog(
            PROGRAM_TYPE const&program,
            BUFSIZE_TYPE const&bufSize,
            LENGTH_TYPE  const&length ,
            INFOLOG_TYPE const&infoLog){
          this->program = program;
          this->bufSize = bufSize;
          this->length  = length ;
          this->infoLog = infoLog;
        }
        virtual~GetProgramInfoLog(){}
        virtual void operator()(){
          glGetProgramInfoLog(
            ge::core::convertTo<GLuint  >(this->program),
            ge::core::convertTo<GLsizei >(this->bufSize),
            ge::core::convertTo<GLsizei*>(this->length ),
            ge::core::convertTo<GLchar* >(this->infoLog)
          );
        }
    };

    template<
      typename PROGRAM_TYPE = GLuint>
    class ValidateProgram:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program")return(void*)&this->program;
          return NULL;
        }
      public:
        PROGRAM_TYPE program;
        ValidateProgram(
            PROGRAM_TYPE const&program){
          this->program = program;
        }
        virtual~ValidateProgram(){}
        virtual void operator()(){
          glValidateProgram(
            ge::core::convertTo<GLuint>(this->program)
          );
        }
    };

    template<
      typename PROGRAM_TYPE    = GLuint,
      typename SHADERTYPE_TYPE = GLenum,
      typename PNAME_TYPE      = GLenum,
      typename VALUES_TYPE     = GLint*>
    class GetProgramStageiv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program"   )return(void*)&this->program   ;
          if(name == "shadertype")return(void*)&this->shadertype;
          if(name == "pname"     )return(void*)&this->pname     ;
          if(name == "values"    )return(void*)&this->values    ;
          return NULL;
        }
      public:
        PROGRAM_TYPE    program   ;
        SHADERTYPE_TYPE shadertype;
        PNAME_TYPE      pname     ;
        VALUES_TYPE     values    ;
        GetProgramStageiv(
            PROGRAM_TYPE    const&program   ,
            SHADERTYPE_TYPE const&shadertype,
            PNAME_TYPE      const&pname     ,
            VALUES_TYPE     const&values    ){
          this->program    = program   ;
          this->shadertype = shadertype;
          this->pname      = pname     ;
          this->values     = values    ;
        }
        virtual~GetProgramStageiv(){}
        virtual void operator()(){
          glGetProgramStageiv(
            ge::core::convertTo<GLuint>(this->program   ),
            ge::core::convertTo<GLenum>(this->shadertype),
            ge::core::convertTo<GLenum>(this->pname     ),
            ge::core::convertTo<GLint*>(this->values    )
          );
        }
    };

    template<
      typename RET_TYPE     = GLboolean,
      typename PROGRAM_TYPE = GLuint   >
    class IsProgram:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "ret"    )return(void*)&this->ret    ;
          if(name == "program")return(void*)&this->program;
          return NULL;
        }
      public:
        RET_TYPE     ret    ;
        PROGRAM_TYPE program;
        IsProgram(
            RET_TYPE     const&ret    ,
            PROGRAM_TYPE const&program){
          this->ret     = ret    ;
          this->program = program;
        }
        virtual~IsProgram(){}
        virtual void operator()(){
          ge::core::convertFrom<GLboolean>(this->ret,glIsProgram(
              ge::core::convertTo<GLuint   >(this->program))
          );
        }
    };

    template<
      typename PROGRAM_TYPE          = GLuint,
      typename PROGRAMINTERFACE_TYPE = GLenum,
      typename PNAME_TYPE            = GLenum,
      typename PARAMS_TYPE           = GLint*>
    class GetProgramInterfaceiv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program"         )return(void*)&this->program         ;
          if(name == "programInterface")return(void*)&this->programInterface;
          if(name == "pname"           )return(void*)&this->pname           ;
          if(name == "params"          )return(void*)&this->params          ;
          return NULL;
        }
      public:
        PROGRAM_TYPE          program         ;
        PROGRAMINTERFACE_TYPE programInterface;
        PNAME_TYPE            pname           ;
        PARAMS_TYPE           params          ;
        GetProgramInterfaceiv(
            PROGRAM_TYPE          const&program         ,
            PROGRAMINTERFACE_TYPE const&programInterface,
            PNAME_TYPE            const&pname           ,
            PARAMS_TYPE           const&params          ){
          this->program          = program         ;
          this->programInterface = programInterface;
          this->pname            = pname           ;
          this->params           = params          ;
        }
        virtual~GetProgramInterfaceiv(){}
        virtual void operator()(){
          glGetProgramInterfaceiv(
            ge::core::convertTo<GLuint>(this->program         ),
            ge::core::convertTo<GLenum>(this->programInterface),
            ge::core::convertTo<GLenum>(this->pname           ),
            ge::core::convertTo<GLint*>(this->params          )
          );
        }
    };

    template<
      typename PROGRAM_TYPE = GLuint,
      typename PNAME_TYPE   = GLenum,
      typename PARAMS_TYPE  = GLint*>
    class GetProgramiv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program")return(void*)&this->program;
          if(name == "pname"  )return(void*)&this->pname  ;
          if(name == "params" )return(void*)&this->params ;
          return NULL;
        }
      public:
        PROGRAM_TYPE program;
        PNAME_TYPE   pname  ;
        PARAMS_TYPE  params ;
        GetProgramiv(
            PROGRAM_TYPE const&program,
            PNAME_TYPE   const&pname  ,
            PARAMS_TYPE  const&params ){
          this->program = program;
          this->pname   = pname  ;
          this->params  = params ;
        }
        virtual~GetProgramiv(){}
        virtual void operator()(){
          glGetProgramiv(
            ge::core::convertTo<GLuint>(this->program),
            ge::core::convertTo<GLenum>(this->pname  ),
            ge::core::convertTo<GLint*>(this->params )
          );
        }
    };

    template<
      typename PIPELINE_TYPE = GLuint,
      typename PROGRAM_TYPE  = GLuint>
    class ActiveShaderProgram:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "pipeline")return(void*)&this->pipeline;
          if(name == "program" )return(void*)&this->program ;
          return NULL;
        }
      public:
        PIPELINE_TYPE pipeline;
        PROGRAM_TYPE  program ;
        ActiveShaderProgram(
            PIPELINE_TYPE const&pipeline,
            PROGRAM_TYPE  const&program ){
          this->pipeline = pipeline;
          this->program  = program ;
        }
        virtual~ActiveShaderProgram(){}
        virtual void operator()(){
          glActiveShaderProgram(
            ge::core::convertTo<GLuint>(this->pipeline),
            ge::core::convertTo<GLuint>(this->program )
          );
        }
    };

    template<
      typename RET_TYPE              = GLuint       ,
      typename PROGRAM_TYPE          = GLuint       ,
      typename PROGRAMINTERFACE_TYPE = GLenum       ,
      typename NAME_TYPE             = const GLchar*>
    class GetProgramResourceIndex:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "ret"             )return(void*)&this->ret             ;
          if(name == "program"         )return(void*)&this->program         ;
          if(name == "programInterface")return(void*)&this->programInterface;
          if(name == "name"            )return(void*)&this->name            ;
          return NULL;
        }
      public:
        RET_TYPE              ret             ;
        PROGRAM_TYPE          program         ;
        PROGRAMINTERFACE_TYPE programInterface;
        NAME_TYPE             name            ;
        GetProgramResourceIndex(
            RET_TYPE              const&ret             ,
            PROGRAM_TYPE          const&program         ,
            PROGRAMINTERFACE_TYPE const&programInterface,
            NAME_TYPE             const&name            ){
          this->ret              = ret             ;
          this->program          = program         ;
          this->programInterface = programInterface;
          this->name             = name            ;
        }
        virtual~GetProgramResourceIndex(){}
        virtual void operator()(){
          ge::core::convertFrom<GLuint>(this->ret,glGetProgramResourceIndex(
              ge::core::convertTo<GLuint       >(this->program         ),
              ge::core::convertTo<GLenum       >(this->programInterface),
              ge::core::convertTo<const GLchar*>(this->name            ))
          );
        }
    };

    template<
      typename PROGRAM_TYPE = GLuint>
    class LinkProgram:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program")return(void*)&this->program;
          return NULL;
        }
      public:
        PROGRAM_TYPE program;
        LinkProgram(
            PROGRAM_TYPE const&program){
          this->program = program;
        }
        virtual~LinkProgram(){}
        virtual void operator()(){
          glLinkProgram(
            ge::core::convertTo<GLuint>(this->program)
          );
        }
    };

    template<
      typename RET_TYPE              = GLint        ,
      typename PROGRAM_TYPE          = GLuint       ,
      typename PROGRAMINTERFACE_TYPE = GLenum       ,
      typename NAME_TYPE             = const GLchar*>
    class GetProgramResourceLocationIndex:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "ret"             )return(void*)&this->ret             ;
          if(name == "program"         )return(void*)&this->program         ;
          if(name == "programInterface")return(void*)&this->programInterface;
          if(name == "name"            )return(void*)&this->name            ;
          return NULL;
        }
      public:
        RET_TYPE              ret             ;
        PROGRAM_TYPE          program         ;
        PROGRAMINTERFACE_TYPE programInterface;
        NAME_TYPE             name            ;
        GetProgramResourceLocationIndex(
            RET_TYPE              const&ret             ,
            PROGRAM_TYPE          const&program         ,
            PROGRAMINTERFACE_TYPE const&programInterface,
            NAME_TYPE             const&name            ){
          this->ret              = ret             ;
          this->program          = program         ;
          this->programInterface = programInterface;
          this->name             = name            ;
        }
        virtual~GetProgramResourceLocationIndex(){}
        virtual void operator()(){
          ge::core::convertFrom<GLint>(this->ret,glGetProgramResourceLocationIndex(
              ge::core::convertTo<GLuint       >(this->program         ),
              ge::core::convertTo<GLenum       >(this->programInterface),
              ge::core::convertTo<const GLchar*>(this->name            ))
          );
        }
    };

    template<
      typename RET_TYPE     = GLuint             ,
      typename TYPE_TYPE    = GLenum             ,
      typename COUNT_TYPE   = GLsizei            ,
      typename STRINGS_TYPE = const GLchar*const*>
    class CreateShaderProgramv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "ret"    )return(void*)&this->ret    ;
          if(name == "type"   )return(void*)&this->type   ;
          if(name == "count"  )return(void*)&this->count  ;
          if(name == "strings")return(void*)&this->strings;
          return NULL;
        }
      public:
        RET_TYPE     ret    ;
        TYPE_TYPE    type   ;
        COUNT_TYPE   count  ;
        STRINGS_TYPE strings;
        CreateShaderProgramv(
            RET_TYPE     const&ret    ,
            TYPE_TYPE    const&type   ,
            COUNT_TYPE   const&count  ,
            STRINGS_TYPE const&strings){
          this->ret     = ret    ;
          this->type    = type   ;
          this->count   = count  ;
          this->strings = strings;
        }
        virtual~CreateShaderProgramv(){}
        virtual void operator()(){
          ge::core::convertFrom<GLuint>(this->ret,glCreateShaderProgramv(
              ge::core::convertTo<GLenum             >(this->type   ),
              ge::core::convertTo<GLsizei            >(this->count  ),
              ge::core::convertTo<const GLchar*const*>(this->strings))
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
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program"         )return(void*)&this->program         ;
          if(name == "programInterface")return(void*)&this->programInterface;
          if(name == "index"           )return(void*)&this->index           ;
          if(name == "bufSize"         )return(void*)&this->bufSize         ;
          if(name == "length"          )return(void*)&this->length          ;
          if(name == "name"            )return(void*)&this->name            ;
          return NULL;
        }
      public:
        PROGRAM_TYPE          program         ;
        PROGRAMINTERFACE_TYPE programInterface;
        INDEX_TYPE            index           ;
        BUFSIZE_TYPE          bufSize         ;
        LENGTH_TYPE           length          ;
        NAME_TYPE             name            ;
        GetProgramResourceName(
            PROGRAM_TYPE          const&program         ,
            PROGRAMINTERFACE_TYPE const&programInterface,
            INDEX_TYPE            const&index           ,
            BUFSIZE_TYPE          const&bufSize         ,
            LENGTH_TYPE           const&length          ,
            NAME_TYPE             const&name            ){
          this->program          = program         ;
          this->programInterface = programInterface;
          this->index            = index           ;
          this->bufSize          = bufSize         ;
          this->length           = length          ;
          this->name             = name            ;
        }
        virtual~GetProgramResourceName(){}
        virtual void operator()(){
          glGetProgramResourceName(
            ge::core::convertTo<GLuint  >(this->program         ),
            ge::core::convertTo<GLenum  >(this->programInterface),
            ge::core::convertTo<GLuint  >(this->index           ),
            ge::core::convertTo<GLsizei >(this->bufSize         ),
            ge::core::convertTo<GLsizei*>(this->length          ),
            ge::core::convertTo<GLchar* >(this->name            )
          );
        }
    };

    template<
      typename PROGRAM_TYPE      = GLuint     ,
      typename BINARYFORMAT_TYPE = GLenum     ,
      typename BINARY_TYPE       = const void*,
      typename LENGTH_TYPE       = GLsizei    >
    class ProgramBinary:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program"     )return(void*)&this->program     ;
          if(name == "binaryFormat")return(void*)&this->binaryFormat;
          if(name == "binary"      )return(void*)&this->binary      ;
          if(name == "length"      )return(void*)&this->length      ;
          return NULL;
        }
      public:
        PROGRAM_TYPE      program     ;
        BINARYFORMAT_TYPE binaryFormat;
        BINARY_TYPE       binary      ;
        LENGTH_TYPE       length      ;
        ProgramBinary(
            PROGRAM_TYPE      const&program     ,
            BINARYFORMAT_TYPE const&binaryFormat,
            BINARY_TYPE       const&binary      ,
            LENGTH_TYPE       const&length      ){
          this->program      = program     ;
          this->binaryFormat = binaryFormat;
          this->binary       = binary      ;
          this->length       = length      ;
        }
        virtual~ProgramBinary(){}
        virtual void operator()(){
          glProgramBinary(
            ge::core::convertTo<GLuint     >(this->program     ),
            ge::core::convertTo<GLenum     >(this->binaryFormat),
            ge::core::convertTo<const void*>(this->binary      ),
            ge::core::convertTo<GLsizei    >(this->length      )
          );
        }
    };

    template<
      typename PIPELINE_TYPE = GLuint    ,
      typename STAGES_TYPE   = GLbitfield,
      typename PROGRAM_TYPE  = GLuint    >
    class UseProgramStages:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "pipeline")return(void*)&this->pipeline;
          if(name == "stages"  )return(void*)&this->stages  ;
          if(name == "program" )return(void*)&this->program ;
          return NULL;
        }
      public:
        PIPELINE_TYPE pipeline;
        STAGES_TYPE   stages  ;
        PROGRAM_TYPE  program ;
        UseProgramStages(
            PIPELINE_TYPE const&pipeline,
            STAGES_TYPE   const&stages  ,
            PROGRAM_TYPE  const&program ){
          this->pipeline = pipeline;
          this->stages   = stages  ;
          this->program  = program ;
        }
        virtual~UseProgramStages(){}
        virtual void operator()(){
          glUseProgramStages(
            ge::core::convertTo<GLuint    >(this->pipeline),
            ge::core::convertTo<GLbitfield>(this->stages  ),
            ge::core::convertTo<GLuint    >(this->program )
          );
        }
    };

    template<
      typename PROGRAM_TYPE = GLuint>
    class DeleteProgram:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program")return(void*)&this->program;
          return NULL;
        }
      public:
        PROGRAM_TYPE program;
        DeleteProgram(
            PROGRAM_TYPE const&program){
          this->program = program;
        }
        virtual~DeleteProgram(){}
        virtual void operator()(){
          glDeleteProgram(
            ge::core::convertTo<GLuint>(this->program)
          );
        }
    };

    template<
      typename PROGRAM_TYPE = GLuint,
      typename PNAME_TYPE   = GLenum,
      typename VALUE_TYPE   = GLint >
    class ProgramParameteri:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program")return(void*)&this->program;
          if(name == "pname"  )return(void*)&this->pname  ;
          if(name == "value"  )return(void*)&this->value  ;
          return NULL;
        }
      public:
        PROGRAM_TYPE program;
        PNAME_TYPE   pname  ;
        VALUE_TYPE   value  ;
        ProgramParameteri(
            PROGRAM_TYPE const&program,
            PNAME_TYPE   const&pname  ,
            VALUE_TYPE   const&value  ){
          this->program = program;
          this->pname   = pname  ;
          this->value   = value  ;
        }
        virtual~ProgramParameteri(){}
        virtual void operator()(){
          glProgramParameteri(
            ge::core::convertTo<GLuint>(this->program),
            ge::core::convertTo<GLenum>(this->pname  ),
            ge::core::convertTo<GLint >(this->value  )
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
