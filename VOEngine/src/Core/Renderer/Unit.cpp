#include "vopch.h"
#include "Unit.h"
#include "Core/ResourceManager.h"

void VOEngine::Unit::UpdateVertices() {
	if (abs(Size.x) > 1.0 or abs(Size.y) > 1.0) {
		m_NormalizedSize.x = Size.x / (float)ResourceManager::getInstance().getScene()->getViewport().x;
		m_NormalizedSize.y = Size.y / (float)ResourceManager::getInstance().getScene()->getViewport().y;
	}
	if (abs(Position.x) > 1.0 or abs(Position.y) > 1.0) {
		m_NormalizedPosition.x = Position.x / ResourceManager::getInstance().getScene()->getViewport().x;
		m_NormalizedPosition.y = Position.y / ResourceManager::getInstance().getScene()->getViewport().y;
	}
	switch (Type) {
		case VOEngine::Quad: {
			float w = m_NormalizedSize.x;
			float h = m_NormalizedSize.y;
			float x = m_NormalizedPosition.x;
			float y = m_NormalizedPosition.y;
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
	this->VAO->AttachIndexBuffer(Indices, Offset * Indices.size());
}
