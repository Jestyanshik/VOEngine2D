#include "vopch.h"
#include "VOEngine.h"



int main() {
	VOEngine::Init();
	VOEngine::ImGuiManager imgui = VOEngine::ImGuiManager();
	VOEngine::Window editorWindow = VOEngine::Window(1920, 1080, "VOEngine");
	imgui.passVOEngineWindow(&editorWindow);

	imgui.createWindow([]() {
		ImGui::Begin("Hello");
		ImGui::End();
		});
	imgui.createWindow([]() {

		ImGui::Begin("Alolololoasdsad");
		ImGui::End();
		});
	while (!editorWindow.shouldClose()) {
		editorWindow.pollEvents();
		if (editorWindow.isKeyPressed(VOEngine::Key::Escape)) {
			editorWindow.closeWindow();
		}
		
		imgui.render();
	}

	return 0;
}


