#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <memory>
#include <string>
#include "Graphics.h"
#include "Clock.h"
#include "Registers.h"
#include "CPU.h"
#include "Memory.h"
#include "Cartridge.h"
#include "SerialDebug.h"
#include "Log.h"

int main()
{
	Log::Init();
	Log::SetLogLevel(Log::GetCoreLogger(), spdlog::level::level_enum::warn);
	CORE_WARN("Logging initialized. Watch out, beavers!");
	
	CORE_WARN("Closing GBEmu.");
}