#pragma once

#include <geSG/Export.h>

#include <geUtil/macros.h>
#include <geCore/EnumRegister.h>

#include <memory>
#include <vector>
#include <algorithm>
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

         unsigned getSize(DataType type)
         {
            switch(type)
            {
               case DataType::UNKNOWN: return 0;
               case DataType::BYTE:
               case DataType::UNSIGNED_BYTE: return sizeof(char);
               case DataType::SHORT:
               case DataType::UNSIGNED_SHORT: return sizeof(short);
               case DataType::INT:
               case DataType::UNSIGNED_INT: return sizeof(int);
               case DataType::FLOAT: return sizeof(float);
               case DataType::DOUBLE: return sizeof(double);
               default: return 0;
            }
         }

         int size;
         DataType dataType;
         Semantic semantic;
         std::unique_ptr<unsigned char[]> data; //shared pointer could be longer than the data itself
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

         /**
          * Finds and returns material component with the given semantic. Automaticaly infers the type
          * of component from the semantic.
          */
         template<typename ComponentType>
         std::shared_ptr<ComponentType> getComponent(typename ComponentType::Semantic semantic)
         {
            auto it = std::find_if(materialComponents.begin(), materialComponents.end(), [semantic](auto& comp)->bool
            {
               ComponentType* c = dynamic_cast<ComponentType*>(comp.get());
               if(c)
               {
                  return c->semantic == semantic;
               }

               return false;
            });

            if(it != materialComponents.end()) return std::static_pointer_cast<ComponentType>(*it);
            return std::shared_ptr<ComponentType>(nullptr);
         }

         std::vector<std::shared_ptr<MaterialComponent>> materialComponents;
      };
   } //namespace sg
} //namespace ge
