#pragma once

namespace VOEngine {
	class Sound {
	public:
		Sound(const std::filesystem::path& fileName);
		~Sound() = default;
	public:
		bool IsPlaying = false;
		std::string Filename;
		std::vector<short> SoundData = { 0 };
		int Format;
		uint8_t Channels;
		int32_t SampleRate;
		int64_t BitsPerSample;
		size_t Size;
	};
}
