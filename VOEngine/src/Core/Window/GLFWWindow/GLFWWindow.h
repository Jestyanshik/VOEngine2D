#pragma once
#include "vopch.h"
#include "../Window.h"
#include "Core/Common/KeyCodes.h"
struct GLFWMonitor : Monitor {
	GLFWmonitor* monitorHandle{};
};

namespace VOEngine {
	void OnResize(GLFWwindow* window, int width, int height);
	class GLFWWindow : public Window {
	private:
		GLFWwindow* m_Window = nullptr;
		GLFWmonitor* m_PrimaryMonitor = nullptr;
		const GLFWvidmode* m_Mode = nullptr;
		int m_SwapInterval = 1;
	public:
		GLFWWindow(int width, int height, const std::string& title) : Window(width, height, title) {
			if (!glfwInit()) {
				VO_CORE_ERROR("GLFW couldn't initialize");
			};
			m_PrimaryMonitor = glfwGetPrimaryMonitor();
			m_Mode = glfwGetVideoMode(m_PrimaryMonitor);
			m_Name = "GLFW Window";

			VO_CORE_INFO("GLFW version used {}.{}.{}\n",
				GLFW_VERSION_MAJOR,
				GLFW_VERSION_MINOR,
				GLFW_VERSION_REVISION);

			glfwSetErrorCallback([](int code, const char* description) {
				VO_CORE_ERROR("Error code: {} \n Description:\n {}", code, description);
			});
			glfwWindowHint(GLFW_RESIZABLE, true);
			glfwWindowHint(GLFW_DECORATED, m_Decorated);
			glfwWindowHint(GLFW_FOCUSED, m_Focused);
			glfwWindowHint(GLFW_AUTO_ICONIFY, m_AutoIconify);
			glfwWindowHint(GLFW_MAXIMIZED, m_Maximized);
			m_Window = glfwCreateWindow(m_Size.x, m_Size.y, m_Title.c_str(), NULL, NULL);
			glfwSetWindowIcon(m_Window, 0, NULL);
			glfwMakeContextCurrent(m_Window);
			glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {OnResize(window, width, height);});
			glfwSwapInterval(m_SwapInterval);
			UpdatePos();
			UpdateSize();
		}

		bool IsKeyPressed(VOEngine::KeyCode key) override;
		bool ShouldClose() override;
		void SetMonitor(Monitor* monitor)    override;
		void SetMaximized(bool value)        override;
		void SetDecorated(bool value)        override;
		void SetFocused(bool value)	         override;
		void SetAutoIconify(bool value)      override;
		void SetResizable(bool value)        override;
		void SetIcon(const char* path)       override;
		void SetPosition(glm::vec2 position) override;
		void SetShouldClose(bool value)      override;
		void SetTitle(const char* title)     override;
		void SetWindowMode(int wm)			 override;
		glm::ivec2& GetPos()				 override;
		glm::uvec2& GetSize()				 override;
		std::vector<Monitor*> GetAvailableMonitors() override;

		GLFWwindow* GetNativeWindow() { return m_Window; };
		void RequestAttention() override;
		void ChangeSize(int width, int height) override;
		void CloseWindow() override;
		void PollEvents() override;
		void SwapBuffers() override;
		void SetVSync(bool value) override;

	private:
		void UpdatePos();
		void UpdateSize();
		void detectMonitor();

	};
}
