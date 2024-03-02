#pragma once

#include <geSG/Export.h>
#include <geSG/Transform.h>
#include <glm/fwd.hpp>
#include <memory>
#include <vector>


namespace ge {
   namespace sg{

      class Mesh;
      class Light;

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
         MatrixTransformBase(glm::mat4 * matrix);
         MatrixTransformBase(const std::shared_ptr<glm::mat4> &matrix);
         MatrixTransformBase(std::shared_ptr<glm::mat4> && matrix);
         MatrixTransformBase(MatrixTransformBase & matrix);
         MatrixTransformBase(const Transform &transform);

         virtual ~MatrixTransformBase();

         virtual float* getMatrixData();
         virtual const float* getMatrixData() const;
         virtual std::shared_ptr<glm::mat4>& getRefMatrix();
         virtual glm::mat4 getMatrix()const;

      protected:
         std::shared_ptr<glm::mat4> _matrix;
      };

      /**
       * Represents local and relative coordinate reference frame for a set of meshes.
       */
      class GESG_EXPORT MatrixTransform : public MatrixTransformBase
      {
      public:
         MatrixTransform();
         MatrixTransform(const float* matrix);
         MatrixTransform(const glm::mat4& matrix);
         MatrixTransform(glm::mat4 * matrix);
         MatrixTransform(const std::shared_ptr<glm::mat4> &matrix);
         MatrixTransform(std::shared_ptr<glm::mat4> && matrix);
         MatrixTransform(MatrixTransform & matrix);
         MatrixTransform(const Transform &transform);

         virtual ~MatrixTransform();

        

         std::vector<std::shared_ptr<Mesh>> meshes;
      };

      /**
       * Represents local and relative coordinate reference frame for a set of lights.
       */
      class GESG_EXPORT LightMatrixTransform : public MatrixTransformBase
      {
      public:
          LightMatrixTransform();
          LightMatrixTransform(const float* matrix);
          LightMatrixTransform(const glm::mat4& matrix);
          LightMatrixTransform(glm::mat4 * matrix);
          LightMatrixTransform(const std::shared_ptr<glm::mat4> &matrix);
          LightMatrixTransform(std::shared_ptr<glm::mat4> && matrix);
          LightMatrixTransform(LightMatrixTransform & matrix);
          LightMatrixTransform(const Transform &transform);

          virtual ~LightMatrixTransform();



          std::vector<std::shared_ptr<Light>> lights;
      };
   } //namespace ge::sg
}
