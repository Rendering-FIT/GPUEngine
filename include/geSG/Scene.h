#pragma once

#include <geSG/Model.h>
#include <vector>
#include <memory>

namespace ge
{
   namespace sg{
      class Animation;

      class Scene
      {
      public:
         //Scene();

         std::vector<std::shared_ptr<Model>> models;
         std::vector<std::shared_ptr<Animation>> animations;
         std::shared_ptr<MatrixTransformNode> rootNode;
      protected:
      };
   }
}