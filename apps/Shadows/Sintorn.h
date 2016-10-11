#pragma once

#include<geGL/geGL.h>
#include"ShadowMethod.h"
#include"Model.h"

class Sintorn: public ShadowMethod{
  public:
    Sintorn(
        glm::uvec2 const&windowSize,
        std::shared_ptr<ge::gl::Texture>const&depthTexture               ,
        std::shared_ptr<ge::gl::Texture>const&normalTexture              ,
        std::shared_ptr<Model>          const&model                      ,
        size_t                                wavefrontSize              ,
        size_t                                shadowFrustumusPerWorkGroup,
        float                                 bias                       ,
        bool                                  discardBackFacing          ,
        std::shared_ptr<ge::gl::Texture>const&shadowMask                 );
    virtual ~Sintorn();
    virtual void create(glm::vec4 const&lightPosition,
        glm::mat4 const&view,
        glm::mat4 const&projection)override;
  protected:
  public:
    glm::uvec2 _windowSize;///window size
		size_t     _nofLevels = 0;///number of level
    bool       _useUniformTileSizeInClipSpace;
    bool       _useUniformTileDivisibility;
    size_t     _shadowFrustaPerWorkGroup;
    size_t     _nofTriangles = 0;
    size_t     _shadowFrustaWGS = 64;
		size_t     _wavefrontSize = 64;
    bool       _discardBackFacing = true;

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
    void drawFinalStencilMask();

    void GenerateHierarchyTexture(glm::vec4 const&lightPosition);
		void ComputeShadowFrusta(glm::vec4 const&lightPosition,glm::mat4 mvp);
    void RasterizeTexture();
    void MergeTexture();
    void blit();
};
