#pragma once
#include "imgui.h"
#include "ImGuiBackend/imgui_impl_opengl3.h"
#include "ImGuiBackend/imgui_impl_glfw.h"
#include "GLFW/glfw3.h"
#include "Window.h"

namespace VOEngine {
	class ImGuiManager {
	public:
		ImGuiManager();
		~ImGuiManager();
		void Initialize();
		void passGLFWwindow(GLFWwindow* window);
		void passVOEngineWindow(Window* window);
		void createWindow(void (*func)()) { m_RenderLayer.push_back(func); };
		std::vector<void (*)()>& getRenderLayer() { return m_RenderLayer; };
		//void preRender();
		//void afterRender();
	private:
		bool m_HasGLFWwindow = false;
		Window* m_RenderWindow;
		std::vector<void (*)()> m_RenderLayer;
	public:

	};
}


