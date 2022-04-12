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
         unsigned char* getBits() override;

         size_t getSizeInBytes() override;
         Format getFormat() override; //should this function return int or some template type which could be specified as GLenum
         DataType getDataType() override;
         size_t getWidth() override;
         size_t getHeight() override;
         
         unsigned char bits[4] = {0xff,0xff,0xff,0xff};
         Format format = Format::RGBA;
         DataType dataType = DataType::UNSIGNED_BYTE;
         size_t width = 1;
         size_t height = 1;
      };
   }
}