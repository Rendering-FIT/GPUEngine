#pragma once

#include<geGL/geGL.h>
#include<glm/glm.hpp>
#include"ShadowMethod.h"
#include"Model.h"
#include"TimeStamp.h"

struct CSSVParams{
  size_t computeSidesWGS = 64   ;
  bool   localAtomic     = true ;
  bool   cullSides       = false;
};

class CSSV: public ShadowMethod{
  public:
    CSSV(
        size_t                          const&maxMultiplicity,
        bool                            const&zfail          ,
        glm::uvec2                      const&windowSize     ,
        std::shared_ptr<ge::gl::Texture>const&depth          ,
        std::shared_ptr<Model>          const&model          ,
        std::shared_ptr<ge::gl::Texture>const&shadowMask     ,
        CSSVParams                      const&params         );
    virtual ~CSSV();
    virtual void create(
        glm::vec4 const&lightPosition,
        glm::mat4 const&view,
        glm::mat4 const&projection)override;
  protected:
    glm::uvec2                          _windowSize;
    std::shared_ptr<ge::gl::Framebuffer>_fbo              = nullptr;
    std::shared_ptr<ge::gl::Framebuffer>_maskFbo          = nullptr;
    std::shared_ptr<ge::gl::VertexArray>_maskVao          = nullptr;

    std::shared_ptr<ge::gl::Program>    _computeSidesProgram = nullptr;
    std::shared_ptr<ge::gl::Program>    _drawSidesProgram    = nullptr;
    std::shared_ptr<ge::gl::Buffer>     _adjacency           = nullptr;
    std::shared_ptr<ge::gl::Buffer>     _sillhouettes        = nullptr;
    std::shared_ptr<ge::gl::Buffer>     _dibo                = nullptr;
    std::shared_ptr<ge::gl::VertexArray>_sidesVao            = nullptr;
    size_t                              _nofEdges            = 0      ;
    size_t                              _nofTriangles        = 0      ;
    bool                                _zfail               = true   ;
    CSSVParams                          _params                    ;

    std::shared_ptr<ge::gl::Program>    _drawCapsProgram  = nullptr;
    std::shared_ptr<ge::gl::VertexArray>_capsVao          = nullptr;
    std::shared_ptr<ge::gl::Buffer>     _caps             = nullptr;

    std::shared_ptr<ge::gl::Program>    _blit             = nullptr;
    std::shared_ptr<ge::gl::VertexArray>_emptyVao         = nullptr;
    std::shared_ptr<TimeStamp>_timeStamper = nullptr;
    void _computeSides(glm::vec4 const&lightPosition);
    void _drawSides(
        glm::vec4 const&lightPosition,
        glm::mat4 const&view,
        glm::mat4 const&projection);
    void _drawCaps(
        glm::vec4 const&lightPosition,
        glm::mat4 const&view,
        glm::mat4 const&projection);

};
