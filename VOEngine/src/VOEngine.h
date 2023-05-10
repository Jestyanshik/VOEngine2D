#pragma once
#include "Core/Common/KeyCodes.h"
#include "Core/Common/Performance.h"
#include "Core/Window/Window.h"
#include "Core/Renderer/Renderer.h"
#include "Core/Common/PlatformUtils.h"
#include "Core/Sound/SoundEngine.h"
#include "Core/ImGuiBackend/imgui_impl_opengl3.h"
#include "Core/ImGuiBackend/imgui_impl_glfw.h"
#include "Core/ResourceManager.h"
#include "Core/Common/Settings.h"

namespace VOEngine {
	class Application {
	public:
		Application(){
			ResourceManager::getInstance().Init();
			m_Window = ResourceManager::getInstance().getWindow();
			m_Settings = ResourceManager::getInstance().getSettings();
			m_Scene = ResourceManager::getInstance().getScene();
		}
		virtual void OnImGuiRender() = 0;
		virtual void OnRender() = 0;
		virtual void OnStartup() = 0;
		void run() {
			OnStartup();
			Render();
			OnCleanup();
		}
	protected:
		std::shared_ptr<Window> m_Window;
		std::shared_ptr<SettingsManager> m_Settings;
		std::shared_ptr<Scene> m_Scene;
	private:
		void OnCleanup() {
			m_Window = nullptr;
			m_Settings = nullptr;
			m_Scene = nullptr;
		};
		void Render() {
			while (!m_Window->shouldClose()) {
				m_Window->pollEvents();

				//temp
				//if (m_Settings->GetValue("Renderer") == "OpenGL") {
					ImGui_ImplOpenGL3_NewFrame();
				//}
				//if (m_Settings->GetValue("WindowLibrary") == "GLFW") {
					ImGui_ImplGlfw_NewFrame();
				//}

				ImGui::NewFrame();
				ImGui::DockSpaceOverViewport(NULL, ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode);
				OnImGuiRender();
				m_Scene->update();
				m_Scene->render();
				ImGui::Begin("Scene");
				ImGui::Image(ImTextureID((void*)m_Scene->getFrameBuffer()), ImVec2(800, 600));
				ImGui::End();
				
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
				OnRender();
				if (m_Window->isKeyPressed(Key::Escape)) {
					m_Window->setShouldClose(true);
				}
				
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
				m_Window->swapBuffers();
			}
		}
	};
}
