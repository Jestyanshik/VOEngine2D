#include "vopch.h"
#include "AudioLoader.h"

VOEngine::Sound::Sound(const std::string& fileName) {
	SF_INFO fileInfo;
	SNDFILE* file;
	file = sf_open(fileName.c_str(), SFM_READ, &fileInfo);
	m_Channels = fileInfo.channels;
	m_SampleRate = fileInfo.samplerate;
	m_BitsPerSample = fileInfo.frames;
	sf_readf_short(file, &m_SoundData[0], m_BitsPerSample);
	m_Size = m_SoundData.size() * sizeof(short);
	sf_close(file);
}

VOEngine::Sound::Sound(const std::wstring& fileName) {
	SF_INFO fileInfo;
	SNDFILE* file;
	file = sf_open(WideStringToString(fileName.c_str()).c_str(), SFM_READ, &fileInfo);
	m_Channels = fileInfo.channels;
	m_SampleRate = fileInfo.samplerate;
	m_BitsPerSample = fileInfo.frames;
	sf_readf_short(file, &m_SoundData[0], m_BitsPerSample);
	m_Size = m_SoundData.size() * sizeof(short);
	sf_close(file);
}
