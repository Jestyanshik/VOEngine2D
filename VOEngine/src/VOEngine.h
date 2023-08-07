#pragma once
#include "Core/Common/KeyCodes.h"
#include "Core/Common/Performance.h"
#include "Core/Window/Window.h"
#include "Core/Renderer/Renderer.h"
#include "Core/Common/PlatformUtils.h"
#include "Core/Sound/SoundEngine.h"
#include "Core/ImGui/ImGuiCore.h"
#include "Core/ResourceManager.h"
#include "Core/Common/Settings.h"
#include "Core/Renderer/SceneRenderer.h"
#include "Core/Common/Threading.h"

namespace VOEngine {
	class Application {
	public:
		Application() {
			ResourceManager::GetInstance().Init();
			m_Window = ResourceManager::GetInstance().getWindow();
			m_Settings = ResourceManager::GetInstance().getSettings();
			m_Scheduler = ResourceManager::GetInstance().GetScheduler();
			m_Renderer = std::make_unique<SceneRenderer>();
		}
		virtual void OnImGuiRender() = 0;
		virtual void OnRender() = 0;
		virtual void OnStartup() = 0;
		virtual void OnClose() = 0;
		void run() {
			OnStartup();
			Render();
			OnCleanup();
			OnClose();
		}
	protected:
		std::shared_ptr<Window> m_Window;
		std::shared_ptr<SettingsManager> m_Settings;
		std::vector<std::shared_ptr<Scene>> m_Scenes;
		std::shared_ptr<Scene> m_Scene = nullptr;
		Scheduler m_Scheduler;

		void CreateScene(std::unique_ptr<Framebuffer> framebuffer, const std::string& name) {
			m_Scene = std::make_shared<Scene>(std::move(framebuffer), name);
			m_Scenes.emplace_back(m_Scene);
		};

		void RenderScene(std::shared_ptr<Scene> scene) {
			m_Renderer->SetScene(scene);
		}
	private:
		std::unique_ptr<SceneRenderer> m_Renderer;

		void OnCleanup() {
			m_Window = nullptr;
			m_Settings = nullptr;
		};
		void Render() {
			while (!m_Window->shouldClose()) {
				m_Window->pollEvents();

				ImGuiWrapper::NewFrame();

				OnImGuiRender();
				if (m_Scene != nullptr) {
					m_Renderer->Render();
				} 	

				ImGuiWrapper::DockSpace();

				OnRender();
				if (m_Window->isKeyPressed(Key::Escape)) {
					m_Window->setShouldClose(true);
				}

				ImGuiWrapper::EndFrame();
				
				m_Window->swapBuffers();
			}
		};
	};
}
