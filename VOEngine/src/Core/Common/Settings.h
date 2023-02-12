#pragma once
#include "vopch.h"

namespace VOEngine {
	class SettingsManager {
	public:
		SettingsManager() {
			m_Config = YAML::LoadFile("settings.yaml");
		}
		~SettingsManager() {
			
		};

		std::string GetValue(const std::string& key) {
			std::string value = "";
			auto applicationNode = m_Config["Application"];
			try { value = applicationNode[key].as<std::string>(); }
			catch (const std::exception& e) { VO_CORE_ERROR("Couldn't find {} inside settigns.yaml {}", key, e.what()); }
			return value;
		}

		std::vector<std::string> GetSequence(const std::string& key) {
			std::vector<std::string> seq;
			auto applicationNode = m_Config["Application"][key];
			if (!applicationNode.IsSequence()) return seq;
			try { seq = applicationNode[key].as<std::vector<std::string>>(); }
			catch (const std::exception& e) { VO_CORE_ERROR("Couldn't find {} inside settigns.yaml {}", key, e.what()); }
			return seq;
		}

		std::vector<std::string> GetNodeSequence(const std::string& node, const std::string& key) {
			std::vector<std::string> seq;
			seq.resize(128);
			auto applicationNode = m_Config[node][key];
			if (!applicationNode.IsSequence()) return seq;
			try { seq = applicationNode.as<std::vector<std::string>>(); }
			catch (const std::exception& e) { VO_CORE_ERROR("Couldn't find {} inside settigns.yaml {}", key, e.what()); }
			return seq;
		}

		void SetValue(const std::pair<std::string, std::string> pair) {
			auto applicationNode = m_Config["Application"];
			applicationNode[pair.first] = pair.second;
			std::ofstream fout("settings.yaml");
			fout << m_Config;
		}

		template<typename T>
		void SetNodeValue(const std::string& node, const std::string& key, T value) {
			auto applicationNode = m_Config[node];
			applicationNode[key] = value;
			std::ofstream fout("settings.yaml");
			fout << m_Config;
		};
	private:
		YAML::Node m_Config;
	};
}