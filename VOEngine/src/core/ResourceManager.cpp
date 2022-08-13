#include "vopch.h"
#include "ResourceManager.h"
#include "ImGuiManager.h"
#include "Renderer.h"
#include "Window.h"


namespace VOEngine {
	std::shared_ptr<ImGuiManager> ResourceManager::s_ImGuiManager;
	std::shared_ptr<Renderer> ResourceManager::s_Renderer;
	Window* ResourceManager::s_Window;
	void(*ResourceManager::s_whileLoop)();
	bool(*ResourceManager::s_whileLoopStopConditionFunction)();


	Window* ResourceManager::createWindow(int width, int height, const std::string& title, bool resizalbe, bool decorated, bool focused, bool autoIconify, bool maximized, const std::string& pathToIcon) {
		s_Window = new Window(width, height, title, resizalbe, decorated, focused, autoIconify, maximized, pathToIcon);
		s_ImGuiManager->passVOEngineWindow(s_Window);
		return s_Window;
	}

	void ResourceManager::createWhileLoopFunction(void(*whileLoopFunction)()) {
		s_whileLoop = whileLoopFunction;
	}

	void ResourceManager::executeWhileLoop() {
		while (!s_whileLoopStopConditionFunction()) {
			s_Window->pollEvents();
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			ImGui::DockSpaceOverViewport(NULL, ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode);
			for (auto renderItem : s_ImGuiManager->getRenderLayer()) {
				renderItem();
			}
			int framebufferWidth = s_Window->getFramebufferWidth();
			int framebufferHeight = s_Window->getFramebufferHeight();

			ImGui::Render();
			glfwGetFramebufferSize(s_Window->getGLFWwindow(), &framebufferWidth, &framebufferHeight);
			s_whileLoop();

			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				GLFWwindow* backup_current_context = glfwGetCurrentContext();
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
				glfwMakeContextCurrent(backup_current_context);
			}

			s_Window->swapBuffers();
		}
	}

	void ResourceManager::setWhileLoopStopCondition(bool(*stopConditionFunction)()) {
		s_whileLoopStopConditionFunction = stopConditionFunction;
	}






}

