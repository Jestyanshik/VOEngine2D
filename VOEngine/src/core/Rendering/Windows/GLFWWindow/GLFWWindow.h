#pragma once
#include "vopch.h"
#include "../Window.h"
#include "../KeyCodes.h"

struct WindowModes {
	const static int fullscreen = 0;
	const static int borderless = 1;
	const static int windowed = 2;
};


namespace VOEngine {
	class GLFWWindow : public Window {
	private:
		GLFWwindow* m_Window = nullptr;
		GLFWmonitor* m_PrimaryMonitor = nullptr;
		const GLFWvidmode* m_Mode = nullptr;
	protected:


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

			glfwWindowHint(GLFW_RESIZABLE, m_Resizable);
			glfwWindowHint(GLFW_DECORATED, m_Decorated);
			glfwWindowHint(GLFW_FOCUSED, m_Focused);
			glfwWindowHint(GLFW_AUTO_ICONIFY, m_AutoIconify);
			glfwWindowHint(GLFW_MAXIMIZED, m_Maximized);
			m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), NULL, NULL);
			VO_CORE_INFO("GLFWWindow width is {}", m_Width);

			glfwMakeContextCurrent(m_Window);
		}

		bool isKeyPressed(VOEngine::KeyCode key);
		bool shouldClose() override;

		void setMaximized(bool value)        override;
		void setDecorated(bool value)        override;
		void setFocused(bool value)	         override;
		void setAutoIconify(bool value)      override;
		void setResizable(bool value)        override;
		void setIcon(const char* path)       override;
		void setPosition(glm::vec2 position) override;
		void setShouldClose(bool value)      override;
		void setTitle(const char* title)     override;

		GLFWwindow* getNativeWindow() { return m_Window; };
		void requestAttention() override;
		void setWindowMode(int wm) override;
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
