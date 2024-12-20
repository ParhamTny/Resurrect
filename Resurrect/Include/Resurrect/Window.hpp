#pragma once

#include <GLFW/glfw3.h>
#include <string>
#include <utility>

namespace Resurrect
{
	class Window
	{
	public:
		Window(const std::string& title, std::pair<int, int> size, std::pair<int, int> position, bool fullscreen = false);
		~Window();

		void SetTitle(const std::string& title);
		const std::string& GetTitle() const { return m_Title; }

		void SetSize(std::pair<int, int> size);
		std::pair<int, int> GetSize() const;

		void SetPosition(std::pair<int, int> position);
		std::pair<int, int> GetPosition() const;

		void SetFullscreen(bool fullscreen);
		bool IsFullscreen() const { return m_Fullscreen; }
	
		void Close();
		bool ShouldClose() const;
	private:
		void OnSize(int width, int height);
		void OnPosition(int left, int top);
	private:
		GLFWwindow* m_Window;

		std::string m_Title;
		std::pair<int, int> m_OldSize, m_OldPosition;
		bool m_Fullscreen;
	};
}