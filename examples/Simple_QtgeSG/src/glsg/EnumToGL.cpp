#include <glsg/EnumToGL.h>

#include <geGL/Generated/OpenGLConstants.h>
#include <geCore/StandardSemanticsNames.h>

using namespace ge::glsg;

GLuint ge::glsg::semnatic2Attribute(unsigned semantic)
{
   if(semantic == (unsigned)idofstring(ge::sg::AttributeDescriptor::Semantic, ge::core::StandardSemanticNames::position))
      return 0;
   else if(semantic == (unsigned)idofstring(ge::sg::AttributeDescriptor::Semantic, ge::core::StandardSemanticNames::normal))
      return 1;
   else if(semantic == (unsigned)idofstring(ge::sg::AttributeDescriptor::Semantic, ge::core::StandardSemanticNames::texcoord))
      return 2;
   else if(semantic == (unsigned)idofstring(ge::sg::AttributeDescriptor::Semantic, ge::core::StandardSemanticNames::tangent))
      return 6;
   return ge::core::EnumRegister::notRegistered;
}

GLenum ge::glsg::translateEnum(ge::sg::AttributeDescriptor::DataType type)
{
   switch(type)
   {
      case ge::sg::AttributeDescriptor::DataType::UNKNOWN: return GL_BYTE;
      case ge::sg::AttributeDescriptor::DataType::BYTE: return GL_BYTE;
         break;
      case ge::sg::AttributeDescriptor::DataType::UNSIGNED_BYTE: return GL_UNSIGNED_BYTE;
         break;
      case ge::sg::AttributeDescriptor::DataType::SHORT: return GL_SHORT;
         break;
      case ge::sg::AttributeDescriptor::DataType::UNSIGNED_SHORT: return GL_UNSIGNED_SHORT;
         break;
      case ge::sg::AttributeDescriptor::DataType::INT: return GL_INT;
         break;
      case ge::sg::AttributeDescriptor::DataType::UNSIGNED_INT: return GL_UNSIGNED_INT;
         break;
      case ge::sg::AttributeDescriptor::DataType::FLOAT: return GL_FLOAT;
         break;
      case ge::sg::AttributeDescriptor::DataType::DOUBLE: return GL_DOUBLE;
         break;
      default: return GL_BYTE;
         break;
   }
}

GLenum ge::glsg::translateEnum(ge::sg::Image::DataType type)
{
   switch(type)
   {
      case ge::sg::Image::DataType::UNKNOWN:
      case ge::sg::Image::DataType::BYTE: return GL_BYTE;
      case ge::sg::Image::DataType::UNSIGNED_BYTE: return GL_UNSIGNED_BYTE;
      case ge::sg::Image::DataType::SHORT: return GL_SHORT;
      case ge::sg::Image::DataType::UNSIGNED_SHORT: return GL_UNSIGNED_SHORT;
      case ge::sg::Image::DataType::INT: return GL_INT;
      case ge::sg::Image::DataType::UNSIGNED_INT: return GL_UNSIGNED_INT;
      case ge::sg::Image::DataType::HALF_FLOAT: return GL_HALF_FLOAT;
      case ge::sg::Image::DataType::FLOAT: return GL_FLOAT;
      default: return GL_BYTE;
   }
}

GLenum ge::glsg::translateEnum(ge::sg::Image::Format type)
{
   switch(type)
   {
      case ge::sg::Image::Format::UNKNOWN: return GL_RGBA;
      case ge::sg::Image::Format::R:return GL_R;
      case ge::sg::Image::Format::RG:return GL_RG;
      case ge::sg::Image::Format::RGB:return GL_RGB;
      case ge::sg::Image::Format::BGR:return GL_BGR;
      case ge::sg::Image::Format::RGBA:return GL_RGBA;
      case ge::sg::Image::Format::BGRA:return GL_BGRA;
      default: return GL_RGBA;
   }
}

GLenum ge::glsg::translateEnum(ge::sg::Mesh::PrimitiveType type)
{
   switch(type)
   {
      case ge::sg::Mesh::PrimitiveType::UNKNOWN: return GL_TRIANGLES;
      case ge::sg::Mesh::PrimitiveType::POINTS: return GL_POINTS;
      case ge::sg::Mesh::PrimitiveType::LINES: return GL_LINES;
      case ge::sg::Mesh::PrimitiveType::LINE_LOOP: return GL_LINE_LOOP;
      case ge::sg::Mesh::PrimitiveType::LINE_STRIP: return GL_LINE_STRIP;
      case ge::sg::Mesh::PrimitiveType::TRIANGLES: return GL_TRIANGLES;
      case ge::sg::Mesh::PrimitiveType::TRIANGLE_STRIP: return GL_TRIANGLE_STRIP;
      case ge::sg::Mesh::PrimitiveType::TRIANGLE_FAN: return GL_TRIANGLE_FAN;
      case ge::sg::Mesh::PrimitiveType::QUADS: return GL_QUADS;
      case ge::sg::Mesh::PrimitiveType::QUAD_STRIP: return GL_QUAD_STRIP;
      case ge::sg::Mesh::PrimitiveType::POLYGON: return GL_POLYGON;
      case ge::sg::Mesh::PrimitiveType::PATCH: return GL_PATCHES;
      default: return GL_TRIANGLES;
   }
}
