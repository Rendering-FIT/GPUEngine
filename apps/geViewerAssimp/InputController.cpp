#include "InputController.h"

#include <GLFW/glfw3.h>
#include "CameraManipulator.h"

InputController::MM InputController::_MM;
InputController::MB InputController::_MB;
std::shared_ptr<fsg::OrbitObjectManipulator> InputController::_cameraManipulator;

void InputController::GLFW_MB_callback(GLFWwindow* window, int button, int action, int /*mods*/)
{
   switch(button)
   {
      case GLFW_MOUSE_BUTTON_1: 
         if(action == GLFW_PRESS)
         {
            _MB.cameraMoving = true;
            glfwGetCursorPos(window, &_MM.oldX, &_MM.oldY);
         }
         if(action == GLFW_RELEASE)
            _MB.cameraMoving = false;
         break;
      case GLFW_MOUSE_BUTTON_2:
         if(action == GLFW_PRESS)
         {
            _MB.zooming = true;
            glfwGetCursorPos(window, &_MM.oldX, &_MM.oldY);
         }
         if(action == GLFW_RELEASE)
            _MB.zooming = false;
         break;
      default:
         break;
   }
}

/**
 * Mose Movement callback.
 */
void InputController::GLFW_MM_callback(GLFWwindow* window, double xpos, double ypos)
{
   if (_MB.cameraMoving)
   {
      //send input to camera control
      int width, height;
      glfwGetWindowSize(window, &width, &height);
      float dx = (xpos - _MM.oldX) / width;
      float dy = (ypos - _MM.oldY) / height;
      _MM.oldX = xpos;
      _MM.oldY = ypos;
      _cameraManipulator->rotate(dx, dy);
      _cameraManipulator->updateViewMatrix();

   }
   else if(_MB.zooming)
   {
      int width, height;
      glfwGetWindowSize(window, &width, &height);
      float dx = (xpos - _MM.oldX) / width;
      float dy = (ypos - _MM.oldY) / height;
      _MM.oldX = xpos;
      _MM.oldY = ypos;
      _cameraManipulator->move(-dx,dy);
      _cameraManipulator->updateViewMatrix();
   }
}

void InputController::GLFW_MW_callback(GLFWwindow* /*window*/, double /*xoffset*/, double yoffset)
{
   //offset is either + or - 1
   _cameraManipulator->zoom(0.5 * (-yoffset));
   _cameraManipulator->updateViewMatrix();
}
