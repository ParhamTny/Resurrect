#pragma once

#include <vulkan/vulkan.h>
#include <string>
#include <vector>

namespace Resurrect
{
	class Instance
	{
	public:
		Instance(const std::string& applicationName, std::pair<int, int> applicationVersion);
		~Instance();
	
		const std::string& GetApplicationName() const { return m_ApplicationName; }
		std::pair<int, int> GetApplicationVersion() const { return m_ApplicationVersion; }

		std::uint32_t GetExtensionCount() const { return m_ExtensionCount; }
		const std::vector<std::string>& GetExtensionNames() const { return m_ExtensionNames; }
	private:
		VkInstance m_Instance;

		std::string m_ApplicationName;
		std::pair<int, int> m_ApplicationVersion;
		std::uint32_t m_ExtensionCount;
		std::vector<std::string> m_ExtensionNames;
	};
}