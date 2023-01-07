#pragma once
#include "KeyCodes.h"

class Window
{
public:
	Window(int width, int height, const std::string& title);
	~Window();

	virtual bool isKeyPressed(VOEngine::KeyCode key) = 0;
	virtual bool shouldClose() = 0;
	const int& getHeight()               { return m_Height; };
	const int& getWidth()                { return m_Width; };
	const glm::vec2& getSize()           { return m_Size; };
	const int& getYpos()                 { return m_Ypos; };
	const int& getXpos()                 { return m_Xpos; };
	virtual const std::string& getName() { return m_Name; };


	virtual void setIcon(const char* path) = 0;
	virtual void setWindowMode(int wm) = 0;
	virtual void setMaximized(bool value)        { m_Maximized = value; };
	virtual void setDecorated(bool value)        { m_Decorated = value; };
	virtual void setFocused(bool value)          { m_Focused = value; };
	virtual void setAutoIconify(bool value)      { m_AutoIconify = value; }
	virtual void setResizable(bool value)        { m_Resizable = value; };
	virtual void setPosition(glm::vec2 position) { m_Position = position; };
	virtual void setShouldClose(bool value)      { m_ShouldClose = value; };
	virtual void setTitle(const char* title)     { m_Title = title; };
	
	
	virtual void requestAttention() = 0;
	virtual void changeSize(int width, int height) = 0;
	virtual void closeWindow() = 0;
	virtual void pollEvents() = 0;
	virtual void swapBuffers() = 0;

private:
	


protected:
	std::string m_Name;
	bool m_Resizable  = false,
		m_Decorated   = false,
		m_Focused     = false,
		m_AutoIconify = false,
		m_Maximized   = false;
	std::string m_Title = "VOEngine Window";
	const char* m_PathToIcon = "";
	glm::uvec2 m_Size = glm::uvec2(0, 0),
		m_Position = glm::uvec2(0, 0);
	bool m_ShouldClose = false;
	int m_Width = m_Size.x, m_Height = m_Size.y;
	int m_Xpos = m_Position.x, m_Ypos = m_Position.y;



};

