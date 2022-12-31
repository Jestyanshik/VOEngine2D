#pragma once
#include "Rendering/Renderer/Renderer.h"
#include "Rendering/Renderer/OpenGLRenderer/OpenGLRenderer.h"
#include "Rendering/Windows/Window.h"



namespace VOEngine {
	
	class ResourceManager {
	public:
		
		static void Init();
		static void Cleanup();
		static void Run();
		static Window*   getWindow()   { return s_Window; };
		static Renderer* getRenderer() { return s_Renderer; };
		static void		 addWindow(std::function<void(void)> function) { m_RenderQueue.push_back(function);};

	private:
		static std::string currentUIRenderer;
		static Renderer* s_Renderer;
		static Window* s_Window;
		static std::vector<std::function<void(void)>> m_RenderQueue;
		static std::string s_CurrentWindow;
		static std::string s_CurrentRenderer;

	public:
		
	};
}


