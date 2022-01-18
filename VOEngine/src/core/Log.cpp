#include "vopch.h"
#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"


namespace VOEngine {
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	bool Log::Init()
	{
		s_CoreLogger = spdlog::stdout_color_mt("VOENGINE");
		s_CoreLogger->set_level(spdlog::level::trace);
		s_ClientLogger = spdlog::stdout_color_mt("Console");
		s_ClientLogger->set_level(spdlog::level::trace);
		return true;
	}
}


