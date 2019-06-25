#pragma once
#include <geUtil/Export.h>
#include <glm/glm.hpp>
#include <memory>

namespace ge
{
namespace util
{
   class GEUTIL_EXPORT MatrixManipulatorInterface
   {
   public:

      // method can't be const since the manipulators need to update its internal state (the matrix usually)
      virtual const glm::mat4& getMatrix()
      {
         return *getRefMatrix();
      }

      virtual std::shared_ptr<glm::mat4>& getRefMatrix() = 0;
      virtual void setMatrix(const std::shared_ptr<glm::mat4>& mat) = 0;

      virtual ~MatrixManipulatorInterface() {}

   };

   /**
    *
    */
   class GEUTIL_EXPORT BasicManipulatorInterface : public MatrixManipulatorInterface
   {
   public:
      BasicManipulatorInterface() = default;

      virtual void moveZ(float dz) = 0;
      virtual void moveXY(float dx, float dy) = 0;
      virtual void rotate(float dx, float dy) = 0;

      inline glm::vec3 getLocalUp() const { return localUp; }
      void setLocalUp(glm::vec3 val) { localUp = glm::normalize(val); }


   protected:
      glm::vec3 localUp;
   };

   /**
    * Interface for Position attitude transform like manipulators.
    */
   class GEUTIL_EXPORT PositionAttitudeInterface
   {
   public:
      virtual glm::vec3 getPosition() const = 0;
      virtual void setPosition(glm::vec3) = 0;
      virtual glm::quat getOrientation() const = 0;
      virtual void setOrientation(glm::quat) = 0;
      virtual glm::vec3 getLocalUp() const = 0;
      virtual void setLocalUp(glm::vec3) = 0;
   };
}
}
