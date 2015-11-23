#include "NFPlaneAdjustor.h"


fsg::NFPlaneAdjustor::NFPlaneAdjustor()
   : minimumNear(0.1f)
{
}

/**
 * Computes near and far plane from viewMatrix and bounding sphere.
 * viewMatrix and bounding sphere are member variables.
 *
 * @return Pair of float {near, far}.
 */
std::pair<float, float> fsg::NFPlaneAdjustor::computeNearFar()
{
   glm::vec4 center(bs->center, 1.0f);
   glm::vec4 newCenter = *viewMatrix * center;
   float dist = glm::length(newCenter);
   float near = (dist < (bs->radius + this->minimumNear)) ? this->minimumNear : (dist - bs->radius);
   float far = dist + bs->radius;

   return {near, far};
}