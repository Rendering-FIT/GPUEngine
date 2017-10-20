#pragma once

#include<GPUEngine/geUtil/Camera/camera_export.h>
#include<GPUEngine/geUtil/Camera/Camera.h>

namespace ge{
  namespace util{
    class PerspectiveCamera;
  }
}

class CAMERA_EXPORT ge::util::PerspectiveCamera: public CameraProjection{
  public:
    PerspectiveCamera(
        float fovy   = glm::radians(90.f),
        float aspect = 1024.f/768.f      ,
        float near   = 0.1f              ,
        float far    = 1000.f            );
    virtual ~PerspectiveCamera();
    virtual glm::mat4 getProjection();
    float getNear  ()const;
    float getFar   ()const;
    float getFovy  ()const;
    float getAspect()const;
    void setNear  (float value);
    void setFar   (float value);
    void setFovy  (float value);
    void setAspect(float value);
  protected:
    float     _near      ;
    float     _far       ;
    float     _fovy      ;
    float     _aspect    ;
    glm::mat4 _projection;
    bool      _recompute ;
    void _compute();
};
