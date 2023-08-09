#include "vopch.h"
#include "GLFWWindow.h"
#include "Core/Common/Events.h"
#include "Core/ResourceManager.h"

void VOEngine::GLFWWindow::detectMonitor() {
	//TODO
}

std::vector<Monitor*> VOEngine::GLFWWindow::getAvailableMonitors()
{
	int count;
	GLFWmonitor** monitors = glfwGetMonitors(&count);
	for (int i = 0; i < count; i++) {
		auto* glfwMonitor = new GLFWMonitor();
		glfwMonitor->name = glfwGetMonitorName(monitors[i]);
		
		int x, y, width, height;
		glfwGetMonitorWorkarea(monitors[i], &x, &y, &width, &height);
		glfwMonitor->size = { width, height };
		float xScale, yScale;
		glfwGetMonitorContentScale(monitors[i], &xScale, &yScale);
		glfwMonitor->contectScale = { xScale, yScale };
		glfwMonitor->monitorHandle = monitors[i];
		m_Monitors.push_back(glfwMonitor);
	}
	return m_Monitors;
}

void VOEngine::GLFWWindow::setWindowMode(int wm){
	m_CurrentState = wm;
	if (m_CurrentState == WindowModes::Fullscreen) {
		glfwSetWindowMonitor(m_Window, m_PrimaryMonitor, 0, 0, m_Mode->width, m_Mode->height, m_Mode->refreshRate);
	}
	if (m_CurrentState == WindowModes::Borderless) {
		glfwSetWindowAttrib(m_Window, GLFW_DECORATED, 0);
		glfwSetWindowMonitor(m_Window, nullptr, 0, 0, m_Mode->width, m_Mode->height, m_Mode->refreshRate);
	}
	if (m_CurrentState == WindowModes::Windowed) {
		glfwSetWindowAttrib(m_Window, GLFW_DECORATED, 1);
		glfwSetWindowMonitor(m_Window, nullptr, m_Position.x, m_Position.y, m_Size.x, m_Size.y, NULL);
	}
	return;
}

bool VOEngine::GLFWWindow::IsKeyPressed(VOEngine::KeyCode key) {
	int state = glfwGetKey(m_Window, key);
	if (state == GLFW_PRESS) {
		return true;
	}
	return false;
}

bool VOEngine::GLFWWindow::ShouldClose() {
	if (glfwWindowShouldClose(m_Window)) {
		return true;
	}
	return false;
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
	//TODO: 
}

void VOEngine::GLFWWindow::setPosition(glm::vec2 position) {
	Window::setPosition(position);
	glfwSetWindowPos(m_Window, (int)position.x, (int)position.y);
}

void VOEngine::GLFWWindow::SetShouldClose(bool value) {
	Window::SetShouldClose(value);
	glfwSetWindowShouldClose(m_Window, value);
}

void VOEngine::GLFWWindow::requestAttention() {
	glfwRequestWindowAttention(m_Window);
}

void VOEngine::GLFWWindow::changeSize(int width, int height) {
	m_Size = { width, height };
	glfwSetWindowSize(m_Window, width, height);
}

void VOEngine::GLFWWindow::updateSize() {
	glfwGetWindowSize(m_Window, (int*)&m_Size.x, (int*)&m_Size.y);
}

void VOEngine::GLFWWindow::updatePos() {
	glfwGetWindowPos(m_Window, (int*)&m_Position.x, (int *) & m_Position.y);
}

void VOEngine::GLFWWindow::setTitle(const char* title) {
	glfwSetWindowTitle(m_Window, title);
}

glm::ivec2& VOEngine::GLFWWindow::getPos() {
	updatePos();
	return m_Position;
}

glm::uvec2& VOEngine::GLFWWindow::getSize() {
	updateSize();
	return m_Size;
}

void VOEngine::GLFWWindow::closeWindow() {
	glfwSetWindowShouldClose(m_Window, GLFW_TRUE);
}

void VOEngine::GLFWWindow::PollEvents() {
	glfwPollEvents();
}

void VOEngine::GLFWWindow::SwapBuffers() {
	glfwSwapBuffers(m_Window);
}

void VOEngine::GLFWWindow::setMonitor(Monitor* monitor) {
	GLFWmonitor* monitorHandle = ((GLFWMonitor*)monitor)->monitorHandle;
	const GLFWvidmode* mode = glfwGetVideoMode(monitorHandle);
	glfwSetWindowMonitor(m_Window, monitorHandle, m_Position.x, m_Position.y, m_Size.x, m_Size.y, mode->refreshRate);
}

void VOEngine::OnResize(GLFWwindow* window, int width, int height) {
	glm::uvec2 size{width, height};
	ResizeEventInfo info{ size };
	ResourceManager::GetInstance().GetEventNotifier()->GenerateEvent(Event{ EventType::Resize, (void*)&info });
}
