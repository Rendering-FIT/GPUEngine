#pragma once
#include <geVu/geVuClasses.h>

class ge::vu::DeviceContextCreateInfo {
public:
	ContextShared context;
	int deviceIndex;
	vk::Instance instance;
	bool validation = true;
	bool verbose = true;
	int queueCount = 1;
};

class ge::vu::DeviceContext {
public:
	DeviceContext(const DeviceContextCreateInfo &o= DeviceContextCreateInfo());

	bool isLayerSupported(std::string name);
	bool isExtensionSupported(std::string name);
private:
	bool validation;
	bool verbose;
	vk::Instance instance;
	vk::PhysicalDevice physicalDevice;
	vk::Device device;
	int universalQueueIndex = -1;
};