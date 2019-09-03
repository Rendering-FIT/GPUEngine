#pragma once

#include <geGL/geGL.h>
#include "../ShadowMethod.h"

struct ShadowMappingParams 
{
	glm::vec3 viewDir = glm::vec3(0, -1, 0);
	glm::vec3 upDir =   glm::vec3(0, 1, 0);
	float     near = 0.1f;
	float     far = 1000.f;
	float     fovy = 45.0f;
	uint32_t  resolution = 1024;
	uint32_t  pcfTaps = 1;
};

class ShadowMapping : public ShadowMethod 
{
public:
	ShadowMapping(
		std::shared_ptr<ge::gl::Texture>const&shadowMask,
		glm::uvec2                      const&windowSize,
		std::shared_ptr<ge::gl::Texture>const&positionTex,
		uint32_t                        const&nofVertices,
		std::shared_ptr<ge::gl::Buffer> const&vertices,
		ShadowMappingParams         const&params);

	virtual ~ShadowMapping();

	virtual void create(
		glm::vec4 const&lightPosition,
		glm::mat4 const&viewMatrix,
		glm::mat4 const&projectionMatrix) override;

	void setViewProps(glm::vec3 const& view, glm::vec3 const& up) { _params.viewDir = view; _params.upDir = up; }

protected:

	glm::mat4 computeLightView(glm::vec3 const& lightPos, glm::vec3 const& viewVec, glm::vec3 const& upVec);
	glm::mat4 computeLightProj(float nearZ, float farZ, float fovY);

	glm::uvec2                          _windowSize;
	std::shared_ptr<ge::gl::Texture>    _positionTexture = nullptr;
	uint32_t                            _nofVertices = 0;
	std::shared_ptr<ge::gl::Texture>    _shadowMap = nullptr;
	std::shared_ptr<ge::gl::Framebuffer>_fbo = nullptr;
	std::shared_ptr<ge::gl::VertexArray>_vao = nullptr;
	std::shared_ptr<ge::gl::VertexArray>_maskVao = nullptr;
	std::shared_ptr<ge::gl::Framebuffer>_maskFbo = nullptr;
	std::shared_ptr<ge::gl::Program>    _createShadowMap = nullptr;
	std::shared_ptr<ge::gl::Program>    _createShadowMask = nullptr;
	
	ShadowMappingParams					_params;

	glm::mat4							_lightView;
	glm::mat4							_lightProj;
	float								_texelSize = 0;
};
