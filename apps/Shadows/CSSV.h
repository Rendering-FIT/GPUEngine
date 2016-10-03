#pragma once

#include<geGL/geGL.h>
#include"ShadowMethod.h"
#include"Model.h"

class CSSV: public ShadowMethod{
  public:
    CSSV(
        size_t maxMultiplicity,
        int computeSidesWGS,
        glm::uvec2 const&windowSize,
        std::shared_ptr<ge::gl::Texture>const&depth,
        std::shared_ptr<Model>const&model,
        std::shared_ptr<ge::gl::Texture>const&shadowMask);
    virtual ~CSSV();
    virtual void create(glm::vec4 const&lightPosition,
        glm::mat4 const&view,
        glm::mat4 const&projection)override;
  protected:
    glm::uvec2                          _windowSize;
    std::shared_ptr<ge::gl::Framebuffer>_fbo              = nullptr;
    std::shared_ptr<ge::gl::Framebuffer>_maskFbo          = nullptr;
    std::shared_ptr<ge::gl::VertexArray>_maskVao          = nullptr;

    std::shared_ptr<ge::gl::Program>    _computeSides     = nullptr;
    std::shared_ptr<ge::gl::Program>    _drawSides        = nullptr;
    std::shared_ptr<ge::gl::Buffer>     _adjacency        = nullptr;
    std::shared_ptr<ge::gl::Buffer>     _sillhouettes     = nullptr;
    std::shared_ptr<ge::gl::Buffer>     _dibo             = nullptr;
    std::shared_ptr<ge::gl::VertexArray>_sidesVao         = nullptr;
    size_t                              _nofEdges         = 0;
    int                                 _computeSidesWGS  = 64;

    std::shared_ptr<ge::gl::Program>    _drawCaps         = nullptr;
    std::shared_ptr<ge::gl::VertexArray>_capsVao          = nullptr;
    std::shared_ptr<ge::gl::Program>    _createShadowMask = nullptr;

    std::shared_ptr<ge::gl::Program>    _blit             = nullptr;
    std::shared_ptr<ge::gl::VertexArray>_emptyVao         = nullptr;
};
