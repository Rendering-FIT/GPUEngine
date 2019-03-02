#include "GSSV.hpp"
#include "GenerateGeometryShaderSilhouette.hpp"

GSSV::GSSV(
	std::shared_ptr<Model> model,
	bool ReferenceEdge,
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
	_initSidesProgram(CullSides, ReferenceEdge, UseStencilValueExport, unsigned(ad->getMaxMultiplicity()));

	_capsDrawer = std::make_shared<GSCaps>(ad);
}

GSSV::~GSSV() {}

void GSSV::drawCaps(glm::vec4 const& lightPosition, glm::mat4 const& viewMatrix, glm::mat4 const& projectionMatrix)
{
	_capsDrawer->drawCaps(lightPosition, viewMatrix, projectionMatrix);
}

void GSSV::_initSidesBuffers(std::shared_ptr<Adjacency const> ad)
{
	unsigned const NumV = 2 + 1 + unsigned(ad->getMaxMultiplicity());
	
	_nofEdges = ad->getNofEdges();

	_sidesVBO = std::make_shared<ge::gl::Buffer>(sizeof(float) * 4 * NumV * _nofEdges);

	float* Ptr = (float*)this->_sidesVBO->map();
	const float*vertices = ad->getVertices();

	for (unsigned e = 0; e < _nofEdges; ++e)
	{
		//A
		for (int k = 0; k < 3; ++k)
			Ptr[(e*NumV + 0) * 4 + k] = vertices[ad->getEdge(e, 0) + k];
		Ptr[(e*NumV + 0) * 4 + 3] = 1;
		//B
		for (int k = 0; k < 3; ++k)
			Ptr[(e*NumV + 1) * 4 + k] = vertices[ad->getEdge(e, 1) + k];
		Ptr[(e*NumV + 1) * 4 + 3] = 1;
		//N
		Ptr[(e*NumV + 2) * 4 + 0] = float(ad->getNofOpposite(e));
		for (int k = 1; k < 4; ++k)
			Ptr[(e*NumV + 2) * 4 + k] = 0;
		//Oi
		unsigned o = 0;
		for (; o < ad->getNofOpposite(e); ++o) 
		{
			for (int k = 0; k < 3; ++k)
				Ptr[(e*NumV + 2 + 1 + o) * 4 + k] = vertices[ad->getOpposite(e, o) + k];
			Ptr[(e*NumV + 2 + 1 + o) * 4 + 3] = 1;
		}
		//zeros
		for (; o < ad->getNofOpposite(e); ++o)
			for (int k = 0; k < 4; ++k)Ptr[(e*NumV + 2 + 1 + o) * 4 + k] = 0;
	}
	_sidesVBO->unmap();

	_sidesVAO = std::make_shared<ge::gl::VertexArray>();
	
	for (unsigned a = 0; a < NumV; ++a) 
	{
		_sidesVAO->addAttrib( _sidesVBO, a, 4, GL_FLOAT, sizeof(float) * 4 * NumV, (GLintptr)(sizeof(float) * 4 * a));
	}
}

void GSSV::_initSidesProgram(bool CullSides, bool ReferenceEdge, bool UseStencilValueExport, uint32_t maxMultiplicity)
{
	SGSSilTemplate TGS;

	TGS.Deterministic = true;
	TGS.ReferenceEdge = ReferenceEdge;
	TGS.Universal = true;
	TGS.UseVS2GSArray = true;
	TGS.UseVertexArray = true;
	TGS.UseLayouts = true;
	TGS.UseStencilValueExport = UseStencilValueExport;
	TGS.CCWIsFrontFace = true;
	TGS.FrontFaceInside = false;
	TGS.CullSides = CullSides;
	TGS.Visualize = false;
	TGS.FrontCapToInfinity = false;
	TGS.GenerateSides = true;
	TGS.GenerateCaps = false;
	TGS.Matrix = "mvp";
	TGS.MaxMultiplicity = maxMultiplicity;
	TGS.LightUniform = "LightPosition";
	TGS.VertexAttribName = "Position";

	std::shared_ptr<ge::gl::Shader>GSSilVer = std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, genGsSilVertexShader(TGS));
	std::shared_ptr<ge::gl::Shader>GSSilGeom = std::make_shared<ge::gl::Shader>(GL_GEOMETRY_SHADER, genGsSilGeometryShader(TGS));
	std::shared_ptr<ge::gl::Shader>GSSilFrag = std::make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER, genGsSilFragmentShader(TGS));

	_sidesProgram = std::make_shared<ge::gl::Program>(GSSilVer, GSSilGeom, GSSilFrag);
}

void GSSV::drawSides(glm::vec4 const& lightPosition, glm::mat4 const& viewMatrix, glm::mat4 const& projectionMatrix)
{
	const glm::mat4 mvp = projectionMatrix * viewMatrix;

	_sidesVAO->bind();
	_sidesProgram->use();
	_sidesProgram->setMatrix4fv("mvp", glm::value_ptr(mvp), 1, GL_FALSE);
	_sidesProgram->set4fv("LightPosition", glm::value_ptr(lightPosition), 1);

  glDrawArrays(GL_POINTS,0,_nofEdges);

	_sidesVAO->unbind();
}
