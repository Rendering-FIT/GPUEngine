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

namespace ge{
  namespace gl{

#if defined(REPLACE_GLEW)
    GEGL_EXPORT void init(
        opengl::GET_PROC_ADDRESS getProcAddress = nullptr);
    namespace opengl{
      GEGL_EXPORT FunctionTablePointer prepareFunctionTable(
          GET_PROC_ADDRESS getProcAddress);
      GEGL_EXPORT FunctionTablePointer const& getDefaultFunctionTable();
    }
#else
    GEGL_EXPORT void init();
#endif
  }
}


