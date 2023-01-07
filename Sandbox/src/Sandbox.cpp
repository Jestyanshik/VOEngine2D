#include "vopch.h"
#include "VOEngine.h"

using namespace VOEngine;

class Application {
public:
	Application(){
		ResourceManager::Init();
	}
	~Application() {
		ResourceManager::Cleanup();
	}
	void run() {
		BeforeRun();
		ResourceManager::Run();
	}
	void BeforeRun() {
		ResourceManager::addWindow([]() {
		ImGui::Begin("Main Window");
		if (ImGui::Button("Cool button")) {
			ImGui::Text("hahas");
		}
		ImGui::End();
		});
	}
};

int main() {
	Application app;
	app.run();
	return 0;
}


