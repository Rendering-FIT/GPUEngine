#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>

namespace ge
{
namespace util
{
   class MatrixInterface
   {
   public:
      virtual glm::mat4 getMatrix() const = 0;      
   };

   /**
    *
    */
   class BasicManipulatorInterface : public virtual MatrixInterface
   {
   public:
      BasicManipulatorInterface() = default;

      virtual void moveZ(float dz) = 0;
      virtual void moveXY(float dx, float dy) = 0;
      virtual void rotate(float dx, float dy) = 0;
      virtual glm::vec3 getLocalUp() const = 0;
      virtual void setLocalUp(const glm::vec3&) = 0;
   };


   /**
    * Interface for Position attitude transform like manipulators.
    */
   class PositionOrientationInterface : public virtual MatrixInterface
   {
   public:
      virtual glm::vec3 getPosition() const = 0;
      virtual void setPosition(const glm::vec3&) = 0;
      virtual glm::quat getOrientation() const = 0;
      virtual void setOrientation(const glm::quat&) = 0;
   };
}
}
