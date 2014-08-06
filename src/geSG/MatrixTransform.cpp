#include <geSG/MatrixTransform.h>

using namespace ge::sg;


void MatrixTransform::setMatrix(std::shared_ptr<glm::mat4[]> matrices,unsigned numMatrices)
{
}


void MatrixTransform::setMatrix(glm::mat4 *matrices,unsigned numMatrices,bool deleteOnObjectDestruction)
{
}


void MatrixTransform::setMatrix(std::shared_ptr<float[][16]> matrices,unsigned numMatrices)
{
}


void MatrixTransform::setMatrix(float *matrices[16],unsigned numMatrices,bool deleteOnObjectDestruction)
{
}


void MatrixTransform::setMatrix(const float a1,const float a2,const float a3,const float a4,
                                const float a5,const float a6,const float a7,const float a8,
                                const float a9,const float a10,const float a11,const float a12,
                                const float a13,const float a14,const float a15,const float a16)
{
}
