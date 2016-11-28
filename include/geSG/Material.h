#pragma once

#include <geSG/Export.h>

#include <geUtil/macros.h>
#include <geCore/EnumRegister.h>

#include <memory>
#include <vector>
#include "geCore/idlist.h"

namespace ge{
   namespace sg
   {
      class Image;

      /**
       * Material component base class. Serving only as a common type.
       */
      class /*GESG_EXPORT*/ MaterialComponent
      {
      public:
        
         ENUM_CLASS_FRIEND_OPERATOR(ComponentType, UNKNOWN, SIMPLE, IMAGE);

         MaterialComponent() : componentType(ComponentType::UNKNOWN){}

         inline ComponentType getType(){ return componentType; }
         inline void setType(ComponentType type){ componentType = type; }


         virtual ~MaterialComponent(){}
      protected:
         ComponentType componentType;
      private:
      };

      /**
       * Representing simple uniform-like material component e.g. diffuse color of type vec4
       */
      class /*GESG_EXPORT*/ MaterialSimpleComponent : public MaterialComponent
      {
      public:
         ENUM_CLASS_FRIEND_OPERATOR(DataType, UNKNOWN, BYTE, UNSIGNED_BYTE, SHORT, UNSIGNED_SHORT, INT, UNSIGNED_INT, FLOAT, DOUBLE);
         idlist(Semantic, unknown, ambientColor, diffuseColor, specularColor, emissiveColor, shininess)

         MaterialSimpleComponent()
            : MaterialComponent()
            , semantic(Semantic::unknown)
            , data(nullptr)
         {
            componentType = ComponentType::SIMPLE;
         }

         int size;
         DataType dataType;
         Semantic semantic;
         std::unique_ptr<unsigned char[]> data;
      };

      /**
       * Material component representing image e.g. 2D texture image (without mip-maps ofc.)
       */
      class /*GESG_EXPORT*/ MaterialImageComponent : public MaterialComponent
      {
      public:
         idlist(Semantic, unknown, ambientTexture, diffuseTexture, specularTexture, emissiveTexture, heightTexture, normalTexture, shininessTexture, opacityTexture, displacementTexture, lightmapTexture, reflectionTexture)

         MaterialImageComponent()
            : MaterialComponent()
            , semantic(Semantic::unknown)
         {
            componentType = ComponentType::IMAGE;
         }

         std::string filePath;
         Semantic semantic;
         std::shared_ptr<Image> image;
      };

      /**
       * Collection of material components.
       */
      class /*GESG_EXPORT*/ Material
      {
      public:
         std::vector<std::shared_ptr<MaterialComponent>> materialComponents;
      };
   } //namespace sg
} //namespace ge
