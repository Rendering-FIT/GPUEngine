#pragma once

#include <geGL/VertexArray.h>
#include <geGL/Program.h>
#include <geGL/Buffer.h>

#include "../FastAdjacency.h"
#include "apps/Shadows/ShadowVolumes.h"
#include "apps/Shadows/Model.h"

struct TSSVParams
{
	bool UseReferenceEdge = false;
	bool CullSides = false;
	bool UseStencilValueExport = false;
};

class TSSV : public ShadowVolumes
{
  public:
	  TSSV(
		std::shared_ptr<Model> model,
        bool UseReferenceEdge,
		bool CullSides,
        bool UseStencilValueExport,
		size_t maxMultiplicity,
		std::shared_ptr<ge::gl::Texture>const& shadowMask,
		std::shared_ptr<ge::gl::Texture>const& depth,
		ShadowVolumesParams const& params);
    
	~TSSV();
	
	void drawSides( glm::vec4 const&lightPosition, glm::mat4 const&viewMatrix, glm::mat4 const&projectionMatrix) override;
	void drawCaps(glm::vec4 const&lightPosition, glm::mat4 const&viewMatrix, glm::mat4 const&projectionMatrix) override;

private:

	void _initCapsBuffers(std::shared_ptr<Adjacency const> ad);
	void _initCapsProgram();

	void _initSidesBuffers(const std::shared_ptr<Adjacency const> ad);
	void _initSidesProgram(bool UseReferenceEdge, bool CullSides, bool UseStencilValueExport, unsigned int maxMultiplicity);

    std::shared_ptr<ge::gl::Buffer> _sidesVBO;
	std::shared_ptr<ge::gl::Buffer> _sidesEBO;
	std::shared_ptr<ge::gl::VertexArray> _sidesVAO;
	std::shared_ptr<ge::gl::Program> _sidesProgram;

	std::shared_ptr<ge::gl::Buffer> _capsVBO;
	std::shared_ptr<ge::gl::VertexArray> _capsVAO;
	std::shared_ptr<ge::gl::Program> _capsProgram;

	size_t	_patchVertices;
    size_t		_nofEdges;
	size_t		_nofCapsTriangles;
};
