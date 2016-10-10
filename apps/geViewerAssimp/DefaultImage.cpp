#include "DefaultImage.h"

fsg::DefaultImage::DefaultImage()
{
   _bits = new char[4];
   *(unsigned*)_bits = 0xffffffff;
   _format = Format::RGBA;
   _dataType = DataType::UNSIGNED_BYTE;
   _width = 1;
   _height = 1;
}

char* fsg::DefaultImage::getBits()
{
   return _bits;
}

size_t fsg::DefaultImage::getSizeInBytes()
{
   return 4;
}

ge::sg::Image::Format fsg::DefaultImage::getFormat()
{
   return _format;
}

ge::sg::Image::DataType fsg::DefaultImage::getDataType()
{
   return _dataType;
}

size_t fsg::DefaultImage::getWidth()
{
   return _width;
}

size_t fsg::DefaultImage::getHeight()
{
   return _height;
}

fsg::DefaultImage::~DefaultImage()
{
   if(_bits)
   {
      delete[]_bits;
      _bits = nullptr;
   }
}