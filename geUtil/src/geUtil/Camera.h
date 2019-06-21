#pragma once

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include <geUtil/ManipulatorInterfaces.h>

namespace ge
{
namespace util
{
   class BasicManipulatorInterface;

   class CameraProjection {
   public:
      virtual ~CameraProjection() {}
      virtual glm::mat4 getProjection() = 0;
   };

   class CameraTransform {
   public:
      virtual ~CameraTransform() {}
      virtual glm::mat4 getView() = 0;
   };

   class CameraMatrixInterface
   {
   public:
      virtual glm::mat4 getProjection() = 0;
      virtual glm::mat4 getView() = 0;
   };

   class BasicCamera: public CameraMatrixInterface, BasicManipulatorInterface
   {
   public:
      std::shared_ptr<glm::mat4>& matrix() override;
      void setMatrix(const std::shared_ptr<glm::mat4>& mat) override;
      void moveZ(float dz) override;
      void moveXY(float dx, float dy) override;
      void rotate(float dx, float dy) override;
      glm::mat4 getProjection() override;
      glm::mat4 getView() override;

      BasicManipulatorInterface& getActiveManipulator();
      void setActiveManipulator(std::unique_ptr<BasicManipulatorInterface> manipulator);
   };
}
}


