#pragma once
#include <geSG/Export.h>
#include <memory>
#include <geCore/idlist.h>

namespace ge {
namespace sg {

/**
 * AttributeDescriptor manages vertex attribute data.
 * From OpenGL point of view, it represents vertex attrib pointer.
 */
struct AttributeDescriptor
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

   int size = 0; ///< size of buffer AttributeDescriptor::data in bytes
   unsigned numComponents = 0; ///< number of vector component
   DataType type = DataType::UNKNOWN; ///< vector data type
   size_t stride = 0;
   size_t offset= 0;
   Semantic semantic = Semantic::unknown;
   std::shared_ptr<void> data; ///< data buffer
};

} // namespace sg
} // namespace ge
