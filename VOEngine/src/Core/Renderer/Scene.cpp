#include "vopch.h"
#include "Scene.h"
#include "Core/Sound/OpenAL/OpenALSoundEngine.h"
#include "Core/ResourceManager.h"


VOEngine::Scene::Scene(const glm::uvec2& viewport, const std::string& name) : m_Viewport(viewport), m_Name(name) {
	if (ResourceManager::GetInstance().getSettings()->GetValue("SoundEngine") == "OpenAL") {
		m_SoundEngine = new OpenALSoundEngine;
	}
	else {
		VO_CORE_ERROR("SoundEngine setting isn't correct, defaulted to OpenAL");
		ResourceManager::GetInstance().getSettings()->SetValue(std::pair("SoundEngine", "OpenAL"));
		m_SoundEngine = new OpenALSoundEngine;
	}
}

VOEngine::Scene::Scene(std::unique_ptr<Framebuffer> framebuffer, const std::string& name): m_Name(name) {
	if (ResourceManager::GetInstance().getSettings()->GetValue("SoundEngine") == "OpenAL") {
		m_SoundEngine = new OpenALSoundEngine;
	}
	else {
		VO_CORE_ERROR("SoundEngine setting isn't correct, defaulted to OpenAL");
		ResourceManager::GetInstance().getSettings()->SetValue(std::pair("SoundEngine", "OpenAL"));
		m_SoundEngine = new OpenALSoundEngine;
	}
}

//Default size for object is 100 by 100 pixels
//Default color is black
//Centered in viewport
//Sound And Texture are not specified
void VOEngine::Scene::AddUnit(UnitTypes unitType) {
	std::shared_ptr<Unit> unit = std::make_shared<Unit>();
	unit->Name = "Empty unit";
	unit->Size = { 0.1f, 0.1f };
	unit->Type = unitType;
	m_RenderUnitList.emplace(unit->uuid, unit);
	Event event{ UUID(), SceneChange };
	ResourceManager::GetInstance().GetEvents().push_back(event);
}

void VOEngine::Scene::AddUnit(Unit* punit) {
	std::shared_ptr<Unit> unit(punit);
	m_RenderUnitList.emplace(unit->uuid, unit);
	Event event{ UUID(), SceneChange };
	ResourceManager::GetInstance().GetEvents().push_back(event);
}

VOEngine::Scene* VOEngine::Scene::loadFromString(std::unique_ptr<Framebuffer> framebuffer, const std::string& sceneString) {
	YAML::Node node = YAML::Load(sceneString);
	std::string sceneName = "Unknown scene";
	for (YAML::const_iterator it = node.begin(); it != node.end(); ++it) {
		sceneName = it->first.as<std::string>();
		Scene* instance = new Scene(move(framebuffer), sceneName);
		for (YAML::const_iterator iter = node[sceneName]["Units"].begin(); iter != node[sceneName]["Units"].end(); ++iter) {
			std::stringstream ss;
			ss << iter->second;

			Unit* unit = Unit::fromString(ss.str());
			instance->AddUnit(unit);
		}
		return instance;
	}
	return new Scene(move(framebuffer), sceneName);
}


std::string VOEngine::Scene::toString() {
	YAML::Node node;
	for (const auto& pair : m_RenderUnitList) {
		const std::shared_ptr<Unit> unit = pair.second;
		node[m_Name]["Units"][(uint64_t)pair.first] = unit->toNode();
	}
	std::stringstream out;
	out << node;

	return out.str();
}
