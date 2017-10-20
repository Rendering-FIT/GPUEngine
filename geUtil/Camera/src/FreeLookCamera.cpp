#include<GPUEngine/geUtil/Camera/FreeLookCamera.h>
#include<glm/gtx/euler_angles.hpp>

using namespace ge::util;

FreeLookCamera::FreeLookCamera():CameraTransform(){
  assert(this!=nullptr);
  this->_recomputeRotation = true;
  this->_recomputeView     = true;
}

FreeLookCamera::~FreeLookCamera(){}

glm::mat4 FreeLookCamera::getView(){
  assert(this!=nullptr);
  if(this->_recomputeView)this->_computeView();
  return this->_view;
}

glm::mat4 FreeLookCamera::getRotation(){
  assert(this!=nullptr);
  if(this->_recomputeRotation)this->_computeRotation();
  return this->_rotation;
}

void FreeLookCamera::up(float d){
  assert(this!=nullptr);
  this->move(1,d);
}

void FreeLookCamera::down(float d){
  assert(this!=nullptr);
  this->move(1,-d);
}

void FreeLookCamera::left(float d){
  assert(this!=nullptr);
  this->move(0,-d);
}

void FreeLookCamera::right(float d){
  assert(this!=nullptr);
  this->move(0,d);
}

void FreeLookCamera::forward(float d){
  assert(this!=nullptr);
  this->move(2,-d);
}

void FreeLookCamera::back(float d){
  assert(this!=nullptr);
  this->move(2,d);
}

void FreeLookCamera::move(size_t axis,float d){
  assert(this!=nullptr);
  assert(axis<3);
  this->_position+=d*glm::vec3(glm::row(this->_rotation,(glm::length_t)axis));
  this->_recomputeView = true;
}

void FreeLookCamera::setPosition(glm::vec3 const&p){
  assert(this!=nullptr);
  this->_position = p;
  this->_recomputeView = true;
}

void FreeLookCamera::addPosition(glm::vec3 const&delta){
  assert(this!=nullptr);
  this->_position += delta;
  this->_recomputeView = true;
}

glm::vec3 FreeLookCamera::getPosition()const{
  assert(this!=nullptr);
  return this->_position;
}

float FreeLookCamera::getXAngle  ()const{
  assert(this!=nullptr);
  return this->getAngle(0);
}

float FreeLookCamera::getYAngle  ()const{
  assert(this!=nullptr);
  return this->getAngle(1);
}

float FreeLookCamera::getZAngle  ()const{
  assert(this!=nullptr);
  return this->getAngle(2);
}

float FreeLookCamera::getAngle(size_t axis)const{
  assert(this!=nullptr);
  assert(axis<3);
  return this->_angles[(uint32_t)axis];
}

void FreeLookCamera::setXAngle  (float value){
  assert(this!=nullptr);
  this->setAngle(0,value);
}

void FreeLookCamera::setYAngle  (float value){
  assert(this!=nullptr);
  this->setAngle(1,value);
}

void FreeLookCamera::setZAngle  (float value){
  assert(this!=nullptr);
  this->setAngle(2,value);
}

void FreeLookCamera::setAngle(size_t axis,float value){
  assert(this!=nullptr);
  assert(axis<3);
  if(axis==0)this->_angles[(uint32_t)axis] = glm::clamp(value,-glm::half_pi<float>(),glm::half_pi<float>());
  else this->_angles[(uint32_t)axis]=value;
  this->_recomputeRotation = true;
  this->_recomputeView = true;
}

void FreeLookCamera::addXAngle  (float delta){
  assert(this!=nullptr);
  this->setAngle(0,this->getAngle(0)+delta);
}

void FreeLookCamera::addYAngle  (float delta){
  assert(this!=nullptr);
  this->setAngle(1,this->getAngle(1)+delta);
}

void FreeLookCamera::addZAngle  (float delta){
  assert(this!=nullptr);
  this->setAngle(2,this->getAngle(2)+delta);
}

void FreeLookCamera::addAngle(size_t axis,float delta){
  assert(this!=nullptr);
  assert(axis < 3);
  this->setAngle(axis,this->getAngle(axis)+delta);
}

void FreeLookCamera::setRotation(glm::vec3 const&viewVector,glm::vec3 const&upVector){
  assert(this!=nullptr);
  glm::vec3 xx = glm::normalize(glm::cross(viewVector,upVector));
  glm::vec3 yy = glm::normalize(glm::cross(xx,viewVector));
  glm::vec3 zz = glm::normalize(glm::cross(xx,yy));
  this->_rotation[0] = glm::vec4(xx,0.f);
  this->_rotation[1] = glm::vec4(yy,0.f);
  this->_rotation[2] = glm::vec4(zz,0.f);
  this->_rotation[3] = glm::vec4(0.f,0.f,0.f,1.f);
  this->_rotation = glm::transpose(this->_rotation);
  this->_recomputeRotation = false;
  this->_recomputeView = true;
}

void FreeLookCamera::_computeRotation(){
  assert(this!=nullptr);
  this->_rotation=glm::eulerAngleXYZ(this->_angles.x,this->_angles.y,this->_angles.z);
  this->_recomputeRotation = false;
}

void FreeLookCamera::_computeView(){
  assert(this!=nullptr);
  if(this->_recomputeRotation)this->_computeRotation();
  this->_view = this->_rotation*glm::translate(glm::mat4(1.f),-this->_position);
  this->_recomputeView = false;
}

