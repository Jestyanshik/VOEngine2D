#include "vopch.h"
#include "OpenALSoundEngine.h"

std::vector<std::string>& VOEngine::OpenALSoundEngine::getAvailableDevices() {
	m_AvailableDevices.clear();
    const ALCchar* devices = alcGetString(NULL, ALC_ALL_DEVICES_SPECIFIER);
    const ALCchar* device = devices, * next = devices + 1;
    size_t len = 0;

    while (device && *device != '\0' && next && *next != '\0') {
        m_AvailableDevices.emplace_back(device);
        len = strlen(device);
        device += (len + 1);
        next += (len + 2);
    }
    return m_AvailableDevices;
}

void VOEngine::OpenALSoundEngine::playSound(uint32_t id) {
	m_SourceList.push_back(new ALuint);
	alGenSources(1, m_SourceList.back());
	alSourcei(*m_SourceList.back(), AL_BUFFER, ((OpenALSound*)m_SoundList[id])->Buffer);
	alSourcef(*m_SourceList.back(), AL_GAIN, Volume);
	alSourcePlay(*m_SourceList.back());
	int source_state;
	alGetSourcei(*m_SourceList.back(), AL_SOURCE_STATE, &source_state);
	m_SoundList[id]->IsPlaying = source_state == AL_PLAYING;
	ALuint source = *m_SourceList.back();
	m_PlayList.push_back(std::async(std::launch::async, [this, id, source, source_state]() {
		int state = source_state;
		while (state == AL_PLAYING) {
			alGetSourcei(source, AL_SOURCE_STATE, &state);
			m_SoundList[id]->IsPlaying = state == AL_PLAYING;
		}
	}));
}

std::string VOEngine::OpenALSoundEngine::getDefaultDevice() {
	return alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);
}

uint32_t VOEngine::OpenALSoundEngine::loadSoundFromFile(const std::filesystem::path& filepath) {
	std::string filePathString = m_SoundDir.string() + filepath.string();
	if (!std::filesystem::exists(filePathString)) {
		VO_CORE_ERROR("[SoundEngine] File doesn't exist {}", filepath);
		return 0;
	}
	Sound* sound = new OpenALSound(filePathString);
	m_SoundList.insert(std::pair(m_LastID, sound));
	m_BufferList.push_back(new ALuint);
	alGenBuffers(1, m_BufferList.back());
	alBufferData(*m_BufferList.back(), sound->Channels == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16,
		&sound->SoundData[0], (ALsizei)sound->Size - sound->Size % 4, sound->SampleRate);
	((OpenALSound*)sound)->Buffer = *m_BufferList.back();
	m_LastID++;
	return m_LastID - 1;
}
