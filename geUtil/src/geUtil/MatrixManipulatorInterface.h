#pragma once
#include <geUtil/Export.h>
#include <glm/glm.hpp>
#include <memory>

namespace ge
{
namespace util
{
   class GEUTIL_EXPORT MatrixManipulatorInterface
   {
   public:

      inline const glm::mat4& mat() const;

      virtual std::shared_ptr<glm::mat4>& matrix() = 0;
      virtual void setMatrix(const std::shared_ptr<glm::mat4>& mat) = 0;

      virtual ~MatrixManipulatorInterface() {}

   };

}
}