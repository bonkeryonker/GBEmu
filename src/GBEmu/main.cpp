#define SDL_MAIN_HANDLED
#include <memory>
#include <string>
#include "Screen.h"
#include "Gameboy.h"
#include "Log.h"

void waitForFileDrop(Screen& lcd, std::string& fileDropPath);

int main()
{
	Log::Init();
	Log::SetLogLevel(Log::GetCoreLogger(), spdlog::level::level_enum::warn);
	CORE_WARN("Logging initialized. Watch out, beavers!");
	Screen lcd(4);
	lcd.setWindowTitle("GBEmu: Please drop ROM into window");
	std::string romFilepath;
	waitForFileDrop(lcd, romFilepath);
	CORE_WARN("Closing GBEmu.");
}

void waitForFileDrop(Screen& lcd, std::string& fileDropPath)
{
	SDL_EventState(SDL_DROPFILE, SDL_ENABLE);
	SDL_bool done = SDL_FALSE;
	SDL_Event e;
	SDL_Rect fillRect = { 0, 0, LCD_WIDTH, LCD_HEIGHT };
	char* dropped_filedir;
	while (!done)
	{
		while (!done && SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
				done = SDL_TRUE;
				break;
			case SDL_DROPFILE:
				dropped_filedir = e.drop.file;
				CORE_WARN("Rompath: {}", dropped_filedir);
				fileDropPath = dropped_filedir; //copy
				SDL_free(dropped_filedir);
				lcd.setWindowTitle(); // Set title to default
				//done = SDL_TRUE;
				break;
			}
		}
		lcd.fillBG(&fillRect);
		lcd.flush();
	}
}