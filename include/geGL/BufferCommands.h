#pragma once

#include<geCore/Command.h>
#include<geGL/Export.h>
#include<GL/glew.h>
#include<geGL/BufferObject.h>
#include<geGL/AllAttribs.h>

namespace ge{
  namespace core{
    template<typename TYPE>
      inline TYPE convertTo(ge::gl::BufferObject*const&bufferObject){
        return bufferObject->getId();
      }
    template<typename TYPE>
      inline TYPE convertTo(std::shared_ptr<ge::gl::BufferObject>const&sharedBufferObject){
        return sharedBufferObject->getId();
      }
  }
}

namespace ge{
  namespace gl{
    template<
      typename BUFFER_TYPE = GLuint    ,
      typename OFFSET_TYPE = GLintptr  ,
      typename LENGTH_TYPE = GLsizeiptr>
    class InvalidateBufferSubData:
        public ge::core::Command,
        public at::Buffer<BUFFER_TYPE>,
        public at::Offset<OFFSET_TYPE>,
        public at::Length<LENGTH_TYPE>{
      public:
        InvalidateBufferSubData(
            BUFFER_TYPE const&buffer,
            OFFSET_TYPE const&offset,
            LENGTH_TYPE const&length):
          at::Buffer<BUFFER_TYPE>(buffer),
          at::Offset<OFFSET_TYPE>(offset),
          at::Length<LENGTH_TYPE>(length){}
        virtual~InvalidateBufferSubData(){}
        virtual void operator()(){
          glInvalidateBufferSubData(
            ge::core::convertTo<GLuint    >(this->at::Buffer<BUFFER_TYPE>::_value),
            ge::core::convertTo<GLintptr  >(this->at::Offset<OFFSET_TYPE>::_value),
            ge::core::convertTo<GLsizeiptr>(this->at::Length<LENGTH_TYPE>::_value)
          );
        }
    };

