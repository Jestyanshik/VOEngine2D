#pragma once
#include "Renderer.h"
#include "Scene.h"

namespace VOEngine {
	class SceneRenderer {
	public:
		SceneRenderer();
		~SceneRenderer() = default;

		void SetScene(std::shared_ptr<Scene> scene);
		void Render();
		void Resize(glm::uvec2 size);
		void UpdateBuffers();
	private:
		std::shared_ptr<VertexArray> CreateUnitVAO(std::shared_ptr<Unit> unit);
		VertexArrayBuilder m_Builder{};
		std::shared_ptr<Scene> m_Scene;
		std::shared_ptr<Renderer> m_Renderer;
		std::shared_ptr<Framebuffer> m_Framebuffer;
		std::vector<std::shared_ptr<VertexArray>> m_VertexArrays{};
		uint32_t m_IndicesCount = 0;
	};
}