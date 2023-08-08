#include "vopch.h"
#include "ResourceManager.h"
#include "Common/Log.h"
#include "Window/GLFWWindow/GLFWWindow.h"
#include "Sound/SoundEngine.h"
#include "Sound/OpenAL/OpenALSoundEngine.h"
#include "Common/PlatformUtils.h"


namespace VOEngine {
	void ResourceManager::Init() {
		if (Log::Init())
			VO_CORE_INFO("spdlog succesfuly initialized");
		m_Settings = std::make_shared<SettingsManager>();
		m_Notifier = std::make_shared<EventNotifier>();

		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		ImGui::StyleColorsDark();
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		std::vector<std::string> strSize = m_Settings->GetNodeSequence("Window", "Size");
		glm::ivec2 size;
		if (!(strSize[0]).empty()) size = { std::stoi(strSize[0]), std::stoi(strSize[1]) };
		else size = { 1280, 720 };
		if (m_Settings->GetValue("WindowLibrary") == "GLFW")
			m_Window = std::make_shared<GLFWWindow>(size.x, size.y, m_Settings->GetValue("Name"));
		m_Window->setDecorated(true);
		std::vector<std::string> strPos = m_Settings->GetNodeSequence("Window", "Pos");
		glm::ivec2 pos;
		if (!(strPos[0]).empty()) pos = { std::stoi(strPos[0]), std::stoi(strPos[1]) };
		else pos = { 100, 100 };
		m_Window->setPosition(pos);

		{
			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
				VO_CORE_ERROR("OpenGL couldn't initialize");
			else
				VO_CORE_INFO("OpenGL succesfully initialized");
		}

		if (m_Settings->GetValue("WindowLibrary") == "GLFW")
			ImGui_ImplGlfw_InitForOpenGL(((GLFWWindow*)m_Window.get())->getNativeWindow(), true);
		if (m_Settings->GetValue("Renderer") == "OpenGL")
			ImGui_ImplOpenGL3_Init("#version 460");
	}

	ResourceManager::~ResourceManager() {
		CollectData();
		VO_CORE_INFO("ImGui destructed");
		if (m_Settings->GetValue("Renderer") == "OpenGL")
			ImGui_ImplOpenGL3_Shutdown();
		if (m_Settings->GetValue("WindowLibrary") == "GLFW")
			ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ResourceManager::CollectData() {
		std::vector<uint32_t> windowSize = { m_Window->getSize().x, m_Window->getSize().y };
		std::vector<int> windowPos = { m_Window->getPos().x, m_Window->getPos().y };

		m_Settings->SetNodeValue("Window", "Size", windowSize);
		m_Settings->SetNodeValue("Window", "Pos", windowPos);
	}
}

