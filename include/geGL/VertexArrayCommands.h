#pragma once

#include<geCore/Command.h>
#include<geGL/Export.h>
#include<GL/glew.h>
#include<geGL/AllAttribs.h>

namespace ge{
  namespace gl{
    template<
      typename VAOBJ_TYPE          = GLuint,
      typename ATTRIBINDEX_TYPE    = GLuint,
      typename SIZE_TYPE           = GLint ,
      typename TYPE_TYPE           = GLenum,
      typename RELATIVEOFFSET_TYPE = GLuint>
    class VertexArrayAttribIFormat:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "vaobj"         )return(void*)&this->vaobj         ;
          if(name == "attribindex"   )return(void*)&this->attribindex   ;
          if(name == "size"          )return(void*)&this->size          ;
          if(name == "type"          )return(void*)&this->type          ;
          if(name == "relativeoffset")return(void*)&this->relativeoffset;
          return NULL;
        }
      public:
        VAOBJ_TYPE          vaobj         ;
        ATTRIBINDEX_TYPE    attribindex   ;
        SIZE_TYPE           size          ;
        TYPE_TYPE           type          ;
        RELATIVEOFFSET_TYPE relativeoffset;
        VertexArrayAttribIFormat(
            VAOBJ_TYPE          const&vaobj         ,
            ATTRIBINDEX_TYPE    const&attribindex   ,
            SIZE_TYPE           const&size          ,
            TYPE_TYPE           const&type          ,
            RELATIVEOFFSET_TYPE const&relativeoffset){
          this->vaobj          = vaobj         ;
          this->attribindex    = attribindex   ;
          this->size           = size          ;
          this->type           = type          ;
          this->relativeoffset = relativeoffset;
        }
        virtual~VertexArrayAttribIFormat(){}
        virtual void operator()(){
          glVertexArrayAttribIFormat(
            ge::core::convertTo<GLuint>(this->vaobj         ),
            ge::core::convertTo<GLuint>(this->attribindex   ),
            ge::core::convertTo<GLint >(this->size          ),
            ge::core::convertTo<GLenum>(this->type          ),
            ge::core::convertTo<GLuint>(this->relativeoffset)
          );
        }
    };

    template<
      typename N_TYPE      = GLsizei,
      typename ARRAYS_TYPE = GLuint*>
    class GenVertexArrays:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "n"     )return(void*)&this->n     ;
          if(name == "arrays")return(void*)&this->arrays;
          return NULL;
        }
      public:
        N_TYPE      n     ;
        ARRAYS_TYPE arrays;
        GenVertexArrays(
            N_TYPE      const&n     ,
            ARRAYS_TYPE const&arrays){
          this->n      = n     ;
          this->arrays = arrays;
        }
        virtual~GenVertexArrays(){}
        virtual void operator()(){
          glGenVertexArrays(
            ge::core::convertTo<GLsizei>(this->n     ),
            ge::core::convertTo<GLuint*>(this->arrays)
          );
        }
    };

    template<
      typename VAOBJ_TYPE = GLuint,
      typename INDEX_TYPE = GLuint>
    class EnableVertexArrayAttrib:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "vaobj")return(void*)&this->vaobj;
          if(name == "index")return(void*)&this->index;
          return NULL;
        }
      public:
        VAOBJ_TYPE vaobj;
        INDEX_TYPE index;
        EnableVertexArrayAttrib(
            VAOBJ_TYPE const&vaobj,
            INDEX_TYPE const&index){
          this->vaobj = vaobj;
          this->index = index;
        }
        virtual~EnableVertexArrayAttrib(){}
        virtual void operator()(){
          glEnableVertexArrayAttrib(
            ge::core::convertTo<GLuint>(this->vaobj),
            ge::core::convertTo<GLuint>(this->index)
          );
        }
    };

    template<
      typename VAOBJ_TYPE          = GLuint,
      typename ATTRIBINDEX_TYPE    = GLuint,
      typename SIZE_TYPE           = GLint ,
      typename TYPE_TYPE           = GLenum,
      typename RELATIVEOFFSET_TYPE = GLuint>
    class VertexArrayAttribLFormat:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "vaobj"         )return(void*)&this->vaobj         ;
          if(name == "attribindex"   )return(void*)&this->attribindex   ;
          if(name == "size"          )return(void*)&this->size          ;
          if(name == "type"          )return(void*)&this->type          ;
          if(name == "relativeoffset")return(void*)&this->relativeoffset;
          return NULL;
        }
      public:
        VAOBJ_TYPE          vaobj         ;
        ATTRIBINDEX_TYPE    attribindex   ;
        SIZE_TYPE           size          ;
        TYPE_TYPE           type          ;
        RELATIVEOFFSET_TYPE relativeoffset;
        VertexArrayAttribLFormat(
            VAOBJ_TYPE          const&vaobj         ,
            ATTRIBINDEX_TYPE    const&attribindex   ,
            SIZE_TYPE           const&size          ,
            TYPE_TYPE           const&type          ,
            RELATIVEOFFSET_TYPE const&relativeoffset){
          this->vaobj          = vaobj         ;
          this->attribindex    = attribindex   ;
          this->size           = size          ;
          this->type           = type          ;
          this->relativeoffset = relativeoffset;
        }
        virtual~VertexArrayAttribLFormat(){}
        virtual void operator()(){
          glVertexArrayAttribLFormat(
            ge::core::convertTo<GLuint>(this->vaobj         ),
            ge::core::convertTo<GLuint>(this->attribindex   ),
            ge::core::convertTo<GLint >(this->size          ),
            ge::core::convertTo<GLenum>(this->type          ),
            ge::core::convertTo<GLuint>(this->relativeoffset)
          );
        }
    };

    template<
      typename VAOBJ_TYPE = GLuint,
      typename PNAME_TYPE = GLenum,
      typename PARAM_TYPE = GLint*>
    class GetVertexArrayiv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "vaobj")return(void*)&this->vaobj;
          if(name == "pname")return(void*)&this->pname;
          if(name == "param")return(void*)&this->param;
          return NULL;
        }
      public:
        VAOBJ_TYPE vaobj;
        PNAME_TYPE pname;
        PARAM_TYPE param;
        GetVertexArrayiv(
            VAOBJ_TYPE const&vaobj,
            PNAME_TYPE const&pname,
            PARAM_TYPE const&param){
          this->vaobj = vaobj;
          this->pname = pname;
          this->param = param;
        }
        virtual~GetVertexArrayiv(){}
        virtual void operator()(){
          glGetVertexArrayiv(
            ge::core::convertTo<GLuint>(this->vaobj),
            ge::core::convertTo<GLenum>(this->pname),
            ge::core::convertTo<GLint*>(this->param)
          );
        }
    };

    template<
      typename VAOBJ_TYPE   = GLuint         ,
      typename FIRST_TYPE   = GLuint         ,
      typename COUNT_TYPE   = GLsizei        ,
      typename BUFFERS_TYPE = const GLuint*  ,
      typename OFFSETS_TYPE = const GLintptr*,
      typename STRIDES_TYPE = const GLsizei* >
    class VertexArrayVertexBuffers:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "vaobj"  )return(void*)&this->vaobj  ;
          if(name == "first"  )return(void*)&this->first  ;
          if(name == "count"  )return(void*)&this->count  ;
          if(name == "buffers")return(void*)&this->buffers;
          if(name == "offsets")return(void*)&this->offsets;
          if(name == "strides")return(void*)&this->strides;
          return NULL;
        }
      public:
        VAOBJ_TYPE   vaobj  ;
        FIRST_TYPE   first  ;
        COUNT_TYPE   count  ;
        BUFFERS_TYPE buffers;
        OFFSETS_TYPE offsets;
        STRIDES_TYPE strides;
        VertexArrayVertexBuffers(
            VAOBJ_TYPE   const&vaobj  ,
            FIRST_TYPE   const&first  ,
            COUNT_TYPE   const&count  ,
            BUFFERS_TYPE const&buffers,
            OFFSETS_TYPE const&offsets,
            STRIDES_TYPE const&strides){
          this->vaobj   = vaobj  ;
          this->first   = first  ;
          this->count   = count  ;
          this->buffers = buffers;
          this->offsets = offsets;
          this->strides = strides;
        }
        virtual~VertexArrayVertexBuffers(){}
        virtual void operator()(){
          glVertexArrayVertexBuffers(
            ge::core::convertTo<GLuint         >(this->vaobj  ),
            ge::core::convertTo<GLuint         >(this->first  ),
            ge::core::convertTo<GLsizei        >(this->count  ),
            ge::core::convertTo<const GLuint*  >(this->buffers),
            ge::core::convertTo<const GLintptr*>(this->offsets),
            ge::core::convertTo<const GLsizei* >(this->strides)
          );
        }
    };

    template<
      typename VAOBJ_TYPE  = GLuint,
      typename BUFFER_TYPE = GLuint>
    class VertexArrayElementBuffer:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "vaobj" )return(void*)&this->vaobj ;
          if(name == "buffer")return(void*)&this->buffer;
          return NULL;
        }
      public:
        VAOBJ_TYPE  vaobj ;
        BUFFER_TYPE buffer;
        VertexArrayElementBuffer(
            VAOBJ_TYPE  const&vaobj ,
            BUFFER_TYPE const&buffer){
          this->vaobj  = vaobj ;
          this->buffer = buffer;
        }
        virtual~VertexArrayElementBuffer(){}
        virtual void operator()(){
          glVertexArrayElementBuffer(
            ge::core::convertTo<GLuint>(this->vaobj ),
            ge::core::convertTo<GLuint>(this->buffer)
          );
        }
    };

    template<
      typename VAOBJ_TYPE        = GLuint  ,
      typename BINDINGINDEX_TYPE = GLuint  ,
      typename BUFFER_TYPE       = GLuint  ,
      typename OFFSET_TYPE       = GLintptr,
      typename STRIDE_TYPE       = GLsizei >
    class VertexArrayVertexBuffer:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "vaobj"       )return(void*)&this->vaobj       ;
          if(name == "bindingindex")return(void*)&this->bindingindex;
          if(name == "buffer"      )return(void*)&this->buffer      ;
          if(name == "offset"      )return(void*)&this->offset      ;
          if(name == "stride"      )return(void*)&this->stride      ;
          return NULL;
        }
      public:
        VAOBJ_TYPE        vaobj       ;
        BINDINGINDEX_TYPE bindingindex;
        BUFFER_TYPE       buffer      ;
        OFFSET_TYPE       offset      ;
        STRIDE_TYPE       stride      ;
        VertexArrayVertexBuffer(
            VAOBJ_TYPE        const&vaobj       ,
            BINDINGINDEX_TYPE const&bindingindex,
            BUFFER_TYPE       const&buffer      ,
            OFFSET_TYPE       const&offset      ,
            STRIDE_TYPE       const&stride      ){
          this->vaobj        = vaobj       ;
          this->bindingindex = bindingindex;
          this->buffer       = buffer      ;
          this->offset       = offset      ;
          this->stride       = stride      ;
        }
        virtual~VertexArrayVertexBuffer(){}
        virtual void operator()(){
          glVertexArrayVertexBuffer(
            ge::core::convertTo<GLuint  >(this->vaobj       ),
            ge::core::convertTo<GLuint  >(this->bindingindex),
            ge::core::convertTo<GLuint  >(this->buffer      ),
            ge::core::convertTo<GLintptr>(this->offset      ),
            ge::core::convertTo<GLsizei >(this->stride      )
          );
        }
    };

    template<
      typename N_TYPE      = GLsizei,
      typename ARRAYS_TYPE = GLuint*>
    class CreateVertexArrays:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "n"     )return(void*)&this->n     ;
          if(name == "arrays")return(void*)&this->arrays;
          return NULL;
        }
      public:
        N_TYPE      n     ;
        ARRAYS_TYPE arrays;
        CreateVertexArrays(
            N_TYPE      const&n     ,
            ARRAYS_TYPE const&arrays){
          this->n      = n     ;
          this->arrays = arrays;
        }
        virtual~CreateVertexArrays(){}
        virtual void operator()(){
          glCreateVertexArrays(
            ge::core::convertTo<GLsizei>(this->n     ),
            ge::core::convertTo<GLuint*>(this->arrays)
          );
        }
    };

    template<
      typename N_TYPE      = GLsizei      ,
      typename ARRAYS_TYPE = const GLuint*>
    class DeleteVertexArrays:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "n"     )return(void*)&this->n     ;
          if(name == "arrays")return(void*)&this->arrays;
          return NULL;
        }
      public:
        N_TYPE      n     ;
        ARRAYS_TYPE arrays;
        DeleteVertexArrays(
            N_TYPE      const&n     ,
            ARRAYS_TYPE const&arrays){
          this->n      = n     ;
          this->arrays = arrays;
        }
        virtual~DeleteVertexArrays(){}
        virtual void operator()(){
          glDeleteVertexArrays(
            ge::core::convertTo<GLsizei      >(this->n     ),
            ge::core::convertTo<const GLuint*>(this->arrays)
          );
        }
    };

    template<
      typename VAOBJ_TYPE = GLuint,
      typename INDEX_TYPE = GLuint,
      typename PNAME_TYPE = GLenum,
      typename PARAM_TYPE = GLint*>
    class GetVertexArrayIndexediv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "vaobj")return(void*)&this->vaobj;
          if(name == "index")return(void*)&this->index;
          if(name == "pname")return(void*)&this->pname;
          if(name == "param")return(void*)&this->param;
          return NULL;
        }
      public:
        VAOBJ_TYPE vaobj;
        INDEX_TYPE index;
        PNAME_TYPE pname;
        PARAM_TYPE param;
        GetVertexArrayIndexediv(
            VAOBJ_TYPE const&vaobj,
            INDEX_TYPE const&index,
            PNAME_TYPE const&pname,
            PARAM_TYPE const&param){
          this->vaobj = vaobj;
          this->index = index;
          this->pname = pname;
          this->param = param;
        }
        virtual~GetVertexArrayIndexediv(){}
        virtual void operator()(){
          glGetVertexArrayIndexediv(
            ge::core::convertTo<GLuint>(this->vaobj),
            ge::core::convertTo<GLuint>(this->index),
            ge::core::convertTo<GLenum>(this->pname),
            ge::core::convertTo<GLint*>(this->param)
          );
        }
    };

    template<
      typename VAOBJ_TYPE = GLuint  ,
      typename INDEX_TYPE = GLuint  ,
      typename PNAME_TYPE = GLenum  ,
      typename PARAM_TYPE = GLint64*>
    class GetVertexArrayIndexed64iv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "vaobj")return(void*)&this->vaobj;
          if(name == "index")return(void*)&this->index;
          if(name == "pname")return(void*)&this->pname;
          if(name == "param")return(void*)&this->param;
          return NULL;
        }
      public:
        VAOBJ_TYPE vaobj;
        INDEX_TYPE index;
        PNAME_TYPE pname;
        PARAM_TYPE param;
        GetVertexArrayIndexed64iv(
            VAOBJ_TYPE const&vaobj,
            INDEX_TYPE const&index,
            PNAME_TYPE const&pname,
            PARAM_TYPE const&param){
          this->vaobj = vaobj;
          this->index = index;
          this->pname = pname;
          this->param = param;
        }
        virtual~GetVertexArrayIndexed64iv(){}
        virtual void operator()(){
          glGetVertexArrayIndexed64iv(
            ge::core::convertTo<GLuint  >(this->vaobj),
            ge::core::convertTo<GLuint  >(this->index),
            ge::core::convertTo<GLenum  >(this->pname),
            ge::core::convertTo<GLint64*>(this->param)
          );
        }
    };

    template<
      typename VAOBJ_TYPE          = GLuint   ,
      typename ATTRIBINDEX_TYPE    = GLuint   ,
      typename SIZE_TYPE           = GLint    ,
      typename TYPE_TYPE           = GLenum   ,
      typename NORMALIZED_TYPE     = GLboolean,
      typename RELATIVEOFFSET_TYPE = GLuint   >
    class VertexArrayAttribFormat:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "vaobj"         )return(void*)&this->vaobj         ;
          if(name == "attribindex"   )return(void*)&this->attribindex   ;
          if(name == "size"          )return(void*)&this->size          ;
          if(name == "type"          )return(void*)&this->type          ;
          if(name == "normalized"    )return(void*)&this->normalized    ;
          if(name == "relativeoffset")return(void*)&this->relativeoffset;
          return NULL;
        }
      public:
        VAOBJ_TYPE          vaobj         ;
        ATTRIBINDEX_TYPE    attribindex   ;
        SIZE_TYPE           size          ;
        TYPE_TYPE           type          ;
        NORMALIZED_TYPE     normalized    ;
        RELATIVEOFFSET_TYPE relativeoffset;
        VertexArrayAttribFormat(
            VAOBJ_TYPE          const&vaobj         ,
            ATTRIBINDEX_TYPE    const&attribindex   ,
            SIZE_TYPE           const&size          ,
            TYPE_TYPE           const&type          ,
            NORMALIZED_TYPE     const&normalized    ,
            RELATIVEOFFSET_TYPE const&relativeoffset){
          this->vaobj          = vaobj         ;
          this->attribindex    = attribindex   ;
          this->size           = size          ;
          this->type           = type          ;
          this->normalized     = normalized    ;
          this->relativeoffset = relativeoffset;
        }
        virtual~VertexArrayAttribFormat(){}
        virtual void operator()(){
          glVertexArrayAttribFormat(
            ge::core::convertTo<GLuint   >(this->vaobj         ),
            ge::core::convertTo<GLuint   >(this->attribindex   ),
            ge::core::convertTo<GLint    >(this->size          ),
            ge::core::convertTo<GLenum   >(this->type          ),
            ge::core::convertTo<GLboolean>(this->normalized    ),
            ge::core::convertTo<GLuint   >(this->relativeoffset)
          );
        }
    };

    template<
      typename VAOBJ_TYPE = GLuint,
      typename INDEX_TYPE = GLuint>
    class DisableVertexArrayAttrib:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "vaobj")return(void*)&this->vaobj;
          if(name == "index")return(void*)&this->index;
          return NULL;
        }
      public:
        VAOBJ_TYPE vaobj;
        INDEX_TYPE index;
        DisableVertexArrayAttrib(
            VAOBJ_TYPE const&vaobj,
            INDEX_TYPE const&index){
          this->vaobj = vaobj;
          this->index = index;
        }
        virtual~DisableVertexArrayAttrib(){}
        virtual void operator()(){
          glDisableVertexArrayAttrib(
            ge::core::convertTo<GLuint>(this->vaobj),
            ge::core::convertTo<GLuint>(this->index)
          );
        }
    };

    template<
      typename VAOBJ_TYPE        = GLuint,
      typename BINDINGINDEX_TYPE = GLuint,
      typename DIVISOR_TYPE      = GLuint>
    class VertexArrayBindingDivisor:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "vaobj"       )return(void*)&this->vaobj       ;
          if(name == "bindingindex")return(void*)&this->bindingindex;
          if(name == "divisor"     )return(void*)&this->divisor     ;
          return NULL;
        }
      public:
        VAOBJ_TYPE        vaobj       ;
        BINDINGINDEX_TYPE bindingindex;
        DIVISOR_TYPE      divisor     ;
        VertexArrayBindingDivisor(
            VAOBJ_TYPE        const&vaobj       ,
            BINDINGINDEX_TYPE const&bindingindex,
            DIVISOR_TYPE      const&divisor     ){
          this->vaobj        = vaobj       ;
          this->bindingindex = bindingindex;
          this->divisor      = divisor     ;
        }
        virtual~VertexArrayBindingDivisor(){}
        virtual void operator()(){
          glVertexArrayBindingDivisor(
            ge::core::convertTo<GLuint>(this->vaobj       ),
            ge::core::convertTo<GLuint>(this->bindingindex),
            ge::core::convertTo<GLuint>(this->divisor     )
          );
        }
    };

    template<
      typename VAOBJ_TYPE        = GLuint,
      typename ATTRIBINDEX_TYPE  = GLuint,
      typename BINDINGINDEX_TYPE = GLuint>
    class VertexArrayAttribBinding:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "vaobj"       )return(void*)&this->vaobj       ;
          if(name == "attribindex" )return(void*)&this->attribindex ;
          if(name == "bindingindex")return(void*)&this->bindingindex;
          return NULL;
        }
      public:
        VAOBJ_TYPE        vaobj       ;
        ATTRIBINDEX_TYPE  attribindex ;
        BINDINGINDEX_TYPE bindingindex;
        VertexArrayAttribBinding(
            VAOBJ_TYPE        const&vaobj       ,
            ATTRIBINDEX_TYPE  const&attribindex ,
            BINDINGINDEX_TYPE const&bindingindex){
          this->vaobj        = vaobj       ;
          this->attribindex  = attribindex ;
          this->bindingindex = bindingindex;
        }
        virtual~VertexArrayAttribBinding(){}
        virtual void operator()(){
          glVertexArrayAttribBinding(
            ge::core::convertTo<GLuint>(this->vaobj       ),
            ge::core::convertTo<GLuint>(this->attribindex ),
            ge::core::convertTo<GLuint>(this->bindingindex)
          );
        }
    };

    template<
      typename RET_TYPE   = GLboolean,
      typename ARRAY_TYPE = GLuint   >
    class IsVertexArray:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "ret"  )return(void*)&this->ret  ;
          if(name == "array")return(void*)&this->array;
          return NULL;
        }
      public:
        RET_TYPE   ret  ;
        ARRAY_TYPE array;
        IsVertexArray(
            RET_TYPE   const&ret  ,
            ARRAY_TYPE const&array){
          this->ret   = ret  ;
          this->array = array;
        }
        virtual~IsVertexArray(){}
        virtual void operator()(){
          ge::core::convertFrom<GLboolean>(this->ret,glIsVertexArray(
              ge::core::convertTo<GLuint   >(this->array))
          );
        }
    };

    template<
      typename ARRAY_TYPE = GLuint>
    class BindVertexArray:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "array")return(void*)&this->array;
          return NULL;
        }
      public:
        ARRAY_TYPE array;
        BindVertexArray(
            ARRAY_TYPE const&array){
          this->array = array;
        }
        virtual~BindVertexArray(){}
        virtual void operator()(){
          glBindVertexArray(
            ge::core::convertTo<GLuint>(this->array)
          );
        }
    };

    template<
      typename VAOBJ_TYPE          = GLuint,
      typename ATTRIBINDEX_TYPE    = GLuint,
      typename SIZE_TYPE           = GLint ,
      typename TYPE_TYPE           = GLenum,
      typename RELATIVEOFFSET_TYPE = GLuint>
    inline VertexArrayAttribIFormat<
      VAOBJ_TYPE         ,
      ATTRIBINDEX_TYPE   ,
      SIZE_TYPE          ,
      TYPE_TYPE          ,
      RELATIVEOFFSET_TYPE>* newVertexArrayAttribIFormat(
        VAOBJ_TYPE          const&vaobj         ,
        ATTRIBINDEX_TYPE    const&attribindex   ,
        SIZE_TYPE           const&size          ,
        TYPE_TYPE           const&type          ,
        RELATIVEOFFSET_TYPE const&relativeoffset){
        return new VertexArrayAttribIFormat<
          VAOBJ_TYPE         ,
          ATTRIBINDEX_TYPE   ,
          SIZE_TYPE          ,
          TYPE_TYPE          ,
          RELATIVEOFFSET_TYPE>(
              vaobj         ,
              attribindex   ,
              size          ,
              type          ,
              relativeoffset);
    }
    template<
      typename N_TYPE      = GLsizei,
      typename ARRAYS_TYPE = GLuint*>
    inline GenVertexArrays<
      N_TYPE     ,
      ARRAYS_TYPE>* newGenVertexArrays(
        N_TYPE      const&n     ,
        ARRAYS_TYPE const&arrays){
        return new GenVertexArrays<
          N_TYPE     ,
          ARRAYS_TYPE>(
              n     ,
              arrays);
    }
    template<
      typename VAOBJ_TYPE = GLuint,
      typename INDEX_TYPE = GLuint>
    inline EnableVertexArrayAttrib<
      VAOBJ_TYPE,
      INDEX_TYPE>* newEnableVertexArrayAttrib(
        VAOBJ_TYPE const&vaobj,
        INDEX_TYPE const&index){
        return new EnableVertexArrayAttrib<
          VAOBJ_TYPE,
          INDEX_TYPE>(
              vaobj,
              index);
    }
    template<
      typename VAOBJ_TYPE          = GLuint,
      typename ATTRIBINDEX_TYPE    = GLuint,
      typename SIZE_TYPE           = GLint ,
      typename TYPE_TYPE           = GLenum,
      typename RELATIVEOFFSET_TYPE = GLuint>
    inline VertexArrayAttribLFormat<
      VAOBJ_TYPE         ,
      ATTRIBINDEX_TYPE   ,
      SIZE_TYPE          ,
      TYPE_TYPE          ,
      RELATIVEOFFSET_TYPE>* newVertexArrayAttribLFormat(
        VAOBJ_TYPE          const&vaobj         ,
        ATTRIBINDEX_TYPE    const&attribindex   ,
        SIZE_TYPE           const&size          ,
        TYPE_TYPE           const&type          ,
        RELATIVEOFFSET_TYPE const&relativeoffset){
        return new VertexArrayAttribLFormat<
          VAOBJ_TYPE         ,
          ATTRIBINDEX_TYPE   ,
          SIZE_TYPE          ,
          TYPE_TYPE          ,
          RELATIVEOFFSET_TYPE>(
              vaobj         ,
              attribindex   ,
              size          ,
              type          ,
              relativeoffset);
    }
    template<
      typename VAOBJ_TYPE = GLuint,
      typename PNAME_TYPE = GLenum,
      typename PARAM_TYPE = GLint*>
    inline GetVertexArrayiv<
      VAOBJ_TYPE,
      PNAME_TYPE,
      PARAM_TYPE>* newGetVertexArrayiv(
        VAOBJ_TYPE const&vaobj,
        PNAME_TYPE const&pname,
        PARAM_TYPE const&param){
        return new GetVertexArrayiv<
          VAOBJ_TYPE,
          PNAME_TYPE,
          PARAM_TYPE>(
              vaobj,
              pname,
              param);
    }
    template<
      typename VAOBJ_TYPE   = GLuint         ,
      typename FIRST_TYPE   = GLuint         ,
      typename COUNT_TYPE   = GLsizei        ,
      typename BUFFERS_TYPE = const GLuint*  ,
      typename OFFSETS_TYPE = const GLintptr*,
      typename STRIDES_TYPE = const GLsizei* >
    inline VertexArrayVertexBuffers<
      VAOBJ_TYPE  ,
      FIRST_TYPE  ,
      COUNT_TYPE  ,
      BUFFERS_TYPE,
      OFFSETS_TYPE,
      STRIDES_TYPE>* newVertexArrayVertexBuffers(
        VAOBJ_TYPE   const&vaobj  ,
        FIRST_TYPE   const&first  ,
        COUNT_TYPE   const&count  ,
        BUFFERS_TYPE const&buffers,
        OFFSETS_TYPE const&offsets,
        STRIDES_TYPE const&strides){
        return new VertexArrayVertexBuffers<
          VAOBJ_TYPE  ,
          FIRST_TYPE  ,
          COUNT_TYPE  ,
          BUFFERS_TYPE,
          OFFSETS_TYPE,
          STRIDES_TYPE>(
              vaobj  ,
              first  ,
              count  ,
              buffers,
              offsets,
              strides);
    }
    template<
      typename VAOBJ_TYPE  = GLuint,
      typename BUFFER_TYPE = GLuint>
    inline VertexArrayElementBuffer<
      VAOBJ_TYPE ,
      BUFFER_TYPE>* newVertexArrayElementBuffer(
        VAOBJ_TYPE  const&vaobj ,
        BUFFER_TYPE const&buffer){
        return new VertexArrayElementBuffer<
          VAOBJ_TYPE ,
          BUFFER_TYPE>(
              vaobj ,
              buffer);
    }
    template<
      typename VAOBJ_TYPE        = GLuint  ,
      typename BINDINGINDEX_TYPE = GLuint  ,
      typename BUFFER_TYPE       = GLuint  ,
      typename OFFSET_TYPE       = GLintptr,
      typename STRIDE_TYPE       = GLsizei >
    inline VertexArrayVertexBuffer<
      VAOBJ_TYPE       ,
      BINDINGINDEX_TYPE,
      BUFFER_TYPE      ,
      OFFSET_TYPE      ,
      STRIDE_TYPE      >* newVertexArrayVertexBuffer(
        VAOBJ_TYPE        const&vaobj       ,
        BINDINGINDEX_TYPE const&bindingindex,
        BUFFER_TYPE       const&buffer      ,
        OFFSET_TYPE       const&offset      ,
        STRIDE_TYPE       const&stride      ){
        return new VertexArrayVertexBuffer<
          VAOBJ_TYPE       ,
          BINDINGINDEX_TYPE,
          BUFFER_TYPE      ,
          OFFSET_TYPE      ,
          STRIDE_TYPE      >(
              vaobj       ,
              bindingindex,
              buffer      ,
              offset      ,
              stride      );
    }
    template<
      typename N_TYPE      = GLsizei,
      typename ARRAYS_TYPE = GLuint*>
    inline CreateVertexArrays<
      N_TYPE     ,
      ARRAYS_TYPE>* newCreateVertexArrays(
        N_TYPE      const&n     ,
        ARRAYS_TYPE const&arrays){
        return new CreateVertexArrays<
          N_TYPE     ,
          ARRAYS_TYPE>(
              n     ,
              arrays);
    }
    template<
      typename N_TYPE      = GLsizei      ,
      typename ARRAYS_TYPE = const GLuint*>
    inline DeleteVertexArrays<
      N_TYPE     ,
      ARRAYS_TYPE>* newDeleteVertexArrays(
        N_TYPE      const&n     ,
        ARRAYS_TYPE const&arrays){
        return new DeleteVertexArrays<
          N_TYPE     ,
          ARRAYS_TYPE>(
              n     ,
              arrays);
    }
    template<
      typename VAOBJ_TYPE = GLuint,
      typename INDEX_TYPE = GLuint,
      typename PNAME_TYPE = GLenum,
      typename PARAM_TYPE = GLint*>
    inline GetVertexArrayIndexediv<
      VAOBJ_TYPE,
      INDEX_TYPE,
      PNAME_TYPE,
      PARAM_TYPE>* newGetVertexArrayIndexediv(
        VAOBJ_TYPE const&vaobj,
        INDEX_TYPE const&index,
        PNAME_TYPE const&pname,
        PARAM_TYPE const&param){
        return new GetVertexArrayIndexediv<
          VAOBJ_TYPE,
          INDEX_TYPE,
          PNAME_TYPE,
          PARAM_TYPE>(
              vaobj,
              index,
              pname,
              param);
    }
    template<
      typename VAOBJ_TYPE = GLuint  ,
      typename INDEX_TYPE = GLuint  ,
      typename PNAME_TYPE = GLenum  ,
      typename PARAM_TYPE = GLint64*>
    inline GetVertexArrayIndexed64iv<
      VAOBJ_TYPE,
      INDEX_TYPE,
      PNAME_TYPE,
      PARAM_TYPE>* newGetVertexArrayIndexed64iv(
        VAOBJ_TYPE const&vaobj,
        INDEX_TYPE const&index,
        PNAME_TYPE const&pname,
        PARAM_TYPE const&param){
        return new GetVertexArrayIndexed64iv<
          VAOBJ_TYPE,
          INDEX_TYPE,
          PNAME_TYPE,
          PARAM_TYPE>(
              vaobj,
              index,
              pname,
              param);
    }
    template<
      typename VAOBJ_TYPE          = GLuint   ,
      typename ATTRIBINDEX_TYPE    = GLuint   ,
      typename SIZE_TYPE           = GLint    ,
      typename TYPE_TYPE           = GLenum   ,
      typename NORMALIZED_TYPE     = GLboolean,
      typename RELATIVEOFFSET_TYPE = GLuint   >
    inline VertexArrayAttribFormat<
      VAOBJ_TYPE         ,
      ATTRIBINDEX_TYPE   ,
      SIZE_TYPE          ,
      TYPE_TYPE          ,
      NORMALIZED_TYPE    ,
      RELATIVEOFFSET_TYPE>* newVertexArrayAttribFormat(
        VAOBJ_TYPE          const&vaobj         ,
        ATTRIBINDEX_TYPE    const&attribindex   ,
        SIZE_TYPE           const&size          ,
        TYPE_TYPE           const&type          ,
        NORMALIZED_TYPE     const&normalized    ,
        RELATIVEOFFSET_TYPE const&relativeoffset){
        return new VertexArrayAttribFormat<
          VAOBJ_TYPE         ,
          ATTRIBINDEX_TYPE   ,
          SIZE_TYPE          ,
          TYPE_TYPE          ,
          NORMALIZED_TYPE    ,
          RELATIVEOFFSET_TYPE>(
              vaobj         ,
              attribindex   ,
              size          ,
              type          ,
              normalized    ,
              relativeoffset);
    }
    template<
      typename VAOBJ_TYPE = GLuint,
      typename INDEX_TYPE = GLuint>
    inline DisableVertexArrayAttrib<
      VAOBJ_TYPE,
      INDEX_TYPE>* newDisableVertexArrayAttrib(
        VAOBJ_TYPE const&vaobj,
        INDEX_TYPE const&index){
        return new DisableVertexArrayAttrib<
          VAOBJ_TYPE,
          INDEX_TYPE>(
              vaobj,
              index);
    }
    template<
      typename VAOBJ_TYPE        = GLuint,
      typename BINDINGINDEX_TYPE = GLuint,
      typename DIVISOR_TYPE      = GLuint>
    inline VertexArrayBindingDivisor<
      VAOBJ_TYPE       ,
      BINDINGINDEX_TYPE,
      DIVISOR_TYPE     >* newVertexArrayBindingDivisor(
        VAOBJ_TYPE        const&vaobj       ,
        BINDINGINDEX_TYPE const&bindingindex,
        DIVISOR_TYPE      const&divisor     ){
        return new VertexArrayBindingDivisor<
          VAOBJ_TYPE       ,
          BINDINGINDEX_TYPE,
          DIVISOR_TYPE     >(
              vaobj       ,
              bindingindex,
              divisor     );
    }
    template<
      typename VAOBJ_TYPE        = GLuint,
      typename ATTRIBINDEX_TYPE  = GLuint,
      typename BINDINGINDEX_TYPE = GLuint>
    inline VertexArrayAttribBinding<
      VAOBJ_TYPE       ,
      ATTRIBINDEX_TYPE ,
      BINDINGINDEX_TYPE>* newVertexArrayAttribBinding(
        VAOBJ_TYPE        const&vaobj       ,
        ATTRIBINDEX_TYPE  const&attribindex ,
        BINDINGINDEX_TYPE const&bindingindex){
        return new VertexArrayAttribBinding<
          VAOBJ_TYPE       ,
          ATTRIBINDEX_TYPE ,
          BINDINGINDEX_TYPE>(
              vaobj       ,
              attribindex ,
              bindingindex);
    }
    template<
      typename RET_TYPE   = GLboolean,
      typename ARRAY_TYPE = GLuint   >
    inline IsVertexArray<
      RET_TYPE  ,
      ARRAY_TYPE>* newIsVertexArray(
        RET_TYPE   const&ret  ,
        ARRAY_TYPE const&array){
        return new IsVertexArray<
          RET_TYPE  ,
          ARRAY_TYPE>(
              ret  ,
              array);
    }
    template<
      typename ARRAY_TYPE = GLuint>
    inline BindVertexArray<
      ARRAY_TYPE>* newBindVertexArray(
        ARRAY_TYPE const&array){
        return new BindVertexArray<
          ARRAY_TYPE>(
              array);
    }
  }
}
