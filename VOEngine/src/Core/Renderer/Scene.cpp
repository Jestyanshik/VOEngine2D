#include "vopch.h"
#include "Scene.h"
#include "Core/Common/Events.h"
#include "Core/Sound/OpenAL/OpenALSoundEngine.h"
#include "Core/ResourceManager.h"

VOEngine::Scene::Scene(std::shared_ptr<Framebuffer> framebuffer, const std::string& name): m_Name(name) {
	m_Viewport = framebuffer->GetSize();
	m_Framebuffer = framebuffer;
}

void VOEngine::Scene::AddUnit(UnitTypes unitType) {
	std::shared_ptr<Unit> unit = std::make_shared<Unit>();
	unit->Type = unitType;
	m_RenderUnitList.emplace(unit->uuid, unit);
	Event event{ EventType::RenderUpdate, nullptr };
	ResourceManager::GetInstance().GetEventNotifier()->GenerateEvent(event, false);
}

void VOEngine::Scene::LoadFromFile(const std::filesystem::path& path) {
	if (not std::filesystem::exists(path.string() + ".vo"))
		return;
	
	YAML::Node node = YAML::LoadFile(path.string() + ".vo");
	for (YAML::const_iterator it = node.begin(); it != node.end(); ++it) {
		m_Name = it->first.as<std::string>();
		for (YAML::const_iterator iter = node[m_Name]["Units"].begin(); iter != node[m_Name]["Units"].end(); ++iter) {
			try {
				const YAML::Node& unitNode = iter->second;
				std::shared_ptr<Unit> unit = std::make_shared<Unit>();

				unit->Type = UnitTypes::Quad;
				unit->Name = unitNode["Name"].as<std::string>();

				unit->Position.x = unitNode["Position"][0].as<float>();
				unit->Position.y = unitNode["Position"][1].as<float>();
				unit->Position.z = unitNode["Position"][2].as<float>();

				unit->Size.x = unitNode["Size"][0].as<float>();
				unit->Size.y = unitNode["Size"][1].as<float>();

				unit->Color.r = unitNode["Color"][0].as<float>();
				unit->Color.g = unitNode["Color"][1].as<float>();
				unit->Color.b = unitNode["Color"][2].as<float>();
				unit->Color.a = unitNode["Color"][3].as<float>();

				m_RenderUnitList.emplace(unit->uuid, unit);
			}
			catch (const std::exception& e) {
				VO_CORE_ERROR(e.what());
			}

		}
	}
	Event event{ EventType::RenderUpdate, nullptr };
	ResourceManager::GetInstance().GetEventNotifier()->GenerateEvent(event, false);
}

void VOEngine::Scene::SaveToFile(const std::filesystem::path& path) {
	YAML::Node node;
	for (const auto& pair : m_RenderUnitList) {
		const std::shared_ptr<Unit> unit = pair.second;
		YAML::Node unitNode;
		unitNode["Name"] = unit->Name;
		unitNode["Position"].push_back(unit->Position.x);
		unitNode["Position"].push_back(unit->Position.y);
		unitNode["Position"].push_back(unit->Position.z);
		unitNode["Size"].push_back(unit->Size.x);
		unitNode["Size"].push_back(unit->Size.y);
		unitNode["Color"].push_back(unit->Color.r);
		unitNode["Color"].push_back(unit->Color.g);
		unitNode["Color"].push_back(unit->Color.b);
		unitNode["Color"].push_back(unit->Color.a);

		node[m_Name]["Units"][(uint64_t)pair.first] = unitNode;
	}
	std::ofstream out((path.string() + ".vo").c_str());
	out << node;
}
