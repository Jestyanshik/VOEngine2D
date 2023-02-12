#include "vopch.h"
#include "OpenGLRenderer.h"
#include "glad/glad.h"
#include "glm.hpp"

#include "Core/Window/Window.h"


void VOEngine::OpenGLRenderer::doFill(color color) {
	glClearColor(color.x, color.y, color.z, color.a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void VOEngine::OpenGLRenderer::render() {
	Renderer::render();
}



const char* VOEngine::OpenGLRenderer::getVersion() {
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

	glViewport(0, 0, window->getWidth(), window->getHeight());
}


