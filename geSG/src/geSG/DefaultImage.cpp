#include <geSG/DefaultImage.h>

using namespace ge::sg;

unsigned char* DefaultImage::getBits()
{
   return bits;
}

size_t DefaultImage::getSizeInBytes()
{
   return 4;
}

Image::Format DefaultImage::getFormat()
{
   return format;
}

Image::DataType DefaultImage::getDataType()
{
   return dataType;
}

size_t DefaultImage::getWidth()
{
   return width;
}

size_t DefaultImage::getHeight()
{
   return height;
}
