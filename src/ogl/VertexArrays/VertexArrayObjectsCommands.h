#ifndef _VERTEXARRAYOBJECTSCOMMANDS_H_
#define _VERTEXARRAYOBJECTSCOMMANDS_H_

#include"../../ogl/Standard/OpenGL.h"

namespace ge
{
  namespace ogl
  {
    class GenVertexArrays: public Command
    {
      public:
        GLsizei  n;
        GLuint  *arrays;
        GenVertexArrays(
            GLsizei  n,
            GLuint  *arrays);
        void apply();
    };
    class DeleteVertexArrays: public Command
    {
      public:
        GLsizei  n;
        GLuint  *arrays;
        DeleteVertexArrays(
            GLsizei  n,
            GLuint  *arrays);
        void apply();
    };
    class BindVertexArray: public Command
    {
      public:
        GLuint array;
        BindVertexArray(GLuint array);
        void apply();
    };
  }//ogl
}//ge

#endif//_VERTEXARRAYOBJECTSCOMMANDS_H_
