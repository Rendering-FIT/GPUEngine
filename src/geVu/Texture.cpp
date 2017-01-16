#include <geVu/Texture.h>

#include <geVu/DeviceContext.h>
#include <geVu/MemoryManager.h>

using namespace ge::vu;
using namespace std;


Texture::Texture(DeviceContextShared & deviceContext) :
  deviceContext(deviceContext) {
}

Texture::~Texture() {
  auto &dev = deviceContext->getDevice();
  if (image) {
    dev.destroyImage(image);
  }
  if (imageView) {
    dev.destroyImageView(imageView);
  }
  deviceContext->getMemoryManager()->freeMemory(memoryBlock);
}


void ge::vu::Texture::create(
  vk::Format format, vk::ImageType imageType,
  vk::Extent3D extent, int layers, int mipLevels,
  vk::ImageUsageFlags usage, vk::ImageAspectFlags aspect, bool deviceLocal) {

  vk::ImageTiling imageTiling = deviceLocal ? vk::ImageTiling::eOptimal : vk::ImageTiling::eLinear;
  vk::ImageLayout layout = deviceLocal ? vk::ImageLayout::eUndefined : vk::ImageLayout::ePreinitialized;

  vk::ImageCreateInfo ici;
  ici.arrayLayers = layers;
  ici.extent = extent;
  ici.format = format;
  ici.imageType = imageType;
  ici.mipLevels = mipLevels;
  ici.usage = usage;
  ici.tiling = imageTiling;
  ici.initialLayout = layout;

  image = deviceContext->getDevice().createImage(ici);

  memoryBlock = deviceContext->getMemoryManager()->allocMemory(image, vk::MemoryPropertyFlagBits::eDeviceLocal);
  deviceContext->getDevice().bindImageMemory(image, memoryBlock.memory, memoryBlock.offset);

  vk::ImageViewType imageViewType;
  if (imageType == vk::ImageType::e1D)imageViewType = vk::ImageViewType::e1D;
  if (imageType == vk::ImageType::e2D)imageViewType = vk::ImageViewType::e2D;
  if (imageType == vk::ImageType::e3D)imageViewType = vk::ImageViewType::e3D;

  this->imageType = imageType;
  this->layers = layers;
  this->mipLevels = mipLevels;
  this->format = format;
  this->aspect = aspect;
  this->width = extent.width;
  this->height = extent.height;
  this->depth = extent.depth;

  imageView = createImageView(imageViewType);
}

void Texture::createDepthBuffer(vk::Format format, int width, int height) {
  if (width < 1)width = 1;
  if (height < 1)height = 1;
  create(format, vk::ImageType::e2D, vk::Extent3D(width, height, 1), 1, 1, vk::ImageUsageFlagBits::eDepthStencilAttachment, vk::ImageAspectFlagBits::eDepth, true);
}

vk::ImageView ge::vu::Texture::createImageView(vk::ImageViewType type) {
  return createImageView(type, aspect, 0, mipLevels, 0, layers);
}

vk::ImageView ge::vu::Texture::createImageView(vk::ImageViewType type, vk::ImageAspectFlags aspect, int mipBase, int mipCount, int layerBase, int layerCount) {
  vk::ImageViewCreateInfo ivci;
  ivci.format = format;
  ivci.image = image;
  ivci.subresourceRange = vk::ImageSubresourceRange(aspect, mipBase, mipCount, layerBase, layerCount);
  ivci.viewType = type;
  return deviceContext->getDevice().createImageView(ivci);
}

void ge::vu::Texture::setLayout(vk::CommandBuffer commandBuffer, vk::ImageLayout oldLayout, vk::ImageLayout newLayout, int baseMip, int mipCount, int baseLayer, int layerCount) {
  deviceContext->changeImageLayout(commandBuffer, image, oldLayout, newLayout, aspect, baseMip, mipCount, baseLayer, layerCount);
}