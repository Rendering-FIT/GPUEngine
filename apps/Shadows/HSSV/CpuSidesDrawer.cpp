#include "CpuSidesDrawer.hpp"
#include "SidesProgram.hpp"
#include "geGL/StaticCalls.h"
#include "MultiplicityCoding.hpp"
#include "AdjacencyEdgeWrapper.hpp"
#include "GeometryOperations.hpp"

#include <algorithm>
#include <iostream>
#include <fstream>

CpuSidesDrawer::CpuSidesDrawer(std::shared_ptr<OctreeVisitor> visitor, std::shared_ptr<const Adjacency> edges) : ISidesDrawer(visitor), _edges(edges)
{
	_octree = _visitor->getOctree();
}

bool CpuSidesDrawer::init(std::shared_ptr<GpuEdges> gpuEdges)
{
	_prepareProgram();
	_prepareBuffers(2 * _edges->getNofEdges() * 6 * 4 * sizeof(float));

	return true;
}

void CpuSidesDrawer::_prepareBuffers(size_t maxVboSize)
{
	_sidesVBO = std::make_shared <ge::gl::Buffer>(maxVboSize);
	_sidesVAO = std::make_shared<ge::gl::VertexArray>();

	_sidesVAO->addAttrib(_sidesVBO, 0, 4, GL_FLOAT);
}

void CpuSidesDrawer::_prepareProgram()
{
	std::shared_ptr<ge::gl::Shader> vs = std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, hssvVsSource);
	std::shared_ptr<ge::gl::Shader> fs = std::make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER, hssvFsSource);

	_sidesProgram = std::make_shared<ge::gl::Program>(vs, fs);
}

void CpuSidesDrawer::drawSides(const glm::mat4& mvp, const glm::vec4& light)
{
	std::vector<float> sidesGeometry;

	_getSilhouetteFromLightPos(light, sidesGeometry);
	
	_updateSidesVBO(sidesGeometry);
	
	_sidesVAO->bind();
	_sidesProgram->use();
	_sidesProgram->setMatrix4fv("mvp", glm::value_ptr(mvp));
	
	ge::gl::glDrawArrays(GL_TRIANGLES, 0, sidesGeometry.size() / 4);
	
	_sidesVAO->unbind();
}

void CpuSidesDrawer::_updateSidesVBO(const std::vector<float>& vertices)
{
	float* ptr = reinterpret_cast<float*>(_sidesVBO->map(GL_MAP_WRITE_BIT));

	memcpy(ptr, vertices.data(), vertices.size() * sizeof(float));

	_sidesVBO->unmap();
}

void CpuSidesDrawer::_getSilhouetteFromLightPos(const glm::vec3& lightPos, std::vector<float>& sidesVertices)
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

	std::vector<uint32_t> silhouetteEdges;
	std::vector<uint32_t> potentialEdges;

	_visitor->getSilhouttePotentialEdgesFromNodeUp(potentialEdges, silhouetteEdges, lowestNode);

	sidesVertices.clear();
	sidesVertices.reserve((potentialEdges.size() + silhouetteEdges.size()) * 4);

	//--
	std::vector<int> ed;
	ed.insert(ed.end(), silhouetteEdges.begin(), silhouetteEdges.end());
	//--

	for (const auto edge : silhouetteEdges)
	{
		int const multiplicity = decodeEdgeMultiplicityFromId(edge);
		auto const& lowerPoint = getEdgeVertexLow(_edges, decodeEdgeFromEncoded(edge));
		auto const& higherPoint = getEdgeVertexHigh(_edges, decodeEdgeFromEncoded(edge));;

		_generatePushSideFromEdge(lightPos, lowerPoint, higherPoint, multiplicity, sidesVertices);
	}
	//*/
	for (const auto edge : potentialEdges)
	{
		const int multiplicity = GeometryOps::calcEdgeMultiplicity(_edges, edge, lightPos);
		if (multiplicity != 0)
		{
			const glm::vec3& lowerPoint = getEdgeVertexLow(_edges, edge);
			const glm::vec3& higherPoint = getEdgeVertexHigh(_edges, edge);

			_generatePushSideFromEdge(lightPos, lowerPoint, higherPoint, multiplicity, sidesVertices);
			ed.push_back(encodeEdgeMultiplicityToId(edge, multiplicity));
		}
	}

	static bool printOnce = false;
	if (!printOnce)
	{
		std::cout << "Light node: " << lowestNode << std::endl;
		std::cout << "Light " << lightPos.x << ", " << lightPos.y << ", " << lightPos.z << std::endl;
		const auto n = _octree->getNode(lowestNode);
		auto minP = n->volume.getMinPoint();
		auto maxP = n->volume.getMaxPoint();
		std::cout << "Node space " << minP.x << ", " << minP.y << ", " << minP.z << " Max: " << maxP.x << ", " << maxP.y << ", " << maxP.z << "\n";
		minP = n->volume.getCenterPoint();
		n->volume.getExtents(maxP.x, maxP.y, maxP.z);
		std::cout << "Center " << minP.x << ", " << minP.y << ", " << minP.z << " Extents: " << maxP.x << ", " << maxP.y << ", " << maxP.z << "\n";

		std::cout << "Num potential: " << potentialEdges.size() << ", numSilhouette: " << silhouetteEdges.size() << std::endl;
		std::cout << "Silhouette consists of " << ed.size() << " edges\n";

		std::ofstream of;
		of.open("CPU_Edges.txt");
		std::sort(potentialEdges.begin(), potentialEdges.end());
		std::sort(silhouetteEdges.begin(), silhouetteEdges.end());

		of << "Potential:\n";
		for (const auto e : potentialEdges)
			of << e << std::endl;

		of << "\nSilhouette:\n";
		for (const auto e : silhouetteEdges)
			of << decodeEdgeFromEncoded(e) << " multiplicity: " << decodeEdgeMultiplicityFromId(e) << std::endl;
		of.close();
		/*
		std::ofstream sof;
		sof.open("silhouette.txt");
		sof << "SIL\n";
		for (const auto e : silhouetteEdges)
		sof << decodeEdgeFromEncoded(e) << "(" << decodeEdgeMultiplicityFromId(e) << ")" << std::endl;

		sof << "POT\n";
		for (const auto e : ed)
		sof << decodeEdgeFromEncoded(e) << "(" << decodeEdgeMultiplicityFromId(e) << ")" << std::endl;
		sof.close();
		//*/

		printOnce = true;
	}
	//*/
}

void CpuSidesDrawer::_generatePushSideFromEdge(const glm::vec3& lightPos, const glm::vec3& lowerPoint, const glm::vec3& higherPoint, int multiplicity, std::vector<float>& sides)
{
	const glm::vec3 lowInfinity = lowerPoint - lightPos;
	const glm::vec3 highInfinity = higherPoint - lightPos;

	const uint32_t absMultiplicity = abs(multiplicity);

	if (multiplicity > 0)
	{
		for (uint32_t i = 0; i < absMultiplicity; ++i)
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
		for (uint32_t i = 0; i < absMultiplicity; ++i)
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