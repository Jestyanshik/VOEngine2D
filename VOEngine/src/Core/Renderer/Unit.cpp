#include "vopch.h"
#include "Unit.h"

void VOEngine::Unit::UpdateVertices() {
	switch (Type) {
		case VOEngine::Quad:
			this->Vertices = {
				 (this->Size.x + this->Position.x),  (this->Size.y + this->Position.y), 0.0f, //top right
				 (this->Size.x + this->Position.x), -(this->Size.y + this->Position.y), 0.0f, //bottom right
				-(this->Size.x + this->Position.x), -(this->Size.y + this->Position.y), 0.0f, //bottom left
				-(this->Size.x + this->Position.x),  (this->Size.y + this->Position.y), 0.0f  //top left
			};
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
}

void VOEngine::Unit::UpdateIndices(uint32_t offset) {
	switch (Type) {
		case VOEngine::Quad:
			this->Indices = {
				offset + 0, offset + 1, offset + 3,
				offset + 1, offset + 2, offset + 3
			};
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
}
