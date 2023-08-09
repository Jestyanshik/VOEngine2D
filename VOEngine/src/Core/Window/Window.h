#pragma once
#include "Core/Common/KeyCodes.h"

struct Monitor {
	std::string name;
	glm::ivec2 size;
	glm::vec2 contectScale;
};

struct WindowModes {
	const static int Fullscreen = 0;
	const static int Borderless = 1;
	const static int Windowed = 2;
};

class Window
{
public:
	Window(int width, int height, const std::string& title);
	~Window();

	virtual bool IsKeyPressed(VOEngine::KeyCode key) = 0;
	virtual bool ShouldClose() = 0;

	bool isFullscreen() { return m_CurrentState == WindowModes::Fullscreen; };
	bool isBorderless() { return m_CurrentState == WindowModes::Borderless; };
	bool isWindowed()   { return m_CurrentState == WindowModes::Windowed; };
	const int getWidth()                { return getSize().x; };
	const int getHeight()               { return getSize().y; };
	const int getXpos()					{ return getPos().x; };
	const int getYpos()					{ return getPos().y; };
	virtual const std::string& getName() { return m_Name; };

	virtual const glm::ivec2& getPos() = 0;
	virtual const glm::uvec2& getSize() = 0;
	virtual std::vector<Monitor*> getAvailableMonitors() = 0;
	virtual void setIcon(const char* path) = 0;
	virtual void setMonitor(Monitor* monitor) = 0;
	virtual void setWindowMode(int wm) = 0;
	virtual void setMaximized(bool value)		 { m_Maximized = value; m_CurrentState = WindowModes::Fullscreen; };
	virtual void setDecorated(bool value)        { m_Decorated = value; };
	virtual void setFocused(bool value)          { m_Focused = value; };
	virtual void setAutoIconify(bool value)      { m_AutoIconify = value; }
	virtual void setResizable(bool value)        { m_Resizable = value; };
	virtual void setPosition(glm::vec2 position) { m_Position = position; };
	virtual void SetShouldClose(bool value)      { m_ShouldClose = value; };
	virtual void setTitle(const char* title)     { m_Title = title; };

	virtual void requestAttention() = 0;
	virtual void changeSize(int width, int height) = 0;
	virtual void closeWindow() = 0;
	virtual void PollEvents() = 0;
	virtual void SwapBuffers() = 0;
private:
	


protected:
	std::string m_Name;
	bool m_Resizable  = false,
		m_Decorated   = false,
		m_Focused     = false,
		m_AutoIconify = false,
		m_Maximized   = false;
	std::string m_Title = "VOEngine Window";
	glm::uvec2 m_Size = glm::uvec2(0, 0);
	glm::ivec2 m_Position = glm::ivec2(0, 0);
	bool m_ShouldClose = false;
	std::vector<Monitor*> m_Monitors;
	int m_CurrentState = WindowModes::Windowed;
	uint32_t m_Xpos = m_Position.x, m_Ypos = m_Position.y;
};

