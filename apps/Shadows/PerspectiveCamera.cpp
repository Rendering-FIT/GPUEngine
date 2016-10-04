#include"PerspectiveCamera.h"

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
  if(this->_far != std::numeric_limits<float>::infinity()){
    this->_projection = glm::perspective(this->_fovy,this->_aspect,this->_near,this->_far);
    return;
  }
  float top=glm::tan(this->_fovy/2)*this->_near;//top border of viewport
  float bottom=-top;//bottom border of viewport
  float right=top*this->_aspect;//right border of viewport
  float left=-right;//left border of viewport
  //0. column
  this->_projection[0][0]=2*this->_near/(right-left);
  this->_projection[0][1]=0;
  this->_projection[0][2]=0;
  this->_projection[0][3]=0;
  //1. column
  this->_projection[1][0]=0;
  this->_projection[1][1]=2*this->_near/(top-bottom);
  this->_projection[1][2]=0;
  this->_projection[1][3]=0;
  //2. column
  this->_projection[2][0]=(right+left)/(right-left);
  this->_projection[2][1]=(top+bottom)/(top-bottom);
  this->_projection[2][2]=-1;
  this->_projection[2][3]=-1;
  //3. column
  this->_projection[3][0]=0;
  this->_projection[3][1]=0;
  this->_projection[3][2]=-2*this->_near;
  this->_projection[3][3]=0;
}

