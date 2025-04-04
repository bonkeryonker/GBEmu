#ifndef LOG_H
#define LOG_H
#include <spdlog/spdlog.h>
#include <memory>
#include <spdlog/sinks/stdout_color_sinks.h>

class Log
{
public:

	// Initialize all loggers with default level of TRACE
	static void Init();

	// Override the log level of the passed logger
	static void SetLogLevel(std::shared_ptr<spdlog::logger>& logger, spdlog::level::level_enum level);

	// Getters
	inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
	inline static std::shared_ptr<spdlog::logger>& GetGBLogger() { return s_GBLogger; }

private:
	static std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	static std::shared_ptr<spdlog::logger> Log::s_GBLogger;
};

/* Log macros */
#define CORE_FATAL(...) Log::GetCoreLogger()->critical(__VA_ARGS__)
#define CORE_ERROR(...) Log::GetCoreLogger()->error(__VA_ARGS__)
#define CORE_WARN(...) Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CORE_INFO(...) Log::GetCoreLogger()->info(__VA_ARGS__)
#define CORE_TRACE(...) Log::GetCoreLogger()->trace(__VA_ARGS__)

#define GB_ERROR(...) Log::GetGBLogger()->error(__VA_ARGS__)
#define GB_WARN(...) Log::GetGBLogger()->warn(__VA_ARGS__)
#define GB_INFO(...) Log::GetGBLogger()->info(__VA_ARGS__)
#define GB_TRACE(...) Log::GetGBLogger()->trace(__VA_ARGS__)
#endif
