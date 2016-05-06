#pragma once

#include<geGL/OpenGLObject.h>

namespace ge{
  namespace gl{
    class GEGL_EXPORT AsynchronousQueryObject: public OpenGLObject
    {
      public:
        enum ResultSize{
          INT32,
          UINT32,
          INT64,
          UINT64
        };
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
      public:
        /**
         * @brief Constructor
         *
         * @param target type of query
         * @param waitingType type of waiting for results
         * @param resultSize size and type of result
         */
        AsynchronousQueryObject(
            GLenum     target,
            GLenum     waitingType,
            ResultSize resultSize);
        /**
         * @brief Constructor of query from existing query
         *
         * @param existingQuery This query has already been created
         */
        AsynchronousQueryObject(
            AsynchronousQueryObject*existingQuery);
#if defined(REPLACE_GLEW)
        AsynchronousQueryObject(
            opengl::FunctionTablePointer const&table,
            GLenum     target,
            GLenum     waitingType,
            ResultSize resultSize);
        AsynchronousQueryObject(
            opengl::FunctionTablePointer const&table,
            AsynchronousQueryObject*existingQuery);
#endif
        /**
         * @brief Destructor
         */
        ~AsynchronousQueryObject();
        /**
         * @brief Begins query
         */
        void begin();
        /**
         * @brief Ends query
         */
        void end();
        /**
         * @brief Begins indexed query
         *
         * @param index index of query
         */
        void begin(GLuint index);
        /**
         * @brief Ends indexed query
         *
         * @param index index of query
         */
        void end(GLuint index);
        /**
         * @brief Gets results
         *
         * @return query uint64 results
         */
        GLuint64 getui64();
        /**
         * @brief Gets result
         *
         * @return query int64 results
         */
        GLint64  geti64();
        /**
         * @brief Gets result
         *
         * @return query uint resutls
         */
        GLuint   getui();
        /**
         * @brief Gets result
         *
         * @return query int results
         */
        GLint    geti();
        /**
         * @brief gets target of query
         *
         * @return target
         */
        GLenum   getTarget();
        /**
         * @brief gets type of waiting
         *
         * @return wainting type
         */
        GLenum   getWaitingType();

    };
  }//gl
}//ge

