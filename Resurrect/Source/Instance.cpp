#include "Resurrect/Instance.hpp"

#include <GLFW/glfw3.h>
#include <stdexcept>

namespace Resurrect
{
	Instance::Instance(const std::string& applicationName, std::pair<int, int> applicationVersion)
		: m_ApplicationName(applicationName), m_ApplicationVersion(applicationVersion)
	{
		VkApplicationInfo applicationInfo = {};
		applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		applicationInfo.pApplicationName = applicationName.c_str();
		applicationInfo.applicationVersion = VK_MAKE_API_VERSION(0, applicationVersion.first, applicationVersion.second, 0);
		applicationInfo.pEngineName = "Resurrect";
		applicationInfo.engineVersion = VK_MAKE_API_VERSION(0, 1, 0, 0);
		applicationInfo.apiVersion = VK_API_VERSION_1_0;

		const char** extensionNames = glfwGetRequiredInstanceExtensions(&m_ExtensionCount);

		m_ExtensionNames.reserve(m_ExtensionCount);
		for (std::uint32_t i = 0; i < m_ExtensionCount; i++)
			m_ExtensionNames.emplace_back(extensionNames[i]);

		VkInstanceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &applicationInfo;
		createInfo.enabledExtensionCount = m_ExtensionCount;
		createInfo.ppEnabledExtensionNames = extensionNames;
		createInfo.enabledLayerCount = 0;

		VkResult result = vkCreateInstance(&createInfo, nullptr, &m_Instance);
		if (result != VK_SUCCESS)
			throw std::runtime_error("Failed to create the instance");
	}
	
	Instance::~Instance()
	{
		vkDestroyInstance(m_Instance, nullptr);
	}
}