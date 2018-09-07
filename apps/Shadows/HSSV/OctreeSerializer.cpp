#include "OctreeSerializer.hpp"
#include <glm/gtc/type_ptr.inl>

#include <iostream>
#include <sstream>

std::string OctreeSerializer::_generateFileName(const std::string& modelFilename, const glm::vec3& sceneScale, unsigned int deepestLevel, unsigned int compressionRatio) const
{
	std::stringstream str;
	str << modelFilename << "_" << sceneScale[0] << "_" << sceneScale[1] << "_" << sceneScale[2] << "-" << deepestLevel << "c" << compressionRatio << ".hssvc";

	return str.str();
}

std::shared_ptr<Octree> OctreeSerializer::loadFromFile(const std::string& modelFilename, const glm::vec3& sceneScale, unsigned int deepestLevel, unsigned int compressionLevel)
{
	FILE* input = fopen(_generateFileName(modelFilename, sceneScale, deepestLevel, compressionLevel).c_str(), "rb");
	if (!input)
		return nullptr;

	//Read num levels
	const uint32_t numLevels = _readUint(input);

	//Read compression level
	const uint32_t compression = _readUint(input);

	if (compression != compressionLevel)
		return nullptr;

	//Read root AABB
	AABB rootVolume;
	_readAabb(input, rootVolume);

	//Create octree
	std::shared_ptr<Octree> octree = std::make_shared<Octree>(numLevels, rootVolume);
	octree->setCompressionLevel(compressionLevel);

	//Read node data
	const unsigned int numNodes = octree->getTotalNumNodes();

	for (unsigned int i = 0; i < numNodes; ++i)
	{
		{
			//Read number of potential subbuffers
			const unsigned int numSubbuffersPotential = _readUint(input);

			auto node = octree->getNode(i);

			for (unsigned int bufferId = 0; bufferId < numSubbuffersPotential; ++bufferId)
			{
				//Read subbuffer id
				const unsigned int subbufferId = _readUint(input);

				//Read subbuffer size
				const unsigned int subbufferSize = _readUint(input);

				//Read subbuffer data
				_readUintBuffer(input, subbufferSize, node->edgesMayCastMap[subbufferId]);
			}
		}

		{
			//Read number of silhouette subbuffers
			const unsigned int numSubbuffersSilhouette = _readUint(input);

			auto node = octree->getNode(i);

			for (unsigned int bufferId = 0; bufferId < numSubbuffersSilhouette; ++bufferId)
			{
				//Read subbuffer id
				const unsigned int subbufferId = _readUint(input);

				//Read subbuffer size
				const unsigned int subbufferSize = _readUint(input);

				//Read subbuffer data
				_readUintBuffer(input, subbufferSize, node->edgesAlwaysCastMap[subbufferId]);
			}
		}
	}

	fclose(input);

	return octree;
}

void OctreeSerializer::storeToFile(const std::string& modelFilename, const glm::vec3& sceneScale, std::shared_ptr<Octree> octree)
{
	FILE* output = fopen(_generateFileName(modelFilename, sceneScale, octree->getDeepestLevel(), octree->getCompressionLevel()).c_str(), "wb");
	if (!output)
		return;

	//Write octree level
	_writeUint(output, octree->getDeepestLevel());

	//Write octree compression level
	_writeUint(output, octree->getCompressionLevel());

	//Write top level AABB
	_writeAabb(output, octree->getNode(0)->volume);

	//Write nodes
	const unsigned int nofNodes = octree->getTotalNumNodes();
	for (unsigned int i = 0; i<nofNodes; ++i)
	{
		auto node = octree->getNode(i);

		{
			//Write nof potential subbuffers
			_writeUint(output, node->edgesMayCastMap.size());

			for(const auto subBuffer : node->edgesMayCastMap)
			{
				//Write subbuffer Id (bitmask)
				_writeUint(output, subBuffer.first);

				//write subbuffer size
				_writeUint(output, subBuffer.second.size());

				//write data
				_writeUintBuffer(output, subBuffer.second);
			}
		}

		{
			//Write nof silhouette subbuffers
			_writeUint(output, node->edgesAlwaysCastMap.size());

			for (const auto subBuffer : node->edgesAlwaysCastMap)
			{
				//Write subbuffer Id (bitmask)
				_writeUint(output, subBuffer.first);

				//write subbuffer size
				_writeUint(output, subBuffer.second.size());

				//write data
				_writeUintBuffer(output, subBuffer.second);
			}
		}

	}

	//Finish
	fclose(output);
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

void OctreeSerializer::_writeUint(FILE* output, uint32_t value)
{
	fwrite(&value, sizeof(uint32_t), 1, output);
}

void OctreeSerializer::_writeAabb(FILE* output, const AABB& bbox)
{
	fwrite(glm::value_ptr(bbox.getMinPoint()), sizeof(float), 3, output);
	fwrite(glm::value_ptr(bbox.getMaxPoint()), sizeof(float), 3, output);
}

void OctreeSerializer::_writeUintBuffer(FILE* output, const std::vector<uint32_t>& buffer)
{
	if (buffer.size() == 0)
		return;

	fwrite(buffer.data(), sizeof(uint32_t), buffer.size(), output);
}