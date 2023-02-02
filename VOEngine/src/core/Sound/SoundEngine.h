#pragma once
#include "AudioLoader.h"

namespace VOEngine {

	class SoundEngine  {
	public:
		SoundEngine() {
			m_SoundList = {};
		}
		virtual ~SoundEngine() {
			std::for_each(m_SoundList.begin(), m_SoundList.end(), [](const std::pair<uint32_t, Sound*>& n) {
				delete(n.second);	
			});
		};
		uint32_t loadSoundFromFile(const std::string& filepath) {
			Sound* sound = new Sound(filepath);
			m_SoundList[m_LastID] = sound;
			m_LastID++;
		};
		uint32_t loadSoundFromFile(const std::wstring& filepath) {
			Sound* sound = new Sound(filepath);
			m_SoundList[m_LastID] = sound;
			m_LastID++;
		};
		virtual std::vector<std::string>& getAvailableDevices() = 0;
		const Sound& getSoundByAudio(uint32_t id) {
			return *m_SoundList[id];
		}
	protected:
		std::unordered_map<uint32_t, Sound*> m_SoundList;
		std::vector<std::string> m_AvailableDevices;
		uint32_t m_LastID = 0;
	};
	
}