    template<
      typename ID_TYPE     = GLuint  ,
      typename BUFFER_TYPE = GLuint  ,
      typename PNAME_TYPE  = GLenum  ,
      typename OFFSET_TYPE = GLintptr>
    class GetQueryBufferObjectiv:
        public ge::core::Command,
        public at::Id    <ID_TYPE    >,
        public at::Buffer<BUFFER_TYPE>,
        public at::Pname <PNAME_TYPE >,
        public at::Offset<OFFSET_TYPE>{
      public:
        GetQueryBufferObjectiv(
            ID_TYPE     const&id    ,
            BUFFER_TYPE const&buffer,
            PNAME_TYPE  const&pname ,
            OFFSET_TYPE const&offset):
          at::Id    <ID_TYPE    >(id    ),
          at::Buffer<BUFFER_TYPE>(buffer),
          at::Pname <PNAME_TYPE >(pname ),
          at::Offset<OFFSET_TYPE>(offset){}
        virtual~GetQueryBufferObjectiv(){}
        virtual void operator()(){
          glGetQueryBufferObjectiv(
            ge::core::convertTo<GLuint  >(this->at::Id    <ID_TYPE    >::_value),
            ge::core::convertTo<GLuint  >(this->at::Buffer<BUFFER_TYPE>::_value),
            ge::core::convertTo<GLenum  >(this->at::Pname <PNAME_TYPE >::_value),
            ge::core::convertTo<GLintptr>(this->at::Offset<OFFSET_TYPE>::_value)
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
        public ge::core::Command,
        public at::Buffer        <BUFFER_TYPE        >,
        public at::Internalformat<INTERNALFORMAT_TYPE>,
        public at::Format        <FORMAT_TYPE        >,
        public at::Type          <TYPE_TYPE          >,
        public at::Data          <DATA_TYPE          >{
      public:
        ClearNamedBufferData(
            BUFFER_TYPE         const&buffer        ,
            INTERNALFORMAT_TYPE const&internalformat,
            FORMAT_TYPE         const&format        ,
            TYPE_TYPE           const&type          ,
            DATA_TYPE           const&data          ):
          at::Buffer        <BUFFER_TYPE        >(buffer        ),
          at::Internalformat<INTERNALFORMAT_TYPE>(internalformat),
          at::Format        <FORMAT_TYPE        >(format        ),
          at::Type          <TYPE_TYPE          >(type          ),
          at::Data          <DATA_TYPE          >(data          ){}
        virtual~ClearNamedBufferData(){}
        virtual void operator()(){
          glClearNamedBufferData(
            ge::core::convertTo<GLuint     >(this->at::Buffer        <BUFFER_TYPE        >::_value),
            ge::core::convertTo<GLenum     >(this->at::Internalformat<INTERNALFORMAT_TYPE>::_value),
            ge::core::convertTo<GLenum     >(this->at::Format        <FORMAT_TYPE        >::_value),
            ge::core::convertTo<GLenum     >(this->at::Type          <TYPE_TYPE          >::_value),
            ge::core::convertTo<const void*>(this->at::Data          <DATA_TYPE          >::_value)
          );
        }
    };

    template<
      typename PROGRAM_TYPE     = GLuint,
      typename BUFFERINDEX_TYPE = GLuint,
      typename PNAME_TYPE       = GLenum,
      typename PARAMS_TYPE      = GLint*>
    class GetActiveAtomicCounterBufferiv:
        public ge::core::Command,
        public at::Program    <PROGRAM_TYPE    >,
        public at::BufferIndex<BUFFERINDEX_TYPE>,
        public at::Pname      <PNAME_TYPE      >,
        public at::Params     <PARAMS_TYPE     >{
      public:
        GetActiveAtomicCounterBufferiv(
            PROGRAM_TYPE     const&program    ,
            BUFFERINDEX_TYPE const&bufferIndex,
            PNAME_TYPE       const&pname      ,
            PARAMS_TYPE      const&params     ):
          at::Program    <PROGRAM_TYPE    >(program    ),
          at::BufferIndex<BUFFERINDEX_TYPE>(bufferIndex),
          at::Pname      <PNAME_TYPE      >(pname      ),
          at::Params     <PARAMS_TYPE     >(params     ){}
        virtual~GetActiveAtomicCounterBufferiv(){}
        virtual void operator()(){
          glGetActiveAtomicCounterBufferiv(
            ge::core::convertTo<GLuint>(this->at::Program    <PROGRAM_TYPE    >::_value),
            ge::core::convertTo<GLuint>(this->at::BufferIndex<BUFFERINDEX_TYPE>::_value),
            ge::core::convertTo<GLenum>(this->at::Pname      <PNAME_TYPE      >::_value),
            ge::core::convertTo<GLint*>(this->at::Params     <PARAMS_TYPE     >::_value)
          );
        }
    };

    template<
      typename ID_TYPE     = GLuint  ,
      typename BUFFER_TYPE = GLuint  ,
      typename PNAME_TYPE  = GLenum  ,
      typename OFFSET_TYPE = GLintptr>
    class GetQueryBufferObjectuiv:
        public ge::core::Command,
        public at::Id    <ID_TYPE    >,
        public at::Buffer<BUFFER_TYPE>,
        public at::Pname <PNAME_TYPE >,
        public at::Offset<OFFSET_TYPE>{
      public:
        GetQueryBufferObjectuiv(
            ID_TYPE     const&id    ,
            BUFFER_TYPE const&buffer,
            PNAME_TYPE  const&pname ,
            OFFSET_TYPE const&offset):
          at::Id    <ID_TYPE    >(id    ),
          at::Buffer<BUFFER_TYPE>(buffer),
          at::Pname <PNAME_TYPE >(pname ),
          at::Offset<OFFSET_TYPE>(offset){}
        virtual~GetQueryBufferObjectuiv(){}
        virtual void operator()(){
          glGetQueryBufferObjectuiv(
            ge::core::convertTo<GLuint  >(this->at::Id    <ID_TYPE    >::_value),
            ge::core::convertTo<GLuint  >(this->at::Buffer<BUFFER_TYPE>::_value),
            ge::core::convertTo<GLenum  >(this->at::Pname <PNAME_TYPE >::_value),
            ge::core::convertTo<GLintptr>(this->at::Offset<OFFSET_TYPE>::_value)
          );
        }
    };

    template<
      typename BUFFER_TYPE = GLuint     ,
      typename SIZE_TYPE   = GLsizeiptr ,
      typename DATA_TYPE   = const void*,
      typename FLAGS_TYPE  = GLbitfield >
    class NamedBufferStorage:
        public ge::core::Command,
        public at::Buffer<BUFFER_TYPE>,
        public at::Size  <SIZE_TYPE  >,
        public at::Data  <DATA_TYPE  >,
        public at::Flags <FLAGS_TYPE >{
      public:
        NamedBufferStorage(
            BUFFER_TYPE const&buffer,
            SIZE_TYPE   const&size  ,
            DATA_TYPE   const&data  ,
            FLAGS_TYPE  const&flags ):
          at::Buffer<BUFFER_TYPE>(buffer),
          at::Size  <SIZE_TYPE  >(size  ),
          at::Data  <DATA_TYPE  >(data  ),
          at::Flags <FLAGS_TYPE >(flags ){}
        virtual~NamedBufferStorage(){}
        virtual void operator()(){
          glNamedBufferStorage(
            ge::core::convertTo<GLuint     >(this->at::Buffer<BUFFER_TYPE>::_value),
            ge::core::convertTo<GLsizeiptr >(this->at::Size  <SIZE_TYPE  >::_value),
            ge::core::convertTo<const void*>(this->at::Data  <DATA_TYPE  >::_value),
            ge::core::convertTo<GLbitfield >(this->at::Flags <FLAGS_TYPE >::_value)
          );
        }
    };

    template<
      typename BUFFER_TYPE     = GLenum       ,
      typename DRAWBUFFER_TYPE = GLint        ,
      typename VALUE_TYPE      = const GLuint*>
    class ClearBufferuiv:
        public ge::core::Command,
        public at::Buffer    <BUFFER_TYPE    >,
        public at::Drawbuffer<DRAWBUFFER_TYPE>,
        public at::Value     <VALUE_TYPE     >{
      public:
        ClearBufferuiv(
            BUFFER_TYPE     const&buffer    ,
            DRAWBUFFER_TYPE const&drawbuffer,
            VALUE_TYPE      const&value     ):
          at::Buffer    <BUFFER_TYPE    >(buffer    ),
          at::Drawbuffer<DRAWBUFFER_TYPE>(drawbuffer),
          at::Value     <VALUE_TYPE     >(value     ){}
        virtual~ClearBufferuiv(){}
        virtual void operator()(){
          glClearBufferuiv(
            ge::core::convertTo<GLenum       >(this->at::Buffer    <BUFFER_TYPE    >::_value),
            ge::core::convertTo<GLint        >(this->at::Drawbuffer<DRAWBUFFER_TYPE>::_value),
            ge::core::convertTo<const GLuint*>(this->at::Value     <VALUE_TYPE     >::_value)
          );
        }
    };

    template<
      typename BUFFER_TYPE     = GLenum        ,
      typename DRAWBUFFER_TYPE = GLint         ,
      typename VALUE_TYPE      = const GLfloat*>
    class ClearBufferfv:
        public ge::core::Command,
        public at::Buffer    <BUFFER_TYPE    >,
        public at::Drawbuffer<DRAWBUFFER_TYPE>,
        public at::Value     <VALUE_TYPE     >{
      public:
        ClearBufferfv(
            BUFFER_TYPE     const&buffer    ,
            DRAWBUFFER_TYPE const&drawbuffer,
            VALUE_TYPE      const&value     ):
          at::Buffer    <BUFFER_TYPE    >(buffer    ),
          at::Drawbuffer<DRAWBUFFER_TYPE>(drawbuffer),
          at::Value     <VALUE_TYPE     >(value     ){}
        virtual~ClearBufferfv(){}
        virtual void operator()(){
          glClearBufferfv(
            ge::core::convertTo<GLenum        >(this->at::Buffer    <BUFFER_TYPE    >::_value),
            ge::core::convertTo<GLint         >(this->at::Drawbuffer<DRAWBUFFER_TYPE>::_value),
            ge::core::convertTo<const GLfloat*>(this->at::Value     <VALUE_TYPE     >::_value)
          );
        }
    };

    template<
      typename RET_TYPE    = GLboolean,
      typename BUFFER_TYPE = GLuint   >
    class UnmapNamedBuffer:
        public ge::core::Command,
        public at::Ret   <RET_TYPE   >,
        public at::Buffer<BUFFER_TYPE>{
      public:
        UnmapNamedBuffer(
            RET_TYPE    const&ret   ,
            BUFFER_TYPE const&buffer):
          at::Ret   <RET_TYPE   >(ret   ),
          at::Buffer<BUFFER_TYPE>(buffer){}
        virtual~UnmapNamedBuffer(){}
        virtual void operator()(){
          ge::core::convertFrom<GLboolean>(this->at::Ret<RET_TYPE>::_value,glUnmapNamedBuffer(
              ge::core::convertTo<GLuint   >(this->at::Buffer<BUFFER_TYPE>::_value))
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
        public ge::core::Command,
        public at::Xfb   <XFB_TYPE   >,
        public at::Index <INDEX_TYPE >,
        public at::Buffer<BUFFER_TYPE>,
        public at::Offset<OFFSET_TYPE>,
        public at::Size  <SIZE_TYPE  >{
      public:
        TransformFeedbackBufferRange(
            XFB_TYPE    const&xfb   ,
            INDEX_TYPE  const&index ,
            BUFFER_TYPE const&buffer,
            OFFSET_TYPE const&offset,
            SIZE_TYPE   const&size  ):
          at::Xfb   <XFB_TYPE   >(xfb   ),
          at::Index <INDEX_TYPE >(index ),
          at::Buffer<BUFFER_TYPE>(buffer),
          at::Offset<OFFSET_TYPE>(offset),
          at::Size  <SIZE_TYPE  >(size  ){}
        virtual~TransformFeedbackBufferRange(){}
        virtual void operator()(){
          glTransformFeedbackBufferRange(
            ge::core::convertTo<GLuint    >(this->at::Xfb   <XFB_TYPE   >::_value),
            ge::core::convertTo<GLuint    >(this->at::Index <INDEX_TYPE >::_value),
            ge::core::convertTo<GLuint    >(this->at::Buffer<BUFFER_TYPE>::_value),
            ge::core::convertTo<GLintptr  >(this->at::Offset<OFFSET_TYPE>::_value),
            ge::core::convertTo<GLsizeiptr>(this->at::Size  <SIZE_TYPE  >::_value)
          );
        }
    };

    template<
      typename BUFFER_TYPE = GLuint,
      typename PNAME_TYPE  = GLenum,
      typename PARAMS_TYPE = void**>
    class GetNamedBufferPointerv:
        public ge::core::Command,
        public at::Buffer<BUFFER_TYPE>,
        public at::Pname <PNAME_TYPE >,
        public at::Params<PARAMS_TYPE>{
      public:
        GetNamedBufferPointerv(
            BUFFER_TYPE const&buffer,
            PNAME_TYPE  const&pname ,
            PARAMS_TYPE const&params):
          at::Buffer<BUFFER_TYPE>(buffer),
          at::Pname <PNAME_TYPE >(pname ),
          at::Params<PARAMS_TYPE>(params){}
        virtual~GetNamedBufferPointerv(){}
        virtual void operator()(){
          glGetNamedBufferPointerv(
            ge::core::convertTo<GLuint>(this->at::Buffer<BUFFER_TYPE>::_value),
            ge::core::convertTo<GLenum>(this->at::Pname <PNAME_TYPE >::_value),
            ge::core::convertTo<void**>(this->at::Params<PARAMS_TYPE>::_value)
          );
        }
    };

    template<
      typename TARGET_TYPE = GLenum    ,
      typename OFFSET_TYPE = GLintptr  ,
      typename SIZE_TYPE   = GLsizeiptr,
      typename DATA_TYPE   = void*     >
    class GetBufferSubData:
        public ge::core::Command,
        public at::Target<TARGET_TYPE>,
        public at::Offset<OFFSET_TYPE>,
        public at::Size  <SIZE_TYPE  >,
        public at::Data  <DATA_TYPE  >{
      public:
        GetBufferSubData(
            TARGET_TYPE const&target,
            OFFSET_TYPE const&offset,
            SIZE_TYPE   const&size  ,
            DATA_TYPE   const&data  ):
          at::Target<TARGET_TYPE>(target),
          at::Offset<OFFSET_TYPE>(offset),
          at::Size  <SIZE_TYPE  >(size  ),
          at::Data  <DATA_TYPE  >(data  ){}
        virtual~GetBufferSubData(){}
        virtual void operator()(){
          glGetBufferSubData(
            ge::core::convertTo<GLenum    >(this->at::Target<TARGET_TYPE>::_value),
            ge::core::convertTo<GLintptr  >(this->at::Offset<OFFSET_TYPE>::_value),
            ge::core::convertTo<GLsizeiptr>(this->at::Size  <SIZE_TYPE  >::_value),
            ge::core::convertTo<void*     >(this->at::Data  <DATA_TYPE  >::_value)
          );
        }
    };

    template<
      typename N_TYPE    = GLsizei      ,
      typename BUFS_TYPE = const GLenum*>
    class DrawBuffers:
        public ge::core::Command,
        public at::N   <N_TYPE   >,
        public at::Bufs<BUFS_TYPE>{
      public:
        DrawBuffers(
            N_TYPE    const&n   ,
            BUFS_TYPE const&bufs):
          at::N   <N_TYPE   >(n   ),
          at::Bufs<BUFS_TYPE>(bufs){}
        virtual~DrawBuffers(){}
        virtual void operator()(){
          glDrawBuffers(
            ge::core::convertTo<GLsizei      >(this->at::N   <N_TYPE   >::_value),
            ge::core::convertTo<const GLenum*>(this->at::Bufs<BUFS_TYPE>::_value)
          );
        }
    };

    template<
      typename TARGET_TYPE = GLenum,
      typename PNAME_TYPE  = GLenum,
      typename PARAMS_TYPE = void**>
    class GetBufferPointerv:
        public ge::core::Command,
        public at::Target<TARGET_TYPE>,
        public at::Pname <PNAME_TYPE >,
        public at::Params<PARAMS_TYPE>{
      public:
        GetBufferPointerv(
            TARGET_TYPE const&target,
            PNAME_TYPE  const&pname ,
            PARAMS_TYPE const&params):
          at::Target<TARGET_TYPE>(target),
          at::Pname <PNAME_TYPE >(pname ),
          at::Params<PARAMS_TYPE>(params){}
        virtual~GetBufferPointerv(){}
        virtual void operator()(){
          glGetBufferPointerv(
            ge::core::convertTo<GLenum>(this->at::Target<TARGET_TYPE>::_value),
            ge::core::convertTo<GLenum>(this->at::Pname <PNAME_TYPE >::_value),
            ge::core::convertTo<void**>(this->at::Params<PARAMS_TYPE>::_value)
          );
        }
    };

    template<
      typename N_TYPE       = GLsizei,
      typename BUFFERS_TYPE = GLuint*>
    class GenBuffers:
        public ge::core::Command,
        public at::N      <N_TYPE      >,
        public at::Buffers<BUFFERS_TYPE>{
      public:
        GenBuffers(
            N_TYPE       const&n      ,
            BUFFERS_TYPE const&buffers):
          at::N      <N_TYPE      >(n      ),
          at::Buffers<BUFFERS_TYPE>(buffers){}
        virtual~GenBuffers(){}
        virtual void operator()(){
          glGenBuffers(
            ge::core::convertTo<GLsizei>(this->at::N      <N_TYPE      >::_value),
            ge::core::convertTo<GLuint*>(this->at::Buffers<BUFFERS_TYPE>::_value)
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
        public ge::core::Command,
        public at::First  <FIRST_TYPE  >,
        public at::Count  <COUNT_TYPE  >,
        public at::Buffers<BUFFERS_TYPE>,
        public at::Offsets<OFFSETS_TYPE>,
        public at::Strides<STRIDES_TYPE>{
      public:
        BindVertexBuffers(
            FIRST_TYPE   const&first  ,
            COUNT_TYPE   const&count  ,
            BUFFERS_TYPE const&buffers,
            OFFSETS_TYPE const&offsets,
            STRIDES_TYPE const&strides):
          at::First  <FIRST_TYPE  >(first  ),
          at::Count  <COUNT_TYPE  >(count  ),
          at::Buffers<BUFFERS_TYPE>(buffers),
          at::Offsets<OFFSETS_TYPE>(offsets),
          at::Strides<STRIDES_TYPE>(strides){}
        virtual~BindVertexBuffers(){}
        virtual void operator()(){
          glBindVertexBuffers(
            ge::core::convertTo<GLuint         >(this->at::First  <FIRST_TYPE  >::_value),
            ge::core::convertTo<GLsizei        >(this->at::Count  <COUNT_TYPE  >::_value),
            ge::core::convertTo<const GLuint*  >(this->at::Buffers<BUFFERS_TYPE>::_value),
            ge::core::convertTo<const GLintptr*>(this->at::Offsets<OFFSETS_TYPE>::_value),
            ge::core::convertTo<const GLsizei* >(this->at::Strides<STRIDES_TYPE>::_value)
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
        public ge::core::Command,
        public at::Ret   <RET_TYPE   >,
        public at::Target<TARGET_TYPE>,
        public at::Offset<OFFSET_TYPE>,
        public at::Length<LENGTH_TYPE>,
        public at::Access<ACCESS_TYPE>{
      public:
        MapBufferRange(
            RET_TYPE    const&ret   ,
            TARGET_TYPE const&target,
            OFFSET_TYPE const&offset,
            LENGTH_TYPE const&length,
            ACCESS_TYPE const&access):
          at::Ret   <RET_TYPE   >(ret   ),
          at::Target<TARGET_TYPE>(target),
          at::Offset<OFFSET_TYPE>(offset),
          at::Length<LENGTH_TYPE>(length),
          at::Access<ACCESS_TYPE>(access){}
        virtual~MapBufferRange(){}
        virtual void operator()(){
          ge::core::convertFrom<void*>(this->at::Ret<RET_TYPE>::_value,glMapBufferRange(
              ge::core::convertTo<GLenum    >(this->at::Target<TARGET_TYPE>::_value),
              ge::core::convertTo<GLintptr  >(this->at::Offset<OFFSET_TYPE>::_value),
              ge::core::convertTo<GLsizeiptr>(this->at::Length<LENGTH_TYPE>::_value),
              ge::core::convertTo<GLbitfield>(this->at::Access<ACCESS_TYPE>::_value))
          );
        }
    };

    template<
      typename TARGET_TYPE = GLenum    ,
      typename OFFSET_TYPE = GLintptr  ,
      typename LENGTH_TYPE = GLsizeiptr>
    class FlushMappedBufferRange:
        public ge::core::Command,
        public at::Target<TARGET_TYPE>,
        public at::Offset<OFFSET_TYPE>,
        public at::Length<LENGTH_TYPE>{
      public:
        FlushMappedBufferRange(
            TARGET_TYPE const&target,
            OFFSET_TYPE const&offset,
            LENGTH_TYPE const&length):
          at::Target<TARGET_TYPE>(target),
          at::Offset<OFFSET_TYPE>(offset),
          at::Length<LENGTH_TYPE>(length){}
        virtual~FlushMappedBufferRange(){}
        virtual void operator()(){
          glFlushMappedBufferRange(
            ge::core::convertTo<GLenum    >(this->at::Target<TARGET_TYPE>::_value),
            ge::core::convertTo<GLintptr  >(this->at::Offset<OFFSET_TYPE>::_value),
            ge::core::convertTo<GLsizeiptr>(this->at::Length<LENGTH_TYPE>::_value)
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
        public ge::core::Command,
        public at::Target        <TARGET_TYPE        >,
        public at::Internalformat<INTERNALFORMAT_TYPE>,
        public at::Offset        <OFFSET_TYPE        >,
        public at::Size          <SIZE_TYPE          >,
        public at::Format        <FORMAT_TYPE        >,
        public at::Type          <TYPE_TYPE          >,
        public at::Data          <DATA_TYPE          >{
      public:
        ClearBufferSubData(
            TARGET_TYPE         const&target        ,
            INTERNALFORMAT_TYPE const&internalformat,
            OFFSET_TYPE         const&offset        ,
            SIZE_TYPE           const&size          ,
            FORMAT_TYPE         const&format        ,
            TYPE_TYPE           const&type          ,
            DATA_TYPE           const&data          ):
          at::Target        <TARGET_TYPE        >(target        ),
          at::Internalformat<INTERNALFORMAT_TYPE>(internalformat),
          at::Offset        <OFFSET_TYPE        >(offset        ),
          at::Size          <SIZE_TYPE          >(size          ),
          at::Format        <FORMAT_TYPE        >(format        ),
          at::Type          <TYPE_TYPE          >(type          ),
          at::Data          <DATA_TYPE          >(data          ){}
        virtual~ClearBufferSubData(){}
        virtual void operator()(){
          glClearBufferSubData(
            ge::core::convertTo<GLenum     >(this->at::Target        <TARGET_TYPE        >::_value),
            ge::core::convertTo<GLenum     >(this->at::Internalformat<INTERNALFORMAT_TYPE>::_value),
            ge::core::convertTo<GLintptr   >(this->at::Offset        <OFFSET_TYPE        >::_value),
            ge::core::convertTo<GLsizeiptr >(this->at::Size          <SIZE_TYPE          >::_value),
            ge::core::convertTo<GLenum     >(this->at::Format        <FORMAT_TYPE        >::_value),
            ge::core::convertTo<GLenum     >(this->at::Type          <TYPE_TYPE          >::_value),
            ge::core::convertTo<const void*>(this->at::Data          <DATA_TYPE          >::_value)
          );
        }
    };

    template<
      typename TARGET_TYPE = GLenum  ,
      typename PNAME_TYPE  = GLenum  ,
      typename PARAMS_TYPE = GLint64*>
    class GetBufferParameteri64v:
        public ge::core::Command,
        public at::Target<TARGET_TYPE>,
        public at::Pname <PNAME_TYPE >,
        public at::Params<PARAMS_TYPE>{
      public:
        GetBufferParameteri64v(
            TARGET_TYPE const&target,
            PNAME_TYPE  const&pname ,
            PARAMS_TYPE const&params):
          at::Target<TARGET_TYPE>(target),
          at::Pname <PNAME_TYPE >(pname ),
          at::Params<PARAMS_TYPE>(params){}
        virtual~GetBufferParameteri64v(){}
        virtual void operator()(){
          glGetBufferParameteri64v(
            ge::core::convertTo<GLenum  >(this->at::Target<TARGET_TYPE>::_value),
            ge::core::convertTo<GLenum  >(this->at::Pname <PNAME_TYPE >::_value),
            ge::core::convertTo<GLint64*>(this->at::Params<PARAMS_TYPE>::_value)
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
        public ge::core::Command,
        public at::Target <TARGET_TYPE >,
        public at::First  <FIRST_TYPE  >,
        public at::Count  <COUNT_TYPE  >,
        public at::Buffers<BUFFERS_TYPE>,
        public at::Offsets<OFFSETS_TYPE>,
        public at::Sizes  <SIZES_TYPE  >{
      public:
        BindBuffersRange(
            TARGET_TYPE  const&target ,
            FIRST_TYPE   const&first  ,
            COUNT_TYPE   const&count  ,
            BUFFERS_TYPE const&buffers,
            OFFSETS_TYPE const&offsets,
            SIZES_TYPE   const&sizes  ):
          at::Target <TARGET_TYPE >(target ),
          at::First  <FIRST_TYPE  >(first  ),
          at::Count  <COUNT_TYPE  >(count  ),
          at::Buffers<BUFFERS_TYPE>(buffers),
          at::Offsets<OFFSETS_TYPE>(offsets),
          at::Sizes  <SIZES_TYPE  >(sizes  ){}
        virtual~BindBuffersRange(){}
        virtual void operator()(){
          glBindBuffersRange(
            ge::core::convertTo<GLenum           >(this->at::Target <TARGET_TYPE >::_value),
            ge::core::convertTo<GLuint           >(this->at::First  <FIRST_TYPE  >::_value),
            ge::core::convertTo<GLsizei          >(this->at::Count  <COUNT_TYPE  >::_value),
            ge::core::convertTo<const GLuint*    >(this->at::Buffers<BUFFERS_TYPE>::_value),
            ge::core::convertTo<const GLintptr*  >(this->at::Offsets<OFFSETS_TYPE>::_value),
            ge::core::convertTo<const GLsizeiptr*>(this->at::Sizes  <SIZES_TYPE  >::_value)
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
        public ge::core::Command,
        public at::Vaobj  <VAOBJ_TYPE  >,
        public at::First  <FIRST_TYPE  >,
        public at::Count  <COUNT_TYPE  >,
        public at::Buffers<BUFFERS_TYPE>,
        public at::Offsets<OFFSETS_TYPE>,
        public at::Strides<STRIDES_TYPE>{
      public:
        VertexArrayVertexBuffers(
            VAOBJ_TYPE   const&vaobj  ,
            FIRST_TYPE   const&first  ,
            COUNT_TYPE   const&count  ,
            BUFFERS_TYPE const&buffers,
            OFFSETS_TYPE const&offsets,
            STRIDES_TYPE const&strides):
          at::Vaobj  <VAOBJ_TYPE  >(vaobj  ),
          at::First  <FIRST_TYPE  >(first  ),
          at::Count  <COUNT_TYPE  >(count  ),
          at::Buffers<BUFFERS_TYPE>(buffers),
          at::Offsets<OFFSETS_TYPE>(offsets),
          at::Strides<STRIDES_TYPE>(strides){}
        virtual~VertexArrayVertexBuffers(){}
        virtual void operator()(){
          glVertexArrayVertexBuffers(
            ge::core::convertTo<GLuint         >(this->at::Vaobj  <VAOBJ_TYPE  >::_value),
            ge::core::convertTo<GLuint         >(this->at::First  <FIRST_TYPE  >::_value),
            ge::core::convertTo<GLsizei        >(this->at::Count  <COUNT_TYPE  >::_value),
            ge::core::convertTo<const GLuint*  >(this->at::Buffers<BUFFERS_TYPE>::_value),
            ge::core::convertTo<const GLintptr*>(this->at::Offsets<OFFSETS_TYPE>::_value),
            ge::core::convertTo<const GLsizei* >(this->at::Strides<STRIDES_TYPE>::_value)
          );
        }
    };

    template<
      typename TARGET_TYPE = GLenum     ,
      typename OFFSET_TYPE = GLintptr   ,
      typename SIZE_TYPE   = GLsizeiptr ,
      typename DATA_TYPE   = const void*>
    class BufferSubData:
        public ge::core::Command,
        public at::Target<TARGET_TYPE>,
        public at::Offset<OFFSET_TYPE>,
        public at::Size  <SIZE_TYPE  >,
        public at::Data  <DATA_TYPE  >{
      public:
        BufferSubData(
            TARGET_TYPE const&target,
            OFFSET_TYPE const&offset,
            SIZE_TYPE   const&size  ,
            DATA_TYPE   const&data  ):
          at::Target<TARGET_TYPE>(target),
          at::Offset<OFFSET_TYPE>(offset),
          at::Size  <SIZE_TYPE  >(size  ),
          at::Data  <DATA_TYPE  >(data  ){}
        virtual~BufferSubData(){}
        virtual void operator()(){
          glBufferSubData(
            ge::core::convertTo<GLenum     >(this->at::Target<TARGET_TYPE>::_value),
            ge::core::convertTo<GLintptr   >(this->at::Offset<OFFSET_TYPE>::_value),
            ge::core::convertTo<GLsizeiptr >(this->at::Size  <SIZE_TYPE  >::_value),
            ge::core::convertTo<const void*>(this->at::Data  <DATA_TYPE  >::_value)
          );
        }
    };

    template<
      typename VAOBJ_TYPE  = GLuint,
      typename BUFFER_TYPE = GLuint>
    class VertexArrayElementBuffer:
        public ge::core::Command,
        public at::Vaobj <VAOBJ_TYPE >,
        public at::Buffer<BUFFER_TYPE>{
      public:
        VertexArrayElementBuffer(
            VAOBJ_TYPE  const&vaobj ,
            BUFFER_TYPE const&buffer):
          at::Vaobj <VAOBJ_TYPE >(vaobj ),
          at::Buffer<BUFFER_TYPE>(buffer){}
        virtual~VertexArrayElementBuffer(){}
        virtual void operator()(){
          glVertexArrayElementBuffer(
            ge::core::convertTo<GLuint>(this->at::Vaobj <VAOBJ_TYPE >::_value),
            ge::core::convertTo<GLuint>(this->at::Buffer<BUFFER_TYPE>::_value)
          );
        }
    };

    template<
      typename N_TYPE       = GLsizei,
      typename BUFFERS_TYPE = GLuint*>
    class CreateBuffers:
        public ge::core::Command,
        public at::N      <N_TYPE      >,
        public at::Buffers<BUFFERS_TYPE>{
      public:
        CreateBuffers(
            N_TYPE       const&n      ,
            BUFFERS_TYPE const&buffers):
          at::N      <N_TYPE      >(n      ),
          at::Buffers<BUFFERS_TYPE>(buffers){}
        virtual~CreateBuffers(){}
        virtual void operator()(){
          glCreateBuffers(
            ge::core::convertTo<GLsizei>(this->at::N      <N_TYPE      >::_value),
            ge::core::convertTo<GLuint*>(this->at::Buffers<BUFFERS_TYPE>::_value)
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
        public ge::core::Command,
        public at::Vaobj       <VAOBJ_TYPE       >,
        public at::Bindingindex<BINDINGINDEX_TYPE>,
        public at::Buffer      <BUFFER_TYPE      >,
        public at::Offset      <OFFSET_TYPE      >,
        public at::Stride      <STRIDE_TYPE      >{
      public:
        VertexArrayVertexBuffer(
            VAOBJ_TYPE        const&vaobj       ,
            BINDINGINDEX_TYPE const&bindingindex,
            BUFFER_TYPE       const&buffer      ,
            OFFSET_TYPE       const&offset      ,
            STRIDE_TYPE       const&stride      ):
          at::Vaobj       <VAOBJ_TYPE       >(vaobj       ),
          at::Bindingindex<BINDINGINDEX_TYPE>(bindingindex),
          at::Buffer      <BUFFER_TYPE      >(buffer      ),
          at::Offset      <OFFSET_TYPE      >(offset      ),
          at::Stride      <STRIDE_TYPE      >(stride      ){}
        virtual~VertexArrayVertexBuffer(){}
        virtual void operator()(){
          glVertexArrayVertexBuffer(
            ge::core::convertTo<GLuint  >(this->at::Vaobj       <VAOBJ_TYPE       >::_value),
            ge::core::convertTo<GLuint  >(this->at::Bindingindex<BINDINGINDEX_TYPE>::_value),
            ge::core::convertTo<GLuint  >(this->at::Buffer      <BUFFER_TYPE      >::_value),
            ge::core::convertTo<GLintptr>(this->at::Offset      <OFFSET_TYPE      >::_value),
            ge::core::convertTo<GLsizei >(this->at::Stride      <STRIDE_TYPE      >::_value)
          );
        }
    };

    template<
      typename TARGET_TYPE  = GLenum       ,
      typename FIRST_TYPE   = GLuint       ,
      typename COUNT_TYPE   = GLsizei      ,
      typename BUFFERS_TYPE = const GLuint*>
    class BindBuffersBase:
        public ge::core::Command,
        public at::Target <TARGET_TYPE >,
        public at::First  <FIRST_TYPE  >,
        public at::Count  <COUNT_TYPE  >,
        public at::Buffers<BUFFERS_TYPE>{
      public:
        BindBuffersBase(
            TARGET_TYPE  const&target ,
            FIRST_TYPE   const&first  ,
            COUNT_TYPE   const&count  ,
            BUFFERS_TYPE const&buffers):
          at::Target <TARGET_TYPE >(target ),
          at::First  <FIRST_TYPE  >(first  ),
          at::Count  <COUNT_TYPE  >(count  ),
          at::Buffers<BUFFERS_TYPE>(buffers){}
        virtual~BindBuffersBase(){}
        virtual void operator()(){
          glBindBuffersBase(
            ge::core::convertTo<GLenum       >(this->at::Target <TARGET_TYPE >::_value),
            ge::core::convertTo<GLuint       >(this->at::First  <FIRST_TYPE  >::_value),
            ge::core::convertTo<GLsizei      >(this->at::Count  <COUNT_TYPE  >::_value),
            ge::core::convertTo<const GLuint*>(this->at::Buffers<BUFFERS_TYPE>::_value)
          );
        }
    };

    template<
      typename N_TYPE       = GLsizei      ,
      typename BUFFERS_TYPE = const GLuint*>
    class DeleteBuffers:
        public ge::core::Command,
        public at::N      <N_TYPE      >,
        public at::Buffers<BUFFERS_TYPE>{
      public:
        DeleteBuffers(
            N_TYPE       const&n      ,
            BUFFERS_TYPE const&buffers):
          at::N      <N_TYPE      >(n      ),
          at::Buffers<BUFFERS_TYPE>(buffers){}
        virtual~DeleteBuffers(){}
        virtual void operator()(){
          glDeleteBuffers(
            ge::core::convertTo<GLsizei      >(this->at::N      <N_TYPE      >::_value),
            ge::core::convertTo<const GLuint*>(this->at::Buffers<BUFFERS_TYPE>::_value)
          );
        }
    };

    template<
      typename BUFFER_TYPE = GLuint,
      typename PNAME_TYPE  = GLenum,
      typename PARAMS_TYPE = GLint*>
    class GetNamedBufferParameteriv:
        public ge::core::Command,
        public at::Buffer<BUFFER_TYPE>,
        public at::Pname <PNAME_TYPE >,
        public at::Params<PARAMS_TYPE>{
      public:
        GetNamedBufferParameteriv(
            BUFFER_TYPE const&buffer,
            PNAME_TYPE  const&pname ,
            PARAMS_TYPE const&params):
          at::Buffer<BUFFER_TYPE>(buffer),
          at::Pname <PNAME_TYPE >(pname ),
          at::Params<PARAMS_TYPE>(params){}
        virtual~GetNamedBufferParameteriv(){}
        virtual void operator()(){
          glGetNamedBufferParameteriv(
            ge::core::convertTo<GLuint>(this->at::Buffer<BUFFER_TYPE>::_value),
            ge::core::convertTo<GLenum>(this->at::Pname <PNAME_TYPE >::_value),
            ge::core::convertTo<GLint*>(this->at::Params<PARAMS_TYPE>::_value)
          );
        }
    };

    template<
      typename FRAMEBUFFER_TYPE = GLuint,
      typename SRC_TYPE         = GLenum>
    class NamedFramebufferReadBuffer:
        public ge::core::Command,
        public at::Framebuffer<FRAMEBUFFER_TYPE>,
        public at::Src        <SRC_TYPE        >{
      public:
        NamedFramebufferReadBuffer(
            FRAMEBUFFER_TYPE const&framebuffer,
            SRC_TYPE         const&src        ):
          at::Framebuffer<FRAMEBUFFER_TYPE>(framebuffer),
          at::Src        <SRC_TYPE        >(src        ){}
        virtual~NamedFramebufferReadBuffer(){}
        virtual void operator()(){
          glNamedFramebufferReadBuffer(
            ge::core::convertTo<GLuint>(this->at::Framebuffer<FRAMEBUFFER_TYPE>::_value),
            ge::core::convertTo<GLenum>(this->at::Src        <SRC_TYPE        >::_value)
          );
        }
    };

    template<
      typename BUFFER_TYPE = GLuint    ,
      typename OFFSET_TYPE = GLintptr  ,
      typename LENGTH_TYPE = GLsizeiptr>
    class FlushMappedNamedBufferRange:
        public ge::core::Command,
        public at::Buffer<BUFFER_TYPE>,
        public at::Offset<OFFSET_TYPE>,
        public at::Length<LENGTH_TYPE>{
      public:
        FlushMappedNamedBufferRange(
            BUFFER_TYPE const&buffer,
            OFFSET_TYPE const&offset,
            LENGTH_TYPE const&length):
          at::Buffer<BUFFER_TYPE>(buffer),
          at::Offset<OFFSET_TYPE>(offset),
          at::Length<LENGTH_TYPE>(length){}
        virtual~FlushMappedNamedBufferRange(){}
        virtual void operator()(){
          glFlushMappedNamedBufferRange(
            ge::core::convertTo<GLuint    >(this->at::Buffer<BUFFER_TYPE>::_value),
            ge::core::convertTo<GLintptr  >(this->at::Offset<OFFSET_TYPE>::_value),
            ge::core::convertTo<GLsizeiptr>(this->at::Length<LENGTH_TYPE>::_value)
          );
        }
    };

    template<
      typename BUFFER_TYPE     = GLenum ,
      typename DRAWBUFFER_TYPE = GLint  ,
      typename DEPTH_TYPE      = GLfloat,
      typename STENCIL_TYPE    = GLint  >
    class ClearBufferfi:
        public ge::core::Command,
        public at::Buffer    <BUFFER_TYPE    >,
        public at::Drawbuffer<DRAWBUFFER_TYPE>,
        public at::Depth     <DEPTH_TYPE     >,
        public at::Stencil   <STENCIL_TYPE   >{
      public:
        ClearBufferfi(
            BUFFER_TYPE     const&buffer    ,
            DRAWBUFFER_TYPE const&drawbuffer,
            DEPTH_TYPE      const&depth     ,
            STENCIL_TYPE    const&stencil   ):
          at::Buffer    <BUFFER_TYPE    >(buffer    ),
          at::Drawbuffer<DRAWBUFFER_TYPE>(drawbuffer),
          at::Depth     <DEPTH_TYPE     >(depth     ),
          at::Stencil   <STENCIL_TYPE   >(stencil   ){}
        virtual~ClearBufferfi(){}
        virtual void operator()(){
          glClearBufferfi(
            ge::core::convertTo<GLenum >(this->at::Buffer    <BUFFER_TYPE    >::_value),
            ge::core::convertTo<GLint  >(this->at::Drawbuffer<DRAWBUFFER_TYPE>::_value),
            ge::core::convertTo<GLfloat>(this->at::Depth     <DEPTH_TYPE     >::_value),
            ge::core::convertTo<GLint  >(this->at::Stencil   <STENCIL_TYPE   >::_value)
          );
        }
    };

    template<
      typename TEXTURE_TYPE        = GLuint,
      typename INTERNALFORMAT_TYPE = GLenum,
      typename BUFFER_TYPE         = GLuint>
    class TextureBuffer:
        public ge::core::Command,
        public at::Texture       <TEXTURE_TYPE       >,
        public at::Internalformat<INTERNALFORMAT_TYPE>,
        public at::Buffer        <BUFFER_TYPE        >{
      public:
        TextureBuffer(
            TEXTURE_TYPE        const&texture       ,
            INTERNALFORMAT_TYPE const&internalformat,
            BUFFER_TYPE         const&buffer        ):
          at::Texture       <TEXTURE_TYPE       >(texture       ),
          at::Internalformat<INTERNALFORMAT_TYPE>(internalformat),
          at::Buffer        <BUFFER_TYPE        >(buffer        ){}
        virtual~TextureBuffer(){}
        virtual void operator()(){
          glTextureBuffer(
            ge::core::convertTo<GLuint>(this->at::Texture       <TEXTURE_TYPE       >::_value),
            ge::core::convertTo<GLenum>(this->at::Internalformat<INTERNALFORMAT_TYPE>::_value),
            ge::core::convertTo<GLuint>(this->at::Buffer        <BUFFER_TYPE        >::_value)
          );
        }
    };

    template<
      typename ID_TYPE     = GLuint  ,
      typename BUFFER_TYPE = GLuint  ,
      typename PNAME_TYPE  = GLenum  ,
      typename OFFSET_TYPE = GLintptr>
    class GetQueryBufferObjecti64v:
        public ge::core::Command,
        public at::Id    <ID_TYPE    >,
        public at::Buffer<BUFFER_TYPE>,
        public at::Pname <PNAME_TYPE >,
        public at::Offset<OFFSET_TYPE>{
      public:
        GetQueryBufferObjecti64v(
            ID_TYPE     const&id    ,
            BUFFER_TYPE const&buffer,
            PNAME_TYPE  const&pname ,
            OFFSET_TYPE const&offset):
          at::Id    <ID_TYPE    >(id    ),
          at::Buffer<BUFFER_TYPE>(buffer),
          at::Pname <PNAME_TYPE >(pname ),
          at::Offset<OFFSET_TYPE>(offset){}
        virtual~GetQueryBufferObjecti64v(){}
        virtual void operator()(){
          glGetQueryBufferObjecti64v(
            ge::core::convertTo<GLuint  >(this->at::Id    <ID_TYPE    >::_value),
            ge::core::convertTo<GLuint  >(this->at::Buffer<BUFFER_TYPE>::_value),
            ge::core::convertTo<GLenum  >(this->at::Pname <PNAME_TYPE >::_value),
            ge::core::convertTo<GLintptr>(this->at::Offset<OFFSET_TYPE>::_value)
          );
        }
    };

    template<
      typename ID_TYPE     = GLuint  ,
      typename BUFFER_TYPE = GLuint  ,
      typename PNAME_TYPE  = GLenum  ,
      typename OFFSET_TYPE = GLintptr>
    class GetQueryBufferObjectui64v:
        public ge::core::Command,
        public at::Id    <ID_TYPE    >,
        public at::Buffer<BUFFER_TYPE>,
        public at::Pname <PNAME_TYPE >,
        public at::Offset<OFFSET_TYPE>{
      public:
        GetQueryBufferObjectui64v(
            ID_TYPE     const&id    ,
            BUFFER_TYPE const&buffer,
            PNAME_TYPE  const&pname ,
            OFFSET_TYPE const&offset):
          at::Id    <ID_TYPE    >(id    ),
          at::Buffer<BUFFER_TYPE>(buffer),
          at::Pname <PNAME_TYPE >(pname ),
          at::Offset<OFFSET_TYPE>(offset){}
        virtual~GetQueryBufferObjectui64v(){}
        virtual void operator()(){
          glGetQueryBufferObjectui64v(
            ge::core::convertTo<GLuint  >(this->at::Id    <ID_TYPE    >::_value),
            ge::core::convertTo<GLuint  >(this->at::Buffer<BUFFER_TYPE>::_value),
            ge::core::convertTo<GLenum  >(this->at::Pname <PNAME_TYPE >::_value),
            ge::core::convertTo<GLintptr>(this->at::Offset<OFFSET_TYPE>::_value)
          );
        }
    };

    template<
      typename FRAMEBUFFER_TYPE = GLuint       ,
      typename N_TYPE           = GLsizei      ,
      typename BUFS_TYPE        = const GLenum*>
    class NamedFramebufferDrawBuffers:
        public ge::core::Command,
        public at::Framebuffer<FRAMEBUFFER_TYPE>,
        public at::N          <N_TYPE          >,
        public at::Bufs       <BUFS_TYPE       >{
      public:
        NamedFramebufferDrawBuffers(
            FRAMEBUFFER_TYPE const&framebuffer,
            N_TYPE           const&n          ,
            BUFS_TYPE        const&bufs       ):
          at::Framebuffer<FRAMEBUFFER_TYPE>(framebuffer),
          at::N          <N_TYPE          >(n          ),
          at::Bufs       <BUFS_TYPE       >(bufs       ){}
        virtual~NamedFramebufferDrawBuffers(){}
        virtual void operator()(){
          glNamedFramebufferDrawBuffers(
            ge::core::convertTo<GLuint       >(this->at::Framebuffer<FRAMEBUFFER_TYPE>::_value),
            ge::core::convertTo<GLsizei      >(this->at::N          <N_TYPE          >::_value),
            ge::core::convertTo<const GLenum*>(this->at::Bufs       <BUFS_TYPE       >::_value)
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
        public ge::core::Command,
        public at::Target        <TARGET_TYPE        >,
        public at::Internalformat<INTERNALFORMAT_TYPE>,
        public at::Format        <FORMAT_TYPE        >,
        public at::Type          <TYPE_TYPE          >,
        public at::Data          <DATA_TYPE          >{
      public:
        ClearBufferData(
            TARGET_TYPE         const&target        ,
            INTERNALFORMAT_TYPE const&internalformat,
            FORMAT_TYPE         const&format        ,
            TYPE_TYPE           const&type          ,
            DATA_TYPE           const&data          ):
          at::Target        <TARGET_TYPE        >(target        ),
          at::Internalformat<INTERNALFORMAT_TYPE>(internalformat),
          at::Format        <FORMAT_TYPE        >(format        ),
          at::Type          <TYPE_TYPE          >(type          ),
          at::Data          <DATA_TYPE          >(data          ){}
        virtual~ClearBufferData(){}
        virtual void operator()(){
          glClearBufferData(
            ge::core::convertTo<GLenum     >(this->at::Target        <TARGET_TYPE        >::_value),
            ge::core::convertTo<GLenum     >(this->at::Internalformat<INTERNALFORMAT_TYPE>::_value),
            ge::core::convertTo<GLenum     >(this->at::Format        <FORMAT_TYPE        >::_value),
            ge::core::convertTo<GLenum     >(this->at::Type          <TYPE_TYPE          >::_value),
            ge::core::convertTo<const void*>(this->at::Data          <DATA_TYPE          >::_value)
          );
        }
    };

    template<
      typename RET_TYPE    = void* ,
      typename BUFFER_TYPE = GLuint,
      typename ACCESS_TYPE = GLenum>
    class MapNamedBuffer:
        public ge::core::Command,
        public at::Ret   <RET_TYPE   >,
        public at::Buffer<BUFFER_TYPE>,
        public at::Access<ACCESS_TYPE>{
      public:
        MapNamedBuffer(
            RET_TYPE    const&ret   ,
            BUFFER_TYPE const&buffer,
            ACCESS_TYPE const&access):
          at::Ret   <RET_TYPE   >(ret   ),
          at::Buffer<BUFFER_TYPE>(buffer),
          at::Access<ACCESS_TYPE>(access){}
        virtual~MapNamedBuffer(){}
        virtual void operator()(){
          ge::core::convertFrom<void*>(this->at::Ret<RET_TYPE>::_value,glMapNamedBuffer(
              ge::core::convertTo<GLuint>(this->at::Buffer<BUFFER_TYPE>::_value),
              ge::core::convertTo<GLenum>(this->at::Access<ACCESS_TYPE>::_value))
          );
        }
    };

    template<
      typename BINDINGINDEX_TYPE = GLuint  ,
      typename BUFFER_TYPE       = GLuint  ,
      typename OFFSET_TYPE       = GLintptr,
      typename STRIDE_TYPE       = GLsizei >
    class BindVertexBuffer:
        public ge::core::Command,
        public at::Bindingindex<BINDINGINDEX_TYPE>,
        public at::Buffer      <BUFFER_TYPE      >,
        public at::Offset      <OFFSET_TYPE      >,
        public at::Stride      <STRIDE_TYPE      >{
      public:
        BindVertexBuffer(
            BINDINGINDEX_TYPE const&bindingindex,
            BUFFER_TYPE       const&buffer      ,
            OFFSET_TYPE       const&offset      ,
            STRIDE_TYPE       const&stride      ):
          at::Bindingindex<BINDINGINDEX_TYPE>(bindingindex),
          at::Buffer      <BUFFER_TYPE      >(buffer      ),
          at::Offset      <OFFSET_TYPE      >(offset      ),
          at::Stride      <STRIDE_TYPE      >(stride      ){}
        virtual~BindVertexBuffer(){}
        virtual void operator()(){
          glBindVertexBuffer(
            ge::core::convertTo<GLuint  >(this->at::Bindingindex<BINDINGINDEX_TYPE>::_value),
            ge::core::convertTo<GLuint  >(this->at::Buffer      <BUFFER_TYPE      >::_value),
            ge::core::convertTo<GLintptr>(this->at::Offset      <OFFSET_TYPE      >::_value),
            ge::core::convertTo<GLsizei >(this->at::Stride      <STRIDE_TYPE      >::_value)
          );
        }
    };

    template<
      typename TARGET_TYPE = GLenum,
      typename INDEX_TYPE  = GLuint,
      typename BUFFER_TYPE = GLuint>
    class BindBufferBase:
        public ge::core::Command,
        public at::Target<TARGET_TYPE>,
        public at::Index <INDEX_TYPE >,
        public at::Buffer<BUFFER_TYPE>{
      public:
        BindBufferBase(
            TARGET_TYPE const&target,
            INDEX_TYPE  const&index ,
            BUFFER_TYPE const&buffer):
          at::Target<TARGET_TYPE>(target),
          at::Index <INDEX_TYPE >(index ),
          at::Buffer<BUFFER_TYPE>(buffer){}
        virtual~BindBufferBase(){}
        virtual void operator()(){
          glBindBufferBase(
            ge::core::convertTo<GLenum>(this->at::Target<TARGET_TYPE>::_value),
            ge::core::convertTo<GLuint>(this->at::Index <INDEX_TYPE >::_value),
            ge::core::convertTo<GLuint>(this->at::Buffer<BUFFER_TYPE>::_value)
          );
        }
    };

    template<
      typename TARGET_TYPE = GLenum     ,
      typename SIZE_TYPE   = GLsizeiptr ,
      typename DATA_TYPE   = const void*,
      typename USAGE_TYPE  = GLenum     >
    class BufferData:
        public ge::core::Command,
        public at::Target<TARGET_TYPE>,
        public at::Size  <SIZE_TYPE  >,
        public at::Data  <DATA_TYPE  >,
        public at::Usage <USAGE_TYPE >{
      public:
        BufferData(
            TARGET_TYPE const&target,
            SIZE_TYPE   const&size  ,
            DATA_TYPE   const&data  ,
            USAGE_TYPE  const&usage ):
          at::Target<TARGET_TYPE>(target),
          at::Size  <SIZE_TYPE  >(size  ),
          at::Data  <DATA_TYPE  >(data  ),
          at::Usage <USAGE_TYPE >(usage ){}
        virtual~BufferData(){}
        virtual void operator()(){
          glBufferData(
            ge::core::convertTo<GLenum     >(this->at::Target<TARGET_TYPE>::_value),
            ge::core::convertTo<GLsizeiptr >(this->at::Size  <SIZE_TYPE  >::_value),
            ge::core::convertTo<const void*>(this->at::Data  <DATA_TYPE  >::_value),
            ge::core::convertTo<GLenum     >(this->at::Usage <USAGE_TYPE >::_value)
          );
        }
    };

    template<
      typename TARGET_TYPE = GLenum     ,
      typename SIZE_TYPE   = GLsizeiptr ,
      typename DATA_TYPE   = const void*,
      typename FLAGS_TYPE  = GLbitfield >
    class BufferStorage:
        public ge::core::Command,
        public at::Target<TARGET_TYPE>,
        public at::Size  <SIZE_TYPE  >,
        public at::Data  <DATA_TYPE  >,
        public at::Flags <FLAGS_TYPE >{
      public:
        BufferStorage(
            TARGET_TYPE const&target,
            SIZE_TYPE   const&size  ,
            DATA_TYPE   const&data  ,
            FLAGS_TYPE  const&flags ):
          at::Target<TARGET_TYPE>(target),
          at::Size  <SIZE_TYPE  >(size  ),
          at::Data  <DATA_TYPE  >(data  ),
          at::Flags <FLAGS_TYPE >(flags ){}
        virtual~BufferStorage(){}
        virtual void operator()(){
          glBufferStorage(
            ge::core::convertTo<GLenum     >(this->at::Target<TARGET_TYPE>::_value),
            ge::core::convertTo<GLsizeiptr >(this->at::Size  <SIZE_TYPE  >::_value),
            ge::core::convertTo<const void*>(this->at::Data  <DATA_TYPE  >::_value),
            ge::core::convertTo<GLbitfield >(this->at::Flags <FLAGS_TYPE >::_value)
          );
        }
    };

    template<
      typename BUFFER_TYPE = GLuint     ,
      typename SIZE_TYPE   = GLsizeiptr ,
      typename DATA_TYPE   = const void*,
      typename USAGE_TYPE  = GLenum     >
    class NamedBufferData:
        public ge::core::Command,
        public at::Buffer<BUFFER_TYPE>,
        public at::Size  <SIZE_TYPE  >,
        public at::Data  <DATA_TYPE  >,
        public at::Usage <USAGE_TYPE >{
      public:
        NamedBufferData(
            BUFFER_TYPE const&buffer,
            SIZE_TYPE   const&size  ,
            DATA_TYPE   const&data  ,
            USAGE_TYPE  const&usage ):
          at::Buffer<BUFFER_TYPE>(buffer),
          at::Size  <SIZE_TYPE  >(size  ),
          at::Data  <DATA_TYPE  >(data  ),
          at::Usage <USAGE_TYPE >(usage ){}
        virtual~NamedBufferData(){}
        virtual void operator()(){
          glNamedBufferData(
            ge::core::convertTo<GLuint     >(this->at::Buffer<BUFFER_TYPE>::_value),
            ge::core::convertTo<GLsizeiptr >(this->at::Size  <SIZE_TYPE  >::_value),
            ge::core::convertTo<const void*>(this->at::Data  <DATA_TYPE  >::_value),
            ge::core::convertTo<GLenum     >(this->at::Usage <USAGE_TYPE >::_value)
          );
        }
    };

    template<
      typename TARGET_TYPE         = GLenum,
      typename INTERNALFORMAT_TYPE = GLenum,
      typename BUFFER_TYPE         = GLuint>
    class TexBuffer:
        public ge::core::Command,
        public at::Target        <TARGET_TYPE        >,
        public at::Internalformat<INTERNALFORMAT_TYPE>,
        public at::Buffer        <BUFFER_TYPE        >{
      public:
        TexBuffer(
            TARGET_TYPE         const&target        ,
            INTERNALFORMAT_TYPE const&internalformat,
            BUFFER_TYPE         const&buffer        ):
          at::Target        <TARGET_TYPE        >(target        ),
          at::Internalformat<INTERNALFORMAT_TYPE>(internalformat),
          at::Buffer        <BUFFER_TYPE        >(buffer        ){}
        virtual~TexBuffer(){}
        virtual void operator()(){
          glTexBuffer(
            ge::core::convertTo<GLenum>(this->at::Target        <TARGET_TYPE        >::_value),
            ge::core::convertTo<GLenum>(this->at::Internalformat<INTERNALFORMAT_TYPE>::_value),
            ge::core::convertTo<GLuint>(this->at::Buffer        <BUFFER_TYPE        >::_value)
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
        public ge::core::Command,
        public at::ReadTarget <READTARGET_TYPE >,
        public at::WriteTarget<WRITETARGET_TYPE>,
        public at::ReadOffset <READOFFSET_TYPE >,
        public at::WriteOffset<WRITEOFFSET_TYPE>,
        public at::Size       <SIZE_TYPE       >{
      public:
        CopyBufferSubData(
            READTARGET_TYPE  const&readTarget ,
            WRITETARGET_TYPE const&writeTarget,
            READOFFSET_TYPE  const&readOffset ,
            WRITEOFFSET_TYPE const&writeOffset,
            SIZE_TYPE        const&size       ):
          at::ReadTarget <READTARGET_TYPE >(readTarget ),
          at::WriteTarget<WRITETARGET_TYPE>(writeTarget),
          at::ReadOffset <READOFFSET_TYPE >(readOffset ),
          at::WriteOffset<WRITEOFFSET_TYPE>(writeOffset),
          at::Size       <SIZE_TYPE       >(size       ){}
        virtual~CopyBufferSubData(){}
        virtual void operator()(){
          glCopyBufferSubData(
            ge::core::convertTo<GLenum    >(this->at::ReadTarget <READTARGET_TYPE >::_value),
            ge::core::convertTo<GLenum    >(this->at::WriteTarget<WRITETARGET_TYPE>::_value),
            ge::core::convertTo<GLintptr  >(this->at::ReadOffset <READOFFSET_TYPE >::_value),
            ge::core::convertTo<GLintptr  >(this->at::WriteOffset<WRITEOFFSET_TYPE>::_value),
            ge::core::convertTo<GLsizeiptr>(this->at::Size       <SIZE_TYPE       >::_value)
          );
        }
    };

    template<
      typename BUFFER_TYPE = GLuint>
    class InvalidateBufferData:
        public ge::core::Command,
        public at::Buffer<BUFFER_TYPE>{
      public:
        InvalidateBufferData(
            BUFFER_TYPE const&buffer):
          at::Buffer<BUFFER_TYPE>(buffer){}
        virtual~InvalidateBufferData(){}
        virtual void operator()(){
          glInvalidateBufferData(
            ge::core::convertTo<GLuint>(this->at::Buffer<BUFFER_TYPE>::_value)
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
        public ge::core::Command,
        public at::Target<TARGET_TYPE>,
        public at::Index <INDEX_TYPE >,
        public at::Buffer<BUFFER_TYPE>,
        public at::Offset<OFFSET_TYPE>,
        public at::Size  <SIZE_TYPE  >{
      public:
        BindBufferRange(
            TARGET_TYPE const&target,
            INDEX_TYPE  const&index ,
            BUFFER_TYPE const&buffer,
            OFFSET_TYPE const&offset,
            SIZE_TYPE   const&size  ):
          at::Target<TARGET_TYPE>(target),
          at::Index <INDEX_TYPE >(index ),
          at::Buffer<BUFFER_TYPE>(buffer),
          at::Offset<OFFSET_TYPE>(offset),
          at::Size  <SIZE_TYPE  >(size  ){}
        virtual~BindBufferRange(){}
        virtual void operator()(){
          glBindBufferRange(
            ge::core::convertTo<GLenum    >(this->at::Target<TARGET_TYPE>::_value),
            ge::core::convertTo<GLuint    >(this->at::Index <INDEX_TYPE >::_value),
            ge::core::convertTo<GLuint    >(this->at::Buffer<BUFFER_TYPE>::_value),
            ge::core::convertTo<GLintptr  >(this->at::Offset<OFFSET_TYPE>::_value),
            ge::core::convertTo<GLsizeiptr>(this->at::Size  <SIZE_TYPE  >::_value)
          );
        }
    };

    template<
      typename XFB_TYPE    = GLuint,
      typename INDEX_TYPE  = GLuint,
      typename BUFFER_TYPE = GLuint>
    class TransformFeedbackBufferBase:
        public ge::core::Command,
        public at::Xfb   <XFB_TYPE   >,
        public at::Index <INDEX_TYPE >,
        public at::Buffer<BUFFER_TYPE>{
      public:
        TransformFeedbackBufferBase(
            XFB_TYPE    const&xfb   ,
            INDEX_TYPE  const&index ,
            BUFFER_TYPE const&buffer):
          at::Xfb   <XFB_TYPE   >(xfb   ),
          at::Index <INDEX_TYPE >(index ),
          at::Buffer<BUFFER_TYPE>(buffer){}
        virtual~TransformFeedbackBufferBase(){}
        virtual void operator()(){
          glTransformFeedbackBufferBase(
            ge::core::convertTo<GLuint>(this->at::Xfb   <XFB_TYPE   >::_value),
            ge::core::convertTo<GLuint>(this->at::Index <INDEX_TYPE >::_value),
            ge::core::convertTo<GLuint>(this->at::Buffer<BUFFER_TYPE>::_value)
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
        public ge::core::Command,
        public at::Buffer        <BUFFER_TYPE        >,
        public at::Internalformat<INTERNALFORMAT_TYPE>,
        public at::Offset        <OFFSET_TYPE        >,
        public at::Size          <SIZE_TYPE          >,
        public at::Format        <FORMAT_TYPE        >,
        public at::Type          <TYPE_TYPE          >,
        public at::Data          <DATA_TYPE          >{
      public:
        ClearNamedBufferSubData(
            BUFFER_TYPE         const&buffer        ,
            INTERNALFORMAT_TYPE const&internalformat,
            OFFSET_TYPE         const&offset        ,
            SIZE_TYPE           const&size          ,
            FORMAT_TYPE         const&format        ,
            TYPE_TYPE           const&type          ,
            DATA_TYPE           const&data          ):
          at::Buffer        <BUFFER_TYPE        >(buffer        ),
          at::Internalformat<INTERNALFORMAT_TYPE>(internalformat),
          at::Offset        <OFFSET_TYPE        >(offset        ),
          at::Size          <SIZE_TYPE          >(size          ),
          at::Format        <FORMAT_TYPE        >(format        ),
          at::Type          <TYPE_TYPE          >(type          ),
          at::Data          <DATA_TYPE          >(data          ){}
        virtual~ClearNamedBufferSubData(){}
        virtual void operator()(){
          glClearNamedBufferSubData(
            ge::core::convertTo<GLuint     >(this->at::Buffer        <BUFFER_TYPE        >::_value),
            ge::core::convertTo<GLenum     >(this->at::Internalformat<INTERNALFORMAT_TYPE>::_value),
            ge::core::convertTo<GLintptr   >(this->at::Offset        <OFFSET_TYPE        >::_value),
            ge::core::convertTo<GLsizeiptr >(this->at::Size          <SIZE_TYPE          >::_value),
            ge::core::convertTo<GLenum     >(this->at::Format        <FORMAT_TYPE        >::_value),
            ge::core::convertTo<GLenum     >(this->at::Type          <TYPE_TYPE          >::_value),
            ge::core::convertTo<const void*>(this->at::Data          <DATA_TYPE          >::_value)
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
        public ge::core::Command,
        public at::Ret   <RET_TYPE   >,
        public at::Buffer<BUFFER_TYPE>,
        public at::Offset<OFFSET_TYPE>,
        public at::Length<LENGTH_TYPE>,
        public at::Access<ACCESS_TYPE>{
      public:
        MapNamedBufferRange(
            RET_TYPE    const&ret   ,
            BUFFER_TYPE const&buffer,
            OFFSET_TYPE const&offset,
            LENGTH_TYPE const&length,
            ACCESS_TYPE const&access):
          at::Ret   <RET_TYPE   >(ret   ),
          at::Buffer<BUFFER_TYPE>(buffer),
          at::Offset<OFFSET_TYPE>(offset),
          at::Length<LENGTH_TYPE>(length),
          at::Access<ACCESS_TYPE>(access){}
        virtual~MapNamedBufferRange(){}
        virtual void operator()(){
          ge::core::convertFrom<void*>(this->at::Ret<RET_TYPE>::_value,glMapNamedBufferRange(
              ge::core::convertTo<GLuint    >(this->at::Buffer<BUFFER_TYPE>::_value),
              ge::core::convertTo<GLintptr  >(this->at::Offset<OFFSET_TYPE>::_value),
              ge::core::convertTo<GLsizeiptr>(this->at::Length<LENGTH_TYPE>::_value),
              ge::core::convertTo<GLbitfield>(this->at::Access<ACCESS_TYPE>::_value))
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
        public ge::core::Command,
        public at::Texture       <TEXTURE_TYPE       >,
        public at::Internalformat<INTERNALFORMAT_TYPE>,
        public at::Buffer        <BUFFER_TYPE        >,
        public at::Offset        <OFFSET_TYPE        >,
        public at::Size          <SIZE_TYPE          >{
      public:
        TextureBufferRange(
            TEXTURE_TYPE        const&texture       ,
            INTERNALFORMAT_TYPE const&internalformat,
            BUFFER_TYPE         const&buffer        ,
            OFFSET_TYPE         const&offset        ,
            SIZE_TYPE           const&size          ):
          at::Texture       <TEXTURE_TYPE       >(texture       ),
          at::Internalformat<INTERNALFORMAT_TYPE>(internalformat),
          at::Buffer        <BUFFER_TYPE        >(buffer        ),
          at::Offset        <OFFSET_TYPE        >(offset        ),
          at::Size          <SIZE_TYPE          >(size          ){}
        virtual~TextureBufferRange(){}
        virtual void operator()(){
          glTextureBufferRange(
            ge::core::convertTo<GLuint    >(this->at::Texture       <TEXTURE_TYPE       >::_value),
            ge::core::convertTo<GLenum    >(this->at::Internalformat<INTERNALFORMAT_TYPE>::_value),
            ge::core::convertTo<GLuint    >(this->at::Buffer        <BUFFER_TYPE        >::_value),
            ge::core::convertTo<GLintptr  >(this->at::Offset        <OFFSET_TYPE        >::_value),
            ge::core::convertTo<GLsizeiptr>(this->at::Size          <SIZE_TYPE          >::_value)
          );
        }
    };

    template<
      typename FRAMEBUFFER_TYPE = GLuint,
      typename BUF_TYPE         = GLenum>
    class NamedFramebufferDrawBuffer:
        public ge::core::Command,
        public at::Framebuffer<FRAMEBUFFER_TYPE>,
        public at::Buf        <BUF_TYPE        >{
      public:
        NamedFramebufferDrawBuffer(
            FRAMEBUFFER_TYPE const&framebuffer,
            BUF_TYPE         const&buf        ):
          at::Framebuffer<FRAMEBUFFER_TYPE>(framebuffer),
          at::Buf        <BUF_TYPE        >(buf        ){}
        virtual~NamedFramebufferDrawBuffer(){}
        virtual void operator()(){
          glNamedFramebufferDrawBuffer(
            ge::core::convertTo<GLuint>(this->at::Framebuffer<FRAMEBUFFER_TYPE>::_value),
            ge::core::convertTo<GLenum>(this->at::Buf        <BUF_TYPE        >::_value)
          );
        }
    };

    template<
      typename TARGET_TYPE = GLenum,
      typename PNAME_TYPE  = GLenum,
      typename PARAMS_TYPE = GLint*>
    class GetBufferParameteriv:
        public ge::core::Command,
        public at::Target<TARGET_TYPE>,
        public at::Pname <PNAME_TYPE >,
        public at::Params<PARAMS_TYPE>{
      public:
        GetBufferParameteriv(
            TARGET_TYPE const&target,
            PNAME_TYPE  const&pname ,
            PARAMS_TYPE const&params):
          at::Target<TARGET_TYPE>(target),
          at::Pname <PNAME_TYPE >(pname ),
          at::Params<PARAMS_TYPE>(params){}
        virtual~GetBufferParameteriv(){}
        virtual void operator()(){
          glGetBufferParameteriv(
            ge::core::convertTo<GLenum>(this->at::Target<TARGET_TYPE>::_value),
            ge::core::convertTo<GLenum>(this->at::Pname <PNAME_TYPE >::_value),
            ge::core::convertTo<GLint*>(this->at::Params<PARAMS_TYPE>::_value)
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
        public ge::core::Command,
        public at::Target        <TARGET_TYPE        >,
        public at::Internalformat<INTERNALFORMAT_TYPE>,
        public at::Buffer        <BUFFER_TYPE        >,
        public at::Offset        <OFFSET_TYPE        >,
        public at::Size          <SIZE_TYPE          >{
      public:
        TexBufferRange(
            TARGET_TYPE         const&target        ,
            INTERNALFORMAT_TYPE const&internalformat,
            BUFFER_TYPE         const&buffer        ,
            OFFSET_TYPE         const&offset        ,
            SIZE_TYPE           const&size          ):
          at::Target        <TARGET_TYPE        >(target        ),
          at::Internalformat<INTERNALFORMAT_TYPE>(internalformat),
          at::Buffer        <BUFFER_TYPE        >(buffer        ),
          at::Offset        <OFFSET_TYPE        >(offset        ),
          at::Size          <SIZE_TYPE          >(size          ){}
        virtual~TexBufferRange(){}
        virtual void operator()(){
          glTexBufferRange(
            ge::core::convertTo<GLenum    >(this->at::Target        <TARGET_TYPE        >::_value),
            ge::core::convertTo<GLenum    >(this->at::Internalformat<INTERNALFORMAT_TYPE>::_value),
            ge::core::convertTo<GLuint    >(this->at::Buffer        <BUFFER_TYPE        >::_value),
            ge::core::convertTo<GLintptr  >(this->at::Offset        <OFFSET_TYPE        >::_value),
            ge::core::convertTo<GLsizeiptr>(this->at::Size          <SIZE_TYPE          >::_value)
          );
        }
    };

    template<
      typename RET_TYPE    = GLboolean,
      typename TARGET_TYPE = GLenum   >
    class UnmapBuffer:
        public ge::core::Command,
        public at::Ret   <RET_TYPE   >,
        public at::Target<TARGET_TYPE>{
      public:
        UnmapBuffer(
            RET_TYPE    const&ret   ,
            TARGET_TYPE const&target):
          at::Ret   <RET_TYPE   >(ret   ),
          at::Target<TARGET_TYPE>(target){}
        virtual~UnmapBuffer(){}
        virtual void operator()(){
          ge::core::convertFrom<GLboolean>(this->at::Ret<RET_TYPE>::_value,glUnmapBuffer(
              ge::core::convertTo<GLenum   >(this->at::Target<TARGET_TYPE>::_value))
          );
        }
    };

    template<
      typename RET_TYPE    = void* ,
      typename TARGET_TYPE = GLenum,
      typename ACCESS_TYPE = GLenum>
    class MapBuffer:
        public ge::core::Command,
        public at::Ret   <RET_TYPE   >,
        public at::Target<TARGET_TYPE>,
        public at::Access<ACCESS_TYPE>{
      public:
        MapBuffer(
            RET_TYPE    const&ret   ,
            TARGET_TYPE const&target,
            ACCESS_TYPE const&access):
          at::Ret   <RET_TYPE   >(ret   ),
          at::Target<TARGET_TYPE>(target),
          at::Access<ACCESS_TYPE>(access){}
        virtual~MapBuffer(){}
        virtual void operator()(){
          ge::core::convertFrom<void*>(this->at::Ret<RET_TYPE>::_value,glMapBuffer(
              ge::core::convertTo<GLenum>(this->at::Target<TARGET_TYPE>::_value),
              ge::core::convertTo<GLenum>(this->at::Access<ACCESS_TYPE>::_value))
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
        public ge::core::Command,
        public at::ReadBuffer <READBUFFER_TYPE >,
        public at::WriteBuffer<WRITEBUFFER_TYPE>,
        public at::ReadOffset <READOFFSET_TYPE >,
        public at::WriteOffset<WRITEOFFSET_TYPE>,
        public at::Size       <SIZE_TYPE       >{
      public:
        CopyNamedBufferSubData(
            READBUFFER_TYPE  const&readBuffer ,
            WRITEBUFFER_TYPE const&writeBuffer,
            READOFFSET_TYPE  const&readOffset ,
            WRITEOFFSET_TYPE const&writeOffset,
            SIZE_TYPE        const&size       ):
          at::ReadBuffer <READBUFFER_TYPE >(readBuffer ),
          at::WriteBuffer<WRITEBUFFER_TYPE>(writeBuffer),
          at::ReadOffset <READOFFSET_TYPE >(readOffset ),
          at::WriteOffset<WRITEOFFSET_TYPE>(writeOffset),
          at::Size       <SIZE_TYPE       >(size       ){}
        virtual~CopyNamedBufferSubData(){}
        virtual void operator()(){
          glCopyNamedBufferSubData(
            ge::core::convertTo<GLuint    >(this->at::ReadBuffer <READBUFFER_TYPE >::_value),
            ge::core::convertTo<GLuint    >(this->at::WriteBuffer<WRITEBUFFER_TYPE>::_value),
            ge::core::convertTo<GLintptr  >(this->at::ReadOffset <READOFFSET_TYPE >::_value),
            ge::core::convertTo<GLintptr  >(this->at::WriteOffset<WRITEOFFSET_TYPE>::_value),
            ge::core::convertTo<GLsizeiptr>(this->at::Size       <SIZE_TYPE       >::_value)
          );
        }
    };

    template<
      typename BUFFER_TYPE     = GLenum      ,
      typename DRAWBUFFER_TYPE = GLint       ,
      typename VALUE_TYPE      = const GLint*>
    class ClearBufferiv:
        public ge::core::Command,
        public at::Buffer    <BUFFER_TYPE    >,
        public at::Drawbuffer<DRAWBUFFER_TYPE>,
        public at::Value     <VALUE_TYPE     >{
      public:
        ClearBufferiv(
            BUFFER_TYPE     const&buffer    ,
            DRAWBUFFER_TYPE const&drawbuffer,
            VALUE_TYPE      const&value     ):
          at::Buffer    <BUFFER_TYPE    >(buffer    ),
          at::Drawbuffer<DRAWBUFFER_TYPE>(drawbuffer),
          at::Value     <VALUE_TYPE     >(value     ){}
        virtual~ClearBufferiv(){}
        virtual void operator()(){
          glClearBufferiv(
            ge::core::convertTo<GLenum      >(this->at::Buffer    <BUFFER_TYPE    >::_value),
            ge::core::convertTo<GLint       >(this->at::Drawbuffer<DRAWBUFFER_TYPE>::_value),
            ge::core::convertTo<const GLint*>(this->at::Value     <VALUE_TYPE     >::_value)
          );
        }
    };

    template<
      typename RET_TYPE    = GLboolean,
      typename BUFFER_TYPE = GLuint   >
    class IsBuffer:
        public ge::core::Command,
        public at::Ret   <RET_TYPE   >,
        public at::Buffer<BUFFER_TYPE>{
      public:
        IsBuffer(
            RET_TYPE    const&ret   ,
            BUFFER_TYPE const&buffer):
          at::Ret   <RET_TYPE   >(ret   ),
          at::Buffer<BUFFER_TYPE>(buffer){}
        virtual~IsBuffer(){}
        virtual void operator()(){
          ge::core::convertFrom<GLboolean>(this->at::Ret<RET_TYPE>::_value,glIsBuffer(
              ge::core::convertTo<GLuint   >(this->at::Buffer<BUFFER_TYPE>::_value))
          );
        }
    };

    template<
      typename BUFFER_TYPE = GLuint  ,
      typename PNAME_TYPE  = GLenum  ,
      typename PARAMS_TYPE = GLint64*>
    class GetNamedBufferParameteri64v:
        public ge::core::Command,
        public at::Buffer<BUFFER_TYPE>,
        public at::Pname <PNAME_TYPE >,
        public at::Params<PARAMS_TYPE>{
      public:
        GetNamedBufferParameteri64v(
            BUFFER_TYPE const&buffer,
            PNAME_TYPE  const&pname ,
            PARAMS_TYPE const&params):
          at::Buffer<BUFFER_TYPE>(buffer),
          at::Pname <PNAME_TYPE >(pname ),
          at::Params<PARAMS_TYPE>(params){}
        virtual~GetNamedBufferParameteri64v(){}
        virtual void operator()(){
          glGetNamedBufferParameteri64v(
            ge::core::convertTo<GLuint  >(this->at::Buffer<BUFFER_TYPE>::_value),
            ge::core::convertTo<GLenum  >(this->at::Pname <PNAME_TYPE >::_value),
            ge::core::convertTo<GLint64*>(this->at::Params<PARAMS_TYPE>::_value)
          );
        }
    };

    template<
      typename BUFFER_TYPE = GLuint    ,
      typename OFFSET_TYPE = GLintptr  ,
      typename SIZE_TYPE   = GLsizeiptr,
      typename DATA_TYPE   = void*     >
    class GetNamedBufferSubData:
        public ge::core::Command,
        public at::Buffer<BUFFER_TYPE>,
        public at::Offset<OFFSET_TYPE>,
        public at::Size  <SIZE_TYPE  >,
        public at::Data  <DATA_TYPE  >{
      public:
        GetNamedBufferSubData(
            BUFFER_TYPE const&buffer,
            OFFSET_TYPE const&offset,
            SIZE_TYPE   const&size  ,
            DATA_TYPE   const&data  ):
          at::Buffer<BUFFER_TYPE>(buffer),
          at::Offset<OFFSET_TYPE>(offset),
          at::Size  <SIZE_TYPE  >(size  ),
          at::Data  <DATA_TYPE  >(data  ){}
        virtual~GetNamedBufferSubData(){}
        virtual void operator()(){
          glGetNamedBufferSubData(
            ge::core::convertTo<GLuint    >(this->at::Buffer<BUFFER_TYPE>::_value),
            ge::core::convertTo<GLintptr  >(this->at::Offset<OFFSET_TYPE>::_value),
            ge::core::convertTo<GLsizeiptr>(this->at::Size  <SIZE_TYPE  >::_value),
            ge::core::convertTo<void*     >(this->at::Data  <DATA_TYPE  >::_value)
          );
        }
    };

    template<
      typename BUFFER_TYPE = GLuint     ,
      typename OFFSET_TYPE = GLintptr   ,
      typename SIZE_TYPE   = GLsizeiptr ,
      typename DATA_TYPE   = const void*>
    class NamedBufferSubData:
        public ge::core::Command,
        public at::Buffer<BUFFER_TYPE>,
        public at::Offset<OFFSET_TYPE>,
        public at::Size  <SIZE_TYPE  >,
        public at::Data  <DATA_TYPE  >{
      public:
        NamedBufferSubData(
            BUFFER_TYPE const&buffer,
            OFFSET_TYPE const&offset,
            SIZE_TYPE   const&size  ,
            DATA_TYPE   const&data  ):
          at::Buffer<BUFFER_TYPE>(buffer),
          at::Offset<OFFSET_TYPE>(offset),
          at::Size  <SIZE_TYPE  >(size  ),
          at::Data  <DATA_TYPE  >(data  ){}
        virtual~NamedBufferSubData(){}
        virtual void operator()(){
          glNamedBufferSubData(
            ge::core::convertTo<GLuint     >(this->at::Buffer<BUFFER_TYPE>::_value),
            ge::core::convertTo<GLintptr   >(this->at::Offset<OFFSET_TYPE>::_value),
            ge::core::convertTo<GLsizeiptr >(this->at::Size  <SIZE_TYPE  >::_value),
            ge::core::convertTo<const void*>(this->at::Data  <DATA_TYPE  >::_value)
          );
        }
    };

    template<
      typename TARGET_TYPE = GLenum,
      typename BUFFER_TYPE = GLuint>
    class BindBuffer:
        public ge::core::Command,
        public at::Target<TARGET_TYPE>,
        public at::Buffer<BUFFER_TYPE>{
      public:
        BindBuffer(
            TARGET_TYPE const&target,
            BUFFER_TYPE const&buffer):
          at::Target<TARGET_TYPE>(target),
          at::Buffer<BUFFER_TYPE>(buffer){}
        virtual~BindBuffer(){}
        virtual void operator()(){
          glBindBuffer(
            ge::core::convertTo<GLenum>(this->at::Target<TARGET_TYPE>::_value),
            ge::core::convertTo<GLuint>(this->at::Buffer<BUFFER_TYPE>::_value)
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
