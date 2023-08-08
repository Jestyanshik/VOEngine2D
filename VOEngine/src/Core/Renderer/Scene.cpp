#include "vopch.h"
#include "Scene.h"
#include "Core/Common/Events.h"
#include "Core/Sound/OpenAL/OpenALSoundEngine.h"
#include "Core/ResourceManager.h"

VOEngine::Scene::Scene(std::unique_ptr<Framebuffer> framebuffer, const std::string& name): m_Name(name) {
	m_Viewport = framebuffer->GetSize();
}

void VOEngine::Scene::AddUnit(UnitTypes unitType) {
	std::shared_ptr<Unit> unit = std::make_shared<Unit>();
	unit->Name = "Empty unit";
	unit->Size = { 0.1f, 0.1f };
	unit->Type = unitType;
	m_RenderUnitList.emplace(unit->uuid, unit);
	Event event{ EventType::RenderUpdate, nullptr };
	ResourceManager::GetInstance().GetEventNotifier()->GenerateEvent(event);
}

void VOEngine::Scene::AddUnit(Unit* punit) {
	std::shared_ptr<Unit> unit(punit);
	m_RenderUnitList.emplace(unit->uuid, unit);
	Event event{ EventType::RenderUpdate, nullptr };
	ResourceManager::GetInstance().GetEventNotifier()->GenerateEvent(event);
}

void VOEngine::Scene::LoadFromFile(const std::filesystem::path& path) {
	YAML::Node node = YAML::LoadFile(path.string());
	for (YAML::const_iterator it = node.begin(); it != node.end(); ++it) {
		m_Name = it->first.as<std::string>();
		for (YAML::const_iterator iter = node[m_Name]["Units"].begin(); iter != node[m_Name]["Units"].end(); ++iter) {
			std::stringstream ss;
			ss << iter->second;
			
			Unit* unit = Unit::FromString(ss.str());
			AddUnit(unit);
		}
	}
}

void VOEngine::Scene::SaveToFile(const std::filesystem::path& path) {
	YAML::Node node;
	for (const auto& pair : m_RenderUnitList) {
		const std::shared_ptr<Unit> unit = pair.second;
		node[m_Name]["Units"][(uint64_t)pair.first] = unit->toNode();
	}
	std::fstream out{path};
	out << node;
}
