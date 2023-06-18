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

VOEngine::Unit* VOEngine::Unit::fromString(const std::string& unitStr) {
	YAML::Node node = YAML::Load(unitStr);
	Unit* instance = new Unit;

	instance->Type = UnitTypes::Quad;
	instance->Name = node["Name"].as<std::string>();

	instance->Position.x = node["Position"][0].as<float>();
	instance->Position.y = node["Position"][1].as<float>();
	instance->Position.z = node["Position"][2].as<float>();

	instance->Size.x = node["Size"][0].as<float>();
	instance->Size.y = node["Size"][1].as<float>();

	instance->Color.r = node["Color"][0].as<float>();
	instance->Color.g = node["Color"][1].as<float>();
	instance->Color.b = node["Color"][2].as<float>();
	instance->Color.a = node["Color"][3].as<float>();

	return instance;
}

std::string VOEngine::Unit::toString() {
	YAML::Node node = toNode();

	std::stringstream out;
	out << node;
	return out.str();;
}

YAML::Node VOEngine::Unit::toNode() {
	YAML::Node node;
	node["Name"] = Name;
	node["Position"].push_back(Position.x);
	node["Position"].push_back(Position.y);
	node["Position"].push_back(Position.z);
	node["Size"].push_back(Size.x);
	node["Size"].push_back(Size.y);
	node["Color"].push_back(Color.r);
	node["Color"].push_back(Color.g);
	node["Color"].push_back(Color.b);
	node["Color"].push_back(Color.a);

	return node;
}
