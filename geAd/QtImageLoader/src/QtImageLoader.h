#pragma once

#include <geSG/Image.h>

class QImage;
class QString;
class QtImage;

/**
 * Image loader for Qt.
 * Use loadImage with path to an image file and options if supported. The funtions return
 * the pointer to QtImage. The receiver takes ownership of returned image and it is required
 * to stuff it inside the shared_ptr if you want to use it with the rest of GPUEngine.
 * The loaded image is converted to either Format_Grayscale8 for grey scale images or
 * Format_RGBA8888.
 * 
 * \example Simple_QtgeSG/main.cpp
 */
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