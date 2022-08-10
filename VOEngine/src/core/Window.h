#pragma once
#include "vopch.h"
#include "GLFW/glfw3.h"
#include "KeyCodes.h"

struct WindowModes {
	const static int fullscreen = 0;
	const static int borderless = 1;
	const static int windowed = 2;
};


namespace VOEngine {
	class Window {
	private:
		GLFWwindow* m_Window = nullptr;
		GLFWmonitor* m_PrimaryMonitor = nullptr;
		const GLFWvidmode* m_Mode = nullptr;
		bool m_Resizable, m_Decorated, m_Focused, m_AutoIconify, m_Maximized = false;
		int m_Width, m_Height;
		int m_Xpos, m_Ypos;
		int m_FramebufferW, m_FramebufferH;
		const char* m_Title;
		const char* m_PathToIcon;
	public:
		Window(int width, int height,const std::string& title,bool resizalbe = true,
			bool decorated = true, bool focused = true, bool autoIconify = false,
			bool maximized = false, const std::string& pathToIcon = "") {
			if (!glfwInit()) {
				VO_CORE_ERROR("GLFW couldn't initialize");
			};
			m_Resizable = resizalbe;
			m_Decorated = decorated;
			m_Focused = focused;
			m_AutoIconify = autoIconify;
			m_Maximized = maximized;
			m_Width = width;
			m_Height = height;
			m_Title = title.c_str();
			m_PathToIcon = pathToIcon.c_str();
			m_PrimaryMonitor = glfwGetPrimaryMonitor();
			m_Mode = glfwGetVideoMode(m_PrimaryMonitor);

			VO_CORE_INFO("GLFW version used {}.{}.{}\n",
						GLFW_VERSION_MAJOR,
						GLFW_VERSION_MINOR,
						GLFW_VERSION_REVISION);

			glfwSetErrorCallback([](int code, const char* description) {
				VO_CORE_ERROR("Error code: {} \n Description:\n {}", code, description);
			});
			createWindow();
			

		}
		~Window() {
			glfwDestroyWindow(m_Window);
		}
		bool isKeyPressed(VOEngine::KeyCode key);
		bool shouldClose();
		GLFWwindow* getGLFWwindow();
		int getHeight();
		int getWidth();

		int getYpos();
		int getXpos();

		void setIcon(const char* path);
		void requestAttention();
		void setWindowMode(int wm);
		void changeSize(int width, int height);
		void changeTitle(const char* title);
		void closeWindow();
		void pollEvents();
		void swapBuffers();
		int& getFramebufferWidth() {
			return m_FramebufferW;
		};
		int& getFramebufferHeight() {
			return m_FramebufferH;
		};
	private:
		void updatePos();
		void updateSize();
		void detectMonitor();
		void createWindow();
	};
	
}
