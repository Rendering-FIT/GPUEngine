#include <geVu/Texture.h>

#include <geVu/DeviceContext.h>
#include <geVu/MemoryManager.h>

using namespace ge::vu;
using namespace std;


ge::vu::Texture::Texture(DeviceContextShared & deviceContext):
  deviceContext(deviceContext)
{
}

void ge::vu::Texture::createDepthBuffer(vk::Format format, int width, int height){

  vk::ImageCreateInfo ici;
  ici.arrayLayers = 1;
  ici.extent = vk::Extent3D(width, height, 1);
  ici.format = format;
  ici.imageType = vk::ImageType::e2D;
  ici.mipLevels = 1;
  ici.usage = vk::ImageUsageFlagBits::eDepthStencilAttachment;
  ici.tiling = vk::ImageTiling::eOptimal;
  ici.initialLayout = vk::ImageLayout::eUndefined;

  image = deviceContext->getDevice().createImage(ici);

  memoryBlock = deviceContext->getMemoryManager()->allocMemory(image, vk::MemoryPropertyFlagBits::eDeviceLocal);
  deviceContext->getDevice().bindImageMemory(image, memoryBlock.memory, memoryBlock.offset);

  vk::ImageViewCreateInfo ivci;
  ivci.format = format;
  ivci.image = image;
  ivci.subresourceRange = vk::ImageSubresourceRange(vk::ImageAspectFlagBits::eDepth, 0, 1, 0, 1);
  ivci.viewType = vk::ImageViewType::e2D;
  imageView = deviceContext->getDevice().createImageView(ivci);

  this->format = format;
  this->aspect = vk::ImageAspectFlagBits::eDepth;
  this->width = width;
  this->height = height;
  this->depth = 1;
  this->layout = vk::ImageLayout::eUndefined;
}

void ge::vu::Texture::setLayout(vk::CommandBuffer commandBuffer, vk::ImageLayout newLayout, int baseMip, int mipCount, int baseLayer, int layerCount){
  deviceContext->changeImageLayout(commandBuffer, image, layout, newLayout, aspect, baseMip, mipCount, baseLayer, layerCount);
  this->layout = newLayout;
}