#include "HSSV.hpp"
#include "SidesProgram.hpp"

#include <glm/gtx/transform.hpp>
#include "geGL/StaticCalls.h"

HSSV::HSSV(
	std::shared_ptr<Model> model,
	const glm::vec3& sceneAABBscale, 
	unsigned maxOctreeLevel, 
	std::shared_ptr<ge::gl::Texture> const& shadowMask, 
	std::shared_ptr<ge::gl::Texture> const& depth, 
	ShadowVolumesParams const& params) : ShadowVolumes(shadowMask, depth, params)
{
	std::vector<float>vertices;
	model->getVertices(vertices);
	const auto nofVertexFloats = vertices.size();

	_vertices = new float[vertices.size()];
	memcpy(_vertices, vertices.data(), vertices.size() * sizeof(float));
	vertices.swap(std::vector<float>());

	size_t const nofTriangles = nofVertexFloats / (verticesPerTriangle*componentsPerVertex3D);
	_edges = std::make_shared<Adjacency const>(_vertices, nofTriangles, 2);

	_capsDrawer = std::make_shared<GSCaps>(_edges);

	AABB sceneBbox = _getSceneAabb(_vertices, nofVertexFloats);
	_fixSceneAABB(sceneBbox);

	auto minP = sceneBbox.getMinPoint();
	auto maxP = sceneBbox.getMaxPoint();
	std::cout << "Scene AABB " << minP.x << ", " << minP.y << ", " << minP.z << " Max: " << maxP.x << ", " << maxP.y << ", " << maxP.z << "\n";

	sceneBbox.applyTransform(glm::scale(sceneAABBscale));

	minP = sceneBbox.getMinPoint();
	maxP = sceneBbox.getMaxPoint();
	std::cout << "Octree working space: " << minP.x << ", " << minP.y << ", " << minP.z << " Max: " << maxP.x << ", " << maxP.y << ", " << maxP.z << "\n";

	_octree = std::make_shared<Octree>(maxOctreeLevel, sceneBbox);
	_visitor = std::make_shared<OctreeVisitor>(_octree);

	_visitor->addEdges(_edges);

	_prepareBuffers(2 * _edges->getNofEdges() * 6 * 4 * sizeof(float));
	_prepareProgram();
}

HSSV::~HSSV()
{
	if (_vertices)
		delete[] _vertices;
}

void HSSV::drawCaps(glm::vec4 const& lightPosition, glm::mat4 const& viewMatrix, glm::mat4 const& projectionMatrix)
{
	_capsDrawer->drawCaps(lightPosition, viewMatrix, projectionMatrix);
}

void HSSV::drawSides(glm::vec4 const& lightPosition, glm::mat4 const& viewMatrix, glm::mat4 const& projectionMatrix)
{
	const glm::mat4 mvp = projectionMatrix * viewMatrix;
	
	std::vector<float> sidesGeometry;

	_getSilhouetteFromLightPos(lightPosition, sidesGeometry);
	_updateSidesVBO(sidesGeometry);

	_sidesVAO->bind();
	_sidesProgram->use();
	_sidesProgram->setMatrix4fv("mvp", glm::value_ptr(mvp));

	ge::gl::glDrawArrays(GL_TRIANGLES, 0, sidesGeometry.size() / 4);

	_sidesVAO->unbind();
}

AABB HSSV::_getSceneAabb(float* vertices3fv, size_t numVerticesFloats)
{
	AABB bbox;
	bbox.updateWithVerticesVec3(vertices3fv, numVerticesFloats);

	return bbox;
}

void HSSV::_fixSceneAABB(AABB& bbox)
{
	float ex, ey, ez;
	bbox.getExtents(ex, ey, ez);

	const float minSize = 0.01f;

	if(ex==0)
	{
		auto min = bbox.getMinPoint();
		auto max = bbox.getMaxPoint();

		bbox.setMinMaxPoints(min - glm::vec3(minSize, 0, 0), max + glm::vec3(minSize, 0, 0));

		std::cout << "Fixing X AABB dimension\n";
	}

	if(ey==0)
	{
		auto min = bbox.getMinPoint();
		auto max = bbox.getMaxPoint();

		bbox.setMinMaxPoints(min - glm::vec3(0, minSize, 0), max + glm::vec3(0, minSize, 0));

		std::cout << "Fixing Y AABB dimension\n";
	}

	if(ez==0)
	{
		auto min = bbox.getMinPoint();
		auto max = bbox.getMaxPoint();

		bbox.setMinMaxPoints(min - glm::vec3(0, 0, minSize), max + glm::vec3(0, 0, minSize));

		std::cout << "Fixing Z AABB dimension\n";
	}
}

void HSSV::_prepareBuffers(size_t maxVboSize)
{
	_sidesVBO = std::make_shared <ge::gl::Buffer>(maxVboSize);
	_sidesVAO = std::make_shared<ge::gl::VertexArray>();

	_sidesVAO->addAttrib(_sidesVBO, 0, 4, GL_FLOAT);
}

void HSSV::_prepareProgram()
{
	std::shared_ptr<ge::gl::Shader> vs = std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, hssvVsSource);
	std::shared_ptr<ge::gl::Shader> fs = std::make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER, hssvFsSource);

	_sidesProgram = std::make_shared<ge::gl::Program>(vs, fs);
}

void HSSV::_updateSidesVBO(const std::vector<float>& vertices)
{
	float* ptr = reinterpret_cast<float*>(_sidesVBO->map(GL_MAP_WRITE_BIT));

	memcpy(ptr, vertices.data(), vertices.size() * sizeof(float));

	_sidesVBO->unmap();
}

