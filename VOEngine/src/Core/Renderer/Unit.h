#pragma once
#include "vopch.h"
#include "Texture.h"
#include "../Sound/AudioLoader.h"
#include "Core/Common/UUID.h"

namespace VOEngine {
	enum class ShapeTypes {
		Square = 0, Circle = 1, Triangle = 2,
	};

	struct Unit {
		Texture* Texture = nullptr;
		Sound* Sound = nullptr;
		glm::vec2 Position;
		glm::uvec2 Size;
		glm::vec4 Color;
		UUID uuid;
		ShapeTypes shapeType = ShapeTypes::Square;
		Unit(const glm::vec2& position = glm::vec2(0,0),
			const glm::uvec2& size = glm::uvec2(0,0),
			const glm::vec4& color = glm::vec4(0, 0, 0, 0)) : Position(position), Size(size), Color(color) {}
	};
}