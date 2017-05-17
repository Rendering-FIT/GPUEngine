#pragma once

#pragma once

#include<geGL/geGL.h>
#include<glm/glm.hpp>
#include"ShadowVolumes.h"
#include"Model.h"
#include"TimeStamp.h"

struct CSSVSOEParams{
  size_t computeSidesWGS = 64   ;
};

class Adjacency;
class CSSVSOE: public ShadowVolumes{
  public:
    CSSVSOE(
        std::shared_ptr<ge::gl::Texture>const&shadowMask     ,
        std::shared_ptr<Model>          const&model          ,
        std::shared_ptr<ge::gl::Texture>const&depth          ,
        ShadowVolumesParams             const&svParams       ,
        size_t                          const&maxMultiplicity,
        CSSVSOEParams                   const&params         );
    virtual ~CSSVSOE();
    virtual void drawSides(
        glm::vec4 const&lightPosition   ,
        glm::mat4 const&viewMatrix      ,
        glm::mat4 const&projectionMatrix)override;
    virtual void drawCaps(
        glm::vec4 const&lightPosition   ,
        glm::mat4 const&viewMatirx      ,
        glm::mat4 const&projectionMatrix)override;
  protected:
    std::shared_ptr<ge::gl::Program>    _computeSidesProgram = nullptr;
    std::shared_ptr<ge::gl::Program>    _drawSidesProgram    = nullptr;
    std::shared_ptr<ge::gl::Buffer>     _edges               = nullptr;
    std::shared_ptr<ge::gl::Buffer>     _silhouettes                  ;
    std::shared_ptr<ge::gl::Buffer>     _dibo                = nullptr;
    std::shared_ptr<ge::gl::VertexArray>_sidesVao                     ;
    size_t                              _nofEdges                     ;
    size_t                              _nofTriangles        = 0      ;
    size_t                              _maxMultiplicity     = 0      ;
    CSSVSOEParams                       _params                       ;

    std::shared_ptr<ge::gl::Program>    _drawCapsProgram     = nullptr;
    std::shared_ptr<ge::gl::VertexArray>_capsVao             = nullptr;
    std::shared_ptr<ge::gl::Buffer>     _caps                = nullptr;

    void _computeSides(glm::vec4 const&lightPosition);

    void _createSidesData                           (std::shared_ptr<Adjacency const>const&adj);
    void _createCapsData                            (std::shared_ptr<Adjacency const>const&adj);
};
