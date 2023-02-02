#include "vopch.h"
#include "OpenALSoundEngine.h"

std::vector<std::string>& VOEngine::OpenALSoundEngine::getAvailableDevices() {
    const ALCchar* devices = alcGetString(NULL, ALC_ALL_DEVICES_SPECIFIER);
    const ALCchar* device = devices, * next = devices + 1;
    size_t len = 0;

    while (device && *device != '\0' && next && *next != '\0') {
        m_AvailableDevices.push_back(device);
        len = strlen(device);
        device += (len + 1);
        next += (len + 2);
    }
    return m_AvailableDevices;
}
