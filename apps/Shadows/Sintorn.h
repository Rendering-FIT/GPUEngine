#pragma once

#include<geGL/geGL.h>
#include"ShadowMethod.h"
#include"Model.h"

struct SintornParams{
  size_t shadowFrustaPerWorkGroup = 1    ;
  float  bias                     = 0.01f;
  bool   discardBackFacing        = true ;
  size_t shadowFrustaWGS          = 64   ;
};

class Sintorn: public ShadowMethod{
  public:
    Sintorn(
        std::shared_ptr<ge::gl::Texture>const&shadowMask   ,
        glm::uvec2                      const&windowSize   ,
        std::shared_ptr<ge::gl::Texture>const&depth        ,
        std::shared_ptr<ge::gl::Texture>const&normalTexture,
        std::shared_ptr<Model>          const&model        ,
        size_t                          const&wavefrontSize,
        SintornParams                   const&params       );
    virtual ~Sintorn();
    virtual void create(
        glm::vec4 const&lightPosition   ,
        glm::mat4 const&viewMatrix      ,
        glm::mat4 const&projectionMatrix)override;
  protected:
  public:
    glm::uvec2 _windowSize;///window size
    size_t     _nofLevels = 0;///number of level
    bool       _useUniformTileSizeInClipSpace;
    bool       _useUniformTileDivisibility;
    size_t     _nofTriangles = 0;
    size_t     _wavefrontSize = 64;

    std::shared_ptr<ge::gl::Texture>_finalStencilMask;
    std::shared_ptr<ge::gl::Buffer>_shadowFrusta = nullptr;
    std::shared_ptr<ge::gl::VertexArray>_emptyVao;
    std::shared_ptr<ge::gl::Buffer>_triangles = nullptr;
    std::vector<std::shared_ptr<ge::gl::Texture>>_HDT;
    std::vector<std::shared_ptr<ge::gl::Texture>>_HST;

    std::vector<glm::uvec2>_tileCount;
    std::vector<glm::uvec2>_usedTiles;
    std::vector<glm::uvec2>_tileSizeInPixels;///size of tiles in pixels in each level
    std::vector<glm::uvec2>_tileDivisibility;
    std::vector<glm::vec2>_tileSizeInClipSpace;
    std::shared_ptr<ge::gl::Texture>_depthTexture;
    std::shared_ptr<ge::gl::Texture>_normalTexture;

    std::shared_ptr<ge::gl::Program>WriteDepthTextureProgram;
    std::shared_ptr<ge::gl::Program>HierarchicalDepthTextureProgram;
    std::shared_ptr<ge::gl::Program>ShadowFrustumProgram;
    std::shared_ptr<ge::gl::Program>RasterizeTextureProgram;
    std::shared_ptr<ge::gl::Program>MergeTextureProgram;
    std::shared_ptr<ge::gl::Program>WriteStencilTextureProgram;
    std::shared_ptr<ge::gl::Program>ClearStencilProgram;
    std::shared_ptr<ge::gl::Program>SFProgram;

    std::shared_ptr<ge::gl::Texture>_shadowMask;
    std::shared_ptr<ge::gl::Program>_blitProgram;

    std::shared_ptr<ge::gl::Program>_drawHSTProgram;
    void drawHST(size_t l);
    std::shared_ptr<ge::gl::Program>_drawFinalStencilMask;
    SintornParams                   _params;
    void drawFinalStencilMask();

    void GenerateHierarchyTexture(glm::vec4 const&lightPosition);
    void ComputeShadowFrusta(glm::vec4 const&lightPosition,glm::mat4 mvp);
    void RasterizeTexture();
    void MergeTexture();
    void blit();
};
