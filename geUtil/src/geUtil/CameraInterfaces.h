#pragma once
#include <geUtil/Export.h>
#include <glm/mat4x4.hpp>

namespace ge
{
namespace util
{
   class GEUTIL_EXPORT CameraMatrixInterface
   {
   public:
      virtual glm::mat4 getProjectionMatrix() const = 0;
      virtual glm::mat4 getViewMatrix() const = 0;
   };

}
}
