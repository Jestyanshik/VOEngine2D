#pragma once
#include "vopch.h"
#include "Texture.h"
#include "VertexArray.h"
#include "../Sound/AudioLoader.h"
#include "Core/Common/UUID.h"

namespace VOEngine {
	struct Unit {
		Texture* Texture = nullptr;
		Sound* Sound = nullptr;
		glm::vec2 Position = { 0,0 };
		glm::uvec2 Size = { 0,0 };
		glm::vec4 Color = { 0, 0, 0, 0 };
		std::vector<float> Verticies{};
		std::vector<uint32_t> Indicies{};
		std::shared_ptr<VertexArray> VAO = nullptr;
		UUID uuid;
		/*Unit(const glm::vec2& position = glm::vec2(0,0),
			const glm::uvec2& size = glm::uvec2(0,0),
			const glm::vec4& color = glm::vec4(0, 0, 0, 0)) : Position(position), Size(size), Color(color) {}*/
	};
}