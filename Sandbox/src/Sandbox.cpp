#include "vopch.h"
#include "VOEngine.h"

using namespace VOEngine;

class ExampleApplication : public Application {
public:
	void OnImGuiRender(int64_t deltaTime) override {
		ImGui::Begin("Controls");
		if (ImGui::Button("Add Square")) {
			m_Scene->AddUnit(UnitTypes::Quad);
		}

		if (m_Scene != nullptr) {
			for (const auto& unit : m_Scene->GetRenderUnits()) {
				if (ImGui::TreeNode((void*)(intptr_t)unit.first, unit.second->Name.c_str())) {
					ImGui::DragFloat3("Position", &unit.second->Position[0], 0.025f, -FLT_MAX / INT_MIN, FLT_MAX / INT_MAX);
					ImGui::DragFloat2("Size", &unit.second->Size.x, 0.025f, 0.0f, FLT_MAX / INT_MAX);
					ImGui::ColorEdit4("Color", &unit.second->Color.x);
					ImGui::TreePop();
				}
			}
		}

		ImGui::End();
		ImGui::Begin(m_Scene->GetName().data());
		glm::uvec2 size = (glm::vec2)ImGui::GetContentRegionAvail();
		if (size != m_Size) {
			m_Size = size;
			ResizeEventInfo info{ size };
			m_EventNotifier->GenerateEvent(Event{ EventType::Resize, (void*)&info });
		}
		ImGui::Image((ImTextureID)m_Scene->GetFramebuffer()->GetTextureID(),
			(glm::vec2)m_Scene->GetFramebuffer()->GetSize());
		ImGui::End();

		ImGui::Begin("Debug info");
		ImGui::Text(std::format("Frametime: {} ms", (deltaTime / 10e6)).c_str());
		ImGui::Text(std::format("FPS: {}", 1.0 / (double)(deltaTime * 10e-9)).c_str());
		ImGui::End();
		
		if (m_Window->IsKeyPressed(Key::L)) {
			m_Window->SetWindowMode(WindowModes::Windowed);
		}

		ImGui::ShowDemoWindow();
	}

	void OnRender(int64_t deltaTime) override {

	}

	void OnStartup() override {
		auto fb = std::make_shared<Framebuffer>(800, 600);
		CreateScene(fb, "Unkown Scene");
		m_Scene->LoadFromFile(m_Scene->GetName());
		m_ShortcutManager->AddShortcut(Key::Escape, [this]() { m_Window->SetShouldClose(true); });
		//CreateShortcut(Key::Escape(), []() { m_Window->SetWindowMode(WindowModes::Windowed)});
		SetScene(m_Scene);
	}

	void OnClose() override {
		m_Scene->SaveToFile(m_Scene->GetName());
	}

private:
	glm::uvec2 m_Size{0, 0};
};

int main() {
	ExampleApplication app;
	app.Run();
	return 0;
}


