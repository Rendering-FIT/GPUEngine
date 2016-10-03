#pragma once

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtc/matrix_access.hpp>

#include<geGL/geGL.h>

class ShadowMethod: public ge::gl::Context{
  public:
    virtual ~ShadowMethod(){}
    virtual void create(glm::vec4 const&lightPosition,glm::vec3 const&cameraPosition) = 0;
};
