#pragma once

#include<geCore/Command.h>
#include<geGL/Export.h>
#include<GL/glew.h>
#include<geGL/AllAttribs.h>

namespace ge{
  namespace gl{
    template<
      typename MODE_TYPE       = GLenum           ,
      typename COUNT_TYPE      = const GLsizei*   ,
      typename TYPE_TYPE       = GLenum           ,
      typename INDICES_TYPE    = const void*const*,
      typename DRAWCOUNT_TYPE  = GLsizei          ,
      typename BASEVERTEX_TYPE = const GLint*     >
    class MultiDrawElementsBaseVertex:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "mode"      )return(void*)&this->mode      ;
          if(name == "count"     )return(void*)&this->count     ;
          if(name == "type"      )return(void*)&this->type      ;
          if(name == "indices"   )return(void*)&this->indices   ;
          if(name == "drawcount" )return(void*)&this->drawcount ;
          if(name == "basevertex")return(void*)&this->basevertex;
          return NULL;
        }
      public:
        MODE_TYPE       mode      ;
        COUNT_TYPE      count     ;
        TYPE_TYPE       type      ;
        INDICES_TYPE    indices   ;
        DRAWCOUNT_TYPE  drawcount ;
        BASEVERTEX_TYPE basevertex;
        MultiDrawElementsBaseVertex(
            MODE_TYPE       const&mode      ,
            COUNT_TYPE      const&count     ,
            TYPE_TYPE       const&type      ,
            INDICES_TYPE    const&indices   ,
            DRAWCOUNT_TYPE  const&drawcount ,
            BASEVERTEX_TYPE const&basevertex){
          this->mode       = mode      ;
          this->count      = count     ;
          this->type       = type      ;
          this->indices    = indices   ;
          this->drawcount  = drawcount ;
          this->basevertex = basevertex;
        }
        virtual~MultiDrawElementsBaseVertex(){}
        virtual void operator()(){
          glMultiDrawElementsBaseVertex(
            ge::core::convertTo<GLenum           >(this->mode      ),
            ge::core::convertTo<const GLsizei*   >(this->count     ),
            ge::core::convertTo<GLenum           >(this->type      ),
            ge::core::convertTo<const void*const*>(this->indices   ),
            ge::core::convertTo<GLsizei          >(this->drawcount ),
            ge::core::convertTo<const GLint*     >(this->basevertex)
          );
        }
    };

    template<
      typename MODE_TYPE      = GLenum        ,
      typename FIRST_TYPE     = const GLint*  ,
      typename COUNT_TYPE     = const GLsizei*,
      typename DRAWCOUNT_TYPE = GLsizei       >
    class MultiDrawArrays:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "mode"     )return(void*)&this->mode     ;
          if(name == "first"    )return(void*)&this->first    ;
          if(name == "count"    )return(void*)&this->count    ;
          if(name == "drawcount")return(void*)&this->drawcount;
          return NULL;
        }
      public:
        MODE_TYPE      mode     ;
        FIRST_TYPE     first    ;
        COUNT_TYPE     count    ;
        DRAWCOUNT_TYPE drawcount;
        MultiDrawArrays(
            MODE_TYPE      const&mode     ,
            FIRST_TYPE     const&first    ,
            COUNT_TYPE     const&count    ,
            DRAWCOUNT_TYPE const&drawcount){
          this->mode      = mode     ;
          this->first     = first    ;
          this->count     = count    ;
          this->drawcount = drawcount;
        }
        virtual~MultiDrawArrays(){}
        virtual void operator()(){
          glMultiDrawArrays(
            ge::core::convertTo<GLenum        >(this->mode     ),
            ge::core::convertTo<const GLint*  >(this->first    ),
            ge::core::convertTo<const GLsizei*>(this->count    ),
            ge::core::convertTo<GLsizei       >(this->drawcount)
          );
        }
    };

    template<
      typename MODE_TYPE          = GLenum     ,
      typename COUNT_TYPE         = GLsizei    ,
      typename TYPE_TYPE          = GLenum     ,
      typename INDICES_TYPE       = const void*,
      typename INSTANCECOUNT_TYPE = GLsizei    ,
      typename BASEINSTANCE_TYPE  = GLuint     >
    class DrawElementsInstancedBaseInstance:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "mode"         )return(void*)&this->mode         ;
          if(name == "count"        )return(void*)&this->count        ;
          if(name == "type"         )return(void*)&this->type         ;
          if(name == "indices"      )return(void*)&this->indices      ;
          if(name == "instancecount")return(void*)&this->instancecount;
          if(name == "baseinstance" )return(void*)&this->baseinstance ;
          return NULL;
        }
      public:
        MODE_TYPE          mode         ;
        COUNT_TYPE         count        ;
        TYPE_TYPE          type         ;
        INDICES_TYPE       indices      ;
        INSTANCECOUNT_TYPE instancecount;
        BASEINSTANCE_TYPE  baseinstance ;
        DrawElementsInstancedBaseInstance(
            MODE_TYPE          const&mode         ,
            COUNT_TYPE         const&count        ,
            TYPE_TYPE          const&type         ,
            INDICES_TYPE       const&indices      ,
            INSTANCECOUNT_TYPE const&instancecount,
            BASEINSTANCE_TYPE  const&baseinstance ){
          this->mode          = mode         ;
          this->count         = count        ;
          this->type          = type         ;
          this->indices       = indices      ;
          this->instancecount = instancecount;
          this->baseinstance  = baseinstance ;
        }
        virtual~DrawElementsInstancedBaseInstance(){}
        virtual void operator()(){
          glDrawElementsInstancedBaseInstance(
            ge::core::convertTo<GLenum     >(this->mode         ),
            ge::core::convertTo<GLsizei    >(this->count        ),
            ge::core::convertTo<GLenum     >(this->type         ),
            ge::core::convertTo<const void*>(this->indices      ),
            ge::core::convertTo<GLsizei    >(this->instancecount),
            ge::core::convertTo<GLuint     >(this->baseinstance )
          );
        }
    };

    template<
      typename MODE_TYPE      = GLenum           ,
      typename COUNT_TYPE     = const GLsizei*   ,
      typename TYPE_TYPE      = GLenum           ,
      typename INDICES_TYPE   = const void*const*,
      typename DRAWCOUNT_TYPE = GLsizei          >
    class MultiDrawElements:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "mode"     )return(void*)&this->mode     ;
          if(name == "count"    )return(void*)&this->count    ;
          if(name == "type"     )return(void*)&this->type     ;
          if(name == "indices"  )return(void*)&this->indices  ;
          if(name == "drawcount")return(void*)&this->drawcount;
          return NULL;
        }
      public:
        MODE_TYPE      mode     ;
        COUNT_TYPE     count    ;
        TYPE_TYPE      type     ;
        INDICES_TYPE   indices  ;
        DRAWCOUNT_TYPE drawcount;
        MultiDrawElements(
            MODE_TYPE      const&mode     ,
            COUNT_TYPE     const&count    ,
            TYPE_TYPE      const&type     ,
            INDICES_TYPE   const&indices  ,
            DRAWCOUNT_TYPE const&drawcount){
          this->mode      = mode     ;
          this->count     = count    ;
          this->type      = type     ;
          this->indices   = indices  ;
          this->drawcount = drawcount;
        }
        virtual~MultiDrawElements(){}
        virtual void operator()(){
          glMultiDrawElements(
            ge::core::convertTo<GLenum           >(this->mode     ),
            ge::core::convertTo<const GLsizei*   >(this->count    ),
            ge::core::convertTo<GLenum           >(this->type     ),
            ge::core::convertTo<const void*const*>(this->indices  ),
            ge::core::convertTo<GLsizei          >(this->drawcount)
          );
        }
    };

    template<
      typename MODE_TYPE          = GLenum ,
      typename FIRST_TYPE         = GLint  ,
      typename COUNT_TYPE         = GLsizei,
      typename INSTANCECOUNT_TYPE = GLsizei,
      typename BASEINSTANCE_TYPE  = GLuint >
    class DrawArraysInstancedBaseInstance:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "mode"         )return(void*)&this->mode         ;
          if(name == "first"        )return(void*)&this->first        ;
          if(name == "count"        )return(void*)&this->count        ;
          if(name == "instancecount")return(void*)&this->instancecount;
          if(name == "baseinstance" )return(void*)&this->baseinstance ;
          return NULL;
        }
      public:
        MODE_TYPE          mode         ;
        FIRST_TYPE         first        ;
        COUNT_TYPE         count        ;
        INSTANCECOUNT_TYPE instancecount;
        BASEINSTANCE_TYPE  baseinstance ;
        DrawArraysInstancedBaseInstance(
            MODE_TYPE          const&mode         ,
            FIRST_TYPE         const&first        ,
            COUNT_TYPE         const&count        ,
            INSTANCECOUNT_TYPE const&instancecount,
            BASEINSTANCE_TYPE  const&baseinstance ){
          this->mode          = mode         ;
          this->first         = first        ;
          this->count         = count        ;
          this->instancecount = instancecount;
          this->baseinstance  = baseinstance ;
        }
        virtual~DrawArraysInstancedBaseInstance(){}
        virtual void operator()(){
          glDrawArraysInstancedBaseInstance(
            ge::core::convertTo<GLenum >(this->mode         ),
            ge::core::convertTo<GLint  >(this->first        ),
            ge::core::convertTo<GLsizei>(this->count        ),
            ge::core::convertTo<GLsizei>(this->instancecount),
            ge::core::convertTo<GLuint >(this->baseinstance )
          );
        }
    };

    template<
      typename MODE_TYPE          = GLenum ,
      typename FIRST_TYPE         = GLint  ,
      typename COUNT_TYPE         = GLsizei,
      typename INSTANCECOUNT_TYPE = GLsizei>
    class DrawArraysInstanced:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "mode"         )return(void*)&this->mode         ;
          if(name == "first"        )return(void*)&this->first        ;
          if(name == "count"        )return(void*)&this->count        ;
          if(name == "instancecount")return(void*)&this->instancecount;
          return NULL;
        }
      public:
        MODE_TYPE          mode         ;
        FIRST_TYPE         first        ;
        COUNT_TYPE         count        ;
        INSTANCECOUNT_TYPE instancecount;
        DrawArraysInstanced(
            MODE_TYPE          const&mode         ,
            FIRST_TYPE         const&first        ,
            COUNT_TYPE         const&count        ,
            INSTANCECOUNT_TYPE const&instancecount){
          this->mode          = mode         ;
          this->first         = first        ;
          this->count         = count        ;
          this->instancecount = instancecount;
        }
        virtual~DrawArraysInstanced(){}
        virtual void operator()(){
          glDrawArraysInstanced(
            ge::core::convertTo<GLenum >(this->mode         ),
            ge::core::convertTo<GLint  >(this->first        ),
            ge::core::convertTo<GLsizei>(this->count        ),
            ge::core::convertTo<GLsizei>(this->instancecount)
          );
        }
    };

    template<
      typename WIDTH_TYPE  = GLsizei      ,
      typename HEIGHT_TYPE = GLsizei      ,
      typename FORMAT_TYPE = GLenum       ,
      typename TYPE_TYPE   = GLenum       ,
      typename PIXELS_TYPE = const GLvoid*>
    class DrawPixels:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "width" )return(void*)&this->width ;
          if(name == "height")return(void*)&this->height;
          if(name == "format")return(void*)&this->format;
          if(name == "type"  )return(void*)&this->type  ;
          if(name == "pixels")return(void*)&this->pixels;
          return NULL;
        }
      public:
        WIDTH_TYPE  width ;
        HEIGHT_TYPE height;
        FORMAT_TYPE format;
        TYPE_TYPE   type  ;
        PIXELS_TYPE pixels;
        DrawPixels(
            WIDTH_TYPE  const&width ,
            HEIGHT_TYPE const&height,
            FORMAT_TYPE const&format,
            TYPE_TYPE   const&type  ,
            PIXELS_TYPE const&pixels){
          this->width  = width ;
          this->height = height;
          this->format = format;
          this->type   = type  ;
          this->pixels = pixels;
        }
        virtual~DrawPixels(){}
        virtual void operator()(){
          glDrawPixels(
            ge::core::convertTo<GLsizei      >(this->width ),
            ge::core::convertTo<GLsizei      >(this->height),
            ge::core::convertTo<GLenum       >(this->format),
            ge::core::convertTo<GLenum       >(this->type  ),
            ge::core::convertTo<const GLvoid*>(this->pixels)
          );
        }
    };

    template<
      typename MODE_TYPE          = GLenum     ,
      typename COUNT_TYPE         = GLsizei    ,
      typename TYPE_TYPE          = GLenum     ,
      typename INDICES_TYPE       = const void*,
      typename INSTANCECOUNT_TYPE = GLsizei    ,
      typename BASEVERTEX_TYPE    = GLint      ,
      typename BASEINSTANCE_TYPE  = GLuint     >
    class DrawElementsInstancedBaseVertexBaseInstance:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "mode"         )return(void*)&this->mode         ;
          if(name == "count"        )return(void*)&this->count        ;
          if(name == "type"         )return(void*)&this->type         ;
          if(name == "indices"      )return(void*)&this->indices      ;
          if(name == "instancecount")return(void*)&this->instancecount;
          if(name == "basevertex"   )return(void*)&this->basevertex   ;
          if(name == "baseinstance" )return(void*)&this->baseinstance ;
          return NULL;
        }
      public:
        MODE_TYPE          mode         ;
        COUNT_TYPE         count        ;
        TYPE_TYPE          type         ;
        INDICES_TYPE       indices      ;
        INSTANCECOUNT_TYPE instancecount;
        BASEVERTEX_TYPE    basevertex   ;
        BASEINSTANCE_TYPE  baseinstance ;
        DrawElementsInstancedBaseVertexBaseInstance(
            MODE_TYPE          const&mode         ,
            COUNT_TYPE         const&count        ,
            TYPE_TYPE          const&type         ,
            INDICES_TYPE       const&indices      ,
            INSTANCECOUNT_TYPE const&instancecount,
            BASEVERTEX_TYPE    const&basevertex   ,
            BASEINSTANCE_TYPE  const&baseinstance ){
          this->mode          = mode         ;
          this->count         = count        ;
          this->type          = type         ;
          this->indices       = indices      ;
          this->instancecount = instancecount;
          this->basevertex    = basevertex   ;
          this->baseinstance  = baseinstance ;
        }
        virtual~DrawElementsInstancedBaseVertexBaseInstance(){}
        virtual void operator()(){
          glDrawElementsInstancedBaseVertexBaseInstance(
            ge::core::convertTo<GLenum     >(this->mode         ),
            ge::core::convertTo<GLsizei    >(this->count        ),
            ge::core::convertTo<GLenum     >(this->type         ),
            ge::core::convertTo<const void*>(this->indices      ),
            ge::core::convertTo<GLsizei    >(this->instancecount),
            ge::core::convertTo<GLint      >(this->basevertex   ),
            ge::core::convertTo<GLuint     >(this->baseinstance )
          );
        }
    };

    template<
      typename MODE_TYPE       = GLenum     ,
      typename COUNT_TYPE      = GLsizei    ,
      typename TYPE_TYPE       = GLenum     ,
      typename INDICES_TYPE    = const void*,
      typename BASEVERTEX_TYPE = GLint      >
    class DrawElementsBaseVertex:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "mode"      )return(void*)&this->mode      ;
          if(name == "count"     )return(void*)&this->count     ;
          if(name == "type"      )return(void*)&this->type      ;
          if(name == "indices"   )return(void*)&this->indices   ;
          if(name == "basevertex")return(void*)&this->basevertex;
          return NULL;
        }
      public:
        MODE_TYPE       mode      ;
        COUNT_TYPE      count     ;
        TYPE_TYPE       type      ;
        INDICES_TYPE    indices   ;
        BASEVERTEX_TYPE basevertex;
        DrawElementsBaseVertex(
            MODE_TYPE       const&mode      ,
            COUNT_TYPE      const&count     ,
            TYPE_TYPE       const&type      ,
            INDICES_TYPE    const&indices   ,
            BASEVERTEX_TYPE const&basevertex){
          this->mode       = mode      ;
          this->count      = count     ;
          this->type       = type      ;
          this->indices    = indices   ;
          this->basevertex = basevertex;
        }
        virtual~DrawElementsBaseVertex(){}
        virtual void operator()(){
          glDrawElementsBaseVertex(
            ge::core::convertTo<GLenum     >(this->mode      ),
            ge::core::convertTo<GLsizei    >(this->count     ),
            ge::core::convertTo<GLenum     >(this->type      ),
            ge::core::convertTo<const void*>(this->indices   ),
            ge::core::convertTo<GLint      >(this->basevertex)
          );
        }
    };

    template<
      typename MODE_TYPE    = GLenum       ,
      typename START_TYPE   = GLuint       ,
      typename END_TYPE     = GLuint       ,
      typename COUNT_TYPE   = GLsizei      ,
      typename TYPE_TYPE    = GLenum       ,
      typename INDICES_TYPE = const GLvoid*>
    class DrawRangeElements:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "mode"   )return(void*)&this->mode   ;
          if(name == "start"  )return(void*)&this->start  ;
          if(name == "end"    )return(void*)&this->end    ;
          if(name == "count"  )return(void*)&this->count  ;
          if(name == "type"   )return(void*)&this->type   ;
          if(name == "indices")return(void*)&this->indices;
          return NULL;
        }
      public:
        MODE_TYPE    mode   ;
        START_TYPE   start  ;
        END_TYPE     end    ;
        COUNT_TYPE   count  ;
        TYPE_TYPE    type   ;
        INDICES_TYPE indices;
        DrawRangeElements(
            MODE_TYPE    const&mode   ,
            START_TYPE   const&start  ,
            END_TYPE     const&end    ,
            COUNT_TYPE   const&count  ,
            TYPE_TYPE    const&type   ,
            INDICES_TYPE const&indices){
          this->mode    = mode   ;
          this->start   = start  ;
          this->end     = end    ;
          this->count   = count  ;
          this->type    = type   ;
          this->indices = indices;
        }
        virtual~DrawRangeElements(){}
        virtual void operator()(){
          glDrawRangeElements(
            ge::core::convertTo<GLenum       >(this->mode   ),
            ge::core::convertTo<GLuint       >(this->start  ),
            ge::core::convertTo<GLuint       >(this->end    ),
            ge::core::convertTo<GLsizei      >(this->count  ),
            ge::core::convertTo<GLenum       >(this->type   ),
            ge::core::convertTo<const GLvoid*>(this->indices)
          );
        }
    };

    template<
      typename PNAME_TYPE  = GLenum        ,
      typename VALUES_TYPE = const GLfloat*>
    class PatchParameterfv:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "pname" )return(void*)&this->pname ;
          if(name == "values")return(void*)&this->values;
          return NULL;
        }
      public:
        PNAME_TYPE  pname ;
        VALUES_TYPE values;
        PatchParameterfv(
            PNAME_TYPE  const&pname ,
            VALUES_TYPE const&values){
          this->pname  = pname ;
          this->values = values;
        }
        virtual~PatchParameterfv(){}
        virtual void operator()(){
          glPatchParameterfv(
            ge::core::convertTo<GLenum        >(this->pname ),
            ge::core::convertTo<const GLfloat*>(this->values)
          );
        }
    };

    template<
      typename PNAME_TYPE = GLenum,
      typename VALUE_TYPE = GLint >
    class PatchParameteri:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "pname")return(void*)&this->pname;
          if(name == "value")return(void*)&this->value;
          return NULL;
        }
      public:
        PNAME_TYPE pname;
        VALUE_TYPE value;
        PatchParameteri(
            PNAME_TYPE const&pname,
            VALUE_TYPE const&value){
          this->pname = pname;
          this->value = value;
        }
        virtual~PatchParameteri(){}
        virtual void operator()(){
          glPatchParameteri(
            ge::core::convertTo<GLenum>(this->pname),
            ge::core::convertTo<GLint >(this->value)
          );
        }
    };

    template<
      typename MODE_TYPE = GLenum,
      typename ID_TYPE   = GLuint>
    class DrawTransformFeedback:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "mode")return(void*)&this->mode;
          if(name == "id"  )return(void*)&this->id  ;
          return NULL;
        }
      public:
        MODE_TYPE mode;
        ID_TYPE   id  ;
        DrawTransformFeedback(
            MODE_TYPE const&mode,
            ID_TYPE   const&id  ){
          this->mode = mode;
          this->id   = id  ;
        }
        virtual~DrawTransformFeedback(){}
        virtual void operator()(){
          glDrawTransformFeedback(
            ge::core::convertTo<GLenum>(this->mode),
            ge::core::convertTo<GLuint>(this->id  )
          );
        }
    };

    template<
      typename MODE_TYPE   = GLenum,
      typename ID_TYPE     = GLuint,
      typename STREAM_TYPE = GLuint>
    class DrawTransformFeedbackStream:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "mode"  )return(void*)&this->mode  ;
          if(name == "id"    )return(void*)&this->id    ;
          if(name == "stream")return(void*)&this->stream;
          return NULL;
        }
      public:
        MODE_TYPE   mode  ;
        ID_TYPE     id    ;
        STREAM_TYPE stream;
        DrawTransformFeedbackStream(
            MODE_TYPE   const&mode  ,
            ID_TYPE     const&id    ,
            STREAM_TYPE const&stream){
          this->mode   = mode  ;
          this->id     = id    ;
          this->stream = stream;
        }
        virtual~DrawTransformFeedbackStream(){}
        virtual void operator()(){
          glDrawTransformFeedbackStream(
            ge::core::convertTo<GLenum>(this->mode  ),
            ge::core::convertTo<GLuint>(this->id    ),
            ge::core::convertTo<GLuint>(this->stream)
          );
        }
    };

    template<
      typename MODE_TYPE          = GLenum ,
      typename ID_TYPE            = GLuint ,
      typename STREAM_TYPE        = GLuint ,
      typename INSTANCECOUNT_TYPE = GLsizei>
    class DrawTransformFeedbackStreamInstanced:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "mode"         )return(void*)&this->mode         ;
          if(name == "id"           )return(void*)&this->id           ;
          if(name == "stream"       )return(void*)&this->stream       ;
          if(name == "instancecount")return(void*)&this->instancecount;
          return NULL;
        }
      public:
        MODE_TYPE          mode         ;
        ID_TYPE            id           ;
        STREAM_TYPE        stream       ;
        INSTANCECOUNT_TYPE instancecount;
        DrawTransformFeedbackStreamInstanced(
            MODE_TYPE          const&mode         ,
            ID_TYPE            const&id           ,
            STREAM_TYPE        const&stream       ,
            INSTANCECOUNT_TYPE const&instancecount){
          this->mode          = mode         ;
          this->id            = id           ;
          this->stream        = stream       ;
          this->instancecount = instancecount;
        }
        virtual~DrawTransformFeedbackStreamInstanced(){}
        virtual void operator()(){
          glDrawTransformFeedbackStreamInstanced(
            ge::core::convertTo<GLenum >(this->mode         ),
            ge::core::convertTo<GLuint >(this->id           ),
            ge::core::convertTo<GLuint >(this->stream       ),
            ge::core::convertTo<GLsizei>(this->instancecount)
          );
        }
    };

    template<
      typename MODE_TYPE     = GLenum     ,
      typename INDIRECT_TYPE = const void*>
    class DrawArraysIndirect:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "mode"    )return(void*)&this->mode    ;
          if(name == "indirect")return(void*)&this->indirect;
          return NULL;
        }
      public:
        MODE_TYPE     mode    ;
        INDIRECT_TYPE indirect;
        DrawArraysIndirect(
            MODE_TYPE     const&mode    ,
            INDIRECT_TYPE const&indirect){
          this->mode     = mode    ;
          this->indirect = indirect;
        }
        virtual~DrawArraysIndirect(){}
        virtual void operator()(){
          glDrawArraysIndirect(
            ge::core::convertTo<GLenum     >(this->mode    ),
            ge::core::convertTo<const void*>(this->indirect)
          );
        }
    };

    template<
      typename MODE_TYPE     = GLenum     ,
      typename TYPE_TYPE     = GLenum     ,
      typename INDIRECT_TYPE = const void*>
    class DrawElementsIndirect:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "mode"    )return(void*)&this->mode    ;
          if(name == "type"    )return(void*)&this->type    ;
          if(name == "indirect")return(void*)&this->indirect;
          return NULL;
        }
      public:
        MODE_TYPE     mode    ;
        TYPE_TYPE     type    ;
        INDIRECT_TYPE indirect;
        DrawElementsIndirect(
            MODE_TYPE     const&mode    ,
            TYPE_TYPE     const&type    ,
            INDIRECT_TYPE const&indirect){
          this->mode     = mode    ;
          this->type     = type    ;
          this->indirect = indirect;
        }
        virtual~DrawElementsIndirect(){}
        virtual void operator()(){
          glDrawElementsIndirect(
            ge::core::convertTo<GLenum     >(this->mode    ),
            ge::core::convertTo<GLenum     >(this->type    ),
            ge::core::convertTo<const void*>(this->indirect)
          );
        }
    };

    template<
      typename MODE_TYPE  = GLenum ,
      typename FIRST_TYPE = GLint  ,
      typename COUNT_TYPE = GLsizei>
    class DrawArrays:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "mode" )return(void*)&this->mode ;
          if(name == "first")return(void*)&this->first;
          if(name == "count")return(void*)&this->count;
          return NULL;
        }
      public:
        MODE_TYPE  mode ;
        FIRST_TYPE first;
        COUNT_TYPE count;
        DrawArrays(
            MODE_TYPE  const&mode ,
            FIRST_TYPE const&first,
            COUNT_TYPE const&count){
          this->mode  = mode ;
          this->first = first;
          this->count = count;
        }
        virtual~DrawArrays(){}
        virtual void operator()(){
          glDrawArrays(
            ge::core::convertTo<GLenum >(this->mode ),
            ge::core::convertTo<GLint  >(this->first),
            ge::core::convertTo<GLsizei>(this->count)
          );
        }
    };

    template<
      typename MODE_TYPE          = GLenum     ,
      typename COUNT_TYPE         = GLsizei    ,
      typename TYPE_TYPE          = GLenum     ,
      typename INDICES_TYPE       = const void*,
      typename INSTANCECOUNT_TYPE = GLsizei    >
    class DrawElementsInstanced:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "mode"         )return(void*)&this->mode         ;
          if(name == "count"        )return(void*)&this->count        ;
          if(name == "type"         )return(void*)&this->type         ;
          if(name == "indices"      )return(void*)&this->indices      ;
          if(name == "instancecount")return(void*)&this->instancecount;
          return NULL;
        }
      public:
        MODE_TYPE          mode         ;
        COUNT_TYPE         count        ;
        TYPE_TYPE          type         ;
        INDICES_TYPE       indices      ;
        INSTANCECOUNT_TYPE instancecount;
        DrawElementsInstanced(
            MODE_TYPE          const&mode         ,
            COUNT_TYPE         const&count        ,
            TYPE_TYPE          const&type         ,
            INDICES_TYPE       const&indices      ,
            INSTANCECOUNT_TYPE const&instancecount){
          this->mode          = mode         ;
          this->count         = count        ;
          this->type          = type         ;
          this->indices       = indices      ;
          this->instancecount = instancecount;
        }
        virtual~DrawElementsInstanced(){}
        virtual void operator()(){
          glDrawElementsInstanced(
            ge::core::convertTo<GLenum     >(this->mode         ),
            ge::core::convertTo<GLsizei    >(this->count        ),
            ge::core::convertTo<GLenum     >(this->type         ),
            ge::core::convertTo<const void*>(this->indices      ),
            ge::core::convertTo<GLsizei    >(this->instancecount)
          );
        }
    };

    template<
      typename MODE_TYPE      = GLenum     ,
      typename INDIRECT_TYPE  = const void*,
      typename DRAWCOUNT_TYPE = GLsizei    ,
      typename STRIDE_TYPE    = GLsizei    >
    class MultiDrawArraysIndirect:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "mode"     )return(void*)&this->mode     ;
          if(name == "indirect" )return(void*)&this->indirect ;
          if(name == "drawcount")return(void*)&this->drawcount;
          if(name == "stride"   )return(void*)&this->stride   ;
          return NULL;
        }
      public:
        MODE_TYPE      mode     ;
        INDIRECT_TYPE  indirect ;
        DRAWCOUNT_TYPE drawcount;
        STRIDE_TYPE    stride   ;
        MultiDrawArraysIndirect(
            MODE_TYPE      const&mode     ,
            INDIRECT_TYPE  const&indirect ,
            DRAWCOUNT_TYPE const&drawcount,
            STRIDE_TYPE    const&stride   ){
          this->mode      = mode     ;
          this->indirect  = indirect ;
          this->drawcount = drawcount;
          this->stride    = stride   ;
        }
        virtual~MultiDrawArraysIndirect(){}
        virtual void operator()(){
          glMultiDrawArraysIndirect(
            ge::core::convertTo<GLenum     >(this->mode     ),
            ge::core::convertTo<const void*>(this->indirect ),
            ge::core::convertTo<GLsizei    >(this->drawcount),
            ge::core::convertTo<GLsizei    >(this->stride   )
          );
        }
    };

    template<
      typename MODE_TYPE      = GLenum     ,
      typename TYPE_TYPE      = GLenum     ,
      typename INDIRECT_TYPE  = const void*,
      typename DRAWCOUNT_TYPE = GLsizei    ,
      typename STRIDE_TYPE    = GLsizei    >
    class MultiDrawElementsIndirect:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "mode"     )return(void*)&this->mode     ;
          if(name == "type"     )return(void*)&this->type     ;
          if(name == "indirect" )return(void*)&this->indirect ;
          if(name == "drawcount")return(void*)&this->drawcount;
          if(name == "stride"   )return(void*)&this->stride   ;
          return NULL;
        }
      public:
        MODE_TYPE      mode     ;
        TYPE_TYPE      type     ;
        INDIRECT_TYPE  indirect ;
        DRAWCOUNT_TYPE drawcount;
        STRIDE_TYPE    stride   ;
        MultiDrawElementsIndirect(
            MODE_TYPE      const&mode     ,
            TYPE_TYPE      const&type     ,
            INDIRECT_TYPE  const&indirect ,
            DRAWCOUNT_TYPE const&drawcount,
            STRIDE_TYPE    const&stride   ){
          this->mode      = mode     ;
          this->type      = type     ;
          this->indirect  = indirect ;
          this->drawcount = drawcount;
          this->stride    = stride   ;
        }
        virtual~MultiDrawElementsIndirect(){}
        virtual void operator()(){
          glMultiDrawElementsIndirect(
            ge::core::convertTo<GLenum     >(this->mode     ),
            ge::core::convertTo<GLenum     >(this->type     ),
            ge::core::convertTo<const void*>(this->indirect ),
            ge::core::convertTo<GLsizei    >(this->drawcount),
            ge::core::convertTo<GLsizei    >(this->stride   )
          );
        }
    };

    template<
      typename MODE_TYPE          = GLenum     ,
      typename COUNT_TYPE         = GLsizei    ,
      typename TYPE_TYPE          = GLenum     ,
      typename INDICES_TYPE       = const void*,
      typename INSTANCECOUNT_TYPE = GLsizei    ,
      typename BASEVERTEX_TYPE    = GLint      >
    class DrawElementsInstancedBaseVertex:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "mode"         )return(void*)&this->mode         ;
          if(name == "count"        )return(void*)&this->count        ;
          if(name == "type"         )return(void*)&this->type         ;
          if(name == "indices"      )return(void*)&this->indices      ;
          if(name == "instancecount")return(void*)&this->instancecount;
          if(name == "basevertex"   )return(void*)&this->basevertex   ;
          return NULL;
        }
      public:
        MODE_TYPE          mode         ;
        COUNT_TYPE         count        ;
        TYPE_TYPE          type         ;
        INDICES_TYPE       indices      ;
        INSTANCECOUNT_TYPE instancecount;
        BASEVERTEX_TYPE    basevertex   ;
        DrawElementsInstancedBaseVertex(
            MODE_TYPE          const&mode         ,
            COUNT_TYPE         const&count        ,
            TYPE_TYPE          const&type         ,
            INDICES_TYPE       const&indices      ,
            INSTANCECOUNT_TYPE const&instancecount,
            BASEVERTEX_TYPE    const&basevertex   ){
          this->mode          = mode         ;
          this->count         = count        ;
          this->type          = type         ;
          this->indices       = indices      ;
          this->instancecount = instancecount;
          this->basevertex    = basevertex   ;
        }
        virtual~DrawElementsInstancedBaseVertex(){}
        virtual void operator()(){
          glDrawElementsInstancedBaseVertex(
            ge::core::convertTo<GLenum     >(this->mode         ),
            ge::core::convertTo<GLsizei    >(this->count        ),
            ge::core::convertTo<GLenum     >(this->type         ),
            ge::core::convertTo<const void*>(this->indices      ),
            ge::core::convertTo<GLsizei    >(this->instancecount),
            ge::core::convertTo<GLint      >(this->basevertex   )
          );
        }
    };

    template<
      typename MODE_TYPE    = GLenum       ,
      typename COUNT_TYPE   = GLsizei      ,
      typename TYPE_TYPE    = GLenum       ,
      typename INDICES_TYPE = const GLvoid*>
    class DrawElements:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "mode"   )return(void*)&this->mode   ;
          if(name == "count"  )return(void*)&this->count  ;
          if(name == "type"   )return(void*)&this->type   ;
          if(name == "indices")return(void*)&this->indices;
          return NULL;
        }
      public:
        MODE_TYPE    mode   ;
        COUNT_TYPE   count  ;
        TYPE_TYPE    type   ;
        INDICES_TYPE indices;
        DrawElements(
            MODE_TYPE    const&mode   ,
            COUNT_TYPE   const&count  ,
            TYPE_TYPE    const&type   ,
            INDICES_TYPE const&indices){
          this->mode    = mode   ;
          this->count   = count  ;
          this->type    = type   ;
          this->indices = indices;
        }
        virtual~DrawElements(){}
        virtual void operator()(){
          glDrawElements(
            ge::core::convertTo<GLenum       >(this->mode   ),
            ge::core::convertTo<GLsizei      >(this->count  ),
            ge::core::convertTo<GLenum       >(this->type   ),
            ge::core::convertTo<const GLvoid*>(this->indices)
          );
        }
    };

    template<
      typename MODE_TYPE          = GLenum ,
      typename ID_TYPE            = GLuint ,
      typename INSTANCECOUNT_TYPE = GLsizei>
    class DrawTransformFeedbackInstanced:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "mode"         )return(void*)&this->mode         ;
          if(name == "id"           )return(void*)&this->id           ;
          if(name == "instancecount")return(void*)&this->instancecount;
          return NULL;
        }
      public:
        MODE_TYPE          mode         ;
        ID_TYPE            id           ;
        INSTANCECOUNT_TYPE instancecount;
        DrawTransformFeedbackInstanced(
            MODE_TYPE          const&mode         ,
            ID_TYPE            const&id           ,
            INSTANCECOUNT_TYPE const&instancecount){
          this->mode          = mode         ;
          this->id            = id           ;
          this->instancecount = instancecount;
        }
        virtual~DrawTransformFeedbackInstanced(){}
        virtual void operator()(){
          glDrawTransformFeedbackInstanced(
            ge::core::convertTo<GLenum >(this->mode         ),
            ge::core::convertTo<GLuint >(this->id           ),
            ge::core::convertTo<GLsizei>(this->instancecount)
          );
        }
    };

    template<
      typename MODE_TYPE       = GLenum     ,
      typename START_TYPE      = GLuint     ,
      typename END_TYPE        = GLuint     ,
      typename COUNT_TYPE      = GLsizei    ,
      typename TYPE_TYPE       = GLenum     ,
      typename INDICES_TYPE    = const void*,
      typename BASEVERTEX_TYPE = GLint      >
    class DrawRangeElementsBaseVertex:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "mode"      )return(void*)&this->mode      ;
          if(name == "start"     )return(void*)&this->start     ;
          if(name == "end"       )return(void*)&this->end       ;
          if(name == "count"     )return(void*)&this->count     ;
          if(name == "type"      )return(void*)&this->type      ;
          if(name == "indices"   )return(void*)&this->indices   ;
          if(name == "basevertex")return(void*)&this->basevertex;
          return NULL;
        }
      public:
        MODE_TYPE       mode      ;
        START_TYPE      start     ;
        END_TYPE        end       ;
        COUNT_TYPE      count     ;
        TYPE_TYPE       type      ;
        INDICES_TYPE    indices   ;
        BASEVERTEX_TYPE basevertex;
        DrawRangeElementsBaseVertex(
            MODE_TYPE       const&mode      ,
            START_TYPE      const&start     ,
            END_TYPE        const&end       ,
            COUNT_TYPE      const&count     ,
            TYPE_TYPE       const&type      ,
            INDICES_TYPE    const&indices   ,
            BASEVERTEX_TYPE const&basevertex){
          this->mode       = mode      ;
          this->start      = start     ;
          this->end        = end       ;
          this->count      = count     ;
          this->type       = type      ;
          this->indices    = indices   ;
          this->basevertex = basevertex;
        }
        virtual~DrawRangeElementsBaseVertex(){}
        virtual void operator()(){
          glDrawRangeElementsBaseVertex(
            ge::core::convertTo<GLenum     >(this->mode      ),
            ge::core::convertTo<GLuint     >(this->start     ),
            ge::core::convertTo<GLuint     >(this->end       ),
            ge::core::convertTo<GLsizei    >(this->count     ),
            ge::core::convertTo<GLenum     >(this->type      ),
            ge::core::convertTo<const void*>(this->indices   ),
            ge::core::convertTo<GLint      >(this->basevertex)
          );
        }
    };

    template<
      typename MODE_TYPE       = GLenum           ,
      typename COUNT_TYPE      = const GLsizei*   ,
      typename TYPE_TYPE       = GLenum           ,
      typename INDICES_TYPE    = const void*const*,
      typename DRAWCOUNT_TYPE  = GLsizei          ,
      typename BASEVERTEX_TYPE = const GLint*     >
    inline MultiDrawElementsBaseVertex<
      MODE_TYPE      ,
      COUNT_TYPE     ,
      TYPE_TYPE      ,
      INDICES_TYPE   ,
      DRAWCOUNT_TYPE ,
      BASEVERTEX_TYPE>* newMultiDrawElementsBaseVertex(
        MODE_TYPE       const&mode      ,
        COUNT_TYPE      const&count     ,
        TYPE_TYPE       const&type      ,
        INDICES_TYPE    const&indices   ,
        DRAWCOUNT_TYPE  const&drawcount ,
        BASEVERTEX_TYPE const&basevertex){
        return new MultiDrawElementsBaseVertex<
          MODE_TYPE      ,
          COUNT_TYPE     ,
          TYPE_TYPE      ,
          INDICES_TYPE   ,
          DRAWCOUNT_TYPE ,
          BASEVERTEX_TYPE>(
              mode      ,
              count     ,
              type      ,
              indices   ,
              drawcount ,
              basevertex);
    }
    template<
      typename MODE_TYPE      = GLenum        ,
      typename FIRST_TYPE     = const GLint*  ,
      typename COUNT_TYPE     = const GLsizei*,
      typename DRAWCOUNT_TYPE = GLsizei       >
    inline MultiDrawArrays<
      MODE_TYPE     ,
      FIRST_TYPE    ,
      COUNT_TYPE    ,
      DRAWCOUNT_TYPE>* newMultiDrawArrays(
        MODE_TYPE      const&mode     ,
        FIRST_TYPE     const&first    ,
        COUNT_TYPE     const&count    ,
        DRAWCOUNT_TYPE const&drawcount){
        return new MultiDrawArrays<
          MODE_TYPE     ,
          FIRST_TYPE    ,
          COUNT_TYPE    ,
          DRAWCOUNT_TYPE>(
              mode     ,
              first    ,
              count    ,
              drawcount);
    }
    template<
      typename MODE_TYPE          = GLenum     ,
      typename COUNT_TYPE         = GLsizei    ,
      typename TYPE_TYPE          = GLenum     ,
      typename INDICES_TYPE       = const void*,
      typename INSTANCECOUNT_TYPE = GLsizei    ,
      typename BASEINSTANCE_TYPE  = GLuint     >
    inline DrawElementsInstancedBaseInstance<
      MODE_TYPE         ,
      COUNT_TYPE        ,
      TYPE_TYPE         ,
      INDICES_TYPE      ,
      INSTANCECOUNT_TYPE,
      BASEINSTANCE_TYPE >* newDrawElementsInstancedBaseInstance(
        MODE_TYPE          const&mode         ,
        COUNT_TYPE         const&count        ,
        TYPE_TYPE          const&type         ,
        INDICES_TYPE       const&indices      ,
        INSTANCECOUNT_TYPE const&instancecount,
        BASEINSTANCE_TYPE  const&baseinstance ){
        return new DrawElementsInstancedBaseInstance<
          MODE_TYPE         ,
          COUNT_TYPE        ,
          TYPE_TYPE         ,
          INDICES_TYPE      ,
          INSTANCECOUNT_TYPE,
          BASEINSTANCE_TYPE >(
              mode         ,
              count        ,
              type         ,
              indices      ,
              instancecount,
              baseinstance );
    }
    template<
      typename MODE_TYPE      = GLenum           ,
      typename COUNT_TYPE     = const GLsizei*   ,
      typename TYPE_TYPE      = GLenum           ,
      typename INDICES_TYPE   = const void*const*,
      typename DRAWCOUNT_TYPE = GLsizei          >
    inline MultiDrawElements<
      MODE_TYPE     ,
      COUNT_TYPE    ,
      TYPE_TYPE     ,
      INDICES_TYPE  ,
      DRAWCOUNT_TYPE>* newMultiDrawElements(
        MODE_TYPE      const&mode     ,
        COUNT_TYPE     const&count    ,
        TYPE_TYPE      const&type     ,
        INDICES_TYPE   const&indices  ,
        DRAWCOUNT_TYPE const&drawcount){
        return new MultiDrawElements<
          MODE_TYPE     ,
          COUNT_TYPE    ,
          TYPE_TYPE     ,
          INDICES_TYPE  ,
          DRAWCOUNT_TYPE>(
              mode     ,
              count    ,
              type     ,
              indices  ,
              drawcount);
    }
    template<
      typename MODE_TYPE          = GLenum ,
      typename FIRST_TYPE         = GLint  ,
      typename COUNT_TYPE         = GLsizei,
      typename INSTANCECOUNT_TYPE = GLsizei,
      typename BASEINSTANCE_TYPE  = GLuint >
    inline DrawArraysInstancedBaseInstance<
      MODE_TYPE         ,
      FIRST_TYPE        ,
      COUNT_TYPE        ,
      INSTANCECOUNT_TYPE,
      BASEINSTANCE_TYPE >* newDrawArraysInstancedBaseInstance(
        MODE_TYPE          const&mode         ,
        FIRST_TYPE         const&first        ,
        COUNT_TYPE         const&count        ,
        INSTANCECOUNT_TYPE const&instancecount,
        BASEINSTANCE_TYPE  const&baseinstance ){
        return new DrawArraysInstancedBaseInstance<
          MODE_TYPE         ,
          FIRST_TYPE        ,
          COUNT_TYPE        ,
          INSTANCECOUNT_TYPE,
          BASEINSTANCE_TYPE >(
              mode         ,
              first        ,
              count        ,
              instancecount,
              baseinstance );
    }
    template<
      typename MODE_TYPE          = GLenum ,
      typename FIRST_TYPE         = GLint  ,
      typename COUNT_TYPE         = GLsizei,
      typename INSTANCECOUNT_TYPE = GLsizei>
    inline DrawArraysInstanced<
      MODE_TYPE         ,
      FIRST_TYPE        ,
      COUNT_TYPE        ,
      INSTANCECOUNT_TYPE>* newDrawArraysInstanced(
        MODE_TYPE          const&mode         ,
        FIRST_TYPE         const&first        ,
        COUNT_TYPE         const&count        ,
        INSTANCECOUNT_TYPE const&instancecount){
        return new DrawArraysInstanced<
          MODE_TYPE         ,
          FIRST_TYPE        ,
          COUNT_TYPE        ,
          INSTANCECOUNT_TYPE>(
              mode         ,
              first        ,
              count        ,
              instancecount);
    }
    template<
      typename WIDTH_TYPE  = GLsizei      ,
      typename HEIGHT_TYPE = GLsizei      ,
      typename FORMAT_TYPE = GLenum       ,
      typename TYPE_TYPE   = GLenum       ,
      typename PIXELS_TYPE = const GLvoid*>
    inline DrawPixels<
      WIDTH_TYPE ,
      HEIGHT_TYPE,
      FORMAT_TYPE,
      TYPE_TYPE  ,
      PIXELS_TYPE>* newDrawPixels(
        WIDTH_TYPE  const&width ,
        HEIGHT_TYPE const&height,
        FORMAT_TYPE const&format,
        TYPE_TYPE   const&type  ,
        PIXELS_TYPE const&pixels){
        return new DrawPixels<
          WIDTH_TYPE ,
          HEIGHT_TYPE,
          FORMAT_TYPE,
          TYPE_TYPE  ,
          PIXELS_TYPE>(
              width ,
              height,
              format,
              type  ,
              pixels);
    }
    template<
      typename MODE_TYPE          = GLenum     ,
      typename COUNT_TYPE         = GLsizei    ,
      typename TYPE_TYPE          = GLenum     ,
      typename INDICES_TYPE       = const void*,
      typename INSTANCECOUNT_TYPE = GLsizei    ,
      typename BASEVERTEX_TYPE    = GLint      ,
      typename BASEINSTANCE_TYPE  = GLuint     >
    inline DrawElementsInstancedBaseVertexBaseInstance<
      MODE_TYPE         ,
      COUNT_TYPE        ,
      TYPE_TYPE         ,
      INDICES_TYPE      ,
      INSTANCECOUNT_TYPE,
      BASEVERTEX_TYPE   ,
      BASEINSTANCE_TYPE >* newDrawElementsInstancedBaseVertexBaseInstance(
        MODE_TYPE          const&mode         ,
        COUNT_TYPE         const&count        ,
        TYPE_TYPE          const&type         ,
        INDICES_TYPE       const&indices      ,
        INSTANCECOUNT_TYPE const&instancecount,
        BASEVERTEX_TYPE    const&basevertex   ,
        BASEINSTANCE_TYPE  const&baseinstance ){
        return new DrawElementsInstancedBaseVertexBaseInstance<
          MODE_TYPE         ,
          COUNT_TYPE        ,
          TYPE_TYPE         ,
          INDICES_TYPE      ,
          INSTANCECOUNT_TYPE,
          BASEVERTEX_TYPE   ,
          BASEINSTANCE_TYPE >(
              mode         ,
              count        ,
              type         ,
              indices      ,
              instancecount,
              basevertex   ,
              baseinstance );
    }
    template<
      typename MODE_TYPE       = GLenum     ,
      typename COUNT_TYPE      = GLsizei    ,
      typename TYPE_TYPE       = GLenum     ,
      typename INDICES_TYPE    = const void*,
      typename BASEVERTEX_TYPE = GLint      >
    inline DrawElementsBaseVertex<
      MODE_TYPE      ,
      COUNT_TYPE     ,
      TYPE_TYPE      ,
      INDICES_TYPE   ,
      BASEVERTEX_TYPE>* newDrawElementsBaseVertex(
        MODE_TYPE       const&mode      ,
        COUNT_TYPE      const&count     ,
        TYPE_TYPE       const&type      ,
        INDICES_TYPE    const&indices   ,
        BASEVERTEX_TYPE const&basevertex){
        return new DrawElementsBaseVertex<
          MODE_TYPE      ,
          COUNT_TYPE     ,
          TYPE_TYPE      ,
          INDICES_TYPE   ,
          BASEVERTEX_TYPE>(
              mode      ,
              count     ,
              type      ,
              indices   ,
              basevertex);
    }
    template<
      typename MODE_TYPE    = GLenum       ,
      typename START_TYPE   = GLuint       ,
      typename END_TYPE     = GLuint       ,
      typename COUNT_TYPE   = GLsizei      ,
      typename TYPE_TYPE    = GLenum       ,
      typename INDICES_TYPE = const GLvoid*>
    inline DrawRangeElements<
      MODE_TYPE   ,
      START_TYPE  ,
      END_TYPE    ,
      COUNT_TYPE  ,
      TYPE_TYPE   ,
      INDICES_TYPE>* newDrawRangeElements(
        MODE_TYPE    const&mode   ,
        START_TYPE   const&start  ,
        END_TYPE     const&end    ,
        COUNT_TYPE   const&count  ,
        TYPE_TYPE    const&type   ,
        INDICES_TYPE const&indices){
        return new DrawRangeElements<
          MODE_TYPE   ,
          START_TYPE  ,
          END_TYPE    ,
          COUNT_TYPE  ,
          TYPE_TYPE   ,
          INDICES_TYPE>(
              mode   ,
              start  ,
              end    ,
              count  ,
              type   ,
              indices);
    }
    template<
      typename PNAME_TYPE  = GLenum        ,
      typename VALUES_TYPE = const GLfloat*>
    inline PatchParameterfv<
      PNAME_TYPE ,
      VALUES_TYPE>* newPatchParameterfv(
        PNAME_TYPE  const&pname ,
        VALUES_TYPE const&values){
        return new PatchParameterfv<
          PNAME_TYPE ,
          VALUES_TYPE>(
              pname ,
              values);
    }
    template<
      typename PNAME_TYPE = GLenum,
      typename VALUE_TYPE = GLint >
    inline PatchParameteri<
      PNAME_TYPE,
      VALUE_TYPE>* newPatchParameteri(
        PNAME_TYPE const&pname,
        VALUE_TYPE const&value){
        return new PatchParameteri<
          PNAME_TYPE,
          VALUE_TYPE>(
              pname,
              value);
    }
    template<
      typename MODE_TYPE = GLenum,
      typename ID_TYPE   = GLuint>
    inline DrawTransformFeedback<
      MODE_TYPE,
      ID_TYPE  >* newDrawTransformFeedback(
        MODE_TYPE const&mode,
        ID_TYPE   const&id  ){
        return new DrawTransformFeedback<
          MODE_TYPE,
          ID_TYPE  >(
              mode,
              id  );
    }
    template<
      typename MODE_TYPE   = GLenum,
      typename ID_TYPE     = GLuint,
      typename STREAM_TYPE = GLuint>
    inline DrawTransformFeedbackStream<
      MODE_TYPE  ,
      ID_TYPE    ,
      STREAM_TYPE>* newDrawTransformFeedbackStream(
        MODE_TYPE   const&mode  ,
        ID_TYPE     const&id    ,
        STREAM_TYPE const&stream){
        return new DrawTransformFeedbackStream<
          MODE_TYPE  ,
          ID_TYPE    ,
          STREAM_TYPE>(
              mode  ,
              id    ,
              stream);
    }
    template<
      typename MODE_TYPE          = GLenum ,
      typename ID_TYPE            = GLuint ,
      typename STREAM_TYPE        = GLuint ,
      typename INSTANCECOUNT_TYPE = GLsizei>
    inline DrawTransformFeedbackStreamInstanced<
      MODE_TYPE         ,
      ID_TYPE           ,
      STREAM_TYPE       ,
      INSTANCECOUNT_TYPE>* newDrawTransformFeedbackStreamInstanced(
        MODE_TYPE          const&mode         ,
        ID_TYPE            const&id           ,
        STREAM_TYPE        const&stream       ,
        INSTANCECOUNT_TYPE const&instancecount){
        return new DrawTransformFeedbackStreamInstanced<
          MODE_TYPE         ,
          ID_TYPE           ,
          STREAM_TYPE       ,
          INSTANCECOUNT_TYPE>(
              mode         ,
              id           ,
              stream       ,
              instancecount);
    }
    template<
      typename MODE_TYPE     = GLenum     ,
      typename INDIRECT_TYPE = const void*>
    inline DrawArraysIndirect<
      MODE_TYPE    ,
      INDIRECT_TYPE>* newDrawArraysIndirect(
        MODE_TYPE     const&mode    ,
        INDIRECT_TYPE const&indirect){
        return new DrawArraysIndirect<
          MODE_TYPE    ,
          INDIRECT_TYPE>(
              mode    ,
              indirect);
    }
    template<
      typename MODE_TYPE     = GLenum     ,
      typename TYPE_TYPE     = GLenum     ,
      typename INDIRECT_TYPE = const void*>
    inline DrawElementsIndirect<
      MODE_TYPE    ,
      TYPE_TYPE    ,
      INDIRECT_TYPE>* newDrawElementsIndirect(
        MODE_TYPE     const&mode    ,
        TYPE_TYPE     const&type    ,
        INDIRECT_TYPE const&indirect){
        return new DrawElementsIndirect<
          MODE_TYPE    ,
          TYPE_TYPE    ,
          INDIRECT_TYPE>(
              mode    ,
              type    ,
              indirect);
    }
    template<
      typename MODE_TYPE  = GLenum ,
      typename FIRST_TYPE = GLint  ,
      typename COUNT_TYPE = GLsizei>
    inline DrawArrays<
      MODE_TYPE ,
      FIRST_TYPE,
      COUNT_TYPE>* newDrawArrays(
        MODE_TYPE  const&mode ,
        FIRST_TYPE const&first,
        COUNT_TYPE const&count){
        return new DrawArrays<
          MODE_TYPE ,
          FIRST_TYPE,
          COUNT_TYPE>(
              mode ,
              first,
              count);
    }
    template<
      typename MODE_TYPE          = GLenum     ,
      typename COUNT_TYPE         = GLsizei    ,
      typename TYPE_TYPE          = GLenum     ,
      typename INDICES_TYPE       = const void*,
      typename INSTANCECOUNT_TYPE = GLsizei    >
    inline DrawElementsInstanced<
      MODE_TYPE         ,
      COUNT_TYPE        ,
      TYPE_TYPE         ,
      INDICES_TYPE      ,
      INSTANCECOUNT_TYPE>* newDrawElementsInstanced(
        MODE_TYPE          const&mode         ,
        COUNT_TYPE         const&count        ,
        TYPE_TYPE          const&type         ,
        INDICES_TYPE       const&indices      ,
        INSTANCECOUNT_TYPE const&instancecount){
        return new DrawElementsInstanced<
          MODE_TYPE         ,
          COUNT_TYPE        ,
          TYPE_TYPE         ,
          INDICES_TYPE      ,
          INSTANCECOUNT_TYPE>(
              mode         ,
              count        ,
              type         ,
              indices      ,
              instancecount);
    }
    template<
      typename MODE_TYPE      = GLenum     ,
      typename INDIRECT_TYPE  = const void*,
      typename DRAWCOUNT_TYPE = GLsizei    ,
      typename STRIDE_TYPE    = GLsizei    >
    inline MultiDrawArraysIndirect<
      MODE_TYPE     ,
      INDIRECT_TYPE ,
      DRAWCOUNT_TYPE,
      STRIDE_TYPE   >* newMultiDrawArraysIndirect(
        MODE_TYPE      const&mode     ,
        INDIRECT_TYPE  const&indirect ,
        DRAWCOUNT_TYPE const&drawcount,
        STRIDE_TYPE    const&stride   ){
        return new MultiDrawArraysIndirect<
          MODE_TYPE     ,
          INDIRECT_TYPE ,
          DRAWCOUNT_TYPE,
          STRIDE_TYPE   >(
              mode     ,
              indirect ,
              drawcount,
              stride   );
    }
    template<
      typename MODE_TYPE      = GLenum     ,
      typename TYPE_TYPE      = GLenum     ,
      typename INDIRECT_TYPE  = const void*,
      typename DRAWCOUNT_TYPE = GLsizei    ,
      typename STRIDE_TYPE    = GLsizei    >
    inline MultiDrawElementsIndirect<
      MODE_TYPE     ,
      TYPE_TYPE     ,
      INDIRECT_TYPE ,
      DRAWCOUNT_TYPE,
      STRIDE_TYPE   >* newMultiDrawElementsIndirect(
        MODE_TYPE      const&mode     ,
        TYPE_TYPE      const&type     ,
        INDIRECT_TYPE  const&indirect ,
        DRAWCOUNT_TYPE const&drawcount,
        STRIDE_TYPE    const&stride   ){
        return new MultiDrawElementsIndirect<
          MODE_TYPE     ,
          TYPE_TYPE     ,
          INDIRECT_TYPE ,
          DRAWCOUNT_TYPE,
          STRIDE_TYPE   >(
              mode     ,
              type     ,
              indirect ,
              drawcount,
              stride   );
    }
    template<
      typename MODE_TYPE          = GLenum     ,
      typename COUNT_TYPE         = GLsizei    ,
      typename TYPE_TYPE          = GLenum     ,
      typename INDICES_TYPE       = const void*,
      typename INSTANCECOUNT_TYPE = GLsizei    ,
      typename BASEVERTEX_TYPE    = GLint      >
    inline DrawElementsInstancedBaseVertex<
      MODE_TYPE         ,
      COUNT_TYPE        ,
      TYPE_TYPE         ,
      INDICES_TYPE      ,
      INSTANCECOUNT_TYPE,
      BASEVERTEX_TYPE   >* newDrawElementsInstancedBaseVertex(
        MODE_TYPE          const&mode         ,
        COUNT_TYPE         const&count        ,
        TYPE_TYPE          const&type         ,
        INDICES_TYPE       const&indices      ,
        INSTANCECOUNT_TYPE const&instancecount,
        BASEVERTEX_TYPE    const&basevertex   ){
        return new DrawElementsInstancedBaseVertex<
          MODE_TYPE         ,
          COUNT_TYPE        ,
          TYPE_TYPE         ,
          INDICES_TYPE      ,
          INSTANCECOUNT_TYPE,
          BASEVERTEX_TYPE   >(
              mode         ,
              count        ,
              type         ,
              indices      ,
              instancecount,
              basevertex   );
    }
    template<
      typename MODE_TYPE    = GLenum       ,
      typename COUNT_TYPE   = GLsizei      ,
      typename TYPE_TYPE    = GLenum       ,
      typename INDICES_TYPE = const GLvoid*>
    inline DrawElements<
      MODE_TYPE   ,
      COUNT_TYPE  ,
      TYPE_TYPE   ,
      INDICES_TYPE>* newDrawElements(
        MODE_TYPE    const&mode   ,
        COUNT_TYPE   const&count  ,
        TYPE_TYPE    const&type   ,
        INDICES_TYPE const&indices){
        return new DrawElements<
          MODE_TYPE   ,
          COUNT_TYPE  ,
          TYPE_TYPE   ,
          INDICES_TYPE>(
              mode   ,
              count  ,
              type   ,
              indices);
    }
    template<
      typename MODE_TYPE          = GLenum ,
      typename ID_TYPE            = GLuint ,
      typename INSTANCECOUNT_TYPE = GLsizei>
    inline DrawTransformFeedbackInstanced<
      MODE_TYPE         ,
      ID_TYPE           ,
      INSTANCECOUNT_TYPE>* newDrawTransformFeedbackInstanced(
        MODE_TYPE          const&mode         ,
        ID_TYPE            const&id           ,
        INSTANCECOUNT_TYPE const&instancecount){
        return new DrawTransformFeedbackInstanced<
          MODE_TYPE         ,
          ID_TYPE           ,
          INSTANCECOUNT_TYPE>(
              mode         ,
              id           ,
              instancecount);
    }
    template<
      typename MODE_TYPE       = GLenum     ,
      typename START_TYPE      = GLuint     ,
      typename END_TYPE        = GLuint     ,
      typename COUNT_TYPE      = GLsizei    ,
      typename TYPE_TYPE       = GLenum     ,
      typename INDICES_TYPE    = const void*,
      typename BASEVERTEX_TYPE = GLint      >
    inline DrawRangeElementsBaseVertex<
      MODE_TYPE      ,
      START_TYPE     ,
      END_TYPE       ,
      COUNT_TYPE     ,
      TYPE_TYPE      ,
      INDICES_TYPE   ,
      BASEVERTEX_TYPE>* newDrawRangeElementsBaseVertex(
        MODE_TYPE       const&mode      ,
        START_TYPE      const&start     ,
        END_TYPE        const&end       ,
        COUNT_TYPE      const&count     ,
        TYPE_TYPE       const&type      ,
        INDICES_TYPE    const&indices   ,
        BASEVERTEX_TYPE const&basevertex){
        return new DrawRangeElementsBaseVertex<
          MODE_TYPE      ,
          START_TYPE     ,
          END_TYPE       ,
          COUNT_TYPE     ,
          TYPE_TYPE      ,
          INDICES_TYPE   ,
          BASEVERTEX_TYPE>(
              mode      ,
              start     ,
              end       ,
              count     ,
              type      ,
              indices   ,
              basevertex);
    }
  }
}
