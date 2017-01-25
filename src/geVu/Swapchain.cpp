#include <geVu/Swapchain.h>

#include <geVu/DeviceContext.h>

using namespace ge::vu;
using namespace std;

Swapchain::Swapchain(DeviceContextShared const& deviceContext) :
  deviceContext(deviceContext) {
  presentSemaphore = deviceContext->getDevice().createSemaphore(vk::SemaphoreCreateInfo());
}

Swapchain::~Swapchain() {
  deviceContext->getDevice().destroySemaphore(presentSemaphore);
}
