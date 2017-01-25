#pragma once

#include <geVu/geVuClasses.h>
#include <gevu/MemoryBlock.h>

class ge::vu::Texture {
protected:
  vk::Image image;
  vk::ImageView imageView;
  vk::Format format;
  //vk::ImageLayout layout;
  vk::ImageAspectFlags aspect;
  vk::ImageType imageType;
  int width;
  int height;
  int depth;
  int mipLevels;
  int layers;
  MemoryBlock memoryBlock;
  DeviceContextShared deviceContext;
public:
  Texture(DeviceContextShared &deviceContext);
  ~Texture();


  void create(vk::Format format, vk::ImageType imageType, vk::Extent3D extent, int layers, int mipLevels, vk::ImageUsageFlags usage, vk::ImageAspectFlags aspect, bool deviceLocal);
  void createDepthRenderBuffer(vk::Format format, int width, int height);
  void createColorRenderBuffer(vk::Format format, int width, int height);

  void createDepthAttachment(vk::Format format, int width, int height);
  void createColorAttachment(vk::Format format, int width, int height);

  void createColorSampled(vk::Format format, int width, int height, bool mipMap = true);
  
  vk::ImageView createImageView(vk::ImageViewType type);
  vk::ImageView createImageView(vk::ImageViewType type, vk::ImageAspectFlags aspect, int mipBase, int mipCount, int layerBase, int layerCount);

  void setData(void* data);

  void setLayout(vk::CommandBuffer commandBuffer, vk::ImageLayout oldLayout, vk::ImageLayout newLayout,
    int baseMip = 0, int mipCount = 1, int baseLayer = 0, int layerCount = 1);

  vk::Sampler getSampler();

  vk::Format getFormat() const { return format; }
  vk::ImageView getImageView() const { return imageView; }
};