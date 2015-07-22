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
       * Class representing a model inside scene. This should be an output
       * of some loader which loads 3D models files
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
