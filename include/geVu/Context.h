#pragma once

#include <geVu/geVuClasses.h>

#include <vector>
#include <string>

class ge::vu::ContextCreateInfo {
public:
	bool validation = true;
	bool verbose = false;
	std::string appName = "geVu application";
	int appVersion = 0;
	std::string engineName = "GPUEngine";
	int engineVersion = 0;
};

class ge::vu::Context : public std::enable_shared_from_this<ge::vu::Context> {
public:
	Context(const ContextCreateInfo &o = ContextCreateInfo());
	~Context();

	std::vector<std::string> listDeviceNames();

	DeviceContextShared createDeviceContext(int index = 0);

	static bool isExtensionSupported(std::string name);
	static bool isLayerSupported(std::string name);


	vk::Instance getInstance() { return instance; }
	bool isVerbose() { return verbose; }
	bool isValidation() { return validation; }
private:
	bool verbose;
	bool validation;
	vk::Instance instance;
};