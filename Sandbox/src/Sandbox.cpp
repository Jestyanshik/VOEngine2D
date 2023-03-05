#include "vopch.h"
#include "VOEngine.h"

using namespace VOEngine;

class ExampleApplication : public Application {
public:
	void OnImGuiRender() override {
		ImGui::Begin("Main Window");
		if (ImGui::Button("Add Square")) {
			m_Scene->AddUnit(UnitTypes::Quad);
		}
		for (const auto& unit : m_Scene->getRenderUnits()) {
			if (ImGui::TreeNode((void*)(intptr_t)unit.first, unit.second->Name.c_str())) {
				ImGui::DragFloat3("Position", &unit.second->Position[0], 1.f, -FLT_MAX / INT_MIN, FLT_MAX / INT_MAX);
				ImGui::DragFloat2("Size", &unit.second->Size.x, 1.f, 0.0f, FLT_MAX / INT_MAX);
				ImGui::ColorEdit4("Color", &unit.second->Color.x);
				ImGui::TreePop();
			}
		}
		ImGui::End();
		ImGui::ShowDemoWindow();
	}

	void OnRender() override {}


	void OnStartup() override {}

};

int main() {
	ExampleApplication app;
	app.run();
	return 0;
}


