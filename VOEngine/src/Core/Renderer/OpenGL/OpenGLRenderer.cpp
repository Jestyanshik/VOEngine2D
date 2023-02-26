#include "vopch.h"
#include "OpenGLRenderer.h"
#include "Core/Window/Window.h"
#include "OpenGLShader.h"

std::string VOEngine::OpenGLRenderer::getVersion() {
	return (char*)glGetString(GL_VERSION);
}

VOEngine::OpenGLRenderer::OpenGLRenderer() {
	Window* window = ResourceManager::getWindow();
	if (window->getName() == "GLFW Window") {
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			VO_CORE_ERROR("OpenGL couldn't initialize");
		else
			VO_CORE_INFO("OpenGL succesfully initialized");
	}
	VO_CORE_INFO("Current OpenGL version is {}", getVersion());
	m_Shader = new OpenGLShader("../VOEngine/src/Core/Renderer/Shaders/vertexShader.glsl", "../VOEngine/src/Core/Renderer/Shaders/fragmentShader.glsl");
}

void VOEngine::OpenGLRenderer::setViewport(glm::uvec2 viewport) {
	glViewport(0, 0, viewport.x, viewport.y);
}

void VOEngine::OpenGLRenderer::renderSquare(const Unit& unit) {

}

void VOEngine::OpenGLRenderer::render() {

}

