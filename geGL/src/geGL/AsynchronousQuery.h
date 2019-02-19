#pragma once

#include<geGL/OpenGLObject.h>

class ge::gl::AsynchronousQuery: public OpenGLObject{
  public:
    enum ResultSize{
      INT32 ,
      UINT32,
      INT64 ,
      UINT64,
    };
	GEGL_EXPORT AsynchronousQuery();
	GEGL_EXPORT void create(
        GLenum     const&target     ,
        GLenum     const&waitingType,
        ResultSize const&resultSize );
	GEGL_EXPORT AsynchronousQuery(
        GLenum     const&target     ,
        GLenum     const&waitingType,
        ResultSize const&resultSize );
	GEGL_EXPORT AsynchronousQuery(
        AsynchronousQuery const*const&existingQuery);
	GEGL_EXPORT AsynchronousQuery(
        FunctionTablePointer const&table      ,
        GLenum               const&target     ,
        GLenum               const&waitingType,
        ResultSize           const&resultSize );
	GEGL_EXPORT AsynchronousQuery(
        FunctionTablePointer       const&table        ,
        AsynchronousQuery    const*const&existingQuery);
	GEGL_EXPORT ~AsynchronousQuery();
	GEGL_EXPORT void begin();
	GEGL_EXPORT void end  ();
	GEGL_EXPORT void begin(GLuint const&index);
	GEGL_EXPORT void end  (GLuint const&index);
	GEGL_EXPORT GLuint64 getui64       ()const;
	GEGL_EXPORT GLint64  geti64        ()const;
	GEGL_EXPORT GLuint   getui         ()const;
	GEGL_EXPORT GLint    geti          ()const;
	GEGL_EXPORT GLenum   getTarget     ()const;
	GEGL_EXPORT GLenum   getWaitingType()const;
  protected:
    /**
     * @brief 
     * GL_ANY_SAMPLES_PASSED
     * GL_ANY_SAMPLES_PASSED_CONSERVATIVE
     * GL_PRIMITIVES_GENERATED
     * GL_SAMPLES_PASSED
     * GL_TIME_ELAPSED
     * GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN
     */
    GLenum _target;
    /**
     * @brief 
     * GL_QUERY_RESULT
     * GL_QUERY_RESULT_AVAILABLE
     * GL_QUERy_RESULT_NO_WAIT
     */
    GLenum     _waitingType;
    GLint      _datai32    ;///<obtained data
    GLuint     _dataui32   ;///<obtained data
    GLint64    _datai64    ;///<obtained data
    GLuint64   _dataui64   ;///<obtained data
    ResultSize _resultSize ;

};

