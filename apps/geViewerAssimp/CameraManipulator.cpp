#include "CameraManipulator.h"

#include <GLFW/glfw3.h>
#include <iostream>

#include <glm/ext.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/string_cast.hpp>

using namespace std;

fsg::OrbitObjectManipulator::OrbitObjectManipulator()
   : _dirty(true)
   , _matrix(make_shared<glm::mat4>())
   , _matrixInverse(make_shared<glm::mat4>())
   //, _camera(1, 1, 1, 1000, 60)
   , sensitivityX(3)
   , sensitivityY(3)
   , sensitivityZ(1)
   , _localUp(0, 1, 0)
   , forward(0, 0, -1)
   , _center(0, 0, 0)
   , _rotation()
   , _distance(5)
   , _angleX(0)
   , _angleY(0)
   , _fixVerticalAxis(true)
   , _diableFlipOver(true)
   , _minimalDistance(0)
{

}

void fsg::OrbitObjectManipulator::operator()()
{

}

/**
 * Feed this method with the delta (change) of normalized screen coordinates.
 * Speed can be adjusted via the sensitivity ratios.
 */
void fsg::OrbitObjectManipulator::rotate(float dx, float dy)
{
   _dirty = true;
   _angleX += dx * sensitivityX;
   _angleY += dy * sensitivityY;

   _angleY = glm::clamp(_angleY, -glm::half_pi<float>(), glm::half_pi<float>());

   _rotationMat = glm::rotate(glm::mat4(), _angleY, glm::vec3(1, 0, 0)) * glm::rotate(glm::mat4(), _angleX, glm::vec3(0, 1, 0));

}

/**
 * Zoom in/out fluently.
 */
void fsg::OrbitObjectManipulator::zoom(float dz)
{
   _dirty = true;
   _distance += dz * sensitivityZ;
   if(_distance < _minimalDistance) _distance = _minimalDistance;
}

/**
 * Updates the view matrix need to be called before getMatrix().
 * When you manipulate the "camera"/view through zoom(),
 * move(), rotate() methods it only updates its internal state (center, distance, rotation).
 * 
 * Suggestion: Maybe use dirty mechanism...
 */
void fsg::OrbitObjectManipulator::updateViewMatrix()
{
   if(!_dirty) return;
   *_matrix = glm::translate(glm::mat4(), glm::vec3(0, 0, -_distance))* _rotationMat * glm::translate(glm::mat4(), -_center);
   *_matrixInverse = glm::inverse(*_matrix);
   _dirty = false;

   /*glm::vec3 dummy1;
   glm::vec4 dummy2;
   glm::vec3 trans;
   glm::quat orientation;
   glm::decompose(*_matrix, dummy1, orientation, trans, dummy1, dummy2);
   std::cout << "camera Pos " << glm::to_string(orientation * trans) << std::endl;*/
}

std::shared_ptr<glm::mat4>& fsg::OrbitObjectManipulator::getRefMatrix()
{
   return _matrix;
}

glm::mat4 fsg::OrbitObjectManipulator::getMatrix()
{
   return *_matrix;
}

void fsg::OrbitObjectManipulator::setRefMatrix(std::shared_ptr<glm::mat4>& mat)
{
   _matrix = mat;
   *_matrixInverse = glm::inverse(*_matrix);
}

/**
 * Pan the camera. Takes the distance from center into account.
 */
void fsg::OrbitObjectManipulator::move(float dx, float dy)
{
   _dirty = true;
   float distX, distY;
   // 0.3f is magical constant from OSG - perhaps there should be different sensitivities?
   distX = dx * _distance * 0.3f * sensitivityX;
   distY = dy * _distance * 0.3f * sensitivityY;
  
   _center += glm::vec3(glm::vec4(distX, distY, 0, 1) * _rotationMat);
}

void fsg::OrbitObjectManipulator::setCenter(const glm::vec3& center)
{
   _dirty = true;
   this->_center = center;
}

void fsg::OrbitObjectManipulator::setEye(const glm::vec3& eye)
{
   _dirty = true;
   this->_distance = glm::distance(this->_center, eye);
   glm::mat4 lookat = glm::lookAt(eye, this->_center, this->_localUp);
   glm::vec3 dummy1;
   glm::vec4 dummy2;
   glm::quat orientation;
   glm::decompose(lookat, dummy1, orientation, dummy1, dummy1, dummy2);
   dummy1 = glm::eulerAngles(orientation);
   _angleX = dummy1.y;
   _angleY = dummy1.x;
   _angleY = glm::clamp(_angleY, -glm::half_pi<float>(), glm::half_pi<float>());

   _rotationMat = glm::rotate(glm::mat4(), _angleY, glm::vec3(1, 0, 0)) * glm::rotate(glm::mat4(), _angleX, glm::vec3(0, 1, 0));

}

void fsg::OrbitObjectManipulator::setDistance(const float distance)
{
   _dirty = true;
   this->_distance = distance;
}