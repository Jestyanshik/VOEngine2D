#pragma once
#include "Window/Window.h"
#include "Common/Settings.h"
#include "Common/Threading.h"
#include "Renderer/Scene.h"

namespace VOEngine {
	class ResourceManager {
	public:
		static ResourceManager& GetInstance() {
			static ResourceManager instance{};
			return instance;
		}
		ResourceManager(const ResourceManager&) = delete;
		ResourceManager(ResourceManager&&) = delete;
		ResourceManager& operator=(const ResourceManager&) = delete;
		ResourceManager& operator=(ResourceManager&&) = delete;
		std::shared_ptr<Window> getWindow() { return m_Window; };
		std::shared_ptr<SettingsManager> getSettings() { return m_Settings; };
		std::vector<Event>& GetEvents() { return m_Events; };
		Scheduler& GetScheduler() { return m_Scheduler; };
		void Init();
	private:
		ResourceManager() {};
		~ResourceManager();
		std::shared_ptr<Window> m_Window;
		std::shared_ptr<SettingsManager> m_Settings;
		std::vector<Event> m_Events{};
		std::shared_ptr<Scene> m_Scene;
		Scheduler m_Scheduler{};
		void CollectData();
	};
}


