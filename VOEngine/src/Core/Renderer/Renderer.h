#pragma once
#include "Shader.h"
#include "Unit.h"

namespace VOEngine {
	class Renderer {
	public:
		Renderer() {};
		virtual std::string getVersion() = 0;

		virtual void setViewport(glm::uvec2 viewport) = 0;
		virtual void renderSquare(const Unit& unit) = 0;
		virtual void render() = 0;
	protected:
		Shader* m_Shader = nullptr;
	};
}


