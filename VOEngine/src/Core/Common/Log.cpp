#include "vopch.h"
#include "Log.h"

std::shared_ptr<spdlog::logger> VOEngine::Log::s_CoreLogger;
std::shared_ptr<spdlog::logger> VOEngine::Log::s_ClientLogger;

bool VOEngine::Log::Init() {
	s_CoreLogger = spdlog::stdout_color_mt("VOEngine");
	s_CoreLogger->set_level(spdlog::level::trace);
	s_ClientLogger = spdlog::stdout_color_mt("Console");
	s_ClientLogger->set_level(spdlog::level::trace);
	return true;
}
