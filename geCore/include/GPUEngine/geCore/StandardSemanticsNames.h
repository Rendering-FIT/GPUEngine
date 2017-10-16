#pragma once

#include <GPUEngine/geCore/gecore_export.h>

#include <string>

namespace ge
{
   namespace core
   {
      struct GECORE_EXPORT StandardSemanticNames
      {
         static std::string ambientColor;
         static std::string diffuseColor;
         static std::string specularColor;
         static std::string emissiveColor;
         static std::string shininess;
         static std::string ambientTexture;
         static std::string diffuseTexture;
         static std::string specularTexture;
         static std::string emissiveTexture;
         static std::string heightTexture;
         static std::string normalTexture;
         static std::string shininessTexture;
         static std::string opacityTexture;
         static std::string displacementTexture;
         static std::string lightmapTexture;
         static std::string reflectionTexture;

         static std::string position;
         static std::string normal;
         static std::string tangent;
         static std::string binormal;
         static std::string indices;
         static std::string texcoord;
      };
   }
}
