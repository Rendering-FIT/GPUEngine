#include "ShadowMapping.h"
#include "ShadowMapShaders.h"


ShadowMapping::ShadowMapping(
	std::shared_ptr<ge::gl::Texture>const&shadowMask,
	glm::uvec2                      const&windowSize,
	std::shared_ptr<ge::gl::Texture>const&positionTex,
	uint32_t                        const&nofVertices,
	std::shared_ptr<ge::gl::Buffer> const&vertices,
	ShadowMappingParams         const&params) :
	_windowSize(windowSize),
	_positionTexture(positionTex),
	_nofVertices(nofVertices),
	_params(params)
{
	_shadowMap = std::make_shared<ge::gl::Texture>(GL_TEXTURE_2D, GL_DEPTH_COMPONENT24, 1, _params.resolution, _params.resolution);
	_shadowMap->texParameteri(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	_shadowMap->texParameteri(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	_shadowMap->texParameteri(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	_shadowMap->texParameteri(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	_shadowMap->texParameteri(GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	_shadowMap->texParameteri(GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);

	_fbo = std::make_shared<ge::gl::Framebuffer>();
	_fbo->attachTexture(GL_DEPTH_ATTACHMENT, _shadowMap);

	_vao = std::make_shared<ge::gl::VertexArray>();
	_vao->addAttrib(vertices, 0, 3, GL_FLOAT);

	_maskVao = std::make_shared<ge::gl::VertexArray>();
	_maskFbo = std::make_shared<ge::gl::Framebuffer>();
	_maskFbo->attachTexture(GL_COLOR_ATTACHMENT0, shadowMask);
	_maskFbo->drawBuffers(1, GL_COLOR_ATTACHMENT0);


	_createShadowMap = std::make_shared<ge::gl::Program>( std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, smVsSource));

	_createShadowMask = std::make_shared<ge::gl::Program>(
		std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, smMaskVs),
		std::make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER, smMaskFs));

	_lightProj = computeLightProj(_params.near, _params.far, _params.fovy);

	_texelSize = 1.0f / _params.resolution;
}

ShadowMapping::~ShadowMapping() {}

void ShadowMapping::create(
	glm::vec4 const&lightPosition,
	glm::mat4 const&,
	glm::mat4 const&) 
{
	if (timeStamp)
	{
		timeStamp->stamp("");
	}

	_lightView = computeLightView(lightPosition, _params.viewDir, _params.upDir);

	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(2.5, 10);
	glViewport(0, 0, _params.resolution, _params.resolution);
	glEnable(GL_DEPTH_TEST);
	_fbo->bind();
	glClear(GL_DEPTH_BUFFER_BIT);
	_vao->bind();

	glm::mat4 lightVP = _lightProj * _lightView;
	_createShadowMap->setMatrix4fv("lightVP", glm::value_ptr(lightVP));
	_createShadowMap->use();

	glDrawArrays(GL_TRIANGLES, 0, _nofVertices);
	_vao->unbind();
	_fbo->unbind();
	
	if (timeStamp)
	{
		timeStamp->stamp("createShadowMap");
	}
	//--------------
	glViewport(0, 0, _windowSize.x, _windowSize.y);
	_maskFbo->bind();
	_maskVao->bind();

	_createShadowMask->setMatrix4fv("lightVP", glm::value_ptr(lightVP));
	_createShadowMask->set1i("pcfSize", _params.pcfTaps);
	_createShadowMask->set1f("texelSize", _texelSize);
	_createShadowMask->use();

	_positionTexture->bind(0);
	_shadowMap->bind(1);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	_maskVao->unbind();
	_maskFbo->unbind();

	if (timeStamp)
	{
		timeStamp->stamp("createShadowMask");
	}
}


glm::mat4 ShadowMapping::computeLightView(glm::vec3 const& lightPos, glm::vec3 const& viewVec, glm::vec3 const& upVec)
{
	return glm::lookAt(lightPos, lightPos + viewVec, upVec);
}

glm::mat4 ShadowMapping::computeLightProj(float nearZ, float farZ, float fovY)
{
	return glm::perspective(fovY, 1.0f, nearZ, farZ);
}