#pragma once

#include <geGL/Generated/OpenGLTypes.h>
#include <geSG/AttributeDescriptor.h>
#include <geSG/Image.h>
#include <geSG/Mesh.h>

namespace ge
{
   namespace glsg
   {
      GLuint semnatic2Attribute(unsigned semantic);
      GLenum translateEnum(ge::sg::AttributeDescriptor::DataType type);
      GLenum translateEnum(ge::sg::Image::DataType type);
      GLenum translateEnum(ge::sg::Image::Format type);
      GLenum translateEnum(ge::sg::Mesh::PrimitiveType type);
   }
}