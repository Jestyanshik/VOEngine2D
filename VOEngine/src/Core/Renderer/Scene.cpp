#include "vopch.h"
#include "Scene.h"
#include "OpenGL/OpenGLRenderer.h"
#include "OpenGL/OpenGLShader.h"
#include "Core/Sound/OpenAL/OpenALSoundEngine.h"
#include "Core/ResourceManager.h"


VOEngine::Scene::Scene(glm::uvec2 viewport) : m_Viewport(viewport) {
	if (ResourceManager::getSettings()->GetValue("Renderer") == "OpenGL") {
		m_Renderer = new OpenGLRenderer;
	}
	if (ResourceManager::getSettings()->GetValue("SoundEngine") == "OpenAL") {
		m_SoundEngine = new OpenALSoundEngine;
	}
	m_Renderer->setViewport(m_Viewport);
}
