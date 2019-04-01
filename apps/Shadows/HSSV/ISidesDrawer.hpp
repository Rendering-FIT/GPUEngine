#pragma once
#include "apps/Shadows/TimeStamp.h"
#include "GpuEdges.hpp"
#include <glm/glm.hpp>

class OctreeVisitor;
class Adjacency;
class Octree;

class ISidesDrawer
{
public:
	ISidesDrawer(std::shared_ptr<OctreeVisitor> visitor)
	{
		_visitor = visitor;
	}

	virtual ~ISidesDrawer() {}

	virtual bool init(std::shared_ptr<GpuEdges> gpuEdges) = 0;

	virtual void drawSides(const glm::mat4& mvp, const glm::vec4& light) = 0;


	void setStamper(std::shared_ptr<TimeStamp> stamper)
	{
		_timer = stamper;
	}

protected:
	std::shared_ptr<TimeStamp> _timer;
	std::shared_ptr<OctreeVisitor> _visitor;
};
