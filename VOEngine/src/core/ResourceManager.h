#pragma once
#include "Window/Window.h"
#include "Common/Settings.h"
#include "Renderer/Scene.h"

namespace VOEngine {
	//Singleton
	class ResourceManager {
	public:
		static ResourceManager& getInstance() {
			static ResourceManager instance{};
			return instance;
		}
		ResourceManager(const ResourceManager&) = delete;
		ResourceManager(ResourceManager&&) = delete;
		ResourceManager& operator=(const ResourceManager&) = delete;
		ResourceManager& operator=(ResourceManager&&) = delete;
		std::shared_ptr<Window> getWindow() { return m_Window; };
		std::shared_ptr<SettingsManager> getSettings() { return m_Settings; };
		void Init();
	private:
		ResourceManager() {};
		~ResourceManager();
		std::shared_ptr<Window> m_Window;
		std::shared_ptr<SettingsManager> m_Settings;
		std::shared_ptr<Scene> m_Scene;
		void collectData();
	};
}


