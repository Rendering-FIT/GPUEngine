#pragma once

#include<geCore/Command.h>
#include<geGL/Export.h>
#include<GL/glew.h>
#include<geGL/BufferObject.h>
#include<geGL/AllAttribs.h>

namespace ge{
  namespace gl{
    template<
      typename BUFFER_TYPE = GLuint    ,
      typename OFFSET_TYPE = GLintptr  ,
      typename LENGTH_TYPE = GLsizeiptr>
    class InvalidateBufferSubData:
        public ge::core::Command{
      public:
        BUFFER_TYPE buffer;
        OFFSET_TYPE offset;
        LENGTH_TYPE length;
        InvalidateBufferSubData(
            BUFFER_TYPE const&buffer,
            OFFSET_TYPE const&offset,
            LENGTH_TYPE const&length){
          this->buffer = buffer;
          this->offset = offset;
          this->length = length;
        }
        virtual~InvalidateBufferSubData(){}
        virtual void operator()(){
          glInvalidateBufferSubData(
            ge::core::convertTo<GLuint    >(this->buffer),
            ge::core::convertTo<GLintptr  >(this->offset),
            ge::core::convertTo<GLsizeiptr>(this->length)
          );
        }
    };

    template<
      typename ID_TYPE     = GLuint  ,
      typename BUFFER_TYPE = GLuint  ,
      typename PNAME_TYPE  = GLenum  ,
      typename OFFSET_TYPE = GLintptr>
    class GetQueryBufferObjectiv:
        public ge::core::Command{
      public:
        ID_TYPE     id    ;
        BUFFER_TYPE buffer;
        PNAME_TYPE  pname ;
        OFFSET_TYPE offset;
        GetQueryBufferObjectiv(
            ID_TYPE     const&id    ,
            BUFFER_TYPE const&buffer,
            PNAME_TYPE  const&pname ,
            OFFSET_TYPE const&offset){
          this->id     = id    ;
          this->buffer = buffer;
          this->pname  = pname ;
          this->offset = offset;
        }
        virtual~GetQueryBufferObjectiv(){}
        virtual void operator()(){
          glGetQueryBufferObjectiv(
            ge::core::convertTo<GLuint  >(this->id    ),
            ge::core::convertTo<GLuint  >(this->buffer),
            ge::core::convertTo<GLenum  >(this->pname ),
            ge::core::convertTo<GLintptr>(this->offset)
          );
        }
    };

    template<
      typename BUFFER_TYPE         = GLuint     ,
      typename INTERNALFORMAT_TYPE = GLenum     ,
      typename FORMAT_TYPE         = GLenum     ,
      typename TYPE_TYPE           = GLenum     ,
      typename DATA_TYPE           = const void*>
    class ClearNamedBufferData:
        public ge::core::Command{
      public:
        BUFFER_TYPE         buffer        ;
        INTERNALFORMAT_TYPE internalformat;
        FORMAT_TYPE         format        ;
        TYPE_TYPE           type          ;
        DATA_TYPE           data          ;
        ClearNamedBufferData(
            BUFFER_TYPE         const&buffer        ,
            INTERNALFORMAT_TYPE const&internalformat,
            FORMAT_TYPE         const&format        ,
            TYPE_TYPE           const&type          ,
            DATA_TYPE           const&data          ){
          this->buffer         = buffer        ;
          this->internalformat = internalformat;
          this->format         = format        ;
          this->type           = type          ;
          this->data           = data          ;
        }
        virtual~ClearNamedBufferData(){}
        virtual void operator()(){
          glClearNamedBufferData(
            ge::core::convertTo<GLuint     >(this->buffer        ),
            ge::core::convertTo<GLenum     >(this->internalformat),
            ge::core::convertTo<GLenum     >(this->format        ),
            ge::core::convertTo<GLenum     >(this->type          ),
            ge::core::convertTo<const void*>(this->data          )
          );
        }
    };

    template<
      typename PROGRAM_TYPE     = GLuint,
      typename BUFFERINDEX_TYPE = GLuint,
      typename PNAME_TYPE       = GLenum,
      typename PARAMS_TYPE      = GLint*>
    class GetActiveAtomicCounterBufferiv:
        public ge::core::Command{
      public:
        PROGRAM_TYPE     program    ;
        BUFFERINDEX_TYPE bufferIndex;
        PNAME_TYPE       pname      ;
        PARAMS_TYPE      params     ;
        GetActiveAtomicCounterBufferiv(
            PROGRAM_TYPE     const&program    ,
            BUFFERINDEX_TYPE const&bufferIndex,
            PNAME_TYPE       const&pname      ,
            PARAMS_TYPE      const&params     ){
          this->program     = program    ;
          this->bufferIndex = bufferIndex;
          this->pname       = pname      ;
          this->params      = params     ;
        }
        virtual~GetActiveAtomicCounterBufferiv(){}
        virtual void operator()(){
          glGetActiveAtomicCounterBufferiv(
            ge::core::convertTo<GLuint>(this->program    ),
            ge::core::convertTo<GLuint>(this->bufferIndex),
            ge::core::convertTo<GLenum>(this->pname      ),
            ge::core::convertTo<GLint*>(this->params     )
          );
        }
    };

    template<
      typename ID_TYPE     = GLuint  ,
      typename BUFFER_TYPE = GLuint  ,
      typename PNAME_TYPE  = GLenum  ,
      typename OFFSET_TYPE = GLintptr>
    class GetQueryBufferObjectuiv:
        public ge::core::Command{
      public:
        ID_TYPE     id    ;
        BUFFER_TYPE buffer;
        PNAME_TYPE  pname ;
        OFFSET_TYPE offset;
        GetQueryBufferObjectuiv(
            ID_TYPE     const&id    ,
            BUFFER_TYPE const&buffer,
            PNAME_TYPE  const&pname ,
            OFFSET_TYPE const&offset){
          this->id     = id    ;
          this->buffer = buffer;
          this->pname  = pname ;
          this->offset = offset;
        }
        virtual~GetQueryBufferObjectuiv(){}
        virtual void operator()(){
          glGetQueryBufferObjectuiv(
            ge::core::convertTo<GLuint  >(this->id    ),
            ge::core::convertTo<GLuint  >(this->buffer),
            ge::core::convertTo<GLenum  >(this->pname ),
            ge::core::convertTo<GLintptr>(this->offset)
          );
        }
    };

    template<
      typename BUFFER_TYPE = GLuint     ,
      typename SIZE_TYPE   = GLsizeiptr ,
      typename DATA_TYPE   = const void*,
      typename FLAGS_TYPE  = GLbitfield >
    class NamedBufferStorage:
        public ge::core::Command{
      public:
        BUFFER_TYPE buffer;
        SIZE_TYPE   size  ;
        DATA_TYPE   data  ;
        FLAGS_TYPE  flags ;
        NamedBufferStorage(
            BUFFER_TYPE const&buffer,
            SIZE_TYPE   const&size  ,
            DATA_TYPE   const&data  ,
            FLAGS_TYPE  const&flags ){
          this->buffer = buffer;
          this->size   = size  ;
          this->data   = data  ;
          this->flags  = flags ;
        }
        virtual~NamedBufferStorage(){}
        virtual void operator()(){
          glNamedBufferStorage(
            ge::core::convertTo<GLuint     >(this->buffer),
            ge::core::convertTo<GLsizeiptr >(this->size  ),
            ge::core::convertTo<const void*>(this->data  ),
            ge::core::convertTo<GLbitfield >(this->flags )
          );
        }
    };

    template<
      typename BUFFER_TYPE     = GLenum       ,
      typename DRAWBUFFER_TYPE = GLint        ,
      typename VALUE_TYPE      = const GLuint*>
    class ClearBufferuiv:
        public ge::core::Command{
      public:
        BUFFER_TYPE     buffer    ;
        DRAWBUFFER_TYPE drawbuffer;
        VALUE_TYPE      value     ;
        ClearBufferuiv(
            BUFFER_TYPE     const&buffer    ,
            DRAWBUFFER_TYPE const&drawbuffer,
            VALUE_TYPE      const&value     ){
          this->buffer     = buffer    ;
          this->drawbuffer = drawbuffer;
          this->value      = value     ;
        }
        virtual~ClearBufferuiv(){}
        virtual void operator()(){
          glClearBufferuiv(
            ge::core::convertTo<GLenum       >(this->buffer    ),
            ge::core::convertTo<GLint        >(this->drawbuffer),
            ge::core::convertTo<const GLuint*>(this->value     )
          );
        }
    };

    template<
      typename BUFFER_TYPE     = GLenum        ,
      typename DRAWBUFFER_TYPE = GLint         ,
      typename VALUE_TYPE      = const GLfloat*>
    class ClearBufferfv:
        public ge::core::Command{
      public:
        BUFFER_TYPE     buffer    ;
        DRAWBUFFER_TYPE drawbuffer;
        VALUE_TYPE      value     ;
        ClearBufferfv(
            BUFFER_TYPE     const&buffer    ,
            DRAWBUFFER_TYPE const&drawbuffer,
            VALUE_TYPE      const&value     ){
          this->buffer     = buffer    ;
          this->drawbuffer = drawbuffer;
          this->value      = value     ;
        }
        virtual~ClearBufferfv(){}
        virtual void operator()(){
          glClearBufferfv(
            ge::core::convertTo<GLenum        >(this->buffer    ),
            ge::core::convertTo<GLint         >(this->drawbuffer),
            ge::core::convertTo<const GLfloat*>(this->value     )
          );
        }
    };

    template<
      typename RET_TYPE    = GLboolean,
      typename BUFFER_TYPE = GLuint   >
    class UnmapNamedBuffer:
        public ge::core::Command{
      public:
        RET_TYPE    ret   ;
        BUFFER_TYPE buffer;
        UnmapNamedBuffer(
            RET_TYPE    const&ret   ,
            BUFFER_TYPE const&buffer){
          this->ret    = ret   ;
          this->buffer = buffer;
        }
        virtual~UnmapNamedBuffer(){}
        virtual void operator()(){
          ge::core::convertFrom<GLboolean>(this->ret,glUnmapNamedBuffer(
              ge::core::convertTo<GLuint   >(this->buffer))
          );
        }
    };

    template<
      typename XFB_TYPE    = GLuint    ,
      typename INDEX_TYPE  = GLuint    ,
      typename BUFFER_TYPE = GLuint    ,
      typename OFFSET_TYPE = GLintptr  ,
      typename SIZE_TYPE   = GLsizeiptr>
    class TransformFeedbackBufferRange:
        public ge::core::Command{
      public:
        XFB_TYPE    xfb   ;
        INDEX_TYPE  index ;
        BUFFER_TYPE buffer;
        OFFSET_TYPE offset;
        SIZE_TYPE   size  ;
        TransformFeedbackBufferRange(
            XFB_TYPE    const&xfb   ,
            INDEX_TYPE  const&index ,
            BUFFER_TYPE const&buffer,
            OFFSET_TYPE const&offset,
            SIZE_TYPE   const&size  ){
          this->xfb    = xfb   ;
          this->index  = index ;
          this->buffer = buffer;
          this->offset = offset;
          this->size   = size  ;
        }
        virtual~TransformFeedbackBufferRange(){}
        virtual void operator()(){
          glTransformFeedbackBufferRange(
            ge::core::convertTo<GLuint    >(this->xfb   ),
            ge::core::convertTo<GLuint    >(this->index ),
            ge::core::convertTo<GLuint    >(this->buffer),
            ge::core::convertTo<GLintptr  >(this->offset),
            ge::core::convertTo<GLsizeiptr>(this->size  )
          );
        }
    };

    template<
      typename BUFFER_TYPE = GLuint,
      typename PNAME_TYPE  = GLenum,
      typename PARAMS_TYPE = void**>
    class GetNamedBufferPointerv:
        public ge::core::Command{
      public:
        BUFFER_TYPE buffer;
        PNAME_TYPE  pname ;
        PARAMS_TYPE params;
        GetNamedBufferPointerv(
            BUFFER_TYPE const&buffer,
            PNAME_TYPE  const&pname ,
            PARAMS_TYPE const&params){
          this->buffer = buffer;
          this->pname  = pname ;
          this->params = params;
        }
        virtual~GetNamedBufferPointerv(){}
        virtual void operator()(){
          glGetNamedBufferPointerv(
            ge::core::convertTo<GLuint>(this->buffer),
            ge::core::convertTo<GLenum>(this->pname ),
            ge::core::convertTo<void**>(this->params)
          );
        }
    };

    template<
      typename TARGET_TYPE = GLenum    ,
      typename OFFSET_TYPE = GLintptr  ,
      typename SIZE_TYPE   = GLsizeiptr,
      typename DATA_TYPE   = void*     >
    class GetBufferSubData:
        public ge::core::Command{
      public:
        TARGET_TYPE target;
        OFFSET_TYPE offset;
        SIZE_TYPE   size  ;
        DATA_TYPE   data  ;
        GetBufferSubData(
            TARGET_TYPE const&target,
            OFFSET_TYPE const&offset,
            SIZE_TYPE   const&size  ,
            DATA_TYPE   const&data  ){
          this->target = target;
          this->offset = offset;
          this->size   = size  ;
          this->data   = data  ;
        }
        virtual~GetBufferSubData(){}
        virtual void operator()(){
          glGetBufferSubData(
            ge::core::convertTo<GLenum    >(this->target),
            ge::core::convertTo<GLintptr  >(this->offset),
            ge::core::convertTo<GLsizeiptr>(this->size  ),
            ge::core::convertTo<void*     >(this->data  )
          );
        }
    };

    template<
      typename N_TYPE    = GLsizei      ,
      typename BUFS_TYPE = const GLenum*>
    class DrawBuffers:
        public ge::core::Command{
      public:
        N_TYPE    n   ;
        BUFS_TYPE bufs;
        DrawBuffers(
            N_TYPE    const&n   ,
            BUFS_TYPE const&bufs){
          this->n    = n   ;
          this->bufs = bufs;
        }
        virtual~DrawBuffers(){}
        virtual void operator()(){
          glDrawBuffers(
            ge::core::convertTo<GLsizei      >(this->n   ),
            ge::core::convertTo<const GLenum*>(this->bufs)
          );
        }
    };

