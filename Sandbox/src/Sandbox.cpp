#include "vopch.h"
#include "VOEngine.h"

using namespace VOEngine;

class ExampleApplication : public Application {
public:
	void OnImGuiRender() override {
		ImGui::Begin("Main Window");
		if (ImGui::Button("Cool button")) {
			ImGui::Text("123");
		}
		ImGui::End();
	}

	void OnRender() override {
	}


	void OnStartup() override {
	}

};

int main() {
	ExampleApplication app;
	app.run();
	return 0;
}


