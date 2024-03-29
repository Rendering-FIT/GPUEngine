#include <geSG/MatrixTransformBase.h>

#include <glm/gtc/type_ptr.hpp>
#include <algorithm>

ge::sg::MatrixTransformBase::MatrixTransformBase()
	: _matrix(std::make_shared<glm::mat4>())
{

}

ge::sg::MatrixTransformBase::MatrixTransformBase(const float* matrix)
	: _matrix(std::make_shared<glm::mat4>())
{
	std::copy_n(matrix, 16, glm::value_ptr(*_matrix));
}

/**
 * BEWARE!! Change of ownership.
 */
ge::sg::MatrixTransformBase::MatrixTransformBase(glm::mat4* matrix)
{
	_matrix = std::shared_ptr<glm::mat4>(matrix);
}

ge::sg::MatrixTransformBase::MatrixTransformBase(const glm::mat4& matrix)
	: _matrix(std::make_shared<glm::mat4>(matrix))
{

}

ge::sg::MatrixTransformBase::MatrixTransformBase(const std::shared_ptr<glm::mat4>& matrix)
	: _matrix(matrix)
{

}

ge::sg::MatrixTransformBase::MatrixTransformBase(std::shared_ptr<glm::mat4>&& matrix)
{
	_matrix.swap(matrix);
}

ge::sg::MatrixTransformBase::MatrixTransformBase(ge::sg::MatrixTransformBase& matrix)
	: _matrix(matrix.getRefMatrix())
{

}

ge::sg::MatrixTransformBase::MatrixTransformBase(const ge::sg::Transform& transform)
{
	std::copy_n(transform.getMatrixData(), 16, glm::value_ptr(*_matrix));
}

float* ge::sg::MatrixTransformBase::getMatrixData()
{
	return glm::value_ptr(*_matrix);
}

const float* ge::sg::MatrixTransformBase::getMatrixData() const
{
	return glm::value_ptr(*_matrix);
}

glm::mat4 ge::sg::MatrixTransformBase::getMatrix() const
{
	return *_matrix;
}

std::shared_ptr<glm::mat4>& ge::sg::MatrixTransformBase::getRefMatrix()
{
	return _matrix;
}

ge::sg::MatrixTransformBase::~MatrixTransformBase()
{

}
