#pragma once

#include <geVu/geVuClasses.h>
#include <gevu/MemoryBlock.h>

class ge::vu::Texture {
protected:
  vk::Image image;
  vk::ImageView imageView;
  vk::Format format;
  vk::ImageLayout layout;
  vk::ImageAspectFlags aspect;
  int width;
  int height;
  int depth;
  MemoryBlock memoryBlock;
  DeviceContextShared deviceContext;
public:
  Texture(DeviceContextShared &deviceContext);

  void createDepthBuffer(vk::Format format, int width, int height);

  void setLayout(vk::CommandBuffer commandBuffer, vk::ImageLayout newLayout,
    int baseMip = 0, int mipCount = 1, int baseLayer = 0, int layerCount = 1);


  vk::Format getFormat() { return format; }
  vk::ImageView getImageView() { return imageView; }
};