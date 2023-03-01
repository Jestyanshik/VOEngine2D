#pragma once
#include "Shader.h"
#include "Unit.h"

namespace VOEngine {
	class Renderer {
	public:
		Renderer() {};
		virtual std::string getVersion() = 0;

		virtual std::shared_ptr<VertexArray> GenerateVertexArray(const std::vector<float>& VBO, const std::vector<uint32_t>& IBO) = 0;
		virtual void setViewport(glm::uvec2 viewport) = 0;
		virtual void drawSquare(const Unit& unit) = 0;
		virtual void submitDrawCalls(VertexArray* VAO) = 0;
	protected:
		Shader* m_Shader = nullptr;
	};
}


