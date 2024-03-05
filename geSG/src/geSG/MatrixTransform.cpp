#include <geSG/MatrixTransform.h>

#include <glm/gtc/type_ptr.hpp>
#include <algorithm>

ge::sg::MatrixTransform::MatrixTransform()
   : MatrixTransformBase()
{
}

ge::sg::MatrixTransform::MatrixTransform(const float* matrix)
   : MatrixTransformBase(matrix)
{
}

ge::sg::MatrixTransform::MatrixTransform(const glm::mat4& matrix)
   : MatrixTransformBase(matrix)
{
}

ge::sg::MatrixTransform::MatrixTransform(glm::mat4* matrix)
   : MatrixTransformBase(matrix)
{
}

ge::sg::MatrixTransform::MatrixTransform(const std::shared_ptr<glm::mat4>& matrix)
   : MatrixTransformBase(matrix)
{
}

ge::sg::MatrixTransform::MatrixTransform(std::shared_ptr<glm::mat4>&& matrix)
   : MatrixTransformBase(matrix)
{
}

ge::sg::MatrixTransform::MatrixTransform(MatrixTransform& matrix)
   : MatrixTransformBase(matrix)
{
}

ge::sg::MatrixTransform::MatrixTransform(const Transform& transform)
   : MatrixTransformBase(transform)
{
}

ge::sg::MatrixTransform::~MatrixTransform()
{
}
