#include "FreeImageImageLoader.h"

#include <FreeImagePlus.h>

#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

/**
 * Loads an image file from path given by imageIdentifier. On Windows platforms
 * it expects UTF-8 encoded string (ANSI should work). Inside it is transformed
 * to wide char so the characters in imageIdentifier to the image could be
 * correctly interpreted.
 */
FreeImageImage* FreeImageImageLoader::loadImage(const char* imageIdentifier, int options /*=0*/)
{
   //convert to UCS2
   int size = (int)strlen(imageIdentifier);
   int destLen = MultiByteToWideChar(CP_UTF8, 0, imageIdentifier, size, 0, 0);
   std::wstring wFilename(destLen, L'\0');
   destLen = MultiByteToWideChar(CP_UTF8, 0, imageIdentifier, size, &wFilename[0], destLen);

   FreeImageImage *image = new FreeImageImage();
   fipImage *freeImage = new fipImage();

   if(!freeImage->loadU(wFilename.c_str(), options)) return nullptr;

   image->setImageImpl(freeImage);

   return image;
}
#else

/**
 * Loads an image file from path given by imageIdentifier.
 */
FreeImageImage* FreeImageImageLoader::loadImage(const char* imageIdentifier, int options /*=0*/)
{
   FreeImageImage *image = new FreeImageImage();
   fipImage *freeImage = new fipImage();

   if(!freeImage->load(imageIdentifier)) return nullptr;

   image->setImageImpl(freeImage);

   return image;
}


#endif

/**
 * Loads an image file from path given by imageIdentifier.
 * This should be used only on windows platforms, since FipImage::loadU only works there.
 */
FreeImageImage* FreeImageImageLoader::loadImage(const wchar_t* imageIdentifier, int options /*= 0*/)
{
   FreeImageImage *image = new FreeImageImage();
   fipImage *freeImage = new fipImage();

   if(!freeImage->loadU(imageIdentifier)) return nullptr;

   image->setImageImpl(freeImage);

   return image;
}

//#include <gl/GL.h>
//////////////////////////////////////////////////////////////////////////
// FreeImageImage
//////////////////////////////////////////////////////////////////////////

unsigned char* FreeImageImage::getBits()
{
   if(!_image) return NULL;
   return _image->accessPixels();
}

size_t FreeImageImage::getSizeInBytes()
{
   if(!_image) return 0;
   return _image->getImageSize();
}

ge::sg::Image::Format FreeImageImage::getFormat()
{
   switch(_image->getImageType())
   {
      case FIT_UNKNOWN: return Format::UNKNOWN;
      case FIT_BITMAP :
         switch(_image->getBitsPerPixel())
         {
            case 8:return Format::R;
            case 16:return Format::RG;
            case 24: return FREEIMAGE_COLORORDER == FREEIMAGE_COLORORDER_BGR ? Format::BGR : Format::RGB;
            case 32: return FREEIMAGE_COLORORDER == FREEIMAGE_COLORORDER_BGR ? Format::BGRA : Format::RGBA;
            default: return Format::UNKNOWN;
         }
      case FIT_UINT16 :
      case FIT_INT16  :
         switch(_image->getBitsPerPixel())
         {
            case 16:return Format::R;
            case 32:return Format::RG;
            case 48: FREEIMAGE_COLORORDER == FREEIMAGE_COLORORDER_BGR ? Format::BGR : Format::RGB;
            case 64: FREEIMAGE_COLORORDER == FREEIMAGE_COLORORDER_BGR ? Format::BGRA : Format::RGBA;
            default: return Format::UNKNOWN;
         }
      case FIT_UINT32 :
      case FIT_INT32  :
         switch(_image->getBitsPerPixel())
         {
            case 32:return Format::R;
            case 64:return Format::RG;
            case 96: FREEIMAGE_COLORORDER == FREEIMAGE_COLORORDER_BGR ? Format::BGR : Format::RGB;
            case 128: FREEIMAGE_COLORORDER == FREEIMAGE_COLORORDER_BGR ? Format::BGRA : Format::RGBA;
            default: return Format::UNKNOWN;
         }
      case FIT_FLOAT  :
      case FIT_DOUBLE :
      case FIT_COMPLEX:
         return Format::UNKNOWN;
      case FIT_RGB16: return Format::RGB;
      case FIT_RGBA16:return Format::RGBA;
      case FIT_RGBF:return Format::RGB;
      case FIT_RGBAF: return Format::RGBA;
      default: return Format::UNKNOWN;
   }
}

ge::sg::Image::DataType FreeImageImage::getDataType()
{
   switch(_image->getImageType())
   {
      case FIT_UNKNOWN: return DataType::UNKNOWN;
      case FIT_BITMAP: return DataType::UNSIGNED_BYTE;
      case FIT_UINT16: return DataType::UNSIGNED_SHORT;
      case FIT_INT16: return DataType::SHORT;
      case FIT_UINT32: return DataType::UNSIGNED_INT;
      case FIT_INT32: return DataType::INT;
      case FIT_FLOAT: return DataType::FLOAT;
      case FIT_DOUBLE:
      case FIT_COMPLEX:
         return DataType::UNKNOWN;
      case FIT_RGB16: return DataType::HALF_FLOAT;
      case FIT_RGBA16:return DataType::HALF_FLOAT;
      case FIT_RGBF:return DataType::FLOAT;
      case FIT_RGBAF: return DataType::FLOAT;
      default: return DataType::UNKNOWN;
   }
}

size_t FreeImageImage::getWidth()
{
   return (size_t)_image->getWidth();
}

size_t FreeImageImage::getHeight()
{
   return (size_t)_image->getHeight();
}
