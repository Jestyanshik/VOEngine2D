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
		glm::vec2 Size = { 0,0 };
		glm::vec4 Color = { 1, 1, 1, 0 };
		std::vector<float> Vertices{};
		std::vector<uint32_t> Indices{};
		std::shared_ptr<VertexArray> VAO = nullptr;
		std::string Name;
		uint32_t Offset;
		UnitTypes Type;
		UUID uuid;
		void UpdateVertices();
		void UpdateIndices(uint32_t offset);
		static Unit* fromString(const std::string& unitStr);
		std::string toString();
		YAML::Node toNode();
	private:
		glm::vec3 m_NormalizedPosition;
		glm::vec2 m_NormalizedSize;
	};
}