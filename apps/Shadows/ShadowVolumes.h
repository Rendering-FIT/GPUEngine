#pragma once

#include<geGL/geGL.h>
#include"ShadowMethod.h"

struct ShadowVolumesParams{
  bool zfail = true;
  bool rasterDiscard = false;
};

class ShadowVolumes: public ShadowMethod{
  public:
    ShadowVolumes(
        std::shared_ptr<ge::gl::Texture>const&shadowMask,
        std::shared_ptr<ge::gl::Texture>const&depth     ,
        ShadowVolumesParams             const&params    );
    virtual ~ShadowVolumes();
    virtual void create(
        glm::vec4 const&lightPosition   ,
        glm::mat4 const&viewMatrix      ,
        glm::mat4 const&projectionMatrix)override final;
    virtual void drawSides(
        glm::vec4 const&lightPosition   ,
        glm::mat4 const&viewMatrix      ,
        glm::mat4 const&projectionMatrix) = 0;
    virtual void drawCaps(
        glm::vec4 const&lightPosition   ,
        glm::mat4 const&viewMatrix      ,
        glm::mat4 const&projectionMatrix) = 0;
  protected:
    ShadowVolumesParams                 _params               ;
    std::shared_ptr<ge::gl::Framebuffer>_fbo         = nullptr;
    std::shared_ptr<ge::gl::Framebuffer>_maskFbo     = nullptr;
    std::shared_ptr<ge::gl::Program>    _blitProgram = nullptr;
    std::shared_ptr<ge::gl::VertexArray>_emptyVao    = nullptr;
    void _blit();
};
