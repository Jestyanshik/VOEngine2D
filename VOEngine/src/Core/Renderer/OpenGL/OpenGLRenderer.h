#pragma once
#include "../Renderer.h"
#include "../Shader.h"
#include "Core/ResourceManager.h"


namespace VOEngine { 
	class OpenGLRenderer : public Renderer {
	public:
		std::string getVersion() override;
		OpenGLRenderer();
		void setViewport(glm::uvec2 viewport) override;
		void drawSquare(const Unit& unit) override;
		void submitDrawCalls(VertexArray* VAO) override;
		std::shared_ptr<VertexArray> GenerateVertexArray(const std::vector<float>& VBO, const std::vector<uint32_t>& IBO) override;
	};
}
