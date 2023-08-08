#pragma once

namespace VOEngine {
	class Framebuffer {
	public:
		Framebuffer(uint32_t width, uint32_t height, const std::string& imGuiWindowName);
		~Framebuffer();
		//Constructor that takes in imgui control
		void BeginFrame();
		void EndFrame();
		std::string GetImGuiWindowName() const { return m_ImGuiWindowName; };
		void Resize(glm::uvec2 size);
		glm::uvec2 GetSize() { return m_Size; };
		uint32_t GetTextureID() { return m_TextureID; };
	private:
		uint32_t m_TextureID = 0; //Texture on which scene is rendered to
		uint32_t m_FramebufferID = 0; 
		uint32_t m_DepthBufferID = 0;
		std::string m_ImGuiWindowName = ""; // optional
		glm::uvec2 m_Size;
	};
}