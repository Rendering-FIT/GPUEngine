#pragma once

#include <GL/glew.h>
#include <AttributeDescriptor.h>
#include <Image.h>
#include <Mesh.h>

namespace fsg
{
   GLuint semnatic2Attribute(fsg::AttributeDescriptor::Semantic semantic);
   GLenum translateEnum(fsg::AttributeDescriptor::DataType type);
   GLenum translateEnum(fsg::Image::DataType type);
   GLenum translateEnum(fsg::Image::Format type);
   GLenum translateEnum(fsg::Mesh::PrimitiveType type);
}