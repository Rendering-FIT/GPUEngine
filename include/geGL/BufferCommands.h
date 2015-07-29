#pragma once

#include<geCore/Command.h>
#include<geGL/Export.h>
#include<GL/glew.h>
#include<geGL/ProgramObject.h>
#include<geGL/BufferObject.h>

namespace ge{
  namespace core{
    template<typename TYPE>
      inline TYPE convertTo(std::shared_ptr<ge::gl::BufferObject>const&sharedBufferObject){
        return sharedBufferObject->getId();
      }
  }
}

namespace ge{
  namespace gl{

    DEF_NAMED_TEMPLATE_ATTRIBUTE(Ptr   );
    DEF_NAMED_TEMPLATE_ATTRIBUTE(Buffer);
    DEF_NAMED_TEMPLATE_ATTRIBUTE(Target);
    DEF_NAMED_TEMPLATE_ATTRIBUTE(Access);
    DEF_NAMED_TEMPLATE_ATTRIBUTE(Index );

    template<typename BUFFER=GLuint,typename TARGET=GLenum>
      class BindBuffer: public Buffer<BUFFER>,public Target<TARGET>,public ge::core::Command{
        public:
          BindBuffer(BUFFER const&buffer,TARGET const&target):
            Buffer<BUFFER>(buffer),Target<TARGET>(target){}
          virtual~BindBuffer(){}
          virtual void operator()(){
            glBindBuffer(
                ge::core::convertTo<GLenum>(this->Target<TARGET>::_value),
                ge::core::convertTo<GLuint>(this->Buffer<BUFFER>::_value));
          }
      };

    template<typename PTR=GLvoid*,typename TARGET=GLenum,typename ACCESS=GLenum>
      class MapBuffer: public Ptr<PTR>,public Target<TARGET>,public Access<ACCESS>{
        public:
          MapBuffer(PTR const&ptr,TARGET const&target,ACCESS const&access):
            Ptr<PTR>(ptr),Target<TARGET>(target),Access<ACCESS>(access){}
          virtual~MapBuffer(){}
          virtual void operator()(){
            ge::core::convertFrom<GLvoid*>(this->Ptr<PTR>::_value,glMapBuffer(
                  ge::core::convertTo<GLenum>(this->Target<TARGET>::_value),
                  ge::core::convertTo<GLenum>(this->Access<ACCESS>::_value)));
          }
      };

    template<typename TARGET=GLenum>
      class UnmapBuffer: public Target<TARGET>, public ge::core::Command{
        public:
          UnmapBuffer(TARGET const&ptr);
          virtual~UnmapBuffer(){}
          virtual void operator()(){
            glUnmapBuffer(ge::core::convertTo(this->Target<TARGET>::_value));
          }
      };

    template<typename TARGET=GLenum,typename INDEX=GLuint,typename BUFFER=GLuint>
      class BindBufferBase: public Target<TARGET>,public Index<INDEX>,public Buffer<BUFFER>,public ge::core::Command{
        public:
          BindBufferBase(TARGET const&target,INDEX const&index,BUFFER const&buffer):
            Target<TARGET>(target),Index<INDEX>(index),Buffer<BUFFER>(buffer){}
          virtual~BindBufferBase(){}
          virtual void operator()(){
            glBindBufferBase(
                ge::core::convertTo<GLenum>(this->Target<TARGET>::_value),
                ge::core::convertTo<GLuint>(this->Index <INDEX >::_value),
                ge::core::convertTo<GLuint>(this->Buffer<BUFFER>::_value));
          }
      };
  }
}
