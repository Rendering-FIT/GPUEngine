#pragma once

#include <geUtil/macros.h>

#include <geSG/Export.h>
#include <geSG/Model.h>
#include <geSG/AttributeDescriptor.h>

#include <vector>
#include <memory>
#include <algorithm>


namespace ge{
   namespace sg
   {
      class Material;

      /**
       * Basic geometrical drawable. Represents one type of primitive described
       * by number of attributes (position, normal etc.) and one material.
       * It is basically opengl draw command.
       */
      class /*GESG_EXPORT*/ Mesh
      {
      public:

         /**
          * Helper comparator to be used with std algorithms such as find_if.
          *
          * @see getAttribute
          */
         struct IsSemantic {
         protected:

            AttributeDescriptor::Semantic semantic;

         public:

            IsSemantic(AttributeDescriptor::Semantic sem) : semantic(sem){}
            IsSemantic(const std::string& sem) : semantic(AttributeDescriptor::Semantic_register::str2id(sem)){}

            inline bool operator()(AttributeDescriptor::Semantic semantic, std::shared_ptr<AttributeDescriptor> desc)
            {
               return desc->semantic == semantic;
            }

            inline bool operator()(const std::string& semantic, std::shared_ptr<AttributeDescriptor> desc)
            {
               return desc->semantic == AttributeDescriptor::Semantic_register::str2id(semantic);
            }

            inline bool operator()(std::shared_ptr<AttributeDescriptor> desc)
            {
               return desc->semantic == this->semantic;
            }
         };

         inline std::shared_ptr<AttributeDescriptor> getAttribute(AttributeDescriptor::Semantic semantic)
         {
            auto it = std::find_if(this->attributes.begin(), this->attributes.end(), Mesh::IsSemantic(semantic));
            if(it != this->attributes.end())
               return *it;
            return std::shared_ptr<AttributeDescriptor>(nullptr);
         }

         inline std::shared_ptr<AttributeDescriptor> getAttribute(const std::string& semantic)
         {
            auto it = std::find_if(this->attributes.begin(), this->attributes.end(), Mesh::IsSemantic(semantic));
            if(it != this->attributes.end())
               return *it;
            return std::shared_ptr<AttributeDescriptor>(nullptr);
         }

         /*enum class PrimitiveType
         {
         UNKNOWN,
         POINTS,
         LINES,
         LINE_LOOP,
         LINE_STRIP,
         TRIANGLES,
         TRIANGLE_STRIP,
         TRIANGLE_FAN,
         QUADS,
         QUAD_STRIP,
         POLYGON,
         PATCH,
         };*/

         ENUM_CLASS_FRIEND_OPERATOR(PrimitiveType, UNKNOWN, POINTS, LINES, LINE_LOOP, LINE_STRIP, TRIANGLES, TRIANGLE_STRIP, TRIANGLE_FAN, QUADS, QUAD_STRIP, POLYGON, PATCH, )
         size_t count; ///< vertex count
         PrimitiveType primitive;
         std::vector<std::shared_ptr<AttributeDescriptor>>   attributes;
         std::shared_ptr<Material> material;
      protected:
      private:
      };

   }
}
