#pragma once

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtc/matrix_access.hpp>

#include<GPUEngine/geUtil/Camera/camera_export.h>
#include<GPUEngine/geUtil/Camera/Camera.h>

namespace ge{
  namespace util{
    class FreeLookCamera;
  }
}

class CAMERA_EXPORT ge::util::FreeLookCamera: public CameraTransform{
  public:
    FreeLookCamera();
    virtual ~FreeLookCamera();
    virtual glm::mat4 getView();
    glm::mat4 getRotation();
    void up(float dy);
    void down(float dy);
    void left(float dx);
    void right(float dx);
    void forward(float dz);
    void back(float dz);
    void move(size_t axis,float d);
    void setPosition(glm::vec3 const&p);
    void addPosition(glm::vec3 const&delta);
    glm::vec3 getPosition()const;
    float getXAngle  ()const;
    float getYAngle  ()const;
    float getZAngle  ()const;
    float getAngle(size_t axis)const;
    void setXAngle  (float value);
    void setYAngle  (float value);
    void setZAngle  (float value);
    void setAngle(size_t axis,float value);
    void addXAngle  (float delta);
    void addYAngle  (float delta);
    void addZAngle  (float delta);
    void addAngle(size_t axis,float delta);
    void setRotation(glm::vec3 const&viewVector,glm::vec3 const&upVector);
  protected:
    glm::vec3 _angles;
    bool      _recomputeView;
    bool      _recomputeRotation;
    glm::vec3 _position ;
    glm::mat4 _view     ;
    glm::mat4 _rotation ;
    void _computeView();
    void _computeRotation();
};


