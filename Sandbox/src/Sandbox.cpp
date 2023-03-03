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
		if (ImGui::TreeNode("Basic trees")) {
			for (const auto& unit : m_Scene->getRenderUnits()) {
				// Use SetNextItemOpen() so set the default state of a node to be open. We could
				// also use TreeNodeEx() with the ImGuiTreeNodeFlags_DefaultOpen flag to achieve the same thing!

				if (ImGui::TreeNode((void*)(intptr_t)unit.first, unit.second->Name.c_str())) {
					ImGui::Text("blah blah");
					ImGui::SameLine();
					if (ImGui::SmallButton("button")) {}
					ImGui::TreePop();
				}
			}
			ImGui::TreePop();
		}
		ImGui::End();
		ImGui::ShowDemoWindow();
	}

	void OnRender() override {
	}


	void OnStartup() override {
		m_Scene->AddUnit(UnitTypes::Quad);
		m_Scene->AddUnit(UnitTypes::Quad);
	}

};

int main() {
	ExampleApplication app;
	app.run();
	return 0;
}


