#ifndef GE_UTIL_ORBIT_MANIPULATOR_H
#define GE_UTIL_ORBIT_MANIPULATOR_H

#include <geUtil/Export.h>
#include <memory>
#include <glm/gtc/quaternion.hpp>
#include <geUtil/ManipulatorInterfaces.h>

namespace ge {
namespace util {

class GEUTIL_EXPORT OrbitManipulator : public BasicManipulatorInterface, public PositionAttitudeInterface
{
protected:

   bool _dirty;

   std::shared_ptr<glm::mat4> _matrix;

   glm::vec3 _localUp;
   glm::vec3 _center;
   glm::quat _rotation;
   float _distance;
   float _angleX;
   float _angleY;

public:
protected:
   bool _diableFlipOver;
   bool _fixVerticalAxis;
   glm::mat4 _rotationMat;
   float _minimalDistance;

public:

   float sensitivityX;
   float sensitivityY;
   float sensitivityZ;
   glm::vec3 forward;

   OrbitManipulator();

   inline bool isDirty(){ return _dirty; }

   const glm::mat4& getMatrix() override;
   std::shared_ptr<glm::mat4>& getRefMatrix() override;
   void setMatrix(const std::shared_ptr<glm::mat4>& matrix) override;

   void moveZ(float dz) override;
   void moveXY(float dx, float dy) override;
   void rotate(float dx,float dy) override;

   void zoom(float dz);
   void move(float dx,float dy);
   //void zoomJump(int dir);

   void setCenter(const glm::vec3& center);
   void setDistance(const float distance);

   void updateMatrix();

   glm::vec3 getLocalUp() const override { return _localUp; }
   void setLocalUp(const glm::vec3& val) override
   {
      _dirty = true;
      _localUp = glm::normalize(val);
   }

   glm::vec3 getPosition() const override;
   void setPosition(const glm::vec3&) override;
   glm::quat getOrientation() const override;
   void setOrientation(const glm::quat&) override;
};


}
}

#endif /* GE_UTIL_ORBIT_MANIPULATOR_H */
