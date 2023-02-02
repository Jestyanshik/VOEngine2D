#pragma once
#include "vopch.h"
#include "../SoundEngine.h"

namespace VOEngine {
	class OpenALSoundEngine : public SoundEngine {
	public:
		OpenALSoundEngine() : SoundEngine() {
			
		};
		~OpenALSoundEngine() override {
			
		};
		std::vector<std::string>& getAvailableDevices() override;




	private:
		ALCcontext* m_Context;
	};
}