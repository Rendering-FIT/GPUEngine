#pragma once

#include <geSG/Image.h>

class fipImage;
class FreeImageImage;

class FreeImageImageLoader
{
public: 

   static FreeImageImage* loadImage(const char* imageIdentifier, int options = 0);
   static FreeImageImage* loadImage(const wchar_t* imageIdentifier, int options = 0);
};

class FreeImageImage : public ge::sg::ImageTemplate < fipImage >
{
public:
   virtual unsigned char* getBits();

   virtual size_t getSizeInBytes();
   virtual ge::sg::Image::Format getFormat(); //should this function return int or some template type which could be specified as GLenum
   virtual ge::sg::Image::DataType getDataType();
   virtual size_t getWidth();
   virtual size_t getHeight();
};