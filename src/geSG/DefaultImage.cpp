#include <geSG/DefaultImage.h>

using namespace ge::sg;

DefaultImage::DefaultImage()
{
   _bits = new char[4];
   *(unsigned*)_bits = 0xffffffff;
   _format = Format::RGBA;
   _dataType = DataType::UNSIGNED_BYTE;
   _width = 1;
   _height = 1;
}

char* DefaultImage::getBits()
{
   return _bits;
}

size_t DefaultImage::getSizeInBytes()
{
   return 4;
}

Image::Format DefaultImage::getFormat()
{
   return _format;
}

Image::DataType DefaultImage::getDataType()
{
   return _dataType;
}

size_t DefaultImage::getWidth()
{
   return _width;
}

size_t DefaultImage::getHeight()
{
   return _height;
}

DefaultImage::~DefaultImage()
{
   if(_bits)
   {
      delete[]_bits;
      _bits = nullptr;
   }
}