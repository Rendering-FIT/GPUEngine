#pragma once

#include<geGL/AsynchronousQuery.h>
#include<geGL/Buffer.h>
#include<geGL/Framebuffer.h>
#include<geGL/Shader.h>
#include<geGL/Program.h>
#include<geGL/VertexArray.h>
#include<geGL/ProgramPipeline.h>
#include<geGL/Texture.h>
#include<geGL/Sampler.h>
#include<geGL/Renderbuffer.h>
#include<geGL/DebugMessage.h>
#include<geGL/OpenGLFunctionTable.h>
#include<geGL/FunctionLoaderInterface.h>
#include<geGL/DefaultLoader.h>

namespace ge{
  namespace gl{
    GEGL_EXPORT void init(
        std::shared_ptr<opengl::FunctionLoaderInterface>const&loader = nullptr);
  }
}


