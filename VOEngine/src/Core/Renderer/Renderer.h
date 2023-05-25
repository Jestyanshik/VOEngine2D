#pragma once
#include "Shader.h"
#include "Unit.h"

namespace VOEngine {
	class Renderer {
	public:
		Renderer();
		std::string getVersion();

		std::shared_ptr<VertexArray> GenerateVertexArray();
		void setViewport(glm::uvec2 viewport);

		void drawSquare(std::shared_ptr<Unit> unit, bool isCopy) {
			if (!isCopy) {
				m_DrawCount++;
				m_VAOToDraw.emplace_back(unit->VAO);
			}
		};
		const uint32_t getFrameBufferID() { return m_FrameBufferID; };
		void submitDrawCalls();
		void clear(glm::vec4 color);
	protected:
		Shader* m_Shader = nullptr;
		uint32_t m_DrawCount = 0;
		uint32_t m_FrameBufferID = 0;
		std::vector<std::shared_ptr<VertexArray>> m_VAOToDraw{};
	};


}


