#pragma once

#include<geGL/OpenGLObject.h>

namespace ge{
  namespace gl{
    class GEGL_EXPORT AsynchronousQuery: public OpenGLObject{
      public:
        enum ResultSize{
          INT32,
          UINT32,
          INT64,
          UINT64
        };
      public:
        AsynchronousQuery();
        void create(
            GLenum     target,
            GLenum     waitingType,
            ResultSize resultSize);
        AsynchronousQuery(
            GLenum     target,
            GLenum     waitingType,
            ResultSize resultSize);
        AsynchronousQuery(
            AsynchronousQuery*existingQuery);
        AsynchronousQuery(
            FunctionTablePointer const&table,
            GLenum     target,
            GLenum     waitingType,
            ResultSize resultSize);
        AsynchronousQuery(
            FunctionTablePointer const&table,
            AsynchronousQuery*existingQuery);
        ~AsynchronousQuery();
        void begin();
        void end();
        void begin(GLuint index);
        void end(GLuint index);
        GLuint64 getui64();
        GLint64  geti64();
        GLuint   getui();
        GLint    geti();
        GLenum   getTarget();
        GLenum   getWaitingType();
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
        GLint      _datai32; ///<obtained data
        GLuint     _dataui32;///<obtained data
        GLint64    _datai64; ///<obtained data
        GLuint64   _dataui64;///<obtained data
        ResultSize _resultSize;

    };
  }//gl
}//ge

