#pragma once
#include "../Renderer.h"
#include "../Shader.h"
#include "Core/ResourceManager.h"


namespace VOEngine { 
	class OpenGLRenderer : public Renderer {
	public:
		std::string getVersion() override;
		OpenGLRenderer();
		~OpenGLRenderer();
		void setViewport(glm::uvec2 viewport) override;
		void submitDrawCalls() override;
		std::shared_ptr<VertexArray> GenerateVertexArray() override;
	private:
		void createFrameBuffer();
		GLuint m_FrameBuffer = 0;
	};
}
