#pragma once

#pragma once

#include <geGL/VertexArray.h>
#include <geGL/Program.h>
#include <geGL/Buffer.h>

#include "../FastAdjacency.h"
#include "../ShadowVolumes.h"
#include "../Model.h"
#include "../GSCaps.h"

struct GSSVParams
{
	bool UseReferenceEdge = false;
	bool CullSides = false;
	bool UseStencilValueExport = false;
};

class GSSV : public ShadowVolumes
{
public:
	GSSV(
		std::shared_ptr<Model> model,
		bool ReferenceEdge,
		bool CullSides,
		bool UseStencilValueExport,
		size_t maxMultiplicity,
		std::shared_ptr<ge::gl::Texture>const& shadowMask,
		std::shared_ptr<ge::gl::Texture>const& depth,
		ShadowVolumesParams const& params);

	~GSSV();

	void drawSides(glm::vec4 const&lightPosition, glm::mat4 const&viewMatrix, glm::mat4 const&projectionMatrix) override;
	void drawCaps(glm::vec4 const&lightPosition, glm::mat4 const&viewMatrix, glm::mat4 const&projectionMatrix) override;

private:
	void _initSidesBuffers(const std::shared_ptr<Adjacency const> ad);
	void _initSidesProgram(bool CullSides, bool ReferenceEdge, bool UseStencilValueExport, uint32_t maxMultiplicity);

	std::shared_ptr<ge::gl::Buffer>      _sidesVBO;
	std::shared_ptr<ge::gl::Buffer>      _sidesEBO;
	std::shared_ptr<ge::gl::VertexArray> _sidesVAO;
	std::shared_ptr<ge::gl::Program>     _sidesProgram;

	std::shared_ptr<GSCaps>              _capsDrawer;

	size_t	_nofEdges;
};
