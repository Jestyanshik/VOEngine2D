#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <io.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <chrono>
#include <cstdint>
#include <fstream>
#include <direct.h>
#include <limits.h>
#include <filesystem>
#ifdef _WIN32 
#include <Windows.h>
#endif

//SoundLibrary
#include "AL/al.h"
#include "AL/alc.h"
//Audio loading library
#include "sndfile.h"
#include "sndfile.hh"

#include "Core/Log/Log.h"
#include "GLFW/glfw3.h"
#include "glm.hpp"
#include <imgui.h>

typedef glm::vec4 color;

#include "Core/Rendering/Windows/Window.h"
#include "Core/Rendering/Renderer/Renderer.h"
#include "Core/Utils/Utils.h"
#include "Core/ResourceManager.h"



