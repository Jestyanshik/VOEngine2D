#pragma once
#include "AudioLoader.h"

namespace VOEngine {

	class SoundEngine  {
	public:
		SoundEngine() { }
		virtual ~SoundEngine() {
			std::for_each(m_SoundList.begin(), m_SoundList.end(), [](const std::pair<uint32_t, Sound*>& n) {
				delete n.second;	
			});
		};
		//Returns 0 if file doesn't exist otherwise returns uint32_t >= 1
		virtual uint32_t loadSoundFromFile(const std::filesystem::path& filepath) {
			std::string filePathString = m_SoundDir.string() + filepath.string();
			if (not std::filesystem::exists(filePathString)) {
				VO_CORE_ERROR("[SoundEngine] File doesn't exist {}", filepath);
				return 0;
			}
			Sound* sound = new Sound(filePathString);
			m_SoundList.insert(std::pair(m_LastID, sound));
			m_LastID++;
			return m_LastID - 1;
		};
		virtual void playSound(uint32_t id) = 0;
		virtual std::vector<std::string>& getAvailableDevices() = 0;
		virtual std::string getDefaultDevice() = 0;
		const Sound* getSoundByID(uint32_t id) {
			return m_SoundList[id];
		}
		bool isSoundPlaying(uint32_t id) {
			return m_SoundList[id]->IsPlaying;
		}
		float Volume = 1.0f;
	protected:
		std::unordered_map<uint32_t, Sound*> m_SoundList = {};
		std::filesystem::path m_SoundDir = "res/sounds/";
		std::vector<std::string> m_AvailableDevices = {};
		uint32_t m_LastID = 1;
	};
	
}