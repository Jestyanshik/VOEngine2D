#pragma once
#include "Window/Window.h"
#include "Common/Settings.h"
#include "Renderer/Scene.h"

namespace VOEngine {
	
	class ResourceManager {
	public:
		static void Init();
		static void Cleanup();
		static Window*   getWindow()   { return s_Window; };
		static SettingsManager* getSettings() { return s_Settings; };
	private:
		static Window* s_Window;
		static SettingsManager* s_Settings;
		static Scene* s_Scene;
		static void collectData();
	};
}


