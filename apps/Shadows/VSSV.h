#pragma once

#include<geGL/geGL.h>
#include"ShadowMethod.h"
#include"Model.h"
#include"TimeStamp.h"

class Adjacency;
class VSSV: public ShadowMethod{
  public:
    VSSV(
        size_t                          const&maxMultiplicity       ,
        bool                            const&zfail                 ,
        glm::uvec2                      const&windowSize            ,
        std::shared_ptr<ge::gl::Texture>const&depth                 ,
        std::shared_ptr<Model>          const&model                 ,
        std::shared_ptr<ge::gl::Texture>const&shadowMask            ,
        bool                            const&usePlanes             ,
        bool                            const&useStrips             ,
        bool                            const&useAllOppositeVertices);
    virtual ~VSSV();
    virtual void create(
        glm::vec4 const&lightPosition,
        glm::mat4 const&view         ,
        glm::mat4 const&projection   )override;
  protected:
    glm::uvec2                          _windowSize;
    std::shared_ptr<ge::gl::Framebuffer>_fbo                    = nullptr;
    std::shared_ptr<ge::gl::Framebuffer>_maskFbo                = nullptr;
    std::shared_ptr<ge::gl::VertexArray>_maskVao                = nullptr;

    std::shared_ptr<ge::gl::Program>    _drawSidesProgram       = nullptr;
    std::shared_ptr<ge::gl::Buffer>     _adjacency              = nullptr;
    std::shared_ptr<ge::gl::VertexArray>_sidesVao               = nullptr;
    size_t                              _nofEdges               = 0;
    size_t                              _maxMultiplicity        = 0;
    size_t                              _nofTriangles           = 0;
    bool                                _zfail                  = true;

    std::shared_ptr<ge::gl::Program>    _drawCapsProgram        = nullptr;
    std::shared_ptr<ge::gl::VertexArray>_capsVao                = nullptr;
    std::shared_ptr<ge::gl::Buffer>     _caps                   = nullptr;

    std::shared_ptr<ge::gl::Program>    _blitProgram            = nullptr;
    std::shared_ptr<ge::gl::VertexArray>_emptyVao               = nullptr;
    std::shared_ptr<TimeStamp>          _timeStamper            = nullptr;
    bool                                _usePlanes              = false;
    bool                                _useStrips              = true;
    bool                                _useAllOppositeVertices = false;
    void                                _createSideDataUsingPoints   (std::shared_ptr<Adjacency>const&adj);
    void                                _createSideDataUsingAllPlanes(std::shared_ptr<Adjacency>const&adj);
    void                                _createSideDataUsingPlanes   (std::shared_ptr<Adjacency>const&adj);
    void                                _createCapDataUsingPoints    (std::shared_ptr<Adjacency>const&adj);
    void _drawSides(
        glm::vec4 const&lightPosition,
        glm::mat4 const&view         ,
        glm::mat4 const&projection   );
    void _drawCaps(
        glm::vec4 const&lightPosition,
        glm::mat4 const&view         ,
        glm::mat4 const&projection   );
    void _blit();
};
