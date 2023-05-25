#include "vopch.h"
#include "Scene.h"
#include "Core/Sound/OpenAL/OpenALSoundEngine.h"
#include "Core/ResourceManager.h"


VOEngine::Scene::Scene(const glm::uvec2& viewport, const std::string& name) : m_Viewport(viewport), m_Name(name) {
	m_Renderer = std::make_unique<Renderer>();

	if (ResourceManager::getInstance().getSettings()->GetValue("SoundEngine") == "OpenAL") {
		m_SoundEngine = new OpenALSoundEngine;
	}
	else {
		VO_CORE_ERROR("SoundEngine setting isn't correct, defaulted to OpenAL");
		ResourceManager::getInstance().getSettings()->SetValue(std::pair("SoundEngine", "OpenAL"));
		m_SoundEngine = new OpenALSoundEngine;
	}
	m_Renderer->setViewport(m_Viewport);
}

VOEngine::Scene::Scene(std::unique_ptr<Framebuffer> framebuffer, const std::string& name): m_Name(name) {
	m_Framebuffer = std::move(framebuffer);
	m_Renderer = std::make_unique<Renderer>();

	if (ResourceManager::getInstance().getSettings()->GetValue("SoundEngine") == "OpenAL") {
		m_SoundEngine = new OpenALSoundEngine;
	}
	else {
		VO_CORE_ERROR("SoundEngine setting isn't correct, defaulted to OpenAL");
		ResourceManager::getInstance().getSettings()->SetValue(std::pair("SoundEngine", "OpenAL"));
		m_SoundEngine = new OpenALSoundEngine;
	}
	m_Renderer->setViewport(m_Framebuffer->getSize());
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
	bool isUnique = m_UnitTypes.find(unitType) == m_UnitTypes.end();
	uint32_t offset = 0;
	if (isUnique) {
		m_UnitTypes.insert(unitType);
	}
	else {
		offset = (uint32_t)m_RenderUnitList.size() * 4;
		for (const auto& _unit : m_RenderUnitList) {
			if (_unit.second->Type == unit->Type) {
				unit->VAO = _unit.second->VAO;
				break;
			}
		}
	}
	unit->Offset = offset / 4;
	unit->VAO = unit->VAO == nullptr ? m_Renderer->GenerateVertexArray() : unit->VAO;
	unit->UpdateVertices();
	unit->UpdateIndices(offset);
	m_Renderer->drawSquare(unit, !isUnique);
	m_RenderUnitList.emplace(unit->uuid, unit);
}

void VOEngine::Scene::AddUnit(Unit* punit) {
	std::shared_ptr<Unit> unit(punit);
	bool isUnique = m_UnitTypes.find(UnitTypes::Quad) == m_UnitTypes.end();
	uint32_t offset = 0;
	if (isUnique) {
		m_UnitTypes.insert(UnitTypes::Quad);
	}
	else {
		offset = (uint32_t)m_RenderUnitList.size() * 4;
		for (const auto& _unit : m_RenderUnitList) {
			if (_unit.second->Type == unit->Type) {
				unit->VAO = _unit.second->VAO;
				break;
			}
		}
	}
	unit->Offset = offset / 4;
	unit->VAO = unit->VAO == nullptr ? m_Renderer->GenerateVertexArray() : unit->VAO;
	unit->UpdateVertices();
	unit->UpdateIndices(offset);
	m_Renderer->drawSquare(unit, !isUnique);
	m_RenderUnitList.emplace(unit->uuid, unit);
}

VOEngine::Scene* VOEngine::Scene::loadFromString(std::unique_ptr<Framebuffer> framebuffer, const std::string& sceneString) {
	YAML::Node node = YAML::Load(sceneString);

	Scene* instance = new Scene(move(framebuffer), node["Name"].as<std::string>());
	for (YAML::const_iterator it = node["Units"].begin(); it != node["Units"].end(); ++it) {
		std::stringstream ss;
		ss << it->second;

		Unit* unit = Unit::fromString(ss.str());
		instance->AddUnit(unit);
	}
	return instance;
}


void VOEngine::Scene::render() {
	m_Renderer->clear({ 0,0,0,1 });

	if (m_Framebuffer != nullptr) {
		std::string imGuiWindowName = m_Framebuffer->getImGuiWindowName();
		ImGui::Begin(imGuiWindowName.c_str());
		if (m_Framebuffer->onImGuiWindow()) {
			glm::uvec2 size = (glm::vec2)ImGui::GetContentRegionAvail();
			if (size != m_Framebuffer->getSize()) {
				resize(size);
			}
		}
		m_Framebuffer->beginFrame();
	}
	m_Renderer->clear({ 0,0,0,1 });
	m_Renderer->submitDrawCalls();

	if (m_Framebuffer != nullptr) {
		m_Framebuffer->endFrame();
		//m_Renderer->clear({ 0,0,0,1 });
		ImGui::Image((ImTextureID)m_Framebuffer->getTextureID(), (glm::vec2)m_Framebuffer->getSize());
		ImGui::End();
	}
}


std::string VOEngine::Scene::toString() {
	YAML::Node node;
	node["Name"] = m_Name;
	for (const auto& pair : m_RenderUnitList) {
		const std::shared_ptr<Unit> unit = pair.second;
		node["Units"][(uint64_t)pair.first] = unit->toNode();
	}

	std::stringstream out;
	out << node;

	return out.str();
}
