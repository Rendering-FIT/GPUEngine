#pragma once
#include <geSG/Export.h>
#include <geUtil/macros.h>
#include <memory>
#include <geCore/EnumRegister.h>
#include <geCore/idlist.h>

namespace ge {
namespace sg {

/**
 * AttributeDescriptor manages vertex attribute data.
 * From OpenGL point of view, it represents vertex attrib pointer.
 */
struct GESG_EXPORT AttributeDescriptor
{
   idlist(DataType, UNKNOWN, BYTE, UNSIGNED_BYTE, SHORT, UNSIGNED_SHORT, INT, UNSIGNED_INT, FLOAT, DOUBLE);

   unsigned getSize(DataType type)
   {
      switch(type)
      {
         case DataType::UNKNOWN: return 0;
         case DataType::BYTE:
         case DataType::UNSIGNED_BYTE: return sizeof(char);
         case DataType::SHORT:
         case DataType::UNSIGNED_SHORT: return sizeof(short);
         case DataType::INT:
         case DataType::UNSIGNED_INT: return sizeof(int);
         case DataType::FLOAT: return sizeof(float);
         case DataType::DOUBLE: return sizeof(double);
         default: return 0;
      }
   }

   idlist(Semantic, unknown, position, normal, color, texcoord, indices, tangent, binormal);

   int size; ///< size of buffer AttributeDescriptor::data in bytes
   unsigned numComponents; ///< number of vector component
   DataType type; ///< vector data type
   size_t stride;
   size_t offset;
   Semantic semantic;
   std::shared_ptr<void> data; ///< data buffer

   inline AttributeDescriptor()
      : size(0)
      , type(DataType::UNKNOWN)
      , stride(0)
      , offset(0)
      , semantic(Semantic::unknown)
      , data(nullptr)
   {
   }
};

} // namespace sg
} // namespace ge
