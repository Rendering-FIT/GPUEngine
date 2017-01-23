#pragma once

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtc/matrix_access.hpp>

#include<geGL/geGL.h>

#include"TimeStamp.h"

size_t const componentsPerVertex2D   = 2;
size_t const componentsPerVertex3D   = 3;
size_t const componentsPerVertex4D   = 4;
size_t const componentsPerPlane3D    = 4;
size_t const verticesPerEdge         = 2;
size_t const verticesPerTriangle     = 3;
size_t const verticesPerQuad         = 4;

class ShadowMethod: public ge::gl::Context{
  public:
    std::shared_ptr<TimeStamp      >timeStamp  = nullptr;
    ShadowMethod();
    virtual ~ShadowMethod(){}
    virtual void create(
        glm::vec4 const&lightPosition   ,
        glm::mat4 const&viewMatrix      ,
        glm::mat4 const&projectionMatrix) = 0;
};
