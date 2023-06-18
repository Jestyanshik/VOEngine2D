#pragma once
#include "Shader.h"
#include "Unit.h"

namespace VOEngine {
	class Renderer {
	public:
		Renderer();
		std::string getVersion();

		std::shared_ptr<VertexArray> GenerateVertexArray();
		void SetViewport(glm::uvec2 viewport);

		void DrawSquare(std::shared_ptr<Unit> unit, bool isCopy) {
			if (!isCopy) {
				m_DrawCount++;
				m_VAOToDraw.emplace_back(unit->VAO);
			}
		};

		void DrawElements(VertexArray* vao, uint32_t indices);
		void SubmitDrawCalls();
		void Clear(glm::vec4 color);
	protected:
		Shader* m_Shader = nullptr;
		uint32_t m_DrawCount = 0;
		std::vector<std::shared_ptr<VertexArray>> m_VAOToDraw{};
	};


}


