#include <geUtil/BasicCamera.h>

using namespace ge::util;

inline void BasicCamera::moveZ(float dz)
{
   activeManipulator->moveZ(dz);
}

inline void BasicCamera::moveXY(float dx, float dy)
{
   activeManipulator->moveXY(dx,dy);
}

inline void BasicCamera::rotate(float dx, float dy)
{
   activeManipulator->rotate(dx,dy);
}

inline glm::mat4 BasicCamera::getProjectionMatrix() const
{
   return *projectionMatrix;
}

inline glm::mat4 BasicCamera::getViewMatrix() const
{
   return activeManipulator->getMatrix();
}

inline BasicManipulatorInterface& BasicCamera::getActiveManipulator()
{
   return *activeManipulator;
}

inline void BasicCamera::setActiveManipulator(std::shared_ptr<BasicManipulatorInterface>& manipulator)
{
   activeManipulator = manipulator;
}