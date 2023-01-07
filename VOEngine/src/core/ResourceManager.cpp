#include "vopch.h"
#include "ResourceManager.h"
#include "Log/Log.h"
#include "Rendering/Renderer/OpenGLRenderer/OpenGLRenderer.h"
#include "Rendering/Windows/GLFWWindow/GLFWWindow.h"

#include "ImGuiBackend/imgui_impl_opengl3.h"
#include "ImGuiBackend/imgui_impl_glfw.h"
#include "imgui.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"


namespace VOEngine {
	Renderer* ResourceManager::s_Renderer;
	Window* ResourceManager::s_Window;
	std::vector<std::function<void(void)>> ResourceManager::m_RenderQueue;
	std::string ResourceManager::s_CurrentWindow;
	std::string ResourceManager::s_CurrentRenderer;

	void ResourceManager::Init()
	{
		if (Log::Init())
			VO_CORE_INFO("spdlog succesfuly initialized");
		//Temporary code imGui should be replaced with something else
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		ImGui::StyleColorsDark();
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		//
		
		//TODO: Settings in .ini file
		s_CurrentRenderer = "OpenGL";
		s_CurrentWindow   = "GLFW";

		if (s_CurrentWindow == "GLFW") {
			s_Window = new GLFWWindow(1280, 720, "VOEngine application");
			s_Window->setDecorated(true);
			s_Window->setPosition(glm::vec2(200,200));
			
		}
		if (s_CurrentRenderer == "OpenGL")
			s_Renderer = new OpenGLRenderer();

		//Temp
		if (s_CurrentWindow == "GLFW")
			ImGui_ImplGlfw_InitForOpenGL(((GLFWWindow*)s_Window)->getNativeWindow(), true);
		if (s_CurrentRenderer == "OpenGL")
			ImGui_ImplOpenGL3_Init("#version 460");
		//Temp
	}

	void ResourceManager::Cleanup() {
		//Temp
		VO_CORE_INFO("ImGui destructed");
		if (s_CurrentRenderer == "OpenGL") 
			ImGui_ImplOpenGL3_Shutdown();
		if (s_CurrentWindow == "GLFW")
			ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
		//Temp
		delete s_Window;
		delete s_Renderer;
	}

	void ResourceManager::Run() {
		while (!s_Window->shouldClose()) {
			s_Window->pollEvents();

			//temp
			if (s_CurrentRenderer == "OpenGL")
				ImGui_ImplOpenGL3_NewFrame();
			if (s_CurrentWindow == "GLFW")
				ImGui_ImplGlfw_NewFrame();
			
			ImGui::NewFrame();
			ImGui::DockSpaceOverViewport(NULL, ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode);
			for (std::function<void(void)> fn : m_RenderQueue) {
				fn();
			}
			static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
			ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

			if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
				window_flags |= ImGuiWindowFlags_NoBackground;

			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
			ImGui::Begin("DockSpace", nullptr, window_flags);
			ImGui::PopStyleVar();
			ImGui::PopStyleVar(2);

			// DockSpace
			ImGuiIO& io = ImGui::GetIO();
			if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
				ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
				ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
			}
			ImGui::End();
			ImGui::Render();
			//temp

			if (s_Window->isKeyPressed(Key::Escape)) {
				s_Window->setShouldClose(true);
			}
			s_Renderer->render();

			//temp
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				GLFWwindow* backup_current_context = glfwGetCurrentContext();
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
				glfwMakeContextCurrent(backup_current_context);
			}
			ImGui::EndFrame();
			//temp

			s_Window->swapBuffers();
		}
	}


}

