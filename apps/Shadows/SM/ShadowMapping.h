#pragma once

#include <geGL/geGL.h>
#include "../IShadowMapping.h"

class ShadowMapping : public IShadowMapping
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

protected:

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
	
	glm::vec2							_texelSize;
};
