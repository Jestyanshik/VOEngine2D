#pragma once
#include "Core/Window/Window.h"
#include "Core/Sound/SoundEngine.h"
#include "Core/ImGui/ImGuiCore.h"
#include "Core/ResourceManager.h"
#include "Core/Common/Settings.h"
#include "Core/Renderer/SceneRenderer.h"
#include "Core/Common/Threading.h"
#include "Core/Common/Events.h"
#include "Core/Renderer/Scene.h"
#include "Core/Renderer/Framebuffer.h"

namespace VOEngine {
	class Application {
	public:
		Application() {
			ResourceManager::GetInstance().Init();
			m_Window = ResourceManager::GetInstance().GetWindow();
			m_Settings = ResourceManager::GetInstance().GetSettings();
			m_Scheduler = ResourceManager::GetInstance().GetScheduler();
			m_EventNotifier = ResourceManager::GetInstance().GetEventNotifier();
			m_Renderer = std::make_unique<SceneRenderer>();
			m_SoundEngine = BuildSoundEngine();
		}
		virtual void OnImGuiRender(int64_t deltaTime) = 0;
		virtual void OnRender(int64_t deltaTime) = 0;
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
		std::shared_ptr<EventNotifier> m_EventNotifier;
		std::vector<std::shared_ptr<Scene>> m_Scenes;
		std::unique_ptr<SoundEngine> m_SoundEngine;
		std::shared_ptr<Scene> m_Scene = nullptr;
		Scheduler m_Scheduler;

		void CreateScene(std::shared_ptr<Framebuffer> framebuffer, const std::string& name) {
			m_Scene = std::make_shared<Scene>(framebuffer, name);
			m_Scenes.emplace_back(m_Scene);
		};

		void SetScene(std::shared_ptr<Scene> scene) {
			m_Renderer->SetScene(scene);
		}
	private:
		std::unique_ptr<SceneRenderer> m_Renderer;

		void OnCleanup() {
			m_Window = nullptr;
			m_Settings = nullptr;
		};
		void Render() {
			std::chrono::steady_clock::time_point end, begin;
			uint64_t deltaTime{1};
			while (!m_Window->ShouldClose()) {
				m_Window->PollEvents();
				
				ImGuiWrapper::NewFrame();
				m_Renderer->Clear({0,0,0,1});

				OnImGuiRender(deltaTime);
				
				if (m_Scene != nullptr) {
					begin = std::chrono::steady_clock::now();
					
					m_EventNotifier->Notify(EventType::RenderUpdate);
					
					m_Renderer->Render();
					OnRender(deltaTime);

					m_EventNotifier->Notify(EventType::Resize);
					
					end = std::chrono::steady_clock::now();
					deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
				} 	
				
				ImGuiWrapper::DockSpace();
				
				if (m_Window->IsKeyPressed(Key::Escape)) {
					m_Window->SetShouldClose(true);
				}

				ImGuiWrapper::EndFrame();
				
				m_Window->SwapBuffers();
			}
		};
	};
}
