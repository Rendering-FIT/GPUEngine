#pragma once
#include <string>
#include <memory>
#include "Octree.hpp"

class OctreeSerializer
{
public:
	std::shared_ptr<Octree> loadFromFile(const std::string& modelFilename);
	void storeToFile(const std::string& modelFilename, std::shared_ptr<Octree> octree);

protected:
	uint32_t _readUint(FILE* input);
	void	 _readAabb(FILE* input, AABB& bbox);
	void	 _readUintBuffer(FILE* input, unsigned int nofUints, std::vector<uint32_t>& buffer);

	void	 _writeUint(FILE* output, uint32_t value);
	void     _writeAabb(FILE* output, const AABB& bbox);
	void	 _writeUintBuffer(FILE* output, std::vector<uint32_t>& buffer);
};
