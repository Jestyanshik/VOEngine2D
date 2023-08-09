#pragma once
#include "vopch.h"
#include "Texture.h"
#include "VertexArray.h"
#include "../Sound/AudioLoader.h"
#include "Core/Common/UUID.h"

namespace VOEngine {
	struct Unit {
		std::shared_ptr<Texture> Texture = nullptr;
		std::shared_ptr<Sound> Sound = nullptr;
		glm::vec3 Position = { 0,0,0 };
		glm::vec2 Size = { 0.1f, 0.1f };
		glm::vec4 Color = { 1, 1, 1, 0 };
		std::vector<float> Vertices{};
		uint32_t IndicesCount = 0;
		std::shared_ptr<VertexArray> VAO = nullptr;
		std::string Name = "Empty unit";
		uint32_t Offset;
		UnitTypes Type;
		UUID uuid;
		void UpdateVertices();
		std::vector<uint32_t> UpdateIndices(uint32_t offset);
	};
}