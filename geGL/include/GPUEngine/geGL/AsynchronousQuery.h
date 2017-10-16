#pragma once

#include<GPUEngine/geGL/OpenGLObject.h>

class GEGL_EXPORT ge::gl::AsynchronousQuery: public OpenGLObject{
  public:
    enum ResultSize{
      INT32 ,
      UINT32,
      INT64 ,
      UINT64,
    };
    AsynchronousQuery();
    void create(
        GLenum     const&target     ,
        GLenum     const&waitingType,
        ResultSize const&resultSize );
    AsynchronousQuery(
        GLenum     const&target     ,
        GLenum     const&waitingType,
        ResultSize const&resultSize );
    AsynchronousQuery(
        AsynchronousQuery const*const&existingQuery);
    AsynchronousQuery(
        FunctionTablePointer const&table      ,
        GLenum               const&target     ,
        GLenum               const&waitingType,
        ResultSize           const&resultSize );
    AsynchronousQuery(
        FunctionTablePointer       const&table        ,
        AsynchronousQuery    const*const&existingQuery);
    ~AsynchronousQuery();
    void begin();
    void end  ();
    void begin(GLuint const&index);
    void end  (GLuint const&index);
    GLuint64 getui64       ()const;
    GLint64  geti64        ()const;
    GLuint   getui         ()const;
    GLint    geti          ()const;
    GLenum   getTarget     ()const;
    GLenum   getWaitingType()const;
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

