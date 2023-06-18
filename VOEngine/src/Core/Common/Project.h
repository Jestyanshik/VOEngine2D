#pragma once
#include "Core/Renderer/Scene.h"

namespace VOEngine {
	class Project {
	public:
		Project(const std::filesystem::path& path);
		~Project();

		void Save();
		void AddScene(const std::shared_ptr<Scene> scene);
	private:
		std::vector<std::shared_ptr<Scene>> m_Scenes;
		std::filesystem::path m_Path;
	};
}