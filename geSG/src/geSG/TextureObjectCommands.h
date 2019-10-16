#pragma once

#include <geCore/Command.h>
#include <memory>

#include<GL/glew.h>

namespace ge
{
   namespace gl
   {
      class TextureObject;

      class ActiveTexture : public ge::core::Command
      {
      public:
         ActiveTexture(GLenum texUnit);

         virtual void operator()();

         GLenum textureUnit;
      };

      class BindTexture : public ge::core::Command
      {
      public:
         BindTexture(std::shared_ptr<TextureObject>& texObject, GLenum texUnit);

         virtual void operator()();

         GLenum textureUnit;
         std::shared_ptr<TextureObject> textureObject;
      };
   }
}