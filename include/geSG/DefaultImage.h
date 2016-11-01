#pragma once
#include <geSG/Export.h>
#include <geSG/Image.h>

namespace ge
{
   namespace sg
   {
      class GESG_EXPORT DefaultImage : public ge::sg::Image
      {
      public:
         DefaultImage();

         virtual unsigned char* getBits() override;

         virtual size_t getSizeInBytes() override;
         virtual Format getFormat() override; //should this function return int or some template type which could be specified as GLenum
         virtual DataType getDataType() override;
         virtual size_t getWidth() override;
         virtual size_t getHeight() override;

         ~DefaultImage();

         unsigned char* _bits;
         Format _format;
         DataType _dataType;
         size_t _width;
         size_t _height;
      };
   }
}