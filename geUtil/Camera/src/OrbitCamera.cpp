#include<GPUEngine/geUtil/Camera/OrbitCamera.h>


using namespace ge::util;

OrbitCamera::OrbitCamera(float distance):CameraTransform(),_xAngle(0),_yAngle(0),_distance(distance),_recompute(true){
}

OrbitCamera::~OrbitCamera(){
}

glm::mat4 OrbitCamera::getView(){
  assert(this);
  if(this->_recompute){
    this->_compute();
    this->_recompute = false;
  }
  return this->_view;
}

glm::mat4 OrbitCamera::getRotation(){
  assert(this);
  if(this->_recompute){
    this->_compute();
    this->_recompute = false;
  }
  return this->_rotation;
}

float OrbitCamera::getXAngle  ()const{
  assert(this);
  return this->_xAngle  ;
}

float OrbitCamera::getYAngle  ()const{
  assert(this);
  return this->_yAngle  ;
}

float OrbitCamera::getDistance()const{
  assert(this);
  return this->_distance;
}

glm::vec3 OrbitCamera::getFocus()const{
  assert(this);
  return this->_position;
}

void OrbitCamera::setXAngle  (float value){
  assert(this);
  this->_xAngle = glm::clamp(value,-glm::half_pi<float>(),glm::half_pi<float>());
  this->_recompute = true;
}

void OrbitCamera::setYAngle  (float value){
  assert(this);
  this->_yAngle   = value;
  this->_recompute = true;
}

void OrbitCamera::setAngles(glm::vec2 const&angles){
  assert(this);
  this->setXAngle(angles.x);
  this->setYAngle(angles.y);
}

void OrbitCamera::setDistance(float value){
  assert(this);
  this->_distance = value;
  this->_recompute = true;
}

void OrbitCamera::setFocus(glm::vec3 const&value){
  assert(this);
  this->_position = value;
  this->_recompute = true;
}

void OrbitCamera::addXPosition(float dx){
  assert(this);
  this->_position += glm::vec3(glm::row(this->_rotation,0))*dx;
  this->_recompute = true;
}

void OrbitCamera::addYPosition(float dy){
  assert(this);
  this->_position += glm::vec3(glm::row(this->_rotation,1))*dy;
  this->_recompute = true;
}

void OrbitCamera::addXYPosition(glm::vec2 const&value){
  assert(this);
  this->addXPosition(value.x);
  this->addYPosition(value.y);
}

void OrbitCamera::addXAngle  (float value){
  assert(this);
  this->setXAngle(this->getXAngle()+value);
}

void OrbitCamera::addYAngle  (float value){
  assert(this);
  this->setYAngle(this->getYAngle()+value);
}

void OrbitCamera::addAngles(glm::vec2 const&value){
  assert(this);
  this->addXAngle(value.x);
  this->addYAngle(value.y);
}

void OrbitCamera::addDistance(float value){
  assert(this);
  this->setDistance(this->getDistance()+value);
}

void OrbitCamera::_compute(){
  assert(this);
  this->_rotation = 
    glm::rotate(glm::mat4(1.f),this->_xAngle,glm::vec3(1.f,0.f,0.f))*
    glm::rotate(glm::mat4(1.f),this->_yAngle,glm::vec3(0.f,1.f,0.f));
  this->_view =
    glm::translate(glm::mat4(1.f),glm::vec3(0.f,0.f,-this->_distance))*
    this->_rotation*
    glm::translate(glm::mat4(1.f),this->_position);
}

