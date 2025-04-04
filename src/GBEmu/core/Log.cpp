#include "Log.h"

std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
std::shared_ptr<spdlog::logger> Log::s_GBLogger;

void Log::Init()
{
	spdlog::set_pattern("%^[%n/%l]:%$ %v");
	s_CoreLogger = spdlog::stdout_color_mt("Core");
	s_CoreLogger->set_level(spdlog::level::trace);

	s_GBLogger = spdlog::stdout_color_mt("Gameboy");
	s_GBLogger->set_level(spdlog::level::trace);
}

void Log::SetLogLevel(std::shared_ptr<spdlog::logger>& logger, spdlog::level::level_enum level)
{
	logger->set_level(level);
}