#pragma once

#include<geCore/Command.h>
#include<geGL/Export.h>
#include<GL/glew.h>
#include<geGL/BufferObject.h>
#include<geGL/ObjectCommands.h>

namespace ge{
  namespace gl{
    namespace bo{
      
      class BufferData{
        private:
          GLsizeiptr    _size;
          const GLvoid* _data;
        public:
          BufferData(
              GLsizeiptr    size = 0   ,
              const GLvoid* data = NULL);
          void set(
              GLsizeiptr    size = 0   ,
              const GLvoid* data = NULL);
          GLsizeiptr    getSize();
          const GLvoid* getData();
      };

      class GEGL_EXPORT Offset{
        protected:
          GLintptr _offset;
        public:
            Offset(GLintptr offset = 0);
            GLintptr getOffset();
            void     setOffset(GLintptr offset);
      };

      class GEGL_EXPORT Size{
        protected:
          GLsizeiptr _size;
        public:
          Size(GLsizeiptr size = 0);
          GLsizeiptr getSize();
          void       setSize(GLsizeiptr size);
      };

      class GEGL_EXPORT SizeOffset: public Offset, public Size{
      };

      class GEGL_EXPORT Map: public ge::core::Command, public Shared<BufferObject>{
        private:
          std::shared_ptr<GLvoid*>   _ptr   ;
          std::shared_ptr<GLbitfield>_access;
          std::shared_ptr<GLintptr>  _offset;
          std::shared_ptr<GLsizeiptr>_size  ;
        public:
          Map(
              std::shared_ptr<BufferObject>buffer                                   ,
              std::shared_ptr<GLvoid*>     ptr                                      ,
              GLbitfield                   access = GL_MAP_READ_BIT|GL_MAP_WRITE_BIT);
          Map(
              std::shared_ptr<BufferObject>buffer                                   ,
              std::shared_ptr<GLvoid*>     ptr                                      ,
              GLintptr                     offset                                   ,
              GLsizeiptr                   size                                     ,
              GLbitfield                   access = GL_MAP_READ_BIT|GL_MAP_WRITE_BIT);
          void operator()();
          std::shared_ptr<GLvoid*   >&getPtr();
          std::shared_ptr<GLbitfield>&getAccess();
          std::shared_ptr<GLintptr  >&getOffset();
          std::shared_ptr<GLsizeiptr>&getSize  ();
      };

      class GEGL_EXPORT Unmap: public ge::core::Command, public Shared<BufferObject>{
        public:
          Unmap(std::shared_ptr<BufferObject>buffer);
          void operator()();
      };

      class GEGL_EXPORT SetData: public ge::core::Command, public Shared<BufferObject>{
        private:
          const GLvoid*_data  ;
          GLsizeiptr   _size  ;
          GLintptr     _offset;
        public:
          SetData(const GLvoid*data,GLsizeiptr size,GLintptr offset);


      };
    }
  }
}
