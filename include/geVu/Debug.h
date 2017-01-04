#pragma once
#include <geVu/geVuClasses.h>
#include <iostream>

VKAPI_ATTR VkBool32 VKAPI_CALL debugReportCallback(
	VkDebugReportFlagsEXT       flags,
	VkDebugReportObjectTypeEXT  objectType,
	uint64_t                    object,
	size_t                      location,
	int32_t                     messageCode,
	const char*                 pLayerPrefix,
	const char*                 pMessage,
	void*                       pUserData)
{
	vk::DebugReportFlagBitsEXT f = (vk::DebugReportFlagBitsEXT)flags;
	if (f == vk::DebugReportFlagBitsEXT::eError) {
		std::cout << "\n***ERROR***\n";
	}
	std::cout << vk::to_string((vk::DebugReportFlagBitsEXT)flags) << ":" << pMessage << std::endl << std::endl;
	return VK_FALSE;
}

PFN_vkCreateDebugReportCallbackEXT vkCreateDebugReportCallback;
VKAPI_ATTR VkResult VKAPI_CALL vkCreateDebugReportCallbackEXT(
	VkInstance                                  instance,
	const VkDebugReportCallbackCreateInfoEXT*   pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkDebugReportCallbackEXT*                   pCallback) {
	return vkCreateDebugReportCallback(instance, pCreateInfo, pAllocator, pCallback);
}

void debugInitFunctions(vk::Instance i) {
	vkCreateDebugReportCallback = reinterpret_cast<PFN_vkCreateDebugReportCallbackEXT>(i.getProcAddr("vkCreateDebugReportCallbackEXT"));
}

void enableDebugCallbacks(vk::Instance i) {
	debugInitFunctions(i);
	auto drcci = vk::DebugReportCallbackCreateInfoEXT(
		//vk::DebugReportFlagBitsEXT::eDebug |
		vk::DebugReportFlagBitsEXT::eError |
		//vk::DebugReportFlagBitsEXT::eInformation |
		vk::DebugReportFlagBitsEXT::ePerformanceWarning |
		vk::DebugReportFlagBitsEXT::eWarning,
		&debugReportCallback, 0);
	i.createDebugReportCallbackEXT(drcci);
}