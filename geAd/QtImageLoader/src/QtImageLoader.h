#pragma once

#include <geSG/Image.h>

class QImage;
class QString;
class QtImage;

class QtImageLoader
{
public:

   static QtImage* loadImage(const char* imageIdentifier, int options = 0);
   static QtImage* loadImage(const wchar_t* imageIdentifier, int options = 0);
   static QtImage* loadImage(const QString& imageIdentifier, int options = 0);
};

class QtImage : public ge::sg::ImageTemplate < QImage >
{
public:
   virtual unsigned char* getBits();

   virtual size_t getSizeInBytes();
   virtual ge::sg::Image::Format getFormat(); //should this function return int or some template type which could be specified as GLenum
   virtual ge::sg::Image::DataType getDataType();
   virtual size_t getWidth();
   virtual size_t getHeight();
};