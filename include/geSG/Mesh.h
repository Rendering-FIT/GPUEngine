#pragma once

#include <geUtil/macros.h>

#include <geSG/Export.h>
//#include <Drawable.h>
#include <geSG/Model.h>
#include <geSG/AttributeDescriptor.h>

#include <vector>
#include <memory>
#include <algorithm>


namespace ge{
   namespace sg
   {
      //struct AttributeDescriptor;
      class Material;

      /**
       * Basic geometrical drawable. Represents one type of primitive described
       * by number of attributes (position, normal etc.) and one material.
       * It is basically opengl draw command.
       */
      class /*GESG_EXPORT*/ Mesh// : public Drawable
      {
      public:

         /**
          * Helper comparator to be used with std algorithms such as find_if.
          *
          * @see getAttribute
          */
         struct IsSemantic
         {

            IsSemantic(unsigned sem) : semantic(sem){}
            IsSemantic(const std::string& sem) : semantic(AttributeDescriptor::semanticRegister.getValue(sem)){}

            inline bool operator()(unsigned semantic, std::shared_ptr<AttributeDescriptor> desc)
            {
               return desc->semantic == semantic;
            }

            inline bool operator()(const std::string& semantic, std::shared_ptr<AttributeDescriptor> desc)
            {
               return desc->semantic == AttributeDescriptor::semanticRegister.getValue(semantic);
            }

            inline bool operator()(std::shared_ptr<AttributeDescriptor> desc)
            {
               return desc->semantic == this->semantic;
            }

            unsigned semantic;
         };

         inline std::shared_ptr<AttributeDescriptor> getAttribute(unsigned semantic)
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