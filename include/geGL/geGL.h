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
#include<geGL/OpenGLFunctionTable.h>
#include<geGL/FunctionLoaderInterface.h>
#include<geGL/DefaultLoader.h>

namespace ge{
  namespace gl{
    GEGL_EXPORT void init(
        std::shared_ptr<opengl::FunctionLoaderInterface>const&loader = nullptr);
    namespace opengl{
      GEGL_EXPORT FunctionTablePointer    const& getDefaultFunctionTable();
      GEGL_EXPORT FunctionProviderPointer const& getDefaultFunctionProvider();
    }
  }
}


