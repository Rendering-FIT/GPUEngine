#include <geSG/MatrixTransform.h>

#include <glm/gtc/type_ptr.hpp>
#include <algorithm>


ge::sg::MatrixTransform::MatrixTransform()
   : _matrix(std::make_shared<glm::mat4>())
{

}

ge::sg::MatrixTransform::MatrixTransform(const float* matrix)
   : _matrix(std::make_shared<glm::mat4>())
{
   std::copy_n(matrix, 16, glm::value_ptr(*_matrix));
}

/**
 * BEWARE!! Change of ownership.
 */
ge::sg::MatrixTransform::MatrixTransform(glm::mat4 * matrix)
{
   _matrix = std::shared_ptr<glm::mat4>(matrix);
}

ge::sg::MatrixTransform::MatrixTransform(const glm::mat4& matrix)
   : _matrix(std::make_shared<glm::mat4>(matrix))
{

}

ge::sg::MatrixTransform::MatrixTransform(const std::shared_ptr<glm::mat4> &matrix)
   : _matrix(matrix)
{

}

ge::sg::MatrixTransform::MatrixTransform(std::shared_ptr<glm::mat4> && matrix)
{
   _matrix.swap(matrix);
}

ge::sg::MatrixTransform::MatrixTransform(ge::sg::MatrixTransform & matrix)
   : _matrix(matrix.getMatrix())
{

}

ge::sg::MatrixTransform::MatrixTransform(const ge::sg::Transform &transform)
{
   std::copy_n(transform.getMatrixData(), 16, glm::value_ptr(*_matrix));
}

float* ge::sg::MatrixTransform::getMatrixData()
{
   return glm::value_ptr(*_matrix);
}

const float* ge::sg::MatrixTransform::getMatrixData() const
{
   return glm::value_ptr(*_matrix);
}

std::shared_ptr<glm::mat4>& ge::sg::MatrixTransform::getMatrix()
{
   return _matrix;
}

ge::sg::MatrixTransform::~MatrixTransform()
{

}
