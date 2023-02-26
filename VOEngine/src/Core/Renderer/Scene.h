#pragma once
#include "Unit.h"
#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include "Core/Sound/AudioLoader.h"
#include "Core/Sound/SoundEngine.h"

namespace VOEngine {
	class Scene {
	public:
		Scene(glm::uvec2 viewport);
		~Scene() {
			delete m_Renderer;
			delete m_SoundEngine;
		}
		void resize(glm::uvec2 viewport) {
			m_Viewport = viewport;
			m_Renderer->setViewport(m_Viewport);
		}
		void AddSquare(const glm::vec2& position = glm::vec2(0,0),
			const glm::uvec2& size = glm::uvec2(0,0),
			const glm::vec4& color = glm::vec4(0,0,0,0),
			Sound* sound = nullptr, 
			Texture* texture = nullptr) {
			std::shared_ptr<Unit> square = std::make_shared<Unit>(position, size, color);
			square->Texture = texture;
			square->Sound = sound;
			m_RenderUnitList.push_back(square);
		}
		void render() {
			for (const std::shared_ptr<Unit>& unit : m_RenderUnitList) {
				if (unit->shapeType == ShapeTypes::Square)
					m_Renderer->renderSquare(unit->Position);
			}
		}
		Renderer* getRenderer() { return m_Renderer; };
	private:
		std::vector<std::shared_ptr<Unit>> m_RenderUnitList;
		Renderer* m_Renderer;
		SoundEngine* m_SoundEngine;
		//TODO: Add camera
		glm::uvec2 m_Viewport;
	};
}