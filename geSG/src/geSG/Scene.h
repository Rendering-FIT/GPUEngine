#pragma once

#include <geSG/Model.h>
#include <vector>
#include <memory>

namespace ge
{
   namespace sg{
      class Animation;

      /**
       * Class holding the information about the scene you want to visualize.
       */
      class Scene
      {
      public:
         //Scene();

         std::vector<std::shared_ptr<Model>> models; ///< holds all models of the scene
         std::vector<std::shared_ptr<Animation>> animations; ///holds animations
         std::shared_ptr<MatrixTransformNode> rootNode; ///< root node of the scene
      protected:
      };

      /**
       * Example of loading and visualizing model.
       * 
       * \example Simple_QtgeSG/src/main.cpp
       */
   }
}