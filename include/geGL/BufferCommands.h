#pragma once

#include<geGL/OpenGL.h>
#include<geGL/ProgramObject.h>
#include<geGL/BufferObject.h>

namespace ge{
  namespace gl{
    class GEGL_EXPORT BindBufferBase: public Command{
      protected:
        GLenum _target;
        GLuint _index ;
        GLuint _buffer;
      public:
        BindBufferBase(GLenum target,GLuint index,GLuint buffer);
        BindBufferBase(ge::gl::ProgramObject*program,std::string name,ge::gl::BufferObject*buffer);
        void apply();
        GLenum getTarget();
        GLuint getIndex ();
        GLuint getBuffer();
    };
  }
}
