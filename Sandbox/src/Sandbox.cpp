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
			for (const auto& unit : m_Scene->getRenderUnits()) {
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

	void OnRender() override {}


	void OnStartup() override {
		constexpr auto read_size = std::size_t(4096);
		auto stream = std::ifstream("scene.vo");
		stream.exceptions(std::ios_base::badbit);

		auto out = std::string();
		auto buf = std::string(read_size, '\0');
		while (stream.read(&buf[0], read_size)) {
			out.append(buf, 0, stream.gcount());
		}
		out.append(buf, 0, stream.gcount());

		auto fb = std::make_unique<Framebuffer>(800,600, "Scene");
		m_SceneID = loadSceneFromString(move(fb), out);
	}

	void OnClose() override {
		std::string scene = m_Scenes[m_SceneID]->toString();
		std::ofstream of("scene.vo");
		of << scene;
	}

private:
	VOEngine::UUID m_SceneID;

};

int main() {
	ExampleApplication app;
	app.run();
	return 0;
}


