#include "HSSV.hpp"



void HSSV::drawCaps(glm::vec4 const& lightPosition, glm::mat4 const& viewMatrix, glm::mat4 const& projectionMatrix)
{
	_capsDrawer->drawCaps(lightPosition, viewMatrix, projectionMatrix);
}

void HSSV::drawSides(glm::vec4 const& lightPosition, glm::mat4 const& viewMatrix, glm::mat4 const& projectionMatrix)
{
	
}


