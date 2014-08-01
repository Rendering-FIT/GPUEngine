#ifndef _VERTEXARRAYOBJECTSCOMMANDS_H_
#define _VERTEXARRAYOBJECTSCOMMANDS_H_

#include<geGL/Standard/OpenGL.h>

namespace ge
{
  namespace gl
  {
    class GE_EXPORT GenVertexArrays: public Command
    {
      public:
        GLsizei  n;
        GLuint  *arrays;
        GenVertexArrays(
            GLsizei  n,
            GLuint  *arrays);
        void apply();
    };
    class GE_EXPORT DeleteVertexArrays: public Command
    {
      public:
        GLsizei  n;
        GLuint  *arrays;
        DeleteVertexArrays(
            GLsizei  n,
            GLuint  *arrays);
        void apply();
    };
    class GE_EXPORT BindVertexArray: public Command
    {
      public:
        GLuint array;
        BindVertexArray(GLuint array);
        void apply();
    };
  }//ogl
}//ge

#endif//_VERTEXARRAYOBJECTSCOMMANDS_H_
