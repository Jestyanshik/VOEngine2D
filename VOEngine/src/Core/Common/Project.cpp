#include "vopch.h"
#include "Project.h"
#include "Core/Common/Utils.h"

VOEngine::Project::Project(const std::filesystem::path& path): m_Path(path) {
	if (path.extension() == ".voproj") {
		std::string project = ReadFile(path);
		YAML::Node node = YAML::Load(project);
		/*for (YAML::const_iterator it = node.begin(); it != node.end(); ++it) {
			std::string sceneName = it->first.as<std::string>();
			Scene* instance = new Scene(move(framebuffer), sceneName);
			for (YAML::const_iterator iter = node[sceneName]["Units"].begin(); iter != node[sceneName]["Units"].end(); ++iter) {
				std::stringstream ss;
				ss << iter->second;

				Unit* unit = Unit::fromString(ss.str());
				instance->AddUnit(unit);
			}
			return instance;
		}*/
	}
	else
		throw std::exception("Not a project");
}

void VOEngine::Project::AddScene(const std::shared_ptr<Scene> scene) {
	m_Scenes.push_back(scene);
}
