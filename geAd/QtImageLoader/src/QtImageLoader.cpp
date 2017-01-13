#include "QtImageLoader.h"

#include <QImage>

/**
 * Loads an Image from given path if Qt supports the format.
 * \param imageIdentifier Path to image file.
 * \param options Options are not supported.
 * \return Loaded image or null.
 */
QtImage* QtImageLoader::loadImage(const char* imageIdentifier, int options)
{
   return loadImage(QString(imageIdentifier), options);
}

/**
 * 
 * \param imageIdentifier Path to image file.
 * \param options Options are not supported.
 * \return Loaded image or null.
 */
QtImage* QtImageLoader::loadImage(const wchar_t* imageIdentifier, int options)
{
   //Not implemented yet
   return nullptr;
}

/**
 * Loads an Image from given path if Qt supports the format.
 * \param imageIdentifier Path to image file.
 * \param options Options are not supported.
 * \return Loaded image or null.
 */
QtImage* QtImageLoader::loadImage(const QString& imageIdentifier, int options)
{
   QImage *image = new QImage();
   QtImage *qtImage = new QtImage();

   if(!image->load(imageIdentifier)) return nullptr;

   switch(image->format())
   {
      case QImage::Format_Alpha8:
         *image = image->convertToFormat(QImage::Format_Grayscale8);
         break;
      case QImage::Format_Invalid:
         delete image;
         delete qtImage;
         return nullptr;
         break;
      default:
         *image = image->convertToFormat(QImage::Format_RGBA8888);
         break;
   }

   qtImage->setImageImpl(image);

   return qtImage;
}


//////////////////////////////////////////////////////////////////////////
// QtImage
//////////////////////////////////////////////////////////////////////////


unsigned char* QtImage::getBits()
{
   if(!_image) return nullptr;
   return _image->bits();
}

size_t QtImage::getSizeInBytes()
{
   if(!_image) return 0;
   return _image->byteCount();
}

ge::sg::Image::Format QtImage::getFormat()
{
   using Format = ge::sg::Image::Format;
   switch( _image->format())
   {
      case QImage::Format_Alpha8:
      case QImage::Format_Grayscale8:
         return Format::R;
         break;
      case QImage::Format_Invalid:
         return Format::UNKNOWN;
         break;
      case QImage::Format_RGB888:
      case QImage::Format_RGB32:
         return Format::RGB;
      case QImage::Format_RGBX8888:
      case QImage::Format_RGBA8888:
         return Format::RGBA;
      default:
         return Format::UNKNOWN;
   }
}

ge::sg::Image::DataType QtImage::getDataType()
{
   //switch(_image->depth())
   return ge::sg::Image::DataType::UNSIGNED_BYTE;
}

size_t QtImage::getWidth()
{
   return _image->width();
}

size_t QtImage::getHeight()
{
   return _image->height();
}