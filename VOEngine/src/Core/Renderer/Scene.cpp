#include "vopch.h"
#include "Scene.h"
#include "OpenGL/OpenGLRenderer.h"
#include "OpenGL/OpenGLShader.h"
#include "Core/Sound/OpenAL/OpenALSoundEngine.h"
#include "Core/ResourceManager.h"


VOEngine::Scene::Scene(glm::uvec2 viewport) : m_Viewport(viewport) {
	if (ResourceManager::getInstance().getSettings()->GetValue("Renderer") == "OpenGL") {
		m_Renderer = new OpenGLRenderer;
	}
	else {
		VO_CORE_ERROR("Renderer setting isn't correct, defaulted to OpenGL");
		ResourceManager::getInstance().getSettings()->SetValue(std::pair("Renderer", "OpenGL"));
		m_Renderer = new OpenGLRenderer;
	}
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

//Default size for object is 100 by 100 pixels
//Default color is black
//Centered in viewport
//Sound And Texture are not specified
void VOEngine::Scene::AddUnit(UnitTypes unitType) {
	std::shared_ptr<Unit> unit = std::make_shared<Unit>();
	unit->Name = "Square";
	unit->Size = { 100.0f / m_Viewport.x, 100.0f / m_Viewport.y };
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
	unit->UpdateVertices();
	unit->UpdateIndices(offset);
	unit->VAO = unit->VAO == nullptr ? m_Renderer->GenerateVertexArray() : unit->VAO;
	unit->VAO->AttachBuffers(unit->Vertices, unit->Indices,
		(offset / 4) * unit->Vertices.size(), (offset / 4) * unit->Indices.size());
	m_Renderer->drawSquare(unit, !isUnique);
	m_RenderUnitList.emplace(unit->uuid, unit);
}
