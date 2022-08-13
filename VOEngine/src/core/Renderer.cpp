#include "vopch.h"
#include "Renderer.h"
#include "glad/glad.h"
#include "glm.hpp"

VOEngine::Renderer::Renderer() {
	m_RenderLayer = {};
}

VOEngine::Renderer::~Renderer() {

}

void VOEngine::Renderer::render() {

}

void VOEngine::Renderer::setViewport(int x, int y, int width, int height) {
	glViewport(x, y, width, height);
}

void VOEngine::Renderer::setViewport(glm::vec2 pos, glm::ivec2 size) {
	glViewport(pos.x, pos.y, size.x, size.y);
}

void VOEngine::Renderer::fillWindow(glm::vec4 color) {
	glClearColor(color.x, color.y, color.z, color.a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void VOEngine::Renderer::fillWindow(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}


