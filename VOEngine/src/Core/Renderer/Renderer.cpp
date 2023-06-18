#include "vopch.h"
#include "Renderer.h"
#include "../ResourceManager.h"

VOEngine::Renderer::Renderer() {
	std::shared_ptr<Window> window = ResourceManager::GetInstance().getWindow();
	if (window->getName() == "GLFW Window") {
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			VO_CORE_ERROR("OpenGL couldn't initialize");
		else
			VO_CORE_INFO("OpenGL succesfully initialized");
	}
	VO_CORE_INFO("Current OpenGL version is {}", getVersion());
	m_Shader = new Shader("res\\shaders\\vertexShader.glsl", "res\\shaders\\fragmentShader.glsl");
}

std::string VOEngine::Renderer::getVersion() {
	return (char*)glGetString(GL_VERSION);
}

std::shared_ptr<VOEngine::VertexArray> VOEngine::Renderer::GenerateVertexArray() {
	std::shared_ptr<VertexArray> VAO = std::make_shared<VOEngine::VertexArray>();
	VAO->Create();
	return VAO;
}

void VOEngine::Renderer::SetViewport(glm::uvec2 viewport) {
	glViewport(0, 0, viewport.x, viewport.y);
}

void VOEngine::Renderer::DrawElements(VertexArray* vao, uint32_t indices) {
	glUseProgram(m_Shader->getID());
	vao->Bind();
	glDrawElements(GL_TRIANGLES, indices, GL_UNSIGNED_INT, 0);
	vao->Unbind();
	glUseProgram(0);
}

void VOEngine::Renderer::SubmitDrawCalls() {
	for (uint32_t i = 0; i < m_DrawCount; i++) {
		glUseProgram(m_Shader->getID());
		std::shared_ptr<VertexArray> VAO = m_VAOToDraw[i];
		VAO->Bind();
		glDrawElements(GL_TRIANGLES, (uint32_t)VAO->IndexCount , GL_UNSIGNED_INT, 0);
		VAO->Unbind();
	}
}

void VOEngine::Renderer::Clear(glm::vec4 color) {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
}
