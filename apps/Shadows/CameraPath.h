#pragma once

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtc/matrix_access.hpp>

#include<vector>
#include<iostream>

class CameraPathKeypoint{
  public:
    CameraPathKeypoint(
        glm::vec3 const&pos  = glm::vec3(0.f),
        glm::vec3 const&view = glm::vec3(0.f),
        glm::vec3 const&up   = glm::vec3(0.f)):position(pos),viewVector(view),upVector(up){
    }
    glm::vec3 position;
    glm::vec3 viewVector;
    glm::vec3 upVector;
};

class CameraPath{
  public:
    CameraPath(bool looping = false);
    CameraPath(bool looping,std::string const&file);
    CameraPathKeypoint getKeypoint(float t);
    std::vector<CameraPathKeypoint>keys;
  protected:
    bool _looping;
};
