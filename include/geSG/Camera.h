#ifndef GE_SG_CAMERA_H
#define GE_SG_CAMERA_H

#include <geSG/Projection.h>

namespace ge
{
   namespace sg
   {
      class Clear;

      class Camera : public Projection
      {
      protected:
         std::shared_ptr<Clear> _clear;

      public:

         void setViewport(int x,int y,int w,int h);
         void getViewport(int &x,int &y,int &w,int &h);

      };
   }
}

#endif // GE_SG_CAMERA_H
