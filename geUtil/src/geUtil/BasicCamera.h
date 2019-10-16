#pragma once

#include <geUtil/ManipulatorInterfaces.h>
#include <geUtil/CameraInterfaces.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace ge
{
namespace util
{
   class BasicManipulatorInterface;

   class GEUTIL_EXPORT BasicCamera: public CameraMatrixInterface, BasicManipulatorInterface
   {
   public:
      std::shared_ptr<glm::mat4>& getRefMatrix() override;
      void setMatrix(const std::shared_ptr<glm::mat4>& mat) override;
      void moveZ(float dz) override;
      void moveXY(float dx, float dy) override;
      void rotate(float dx, float dy) override;
      glm::mat4 getProjectionMatrix() const override;
      glm::mat4 getViewMatrix() const override;

      BasicManipulatorInterface& getActiveManipulator();
      void setActiveManipulator(std::shared_ptr<BasicManipulatorInterface>& manipulator);

   protected:
      std::shared_ptr<glm::mat4> viewMatrix;
      std::shared_ptr<glm::mat4> projectionMatrix;
      std::shared_ptr<BasicManipulatorInterface> activeManipulator;
   };

   
}
}


