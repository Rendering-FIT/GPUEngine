#pragma once

#include <geSG/Export.h>
#include <geSG/Transform.h>
#include <geSG/MatrixTransformBase.h>
#include <glm/fwd.hpp>
#include <memory>
#include <vector>

namespace ge {
    namespace sg {

        class Mesh;

        /**
         * Represents local and relative coordinate reference frame for a set of meshes.
         */
        class GESG_EXPORT MatrixTransform : public MatrixTransformBase
        {
        public:
            MatrixTransform();
            MatrixTransform(const float* matrix);
            MatrixTransform(const glm::mat4& matrix);
            MatrixTransform(glm::mat4* matrix);
            MatrixTransform(const std::shared_ptr<glm::mat4>& matrix);
            MatrixTransform(std::shared_ptr<glm::mat4>&& matrix);
            MatrixTransform(MatrixTransform& matrix);
            MatrixTransform(const Transform& transform);

            virtual ~MatrixTransform();



            std::vector<std::shared_ptr<Mesh>> meshes;
        };
    }
}