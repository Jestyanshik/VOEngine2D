#pragma once
#include "vopch.h"

class BaseShape {
public:
	BaseShape(int width, int height, glm::vec3 color, glm::vec3 position) :
		m_Width{ width }, m_Height{ height }, m_Color{ color }, m_Position{ position } {}

	BaseShape(int width, int height, float r, float g, float b, glm::vec3 position) :
		m_Width{ width }, m_Height{ height }, m_Position{ position }
	{
		m_Color.x = r;
		m_Color.y = g;
		m_Color.z = b;
	}

	BaseShape(int width, int height, glm::vec3 color, float x, float y, float z) :
		m_Width{ width }, m_Height{ height }, m_Color{ color }
	{

		m_Position.x = x;
		m_Position.y = y;
		m_Position.z = z;
	}
	BaseShape(int width, int height, float r, float g, float b, float x, float y, float z) :
		m_Width{ width }, m_Height{ height }
	{
		m_Color.x = r;
		m_Color.y = g;
		m_Color.z = b;
		m_Position.x = x;
		m_Position.y = y;
		m_Position.z = z;
	}
	void setHeight(int height) { m_Height = height; }
	void setWidth(int width) { m_Width = width; }
	void setColor(glm::vec3 color) { m_Color = color; }
	void setColor(float r, float g, float b) 
	{
		m_Color.x = r;
		m_Color.y = g;
		m_Color.z = b;
	}
	glm::vec3 getColor() { return m_Color; }
	int getHeight() { return m_Height; }
	int getWidth() { return m_Width; }

	virtual float getArea() = 0;
	virtual float* generateVertices() = 0;


protected:
	int m_Width = 0;
	int m_Height = 0;
	

	glm::vec3 m_Position = {};
	glm::vec3 m_Color = {};
	
};

