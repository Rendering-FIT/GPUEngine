#include"OrbitCamera.h"

OrbitCamera::OrbitCamera(float distance):CameraTransform(){
  this->_xAngle    = 0       ;
  this->_yAngle    = 0       ;
  this->_distance  = distance;
  this->_recompute = true    ;
}

OrbitCamera::~OrbitCamera(){}

glm::mat4 OrbitCamera::getView(){
  if(this->_recompute){
    this->_compute();
    this->_recompute = false;
  }
  return this->_view;
}

glm::mat4 OrbitCamera::getRotation(){
  if(this->_recompute){
    this->_compute();
    this->_recompute = false;
  }
  return this->_rotation;
}

float OrbitCamera::getXAngle  ()const{return this->_xAngle  ;}

float OrbitCamera::getYAngle  ()const{return this->_yAngle  ;}

float OrbitCamera::getDistance()const{return this->_distance;}

glm::vec3 OrbitCamera::getPosition()const{return this->_position;}

void OrbitCamera::setXAngle  (float value){
  this->_xAngle = glm::clamp(value,-glm::half_pi<float>(),glm::half_pi<float>());
  this->_recompute = true;
}

void OrbitCamera::setYAngle  (float value){this->_yAngle   = value;this->_recompute = true;}

void OrbitCamera::setDistance(float value){this->_distance = value;this->_recompute = true;}

void OrbitCamera::setPosition(glm::vec3 value){this->_position = value;this->_recompute = true;}

void OrbitCamera::addXPosition(float dx){
  this->_position += glm::vec3(glm::row(this->_rotation,0))*dx;
  this->_recompute = true;
}

void OrbitCamera::addYPosition(float dy){
  this->_position += glm::vec3(glm::row(this->_rotation,1))*dy;
  this->_recompute = true;
}

void OrbitCamera::_compute(){
  this->_rotation = 
    glm::rotate(glm::mat4(1.f),this->_xAngle,glm::vec3(1.f,0.f,0.f))*
    glm::rotate(glm::mat4(1.f),this->_yAngle,glm::vec3(0.f,1.f,0.f));
  this->_view =
    glm::translate(glm::mat4(1.f),glm::vec3(0.f,0.f,-this->_distance))*
    this->_rotation*
    glm::translate(glm::mat4(1.f),this->_position);
}

