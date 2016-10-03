#pragma once

#include<geGL/geGL.h>
#include"ShadowMethod.h"
#include"Model.h"

class Sintorn: public ShadowMethod{
  public:
    Sintorn(
        glm::uvec2 const&windowSize,
        std::shared_ptr<Model>const&model,
        uint32_t wavefrontSize,
        uint32_t shadowFrustumusPerWorkGroup);
    virtual ~Sintorn();
    virtual void create(glm::vec4 const&lightPosition,
        glm::mat4 const&view,
        glm::mat4 const&projection)override;
  protected:
    glm::uvec2 _windowSize;///window size
		uint32_t _numLevels;///number of level
    bool     _useUniformTileSizeInClipSpace;
    bool     _useUniformTileDivisibility;
    std::shared_ptr<ge::gl::Texture>_finalStencilMask;
    uint32_t _shadowFrustaPerWorkGroup;
    std::shared_ptr<ge::gl::Buffer>_shadowFrusta = nullptr;
    std::shared_ptr<ge::gl::Buffer>_HSB = nullptr;
    std::shared_ptr<ge::gl::Buffer>_HDB = nullptr;

    std::vector<std::shared_ptr<ge::gl::Texture>>_HDT;
    std::vector<std::shared_ptr<ge::gl::Texture>>_HST;

    std::shared_ptr<ge::gl::Texture>_HDBImage = nullptr;
    std::shared_ptr<ge::gl::Texture>_HSBImage = nullptr;

		uint32_t _wavefrontSize = 64;
    std::vector<glm::uvec2>_tileCount;
    std::vector<glm::uvec2>_tileSizeInPixels;///size of tiles in pixels in each level
    std::vector<glm::uvec2>_tileDivisibility;
    std::vector<glm::vec2>_tileSizeInClipSpace;

    std::shared_ptr<ge::gl::Program>WriteDepthProgram;
    std::shared_ptr<ge::gl::Program>WriteDepthTextureProgram;
		std::shared_ptr<ge::gl::Program>HierarchicalDepthProgram;
    std::shared_ptr<ge::gl::Program>HierarchicalDepthTextureProgram;
		std::shared_ptr<ge::gl::Program>ShadowFrustumProgram;
		std::shared_ptr<ge::gl::Program>RasterizeProgram;
    std::shared_ptr<ge::gl::Program>RasterizeTextureProgram;
    std::shared_ptr<ge::gl::Program>MergeProgram;
    std::shared_ptr<ge::gl::Program>MergeTextureProgram;
    std::shared_ptr<ge::gl::Program>WriteStencilProgram;
    std::shared_ptr<ge::gl::Program>WriteStencilTextureProgram;
    std::shared_ptr<ge::gl::Program>ClearStencilProgram;

		std::shared_ptr<ge::gl::Program>HDBProgram;
		std::shared_ptr<ge::gl::Program>SFProgram;

    std::shared_ptr<ge::gl::Program>DrawHDBProgram;
    std::shared_ptr<ge::gl::Program>DrawHSBProgram;

    std::shared_ptr<ge::gl::Program>CopyHDBProgram;
    std::shared_ptr<ge::gl::Program>CopyHSBProgram;

    std::shared_ptr<ge::gl::VertexArray>_emptyVao;
    std::shared_ptr<ge::gl::Buffer>_triangles = nullptr;
		unsigned GetTileSize(unsigned Level,unsigned Axis);
		unsigned GetTileCount(unsigned Level,unsigned Axis);
		std::string GenerateRasterizeProgram(
				unsigned NumLevels,
				unsigned WaveforntSize,
				unsigned ShadowFrustaPerWorkGroup);
		std::string GenerateWriteDepth(int*TileSize);
		void GenerateHierarchy(GLuint DepthTexture,GLuint NormalTexture,float*LightPosition);
    void GenerateHierarchyTexture(GLuint DepthTexture,GLuint NormalTexture,float*LightPosition);
		void ComputeShadowFrusta(float*LP,glm::mat4 mvp);
		void Rasterize();
    void RasterizeTexture();
    void Merge();
    void MergeTexture();
    void CopyHDB();
    void CopyHSB();
    void DrawHDB(unsigned Level,unsigned DrawNear);
    void DrawHSB(unsigned Level);

};
