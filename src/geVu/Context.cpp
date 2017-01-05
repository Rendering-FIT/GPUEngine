#include <geVu/Context.h>
#include <geVu/Debug.h>
#include <geVu/DeviceContext.h>

using namespace ge::vu;
using namespace std;

Context::Context(const ContextCreateInfo & o){
	this->validation = o.validation;
	this->verbose = o.verbose;

	vector<const char*> enabledExtensions;
	vector<const char*> enabledLayers;

	enabledExtensions.push_back("VK_KHR_surface");
#ifdef WIN32
	enabledExtensions.push_back("VK_KHR_win32_surface");
#endif
	//@todo linux

	if (validation) {
		if (isLayerSupported("VK_LAYER_LUNARG_standard_validation")) {
			enabledLayers.push_back("VK_LAYER_LUNARG_standard_validation");
		}
		if (isExtensionSupported("VK_EXT_debug_report")) {
			enabledExtensions.push_back("VK_EXT_debug_report");
		}
	}
	
	vk::ApplicationInfo ai;
	ai.apiVersion = 0;
	ai.applicationVersion = o.appVersion;
	ai.engineVersion = o.engineVersion;
	ai.pApplicationName = o.appName.c_str();
	ai.pEngineName = o.engineName.c_str();

	vk::InstanceCreateInfo ici;
	ici.enabledExtensionCount = enabledExtensions.size();
	ici.ppEnabledExtensionNames = enabledExtensions.data();
	ici.enabledLayerCount = enabledLayers.size();
	ici.ppEnabledLayerNames = enabledLayers.data();
	ici.pApplicationInfo = &ai;

	instance = vk::createInstance(ici);

	if (validation) {
		enableDebugCallbacks(instance);
	}
}

Context::~Context() {
	instance.destroy();
}

std::vector<string> Context::listDeviceNames(){
	auto devices = instance.enumeratePhysicalDevices();
	std::vector<string> names;
	for (auto &dev : devices) {
		auto prop = dev.getProperties();
		names.push_back(prop.deviceName);
	}
	return names;
}

DeviceContextShared Context::createDeviceContext(int index){
	DeviceContextCreateInfo dcci;
	dcci.context = shared_from_this();
	dcci.deviceIndex = index;
	dcci.validation = validation;
	dcci.verbose = true;

	return std::make_shared<DeviceContext>(dcci);
}

bool Context::isExtensionSupported(std::string name){
	auto n = vk::enumerateInstanceExtensionProperties();
	for (auto &p : n) {
		if (p.extensionName == name)return true;
	}
	return false;
}

bool Context::isLayerSupported(std::string name){
	auto n = vk::enumerateInstanceLayerProperties();
	for (auto &p : n) {
		if (p.layerName == name)return true;
	}
	return false;
}
