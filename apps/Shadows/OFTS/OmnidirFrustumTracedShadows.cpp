#include "OmnidirFrustumTracedShadows.h"
#include "../FTS//FtsShaderGen.h"

#include <algorithm>
#include <cassert>

#include <geGL/Texture.h>
#include <geGL/Buffer.h>
#include <geGL/Program.h>
#include <gegl/Framebuffer.h>
#include <geGL/VertexArray.h>

using namespace ge;
using namespace gl;

constexpr u32 NOF_SIDES = 6u;

//#define USE_FRUSTA

OmnidirFrustumTracedShadows::OmnidirFrustumTracedShadows(ShadowMappingParams const& params, 
    std::shared_ptr<ge::gl::Texture>const& shadowMask, 
    glm::uvec2 const& windowSize, 
    std::shared_ptr<ge::gl::Texture>const& positionTex, 
    uint32_t const& nofVertices, 
    std::shared_ptr<ge::gl::Buffer> const& vertices) : FrustumTracedShadows(params, shadowMask, windowSize, positionTex, nofVertices, vertices)
{
}

OmnidirFrustumTracedShadows::~OmnidirFrustumTracedShadows()
{
}

void OmnidirFrustumTracedShadows::create(glm::vec4 const& lightPosition, glm::mat4 const& viewMatrix, glm::mat4 const& projectionMatrix)
{
#ifdef USE_FRUSTA
    createFrusta(lightPosition);
#else
    createRaytrace(lightPosition);
#endif
}

bool OmnidirFrustumTracedShadows::init()
{
    if (!IsConservativeRasterizationSupported())
    {
        std::cerr << "Conservative rasterization not supported!\n";
        return false;
    }

    IrregularZBuffer = std::make_shared<Buffer>(NOF_SIDES * _params.resolution.x * _params.resolution.y * _params.resolution.z * sizeof(u32));

    AtomicCounter = std::make_shared<Buffer>(NOF_SIDES * _params.resolution.x * _params.resolution.y * sizeof(u32));
    Fbo = std::make_unique<Framebuffer>();
    Fbo->setDefaultWidth(_params.resolution.x);
    Fbo->setDefaultHeight(_params.resolution.y);
    Fbo->setDefaultLayers(NOF_SIDES);

    Vao = std::make_unique<VertexArray>();
    Vao->addAttrib(Vertices, 0, 3, GL_FLOAT);

    CreateShadowMaskData();

    FtsShaderGen shaderGen;
    IzbFillProgram = shaderGen.GetIzbFillProgramOmnidir(_params.resolution);
#ifdef USE_FRUSTA
    ShadowMaskProgram = shaderGen.GetIzbTraversalProgramOmnidirFrusta(_params.resolution);
    TriangleFrustaCS = shaderGen.GetTrianglePreprocessCS(WgSize);
    Frusta = std::make_shared<Buffer>((NofVertices / 3) * 4 * 4 * sizeof(float));
    NofWgs = (NofVertices / 3) / WgSize + 1;
#else
    ShadowMaskProgram = shaderGen.GetIzbTraversalProgramOmnidirRaytrace(_params.resolution);
#endif
    assert(glGetError() == GL_NO_ERROR);

    return (IzbFillProgram != nullptr && ShadowMaskProgram != nullptr);
}

