#include <EnumToGL.h>

GLuint fsg::semnatic2Attribute(AttributeDescriptor::Semantic semantic)
{
   switch(semantic)
   {
      case fsg::AttributeDescriptor::Semantic::POSITION: return 0;
      case fsg::AttributeDescriptor::Semantic::NORMAL: return 1;
      case fsg::AttributeDescriptor::Semantic::TEXCOORD: return 2;
      default:
         return -1;
         break;
   }
}

GLenum fsg::translateEnum(fsg::AttributeDescriptor::DataType type)
{
   switch(type)
   {
      case fsg::AttributeDescriptor::DataType::UNKNOWN: return GL_BYTE;
      case fsg::AttributeDescriptor::DataType::BYTE: return GL_BYTE;
         break;
      case fsg::AttributeDescriptor::DataType::UNSIGNED_BYTE: return GL_UNSIGNED_BYTE;
         break;
      case fsg::AttributeDescriptor::DataType::SHORT: return GL_SHORT;
         break;
      case fsg::AttributeDescriptor::DataType::UNSIGNED_SHORT: return GL_UNSIGNED_SHORT;
         break;
      case fsg::AttributeDescriptor::DataType::INT: return GL_INT;
         break;
      case fsg::AttributeDescriptor::DataType::UNSIGNED_INT: return GL_UNSIGNED_INT;
         break;
      case fsg::AttributeDescriptor::DataType::FLOAT: return GL_FLOAT;
         break;
      case fsg::AttributeDescriptor::DataType::DOUBLE: return GL_DOUBLE;
         break;
      default: return GL_BYTE;
         break;
   }
}

GLenum fsg::translateEnum(fsg::Image::DataType type)
{
   switch(type)
   {
      case fsg::Image::DataType::UNKNOWN:
      case fsg::Image::DataType::BYTE: return GL_BYTE;
      case fsg::Image::DataType::UNSIGNED_BYTE: return GL_UNSIGNED_BYTE;
      case fsg::Image::DataType::SHORT: return GL_SHORT;
      case fsg::Image::DataType::UNSIGNED_SHORT: return GL_UNSIGNED_SHORT;
      case fsg::Image::DataType::INT: return GL_INT;
      case fsg::Image::DataType::UNSIGNED_INT: return GL_UNSIGNED_INT;
      case fsg::Image::DataType::HALF_FLOAT: return GL_HALF_FLOAT;
      case fsg::Image::DataType::FLOAT: return GL_FLOAT;
      default: return GL_BYTE;
   }
}

GLenum fsg::translateEnum(fsg::Image::Format type)
{
   switch(type)
   {
      case fsg::Image::Format::UNKNOWN: return GL_RGBA;
      case fsg::Image::Format::R:return GL_R;
      case fsg::Image::Format::RG:return GL_RG;
      case fsg::Image::Format::RGB:return GL_RGB;
      case fsg::Image::Format::BGR:return GL_BGR;
      case fsg::Image::Format::RGBA:return GL_RGBA;
      case fsg::Image::Format::BGRA:return GL_BGRA;
      default: return GL_RGBA;
   }
}

GLenum fsg::translateEnum(Mesh::PrimitiveType type)
{
   switch(type)
   {
      case fsg::Mesh::PrimitiveType::UNKNOWN: return GL_TRIANGLES;
      case fsg::Mesh::PrimitiveType::POINTS: return GL_POINTS;
      case fsg::Mesh::PrimitiveType::LINES: return GL_LINES;
      case fsg::Mesh::PrimitiveType::LINE_LOOP: return GL_LINE_LOOP;
      case fsg::Mesh::PrimitiveType::LINE_STRIP: return GL_LINE_STRIP;
      case fsg::Mesh::PrimitiveType::TRIANGLES: return GL_TRIANGLES;
      case fsg::Mesh::PrimitiveType::TRIANGLE_STRIP: return GL_TRIANGLE_STRIP;
      case fsg::Mesh::PrimitiveType::TRIANGLE_FAN: return GL_TRIANGLE_FAN;
      case fsg::Mesh::PrimitiveType::QUADS: return GL_QUADS;
      case fsg::Mesh::PrimitiveType::QUAD_STRIP: return GL_QUAD_STRIP;
      case fsg::Mesh::PrimitiveType::POLYGON: return GL_POLYGON;
      case fsg::Mesh::PrimitiveType::PATCH: return GL_PATCHES;
      default: return GL_TRIANGLES;
   }
}
