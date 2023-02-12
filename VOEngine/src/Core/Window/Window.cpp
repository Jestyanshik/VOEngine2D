#include "vopch.h"
#include "Window.h"


Window::Window(int width, int height, const std::string& title) {
	m_Size = { width, height };
	m_Title = title;
}

Window::~Window() {
	for (auto monitor : m_Monitors) {
		delete monitor;
	}
}