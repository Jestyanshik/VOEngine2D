#pragma once
#include "glm.hpp"

namespace VOEngine { 
	class Renderer {
	public:
		Renderer();
		~Renderer();
		void setViewport(int x, int y, int width, int height);
		void setViewport(glm::vec2 pos, glm::ivec2 size);
		void fillWindow(glm::vec4 color);
		void fillWindow(float r, float g, float b, float a);
		void pushToRenderLayer(void (*f)()) { m_RenderLayer.push_back(f);};
		void render();
	private:
		std::vector<void (*)()> m_RenderLayer;
	};
}
