#ifndef GE_UTIL_ORBIT_MANIPULATOR_H
#define GE_UTIL_ORBIT_MANIPULATOR_H

#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <GPUEngine/geUtil/geutil_export.h>

namespace ge {
namespace util {


class GEUTIL_EXPORT ObjectManipulator
{
public:

   inline const glm::mat4& mat() const;

   virtual std::shared_ptr<glm::mat4>& matrix() = 0;
   virtual void setMatrix(const std::shared_ptr<glm::mat4>& mat) = 0;

   virtual ~ObjectManipulator() {}

};


class GEUTIL_EXPORT OrbitManipulator : public ObjectManipulator
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

   virtual std::shared_ptr<glm::mat4>& matrix() override;
   virtual void setMatrix(const std::shared_ptr<glm::mat4>& matrix) override;

   void rotate(float dx,float dy);
   void zoom(float dz);
   void move(float dx,float dy);
   //void zoomJump(int dir);

   void setCenter(const glm::vec3& center);
   void setEye(const glm::vec3& eye);
   void setDistance(const float distance);

   void updateMatrix();

   inline glm::vec3 getLocalUp() const { return _localUp; }
   void setLocalUp(glm::vec3 val) { _localUp = glm::normalize(val); }

};


// inline methods
inline const glm::mat4& ObjectManipulator::mat() const  { return *const_cast<ObjectManipulator*>(this)->matrix(); }

}
}

#endif /* GE_UTIL_ORBIT_MANIPULATOR_H */
