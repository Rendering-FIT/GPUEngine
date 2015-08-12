#pragma once 
#include <geSG/Export.h>
#include <geUtil/macros.h>
#include <memory>
#include <geCore/EnumRegister.h>

namespace ge{
   namespace sg
   {
      /**
       * This class represents vertex attrib pointer.
       * It also own data it's describing.
       */
      struct GESG_EXPORT AttributeDescriptor
      {
         /*enum class DataType
         {
         UNKNOWN,
         BYTE,
         UNSIGNED_BYTE,
         SHORT,
         UNSIGNED_SHORT,
         INT,
         UNSIGNED_INT,
         FLOAT,
         DOUBLE,
         };*/

         ENUM_CLASS_FRIEND_OPERATOR(DataType, UNKNOWN, BYTE, UNSIGNED_BYTE, SHORT, UNSIGNED_SHORT, INT, UNSIGNED_INT, FLOAT, DOUBLE);

         size_t getSize(DataType type)
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

         /*enum class Semantic
         {
         UNKNOWN,
         POSITION,
         NORMAL,
         BINORMAL,
         INDICES,
         TEXCOORD,
         };*/

         //ENUM_CLASS_FRIEND_OPERATOR(Semantic, UNKNOWN, POSITION, NORMAL, BINORMAL, INDICES, TEXCOORD)
         static ge::core::EnumRegister semanticRegister;

         int size; ///< size of buffer AttributeDescriptor::data in bytes
         unsigned numComponents; ///< number of vector component
         DataType type; ///< vector data type
         size_t stride;
         size_t offset;
         unsigned semantic;
         std::shared_ptr<void> data; ///< data buffer

         AttributeDescriptor()
            : size(0)
            , type(DataType::UNKNOWN)
            , stride(0)
            , offset(0)
            , semantic(ge::core::EnumRegister::notRegistered)
            , data(nullptr)
         {

         }
      };
   } //namespace sg
} //namespace ge