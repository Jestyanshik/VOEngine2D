#pragma once
#include "ImGuiManager.h"
#include "Renderer.h"
#include "Window.h"

namespace VOEngine {
	class ResourceManager {
	public:
		static void Init() {
			s_ImGuiManager = std::make_shared<ImGuiManager>();
			s_Renderer = std::make_shared<Renderer>();
		};
		static void Cleanup() {
			delete s_Window;
		}
		static Window* createWindow(int width, int height, const std::string& title, bool resizalbe = true,
			bool decorated = true, bool focused = true, bool autoIconify = false,
			bool maximized = false, const std::string& pathToIcon = "");
		static std::shared_ptr<ImGuiManager>& getImGuiManager() { return s_ImGuiManager;}
		static std::shared_ptr<Renderer>& getRenderer() { return s_Renderer;}
		static Window* getWindow() { return s_Window;}
		static void testFunc() { if (s_Window != nullptr) VO_CORE_INFO(s_Window->getHeight());}
		static void createWhileLoopFunction(void (*whileLoopFunction)());
		static void setWhileLoopStopCondition(bool (*stopConditionFunction)());
		static void executeWhileLoop();

	private:		
		static std::shared_ptr<ImGuiManager> s_ImGuiManager;
		static std::shared_ptr<Renderer> s_Renderer;
		static Window* s_Window;
		static void(*s_whileLoop)();
		static bool(*s_whileLoopStopConditionFunction)();
	public:

	};
}


