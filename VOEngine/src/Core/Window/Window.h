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

	bool IsFullscreen() { return m_CurrentState == WindowModes::Fullscreen; };
	bool IsBorderless() { return m_CurrentState == WindowModes::Borderless; };
	bool IsWindowed()   { return m_CurrentState == WindowModes::Windowed; };
	const int GetWidth()                { return GetSize().x; };
	const int GetHeight()               { return GetSize().y; };
	const int GetXpos()					{ return GetPos().x; };
	const int GetYpos()					{ return GetPos().y; };
	virtual const std::string& GetName() { return m_Name; };

	virtual const glm::ivec2& GetPos() = 0;
	virtual const glm::uvec2& GetSize() = 0;
	virtual std::vector<Monitor*> GetAvailableMonitors() = 0;
	virtual void SetIcon(const char* path) = 0;
	virtual void SetMonitor(Monitor* monitor) = 0;
	virtual void SetVSync(bool value) = 0;
	virtual void SetWindowMode(int wm) = 0;
	virtual void SetMaximized(bool value)		 { m_Maximized = value; m_CurrentState = WindowModes::Fullscreen; };
	virtual void SetDecorated(bool value)        { m_Decorated = value; };
	virtual void SetFocused(bool value)          { m_Focused = value; };
	virtual void SetAutoIconify(bool value)      { m_AutoIconify = value; }
	virtual void SetResizable(bool value)        { m_Resizable = value; };
	virtual void SetPosition(glm::vec2 position) { m_Position = position; };
	virtual void SetShouldClose(bool value)      { m_ShouldClose = value; };
	virtual void SetTitle(const char* title)     { m_Title = title; };

	virtual void RequestAttention() = 0;
	virtual void ChangeSize(int width, int height) = 0;
	virtual void CloseWindow() = 0;
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

