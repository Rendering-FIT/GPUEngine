#pragma once

#include <geSG/Export.h>
#include <geSG/Transform.h>
#include <geSG/MatrixTransformBase.h>
#include <glm/fwd.hpp>
#include <memory>
#include <vector>

namespace ge {
    namespace sg {

        class Light;

        /**
         * Represents local and relative coordinate reference frame for a set of lights.
         */
        class GESG_EXPORT LightMatrixTransform : public MatrixTransformBase
        {
        public:
            LightMatrixTransform();
            LightMatrixTransform(const float* matrix);
            LightMatrixTransform(const glm::mat4& matrix);
            LightMatrixTransform(glm::mat4* matrix);
            LightMatrixTransform(const std::shared_ptr<glm::mat4>& matrix);
            LightMatrixTransform(std::shared_ptr<glm::mat4>&& matrix);
            LightMatrixTransform(LightMatrixTransform& matrix);
            LightMatrixTransform(const Transform& transform);

            virtual ~LightMatrixTransform();



            std::vector<std::shared_ptr<Light>> lights;
        };
    }
}