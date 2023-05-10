#pragma once
#include "Shader.h"
#include "Unit.h"

namespace VOEngine {
	class Renderer {
	public:
		Renderer() {};
		virtual std::string getVersion() = 0;

		virtual std::shared_ptr<VertexArray> GenerateVertexArray() = 0;
		virtual void setViewport(glm::uvec2 viewport) = 0;
		//isCopy just tells if unit got assigned new VAO{false} or the reference to the existing one{true} 
		void drawSquare(std::shared_ptr<Unit> unit, bool isCopy) {
			if (!isCopy) {
				m_DrawCount++;
				m_VAOToDraw.emplace_back(unit->VAO);
			}
		};
		const uint32_t getFrameBufferID() { return m_FrameBufferID; };
		virtual void submitDrawCalls() = 0;
	protected:
		Shader* m_Shader = nullptr;
		uint32_t m_DrawCount = 0;
		uint32_t m_FrameBufferID = 0;
		std::vector<std::shared_ptr<VertexArray>> m_VAOToDraw{};
	};
}


