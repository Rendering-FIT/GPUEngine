#pragma once

#include<geGL/geGL.h>
#include"ShadowMethod.h"

class CubeShadowMapping: public ShadowMethod{
  public:
    CubeShadowMapping(
        glm::uvec2 const&windowSize,
        uint32_t resolution,
        float    near,
        float    far,
        std::shared_ptr<ge::gl::Texture>const&position,
        uint32_t nofVertices,
        std::shared_ptr<ge::gl::Buffer>const&vertices,
        std::shared_ptr<ge::gl::Texture>const&shadowMask);
    virtual ~CubeShadowMapping();
    virtual void create(glm::vec4 const&lightPosition,glm::vec3 const&cameraPosition)override;
  protected:
    glm::uvec2                          _windowSize;
    uint32_t                            _resolution   = 1024u  ;
    float                               _near         = 0.1f   ;
    float                               _far          = 1000.f ;
    std::shared_ptr<ge::gl::Texture>    _position     = nullptr;
    uint32_t                            _nofVertices  = 0      ;
    std::shared_ptr<ge::gl::Texture>    _shadowMap    = nullptr;
    std::shared_ptr<ge::gl::Framebuffer>_fbo          = nullptr;
    std::shared_ptr<ge::gl::VertexArray>_vao          = nullptr;
    std::shared_ptr<ge::gl::VertexArray>_maskVao      = nullptr;
    std::shared_ptr<ge::gl::Framebuffer>_maskFbo      = nullptr;
    std::shared_ptr<ge::gl::Program>_createShadowMap  = nullptr;
    std::shared_ptr<ge::gl::Program>_createShadowMask = nullptr;
};
