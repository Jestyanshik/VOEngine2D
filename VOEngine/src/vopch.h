#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <io.h>
#include <cstdlib>
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
#include <climits>
#include <filesystem>
#include <future>
#ifdef _WIN32 
#include <Windows.h>
#endif

//SoundLibrary
#include "AL/al.h"
#include "AL/alc.h"
//Audio loading library
#include "sndfile.h"
#include "sndfile.hh"

#include "yaml-cpp/yaml.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm.hpp"
#include <imgui.h>
#include "Core/ImGuiBackend/imgui_impl_opengl3.h"
#include "Core/ImGuiBackend/imgui_impl_glfw.h"

typedef glm::vec4 color;

#include "Core/Common/Consts.h"
#include "Core/Common/UUID.h"
#include "Core/Common/Log.h"



