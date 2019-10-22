#pragma once

#include "../FTS/FrustumTracedShadows.h"

class OmnidirFrustumTracedShadows : public FrustumTracedShadows
{
public:

    OmnidirFrustumTracedShadows(
        ShadowMappingParams             const& params,
        std::shared_ptr<ge::gl::Texture>const& shadowMask,
        glm::uvec2                      const& windowSize,
        std::shared_ptr<ge::gl::Texture>const& positionTex,
        uint32_t                        const& nofVertices,
        std::shared_ptr<ge::gl::Buffer> const& vertices);

    virtual ~OmnidirFrustumTracedShadows();

    virtual void create(glm::vec4 const& lightPosition,
        glm::mat4 const& viewMatrix,
        glm::mat4 const& projectionMatrix) override;

    virtual bool init() override;

protected:
    void createRaytrace(glm::vec4 const& lightPosition);

    void createFrusta(glm::vec4 const& lightPosition);

    std::unique_ptr<ge::gl::Program> TriangleFrustaCS;
    std::shared_ptr<ge::gl::Buffer>  Frusta;
    
    uint32_t WgSize = 128;
    uint32_t NofWgs = 0;

};