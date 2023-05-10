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
	createFrameBuffer();
}

VOEngine::OpenGLRenderer::~OpenGLRenderer() {
	//glDeleteTextures(1, &m_FrameBufferID);
	//glDeleteBuffers(1, &m_FrameBuffer);
}

void VOEngine::OpenGLRenderer::setViewport(glm::uvec2 viewport) {
	glViewport(0, 0, viewport.x, viewport.y);
}

void VOEngine::OpenGLRenderer::submitDrawCalls() {
	glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBuffer);
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	for (uint32_t i = 0; i < m_DrawCount; i++) {
		glUseProgram(m_Shader->getID());
		std::shared_ptr<VertexArray> VAO = m_VAOToDraw[i];
		VAO->Bind();
		glDrawElements(GL_TRIANGLES, (uint32_t)VAO->IndexCount, GL_UNSIGNED_INT, 0);
		VAO->Unbind();
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
}

std::shared_ptr<VOEngine::VertexArray> VOEngine::OpenGLRenderer::GenerateVertexArray() {
	std::shared_ptr<VertexArray> VAO = std::make_shared<VOEngine::OpenGLVertexArray>();
	VAO->Create();
	return VAO;
}

void VOEngine::OpenGLRenderer::createFrameBuffer() {
	glCreateFramebuffers(1, &m_FrameBuffer);
	// create a color attachment texture
	glCreateTextures(GL_TEXTURE_2D ,1, &m_FrameBufferID);
	glTextureStorage2D(m_FrameBufferID, 1, GL_RGB8, 800, 600);
	//glTextureSubImage2D(m_FrameBufferID, 0, 0, 0, 800, 600, GL_RGB8, GL_UNSIGNED_BYTE, nullptr);
	//glTextureParameteri(m_FrameBufferID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTextureParameteri(m_FrameBufferID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTextureParameteri(m_FrameBufferID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(m_FrameBufferID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glNamedFramebufferTexture(m_FrameBuffer, GL_COLOR_ATTACHMENT0, m_FrameBufferID, 0);
	// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
	uint32_t rbo;
	glCreateTextures(GL_TEXTURE_2D, 1, &rbo);
	glTextureStorage2D(rbo, 1, GL_DEPTH_COMPONENT32F, 800, 600);
	glNamedFramebufferTexture(m_FrameBuffer, GL_DEPTH_ATTACHMENT, rbo, 0);
	// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
	uint32_t error_code = glCheckNamedFramebufferStatus(m_FrameBuffer, GL_FRAMEBUFFER);
	if (error_code != GL_FRAMEBUFFER_COMPLETE)
		VO_CORE_ERROR("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");

	static const GLenum draw_buffers[]{ GL_COLOR_ATTACHMENT0 };
	glNamedFramebufferDrawBuffers(m_FrameBuffer, 1, draw_buffers);
}

