#include<geUtil/CameraObject.h>

#include <limits>

namespace ge{
  namespace util{
    CameraObject::CameraObject(unsigned Size[2],float Near,float Far,float Fovy){
      this->_size[0]      = Size[0];//sets width of viewport/window
      this->_size[1]      = Size[1];//sets height of viewport/window
      this->_near         = Near;//near plane
      this->_far          = Far;//far plane
      this->_fovy         = Fovy;//field of view
      this->_viewRotation = glm::mat4(1.f);//sets view rotation matrix
      this->_position     = glm::vec3(0.f);//sets position
      this->_computeProjection();//compute projection matrix 
    }
    void CameraObject::_computeProjection(){
      if(this->_far==std::numeric_limits<float>::infinity()){//is far inifinty?
        float top=glm::tan(glm::radians(this->_fovy/2))*this->_near;//top border of viewport
        float bottom=-top;//bottom border of viewport
        float right=(top*this->_size[0])/this->_size[1];//right border of viewport
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
      }else//far is finite
        this->_projection=glm::perspective(
            glm::radians<float>(this->_fovy),//field of view
            1.f*this->_size[0]/this->_size[1],//aspect ratio
            this->_near,//near plane
            this->_far);//far plane
    }
    void CameraObject::left(float Dx){
      this->_position-=Dx*glm::vec3(glm::row(this->_viewRotation,0));
    }
    void CameraObject::right(float Dx){
      this->_position+=Dx*glm::vec3(glm::row(this->_viewRotation,0));
    }
    void CameraObject::down(float Dy){
      this->_position-=Dy*glm::vec3(glm::row(this->_viewRotation,1));
    }
    void CameraObject::up(float Dy){
      this->_position+=Dy*glm::vec3(glm::row(this->_viewRotation,1));
    }
    void CameraObject::forward(float Dz){
      this->_position-=Dz*glm::vec3(glm::row(this->_viewRotation,2));
    }
    void CameraObject::back(float Dz){
      this->_position+=Dz*glm::vec3(glm::row(this->_viewRotation,2));
    }
    void CameraObject::setFovy(float Fovy){
      this->_fovy=Fovy;
      this->_computeProjection();
    }
    void CameraObject::setNear(float Near){
      this->_near=Near;
      this->_computeProjection();
    }
    void CameraObject::setFar(float Far){
      this->_far=Far;
      this->_computeProjection();
    }
    void CameraObject::setNearFar(float Near,float Far){
      this->_near=Near;
      this->_far=Far;
      this->_computeProjection();
    }
    void CameraObject::fpsCamera(float Rx,float Ry,float Rz){
      this->_viewRotation=
        (glm::rotate(glm::mat4(1.),Rz,glm::vec3(0,0,1))*
         (glm::rotate(glm::mat4(1.),Rx,glm::vec3(1,0,0))*
          glm::rotate(glm::mat4(1.),Ry,glm::vec3(0,1,0))));
    }
    void CameraObject::setView(float*P,float*Look,float*V){
      for(int k=0;k<3;++k)this->_position[k]=P[k];
      glm::vec3 Z=glm::normalize(glm::vec3(-Look[0],-Look[1],-Look[2]));
      glm::vec3 Y=glm::normalize(glm::vec3(V[0],V[1],V[2]));
      glm::vec3 X=glm::normalize(glm::cross(Y,Z));
      for(int k=0;k<3;++k)this->_viewRotation[k][0]=X[k];
      for(int k=0;k<3;++k)this->_viewRotation[k][1]=Y[k];
      for(int k=0;k<3;++k)this->_viewRotation[k][2]=Z[k];
      for(int k=0;k<3;++k)this->_viewRotation[k][3]=0;
      for(int k=0;k<3;++k)this->_viewRotation[3][k]=0;
      this->_viewRotation[3][3]=1;
    }
    void CameraObject::getView(glm::mat4*V){
      *V=this->_viewRotation*glm::translate(glm::mat4(1.f),-this->_position);
      /*glm::mat4 ViewTranslate=glm::translate(glm::mat4(1.f),this->Position);
        return this->ViewRotation*ViewTranslate;*/
    }
    void CameraObject::getViewRoration(glm::mat4*V){
      *V=this->_viewRotation;
    }

    void CameraObject::getProjection(glm::mat4*P){
      this->_computeProjection();
      *P=this->_projection;
      //return this->Projection;
    }
    glm::mat4 CameraObject::getView(){
      return this->_viewRotation*glm::translate(glm::mat4(1.f),-this->_position);
    }
    glm::mat4 CameraObject::getViewRoration(){
      return this->_viewRotation;
    }
    glm::mat4 CameraObject::getProjection(){
      this->_computeProjection();
      return this->_projection;
    }
    glm::vec3 CameraObject::getPosition(){
      return -this->_position;
    }
    void CameraObject::setPosition(glm::vec3 p){
      this->_position=-p;
    }
    glm::vec3 CameraObject::getVector(int k){
      return glm::vec3(glm::row(this->_viewRotation,k));
    }
    float CameraObject::getFovy(){
      return this->_fovy;
    }
    glm::vec3 CameraObject::getPickVector(unsigned x,unsigned y){
      float dy=2.*x/this->_size[0]-1;
      float dx=2.*y/this->_size[1]-1;

      float ratio=1.*this->_size[0]/this->_size[1];
      float tangle=tan(this->_fovy/2);
      glm::vec3 X= glm::vec3(glm::row(this->_viewRotation,0));
      glm::vec3 Y= glm::vec3(glm::row(this->_viewRotation,1));
      glm::vec3 Z=-glm::vec3(glm::row(this->_viewRotation,2));

      X*=ratio*tangle*dy;
      Y*=-1*tangle*dx;
      return glm::normalize(X+Y+Z);
    }


  }//util
}//ge
