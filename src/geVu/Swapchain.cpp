#include <geVu/Swapchain.h>

#include <geVu/DeviceContext.h>
#include <algorithm>

ge::vu::Swapchain::Swapchain(const SwapchainCreateInfo & o):createInfo(o){

	createSurface();
	createSwapchain();
}

ge::vu::Swapchain::~Swapchain(){
}

void ge::vu::Swapchain::createSurface(){
#ifdef WIN32
	vk::Win32SurfaceCreateInfoKHR wsci;
	wsci.hinstance = createInfo.hinstance;
	wsci.hwnd = createInfo.hwnd;
	surface = deviceContext->getInstance().createWin32SurfaceKHR(wsci);
	auto surfaceFormats = deviceContext->getPhysicalDevice().getSurfaceFormatsKHR(surface);
	surfaceFormat = surfaceFormats[0];
	//@TODO choose format

	assert(deviceContext->getPhysicalDevice().getSurfaceSupportKHR(deviceContext->getUnivesalQueueIndex(), surface));

#else
	//@TODO
	assert("No pinguins" && 0);
#endif
}

void ge::vu::Swapchain::createSwapchain(){
	auto &physicalDevice = deviceContext->getPhysicalDevice();
	auto &device = deviceContext->getDevice();

	auto surfaceCapabilities = physicalDevice.getSurfaceCapabilitiesKHR(surface);
	auto presentModes = physicalDevice.getSurfacePresentModesKHR(surface);



	auto isModePresent = [&](vk::PresentModeKHR mode) {
		return find(presentModes.begin(), presentModes.end(), mode) != presentModes.end();
	};

	vk::PresentModeKHR presentMode = vk::PresentModeKHR::eImmediate;
	
	if (createInfo.vsync) {
		if (isModePresent(vk::PresentModeKHR::eFifo))
			presentMode = vk::PresentModeKHR::eFifo;
		if (isModePresent(vk::PresentModeKHR::eFifoRelaxed))
			presentMode = vk::PresentModeKHR::eFifoRelaxed;
	} else {
		if (isModePresent(vk::PresentModeKHR::eMailbox))
			presentMode = vk::PresentModeKHR::eMailbox;
	}
	
	imageCount = createInfo.imageCount;
	imageCount = (std::min)(imageCount, surfaceCapabilities.maxImageCount);
	imageCount = (std::max)(imageCount, surfaceCapabilities.minImageCount);

	auto transform = surfaceCapabilities.currentTransform;

	vk::SwapchainCreateInfoKHR sci;
	sci.compositeAlpha = vk::CompositeAlphaFlagBitsKHR::eOpaque;
	sci.imageArrayLayers = 1;
	sci.imageColorSpace = surfaceFormat.colorSpace;
	sci.imageExtent = surfaceCapabilities.currentExtent;
	sci.imageFormat = surfaceFormat.format;
	sci.imageSharingMode = vk::SharingMode::eExclusive;
	sci.imageUsage = vk::ImageUsageFlagBits::eColorAttachment;
	sci.minImageCount = imageCount;
	sci.oldSwapchain = swapchain;
	sci.pQueueFamilyIndices = NULL;
	sci.presentMode = presentMode;
	sci.preTransform = transform;
	sci.queueFamilyIndexCount = 0;
	sci.surface = surface;

	swapchain = device.createSwapchainKHR(sci);

	swapchainImages = device.getSwapchainImagesKHR(swapchain);

	width = surfaceCapabilities.currentExtent.width;
	height = surfaceCapabilities.currentExtent.height;

	for (auto &img : swapchainImages) {
		vk::ImageViewCreateInfo ivci;
		ivci.format = surfaceFormat.format;
		ivci.image = img;
		ivci.subresourceRange = vk::ImageSubresourceRange(vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1);
		ivci.viewType = vk::ImageViewType::e2D;
    deviceContext->changeImageLayout(deviceContext->getCommandBuffer(), img, vk::ImageLayout::eUndefined, vk::ImageLayout::ePresentSrcKHR);
		swapchainImageViews.emplace_back(device.createImageView(ivci));
	}
}

void ge::vu::Swapchain::createDepthBuffer(){
}
