#pragma once

#include<geCore/dtemplates.h>
#include<geGL/ProgramObject.h>
#include<geGL/BufferObject.h>
#include<geGL/VertexArrayObject.h>
#include<geGL/FramebufferObject.h>
#include<geGL/TextureObject.h>

namespace ge{
  namespace core{
    template<typename TYPE>
      inline TYPE convertTo(ge::gl::BufferObject*const&bufferObject){
        return bufferObject->getId();
      }
    template<typename TYPE>
      inline TYPE convertTo(std::shared_ptr<ge::gl::BufferObject>const&sharedBufferObject){
        return sharedBufferObject->getId();
      }
    template<typename TYPE>
      inline TYPE convertTo(ge::gl::ProgramObject*const&programObject){
        return programObject->getId();
      }
    template<typename TYPE>
      inline TYPE convertTo(std::shared_ptr<ge::gl::ProgramObject>const&sharedProgramObject){
        return sharedProgramObject->getId();
      }
    template<typename TYPE>
      inline TYPE convertTo(ge::gl::VertexArrayObject*const&vertexArrayObject){
        return vertexArrayObject->getId();
      }
    template<typename TYPE>
      inline TYPE convertTo(std::shared_ptr<ge::gl::VertexArrayObject>const&sharedVertexArrayObject){
        return sharedVertexArrayObject->getId();
      }
    template<typename TYPE>
      inline TYPE convertTo(ge::gl::FramebufferObject*const&framebufferObject){
        return framebufferObject->getId();
      }
    template<typename TYPE>
      inline TYPE convertTo(std::shared_ptr<ge::gl::FramebufferObject>const&sharedFramebufferObject){
        return sharedFramebufferObject->getId();
      }
    template<typename TYPE>
      inline TYPE convertTo(ge::gl::TextureObject*const&textureObject){
        return textureObject->getId();
      }
    template<typename TYPE>
      inline TYPE convertTo(std::shared_ptr<ge::gl::TextureObject>const&sharedTextureObject){
        return sharedTextureObject->getId();
      }

  }
}

