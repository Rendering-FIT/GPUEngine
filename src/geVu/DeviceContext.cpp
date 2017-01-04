#include <geVu/DeviceContext.h>
#include <iostream>
#include <vector>

using namespace ge::vu;
using namespace std;

DeviceContext::DeviceContext(const DeviceContextCreateInfo & o){
	instance = o.instance;
	validation = o.validation;
	verbose = o.verbose;

	auto devices = instance.enumeratePhysicalDevices();
	int index = o.deviceIndex;
	if (index < 0 || index >= devices.size()) {
		index = 0;
		if (verbose) std::cout << "Device index out of range\n";
	}
	
	physicalDevice = devices[index];


	auto queueProps = physicalDevice.getQueueFamilyProperties();
	for (int i = 0; i < queueProps.size(); i++) {
		auto &q = queueProps[i];
		if (q.queueFlags & (vk::QueueFlagBits::eTransfer | vk::QueueFlagBits::eGraphics | vk::QueueFlagBits::eCompute)) {
			universalQueueIndex = i;
			break;
		}
	}
	assert(universalQueueIndex >= 0 && "Universal queue not found.");

	float priorities[1] = { 1.0 };
	vk::DeviceQueueCreateInfo dqci;
	dqci.queueCount = o.queueCount;
	dqci.queueFamilyIndex = universalQueueIndex;
	dqci.pQueuePriorities = priorities;


	vector<const char*> enabledLayers;
	if (validation && isLayerSupported("VK_LAYER_LUNARG_standard_validation")) {
		enabledLayers.push_back("VK_LAYER_LUNARG_standard_validation");
	}
	
	vector<const char*> enabledExtensions;
	enabledExtensions.push_back("VK_KHR_swapchain");


	vk::DeviceCreateInfo dci;
	dci.queueCreateInfoCount = 1;
	dci.pQueueCreateInfos = &dqci;
	dci.enabledExtensionCount = (unsigned int)enabledExtensions.size();
	dci.ppEnabledExtensionNames = enabledExtensions.data();
	dci.enabledLayerCount = (unsigned int)enabledLayers.size();
	dci.ppEnabledLayerNames = enabledLayers.data();

	device = physicalDevice.createDevice(dci);
}

bool ge::vu::DeviceContext::isLayerSupported(std::string name){
	auto n = physicalDevice.enumerateDeviceLayerProperties();
	for (auto &p : n) {
		if (p.layerName == name)return true;
	}
	return false;
}

bool ge::vu::DeviceContext::isExtensionSupported(std::string name){
	auto n = physicalDevice.enumerateDeviceExtensionProperties();
	for (auto &p : n) {
		if (p.extensionName == name)return true;
	}
	return false;
}
