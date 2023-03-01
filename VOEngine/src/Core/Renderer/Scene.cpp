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
	if (unitType == UnitTypes::Square) {
		std::shared_ptr<Unit> square = std::make_shared<Unit>();
		glm::vec2 size = {100.0f / m_Viewport.x, 100.0f / m_Viewport.y};
		square->Verticies = {
				 (size.x + 0.0f),  (size.y + 0.0f), 0.0f, //top right
				 (size.x + 0.0f), -(size.y + 0.0f), 0.0f, //bottom right
				-(size.x + 0.0f), -(size.y + 0.0f), 0.0f, //bottom left
				-(size.x + 0.0f),  (size.y + 0.0f), 0.0f  //top left
		};
		square->Indicies = {
			0, 1, 3,
			1, 2, 3
		};
		square->VAO = m_Renderer->GenerateVertexArray(square->Verticies, square->Indicies);
		m_RenderUnitList.emplace(square->uuid, square);
	}
		

}
