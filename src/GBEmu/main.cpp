#define SDL_MAIN_HANDLED
#include "Log.h"
#include "Application.h"


int main()
{
	// Set up logging
	Log::Init();
	Log::SetLogLevel(Log::GetCoreLogger(), spdlog::level::level_enum::trace);
	CORE_WARN("Logging initialized. Watch out, beavers!");

	// Set up app
	App::Application app;
	app.run();

	// Clean up
	CORE_WARN("Closing GBEmu.");
}