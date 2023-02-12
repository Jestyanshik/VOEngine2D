#pragma once
#include "../SoundEngine.h"
#include "../AudioLoader.h"

namespace VOEngine {
	class OpenALSound : public Sound {
	public:
		OpenALSound(const std::filesystem::path& fileName) : Sound(fileName) {

		}
		ALuint Buffer;
	};

	class OpenALSoundEngine : public SoundEngine {
	public:
		OpenALSoundEngine() : SoundEngine() {
			getAvailableDevices();
			m_CurrentDevice = alcOpenDevice(m_AvailableDevices[0].c_str());
			if (m_CurrentDevice) {
				m_Context = alcCreateContext(m_CurrentDevice, NULL);
				alcMakeContextCurrent(m_Context);
			}
			else {
				m_Context = nullptr;
			}

		};
		~OpenALSoundEngine() override {
			for (auto source : m_SourceList) {
				alDeleteSources(1, source);
			}
			for (auto buffer : m_BufferList) {
				alDeleteBuffers(1, buffer);
			}
			alcMakeContextCurrent(0);
			alcDestroyContext(m_Context);
			alcCloseDevice(m_CurrentDevice);
		};

		std::vector<std::string>& getAvailableDevices() override;
		void playSound(uint32_t id) override;
		std::string getDefaultDevice() override;
		uint32_t loadSoundFromFile(const std::filesystem::path& filepath) override;
	private:
		std::vector<ALuint*> m_BufferList;
		std::vector<ALuint*> m_SourceList;
		std::vector<std::future<void>> m_PlayList;
		ALCcontext* m_Context;
		ALCdevice* m_CurrentDevice;
	};
}