    template<
      typename TARGET_TYPE = GLenum,
      typename PNAME_TYPE  = GLenum,
      typename PARAMS_TYPE = void**>
    class GetBufferPointerv:
        public ge::core::Command{
      public:
        TARGET_TYPE target;
        PNAME_TYPE  pname ;
        PARAMS_TYPE params;
        GetBufferPointerv(
            TARGET_TYPE const&target,
            PNAME_TYPE  const&pname ,
            PARAMS_TYPE const&params){
          this->target = target;
          this->pname  = pname ;
          this->params = params;
        }
        virtual~GetBufferPointerv(){}
        virtual void operator()(){
          glGetBufferPointerv(
            ge::core::convertTo<GLenum>(this->target),
            ge::core::convertTo<GLenum>(this->pname ),
            ge::core::convertTo<void**>(this->params)
          );
        }
    };

    template<
      typename N_TYPE       = GLsizei,
      typename BUFFERS_TYPE = GLuint*>
    class GenBuffers:
        public ge::core::Command{
      public:
        N_TYPE       n      ;
        BUFFERS_TYPE buffers;
        GenBuffers(
            N_TYPE       const&n      ,
            BUFFERS_TYPE const&buffers){
          this->n       = n      ;
          this->buffers = buffers;
        }
        virtual~GenBuffers(){}
        virtual void operator()(){
          glGenBuffers(
            ge::core::convertTo<GLsizei>(this->n      ),
            ge::core::convertTo<GLuint*>(this->buffers)
          );
        }
    };

    template<
      typename FIRST_TYPE   = GLuint         ,
      typename COUNT_TYPE   = GLsizei        ,
      typename BUFFERS_TYPE = const GLuint*  ,
      typename OFFSETS_TYPE = const GLintptr*,
      typename STRIDES_TYPE = const GLsizei* >
    class BindVertexBuffers:
        public ge::core::Command{
      public:
        FIRST_TYPE   first  ;
        COUNT_TYPE   count  ;
        BUFFERS_TYPE buffers;
        OFFSETS_TYPE offsets;
        STRIDES_TYPE strides;
        BindVertexBuffers(
            FIRST_TYPE   const&first  ,
            COUNT_TYPE   const&count  ,
            BUFFERS_TYPE const&buffers,
            OFFSETS_TYPE const&offsets,
            STRIDES_TYPE const&strides){
          this->first   = first  ;
          this->count   = count  ;
          this->buffers = buffers;
          this->offsets = offsets;
          this->strides = strides;
        }
        virtual~BindVertexBuffers(){}
        virtual void operator()(){
          glBindVertexBuffers(
            ge::core::convertTo<GLuint         >(this->first  ),
            ge::core::convertTo<GLsizei        >(this->count  ),
            ge::core::convertTo<const GLuint*  >(this->buffers),
            ge::core::convertTo<const GLintptr*>(this->offsets),
            ge::core::convertTo<const GLsizei* >(this->strides)
          );
        }
    };

    template<
      typename RET_TYPE    = void*     ,
      typename TARGET_TYPE = GLenum    ,
      typename OFFSET_TYPE = GLintptr  ,
      typename LENGTH_TYPE = GLsizeiptr,
      typename ACCESS_TYPE = GLbitfield>
    class MapBufferRange:
        public ge::core::Command{
      public:
        RET_TYPE    ret   ;
        TARGET_TYPE target;
        OFFSET_TYPE offset;
        LENGTH_TYPE length;
        ACCESS_TYPE access;
        MapBufferRange(
            RET_TYPE    const&ret   ,
            TARGET_TYPE const&target,
            OFFSET_TYPE const&offset,
            LENGTH_TYPE const&length,
            ACCESS_TYPE const&access){
          this->ret    = ret   ;
          this->target = target;
          this->offset = offset;
          this->length = length;
          this->access = access;
        }
        virtual~MapBufferRange(){}
        virtual void operator()(){
          ge::core::convertFrom<void*>(this->ret,glMapBufferRange(
              ge::core::convertTo<GLenum    >(this->target),
              ge::core::convertTo<GLintptr  >(this->offset),
              ge::core::convertTo<GLsizeiptr>(this->length),
              ge::core::convertTo<GLbitfield>(this->access))
          );
        }
    };

    template<
      typename TARGET_TYPE = GLenum    ,
      typename OFFSET_TYPE = GLintptr  ,
      typename LENGTH_TYPE = GLsizeiptr>
    class FlushMappedBufferRange:
        public ge::core::Command{
      public:
        TARGET_TYPE target;
        OFFSET_TYPE offset;
        LENGTH_TYPE length;
        FlushMappedBufferRange(
            TARGET_TYPE const&target,
            OFFSET_TYPE const&offset,
            LENGTH_TYPE const&length){
          this->target = target;
          this->offset = offset;
          this->length = length;
        }
        virtual~FlushMappedBufferRange(){}
        virtual void operator()(){
          glFlushMappedBufferRange(
            ge::core::convertTo<GLenum    >(this->target),
            ge::core::convertTo<GLintptr  >(this->offset),
            ge::core::convertTo<GLsizeiptr>(this->length)
          );
        }
    };

    template<
      typename TARGET_TYPE         = GLenum     ,
      typename INTERNALFORMAT_TYPE = GLenum     ,
      typename OFFSET_TYPE         = GLintptr   ,
      typename SIZE_TYPE           = GLsizeiptr ,
      typename FORMAT_TYPE         = GLenum     ,
      typename TYPE_TYPE           = GLenum     ,
      typename DATA_TYPE           = const void*>
    class ClearBufferSubData:
        public ge::core::Command{
      public:
        TARGET_TYPE         target        ;
        INTERNALFORMAT_TYPE internalformat;
        OFFSET_TYPE         offset        ;
        SIZE_TYPE           size          ;
        FORMAT_TYPE         format        ;
        TYPE_TYPE           type          ;
        DATA_TYPE           data          ;
        ClearBufferSubData(
            TARGET_TYPE         const&target        ,
            INTERNALFORMAT_TYPE const&internalformat,
            OFFSET_TYPE         const&offset        ,
            SIZE_TYPE           const&size          ,
            FORMAT_TYPE         const&format        ,
            TYPE_TYPE           const&type          ,
            DATA_TYPE           const&data          ){
          this->target         = target        ;
          this->internalformat = internalformat;
          this->offset         = offset        ;
          this->size           = size          ;
          this->format         = format        ;
          this->type           = type          ;
          this->data           = data          ;
        }
        virtual~ClearBufferSubData(){}
        virtual void operator()(){
          glClearBufferSubData(
            ge::core::convertTo<GLenum     >(this->target        ),
            ge::core::convertTo<GLenum     >(this->internalformat),
            ge::core::convertTo<GLintptr   >(this->offset        ),
            ge::core::convertTo<GLsizeiptr >(this->size          ),
            ge::core::convertTo<GLenum     >(this->format        ),
            ge::core::convertTo<GLenum     >(this->type          ),
            ge::core::convertTo<const void*>(this->data          )
          );
        }
    };

    template<
      typename TARGET_TYPE = GLenum  ,
      typename PNAME_TYPE  = GLenum  ,
      typename PARAMS_TYPE = GLint64*>
    class GetBufferParameteri64v:
        public ge::core::Command{
      public:
        TARGET_TYPE target;
        PNAME_TYPE  pname ;
        PARAMS_TYPE params;
        GetBufferParameteri64v(
            TARGET_TYPE const&target,
            PNAME_TYPE  const&pname ,
            PARAMS_TYPE const&params){
          this->target = target;
          this->pname  = pname ;
          this->params = params;
        }
        virtual~GetBufferParameteri64v(){}
        virtual void operator()(){
          glGetBufferParameteri64v(
            ge::core::convertTo<GLenum  >(this->target),
            ge::core::convertTo<GLenum  >(this->pname ),
            ge::core::convertTo<GLint64*>(this->params)
          );
        }
    };

