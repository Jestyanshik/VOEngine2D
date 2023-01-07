#include "vopch.h"
#include "GLFWWindow.h"
#include "glad/glad.h"


void VOEngine::GLFWWindow::detectMonitor() {
	//TODO
}

void VOEngine::GLFWWindow::setWindowMode(int wm){
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

bool VOEngine::GLFWWindow::isKeyPressed(VOEngine::KeyCode key) {
	int state = glfwGetKey(m_Window, key);
	if (state == GLFW_PRESS)
	{
		return true;
	}
	else {
		return false;
	}
}

bool VOEngine::GLFWWindow::shouldClose() {
	if (glfwWindowShouldClose(m_Window)) {
		return true;
	}
	else {
		return false;
	}
}

void VOEngine::GLFWWindow::setMaximized(bool value) {
	Window::setMaximized(value);
	glfwSetWindowAttrib(m_Window, GLFW_MAXIMIZED, value);
}

void VOEngine::GLFWWindow::setDecorated(bool value) {
	Window::setDecorated(value);
	glfwSetWindowAttrib(m_Window, GLFW_DECORATED, value);
}

void VOEngine::GLFWWindow::setFocused(bool value) {
	Window::setFocused(value);
	glfwSetWindowAttrib(m_Window, GLFW_FOCUSED, value);
}

void VOEngine::GLFWWindow::setAutoIconify(bool value) {
	Window::setAutoIconify(value);
	glfwSetWindowAttrib(m_Window, GLFW_AUTO_ICONIFY, value);
}

void VOEngine::GLFWWindow::setResizable(bool value) {
	Window::setResizable(value);
	glfwSetWindowAttrib(m_Window, GLFW_RESIZABLE, value);
}

void VOEngine::GLFWWindow::setIcon(const char* path) {
	//TODO
}

void VOEngine::GLFWWindow::setPosition(glm::vec2 position) {
	Window::setPosition(position);
	glfwSetWindowPos(m_Window, position.x, position.y);
}

void VOEngine::GLFWWindow::setShouldClose(bool value) {
	Window::setShouldClose(value);
	glfwSetWindowShouldClose(m_Window, value);
}

void VOEngine::GLFWWindow::requestAttention() {
	glfwRequestWindowAttention(m_Window);
}

void VOEngine::GLFWWindow::changeSize(int width, int height) {
	m_Width = width;
	m_Height = height;
	glfwSetWindowSize(m_Window, width, height);
}

void VOEngine::GLFWWindow::updateSize() {
	glfwGetWindowSize(m_Window, &m_Width, &m_Height);
}

void VOEngine::GLFWWindow::updatePos() {
	glfwGetWindowPos(m_Window, &m_Xpos, &m_Ypos); 
}

void VOEngine::GLFWWindow::setTitle(const char* title) {
	glfwSetWindowTitle(m_Window, title);
}

void VOEngine::GLFWWindow::closeWindow() {
	glfwSetWindowShouldClose(m_Window, GLFW_TRUE);
}

void VOEngine::GLFWWindow::pollEvents() {
	glfwPollEvents();
}

void VOEngine::GLFWWindow::swapBuffers() {

	glfwSwapBuffers(m_Window);
}