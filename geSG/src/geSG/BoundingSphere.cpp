#include <geSG/BoundingSphere.h>

#include <algorithm>

using namespace ge::sg;

BoundingSphere::BoundingSphere(const BoundingSphere& other): center(other.center)
                                                             , radius(other.radius)
{
}

void BoundingSphere::transform(const glm::mat4& mat)
{
   glm::vec4 pos(this->center, 1.0f);
   pos = mat * pos;
   glm::vec4 x(1, 0, 0, 0), y(0, 1, 0, 0), z(0, 0, 1, 0);
   x = mat * x;
   y = mat * y;
   z = mat * z;
   float maxScale = 0.0f;
   float lx = glm::length(x);
   float ly = glm::length(y);
   float lz = glm::length(z);
   maxScale = std::max(lx, ly);
   maxScale = std::max(maxScale, lz);
   this->center = glm::vec3(pos);
   this->radius *= maxScale;
}
