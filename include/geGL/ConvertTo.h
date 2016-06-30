#pragma once

#include<geCore/Dtemplates.h>
#include<geGL/Program.h>
#include<geGL/Buffer.h>
#include<geGL/VertexArray.h>
#include<geGL/Framebuffer.h>
#include<geGL/Texture.h>

namespace ge{
  namespace core{
    template<typename TYPE>
      inline TYPE convertTo(ge::gl::Buffer*const&buffer){
        return buffer->getId();
      }
    template<typename TYPE>
      inline TYPE convertTo(std::shared_ptr<ge::gl::Buffer>const&sharedBuffer){
        return sharedBuffer->getId();
      }
    template<typename TYPE>
      inline TYPE convertTo(ge::gl::Program*const&program){
        return program->getId();
      }
    template<typename TYPE>
      inline TYPE convertTo(std::shared_ptr<ge::gl::Program>const&sharedProgram){
        return sharedProgram->getId();
      }
    template<typename TYPE>
      inline TYPE convertTo(ge::gl::VertexArray*const&vertexArray){
        return vertexArray->getId();
      }
    template<typename TYPE>
      inline TYPE convertTo(std::shared_ptr<ge::gl::VertexArray>const&sharedVertexArray){
        return sharedVertexArray->getId();
      }
    template<typename TYPE>
      inline TYPE convertTo(ge::gl::Framebuffer*const&framebuffer){
        return framebuffer->getId();
      }
    template<typename TYPE>
      inline TYPE convertTo(std::shared_ptr<ge::gl::Framebuffer>const&sharedFramebuffer){
        return sharedFramebuffer->getId();
      }
    template<typename TYPE>
      inline TYPE convertTo(ge::gl::Texture*const&texture){
        return texture->getId();
      }
    template<typename TYPE>
      inline TYPE convertTo(std::shared_ptr<ge::gl::Texture>const&sharedTexture){
        return sharedTexture->getId();
      }

  }
}

