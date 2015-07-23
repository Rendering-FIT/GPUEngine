#pragma once

#include <geSG/Export.h>

#include <geUtil/macros.h>
#include <geCore/EnumRegister.h>

#include <memory>
#include <vector>

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
         /*enum class ComponentType
         {
         UNKNOWN,
         SIMPLE,
         IMAGE,
         };*/

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
         //ENUM_CLASS_FRIEND_OPERATOR(Semantic, UNKNOWN, AMBIENT, DIFFUSE, SPECULAR, EMISSIVE, SHININESS);
         GESG_EXPORT static ge::core::EnumRegister semanticRegister;

         MaterialSimpleComponent()
            : MaterialComponent()
            , semantic(ge::core::EnumRegister::notRegistered)
            , data(nullptr)
         {
            componentType = ComponentType::SIMPLE;
         }

         int size;
         DataType dataType;
         unsigned semantic;
         char *data;
      };

      template<typename Deleter = std::default_delete<char[]>>
      class MaterialSimpleComponentTemplate : public MaterialSimpleComponent
      {
      public:
         virtual ~MaterialSimpleComponentTemplate()
         {
            if(data) Deleter(data);
         }
      };

      /**
       * Material component representing image e.g. 2D texture image (without mip-maps ofc.)
       */
      class /*GESG_EXPORT*/ MaterialImageComponent : public MaterialComponent
      {
      public:
         //ENUM_CLASS_FRIEND_OPERATOR(Semantic, UNKNOWN, DIFFUSE, SPECULAR, AMBIENT, EMISSIVE, HEIGHT, NORMAL, SHININESS, OPACITY, DISPLACEMENT, LIGHTMAP, REFLECTION, TEXT)
         static ge::core::EnumRegister semanticRegister;

         MaterialImageComponent()
            : MaterialComponent()
            , semantic(ge::core::EnumRegister::notRegistered)
         {
            componentType = ComponentType::IMAGE;
         }

         std::string filePath;
         unsigned semantic;
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
