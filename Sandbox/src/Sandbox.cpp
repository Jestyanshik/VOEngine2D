#include "vopch.h"
#include "VOEngine.h"



int main() {
	VOEngine::Init();
	
	VOEngine::ImGuiManager& imgui = *VOEngine::ResourceManager::getImGuiManager();
	VOEngine::Renderer& renderer = *VOEngine::ResourceManager::getRenderer();
	VOEngine::Window& editorWindow = *VOEngine::ResourceManager::createWindow(1920, 1080, "VOEngine");
	

	VOEngine::ResourceManager::testFunc();

	imgui.createWindow([]() {
		ImGui::Begin("VOEngine", NULL);
		static glm::vec3 color;
		ImGui::ColorEdit3("Clear color", (float*)&color);
		VOEngine::ResourceManager::getRenderer()->fillWindow(color.x, color.y, color.z, 1);
		ImGui::End();
		});
	imgui.createWindow([]() {
		ImGui::Begin("Alolololoasdsad");
		static char buf[10000];
		ImGui::InputText("Text", buf, sizeof(buf));
		ImGui::End();
		});
	VOEngine::ResourceManager::createWhileLoopFunction([]() {
		if (VOEngine::ResourceManager::getWindow()->isKeyPressed(VOEngine::Key::Escape)) VOEngine::ResourceManager::getWindow()->closeWindow();
		if (VOEngine::ResourceManager::getWindow()->isKeyPressed(VOEngine::Key::W)) VOEngine::ResourceManager::getWindow()->setWindowMode(WindowModes::windowed);
		});

	VOEngine::ResourceManager::setWhileLoopStopCondition([]() { return VOEngine::ResourceManager::getWindow()->shouldClose(); });
	VOEngine::ResourceManager::executeWhileLoop();

	VOEngine::Cleanup();
	return 0;
}


