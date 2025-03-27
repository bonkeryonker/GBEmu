#include "Log.h"

std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
std::shared_ptr<spdlog::logger> Log::s_CPULogger;

void Log::Init()
{
	spdlog::set_pattern("%^[&T] %n: %v%$");
	s_CoreLogger = spdlog::stdout_color_mt("Core");
	s_CoreLogger->set_level(spdlog::level::trace);

	s_CPULogger = spdlog::stdout_color_mt("CPU");
	s_CPULogger->set_level(spdlog::level::trace);
}