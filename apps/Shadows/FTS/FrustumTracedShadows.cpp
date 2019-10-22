#include "FrustumTracedShadows.h"
#include "FtsShaderGen.h"

#include <cassert>
#include <algorithm>

#include <geGL/Texture.h>
#include <geGL/Buffer.h>
#include <geGL/Program.h>
#include <gegl/Framebuffer.h>
#include <geGL/VertexArray.h>

using namespace ge;
using namespace gl;

FrustumTracedShadows::FrustumTracedShadows(
    ShadowMappingParams             const& params,
    std::shared_ptr<ge::gl::Texture>const& shadowMask,
    glm::uvec2                      const& windowSize,
    std::shared_ptr<ge::gl::Texture>const& positionTex,
    uint32_t                        const& nofVertices,
    std::shared_ptr<ge::gl::Buffer> const& vertices) : IShadowMapping()
{
    assert(shadowMask != nullptr);
    assert(vertices != nullptr);
    assert(positionTex != nullptr);
    assert(nofVertices >= 0);

    _params = params;
    PositionTexture = positionTex;
    Vertices = vertices;
    NofVertices = nofVertices;
    ShadowMask = shadowMask;
    WindowSize = windowSize;
}

FrustumTracedShadows::~FrustumTracedShadows()
{
}

void FrustumTracedShadows::create(glm::vec4 const& lightPosition, glm::mat4 const& viewMatrix, glm::mat4 const& projectionMatrix)
{
    if (timeStamp)
    {
        timeStamp->stamp("");
    }

    assert(glGetError() == GL_NO_ERROR);

    computeLightView(lightPosition, _params.viewDir, _params.upDir);
    glm::mat4 const lightVP = _lightProj * _lightView;

    //Fill IZB
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
    IzbFillProgram->setMatrix4fv("lightVP", glm::value_ptr(lightVP));
    
    IrregularZBuffer->bindBase(GL_SHADER_STORAGE_BUFFER, 0);
    AtomicCounter->bindBase(GL_SHADER_STORAGE_BUFFER, 1);

    glDrawArrays(GL_TRIANGLES, 0, NofVertices);

    Fbo->unbind();
    Vao->unbind();

    //--
    /*
    glFinish();
    std::vector<u32> vec, izbvec;
    vec.resize(_params.resolution.x * _params.resolution.y);
    izbvec.resize(_params.resolution.x * _params.resolution.y * _params.resolution.z);
    AtomicCounter->getData(vec.data(), _params.resolution.x * _params.resolution.y * sizeof(u32));
    IrregularZBuffer->getData(izbvec.data(), _params.resolution.x * _params.resolution.y * _params.resolution.z * sizeof(u32));
    glFinish();
    u32 minVal = 50000;
    u32 maxVax = 0;
    for (auto const& val : vec)
    {
        if (val != 0)
        {
            minVal = std::min(minVal, val);
            maxVax = std::max(maxVax, val);
        }
    }
    //*/
    //--

    //Create shadow mask
    glEnable(GL_DEPTH_TEST);
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glDisable(GL_CONSERVATIVE_RASTERIZATION_NV);
    glViewport(0, 0, WindowSize.x, WindowSize.y);
    glDisable(GL_CULL_FACE);

    ShadowMaskFbo->bind();
    ShadowMaskVao->bind();

    ShadowMaskProgram->use();
    ShadowMaskProgram->setMatrix4fv("lightVP", glm::value_ptr(lightVP));
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

bool FrustumTracedShadows::IsConservativeRasterizationSupported() const
{
    s32 NumberOfExtensions;
    glGetIntegerv(GL_NUM_EXTENSIONS, &NumberOfExtensions);
    for (s32 i = 0; i < NumberOfExtensions; i++) 
    {
        const char* ccc = reinterpret_cast<const char*>(glGetStringi(GL_EXTENSIONS, i));

        if (strcmp(ccc, "GL_NV_conservative_raster") == 0) 
        {
            return true;
        }
    }

    return false;
}

void FrustumTracedShadows::CreateShadowMaskData()
{
    ShadowMaskVao = std::make_unique<VertexArray>();

    ShadowMaskFbo = std::make_unique<Framebuffer>();
    ShadowMaskFbo->attachTexture(GL_COLOR_ATTACHMENT0, ShadowMask);
    ShadowMaskFbo->drawBuffers(1, GL_COLOR_ATTACHMENT0);
}

bool FrustumTracedShadows::init()
{
    if (!IsConservativeRasterizationSupported())
    {
        std::cerr << "Conservative rasterization not supported!\n";
        return false;
    }
    
    computeLightProjPersp(_params.near, _params.far, _params.fovy, float(_params.resolution.x) / float(_params.resolution.y));

    IrregularZBuffer = std::make_shared<Buffer>(_params.resolution.x * _params.resolution.y * _params.resolution.z * sizeof(u32));
    AtomicCounter = std::make_shared<Buffer>(_params.resolution.x * _params.resolution.y * sizeof(u32));

    Fbo = std::make_unique<Framebuffer>();
    Fbo->setDefaultWidth(_params.resolution.x);
    Fbo->setDefaultHeight(_params.resolution.y);

    Vao = std::make_unique<VertexArray>();
    Vao->addAttrib(Vertices, 0, 3, GL_FLOAT);

    CreateShadowMaskData();

    FtsShaderGen shaderGen;
    IzbFillProgram = shaderGen.GetIzbFillProgram(_params.resolution);
    ShadowMaskProgram = shaderGen.GetIzbTraversalProgram(_params.resolution);

    assert(glGetError() == GL_NO_ERROR);

    return (IzbFillProgram != nullptr && ShadowMaskProgram != nullptr);
}
