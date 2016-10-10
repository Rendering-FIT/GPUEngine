#include"FreeLookCamera.h"

#include<glm/gtx/euler_angles.hpp>

FreeLookCamera::FreeLookCamera():CameraTransform(){
  assert(this!=nullptr);
  this->_recompute = true;
}

FreeLookCamera::~FreeLookCamera(){}

glm::mat4 FreeLookCamera::getView(){
  assert(this!=nullptr);
  if(this->_recompute){
    this->_compute();
    this->_recompute = false;
  }
  return this->_view;
}

glm::mat4 FreeLookCamera::getRotation(){
  assert(this!=nullptr);
  if(this->_recompute){
    this->_compute();
    this->_recompute = false;
  }
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
  this->_position+=d*glm::vec3(glm::row(this->_rotation,axis));
  this->_recompute = true;
}

void FreeLookCamera::setPosition(glm::vec3 const&p){
  assert(this!=nullptr);
  this->_position = p;
  this->_recompute = true;
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
  return this->_angles[axis];
}

void FreeLookCamera::setXAngle  (float value){
  assert(this!=nullptr);
  return this->setAngle(0,value);
}

void FreeLookCamera::setYAngle  (float value){
  assert(this!=nullptr);
  return this->setAngle(1,value);
}

void FreeLookCamera::setZAngle  (float value){
  assert(this!=nullptr);
  return this->setAngle(2,value);
}

void FreeLookCamera::setAngle(size_t axis,float value){
  assert(this!=nullptr);
  assert(axis<3);
  if(axis==0)this->_angles[axis] = glm::clamp(value,-glm::half_pi<float>(),glm::half_pi<float>());
  else this->_angles[axis]=value;
  this->_recompute = true;
}

#include<iostream>
#include<sstream>

std::string glm2str(glm::vec3 const&x){
  std::stringstream ss;
  ss<<"("<<x.x<<","<<x.y<<","<<x.z<<")";
  return ss.str();
}

void FreeLookCamera::setRotation(glm::vec3 const&viewVector,glm::vec3 const&upVector){
  assert(this!=nullptr);
  glm::vec3 xx = glm::normalize(glm::cross(viewVector,upVector));
  glm::vec3 yy = glm::normalize(glm::cross(xx,viewVector));
  glm::vec3 zz = glm::normalize(glm::cross(xx,yy));
  if(zz.x!=-1 && zz.x!=+1){
    float y1 = -glm::asin(zz.x);
    float y2 = glm::pi<float>()-y1;
    float x1 = glm::atan(zz.y/glm::cos(y1),zz.z/glm::cos(y1));
    float x2 = glm::atan(zz.y/glm::cos(y2),zz.z/glm::cos(y2));
    float z1 = glm::atan(yy.x/glm::cos(y1),xx.x/glm::cos(y1));
    float z2 = glm::atan(yy.x/glm::cos(y2),xx.x/glm::cos(y2));
    (void)x2;
    (void)z2;
    this->_angles[0]=-x1;
    this->_angles[1]=-y1;
    this->_angles[2]=-z1;
  }else{
    float z = 0.f;
    float x;
    float y;
    if(xx.z == -1){
      y = glm::half_pi<float>();
      x = z + glm::atan(xx.y,xx.z);
    }else{
      y = -glm::half_pi<float>();
      x = -z + glm::atan(-xx.y,-xx.z);
    }
    this->_angles[0]=-x;
    this->_angles[1]=-y;
    this->_angles[2]=-z;
  }
  this->_recompute = true;
}

void FreeLookCamera::_compute(){
  this->_rotation=glm::eulerAngleXYZ(this->_angles.x,this->_angles.y,this->_angles.z);
  this->_view = this->_rotation*glm::translate(glm::mat4(1.f),-this->_position);
}