void OmnidirFrustumTracedShadows::createRaytrace(glm::vec4 const& lightPosition)
{
    if (timeStamp)
    {
        timeStamp->stamp("");
    }

    assert(glGetError() == GL_NO_ERROR);

    AtomicCounter->clear(GL_R32UI, GL_RED, GL_INT);

    Fbo->bind();
    Vao->bind();

    glViewport(0, 0, _params.resolution.x, _params.resolution.y);
    glDisable(GL_DEPTH_TEST);
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    glEnable(GL_CONSERVATIVE_RASTERIZATION_NV);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    IzbFillProgram->use();
    IzbFillProgram->set4fv("lightPos", glm::value_ptr(lightPosition));
    IzbFillProgram->set1f("far", _params.far);
    IzbFillProgram->set1f("near", _params.near);

    IrregularZBuffer->bindBase(GL_SHADER_STORAGE_BUFFER, 0);
    AtomicCounter->bindBase(GL_SHADER_STORAGE_BUFFER, 1);

    glDrawArraysInstanced(GL_TRIANGLES, 0, NofVertices, NOF_SIDES);

    Fbo->unbind();
    Vao->unbind();

    //Create shadow mask
    glEnable(GL_DEPTH_TEST);
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glDisable(GL_CONSERVATIVE_RASTERIZATION_NV);
    glViewport(0, 0, WindowSize.x, WindowSize.y);
    glDisable(GL_CULL_FACE);

    ShadowMaskFbo->bind();
    ShadowMaskVao->bind();

    ShadowMaskProgram->use();
    ShadowMaskProgram->set4fv("lightPos", glm::value_ptr(lightPosition));

    PositionTexture->bind(0);

    IrregularZBuffer->bindBase(GL_SHADER_STORAGE_BUFFER, 0);
    AtomicCounter->bindBase(GL_SHADER_STORAGE_BUFFER, 1);
    Vertices->bindBase(GL_SHADER_STORAGE_BUFFER, 2);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    ShadowMaskFbo->unbind();
    ShadowMaskVao->unbind();

    IrregularZBuffer->unbindBase(GL_SHADER_STORAGE_BUFFER, 0);
    AtomicCounter->unbindBase(GL_SHADER_STORAGE_BUFFER, 1);
    Vertices->unbindBase(GL_SHADER_STORAGE_BUFFER, 2);

    assert(glGetError() == GL_NO_ERROR);

    if (timeStamp)
    {
        timeStamp->stamp("createShadowMask");
    }
}

void OmnidirFrustumTracedShadows::createFrusta(glm::vec4 const& lightPosition)
{
    if (timeStamp)
    {
        timeStamp->stamp("");
    }

    assert(glGetError() == GL_NO_ERROR);
    AtomicCounter->clear(GL_R32UI, GL_RED, GL_INT);
    
    //Create frusta
    TriangleFrustaCS->use();
    TriangleFrustaCS->set4fv("lightPos", glm::value_ptr(lightPosition));
    TriangleFrustaCS->set1ui("nofTriangles", NofVertices / 3);

    Vertices->bindBase(GL_SHADER_STORAGE_BUFFER, 0);
    Frusta->bindBase(GL_SHADER_STORAGE_BUFFER, 1);

    glDispatchCompute(NofWgs, 1, 1);

    Vertices->unbindBase(GL_SHADER_STORAGE_BUFFER, 0);
    Frusta->unbindBase(GL_SHADER_STORAGE_BUFFER, 1);

    //Fill IZB
    Fbo->bind();
    Vao->bind();

    glViewport(0, 0, _params.resolution.x, _params.resolution.y);
    glDisable(GL_DEPTH_TEST);
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    glEnable(GL_CONSERVATIVE_RASTERIZATION_NV);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    IzbFillProgram->use();
    IzbFillProgram->set4fv("lightPos", glm::value_ptr(lightPosition));
    IzbFillProgram->set1f("far", _params.far);
    IzbFillProgram->set1f("near", _params.near);

    IrregularZBuffer->bindBase(GL_SHADER_STORAGE_BUFFER, 0);
    AtomicCounter->bindBase(GL_SHADER_STORAGE_BUFFER, 1);

    glDrawArraysInstanced(GL_TRIANGLES, 0, NofVertices, NOF_SIDES);

    Fbo->unbind();
    Vao->unbind();

    //Create shadow mask
    glEnable(GL_DEPTH_TEST);
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glDisable(GL_CONSERVATIVE_RASTERIZATION_NV);
    glViewport(0, 0, WindowSize.x, WindowSize.y);
    glDisable(GL_CULL_FACE);

    ShadowMaskFbo->bind();
    ShadowMaskVao->bind();

    ShadowMaskProgram->use();
    ShadowMaskProgram->set4fv("lightPos", glm::value_ptr(lightPosition));

    PositionTexture->bind(0);

    IrregularZBuffer->bindBase(GL_SHADER_STORAGE_BUFFER, 0);
    AtomicCounter->bindBase(GL_SHADER_STORAGE_BUFFER, 1);
    Frusta->bindBase(GL_SHADER_STORAGE_BUFFER, 2);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    ShadowMaskFbo->unbind();
    ShadowMaskVao->unbind();

    IrregularZBuffer->unbindBase(GL_SHADER_STORAGE_BUFFER, 0);
    AtomicCounter->unbindBase(GL_SHADER_STORAGE_BUFFER, 1);
    Frusta->unbindBase(GL_SHADER_STORAGE_BUFFER, 2);

    assert(glGetError() == GL_NO_ERROR);

    if (timeStamp)
    {
        timeStamp->stamp("createShadowMask");
    }
}
