#pragma once

#include<geGL/geGL.h>
#include"../ShadowMethod.h"

struct CubeShadowMappingParams{
  uint32_t resolution = 1024  ;
  float    near       = 0.1f  ;
  float    far        = 1000.f;
  uint32_t faces      = 6     ;
};

class CubeShadowMapping: public ShadowMethod{
  public:
    CubeShadowMapping(
        std::shared_ptr<ge::gl::Texture>const&shadowMask ,
        glm::uvec2                      const&windowSize ,
        std::shared_ptr<ge::gl::Texture>const&position   ,
        uint32_t                        const&nofVertices,
        std::shared_ptr<ge::gl::Buffer> const&vertices   ,
        CubeShadowMappingParams         const&params     );
    virtual ~CubeShadowMapping();
    virtual void create(
        glm::vec4 const&lightPosition   ,
        glm::mat4 const&viewMatrix      ,
        glm::mat4 const&projectionMatrix)override;
  protected:
    glm::uvec2                          _windowSize                ;
    std::shared_ptr<ge::gl::Texture>    _position         = nullptr;
    uint32_t                            _nofVertices      = 0      ;
    std::shared_ptr<ge::gl::Texture>    _shadowMap        = nullptr;
    std::shared_ptr<ge::gl::Framebuffer>_fbo              = nullptr;
    std::shared_ptr<ge::gl::VertexArray>_vao              = nullptr;
    std::shared_ptr<ge::gl::VertexArray>_maskVao          = nullptr;
    std::shared_ptr<ge::gl::Framebuffer>_maskFbo          = nullptr;
    std::shared_ptr<ge::gl::Program>    _createShadowMap  = nullptr;
    std::shared_ptr<ge::gl::Program>    _createShadowMask = nullptr;
    CubeShadowMappingParams             _params                    ;
};
