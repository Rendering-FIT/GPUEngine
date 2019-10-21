#pragma once

#include "../IShadowMapping.h"

typedef uint32_t u32;
typedef int32_t  s32;

namespace ge
{
    namespace gl
    {
        class Texture;
        class Program;
        class Buffer;
    }
}

class FrustumTracedShadows : public IShadowMapping
{
public:
    FrustumTracedShadows(
        ShadowMappingParams             const& params,
        std::shared_ptr<ge::gl::Texture>const& shadowMask,
        glm::uvec2                      const& windowSize,
        std::shared_ptr<ge::gl::Texture>const& positionTex,
        uint32_t                        const& nofVertices,
        std::shared_ptr<ge::gl::Buffer> const& vertices);

    virtual ~FrustumTracedShadows();

	virtual void create( glm::vec4 const& lightPosition,
						 glm::mat4 const& viewMatrix,
						 glm::mat4 const& projectionMatrix) override;

    virtual bool init() override;

private:
    bool IsConservativeRasterizationSupported() const;

    std::shared_ptr<ge::gl::Buffer> IrregularZBuffer;
    std::shared_ptr<ge::gl::Buffer> AtomicCounter;

    std::shared_ptr<ge::gl::Buffer>  Vertices;
    u32                              NofVertices;
    std::shared_ptr<ge::gl::Texture> PositionTexture;
    std::shared_ptr<ge::gl::Texture> ShadowMask;

    std::unique_ptr<ge::gl::Framebuffer>    Fbo;
    std::unique_ptr<ge::gl::VertexArray>    Vao;
    std::unique_ptr<ge::gl::VertexArray>    ShadowMaskVao;
    std::unique_ptr<ge::gl::Framebuffer>    ShadowMaskFbo;

    std::unique_ptr<ge::gl::Program> IzbFillProgram;
    std::unique_ptr<ge::gl::Program> ShadowMaskProgram;

    glm::uvec2                       WindowSize;

    std::shared_ptr<ge::gl::Buffer> shit;
    std::shared_ptr<ge::gl::Texture> shitTex;
};