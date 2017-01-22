#pragma once

#include<geGL/geGL.h>
#include<glm/glm.hpp>
#include"ShadowVolumes.h"
#include"Model.h"
#include"TimeStamp.h"

struct CSSVParams{
  size_t computeSidesWGS = 64   ;
  bool   localAtomic     = true ;
  bool   cullSides       = false;
};

class CSSV: public ShadowVolumes{
  public:
    CSSV(
        glm::uvec2                      const&windowSize     ,
        std::shared_ptr<Model>          const&model          ,
        std::shared_ptr<ge::gl::Texture>const&depth          ,
        std::shared_ptr<ge::gl::Texture>const&shadowMask     ,
        ShadowVolumesParams             const&svParams       ,
        size_t                          const&maxMultiplicity,
        CSSVParams                      const&params         );
    virtual ~CSSV();
    virtual void drawSides(
        glm::vec4 const&lightPosition   ,
        glm::mat4 const&viewMatrix      ,
        glm::mat4 const&projectionMatrix)override;
    virtual void drawCaps(
        glm::vec4 const&lightPosition   ,
        glm::mat4 const&viewMatirx      ,
        glm::mat4 const&projectionMatrix)override;
  protected:
    glm::uvec2                          _windowSize;

    std::shared_ptr<ge::gl::Program>    _computeSidesProgram = nullptr;
    std::shared_ptr<ge::gl::Program>    _drawSidesProgram    = nullptr;
    std::shared_ptr<ge::gl::Buffer>     _adjacency           = nullptr;
    std::shared_ptr<ge::gl::Buffer>     _sillhouettes        = nullptr;
    std::shared_ptr<ge::gl::Buffer>     _dibo                = nullptr;
    std::shared_ptr<ge::gl::VertexArray>_sidesVao            = nullptr;
    size_t                              _nofEdges            = 0      ;
    size_t                              _nofTriangles        = 0      ;
    CSSVParams                          _params                    ;

    std::shared_ptr<ge::gl::Program>    _drawCapsProgram  = nullptr;
    std::shared_ptr<ge::gl::VertexArray>_capsVao          = nullptr;
    std::shared_ptr<ge::gl::Buffer>     _caps             = nullptr;

    std::shared_ptr<TimeStamp>_timeStamper = nullptr;
    void _computeSides(glm::vec4 const&lightPosition);
};
