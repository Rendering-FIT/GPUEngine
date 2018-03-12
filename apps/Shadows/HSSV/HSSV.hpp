#pragma once
#include "../ShadowVolumes.h"
#include "../GSCaps.h"

class HSSV : public ShadowVolumes
{
public:
	HSSV(const glm::vec3& sceneAABBscale,
		unsigned int maxOctreeLevel,
		std::shared_ptr<ge::gl::Texture>const& shadowMask,
		std::shared_ptr<ge::gl::Texture>const& depth,
		ShadowVolumesParams const& params);

	void drawSides(glm::vec4 const&lightPosition, glm::mat4 const&viewMatrix, glm::mat4 const&projectionMatrix) override;
	void drawCaps(glm::vec4 const&lightPosition, glm::mat4 const&viewMatrix, glm::mat4 const&projectionMatrix) override;


protected:
	std::shared_ptr<ge::gl::Buffer> _sidesVBO;
	std::shared_ptr<ge::gl::VertexArray> _sidesVAO;
	
	std::shared_ptr<GSCaps> _capsDrawer;
};
