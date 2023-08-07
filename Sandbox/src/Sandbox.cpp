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

		if (m_Scene != nullptr) {
			for (const auto& unit : m_Scene->GetRenderUnits()) {
				if (ImGui::TreeNode((void*)(intptr_t)unit.first, unit.second->Name.c_str())) {
					ImGui::DragFloat3("Position", &unit.second->Position[0], 0.1f, -FLT_MAX / INT_MIN, FLT_MAX / INT_MAX);
					ImGui::DragFloat2("Size", &unit.second->Size.x, 0.1f, 0.0f, FLT_MAX / INT_MAX);
					ImGui::ColorEdit4("Color", &unit.second->Color.x);
					ImGui::TreePop();
				}
			}
		}
		ImGui::End();
		ImGui::ShowDemoWindow();
	}

	void OnRender() override {
		RenderScene(m_Scene);
	}


	void OnStartup() override {
		auto fb = std::make_unique<Framebuffer>(800,600, "Scene");
		CreateScene(move(fb), "Unkown Scene");
		m_Scene->LoadFromFile("scene.vo");
	}

	void OnClose() override {
		m_Scene->SaveToFile("scene.vo");
	}

private:

};

int main() {
	ExampleApplication app;
	app.run();
	return 0;
}