void HSSV::_getSilhouetteFromLightPos(const glm::vec3& lightPos, std::vector<float>& sidesVertices)
{
	const int lowestNode = _visitor->getLowestNodeIndexFromPoint(lightPos);

	static bool isLightOut = false;

	if (lowestNode < 0)
	{
		if (!isLightOut)
		{
			std::cerr << "Light (" << lightPos.x << " " << lightPos.y << " " << lightPos.z << ") is out of octree range\n";
			isLightOut = true;
		}
		return;
	}

	isLightOut = false;

	std::vector<int> silhouetteEdges;
	std::vector<int> potentialEdges;

	_visitor->getSilhouttePotentialEdgesFromNodeUp(potentialEdges, silhouetteEdges, lowestNode);

	sidesVertices.clear();
	sidesVertices.reserve((potentialEdges.size() + silhouetteEdges.size()) * 4);

	//--
	std::vector<int> ed;
	ed.insert(ed.end(), silhouetteEdges.begin(), silhouetteEdges.end());
	//--

	for(const auto edge : silhouetteEdges)
	{
		/*
		const int multiplicitySign = edge >= 0 ? 1 : -1;
		glm::vec3 lowerPoint, higherPoint;
		getEdgeVertices(_edges, abs(edge), lowerPoint, higherPoint);

		_generatePushSideFromEdge(lightPos, lowerPoint, higherPoint, multiplicitySign, sidesVertices);
		*/
		const int multiplicity = GeometryOps::calcEdgeMultiplicity(_edges, abs(edge), lightPos);
		if (multiplicity != 0)
		{
			glm::vec3 lowerPoint, higherPoint;
			getEdgeVertices(_edges, abs(edge), lowerPoint, higherPoint);

			_generatePushSideFromEdge(lightPos, lowerPoint, higherPoint, multiplicity, sidesVertices);
			ed.push_back(edge);
		}
	}

	for(const auto edge : potentialEdges)
	{
		const int multiplicity = GeometryOps::calcEdgeMultiplicity(_edges, edge, lightPos);
		if (multiplicity != 0)
		{
			glm::vec3 lowerPoint, higherPoint;
			getEdgeVertices(_edges, edge, lowerPoint, higherPoint);

			_generatePushSideFromEdge(lightPos, lowerPoint, higherPoint, multiplicity, sidesVertices);
			ed.push_back(edge);
		}
	}

	static bool printOnce = false;
	if (!printOnce)
	{
		const auto n = _octree->getNode(lowestNode);
		auto minP = n->volume.getMinPoint();
		auto maxP = n->volume.getMaxPoint();
		std::cout << "Node space " << minP.x << ", " << minP.y << ", " << minP.z << " Max: " << maxP.x << ", " << maxP.y << ", " << maxP.z << "\n";
		minP = n->volume.getCenterPoint();
		n->volume.getExtents(maxP.x, maxP.y, maxP.z);
		std::cout << "Center " << minP.x << ", " << minP.y << ", " << minP.z << " Extents: " << maxP.x << ", " << maxP.y << ", " << maxP.z << "\n";

		std::cout << "Silhouette consists of " << ed.size() << " edges\n";

		printOnce = true;
	}
}

void HSSV::_generatePushSideFromEdge(const glm::vec3& lightPos, const glm::vec3& lowerPoint, const glm::vec3& higherPoint, int multiplicity, std::vector<float>& sides)
{
	const glm::vec3 lowInfinity = lowerPoint - lightPos;
	const glm::vec3 highInfinity = higherPoint - lightPos;

	const unsigned int absMultiplicity = abs(multiplicity);

	if (multiplicity > 0)
	{
		for (unsigned int i = 0; i < absMultiplicity; ++i)
		{
			sides.push_back(highInfinity.x); sides.push_back(highInfinity.y); sides.push_back(highInfinity.z); sides.push_back(0);
			sides.push_back(higherPoint.x); sides.push_back(higherPoint.y); sides.push_back(higherPoint.z); sides.push_back(1.0f);
			sides.push_back(lowerPoint.x); sides.push_back(lowerPoint.y); sides.push_back(lowerPoint.z); sides.push_back(1.0f);

			sides.push_back(lowInfinity.x); sides.push_back(lowInfinity.y); sides.push_back(lowInfinity.z); sides.push_back(0);
			sides.push_back(highInfinity.x); sides.push_back(highInfinity.y); sides.push_back(highInfinity.z); sides.push_back(0);
			sides.push_back(lowerPoint.x); sides.push_back(lowerPoint.y); sides.push_back(lowerPoint.z); sides.push_back(1.0f);
		}
	}
	else if (multiplicity < 0)
	{
		for (unsigned int i = 0; i < absMultiplicity; ++i)
		{
			sides.push_back(lowInfinity.x); sides.push_back(lowInfinity.y); sides.push_back(lowInfinity.z); sides.push_back(0);
			sides.push_back(lowerPoint.x); sides.push_back(lowerPoint.y); sides.push_back(lowerPoint.z); sides.push_back(1.0f);
			sides.push_back(higherPoint.x); sides.push_back(higherPoint.y); sides.push_back(higherPoint.z); sides.push_back(1.0f);

			sides.push_back(highInfinity.x); sides.push_back(highInfinity.y); sides.push_back(highInfinity.z); sides.push_back(0);
			sides.push_back(lowInfinity.x); sides.push_back(lowInfinity.y); sides.push_back(lowInfinity.z); sides.push_back(0);
			sides.push_back(higherPoint.x); sides.push_back(higherPoint.y); sides.push_back(higherPoint.z); sides.push_back(1.0f);
		}
	}
}