#pragma once

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtc/matrix_access.hpp>

#include<GPUEngine/geUtil/Camera/camera_export.h>
#include<GPUEngine/geUtil/Camera/Camera.h>

namespace ge{
  namespace util{
    class CAMERA_EXPORT OrbitCamera: public CameraTransform{
      public:
        OrbitCamera(float distance = 1);
        virtual ~OrbitCamera();
        virtual glm::mat4 getView();
        glm::mat4 getRotation();
        float getXAngle  ()const;
        float getYAngle  ()const;
        float getDistance()const;
        glm::vec3 getFocus()const;
        void setXAngle  (float value);
        void setYAngle  (float value);
        void setAngles  (glm::vec2 const&angles);
        void setDistance(float value);
        void setFocus(glm::vec3 const&value);
        void addXPosition(float dx);
        void addYPosition(float dy);
        void addXYPosition(glm::vec2 const&value);
        void addXAngle  (float value);
        void addYAngle  (float value);
        void addAngles  (glm::vec2 const&value);
        void addDistance(float value);
      protected:
        float     _xAngle   ;
        float     _yAngle   ;
        float     _distance ;
        bool      _recompute;
        glm::vec3 _position ;
        glm::mat4 _view     ;
        glm::mat4 _rotation ;
        void _compute();
    };
  }
}


