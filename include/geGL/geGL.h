#pragma once

#include<geGL/AsynchronousQueryObject.h>
#include<geGL/BufferObject.h>
#include<geGL/FramebufferObject.h>
#include<geGL/ShaderObject.h>
#include<geGL/ProgramObject.h>
#include<geGL/VertexArrayObject.h>
#include<geGL/ProgramPipelineObject.h>
#include<geGL/TextureObject.h>
#include<geGL/SamplerObject.h>
#include<geGL/RenderbufferObject.h>
#include<geGL/DebugMessage.h>
#include<geGL/LoadOpenGLFunctions.h>
#include<geGL/OpenGLFunctionTable.h>
#include<geGL/FunctionLoaderInterface.h>

namespace ge{
  namespace gl{
    GEGL_EXPORT void init(
        std::shared_ptr<opengl::FunctionLoaderInterface>const&loader = nullptr);
    namespace opengl{
      class DefaultLoader: public ge::gl::opengl::FunctionLoaderInterface{
        public:
          DefaultLoader(ge::gl::opengl::GET_PROC_ADDRESS getProcAddress){
            this->m_getProcAddress = getProcAddress;
          }
          ~DefaultLoader(){}
          virtual FUNCTION_POINTER load(char const*fceName)const{
            return this->m_getProcAddress(fceName);
          }
        protected:
          ge::gl::opengl::GET_PROC_ADDRESS m_getProcAddress = nullptr;
      };

      GEGL_EXPORT FunctionTablePointer    const& getDefaultFunctionTable();
      GEGL_EXPORT FunctionProviderPointer const& getDefaultFunctionProvider();
    }
  }
}


