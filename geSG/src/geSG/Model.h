#pragma once

#include <geSG/Mesh.h>
#include <geSG/Material.h>
#include <geSG/Node.h>

#include <memory>


namespace ge{
   namespace sg
   {

      class Mesh;
      class Material;

      /**
       * Class representing a model inside scene. It is collection
       * of meshes and materials placed in MatrixTransfom hieararchy
       * (DAG).
       */
      struct Model
      {
         std::vector<std::shared_ptr<Mesh>> meshes;
         std::vector<std::shared_ptr<Material>> materials;
         std::shared_ptr<MatrixTransformNode> rootNode;
      };
   }
}
