#include <geVu/Texture.h>

#include <geVu/DeviceContext.h>
#include <geVu/MemoryManager.h>
#include <geVu/Buffer.h>

#include <geVu/Conversions.h>

using namespace ge::vu;
using namespace std;


Texture::Texture(DeviceContextShared& deviceContext) :
  deviceContext(deviceContext) {
}

Texture::~Texture() {
  auto& dev = deviceContext->getDevice();
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
  deviceContext->info("Texture::create");

  if (extent.width < 1)extent.width = 1;
  if (extent.height < 1)extent.height  = 1;
  if (extent.depth < 1)extent.depth = 1;

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

  memoryBlock = deviceContext->getMemoryManager()->allocMemory(
    image, deviceLocal ? vk::MemoryPropertyFlagBits::eDeviceLocal :
             vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent
  );
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

void Texture::createDepthRenderBuffer(vk::Format format, int width, int height) {
  create(format, vk::ImageType::e2D, vk::Extent3D(width, height, 1), 1, 1,
         vk::ImageUsageFlagBits::eDepthStencilAttachment,
         vk::ImageAspectFlagBits::eDepth, true);
}

void Texture::createColorRenderBuffer(vk::Format format, int width, int height) {
  create(format, vk::ImageType::e2D, vk::Extent3D(width, height, 1), 1, 1,
    vk::ImageUsageFlagBits::eColorAttachment,
    vk::ImageAspectFlagBits::eColor, true);
}

void Texture::createDepthAttachment(vk::Format format, int width, int height) {
  create(format, vk::ImageType::e2D, vk::Extent3D(width, height, 1), 1, 1,
         vk::ImageUsageFlagBits::eDepthStencilAttachment | vk::ImageUsageFlagBits::eSampled,
         vk::ImageAspectFlagBits::eDepth, true);
}

void Texture::createColorAttachment(vk::Format format, int width, int height) {
  create(format, vk::ImageType::e2D, vk::Extent3D(width, height, 1), 1, 1,
    vk::ImageUsageFlagBits::eColorAttachment | vk::ImageUsageFlagBits::eSampled | vk::ImageUsageFlagBits::eStorage,
    vk::ImageAspectFlagBits::eColor, true);
}

void ge::vu::Texture::createColorSampled(vk::Format format, int width, int height, bool mipMap) {
  int mipMapLevels = 1;
  if (mipMap)mipMapLevels = 1 + floor(log2(max(width, height)));
  create(format, vk::ImageType::e2D, vk::Extent3D(width, height, 1), 1, mipMapLevels, vk::ImageUsageFlagBits::eTransferSrc | vk::ImageUsageFlagBits::eTransferDst | vk::ImageUsageFlagBits::eSampled |vk::ImageUsageFlagBits::eStorage, vk::ImageAspectFlagBits::eColor, true);
  //create(format, vk::ImageType::e2D, vk::Extent3D(width, height, 1), 1, 1, vk::ImageUsageFlagBits::eSampled, vk::ImageAspectFlagBits::eColor, false);
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

void ge::vu::Texture::setData(void* data) {
  vk::DeviceSize size = width * height * formatToSize(format);
  deviceContext->info("Texture::setData", size);

  if (memoryBlock.flags & vk::MemoryPropertyFlagBits::eHostVisible) {
    void* ptr = deviceContext->getMemoryManager()->mapMemory(memoryBlock);
    memcpy(ptr, data, size);
    deviceContext->getMemoryManager()->unmapMemory(memoryBlock);
  } else {
    auto cmd = deviceContext->getCommandBuffer();

    setLayout(cmd, vk::ImageLayout::eUndefined, vk::ImageLayout::eTransferDstOptimal, 0, mipLevels);

    BufferShared buffer = make_shared<Buffer>(deviceContext);
    buffer->createStaggingBuffer(size);
    buffer->setSubData(data, size);

    vk::BufferImageCopy copy;
    copy.imageOffset = vk::Offset3D(0, 0, 0);
    copy.bufferImageHeight = 0;
    copy.bufferOffset = 0;
    copy.bufferRowLength = 0;
    copy.imageExtent = vk::Extent3D(width, height, 1);
    copy.imageSubresource = vk::ImageSubresourceLayers(aspect, 0, 0, 1);
    cmd.copyBufferToImage(*buffer, image, vk::ImageLayout::eTransferDstOptimal, {copy});

    if (mipLevels > 1) {
      setLayout(cmd, vk::ImageLayout::eTransferDstOptimal, vk::ImageLayout::eTransferSrcOptimal, 0, 1);

      for (int i = 1; i < mipLevels; i++) {
        vk::ImageBlit ib;
        ib.srcOffsets[0] = vk::Offset3D(0, 0, 0);
        ib.srcOffsets[1] = vk::Offset3D(width >> (i - 1), height >> (i - 1), 1);
        ib.srcSubresource = vk::ImageSubresourceLayers(vk::ImageAspectFlagBits::eColor, i - 1, 0, 1);

        ib.dstOffsets[0] = vk::Offset3D(0, 0, 0);
        ib.dstOffsets[1] = vk::Offset3D(width >> i, height >> i, 1);
        ib.dstSubresource = vk::ImageSubresourceLayers(vk::ImageAspectFlagBits::eColor, i, 0, 1);

        cmd.blitImage(image, vk::ImageLayout::eTransferSrcOptimal, image, vk::ImageLayout::eTransferDstOptimal, {ib}, vk::Filter::eLinear);

        setLayout(cmd, vk::ImageLayout::eTransferDstOptimal, vk::ImageLayout::eTransferSrcOptimal, i);
      }
      setLayout(cmd, vk::ImageLayout::eTransferSrcOptimal, vk::ImageLayout::eShaderReadOnlyOptimal, 0, mipLevels);
    } else {
      setLayout(cmd, vk::ImageLayout::eUndefined, vk::ImageLayout::eShaderReadOnlyOptimal, 0, 1);
    }
    deviceContext->flushCommandBuffer();
  }
}

void ge::vu::Texture::setLayout(vk::CommandBuffer commandBuffer, vk::ImageLayout oldLayout, vk::ImageLayout newLayout, int baseMip, int mipCount, int baseLayer, int layerCount) {
  deviceContext->changeImageLayout(commandBuffer, image, oldLayout, newLayout, aspect, baseMip, mipCount, baseLayer, layerCount);
}

vk::Sampler Texture::getSampler() {
  //@TODO customisable
  vk::SamplerCreateInfo sci;
  sci.addressModeU = vk::SamplerAddressMode::eRepeat;
  sci.addressModeV = vk::SamplerAddressMode::eRepeat;
  sci.addressModeW = vk::SamplerAddressMode::eRepeat;
  sci.anisotropyEnable = true;
  sci.maxAnisotropy = 16;
  sci.minFilter = vk::Filter::eLinear;
  sci.magFilter = vk::Filter::eLinear;
  sci.mipmapMode = vk::SamplerMipmapMode::eLinear;
  sci.mipLodBias = 0;
  sci.compareOp = vk::CompareOp::eNever;
  sci.minLod = 0;
  sci.maxLod = mipLevels;
  sci.borderColor = vk::BorderColor::eFloatOpaqueWhite;
  sci.unnormalizedCoordinates = false;
  return deviceContext->getDevice().createSampler(sci);
}
