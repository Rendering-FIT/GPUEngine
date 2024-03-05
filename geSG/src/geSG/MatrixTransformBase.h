#pragma once

#include <geSG/Export.h>
#include <geSG/Transform.h>
#include <glm/fwd.hpp>
#include <memory>
#include <vector>

namespace ge {
    namespace sg {
        /**
         * Base class for transforms that uses matrix representation.
         * glm::mat4 type is used as matrix.
         */
        class GESG_EXPORT MatrixTransformBase : public Transform
        {
        public:
            MatrixTransformBase();
            MatrixTransformBase(const float* matrix);
            MatrixTransformBase(const glm::mat4& matrix);
            MatrixTransformBase(glm::mat4* matrix);
            MatrixTransformBase(const std::shared_ptr<glm::mat4>& matrix);
            MatrixTransformBase(std::shared_ptr<glm::mat4>&& matrix);
            MatrixTransformBase(MatrixTransformBase& matrix);
            MatrixTransformBase(const Transform& transform);

            virtual ~MatrixTransformBase();

            virtual float* getMatrixData();
            virtual const float* getMatrixData() const;
            virtual std::shared_ptr<glm::mat4>& getRefMatrix();
            virtual glm::mat4 getMatrix()const;

        protected:
            std::shared_ptr<glm::mat4> _matrix;
        };
    }
}