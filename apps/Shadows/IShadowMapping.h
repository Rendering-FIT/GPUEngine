#pragma once

#include "ShadowMethod.h"

struct ShadowMappingParams
{
    glm::vec3 viewDir = glm::vec3(0, -1, 0);
    glm::vec3 upDir = glm::vec3(0, 1, 0);
    float     near = 0.1f;
    float     far = 1000.f;
    float     fovy = 1.5707963267948966f;
    glm::uvec3 resolution = glm::uvec3(1024, 1024, 1);
    uint32_t  pcfTaps = 1;
};


class IShadowMapping : public ShadowMethod
{
public:
    void setLightViewProps(glm::vec3 const& view, glm::vec3 const& up)
    { 
        _params.viewDir = view; _params.upDir = up; 
    }

protected:

    void computeLightView(glm::vec3 const& lightPos, glm::vec3 const& viewVec, glm::vec3 const& upVec)
    {
        _lightView = glm::lookAt(lightPos, lightPos + viewVec, upVec);
    }

    void computeLightProjPersp(float nearZ, float farZ, float fovY, float aspectRatio)
    {
        _lightProj = glm::perspective(fovY, aspectRatio, nearZ, farZ);
    }

    ShadowMappingParams					_params;

    glm::mat4							_lightView;
    glm::mat4							_lightProj;
    glm::uvec2                          _reslution;
};