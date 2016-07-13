/*!
 * OpenGL part of geGL library contains two main objects - FunctionTable and FunctionProvider
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
    namespace opengl{
      class FunctionTable;
      using FunctionTablePointer = std::shared_ptr<FunctionTable>;
      class FunctionProvider;
      using FunctionProviderPointer = std::shared_ptr<FunctionProvider>;
      class FunctionLoaderInterface;
      using FunctionLoaderInterfacePointer = std::shared_ptr<FunctionLoaderInterface>;
      GEGL_EXPORT FunctionTablePointer    const& getDefaultFunctionTable();
      GEGL_EXPORT FunctionProviderPointer const& getDefaultFunctionProvider();
      GEGL_EXPORT void setDefaultFunctionTable   (FunctionTablePointer    const&table   );
      GEGL_EXPORT void setDefaultFunctionProvider(FunctionProviderPointer const&provider);
      GEGL_EXPORT FunctionTablePointer    createTable(FunctionLoaderInterfacePointer const&loader);
      GEGL_EXPORT FunctionProviderPointer createProvider(FunctionTablePointer const&table = nullptr);
    }
  }
}


