#define SDL_MAIN_HANDLED
#include <string>
#include "Screen.h"
#include "Gameboy.h"
#include "Log.h"

void waitForFileDrop(Screen& lcd, std::string& fileDropPath);

int main()
{
	// Set up logging
	Log::Init();
	Log::SetLogLevel(Log::GetCoreLogger(), spdlog::level::level_enum::warn);
	CORE_WARN("Logging initialized. Watch out, beavers!");

	// Set up SDL to display a window
	Screen lcd(4);
	lcd.setWindowTitle("GBEmu: Please drop ROM into window");

	// Wait for the user to drag and drop a rom file into the window
	std::string romFilepath;
	waitForFileDrop(lcd, romFilepath);

	// Create the gameboy and run the rom
	Gameboy dmg;
	dmg.cart->loadROM(romFilepath);

	// Clean up
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
				CORE_INFO("Rompath: {}", dropped_filedir);
				fileDropPath = dropped_filedir; //copy
				SDL_free(dropped_filedir);
				lcd.setWindowTitle(); // Set title to default
				SDL_EventState(SDL_DROPFILE, SDL_DISABLE); // Disable filedrop events
				done = SDL_TRUE;
				break;
			}
		}
		lcd.fillBG(&fillRect);
		lcd.flush();
	}
}