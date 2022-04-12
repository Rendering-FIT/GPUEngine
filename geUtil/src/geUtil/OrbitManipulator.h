#pragma once

#include <geUtil/Export.h>
#include <glm/gtc/quaternion.hpp>
#include <geUtil/ManipulatorInterfaces.h>

namespace ge {
namespace util {

/**
 * \brief Very simple manipulator for orbital camera.
 * This manipulator is mostly for producing/manipulating the view matrix. It emulates the orbiting movement around the center point (pivot).
 * It cannot roll and it cannot move closer to the center that the minimalDistance.
 * It implements both the BasicManipulatorInterface and the PositionOrientationInterface for camera manipulation (input) as well as some convenience methods
 * like zoom and move. For output there are getters from PositionOrientationInterface or getMatrix() from BasicManipulatorInterface which will compute and return a view matrix.
 * Since it's assumed that the move and rotate methods will be hooked up to the mouse movement there are sensitivity* parameters which modulates the movement speed.
 */
class GEUTIL_EXPORT OrbitManipulator : public BasicManipulatorInterface, public PositionOrientationInterface
{
protected:
   glm::vec3 localUp;
   glm::vec3 center;
   float distance;
   float angleX;
   float angleY;
   
   float minimalDistance;

public:

   float sensitivityX;
   float sensitivityY;
   float sensitivityZ;

   OrbitManipulator();

   //Matrix Interface
   glm::mat4 getMatrix() const override;

   //BasicManipulatorInterface
   void moveZ(float dz) override;
   void moveXY(float dx, float dy) override;
   void rotate(float dx,float dy) override;

   void zoom(float dz);
   void move(float dx,float dy);

   void setCenter(const glm::vec3& center);
   void setDistance(const float distance);

   glm::vec3 getLocalUp() const override { return localUp; }
   void setLocalUp(const glm::vec3& val) override
   {
      localUp = glm::normalize(val);
   }

   //PositionOrientationInterface
   glm::vec3 getPosition() const override;
   void setPosition(const glm::vec3&) override;
   glm::quat getOrientation() const override;
   void setOrientation(const glm::quat&) override;
};


}
}
