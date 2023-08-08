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
			glfwSwapInterval(0);
			updatePos();
			updateSize();
		}

		bool isKeyPressed(VOEngine::KeyCode key) override;
		bool shouldClose() override;
		void setMonitor(Monitor* monitor)    override;
		void setMaximized(bool value)        override;
		void setDecorated(bool value)        override;
		void setFocused(bool value)	         override;
		void setAutoIconify(bool value)      override;
		void setResizable(bool value)        override;
		void setIcon(const char* path)       override;
		void setPosition(glm::vec2 position) override;
		void setShouldClose(bool value)      override;
		void setTitle(const char* title)     override;
		void setWindowMode(int wm)			 override;
		glm::ivec2& getPos()				 override;
		glm::uvec2& getSize()				 override;
		std::vector<Monitor*> getAvailableMonitors() override;

		GLFWwindow* getNativeWindow() { return m_Window; };
		void requestAttention() override;
		void changeSize(int width, int height) override;
		void closeWindow() override;
		void pollEvents() override;
		void swapBuffers() override;
	private:
		void updatePos();
		void updateSize();
		void detectMonitor();

	};
}
