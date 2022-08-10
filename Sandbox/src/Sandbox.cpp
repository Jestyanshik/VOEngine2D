#include "vopch.h"
#include "VOEngine.h"



int main() {
	VOEngine::Init();
	VOEngine::ImGuiManager imgui = VOEngine::ImGuiManager();
	VOEngine::Window editorWindow = VOEngine::Window(1920, 1080, "VOEngine");
	imgui.passVOEngineWindow(&editorWindow);

	
	imgui.createWindow([]() {
		ImGui::Begin("VOEngine", NULL);
		ImGui::End();
		});
	imgui.createWindow([]() {
		ImGui::Begin("Alolololoasdsad");
		static char buf[10000];
		ImGui::InputText("Text", buf, sizeof(buf));
		ImGui::End();
		});
	while (!editorWindow.shouldClose()) {
		editorWindow.pollEvents();
		if (editorWindow.isKeyPressed(VOEngine::Key::Escape)) {
			editorWindow.closeWindow();
		}
		if (editorWindow.isKeyPressed(VOEngine::Key::W)) editorWindow.setWindowMode(WindowModes::windowed);
		imgui.render();
	}

	return 0;
}


