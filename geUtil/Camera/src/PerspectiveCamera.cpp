#include<GPUEngine/geUtil/Camera/PerspectiveCamera.h>

using namespace ge::util;

PerspectiveCamera::PerspectiveCamera(
    float fovy  ,
    float aspect,
    float near  ,
    float far   ):CameraProjection(){
  this->_fovy      = fovy  ;
  this->_near      = near  ;
  this->_far       = far   ;
  this->_aspect    = aspect;
  this->_recompute = true  ;
}

PerspectiveCamera::~PerspectiveCamera(){}

glm::mat4 PerspectiveCamera::getProjection(){
  if(this->_recompute){
    this->_compute();
    this->_recompute = false;
  }
  return this->_projection;
}

float PerspectiveCamera::getNear  ()const{return this->_near  ;}
float PerspectiveCamera::getFar   ()const{return this->_far   ;}
float PerspectiveCamera::getFovy  ()const{return this->_fovy  ;}
float PerspectiveCamera::getAspect()const{return this->_aspect;}

void PerspectiveCamera::setNear  (float value){this->_near   = value;this->_recompute = true;}
void PerspectiveCamera::setFar   (float value){this->_far    = value;this->_recompute = true;}
void PerspectiveCamera::setFovy  (float value){this->_fovy   = value;this->_recompute = true;}
void PerspectiveCamera::setAspect(float value){this->_aspect = value;this->_recompute = true;}

void PerspectiveCamera::_compute(){
  if(this->_far == std::numeric_limits<float>::infinity())
    this->_projection = glm::infinitePerspective(this->_fovy,this->_aspect,this->_near);
  else
    this->_projection = glm::perspective(this->_fovy,this->_aspect,this->_near,this->_far);
}

