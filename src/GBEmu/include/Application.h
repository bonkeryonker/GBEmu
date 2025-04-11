#ifndef APP_H
#define APP_H
#include <SDL2/SDL.h>
#include <memory>
#include <string>
#include "Graphics.h"
#include "Screen.h"
#include "Log.h"
#include "Gameboy.h"

namespace App
{
	enum APPSTATE
	{
		WAIT_FOR_ROM, RUN_ROM
	};

	class Application
	{
	public:
		Application();
		~Application();

		// Returns: Exit status
		int run();
		void stop();

	private:
		int m_exit_status{ 0 };
		bool m_running{ false };
		APPSTATE m_appState{ WAIT_FOR_ROM };
		std::string m_droppedFilePath{ "" }; // Instantiated when file dropped event occurs
		std::unique_ptr<Screen> m_mainWindow{ nullptr }; // Instantiated inside constructor
		std::unique_ptr<Gameboy> m_gb{ nullptr }; // Instantiated inside constructor
	private:
		void handleSDLEvents();
		void waitForROM();
	};
};

#endif

