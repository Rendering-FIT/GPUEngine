#pragma once

#include <geSG/Export.h>
#include <geSG/Mesh.h>
#include <geSG/Material.h>
#include <ste/DAG.h>
#include <geSG/Node.h>
#include <geSG/MatrixTransform.h>

#include <memory>

namespace geSG
{
   class Mesh;
   class Material;
}

namespace ge{
   namespace sg
   {

      /**
       * Class representing a model inside scene. It is collection
       * of meshes and materials placed in MatrixTransfom hieararchy
       * (DAG).
       */
      class /*GESG_EXPORT*/ Model
      {
      public:

         std::vector<std::shared_ptr<Mesh>> meshes;
         std::vector<std::shared_ptr<Material>> materials;
         std::shared_ptr<MatrixTransformNode> rootNode;
         //~Model();
      protected:

      private:
      };
   }
}
