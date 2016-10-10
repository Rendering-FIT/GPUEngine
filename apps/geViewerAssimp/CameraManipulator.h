#pragma once

#include <geUtil/CameraObject.h>

#include <glm/glm.hpp>

#include <memory>

struct GLFWwindow;

namespace fsg{
   class ObjectManipulator
   {
   public:

      virtual glm::mat4 getMatrix() = 0;
      virtual ~ObjectManipulator(){}
   };

   class OrbitObjectManipulator : public ObjectManipulator
   {
   protected:

      bool _dirty;

      std::shared_ptr<glm::mat4> _matrix;
      std::shared_ptr<glm::mat4> _matrixInverse;
      //ge::util::CameraObject _camera;

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

      OrbitObjectManipulator();

      virtual void operator()();

      inline bool isDirty(){ return _dirty; }

      virtual glm::mat4 getMatrix();
      virtual std::shared_ptr<glm::mat4>& getRefMatrix();
      virtual void setRefMatrix(std::shared_ptr<glm::mat4>& mat);

      //void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
      void rotate(float dx, float dy);
      void zoom(float dz);
      void move(float dx, float dy);
      //void zoomJump(int dir);

      void setCenter(const glm::vec3& center);
      void setEye(const glm::vec3& eye);
      void setDistance(const float distance);

      void updateViewMatrix();

      inline glm::vec3 getLocalUp() const { return _localUp; }
      virtual void setLocalUp(glm::vec3 val) { _localUp = glm::normalize(val); }
   };
}