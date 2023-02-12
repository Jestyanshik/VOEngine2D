#pragma once
#include "Renderer/Renderer.h"
#include "Window/Window.h"
#include "Common/Settings.h"
#include "Sound/SoundEngine.h"

namespace VOEngine {
	
	class ResourceManager {
	public:
		static void Init();
		static void Cleanup();
		static Window*   getWindow()   { return s_Window; };
		static Renderer* getRenderer() { return s_Renderer; };
		static SoundEngine* getSoundEngine() { return s_SoundEngine; };
		static SettingsManager* getSettings() { return s_Settings; };
	private:
		static Renderer* s_Renderer;
		static Window* s_Window;
		static SoundEngine* s_SoundEngine;
		static SettingsManager* s_Settings;
		static void collectData();
	};
}


