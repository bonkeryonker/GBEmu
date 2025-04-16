#define SDL_MAIN_HANDLED
#include "Log.h"
#include "Application.h"


int main()
{
	// Set up logging
	Log::Init();
	Log::SetLogLevel(Log::GetCoreLogger(), spdlog::level::level_enum::info);
	Log::SetLogLevel(Log::GetGBLogger(), spdlog::level::level_enum::info);
	CORE_WARN("Logging initialized. Watch out, beavers!");

	// Set up app
	App::Application app;

	// Run app, return exit status
	return app.run();
}