#include"TSSV.hpp"
#include"SidesShaderGenerator.hpp"
#include "capsShaders.hpp"

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
	_initSidesProgram(UseReferenceEdge, CullSides, UseStencilValueExport, ad->getMaxMultiplicity());
	
	_initCapsBuffers(ad);
	_initCapsProgram();
}

TSSV::~TSSV(){}

void TSSV::drawSides(glm::vec4 const& lightPosition, glm::mat4 const& viewMatrix, glm::mat4 const& projectionMatrix)
{
	const glm::mat4 mvp = projectionMatrix * viewMatrix;

	_sidesVAO->bind();
	_sidesProgram->use();
	_sidesProgram->setMatrix4fv("mvp", glm::value_ptr(mvp), 1,GL_FALSE);
	_sidesProgram->set4fv("LightPosition", glm::value_ptr(lightPosition), 1);

	glPatchParameteri(GL_PATCH_VERTICES, _patchVertices);
	glDrawElements(GL_PATCHES, _patchVertices*_nofEdges, GL_UNSIGNED_INT, nullptr);

	_sidesVAO->unbind();
}

void TSSV::drawCaps(glm::vec4 const& lightPosition, glm::mat4 const& viewMatrix, glm::mat4 const& projectionMatrix)
{
	const glm::mat4 mvp = projectionMatrix * viewMatrix;

	_capsVAO->bind();
	_capsProgram->use();
	_capsProgram->setMatrix4fv("mvp", glm::value_ptr(mvp), 1, GL_FALSE);
	_capsProgram->set4fv("LightPosition", glm::value_ptr(lightPosition), 1);
	glDrawArrays(GL_TRIANGLES, 0, _nofCapsTriangles * 3);

	_capsVAO->unbind();
}

void TSSV::_initCapsBuffers(std::shared_ptr<Adjacency const> ad)
{
	_capsVAO = std::make_shared<ge::gl::VertexArray>();

	_nofCapsTriangles = ad->getNofTriangles();

	_capsVBO = std::make_shared<ge::gl::Buffer>(sizeof(float) * 4 * 3 * _nofCapsTriangles, nullptr, GL_STATIC_DRAW);

	float*Ptr = (float*)_capsVBO->map();
	for (unsigned t = 0; t<_nofCapsTriangles; ++t)
	{
		for (unsigned p = 0; p<3; ++p) {
			for (unsigned i = 0; i<3; ++i)
				Ptr[(t * 3 + p) * 4 + i] = ad->getVertices()[(t * 3 + p) * 3 + i];
			Ptr[(t * 3 + p) * 4 + 3] = 1;
		}
	}

	_capsVBO->unmap();

	_capsVAO->addAttrib(_capsVBO, 0, 4, GL_FLOAT);
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
		unsigned base = e*_patchVertices;
		eptr[base + 0] = ad->getEdge(e, 0) / 3;
		eptr[base + 1] = ad->getEdge(e, 1) / 3;
		eptr[base + 2] = ad->getNofTriangles() * 3 + e;
		for (unsigned o = 0; o<ad->getMaxMultiplicity(); ++o)
			if (o<ad->getNofOpposite(e))
				eptr[base + 3 + o] = ad->getOpposite(e, o) / 3;
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
		ptr[(ad->getNofTriangles() * 3 + e) * 4 + 0] = ad->getNofOpposite(e);
	
	this->_sidesVBO->unmap();

	this->_sidesVAO = std::make_shared<ge::gl::VertexArray>();
	this->_sidesVAO->addAttrib(_sidesVBO, 0, 4, GL_FLOAT);
	this->_sidesVAO->addElementBuffer(_sidesEBO);
}

void TSSV::_initCapsProgram()
{
	std::shared_ptr<ge::gl::Shader> vs = std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, vsSource);
	std::shared_ptr<ge::gl::Shader> gs = std::make_shared<ge::gl::Shader>(GL_GEOMETRY_SHADER, gsSource);
	std::shared_ptr<ge::gl::Shader> fs = std::make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER, fsSource);

	_capsProgram = std::make_shared<ge::gl::Program>(vs, gs, fs);
}

void TSSV::_initSidesProgram(bool UseReferenceEdge, bool CullSides, bool UseStencilValueExport, unsigned int maxMultiplicity)
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


