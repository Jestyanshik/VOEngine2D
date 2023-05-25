#pragma once
#include "Unit.h"
#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include "Framebuffer.h"
#include "Core/Sound/AudioLoader.h"
#include "Core/Sound/SoundEngine.h"

namespace VOEngine {
	class Scene {
	public:
		Scene(const glm::uvec2& viewport, const std::string& name);
		Scene(std::unique_ptr<Framebuffer> framebuffer, const std::string& name);
		~Scene() {
			delete m_SoundEngine;
		}
		void resize(glm::uvec2 viewport) {
			m_Viewport = viewport;
			m_Renderer->setViewport(m_Viewport);
			if (m_Framebuffer != nullptr) 
				m_Framebuffer->resize(m_Viewport);
		}
		const std::unordered_map<UUID, std::shared_ptr<Unit>> getRenderUnits() { return m_RenderUnitList; };
		void AddUnit(UnitTypes unitType);
		void AddUnit(Unit* unit);
		static Scene* loadFromString(std::unique_ptr<Framebuffer> framebuffer, const std::string& sceneString);
		const uint32_t getFrameBuffer() { return m_Framebuffer->getTextureID(); };
		void render();
		std::string toString();
		void update() {
			for (const auto& unit : m_RenderUnitList) {
				unit.second->UpdateVertices();
			}
		}
		const glm::uvec2& getViewport() { return m_Viewport; };
		Renderer* getRenderer() const { return m_Renderer.get(); };
	private:
		std::unordered_set<UnitTypes> m_UnitTypes{};
		std::unordered_map<UUID, std::shared_ptr<Unit>> m_RenderUnitList;
		std::unique_ptr<Framebuffer> m_Framebuffer;
		std::unique_ptr<Renderer> m_Renderer;
		std::string m_Name;
		SoundEngine* m_SoundEngine;
		//TODO: Add camera
		glm::uvec2 m_Viewport;
	public:
		bool operator==(const Scene& other) const;
	};
}