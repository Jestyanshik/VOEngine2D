#include "vopch.h"
#include "SoundEngine.h"
#include "OpenAL/OpenALSoundEngine.h"
#include "Core/ResourceManager.h";

namespace VOEngine {
    std::unique_ptr<SoundEngine> BuildSoundEngine() {
        std::unique_ptr<SoundEngine> instance;
        if (ResourceManager::GetInstance().GetSettings()->GetValue("SoundEngine") == "OpenAL") {
            instance = std::make_unique<OpenALSoundEngine>();
        }
        return instance;
    }
}

