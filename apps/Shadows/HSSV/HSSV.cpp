#include "HSSV.hpp"
#include "SidesProgram.hpp"

#include <glm/gtx/transform.hpp>

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

	size_t const nofTriangles = vertices.size() / (verticesPerTriangle*componentsPerVertex3D);
	_edges = std::make_shared<Adjacency const>(vertices.data(), nofTriangles, 2);

	_capsDrawer = std::make_shared<GSCaps>(_edges);

	AABB sceneBbox = _getSceneAabb(vertices);
	sceneBbox.applyTransform(glm::scale(sceneAABBscale));

	_octree = std::make_shared<Octree>(maxOctreeLevel, sceneBbox);
	_visitor = std::make_shared<OctreeVisitor>(_octree);

	_visitor->addEdges(_edges);

	_prepareBuffers(_edges->getNofEdges() * 6 * 4 * sizeof(float));
}


void HSSV::drawCaps(glm::vec4 const& lightPosition, glm::mat4 const& viewMatrix, glm::mat4 const& projectionMatrix)
{
	_capsDrawer->drawCaps(lightPosition, viewMatrix, projectionMatrix);
}

void HSSV::drawSides(glm::vec4 const& lightPosition, glm::mat4 const& viewMatrix, glm::mat4 const& projectionMatrix)
{
	
}

AABB HSSV::_getSceneAabb(const std::vector<float>& vertices)
{
	AABB bbox;
	bbox.updateWithVerticesVec3(vertices);

	return bbox;
}

void HSSV::_prepareBuffers(size_t maxVboSize)
{
	_sidesVBO = std::make_shared <ge::gl::Buffer>(maxVboSize);
	_sidesVAO = std::make_shared<ge::gl::VertexArray>();

	_sidesVAO->addAttrib(_sidesVBO, 0, 4, GL_FLOAT);
}

void HSSV::_prepareProgram()
{
	std::shared_ptr<ge::gl::Shader> vs = std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, vsSource);
	std::shared_ptr<ge::gl::Shader> fs = std::make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER, fsSource);

	_sidesProgram = std::make_shared<ge::gl::Program>(vs, fs);
}

void HSSV::_updateSidesVBO(const std::vector<float>& vertices)
{
	float* ptr = reinterpret_cast<float*>(_sidesVBO->map(GL_MAP_WRITE_BIT));

	memcpy(ptr, vertices.data(), vertices.size() * sizeof(float));

	_sidesVBO->unmap();
}

void HSSV::_getSilhouetteFromLightPos(const glm::vec3& lightPos, std::vector<float>& silhouetteVertices)
{
	const int lowestNode = _visitor->getLowestNodeIndexFromPoint(lightPos);

	if (lowestNode < 0)
		return;

	const auto n = _octree->getNode(lowestNode);
	auto minP = n->volume.getMinPoint();
	auto maxP = n->volume.getMaxPoint();
	std::cout << "Node space " << minP.x << ", " << minP.y << ", " << minP.z << " Max: " << maxP.x << ", " << maxP.y << ", " << maxP.z << "\n";
	minP = n->volume.getCenterPoint();
	n->volume.getExtents(maxP.x, maxP.y, maxP.z);
	std::cout << "Center " << minP.x << ", " << minP.y << ", " << minP.z << " Extents: " << maxP.x << ", " << maxP.y << ", " << maxP.z << "\n";

	std::vector<int> silhouetteEdges;
	std::vector<int> potentialEdges;

	_visitor->getSilhouttePotentialEdgesFromNodeUp(potentialEdges, silhouetteEdges, lowestNode);


}
