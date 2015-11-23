#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <glm/detail/type_mat.hpp>
#include <geSG/BoundingVolumes.h>
#include <geSG/MatrixTransform.h>
#include <geSG/Node.h>
#include "ste/DAG.h"

namespace ge
{
   namespace util
   {
      class MatrixStack;

      class BVHGenerator
      {
      public:

         typedef ste::Node<std::shared_ptr<ge::sg::BoundingSphere>> BSNode;
         typedef ge::sg::BoundingSphereTemplate<ge::sg::Mesh> MeshBS;

         struct MatrixTransformBoundingSphere
         {
            MatrixTransformBoundingSphere()
               : MTNode(std::make_shared<ge::sg::BoundingSphereTemplate<ge::sg::MatrixTransformNode>>())
            {}

            std::shared_ptr<ge::sg::BoundingSphereTemplate<ge::sg::MatrixTransformNode>> MTNode;
            std::vector<std::shared_ptr<MeshBS>> meshBS;
         };

         typedef ste::Node<std::shared_ptr<MatrixTransformBoundingSphere>> BSMTNode;


         static std::shared_ptr<ge::util::BVHGenerator::BSMTNode> generateBoundingSpheresHierarchy(std::shared_ptr<ge::sg::MatrixTransformNode>& node);

         static void computeBSforCurrentNode(std::shared_ptr<ste::Node<std::shared_ptr<MatrixTransformBoundingSphere>>>& currentNode);
         static std::shared_ptr<ge::util::BVHGenerator::BSMTNode> generateBSforMT(std::shared_ptr<ge::sg::MatrixTransformNode>& MT, ge::util::MatrixStack& matrixStack);
         //static ge::sg::BoundingSphere generateBSforLocalMeshes(std::shared_ptr<ge::sg::MatrixTransformNode>& MT);
         static std::shared_ptr<MeshBS> generateMeshBS(std::shared_ptr<ge::sg::Mesh>& mesh, ge::util::MatrixStack& matrixStack);

         template<typename Type>
         static glm::vec3 computeMeshCenter(std::shared_ptr<Type>& buffer, unsigned length, unsigned numComponents);

         template<typename Type>
         static float computeRadiusFromCenter(std::shared_ptr<Type>& buffer, unsigned length, unsigned numComponents, const glm::vec3& center);

      protected:
         static ge::sg::BoundingSphere mergeBS(std::vector<std::shared_ptr<ge::sg::BoundingSphere>>& spheres);
      };




      template <typename Type>
      glm::vec3 BVHGenerator::computeMeshCenter(std::shared_ptr<Type>& buffer, unsigned length, unsigned numComponents)
      {
         if(length == 0) glm::vec3();

         glm::vec3 center;
         Type *buff = buffer.get();
         for(size_t i = 0; i < length;)
         {
            center.x += buff[i++];
            center.y += buff[i++];
            center.z += buff[i++];

            i += numComponents - 3;
         }

         float numVertices = length / numComponents;
         center /= numVertices;

         return center;
      }

      template <typename Type>
      float BVHGenerator::computeRadiusFromCenter(std::shared_ptr<Type>& buffer, unsigned length, unsigned numComponents, const glm::vec3& center)
      {
         if(length == 0) return 0.0f;

         float distance2 = 0;
         Type *buff = buffer.get();

         for(size_t i = 0; i < length;)
         {
            glm::vec3 p;

            p.x = buff[i++];
            p.y = buff[i++];
            p.z = buff[i++];

            glm::vec3 dif = p - center;
            float newdist2 = glm::dot(dif, dif);
            distance2 = distance2 >= newdist2 ? distance2 : newdist2;

            i += numComponents - 3;
         }

         return sqrt(distance2);
      }
   }
}