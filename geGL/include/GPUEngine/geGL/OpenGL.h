/*!
 * OpenGL part of geGL library contains two main objects - FunctionTable and Context
 */

#pragma once

#include<GPUEngine/geGL/gegl_export.h>

#include<stdint.h>
#include<stddef.h>
#include<GPUEngine/geGL/Generated/OpenGLTypes.h>
#include<GPUEngine/geGL/Generated/OpenGLConstants.h>
#include<GPUEngine/geGL/Fwd.h>

namespace ge{
  namespace gl{
    GEGL_EXPORT FunctionTablePointer const& getDefaultFunctionTable();
    GEGL_EXPORT ContextPointer       const& getDefaultContext      ();
    GEGL_EXPORT void setDefaultFunctionTable(FunctionTablePointer const&table   );
    GEGL_EXPORT void setDefaultContext      (ContextPointer       const&provider);
    GEGL_EXPORT FunctionTablePointer createTable(FunctionLoaderInterfacePointer const&loader);
    GEGL_EXPORT ContextPointer createContext(FunctionTablePointer const&table = nullptr);
  }
}


