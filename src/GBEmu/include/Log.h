#ifndef LOG_H
#define LOG_H
#include <spdlog/spdlog.h>
#include <memory>
#include <spdlog/sinks/stdout_color_sinks.h>

class Log
{
public:
	static void Init();
	inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
	inline static std::shared_ptr<spdlog::logger>& GetCPULogger() { return s_CPULogger; }
private:
	static std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	static std::shared_ptr<spdlog::logger> Log::s_CPULogger;
};
#endif
