#ifndef _CAMERAOBJECT_H_
#define _CAMERAOBJECT_H_

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtc/matrix_access.hpp>

#include <geUtil/Export.h>
#include <iostream>

namespace ge{
  namespace util{
    /**
     * @brief Class represents camera
     */
    class GEUTIL_EXPORT CameraObject{
      public:
        /**
         * @brief Constructor
         *
         * @param Size[2] size of viewport/window
         * @param Near distance to near plane
         * @param Far distance to far plane
         * @param Fovy field of view
         */
        CameraObject(unsigned const Size[2],float Near,float Far,float Fovy);
        /**
         * @brief Shifts camera up
         *
         * @param Dy offset
         */
        void up(float Dy);
        /**
         * @brief Shifts camera down
         *
         * @param Dy offset
         */
        void down(float Dy);
        /**
         * @brief Shifts camera left
         *
         * @param Dx offset
         */
        void left(float Dx);
        /**
         * @brief  Shifts camera right
         *
         * @param Dx offset
         */
        void right(float Dx);
        /**
         * @brief Shifts camera forward
         *
         * @param Dz offset
         */
        void forward(float Dz);
        /**
         * @brief Shifts camera backward
         *
         * @param Dz offset
         */
        void back(float Dz);
        /**
         * @brief Sets view matrix
         *
         * @param P possition of the camera
         * @param Look look vector
         * @param Y up vector
         */
        void setView(float*P,float*Look,float*Y);
        /**
         * @brief Sets camera's viewport size
         *
         * @param size[2] size
         */
        void setSize(unsigned const size[2]);
        /**
         * @brief Sets camera's field of view
         *
         * @param Fovy field of view
         */
        void setFovy(float Fovy);
        /**
         * @brief Sets near plane distance
         *
         * @param Near neat plane distance
         */
        void setNear(float Near);
        /**
         * @brief Sets far plane distance
         *
         * @param Far far plane distance
         */
        void setFar(float Far);
        /**
         * @brief Sets both, near and far plane distances
         *
         * @param Near near plane distance
         * @param Far far plane distance
         */
        void setNearFar(float Near,float Far);
        /**
         * @brief Compute standard FPS camera
         *
         * @param Rx rotation around x axis
         * @param Ry rotation around y axis
         * @param Rz rotation around z axis
         */
        void fpsCamera(float Rx,float Ry,float Rz);
        /**
         * @brief Gets view matrix
         *
         * @param V view matrix
         */
        void getView(glm::mat4*V);
        /**
         * @brief Gets view matrix
         *
         * @return view matrix
         */
        glm::mat4 getView();
        /**
         * @brief Gets view matrix without translation
         *
         * @param V rotation view matrix
         */
        void getViewRoration(glm::mat4*V);
        /**
         * @brief Gets view matrix without translation
         *
         * @return rotation view matrix
         */
        glm::mat4 getViewRoration();
        /**
         * @brief Gets projection matrix
         *
         * @param P projection matrix
         */
        void getProjection(glm::mat4*P);
        /**
         * @brief Gets projection matrix
         *
         * @return projection matrix
         */
        glm::mat4 getProjection();
        /**
         * @brief Gets position of the camera
         *
         * @return position of the camera
         */
        glm::vec3 getPosition();
        void setPosition(glm::vec3 p);
        /**
         * @brief Gets axes of view matrix
         *
         * @param k index of exis
         *
         * @return base vector of view matrix
         */
        glm::vec3 getVector(int k);
        /**
         * @brief Gets field of view
         *
         * @return field of view
         */
        float getFovy();
        float getNear();
        float getFar();
        std::string toString();
        void saveToFile(std::string file);
        void loadFromString(std::string data);
        void loadFromFile(std::string file);
        /**
         * @brief Gets pickup vector
         *
         * @param x x coordinates into viewport
         * @param y y coordinates into viewport
         *
         * @return pickup vector
         */
        glm::vec3 getPickVector(unsigned x,unsigned y);
      private:
        float     _fovy;        ///<field of view
        float     _near;        ///<near plane distance
        float     _far;         ///<far plane fistance
        unsigned  _size[2];     ///<size of viewport
        glm::mat4 _viewRotation;///<rotation part of view matrix
        glm::mat4 _projection;  ///<projection matrix
        glm::vec3 _position;    ///<position of camera
        void      _computeProjection();///<it computes projection matrix

    };
  }//util
}//ge

#endif//_CAMERAOBJECT_H_
