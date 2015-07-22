#pragma once

#include <geUtil/macros.h>

#include <geSG/Export.h>
//#include <Drawable.h>
#include <geSG/Model.h>

#include <vector>
#include <memory>


namespace ge{
   namespace sg
   {
      struct AttributeDescriptor;
      class MaterialComponent;

      /**
       * Basic geometrical drawable. Represents one type of primitive described
       * by number of attributes (position, normal etc.) and one material.
       * It is basically opengl draw command.
       */
      class /*GESG_EXPORT*/ Mesh// : public Drawable
      {
      public:

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