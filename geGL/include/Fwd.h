#pragma once

#include<memory>

namespace ge{
  namespace gl{
    class FunctionTable;
    using FunctionTablePointer = std::shared_ptr<FunctionTable const>;
    class FunctionLoaderInterface;
    using FunctionLoaderInterfacePointer = std::shared_ptr<FunctionLoaderInterface>;
    class Context;
    using ContextPointer = std::shared_ptr<Context>;
    class OpenGLObject;
    class Buffer;
    class Program;
    class Shader;
    class Texture;
    class VertexArray;
    class AsynchronousQuery;
    class Framebuffer;
    class ProgramPipeline;
    class Sampler;
    class Renderbuffer;
  }
}
