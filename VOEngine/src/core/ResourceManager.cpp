#include "vopch.h"
#include "ResourceManager.h"
#include "Common/Log.h"
#include "Renderer/OpenGLRenderer/OpenGLRenderer.h"
#include "Window/GLFWWindow/GLFWWindow.h"
#include "Sound/SoundEngine.h"
#include "Sound/OpenAL/OpenALSoundEngine.h"
#include "Common/PlatformUtils.h"


namespace VOEngine {
	Renderer* ResourceManager::s_Renderer;
	Window* ResourceManager::s_Window;
	SoundEngine* ResourceManager::s_SoundEngine;
	SettingsManager* ResourceManager::s_Settings;

	void ResourceManager::Init() {
		if (Log::Init())
			VO_CORE_INFO("spdlog succesfuly initialized");
		s_Settings = new SettingsManager();
		//Temporary code imGui should be replaced with something else
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		ImGui::StyleColorsDark();
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		if (s_Settings->GetValue("SoundEngine") == "OpenAL")
			s_SoundEngine = new OpenALSoundEngine();

		std::vector<std::string> strSize = s_Settings->GetNodeSequence("Window", "Size");
		glm::ivec2 size;
		if (!(strSize[0]).empty()) size = { std::stoi(strSize[0]), std::stoi(strSize[1]) };
		else size = { 1280, 720 };
		if (s_Settings->GetValue("WindowLibrary") == "GLFW") 
			s_Window = new GLFWWindow(size.x, size.y, s_Settings->GetValue("Name"));
		s_Window->setDecorated(true);
		std::vector<std::string> strPos = s_Settings->GetNodeSequence("Window", "Pos");
		glm::ivec2 pos;
		if (!(strPos[0]).empty()) pos = { std::stoi(strPos[0]), std::stoi(strPos[1]) };
		else pos = { 100, 100 };
		s_Window->setPosition(pos);

		if (s_Settings->GetValue("Renderer") == "OpenGL")
			s_Renderer = new OpenGLRenderer();

		//Temp
		if (s_Settings->GetValue("WindowLibrary") == "GLFW")
			ImGui_ImplGlfw_InitForOpenGL(((GLFWWindow*)s_Window)->getNativeWindow(), true);
		if (s_Settings->GetValue("Renderer") == "OpenGL")
			ImGui_ImplOpenGL3_Init("#version 460");
		//Temp
	}

	void ResourceManager::Cleanup() {
		//Temp
		PlatformUtils::s_StopExecution = true;
		try {
			PlatformUtils::m_LoopThread.join();
		}
		catch (const std::exception&) {}
		collectData();
		VO_CORE_INFO("ImGui destructed");
		if (s_Settings->GetValue("Renderer") == "OpenGL")
			ImGui_ImplOpenGL3_Shutdown();
		if (s_Settings->GetValue("WindowLibrary") == "GLFW")
			ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
		//Temp
		delete s_Window;
		delete s_Renderer;
		delete s_SoundEngine;
		delete s_Settings;
	}

	void ResourceManager::collectData() {
		std::vector<uint32_t> windowSize = { s_Window->getSize().x, s_Window->getSize().y };
		std::vector<int> windowPos = { s_Window->getPos().x, s_Window->getPos().y };

		s_Settings->SetNodeValue("Window", "Size", windowSize);
		s_Settings->SetNodeValue("Window", "Pos", windowPos);
	}
}

