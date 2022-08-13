#pragma once
#include "vopch.h"
#include "ImGuiManager.h"
#include "imgui.h"
#include "ImGuiBackend/imgui_impl_opengl3.h"
#include "ImGuiBackend/imgui_impl_glfw.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Window.h"

namespace VOEngine {
	ImGuiManager::ImGuiManager() {
		m_RenderLayer = {};
		m_RenderWindow = nullptr;
		Initialize();
	}

	ImGuiManager::~ImGuiManager() {
		VO_CORE_ERROR("Destructed");
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiManager::Initialize() {
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		ImGui::StyleColorsDark();
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	}

	void ImGuiManager::passGLFWwindow(GLFWwindow* window) {
		m_HasGLFWwindow = true;
		VO_CORE_ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 460");
	}

	void ImGuiManager::passVOEngineWindow(Window* window) {
		m_RenderWindow = window; 
		if (!m_HasGLFWwindow) {
			passGLFWwindow(window->getGLFWwindow());
		}

	}



}
