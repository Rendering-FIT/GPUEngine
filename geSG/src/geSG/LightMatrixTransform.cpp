#include <geSG/LightMatrixTransform.h>

#include <glm/gtc/type_ptr.hpp>
#include <algorithm>

ge::sg::LightMatrixTransform::LightMatrixTransform()
	: MatrixTransformBase()
{
}

ge::sg::LightMatrixTransform::LightMatrixTransform(const float* matrix)
	: MatrixTransformBase(matrix)
{
}

ge::sg::LightMatrixTransform::LightMatrixTransform(const glm::mat4& matrix)
	: MatrixTransformBase(matrix)
{
}

ge::sg::LightMatrixTransform::LightMatrixTransform(glm::mat4* matrix)
	: MatrixTransformBase(matrix)
{
}

ge::sg::LightMatrixTransform::LightMatrixTransform(const std::shared_ptr<glm::mat4>& matrix)
	: MatrixTransformBase(matrix)
{
}

ge::sg::LightMatrixTransform::LightMatrixTransform(std::shared_ptr<glm::mat4>&& matrix)
	: MatrixTransformBase(matrix)
{
}

ge::sg::LightMatrixTransform::LightMatrixTransform(LightMatrixTransform& matrix)
	: MatrixTransformBase(matrix)
{
}

ge::sg::LightMatrixTransform::LightMatrixTransform(const Transform& transform)
	: MatrixTransformBase(transform)
{
}

ge::sg::LightMatrixTransform::~LightMatrixTransform()
{
}
