#pragma once
#include <geSG/Material.h>
#include <geGL/OpenGLCommands.h>


namespace ge
{
   namespace gl
   {
      class TextureObject;
   }

   namespace core
   {
      template<typename TYPE>
      inline TYPE convertTo(ge::sg::MaterialSimpleComponent& m )
      {
         return static_cast<TYPE> (m.data);
      }

      template<typename TYPE>
      inline TYPE convertTo(std::shared_ptr<ge::sg::MaterialSimpleComponent>& m)
      {
         return static_cast<TYPE> (m->data);
      }

      template<typename TYPE>
      inline TYPE convertTo(ge::gl::TextureObject& m)
      {
         return static_cast<TYPE> (m.getId());
      }

      template<typename TYPE>
      inline TYPE convertTo(std::shared_ptr<ge::gl::TextureObject>& m)
      {
         return static_cast<TYPE> (m->getId());
      }
   }
}

namespace fsg
{
   typedef ge::gl::Uniform4fv<GLint, GLsizei, std::shared_ptr<ge::sg::MaterialSimpleComponent>> SimpleMaterialUniform4fv;
   typedef ge::gl::BindTextureUnit<GLuint, std::shared_ptr<ge::gl::TextureObject>> BindTexture;
}