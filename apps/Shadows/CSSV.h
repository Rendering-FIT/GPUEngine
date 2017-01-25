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
  bool   usePlanes       = false;
};

class Adjacency;
class CSSV: public ShadowVolumes{
  public:
    CSSV(
        std::shared_ptr<ge::gl::Texture>const&shadowMask     ,
        std::shared_ptr<Model>          const&model          ,
        std::shared_ptr<ge::gl::Texture>const&depth          ,
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
    std::shared_ptr<ge::gl::Program>    _computeSidesProgram = nullptr;
    std::shared_ptr<ge::gl::Program>    _drawSidesProgram    = nullptr;
    std::shared_ptr<ge::gl::Buffer>     _edges               = nullptr;
    std::shared_ptr<ge::gl::Buffer>     _sillhouettes        = nullptr;
    std::shared_ptr<ge::gl::Buffer>     _dibo                = nullptr;
    std::shared_ptr<ge::gl::VertexArray>_sidesVao            = nullptr;
    size_t                              _nofEdges            = 0      ;
    size_t                              _nofTriangles        = 0      ;
    CSSVParams                          _params                       ;

    std::shared_ptr<ge::gl::Program>    _drawCapsProgram  = nullptr;
    std::shared_ptr<ge::gl::VertexArray>_capsVao          = nullptr;
    std::shared_ptr<ge::gl::Buffer>     _caps             = nullptr;

    void _computeSides(glm::vec4 const&lightPosition);

    void _createSidesData           (std::shared_ptr<Adjacency const>const&adj);
    void _createSidesDataUsingPlanes(std::shared_ptr<Adjacency const>const&adj);
    void _createCapsData            (std::shared_ptr<Adjacency const>const&adj);
};
