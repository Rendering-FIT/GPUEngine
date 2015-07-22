#pragma once

#include <geSG/Export.h>

// temporary solution
#include <geUtil/macros.h>

class MaterialComponent;

namespace ge{
   namespace sg
   {
      /**
       * Simple abstract class representing 2D image. Do NOT inherit.
       * Subclass TemplateImage.
       */
      class /*GESG_EXPORT*/ Image
      {
      public:

         /*enum class Format
         {
         UNKNOWN,
         R,
         RG,
         RGB,
         BGR,
         RGBA,
         BGRA,
         };*/

         ENUM_CLASS_FRIEND_OPERATOR(Format, UNKNOWN, R, RG, RGB, BGR, RGBA, BGRA);

         /*enum class Type
         {
         UNKNOWN,
         BYTE,
         UNSIGNED_BYTE,
         SHORT,
         UNSIGNED_SHORT,
         INT,
         UNSIGNED_INT,
         HALF_FLOAT,
         FLOAT,
         };*/

         ENUM_CLASS_FRIEND_OPERATOR(DataType, UNKNOWN, BYTE, UNSIGNED_BYTE, SHORT, UNSIGNED_SHORT, INT, UNSIGNED_INT, HALF_FLOAT, FLOAT);

         //virtual bool loadFile(const char* filePath) = 0;
         virtual char* getBits() = 0;

         virtual size_t getSizeInBytes() = 0;
         virtual Format getFormat() = 0; //should this function return int or some template type which could be specified as GLenum
         virtual DataType getDataType() = 0;
         virtual size_t getWidth() = 0;
         virtual size_t getHeight() = 0;

      };

      /**
       * Base class for 2D image. ImageImpl template should
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