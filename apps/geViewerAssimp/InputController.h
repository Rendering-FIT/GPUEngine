#pragma once

#include <memory>

struct GLFWwindow;

namespace fsg
{
   class OrbitObjectManipulator;
}

class InputController
{
public:
   static void GLFW_MB_callback(GLFWwindow* window, int button, int action, int mods);
   static void GLFW_MM_callback(GLFWwindow* window, double xpos, double ypos);
   static void GLFW_MW_callback(GLFWwindow* window, double xoffset, double yoffset);

   static std::shared_ptr<fsg::OrbitObjectManipulator> _cameraManipulator;

protected:
   //mouse movement
   struct MM
   {
      MM()
         : oldX(0)
         , oldY(0)
      {}
      double oldX, oldY;
   };

   static MM _MM;

   struct MB
   {
      MB()
         : cameraMoving(false)
      {}
      bool cameraMoving;
      bool zooming;
   };

   static MB _MB;

};