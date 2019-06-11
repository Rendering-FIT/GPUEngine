#pragma once

#include <geUtil/MatrixManipulatorInterface.h>

#if 1
namespace ge
{
namespace util
{
   /**
    * 
    */
   class BasicManipulatorInterface: public MatrixManipulatorInterface
   {
   public:
      BasicManipulatorInterface() = default;

      virtual void moveZ(float dz) = 0;
      virtual void moveXY(float dx, float dy) = 0;
      virtual void rotate(float dx, float dy) = 0;

      inline glm::vec3 getLocalUp() const { return _localUp; }
      void setLocalUp(glm::vec3 val) { _localUp = glm::normalize(val); }

      
   protected:
      glm::vec3 _localUp;
   };
}
}

#endif