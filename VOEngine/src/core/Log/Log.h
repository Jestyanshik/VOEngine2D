#pragma once
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)


namespace VOEngine {
	class Log {
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	public:
		static bool Init();
		static std::shared_ptr<spdlog::logger>& getCoreLogger() { return s_CoreLogger; };
		static std::shared_ptr<spdlog::logger>& getClientLogger() { return s_ClientLogger; };
		
	};
}

//#ifdef LOG
#define VO_CORE_INFO(...) VOEngine::Log::getCoreLogger()->info(__VA_ARGS__)
#define VO_CORE_WARN(...) VOEngine::Log::getCoreLogger()->warn(__VA_ARGS__)
#define VO_CORE_ERROR(...) VOEngine::Log::getCoreLogger()->error(__VA_ARGS__)
#define VO_CORE_CRITICAL(...) VOEngine::Log::getCoreLogger()->critical(__VA_ARGS__)
#define VO_CORE_TRACE(...) VOEngine::Log::getCoreLogger()->trace(__VA_ARGS__)
#define VO_CORE_ASSERT(value) if (value == 0) {VOEngine::Log::getCoreLogger()->error("Assertion failed in {} at line {}", __FUNCTION__, __LINE__);}

#define VO_INFO(...) VOEngine::Log::getClientLogger()->info(__VA_ARGS__)
#define VO_WARN(...) VOEngine::Log::getClientLogger()->warn(__VA_ARGS__)
#define VO_ERROR(...) VOEngine::Log::getClientLogger()->error(__VA_ARGS__)
#define VO_CRITICAL(...) VOEngine::Log::getClientLogger()->critical(__VA_ARGS__)
#define VO_TRACE(...) VOEngine::Log::getClientLogger()->trace(__VA_ARGS__)
#define VO_ASSERT(value) if (value == 0) {VOEngine::Log::getClientLogger()->error("Assertion failed in {} at line {}", __FUNCTION__, __LINE__);}


//#else
//#define VO_CORE_INFO
//#endif