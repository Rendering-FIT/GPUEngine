#include"TSSV.hpp"
#include"SidesShaderGenerator.hpp"


TSSV::TSSV(
    std::shared_ptr<Model> model,
    bool UseReferenceEdge,
    bool CullSides,
    bool UseStencilValueExport,
	size_t maxMultiplicity,
	std::shared_ptr<ge::gl::Texture>const& shadowMask,
	std::shared_ptr<ge::gl::Texture>const& depth,
	ShadowVolumesParams const& params) : ShadowVolumes(shadowMask, depth, params)
{ 
	std::vector<float>vertices;
	model->getVertices(vertices);

	size_t const nofTriangles = vertices.size() / (verticesPerTriangle*componentsPerVertex3D);
	auto const ad = std::make_shared<Adjacency const>(vertices.data(), nofTriangles, maxMultiplicity);

	_initSidesBuffers(ad);
	_initSidesProgram(UseReferenceEdge, CullSides, UseStencilValueExport, unsigned(ad->getMaxMultiplicity()));
	
	_capsDrawer = std::make_shared<GSCaps>(ad);
}

TSSV::~TSSV(){}

void TSSV::drawSides(glm::vec4 const& lightPosition, glm::mat4 const& viewMatrix, glm::mat4 const& projectionMatrix)
{
	const glm::mat4 mvp = projectionMatrix * viewMatrix;

	_sidesVAO->bind();
	_sidesProgram->use();
	_sidesProgram->setMatrix4fv("mvp", glm::value_ptr(mvp), 1,GL_FALSE);
	_sidesProgram->set4fv("LightPosition", glm::value_ptr(lightPosition), 1);

	glPatchParameteri(GL_PATCH_VERTICES, GLint(_patchVertices));
	glDrawElements(GL_PATCHES, GLsizei(_patchVertices*_nofEdges), GL_UNSIGNED_INT, nullptr);

	_sidesVAO->unbind();
}

void TSSV::drawCaps(glm::vec4 const& lightPosition, glm::mat4 const& viewMatrix, glm::mat4 const& projectionMatrix)
{
	_capsDrawer->drawCaps(lightPosition, viewMatrix, projectionMatrix);
}

void TSSV::_initSidesBuffers(std::shared_ptr<Adjacency const> ad)
{
	_patchVertices = 2 + 1 + ad->getMaxMultiplicity();
	_nofEdges = ad->getNofEdges();
	_sidesEBO = std::make_shared<ge::gl::Buffer>( sizeof(unsigned)*_patchVertices*ad->getNofEdges());
	
	unsigned*eptr = (unsigned*)_sidesEBO->map();
	for (unsigned e = 0; e<ad->getNofEdges(); ++e) 
	{
		//loop over edges
		unsigned base = e*unsigned(_patchVertices);
		eptr[base + 0] = unsigned(ad->getEdge(e, 0)) / 3;
		eptr[base + 1] = unsigned(ad->getEdge(e, 1)) / 3;
		eptr[base + 2] = unsigned(ad->getNofTriangles()) * 3 + e;
		for (unsigned o = 0; o<ad->getMaxMultiplicity(); ++o)
			if (o<ad->getNofOpposite(e))
				eptr[base + 3 + o] = unsigned(ad->getOpposite(e, o)) / 3;
			else eptr[base + 3 + o] = 0;
	}

	this->_sidesEBO->unmap();

	this->_sidesVBO = std::make_shared<ge::gl::Buffer>(sizeof(float) * 4 * (ad->getNofTriangles() * 3 + ad->getNofEdges()));
	
	float*ptr = (float*)this->_sidesVBO->map();

	for (unsigned p = 0; p<ad->getNofTriangles() * 3; ++p) 
	{
		//loop over points
		for (unsigned e = 0; e<3; ++e)
			ptr[p * 4 + e] = ad->getVertices()[p * 3 + e];
		ptr[p * 4 + 3] = 1;
	}

	for (unsigned e = 0; e<ad->getNofEdges(); ++e)
		ptr[(ad->getNofTriangles() * 3 + e) * 4 + 0] = float(ad->getNofOpposite(e));
	
	this->_sidesVBO->unmap();

	this->_sidesVAO = std::make_shared<ge::gl::VertexArray>();
	this->_sidesVAO->addAttrib(_sidesVBO, 0, 4, GL_FLOAT);
	this->_sidesVAO->addElementBuffer(_sidesEBO);
}

void TSSV::_initSidesProgram(bool UseReferenceEdge, bool CullSides, bool UseStencilValueExport, uint32_t maxMultiplicity)
{
	STSSilTemplate TTS;
	TTS.Version = 430;
	TTS.UseLayouts = true;
	TTS.Universal = true;
	TTS.UseSillyPerPatchLevel = true;
	TTS.UseOptimizedDegeneration = true;
	TTS.UseCompatibility = false;
	TTS.LightPositionUniformName = "LightPosition";
	TTS.MatrixUniformName = "mvp";
	TTS.VertexAttribName = "Position";
	TTS.UseReferenceEdge = UseReferenceEdge;
	TTS.CullSides = CullSides;
	TTS.UseStencilValueExport = UseStencilValueExport;

	std::shared_ptr<ge::gl::Shader>TSSilVerHull2 = std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, GenTSSilVertexHull(TTS));
	std::shared_ptr<ge::gl::Shader>TSSilConHull2 = std::make_shared<ge::gl::Shader>(GL_TESS_CONTROL_SHADER, GenTSSilControlHull(maxMultiplicity, TTS));
	std::shared_ptr<ge::gl::Shader>TSSilEvaHull2 = std::make_shared<ge::gl::Shader>(GL_TESS_EVALUATION_SHADER, GenTSSilEvaluationHull(TTS));
	std::shared_ptr<ge::gl::Shader>TSSilFragHull2 = std::make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER, GenTSSilFragmentHull(TTS));
	
	_sidesProgram = std::make_shared<ge::gl::Program>(TSSilVerHull2, TSSilConHull2, TSSilEvaHull2, TSSilFragHull2);;
}


