#include <algorithm>
#include <iostream>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>
#include <geUtil/OrbitManipulator.h>

using namespace std;
using namespace ge::util;

glm::mat4 OrbitManipulator::getMatrix() const
{
   return glm::translate(glm::mat4(1.f), glm::vec3(0, 0, -distance)) * glm::toMat4(getOrientation()) * glm::translate(glm::mat4(1.f), -center);
}

glm::vec3 OrbitManipulator::getPosition() const
{
   return center + glm::vec3{
      -distance * sin(angleX) * cos(angleY),
      distance * sin(angleY),
      distance * cos(angleX) * cos(angleY)
   };
}

void OrbitManipulator::setPosition(const glm::vec3& pos)
{

   glm::vec3 dir(pos - getPosition()); //direction of the translation
   center += dir; //move centre in the direction of the translation thus preserving the orientation
}

glm::quat OrbitManipulator::getOrientation() const
{
   return {glm::vec3{angleY,angleX,0.0f}}; //used quaternion constructor that accepts the euler angles; BEWARE THE ORDER (pitch, yaw, roll)
}

void OrbitManipulator::setOrientation(const glm::quat& orientation)
{
   glm::vec3 ang = eulerAngles(orientation);
   angleX = ang.x;
   angleY = ang.y;
}


/**
 * \brief Zoom
 * \param dz Counter intuitively +dz means zoom-in (mouse wheel up) so the distance needs to be changed by -dz.
 */
void OrbitManipulator::moveZ(float dz)
{
   distance += -dz * sensitivityZ;
   if(distance < minimalDistance) distance = minimalDistance;
}

/**
 * \brief Pan
 * \param dx Pan -x so the camera movement is left when you drag right.
 * \param dy Pan y
 */
void OrbitManipulator::moveXY(float dx, float dy)
{
   float distX, distY;
   distX = -dx * distance * sensitivityX;
   distY = dy * distance * sensitivityY;

   center += glm::vec3(glm::vec3(distX, distY, 0) * getOrientation());
}

/**
 * Feed this method with the delta (change) of normalized screen coordinates.
 * Speed can be adjusted via the sensitivity ratios.
 */
void OrbitManipulator::rotate(float dx,float dy)
{
   angleX += dx * sensitivityX;
   angleY += dy * sensitivityY;

   angleY = glm::clamp(angleY, -glm::half_pi<float>(), glm::half_pi<float>());
}


/**
 * Zoom in/out.
 * \see moveZ
 */
void OrbitManipulator::zoom(float dz)
{
   moveZ(dz);
}


/**
 * Pan the camera. Takes the distance from center into account.
 * \see moveXY
 */
void OrbitManipulator::move(float dx,float dy)
{
   moveXY(dx,dy);
}


void OrbitManipulator::setCenter(const glm::vec3& center)
{
   this->center = center;
}

void OrbitManipulator::setDistance(const float distance)
{
   this->distance = distance;
}