    template<
      typename TARGET_TYPE  = GLenum           ,
      typename FIRST_TYPE   = GLuint           ,
      typename COUNT_TYPE   = GLsizei          ,
      typename BUFFERS_TYPE = const GLuint*    ,
      typename OFFSETS_TYPE = const GLintptr*  ,
      typename SIZES_TYPE   = const GLsizeiptr*>
    class BindBuffersRange:
        public ge::core::Command{
      public:
        TARGET_TYPE  target ;
        FIRST_TYPE   first  ;
        COUNT_TYPE   count  ;
        BUFFERS_TYPE buffers;
        OFFSETS_TYPE offsets;
        SIZES_TYPE   sizes  ;
        BindBuffersRange(
            TARGET_TYPE  const&target ,
            FIRST_TYPE   const&first  ,
            COUNT_TYPE   const&count  ,
            BUFFERS_TYPE const&buffers,
            OFFSETS_TYPE const&offsets,
            SIZES_TYPE   const&sizes  ){
          this->target  = target ;
          this->first   = first  ;
          this->count   = count  ;
          this->buffers = buffers;
          this->offsets = offsets;
          this->sizes   = sizes  ;
        }
        virtual~BindBuffersRange(){}
        virtual void operator()(){
          glBindBuffersRange(
            ge::core::convertTo<GLenum           >(this->target ),
            ge::core::convertTo<GLuint           >(this->first  ),
            ge::core::convertTo<GLsizei          >(this->count  ),
            ge::core::convertTo<const GLuint*    >(this->buffers),
            ge::core::convertTo<const GLintptr*  >(this->offsets),
            ge::core::convertTo<const GLsizeiptr*>(this->sizes  )
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
      typename TARGET_TYPE = GLenum     ,
      typename OFFSET_TYPE = GLintptr   ,
      typename SIZE_TYPE   = GLsizeiptr ,
      typename DATA_TYPE   = const void*>
    class BufferSubData:
        public ge::core::Command{
      public:
        TARGET_TYPE target;
        OFFSET_TYPE offset;
        SIZE_TYPE   size  ;
        DATA_TYPE   data  ;
        BufferSubData(
            TARGET_TYPE const&target,
            OFFSET_TYPE const&offset,
            SIZE_TYPE   const&size  ,
            DATA_TYPE   const&data  ){
          this->target = target;
          this->offset = offset;
          this->size   = size  ;
          this->data   = data  ;
        }
        virtual~BufferSubData(){}
        virtual void operator()(){
          glBufferSubData(
            ge::core::convertTo<GLenum     >(this->target),
            ge::core::convertTo<GLintptr   >(this->offset),
            ge::core::convertTo<GLsizeiptr >(this->size  ),
            ge::core::convertTo<const void*>(this->data  )
          );
        }
    };

    template<
      typename VAOBJ_TYPE  = GLuint,
      typename BUFFER_TYPE = GLuint>
    class VertexArrayElementBuffer:
        public ge::core::Command{
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
      typename N_TYPE       = GLsizei,
      typename BUFFERS_TYPE = GLuint*>
    class CreateBuffers:
        public ge::core::Command{
      public:
        N_TYPE       n      ;
        BUFFERS_TYPE buffers;
        CreateBuffers(
            N_TYPE       const&n      ,
            BUFFERS_TYPE const&buffers){
          this->n       = n      ;
          this->buffers = buffers;
        }
        virtual~CreateBuffers(){}
        virtual void operator()(){
          glCreateBuffers(
            ge::core::convertTo<GLsizei>(this->n      ),
            ge::core::convertTo<GLuint*>(this->buffers)
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
      typename TARGET_TYPE  = GLenum       ,
      typename FIRST_TYPE   = GLuint       ,
      typename COUNT_TYPE   = GLsizei      ,
      typename BUFFERS_TYPE = const GLuint*>
    class BindBuffersBase:
        public ge::core::Command{
      public:
        TARGET_TYPE  target ;
        FIRST_TYPE   first  ;
        COUNT_TYPE   count  ;
        BUFFERS_TYPE buffers;
        BindBuffersBase(
            TARGET_TYPE  const&target ,
            FIRST_TYPE   const&first  ,
            COUNT_TYPE   const&count  ,
            BUFFERS_TYPE const&buffers){
          this->target  = target ;
          this->first   = first  ;
          this->count   = count  ;
          this->buffers = buffers;
        }
        virtual~BindBuffersBase(){}
        virtual void operator()(){
          glBindBuffersBase(
            ge::core::convertTo<GLenum       >(this->target ),
            ge::core::convertTo<GLuint       >(this->first  ),
            ge::core::convertTo<GLsizei      >(this->count  ),
            ge::core::convertTo<const GLuint*>(this->buffers)
          );
        }
    };

    template<
      typename N_TYPE       = GLsizei      ,
      typename BUFFERS_TYPE = const GLuint*>
    class DeleteBuffers:
        public ge::core::Command{
      public:
        N_TYPE       n      ;
        BUFFERS_TYPE buffers;
        DeleteBuffers(
            N_TYPE       const&n      ,
            BUFFERS_TYPE const&buffers){
          this->n       = n      ;
          this->buffers = buffers;
        }
        virtual~DeleteBuffers(){}
        virtual void operator()(){
          glDeleteBuffers(
            ge::core::convertTo<GLsizei      >(this->n      ),
            ge::core::convertTo<const GLuint*>(this->buffers)
          );
        }
    };

    template<
      typename BUFFER_TYPE = GLuint,
      typename PNAME_TYPE  = GLenum,
      typename PARAMS_TYPE = GLint*>
    class GetNamedBufferParameteriv:
        public ge::core::Command{
      public:
        BUFFER_TYPE buffer;
        PNAME_TYPE  pname ;
        PARAMS_TYPE params;
        GetNamedBufferParameteriv(
            BUFFER_TYPE const&buffer,
            PNAME_TYPE  const&pname ,
            PARAMS_TYPE const&params){
          this->buffer = buffer;
          this->pname  = pname ;
          this->params = params;
        }
        virtual~GetNamedBufferParameteriv(){}
        virtual void operator()(){
          glGetNamedBufferParameteriv(
            ge::core::convertTo<GLuint>(this->buffer),
            ge::core::convertTo<GLenum>(this->pname ),
            ge::core::convertTo<GLint*>(this->params)
          );
        }
    };

    template<
      typename FRAMEBUFFER_TYPE = GLuint,
      typename SRC_TYPE         = GLenum>
    class NamedFramebufferReadBuffer:
        public ge::core::Command{
      public:
        FRAMEBUFFER_TYPE framebuffer;
        SRC_TYPE         src        ;
        NamedFramebufferReadBuffer(
            FRAMEBUFFER_TYPE const&framebuffer,
            SRC_TYPE         const&src        ){
          this->framebuffer = framebuffer;
          this->src         = src        ;
        }
        virtual~NamedFramebufferReadBuffer(){}
        virtual void operator()(){
          glNamedFramebufferReadBuffer(
            ge::core::convertTo<GLuint>(this->framebuffer),
            ge::core::convertTo<GLenum>(this->src        )
          );
        }
    };

    template<
      typename BUFFER_TYPE = GLuint    ,
      typename OFFSET_TYPE = GLintptr  ,
      typename LENGTH_TYPE = GLsizeiptr>
    class FlushMappedNamedBufferRange:
        public ge::core::Command{
      public:
        BUFFER_TYPE buffer;
        OFFSET_TYPE offset;
        LENGTH_TYPE length;
        FlushMappedNamedBufferRange(
            BUFFER_TYPE const&buffer,
            OFFSET_TYPE const&offset,
            LENGTH_TYPE const&length){
          this->buffer = buffer;
          this->offset = offset;
          this->length = length;
        }
        virtual~FlushMappedNamedBufferRange(){}
        virtual void operator()(){
          glFlushMappedNamedBufferRange(
            ge::core::convertTo<GLuint    >(this->buffer),
            ge::core::convertTo<GLintptr  >(this->offset),
            ge::core::convertTo<GLsizeiptr>(this->length)
          );
        }
    };

    template<
      typename BUFFER_TYPE     = GLenum ,
      typename DRAWBUFFER_TYPE = GLint  ,
      typename DEPTH_TYPE      = GLfloat,
      typename STENCIL_TYPE    = GLint  >
    class ClearBufferfi:
        public ge::core::Command{
      public:
        BUFFER_TYPE     buffer    ;
        DRAWBUFFER_TYPE drawbuffer;
        DEPTH_TYPE      depth     ;
        STENCIL_TYPE    stencil   ;
        ClearBufferfi(
            BUFFER_TYPE     const&buffer    ,
            DRAWBUFFER_TYPE const&drawbuffer,
            DEPTH_TYPE      const&depth     ,
            STENCIL_TYPE    const&stencil   ){
          this->buffer     = buffer    ;
          this->drawbuffer = drawbuffer;
          this->depth      = depth     ;
          this->stencil    = stencil   ;
        }
        virtual~ClearBufferfi(){}
        virtual void operator()(){
          glClearBufferfi(
            ge::core::convertTo<GLenum >(this->buffer    ),
            ge::core::convertTo<GLint  >(this->drawbuffer),
            ge::core::convertTo<GLfloat>(this->depth     ),
            ge::core::convertTo<GLint  >(this->stencil   )
          );
        }
    };

    template<
      typename TEXTURE_TYPE        = GLuint,
      typename INTERNALFORMAT_TYPE = GLenum,
      typename BUFFER_TYPE         = GLuint>
    class TextureBuffer:
        public ge::core::Command{
      public:
        TEXTURE_TYPE        texture       ;
        INTERNALFORMAT_TYPE internalformat;
        BUFFER_TYPE         buffer        ;
        TextureBuffer(
            TEXTURE_TYPE        const&texture       ,
            INTERNALFORMAT_TYPE const&internalformat,
            BUFFER_TYPE         const&buffer        ){
          this->texture        = texture       ;
          this->internalformat = internalformat;
          this->buffer         = buffer        ;
        }
        virtual~TextureBuffer(){}
        virtual void operator()(){
          glTextureBuffer(
            ge::core::convertTo<GLuint>(this->texture       ),
            ge::core::convertTo<GLenum>(this->internalformat),
            ge::core::convertTo<GLuint>(this->buffer        )
          );
        }
    };

    template<
      typename ID_TYPE     = GLuint  ,
      typename BUFFER_TYPE = GLuint  ,
      typename PNAME_TYPE  = GLenum  ,
      typename OFFSET_TYPE = GLintptr>
    class GetQueryBufferObjecti64v:
        public ge::core::Command{
      public:
        ID_TYPE     id    ;
        BUFFER_TYPE buffer;
        PNAME_TYPE  pname ;
        OFFSET_TYPE offset;
        GetQueryBufferObjecti64v(
            ID_TYPE     const&id    ,
            BUFFER_TYPE const&buffer,
            PNAME_TYPE  const&pname ,
            OFFSET_TYPE const&offset){
          this->id     = id    ;
          this->buffer = buffer;
          this->pname  = pname ;
          this->offset = offset;
        }
        virtual~GetQueryBufferObjecti64v(){}
        virtual void operator()(){
          glGetQueryBufferObjecti64v(
            ge::core::convertTo<GLuint  >(this->id    ),
            ge::core::convertTo<GLuint  >(this->buffer),
            ge::core::convertTo<GLenum  >(this->pname ),
            ge::core::convertTo<GLintptr>(this->offset)
          );
        }
    };

    template<
      typename ID_TYPE     = GLuint  ,
      typename BUFFER_TYPE = GLuint  ,
      typename PNAME_TYPE  = GLenum  ,
      typename OFFSET_TYPE = GLintptr>
    class GetQueryBufferObjectui64v:
        public ge::core::Command{
      public:
        ID_TYPE     id    ;
        BUFFER_TYPE buffer;
        PNAME_TYPE  pname ;
        OFFSET_TYPE offset;
        GetQueryBufferObjectui64v(
            ID_TYPE     const&id    ,
            BUFFER_TYPE const&buffer,
            PNAME_TYPE  const&pname ,
            OFFSET_TYPE const&offset){
          this->id     = id    ;
          this->buffer = buffer;
          this->pname  = pname ;
          this->offset = offset;
        }
        virtual~GetQueryBufferObjectui64v(){}
        virtual void operator()(){
          glGetQueryBufferObjectui64v(
            ge::core::convertTo<GLuint  >(this->id    ),
            ge::core::convertTo<GLuint  >(this->buffer),
            ge::core::convertTo<GLenum  >(this->pname ),
            ge::core::convertTo<GLintptr>(this->offset)
          );
        }
    };

    template<
      typename FRAMEBUFFER_TYPE = GLuint       ,
      typename N_TYPE           = GLsizei      ,
      typename BUFS_TYPE        = const GLenum*>
    class NamedFramebufferDrawBuffers:
        public ge::core::Command{
      public:
        FRAMEBUFFER_TYPE framebuffer;
        N_TYPE           n          ;
        BUFS_TYPE        bufs       ;
        NamedFramebufferDrawBuffers(
            FRAMEBUFFER_TYPE const&framebuffer,
            N_TYPE           const&n          ,
            BUFS_TYPE        const&bufs       ){
          this->framebuffer = framebuffer;
          this->n           = n          ;
          this->bufs        = bufs       ;
        }
        virtual~NamedFramebufferDrawBuffers(){}
        virtual void operator()(){
          glNamedFramebufferDrawBuffers(
            ge::core::convertTo<GLuint       >(this->framebuffer),
            ge::core::convertTo<GLsizei      >(this->n          ),
            ge::core::convertTo<const GLenum*>(this->bufs       )
          );
        }
    };

    template<
      typename TARGET_TYPE         = GLenum     ,
      typename INTERNALFORMAT_TYPE = GLenum     ,
      typename FORMAT_TYPE         = GLenum     ,
      typename TYPE_TYPE           = GLenum     ,
      typename DATA_TYPE           = const void*>
    class ClearBufferData:
        public ge::core::Command{
      public:
        TARGET_TYPE         target        ;
        INTERNALFORMAT_TYPE internalformat;
        FORMAT_TYPE         format        ;
        TYPE_TYPE           type          ;
        DATA_TYPE           data          ;
        ClearBufferData(
            TARGET_TYPE         const&target        ,
            INTERNALFORMAT_TYPE const&internalformat,
            FORMAT_TYPE         const&format        ,
            TYPE_TYPE           const&type          ,
            DATA_TYPE           const&data          ){
          this->target         = target        ;
          this->internalformat = internalformat;
          this->format         = format        ;
          this->type           = type          ;
          this->data           = data          ;
        }
        virtual~ClearBufferData(){}
        virtual void operator()(){
          glClearBufferData(
            ge::core::convertTo<GLenum     >(this->target        ),
            ge::core::convertTo<GLenum     >(this->internalformat),
            ge::core::convertTo<GLenum     >(this->format        ),
            ge::core::convertTo<GLenum     >(this->type          ),
            ge::core::convertTo<const void*>(this->data          )
          );
        }
    };

    template<
      typename RET_TYPE    = void* ,
      typename BUFFER_TYPE = GLuint,
      typename ACCESS_TYPE = GLenum>
    class MapNamedBuffer:
        public ge::core::Command{
      public:
        RET_TYPE    ret   ;
        BUFFER_TYPE buffer;
        ACCESS_TYPE access;
        MapNamedBuffer(
            RET_TYPE    const&ret   ,
            BUFFER_TYPE const&buffer,
            ACCESS_TYPE const&access){
          this->ret    = ret   ;
          this->buffer = buffer;
          this->access = access;
        }
        virtual~MapNamedBuffer(){}
        virtual void operator()(){
          ge::core::convertFrom<void*>(this->ret,glMapNamedBuffer(
              ge::core::convertTo<GLuint>(this->buffer),
              ge::core::convertTo<GLenum>(this->access))
          );
        }
    };

    template<
      typename BINDINGINDEX_TYPE = GLuint  ,
      typename BUFFER_TYPE       = GLuint  ,
      typename OFFSET_TYPE       = GLintptr,
      typename STRIDE_TYPE       = GLsizei >
    class BindVertexBuffer:
        public ge::core::Command{
      public:
        BINDINGINDEX_TYPE bindingindex;
        BUFFER_TYPE       buffer      ;
        OFFSET_TYPE       offset      ;
        STRIDE_TYPE       stride      ;
        BindVertexBuffer(
            BINDINGINDEX_TYPE const&bindingindex,
            BUFFER_TYPE       const&buffer      ,
            OFFSET_TYPE       const&offset      ,
            STRIDE_TYPE       const&stride      ){
          this->bindingindex = bindingindex;
          this->buffer       = buffer      ;
          this->offset       = offset      ;
          this->stride       = stride      ;
        }
        virtual~BindVertexBuffer(){}
        virtual void operator()(){
          glBindVertexBuffer(
            ge::core::convertTo<GLuint  >(this->bindingindex),
            ge::core::convertTo<GLuint  >(this->buffer      ),
            ge::core::convertTo<GLintptr>(this->offset      ),
            ge::core::convertTo<GLsizei >(this->stride      )
          );
        }
    };

    template<
      typename TARGET_TYPE = GLenum,
      typename INDEX_TYPE  = GLuint,
      typename BUFFER_TYPE = GLuint>
    class BindBufferBase:
        public ge::core::Command{
      public:
        TARGET_TYPE target;
        INDEX_TYPE  index ;
        BUFFER_TYPE buffer;
        BindBufferBase(
            TARGET_TYPE const&target,
            INDEX_TYPE  const&index ,
            BUFFER_TYPE const&buffer){
          this->target = target;
          this->index  = index ;
          this->buffer = buffer;
        }
        virtual~BindBufferBase(){}
        virtual void operator()(){
          glBindBufferBase(
            ge::core::convertTo<GLenum>(this->target),
            ge::core::convertTo<GLuint>(this->index ),
            ge::core::convertTo<GLuint>(this->buffer)
          );
        }
    };

    template<
      typename TARGET_TYPE = GLenum     ,
      typename SIZE_TYPE   = GLsizeiptr ,
      typename DATA_TYPE   = const void*,
      typename USAGE_TYPE  = GLenum     >
    class BufferData:
        public ge::core::Command{
      public:
        TARGET_TYPE target;
        SIZE_TYPE   size  ;
        DATA_TYPE   data  ;
        USAGE_TYPE  usage ;
        BufferData(
            TARGET_TYPE const&target,
            SIZE_TYPE   const&size  ,
            DATA_TYPE   const&data  ,
            USAGE_TYPE  const&usage ){
          this->target = target;
          this->size   = size  ;
          this->data   = data  ;
          this->usage  = usage ;
        }
        virtual~BufferData(){}
        virtual void operator()(){
          glBufferData(
            ge::core::convertTo<GLenum     >(this->target),
            ge::core::convertTo<GLsizeiptr >(this->size  ),
            ge::core::convertTo<const void*>(this->data  ),
            ge::core::convertTo<GLenum     >(this->usage )
          );
        }
    };

    template<
      typename TARGET_TYPE = GLenum     ,
      typename SIZE_TYPE   = GLsizeiptr ,
      typename DATA_TYPE   = const void*,
      typename FLAGS_TYPE  = GLbitfield >
    class BufferStorage:
        public ge::core::Command{
      public:
        TARGET_TYPE target;
        SIZE_TYPE   size  ;
        DATA_TYPE   data  ;
        FLAGS_TYPE  flags ;
        BufferStorage(
            TARGET_TYPE const&target,
            SIZE_TYPE   const&size  ,
            DATA_TYPE   const&data  ,
            FLAGS_TYPE  const&flags ){
          this->target = target;
          this->size   = size  ;
          this->data   = data  ;
          this->flags  = flags ;
        }
        virtual~BufferStorage(){}
        virtual void operator()(){
          glBufferStorage(
            ge::core::convertTo<GLenum     >(this->target),
            ge::core::convertTo<GLsizeiptr >(this->size  ),
            ge::core::convertTo<const void*>(this->data  ),
            ge::core::convertTo<GLbitfield >(this->flags )
          );
        }
    };

    template<
      typename BUFFER_TYPE = GLuint     ,
      typename SIZE_TYPE   = GLsizeiptr ,
      typename DATA_TYPE   = const void*,
      typename USAGE_TYPE  = GLenum     >
    class NamedBufferData:
        public ge::core::Command{
      public:
        BUFFER_TYPE buffer;
        SIZE_TYPE   size  ;
        DATA_TYPE   data  ;
        USAGE_TYPE  usage ;
        NamedBufferData(
            BUFFER_TYPE const&buffer,
            SIZE_TYPE   const&size  ,
            DATA_TYPE   const&data  ,
            USAGE_TYPE  const&usage ){
          this->buffer = buffer;
          this->size   = size  ;
          this->data   = data  ;
          this->usage  = usage ;
        }
        virtual~NamedBufferData(){}
        virtual void operator()(){
          glNamedBufferData(
            ge::core::convertTo<GLuint     >(this->buffer),
            ge::core::convertTo<GLsizeiptr >(this->size  ),
            ge::core::convertTo<const void*>(this->data  ),
            ge::core::convertTo<GLenum     >(this->usage )
          );
        }
    };

    template<
      typename TARGET_TYPE         = GLenum,
      typename INTERNALFORMAT_TYPE = GLenum,
      typename BUFFER_TYPE         = GLuint>
    class TexBuffer:
        public ge::core::Command{
      public:
        TARGET_TYPE         target        ;
        INTERNALFORMAT_TYPE internalformat;
        BUFFER_TYPE         buffer        ;
        TexBuffer(
            TARGET_TYPE         const&target        ,
            INTERNALFORMAT_TYPE const&internalformat,
            BUFFER_TYPE         const&buffer        ){
          this->target         = target        ;
          this->internalformat = internalformat;
          this->buffer         = buffer        ;
        }
        virtual~TexBuffer(){}
        virtual void operator()(){
          glTexBuffer(
            ge::core::convertTo<GLenum>(this->target        ),
            ge::core::convertTo<GLenum>(this->internalformat),
            ge::core::convertTo<GLuint>(this->buffer        )
          );
        }
    };

    template<
      typename READTARGET_TYPE  = GLenum    ,
      typename WRITETARGET_TYPE = GLenum    ,
      typename READOFFSET_TYPE  = GLintptr  ,
      typename WRITEOFFSET_TYPE = GLintptr  ,
      typename SIZE_TYPE        = GLsizeiptr>
    class CopyBufferSubData:
        public ge::core::Command{
      public:
        READTARGET_TYPE  readTarget ;
        WRITETARGET_TYPE writeTarget;
        READOFFSET_TYPE  readOffset ;
        WRITEOFFSET_TYPE writeOffset;
        SIZE_TYPE        size       ;
        CopyBufferSubData(
            READTARGET_TYPE  const&readTarget ,
            WRITETARGET_TYPE const&writeTarget,
            READOFFSET_TYPE  const&readOffset ,
            WRITEOFFSET_TYPE const&writeOffset,
            SIZE_TYPE        const&size       ){
          this->readTarget  = readTarget ;
          this->writeTarget = writeTarget;
          this->readOffset  = readOffset ;
          this->writeOffset = writeOffset;
          this->size        = size       ;
        }
        virtual~CopyBufferSubData(){}
        virtual void operator()(){
          glCopyBufferSubData(
            ge::core::convertTo<GLenum    >(this->readTarget ),
            ge::core::convertTo<GLenum    >(this->writeTarget),
            ge::core::convertTo<GLintptr  >(this->readOffset ),
            ge::core::convertTo<GLintptr  >(this->writeOffset),
            ge::core::convertTo<GLsizeiptr>(this->size       )
          );
        }
    };

    template<
      typename BUFFER_TYPE = GLuint>
    class InvalidateBufferData:
        public ge::core::Command{
      public:
        BUFFER_TYPE buffer;
        InvalidateBufferData(
            BUFFER_TYPE const&buffer){
          this->buffer = buffer;
        }
        virtual~InvalidateBufferData(){}
        virtual void operator()(){
          glInvalidateBufferData(
            ge::core::convertTo<GLuint>(this->buffer)
          );
        }
    };

    template<
      typename TARGET_TYPE = GLenum    ,
      typename INDEX_TYPE  = GLuint    ,
      typename BUFFER_TYPE = GLuint    ,
      typename OFFSET_TYPE = GLintptr  ,
      typename SIZE_TYPE   = GLsizeiptr>
    class BindBufferRange:
        public ge::core::Command{
      public:
        TARGET_TYPE target;
        INDEX_TYPE  index ;
        BUFFER_TYPE buffer;
        OFFSET_TYPE offset;
        SIZE_TYPE   size  ;
        BindBufferRange(
            TARGET_TYPE const&target,
            INDEX_TYPE  const&index ,
            BUFFER_TYPE const&buffer,
            OFFSET_TYPE const&offset,
            SIZE_TYPE   const&size  ){
          this->target = target;
          this->index  = index ;
          this->buffer = buffer;
          this->offset = offset;
          this->size   = size  ;
        }
        virtual~BindBufferRange(){}
        virtual void operator()(){
          glBindBufferRange(
            ge::core::convertTo<GLenum    >(this->target),
            ge::core::convertTo<GLuint    >(this->index ),
            ge::core::convertTo<GLuint    >(this->buffer),
            ge::core::convertTo<GLintptr  >(this->offset),
            ge::core::convertTo<GLsizeiptr>(this->size  )
          );
        }
    };

    template<
      typename XFB_TYPE    = GLuint,
      typename INDEX_TYPE  = GLuint,
      typename BUFFER_TYPE = GLuint>
    class TransformFeedbackBufferBase:
        public ge::core::Command{
      public:
        XFB_TYPE    xfb   ;
        INDEX_TYPE  index ;
        BUFFER_TYPE buffer;
        TransformFeedbackBufferBase(
            XFB_TYPE    const&xfb   ,
            INDEX_TYPE  const&index ,
            BUFFER_TYPE const&buffer){
          this->xfb    = xfb   ;
          this->index  = index ;
          this->buffer = buffer;
        }
        virtual~TransformFeedbackBufferBase(){}
        virtual void operator()(){
          glTransformFeedbackBufferBase(
            ge::core::convertTo<GLuint>(this->xfb   ),
            ge::core::convertTo<GLuint>(this->index ),
            ge::core::convertTo<GLuint>(this->buffer)
          );
        }
    };

    template<
      typename BUFFER_TYPE         = GLuint     ,
      typename INTERNALFORMAT_TYPE = GLenum     ,
      typename OFFSET_TYPE         = GLintptr   ,
      typename SIZE_TYPE           = GLsizeiptr ,
      typename FORMAT_TYPE         = GLenum     ,
      typename TYPE_TYPE           = GLenum     ,
      typename DATA_TYPE           = const void*>
    class ClearNamedBufferSubData:
        public ge::core::Command{
      public:
        BUFFER_TYPE         buffer        ;
        INTERNALFORMAT_TYPE internalformat;
        OFFSET_TYPE         offset        ;
        SIZE_TYPE           size          ;
        FORMAT_TYPE         format        ;
        TYPE_TYPE           type          ;
        DATA_TYPE           data          ;
        ClearNamedBufferSubData(
            BUFFER_TYPE         const&buffer        ,
            INTERNALFORMAT_TYPE const&internalformat,
            OFFSET_TYPE         const&offset        ,
            SIZE_TYPE           const&size          ,
            FORMAT_TYPE         const&format        ,
            TYPE_TYPE           const&type          ,
            DATA_TYPE           const&data          ){
          this->buffer         = buffer        ;
          this->internalformat = internalformat;
          this->offset         = offset        ;
          this->size           = size          ;
          this->format         = format        ;
          this->type           = type          ;
          this->data           = data          ;
        }
        virtual~ClearNamedBufferSubData(){}
        virtual void operator()(){
          glClearNamedBufferSubData(
            ge::core::convertTo<GLuint     >(this->buffer        ),
            ge::core::convertTo<GLenum     >(this->internalformat),
            ge::core::convertTo<GLintptr   >(this->offset        ),
            ge::core::convertTo<GLsizeiptr >(this->size          ),
            ge::core::convertTo<GLenum     >(this->format        ),
            ge::core::convertTo<GLenum     >(this->type          ),
            ge::core::convertTo<const void*>(this->data          )
          );
        }
    };

    template<
      typename RET_TYPE    = void*     ,
      typename BUFFER_TYPE = GLuint    ,
      typename OFFSET_TYPE = GLintptr  ,
      typename LENGTH_TYPE = GLsizeiptr,
      typename ACCESS_TYPE = GLbitfield>
    class MapNamedBufferRange:
        public ge::core::Command{
      public:
        RET_TYPE    ret   ;
        BUFFER_TYPE buffer;
        OFFSET_TYPE offset;
        LENGTH_TYPE length;
        ACCESS_TYPE access;
        MapNamedBufferRange(
            RET_TYPE    const&ret   ,
            BUFFER_TYPE const&buffer,
            OFFSET_TYPE const&offset,
            LENGTH_TYPE const&length,
            ACCESS_TYPE const&access){
          this->ret    = ret   ;
          this->buffer = buffer;
          this->offset = offset;
          this->length = length;
          this->access = access;
        }
        virtual~MapNamedBufferRange(){}
        virtual void operator()(){
          ge::core::convertFrom<void*>(this->ret,glMapNamedBufferRange(
              ge::core::convertTo<GLuint    >(this->buffer),
              ge::core::convertTo<GLintptr  >(this->offset),
              ge::core::convertTo<GLsizeiptr>(this->length),
              ge::core::convertTo<GLbitfield>(this->access))
          );
        }
    };

    template<
      typename TEXTURE_TYPE        = GLuint    ,
      typename INTERNALFORMAT_TYPE = GLenum    ,
      typename BUFFER_TYPE         = GLuint    ,
      typename OFFSET_TYPE         = GLintptr  ,
      typename SIZE_TYPE           = GLsizeiptr>
    class TextureBufferRange:
        public ge::core::Command{
      public:
        TEXTURE_TYPE        texture       ;
        INTERNALFORMAT_TYPE internalformat;
        BUFFER_TYPE         buffer        ;
        OFFSET_TYPE         offset        ;
        SIZE_TYPE           size          ;
        TextureBufferRange(
            TEXTURE_TYPE        const&texture       ,
            INTERNALFORMAT_TYPE const&internalformat,
            BUFFER_TYPE         const&buffer        ,
            OFFSET_TYPE         const&offset        ,
            SIZE_TYPE           const&size          ){
          this->texture        = texture       ;
          this->internalformat = internalformat;
          this->buffer         = buffer        ;
          this->offset         = offset        ;
          this->size           = size          ;
        }
        virtual~TextureBufferRange(){}
        virtual void operator()(){
          glTextureBufferRange(
            ge::core::convertTo<GLuint    >(this->texture       ),
            ge::core::convertTo<GLenum    >(this->internalformat),
            ge::core::convertTo<GLuint    >(this->buffer        ),
            ge::core::convertTo<GLintptr  >(this->offset        ),
            ge::core::convertTo<GLsizeiptr>(this->size          )
          );
        }
    };

    template<
      typename FRAMEBUFFER_TYPE = GLuint,
      typename BUF_TYPE         = GLenum>
    class NamedFramebufferDrawBuffer:
        public ge::core::Command{
      public:
        FRAMEBUFFER_TYPE framebuffer;
        BUF_TYPE         buf        ;
        NamedFramebufferDrawBuffer(
            FRAMEBUFFER_TYPE const&framebuffer,
            BUF_TYPE         const&buf        ){
          this->framebuffer = framebuffer;
          this->buf         = buf        ;
        }
        virtual~NamedFramebufferDrawBuffer(){}
        virtual void operator()(){
          glNamedFramebufferDrawBuffer(
            ge::core::convertTo<GLuint>(this->framebuffer),
            ge::core::convertTo<GLenum>(this->buf        )
          );
        }
    };

    template<
      typename TARGET_TYPE = GLenum,
      typename PNAME_TYPE  = GLenum,
      typename PARAMS_TYPE = GLint*>
    class GetBufferParameteriv:
        public ge::core::Command{
      public:
        TARGET_TYPE target;
        PNAME_TYPE  pname ;
        PARAMS_TYPE params;
        GetBufferParameteriv(
            TARGET_TYPE const&target,
            PNAME_TYPE  const&pname ,
            PARAMS_TYPE const&params){
          this->target = target;
          this->pname  = pname ;
          this->params = params;
        }
        virtual~GetBufferParameteriv(){}
        virtual void operator()(){
          glGetBufferParameteriv(
            ge::core::convertTo<GLenum>(this->target),
            ge::core::convertTo<GLenum>(this->pname ),
            ge::core::convertTo<GLint*>(this->params)
          );
        }
    };

    template<
      typename TARGET_TYPE         = GLenum    ,
      typename INTERNALFORMAT_TYPE = GLenum    ,
      typename BUFFER_TYPE         = GLuint    ,
      typename OFFSET_TYPE         = GLintptr  ,
      typename SIZE_TYPE           = GLsizeiptr>
    class TexBufferRange:
        public ge::core::Command{
      public:
        TARGET_TYPE         target        ;
        INTERNALFORMAT_TYPE internalformat;
        BUFFER_TYPE         buffer        ;
        OFFSET_TYPE         offset        ;
        SIZE_TYPE           size          ;
        TexBufferRange(
            TARGET_TYPE         const&target        ,
            INTERNALFORMAT_TYPE const&internalformat,
            BUFFER_TYPE         const&buffer        ,
            OFFSET_TYPE         const&offset        ,
            SIZE_TYPE           const&size          ){
          this->target         = target        ;
          this->internalformat = internalformat;
          this->buffer         = buffer        ;
          this->offset         = offset        ;
          this->size           = size          ;
        }
        virtual~TexBufferRange(){}
        virtual void operator()(){
          glTexBufferRange(
            ge::core::convertTo<GLenum    >(this->target        ),
            ge::core::convertTo<GLenum    >(this->internalformat),
            ge::core::convertTo<GLuint    >(this->buffer        ),
            ge::core::convertTo<GLintptr  >(this->offset        ),
            ge::core::convertTo<GLsizeiptr>(this->size          )
          );
        }
    };

    template<
      typename RET_TYPE    = GLboolean,
      typename TARGET_TYPE = GLenum   >
    class UnmapBuffer:
        public ge::core::Command{
      public:
        RET_TYPE    ret   ;
        TARGET_TYPE target;
        UnmapBuffer(
            RET_TYPE    const&ret   ,
            TARGET_TYPE const&target){
          this->ret    = ret   ;
          this->target = target;
        }
        virtual~UnmapBuffer(){}
        virtual void operator()(){
          ge::core::convertFrom<GLboolean>(this->ret,glUnmapBuffer(
              ge::core::convertTo<GLenum   >(this->target))
          );
        }
    };

    template<
      typename RET_TYPE    = void* ,
      typename TARGET_TYPE = GLenum,
      typename ACCESS_TYPE = GLenum>
    class MapBuffer:
        public ge::core::Command{
      public:
        RET_TYPE    ret   ;
        TARGET_TYPE target;
        ACCESS_TYPE access;
        MapBuffer(
            RET_TYPE    const&ret   ,
            TARGET_TYPE const&target,
            ACCESS_TYPE const&access){
          this->ret    = ret   ;
          this->target = target;
          this->access = access;
        }
        virtual~MapBuffer(){}
        virtual void operator()(){
          ge::core::convertFrom<void*>(this->ret,glMapBuffer(
              ge::core::convertTo<GLenum>(this->target),
              ge::core::convertTo<GLenum>(this->access))
          );
        }
    };

    template<
      typename READBUFFER_TYPE  = GLuint    ,
      typename WRITEBUFFER_TYPE = GLuint    ,
      typename READOFFSET_TYPE  = GLintptr  ,
      typename WRITEOFFSET_TYPE = GLintptr  ,
      typename SIZE_TYPE        = GLsizeiptr>
    class CopyNamedBufferSubData:
        public ge::core::Command{
      public:
        READBUFFER_TYPE  readBuffer ;
        WRITEBUFFER_TYPE writeBuffer;
        READOFFSET_TYPE  readOffset ;
        WRITEOFFSET_TYPE writeOffset;
        SIZE_TYPE        size       ;
        CopyNamedBufferSubData(
            READBUFFER_TYPE  const&readBuffer ,
            WRITEBUFFER_TYPE const&writeBuffer,
            READOFFSET_TYPE  const&readOffset ,
            WRITEOFFSET_TYPE const&writeOffset,
            SIZE_TYPE        const&size       ){
          this->readBuffer  = readBuffer ;
          this->writeBuffer = writeBuffer;
          this->readOffset  = readOffset ;
          this->writeOffset = writeOffset;
          this->size        = size       ;
        }
        virtual~CopyNamedBufferSubData(){}
        virtual void operator()(){
          glCopyNamedBufferSubData(
            ge::core::convertTo<GLuint    >(this->readBuffer ),
            ge::core::convertTo<GLuint    >(this->writeBuffer),
            ge::core::convertTo<GLintptr  >(this->readOffset ),
            ge::core::convertTo<GLintptr  >(this->writeOffset),
            ge::core::convertTo<GLsizeiptr>(this->size       )
          );
        }
    };

    template<
      typename BUFFER_TYPE     = GLenum      ,
      typename DRAWBUFFER_TYPE = GLint       ,
      typename VALUE_TYPE      = const GLint*>
    class ClearBufferiv:
        public ge::core::Command{
      public:
        BUFFER_TYPE     buffer    ;
        DRAWBUFFER_TYPE drawbuffer;
        VALUE_TYPE      value     ;
        ClearBufferiv(
            BUFFER_TYPE     const&buffer    ,
            DRAWBUFFER_TYPE const&drawbuffer,
            VALUE_TYPE      const&value     ){
          this->buffer     = buffer    ;
          this->drawbuffer = drawbuffer;
          this->value      = value     ;
        }
        virtual~ClearBufferiv(){}
        virtual void operator()(){
          glClearBufferiv(
            ge::core::convertTo<GLenum      >(this->buffer    ),
            ge::core::convertTo<GLint       >(this->drawbuffer),
            ge::core::convertTo<const GLint*>(this->value     )
          );
        }
    };

    template<
      typename RET_TYPE    = GLboolean,
      typename BUFFER_TYPE = GLuint   >
    class IsBuffer:
        public ge::core::Command{
      public:
        RET_TYPE    ret   ;
        BUFFER_TYPE buffer;
        IsBuffer(
            RET_TYPE    const&ret   ,
            BUFFER_TYPE const&buffer){
          this->ret    = ret   ;
          this->buffer = buffer;
        }
        virtual~IsBuffer(){}
        virtual void operator()(){
          ge::core::convertFrom<GLboolean>(this->ret,glIsBuffer(
              ge::core::convertTo<GLuint   >(this->buffer))
          );
        }
    };

    template<
      typename BUFFER_TYPE = GLuint  ,
      typename PNAME_TYPE  = GLenum  ,
      typename PARAMS_TYPE = GLint64*>
    class GetNamedBufferParameteri64v:
        public ge::core::Command{
      public:
        BUFFER_TYPE buffer;
        PNAME_TYPE  pname ;
        PARAMS_TYPE params;
        GetNamedBufferParameteri64v(
            BUFFER_TYPE const&buffer,
            PNAME_TYPE  const&pname ,
            PARAMS_TYPE const&params){
          this->buffer = buffer;
          this->pname  = pname ;
          this->params = params;
        }
        virtual~GetNamedBufferParameteri64v(){}
        virtual void operator()(){
          glGetNamedBufferParameteri64v(
            ge::core::convertTo<GLuint  >(this->buffer),
            ge::core::convertTo<GLenum  >(this->pname ),
            ge::core::convertTo<GLint64*>(this->params)
          );
        }
    };

    template<
      typename BUFFER_TYPE = GLuint    ,
      typename OFFSET_TYPE = GLintptr  ,
      typename SIZE_TYPE   = GLsizeiptr,
      typename DATA_TYPE   = void*     >
    class GetNamedBufferSubData:
        public ge::core::Command{
      public:
        BUFFER_TYPE buffer;
        OFFSET_TYPE offset;
        SIZE_TYPE   size  ;
        DATA_TYPE   data  ;
        GetNamedBufferSubData(
            BUFFER_TYPE const&buffer,
            OFFSET_TYPE const&offset,
            SIZE_TYPE   const&size  ,
            DATA_TYPE   const&data  ){
          this->buffer = buffer;
          this->offset = offset;
          this->size   = size  ;
          this->data   = data  ;
        }
        virtual~GetNamedBufferSubData(){}
        virtual void operator()(){
          glGetNamedBufferSubData(
            ge::core::convertTo<GLuint    >(this->buffer),
            ge::core::convertTo<GLintptr  >(this->offset),
            ge::core::convertTo<GLsizeiptr>(this->size  ),
            ge::core::convertTo<void*     >(this->data  )
          );
        }
    };

    template<
      typename BUFFER_TYPE = GLuint     ,
      typename OFFSET_TYPE = GLintptr   ,
      typename SIZE_TYPE   = GLsizeiptr ,
      typename DATA_TYPE   = const void*>
    class NamedBufferSubData:
        public ge::core::Command{
      public:
        BUFFER_TYPE buffer;
        OFFSET_TYPE offset;
        SIZE_TYPE   size  ;
        DATA_TYPE   data  ;
        NamedBufferSubData(
            BUFFER_TYPE const&buffer,
            OFFSET_TYPE const&offset,
            SIZE_TYPE   const&size  ,
            DATA_TYPE   const&data  ){
          this->buffer = buffer;
          this->offset = offset;
          this->size   = size  ;
          this->data   = data  ;
        }
        virtual~NamedBufferSubData(){}
        virtual void operator()(){
          glNamedBufferSubData(
            ge::core::convertTo<GLuint     >(this->buffer),
            ge::core::convertTo<GLintptr   >(this->offset),
            ge::core::convertTo<GLsizeiptr >(this->size  ),
            ge::core::convertTo<const void*>(this->data  )
          );
        }
    };

    template<
      typename TARGET_TYPE = GLenum,
      typename BUFFER_TYPE = GLuint>
    class BindBuffer:
        public ge::core::Command{
      public:
        TARGET_TYPE target;
        BUFFER_TYPE buffer;
        BindBuffer(
            TARGET_TYPE const&target,
            BUFFER_TYPE const&buffer){
          this->target = target;
          this->buffer = buffer;
        }
        virtual~BindBuffer(){}
        virtual void operator()(){
          glBindBuffer(
            ge::core::convertTo<GLenum>(this->target),
            ge::core::convertTo<GLuint>(this->buffer)
          );
        }
    };

    template<
      typename BUFFER_TYPE = GLuint    ,
      typename OFFSET_TYPE = GLintptr  ,
      typename LENGTH_TYPE = GLsizeiptr>
    inline InvalidateBufferSubData<
      BUFFER_TYPE,
      OFFSET_TYPE,
      LENGTH_TYPE>* newInvalidateBufferSubData(
        BUFFER_TYPE const&buffer,
        OFFSET_TYPE const&offset,
        LENGTH_TYPE const&length){
        return new InvalidateBufferSubData<
          BUFFER_TYPE,
          OFFSET_TYPE,
          LENGTH_TYPE>(
              buffer,
              offset,
              length);
    }
    template<
      typename ID_TYPE     = GLuint  ,
      typename BUFFER_TYPE = GLuint  ,
      typename PNAME_TYPE  = GLenum  ,
      typename OFFSET_TYPE = GLintptr>
    inline GetQueryBufferObjectiv<
      ID_TYPE    ,
      BUFFER_TYPE,
      PNAME_TYPE ,
      OFFSET_TYPE>* newGetQueryBufferObjectiv(
        ID_TYPE     const&id    ,
        BUFFER_TYPE const&buffer,
        PNAME_TYPE  const&pname ,
        OFFSET_TYPE const&offset){
        return new GetQueryBufferObjectiv<
          ID_TYPE    ,
          BUFFER_TYPE,
          PNAME_TYPE ,
          OFFSET_TYPE>(
              id    ,
              buffer,
              pname ,
              offset);
    }
    template<
      typename BUFFER_TYPE         = GLuint     ,
      typename INTERNALFORMAT_TYPE = GLenum     ,
      typename FORMAT_TYPE         = GLenum     ,
      typename TYPE_TYPE           = GLenum     ,
      typename DATA_TYPE           = const void*>
    inline ClearNamedBufferData<
      BUFFER_TYPE        ,
      INTERNALFORMAT_TYPE,
      FORMAT_TYPE        ,
      TYPE_TYPE          ,
      DATA_TYPE          >* newClearNamedBufferData(
        BUFFER_TYPE         const&buffer        ,
        INTERNALFORMAT_TYPE const&internalformat,
        FORMAT_TYPE         const&format        ,
        TYPE_TYPE           const&type          ,
        DATA_TYPE           const&data          ){
        return new ClearNamedBufferData<
          BUFFER_TYPE        ,
          INTERNALFORMAT_TYPE,
          FORMAT_TYPE        ,
          TYPE_TYPE          ,
          DATA_TYPE          >(
              buffer        ,
              internalformat,
              format        ,
              type          ,
              data          );
    }
    template<
      typename PROGRAM_TYPE     = GLuint,
      typename BUFFERINDEX_TYPE = GLuint,
      typename PNAME_TYPE       = GLenum,
      typename PARAMS_TYPE      = GLint*>
    inline GetActiveAtomicCounterBufferiv<
      PROGRAM_TYPE    ,
      BUFFERINDEX_TYPE,
      PNAME_TYPE      ,
      PARAMS_TYPE     >* newGetActiveAtomicCounterBufferiv(
        PROGRAM_TYPE     const&program    ,
        BUFFERINDEX_TYPE const&bufferIndex,
        PNAME_TYPE       const&pname      ,
        PARAMS_TYPE      const&params     ){
        return new GetActiveAtomicCounterBufferiv<
          PROGRAM_TYPE    ,
          BUFFERINDEX_TYPE,
          PNAME_TYPE      ,
          PARAMS_TYPE     >(
              program    ,
              bufferIndex,
              pname      ,
              params     );
    }
    template<
      typename ID_TYPE     = GLuint  ,
      typename BUFFER_TYPE = GLuint  ,
      typename PNAME_TYPE  = GLenum  ,
      typename OFFSET_TYPE = GLintptr>
    inline GetQueryBufferObjectuiv<
      ID_TYPE    ,
      BUFFER_TYPE,
      PNAME_TYPE ,
      OFFSET_TYPE>* newGetQueryBufferObjectuiv(
        ID_TYPE     const&id    ,
        BUFFER_TYPE const&buffer,
        PNAME_TYPE  const&pname ,
        OFFSET_TYPE const&offset){
        return new GetQueryBufferObjectuiv<
          ID_TYPE    ,
          BUFFER_TYPE,
          PNAME_TYPE ,
          OFFSET_TYPE>(
              id    ,
              buffer,
              pname ,
              offset);
    }
    template<
      typename BUFFER_TYPE = GLuint     ,
      typename SIZE_TYPE   = GLsizeiptr ,
      typename DATA_TYPE   = const void*,
      typename FLAGS_TYPE  = GLbitfield >
    inline NamedBufferStorage<
      BUFFER_TYPE,
      SIZE_TYPE  ,
      DATA_TYPE  ,
      FLAGS_TYPE >* newNamedBufferStorage(
        BUFFER_TYPE const&buffer,
        SIZE_TYPE   const&size  ,
        DATA_TYPE   const&data  ,
        FLAGS_TYPE  const&flags ){
        return new NamedBufferStorage<
          BUFFER_TYPE,
          SIZE_TYPE  ,
          DATA_TYPE  ,
          FLAGS_TYPE >(
              buffer,
              size  ,
              data  ,
              flags );
    }
    template<
      typename BUFFER_TYPE     = GLenum       ,
      typename DRAWBUFFER_TYPE = GLint        ,
      typename VALUE_TYPE      = const GLuint*>
    inline ClearBufferuiv<
      BUFFER_TYPE    ,
      DRAWBUFFER_TYPE,
      VALUE_TYPE     >* newClearBufferuiv(
        BUFFER_TYPE     const&buffer    ,
        DRAWBUFFER_TYPE const&drawbuffer,
        VALUE_TYPE      const&value     ){
        return new ClearBufferuiv<
          BUFFER_TYPE    ,
          DRAWBUFFER_TYPE,
          VALUE_TYPE     >(
              buffer    ,
              drawbuffer,
              value     );
    }
    template<
      typename BUFFER_TYPE     = GLenum        ,
      typename DRAWBUFFER_TYPE = GLint         ,
      typename VALUE_TYPE      = const GLfloat*>
    inline ClearBufferfv<
      BUFFER_TYPE    ,
      DRAWBUFFER_TYPE,
      VALUE_TYPE     >* newClearBufferfv(
        BUFFER_TYPE     const&buffer    ,
        DRAWBUFFER_TYPE const&drawbuffer,
        VALUE_TYPE      const&value     ){
        return new ClearBufferfv<
          BUFFER_TYPE    ,
          DRAWBUFFER_TYPE,
          VALUE_TYPE     >(
              buffer    ,
              drawbuffer,
              value     );
    }
    template<
      typename RET_TYPE    = GLboolean,
      typename BUFFER_TYPE = GLuint   >
    inline UnmapNamedBuffer<
      RET_TYPE   ,
      BUFFER_TYPE>* newUnmapNamedBuffer(
        RET_TYPE    const&ret   ,
        BUFFER_TYPE const&buffer){
        return new UnmapNamedBuffer<
          RET_TYPE   ,
          BUFFER_TYPE>(
              ret   ,
              buffer);
    }
    template<
      typename XFB_TYPE    = GLuint    ,
      typename INDEX_TYPE  = GLuint    ,
      typename BUFFER_TYPE = GLuint    ,
      typename OFFSET_TYPE = GLintptr  ,
      typename SIZE_TYPE   = GLsizeiptr>
    inline TransformFeedbackBufferRange<
      XFB_TYPE   ,
      INDEX_TYPE ,
      BUFFER_TYPE,
      OFFSET_TYPE,
      SIZE_TYPE  >* newTransformFeedbackBufferRange(
        XFB_TYPE    const&xfb   ,
        INDEX_TYPE  const&index ,
        BUFFER_TYPE const&buffer,
        OFFSET_TYPE const&offset,
        SIZE_TYPE   const&size  ){
        return new TransformFeedbackBufferRange<
          XFB_TYPE   ,
          INDEX_TYPE ,
          BUFFER_TYPE,
          OFFSET_TYPE,
          SIZE_TYPE  >(
              xfb   ,
              index ,
              buffer,
              offset,
              size  );
    }
    template<
      typename BUFFER_TYPE = GLuint,
      typename PNAME_TYPE  = GLenum,
      typename PARAMS_TYPE = void**>
    inline GetNamedBufferPointerv<
      BUFFER_TYPE,
      PNAME_TYPE ,
      PARAMS_TYPE>* newGetNamedBufferPointerv(
        BUFFER_TYPE const&buffer,
        PNAME_TYPE  const&pname ,
        PARAMS_TYPE const&params){
        return new GetNamedBufferPointerv<
          BUFFER_TYPE,
          PNAME_TYPE ,
          PARAMS_TYPE>(
              buffer,
              pname ,
              params);
    }
    template<
      typename TARGET_TYPE = GLenum    ,
      typename OFFSET_TYPE = GLintptr  ,
      typename SIZE_TYPE   = GLsizeiptr,
      typename DATA_TYPE   = void*     >
    inline GetBufferSubData<
      TARGET_TYPE,
      OFFSET_TYPE,
      SIZE_TYPE  ,
      DATA_TYPE  >* newGetBufferSubData(
        TARGET_TYPE const&target,
        OFFSET_TYPE const&offset,
        SIZE_TYPE   const&size  ,
        DATA_TYPE   const&data  ){
        return new GetBufferSubData<
          TARGET_TYPE,
          OFFSET_TYPE,
          SIZE_TYPE  ,
          DATA_TYPE  >(
              target,
              offset,
              size  ,
              data  );
    }
    template<
      typename N_TYPE    = GLsizei      ,
      typename BUFS_TYPE = const GLenum*>
    inline DrawBuffers<
      N_TYPE   ,
      BUFS_TYPE>* newDrawBuffers(
        N_TYPE    const&n   ,
        BUFS_TYPE const&bufs){
        return new DrawBuffers<
          N_TYPE   ,
          BUFS_TYPE>(
              n   ,
              bufs);
    }
    template<
      typename TARGET_TYPE = GLenum,
      typename PNAME_TYPE  = GLenum,
      typename PARAMS_TYPE = void**>
    inline GetBufferPointerv<
      TARGET_TYPE,
      PNAME_TYPE ,
      PARAMS_TYPE>* newGetBufferPointerv(
        TARGET_TYPE const&target,
        PNAME_TYPE  const&pname ,
        PARAMS_TYPE const&params){
        return new GetBufferPointerv<
          TARGET_TYPE,
          PNAME_TYPE ,
          PARAMS_TYPE>(
              target,
              pname ,
              params);
    }
    template<
      typename N_TYPE       = GLsizei,
      typename BUFFERS_TYPE = GLuint*>
    inline GenBuffers<
      N_TYPE      ,
      BUFFERS_TYPE>* newGenBuffers(
        N_TYPE       const&n      ,
        BUFFERS_TYPE const&buffers){
        return new GenBuffers<
          N_TYPE      ,
          BUFFERS_TYPE>(
              n      ,
              buffers);
    }
    template<
      typename FIRST_TYPE   = GLuint         ,
      typename COUNT_TYPE   = GLsizei        ,
      typename BUFFERS_TYPE = const GLuint*  ,
      typename OFFSETS_TYPE = const GLintptr*,
      typename STRIDES_TYPE = const GLsizei* >
    inline BindVertexBuffers<
      FIRST_TYPE  ,
      COUNT_TYPE  ,
      BUFFERS_TYPE,
      OFFSETS_TYPE,
      STRIDES_TYPE>* newBindVertexBuffers(
        FIRST_TYPE   const&first  ,
        COUNT_TYPE   const&count  ,
        BUFFERS_TYPE const&buffers,
        OFFSETS_TYPE const&offsets,
        STRIDES_TYPE const&strides){
        return new BindVertexBuffers<
          FIRST_TYPE  ,
          COUNT_TYPE  ,
          BUFFERS_TYPE,
          OFFSETS_TYPE,
          STRIDES_TYPE>(
              first  ,
              count  ,
              buffers,
              offsets,
              strides);
    }
    template<
      typename RET_TYPE    = void*     ,
      typename TARGET_TYPE = GLenum    ,
      typename OFFSET_TYPE = GLintptr  ,
      typename LENGTH_TYPE = GLsizeiptr,
      typename ACCESS_TYPE = GLbitfield>
    inline MapBufferRange<
      RET_TYPE   ,
      TARGET_TYPE,
      OFFSET_TYPE,
      LENGTH_TYPE,
      ACCESS_TYPE>* newMapBufferRange(
        RET_TYPE    const&ret   ,
        TARGET_TYPE const&target,
        OFFSET_TYPE const&offset,
        LENGTH_TYPE const&length,
        ACCESS_TYPE const&access){
        return new MapBufferRange<
          RET_TYPE   ,
          TARGET_TYPE,
          OFFSET_TYPE,
          LENGTH_TYPE,
          ACCESS_TYPE>(
              ret   ,
              target,
              offset,
              length,
              access);
    }
    template<
      typename TARGET_TYPE = GLenum    ,
      typename OFFSET_TYPE = GLintptr  ,
      typename LENGTH_TYPE = GLsizeiptr>
    inline FlushMappedBufferRange<
      TARGET_TYPE,
      OFFSET_TYPE,
      LENGTH_TYPE>* newFlushMappedBufferRange(
        TARGET_TYPE const&target,
        OFFSET_TYPE const&offset,
        LENGTH_TYPE const&length){
        return new FlushMappedBufferRange<
          TARGET_TYPE,
          OFFSET_TYPE,
          LENGTH_TYPE>(
              target,
              offset,
              length);
    }
    template<
      typename TARGET_TYPE         = GLenum     ,
      typename INTERNALFORMAT_TYPE = GLenum     ,
      typename OFFSET_TYPE         = GLintptr   ,
      typename SIZE_TYPE           = GLsizeiptr ,
      typename FORMAT_TYPE         = GLenum     ,
      typename TYPE_TYPE           = GLenum     ,
      typename DATA_TYPE           = const void*>
    inline ClearBufferSubData<
      TARGET_TYPE        ,
      INTERNALFORMAT_TYPE,
      OFFSET_TYPE        ,
      SIZE_TYPE          ,
      FORMAT_TYPE        ,
      TYPE_TYPE          ,
      DATA_TYPE          >* newClearBufferSubData(
        TARGET_TYPE         const&target        ,
        INTERNALFORMAT_TYPE const&internalformat,
        OFFSET_TYPE         const&offset        ,
        SIZE_TYPE           const&size          ,
        FORMAT_TYPE         const&format        ,
        TYPE_TYPE           const&type          ,
        DATA_TYPE           const&data          ){
        return new ClearBufferSubData<
          TARGET_TYPE        ,
          INTERNALFORMAT_TYPE,
          OFFSET_TYPE        ,
          SIZE_TYPE          ,
          FORMAT_TYPE        ,
          TYPE_TYPE          ,
          DATA_TYPE          >(
              target        ,
              internalformat,
              offset        ,
              size          ,
              format        ,
              type          ,
              data          );
    }
    template<
      typename TARGET_TYPE = GLenum  ,
      typename PNAME_TYPE  = GLenum  ,
      typename PARAMS_TYPE = GLint64*>
    inline GetBufferParameteri64v<
      TARGET_TYPE,
      PNAME_TYPE ,
      PARAMS_TYPE>* newGetBufferParameteri64v(
        TARGET_TYPE const&target,
        PNAME_TYPE  const&pname ,
        PARAMS_TYPE const&params){
        return new GetBufferParameteri64v<
          TARGET_TYPE,
          PNAME_TYPE ,
          PARAMS_TYPE>(
              target,
              pname ,
              params);
    }
    template<
      typename TARGET_TYPE  = GLenum           ,
      typename FIRST_TYPE   = GLuint           ,
      typename COUNT_TYPE   = GLsizei          ,
      typename BUFFERS_TYPE = const GLuint*    ,
      typename OFFSETS_TYPE = const GLintptr*  ,
      typename SIZES_TYPE   = const GLsizeiptr*>
    inline BindBuffersRange<
      TARGET_TYPE ,
      FIRST_TYPE  ,
      COUNT_TYPE  ,
      BUFFERS_TYPE,
      OFFSETS_TYPE,
      SIZES_TYPE  >* newBindBuffersRange(
        TARGET_TYPE  const&target ,
        FIRST_TYPE   const&first  ,
        COUNT_TYPE   const&count  ,
        BUFFERS_TYPE const&buffers,
        OFFSETS_TYPE const&offsets,
        SIZES_TYPE   const&sizes  ){
        return new BindBuffersRange<
          TARGET_TYPE ,
          FIRST_TYPE  ,
          COUNT_TYPE  ,
          BUFFERS_TYPE,
          OFFSETS_TYPE,
          SIZES_TYPE  >(
              target ,
              first  ,
              count  ,
              buffers,
              offsets,
              sizes  );
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
      typename TARGET_TYPE = GLenum     ,
      typename OFFSET_TYPE = GLintptr   ,
      typename SIZE_TYPE   = GLsizeiptr ,
      typename DATA_TYPE   = const void*>
    inline BufferSubData<
      TARGET_TYPE,
      OFFSET_TYPE,
      SIZE_TYPE  ,
      DATA_TYPE  >* newBufferSubData(
        TARGET_TYPE const&target,
        OFFSET_TYPE const&offset,
        SIZE_TYPE   const&size  ,
        DATA_TYPE   const&data  ){
        return new BufferSubData<
          TARGET_TYPE,
          OFFSET_TYPE,
          SIZE_TYPE  ,
          DATA_TYPE  >(
              target,
              offset,
              size  ,
              data  );
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
      typename N_TYPE       = GLsizei,
      typename BUFFERS_TYPE = GLuint*>
    inline CreateBuffers<
      N_TYPE      ,
      BUFFERS_TYPE>* newCreateBuffers(
        N_TYPE       const&n      ,
        BUFFERS_TYPE const&buffers){
        return new CreateBuffers<
          N_TYPE      ,
          BUFFERS_TYPE>(
              n      ,
              buffers);
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
      typename TARGET_TYPE  = GLenum       ,
      typename FIRST_TYPE   = GLuint       ,
      typename COUNT_TYPE   = GLsizei      ,
      typename BUFFERS_TYPE = const GLuint*>
    inline BindBuffersBase<
      TARGET_TYPE ,
      FIRST_TYPE  ,
      COUNT_TYPE  ,
      BUFFERS_TYPE>* newBindBuffersBase(
        TARGET_TYPE  const&target ,
        FIRST_TYPE   const&first  ,
        COUNT_TYPE   const&count  ,
        BUFFERS_TYPE const&buffers){
        return new BindBuffersBase<
          TARGET_TYPE ,
          FIRST_TYPE  ,
          COUNT_TYPE  ,
          BUFFERS_TYPE>(
              target ,
              first  ,
              count  ,
              buffers);
    }
    template<
      typename N_TYPE       = GLsizei      ,
      typename BUFFERS_TYPE = const GLuint*>
    inline DeleteBuffers<
      N_TYPE      ,
      BUFFERS_TYPE>* newDeleteBuffers(
        N_TYPE       const&n      ,
        BUFFERS_TYPE const&buffers){
        return new DeleteBuffers<
          N_TYPE      ,
          BUFFERS_TYPE>(
              n      ,
              buffers);
    }
    template<
      typename BUFFER_TYPE = GLuint,
      typename PNAME_TYPE  = GLenum,
      typename PARAMS_TYPE = GLint*>
    inline GetNamedBufferParameteriv<
      BUFFER_TYPE,
      PNAME_TYPE ,
      PARAMS_TYPE>* newGetNamedBufferParameteriv(
        BUFFER_TYPE const&buffer,
        PNAME_TYPE  const&pname ,
        PARAMS_TYPE const&params){
        return new GetNamedBufferParameteriv<
          BUFFER_TYPE,
          PNAME_TYPE ,
          PARAMS_TYPE>(
              buffer,
              pname ,
              params);
    }
    template<
      typename FRAMEBUFFER_TYPE = GLuint,
      typename SRC_TYPE         = GLenum>
    inline NamedFramebufferReadBuffer<
      FRAMEBUFFER_TYPE,
      SRC_TYPE        >* newNamedFramebufferReadBuffer(
        FRAMEBUFFER_TYPE const&framebuffer,
        SRC_TYPE         const&src        ){
        return new NamedFramebufferReadBuffer<
          FRAMEBUFFER_TYPE,
          SRC_TYPE        >(
              framebuffer,
              src        );
    }
    template<
      typename BUFFER_TYPE = GLuint    ,
      typename OFFSET_TYPE = GLintptr  ,
      typename LENGTH_TYPE = GLsizeiptr>
    inline FlushMappedNamedBufferRange<
      BUFFER_TYPE,
      OFFSET_TYPE,
      LENGTH_TYPE>* newFlushMappedNamedBufferRange(
        BUFFER_TYPE const&buffer,
        OFFSET_TYPE const&offset,
        LENGTH_TYPE const&length){
        return new FlushMappedNamedBufferRange<
          BUFFER_TYPE,
          OFFSET_TYPE,
          LENGTH_TYPE>(
              buffer,
              offset,
              length);
    }
    template<
      typename BUFFER_TYPE     = GLenum ,
      typename DRAWBUFFER_TYPE = GLint  ,
      typename DEPTH_TYPE      = GLfloat,
      typename STENCIL_TYPE    = GLint  >
    inline ClearBufferfi<
      BUFFER_TYPE    ,
      DRAWBUFFER_TYPE,
      DEPTH_TYPE     ,
      STENCIL_TYPE   >* newClearBufferfi(
        BUFFER_TYPE     const&buffer    ,
        DRAWBUFFER_TYPE const&drawbuffer,
        DEPTH_TYPE      const&depth     ,
        STENCIL_TYPE    const&stencil   ){
        return new ClearBufferfi<
          BUFFER_TYPE    ,
          DRAWBUFFER_TYPE,
          DEPTH_TYPE     ,
          STENCIL_TYPE   >(
              buffer    ,
              drawbuffer,
              depth     ,
              stencil   );
    }
    template<
      typename TEXTURE_TYPE        = GLuint,
      typename INTERNALFORMAT_TYPE = GLenum,
      typename BUFFER_TYPE         = GLuint>
    inline TextureBuffer<
      TEXTURE_TYPE       ,
      INTERNALFORMAT_TYPE,
      BUFFER_TYPE        >* newTextureBuffer(
        TEXTURE_TYPE        const&texture       ,
        INTERNALFORMAT_TYPE const&internalformat,
        BUFFER_TYPE         const&buffer        ){
        return new TextureBuffer<
          TEXTURE_TYPE       ,
          INTERNALFORMAT_TYPE,
          BUFFER_TYPE        >(
              texture       ,
              internalformat,
              buffer        );
    }
    template<
      typename ID_TYPE     = GLuint  ,
      typename BUFFER_TYPE = GLuint  ,
      typename PNAME_TYPE  = GLenum  ,
      typename OFFSET_TYPE = GLintptr>
    inline GetQueryBufferObjecti64v<
      ID_TYPE    ,
      BUFFER_TYPE,
      PNAME_TYPE ,
      OFFSET_TYPE>* newGetQueryBufferObjecti64v(
        ID_TYPE     const&id    ,
        BUFFER_TYPE const&buffer,
        PNAME_TYPE  const&pname ,
        OFFSET_TYPE const&offset){
        return new GetQueryBufferObjecti64v<
          ID_TYPE    ,
          BUFFER_TYPE,
          PNAME_TYPE ,
          OFFSET_TYPE>(
              id    ,
              buffer,
              pname ,
              offset);
    }
    template<
      typename ID_TYPE     = GLuint  ,
      typename BUFFER_TYPE = GLuint  ,
      typename PNAME_TYPE  = GLenum  ,
      typename OFFSET_TYPE = GLintptr>
    inline GetQueryBufferObjectui64v<
      ID_TYPE    ,
      BUFFER_TYPE,
      PNAME_TYPE ,
      OFFSET_TYPE>* newGetQueryBufferObjectui64v(
        ID_TYPE     const&id    ,
        BUFFER_TYPE const&buffer,
        PNAME_TYPE  const&pname ,
        OFFSET_TYPE const&offset){
        return new GetQueryBufferObjectui64v<
          ID_TYPE    ,
          BUFFER_TYPE,
          PNAME_TYPE ,
          OFFSET_TYPE>(
              id    ,
              buffer,
              pname ,
              offset);
    }
    template<
      typename FRAMEBUFFER_TYPE = GLuint       ,
      typename N_TYPE           = GLsizei      ,
      typename BUFS_TYPE        = const GLenum*>
    inline NamedFramebufferDrawBuffers<
      FRAMEBUFFER_TYPE,
      N_TYPE          ,
      BUFS_TYPE       >* newNamedFramebufferDrawBuffers(
        FRAMEBUFFER_TYPE const&framebuffer,
        N_TYPE           const&n          ,
        BUFS_TYPE        const&bufs       ){
        return new NamedFramebufferDrawBuffers<
          FRAMEBUFFER_TYPE,
          N_TYPE          ,
          BUFS_TYPE       >(
              framebuffer,
              n          ,
              bufs       );
    }
    template<
      typename TARGET_TYPE         = GLenum     ,
      typename INTERNALFORMAT_TYPE = GLenum     ,
      typename FORMAT_TYPE         = GLenum     ,
      typename TYPE_TYPE           = GLenum     ,
      typename DATA_TYPE           = const void*>
    inline ClearBufferData<
      TARGET_TYPE        ,
      INTERNALFORMAT_TYPE,
      FORMAT_TYPE        ,
      TYPE_TYPE          ,
      DATA_TYPE          >* newClearBufferData(
        TARGET_TYPE         const&target        ,
        INTERNALFORMAT_TYPE const&internalformat,
        FORMAT_TYPE         const&format        ,
        TYPE_TYPE           const&type          ,
        DATA_TYPE           const&data          ){
        return new ClearBufferData<
          TARGET_TYPE        ,
          INTERNALFORMAT_TYPE,
          FORMAT_TYPE        ,
          TYPE_TYPE          ,
          DATA_TYPE          >(
              target        ,
              internalformat,
              format        ,
              type          ,
              data          );
    }
    template<
      typename RET_TYPE    = void* ,
      typename BUFFER_TYPE = GLuint,
      typename ACCESS_TYPE = GLenum>
    inline MapNamedBuffer<
      RET_TYPE   ,
      BUFFER_TYPE,
      ACCESS_TYPE>* newMapNamedBuffer(
        RET_TYPE    const&ret   ,
        BUFFER_TYPE const&buffer,
        ACCESS_TYPE const&access){
        return new MapNamedBuffer<
          RET_TYPE   ,
          BUFFER_TYPE,
          ACCESS_TYPE>(
              ret   ,
              buffer,
              access);
    }
    template<
      typename BINDINGINDEX_TYPE = GLuint  ,
      typename BUFFER_TYPE       = GLuint  ,
      typename OFFSET_TYPE       = GLintptr,
      typename STRIDE_TYPE       = GLsizei >
    inline BindVertexBuffer<
      BINDINGINDEX_TYPE,
      BUFFER_TYPE      ,
      OFFSET_TYPE      ,
      STRIDE_TYPE      >* newBindVertexBuffer(
        BINDINGINDEX_TYPE const&bindingindex,
        BUFFER_TYPE       const&buffer      ,
        OFFSET_TYPE       const&offset      ,
        STRIDE_TYPE       const&stride      ){
        return new BindVertexBuffer<
          BINDINGINDEX_TYPE,
          BUFFER_TYPE      ,
          OFFSET_TYPE      ,
          STRIDE_TYPE      >(
              bindingindex,
              buffer      ,
              offset      ,
              stride      );
    }
    template<
      typename TARGET_TYPE = GLenum,
      typename INDEX_TYPE  = GLuint,
      typename BUFFER_TYPE = GLuint>
    inline BindBufferBase<
      TARGET_TYPE,
      INDEX_TYPE ,
      BUFFER_TYPE>* newBindBufferBase(
        TARGET_TYPE const&target,
        INDEX_TYPE  const&index ,
        BUFFER_TYPE const&buffer){
        return new BindBufferBase<
          TARGET_TYPE,
          INDEX_TYPE ,
          BUFFER_TYPE>(
              target,
              index ,
              buffer);
    }
    template<
      typename TARGET_TYPE = GLenum     ,
      typename SIZE_TYPE   = GLsizeiptr ,
      typename DATA_TYPE   = const void*,
      typename USAGE_TYPE  = GLenum     >
    inline BufferData<
      TARGET_TYPE,
      SIZE_TYPE  ,
      DATA_TYPE  ,
      USAGE_TYPE >* newBufferData(
        TARGET_TYPE const&target,
        SIZE_TYPE   const&size  ,
        DATA_TYPE   const&data  ,
        USAGE_TYPE  const&usage ){
        return new BufferData<
          TARGET_TYPE,
          SIZE_TYPE  ,
          DATA_TYPE  ,
          USAGE_TYPE >(
              target,
              size  ,
              data  ,
              usage );
    }
    template<
      typename TARGET_TYPE = GLenum     ,
      typename SIZE_TYPE   = GLsizeiptr ,
      typename DATA_TYPE   = const void*,
      typename FLAGS_TYPE  = GLbitfield >
    inline BufferStorage<
      TARGET_TYPE,
      SIZE_TYPE  ,
      DATA_TYPE  ,
      FLAGS_TYPE >* newBufferStorage(
        TARGET_TYPE const&target,
        SIZE_TYPE   const&size  ,
        DATA_TYPE   const&data  ,
        FLAGS_TYPE  const&flags ){
        return new BufferStorage<
          TARGET_TYPE,
          SIZE_TYPE  ,
          DATA_TYPE  ,
          FLAGS_TYPE >(
              target,
              size  ,
              data  ,
              flags );
    }
    template<
      typename BUFFER_TYPE = GLuint     ,
      typename SIZE_TYPE   = GLsizeiptr ,
      typename DATA_TYPE   = const void*,
      typename USAGE_TYPE  = GLenum     >
    inline NamedBufferData<
      BUFFER_TYPE,
      SIZE_TYPE  ,
      DATA_TYPE  ,
      USAGE_TYPE >* newNamedBufferData(
        BUFFER_TYPE const&buffer,
        SIZE_TYPE   const&size  ,
        DATA_TYPE   const&data  ,
        USAGE_TYPE  const&usage ){
        return new NamedBufferData<
          BUFFER_TYPE,
          SIZE_TYPE  ,
          DATA_TYPE  ,
          USAGE_TYPE >(
              buffer,
              size  ,
              data  ,
              usage );
    }
    template<
      typename TARGET_TYPE         = GLenum,
      typename INTERNALFORMAT_TYPE = GLenum,
      typename BUFFER_TYPE         = GLuint>
    inline TexBuffer<
      TARGET_TYPE        ,
      INTERNALFORMAT_TYPE,
      BUFFER_TYPE        >* newTexBuffer(
        TARGET_TYPE         const&target        ,
        INTERNALFORMAT_TYPE const&internalformat,
        BUFFER_TYPE         const&buffer        ){
        return new TexBuffer<
          TARGET_TYPE        ,
          INTERNALFORMAT_TYPE,
          BUFFER_TYPE        >(
              target        ,
              internalformat,
              buffer        );
    }
    template<
      typename READTARGET_TYPE  = GLenum    ,
      typename WRITETARGET_TYPE = GLenum    ,
      typename READOFFSET_TYPE  = GLintptr  ,
      typename WRITEOFFSET_TYPE = GLintptr  ,
      typename SIZE_TYPE        = GLsizeiptr>
    inline CopyBufferSubData<
      READTARGET_TYPE ,
      WRITETARGET_TYPE,
      READOFFSET_TYPE ,
      WRITEOFFSET_TYPE,
      SIZE_TYPE       >* newCopyBufferSubData(
        READTARGET_TYPE  const&readTarget ,
        WRITETARGET_TYPE const&writeTarget,
        READOFFSET_TYPE  const&readOffset ,
        WRITEOFFSET_TYPE const&writeOffset,
        SIZE_TYPE        const&size       ){
        return new CopyBufferSubData<
          READTARGET_TYPE ,
          WRITETARGET_TYPE,
          READOFFSET_TYPE ,
          WRITEOFFSET_TYPE,
          SIZE_TYPE       >(
              readTarget ,
              writeTarget,
              readOffset ,
              writeOffset,
              size       );
    }
    template<
      typename BUFFER_TYPE = GLuint>
    inline InvalidateBufferData<
      BUFFER_TYPE>* newInvalidateBufferData(
        BUFFER_TYPE const&buffer){
        return new InvalidateBufferData<
          BUFFER_TYPE>(
              buffer);
    }
    template<
      typename TARGET_TYPE = GLenum    ,
      typename INDEX_TYPE  = GLuint    ,
      typename BUFFER_TYPE = GLuint    ,
      typename OFFSET_TYPE = GLintptr  ,
      typename SIZE_TYPE   = GLsizeiptr>
    inline BindBufferRange<
      TARGET_TYPE,
      INDEX_TYPE ,
      BUFFER_TYPE,
      OFFSET_TYPE,
      SIZE_TYPE  >* newBindBufferRange(
        TARGET_TYPE const&target,
        INDEX_TYPE  const&index ,
        BUFFER_TYPE const&buffer,
        OFFSET_TYPE const&offset,
        SIZE_TYPE   const&size  ){
        return new BindBufferRange<
          TARGET_TYPE,
          INDEX_TYPE ,
          BUFFER_TYPE,
          OFFSET_TYPE,
          SIZE_TYPE  >(
              target,
              index ,
              buffer,
              offset,
              size  );
    }
    template<
      typename XFB_TYPE    = GLuint,
      typename INDEX_TYPE  = GLuint,
      typename BUFFER_TYPE = GLuint>
    inline TransformFeedbackBufferBase<
      XFB_TYPE   ,
      INDEX_TYPE ,
      BUFFER_TYPE>* newTransformFeedbackBufferBase(
        XFB_TYPE    const&xfb   ,
        INDEX_TYPE  const&index ,
        BUFFER_TYPE const&buffer){
        return new TransformFeedbackBufferBase<
          XFB_TYPE   ,
          INDEX_TYPE ,
          BUFFER_TYPE>(
              xfb   ,
              index ,
              buffer);
    }
    template<
      typename BUFFER_TYPE         = GLuint     ,
      typename INTERNALFORMAT_TYPE = GLenum     ,
      typename OFFSET_TYPE         = GLintptr   ,
      typename SIZE_TYPE           = GLsizeiptr ,
      typename FORMAT_TYPE         = GLenum     ,
      typename TYPE_TYPE           = GLenum     ,
      typename DATA_TYPE           = const void*>
    inline ClearNamedBufferSubData<
      BUFFER_TYPE        ,
      INTERNALFORMAT_TYPE,
      OFFSET_TYPE        ,
      SIZE_TYPE          ,
      FORMAT_TYPE        ,
      TYPE_TYPE          ,
      DATA_TYPE          >* newClearNamedBufferSubData(
        BUFFER_TYPE         const&buffer        ,
        INTERNALFORMAT_TYPE const&internalformat,
        OFFSET_TYPE         const&offset        ,
        SIZE_TYPE           const&size          ,
        FORMAT_TYPE         const&format        ,
        TYPE_TYPE           const&type          ,
        DATA_TYPE           const&data          ){
        return new ClearNamedBufferSubData<
          BUFFER_TYPE        ,
          INTERNALFORMAT_TYPE,
          OFFSET_TYPE        ,
          SIZE_TYPE          ,
          FORMAT_TYPE        ,
          TYPE_TYPE          ,
          DATA_TYPE          >(
              buffer        ,
              internalformat,
              offset        ,
              size          ,
              format        ,
              type          ,
              data          );
    }
    template<
      typename RET_TYPE    = void*     ,
      typename BUFFER_TYPE = GLuint    ,
      typename OFFSET_TYPE = GLintptr  ,
      typename LENGTH_TYPE = GLsizeiptr,
      typename ACCESS_TYPE = GLbitfield>
    inline MapNamedBufferRange<
      RET_TYPE   ,
      BUFFER_TYPE,
      OFFSET_TYPE,
      LENGTH_TYPE,
      ACCESS_TYPE>* newMapNamedBufferRange(
        RET_TYPE    const&ret   ,
        BUFFER_TYPE const&buffer,
        OFFSET_TYPE const&offset,
        LENGTH_TYPE const&length,
        ACCESS_TYPE const&access){
        return new MapNamedBufferRange<
          RET_TYPE   ,
          BUFFER_TYPE,
          OFFSET_TYPE,
          LENGTH_TYPE,
          ACCESS_TYPE>(
              ret   ,
              buffer,
              offset,
              length,
              access);
    }
    template<
      typename TEXTURE_TYPE        = GLuint    ,
      typename INTERNALFORMAT_TYPE = GLenum    ,
      typename BUFFER_TYPE         = GLuint    ,
      typename OFFSET_TYPE         = GLintptr  ,
      typename SIZE_TYPE           = GLsizeiptr>
    inline TextureBufferRange<
      TEXTURE_TYPE       ,
      INTERNALFORMAT_TYPE,
      BUFFER_TYPE        ,
      OFFSET_TYPE        ,
      SIZE_TYPE          >* newTextureBufferRange(
        TEXTURE_TYPE        const&texture       ,
        INTERNALFORMAT_TYPE const&internalformat,
        BUFFER_TYPE         const&buffer        ,
        OFFSET_TYPE         const&offset        ,
        SIZE_TYPE           const&size          ){
        return new TextureBufferRange<
          TEXTURE_TYPE       ,
          INTERNALFORMAT_TYPE,
          BUFFER_TYPE        ,
          OFFSET_TYPE        ,
          SIZE_TYPE          >(
              texture       ,
              internalformat,
              buffer        ,
              offset        ,
              size          );
    }
    template<
      typename FRAMEBUFFER_TYPE = GLuint,
      typename BUF_TYPE         = GLenum>
    inline NamedFramebufferDrawBuffer<
      FRAMEBUFFER_TYPE,
      BUF_TYPE        >* newNamedFramebufferDrawBuffer(
        FRAMEBUFFER_TYPE const&framebuffer,
        BUF_TYPE         const&buf        ){
        return new NamedFramebufferDrawBuffer<
          FRAMEBUFFER_TYPE,
          BUF_TYPE        >(
              framebuffer,
              buf        );
    }
    template<
      typename TARGET_TYPE = GLenum,
      typename PNAME_TYPE  = GLenum,
      typename PARAMS_TYPE = GLint*>
    inline GetBufferParameteriv<
      TARGET_TYPE,
      PNAME_TYPE ,
      PARAMS_TYPE>* newGetBufferParameteriv(
        TARGET_TYPE const&target,
        PNAME_TYPE  const&pname ,
        PARAMS_TYPE const&params){
        return new GetBufferParameteriv<
          TARGET_TYPE,
          PNAME_TYPE ,
          PARAMS_TYPE>(
              target,
              pname ,
              params);
    }
    template<
      typename TARGET_TYPE         = GLenum    ,
      typename INTERNALFORMAT_TYPE = GLenum    ,
      typename BUFFER_TYPE         = GLuint    ,
      typename OFFSET_TYPE         = GLintptr  ,
      typename SIZE_TYPE           = GLsizeiptr>
    inline TexBufferRange<
      TARGET_TYPE        ,
      INTERNALFORMAT_TYPE,
      BUFFER_TYPE        ,
      OFFSET_TYPE        ,
      SIZE_TYPE          >* newTexBufferRange(
        TARGET_TYPE         const&target        ,
        INTERNALFORMAT_TYPE const&internalformat,
        BUFFER_TYPE         const&buffer        ,
        OFFSET_TYPE         const&offset        ,
        SIZE_TYPE           const&size          ){
        return new TexBufferRange<
          TARGET_TYPE        ,
          INTERNALFORMAT_TYPE,
          BUFFER_TYPE        ,
          OFFSET_TYPE        ,
          SIZE_TYPE          >(
              target        ,
              internalformat,
              buffer        ,
              offset        ,
              size          );
    }
    template<
      typename RET_TYPE    = GLboolean,
      typename TARGET_TYPE = GLenum   >
    inline UnmapBuffer<
      RET_TYPE   ,
      TARGET_TYPE>* newUnmapBuffer(
        RET_TYPE    const&ret   ,
        TARGET_TYPE const&target){
        return new UnmapBuffer<
          RET_TYPE   ,
          TARGET_TYPE>(
              ret   ,
              target);
    }
    template<
      typename RET_TYPE    = void* ,
      typename TARGET_TYPE = GLenum,
      typename ACCESS_TYPE = GLenum>
    inline MapBuffer<
      RET_TYPE   ,
      TARGET_TYPE,
      ACCESS_TYPE>* newMapBuffer(
        RET_TYPE    const&ret   ,
        TARGET_TYPE const&target,
        ACCESS_TYPE const&access){
        return new MapBuffer<
          RET_TYPE   ,
          TARGET_TYPE,
          ACCESS_TYPE>(
              ret   ,
              target,
              access);
    }
    template<
      typename READBUFFER_TYPE  = GLuint    ,
      typename WRITEBUFFER_TYPE = GLuint    ,
      typename READOFFSET_TYPE  = GLintptr  ,
      typename WRITEOFFSET_TYPE = GLintptr  ,
      typename SIZE_TYPE        = GLsizeiptr>
    inline CopyNamedBufferSubData<
      READBUFFER_TYPE ,
      WRITEBUFFER_TYPE,
      READOFFSET_TYPE ,
      WRITEOFFSET_TYPE,
      SIZE_TYPE       >* newCopyNamedBufferSubData(
        READBUFFER_TYPE  const&readBuffer ,
        WRITEBUFFER_TYPE const&writeBuffer,
        READOFFSET_TYPE  const&readOffset ,
        WRITEOFFSET_TYPE const&writeOffset,
        SIZE_TYPE        const&size       ){
        return new CopyNamedBufferSubData<
          READBUFFER_TYPE ,
          WRITEBUFFER_TYPE,
          READOFFSET_TYPE ,
          WRITEOFFSET_TYPE,
          SIZE_TYPE       >(
              readBuffer ,
              writeBuffer,
              readOffset ,
              writeOffset,
              size       );
    }
    template<
      typename BUFFER_TYPE     = GLenum      ,
      typename DRAWBUFFER_TYPE = GLint       ,
      typename VALUE_TYPE      = const GLint*>
    inline ClearBufferiv<
      BUFFER_TYPE    ,
      DRAWBUFFER_TYPE,
      VALUE_TYPE     >* newClearBufferiv(
        BUFFER_TYPE     const&buffer    ,
        DRAWBUFFER_TYPE const&drawbuffer,
        VALUE_TYPE      const&value     ){
        return new ClearBufferiv<
          BUFFER_TYPE    ,
          DRAWBUFFER_TYPE,
          VALUE_TYPE     >(
              buffer    ,
              drawbuffer,
              value     );
    }
    template<
      typename RET_TYPE    = GLboolean,
      typename BUFFER_TYPE = GLuint   >
    inline IsBuffer<
      RET_TYPE   ,
      BUFFER_TYPE>* newIsBuffer(
        RET_TYPE    const&ret   ,
        BUFFER_TYPE const&buffer){
        return new IsBuffer<
          RET_TYPE   ,
          BUFFER_TYPE>(
              ret   ,
              buffer);
    }
    template<
      typename BUFFER_TYPE = GLuint  ,
      typename PNAME_TYPE  = GLenum  ,
      typename PARAMS_TYPE = GLint64*>
    inline GetNamedBufferParameteri64v<
      BUFFER_TYPE,
      PNAME_TYPE ,
      PARAMS_TYPE>* newGetNamedBufferParameteri64v(
        BUFFER_TYPE const&buffer,
        PNAME_TYPE  const&pname ,
        PARAMS_TYPE const&params){
        return new GetNamedBufferParameteri64v<
          BUFFER_TYPE,
          PNAME_TYPE ,
          PARAMS_TYPE>(
              buffer,
              pname ,
              params);
    }
    template<
      typename BUFFER_TYPE = GLuint    ,
      typename OFFSET_TYPE = GLintptr  ,
      typename SIZE_TYPE   = GLsizeiptr,
      typename DATA_TYPE   = void*     >
    inline GetNamedBufferSubData<
      BUFFER_TYPE,
      OFFSET_TYPE,
      SIZE_TYPE  ,
      DATA_TYPE  >* newGetNamedBufferSubData(
        BUFFER_TYPE const&buffer,
        OFFSET_TYPE const&offset,
        SIZE_TYPE   const&size  ,
        DATA_TYPE   const&data  ){
        return new GetNamedBufferSubData<
          BUFFER_TYPE,
          OFFSET_TYPE,
          SIZE_TYPE  ,
          DATA_TYPE  >(
              buffer,
              offset,
              size  ,
              data  );
    }
    template<
      typename BUFFER_TYPE = GLuint     ,
      typename OFFSET_TYPE = GLintptr   ,
      typename SIZE_TYPE   = GLsizeiptr ,
      typename DATA_TYPE   = const void*>
    inline NamedBufferSubData<
      BUFFER_TYPE,
      OFFSET_TYPE,
      SIZE_TYPE  ,
      DATA_TYPE  >* newNamedBufferSubData(
        BUFFER_TYPE const&buffer,
        OFFSET_TYPE const&offset,
        SIZE_TYPE   const&size  ,
        DATA_TYPE   const&data  ){
        return new NamedBufferSubData<
          BUFFER_TYPE,
          OFFSET_TYPE,
          SIZE_TYPE  ,
          DATA_TYPE  >(
              buffer,
              offset,
              size  ,
              data  );
    }
    template<
      typename TARGET_TYPE = GLenum,
      typename BUFFER_TYPE = GLuint>
    inline BindBuffer<
      TARGET_TYPE,
      BUFFER_TYPE>* newBindBuffer(
        TARGET_TYPE const&target,
        BUFFER_TYPE const&buffer){
        return new BindBuffer<
          TARGET_TYPE,
          BUFFER_TYPE>(
              target,
              buffer);
    }
  }
}

