#pragma once

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtc/matrix_access.hpp>

#include"Camera.h"

class OrbitCamera: public CameraTransform{
  public:
    OrbitCamera(float distance = 1);
    virtual ~OrbitCamera();
    virtual glm::mat4 getView();
    glm::mat4 getRotation();
    float getXAngle  ()const;
    float getYAngle  ()const;
    float getDistance()const;
    glm::vec3 getPosition()const;
    void setXAngle  (float value);
    void setYAngle  (float value);
    void setDistance(float value);
    void setPosition(glm::vec3 value);
    void addXPosition(float dx);
    void addYPosition(float dy);
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


