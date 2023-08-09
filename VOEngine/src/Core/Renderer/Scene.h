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
		Scene(std::shared_ptr<Framebuffer> framebuffer, const std::string& name);
		void resize(glm::uvec2 viewport) {
			m_Viewport = viewport;
		}
		const std::unordered_map<UUID, std::shared_ptr<Unit>> GetRenderUnits() { return m_RenderUnitList; };
		void AddUnit(UnitTypes unitType);
		void LoadFromFile(const std::filesystem::path& path);
		void SaveToFile(const std::filesystem::path& path);
		std::string_view GetName() { return m_Name; };
		std::shared_ptr<Framebuffer> GetFramebuffer() { return m_Framebuffer; };
		const glm::uvec2& GetViewport() { return m_Viewport; };	
	private:
		std::unordered_map<UUID, std::shared_ptr<Unit>> m_RenderUnitList;
		std::shared_ptr<Framebuffer> m_Framebuffer;
		std::string m_Name;
		//TODO: Add camera
		glm::uvec2 m_Viewport;
	};
}