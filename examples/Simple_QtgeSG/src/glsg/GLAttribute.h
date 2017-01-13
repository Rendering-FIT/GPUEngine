#pragma once

#include <memory>


namespace ge
{
   namespace gl
   {
      class Buffer;
   }

   namespace sg{
      struct AttributeDescriptor;
   }
}

namespace ge
{
   namespace glsg
   {
      /**
       * Class pairing ge::sg::AttributeDescriptor with its ge::gl::Buffer representation.
       * Used by GLScene class.
       */
      class GLAttribute
      {
      public:
         GLAttribute() : attributeDescriptor(nullptr), BO(nullptr){}
         GLAttribute(std::shared_ptr<ge::sg::AttributeDescriptor> ad, std::shared_ptr<ge::gl::Buffer> buff) : attributeDescriptor(ad), BO(buff){}

         std::shared_ptr<ge::sg::AttributeDescriptor> attributeDescriptor;
         std::shared_ptr<ge::gl::Buffer> BO;
      };
   }

}