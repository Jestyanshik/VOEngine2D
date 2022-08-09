#include "vopch.h"
#include "Window.h"
#include "ImGuiManager.h"
#include "glad/glad.h"

void VOEngine::Window::detectMonitor() {
	//TODO
}

void VOEngine::Window::createWindow() {
	glfwWindowHint(GLFW_RESIZABLE, m_Resizable);
	glfwWindowHint(GLFW_DECORATED, m_Decorated);
	glfwWindowHint(GLFW_FOCUSED, m_Focused);
	glfwWindowHint(GLFW_AUTO_ICONIFY, m_AutoIconify);
	glfwWindowHint(GLFW_MAXIMIZED, m_Maximized);
	m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
	glfwMakeContextCurrent(m_Window);
	glfwSwapInterval(1);


}

void VOEngine::Window::setWindowMode(int wm){
	if (wm == WindowModes::fullscreen) {
		glfwSetWindowMonitor(m_Window, m_PrimaryMonitor, 0, 0, m_Mode->width, m_Mode->height, m_Mode->refreshRate);
		//changeSize(m_Mode->width, m_Mode->height);
	}
	if (wm == WindowModes::borderless) {
		glfwSetWindowAttrib(m_Window, GLFW_DECORATED, 0);
		glfwSetWindowMonitor(m_Window, NULL, 0, 0, m_Mode->width, m_Mode->height, m_Mode->refreshRate);
	}
	if (wm == WindowModes::windowed) {
		glfwSetWindowAttrib(m_Window, GLFW_DECORATED, 1);
		glfwSetWindowMonitor(m_Window, NULL, (m_Mode->width - m_Width)/2 ,(m_Mode->height - m_Height)/2, m_Width, m_Height, NULL);

	}
}

bool VOEngine::Window::isKeyPressed(VOEngine::KeyCode key) {
	int state = glfwGetKey(m_Window, key);
	if (state == GLFW_PRESS)
	{
		return true;
	}
	else {
		return false;
	}
}

bool VOEngine::Window::shouldClose() {
	if (glfwWindowShouldClose(m_Window)) {
		return true;
	}
	else {
		return false;
	}
}

GLFWwindow* VOEngine::Window::getGLFWwindow() {
	return m_Window;
}

void VOEngine::Window::setIcon(const char* path) {
	//TODO
}

void VOEngine::Window::requestAttention() {
	glfwRequestWindowAttention(m_Window);
}

void VOEngine::Window::changeSize(int width, int height) {
	m_Width = width;
	m_Height = height;
	glfwSetWindowSize(m_Window, width, height);
}

void VOEngine::Window::changeTitle(const char* title) {
	glfwSetWindowTitle(m_Window, title);
}

void VOEngine::Window::closeWindow() {
	glfwSetWindowShouldClose(m_Window, GLFW_TRUE);
}

void VOEngine::Window::pollEvents() {
	glfwPollEvents();
}

void VOEngine::Window::swapBuffers() {

	glfwSwapBuffers(m_Window);
}