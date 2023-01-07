#include "vopch.h"
#include "Window.h"


Window::Window(int width, int height, const std::string& title) {
	m_Width = width;
	m_Height = height;
	m_Title = title;
}

Window::~Window() {

}