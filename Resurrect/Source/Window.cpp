#include "Resurrect/Window.hpp"

#include <stdexcept>

namespace Resurrect
{
	static std::uintmax_t s_WindowCount = 0;

	Window::Window(const std::string& title, std::pair<int, int> size, std::pair<int, int> position, bool fullscreen)
		: m_Title(title), m_OldSize(size), m_OldPosition(position), m_Fullscreen(fullscreen)
	{
		if (s_WindowCount == 0)
		{
			if (!glfwInit())
				throw std::runtime_error("Failed to initialize Glfw");
		}

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		if (fullscreen)
		{
			GLFWmonitor* monitor = glfwGetPrimaryMonitor();
			const GLFWvidmode* mode = glfwGetVideoMode(monitor);
			m_Window = glfwCreateWindow(mode->width, mode->height, title.c_str(), monitor, nullptr);
		}
		else
		{
			m_Window = glfwCreateWindow(size.first, size.second, title.c_str(), nullptr, nullptr);
			glfwSetWindowPos(m_Window, position.first, position.second);
		}

		glfwSetWindowUserPointer(m_Window, this);

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			static_cast<Window*>(glfwGetWindowUserPointer(window))->OnSize(width, height);
		});

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int left, int top)
		{
			static_cast<Window*>(glfwGetWindowUserPointer(window))->OnPosition(left, top);
		});
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_Window);
		if (s_WindowCount)
			glfwTerminate();

		s_WindowCount--;
	}

	void Window::SetTitle(const std::string& title)
	{
		m_Title = title;
		glfwSetWindowTitle(m_Window, title.c_str());
	}

	void Window::SetSize(std::pair<int, int> size)
	{
		m_OldSize = size;
		glfwSetWindowSize(m_Window, size.first, size.second);
	}

	std::pair<int, int> Window::GetSize() const
	{
		std::pair<int, int> size;
		glfwGetWindowSize(m_Window, &size.first, &size.second);
		return { size.first, size.second };
	}

	void Window::SetPosition(std::pair<int, int> position)
	{
		m_OldPosition = position;
		glfwSetWindowPos(m_Window, position.first, position.second);
	}

	std::pair<int, int> Window::GetPosition() const
	{
		std::pair<int, int> position;
		glfwGetWindowSize(m_Window, &position.first, &position.second);
		return { position.first, position.second };
	}

	void Window::SetFullscreen(bool fullscreen)
	{
		if (fullscreen)
		{
			GLFWmonitor* monitor = glfwGetPrimaryMonitor();
			const GLFWvidmode* mode = glfwGetVideoMode(monitor);
			glfwSetWindowMonitor(m_Window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
		}
		else
		{
			glfwSetWindowMonitor(m_Window, nullptr, m_OldPosition.first, m_OldPosition.second, m_OldSize.first, m_OldSize.first, 0);
		}
	}

	void Window::Close()
	{
		glfwSetWindowShouldClose(m_Window, true);
	}

	bool Window::ShouldClose() const
	{
		while (!glfwWindowShouldClose(m_Window))
		{
			glfwPollEvents();
			return false;
		}

		return true;
	}

	void Window::OnSize(int width, int height)
	{
		if (!m_Fullscreen)
			m_OldSize = { width, height };
	}

	void Window::OnPosition(int left, int top)
	{
		if (!m_Fullscreen)
			m_OldPosition = { left, top };
	}
}