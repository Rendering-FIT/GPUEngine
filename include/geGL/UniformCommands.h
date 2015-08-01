#pragma once

#include<geCore/Command.h>
#include<geGL/Export.h>
#include<GL/glew.h>
#include<geGL/AllAttribs.h>

namespace ge{
  namespace gl{
    template<
      typename LOCATION_TYPE = GLint   ,
      typename X_TYPE        = GLdouble,
      typename Y_TYPE        = GLdouble>
    class Uniform2d:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "location")return(void*)&this->location;
          if(name == "x"       )return(void*)&this->x       ;
          if(name == "y"       )return(void*)&this->y       ;
          return NULL;
        }
      public:
        LOCATION_TYPE location;
        X_TYPE        x       ;
        Y_TYPE        y       ;
        Uniform2d(
            LOCATION_TYPE const&location,
            X_TYPE        const&x       ,
            Y_TYPE        const&y       ){
          this->location = location;
          this->x        = x       ;
          this->y        = y       ;
        }
        virtual~Uniform2d(){}
        virtual void operator()(){
          glUniform2d(
            ge::core::convertTo<GLint   >(this->location),
            ge::core::convertTo<GLdouble>(this->x       ),
            ge::core::convertTo<GLdouble>(this->y       )
          );
        }
    };

    template<
      typename PROGRAM_TYPE  = GLuint  ,
      typename LOCATION_TYPE = GLint   ,
      typename BUFSIZE_TYPE  = GLsizei ,
      typename PARAMS_TYPE   = GLfloat*>
    class GetnUniformfv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program" )return(void*)&this->program ;
          if(name == "location")return(void*)&this->location;
          if(name == "bufSize" )return(void*)&this->bufSize ;
          if(name == "params"  )return(void*)&this->params  ;
          return NULL;
        }
      public:
        PROGRAM_TYPE  program ;
        LOCATION_TYPE location;
        BUFSIZE_TYPE  bufSize ;
        PARAMS_TYPE   params  ;
        GetnUniformfv(
            PROGRAM_TYPE  const&program ,
            LOCATION_TYPE const&location,
            BUFSIZE_TYPE  const&bufSize ,
            PARAMS_TYPE   const&params  ){
          this->program  = program ;
          this->location = location;
          this->bufSize  = bufSize ;
          this->params   = params  ;
        }
        virtual~GetnUniformfv(){}
        virtual void operator()(){
          glGetnUniformfv(
            ge::core::convertTo<GLuint  >(this->program ),
            ge::core::convertTo<GLint   >(this->location),
            ge::core::convertTo<GLsizei >(this->bufSize ),
            ge::core::convertTo<GLfloat*>(this->params  )
          );
        }
    };

    template<
      typename PROGRAM_TYPE   = GLuint         ,
      typename LOCATION_TYPE  = GLint          ,
      typename COUNT_TYPE     = GLsizei        ,
      typename TRANSPOSE_TYPE = GLboolean      ,
      typename VALUE_TYPE     = const GLdouble*>
    class ProgramUniformMatrix4x3dv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program"  )return(void*)&this->program  ;
          if(name == "location" )return(void*)&this->location ;
          if(name == "count"    )return(void*)&this->count    ;
          if(name == "transpose")return(void*)&this->transpose;
          if(name == "value"    )return(void*)&this->value    ;
          return NULL;
        }
      public:
        PROGRAM_TYPE   program  ;
        LOCATION_TYPE  location ;
        COUNT_TYPE     count    ;
        TRANSPOSE_TYPE transpose;
        VALUE_TYPE     value    ;
        ProgramUniformMatrix4x3dv(
            PROGRAM_TYPE   const&program  ,
            LOCATION_TYPE  const&location ,
            COUNT_TYPE     const&count    ,
            TRANSPOSE_TYPE const&transpose,
            VALUE_TYPE     const&value    ){
          this->program   = program  ;
          this->location  = location ;
          this->count     = count    ;
          this->transpose = transpose;
          this->value     = value    ;
        }
        virtual~ProgramUniformMatrix4x3dv(){}
        virtual void operator()(){
          glProgramUniformMatrix4x3dv(
            ge::core::convertTo<GLuint         >(this->program  ),
            ge::core::convertTo<GLint          >(this->location ),
            ge::core::convertTo<GLsizei        >(this->count    ),
            ge::core::convertTo<GLboolean      >(this->transpose),
            ge::core::convertTo<const GLdouble*>(this->value    )
          );
        }
    };

    template<
      typename LOCATION_TYPE = GLint          ,
      typename COUNT_TYPE    = GLsizei        ,
      typename VALUE_TYPE    = const GLdouble*>
    class Uniform3dv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "location")return(void*)&this->location;
          if(name == "count"   )return(void*)&this->count   ;
          if(name == "value"   )return(void*)&this->value   ;
          return NULL;
        }
      public:
        LOCATION_TYPE location;
        COUNT_TYPE    count   ;
        VALUE_TYPE    value   ;
        Uniform3dv(
            LOCATION_TYPE const&location,
            COUNT_TYPE    const&count   ,
            VALUE_TYPE    const&value   ){
          this->location = location;
          this->count    = count   ;
          this->value    = value   ;
        }
        virtual~Uniform3dv(){}
        virtual void operator()(){
          glUniform3dv(
            ge::core::convertTo<GLint          >(this->location),
            ge::core::convertTo<GLsizei        >(this->count   ),
            ge::core::convertTo<const GLdouble*>(this->value   )
          );
        }
    };

    template<
      typename LOCATION_TYPE = GLint         ,
      typename COUNT_TYPE    = GLsizei       ,
      typename VALUE_TYPE    = const GLfloat*>
    class Uniform1fv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "location")return(void*)&this->location;
          if(name == "count"   )return(void*)&this->count   ;
          if(name == "value"   )return(void*)&this->value   ;
          return NULL;
        }
      public:
        LOCATION_TYPE location;
        COUNT_TYPE    count   ;
        VALUE_TYPE    value   ;
        Uniform1fv(
            LOCATION_TYPE const&location,
            COUNT_TYPE    const&count   ,
            VALUE_TYPE    const&value   ){
          this->location = location;
          this->count    = count   ;
          this->value    = value   ;
        }
        virtual~Uniform1fv(){}
        virtual void operator()(){
          glUniform1fv(
            ge::core::convertTo<GLint         >(this->location),
            ge::core::convertTo<GLsizei       >(this->count   ),
            ge::core::convertTo<const GLfloat*>(this->value   )
          );
        }
    };

    template<
      typename LOCATION_TYPE  = GLint          ,
      typename COUNT_TYPE     = GLsizei        ,
      typename TRANSPOSE_TYPE = GLboolean      ,
      typename VALUE_TYPE     = const GLdouble*>
    class UniformMatrix2x3dv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "location" )return(void*)&this->location ;
          if(name == "count"    )return(void*)&this->count    ;
          if(name == "transpose")return(void*)&this->transpose;
          if(name == "value"    )return(void*)&this->value    ;
          return NULL;
        }
      public:
        LOCATION_TYPE  location ;
        COUNT_TYPE     count    ;
        TRANSPOSE_TYPE transpose;
        VALUE_TYPE     value    ;
        UniformMatrix2x3dv(
            LOCATION_TYPE  const&location ,
            COUNT_TYPE     const&count    ,
            TRANSPOSE_TYPE const&transpose,
            VALUE_TYPE     const&value    ){
          this->location  = location ;
          this->count     = count    ;
          this->transpose = transpose;
          this->value     = value    ;
        }
        virtual~UniformMatrix2x3dv(){}
        virtual void operator()(){
          glUniformMatrix2x3dv(
            ge::core::convertTo<GLint          >(this->location ),
            ge::core::convertTo<GLsizei        >(this->count    ),
            ge::core::convertTo<GLboolean      >(this->transpose),
            ge::core::convertTo<const GLdouble*>(this->value    )
          );
        }
    };

    template<
      typename LOCATION_TYPE = GLint          ,
      typename COUNT_TYPE    = GLsizei        ,
      typename VALUE_TYPE    = const GLdouble*>
    class Uniform1dv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "location")return(void*)&this->location;
          if(name == "count"   )return(void*)&this->count   ;
          if(name == "value"   )return(void*)&this->value   ;
          return NULL;
        }
      public:
        LOCATION_TYPE location;
        COUNT_TYPE    count   ;
        VALUE_TYPE    value   ;
        Uniform1dv(
            LOCATION_TYPE const&location,
            COUNT_TYPE    const&count   ,
            VALUE_TYPE    const&value   ){
          this->location = location;
          this->count    = count   ;
          this->value    = value   ;
        }
        virtual~Uniform1dv(){}
        virtual void operator()(){
          glUniform1dv(
            ge::core::convertTo<GLint          >(this->location),
            ge::core::convertTo<GLsizei        >(this->count   ),
            ge::core::convertTo<const GLdouble*>(this->value   )
          );
        }
    };

    template<
      typename PROGRAM_TYPE   = GLuint         ,
      typename LOCATION_TYPE  = GLint          ,
      typename COUNT_TYPE     = GLsizei        ,
      typename TRANSPOSE_TYPE = GLboolean      ,
      typename VALUE_TYPE     = const GLdouble*>
    class ProgramUniformMatrix2x4dv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program"  )return(void*)&this->program  ;
          if(name == "location" )return(void*)&this->location ;
          if(name == "count"    )return(void*)&this->count    ;
          if(name == "transpose")return(void*)&this->transpose;
          if(name == "value"    )return(void*)&this->value    ;
          return NULL;
        }
      public:
        PROGRAM_TYPE   program  ;
        LOCATION_TYPE  location ;
        COUNT_TYPE     count    ;
        TRANSPOSE_TYPE transpose;
        VALUE_TYPE     value    ;
        ProgramUniformMatrix2x4dv(
            PROGRAM_TYPE   const&program  ,
            LOCATION_TYPE  const&location ,
            COUNT_TYPE     const&count    ,
            TRANSPOSE_TYPE const&transpose,
            VALUE_TYPE     const&value    ){
          this->program   = program  ;
          this->location  = location ;
          this->count     = count    ;
          this->transpose = transpose;
          this->value     = value    ;
        }
        virtual~ProgramUniformMatrix2x4dv(){}
        virtual void operator()(){
          glProgramUniformMatrix2x4dv(
            ge::core::convertTo<GLuint         >(this->program  ),
            ge::core::convertTo<GLint          >(this->location ),
            ge::core::convertTo<GLsizei        >(this->count    ),
            ge::core::convertTo<GLboolean      >(this->transpose),
            ge::core::convertTo<const GLdouble*>(this->value    )
          );
        }
    };

    template<
      typename PROGRAM_TYPE    = GLuint,
      typename SHADERTYPE_TYPE = GLenum,
      typename INDEX_TYPE      = GLuint,
      typename PNAME_TYPE      = GLenum,
      typename VALUES_TYPE     = GLint*>
    class GetActiveSubroutineUniformiv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program"   )return(void*)&this->program   ;
          if(name == "shadertype")return(void*)&this->shadertype;
          if(name == "index"     )return(void*)&this->index     ;
          if(name == "pname"     )return(void*)&this->pname     ;
          if(name == "values"    )return(void*)&this->values    ;
          return NULL;
        }
      public:
        PROGRAM_TYPE    program   ;
        SHADERTYPE_TYPE shadertype;
        INDEX_TYPE      index     ;
        PNAME_TYPE      pname     ;
        VALUES_TYPE     values    ;
        GetActiveSubroutineUniformiv(
            PROGRAM_TYPE    const&program   ,
            SHADERTYPE_TYPE const&shadertype,
            INDEX_TYPE      const&index     ,
            PNAME_TYPE      const&pname     ,
            VALUES_TYPE     const&values    ){
          this->program    = program   ;
          this->shadertype = shadertype;
          this->index      = index     ;
          this->pname      = pname     ;
          this->values     = values    ;
        }
        virtual~GetActiveSubroutineUniformiv(){}
        virtual void operator()(){
          glGetActiveSubroutineUniformiv(
            ge::core::convertTo<GLuint>(this->program   ),
            ge::core::convertTo<GLenum>(this->shadertype),
            ge::core::convertTo<GLuint>(this->index     ),
            ge::core::convertTo<GLenum>(this->pname     ),
            ge::core::convertTo<GLint*>(this->values    )
          );
        }
    };

    template<
      typename PROGRAM_TYPE   = GLuint         ,
      typename LOCATION_TYPE  = GLint          ,
      typename COUNT_TYPE     = GLsizei        ,
      typename TRANSPOSE_TYPE = GLboolean      ,
      typename VALUE_TYPE     = const GLdouble*>
    class ProgramUniformMatrix4x2dv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program"  )return(void*)&this->program  ;
          if(name == "location" )return(void*)&this->location ;
          if(name == "count"    )return(void*)&this->count    ;
          if(name == "transpose")return(void*)&this->transpose;
          if(name == "value"    )return(void*)&this->value    ;
          return NULL;
        }
      public:
        PROGRAM_TYPE   program  ;
        LOCATION_TYPE  location ;
        COUNT_TYPE     count    ;
        TRANSPOSE_TYPE transpose;
        VALUE_TYPE     value    ;
        ProgramUniformMatrix4x2dv(
            PROGRAM_TYPE   const&program  ,
            LOCATION_TYPE  const&location ,
            COUNT_TYPE     const&count    ,
            TRANSPOSE_TYPE const&transpose,
            VALUE_TYPE     const&value    ){
          this->program   = program  ;
          this->location  = location ;
          this->count     = count    ;
          this->transpose = transpose;
          this->value     = value    ;
        }
        virtual~ProgramUniformMatrix4x2dv(){}
        virtual void operator()(){
          glProgramUniformMatrix4x2dv(
            ge::core::convertTo<GLuint         >(this->program  ),
            ge::core::convertTo<GLint          >(this->location ),
            ge::core::convertTo<GLsizei        >(this->count    ),
            ge::core::convertTo<GLboolean      >(this->transpose),
            ge::core::convertTo<const GLdouble*>(this->value    )
          );
        }
    };

    template<
      typename PROGRAM_TYPE  = GLuint,
      typename LOCATION_TYPE = GLint ,
      typename V0_TYPE       = GLuint>
    class ProgramUniform1ui:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program" )return(void*)&this->program ;
          if(name == "location")return(void*)&this->location;
          if(name == "v0"      )return(void*)&this->v0      ;
          return NULL;
        }
      public:
        PROGRAM_TYPE  program ;
        LOCATION_TYPE location;
        V0_TYPE       v0      ;
        ProgramUniform1ui(
            PROGRAM_TYPE  const&program ,
            LOCATION_TYPE const&location,
            V0_TYPE       const&v0      ){
          this->program  = program ;
          this->location = location;
          this->v0       = v0      ;
        }
        virtual~ProgramUniform1ui(){}
        virtual void operator()(){
          glProgramUniform1ui(
            ge::core::convertTo<GLuint>(this->program ),
            ge::core::convertTo<GLint >(this->location),
            ge::core::convertTo<GLuint>(this->v0      )
          );
        }
    };

    template<
      typename PROGRAM_TYPE             = GLuint,
      typename UNIFORMBLOCKINDEX_TYPE   = GLuint,
      typename UNIFORMBLOCKBINDING_TYPE = GLuint>
    class UniformBlockBinding:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program"            )return(void*)&this->program            ;
          if(name == "uniformBlockIndex"  )return(void*)&this->uniformBlockIndex  ;
          if(name == "uniformBlockBinding")return(void*)&this->uniformBlockBinding;
          return NULL;
        }
      public:
        PROGRAM_TYPE             program            ;
        UNIFORMBLOCKINDEX_TYPE   uniformBlockIndex  ;
        UNIFORMBLOCKBINDING_TYPE uniformBlockBinding;
        UniformBlockBinding(
            PROGRAM_TYPE             const&program            ,
            UNIFORMBLOCKINDEX_TYPE   const&uniformBlockIndex  ,
            UNIFORMBLOCKBINDING_TYPE const&uniformBlockBinding){
          this->program             = program            ;
          this->uniformBlockIndex   = uniformBlockIndex  ;
          this->uniformBlockBinding = uniformBlockBinding;
        }
        virtual~UniformBlockBinding(){}
        virtual void operator()(){
          glUniformBlockBinding(
            ge::core::convertTo<GLuint>(this->program            ),
            ge::core::convertTo<GLuint>(this->uniformBlockIndex  ),
            ge::core::convertTo<GLuint>(this->uniformBlockBinding)
          );
        }
    };

    template<
      typename PROGRAM_TYPE  = GLuint   ,
      typename LOCATION_TYPE = GLint    ,
      typename BUFSIZE_TYPE  = GLsizei  ,
      typename PARAMS_TYPE   = GLdouble*>
    class GetnUniformdv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program" )return(void*)&this->program ;
          if(name == "location")return(void*)&this->location;
          if(name == "bufSize" )return(void*)&this->bufSize ;
          if(name == "params"  )return(void*)&this->params  ;
          return NULL;
        }
      public:
        PROGRAM_TYPE  program ;
        LOCATION_TYPE location;
        BUFSIZE_TYPE  bufSize ;
        PARAMS_TYPE   params  ;
        GetnUniformdv(
            PROGRAM_TYPE  const&program ,
            LOCATION_TYPE const&location,
            BUFSIZE_TYPE  const&bufSize ,
            PARAMS_TYPE   const&params  ){
          this->program  = program ;
          this->location = location;
          this->bufSize  = bufSize ;
          this->params   = params  ;
        }
        virtual~GetnUniformdv(){}
        virtual void operator()(){
          glGetnUniformdv(
            ge::core::convertTo<GLuint   >(this->program ),
            ge::core::convertTo<GLint    >(this->location),
            ge::core::convertTo<GLsizei  >(this->bufSize ),
            ge::core::convertTo<GLdouble*>(this->params  )
          );
        }
    };

    template<
      typename PROGRAM_TYPE  = GLuint,
      typename LOCATION_TYPE = GLint ,
      typename V0_TYPE       = GLuint,
      typename V1_TYPE       = GLuint,
      typename V2_TYPE       = GLuint,
      typename V3_TYPE       = GLuint>
    class ProgramUniform4ui:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program" )return(void*)&this->program ;
          if(name == "location")return(void*)&this->location;
          if(name == "v0"      )return(void*)&this->v0      ;
          if(name == "v1"      )return(void*)&this->v1      ;
          if(name == "v2"      )return(void*)&this->v2      ;
          if(name == "v3"      )return(void*)&this->v3      ;
          return NULL;
        }
      public:
        PROGRAM_TYPE  program ;
        LOCATION_TYPE location;
        V0_TYPE       v0      ;
        V1_TYPE       v1      ;
        V2_TYPE       v2      ;
        V3_TYPE       v3      ;
        ProgramUniform4ui(
            PROGRAM_TYPE  const&program ,
            LOCATION_TYPE const&location,
            V0_TYPE       const&v0      ,
            V1_TYPE       const&v1      ,
            V2_TYPE       const&v2      ,
            V3_TYPE       const&v3      ){
          this->program  = program ;
          this->location = location;
          this->v0       = v0      ;
          this->v1       = v1      ;
          this->v2       = v2      ;
          this->v3       = v3      ;
        }
        virtual~ProgramUniform4ui(){}
        virtual void operator()(){
          glProgramUniform4ui(
            ge::core::convertTo<GLuint>(this->program ),
            ge::core::convertTo<GLint >(this->location),
            ge::core::convertTo<GLuint>(this->v0      ),
            ge::core::convertTo<GLuint>(this->v1      ),
            ge::core::convertTo<GLuint>(this->v2      ),
            ge::core::convertTo<GLuint>(this->v3      )
          );
        }
    };

    template<
      typename PROGRAM_TYPE   = GLuint        ,
      typename LOCATION_TYPE  = GLint         ,
      typename COUNT_TYPE     = GLsizei       ,
      typename TRANSPOSE_TYPE = GLboolean     ,
      typename VALUE_TYPE     = const GLfloat*>
    class ProgramUniformMatrix2x4fv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program"  )return(void*)&this->program  ;
          if(name == "location" )return(void*)&this->location ;
          if(name == "count"    )return(void*)&this->count    ;
          if(name == "transpose")return(void*)&this->transpose;
          if(name == "value"    )return(void*)&this->value    ;
          return NULL;
        }
      public:
        PROGRAM_TYPE   program  ;
        LOCATION_TYPE  location ;
        COUNT_TYPE     count    ;
        TRANSPOSE_TYPE transpose;
        VALUE_TYPE     value    ;
        ProgramUniformMatrix2x4fv(
            PROGRAM_TYPE   const&program  ,
            LOCATION_TYPE  const&location ,
            COUNT_TYPE     const&count    ,
            TRANSPOSE_TYPE const&transpose,
            VALUE_TYPE     const&value    ){
          this->program   = program  ;
          this->location  = location ;
          this->count     = count    ;
          this->transpose = transpose;
          this->value     = value    ;
        }
        virtual~ProgramUniformMatrix2x4fv(){}
        virtual void operator()(){
          glProgramUniformMatrix2x4fv(
            ge::core::convertTo<GLuint        >(this->program  ),
            ge::core::convertTo<GLint         >(this->location ),
            ge::core::convertTo<GLsizei       >(this->count    ),
            ge::core::convertTo<GLboolean     >(this->transpose),
            ge::core::convertTo<const GLfloat*>(this->value    )
          );
        }
    };

    template<
      typename PROGRAM_TYPE  = GLuint      ,
      typename LOCATION_TYPE = GLint       ,
      typename COUNT_TYPE    = GLsizei     ,
      typename VALUE_TYPE    = const GLint*>
    class ProgramUniform1iv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program" )return(void*)&this->program ;
          if(name == "location")return(void*)&this->location;
          if(name == "count"   )return(void*)&this->count   ;
          if(name == "value"   )return(void*)&this->value   ;
          return NULL;
        }
      public:
        PROGRAM_TYPE  program ;
        LOCATION_TYPE location;
        COUNT_TYPE    count   ;
        VALUE_TYPE    value   ;
        ProgramUniform1iv(
            PROGRAM_TYPE  const&program ,
            LOCATION_TYPE const&location,
            COUNT_TYPE    const&count   ,
            VALUE_TYPE    const&value   ){
          this->program  = program ;
          this->location = location;
          this->count    = count   ;
          this->value    = value   ;
        }
        virtual~ProgramUniform1iv(){}
        virtual void operator()(){
          glProgramUniform1iv(
            ge::core::convertTo<GLuint      >(this->program ),
            ge::core::convertTo<GLint       >(this->location),
            ge::core::convertTo<GLsizei     >(this->count   ),
            ge::core::convertTo<const GLint*>(this->value   )
          );
        }
    };

    template<
      typename LOCATION_TYPE = GLint        ,
      typename COUNT_TYPE    = GLsizei      ,
      typename VALUE_TYPE    = const GLuint*>
    class Uniform2uiv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "location")return(void*)&this->location;
          if(name == "count"   )return(void*)&this->count   ;
          if(name == "value"   )return(void*)&this->value   ;
          return NULL;
        }
      public:
        LOCATION_TYPE location;
        COUNT_TYPE    count   ;
        VALUE_TYPE    value   ;
        Uniform2uiv(
            LOCATION_TYPE const&location,
            COUNT_TYPE    const&count   ,
            VALUE_TYPE    const&value   ){
          this->location = location;
          this->count    = count   ;
          this->value    = value   ;
        }
        virtual~Uniform2uiv(){}
        virtual void operator()(){
          glUniform2uiv(
            ge::core::convertTo<GLint        >(this->location),
            ge::core::convertTo<GLsizei      >(this->count   ),
            ge::core::convertTo<const GLuint*>(this->value   )
          );
        }
    };

    template<
      typename PROGRAM_TYPE  = GLuint        ,
      typename LOCATION_TYPE = GLint         ,
      typename COUNT_TYPE    = GLsizei       ,
      typename VALUE_TYPE    = const GLfloat*>
    class ProgramUniform3fv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program" )return(void*)&this->program ;
          if(name == "location")return(void*)&this->location;
          if(name == "count"   )return(void*)&this->count   ;
          if(name == "value"   )return(void*)&this->value   ;
          return NULL;
        }
      public:
        PROGRAM_TYPE  program ;
        LOCATION_TYPE location;
        COUNT_TYPE    count   ;
        VALUE_TYPE    value   ;
        ProgramUniform3fv(
            PROGRAM_TYPE  const&program ,
            LOCATION_TYPE const&location,
            COUNT_TYPE    const&count   ,
            VALUE_TYPE    const&value   ){
          this->program  = program ;
          this->location = location;
          this->count    = count   ;
          this->value    = value   ;
        }
        virtual~ProgramUniform3fv(){}
        virtual void operator()(){
          glProgramUniform3fv(
            ge::core::convertTo<GLuint        >(this->program ),
            ge::core::convertTo<GLint         >(this->location),
            ge::core::convertTo<GLsizei       >(this->count   ),
            ge::core::convertTo<const GLfloat*>(this->value   )
          );
        }
    };

    template<
      typename PROGRAM_TYPE  = GLuint        ,
      typename LOCATION_TYPE = GLint         ,
      typename COUNT_TYPE    = GLsizei       ,
      typename VALUE_TYPE    = const GLfloat*>
    class ProgramUniform1fv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program" )return(void*)&this->program ;
          if(name == "location")return(void*)&this->location;
          if(name == "count"   )return(void*)&this->count   ;
          if(name == "value"   )return(void*)&this->value   ;
          return NULL;
        }
      public:
        PROGRAM_TYPE  program ;
        LOCATION_TYPE location;
        COUNT_TYPE    count   ;
        VALUE_TYPE    value   ;
        ProgramUniform1fv(
            PROGRAM_TYPE  const&program ,
            LOCATION_TYPE const&location,
            COUNT_TYPE    const&count   ,
            VALUE_TYPE    const&value   ){
          this->program  = program ;
          this->location = location;
          this->count    = count   ;
          this->value    = value   ;
        }
        virtual~ProgramUniform1fv(){}
        virtual void operator()(){
          glProgramUniform1fv(
            ge::core::convertTo<GLuint        >(this->program ),
            ge::core::convertTo<GLint         >(this->location),
            ge::core::convertTo<GLsizei       >(this->count   ),
            ge::core::convertTo<const GLfloat*>(this->value   )
          );
        }
    };

    template<
      typename PROGRAM_TYPE  = GLuint,
      typename LOCATION_TYPE = GLint ,
      typename V0_TYPE       = GLuint,
      typename V1_TYPE       = GLuint>
    class ProgramUniform2ui:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program" )return(void*)&this->program ;
          if(name == "location")return(void*)&this->location;
          if(name == "v0"      )return(void*)&this->v0      ;
          if(name == "v1"      )return(void*)&this->v1      ;
          return NULL;
        }
      public:
        PROGRAM_TYPE  program ;
        LOCATION_TYPE location;
        V0_TYPE       v0      ;
        V1_TYPE       v1      ;
        ProgramUniform2ui(
            PROGRAM_TYPE  const&program ,
            LOCATION_TYPE const&location,
            V0_TYPE       const&v0      ,
            V1_TYPE       const&v1      ){
          this->program  = program ;
          this->location = location;
          this->v0       = v0      ;
          this->v1       = v1      ;
        }
        virtual~ProgramUniform2ui(){}
        virtual void operator()(){
          glProgramUniform2ui(
            ge::core::convertTo<GLuint>(this->program ),
            ge::core::convertTo<GLint >(this->location),
            ge::core::convertTo<GLuint>(this->v0      ),
            ge::core::convertTo<GLuint>(this->v1      )
          );
        }
    };

    template<
      typename LOCATION_TYPE = GLint ,
      typename V0_TYPE       = GLuint,
      typename V1_TYPE       = GLuint,
      typename V2_TYPE       = GLuint>
    class Uniform3ui:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "location")return(void*)&this->location;
          if(name == "v0"      )return(void*)&this->v0      ;
          if(name == "v1"      )return(void*)&this->v1      ;
          if(name == "v2"      )return(void*)&this->v2      ;
          return NULL;
        }
      public:
        LOCATION_TYPE location;
        V0_TYPE       v0      ;
        V1_TYPE       v1      ;
        V2_TYPE       v2      ;
        Uniform3ui(
            LOCATION_TYPE const&location,
            V0_TYPE       const&v0      ,
            V1_TYPE       const&v1      ,
            V2_TYPE       const&v2      ){
          this->location = location;
          this->v0       = v0      ;
          this->v1       = v1      ;
          this->v2       = v2      ;
        }
        virtual~Uniform3ui(){}
        virtual void operator()(){
          glUniform3ui(
            ge::core::convertTo<GLint >(this->location),
            ge::core::convertTo<GLuint>(this->v0      ),
            ge::core::convertTo<GLuint>(this->v1      ),
            ge::core::convertTo<GLuint>(this->v2      )
          );
        }
    };

    template<
      typename LOCATION_TYPE = GLint       ,
      typename COUNT_TYPE    = GLsizei     ,
      typename VALUE_TYPE    = const GLint*>
    class Uniform3iv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "location")return(void*)&this->location;
          if(name == "count"   )return(void*)&this->count   ;
          if(name == "value"   )return(void*)&this->value   ;
          return NULL;
        }
      public:
        LOCATION_TYPE location;
        COUNT_TYPE    count   ;
        VALUE_TYPE    value   ;
        Uniform3iv(
            LOCATION_TYPE const&location,
            COUNT_TYPE    const&count   ,
            VALUE_TYPE    const&value   ){
          this->location = location;
          this->count    = count   ;
          this->value    = value   ;
        }
        virtual~Uniform3iv(){}
        virtual void operator()(){
          glUniform3iv(
            ge::core::convertTo<GLint       >(this->location),
            ge::core::convertTo<GLsizei     >(this->count   ),
            ge::core::convertTo<const GLint*>(this->value   )
          );
        }
    };

    template<
      typename PROGRAM_TYPE           = GLuint  ,
      typename UNIFORMBLOCKINDEX_TYPE = GLuint  ,
      typename BUFSIZE_TYPE           = GLsizei ,
      typename LENGTH_TYPE            = GLsizei*,
      typename UNIFORMBLOCKNAME_TYPE  = GLchar* >
    class GetActiveUniformBlockName:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program"          )return(void*)&this->program          ;
          if(name == "uniformBlockIndex")return(void*)&this->uniformBlockIndex;
          if(name == "bufSize"          )return(void*)&this->bufSize          ;
          if(name == "length"           )return(void*)&this->length           ;
          if(name == "uniformBlockName" )return(void*)&this->uniformBlockName ;
          return NULL;
        }
      public:
        PROGRAM_TYPE           program          ;
        UNIFORMBLOCKINDEX_TYPE uniformBlockIndex;
        BUFSIZE_TYPE           bufSize          ;
        LENGTH_TYPE            length           ;
        UNIFORMBLOCKNAME_TYPE  uniformBlockName ;
        GetActiveUniformBlockName(
            PROGRAM_TYPE           const&program          ,
            UNIFORMBLOCKINDEX_TYPE const&uniformBlockIndex,
            BUFSIZE_TYPE           const&bufSize          ,
            LENGTH_TYPE            const&length           ,
            UNIFORMBLOCKNAME_TYPE  const&uniformBlockName ){
          this->program           = program          ;
          this->uniformBlockIndex = uniformBlockIndex;
          this->bufSize           = bufSize          ;
          this->length            = length           ;
          this->uniformBlockName  = uniformBlockName ;
        }
        virtual~GetActiveUniformBlockName(){}
        virtual void operator()(){
          glGetActiveUniformBlockName(
            ge::core::convertTo<GLuint  >(this->program          ),
            ge::core::convertTo<GLuint  >(this->uniformBlockIndex),
            ge::core::convertTo<GLsizei >(this->bufSize          ),
            ge::core::convertTo<GLsizei*>(this->length           ),
            ge::core::convertTo<GLchar* >(this->uniformBlockName )
          );
        }
    };

    template<
      typename PROGRAM_TYPE        = GLuint             ,
      typename UNIFORMCOUNT_TYPE   = GLsizei            ,
      typename UNIFORMNAMES_TYPE   = const GLchar*const*,
      typename UNIFORMINDICES_TYPE = GLuint*            >
    class GetUniformIndices:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program"       )return(void*)&this->program       ;
          if(name == "uniformCount"  )return(void*)&this->uniformCount  ;
          if(name == "uniformNames"  )return(void*)&this->uniformNames  ;
          if(name == "uniformIndices")return(void*)&this->uniformIndices;
          return NULL;
        }
      public:
        PROGRAM_TYPE        program       ;
        UNIFORMCOUNT_TYPE   uniformCount  ;
        UNIFORMNAMES_TYPE   uniformNames  ;
        UNIFORMINDICES_TYPE uniformIndices;
        GetUniformIndices(
            PROGRAM_TYPE        const&program       ,
            UNIFORMCOUNT_TYPE   const&uniformCount  ,
            UNIFORMNAMES_TYPE   const&uniformNames  ,
            UNIFORMINDICES_TYPE const&uniformIndices){
          this->program        = program       ;
          this->uniformCount   = uniformCount  ;
          this->uniformNames   = uniformNames  ;
          this->uniformIndices = uniformIndices;
        }
        virtual~GetUniformIndices(){}
        virtual void operator()(){
          glGetUniformIndices(
            ge::core::convertTo<GLuint             >(this->program       ),
            ge::core::convertTo<GLsizei            >(this->uniformCount  ),
            ge::core::convertTo<const GLchar*const*>(this->uniformNames  ),
            ge::core::convertTo<GLuint*            >(this->uniformIndices)
          );
        }
    };

    template<
      typename PROGRAM_TYPE  = GLuint,
      typename LOCATION_TYPE = GLint ,
      typename PARAMS_TYPE   = GLint*>
    class GetUniformiv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program" )return(void*)&this->program ;
          if(name == "location")return(void*)&this->location;
          if(name == "params"  )return(void*)&this->params  ;
          return NULL;
        }
      public:
        PROGRAM_TYPE  program ;
        LOCATION_TYPE location;
        PARAMS_TYPE   params  ;
        GetUniformiv(
            PROGRAM_TYPE  const&program ,
            LOCATION_TYPE const&location,
            PARAMS_TYPE   const&params  ){
          this->program  = program ;
          this->location = location;
          this->params   = params  ;
        }
        virtual~GetUniformiv(){}
        virtual void operator()(){
          glGetUniformiv(
            ge::core::convertTo<GLuint>(this->program ),
            ge::core::convertTo<GLint >(this->location),
            ge::core::convertTo<GLint*>(this->params  )
          );
        }
    };

    template<
      typename LOCATION_TYPE  = GLint          ,
      typename COUNT_TYPE     = GLsizei        ,
      typename TRANSPOSE_TYPE = GLboolean      ,
      typename VALUE_TYPE     = const GLdouble*>
    class UniformMatrix4dv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "location" )return(void*)&this->location ;
          if(name == "count"    )return(void*)&this->count    ;
          if(name == "transpose")return(void*)&this->transpose;
          if(name == "value"    )return(void*)&this->value    ;
          return NULL;
        }
      public:
        LOCATION_TYPE  location ;
        COUNT_TYPE     count    ;
        TRANSPOSE_TYPE transpose;
        VALUE_TYPE     value    ;
        UniformMatrix4dv(
            LOCATION_TYPE  const&location ,
            COUNT_TYPE     const&count    ,
            TRANSPOSE_TYPE const&transpose,
            VALUE_TYPE     const&value    ){
          this->location  = location ;
          this->count     = count    ;
          this->transpose = transpose;
          this->value     = value    ;
        }
        virtual~UniformMatrix4dv(){}
        virtual void operator()(){
          glUniformMatrix4dv(
            ge::core::convertTo<GLint          >(this->location ),
            ge::core::convertTo<GLsizei        >(this->count    ),
            ge::core::convertTo<GLboolean      >(this->transpose),
            ge::core::convertTo<const GLdouble*>(this->value    )
          );
        }
    };

    template<
      typename LOCATION_TYPE = GLint ,
      typename V0_TYPE       = GLuint>
    class Uniform1ui:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "location")return(void*)&this->location;
          if(name == "v0"      )return(void*)&this->v0      ;
          return NULL;
        }
      public:
        LOCATION_TYPE location;
        V0_TYPE       v0      ;
        Uniform1ui(
            LOCATION_TYPE const&location,
            V0_TYPE       const&v0      ){
          this->location = location;
          this->v0       = v0      ;
        }
        virtual~Uniform1ui(){}
        virtual void operator()(){
          glUniform1ui(
            ge::core::convertTo<GLint >(this->location),
            ge::core::convertTo<GLuint>(this->v0      )
          );
        }
    };

    template<
      typename LOCATION_TYPE  = GLint          ,
      typename COUNT_TYPE     = GLsizei        ,
      typename TRANSPOSE_TYPE = GLboolean      ,
      typename VALUE_TYPE     = const GLdouble*>
    class UniformMatrix3x4dv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "location" )return(void*)&this->location ;
          if(name == "count"    )return(void*)&this->count    ;
          if(name == "transpose")return(void*)&this->transpose;
          if(name == "value"    )return(void*)&this->value    ;
          return NULL;
        }
      public:
        LOCATION_TYPE  location ;
        COUNT_TYPE     count    ;
        TRANSPOSE_TYPE transpose;
        VALUE_TYPE     value    ;
        UniformMatrix3x4dv(
            LOCATION_TYPE  const&location ,
            COUNT_TYPE     const&count    ,
            TRANSPOSE_TYPE const&transpose,
            VALUE_TYPE     const&value    ){
          this->location  = location ;
          this->count     = count    ;
          this->transpose = transpose;
          this->value     = value    ;
        }
        virtual~UniformMatrix3x4dv(){}
        virtual void operator()(){
          glUniformMatrix3x4dv(
            ge::core::convertTo<GLint          >(this->location ),
            ge::core::convertTo<GLsizei        >(this->count    ),
            ge::core::convertTo<GLboolean      >(this->transpose),
            ge::core::convertTo<const GLdouble*>(this->value    )
          );
        }
    };

    template<
      typename PROGRAM_TYPE  = GLuint,
      typename LOCATION_TYPE = GLint ,
      typename V0_TYPE       = GLint >
    class ProgramUniform1i:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program" )return(void*)&this->program ;
          if(name == "location")return(void*)&this->location;
          if(name == "v0"      )return(void*)&this->v0      ;
          return NULL;
        }
      public:
        PROGRAM_TYPE  program ;
        LOCATION_TYPE location;
        V0_TYPE       v0      ;
        ProgramUniform1i(
            PROGRAM_TYPE  const&program ,
            LOCATION_TYPE const&location,
            V0_TYPE       const&v0      ){
          this->program  = program ;
          this->location = location;
          this->v0       = v0      ;
        }
        virtual~ProgramUniform1i(){}
        virtual void operator()(){
          glProgramUniform1i(
            ge::core::convertTo<GLuint>(this->program ),
            ge::core::convertTo<GLint >(this->location),
            ge::core::convertTo<GLint >(this->v0      )
          );
        }
    };

    template<
      typename PROGRAM_TYPE        = GLuint       ,
      typename UNIFORMCOUNT_TYPE   = GLsizei      ,
      typename UNIFORMINDICES_TYPE = const GLuint*,
      typename PNAME_TYPE          = GLenum       ,
      typename PARAMS_TYPE         = GLint*       >
    class GetActiveUniformsiv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program"       )return(void*)&this->program       ;
          if(name == "uniformCount"  )return(void*)&this->uniformCount  ;
          if(name == "uniformIndices")return(void*)&this->uniformIndices;
          if(name == "pname"         )return(void*)&this->pname         ;
          if(name == "params"        )return(void*)&this->params        ;
          return NULL;
        }
      public:
        PROGRAM_TYPE        program       ;
        UNIFORMCOUNT_TYPE   uniformCount  ;
        UNIFORMINDICES_TYPE uniformIndices;
        PNAME_TYPE          pname         ;
        PARAMS_TYPE         params        ;
        GetActiveUniformsiv(
            PROGRAM_TYPE        const&program       ,
            UNIFORMCOUNT_TYPE   const&uniformCount  ,
            UNIFORMINDICES_TYPE const&uniformIndices,
            PNAME_TYPE          const&pname         ,
            PARAMS_TYPE         const&params        ){
          this->program        = program       ;
          this->uniformCount   = uniformCount  ;
          this->uniformIndices = uniformIndices;
          this->pname          = pname         ;
          this->params         = params        ;
        }
        virtual~GetActiveUniformsiv(){}
        virtual void operator()(){
          glGetActiveUniformsiv(
            ge::core::convertTo<GLuint       >(this->program       ),
            ge::core::convertTo<GLsizei      >(this->uniformCount  ),
            ge::core::convertTo<const GLuint*>(this->uniformIndices),
            ge::core::convertTo<GLenum       >(this->pname         ),
            ge::core::convertTo<GLint*       >(this->params        )
          );
        }
    };

    template<
      typename PROGRAM_TYPE   = GLuint         ,
      typename LOCATION_TYPE  = GLint          ,
      typename COUNT_TYPE     = GLsizei        ,
      typename TRANSPOSE_TYPE = GLboolean      ,
      typename VALUE_TYPE     = const GLdouble*>
    class ProgramUniformMatrix2x3dv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program"  )return(void*)&this->program  ;
          if(name == "location" )return(void*)&this->location ;
          if(name == "count"    )return(void*)&this->count    ;
          if(name == "transpose")return(void*)&this->transpose;
          if(name == "value"    )return(void*)&this->value    ;
          return NULL;
        }
      public:
        PROGRAM_TYPE   program  ;
        LOCATION_TYPE  location ;
        COUNT_TYPE     count    ;
        TRANSPOSE_TYPE transpose;
        VALUE_TYPE     value    ;
        ProgramUniformMatrix2x3dv(
            PROGRAM_TYPE   const&program  ,
            LOCATION_TYPE  const&location ,
            COUNT_TYPE     const&count    ,
            TRANSPOSE_TYPE const&transpose,
            VALUE_TYPE     const&value    ){
          this->program   = program  ;
          this->location  = location ;
          this->count     = count    ;
          this->transpose = transpose;
          this->value     = value    ;
        }
        virtual~ProgramUniformMatrix2x3dv(){}
        virtual void operator()(){
          glProgramUniformMatrix2x3dv(
            ge::core::convertTo<GLuint         >(this->program  ),
            ge::core::convertTo<GLint          >(this->location ),
            ge::core::convertTo<GLsizei        >(this->count    ),
            ge::core::convertTo<GLboolean      >(this->transpose),
            ge::core::convertTo<const GLdouble*>(this->value    )
          );
        }
    };

    template<
      typename PROGRAM_TYPE  = GLuint       ,
      typename LOCATION_TYPE = GLint        ,
      typename COUNT_TYPE    = GLsizei      ,
      typename VALUE_TYPE    = const GLuint*>
    class ProgramUniform3uiv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program" )return(void*)&this->program ;
          if(name == "location")return(void*)&this->location;
          if(name == "count"   )return(void*)&this->count   ;
          if(name == "value"   )return(void*)&this->value   ;
          return NULL;
        }
      public:
        PROGRAM_TYPE  program ;
        LOCATION_TYPE location;
        COUNT_TYPE    count   ;
        VALUE_TYPE    value   ;
        ProgramUniform3uiv(
            PROGRAM_TYPE  const&program ,
            LOCATION_TYPE const&location,
            COUNT_TYPE    const&count   ,
            VALUE_TYPE    const&value   ){
          this->program  = program ;
          this->location = location;
          this->count    = count   ;
          this->value    = value   ;
        }
        virtual~ProgramUniform3uiv(){}
        virtual void operator()(){
          glProgramUniform3uiv(
            ge::core::convertTo<GLuint       >(this->program ),
            ge::core::convertTo<GLint        >(this->location),
            ge::core::convertTo<GLsizei      >(this->count   ),
            ge::core::convertTo<const GLuint*>(this->value   )
          );
        }
    };

    template<
      typename LOCATION_TYPE = GLint       ,
      typename COUNT_TYPE    = GLsizei     ,
      typename VALUE_TYPE    = const GLint*>
    class Uniform2iv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "location")return(void*)&this->location;
          if(name == "count"   )return(void*)&this->count   ;
          if(name == "value"   )return(void*)&this->value   ;
          return NULL;
        }
      public:
        LOCATION_TYPE location;
        COUNT_TYPE    count   ;
        VALUE_TYPE    value   ;
        Uniform2iv(
            LOCATION_TYPE const&location,
            COUNT_TYPE    const&count   ,
            VALUE_TYPE    const&value   ){
          this->location = location;
          this->count    = count   ;
          this->value    = value   ;
        }
        virtual~Uniform2iv(){}
        virtual void operator()(){
          glUniform2iv(
            ge::core::convertTo<GLint       >(this->location),
            ge::core::convertTo<GLsizei     >(this->count   ),
            ge::core::convertTo<const GLint*>(this->value   )
          );
        }
    };

    template<
      typename PROGRAM_TYPE  = GLuint       ,
      typename LOCATION_TYPE = GLint        ,
      typename COUNT_TYPE    = GLsizei      ,
      typename VALUE_TYPE    = const GLuint*>
    class ProgramUniform2uiv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program" )return(void*)&this->program ;
          if(name == "location")return(void*)&this->location;
          if(name == "count"   )return(void*)&this->count   ;
          if(name == "value"   )return(void*)&this->value   ;
          return NULL;
        }
      public:
        PROGRAM_TYPE  program ;
        LOCATION_TYPE location;
        COUNT_TYPE    count   ;
        VALUE_TYPE    value   ;
        ProgramUniform2uiv(
            PROGRAM_TYPE  const&program ,
            LOCATION_TYPE const&location,
            COUNT_TYPE    const&count   ,
            VALUE_TYPE    const&value   ){
          this->program  = program ;
          this->location = location;
          this->count    = count   ;
          this->value    = value   ;
        }
        virtual~ProgramUniform2uiv(){}
        virtual void operator()(){
          glProgramUniform2uiv(
            ge::core::convertTo<GLuint       >(this->program ),
            ge::core::convertTo<GLint        >(this->location),
            ge::core::convertTo<GLsizei      >(this->count   ),
            ge::core::convertTo<const GLuint*>(this->value   )
          );
        }
    };

    template<
      typename PROGRAM_TYPE  = GLuint,
      typename LOCATION_TYPE = GLint ,
      typename V0_TYPE       = GLint ,
      typename V1_TYPE       = GLint ,
      typename V2_TYPE       = GLint >
    class ProgramUniform3i:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program" )return(void*)&this->program ;
          if(name == "location")return(void*)&this->location;
          if(name == "v0"      )return(void*)&this->v0      ;
          if(name == "v1"      )return(void*)&this->v1      ;
          if(name == "v2"      )return(void*)&this->v2      ;
          return NULL;
        }
      public:
        PROGRAM_TYPE  program ;
        LOCATION_TYPE location;
        V0_TYPE       v0      ;
        V1_TYPE       v1      ;
        V2_TYPE       v2      ;
        ProgramUniform3i(
            PROGRAM_TYPE  const&program ,
            LOCATION_TYPE const&location,
            V0_TYPE       const&v0      ,
            V1_TYPE       const&v1      ,
            V2_TYPE       const&v2      ){
          this->program  = program ;
          this->location = location;
          this->v0       = v0      ;
          this->v1       = v1      ;
          this->v2       = v2      ;
        }
        virtual~ProgramUniform3i(){}
        virtual void operator()(){
          glProgramUniform3i(
            ge::core::convertTo<GLuint>(this->program ),
            ge::core::convertTo<GLint >(this->location),
            ge::core::convertTo<GLint >(this->v0      ),
            ge::core::convertTo<GLint >(this->v1      ),
            ge::core::convertTo<GLint >(this->v2      )
          );
        }
    };

    template<
      typename PROGRAM_TYPE  = GLuint  ,
      typename LOCATION_TYPE = GLint   ,
      typename V0_TYPE       = GLdouble,
      typename V1_TYPE       = GLdouble,
      typename V2_TYPE       = GLdouble>
    class ProgramUniform3d:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program" )return(void*)&this->program ;
          if(name == "location")return(void*)&this->location;
          if(name == "v0"      )return(void*)&this->v0      ;
          if(name == "v1"      )return(void*)&this->v1      ;
          if(name == "v2"      )return(void*)&this->v2      ;
          return NULL;
        }
      public:
        PROGRAM_TYPE  program ;
        LOCATION_TYPE location;
        V0_TYPE       v0      ;
        V1_TYPE       v1      ;
        V2_TYPE       v2      ;
        ProgramUniform3d(
            PROGRAM_TYPE  const&program ,
            LOCATION_TYPE const&location,
            V0_TYPE       const&v0      ,
            V1_TYPE       const&v1      ,
            V2_TYPE       const&v2      ){
          this->program  = program ;
          this->location = location;
          this->v0       = v0      ;
          this->v1       = v1      ;
          this->v2       = v2      ;
        }
        virtual~ProgramUniform3d(){}
        virtual void operator()(){
          glProgramUniform3d(
            ge::core::convertTo<GLuint  >(this->program ),
            ge::core::convertTo<GLint   >(this->location),
            ge::core::convertTo<GLdouble>(this->v0      ),
            ge::core::convertTo<GLdouble>(this->v1      ),
            ge::core::convertTo<GLdouble>(this->v2      )
          );
        }
    };

    template<
      typename PROGRAM_TYPE   = GLuint         ,
      typename LOCATION_TYPE  = GLint          ,
      typename COUNT_TYPE     = GLsizei        ,
      typename TRANSPOSE_TYPE = GLboolean      ,
      typename VALUE_TYPE     = const GLdouble*>
    class ProgramUniformMatrix3dv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program"  )return(void*)&this->program  ;
          if(name == "location" )return(void*)&this->location ;
          if(name == "count"    )return(void*)&this->count    ;
          if(name == "transpose")return(void*)&this->transpose;
          if(name == "value"    )return(void*)&this->value    ;
          return NULL;
        }
      public:
        PROGRAM_TYPE   program  ;
        LOCATION_TYPE  location ;
        COUNT_TYPE     count    ;
        TRANSPOSE_TYPE transpose;
        VALUE_TYPE     value    ;
        ProgramUniformMatrix3dv(
            PROGRAM_TYPE   const&program  ,
            LOCATION_TYPE  const&location ,
            COUNT_TYPE     const&count    ,
            TRANSPOSE_TYPE const&transpose,
            VALUE_TYPE     const&value    ){
          this->program   = program  ;
          this->location  = location ;
          this->count     = count    ;
          this->transpose = transpose;
          this->value     = value    ;
        }
        virtual~ProgramUniformMatrix3dv(){}
        virtual void operator()(){
          glProgramUniformMatrix3dv(
            ge::core::convertTo<GLuint         >(this->program  ),
            ge::core::convertTo<GLint          >(this->location ),
            ge::core::convertTo<GLsizei        >(this->count    ),
            ge::core::convertTo<GLboolean      >(this->transpose),
            ge::core::convertTo<const GLdouble*>(this->value    )
          );
        }
    };

    template<
      typename LOCATION_TYPE = GLint  ,
      typename V0_TYPE       = GLfloat,
      typename V1_TYPE       = GLfloat>
    class Uniform2f:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "location")return(void*)&this->location;
          if(name == "v0"      )return(void*)&this->v0      ;
          if(name == "v1"      )return(void*)&this->v1      ;
          return NULL;
        }
      public:
        LOCATION_TYPE location;
        V0_TYPE       v0      ;
        V1_TYPE       v1      ;
        Uniform2f(
            LOCATION_TYPE const&location,
            V0_TYPE       const&v0      ,
            V1_TYPE       const&v1      ){
          this->location = location;
          this->v0       = v0      ;
          this->v1       = v1      ;
        }
        virtual~Uniform2f(){}
        virtual void operator()(){
          glUniform2f(
            ge::core::convertTo<GLint  >(this->location),
            ge::core::convertTo<GLfloat>(this->v0      ),
            ge::core::convertTo<GLfloat>(this->v1      )
          );
        }
    };

    template<
      typename LOCATION_TYPE = GLint       ,
      typename COUNT_TYPE    = GLsizei     ,
      typename VALUE_TYPE    = const GLint*>
    class Uniform1iv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "location")return(void*)&this->location;
          if(name == "count"   )return(void*)&this->count   ;
          if(name == "value"   )return(void*)&this->value   ;
          return NULL;
        }
      public:
        LOCATION_TYPE location;
        COUNT_TYPE    count   ;
        VALUE_TYPE    value   ;
        Uniform1iv(
            LOCATION_TYPE const&location,
            COUNT_TYPE    const&count   ,
            VALUE_TYPE    const&value   ){
          this->location = location;
          this->count    = count   ;
          this->value    = value   ;
        }
        virtual~Uniform1iv(){}
        virtual void operator()(){
          glUniform1iv(
            ge::core::convertTo<GLint       >(this->location),
            ge::core::convertTo<GLsizei     >(this->count   ),
            ge::core::convertTo<const GLint*>(this->value   )
          );
        }
    };

    template<
      typename LOCATION_TYPE  = GLint          ,
      typename COUNT_TYPE     = GLsizei        ,
      typename TRANSPOSE_TYPE = GLboolean      ,
      typename VALUE_TYPE     = const GLdouble*>
    class UniformMatrix2x4dv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "location" )return(void*)&this->location ;
          if(name == "count"    )return(void*)&this->count    ;
          if(name == "transpose")return(void*)&this->transpose;
          if(name == "value"    )return(void*)&this->value    ;
          return NULL;
        }
      public:
        LOCATION_TYPE  location ;
        COUNT_TYPE     count    ;
        TRANSPOSE_TYPE transpose;
        VALUE_TYPE     value    ;
        UniformMatrix2x4dv(
            LOCATION_TYPE  const&location ,
            COUNT_TYPE     const&count    ,
            TRANSPOSE_TYPE const&transpose,
            VALUE_TYPE     const&value    ){
          this->location  = location ;
          this->count     = count    ;
          this->transpose = transpose;
          this->value     = value    ;
        }
        virtual~UniformMatrix2x4dv(){}
        virtual void operator()(){
          glUniformMatrix2x4dv(
            ge::core::convertTo<GLint          >(this->location ),
            ge::core::convertTo<GLsizei        >(this->count    ),
            ge::core::convertTo<GLboolean      >(this->transpose),
            ge::core::convertTo<const GLdouble*>(this->value    )
          );
        }
    };

    template<
      typename LOCATION_TYPE = GLint,
      typename V0_TYPE       = GLint,
      typename V1_TYPE       = GLint,
      typename V2_TYPE       = GLint,
      typename V3_TYPE       = GLint>
    class Uniform4i:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "location")return(void*)&this->location;
          if(name == "v0"      )return(void*)&this->v0      ;
          if(name == "v1"      )return(void*)&this->v1      ;
          if(name == "v2"      )return(void*)&this->v2      ;
          if(name == "v3"      )return(void*)&this->v3      ;
          return NULL;
        }
      public:
        LOCATION_TYPE location;
        V0_TYPE       v0      ;
        V1_TYPE       v1      ;
        V2_TYPE       v2      ;
        V3_TYPE       v3      ;
        Uniform4i(
            LOCATION_TYPE const&location,
            V0_TYPE       const&v0      ,
            V1_TYPE       const&v1      ,
            V2_TYPE       const&v2      ,
            V3_TYPE       const&v3      ){
          this->location = location;
          this->v0       = v0      ;
          this->v1       = v1      ;
          this->v2       = v2      ;
          this->v3       = v3      ;
        }
        virtual~Uniform4i(){}
        virtual void operator()(){
          glUniform4i(
            ge::core::convertTo<GLint>(this->location),
            ge::core::convertTo<GLint>(this->v0      ),
            ge::core::convertTo<GLint>(this->v1      ),
            ge::core::convertTo<GLint>(this->v2      ),
            ge::core::convertTo<GLint>(this->v3      )
          );
        }
    };

    template<
      typename LOCATION_TYPE = GLint,
      typename V0_TYPE       = GLint,
      typename V1_TYPE       = GLint>
    class Uniform2i:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "location")return(void*)&this->location;
          if(name == "v0"      )return(void*)&this->v0      ;
          if(name == "v1"      )return(void*)&this->v1      ;
          return NULL;
        }
      public:
        LOCATION_TYPE location;
        V0_TYPE       v0      ;
        V1_TYPE       v1      ;
        Uniform2i(
            LOCATION_TYPE const&location,
            V0_TYPE       const&v0      ,
            V1_TYPE       const&v1      ){
          this->location = location;
          this->v0       = v0      ;
          this->v1       = v1      ;
        }
        virtual~Uniform2i(){}
        virtual void operator()(){
          glUniform2i(
            ge::core::convertTo<GLint>(this->location),
            ge::core::convertTo<GLint>(this->v0      ),
            ge::core::convertTo<GLint>(this->v1      )
          );
        }
    };

    template<
      typename PROGRAM_TYPE  = GLuint         ,
      typename LOCATION_TYPE = GLint          ,
      typename COUNT_TYPE    = GLsizei        ,
      typename VALUE_TYPE    = const GLdouble*>
    class ProgramUniform2dv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program" )return(void*)&this->program ;
          if(name == "location")return(void*)&this->location;
          if(name == "count"   )return(void*)&this->count   ;
          if(name == "value"   )return(void*)&this->value   ;
          return NULL;
        }
      public:
        PROGRAM_TYPE  program ;
        LOCATION_TYPE location;
        COUNT_TYPE    count   ;
        VALUE_TYPE    value   ;
        ProgramUniform2dv(
            PROGRAM_TYPE  const&program ,
            LOCATION_TYPE const&location,
            COUNT_TYPE    const&count   ,
            VALUE_TYPE    const&value   ){
          this->program  = program ;
          this->location = location;
          this->count    = count   ;
          this->value    = value   ;
        }
        virtual~ProgramUniform2dv(){}
        virtual void operator()(){
          glProgramUniform2dv(
            ge::core::convertTo<GLuint         >(this->program ),
            ge::core::convertTo<GLint          >(this->location),
            ge::core::convertTo<GLsizei        >(this->count   ),
            ge::core::convertTo<const GLdouble*>(this->value   )
          );
        }
    };

    template<
      typename PROGRAM_TYPE  = GLuint      ,
      typename LOCATION_TYPE = GLint       ,
      typename COUNT_TYPE    = GLsizei     ,
      typename VALUE_TYPE    = const GLint*>
    class ProgramUniform3iv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program" )return(void*)&this->program ;
          if(name == "location")return(void*)&this->location;
          if(name == "count"   )return(void*)&this->count   ;
          if(name == "value"   )return(void*)&this->value   ;
          return NULL;
        }
      public:
        PROGRAM_TYPE  program ;
        LOCATION_TYPE location;
        COUNT_TYPE    count   ;
        VALUE_TYPE    value   ;
        ProgramUniform3iv(
            PROGRAM_TYPE  const&program ,
            LOCATION_TYPE const&location,
            COUNT_TYPE    const&count   ,
            VALUE_TYPE    const&value   ){
          this->program  = program ;
          this->location = location;
          this->count    = count   ;
          this->value    = value   ;
        }
        virtual~ProgramUniform3iv(){}
        virtual void operator()(){
          glProgramUniform3iv(
            ge::core::convertTo<GLuint      >(this->program ),
            ge::core::convertTo<GLint       >(this->location),
            ge::core::convertTo<GLsizei     >(this->count   ),
            ge::core::convertTo<const GLint*>(this->value   )
          );
        }
    };

    template<
      typename PROGRAM_TYPE  = GLuint ,
      typename LOCATION_TYPE = GLint  ,
      typename BUFSIZE_TYPE  = GLsizei,
      typename PARAMS_TYPE   = GLuint*>
    class GetnUniformuiv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program" )return(void*)&this->program ;
          if(name == "location")return(void*)&this->location;
          if(name == "bufSize" )return(void*)&this->bufSize ;
          if(name == "params"  )return(void*)&this->params  ;
          return NULL;
        }
      public:
        PROGRAM_TYPE  program ;
        LOCATION_TYPE location;
        BUFSIZE_TYPE  bufSize ;
        PARAMS_TYPE   params  ;
        GetnUniformuiv(
            PROGRAM_TYPE  const&program ,
            LOCATION_TYPE const&location,
            BUFSIZE_TYPE  const&bufSize ,
            PARAMS_TYPE   const&params  ){
          this->program  = program ;
          this->location = location;
          this->bufSize  = bufSize ;
          this->params   = params  ;
        }
        virtual~GetnUniformuiv(){}
        virtual void operator()(){
          glGetnUniformuiv(
            ge::core::convertTo<GLuint >(this->program ),
            ge::core::convertTo<GLint  >(this->location),
            ge::core::convertTo<GLsizei>(this->bufSize ),
            ge::core::convertTo<GLuint*>(this->params  )
          );
        }
    };

    template<
      typename PROGRAM_TYPE   = GLuint        ,
      typename LOCATION_TYPE  = GLint         ,
      typename COUNT_TYPE     = GLsizei       ,
      typename TRANSPOSE_TYPE = GLboolean     ,
      typename VALUE_TYPE     = const GLfloat*>
    class ProgramUniformMatrix4fv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program"  )return(void*)&this->program  ;
          if(name == "location" )return(void*)&this->location ;
          if(name == "count"    )return(void*)&this->count    ;
          if(name == "transpose")return(void*)&this->transpose;
          if(name == "value"    )return(void*)&this->value    ;
          return NULL;
        }
      public:
        PROGRAM_TYPE   program  ;
        LOCATION_TYPE  location ;
        COUNT_TYPE     count    ;
        TRANSPOSE_TYPE transpose;
        VALUE_TYPE     value    ;
        ProgramUniformMatrix4fv(
            PROGRAM_TYPE   const&program  ,
            LOCATION_TYPE  const&location ,
            COUNT_TYPE     const&count    ,
            TRANSPOSE_TYPE const&transpose,
            VALUE_TYPE     const&value    ){
          this->program   = program  ;
          this->location  = location ;
          this->count     = count    ;
          this->transpose = transpose;
          this->value     = value    ;
        }
        virtual~ProgramUniformMatrix4fv(){}
        virtual void operator()(){
          glProgramUniformMatrix4fv(
            ge::core::convertTo<GLuint        >(this->program  ),
            ge::core::convertTo<GLint         >(this->location ),
            ge::core::convertTo<GLsizei       >(this->count    ),
            ge::core::convertTo<GLboolean     >(this->transpose),
            ge::core::convertTo<const GLfloat*>(this->value    )
          );
        }
    };

    template<
      typename PROGRAM_TYPE   = GLuint         ,
      typename LOCATION_TYPE  = GLint          ,
      typename COUNT_TYPE     = GLsizei        ,
      typename TRANSPOSE_TYPE = GLboolean      ,
      typename VALUE_TYPE     = const GLdouble*>
    class ProgramUniformMatrix4dv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program"  )return(void*)&this->program  ;
          if(name == "location" )return(void*)&this->location ;
          if(name == "count"    )return(void*)&this->count    ;
          if(name == "transpose")return(void*)&this->transpose;
          if(name == "value"    )return(void*)&this->value    ;
          return NULL;
        }
      public:
        PROGRAM_TYPE   program  ;
        LOCATION_TYPE  location ;
        COUNT_TYPE     count    ;
        TRANSPOSE_TYPE transpose;
        VALUE_TYPE     value    ;
        ProgramUniformMatrix4dv(
            PROGRAM_TYPE   const&program  ,
            LOCATION_TYPE  const&location ,
            COUNT_TYPE     const&count    ,
            TRANSPOSE_TYPE const&transpose,
            VALUE_TYPE     const&value    ){
          this->program   = program  ;
          this->location  = location ;
          this->count     = count    ;
          this->transpose = transpose;
          this->value     = value    ;
        }
        virtual~ProgramUniformMatrix4dv(){}
        virtual void operator()(){
          glProgramUniformMatrix4dv(
            ge::core::convertTo<GLuint         >(this->program  ),
            ge::core::convertTo<GLint          >(this->location ),
            ge::core::convertTo<GLsizei        >(this->count    ),
            ge::core::convertTo<GLboolean      >(this->transpose),
            ge::core::convertTo<const GLdouble*>(this->value    )
          );
        }
    };

    template<
      typename LOCATION_TYPE  = GLint         ,
      typename COUNT_TYPE     = GLsizei       ,
      typename TRANSPOSE_TYPE = GLboolean     ,
      typename VALUE_TYPE     = const GLfloat*>
    class UniformMatrix4x2fv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "location" )return(void*)&this->location ;
          if(name == "count"    )return(void*)&this->count    ;
          if(name == "transpose")return(void*)&this->transpose;
          if(name == "value"    )return(void*)&this->value    ;
          return NULL;
        }
      public:
        LOCATION_TYPE  location ;
        COUNT_TYPE     count    ;
        TRANSPOSE_TYPE transpose;
        VALUE_TYPE     value    ;
        UniformMatrix4x2fv(
            LOCATION_TYPE  const&location ,
            COUNT_TYPE     const&count    ,
            TRANSPOSE_TYPE const&transpose,
            VALUE_TYPE     const&value    ){
          this->location  = location ;
          this->count     = count    ;
          this->transpose = transpose;
          this->value     = value    ;
        }
        virtual~UniformMatrix4x2fv(){}
        virtual void operator()(){
          glUniformMatrix4x2fv(
            ge::core::convertTo<GLint         >(this->location ),
            ge::core::convertTo<GLsizei       >(this->count    ),
            ge::core::convertTo<GLboolean     >(this->transpose),
            ge::core::convertTo<const GLfloat*>(this->value    )
          );
        }
    };

    template<
      typename LOCATION_TYPE  = GLint         ,
      typename COUNT_TYPE     = GLsizei       ,
      typename TRANSPOSE_TYPE = GLboolean     ,
      typename VALUE_TYPE     = const GLfloat*>
    class UniformMatrix2x3fv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "location" )return(void*)&this->location ;
          if(name == "count"    )return(void*)&this->count    ;
          if(name == "transpose")return(void*)&this->transpose;
          if(name == "value"    )return(void*)&this->value    ;
          return NULL;
        }
      public:
        LOCATION_TYPE  location ;
        COUNT_TYPE     count    ;
        TRANSPOSE_TYPE transpose;
        VALUE_TYPE     value    ;
        UniformMatrix2x3fv(
            LOCATION_TYPE  const&location ,
            COUNT_TYPE     const&count    ,
            TRANSPOSE_TYPE const&transpose,
            VALUE_TYPE     const&value    ){
          this->location  = location ;
          this->count     = count    ;
          this->transpose = transpose;
          this->value     = value    ;
        }
        virtual~UniformMatrix2x3fv(){}
        virtual void operator()(){
          glUniformMatrix2x3fv(
            ge::core::convertTo<GLint         >(this->location ),
            ge::core::convertTo<GLsizei       >(this->count    ),
            ge::core::convertTo<GLboolean     >(this->transpose),
            ge::core::convertTo<const GLfloat*>(this->value    )
          );
        }
    };

    template<
      typename LOCATION_TYPE = GLint          ,
      typename COUNT_TYPE    = GLsizei        ,
      typename VALUE_TYPE    = const GLdouble*>
    class Uniform4dv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "location")return(void*)&this->location;
          if(name == "count"   )return(void*)&this->count   ;
          if(name == "value"   )return(void*)&this->value   ;
          return NULL;
        }
      public:
        LOCATION_TYPE location;
        COUNT_TYPE    count   ;
        VALUE_TYPE    value   ;
        Uniform4dv(
            LOCATION_TYPE const&location,
            COUNT_TYPE    const&count   ,
            VALUE_TYPE    const&value   ){
          this->location = location;
          this->count    = count   ;
          this->value    = value   ;
        }
        virtual~Uniform4dv(){}
        virtual void operator()(){
          glUniform4dv(
            ge::core::convertTo<GLint          >(this->location),
            ge::core::convertTo<GLsizei        >(this->count   ),
            ge::core::convertTo<const GLdouble*>(this->value   )
          );
        }
    };

    template<
      typename PROGRAM_TYPE   = GLuint        ,
      typename LOCATION_TYPE  = GLint         ,
      typename COUNT_TYPE     = GLsizei       ,
      typename TRANSPOSE_TYPE = GLboolean     ,
      typename VALUE_TYPE     = const GLfloat*>
    class ProgramUniformMatrix3x4fv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program"  )return(void*)&this->program  ;
          if(name == "location" )return(void*)&this->location ;
          if(name == "count"    )return(void*)&this->count    ;
          if(name == "transpose")return(void*)&this->transpose;
          if(name == "value"    )return(void*)&this->value    ;
          return NULL;
        }
      public:
        PROGRAM_TYPE   program  ;
        LOCATION_TYPE  location ;
        COUNT_TYPE     count    ;
        TRANSPOSE_TYPE transpose;
        VALUE_TYPE     value    ;
        ProgramUniformMatrix3x4fv(
            PROGRAM_TYPE   const&program  ,
            LOCATION_TYPE  const&location ,
            COUNT_TYPE     const&count    ,
            TRANSPOSE_TYPE const&transpose,
            VALUE_TYPE     const&value    ){
          this->program   = program  ;
          this->location  = location ;
          this->count     = count    ;
          this->transpose = transpose;
          this->value     = value    ;
        }
        virtual~ProgramUniformMatrix3x4fv(){}
        virtual void operator()(){
          glProgramUniformMatrix3x4fv(
            ge::core::convertTo<GLuint        >(this->program  ),
            ge::core::convertTo<GLint         >(this->location ),
            ge::core::convertTo<GLsizei       >(this->count    ),
            ge::core::convertTo<GLboolean     >(this->transpose),
            ge::core::convertTo<const GLfloat*>(this->value    )
          );
        }
    };

    template<
      typename PROGRAM_TYPE  = GLuint       ,
      typename LOCATION_TYPE = GLint        ,
      typename COUNT_TYPE    = GLsizei      ,
      typename VALUE_TYPE    = const GLuint*>
    class ProgramUniform1uiv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program" )return(void*)&this->program ;
          if(name == "location")return(void*)&this->location;
          if(name == "count"   )return(void*)&this->count   ;
          if(name == "value"   )return(void*)&this->value   ;
          return NULL;
        }
      public:
        PROGRAM_TYPE  program ;
        LOCATION_TYPE location;
        COUNT_TYPE    count   ;
        VALUE_TYPE    value   ;
        ProgramUniform1uiv(
            PROGRAM_TYPE  const&program ,
            LOCATION_TYPE const&location,
            COUNT_TYPE    const&count   ,
            VALUE_TYPE    const&value   ){
          this->program  = program ;
          this->location = location;
          this->count    = count   ;
          this->value    = value   ;
        }
        virtual~ProgramUniform1uiv(){}
        virtual void operator()(){
          glProgramUniform1uiv(
            ge::core::convertTo<GLuint       >(this->program ),
            ge::core::convertTo<GLint        >(this->location),
            ge::core::convertTo<GLsizei      >(this->count   ),
            ge::core::convertTo<const GLuint*>(this->value   )
          );
        }
    };

    template<
      typename PROGRAM_TYPE  = GLuint ,
      typename LOCATION_TYPE = GLint  ,
      typename PARAMS_TYPE   = GLuint*>
    class GetUniformuiv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program" )return(void*)&this->program ;
          if(name == "location")return(void*)&this->location;
          if(name == "params"  )return(void*)&this->params  ;
          return NULL;
        }
      public:
        PROGRAM_TYPE  program ;
        LOCATION_TYPE location;
        PARAMS_TYPE   params  ;
        GetUniformuiv(
            PROGRAM_TYPE  const&program ,
            LOCATION_TYPE const&location,
            PARAMS_TYPE   const&params  ){
          this->program  = program ;
          this->location = location;
          this->params   = params  ;
        }
        virtual~GetUniformuiv(){}
        virtual void operator()(){
          glGetUniformuiv(
            ge::core::convertTo<GLuint >(this->program ),
            ge::core::convertTo<GLint  >(this->location),
            ge::core::convertTo<GLuint*>(this->params  )
          );
        }
    };

    template<
      typename LOCATION_TYPE  = GLint         ,
      typename COUNT_TYPE     = GLsizei       ,
      typename TRANSPOSE_TYPE = GLboolean     ,
      typename VALUE_TYPE     = const GLfloat*>
    class UniformMatrix4fv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "location" )return(void*)&this->location ;
          if(name == "count"    )return(void*)&this->count    ;
          if(name == "transpose")return(void*)&this->transpose;
          if(name == "value"    )return(void*)&this->value    ;
          return NULL;
        }
      public:
        LOCATION_TYPE  location ;
        COUNT_TYPE     count    ;
        TRANSPOSE_TYPE transpose;
        VALUE_TYPE     value    ;
        UniformMatrix4fv(
            LOCATION_TYPE  const&location ,
            COUNT_TYPE     const&count    ,
            TRANSPOSE_TYPE const&transpose,
            VALUE_TYPE     const&value    ){
          this->location  = location ;
          this->count     = count    ;
          this->transpose = transpose;
          this->value     = value    ;
        }
        virtual~UniformMatrix4fv(){}
        virtual void operator()(){
          glUniformMatrix4fv(
            ge::core::convertTo<GLint         >(this->location ),
            ge::core::convertTo<GLsizei       >(this->count    ),
            ge::core::convertTo<GLboolean     >(this->transpose),
            ge::core::convertTo<const GLfloat*>(this->value    )
          );
        }
    };

    template<
      typename RET_TYPE              = GLuint       ,
      typename PROGRAM_TYPE          = GLuint       ,
      typename UNIFORMBLOCKNAME_TYPE = const GLchar*>
    class GetUniformBlockIndex:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "ret"             )return(void*)&this->ret             ;
          if(name == "program"         )return(void*)&this->program         ;
          if(name == "uniformBlockName")return(void*)&this->uniformBlockName;
          return NULL;
        }
      public:
        RET_TYPE              ret             ;
        PROGRAM_TYPE          program         ;
        UNIFORMBLOCKNAME_TYPE uniformBlockName;
        GetUniformBlockIndex(
            RET_TYPE              const&ret             ,
            PROGRAM_TYPE          const&program         ,
            UNIFORMBLOCKNAME_TYPE const&uniformBlockName){
          this->ret              = ret             ;
          this->program          = program         ;
          this->uniformBlockName = uniformBlockName;
        }
        virtual~GetUniformBlockIndex(){}
        virtual void operator()(){
          ge::core::convertFrom<GLuint>(this->ret,glGetUniformBlockIndex(
              ge::core::convertTo<GLuint       >(this->program         ),
              ge::core::convertTo<const GLchar*>(this->uniformBlockName))
          );
        }
    };

    template<
      typename LOCATION_TYPE  = GLint         ,
      typename COUNT_TYPE     = GLsizei       ,
      typename TRANSPOSE_TYPE = GLboolean     ,
      typename VALUE_TYPE     = const GLfloat*>
    class UniformMatrix2x4fv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "location" )return(void*)&this->location ;
          if(name == "count"    )return(void*)&this->count    ;
          if(name == "transpose")return(void*)&this->transpose;
          if(name == "value"    )return(void*)&this->value    ;
          return NULL;
        }
      public:
        LOCATION_TYPE  location ;
        COUNT_TYPE     count    ;
        TRANSPOSE_TYPE transpose;
        VALUE_TYPE     value    ;
        UniformMatrix2x4fv(
            LOCATION_TYPE  const&location ,
            COUNT_TYPE     const&count    ,
            TRANSPOSE_TYPE const&transpose,
            VALUE_TYPE     const&value    ){
          this->location  = location ;
          this->count     = count    ;
          this->transpose = transpose;
          this->value     = value    ;
        }
        virtual~UniformMatrix2x4fv(){}
        virtual void operator()(){
          glUniformMatrix2x4fv(
            ge::core::convertTo<GLint         >(this->location ),
            ge::core::convertTo<GLsizei       >(this->count    ),
            ge::core::convertTo<GLboolean     >(this->transpose),
            ge::core::convertTo<const GLfloat*>(this->value    )
          );
        }
    };

    template<
      typename PROGRAM_TYPE   = GLuint        ,
      typename LOCATION_TYPE  = GLint         ,
      typename COUNT_TYPE     = GLsizei       ,
      typename TRANSPOSE_TYPE = GLboolean     ,
      typename VALUE_TYPE     = const GLfloat*>
    class ProgramUniformMatrix2fv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program"  )return(void*)&this->program  ;
          if(name == "location" )return(void*)&this->location ;
          if(name == "count"    )return(void*)&this->count    ;
          if(name == "transpose")return(void*)&this->transpose;
          if(name == "value"    )return(void*)&this->value    ;
          return NULL;
        }
      public:
        PROGRAM_TYPE   program  ;
        LOCATION_TYPE  location ;
        COUNT_TYPE     count    ;
        TRANSPOSE_TYPE transpose;
        VALUE_TYPE     value    ;
        ProgramUniformMatrix2fv(
            PROGRAM_TYPE   const&program  ,
            LOCATION_TYPE  const&location ,
            COUNT_TYPE     const&count    ,
            TRANSPOSE_TYPE const&transpose,
            VALUE_TYPE     const&value    ){
          this->program   = program  ;
          this->location  = location ;
          this->count     = count    ;
          this->transpose = transpose;
          this->value     = value    ;
        }
        virtual~ProgramUniformMatrix2fv(){}
        virtual void operator()(){
          glProgramUniformMatrix2fv(
            ge::core::convertTo<GLuint        >(this->program  ),
            ge::core::convertTo<GLint         >(this->location ),
            ge::core::convertTo<GLsizei       >(this->count    ),
            ge::core::convertTo<GLboolean     >(this->transpose),
            ge::core::convertTo<const GLfloat*>(this->value    )
          );
        }
    };

    template<
      typename PROGRAM_TYPE  = GLuint       ,
      typename LOCATION_TYPE = GLint        ,
      typename COUNT_TYPE    = GLsizei      ,
      typename VALUE_TYPE    = const GLuint*>
    class ProgramUniform4uiv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program" )return(void*)&this->program ;
          if(name == "location")return(void*)&this->location;
          if(name == "count"   )return(void*)&this->count   ;
          if(name == "value"   )return(void*)&this->value   ;
          return NULL;
        }
      public:
        PROGRAM_TYPE  program ;
        LOCATION_TYPE location;
        COUNT_TYPE    count   ;
        VALUE_TYPE    value   ;
        ProgramUniform4uiv(
            PROGRAM_TYPE  const&program ,
            LOCATION_TYPE const&location,
            COUNT_TYPE    const&count   ,
            VALUE_TYPE    const&value   ){
          this->program  = program ;
          this->location = location;
          this->count    = count   ;
          this->value    = value   ;
        }
        virtual~ProgramUniform4uiv(){}
        virtual void operator()(){
          glProgramUniform4uiv(
            ge::core::convertTo<GLuint       >(this->program ),
            ge::core::convertTo<GLint        >(this->location),
            ge::core::convertTo<GLsizei      >(this->count   ),
            ge::core::convertTo<const GLuint*>(this->value   )
          );
        }
    };

    template<
      typename PROGRAM_TYPE  = GLuint  ,
      typename LOCATION_TYPE = GLint   ,
      typename PARAMS_TYPE   = GLfloat*>
    class GetUniformfv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program" )return(void*)&this->program ;
          if(name == "location")return(void*)&this->location;
          if(name == "params"  )return(void*)&this->params  ;
          return NULL;
        }
      public:
        PROGRAM_TYPE  program ;
        LOCATION_TYPE location;
        PARAMS_TYPE   params  ;
        GetUniformfv(
            PROGRAM_TYPE  const&program ,
            LOCATION_TYPE const&location,
            PARAMS_TYPE   const&params  ){
          this->program  = program ;
          this->location = location;
          this->params   = params  ;
        }
        virtual~GetUniformfv(){}
        virtual void operator()(){
          glGetUniformfv(
            ge::core::convertTo<GLuint  >(this->program ),
            ge::core::convertTo<GLint   >(this->location),
            ge::core::convertTo<GLfloat*>(this->params  )
          );
        }
    };

    template<
      typename LOCATION_TYPE = GLint   ,
      typename X_TYPE        = GLdouble,
      typename Y_TYPE        = GLdouble,
      typename Z_TYPE        = GLdouble>
    class Uniform3d:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "location")return(void*)&this->location;
          if(name == "x"       )return(void*)&this->x       ;
          if(name == "y"       )return(void*)&this->y       ;
          if(name == "z"       )return(void*)&this->z       ;
          return NULL;
        }
      public:
        LOCATION_TYPE location;
        X_TYPE        x       ;
        Y_TYPE        y       ;
        Z_TYPE        z       ;
        Uniform3d(
            LOCATION_TYPE const&location,
            X_TYPE        const&x       ,
            Y_TYPE        const&y       ,
            Z_TYPE        const&z       ){
          this->location = location;
          this->x        = x       ;
          this->y        = y       ;
          this->z        = z       ;
        }
        virtual~Uniform3d(){}
        virtual void operator()(){
          glUniform3d(
            ge::core::convertTo<GLint   >(this->location),
            ge::core::convertTo<GLdouble>(this->x       ),
            ge::core::convertTo<GLdouble>(this->y       ),
            ge::core::convertTo<GLdouble>(this->z       )
          );
        }
    };

    template<
      typename PROGRAM_TYPE  = GLuint ,
      typename LOCATION_TYPE = GLint  ,
      typename V0_TYPE       = GLfloat,
      typename V1_TYPE       = GLfloat,
      typename V2_TYPE       = GLfloat,
      typename V3_TYPE       = GLfloat>
    class ProgramUniform4f:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program" )return(void*)&this->program ;
          if(name == "location")return(void*)&this->location;
          if(name == "v0"      )return(void*)&this->v0      ;
          if(name == "v1"      )return(void*)&this->v1      ;
          if(name == "v2"      )return(void*)&this->v2      ;
          if(name == "v3"      )return(void*)&this->v3      ;
          return NULL;
        }
      public:
        PROGRAM_TYPE  program ;
        LOCATION_TYPE location;
        V0_TYPE       v0      ;
        V1_TYPE       v1      ;
        V2_TYPE       v2      ;
        V3_TYPE       v3      ;
        ProgramUniform4f(
            PROGRAM_TYPE  const&program ,
            LOCATION_TYPE const&location,
            V0_TYPE       const&v0      ,
            V1_TYPE       const&v1      ,
            V2_TYPE       const&v2      ,
            V3_TYPE       const&v3      ){
          this->program  = program ;
          this->location = location;
          this->v0       = v0      ;
          this->v1       = v1      ;
          this->v2       = v2      ;
          this->v3       = v3      ;
        }
        virtual~ProgramUniform4f(){}
        virtual void operator()(){
          glProgramUniform4f(
            ge::core::convertTo<GLuint >(this->program ),
            ge::core::convertTo<GLint  >(this->location),
            ge::core::convertTo<GLfloat>(this->v0      ),
            ge::core::convertTo<GLfloat>(this->v1      ),
            ge::core::convertTo<GLfloat>(this->v2      ),
            ge::core::convertTo<GLfloat>(this->v3      )
          );
        }
    };

    template<
      typename PROGRAM_TYPE  = GLuint         ,
      typename LOCATION_TYPE = GLint          ,
      typename COUNT_TYPE    = GLsizei        ,
      typename VALUE_TYPE    = const GLdouble*>
    class ProgramUniform3dv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program" )return(void*)&this->program ;
          if(name == "location")return(void*)&this->location;
          if(name == "count"   )return(void*)&this->count   ;
          if(name == "value"   )return(void*)&this->value   ;
          return NULL;
        }
      public:
        PROGRAM_TYPE  program ;
        LOCATION_TYPE location;
        COUNT_TYPE    count   ;
        VALUE_TYPE    value   ;
        ProgramUniform3dv(
            PROGRAM_TYPE  const&program ,
            LOCATION_TYPE const&location,
            COUNT_TYPE    const&count   ,
            VALUE_TYPE    const&value   ){
          this->program  = program ;
          this->location = location;
          this->count    = count   ;
          this->value    = value   ;
        }
        virtual~ProgramUniform3dv(){}
        virtual void operator()(){
          glProgramUniform3dv(
            ge::core::convertTo<GLuint         >(this->program ),
            ge::core::convertTo<GLint          >(this->location),
            ge::core::convertTo<GLsizei        >(this->count   ),
            ge::core::convertTo<const GLdouble*>(this->value   )
          );
        }
    };

    template<
      typename LOCATION_TYPE  = GLint          ,
      typename COUNT_TYPE     = GLsizei        ,
      typename TRANSPOSE_TYPE = GLboolean      ,
      typename VALUE_TYPE     = const GLdouble*>
    class UniformMatrix4x3dv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "location" )return(void*)&this->location ;
          if(name == "count"    )return(void*)&this->count    ;
          if(name == "transpose")return(void*)&this->transpose;
          if(name == "value"    )return(void*)&this->value    ;
          return NULL;
        }
      public:
        LOCATION_TYPE  location ;
        COUNT_TYPE     count    ;
        TRANSPOSE_TYPE transpose;
        VALUE_TYPE     value    ;
        UniformMatrix4x3dv(
            LOCATION_TYPE  const&location ,
            COUNT_TYPE     const&count    ,
            TRANSPOSE_TYPE const&transpose,
            VALUE_TYPE     const&value    ){
          this->location  = location ;
          this->count     = count    ;
          this->transpose = transpose;
          this->value     = value    ;
        }
        virtual~UniformMatrix4x3dv(){}
        virtual void operator()(){
          glUniformMatrix4x3dv(
            ge::core::convertTo<GLint          >(this->location ),
            ge::core::convertTo<GLsizei        >(this->count    ),
            ge::core::convertTo<GLboolean      >(this->transpose),
            ge::core::convertTo<const GLdouble*>(this->value    )
          );
        }
    };

    template<
      typename PROGRAM_TYPE   = GLuint        ,
      typename LOCATION_TYPE  = GLint         ,
      typename COUNT_TYPE     = GLsizei       ,
      typename TRANSPOSE_TYPE = GLboolean     ,
      typename VALUE_TYPE     = const GLfloat*>
    class ProgramUniformMatrix3x2fv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program"  )return(void*)&this->program  ;
          if(name == "location" )return(void*)&this->location ;
          if(name == "count"    )return(void*)&this->count    ;
          if(name == "transpose")return(void*)&this->transpose;
          if(name == "value"    )return(void*)&this->value    ;
          return NULL;
        }
      public:
        PROGRAM_TYPE   program  ;
        LOCATION_TYPE  location ;
        COUNT_TYPE     count    ;
        TRANSPOSE_TYPE transpose;
        VALUE_TYPE     value    ;
        ProgramUniformMatrix3x2fv(
            PROGRAM_TYPE   const&program  ,
            LOCATION_TYPE  const&location ,
            COUNT_TYPE     const&count    ,
            TRANSPOSE_TYPE const&transpose,
            VALUE_TYPE     const&value    ){
          this->program   = program  ;
          this->location  = location ;
          this->count     = count    ;
          this->transpose = transpose;
          this->value     = value    ;
        }
        virtual~ProgramUniformMatrix3x2fv(){}
        virtual void operator()(){
          glProgramUniformMatrix3x2fv(
            ge::core::convertTo<GLuint        >(this->program  ),
            ge::core::convertTo<GLint         >(this->location ),
            ge::core::convertTo<GLsizei       >(this->count    ),
            ge::core::convertTo<GLboolean     >(this->transpose),
            ge::core::convertTo<const GLfloat*>(this->value    )
          );
        }
    };

    template<
      typename PROGRAM_TYPE   = GLuint         ,
      typename LOCATION_TYPE  = GLint          ,
      typename COUNT_TYPE     = GLsizei        ,
      typename TRANSPOSE_TYPE = GLboolean      ,
      typename VALUE_TYPE     = const GLdouble*>
    class ProgramUniformMatrix3x4dv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program"  )return(void*)&this->program  ;
          if(name == "location" )return(void*)&this->location ;
          if(name == "count"    )return(void*)&this->count    ;
          if(name == "transpose")return(void*)&this->transpose;
          if(name == "value"    )return(void*)&this->value    ;
          return NULL;
        }
      public:
        PROGRAM_TYPE   program  ;
        LOCATION_TYPE  location ;
        COUNT_TYPE     count    ;
        TRANSPOSE_TYPE transpose;
        VALUE_TYPE     value    ;
        ProgramUniformMatrix3x4dv(
            PROGRAM_TYPE   const&program  ,
            LOCATION_TYPE  const&location ,
            COUNT_TYPE     const&count    ,
            TRANSPOSE_TYPE const&transpose,
            VALUE_TYPE     const&value    ){
          this->program   = program  ;
          this->location  = location ;
          this->count     = count    ;
          this->transpose = transpose;
          this->value     = value    ;
        }
        virtual~ProgramUniformMatrix3x4dv(){}
        virtual void operator()(){
          glProgramUniformMatrix3x4dv(
            ge::core::convertTo<GLuint         >(this->program  ),
            ge::core::convertTo<GLint          >(this->location ),
            ge::core::convertTo<GLsizei        >(this->count    ),
            ge::core::convertTo<GLboolean      >(this->transpose),
            ge::core::convertTo<const GLdouble*>(this->value    )
          );
        }
    };

    template<
      typename PROGRAM_TYPE  = GLuint,
      typename LOCATION_TYPE = GLint ,
      typename V0_TYPE       = GLuint,
      typename V1_TYPE       = GLuint,
      typename V2_TYPE       = GLuint>
    class ProgramUniform3ui:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program" )return(void*)&this->program ;
          if(name == "location")return(void*)&this->location;
          if(name == "v0"      )return(void*)&this->v0      ;
          if(name == "v1"      )return(void*)&this->v1      ;
          if(name == "v2"      )return(void*)&this->v2      ;
          return NULL;
        }
      public:
        PROGRAM_TYPE  program ;
        LOCATION_TYPE location;
        V0_TYPE       v0      ;
        V1_TYPE       v1      ;
        V2_TYPE       v2      ;
        ProgramUniform3ui(
            PROGRAM_TYPE  const&program ,
            LOCATION_TYPE const&location,
            V0_TYPE       const&v0      ,
            V1_TYPE       const&v1      ,
            V2_TYPE       const&v2      ){
          this->program  = program ;
          this->location = location;
          this->v0       = v0      ;
          this->v1       = v1      ;
          this->v2       = v2      ;
        }
        virtual~ProgramUniform3ui(){}
        virtual void operator()(){
          glProgramUniform3ui(
            ge::core::convertTo<GLuint>(this->program ),
            ge::core::convertTo<GLint >(this->location),
            ge::core::convertTo<GLuint>(this->v0      ),
            ge::core::convertTo<GLuint>(this->v1      ),
            ge::core::convertTo<GLuint>(this->v2      )
          );
        }
    };

    template<
      typename LOCATION_TYPE = GLint,
      typename V0_TYPE       = GLint,
      typename V1_TYPE       = GLint,
      typename V2_TYPE       = GLint>
    class Uniform3i:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "location")return(void*)&this->location;
          if(name == "v0"      )return(void*)&this->v0      ;
          if(name == "v1"      )return(void*)&this->v1      ;
          if(name == "v2"      )return(void*)&this->v2      ;
          return NULL;
        }
      public:
        LOCATION_TYPE location;
        V0_TYPE       v0      ;
        V1_TYPE       v1      ;
        V2_TYPE       v2      ;
        Uniform3i(
            LOCATION_TYPE const&location,
            V0_TYPE       const&v0      ,
            V1_TYPE       const&v1      ,
            V2_TYPE       const&v2      ){
          this->location = location;
          this->v0       = v0      ;
          this->v1       = v1      ;
          this->v2       = v2      ;
        }
        virtual~Uniform3i(){}
        virtual void operator()(){
          glUniform3i(
            ge::core::convertTo<GLint>(this->location),
            ge::core::convertTo<GLint>(this->v0      ),
            ge::core::convertTo<GLint>(this->v1      ),
            ge::core::convertTo<GLint>(this->v2      )
          );
        }
    };

    template<
      typename PROGRAM_TYPE  = GLuint ,
      typename LOCATION_TYPE = GLint  ,
      typename BUFSIZE_TYPE  = GLsizei,
      typename PARAMS_TYPE   = GLint* >
    class GetnUniformiv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program" )return(void*)&this->program ;
          if(name == "location")return(void*)&this->location;
          if(name == "bufSize" )return(void*)&this->bufSize ;
          if(name == "params"  )return(void*)&this->params  ;
          return NULL;
        }
      public:
        PROGRAM_TYPE  program ;
        LOCATION_TYPE location;
        BUFSIZE_TYPE  bufSize ;
        PARAMS_TYPE   params  ;
        GetnUniformiv(
            PROGRAM_TYPE  const&program ,
            LOCATION_TYPE const&location,
            BUFSIZE_TYPE  const&bufSize ,
            PARAMS_TYPE   const&params  ){
          this->program  = program ;
          this->location = location;
          this->bufSize  = bufSize ;
          this->params   = params  ;
        }
        virtual~GetnUniformiv(){}
        virtual void operator()(){
          glGetnUniformiv(
            ge::core::convertTo<GLuint >(this->program ),
            ge::core::convertTo<GLint  >(this->location),
            ge::core::convertTo<GLsizei>(this->bufSize ),
            ge::core::convertTo<GLint* >(this->params  )
          );
        }
    };

    template<
      typename PROGRAM_TYPE  = GLuint,
      typename LOCATION_TYPE = GLint ,
      typename V0_TYPE       = GLint ,
      typename V1_TYPE       = GLint ,
      typename V2_TYPE       = GLint ,
      typename V3_TYPE       = GLint >
    class ProgramUniform4i:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program" )return(void*)&this->program ;
          if(name == "location")return(void*)&this->location;
          if(name == "v0"      )return(void*)&this->v0      ;
          if(name == "v1"      )return(void*)&this->v1      ;
          if(name == "v2"      )return(void*)&this->v2      ;
          if(name == "v3"      )return(void*)&this->v3      ;
          return NULL;
        }
      public:
        PROGRAM_TYPE  program ;
        LOCATION_TYPE location;
        V0_TYPE       v0      ;
        V1_TYPE       v1      ;
        V2_TYPE       v2      ;
        V3_TYPE       v3      ;
        ProgramUniform4i(
            PROGRAM_TYPE  const&program ,
            LOCATION_TYPE const&location,
            V0_TYPE       const&v0      ,
            V1_TYPE       const&v1      ,
            V2_TYPE       const&v2      ,
            V3_TYPE       const&v3      ){
          this->program  = program ;
          this->location = location;
          this->v0       = v0      ;
          this->v1       = v1      ;
          this->v2       = v2      ;
          this->v3       = v3      ;
        }
        virtual~ProgramUniform4i(){}
        virtual void operator()(){
          glProgramUniform4i(
            ge::core::convertTo<GLuint>(this->program ),
            ge::core::convertTo<GLint >(this->location),
            ge::core::convertTo<GLint >(this->v0      ),
            ge::core::convertTo<GLint >(this->v1      ),
            ge::core::convertTo<GLint >(this->v2      ),
            ge::core::convertTo<GLint >(this->v3      )
          );
        }
    };

    template<
      typename PROGRAM_TYPE  = GLuint        ,
      typename LOCATION_TYPE = GLint         ,
      typename COUNT_TYPE    = GLsizei       ,
      typename VALUE_TYPE    = const GLfloat*>
    class ProgramUniform4fv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program" )return(void*)&this->program ;
          if(name == "location")return(void*)&this->location;
          if(name == "count"   )return(void*)&this->count   ;
          if(name == "value"   )return(void*)&this->value   ;
          return NULL;
        }
      public:
        PROGRAM_TYPE  program ;
        LOCATION_TYPE location;
        COUNT_TYPE    count   ;
        VALUE_TYPE    value   ;
        ProgramUniform4fv(
            PROGRAM_TYPE  const&program ,
            LOCATION_TYPE const&location,
            COUNT_TYPE    const&count   ,
            VALUE_TYPE    const&value   ){
          this->program  = program ;
          this->location = location;
          this->count    = count   ;
          this->value    = value   ;
        }
        virtual~ProgramUniform4fv(){}
        virtual void operator()(){
          glProgramUniform4fv(
            ge::core::convertTo<GLuint        >(this->program ),
            ge::core::convertTo<GLint         >(this->location),
            ge::core::convertTo<GLsizei       >(this->count   ),
            ge::core::convertTo<const GLfloat*>(this->value   )
          );
        }
    };

    template<
      typename PROGRAM_TYPE  = GLuint ,
      typename LOCATION_TYPE = GLint  ,
      typename V0_TYPE       = GLfloat,
      typename V1_TYPE       = GLfloat,
      typename V2_TYPE       = GLfloat>
    class ProgramUniform3f:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program" )return(void*)&this->program ;
          if(name == "location")return(void*)&this->location;
          if(name == "v0"      )return(void*)&this->v0      ;
          if(name == "v1"      )return(void*)&this->v1      ;
          if(name == "v2"      )return(void*)&this->v2      ;
          return NULL;
        }
      public:
        PROGRAM_TYPE  program ;
        LOCATION_TYPE location;
        V0_TYPE       v0      ;
        V1_TYPE       v1      ;
        V2_TYPE       v2      ;
        ProgramUniform3f(
            PROGRAM_TYPE  const&program ,
            LOCATION_TYPE const&location,
            V0_TYPE       const&v0      ,
            V1_TYPE       const&v1      ,
            V2_TYPE       const&v2      ){
          this->program  = program ;
          this->location = location;
          this->v0       = v0      ;
          this->v1       = v1      ;
          this->v2       = v2      ;
        }
        virtual~ProgramUniform3f(){}
        virtual void operator()(){
          glProgramUniform3f(
            ge::core::convertTo<GLuint >(this->program ),
            ge::core::convertTo<GLint  >(this->location),
            ge::core::convertTo<GLfloat>(this->v0      ),
            ge::core::convertTo<GLfloat>(this->v1      ),
            ge::core::convertTo<GLfloat>(this->v2      )
          );
        }
    };

    template<
      typename LOCATION_TYPE = GLint         ,
      typename COUNT_TYPE    = GLsizei       ,
      typename VALUE_TYPE    = const GLfloat*>
    class Uniform2fv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "location")return(void*)&this->location;
          if(name == "count"   )return(void*)&this->count   ;
          if(name == "value"   )return(void*)&this->value   ;
          return NULL;
        }
      public:
        LOCATION_TYPE location;
        COUNT_TYPE    count   ;
        VALUE_TYPE    value   ;
        Uniform2fv(
            LOCATION_TYPE const&location,
            COUNT_TYPE    const&count   ,
            VALUE_TYPE    const&value   ){
          this->location = location;
          this->count    = count   ;
          this->value    = value   ;
        }
        virtual~Uniform2fv(){}
        virtual void operator()(){
          glUniform2fv(
            ge::core::convertTo<GLint         >(this->location),
            ge::core::convertTo<GLsizei       >(this->count   ),
            ge::core::convertTo<const GLfloat*>(this->value   )
          );
        }
    };

    template<
      typename LOCATION_TYPE  = GLint          ,
      typename COUNT_TYPE     = GLsizei        ,
      typename TRANSPOSE_TYPE = GLboolean      ,
      typename VALUE_TYPE     = const GLdouble*>
    class UniformMatrix3dv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "location" )return(void*)&this->location ;
          if(name == "count"    )return(void*)&this->count    ;
          if(name == "transpose")return(void*)&this->transpose;
          if(name == "value"    )return(void*)&this->value    ;
          return NULL;
        }
      public:
        LOCATION_TYPE  location ;
        COUNT_TYPE     count    ;
        TRANSPOSE_TYPE transpose;
        VALUE_TYPE     value    ;
        UniformMatrix3dv(
            LOCATION_TYPE  const&location ,
            COUNT_TYPE     const&count    ,
            TRANSPOSE_TYPE const&transpose,
            VALUE_TYPE     const&value    ){
          this->location  = location ;
          this->count     = count    ;
          this->transpose = transpose;
          this->value     = value    ;
        }
        virtual~UniformMatrix3dv(){}
        virtual void operator()(){
          glUniformMatrix3dv(
            ge::core::convertTo<GLint          >(this->location ),
            ge::core::convertTo<GLsizei        >(this->count    ),
            ge::core::convertTo<GLboolean      >(this->transpose),
            ge::core::convertTo<const GLdouble*>(this->value    )
          );
        }
    };

    template<
      typename PROGRAM_TYPE   = GLuint         ,
      typename LOCATION_TYPE  = GLint          ,
      typename COUNT_TYPE     = GLsizei        ,
      typename TRANSPOSE_TYPE = GLboolean      ,
      typename VALUE_TYPE     = const GLdouble*>
    class ProgramUniformMatrix2dv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program"  )return(void*)&this->program  ;
          if(name == "location" )return(void*)&this->location ;
          if(name == "count"    )return(void*)&this->count    ;
          if(name == "transpose")return(void*)&this->transpose;
          if(name == "value"    )return(void*)&this->value    ;
          return NULL;
        }
      public:
        PROGRAM_TYPE   program  ;
        LOCATION_TYPE  location ;
        COUNT_TYPE     count    ;
        TRANSPOSE_TYPE transpose;
        VALUE_TYPE     value    ;
        ProgramUniformMatrix2dv(
            PROGRAM_TYPE   const&program  ,
            LOCATION_TYPE  const&location ,
            COUNT_TYPE     const&count    ,
            TRANSPOSE_TYPE const&transpose,
            VALUE_TYPE     const&value    ){
          this->program   = program  ;
          this->location  = location ;
          this->count     = count    ;
          this->transpose = transpose;
          this->value     = value    ;
        }
        virtual~ProgramUniformMatrix2dv(){}
        virtual void operator()(){
          glProgramUniformMatrix2dv(
            ge::core::convertTo<GLuint         >(this->program  ),
            ge::core::convertTo<GLint          >(this->location ),
            ge::core::convertTo<GLsizei        >(this->count    ),
            ge::core::convertTo<GLboolean      >(this->transpose),
            ge::core::convertTo<const GLdouble*>(this->value    )
          );
        }
    };

    template<
      typename PROGRAM_TYPE  = GLuint,
      typename LOCATION_TYPE = GLint ,
      typename V0_TYPE       = GLint ,
      typename V1_TYPE       = GLint >
    class ProgramUniform2i:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program" )return(void*)&this->program ;
          if(name == "location")return(void*)&this->location;
          if(name == "v0"      )return(void*)&this->v0      ;
          if(name == "v1"      )return(void*)&this->v1      ;
          return NULL;
        }
      public:
        PROGRAM_TYPE  program ;
        LOCATION_TYPE location;
        V0_TYPE       v0      ;
        V1_TYPE       v1      ;
        ProgramUniform2i(
            PROGRAM_TYPE  const&program ,
            LOCATION_TYPE const&location,
            V0_TYPE       const&v0      ,
            V1_TYPE       const&v1      ){
          this->program  = program ;
          this->location = location;
          this->v0       = v0      ;
          this->v1       = v1      ;
        }
        virtual~ProgramUniform2i(){}
        virtual void operator()(){
          glProgramUniform2i(
            ge::core::convertTo<GLuint>(this->program ),
            ge::core::convertTo<GLint >(this->location),
            ge::core::convertTo<GLint >(this->v0      ),
            ge::core::convertTo<GLint >(this->v1      )
          );
        }
    };

    template<
      typename PROGRAM_TYPE  = GLuint        ,
      typename LOCATION_TYPE = GLint         ,
      typename COUNT_TYPE    = GLsizei       ,
      typename VALUE_TYPE    = const GLfloat*>
    class ProgramUniform2fv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program" )return(void*)&this->program ;
          if(name == "location")return(void*)&this->location;
          if(name == "count"   )return(void*)&this->count   ;
          if(name == "value"   )return(void*)&this->value   ;
          return NULL;
        }
      public:
        PROGRAM_TYPE  program ;
        LOCATION_TYPE location;
        COUNT_TYPE    count   ;
        VALUE_TYPE    value   ;
        ProgramUniform2fv(
            PROGRAM_TYPE  const&program ,
            LOCATION_TYPE const&location,
            COUNT_TYPE    const&count   ,
            VALUE_TYPE    const&value   ){
          this->program  = program ;
          this->location = location;
          this->count    = count   ;
          this->value    = value   ;
        }
        virtual~ProgramUniform2fv(){}
        virtual void operator()(){
          glProgramUniform2fv(
            ge::core::convertTo<GLuint        >(this->program ),
            ge::core::convertTo<GLint         >(this->location),
            ge::core::convertTo<GLsizei       >(this->count   ),
            ge::core::convertTo<const GLfloat*>(this->value   )
          );
        }
    };

    template<
      typename LOCATION_TYPE = GLint         ,
      typename COUNT_TYPE    = GLsizei       ,
      typename VALUE_TYPE    = const GLfloat*>
    class Uniform4fv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "location")return(void*)&this->location;
          if(name == "count"   )return(void*)&this->count   ;
          if(name == "value"   )return(void*)&this->value   ;
          return NULL;
        }
      public:
        LOCATION_TYPE location;
        COUNT_TYPE    count   ;
        VALUE_TYPE    value   ;
        Uniform4fv(
            LOCATION_TYPE const&location,
            COUNT_TYPE    const&count   ,
            VALUE_TYPE    const&value   ){
          this->location = location;
          this->count    = count   ;
          this->value    = value   ;
        }
        virtual~Uniform4fv(){}
        virtual void operator()(){
          glUniform4fv(
            ge::core::convertTo<GLint         >(this->location),
            ge::core::convertTo<GLsizei       >(this->count   ),
            ge::core::convertTo<const GLfloat*>(this->value   )
          );
        }
    };

    template<
      typename LOCATION_TYPE  = GLint         ,
      typename COUNT_TYPE     = GLsizei       ,
      typename TRANSPOSE_TYPE = GLboolean     ,
      typename VALUE_TYPE     = const GLfloat*>
    class UniformMatrix2fv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "location" )return(void*)&this->location ;
          if(name == "count"    )return(void*)&this->count    ;
          if(name == "transpose")return(void*)&this->transpose;
          if(name == "value"    )return(void*)&this->value    ;
          return NULL;
        }
      public:
        LOCATION_TYPE  location ;
        COUNT_TYPE     count    ;
        TRANSPOSE_TYPE transpose;
        VALUE_TYPE     value    ;
        UniformMatrix2fv(
            LOCATION_TYPE  const&location ,
            COUNT_TYPE     const&count    ,
            TRANSPOSE_TYPE const&transpose,
            VALUE_TYPE     const&value    ){
          this->location  = location ;
          this->count     = count    ;
          this->transpose = transpose;
          this->value     = value    ;
        }
        virtual~UniformMatrix2fv(){}
        virtual void operator()(){
          glUniformMatrix2fv(
            ge::core::convertTo<GLint         >(this->location ),
            ge::core::convertTo<GLsizei       >(this->count    ),
            ge::core::convertTo<GLboolean     >(this->transpose),
            ge::core::convertTo<const GLfloat*>(this->value    )
          );
        }
    };

    template<
      typename RET_TYPE        = GLint        ,
      typename PROGRAM_TYPE    = GLuint       ,
      typename SHADERTYPE_TYPE = GLenum       ,
      typename NAME_TYPE       = const GLchar*>
    class GetSubroutineUniformLocation:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "ret"       )return(void*)&this->ret       ;
          if(name == "program"   )return(void*)&this->program   ;
          if(name == "shadertype")return(void*)&this->shadertype;
          if(name == "name"      )return(void*)&this->name      ;
          return NULL;
        }
      public:
        RET_TYPE        ret       ;
        PROGRAM_TYPE    program   ;
        SHADERTYPE_TYPE shadertype;
        NAME_TYPE       name      ;
        GetSubroutineUniformLocation(
            RET_TYPE        const&ret       ,
            PROGRAM_TYPE    const&program   ,
            SHADERTYPE_TYPE const&shadertype,
            NAME_TYPE       const&name      ){
          this->ret        = ret       ;
          this->program    = program   ;
          this->shadertype = shadertype;
          this->name       = name      ;
        }
        virtual~GetSubroutineUniformLocation(){}
        virtual void operator()(){
          ge::core::convertFrom<GLint>(this->ret,glGetSubroutineUniformLocation(
              ge::core::convertTo<GLuint       >(this->program   ),
              ge::core::convertTo<GLenum       >(this->shadertype),
              ge::core::convertTo<const GLchar*>(this->name      ))
          );
        }
    };

    template<
      typename SHADERTYPE_TYPE = GLenum       ,
      typename COUNT_TYPE      = GLsizei      ,
      typename INDICES_TYPE    = const GLuint*>
    class UniformSubroutinesuiv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "shadertype")return(void*)&this->shadertype;
          if(name == "count"     )return(void*)&this->count     ;
          if(name == "indices"   )return(void*)&this->indices   ;
          return NULL;
        }
      public:
        SHADERTYPE_TYPE shadertype;
        COUNT_TYPE      count     ;
        INDICES_TYPE    indices   ;
        UniformSubroutinesuiv(
            SHADERTYPE_TYPE const&shadertype,
            COUNT_TYPE      const&count     ,
            INDICES_TYPE    const&indices   ){
          this->shadertype = shadertype;
          this->count      = count     ;
          this->indices    = indices   ;
        }
        virtual~UniformSubroutinesuiv(){}
        virtual void operator()(){
          glUniformSubroutinesuiv(
            ge::core::convertTo<GLenum       >(this->shadertype),
            ge::core::convertTo<GLsizei      >(this->count     ),
            ge::core::convertTo<const GLuint*>(this->indices   )
          );
        }
    };

    template<
      typename LOCATION_TYPE  = GLint          ,
      typename COUNT_TYPE     = GLsizei        ,
      typename TRANSPOSE_TYPE = GLboolean      ,
      typename VALUE_TYPE     = const GLdouble*>
    class UniformMatrix3x2dv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "location" )return(void*)&this->location ;
          if(name == "count"    )return(void*)&this->count    ;
          if(name == "transpose")return(void*)&this->transpose;
          if(name == "value"    )return(void*)&this->value    ;
          return NULL;
        }
      public:
        LOCATION_TYPE  location ;
        COUNT_TYPE     count    ;
        TRANSPOSE_TYPE transpose;
        VALUE_TYPE     value    ;
        UniformMatrix3x2dv(
            LOCATION_TYPE  const&location ,
            COUNT_TYPE     const&count    ,
            TRANSPOSE_TYPE const&transpose,
            VALUE_TYPE     const&value    ){
          this->location  = location ;
          this->count     = count    ;
          this->transpose = transpose;
          this->value     = value    ;
        }
        virtual~UniformMatrix3x2dv(){}
        virtual void operator()(){
          glUniformMatrix3x2dv(
            ge::core::convertTo<GLint          >(this->location ),
            ge::core::convertTo<GLsizei        >(this->count    ),
            ge::core::convertTo<GLboolean      >(this->transpose),
            ge::core::convertTo<const GLdouble*>(this->value    )
          );
        }
    };

    template<
      typename LOCATION_TYPE = GLint,
      typename V0_TYPE       = GLint>
    class Uniform1i:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "location")return(void*)&this->location;
          if(name == "v0"      )return(void*)&this->v0      ;
          return NULL;
        }
      public:
        LOCATION_TYPE location;
        V0_TYPE       v0      ;
        Uniform1i(
            LOCATION_TYPE const&location,
            V0_TYPE       const&v0      ){
          this->location = location;
          this->v0       = v0      ;
        }
        virtual~Uniform1i(){}
        virtual void operator()(){
          glUniform1i(
            ge::core::convertTo<GLint>(this->location),
            ge::core::convertTo<GLint>(this->v0      )
          );
        }
    };

    template<
      typename LOCATION_TYPE = GLint ,
      typename V0_TYPE       = GLuint,
      typename V1_TYPE       = GLuint,
      typename V2_TYPE       = GLuint,
      typename V3_TYPE       = GLuint>
    class Uniform4ui:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "location")return(void*)&this->location;
          if(name == "v0"      )return(void*)&this->v0      ;
          if(name == "v1"      )return(void*)&this->v1      ;
          if(name == "v2"      )return(void*)&this->v2      ;
          if(name == "v3"      )return(void*)&this->v3      ;
          return NULL;
        }
      public:
        LOCATION_TYPE location;
        V0_TYPE       v0      ;
        V1_TYPE       v1      ;
        V2_TYPE       v2      ;
        V3_TYPE       v3      ;
        Uniform4ui(
            LOCATION_TYPE const&location,
            V0_TYPE       const&v0      ,
            V1_TYPE       const&v1      ,
            V2_TYPE       const&v2      ,
            V3_TYPE       const&v3      ){
          this->location = location;
          this->v0       = v0      ;
          this->v1       = v1      ;
          this->v2       = v2      ;
          this->v3       = v3      ;
        }
        virtual~Uniform4ui(){}
        virtual void operator()(){
          glUniform4ui(
            ge::core::convertTo<GLint >(this->location),
            ge::core::convertTo<GLuint>(this->v0      ),
            ge::core::convertTo<GLuint>(this->v1      ),
            ge::core::convertTo<GLuint>(this->v2      ),
            ge::core::convertTo<GLuint>(this->v3      )
          );
        }
    };

    template<
      typename LOCATION_TYPE  = GLint         ,
      typename COUNT_TYPE     = GLsizei       ,
      typename TRANSPOSE_TYPE = GLboolean     ,
      typename VALUE_TYPE     = const GLfloat*>
    class UniformMatrix3x4fv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "location" )return(void*)&this->location ;
          if(name == "count"    )return(void*)&this->count    ;
          if(name == "transpose")return(void*)&this->transpose;
          if(name == "value"    )return(void*)&this->value    ;
          return NULL;
        }
      public:
        LOCATION_TYPE  location ;
        COUNT_TYPE     count    ;
        TRANSPOSE_TYPE transpose;
        VALUE_TYPE     value    ;
        UniformMatrix3x4fv(
            LOCATION_TYPE  const&location ,
            COUNT_TYPE     const&count    ,
            TRANSPOSE_TYPE const&transpose,
            VALUE_TYPE     const&value    ){
          this->location  = location ;
          this->count     = count    ;
          this->transpose = transpose;
          this->value     = value    ;
        }
        virtual~UniformMatrix3x4fv(){}
        virtual void operator()(){
          glUniformMatrix3x4fv(
            ge::core::convertTo<GLint         >(this->location ),
            ge::core::convertTo<GLsizei       >(this->count    ),
            ge::core::convertTo<GLboolean     >(this->transpose),
            ge::core::convertTo<const GLfloat*>(this->value    )
          );
        }
    };

    template<
      typename LOCATION_TYPE  = GLint         ,
      typename COUNT_TYPE     = GLsizei       ,
      typename TRANSPOSE_TYPE = GLboolean     ,
      typename VALUE_TYPE     = const GLfloat*>
    class UniformMatrix4x3fv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "location" )return(void*)&this->location ;
          if(name == "count"    )return(void*)&this->count    ;
          if(name == "transpose")return(void*)&this->transpose;
          if(name == "value"    )return(void*)&this->value    ;
          return NULL;
        }
      public:
        LOCATION_TYPE  location ;
        COUNT_TYPE     count    ;
        TRANSPOSE_TYPE transpose;
        VALUE_TYPE     value    ;
        UniformMatrix4x3fv(
            LOCATION_TYPE  const&location ,
            COUNT_TYPE     const&count    ,
            TRANSPOSE_TYPE const&transpose,
            VALUE_TYPE     const&value    ){
          this->location  = location ;
          this->count     = count    ;
          this->transpose = transpose;
          this->value     = value    ;
        }
        virtual~UniformMatrix4x3fv(){}
        virtual void operator()(){
          glUniformMatrix4x3fv(
            ge::core::convertTo<GLint         >(this->location ),
            ge::core::convertTo<GLsizei       >(this->count    ),
            ge::core::convertTo<GLboolean     >(this->transpose),
            ge::core::convertTo<const GLfloat*>(this->value    )
          );
        }
    };

    template<
      typename PROGRAM_TYPE = GLuint  ,
      typename INDEX_TYPE   = GLuint  ,
      typename BUFSIZE_TYPE = GLsizei ,
      typename LENGTH_TYPE  = GLsizei*,
      typename SIZE_TYPE    = GLint*  ,
      typename TYPE_TYPE    = GLenum* ,
      typename NAME_TYPE    = GLchar* >
    class GetActiveUniform:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program")return(void*)&this->program;
          if(name == "index"  )return(void*)&this->index  ;
          if(name == "bufSize")return(void*)&this->bufSize;
          if(name == "length" )return(void*)&this->length ;
          if(name == "size"   )return(void*)&this->size   ;
          if(name == "type"   )return(void*)&this->type   ;
          if(name == "name"   )return(void*)&this->name   ;
          return NULL;
        }
      public:
        PROGRAM_TYPE program;
        INDEX_TYPE   index  ;
        BUFSIZE_TYPE bufSize;
        LENGTH_TYPE  length ;
        SIZE_TYPE    size   ;
        TYPE_TYPE    type   ;
        NAME_TYPE    name   ;
        GetActiveUniform(
            PROGRAM_TYPE const&program,
            INDEX_TYPE   const&index  ,
            BUFSIZE_TYPE const&bufSize,
            LENGTH_TYPE  const&length ,
            SIZE_TYPE    const&size   ,
            TYPE_TYPE    const&type   ,
            NAME_TYPE    const&name   ){
          this->program = program;
          this->index   = index  ;
          this->bufSize = bufSize;
          this->length  = length ;
          this->size    = size   ;
          this->type    = type   ;
          this->name    = name   ;
        }
        virtual~GetActiveUniform(){}
        virtual void operator()(){
          glGetActiveUniform(
            ge::core::convertTo<GLuint  >(this->program),
            ge::core::convertTo<GLuint  >(this->index  ),
            ge::core::convertTo<GLsizei >(this->bufSize),
            ge::core::convertTo<GLsizei*>(this->length ),
            ge::core::convertTo<GLint*  >(this->size   ),
            ge::core::convertTo<GLenum* >(this->type   ),
            ge::core::convertTo<GLchar* >(this->name   )
          );
        }
    };

    template<
      typename LOCATION_TYPE = GLint          ,
      typename COUNT_TYPE    = GLsizei        ,
      typename VALUE_TYPE    = const GLdouble*>
    class Uniform2dv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "location")return(void*)&this->location;
          if(name == "count"   )return(void*)&this->count   ;
          if(name == "value"   )return(void*)&this->value   ;
          return NULL;
        }
      public:
        LOCATION_TYPE location;
        COUNT_TYPE    count   ;
        VALUE_TYPE    value   ;
        Uniform2dv(
            LOCATION_TYPE const&location,
            COUNT_TYPE    const&count   ,
            VALUE_TYPE    const&value   ){
          this->location = location;
          this->count    = count   ;
          this->value    = value   ;
        }
        virtual~Uniform2dv(){}
        virtual void operator()(){
          glUniform2dv(
            ge::core::convertTo<GLint          >(this->location),
            ge::core::convertTo<GLsizei        >(this->count   ),
            ge::core::convertTo<const GLdouble*>(this->value   )
          );
        }
    };

    template<
      typename PROGRAM_TYPE  = GLuint      ,
      typename LOCATION_TYPE = GLint       ,
      typename COUNT_TYPE    = GLsizei     ,
      typename VALUE_TYPE    = const GLint*>
    class ProgramUniform2iv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program" )return(void*)&this->program ;
          if(name == "location")return(void*)&this->location;
          if(name == "count"   )return(void*)&this->count   ;
          if(name == "value"   )return(void*)&this->value   ;
          return NULL;
        }
      public:
        PROGRAM_TYPE  program ;
        LOCATION_TYPE location;
        COUNT_TYPE    count   ;
        VALUE_TYPE    value   ;
        ProgramUniform2iv(
            PROGRAM_TYPE  const&program ,
            LOCATION_TYPE const&location,
            COUNT_TYPE    const&count   ,
            VALUE_TYPE    const&value   ){
          this->program  = program ;
          this->location = location;
          this->count    = count   ;
          this->value    = value   ;
        }
        virtual~ProgramUniform2iv(){}
        virtual void operator()(){
          glProgramUniform2iv(
            ge::core::convertTo<GLuint      >(this->program ),
            ge::core::convertTo<GLint       >(this->location),
            ge::core::convertTo<GLsizei     >(this->count   ),
            ge::core::convertTo<const GLint*>(this->value   )
          );
        }
    };

    template<
      typename LOCATION_TYPE = GLint       ,
      typename COUNT_TYPE    = GLsizei     ,
      typename VALUE_TYPE    = const GLint*>
    class Uniform4iv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "location")return(void*)&this->location;
          if(name == "count"   )return(void*)&this->count   ;
          if(name == "value"   )return(void*)&this->value   ;
          return NULL;
        }
      public:
        LOCATION_TYPE location;
        COUNT_TYPE    count   ;
        VALUE_TYPE    value   ;
        Uniform4iv(
            LOCATION_TYPE const&location,
            COUNT_TYPE    const&count   ,
            VALUE_TYPE    const&value   ){
          this->location = location;
          this->count    = count   ;
          this->value    = value   ;
        }
        virtual~Uniform4iv(){}
        virtual void operator()(){
          glUniform4iv(
            ge::core::convertTo<GLint       >(this->location),
            ge::core::convertTo<GLsizei     >(this->count   ),
            ge::core::convertTo<const GLint*>(this->value   )
          );
        }
    };

    template<
      typename PROGRAM_TYPE  = GLuint  ,
      typename LOCATION_TYPE = GLint   ,
      typename V0_TYPE       = GLdouble,
      typename V1_TYPE       = GLdouble>
    class ProgramUniform2d:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program" )return(void*)&this->program ;
          if(name == "location")return(void*)&this->location;
          if(name == "v0"      )return(void*)&this->v0      ;
          if(name == "v1"      )return(void*)&this->v1      ;
          return NULL;
        }
      public:
        PROGRAM_TYPE  program ;
        LOCATION_TYPE location;
        V0_TYPE       v0      ;
        V1_TYPE       v1      ;
        ProgramUniform2d(
            PROGRAM_TYPE  const&program ,
            LOCATION_TYPE const&location,
            V0_TYPE       const&v0      ,
            V1_TYPE       const&v1      ){
          this->program  = program ;
          this->location = location;
          this->v0       = v0      ;
          this->v1       = v1      ;
        }
        virtual~ProgramUniform2d(){}
        virtual void operator()(){
          glProgramUniform2d(
            ge::core::convertTo<GLuint  >(this->program ),
            ge::core::convertTo<GLint   >(this->location),
            ge::core::convertTo<GLdouble>(this->v0      ),
            ge::core::convertTo<GLdouble>(this->v1      )
          );
        }
    };

    template<
      typename LOCATION_TYPE = GLint         ,
      typename COUNT_TYPE    = GLsizei       ,
      typename VALUE_TYPE    = const GLfloat*>
    class Uniform3fv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "location")return(void*)&this->location;
          if(name == "count"   )return(void*)&this->count   ;
          if(name == "value"   )return(void*)&this->value   ;
          return NULL;
        }
      public:
        LOCATION_TYPE location;
        COUNT_TYPE    count   ;
        VALUE_TYPE    value   ;
        Uniform3fv(
            LOCATION_TYPE const&location,
            COUNT_TYPE    const&count   ,
            VALUE_TYPE    const&value   ){
          this->location = location;
          this->count    = count   ;
          this->value    = value   ;
        }
        virtual~Uniform3fv(){}
        virtual void operator()(){
          glUniform3fv(
            ge::core::convertTo<GLint         >(this->location),
            ge::core::convertTo<GLsizei       >(this->count   ),
            ge::core::convertTo<const GLfloat*>(this->value   )
          );
        }
    };

    template<
      typename LOCATION_TYPE = GLint   ,
      typename X_TYPE        = GLdouble,
      typename Y_TYPE        = GLdouble,
      typename Z_TYPE        = GLdouble,
      typename W_TYPE        = GLdouble>
    class Uniform4d:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "location")return(void*)&this->location;
          if(name == "x"       )return(void*)&this->x       ;
          if(name == "y"       )return(void*)&this->y       ;
          if(name == "z"       )return(void*)&this->z       ;
          if(name == "w"       )return(void*)&this->w       ;
          return NULL;
        }
      public:
        LOCATION_TYPE location;
        X_TYPE        x       ;
        Y_TYPE        y       ;
        Z_TYPE        z       ;
        W_TYPE        w       ;
        Uniform4d(
            LOCATION_TYPE const&location,
            X_TYPE        const&x       ,
            Y_TYPE        const&y       ,
            Z_TYPE        const&z       ,
            W_TYPE        const&w       ){
          this->location = location;
          this->x        = x       ;
          this->y        = y       ;
          this->z        = z       ;
          this->w        = w       ;
        }
        virtual~Uniform4d(){}
        virtual void operator()(){
          glUniform4d(
            ge::core::convertTo<GLint   >(this->location),
            ge::core::convertTo<GLdouble>(this->x       ),
            ge::core::convertTo<GLdouble>(this->y       ),
            ge::core::convertTo<GLdouble>(this->z       ),
            ge::core::convertTo<GLdouble>(this->w       )
          );
        }
    };

    template<
      typename PROGRAM_TYPE  = GLuint      ,
      typename LOCATION_TYPE = GLint       ,
      typename COUNT_TYPE    = GLsizei     ,
      typename VALUE_TYPE    = const GLint*>
    class ProgramUniform4iv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program" )return(void*)&this->program ;
          if(name == "location")return(void*)&this->location;
          if(name == "count"   )return(void*)&this->count   ;
          if(name == "value"   )return(void*)&this->value   ;
          return NULL;
        }
      public:
        PROGRAM_TYPE  program ;
        LOCATION_TYPE location;
        COUNT_TYPE    count   ;
        VALUE_TYPE    value   ;
        ProgramUniform4iv(
            PROGRAM_TYPE  const&program ,
            LOCATION_TYPE const&location,
            COUNT_TYPE    const&count   ,
            VALUE_TYPE    const&value   ){
          this->program  = program ;
          this->location = location;
          this->count    = count   ;
          this->value    = value   ;
        }
        virtual~ProgramUniform4iv(){}
        virtual void operator()(){
          glProgramUniform4iv(
            ge::core::convertTo<GLuint      >(this->program ),
            ge::core::convertTo<GLint       >(this->location),
            ge::core::convertTo<GLsizei     >(this->count   ),
            ge::core::convertTo<const GLint*>(this->value   )
          );
        }
    };

    template<
      typename LOCATION_TYPE = GLint        ,
      typename COUNT_TYPE    = GLsizei      ,
      typename VALUE_TYPE    = const GLuint*>
    class Uniform1uiv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "location")return(void*)&this->location;
          if(name == "count"   )return(void*)&this->count   ;
          if(name == "value"   )return(void*)&this->value   ;
          return NULL;
        }
      public:
        LOCATION_TYPE location;
        COUNT_TYPE    count   ;
        VALUE_TYPE    value   ;
        Uniform1uiv(
            LOCATION_TYPE const&location,
            COUNT_TYPE    const&count   ,
            VALUE_TYPE    const&value   ){
          this->location = location;
          this->count    = count   ;
          this->value    = value   ;
        }
        virtual~Uniform1uiv(){}
        virtual void operator()(){
          glUniform1uiv(
            ge::core::convertTo<GLint        >(this->location),
            ge::core::convertTo<GLsizei      >(this->count   ),
            ge::core::convertTo<const GLuint*>(this->value   )
          );
        }
    };

    template<
      typename PROGRAM_TYPE   = GLuint        ,
      typename LOCATION_TYPE  = GLint         ,
      typename COUNT_TYPE     = GLsizei       ,
      typename TRANSPOSE_TYPE = GLboolean     ,
      typename VALUE_TYPE     = const GLfloat*>
    class ProgramUniformMatrix2x3fv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program"  )return(void*)&this->program  ;
          if(name == "location" )return(void*)&this->location ;
          if(name == "count"    )return(void*)&this->count    ;
          if(name == "transpose")return(void*)&this->transpose;
          if(name == "value"    )return(void*)&this->value    ;
          return NULL;
        }
      public:
        PROGRAM_TYPE   program  ;
        LOCATION_TYPE  location ;
        COUNT_TYPE     count    ;
        TRANSPOSE_TYPE transpose;
        VALUE_TYPE     value    ;
        ProgramUniformMatrix2x3fv(
            PROGRAM_TYPE   const&program  ,
            LOCATION_TYPE  const&location ,
            COUNT_TYPE     const&count    ,
            TRANSPOSE_TYPE const&transpose,
            VALUE_TYPE     const&value    ){
          this->program   = program  ;
          this->location  = location ;
          this->count     = count    ;
          this->transpose = transpose;
          this->value     = value    ;
        }
        virtual~ProgramUniformMatrix2x3fv(){}
        virtual void operator()(){
          glProgramUniformMatrix2x3fv(
            ge::core::convertTo<GLuint        >(this->program  ),
            ge::core::convertTo<GLint         >(this->location ),
            ge::core::convertTo<GLsizei       >(this->count    ),
            ge::core::convertTo<GLboolean     >(this->transpose),
            ge::core::convertTo<const GLfloat*>(this->value    )
          );
        }
    };

    template<
      typename LOCATION_TYPE  = GLint         ,
      typename COUNT_TYPE     = GLsizei       ,
      typename TRANSPOSE_TYPE = GLboolean     ,
      typename VALUE_TYPE     = const GLfloat*>
    class UniformMatrix3fv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "location" )return(void*)&this->location ;
          if(name == "count"    )return(void*)&this->count    ;
          if(name == "transpose")return(void*)&this->transpose;
          if(name == "value"    )return(void*)&this->value    ;
          return NULL;
        }
      public:
        LOCATION_TYPE  location ;
        COUNT_TYPE     count    ;
        TRANSPOSE_TYPE transpose;
        VALUE_TYPE     value    ;
        UniformMatrix3fv(
            LOCATION_TYPE  const&location ,
            COUNT_TYPE     const&count    ,
            TRANSPOSE_TYPE const&transpose,
            VALUE_TYPE     const&value    ){
          this->location  = location ;
          this->count     = count    ;
          this->transpose = transpose;
          this->value     = value    ;
        }
        virtual~UniformMatrix3fv(){}
        virtual void operator()(){
          glUniformMatrix3fv(
            ge::core::convertTo<GLint         >(this->location ),
            ge::core::convertTo<GLsizei       >(this->count    ),
            ge::core::convertTo<GLboolean     >(this->transpose),
            ge::core::convertTo<const GLfloat*>(this->value    )
          );
        }
    };

    template<
      typename PROGRAM_TYPE  = GLuint ,
      typename LOCATION_TYPE = GLint  ,
      typename V0_TYPE       = GLfloat>
    class ProgramUniform1f:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program" )return(void*)&this->program ;
          if(name == "location")return(void*)&this->location;
          if(name == "v0"      )return(void*)&this->v0      ;
          return NULL;
        }
      public:
        PROGRAM_TYPE  program ;
        LOCATION_TYPE location;
        V0_TYPE       v0      ;
        ProgramUniform1f(
            PROGRAM_TYPE  const&program ,
            LOCATION_TYPE const&location,
            V0_TYPE       const&v0      ){
          this->program  = program ;
          this->location = location;
          this->v0       = v0      ;
        }
        virtual~ProgramUniform1f(){}
        virtual void operator()(){
          glProgramUniform1f(
            ge::core::convertTo<GLuint >(this->program ),
            ge::core::convertTo<GLint  >(this->location),
            ge::core::convertTo<GLfloat>(this->v0      )
          );
        }
    };

    template<
      typename LOCATION_TYPE = GLint  ,
      typename V0_TYPE       = GLfloat,
      typename V1_TYPE       = GLfloat,
      typename V2_TYPE       = GLfloat,
      typename V3_TYPE       = GLfloat>
    class Uniform4f:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "location")return(void*)&this->location;
          if(name == "v0"      )return(void*)&this->v0      ;
          if(name == "v1"      )return(void*)&this->v1      ;
          if(name == "v2"      )return(void*)&this->v2      ;
          if(name == "v3"      )return(void*)&this->v3      ;
          return NULL;
        }
      public:
        LOCATION_TYPE location;
        V0_TYPE       v0      ;
        V1_TYPE       v1      ;
        V2_TYPE       v2      ;
        V3_TYPE       v3      ;
        Uniform4f(
            LOCATION_TYPE const&location,
            V0_TYPE       const&v0      ,
            V1_TYPE       const&v1      ,
            V2_TYPE       const&v2      ,
            V3_TYPE       const&v3      ){
          this->location = location;
          this->v0       = v0      ;
          this->v1       = v1      ;
          this->v2       = v2      ;
          this->v3       = v3      ;
        }
        virtual~Uniform4f(){}
        virtual void operator()(){
          glUniform4f(
            ge::core::convertTo<GLint  >(this->location),
            ge::core::convertTo<GLfloat>(this->v0      ),
            ge::core::convertTo<GLfloat>(this->v1      ),
            ge::core::convertTo<GLfloat>(this->v2      ),
            ge::core::convertTo<GLfloat>(this->v3      )
          );
        }
    };

    template<
      typename LOCATION_TYPE  = GLint          ,
      typename COUNT_TYPE     = GLsizei        ,
      typename TRANSPOSE_TYPE = GLboolean      ,
      typename VALUE_TYPE     = const GLdouble*>
    class UniformMatrix4x2dv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "location" )return(void*)&this->location ;
          if(name == "count"    )return(void*)&this->count    ;
          if(name == "transpose")return(void*)&this->transpose;
          if(name == "value"    )return(void*)&this->value    ;
          return NULL;
        }
      public:
        LOCATION_TYPE  location ;
        COUNT_TYPE     count    ;
        TRANSPOSE_TYPE transpose;
        VALUE_TYPE     value    ;
        UniformMatrix4x2dv(
            LOCATION_TYPE  const&location ,
            COUNT_TYPE     const&count    ,
            TRANSPOSE_TYPE const&transpose,
            VALUE_TYPE     const&value    ){
          this->location  = location ;
          this->count     = count    ;
          this->transpose = transpose;
          this->value     = value    ;
        }
        virtual~UniformMatrix4x2dv(){}
        virtual void operator()(){
          glUniformMatrix4x2dv(
            ge::core::convertTo<GLint          >(this->location ),
            ge::core::convertTo<GLsizei        >(this->count    ),
            ge::core::convertTo<GLboolean      >(this->transpose),
            ge::core::convertTo<const GLdouble*>(this->value    )
          );
        }
    };

    template<
      typename LOCATION_TYPE = GLint        ,
      typename COUNT_TYPE    = GLsizei      ,
      typename VALUE_TYPE    = const GLuint*>
    class Uniform4uiv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "location")return(void*)&this->location;
          if(name == "count"   )return(void*)&this->count   ;
          if(name == "value"   )return(void*)&this->value   ;
          return NULL;
        }
      public:
        LOCATION_TYPE location;
        COUNT_TYPE    count   ;
        VALUE_TYPE    value   ;
        Uniform4uiv(
            LOCATION_TYPE const&location,
            COUNT_TYPE    const&count   ,
            VALUE_TYPE    const&value   ){
          this->location = location;
          this->count    = count   ;
          this->value    = value   ;
        }
        virtual~Uniform4uiv(){}
        virtual void operator()(){
          glUniform4uiv(
            ge::core::convertTo<GLint        >(this->location),
            ge::core::convertTo<GLsizei      >(this->count   ),
            ge::core::convertTo<const GLuint*>(this->value   )
          );
        }
    };

    template<
      typename LOCATION_TYPE = GLint ,
      typename V0_TYPE       = GLuint,
      typename V1_TYPE       = GLuint>
    class Uniform2ui:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "location")return(void*)&this->location;
          if(name == "v0"      )return(void*)&this->v0      ;
          if(name == "v1"      )return(void*)&this->v1      ;
          return NULL;
        }
      public:
        LOCATION_TYPE location;
        V0_TYPE       v0      ;
        V1_TYPE       v1      ;
        Uniform2ui(
            LOCATION_TYPE const&location,
            V0_TYPE       const&v0      ,
            V1_TYPE       const&v1      ){
          this->location = location;
          this->v0       = v0      ;
          this->v1       = v1      ;
        }
        virtual~Uniform2ui(){}
        virtual void operator()(){
          glUniform2ui(
            ge::core::convertTo<GLint >(this->location),
            ge::core::convertTo<GLuint>(this->v0      ),
            ge::core::convertTo<GLuint>(this->v1      )
          );
        }
    };

    template<
      typename PROGRAM_TYPE   = GLuint         ,
      typename LOCATION_TYPE  = GLint          ,
      typename COUNT_TYPE     = GLsizei        ,
      typename TRANSPOSE_TYPE = GLboolean      ,
      typename VALUE_TYPE     = const GLdouble*>
    class ProgramUniformMatrix3x2dv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program"  )return(void*)&this->program  ;
          if(name == "location" )return(void*)&this->location ;
          if(name == "count"    )return(void*)&this->count    ;
          if(name == "transpose")return(void*)&this->transpose;
          if(name == "value"    )return(void*)&this->value    ;
          return NULL;
        }
      public:
        PROGRAM_TYPE   program  ;
        LOCATION_TYPE  location ;
        COUNT_TYPE     count    ;
        TRANSPOSE_TYPE transpose;
        VALUE_TYPE     value    ;
        ProgramUniformMatrix3x2dv(
            PROGRAM_TYPE   const&program  ,
            LOCATION_TYPE  const&location ,
            COUNT_TYPE     const&count    ,
            TRANSPOSE_TYPE const&transpose,
            VALUE_TYPE     const&value    ){
          this->program   = program  ;
          this->location  = location ;
          this->count     = count    ;
          this->transpose = transpose;
          this->value     = value    ;
        }
        virtual~ProgramUniformMatrix3x2dv(){}
        virtual void operator()(){
          glProgramUniformMatrix3x2dv(
            ge::core::convertTo<GLuint         >(this->program  ),
            ge::core::convertTo<GLint          >(this->location ),
            ge::core::convertTo<GLsizei        >(this->count    ),
            ge::core::convertTo<GLboolean      >(this->transpose),
            ge::core::convertTo<const GLdouble*>(this->value    )
          );
        }
    };

    template<
      typename SHADERTYPE_TYPE = GLenum ,
      typename LOCATION_TYPE   = GLint  ,
      typename PARAMS_TYPE     = GLuint*>
    class GetUniformSubroutineuiv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "shadertype")return(void*)&this->shadertype;
          if(name == "location"  )return(void*)&this->location  ;
          if(name == "params"    )return(void*)&this->params    ;
          return NULL;
        }
      public:
        SHADERTYPE_TYPE shadertype;
        LOCATION_TYPE   location  ;
        PARAMS_TYPE     params    ;
        GetUniformSubroutineuiv(
            SHADERTYPE_TYPE const&shadertype,
            LOCATION_TYPE   const&location  ,
            PARAMS_TYPE     const&params    ){
          this->shadertype = shadertype;
          this->location   = location  ;
          this->params     = params    ;
        }
        virtual~GetUniformSubroutineuiv(){}
        virtual void operator()(){
          glGetUniformSubroutineuiv(
            ge::core::convertTo<GLenum >(this->shadertype),
            ge::core::convertTo<GLint  >(this->location  ),
            ge::core::convertTo<GLuint*>(this->params    )
          );
        }
    };

    template<
      typename PROGRAM_TYPE  = GLuint  ,
      typename LOCATION_TYPE = GLint   ,
      typename V0_TYPE       = GLdouble,
      typename V1_TYPE       = GLdouble,
      typename V2_TYPE       = GLdouble,
      typename V3_TYPE       = GLdouble>
    class ProgramUniform4d:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program" )return(void*)&this->program ;
          if(name == "location")return(void*)&this->location;
          if(name == "v0"      )return(void*)&this->v0      ;
          if(name == "v1"      )return(void*)&this->v1      ;
          if(name == "v2"      )return(void*)&this->v2      ;
          if(name == "v3"      )return(void*)&this->v3      ;
          return NULL;
        }
      public:
        PROGRAM_TYPE  program ;
        LOCATION_TYPE location;
        V0_TYPE       v0      ;
        V1_TYPE       v1      ;
        V2_TYPE       v2      ;
        V3_TYPE       v3      ;
        ProgramUniform4d(
            PROGRAM_TYPE  const&program ,
            LOCATION_TYPE const&location,
            V0_TYPE       const&v0      ,
            V1_TYPE       const&v1      ,
            V2_TYPE       const&v2      ,
            V3_TYPE       const&v3      ){
          this->program  = program ;
          this->location = location;
          this->v0       = v0      ;
          this->v1       = v1      ;
          this->v2       = v2      ;
          this->v3       = v3      ;
        }
        virtual~ProgramUniform4d(){}
        virtual void operator()(){
          glProgramUniform4d(
            ge::core::convertTo<GLuint  >(this->program ),
            ge::core::convertTo<GLint   >(this->location),
            ge::core::convertTo<GLdouble>(this->v0      ),
            ge::core::convertTo<GLdouble>(this->v1      ),
            ge::core::convertTo<GLdouble>(this->v2      ),
            ge::core::convertTo<GLdouble>(this->v3      )
          );
        }
    };

    template<
      typename PROGRAM_TYPE           = GLuint,
      typename UNIFORMBLOCKINDEX_TYPE = GLuint,
      typename PNAME_TYPE             = GLenum,
      typename PARAMS_TYPE            = GLint*>
    class GetActiveUniformBlockiv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program"          )return(void*)&this->program          ;
          if(name == "uniformBlockIndex")return(void*)&this->uniformBlockIndex;
          if(name == "pname"            )return(void*)&this->pname            ;
          if(name == "params"           )return(void*)&this->params           ;
          return NULL;
        }
      public:
        PROGRAM_TYPE           program          ;
        UNIFORMBLOCKINDEX_TYPE uniformBlockIndex;
        PNAME_TYPE             pname            ;
        PARAMS_TYPE            params           ;
        GetActiveUniformBlockiv(
            PROGRAM_TYPE           const&program          ,
            UNIFORMBLOCKINDEX_TYPE const&uniformBlockIndex,
            PNAME_TYPE             const&pname            ,
            PARAMS_TYPE            const&params           ){
          this->program           = program          ;
          this->uniformBlockIndex = uniformBlockIndex;
          this->pname             = pname            ;
          this->params            = params           ;
        }
        virtual~GetActiveUniformBlockiv(){}
        virtual void operator()(){
          glGetActiveUniformBlockiv(
            ge::core::convertTo<GLuint>(this->program          ),
            ge::core::convertTo<GLuint>(this->uniformBlockIndex),
            ge::core::convertTo<GLenum>(this->pname            ),
            ge::core::convertTo<GLint*>(this->params           )
          );
        }
    };

    template<
      typename PROGRAM_TYPE   = GLuint        ,
      typename LOCATION_TYPE  = GLint         ,
      typename COUNT_TYPE     = GLsizei       ,
      typename TRANSPOSE_TYPE = GLboolean     ,
      typename VALUE_TYPE     = const GLfloat*>
    class ProgramUniformMatrix4x2fv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program"  )return(void*)&this->program  ;
          if(name == "location" )return(void*)&this->location ;
          if(name == "count"    )return(void*)&this->count    ;
          if(name == "transpose")return(void*)&this->transpose;
          if(name == "value"    )return(void*)&this->value    ;
          return NULL;
        }
      public:
        PROGRAM_TYPE   program  ;
        LOCATION_TYPE  location ;
        COUNT_TYPE     count    ;
        TRANSPOSE_TYPE transpose;
        VALUE_TYPE     value    ;
        ProgramUniformMatrix4x2fv(
            PROGRAM_TYPE   const&program  ,
            LOCATION_TYPE  const&location ,
            COUNT_TYPE     const&count    ,
            TRANSPOSE_TYPE const&transpose,
            VALUE_TYPE     const&value    ){
          this->program   = program  ;
          this->location  = location ;
          this->count     = count    ;
          this->transpose = transpose;
          this->value     = value    ;
        }
        virtual~ProgramUniformMatrix4x2fv(){}
        virtual void operator()(){
          glProgramUniformMatrix4x2fv(
            ge::core::convertTo<GLuint        >(this->program  ),
            ge::core::convertTo<GLint         >(this->location ),
            ge::core::convertTo<GLsizei       >(this->count    ),
            ge::core::convertTo<GLboolean     >(this->transpose),
            ge::core::convertTo<const GLfloat*>(this->value    )
          );
        }
    };

    template<
      typename PROGRAM_TYPE   = GLuint        ,
      typename LOCATION_TYPE  = GLint         ,
      typename COUNT_TYPE     = GLsizei       ,
      typename TRANSPOSE_TYPE = GLboolean     ,
      typename VALUE_TYPE     = const GLfloat*>
    class ProgramUniformMatrix3fv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program"  )return(void*)&this->program  ;
          if(name == "location" )return(void*)&this->location ;
          if(name == "count"    )return(void*)&this->count    ;
          if(name == "transpose")return(void*)&this->transpose;
          if(name == "value"    )return(void*)&this->value    ;
          return NULL;
        }
      public:
        PROGRAM_TYPE   program  ;
        LOCATION_TYPE  location ;
        COUNT_TYPE     count    ;
        TRANSPOSE_TYPE transpose;
        VALUE_TYPE     value    ;
        ProgramUniformMatrix3fv(
            PROGRAM_TYPE   const&program  ,
            LOCATION_TYPE  const&location ,
            COUNT_TYPE     const&count    ,
            TRANSPOSE_TYPE const&transpose,
            VALUE_TYPE     const&value    ){
          this->program   = program  ;
          this->location  = location ;
          this->count     = count    ;
          this->transpose = transpose;
          this->value     = value    ;
        }
        virtual~ProgramUniformMatrix3fv(){}
        virtual void operator()(){
          glProgramUniformMatrix3fv(
            ge::core::convertTo<GLuint        >(this->program  ),
            ge::core::convertTo<GLint         >(this->location ),
            ge::core::convertTo<GLsizei       >(this->count    ),
            ge::core::convertTo<GLboolean     >(this->transpose),
            ge::core::convertTo<const GLfloat*>(this->value    )
          );
        }
    };

    template<
      typename LOCATION_TYPE  = GLint         ,
      typename COUNT_TYPE     = GLsizei       ,
      typename TRANSPOSE_TYPE = GLboolean     ,
      typename VALUE_TYPE     = const GLfloat*>
    class UniformMatrix3x2fv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "location" )return(void*)&this->location ;
          if(name == "count"    )return(void*)&this->count    ;
          if(name == "transpose")return(void*)&this->transpose;
          if(name == "value"    )return(void*)&this->value    ;
          return NULL;
        }
      public:
        LOCATION_TYPE  location ;
        COUNT_TYPE     count    ;
        TRANSPOSE_TYPE transpose;
        VALUE_TYPE     value    ;
        UniformMatrix3x2fv(
            LOCATION_TYPE  const&location ,
            COUNT_TYPE     const&count    ,
            TRANSPOSE_TYPE const&transpose,
            VALUE_TYPE     const&value    ){
          this->location  = location ;
          this->count     = count    ;
          this->transpose = transpose;
          this->value     = value    ;
        }
        virtual~UniformMatrix3x2fv(){}
        virtual void operator()(){
          glUniformMatrix3x2fv(
            ge::core::convertTo<GLint         >(this->location ),
            ge::core::convertTo<GLsizei       >(this->count    ),
            ge::core::convertTo<GLboolean     >(this->transpose),
            ge::core::convertTo<const GLfloat*>(this->value    )
          );
        }
    };

    template<
      typename PROGRAM_TYPE  = GLuint   ,
      typename LOCATION_TYPE = GLint    ,
      typename PARAMS_TYPE   = GLdouble*>
    class GetUniformdv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program" )return(void*)&this->program ;
          if(name == "location")return(void*)&this->location;
          if(name == "params"  )return(void*)&this->params  ;
          return NULL;
        }
      public:
        PROGRAM_TYPE  program ;
        LOCATION_TYPE location;
        PARAMS_TYPE   params  ;
        GetUniformdv(
            PROGRAM_TYPE  const&program ,
            LOCATION_TYPE const&location,
            PARAMS_TYPE   const&params  ){
          this->program  = program ;
          this->location = location;
          this->params   = params  ;
        }
        virtual~GetUniformdv(){}
        virtual void operator()(){
          glGetUniformdv(
            ge::core::convertTo<GLuint   >(this->program ),
            ge::core::convertTo<GLint    >(this->location),
            ge::core::convertTo<GLdouble*>(this->params  )
          );
        }
    };

    template<
      typename LOCATION_TYPE = GLint  ,
      typename V0_TYPE       = GLfloat,
      typename V1_TYPE       = GLfloat,
      typename V2_TYPE       = GLfloat>
    class Uniform3f:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "location")return(void*)&this->location;
          if(name == "v0"      )return(void*)&this->v0      ;
          if(name == "v1"      )return(void*)&this->v1      ;
          if(name == "v2"      )return(void*)&this->v2      ;
          return NULL;
        }
      public:
        LOCATION_TYPE location;
        V0_TYPE       v0      ;
        V1_TYPE       v1      ;
        V2_TYPE       v2      ;
        Uniform3f(
            LOCATION_TYPE const&location,
            V0_TYPE       const&v0      ,
            V1_TYPE       const&v1      ,
            V2_TYPE       const&v2      ){
          this->location = location;
          this->v0       = v0      ;
          this->v1       = v1      ;
          this->v2       = v2      ;
        }
        virtual~Uniform3f(){}
        virtual void operator()(){
          glUniform3f(
            ge::core::convertTo<GLint  >(this->location),
            ge::core::convertTo<GLfloat>(this->v0      ),
            ge::core::convertTo<GLfloat>(this->v1      ),
            ge::core::convertTo<GLfloat>(this->v2      )
          );
        }
    };

    template<
      typename PROGRAM_TYPE  = GLuint ,
      typename LOCATION_TYPE = GLint  ,
      typename V0_TYPE       = GLfloat,
      typename V1_TYPE       = GLfloat>
    class ProgramUniform2f:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program" )return(void*)&this->program ;
          if(name == "location")return(void*)&this->location;
          if(name == "v0"      )return(void*)&this->v0      ;
          if(name == "v1"      )return(void*)&this->v1      ;
          return NULL;
        }
      public:
        PROGRAM_TYPE  program ;
        LOCATION_TYPE location;
        V0_TYPE       v0      ;
        V1_TYPE       v1      ;
        ProgramUniform2f(
            PROGRAM_TYPE  const&program ,
            LOCATION_TYPE const&location,
            V0_TYPE       const&v0      ,
            V1_TYPE       const&v1      ){
          this->program  = program ;
          this->location = location;
          this->v0       = v0      ;
          this->v1       = v1      ;
        }
        virtual~ProgramUniform2f(){}
        virtual void operator()(){
          glProgramUniform2f(
            ge::core::convertTo<GLuint >(this->program ),
            ge::core::convertTo<GLint  >(this->location),
            ge::core::convertTo<GLfloat>(this->v0      ),
            ge::core::convertTo<GLfloat>(this->v1      )
          );
        }
    };

    template<
      typename PROGRAM_TYPE  = GLuint         ,
      typename LOCATION_TYPE = GLint          ,
      typename COUNT_TYPE    = GLsizei        ,
      typename VALUE_TYPE    = const GLdouble*>
    class ProgramUniform1dv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program" )return(void*)&this->program ;
          if(name == "location")return(void*)&this->location;
          if(name == "count"   )return(void*)&this->count   ;
          if(name == "value"   )return(void*)&this->value   ;
          return NULL;
        }
      public:
        PROGRAM_TYPE  program ;
        LOCATION_TYPE location;
        COUNT_TYPE    count   ;
        VALUE_TYPE    value   ;
        ProgramUniform1dv(
            PROGRAM_TYPE  const&program ,
            LOCATION_TYPE const&location,
            COUNT_TYPE    const&count   ,
            VALUE_TYPE    const&value   ){
          this->program  = program ;
          this->location = location;
          this->count    = count   ;
          this->value    = value   ;
        }
        virtual~ProgramUniform1dv(){}
        virtual void operator()(){
          glProgramUniform1dv(
            ge::core::convertTo<GLuint         >(this->program ),
            ge::core::convertTo<GLint          >(this->location),
            ge::core::convertTo<GLsizei        >(this->count   ),
            ge::core::convertTo<const GLdouble*>(this->value   )
          );
        }
    };

    template<
      typename LOCATION_TYPE  = GLint          ,
      typename COUNT_TYPE     = GLsizei        ,
      typename TRANSPOSE_TYPE = GLboolean      ,
      typename VALUE_TYPE     = const GLdouble*>
    class UniformMatrix2dv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "location" )return(void*)&this->location ;
          if(name == "count"    )return(void*)&this->count    ;
          if(name == "transpose")return(void*)&this->transpose;
          if(name == "value"    )return(void*)&this->value    ;
          return NULL;
        }
      public:
        LOCATION_TYPE  location ;
        COUNT_TYPE     count    ;
        TRANSPOSE_TYPE transpose;
        VALUE_TYPE     value    ;
        UniformMatrix2dv(
            LOCATION_TYPE  const&location ,
            COUNT_TYPE     const&count    ,
            TRANSPOSE_TYPE const&transpose,
            VALUE_TYPE     const&value    ){
          this->location  = location ;
          this->count     = count    ;
          this->transpose = transpose;
          this->value     = value    ;
        }
        virtual~UniformMatrix2dv(){}
        virtual void operator()(){
          glUniformMatrix2dv(
            ge::core::convertTo<GLint          >(this->location ),
            ge::core::convertTo<GLsizei        >(this->count    ),
            ge::core::convertTo<GLboolean      >(this->transpose),
            ge::core::convertTo<const GLdouble*>(this->value    )
          );
        }
    };

    template<
      typename RET_TYPE     = GLint        ,
      typename PROGRAM_TYPE = GLuint       ,
      typename NAME_TYPE    = const GLchar*>
    class GetUniformLocation:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "ret"    )return(void*)&this->ret    ;
          if(name == "program")return(void*)&this->program;
          if(name == "name"   )return(void*)&this->name   ;
          return NULL;
        }
      public:
        RET_TYPE     ret    ;
        PROGRAM_TYPE program;
        NAME_TYPE    name   ;
        GetUniformLocation(
            RET_TYPE     const&ret    ,
            PROGRAM_TYPE const&program,
            NAME_TYPE    const&name   ){
          this->ret     = ret    ;
          this->program = program;
          this->name    = name   ;
        }
        virtual~GetUniformLocation(){}
        virtual void operator()(){
          ge::core::convertFrom<GLint>(this->ret,glGetUniformLocation(
              ge::core::convertTo<GLuint       >(this->program),
              ge::core::convertTo<const GLchar*>(this->name   ))
          );
        }
    };

    template<
      typename LOCATION_TYPE = GLint  ,
      typename V0_TYPE       = GLfloat>
    class Uniform1f:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "location")return(void*)&this->location;
          if(name == "v0"      )return(void*)&this->v0      ;
          return NULL;
        }
      public:
        LOCATION_TYPE location;
        V0_TYPE       v0      ;
        Uniform1f(
            LOCATION_TYPE const&location,
            V0_TYPE       const&v0      ){
          this->location = location;
          this->v0       = v0      ;
        }
        virtual~Uniform1f(){}
        virtual void operator()(){
          glUniform1f(
            ge::core::convertTo<GLint  >(this->location),
            ge::core::convertTo<GLfloat>(this->v0      )
          );
        }
    };

    template<
      typename LOCATION_TYPE = GLint        ,
      typename COUNT_TYPE    = GLsizei      ,
      typename VALUE_TYPE    = const GLuint*>
    class Uniform3uiv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "location")return(void*)&this->location;
          if(name == "count"   )return(void*)&this->count   ;
          if(name == "value"   )return(void*)&this->value   ;
          return NULL;
        }
      public:
        LOCATION_TYPE location;
        COUNT_TYPE    count   ;
        VALUE_TYPE    value   ;
        Uniform3uiv(
            LOCATION_TYPE const&location,
            COUNT_TYPE    const&count   ,
            VALUE_TYPE    const&value   ){
          this->location = location;
          this->count    = count   ;
          this->value    = value   ;
        }
        virtual~Uniform3uiv(){}
        virtual void operator()(){
          glUniform3uiv(
            ge::core::convertTo<GLint        >(this->location),
            ge::core::convertTo<GLsizei      >(this->count   ),
            ge::core::convertTo<const GLuint*>(this->value   )
          );
        }
    };

    template<
      typename PROGRAM_TYPE   = GLuint        ,
      typename LOCATION_TYPE  = GLint         ,
      typename COUNT_TYPE     = GLsizei       ,
      typename TRANSPOSE_TYPE = GLboolean     ,
      typename VALUE_TYPE     = const GLfloat*>
    class ProgramUniformMatrix4x3fv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program"  )return(void*)&this->program  ;
          if(name == "location" )return(void*)&this->location ;
          if(name == "count"    )return(void*)&this->count    ;
          if(name == "transpose")return(void*)&this->transpose;
          if(name == "value"    )return(void*)&this->value    ;
          return NULL;
        }
      public:
        PROGRAM_TYPE   program  ;
        LOCATION_TYPE  location ;
        COUNT_TYPE     count    ;
        TRANSPOSE_TYPE transpose;
        VALUE_TYPE     value    ;
        ProgramUniformMatrix4x3fv(
            PROGRAM_TYPE   const&program  ,
            LOCATION_TYPE  const&location ,
            COUNT_TYPE     const&count    ,
            TRANSPOSE_TYPE const&transpose,
            VALUE_TYPE     const&value    ){
          this->program   = program  ;
          this->location  = location ;
          this->count     = count    ;
          this->transpose = transpose;
          this->value     = value    ;
        }
        virtual~ProgramUniformMatrix4x3fv(){}
        virtual void operator()(){
          glProgramUniformMatrix4x3fv(
            ge::core::convertTo<GLuint        >(this->program  ),
            ge::core::convertTo<GLint         >(this->location ),
            ge::core::convertTo<GLsizei       >(this->count    ),
            ge::core::convertTo<GLboolean     >(this->transpose),
            ge::core::convertTo<const GLfloat*>(this->value    )
          );
        }
    };

    template<
      typename LOCATION_TYPE = GLint   ,
      typename X_TYPE        = GLdouble>
    class Uniform1d:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "location")return(void*)&this->location;
          if(name == "x"       )return(void*)&this->x       ;
          return NULL;
        }
      public:
        LOCATION_TYPE location;
        X_TYPE        x       ;
        Uniform1d(
            LOCATION_TYPE const&location,
            X_TYPE        const&x       ){
          this->location = location;
          this->x        = x       ;
        }
        virtual~Uniform1d(){}
        virtual void operator()(){
          glUniform1d(
            ge::core::convertTo<GLint   >(this->location),
            ge::core::convertTo<GLdouble>(this->x       )
          );
        }
    };

    template<
      typename PROGRAM_TYPE      = GLuint  ,
      typename UNIFORMINDEX_TYPE = GLuint  ,
      typename BUFSIZE_TYPE      = GLsizei ,
      typename LENGTH_TYPE       = GLsizei*,
      typename UNIFORMNAME_TYPE  = GLchar* >
    class GetActiveUniformName:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program"     )return(void*)&this->program     ;
          if(name == "uniformIndex")return(void*)&this->uniformIndex;
          if(name == "bufSize"     )return(void*)&this->bufSize     ;
          if(name == "length"      )return(void*)&this->length      ;
          if(name == "uniformName" )return(void*)&this->uniformName ;
          return NULL;
        }
      public:
        PROGRAM_TYPE      program     ;
        UNIFORMINDEX_TYPE uniformIndex;
        BUFSIZE_TYPE      bufSize     ;
        LENGTH_TYPE       length      ;
        UNIFORMNAME_TYPE  uniformName ;
        GetActiveUniformName(
            PROGRAM_TYPE      const&program     ,
            UNIFORMINDEX_TYPE const&uniformIndex,
            BUFSIZE_TYPE      const&bufSize     ,
            LENGTH_TYPE       const&length      ,
            UNIFORMNAME_TYPE  const&uniformName ){
          this->program      = program     ;
          this->uniformIndex = uniformIndex;
          this->bufSize      = bufSize     ;
          this->length       = length      ;
          this->uniformName  = uniformName ;
        }
        virtual~GetActiveUniformName(){}
        virtual void operator()(){
          glGetActiveUniformName(
            ge::core::convertTo<GLuint  >(this->program     ),
            ge::core::convertTo<GLuint  >(this->uniformIndex),
            ge::core::convertTo<GLsizei >(this->bufSize     ),
            ge::core::convertTo<GLsizei*>(this->length      ),
            ge::core::convertTo<GLchar* >(this->uniformName )
          );
        }
    };

    template<
      typename PROGRAM_TYPE  = GLuint  ,
      typename LOCATION_TYPE = GLint   ,
      typename V0_TYPE       = GLdouble>
    class ProgramUniform1d:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program" )return(void*)&this->program ;
          if(name == "location")return(void*)&this->location;
          if(name == "v0"      )return(void*)&this->v0      ;
          return NULL;
        }
      public:
        PROGRAM_TYPE  program ;
        LOCATION_TYPE location;
        V0_TYPE       v0      ;
        ProgramUniform1d(
            PROGRAM_TYPE  const&program ,
            LOCATION_TYPE const&location,
            V0_TYPE       const&v0      ){
          this->program  = program ;
          this->location = location;
          this->v0       = v0      ;
        }
        virtual~ProgramUniform1d(){}
        virtual void operator()(){
          glProgramUniform1d(
            ge::core::convertTo<GLuint  >(this->program ),
            ge::core::convertTo<GLint   >(this->location),
            ge::core::convertTo<GLdouble>(this->v0      )
          );
        }
    };

    template<
      typename PROGRAM_TYPE    = GLuint  ,
      typename SHADERTYPE_TYPE = GLenum  ,
      typename INDEX_TYPE      = GLuint  ,
      typename BUFSIZE_TYPE    = GLsizei ,
      typename LENGTH_TYPE     = GLsizei*,
      typename NAME_TYPE       = GLchar* >
    class GetActiveSubroutineUniformName:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program"   )return(void*)&this->program   ;
          if(name == "shadertype")return(void*)&this->shadertype;
          if(name == "index"     )return(void*)&this->index     ;
          if(name == "bufsize"   )return(void*)&this->bufsize   ;
          if(name == "length"    )return(void*)&this->length    ;
          if(name == "name"      )return(void*)&this->name      ;
          return NULL;
        }
      public:
        PROGRAM_TYPE    program   ;
        SHADERTYPE_TYPE shadertype;
        INDEX_TYPE      index     ;
        BUFSIZE_TYPE    bufsize   ;
        LENGTH_TYPE     length    ;
        NAME_TYPE       name      ;
        GetActiveSubroutineUniformName(
            PROGRAM_TYPE    const&program   ,
            SHADERTYPE_TYPE const&shadertype,
            INDEX_TYPE      const&index     ,
            BUFSIZE_TYPE    const&bufsize   ,
            LENGTH_TYPE     const&length    ,
            NAME_TYPE       const&name      ){
          this->program    = program   ;
          this->shadertype = shadertype;
          this->index      = index     ;
          this->bufsize    = bufsize   ;
          this->length     = length    ;
          this->name       = name      ;
        }
        virtual~GetActiveSubroutineUniformName(){}
        virtual void operator()(){
          glGetActiveSubroutineUniformName(
            ge::core::convertTo<GLuint  >(this->program   ),
            ge::core::convertTo<GLenum  >(this->shadertype),
            ge::core::convertTo<GLuint  >(this->index     ),
            ge::core::convertTo<GLsizei >(this->bufsize   ),
            ge::core::convertTo<GLsizei*>(this->length    ),
            ge::core::convertTo<GLchar* >(this->name      )
          );
        }
    };

    template<
      typename PROGRAM_TYPE  = GLuint         ,
      typename LOCATION_TYPE = GLint          ,
      typename COUNT_TYPE    = GLsizei        ,
      typename VALUE_TYPE    = const GLdouble*>
    class ProgramUniform4dv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "program" )return(void*)&this->program ;
          if(name == "location")return(void*)&this->location;
          if(name == "count"   )return(void*)&this->count   ;
          if(name == "value"   )return(void*)&this->value   ;
          return NULL;
        }
      public:
        PROGRAM_TYPE  program ;
        LOCATION_TYPE location;
        COUNT_TYPE    count   ;
        VALUE_TYPE    value   ;
        ProgramUniform4dv(
            PROGRAM_TYPE  const&program ,
            LOCATION_TYPE const&location,
            COUNT_TYPE    const&count   ,
            VALUE_TYPE    const&value   ){
          this->program  = program ;
          this->location = location;
          this->count    = count   ;
          this->value    = value   ;
        }
        virtual~ProgramUniform4dv(){}
        virtual void operator()(){
          glProgramUniform4dv(
            ge::core::convertTo<GLuint         >(this->program ),
            ge::core::convertTo<GLint          >(this->location),
            ge::core::convertTo<GLsizei        >(this->count   ),
            ge::core::convertTo<const GLdouble*>(this->value   )
          );
        }
    };

    template<
      typename LOCATION_TYPE = GLint   ,
      typename X_TYPE        = GLdouble,
      typename Y_TYPE        = GLdouble>
    inline Uniform2d<
      LOCATION_TYPE,
      X_TYPE       ,
      Y_TYPE       >* newUniform2d(
        LOCATION_TYPE const&location,
        X_TYPE        const&x       ,
        Y_TYPE        const&y       ){
        return new Uniform2d<
          LOCATION_TYPE,
          X_TYPE       ,
          Y_TYPE       >(
              location,
              x       ,
              y       );
    }
    template<
      typename PROGRAM_TYPE  = GLuint  ,
      typename LOCATION_TYPE = GLint   ,
      typename BUFSIZE_TYPE  = GLsizei ,
      typename PARAMS_TYPE   = GLfloat*>
    inline GetnUniformfv<
      PROGRAM_TYPE ,
      LOCATION_TYPE,
      BUFSIZE_TYPE ,
      PARAMS_TYPE  >* newGetnUniformfv(
        PROGRAM_TYPE  const&program ,
        LOCATION_TYPE const&location,
        BUFSIZE_TYPE  const&bufSize ,
        PARAMS_TYPE   const&params  ){
        return new GetnUniformfv<
          PROGRAM_TYPE ,
          LOCATION_TYPE,
          BUFSIZE_TYPE ,
          PARAMS_TYPE  >(
              program ,
              location,
              bufSize ,
              params  );
    }
    template<
      typename PROGRAM_TYPE   = GLuint         ,
      typename LOCATION_TYPE  = GLint          ,
      typename COUNT_TYPE     = GLsizei        ,
      typename TRANSPOSE_TYPE = GLboolean      ,
      typename VALUE_TYPE     = const GLdouble*>
    inline ProgramUniformMatrix4x3dv<
      PROGRAM_TYPE  ,
      LOCATION_TYPE ,
      COUNT_TYPE    ,
      TRANSPOSE_TYPE,
      VALUE_TYPE    >* newProgramUniformMatrix4x3dv(
        PROGRAM_TYPE   const&program  ,
        LOCATION_TYPE  const&location ,
        COUNT_TYPE     const&count    ,
        TRANSPOSE_TYPE const&transpose,
        VALUE_TYPE     const&value    ){
        return new ProgramUniformMatrix4x3dv<
          PROGRAM_TYPE  ,
          LOCATION_TYPE ,
          COUNT_TYPE    ,
          TRANSPOSE_TYPE,
          VALUE_TYPE    >(
              program  ,
              location ,
              count    ,
              transpose,
              value    );
    }
    template<
      typename LOCATION_TYPE = GLint          ,
      typename COUNT_TYPE    = GLsizei        ,
      typename VALUE_TYPE    = const GLdouble*>
    inline Uniform3dv<
      LOCATION_TYPE,
      COUNT_TYPE   ,
      VALUE_TYPE   >* newUniform3dv(
        LOCATION_TYPE const&location,
        COUNT_TYPE    const&count   ,
        VALUE_TYPE    const&value   ){
        return new Uniform3dv<
          LOCATION_TYPE,
          COUNT_TYPE   ,
          VALUE_TYPE   >(
              location,
              count   ,
              value   );
    }
    template<
      typename LOCATION_TYPE = GLint         ,
      typename COUNT_TYPE    = GLsizei       ,
      typename VALUE_TYPE    = const GLfloat*>
    inline Uniform1fv<
      LOCATION_TYPE,
      COUNT_TYPE   ,
      VALUE_TYPE   >* newUniform1fv(
        LOCATION_TYPE const&location,
        COUNT_TYPE    const&count   ,
        VALUE_TYPE    const&value   ){
        return new Uniform1fv<
          LOCATION_TYPE,
          COUNT_TYPE   ,
          VALUE_TYPE   >(
              location,
              count   ,
              value   );
    }
    template<
      typename LOCATION_TYPE  = GLint          ,
      typename COUNT_TYPE     = GLsizei        ,
      typename TRANSPOSE_TYPE = GLboolean      ,
      typename VALUE_TYPE     = const GLdouble*>
    inline UniformMatrix2x3dv<
      LOCATION_TYPE ,
      COUNT_TYPE    ,
      TRANSPOSE_TYPE,
      VALUE_TYPE    >* newUniformMatrix2x3dv(
        LOCATION_TYPE  const&location ,
        COUNT_TYPE     const&count    ,
        TRANSPOSE_TYPE const&transpose,
        VALUE_TYPE     const&value    ){
        return new UniformMatrix2x3dv<
          LOCATION_TYPE ,
          COUNT_TYPE    ,
          TRANSPOSE_TYPE,
          VALUE_TYPE    >(
              location ,
              count    ,
              transpose,
              value    );
    }
    template<
      typename LOCATION_TYPE = GLint          ,
      typename COUNT_TYPE    = GLsizei        ,
      typename VALUE_TYPE    = const GLdouble*>
    inline Uniform1dv<
      LOCATION_TYPE,
      COUNT_TYPE   ,
      VALUE_TYPE   >* newUniform1dv(
        LOCATION_TYPE const&location,
        COUNT_TYPE    const&count   ,
        VALUE_TYPE    const&value   ){
        return new Uniform1dv<
          LOCATION_TYPE,
          COUNT_TYPE   ,
          VALUE_TYPE   >(
              location,
              count   ,
              value   );
    }
    template<
      typename PROGRAM_TYPE   = GLuint         ,
      typename LOCATION_TYPE  = GLint          ,
      typename COUNT_TYPE     = GLsizei        ,
      typename TRANSPOSE_TYPE = GLboolean      ,
      typename VALUE_TYPE     = const GLdouble*>
    inline ProgramUniformMatrix2x4dv<
      PROGRAM_TYPE  ,
      LOCATION_TYPE ,
      COUNT_TYPE    ,
      TRANSPOSE_TYPE,
      VALUE_TYPE    >* newProgramUniformMatrix2x4dv(
        PROGRAM_TYPE   const&program  ,
        LOCATION_TYPE  const&location ,
        COUNT_TYPE     const&count    ,
        TRANSPOSE_TYPE const&transpose,
        VALUE_TYPE     const&value    ){
        return new ProgramUniformMatrix2x4dv<
          PROGRAM_TYPE  ,
          LOCATION_TYPE ,
          COUNT_TYPE    ,
          TRANSPOSE_TYPE,
          VALUE_TYPE    >(
              program  ,
              location ,
              count    ,
              transpose,
              value    );
    }
    template<
      typename PROGRAM_TYPE    = GLuint,
      typename SHADERTYPE_TYPE = GLenum,
      typename INDEX_TYPE      = GLuint,
      typename PNAME_TYPE      = GLenum,
      typename VALUES_TYPE     = GLint*>
    inline GetActiveSubroutineUniformiv<
      PROGRAM_TYPE   ,
      SHADERTYPE_TYPE,
      INDEX_TYPE     ,
      PNAME_TYPE     ,
      VALUES_TYPE    >* newGetActiveSubroutineUniformiv(
        PROGRAM_TYPE    const&program   ,
        SHADERTYPE_TYPE const&shadertype,
        INDEX_TYPE      const&index     ,
        PNAME_TYPE      const&pname     ,
        VALUES_TYPE     const&values    ){
        return new GetActiveSubroutineUniformiv<
          PROGRAM_TYPE   ,
          SHADERTYPE_TYPE,
          INDEX_TYPE     ,
          PNAME_TYPE     ,
          VALUES_TYPE    >(
              program   ,
              shadertype,
              index     ,
              pname     ,
              values    );
    }
    template<
      typename PROGRAM_TYPE   = GLuint         ,
      typename LOCATION_TYPE  = GLint          ,
      typename COUNT_TYPE     = GLsizei        ,
      typename TRANSPOSE_TYPE = GLboolean      ,
      typename VALUE_TYPE     = const GLdouble*>
    inline ProgramUniformMatrix4x2dv<
      PROGRAM_TYPE  ,
      LOCATION_TYPE ,
      COUNT_TYPE    ,
      TRANSPOSE_TYPE,
      VALUE_TYPE    >* newProgramUniformMatrix4x2dv(
        PROGRAM_TYPE   const&program  ,
        LOCATION_TYPE  const&location ,
        COUNT_TYPE     const&count    ,
        TRANSPOSE_TYPE const&transpose,
        VALUE_TYPE     const&value    ){
        return new ProgramUniformMatrix4x2dv<
          PROGRAM_TYPE  ,
          LOCATION_TYPE ,
          COUNT_TYPE    ,
          TRANSPOSE_TYPE,
          VALUE_TYPE    >(
              program  ,
              location ,
              count    ,
              transpose,
              value    );
    }
    template<
      typename PROGRAM_TYPE  = GLuint,
      typename LOCATION_TYPE = GLint ,
      typename V0_TYPE       = GLuint>
    inline ProgramUniform1ui<
      PROGRAM_TYPE ,
      LOCATION_TYPE,
      V0_TYPE      >* newProgramUniform1ui(
        PROGRAM_TYPE  const&program ,
        LOCATION_TYPE const&location,
        V0_TYPE       const&v0      ){
        return new ProgramUniform1ui<
          PROGRAM_TYPE ,
          LOCATION_TYPE,
          V0_TYPE      >(
              program ,
              location,
              v0      );
    }
    template<
      typename PROGRAM_TYPE             = GLuint,
      typename UNIFORMBLOCKINDEX_TYPE   = GLuint,
      typename UNIFORMBLOCKBINDING_TYPE = GLuint>
    inline UniformBlockBinding<
      PROGRAM_TYPE            ,
      UNIFORMBLOCKINDEX_TYPE  ,
      UNIFORMBLOCKBINDING_TYPE>* newUniformBlockBinding(
        PROGRAM_TYPE             const&program            ,
        UNIFORMBLOCKINDEX_TYPE   const&uniformBlockIndex  ,
        UNIFORMBLOCKBINDING_TYPE const&uniformBlockBinding){
        return new UniformBlockBinding<
          PROGRAM_TYPE            ,
          UNIFORMBLOCKINDEX_TYPE  ,
          UNIFORMBLOCKBINDING_TYPE>(
              program            ,
              uniformBlockIndex  ,
              uniformBlockBinding);
    }
    template<
      typename PROGRAM_TYPE  = GLuint   ,
      typename LOCATION_TYPE = GLint    ,
      typename BUFSIZE_TYPE  = GLsizei  ,
      typename PARAMS_TYPE   = GLdouble*>
    inline GetnUniformdv<
      PROGRAM_TYPE ,
      LOCATION_TYPE,
      BUFSIZE_TYPE ,
      PARAMS_TYPE  >* newGetnUniformdv(
        PROGRAM_TYPE  const&program ,
        LOCATION_TYPE const&location,
        BUFSIZE_TYPE  const&bufSize ,
        PARAMS_TYPE   const&params  ){
        return new GetnUniformdv<
          PROGRAM_TYPE ,
          LOCATION_TYPE,
          BUFSIZE_TYPE ,
          PARAMS_TYPE  >(
              program ,
              location,
              bufSize ,
              params  );
    }
    template<
      typename PROGRAM_TYPE  = GLuint,
      typename LOCATION_TYPE = GLint ,
      typename V0_TYPE       = GLuint,
      typename V1_TYPE       = GLuint,
      typename V2_TYPE       = GLuint,
      typename V3_TYPE       = GLuint>
    inline ProgramUniform4ui<
      PROGRAM_TYPE ,
      LOCATION_TYPE,
      V0_TYPE      ,
      V1_TYPE      ,
      V2_TYPE      ,
      V3_TYPE      >* newProgramUniform4ui(
        PROGRAM_TYPE  const&program ,
        LOCATION_TYPE const&location,
        V0_TYPE       const&v0      ,
        V1_TYPE       const&v1      ,
        V2_TYPE       const&v2      ,
        V3_TYPE       const&v3      ){
        return new ProgramUniform4ui<
          PROGRAM_TYPE ,
          LOCATION_TYPE,
          V0_TYPE      ,
          V1_TYPE      ,
          V2_TYPE      ,
          V3_TYPE      >(
              program ,
              location,
              v0      ,
              v1      ,
              v2      ,
              v3      );
    }
    template<
      typename PROGRAM_TYPE   = GLuint        ,
      typename LOCATION_TYPE  = GLint         ,
      typename COUNT_TYPE     = GLsizei       ,
      typename TRANSPOSE_TYPE = GLboolean     ,
      typename VALUE_TYPE     = const GLfloat*>
    inline ProgramUniformMatrix2x4fv<
      PROGRAM_TYPE  ,
      LOCATION_TYPE ,
      COUNT_TYPE    ,
      TRANSPOSE_TYPE,
      VALUE_TYPE    >* newProgramUniformMatrix2x4fv(
        PROGRAM_TYPE   const&program  ,
        LOCATION_TYPE  const&location ,
        COUNT_TYPE     const&count    ,
        TRANSPOSE_TYPE const&transpose,
        VALUE_TYPE     const&value    ){
        return new ProgramUniformMatrix2x4fv<
          PROGRAM_TYPE  ,
          LOCATION_TYPE ,
          COUNT_TYPE    ,
          TRANSPOSE_TYPE,
          VALUE_TYPE    >(
              program  ,
              location ,
              count    ,
              transpose,
              value    );
    }
    template<
      typename PROGRAM_TYPE  = GLuint      ,
      typename LOCATION_TYPE = GLint       ,
      typename COUNT_TYPE    = GLsizei     ,
      typename VALUE_TYPE    = const GLint*>
    inline ProgramUniform1iv<
      PROGRAM_TYPE ,
      LOCATION_TYPE,
      COUNT_TYPE   ,
      VALUE_TYPE   >* newProgramUniform1iv(
        PROGRAM_TYPE  const&program ,
        LOCATION_TYPE const&location,
        COUNT_TYPE    const&count   ,
        VALUE_TYPE    const&value   ){
        return new ProgramUniform1iv<
          PROGRAM_TYPE ,
          LOCATION_TYPE,
          COUNT_TYPE   ,
          VALUE_TYPE   >(
              program ,
              location,
              count   ,
              value   );
    }
    template<
      typename LOCATION_TYPE = GLint        ,
      typename COUNT_TYPE    = GLsizei      ,
      typename VALUE_TYPE    = const GLuint*>
    inline Uniform2uiv<
      LOCATION_TYPE,
      COUNT_TYPE   ,
      VALUE_TYPE   >* newUniform2uiv(
        LOCATION_TYPE const&location,
        COUNT_TYPE    const&count   ,
        VALUE_TYPE    const&value   ){
        return new Uniform2uiv<
          LOCATION_TYPE,
          COUNT_TYPE   ,
          VALUE_TYPE   >(
              location,
              count   ,
              value   );
    }
    template<
      typename PROGRAM_TYPE  = GLuint        ,
      typename LOCATION_TYPE = GLint         ,
      typename COUNT_TYPE    = GLsizei       ,
      typename VALUE_TYPE    = const GLfloat*>
    inline ProgramUniform3fv<
      PROGRAM_TYPE ,
      LOCATION_TYPE,
      COUNT_TYPE   ,
      VALUE_TYPE   >* newProgramUniform3fv(
        PROGRAM_TYPE  const&program ,
        LOCATION_TYPE const&location,
        COUNT_TYPE    const&count   ,
        VALUE_TYPE    const&value   ){
        return new ProgramUniform3fv<
          PROGRAM_TYPE ,
          LOCATION_TYPE,
          COUNT_TYPE   ,
          VALUE_TYPE   >(
              program ,
              location,
              count   ,
              value   );
    }
    template<
      typename PROGRAM_TYPE  = GLuint        ,
      typename LOCATION_TYPE = GLint         ,
      typename COUNT_TYPE    = GLsizei       ,
      typename VALUE_TYPE    = const GLfloat*>
    inline ProgramUniform1fv<
      PROGRAM_TYPE ,
      LOCATION_TYPE,
      COUNT_TYPE   ,
      VALUE_TYPE   >* newProgramUniform1fv(
        PROGRAM_TYPE  const&program ,
        LOCATION_TYPE const&location,
        COUNT_TYPE    const&count   ,
        VALUE_TYPE    const&value   ){
        return new ProgramUniform1fv<
          PROGRAM_TYPE ,
          LOCATION_TYPE,
          COUNT_TYPE   ,
          VALUE_TYPE   >(
              program ,
              location,
              count   ,
              value   );
    }
    template<
      typename PROGRAM_TYPE  = GLuint,
      typename LOCATION_TYPE = GLint ,
      typename V0_TYPE       = GLuint,
      typename V1_TYPE       = GLuint>
    inline ProgramUniform2ui<
      PROGRAM_TYPE ,
      LOCATION_TYPE,
      V0_TYPE      ,
      V1_TYPE      >* newProgramUniform2ui(
        PROGRAM_TYPE  const&program ,
        LOCATION_TYPE const&location,
        V0_TYPE       const&v0      ,
        V1_TYPE       const&v1      ){
        return new ProgramUniform2ui<
          PROGRAM_TYPE ,
          LOCATION_TYPE,
          V0_TYPE      ,
          V1_TYPE      >(
              program ,
              location,
              v0      ,
              v1      );
    }
    template<
      typename LOCATION_TYPE = GLint ,
      typename V0_TYPE       = GLuint,
      typename V1_TYPE       = GLuint,
      typename V2_TYPE       = GLuint>
    inline Uniform3ui<
      LOCATION_TYPE,
      V0_TYPE      ,
      V1_TYPE      ,
      V2_TYPE      >* newUniform3ui(
        LOCATION_TYPE const&location,
        V0_TYPE       const&v0      ,
        V1_TYPE       const&v1      ,
        V2_TYPE       const&v2      ){
        return new Uniform3ui<
          LOCATION_TYPE,
          V0_TYPE      ,
          V1_TYPE      ,
          V2_TYPE      >(
              location,
              v0      ,
              v1      ,
              v2      );
    }
    template<
      typename LOCATION_TYPE = GLint       ,
      typename COUNT_TYPE    = GLsizei     ,
      typename VALUE_TYPE    = const GLint*>
    inline Uniform3iv<
      LOCATION_TYPE,
      COUNT_TYPE   ,
      VALUE_TYPE   >* newUniform3iv(
        LOCATION_TYPE const&location,
        COUNT_TYPE    const&count   ,
        VALUE_TYPE    const&value   ){
        return new Uniform3iv<
          LOCATION_TYPE,
          COUNT_TYPE   ,
          VALUE_TYPE   >(
              location,
              count   ,
              value   );
    }
    template<
      typename PROGRAM_TYPE           = GLuint  ,
      typename UNIFORMBLOCKINDEX_TYPE = GLuint  ,
      typename BUFSIZE_TYPE           = GLsizei ,
      typename LENGTH_TYPE            = GLsizei*,
      typename UNIFORMBLOCKNAME_TYPE  = GLchar* >
    inline GetActiveUniformBlockName<
      PROGRAM_TYPE          ,
      UNIFORMBLOCKINDEX_TYPE,
      BUFSIZE_TYPE          ,
      LENGTH_TYPE           ,
      UNIFORMBLOCKNAME_TYPE >* newGetActiveUniformBlockName(
        PROGRAM_TYPE           const&program          ,
        UNIFORMBLOCKINDEX_TYPE const&uniformBlockIndex,
        BUFSIZE_TYPE           const&bufSize          ,
        LENGTH_TYPE            const&length           ,
        UNIFORMBLOCKNAME_TYPE  const&uniformBlockName ){
        return new GetActiveUniformBlockName<
          PROGRAM_TYPE          ,
          UNIFORMBLOCKINDEX_TYPE,
          BUFSIZE_TYPE          ,
          LENGTH_TYPE           ,
          UNIFORMBLOCKNAME_TYPE >(
              program          ,
              uniformBlockIndex,
              bufSize          ,
              length           ,
              uniformBlockName );
    }
    template<
      typename PROGRAM_TYPE        = GLuint             ,
      typename UNIFORMCOUNT_TYPE   = GLsizei            ,
      typename UNIFORMNAMES_TYPE   = const GLchar*const*,
      typename UNIFORMINDICES_TYPE = GLuint*            >
    inline GetUniformIndices<
      PROGRAM_TYPE       ,
      UNIFORMCOUNT_TYPE  ,
      UNIFORMNAMES_TYPE  ,
      UNIFORMINDICES_TYPE>* newGetUniformIndices(
        PROGRAM_TYPE        const&program       ,
        UNIFORMCOUNT_TYPE   const&uniformCount  ,
        UNIFORMNAMES_TYPE   const&uniformNames  ,
        UNIFORMINDICES_TYPE const&uniformIndices){
        return new GetUniformIndices<
          PROGRAM_TYPE       ,
          UNIFORMCOUNT_TYPE  ,
          UNIFORMNAMES_TYPE  ,
          UNIFORMINDICES_TYPE>(
              program       ,
              uniformCount  ,
              uniformNames  ,
              uniformIndices);
    }
    template<
      typename PROGRAM_TYPE  = GLuint,
      typename LOCATION_TYPE = GLint ,
      typename PARAMS_TYPE   = GLint*>
    inline GetUniformiv<
      PROGRAM_TYPE ,
      LOCATION_TYPE,
      PARAMS_TYPE  >* newGetUniformiv(
        PROGRAM_TYPE  const&program ,
        LOCATION_TYPE const&location,
        PARAMS_TYPE   const&params  ){
        return new GetUniformiv<
          PROGRAM_TYPE ,
          LOCATION_TYPE,
          PARAMS_TYPE  >(
              program ,
              location,
              params  );
    }
    template<
      typename LOCATION_TYPE  = GLint          ,
      typename COUNT_TYPE     = GLsizei        ,
      typename TRANSPOSE_TYPE = GLboolean      ,
      typename VALUE_TYPE     = const GLdouble*>
    inline UniformMatrix4dv<
      LOCATION_TYPE ,
      COUNT_TYPE    ,
      TRANSPOSE_TYPE,
      VALUE_TYPE    >* newUniformMatrix4dv(
        LOCATION_TYPE  const&location ,
        COUNT_TYPE     const&count    ,
        TRANSPOSE_TYPE const&transpose,
        VALUE_TYPE     const&value    ){
        return new UniformMatrix4dv<
          LOCATION_TYPE ,
          COUNT_TYPE    ,
          TRANSPOSE_TYPE,
          VALUE_TYPE    >(
              location ,
              count    ,
              transpose,
              value    );
    }
    template<
      typename LOCATION_TYPE = GLint ,
      typename V0_TYPE       = GLuint>
    inline Uniform1ui<
      LOCATION_TYPE,
      V0_TYPE      >* newUniform1ui(
        LOCATION_TYPE const&location,
        V0_TYPE       const&v0      ){
        return new Uniform1ui<
          LOCATION_TYPE,
          V0_TYPE      >(
              location,
              v0      );
    }
    template<
      typename LOCATION_TYPE  = GLint          ,
      typename COUNT_TYPE     = GLsizei        ,
      typename TRANSPOSE_TYPE = GLboolean      ,
      typename VALUE_TYPE     = const GLdouble*>
    inline UniformMatrix3x4dv<
      LOCATION_TYPE ,
      COUNT_TYPE    ,
      TRANSPOSE_TYPE,
      VALUE_TYPE    >* newUniformMatrix3x4dv(
        LOCATION_TYPE  const&location ,
        COUNT_TYPE     const&count    ,
        TRANSPOSE_TYPE const&transpose,
        VALUE_TYPE     const&value    ){
        return new UniformMatrix3x4dv<
          LOCATION_TYPE ,
          COUNT_TYPE    ,
          TRANSPOSE_TYPE,
          VALUE_TYPE    >(
              location ,
              count    ,
              transpose,
              value    );
    }
    template<
      typename PROGRAM_TYPE  = GLuint,
      typename LOCATION_TYPE = GLint ,
      typename V0_TYPE       = GLint >
    inline ProgramUniform1i<
      PROGRAM_TYPE ,
      LOCATION_TYPE,
      V0_TYPE      >* newProgramUniform1i(
        PROGRAM_TYPE  const&program ,
        LOCATION_TYPE const&location,
        V0_TYPE       const&v0      ){
        return new ProgramUniform1i<
          PROGRAM_TYPE ,
          LOCATION_TYPE,
          V0_TYPE      >(
              program ,
              location,
              v0      );
    }
    template<
      typename PROGRAM_TYPE        = GLuint       ,
      typename UNIFORMCOUNT_TYPE   = GLsizei      ,
      typename UNIFORMINDICES_TYPE = const GLuint*,
      typename PNAME_TYPE          = GLenum       ,
      typename PARAMS_TYPE         = GLint*       >
    inline GetActiveUniformsiv<
      PROGRAM_TYPE       ,
      UNIFORMCOUNT_TYPE  ,
      UNIFORMINDICES_TYPE,
      PNAME_TYPE         ,
      PARAMS_TYPE        >* newGetActiveUniformsiv(
        PROGRAM_TYPE        const&program       ,
        UNIFORMCOUNT_TYPE   const&uniformCount  ,
        UNIFORMINDICES_TYPE const&uniformIndices,
        PNAME_TYPE          const&pname         ,
        PARAMS_TYPE         const&params        ){
        return new GetActiveUniformsiv<
          PROGRAM_TYPE       ,
          UNIFORMCOUNT_TYPE  ,
          UNIFORMINDICES_TYPE,
          PNAME_TYPE         ,
          PARAMS_TYPE        >(
              program       ,
              uniformCount  ,
              uniformIndices,
              pname         ,
              params        );
    }
    template<
      typename PROGRAM_TYPE   = GLuint         ,
      typename LOCATION_TYPE  = GLint          ,
      typename COUNT_TYPE     = GLsizei        ,
      typename TRANSPOSE_TYPE = GLboolean      ,
      typename VALUE_TYPE     = const GLdouble*>
    inline ProgramUniformMatrix2x3dv<
      PROGRAM_TYPE  ,
      LOCATION_TYPE ,
      COUNT_TYPE    ,
      TRANSPOSE_TYPE,
      VALUE_TYPE    >* newProgramUniformMatrix2x3dv(
        PROGRAM_TYPE   const&program  ,
        LOCATION_TYPE  const&location ,
        COUNT_TYPE     const&count    ,
        TRANSPOSE_TYPE const&transpose,
        VALUE_TYPE     const&value    ){
        return new ProgramUniformMatrix2x3dv<
          PROGRAM_TYPE  ,
          LOCATION_TYPE ,
          COUNT_TYPE    ,
          TRANSPOSE_TYPE,
          VALUE_TYPE    >(
              program  ,
              location ,
              count    ,
              transpose,
              value    );
    }
    template<
      typename PROGRAM_TYPE  = GLuint       ,
      typename LOCATION_TYPE = GLint        ,
      typename COUNT_TYPE    = GLsizei      ,
      typename VALUE_TYPE    = const GLuint*>
    inline ProgramUniform3uiv<
      PROGRAM_TYPE ,
      LOCATION_TYPE,
      COUNT_TYPE   ,
      VALUE_TYPE   >* newProgramUniform3uiv(
        PROGRAM_TYPE  const&program ,
        LOCATION_TYPE const&location,
        COUNT_TYPE    const&count   ,
        VALUE_TYPE    const&value   ){
        return new ProgramUniform3uiv<
          PROGRAM_TYPE ,
          LOCATION_TYPE,
          COUNT_TYPE   ,
          VALUE_TYPE   >(
              program ,
              location,
              count   ,
              value   );
    }
    template<
      typename LOCATION_TYPE = GLint       ,
      typename COUNT_TYPE    = GLsizei     ,
      typename VALUE_TYPE    = const GLint*>
    inline Uniform2iv<
      LOCATION_TYPE,
      COUNT_TYPE   ,
      VALUE_TYPE   >* newUniform2iv(
        LOCATION_TYPE const&location,
        COUNT_TYPE    const&count   ,
        VALUE_TYPE    const&value   ){
        return new Uniform2iv<
          LOCATION_TYPE,
          COUNT_TYPE   ,
          VALUE_TYPE   >(
              location,
              count   ,
              value   );
    }
    template<
      typename PROGRAM_TYPE  = GLuint       ,
      typename LOCATION_TYPE = GLint        ,
      typename COUNT_TYPE    = GLsizei      ,
      typename VALUE_TYPE    = const GLuint*>
    inline ProgramUniform2uiv<
      PROGRAM_TYPE ,
      LOCATION_TYPE,
      COUNT_TYPE   ,
      VALUE_TYPE   >* newProgramUniform2uiv(
        PROGRAM_TYPE  const&program ,
        LOCATION_TYPE const&location,
        COUNT_TYPE    const&count   ,
        VALUE_TYPE    const&value   ){
        return new ProgramUniform2uiv<
          PROGRAM_TYPE ,
          LOCATION_TYPE,
          COUNT_TYPE   ,
          VALUE_TYPE   >(
              program ,
              location,
              count   ,
              value   );
    }
    template<
      typename PROGRAM_TYPE  = GLuint,
      typename LOCATION_TYPE = GLint ,
      typename V0_TYPE       = GLint ,
      typename V1_TYPE       = GLint ,
      typename V2_TYPE       = GLint >
    inline ProgramUniform3i<
      PROGRAM_TYPE ,
      LOCATION_TYPE,
      V0_TYPE      ,
      V1_TYPE      ,
      V2_TYPE      >* newProgramUniform3i(
        PROGRAM_TYPE  const&program ,
        LOCATION_TYPE const&location,
        V0_TYPE       const&v0      ,
        V1_TYPE       const&v1      ,
        V2_TYPE       const&v2      ){
        return new ProgramUniform3i<
          PROGRAM_TYPE ,
          LOCATION_TYPE,
          V0_TYPE      ,
          V1_TYPE      ,
          V2_TYPE      >(
              program ,
              location,
              v0      ,
              v1      ,
              v2      );
    }
    template<
      typename PROGRAM_TYPE  = GLuint  ,
      typename LOCATION_TYPE = GLint   ,
      typename V0_TYPE       = GLdouble,
      typename V1_TYPE       = GLdouble,
      typename V2_TYPE       = GLdouble>
    inline ProgramUniform3d<
      PROGRAM_TYPE ,
      LOCATION_TYPE,
      V0_TYPE      ,
      V1_TYPE      ,
      V2_TYPE      >* newProgramUniform3d(
        PROGRAM_TYPE  const&program ,
        LOCATION_TYPE const&location,
        V0_TYPE       const&v0      ,
        V1_TYPE       const&v1      ,
        V2_TYPE       const&v2      ){
        return new ProgramUniform3d<
          PROGRAM_TYPE ,
          LOCATION_TYPE,
          V0_TYPE      ,
          V1_TYPE      ,
          V2_TYPE      >(
              program ,
              location,
              v0      ,
              v1      ,
              v2      );
    }
    template<
      typename PROGRAM_TYPE   = GLuint         ,
      typename LOCATION_TYPE  = GLint          ,
      typename COUNT_TYPE     = GLsizei        ,
      typename TRANSPOSE_TYPE = GLboolean      ,
      typename VALUE_TYPE     = const GLdouble*>
    inline ProgramUniformMatrix3dv<
      PROGRAM_TYPE  ,
      LOCATION_TYPE ,
      COUNT_TYPE    ,
      TRANSPOSE_TYPE,
      VALUE_TYPE    >* newProgramUniformMatrix3dv(
        PROGRAM_TYPE   const&program  ,
        LOCATION_TYPE  const&location ,
        COUNT_TYPE     const&count    ,
        TRANSPOSE_TYPE const&transpose,
        VALUE_TYPE     const&value    ){
        return new ProgramUniformMatrix3dv<
          PROGRAM_TYPE  ,
          LOCATION_TYPE ,
          COUNT_TYPE    ,
          TRANSPOSE_TYPE,
          VALUE_TYPE    >(
              program  ,
              location ,
              count    ,
              transpose,
              value    );
    }
    template<
      typename LOCATION_TYPE = GLint  ,
      typename V0_TYPE       = GLfloat,
      typename V1_TYPE       = GLfloat>
    inline Uniform2f<
      LOCATION_TYPE,
      V0_TYPE      ,
      V1_TYPE      >* newUniform2f(
        LOCATION_TYPE const&location,
        V0_TYPE       const&v0      ,
        V1_TYPE       const&v1      ){
        return new Uniform2f<
          LOCATION_TYPE,
          V0_TYPE      ,
          V1_TYPE      >(
              location,
              v0      ,
              v1      );
    }
    template<
      typename LOCATION_TYPE = GLint       ,
      typename COUNT_TYPE    = GLsizei     ,
      typename VALUE_TYPE    = const GLint*>
    inline Uniform1iv<
      LOCATION_TYPE,
      COUNT_TYPE   ,
      VALUE_TYPE   >* newUniform1iv(
        LOCATION_TYPE const&location,
        COUNT_TYPE    const&count   ,
        VALUE_TYPE    const&value   ){
        return new Uniform1iv<
          LOCATION_TYPE,
          COUNT_TYPE   ,
          VALUE_TYPE   >(
              location,
              count   ,
              value   );
    }
    template<
      typename LOCATION_TYPE  = GLint          ,
      typename COUNT_TYPE     = GLsizei        ,
      typename TRANSPOSE_TYPE = GLboolean      ,
      typename VALUE_TYPE     = const GLdouble*>
    inline UniformMatrix2x4dv<
      LOCATION_TYPE ,
      COUNT_TYPE    ,
      TRANSPOSE_TYPE,
      VALUE_TYPE    >* newUniformMatrix2x4dv(
        LOCATION_TYPE  const&location ,
        COUNT_TYPE     const&count    ,
        TRANSPOSE_TYPE const&transpose,
        VALUE_TYPE     const&value    ){
        return new UniformMatrix2x4dv<
          LOCATION_TYPE ,
          COUNT_TYPE    ,
          TRANSPOSE_TYPE,
          VALUE_TYPE    >(
              location ,
              count    ,
              transpose,
              value    );
    }
    template<
      typename LOCATION_TYPE = GLint,
      typename V0_TYPE       = GLint,
      typename V1_TYPE       = GLint,
      typename V2_TYPE       = GLint,
      typename V3_TYPE       = GLint>
    inline Uniform4i<
      LOCATION_TYPE,
      V0_TYPE      ,
      V1_TYPE      ,
      V2_TYPE      ,
      V3_TYPE      >* newUniform4i(
        LOCATION_TYPE const&location,
        V0_TYPE       const&v0      ,
        V1_TYPE       const&v1      ,
        V2_TYPE       const&v2      ,
        V3_TYPE       const&v3      ){
        return new Uniform4i<
          LOCATION_TYPE,
          V0_TYPE      ,
          V1_TYPE      ,
          V2_TYPE      ,
          V3_TYPE      >(
              location,
              v0      ,
              v1      ,
              v2      ,
              v3      );
    }
    template<
      typename LOCATION_TYPE = GLint,
      typename V0_TYPE       = GLint,
      typename V1_TYPE       = GLint>
    inline Uniform2i<
      LOCATION_TYPE,
      V0_TYPE      ,
      V1_TYPE      >* newUniform2i(
        LOCATION_TYPE const&location,
        V0_TYPE       const&v0      ,
        V1_TYPE       const&v1      ){
        return new Uniform2i<
          LOCATION_TYPE,
          V0_TYPE      ,
          V1_TYPE      >(
              location,
              v0      ,
              v1      );
    }
    template<
      typename PROGRAM_TYPE  = GLuint         ,
      typename LOCATION_TYPE = GLint          ,
      typename COUNT_TYPE    = GLsizei        ,
      typename VALUE_TYPE    = const GLdouble*>
    inline ProgramUniform2dv<
      PROGRAM_TYPE ,
      LOCATION_TYPE,
      COUNT_TYPE   ,
      VALUE_TYPE   >* newProgramUniform2dv(
        PROGRAM_TYPE  const&program ,
        LOCATION_TYPE const&location,
        COUNT_TYPE    const&count   ,
        VALUE_TYPE    const&value   ){
        return new ProgramUniform2dv<
          PROGRAM_TYPE ,
          LOCATION_TYPE,
          COUNT_TYPE   ,
          VALUE_TYPE   >(
              program ,
              location,
              count   ,
              value   );
    }
    template<
      typename PROGRAM_TYPE  = GLuint      ,
      typename LOCATION_TYPE = GLint       ,
      typename COUNT_TYPE    = GLsizei     ,
      typename VALUE_TYPE    = const GLint*>
    inline ProgramUniform3iv<
      PROGRAM_TYPE ,
      LOCATION_TYPE,
      COUNT_TYPE   ,
      VALUE_TYPE   >* newProgramUniform3iv(
        PROGRAM_TYPE  const&program ,
        LOCATION_TYPE const&location,
        COUNT_TYPE    const&count   ,
        VALUE_TYPE    const&value   ){
        return new ProgramUniform3iv<
          PROGRAM_TYPE ,
          LOCATION_TYPE,
          COUNT_TYPE   ,
          VALUE_TYPE   >(
              program ,
              location,
              count   ,
              value   );
    }
    template<
      typename PROGRAM_TYPE  = GLuint ,
      typename LOCATION_TYPE = GLint  ,
      typename BUFSIZE_TYPE  = GLsizei,
      typename PARAMS_TYPE   = GLuint*>
    inline GetnUniformuiv<
      PROGRAM_TYPE ,
      LOCATION_TYPE,
      BUFSIZE_TYPE ,
      PARAMS_TYPE  >* newGetnUniformuiv(
        PROGRAM_TYPE  const&program ,
        LOCATION_TYPE const&location,
        BUFSIZE_TYPE  const&bufSize ,
        PARAMS_TYPE   const&params  ){
        return new GetnUniformuiv<
          PROGRAM_TYPE ,
          LOCATION_TYPE,
          BUFSIZE_TYPE ,
          PARAMS_TYPE  >(
              program ,
              location,
              bufSize ,
              params  );
    }
    template<
      typename PROGRAM_TYPE   = GLuint        ,
      typename LOCATION_TYPE  = GLint         ,
      typename COUNT_TYPE     = GLsizei       ,
      typename TRANSPOSE_TYPE = GLboolean     ,
      typename VALUE_TYPE     = const GLfloat*>
    inline ProgramUniformMatrix4fv<
      PROGRAM_TYPE  ,
      LOCATION_TYPE ,
      COUNT_TYPE    ,
      TRANSPOSE_TYPE,
      VALUE_TYPE    >* newProgramUniformMatrix4fv(
        PROGRAM_TYPE   const&program  ,
        LOCATION_TYPE  const&location ,
        COUNT_TYPE     const&count    ,
        TRANSPOSE_TYPE const&transpose,
        VALUE_TYPE     const&value    ){
        return new ProgramUniformMatrix4fv<
          PROGRAM_TYPE  ,
          LOCATION_TYPE ,
          COUNT_TYPE    ,
          TRANSPOSE_TYPE,
          VALUE_TYPE    >(
              program  ,
              location ,
              count    ,
              transpose,
              value    );
    }
    template<
      typename PROGRAM_TYPE   = GLuint         ,
      typename LOCATION_TYPE  = GLint          ,
      typename COUNT_TYPE     = GLsizei        ,
      typename TRANSPOSE_TYPE = GLboolean      ,
      typename VALUE_TYPE     = const GLdouble*>
    inline ProgramUniformMatrix4dv<
      PROGRAM_TYPE  ,
      LOCATION_TYPE ,
      COUNT_TYPE    ,
      TRANSPOSE_TYPE,
      VALUE_TYPE    >* newProgramUniformMatrix4dv(
        PROGRAM_TYPE   const&program  ,
        LOCATION_TYPE  const&location ,
        COUNT_TYPE     const&count    ,
        TRANSPOSE_TYPE const&transpose,
        VALUE_TYPE     const&value    ){
        return new ProgramUniformMatrix4dv<
          PROGRAM_TYPE  ,
          LOCATION_TYPE ,
          COUNT_TYPE    ,
          TRANSPOSE_TYPE,
          VALUE_TYPE    >(
              program  ,
              location ,
              count    ,
              transpose,
              value    );
    }
    template<
      typename LOCATION_TYPE  = GLint         ,
      typename COUNT_TYPE     = GLsizei       ,
      typename TRANSPOSE_TYPE = GLboolean     ,
      typename VALUE_TYPE     = const GLfloat*>
    inline UniformMatrix4x2fv<
      LOCATION_TYPE ,
      COUNT_TYPE    ,
      TRANSPOSE_TYPE,
      VALUE_TYPE    >* newUniformMatrix4x2fv(
        LOCATION_TYPE  const&location ,
        COUNT_TYPE     const&count    ,
        TRANSPOSE_TYPE const&transpose,
        VALUE_TYPE     const&value    ){
        return new UniformMatrix4x2fv<
          LOCATION_TYPE ,
          COUNT_TYPE    ,
          TRANSPOSE_TYPE,
          VALUE_TYPE    >(
              location ,
              count    ,
              transpose,
              value    );
    }
    template<
      typename LOCATION_TYPE  = GLint         ,
      typename COUNT_TYPE     = GLsizei       ,
      typename TRANSPOSE_TYPE = GLboolean     ,
      typename VALUE_TYPE     = const GLfloat*>
    inline UniformMatrix2x3fv<
      LOCATION_TYPE ,
      COUNT_TYPE    ,
      TRANSPOSE_TYPE,
      VALUE_TYPE    >* newUniformMatrix2x3fv(
        LOCATION_TYPE  const&location ,
        COUNT_TYPE     const&count    ,
        TRANSPOSE_TYPE const&transpose,
        VALUE_TYPE     const&value    ){
        return new UniformMatrix2x3fv<
          LOCATION_TYPE ,
          COUNT_TYPE    ,
          TRANSPOSE_TYPE,
          VALUE_TYPE    >(
              location ,
              count    ,
              transpose,
              value    );
    }
    template<
      typename LOCATION_TYPE = GLint          ,
      typename COUNT_TYPE    = GLsizei        ,
      typename VALUE_TYPE    = const GLdouble*>
    inline Uniform4dv<
      LOCATION_TYPE,
      COUNT_TYPE   ,
      VALUE_TYPE   >* newUniform4dv(
        LOCATION_TYPE const&location,
        COUNT_TYPE    const&count   ,
        VALUE_TYPE    const&value   ){
        return new Uniform4dv<
          LOCATION_TYPE,
          COUNT_TYPE   ,
          VALUE_TYPE   >(
              location,
              count   ,
              value   );
    }
    template<
      typename PROGRAM_TYPE   = GLuint        ,
      typename LOCATION_TYPE  = GLint         ,
      typename COUNT_TYPE     = GLsizei       ,
      typename TRANSPOSE_TYPE = GLboolean     ,
      typename VALUE_TYPE     = const GLfloat*>
    inline ProgramUniformMatrix3x4fv<
      PROGRAM_TYPE  ,
      LOCATION_TYPE ,
      COUNT_TYPE    ,
      TRANSPOSE_TYPE,
      VALUE_TYPE    >* newProgramUniformMatrix3x4fv(
        PROGRAM_TYPE   const&program  ,
        LOCATION_TYPE  const&location ,
        COUNT_TYPE     const&count    ,
        TRANSPOSE_TYPE const&transpose,
        VALUE_TYPE     const&value    ){
        return new ProgramUniformMatrix3x4fv<
          PROGRAM_TYPE  ,
          LOCATION_TYPE ,
          COUNT_TYPE    ,
          TRANSPOSE_TYPE,
          VALUE_TYPE    >(
              program  ,
              location ,
              count    ,
              transpose,
              value    );
    }
    template<
      typename PROGRAM_TYPE  = GLuint       ,
      typename LOCATION_TYPE = GLint        ,
      typename COUNT_TYPE    = GLsizei      ,
      typename VALUE_TYPE    = const GLuint*>
    inline ProgramUniform1uiv<
      PROGRAM_TYPE ,
      LOCATION_TYPE,
      COUNT_TYPE   ,
      VALUE_TYPE   >* newProgramUniform1uiv(
        PROGRAM_TYPE  const&program ,
        LOCATION_TYPE const&location,
        COUNT_TYPE    const&count   ,
        VALUE_TYPE    const&value   ){
        return new ProgramUniform1uiv<
          PROGRAM_TYPE ,
          LOCATION_TYPE,
          COUNT_TYPE   ,
          VALUE_TYPE   >(
              program ,
              location,
              count   ,
              value   );
    }
    template<
      typename PROGRAM_TYPE  = GLuint ,
      typename LOCATION_TYPE = GLint  ,
      typename PARAMS_TYPE   = GLuint*>
    inline GetUniformuiv<
      PROGRAM_TYPE ,
      LOCATION_TYPE,
      PARAMS_TYPE  >* newGetUniformuiv(
        PROGRAM_TYPE  const&program ,
        LOCATION_TYPE const&location,
        PARAMS_TYPE   const&params  ){
        return new GetUniformuiv<
          PROGRAM_TYPE ,
          LOCATION_TYPE,
          PARAMS_TYPE  >(
              program ,
              location,
              params  );
    }
    template<
      typename LOCATION_TYPE  = GLint         ,
      typename COUNT_TYPE     = GLsizei       ,
      typename TRANSPOSE_TYPE = GLboolean     ,
      typename VALUE_TYPE     = const GLfloat*>
    inline UniformMatrix4fv<
      LOCATION_TYPE ,
      COUNT_TYPE    ,
      TRANSPOSE_TYPE,
      VALUE_TYPE    >* newUniformMatrix4fv(
        LOCATION_TYPE  const&location ,
        COUNT_TYPE     const&count    ,
        TRANSPOSE_TYPE const&transpose,
        VALUE_TYPE     const&value    ){
        return new UniformMatrix4fv<
          LOCATION_TYPE ,
          COUNT_TYPE    ,
          TRANSPOSE_TYPE,
          VALUE_TYPE    >(
              location ,
              count    ,
              transpose,
              value    );
    }
    template<
      typename RET_TYPE              = GLuint       ,
      typename PROGRAM_TYPE          = GLuint       ,
      typename UNIFORMBLOCKNAME_TYPE = const GLchar*>
    inline GetUniformBlockIndex<
      RET_TYPE             ,
      PROGRAM_TYPE         ,
      UNIFORMBLOCKNAME_TYPE>* newGetUniformBlockIndex(
        RET_TYPE              const&ret             ,
        PROGRAM_TYPE          const&program         ,
        UNIFORMBLOCKNAME_TYPE const&uniformBlockName){
        return new GetUniformBlockIndex<
          RET_TYPE             ,
          PROGRAM_TYPE         ,
          UNIFORMBLOCKNAME_TYPE>(
              ret             ,
              program         ,
              uniformBlockName);
    }
    template<
      typename LOCATION_TYPE  = GLint         ,
      typename COUNT_TYPE     = GLsizei       ,
      typename TRANSPOSE_TYPE = GLboolean     ,
      typename VALUE_TYPE     = const GLfloat*>
    inline UniformMatrix2x4fv<
      LOCATION_TYPE ,
      COUNT_TYPE    ,
      TRANSPOSE_TYPE,
      VALUE_TYPE    >* newUniformMatrix2x4fv(
        LOCATION_TYPE  const&location ,
        COUNT_TYPE     const&count    ,
        TRANSPOSE_TYPE const&transpose,
        VALUE_TYPE     const&value    ){
        return new UniformMatrix2x4fv<
          LOCATION_TYPE ,
          COUNT_TYPE    ,
          TRANSPOSE_TYPE,
          VALUE_TYPE    >(
              location ,
              count    ,
              transpose,
              value    );
    }
    template<
      typename PROGRAM_TYPE   = GLuint        ,
      typename LOCATION_TYPE  = GLint         ,
      typename COUNT_TYPE     = GLsizei       ,
      typename TRANSPOSE_TYPE = GLboolean     ,
      typename VALUE_TYPE     = const GLfloat*>
    inline ProgramUniformMatrix2fv<
      PROGRAM_TYPE  ,
      LOCATION_TYPE ,
      COUNT_TYPE    ,
      TRANSPOSE_TYPE,
      VALUE_TYPE    >* newProgramUniformMatrix2fv(
        PROGRAM_TYPE   const&program  ,
        LOCATION_TYPE  const&location ,
        COUNT_TYPE     const&count    ,
        TRANSPOSE_TYPE const&transpose,
        VALUE_TYPE     const&value    ){
        return new ProgramUniformMatrix2fv<
          PROGRAM_TYPE  ,
          LOCATION_TYPE ,
          COUNT_TYPE    ,
          TRANSPOSE_TYPE,
          VALUE_TYPE    >(
              program  ,
              location ,
              count    ,
              transpose,
              value    );
    }
    template<
      typename PROGRAM_TYPE  = GLuint       ,
      typename LOCATION_TYPE = GLint        ,
      typename COUNT_TYPE    = GLsizei      ,
      typename VALUE_TYPE    = const GLuint*>
    inline ProgramUniform4uiv<
      PROGRAM_TYPE ,
      LOCATION_TYPE,
      COUNT_TYPE   ,
      VALUE_TYPE   >* newProgramUniform4uiv(
        PROGRAM_TYPE  const&program ,
        LOCATION_TYPE const&location,
        COUNT_TYPE    const&count   ,
        VALUE_TYPE    const&value   ){
        return new ProgramUniform4uiv<
          PROGRAM_TYPE ,
          LOCATION_TYPE,
          COUNT_TYPE   ,
          VALUE_TYPE   >(
              program ,
              location,
              count   ,
              value   );
    }
    template<
      typename PROGRAM_TYPE  = GLuint  ,
      typename LOCATION_TYPE = GLint   ,
      typename PARAMS_TYPE   = GLfloat*>
    inline GetUniformfv<
      PROGRAM_TYPE ,
      LOCATION_TYPE,
      PARAMS_TYPE  >* newGetUniformfv(
        PROGRAM_TYPE  const&program ,
        LOCATION_TYPE const&location,
        PARAMS_TYPE   const&params  ){
        return new GetUniformfv<
          PROGRAM_TYPE ,
          LOCATION_TYPE,
          PARAMS_TYPE  >(
              program ,
              location,
              params  );
    }
    template<
      typename LOCATION_TYPE = GLint   ,
      typename X_TYPE        = GLdouble,
      typename Y_TYPE        = GLdouble,
      typename Z_TYPE        = GLdouble>
    inline Uniform3d<
      LOCATION_TYPE,
      X_TYPE       ,
      Y_TYPE       ,
      Z_TYPE       >* newUniform3d(
        LOCATION_TYPE const&location,
        X_TYPE        const&x       ,
        Y_TYPE        const&y       ,
        Z_TYPE        const&z       ){
        return new Uniform3d<
          LOCATION_TYPE,
          X_TYPE       ,
          Y_TYPE       ,
          Z_TYPE       >(
              location,
              x       ,
              y       ,
              z       );
    }
    template<
      typename PROGRAM_TYPE  = GLuint ,
      typename LOCATION_TYPE = GLint  ,
      typename V0_TYPE       = GLfloat,
      typename V1_TYPE       = GLfloat,
      typename V2_TYPE       = GLfloat,
      typename V3_TYPE       = GLfloat>
    inline ProgramUniform4f<
      PROGRAM_TYPE ,
      LOCATION_TYPE,
      V0_TYPE      ,
      V1_TYPE      ,
      V2_TYPE      ,
      V3_TYPE      >* newProgramUniform4f(
        PROGRAM_TYPE  const&program ,
        LOCATION_TYPE const&location,
        V0_TYPE       const&v0      ,
        V1_TYPE       const&v1      ,
        V2_TYPE       const&v2      ,
        V3_TYPE       const&v3      ){
        return new ProgramUniform4f<
          PROGRAM_TYPE ,
          LOCATION_TYPE,
          V0_TYPE      ,
          V1_TYPE      ,
          V2_TYPE      ,
          V3_TYPE      >(
              program ,
              location,
              v0      ,
              v1      ,
              v2      ,
              v3      );
    }
    template<
      typename PROGRAM_TYPE  = GLuint         ,
      typename LOCATION_TYPE = GLint          ,
      typename COUNT_TYPE    = GLsizei        ,
      typename VALUE_TYPE    = const GLdouble*>
    inline ProgramUniform3dv<
      PROGRAM_TYPE ,
      LOCATION_TYPE,
      COUNT_TYPE   ,
      VALUE_TYPE   >* newProgramUniform3dv(
        PROGRAM_TYPE  const&program ,
        LOCATION_TYPE const&location,
        COUNT_TYPE    const&count   ,
        VALUE_TYPE    const&value   ){
        return new ProgramUniform3dv<
          PROGRAM_TYPE ,
          LOCATION_TYPE,
          COUNT_TYPE   ,
          VALUE_TYPE   >(
              program ,
              location,
              count   ,
              value   );
    }
    template<
      typename LOCATION_TYPE  = GLint          ,
      typename COUNT_TYPE     = GLsizei        ,
      typename TRANSPOSE_TYPE = GLboolean      ,
      typename VALUE_TYPE     = const GLdouble*>
    inline UniformMatrix4x3dv<
      LOCATION_TYPE ,
      COUNT_TYPE    ,
      TRANSPOSE_TYPE,
      VALUE_TYPE    >* newUniformMatrix4x3dv(
        LOCATION_TYPE  const&location ,
        COUNT_TYPE     const&count    ,
        TRANSPOSE_TYPE const&transpose,
        VALUE_TYPE     const&value    ){
        return new UniformMatrix4x3dv<
          LOCATION_TYPE ,
          COUNT_TYPE    ,
          TRANSPOSE_TYPE,
          VALUE_TYPE    >(
              location ,
              count    ,
              transpose,
              value    );
    }
    template<
      typename PROGRAM_TYPE   = GLuint        ,
      typename LOCATION_TYPE  = GLint         ,
      typename COUNT_TYPE     = GLsizei       ,
      typename TRANSPOSE_TYPE = GLboolean     ,
      typename VALUE_TYPE     = const GLfloat*>
    inline ProgramUniformMatrix3x2fv<
      PROGRAM_TYPE  ,
      LOCATION_TYPE ,
      COUNT_TYPE    ,
      TRANSPOSE_TYPE,
      VALUE_TYPE    >* newProgramUniformMatrix3x2fv(
        PROGRAM_TYPE   const&program  ,
        LOCATION_TYPE  const&location ,
        COUNT_TYPE     const&count    ,
        TRANSPOSE_TYPE const&transpose,
        VALUE_TYPE     const&value    ){
        return new ProgramUniformMatrix3x2fv<
          PROGRAM_TYPE  ,
          LOCATION_TYPE ,
          COUNT_TYPE    ,
          TRANSPOSE_TYPE,
          VALUE_TYPE    >(
              program  ,
              location ,
              count    ,
              transpose,
              value    );
    }
    template<
      typename PROGRAM_TYPE   = GLuint         ,
      typename LOCATION_TYPE  = GLint          ,
      typename COUNT_TYPE     = GLsizei        ,
      typename TRANSPOSE_TYPE = GLboolean      ,
      typename VALUE_TYPE     = const GLdouble*>
    inline ProgramUniformMatrix3x4dv<
      PROGRAM_TYPE  ,
      LOCATION_TYPE ,
      COUNT_TYPE    ,
      TRANSPOSE_TYPE,
      VALUE_TYPE    >* newProgramUniformMatrix3x4dv(
        PROGRAM_TYPE   const&program  ,
        LOCATION_TYPE  const&location ,
        COUNT_TYPE     const&count    ,
        TRANSPOSE_TYPE const&transpose,
        VALUE_TYPE     const&value    ){
        return new ProgramUniformMatrix3x4dv<
          PROGRAM_TYPE  ,
          LOCATION_TYPE ,
          COUNT_TYPE    ,
          TRANSPOSE_TYPE,
          VALUE_TYPE    >(
              program  ,
              location ,
              count    ,
              transpose,
              value    );
    }
    template<
      typename PROGRAM_TYPE  = GLuint,
      typename LOCATION_TYPE = GLint ,
      typename V0_TYPE       = GLuint,
      typename V1_TYPE       = GLuint,
      typename V2_TYPE       = GLuint>
    inline ProgramUniform3ui<
      PROGRAM_TYPE ,
      LOCATION_TYPE,
      V0_TYPE      ,
      V1_TYPE      ,
      V2_TYPE      >* newProgramUniform3ui(
        PROGRAM_TYPE  const&program ,
        LOCATION_TYPE const&location,
        V0_TYPE       const&v0      ,
        V1_TYPE       const&v1      ,
        V2_TYPE       const&v2      ){
        return new ProgramUniform3ui<
          PROGRAM_TYPE ,
          LOCATION_TYPE,
          V0_TYPE      ,
          V1_TYPE      ,
          V2_TYPE      >(
              program ,
              location,
              v0      ,
              v1      ,
              v2      );
    }
    template<
      typename LOCATION_TYPE = GLint,
      typename V0_TYPE       = GLint,
      typename V1_TYPE       = GLint,
      typename V2_TYPE       = GLint>
    inline Uniform3i<
      LOCATION_TYPE,
      V0_TYPE      ,
      V1_TYPE      ,
      V2_TYPE      >* newUniform3i(
        LOCATION_TYPE const&location,
        V0_TYPE       const&v0      ,
        V1_TYPE       const&v1      ,
        V2_TYPE       const&v2      ){
        return new Uniform3i<
          LOCATION_TYPE,
          V0_TYPE      ,
          V1_TYPE      ,
          V2_TYPE      >(
              location,
              v0      ,
              v1      ,
              v2      );
    }
    template<
      typename PROGRAM_TYPE  = GLuint ,
      typename LOCATION_TYPE = GLint  ,
      typename BUFSIZE_TYPE  = GLsizei,
      typename PARAMS_TYPE   = GLint* >
    inline GetnUniformiv<
      PROGRAM_TYPE ,
      LOCATION_TYPE,
      BUFSIZE_TYPE ,
      PARAMS_TYPE  >* newGetnUniformiv(
        PROGRAM_TYPE  const&program ,
        LOCATION_TYPE const&location,
        BUFSIZE_TYPE  const&bufSize ,
        PARAMS_TYPE   const&params  ){
        return new GetnUniformiv<
          PROGRAM_TYPE ,
          LOCATION_TYPE,
          BUFSIZE_TYPE ,
          PARAMS_TYPE  >(
              program ,
              location,
              bufSize ,
              params  );
    }
    template<
      typename PROGRAM_TYPE  = GLuint,
      typename LOCATION_TYPE = GLint ,
      typename V0_TYPE       = GLint ,
      typename V1_TYPE       = GLint ,
      typename V2_TYPE       = GLint ,
      typename V3_TYPE       = GLint >
    inline ProgramUniform4i<
      PROGRAM_TYPE ,
      LOCATION_TYPE,
      V0_TYPE      ,
      V1_TYPE      ,
      V2_TYPE      ,
      V3_TYPE      >* newProgramUniform4i(
        PROGRAM_TYPE  const&program ,
        LOCATION_TYPE const&location,
        V0_TYPE       const&v0      ,
        V1_TYPE       const&v1      ,
        V2_TYPE       const&v2      ,
        V3_TYPE       const&v3      ){
        return new ProgramUniform4i<
          PROGRAM_TYPE ,
          LOCATION_TYPE,
          V0_TYPE      ,
          V1_TYPE      ,
          V2_TYPE      ,
          V3_TYPE      >(
              program ,
              location,
              v0      ,
              v1      ,
              v2      ,
              v3      );
    }
    template<
      typename PROGRAM_TYPE  = GLuint        ,
      typename LOCATION_TYPE = GLint         ,
      typename COUNT_TYPE    = GLsizei       ,
      typename VALUE_TYPE    = const GLfloat*>
    inline ProgramUniform4fv<
      PROGRAM_TYPE ,
      LOCATION_TYPE,
      COUNT_TYPE   ,
      VALUE_TYPE   >* newProgramUniform4fv(
        PROGRAM_TYPE  const&program ,
        LOCATION_TYPE const&location,
        COUNT_TYPE    const&count   ,
        VALUE_TYPE    const&value   ){
        return new ProgramUniform4fv<
          PROGRAM_TYPE ,
          LOCATION_TYPE,
          COUNT_TYPE   ,
          VALUE_TYPE   >(
              program ,
              location,
              count   ,
              value   );
    }
    template<
      typename PROGRAM_TYPE  = GLuint ,
      typename LOCATION_TYPE = GLint  ,
      typename V0_TYPE       = GLfloat,
      typename V1_TYPE       = GLfloat,
      typename V2_TYPE       = GLfloat>
    inline ProgramUniform3f<
      PROGRAM_TYPE ,
      LOCATION_TYPE,
      V0_TYPE      ,
      V1_TYPE      ,
      V2_TYPE      >* newProgramUniform3f(
        PROGRAM_TYPE  const&program ,
        LOCATION_TYPE const&location,
        V0_TYPE       const&v0      ,
        V1_TYPE       const&v1      ,
        V2_TYPE       const&v2      ){
        return new ProgramUniform3f<
          PROGRAM_TYPE ,
          LOCATION_TYPE,
          V0_TYPE      ,
          V1_TYPE      ,
          V2_TYPE      >(
              program ,
              location,
              v0      ,
              v1      ,
              v2      );
    }
    template<
      typename LOCATION_TYPE = GLint         ,
      typename COUNT_TYPE    = GLsizei       ,
      typename VALUE_TYPE    = const GLfloat*>
    inline Uniform2fv<
      LOCATION_TYPE,
      COUNT_TYPE   ,
      VALUE_TYPE   >* newUniform2fv(
        LOCATION_TYPE const&location,
        COUNT_TYPE    const&count   ,
        VALUE_TYPE    const&value   ){
        return new Uniform2fv<
          LOCATION_TYPE,
          COUNT_TYPE   ,
          VALUE_TYPE   >(
              location,
              count   ,
              value   );
    }
    template<
      typename LOCATION_TYPE  = GLint          ,
      typename COUNT_TYPE     = GLsizei        ,
      typename TRANSPOSE_TYPE = GLboolean      ,
      typename VALUE_TYPE     = const GLdouble*>
    inline UniformMatrix3dv<
      LOCATION_TYPE ,
      COUNT_TYPE    ,
      TRANSPOSE_TYPE,
      VALUE_TYPE    >* newUniformMatrix3dv(
        LOCATION_TYPE  const&location ,
        COUNT_TYPE     const&count    ,
        TRANSPOSE_TYPE const&transpose,
        VALUE_TYPE     const&value    ){
        return new UniformMatrix3dv<
          LOCATION_TYPE ,
          COUNT_TYPE    ,
          TRANSPOSE_TYPE,
          VALUE_TYPE    >(
              location ,
              count    ,
              transpose,
              value    );
    }
    template<
      typename PROGRAM_TYPE   = GLuint         ,
      typename LOCATION_TYPE  = GLint          ,
      typename COUNT_TYPE     = GLsizei        ,
      typename TRANSPOSE_TYPE = GLboolean      ,
      typename VALUE_TYPE     = const GLdouble*>
    inline ProgramUniformMatrix2dv<
      PROGRAM_TYPE  ,
      LOCATION_TYPE ,
      COUNT_TYPE    ,
      TRANSPOSE_TYPE,
      VALUE_TYPE    >* newProgramUniformMatrix2dv(
        PROGRAM_TYPE   const&program  ,
        LOCATION_TYPE  const&location ,
        COUNT_TYPE     const&count    ,
        TRANSPOSE_TYPE const&transpose,
        VALUE_TYPE     const&value    ){
        return new ProgramUniformMatrix2dv<
          PROGRAM_TYPE  ,
          LOCATION_TYPE ,
          COUNT_TYPE    ,
          TRANSPOSE_TYPE,
          VALUE_TYPE    >(
              program  ,
              location ,
              count    ,
              transpose,
              value    );
    }
    template<
      typename PROGRAM_TYPE  = GLuint,
      typename LOCATION_TYPE = GLint ,
      typename V0_TYPE       = GLint ,
      typename V1_TYPE       = GLint >
    inline ProgramUniform2i<
      PROGRAM_TYPE ,
      LOCATION_TYPE,
      V0_TYPE      ,
      V1_TYPE      >* newProgramUniform2i(
        PROGRAM_TYPE  const&program ,
        LOCATION_TYPE const&location,
        V0_TYPE       const&v0      ,
        V1_TYPE       const&v1      ){
        return new ProgramUniform2i<
          PROGRAM_TYPE ,
          LOCATION_TYPE,
          V0_TYPE      ,
          V1_TYPE      >(
              program ,
              location,
              v0      ,
              v1      );
    }
    template<
      typename PROGRAM_TYPE  = GLuint        ,
      typename LOCATION_TYPE = GLint         ,
      typename COUNT_TYPE    = GLsizei       ,
      typename VALUE_TYPE    = const GLfloat*>
    inline ProgramUniform2fv<
      PROGRAM_TYPE ,
      LOCATION_TYPE,
      COUNT_TYPE   ,
      VALUE_TYPE   >* newProgramUniform2fv(
        PROGRAM_TYPE  const&program ,
        LOCATION_TYPE const&location,
        COUNT_TYPE    const&count   ,
        VALUE_TYPE    const&value   ){
        return new ProgramUniform2fv<
          PROGRAM_TYPE ,
          LOCATION_TYPE,
          COUNT_TYPE   ,
          VALUE_TYPE   >(
              program ,
              location,
              count   ,
              value   );
    }
    template<
      typename LOCATION_TYPE = GLint         ,
      typename COUNT_TYPE    = GLsizei       ,
      typename VALUE_TYPE    = const GLfloat*>
    inline Uniform4fv<
      LOCATION_TYPE,
      COUNT_TYPE   ,
      VALUE_TYPE   >* newUniform4fv(
        LOCATION_TYPE const&location,
        COUNT_TYPE    const&count   ,
        VALUE_TYPE    const&value   ){
        return new Uniform4fv<
          LOCATION_TYPE,
          COUNT_TYPE   ,
          VALUE_TYPE   >(
              location,
              count   ,
              value   );
    }
    template<
      typename LOCATION_TYPE  = GLint         ,
      typename COUNT_TYPE     = GLsizei       ,
      typename TRANSPOSE_TYPE = GLboolean     ,
      typename VALUE_TYPE     = const GLfloat*>
    inline UniformMatrix2fv<
      LOCATION_TYPE ,
      COUNT_TYPE    ,
      TRANSPOSE_TYPE,
      VALUE_TYPE    >* newUniformMatrix2fv(
        LOCATION_TYPE  const&location ,
        COUNT_TYPE     const&count    ,
        TRANSPOSE_TYPE const&transpose,
        VALUE_TYPE     const&value    ){
        return new UniformMatrix2fv<
          LOCATION_TYPE ,
          COUNT_TYPE    ,
          TRANSPOSE_TYPE,
          VALUE_TYPE    >(
              location ,
              count    ,
              transpose,
              value    );
    }
    template<
      typename RET_TYPE        = GLint        ,
      typename PROGRAM_TYPE    = GLuint       ,
      typename SHADERTYPE_TYPE = GLenum       ,
      typename NAME_TYPE       = const GLchar*>
    inline GetSubroutineUniformLocation<
      RET_TYPE       ,
      PROGRAM_TYPE   ,
      SHADERTYPE_TYPE,
      NAME_TYPE      >* newGetSubroutineUniformLocation(
        RET_TYPE        const&ret       ,
        PROGRAM_TYPE    const&program   ,
        SHADERTYPE_TYPE const&shadertype,
        NAME_TYPE       const&name      ){
        return new GetSubroutineUniformLocation<
          RET_TYPE       ,
          PROGRAM_TYPE   ,
          SHADERTYPE_TYPE,
          NAME_TYPE      >(
              ret       ,
              program   ,
              shadertype,
              name      );
    }
    template<
      typename SHADERTYPE_TYPE = GLenum       ,
      typename COUNT_TYPE      = GLsizei      ,
      typename INDICES_TYPE    = const GLuint*>
    inline UniformSubroutinesuiv<
      SHADERTYPE_TYPE,
      COUNT_TYPE     ,
      INDICES_TYPE   >* newUniformSubroutinesuiv(
        SHADERTYPE_TYPE const&shadertype,
        COUNT_TYPE      const&count     ,
        INDICES_TYPE    const&indices   ){
        return new UniformSubroutinesuiv<
          SHADERTYPE_TYPE,
          COUNT_TYPE     ,
          INDICES_TYPE   >(
              shadertype,
              count     ,
              indices   );
    }
    template<
      typename LOCATION_TYPE  = GLint          ,
      typename COUNT_TYPE     = GLsizei        ,
      typename TRANSPOSE_TYPE = GLboolean      ,
      typename VALUE_TYPE     = const GLdouble*>
    inline UniformMatrix3x2dv<
      LOCATION_TYPE ,
      COUNT_TYPE    ,
      TRANSPOSE_TYPE,
      VALUE_TYPE    >* newUniformMatrix3x2dv(
        LOCATION_TYPE  const&location ,
        COUNT_TYPE     const&count    ,
        TRANSPOSE_TYPE const&transpose,
        VALUE_TYPE     const&value    ){
        return new UniformMatrix3x2dv<
          LOCATION_TYPE ,
          COUNT_TYPE    ,
          TRANSPOSE_TYPE,
          VALUE_TYPE    >(
              location ,
              count    ,
              transpose,
              value    );
    }
    template<
      typename LOCATION_TYPE = GLint,
      typename V0_TYPE       = GLint>
    inline Uniform1i<
      LOCATION_TYPE,
      V0_TYPE      >* newUniform1i(
        LOCATION_TYPE const&location,
        V0_TYPE       const&v0      ){
        return new Uniform1i<
          LOCATION_TYPE,
          V0_TYPE      >(
              location,
              v0      );
    }
    template<
      typename LOCATION_TYPE = GLint ,
      typename V0_TYPE       = GLuint,
      typename V1_TYPE       = GLuint,
      typename V2_TYPE       = GLuint,
      typename V3_TYPE       = GLuint>
    inline Uniform4ui<
      LOCATION_TYPE,
      V0_TYPE      ,
      V1_TYPE      ,
      V2_TYPE      ,
      V3_TYPE      >* newUniform4ui(
        LOCATION_TYPE const&location,
        V0_TYPE       const&v0      ,
        V1_TYPE       const&v1      ,
        V2_TYPE       const&v2      ,
        V3_TYPE       const&v3      ){
        return new Uniform4ui<
          LOCATION_TYPE,
          V0_TYPE      ,
          V1_TYPE      ,
          V2_TYPE      ,
          V3_TYPE      >(
              location,
              v0      ,
              v1      ,
              v2      ,
              v3      );
    }
    template<
      typename LOCATION_TYPE  = GLint         ,
      typename COUNT_TYPE     = GLsizei       ,
      typename TRANSPOSE_TYPE = GLboolean     ,
      typename VALUE_TYPE     = const GLfloat*>
    inline UniformMatrix3x4fv<
      LOCATION_TYPE ,
      COUNT_TYPE    ,
      TRANSPOSE_TYPE,
      VALUE_TYPE    >* newUniformMatrix3x4fv(
        LOCATION_TYPE  const&location ,
        COUNT_TYPE     const&count    ,
        TRANSPOSE_TYPE const&transpose,
        VALUE_TYPE     const&value    ){
        return new UniformMatrix3x4fv<
          LOCATION_TYPE ,
          COUNT_TYPE    ,
          TRANSPOSE_TYPE,
          VALUE_TYPE    >(
              location ,
              count    ,
              transpose,
              value    );
    }
    template<
      typename LOCATION_TYPE  = GLint         ,
      typename COUNT_TYPE     = GLsizei       ,
      typename TRANSPOSE_TYPE = GLboolean     ,
      typename VALUE_TYPE     = const GLfloat*>
    inline UniformMatrix4x3fv<
      LOCATION_TYPE ,
      COUNT_TYPE    ,
      TRANSPOSE_TYPE,
      VALUE_TYPE    >* newUniformMatrix4x3fv(
        LOCATION_TYPE  const&location ,
        COUNT_TYPE     const&count    ,
        TRANSPOSE_TYPE const&transpose,
        VALUE_TYPE     const&value    ){
        return new UniformMatrix4x3fv<
          LOCATION_TYPE ,
          COUNT_TYPE    ,
          TRANSPOSE_TYPE,
          VALUE_TYPE    >(
              location ,
              count    ,
              transpose,
              value    );
    }
    template<
      typename PROGRAM_TYPE = GLuint  ,
      typename INDEX_TYPE   = GLuint  ,
      typename BUFSIZE_TYPE = GLsizei ,
      typename LENGTH_TYPE  = GLsizei*,
      typename SIZE_TYPE    = GLint*  ,
      typename TYPE_TYPE    = GLenum* ,
      typename NAME_TYPE    = GLchar* >
    inline GetActiveUniform<
      PROGRAM_TYPE,
      INDEX_TYPE  ,
      BUFSIZE_TYPE,
      LENGTH_TYPE ,
      SIZE_TYPE   ,
      TYPE_TYPE   ,
      NAME_TYPE   >* newGetActiveUniform(
        PROGRAM_TYPE const&program,
        INDEX_TYPE   const&index  ,
        BUFSIZE_TYPE const&bufSize,
        LENGTH_TYPE  const&length ,
        SIZE_TYPE    const&size   ,
        TYPE_TYPE    const&type   ,
        NAME_TYPE    const&name   ){
        return new GetActiveUniform<
          PROGRAM_TYPE,
          INDEX_TYPE  ,
          BUFSIZE_TYPE,
          LENGTH_TYPE ,
          SIZE_TYPE   ,
          TYPE_TYPE   ,
          NAME_TYPE   >(
              program,
              index  ,
              bufSize,
              length ,
              size   ,
              type   ,
              name   );
    }
    template<
      typename LOCATION_TYPE = GLint          ,
      typename COUNT_TYPE    = GLsizei        ,
      typename VALUE_TYPE    = const GLdouble*>
    inline Uniform2dv<
      LOCATION_TYPE,
      COUNT_TYPE   ,
      VALUE_TYPE   >* newUniform2dv(
        LOCATION_TYPE const&location,
        COUNT_TYPE    const&count   ,
        VALUE_TYPE    const&value   ){
        return new Uniform2dv<
          LOCATION_TYPE,
          COUNT_TYPE   ,
          VALUE_TYPE   >(
              location,
              count   ,
              value   );
    }
    template<
      typename PROGRAM_TYPE  = GLuint      ,
      typename LOCATION_TYPE = GLint       ,
      typename COUNT_TYPE    = GLsizei     ,
      typename VALUE_TYPE    = const GLint*>
    inline ProgramUniform2iv<
      PROGRAM_TYPE ,
      LOCATION_TYPE,
      COUNT_TYPE   ,
      VALUE_TYPE   >* newProgramUniform2iv(
        PROGRAM_TYPE  const&program ,
        LOCATION_TYPE const&location,
        COUNT_TYPE    const&count   ,
        VALUE_TYPE    const&value   ){
        return new ProgramUniform2iv<
          PROGRAM_TYPE ,
          LOCATION_TYPE,
          COUNT_TYPE   ,
          VALUE_TYPE   >(
              program ,
              location,
              count   ,
              value   );
    }
    template<
      typename LOCATION_TYPE = GLint       ,
      typename COUNT_TYPE    = GLsizei     ,
      typename VALUE_TYPE    = const GLint*>
    inline Uniform4iv<
      LOCATION_TYPE,
      COUNT_TYPE   ,
      VALUE_TYPE   >* newUniform4iv(
        LOCATION_TYPE const&location,
        COUNT_TYPE    const&count   ,
        VALUE_TYPE    const&value   ){
        return new Uniform4iv<
          LOCATION_TYPE,
          COUNT_TYPE   ,
          VALUE_TYPE   >(
              location,
              count   ,
              value   );
    }
    template<
      typename PROGRAM_TYPE  = GLuint  ,
      typename LOCATION_TYPE = GLint   ,
      typename V0_TYPE       = GLdouble,
      typename V1_TYPE       = GLdouble>
    inline ProgramUniform2d<
      PROGRAM_TYPE ,
      LOCATION_TYPE,
      V0_TYPE      ,
      V1_TYPE      >* newProgramUniform2d(
        PROGRAM_TYPE  const&program ,
        LOCATION_TYPE const&location,
        V0_TYPE       const&v0      ,
        V1_TYPE       const&v1      ){
        return new ProgramUniform2d<
          PROGRAM_TYPE ,
          LOCATION_TYPE,
          V0_TYPE      ,
          V1_TYPE      >(
              program ,
              location,
              v0      ,
              v1      );
    }
    template<
      typename LOCATION_TYPE = GLint         ,
      typename COUNT_TYPE    = GLsizei       ,
      typename VALUE_TYPE    = const GLfloat*>
    inline Uniform3fv<
      LOCATION_TYPE,
      COUNT_TYPE   ,
      VALUE_TYPE   >* newUniform3fv(
        LOCATION_TYPE const&location,
        COUNT_TYPE    const&count   ,
        VALUE_TYPE    const&value   ){
        return new Uniform3fv<
          LOCATION_TYPE,
          COUNT_TYPE   ,
          VALUE_TYPE   >(
              location,
              count   ,
              value   );
    }
    template<
      typename LOCATION_TYPE = GLint   ,
      typename X_TYPE        = GLdouble,
      typename Y_TYPE        = GLdouble,
      typename Z_TYPE        = GLdouble,
      typename W_TYPE        = GLdouble>
    inline Uniform4d<
      LOCATION_TYPE,
      X_TYPE       ,
      Y_TYPE       ,
      Z_TYPE       ,
      W_TYPE       >* newUniform4d(
        LOCATION_TYPE const&location,
        X_TYPE        const&x       ,
        Y_TYPE        const&y       ,
        Z_TYPE        const&z       ,
        W_TYPE        const&w       ){
        return new Uniform4d<
          LOCATION_TYPE,
          X_TYPE       ,
          Y_TYPE       ,
          Z_TYPE       ,
          W_TYPE       >(
              location,
              x       ,
              y       ,
              z       ,
              w       );
    }
    template<
      typename PROGRAM_TYPE  = GLuint      ,
      typename LOCATION_TYPE = GLint       ,
      typename COUNT_TYPE    = GLsizei     ,
      typename VALUE_TYPE    = const GLint*>
    inline ProgramUniform4iv<
      PROGRAM_TYPE ,
      LOCATION_TYPE,
      COUNT_TYPE   ,
      VALUE_TYPE   >* newProgramUniform4iv(
        PROGRAM_TYPE  const&program ,
        LOCATION_TYPE const&location,
        COUNT_TYPE    const&count   ,
        VALUE_TYPE    const&value   ){
        return new ProgramUniform4iv<
          PROGRAM_TYPE ,
          LOCATION_TYPE,
          COUNT_TYPE   ,
          VALUE_TYPE   >(
              program ,
              location,
              count   ,
              value   );
    }
    template<
      typename LOCATION_TYPE = GLint        ,
      typename COUNT_TYPE    = GLsizei      ,
      typename VALUE_TYPE    = const GLuint*>
    inline Uniform1uiv<
      LOCATION_TYPE,
      COUNT_TYPE   ,
      VALUE_TYPE   >* newUniform1uiv(
        LOCATION_TYPE const&location,
        COUNT_TYPE    const&count   ,
        VALUE_TYPE    const&value   ){
        return new Uniform1uiv<
          LOCATION_TYPE,
          COUNT_TYPE   ,
          VALUE_TYPE   >(
              location,
              count   ,
              value   );
    }
    template<
      typename PROGRAM_TYPE   = GLuint        ,
      typename LOCATION_TYPE  = GLint         ,
      typename COUNT_TYPE     = GLsizei       ,
      typename TRANSPOSE_TYPE = GLboolean     ,
      typename VALUE_TYPE     = const GLfloat*>
    inline ProgramUniformMatrix2x3fv<
      PROGRAM_TYPE  ,
      LOCATION_TYPE ,
      COUNT_TYPE    ,
      TRANSPOSE_TYPE,
      VALUE_TYPE    >* newProgramUniformMatrix2x3fv(
        PROGRAM_TYPE   const&program  ,
        LOCATION_TYPE  const&location ,
        COUNT_TYPE     const&count    ,
        TRANSPOSE_TYPE const&transpose,
        VALUE_TYPE     const&value    ){
        return new ProgramUniformMatrix2x3fv<
          PROGRAM_TYPE  ,
          LOCATION_TYPE ,
          COUNT_TYPE    ,
          TRANSPOSE_TYPE,
          VALUE_TYPE    >(
              program  ,
              location ,
              count    ,
              transpose,
              value    );
    }
    template<
      typename LOCATION_TYPE  = GLint         ,
      typename COUNT_TYPE     = GLsizei       ,
      typename TRANSPOSE_TYPE = GLboolean     ,
      typename VALUE_TYPE     = const GLfloat*>
    inline UniformMatrix3fv<
      LOCATION_TYPE ,
      COUNT_TYPE    ,
      TRANSPOSE_TYPE,
      VALUE_TYPE    >* newUniformMatrix3fv(
        LOCATION_TYPE  const&location ,
        COUNT_TYPE     const&count    ,
        TRANSPOSE_TYPE const&transpose,
        VALUE_TYPE     const&value    ){
        return new UniformMatrix3fv<
          LOCATION_TYPE ,
          COUNT_TYPE    ,
          TRANSPOSE_TYPE,
          VALUE_TYPE    >(
              location ,
              count    ,
              transpose,
              value    );
    }
    template<
      typename PROGRAM_TYPE  = GLuint ,
      typename LOCATION_TYPE = GLint  ,
      typename V0_TYPE       = GLfloat>
    inline ProgramUniform1f<
      PROGRAM_TYPE ,
      LOCATION_TYPE,
      V0_TYPE      >* newProgramUniform1f(
        PROGRAM_TYPE  const&program ,
        LOCATION_TYPE const&location,
        V0_TYPE       const&v0      ){
        return new ProgramUniform1f<
          PROGRAM_TYPE ,
          LOCATION_TYPE,
          V0_TYPE      >(
              program ,
              location,
              v0      );
    }
    template<
      typename LOCATION_TYPE = GLint  ,
      typename V0_TYPE       = GLfloat,
      typename V1_TYPE       = GLfloat,
      typename V2_TYPE       = GLfloat,
      typename V3_TYPE       = GLfloat>
    inline Uniform4f<
      LOCATION_TYPE,
      V0_TYPE      ,
      V1_TYPE      ,
      V2_TYPE      ,
      V3_TYPE      >* newUniform4f(
        LOCATION_TYPE const&location,
        V0_TYPE       const&v0      ,
        V1_TYPE       const&v1      ,
        V2_TYPE       const&v2      ,
        V3_TYPE       const&v3      ){
        return new Uniform4f<
          LOCATION_TYPE,
          V0_TYPE      ,
          V1_TYPE      ,
          V2_TYPE      ,
          V3_TYPE      >(
              location,
              v0      ,
              v1      ,
              v2      ,
              v3      );
    }
    template<
      typename LOCATION_TYPE  = GLint          ,
      typename COUNT_TYPE     = GLsizei        ,
      typename TRANSPOSE_TYPE = GLboolean      ,
      typename VALUE_TYPE     = const GLdouble*>
    inline UniformMatrix4x2dv<
      LOCATION_TYPE ,
      COUNT_TYPE    ,
      TRANSPOSE_TYPE,
      VALUE_TYPE    >* newUniformMatrix4x2dv(
        LOCATION_TYPE  const&location ,
        COUNT_TYPE     const&count    ,
        TRANSPOSE_TYPE const&transpose,
        VALUE_TYPE     const&value    ){
        return new UniformMatrix4x2dv<
          LOCATION_TYPE ,
          COUNT_TYPE    ,
          TRANSPOSE_TYPE,
          VALUE_TYPE    >(
              location ,
              count    ,
              transpose,
              value    );
    }
    template<
      typename LOCATION_TYPE = GLint        ,
      typename COUNT_TYPE    = GLsizei      ,
      typename VALUE_TYPE    = const GLuint*>
    inline Uniform4uiv<
      LOCATION_TYPE,
      COUNT_TYPE   ,
      VALUE_TYPE   >* newUniform4uiv(
        LOCATION_TYPE const&location,
        COUNT_TYPE    const&count   ,
        VALUE_TYPE    const&value   ){
        return new Uniform4uiv<
          LOCATION_TYPE,
          COUNT_TYPE   ,
          VALUE_TYPE   >(
              location,
              count   ,
              value   );
    }
    template<
      typename LOCATION_TYPE = GLint ,
      typename V0_TYPE       = GLuint,
      typename V1_TYPE       = GLuint>
    inline Uniform2ui<
      LOCATION_TYPE,
      V0_TYPE      ,
      V1_TYPE      >* newUniform2ui(
        LOCATION_TYPE const&location,
        V0_TYPE       const&v0      ,
        V1_TYPE       const&v1      ){
        return new Uniform2ui<
          LOCATION_TYPE,
          V0_TYPE      ,
          V1_TYPE      >(
              location,
              v0      ,
              v1      );
    }
    template<
      typename PROGRAM_TYPE   = GLuint         ,
      typename LOCATION_TYPE  = GLint          ,
      typename COUNT_TYPE     = GLsizei        ,
      typename TRANSPOSE_TYPE = GLboolean      ,
      typename VALUE_TYPE     = const GLdouble*>
    inline ProgramUniformMatrix3x2dv<
      PROGRAM_TYPE  ,
      LOCATION_TYPE ,
      COUNT_TYPE    ,
      TRANSPOSE_TYPE,
      VALUE_TYPE    >* newProgramUniformMatrix3x2dv(
        PROGRAM_TYPE   const&program  ,
        LOCATION_TYPE  const&location ,
        COUNT_TYPE     const&count    ,
        TRANSPOSE_TYPE const&transpose,
        VALUE_TYPE     const&value    ){
        return new ProgramUniformMatrix3x2dv<
          PROGRAM_TYPE  ,
          LOCATION_TYPE ,
          COUNT_TYPE    ,
          TRANSPOSE_TYPE,
          VALUE_TYPE    >(
              program  ,
              location ,
              count    ,
              transpose,
              value    );
    }
    template<
      typename SHADERTYPE_TYPE = GLenum ,
      typename LOCATION_TYPE   = GLint  ,
      typename PARAMS_TYPE     = GLuint*>
    inline GetUniformSubroutineuiv<
      SHADERTYPE_TYPE,
      LOCATION_TYPE  ,
      PARAMS_TYPE    >* newGetUniformSubroutineuiv(
        SHADERTYPE_TYPE const&shadertype,
        LOCATION_TYPE   const&location  ,
        PARAMS_TYPE     const&params    ){
        return new GetUniformSubroutineuiv<
          SHADERTYPE_TYPE,
          LOCATION_TYPE  ,
          PARAMS_TYPE    >(
              shadertype,
              location  ,
              params    );
    }
    template<
      typename PROGRAM_TYPE  = GLuint  ,
      typename LOCATION_TYPE = GLint   ,
      typename V0_TYPE       = GLdouble,
      typename V1_TYPE       = GLdouble,
      typename V2_TYPE       = GLdouble,
      typename V3_TYPE       = GLdouble>
    inline ProgramUniform4d<
      PROGRAM_TYPE ,
      LOCATION_TYPE,
      V0_TYPE      ,
      V1_TYPE      ,
      V2_TYPE      ,
      V3_TYPE      >* newProgramUniform4d(
        PROGRAM_TYPE  const&program ,
        LOCATION_TYPE const&location,
        V0_TYPE       const&v0      ,
        V1_TYPE       const&v1      ,
        V2_TYPE       const&v2      ,
        V3_TYPE       const&v3      ){
        return new ProgramUniform4d<
          PROGRAM_TYPE ,
          LOCATION_TYPE,
          V0_TYPE      ,
          V1_TYPE      ,
          V2_TYPE      ,
          V3_TYPE      >(
              program ,
              location,
              v0      ,
              v1      ,
              v2      ,
              v3      );
    }
    template<
      typename PROGRAM_TYPE           = GLuint,
      typename UNIFORMBLOCKINDEX_TYPE = GLuint,
      typename PNAME_TYPE             = GLenum,
      typename PARAMS_TYPE            = GLint*>
    inline GetActiveUniformBlockiv<
      PROGRAM_TYPE          ,
      UNIFORMBLOCKINDEX_TYPE,
      PNAME_TYPE            ,
      PARAMS_TYPE           >* newGetActiveUniformBlockiv(
        PROGRAM_TYPE           const&program          ,
        UNIFORMBLOCKINDEX_TYPE const&uniformBlockIndex,
        PNAME_TYPE             const&pname            ,
        PARAMS_TYPE            const&params           ){
        return new GetActiveUniformBlockiv<
          PROGRAM_TYPE          ,
          UNIFORMBLOCKINDEX_TYPE,
          PNAME_TYPE            ,
          PARAMS_TYPE           >(
              program          ,
              uniformBlockIndex,
              pname            ,
              params           );
    }
    template<
      typename PROGRAM_TYPE   = GLuint        ,
      typename LOCATION_TYPE  = GLint         ,
      typename COUNT_TYPE     = GLsizei       ,
      typename TRANSPOSE_TYPE = GLboolean     ,
      typename VALUE_TYPE     = const GLfloat*>
    inline ProgramUniformMatrix4x2fv<
      PROGRAM_TYPE  ,
      LOCATION_TYPE ,
      COUNT_TYPE    ,
      TRANSPOSE_TYPE,
      VALUE_TYPE    >* newProgramUniformMatrix4x2fv(
        PROGRAM_TYPE   const&program  ,
        LOCATION_TYPE  const&location ,
        COUNT_TYPE     const&count    ,
        TRANSPOSE_TYPE const&transpose,
        VALUE_TYPE     const&value    ){
        return new ProgramUniformMatrix4x2fv<
          PROGRAM_TYPE  ,
          LOCATION_TYPE ,
          COUNT_TYPE    ,
          TRANSPOSE_TYPE,
          VALUE_TYPE    >(
              program  ,
              location ,
              count    ,
              transpose,
              value    );
    }
    template<
      typename PROGRAM_TYPE   = GLuint        ,
      typename LOCATION_TYPE  = GLint         ,
      typename COUNT_TYPE     = GLsizei       ,
      typename TRANSPOSE_TYPE = GLboolean     ,
      typename VALUE_TYPE     = const GLfloat*>
    inline ProgramUniformMatrix3fv<
      PROGRAM_TYPE  ,
      LOCATION_TYPE ,
      COUNT_TYPE    ,
      TRANSPOSE_TYPE,
      VALUE_TYPE    >* newProgramUniformMatrix3fv(
        PROGRAM_TYPE   const&program  ,
        LOCATION_TYPE  const&location ,
        COUNT_TYPE     const&count    ,
        TRANSPOSE_TYPE const&transpose,
        VALUE_TYPE     const&value    ){
        return new ProgramUniformMatrix3fv<
          PROGRAM_TYPE  ,
          LOCATION_TYPE ,
          COUNT_TYPE    ,
          TRANSPOSE_TYPE,
          VALUE_TYPE    >(
              program  ,
              location ,
              count    ,
              transpose,
              value    );
    }
    template<
      typename LOCATION_TYPE  = GLint         ,
      typename COUNT_TYPE     = GLsizei       ,
      typename TRANSPOSE_TYPE = GLboolean     ,
      typename VALUE_TYPE     = const GLfloat*>
    inline UniformMatrix3x2fv<
      LOCATION_TYPE ,
      COUNT_TYPE    ,
      TRANSPOSE_TYPE,
      VALUE_TYPE    >* newUniformMatrix3x2fv(
        LOCATION_TYPE  const&location ,
        COUNT_TYPE     const&count    ,
        TRANSPOSE_TYPE const&transpose,
        VALUE_TYPE     const&value    ){
        return new UniformMatrix3x2fv<
          LOCATION_TYPE ,
          COUNT_TYPE    ,
          TRANSPOSE_TYPE,
          VALUE_TYPE    >(
              location ,
              count    ,
              transpose,
              value    );
    }
    template<
      typename PROGRAM_TYPE  = GLuint   ,
      typename LOCATION_TYPE = GLint    ,
      typename PARAMS_TYPE   = GLdouble*>
    inline GetUniformdv<
      PROGRAM_TYPE ,
      LOCATION_TYPE,
      PARAMS_TYPE  >* newGetUniformdv(
        PROGRAM_TYPE  const&program ,
        LOCATION_TYPE const&location,
        PARAMS_TYPE   const&params  ){
        return new GetUniformdv<
          PROGRAM_TYPE ,
          LOCATION_TYPE,
          PARAMS_TYPE  >(
              program ,
              location,
              params  );
    }
    template<
      typename LOCATION_TYPE = GLint  ,
      typename V0_TYPE       = GLfloat,
      typename V1_TYPE       = GLfloat,
      typename V2_TYPE       = GLfloat>
    inline Uniform3f<
      LOCATION_TYPE,
      V0_TYPE      ,
      V1_TYPE      ,
      V2_TYPE      >* newUniform3f(
        LOCATION_TYPE const&location,
        V0_TYPE       const&v0      ,
        V1_TYPE       const&v1      ,
        V2_TYPE       const&v2      ){
        return new Uniform3f<
          LOCATION_TYPE,
          V0_TYPE      ,
          V1_TYPE      ,
          V2_TYPE      >(
              location,
              v0      ,
              v1      ,
              v2      );
    }
    template<
      typename PROGRAM_TYPE  = GLuint ,
      typename LOCATION_TYPE = GLint  ,
      typename V0_TYPE       = GLfloat,
      typename V1_TYPE       = GLfloat>
    inline ProgramUniform2f<
      PROGRAM_TYPE ,
      LOCATION_TYPE,
      V0_TYPE      ,
      V1_TYPE      >* newProgramUniform2f(
        PROGRAM_TYPE  const&program ,
        LOCATION_TYPE const&location,
        V0_TYPE       const&v0      ,
        V1_TYPE       const&v1      ){
        return new ProgramUniform2f<
          PROGRAM_TYPE ,
          LOCATION_TYPE,
          V0_TYPE      ,
          V1_TYPE      >(
              program ,
              location,
              v0      ,
              v1      );
    }
    template<
      typename PROGRAM_TYPE  = GLuint         ,
      typename LOCATION_TYPE = GLint          ,
      typename COUNT_TYPE    = GLsizei        ,
      typename VALUE_TYPE    = const GLdouble*>
    inline ProgramUniform1dv<
      PROGRAM_TYPE ,
      LOCATION_TYPE,
      COUNT_TYPE   ,
      VALUE_TYPE   >* newProgramUniform1dv(
        PROGRAM_TYPE  const&program ,
        LOCATION_TYPE const&location,
        COUNT_TYPE    const&count   ,
        VALUE_TYPE    const&value   ){
        return new ProgramUniform1dv<
          PROGRAM_TYPE ,
          LOCATION_TYPE,
          COUNT_TYPE   ,
          VALUE_TYPE   >(
              program ,
              location,
              count   ,
              value   );
    }
    template<
      typename LOCATION_TYPE  = GLint          ,
      typename COUNT_TYPE     = GLsizei        ,
      typename TRANSPOSE_TYPE = GLboolean      ,
      typename VALUE_TYPE     = const GLdouble*>
    inline UniformMatrix2dv<
      LOCATION_TYPE ,
      COUNT_TYPE    ,
      TRANSPOSE_TYPE,
      VALUE_TYPE    >* newUniformMatrix2dv(
        LOCATION_TYPE  const&location ,
        COUNT_TYPE     const&count    ,
        TRANSPOSE_TYPE const&transpose,
        VALUE_TYPE     const&value    ){
        return new UniformMatrix2dv<
          LOCATION_TYPE ,
          COUNT_TYPE    ,
          TRANSPOSE_TYPE,
          VALUE_TYPE    >(
              location ,
              count    ,
              transpose,
              value    );
    }
    template<
      typename RET_TYPE     = GLint        ,
      typename PROGRAM_TYPE = GLuint       ,
      typename NAME_TYPE    = const GLchar*>
    inline GetUniformLocation<
      RET_TYPE    ,
      PROGRAM_TYPE,
      NAME_TYPE   >* newGetUniformLocation(
        RET_TYPE     const&ret    ,
        PROGRAM_TYPE const&program,
        NAME_TYPE    const&name   ){
        return new GetUniformLocation<
          RET_TYPE    ,
          PROGRAM_TYPE,
          NAME_TYPE   >(
              ret    ,
              program,
              name   );
    }
    template<
      typename LOCATION_TYPE = GLint  ,
      typename V0_TYPE       = GLfloat>
    inline Uniform1f<
      LOCATION_TYPE,
      V0_TYPE      >* newUniform1f(
        LOCATION_TYPE const&location,
        V0_TYPE       const&v0      ){
        return new Uniform1f<
          LOCATION_TYPE,
          V0_TYPE      >(
              location,
              v0      );
    }
    template<
      typename LOCATION_TYPE = GLint        ,
      typename COUNT_TYPE    = GLsizei      ,
      typename VALUE_TYPE    = const GLuint*>
    inline Uniform3uiv<
      LOCATION_TYPE,
      COUNT_TYPE   ,
      VALUE_TYPE   >* newUniform3uiv(
        LOCATION_TYPE const&location,
        COUNT_TYPE    const&count   ,
        VALUE_TYPE    const&value   ){
        return new Uniform3uiv<
          LOCATION_TYPE,
          COUNT_TYPE   ,
          VALUE_TYPE   >(
              location,
              count   ,
              value   );
    }
    template<
      typename PROGRAM_TYPE   = GLuint        ,
      typename LOCATION_TYPE  = GLint         ,
      typename COUNT_TYPE     = GLsizei       ,
      typename TRANSPOSE_TYPE = GLboolean     ,
      typename VALUE_TYPE     = const GLfloat*>
    inline ProgramUniformMatrix4x3fv<
      PROGRAM_TYPE  ,
      LOCATION_TYPE ,
      COUNT_TYPE    ,
      TRANSPOSE_TYPE,
      VALUE_TYPE    >* newProgramUniformMatrix4x3fv(
        PROGRAM_TYPE   const&program  ,
        LOCATION_TYPE  const&location ,
        COUNT_TYPE     const&count    ,
        TRANSPOSE_TYPE const&transpose,
        VALUE_TYPE     const&value    ){
        return new ProgramUniformMatrix4x3fv<
          PROGRAM_TYPE  ,
          LOCATION_TYPE ,
          COUNT_TYPE    ,
          TRANSPOSE_TYPE,
          VALUE_TYPE    >(
              program  ,
              location ,
              count    ,
              transpose,
              value    );
    }
    template<
      typename LOCATION_TYPE = GLint   ,
      typename X_TYPE        = GLdouble>
    inline Uniform1d<
      LOCATION_TYPE,
      X_TYPE       >* newUniform1d(
        LOCATION_TYPE const&location,
        X_TYPE        const&x       ){
        return new Uniform1d<
          LOCATION_TYPE,
          X_TYPE       >(
              location,
              x       );
    }
    template<
      typename PROGRAM_TYPE      = GLuint  ,
      typename UNIFORMINDEX_TYPE = GLuint  ,
      typename BUFSIZE_TYPE      = GLsizei ,
      typename LENGTH_TYPE       = GLsizei*,
      typename UNIFORMNAME_TYPE  = GLchar* >
    inline GetActiveUniformName<
      PROGRAM_TYPE     ,
      UNIFORMINDEX_TYPE,
      BUFSIZE_TYPE     ,
      LENGTH_TYPE      ,
      UNIFORMNAME_TYPE >* newGetActiveUniformName(
        PROGRAM_TYPE      const&program     ,
        UNIFORMINDEX_TYPE const&uniformIndex,
        BUFSIZE_TYPE      const&bufSize     ,
        LENGTH_TYPE       const&length      ,
        UNIFORMNAME_TYPE  const&uniformName ){
        return new GetActiveUniformName<
          PROGRAM_TYPE     ,
          UNIFORMINDEX_TYPE,
          BUFSIZE_TYPE     ,
          LENGTH_TYPE      ,
          UNIFORMNAME_TYPE >(
              program     ,
              uniformIndex,
              bufSize     ,
              length      ,
              uniformName );
    }
    template<
      typename PROGRAM_TYPE  = GLuint  ,
      typename LOCATION_TYPE = GLint   ,
      typename V0_TYPE       = GLdouble>
    inline ProgramUniform1d<
      PROGRAM_TYPE ,
      LOCATION_TYPE,
      V0_TYPE      >* newProgramUniform1d(
        PROGRAM_TYPE  const&program ,
        LOCATION_TYPE const&location,
        V0_TYPE       const&v0      ){
        return new ProgramUniform1d<
          PROGRAM_TYPE ,
          LOCATION_TYPE,
          V0_TYPE      >(
              program ,
              location,
              v0      );
    }
    template<
      typename PROGRAM_TYPE    = GLuint  ,
      typename SHADERTYPE_TYPE = GLenum  ,
      typename INDEX_TYPE      = GLuint  ,
      typename BUFSIZE_TYPE    = GLsizei ,
      typename LENGTH_TYPE     = GLsizei*,
      typename NAME_TYPE       = GLchar* >
    inline GetActiveSubroutineUniformName<
      PROGRAM_TYPE   ,
      SHADERTYPE_TYPE,
      INDEX_TYPE     ,
      BUFSIZE_TYPE   ,
      LENGTH_TYPE    ,
      NAME_TYPE      >* newGetActiveSubroutineUniformName(
        PROGRAM_TYPE    const&program   ,
        SHADERTYPE_TYPE const&shadertype,
        INDEX_TYPE      const&index     ,
        BUFSIZE_TYPE    const&bufsize   ,
        LENGTH_TYPE     const&length    ,
        NAME_TYPE       const&name      ){
        return new GetActiveSubroutineUniformName<
          PROGRAM_TYPE   ,
          SHADERTYPE_TYPE,
          INDEX_TYPE     ,
          BUFSIZE_TYPE   ,
          LENGTH_TYPE    ,
          NAME_TYPE      >(
              program   ,
              shadertype,
              index     ,
              bufsize   ,
              length    ,
              name      );
    }
    template<
      typename PROGRAM_TYPE  = GLuint         ,
      typename LOCATION_TYPE = GLint          ,
      typename COUNT_TYPE    = GLsizei        ,
      typename VALUE_TYPE    = const GLdouble*>
    inline ProgramUniform4dv<
      PROGRAM_TYPE ,
      LOCATION_TYPE,
      COUNT_TYPE   ,
      VALUE_TYPE   >* newProgramUniform4dv(
        PROGRAM_TYPE  const&program ,
        LOCATION_TYPE const&location,
        COUNT_TYPE    const&count   ,
        VALUE_TYPE    const&value   ){
        return new ProgramUniform4dv<
          PROGRAM_TYPE ,
          LOCATION_TYPE,
          COUNT_TYPE   ,
          VALUE_TYPE   >(
              program ,
              location,
              count   ,
              value   );
    }
  }
}
