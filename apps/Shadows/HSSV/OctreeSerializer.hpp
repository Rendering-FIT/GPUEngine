#pragma once
#include <string>
#include <memory>
#include "Octree.hpp"

class OctreeSerializer
{
public:
	std::shared_ptr<Octree> loadFromFile(const std::string& modelFilename, const glm::vec3& sceneScale, unsigned int deepestLevel);
	void storeToFile(const std::string& modelFilename, const glm::vec3& sceneScale, std::shared_ptr<Octree> octree);

protected:
	std::string _generateFileName(const std::string& modelFilename, const glm::vec3& sceneScale, unsigned int deepestLevel) const;

	uint32_t _readUint(FILE* input);
	void	 _readAabb(FILE* input, AABB& bbox);
	void	 _readUintBuffer(FILE* input, unsigned int nofUints, std::vector<uint32_t>& buffer);

	void	 _writeUint(FILE* output, uint32_t value);
	void     _writeAabb(FILE* output, const AABB& bbox);
	void	 _writeUintBuffer(FILE* output, const std::vector<uint32_t>& buffer);
};
