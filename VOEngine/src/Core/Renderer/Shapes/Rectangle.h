#pragma once
#include "BaseShape.h"
class Rectangle : public BaseShape {
	float* generateVertices() override {
		float x = m_Position.x, y = m_Position.y, z = m_Position.z;
		float vertices[] = {
			x		   , y 			 , z, 0, 0,
			x + m_Width, y   		 , z, 1, 0,
			x + m_Width, y + m_Height, z, 1, 1,
			x          , y + m_Height, z, 0, 1
		};

		return vertices;
	}
};

