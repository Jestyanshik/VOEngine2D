#pragma once
#include "Window/Window.h"
#include "Common/Settings.h"
#include "Common/Threading.h"
#include "Common/Events.h"
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
		std::shared_ptr<Window> GetWindow() { return m_Window; };
		std::shared_ptr<SettingsManager> GetSettings() { return m_Settings; };
		Scheduler& GetScheduler() { return m_Scheduler; };
		std::shared_ptr<EventNotifier> GetEventNotifier() { return m_Notifier; };
		void Init();
	private:
		ResourceManager() {};
		~ResourceManager();
		std::shared_ptr<Window> m_Window;
		std::shared_ptr<SettingsManager> m_Settings;
		std::shared_ptr<EventNotifier> m_Notifier{};
		Scheduler m_Scheduler{};
		void CollectData();
	};
}


