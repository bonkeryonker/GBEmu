#define SDL_MAIN_HANDLED
#include <memory>
#include <string>
#include "Screen.h"
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
	Screen lcd(4);

	bool quit = false;
	SDL_Event e;
	SDL_Rect fillRect = { 0, 0, LCD_WIDTH, LCD_HEIGHT };
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}
		lcd.fillBG(&fillRect);
		lcd.flush();
	}

	CORE_WARN("Closing GBEmu.");
}