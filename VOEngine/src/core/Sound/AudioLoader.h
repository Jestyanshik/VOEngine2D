#pragma once

namespace VOEngine {
	class Sound {
	public:
		Sound(const std::string& fileName);
		Sound(const std::wstring& fileName);
		~Sound() = default;
	private:
		std::string m_Filename;
		std::vector<short> m_SoundData;
		uint8_t m_Channels;
		int32_t m_SampleRate;
		uint8_t m_BitsPerSample;
		size_t m_Size;
	};
}
