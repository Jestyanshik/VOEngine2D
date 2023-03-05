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
		const std::unordered_map<UUID, std::shared_ptr<Unit>> getRenderUnits() { return m_RenderUnitList; };
		void AddUnit(UnitTypes unitType);
		void render() {
			m_Renderer->submitDrawCalls();
		}
		void update() {
			for (const auto& unit : m_RenderUnitList) {
				unit.second->UpdateVertices();
			}
		}
		const glm::uvec2& getViewport() { return m_Viewport; };
		Renderer* getRenderer() const { return m_Renderer; };
	private:
		std::unordered_set<UnitTypes> m_UnitTypes{};
		std::unordered_map<UUID, std::shared_ptr<Unit>> m_RenderUnitList;
		Renderer* m_Renderer;
		SoundEngine* m_SoundEngine;
		//TODO: Add camera
		glm::uvec2 m_Viewport;
	};
}