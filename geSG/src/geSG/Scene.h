#pragma once

#include <geSG/Model.h>
#include <geSG/Light.h>
#include <geSG/Camera.h>
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
         std::vector<std::shared_ptr<Model>> models; ///< holds all models of the scene
         std::vector<std::shared_ptr<Animation>> animations; ///holds animations
         std::vector<std::shared_ptr<Light>> lights; ///holds lights
         std::vector<std::shared_ptr<Camera>> cameras; ///holds cameras

         std::shared_ptr<MatrixTransformNode> rootNode; ///< root node of the scene
      };

      /**
       * Example of loading and visualizing model.
       * 
       * \example Simple_QtgeSG/src/main.cpp
       */
   }
}