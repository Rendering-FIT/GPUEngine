#pragma once

#include <geUtil/ManipulatorInterfaces.h>
#include <geUtil/CameraInterfaces.h>

#include <memory>

namespace ge
{
namespace util
{
   class BasicManipulatorInterface;

   class GEUTIL_EXPORT BasicCamera: public CameraMatrixInterface, public BasicManipulatorInterface
   {
   public:
      void moveZ(float dz) override;
      void moveXY(float dx, float dy) override;
      void rotate(float dx, float dy) override;
      glm::mat4 getProjectionMatrix() const override;
      glm::mat4 getViewMatrix() const override;

      BasicManipulatorInterface& getActiveManipulator();
      void setActiveManipulator(std::shared_ptr<BasicManipulatorInterface>& manipulator);

   protected:
      std::shared_ptr<glm::mat4> projectionMatrix = std::make_shared<glm::mat4>(1.f);
      std::shared_ptr<BasicManipulatorInterface> activeManipulator;
   };

   
}
}


