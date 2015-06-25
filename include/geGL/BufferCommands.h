#pragma once

#include<geCore/Command.h>
#include<geGL/Export.h>
#include<GL/glew.h>
#include<geGL/ProgramObject.h>
#include<geGL/BufferObject.h>

namespace ge{
  namespace gl{
    class GEGL_EXPORT BindBufferBase: public ge::core::Command{
      protected:
        GLenum _target;
        GLuint _index ;
        GLuint _buffer;
      public:
        BindBufferBase(GLenum target,GLuint index,GLuint buffer);
        BindBufferBase(ge::gl::ProgramObject*program,std::string name,ge::gl::BufferObject*buffer);
        void operator()();
        GLenum getTarget();
        GLuint getIndex ();
        GLuint getBuffer();
    };
  }
}
