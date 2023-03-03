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
		glm::vec2 Size = { 0,0 };
		glm::vec4 Color = { 0, 0, 0, 0 };
		std::vector<float> Vertices{};
		std::vector<uint32_t> Indices{};
		std::shared_ptr<VertexArray> VAO = nullptr;
		std::string Name;
		UnitTypes Type;
		UUID uuid;
		void UpdateVertices();
		void UpdateIndices(uint32_t offset);
	};
}