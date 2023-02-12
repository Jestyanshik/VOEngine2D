#include "vopch.h"
#include "AudioLoader.h"

VOEngine::Sound::Sound(const std::filesystem::path& fileName) {
	SF_INFO fileInfo;
	SNDFILE* file;
	memset(&fileInfo, 0, sizeof(fileInfo));
	file = sf_wchar_open(fileName.wstring().c_str(), SFM_READ, &fileInfo);
	if (file == NULL)
		VO_CORE_ERROR("Couldn't open sound file {} {}", fileName.string(), sf_strerror(NULL));
	Channels = fileInfo.channels;
	SampleRate = fileInfo.samplerate;
	BitsPerSample = fileInfo.frames;
	SoundData.resize(BitsPerSample);
	Format = fileInfo.format;
	sf_readf_short(file, &SoundData[0], BitsPerSample);
	Size = SoundData.size() * sizeof(short);
	sf_close(file);
}
