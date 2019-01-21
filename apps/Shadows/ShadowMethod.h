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

bool greaterVec(glm::vec3 const&a,glm::vec3 const&b);

template<typename TYPE>
void swapValues(TYPE&a,TYPE&b){TYPE c=a;a=b;b=c;}

glm::vec3 toVec3(float const*ptr);

glm::vec4 computePlane(glm::vec3 A,glm::vec3 B,glm::vec3 C);

class ShadowMethod: public ge::gl::Context{
  public:
    ShadowMethod();
    virtual ~ShadowMethod(){}
    virtual void create(
        glm::vec4 const&lightPosition   ,
        glm::mat4 const&viewMatrix      ,
        glm::mat4 const&projectionMatrix) = 0;
	virtual void setTimeStamper(std::shared_ptr<TimeStamp> stamper) { timeStamp = stamper; }
	virtual void drawUser(glm::vec4 const&lightPosition,
		glm::mat4 const&viewMatrix,
		glm::mat4 const&projectionMatrix) {}
protected:
	std::shared_ptr<TimeStamp      >timeStamp = nullptr;
};
