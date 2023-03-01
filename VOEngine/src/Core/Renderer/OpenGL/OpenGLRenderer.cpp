#include "vopch.h"
#include "Core/Window/Window.h"
#include "OpenGLRenderer.h"
#include "OpenGLShader.h"
#include "OpenGLVertexArray.h"

std::string VOEngine::OpenGLRenderer::getVersion() {
	return (char*)glGetString(GL_VERSION);
}

VOEngine::OpenGLRenderer::OpenGLRenderer() {
	std::shared_ptr<Window> window = ResourceManager::getInstance().getWindow();
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

void VOEngine::OpenGLRenderer::drawSquare(const Unit& unit) {

}

void VOEngine::OpenGLRenderer::submitDrawCalls(VertexArray* VAO) {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(m_Shader->getID());
	VAO->Bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	VAO->Unbind();
}

std::shared_ptr<VOEngine::VertexArray> VOEngine::OpenGLRenderer::GenerateVertexArray(const std::vector<float>& VBO, const std::vector<uint32_t>& IBO) {
	std::shared_ptr<VertexArray> VAO = std::make_shared<VOEngine::OpenGLVertexArray>();
	VAO->AttachBuffers(VBO, IBO);
	return VAO;
}

