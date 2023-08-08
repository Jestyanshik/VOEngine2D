#include "vopch.h"
#include "Framebuffer.h"
#include "Core/ResourceManager.h"

VOEngine::Framebuffer::Framebuffer(uint32_t width, uint32_t height, const std::string& imGuiWindowName) : m_ImGuiWindowName(imGuiWindowName) {
	m_Size = { width, height };

	glCreateFramebuffers(1, &m_FramebufferID);
	// create a color attachment texture
	glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);
	glTextureStorage2D(m_TextureID, 1, GL_RGB8, width, height);

	glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glNamedFramebufferTexture(m_TextureID, GL_COLOR_ATTACHMENT0, m_TextureID, 0);

	glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthBufferID);
	glTextureStorage2D(m_DepthBufferID, 1, GL_DEPTH_COMPONENT32F, width, height);
	glNamedFramebufferTexture(m_FramebufferID, GL_DEPTH_ATTACHMENT, m_DepthBufferID, 0);

	uint32_t error_code = glCheckNamedFramebufferStatus(m_FramebufferID, GL_FRAMEBUFFER);
	if (error_code != GL_FRAMEBUFFER_COMPLETE)
		VO_CORE_ERROR("Framebuffer is not complete!");

	static const uint32_t draw_buffers[]{ GL_COLOR_ATTACHMENT0 };
	glNamedFramebufferDrawBuffers(m_FramebufferID, 1, draw_buffers);
}

VOEngine::Framebuffer::~Framebuffer() {
	const uint32_t textures[]{ m_DepthBufferID, m_TextureID };
	glDeleteTextures(2, textures);
	glDeleteFramebuffers(1, &m_FramebufferID);
}

void VOEngine::Framebuffer::BeginFrame() {
	glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferID);
	ImGui::Begin(m_ImGuiWindowName.c_str());
	glm::uvec2 size = (glm::vec2)ImGui::GetContentRegionAvail();
	if (size != m_Size) {
		ResizeEventInfo info{ size };
		ResourceManager::GetInstance().GetEventNotifier()->GenerateEvent(Event{ EventType::Resize, (void*)&info});
	}
}

void VOEngine::Framebuffer::EndFrame() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	ImGui::Image((ImTextureID)m_TextureID, (glm::vec2)m_Size);
	ImGui::End();
}

void VOEngine::Framebuffer::Resize(glm::uvec2 size) {
	const uint32_t textures[]{ m_DepthBufferID, m_TextureID };
	glDeleteTextures(2, textures);
	glDeleteFramebuffers(1, &m_FramebufferID);

	m_Size = size;

	glCreateFramebuffers(1, &m_FramebufferID);
	// create a color attachment texture
	glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);
	glTextureStorage2D(m_TextureID, 1, GL_RGB8, size.x, size.y);

	glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glNamedFramebufferTexture(m_TextureID, GL_COLOR_ATTACHMENT0, m_TextureID, 0);


	glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthBufferID);
	glTextureStorage2D(m_DepthBufferID, 1, GL_DEPTH_COMPONENT32F, size.x, size.y);
	glNamedFramebufferTexture(m_FramebufferID, GL_DEPTH_ATTACHMENT, m_DepthBufferID, 0);

	uint32_t error_code = glCheckNamedFramebufferStatus(m_FramebufferID, GL_FRAMEBUFFER);
	if (error_code != GL_FRAMEBUFFER_COMPLETE)
		VO_CORE_ERROR("Framebuffer is not complete!");

	static const uint32_t draw_buffers[]{ GL_COLOR_ATTACHMENT0 };
	glNamedFramebufferDrawBuffers(m_FramebufferID, 1, draw_buffers);

}
