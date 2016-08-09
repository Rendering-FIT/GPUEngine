/*!
 * OpenGL part of geGL library contains two main objects - FunctionTable and Context
 */

#pragma once

#include<geGL/Export.h>

#include<stdint.h>
#include<stddef.h>
#include<geGL/Generated/OpenGLTypes.h>
#include<geGL/Generated/OpenGLConstants.h>
#include<memory>

namespace ge{
  namespace gl{
    class FunctionTable;
    using FunctionTablePointer = std::shared_ptr<FunctionTable>;
    class Context;
    using ContextPointer = std::shared_ptr<Context>;
    class FunctionLoaderInterface;
    using FunctionLoaderInterfacePointer = std::shared_ptr<FunctionLoaderInterface>;
    GEGL_EXPORT FunctionTablePointer    const& getDefaultFunctionTable();
    GEGL_EXPORT ContextPointer const& getDefaultContext();
    GEGL_EXPORT void setDefaultFunctionTable   (FunctionTablePointer const&table   );
    GEGL_EXPORT void setDefaultContext         (ContextPointer       const&provider);
    GEGL_EXPORT FunctionTablePointer    createTable  (FunctionLoaderInterfacePointer const&loader);
    GEGL_EXPORT ContextPointer createContext(FunctionTablePointer const&table = nullptr);
  }
}


