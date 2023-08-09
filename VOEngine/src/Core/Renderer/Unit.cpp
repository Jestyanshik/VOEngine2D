#include "vopch.h"
#include "Unit.h"
#include "Core/ResourceManager.h"

void VOEngine::Unit::UpdateVertices() {
	switch (Type) {
		case VOEngine::Quad: {
			float w = Size.x;
			float h = Size.y;
			float x = Position.x;
			float y = Position.y;
			Vertices = {
				 x + w,  y + h, 0.0f, Color.x, Color.y, Color.z, Color.w, 0.0, 0.0, //top right
				 x + w,  y - h, 0.0f, Color.x, Color.y, Color.z, Color.w, 0.0, 0.0, //bottom right
				 x - w,  y - h, 0.0f, Color.x, Color.y, Color.z, Color.w, 0.0, 0.0, //bottom left
				 x - w,  y + h, 0.0f, Color.x, Color.y, Color.z, Color.w, 0.0, 0.0  //top left
			};
			break;
		}
			
		case VOEngine::Triangle:
			break;
		case VOEngine::Circle:
			break;
		case VOEngine::Polygon:
			break;
		default:
			break;
	}
	this->VAO->AttachVertexBuffer(Vertices, Offset * Vertices.size());
}

std::vector<uint32_t> VOEngine::Unit::UpdateIndices(uint32_t offset) {
	std::vector<uint32_t> result;
	switch (Type) {
	case VOEngine::Quad:
		offset *= 4;
		result = {
			offset + 0, offset + 1, offset + 3,
			offset + 1, offset + 2, offset + 3
		};
		IndicesCount = 6;
		break;
	case VOEngine::Triangle:
		break;
	case VOEngine::Circle:
		break;
	case VOEngine::Polygon:
		break;
	default:
		break;
	}
	return result;
}
