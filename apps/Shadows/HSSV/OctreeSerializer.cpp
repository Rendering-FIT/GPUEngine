#include "OctreeSerializer.hpp"
#include <glm/gtc/type_ptr.inl>

#include <iostream>
#include <sstream>

std::string OctreeSerializer::_generateFileName(const std::string& modelFilename, const glm::vec3& sceneScale, unsigned int deepestLevel) const
{
	std::stringstream str;
	str << modelFilename << "_" << sceneScale[0] << "_" << sceneScale[1] << "_" << sceneScale[2] << "-" << deepestLevel << ".hssv";

	return str.str();
}

std::shared_ptr<Octree> OctreeSerializer::loadFromFile(const std::string& modelFilename, const glm::vec3& sceneScale, unsigned int deepestLevel)
{
	FILE* input = fopen(_generateFileName(modelFilename, sceneScale, deepestLevel).c_str(), "rb");
	if (!input)
		return nullptr;

	//Read num levels
	const uint32_t numLevels = _readUint(input);

	//Read root AABB
	AABB rootVolume;
	_readAabb(input, rootVolume);

	//Create octree
	std::shared_ptr<Octree> octree = std::make_shared<Octree>(numLevels, rootVolume);

	//Read node data
	const unsigned int numNodes = octree->getTotalNumNodes();

	for(unsigned int i=0; i<numNodes; ++i)
	{
		const unsigned int numPotential = _readUint(input);
		const unsigned int numSilhouette = _readUint(input);

		auto node = octree->getNode(i);

		_readUintBuffer(input, numPotential, node->edgesMayCast);
		_readUintBuffer(input, numSilhouette, node->edgesAlwaysCast);
	}

	fclose(input);

	return octree;
}


uint32_t OctreeSerializer::_readUint(FILE* f)
{
	uint32_t n = 0;
	fread(&n, sizeof(uint32_t), 1, f);
	return n;
}

void OctreeSerializer::_readAabb(FILE* f, AABB& bbox)
{
	glm::vec3 minP, maxP;

	fread(glm::value_ptr(minP), sizeof(float), 3, f);
	fread(glm::value_ptr(maxP), sizeof(float), 3, f);

	bbox.setMinMaxPoints(minP, maxP);
}

void OctreeSerializer::_readUintBuffer(FILE* f, unsigned int nofUints, std::vector<uint32_t>& buffer)
{
	if (!nofUints)
		return;
	
	buffer.resize(nofUints);

	fread(buffer.data(), sizeof(uint32_t), nofUints, f);
}

void OctreeSerializer::storeToFile(const std::string& modelFilename, const glm::vec3& sceneScale, std::shared_ptr<Octree> octree)
{
	FILE* output = fopen(_generateFileName(modelFilename, sceneScale, octree->getDeepestLevel()).c_str(), "wb");
	if (!output)
		return;

	//Write octree level
	_writeUint(output, octree->getDeepestLevel());

	//Write top level AABB
	_writeAabb(output, octree->getNode(0)->volume);

	//Write nodes
	const unsigned int nofNodes = octree->getTotalNumNodes();
	for(unsigned int i=0; i<nofNodes; ++i)
	{
		auto node = octree->getNode(i);
		_writeUint(output, node->edgesMayCast.size());
		_writeUint(output, node->edgesAlwaysCast.size());

		_writeUintBuffer(output, node->edgesMayCast);
		_writeUintBuffer(output, node->edgesAlwaysCast);
	}

	//Finish
	fclose(output);
}

void OctreeSerializer::_writeUint(FILE* output, uint32_t value)
{
	fwrite(&value, sizeof(uint32_t), 1, output);
}

void OctreeSerializer::_writeAabb(FILE* output, const AABB& bbox)
{
	fwrite(glm::value_ptr(bbox.getMinPoint()), sizeof(float), 3, output);
	fwrite(glm::value_ptr(bbox.getMaxPoint()), sizeof(float), 3, output);
}

void OctreeSerializer::_writeUintBuffer(FILE* output, std::vector<uint32_t>& buffer)
{
	if (buffer.size() == 0)
		return;

	fwrite(buffer.data(), sizeof(uint32_t), buffer.size(), output);
}