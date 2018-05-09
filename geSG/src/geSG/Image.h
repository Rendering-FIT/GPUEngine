#pragma once

#include <geSG/Export.h>

// temporary solution
#include <geUtil/macros.h>


namespace ge{
   namespace sg
   {
      class MaterialComponent;

      /**
       * Simple abstract class representing 2D image. Do NOT inherit.
       * Subclass TemplateImage.
       */
      class GESG_EXPORT Image
      {
      public:

         ENUM_CLASS_FRIEND_OPERATOR(Format, UNKNOWN, R, RG, RGB, BGR, RGBA, BGRA);

         ENUM_CLASS_FRIEND_OPERATOR(DataType, UNKNOWN, BYTE, UNSIGNED_BYTE, SHORT, UNSIGNED_SHORT, INT, UNSIGNED_INT, HALF_FLOAT, FLOAT);

         //virtual bool loadFile(const char* filePath) = 0;
         virtual unsigned char* getBits() = 0;

         virtual size_t getSizeInBytes() = 0;
         virtual Format getFormat() = 0; //should this function return int or some template type which could be specified as GLenum
         virtual DataType getDataType() = 0;
         virtual size_t getWidth() = 0;
         virtual size_t getHeight() = 0;

         virtual ~Image() = default;

      };

      /**
       * Base class for 2D image. Derived class should wrap the
       * 3rd party image implementation such as fipImage in
       * FreeImage library. In this example the fipImage would be
       * substituded for ImageImpl template parametr.
       */
      template<typename ImageImpl>
      class ImageTemplate : public Image
      {
      public:

         typedef ImageImpl image_implementation;

         inline ImageImpl * getImageImpl() const { return _image; }
         inline void setImageImpl(ImageImpl * val) { _image = val; }

      protected:
         ImageImpl *_image;
      private:
      };
   }//namespace sg
} //namespace ge
