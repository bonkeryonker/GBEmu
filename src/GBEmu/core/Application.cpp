#include "Application.h"

namespace App
{
	Application::Application()
	{
		// Init SDL
		unsigned int init_flags{
			SDL_INIT_VIDEO | SDL_INIT_AUDIO
		};
		if (SDL_Init(init_flags) != 0)
		{
			CORE_ERROR("Failed to init SDL! Err: {}", SDL_GetError());
			m_exit_status = 1;
		}
		CORE_WARN("SDL Initialized.");

		// Create main screen
		m_mainWindow = std::make_shared<Window>();
		m_mainWindow->setWindowTitle("Drop ROM into window");

		// Create debug screen
		m_debugWindow = std::make_shared<Window>();
		m_debugWindow->setWindowTitle("Debug");
		m_debugWindow->toggleHidden();

		// Create gameboy object
		m_gb = std::make_unique<Gameboy>(m_mainWindow);

		// We start in app state: WAIT_FOR_ROM, so let's enable that event for SDL by default
		SDL_EventState(SDL_DROPFILE, SDL_ENABLE);
	}

	Application::~Application()
	{
		CORE_WARN("Terminating SDL!");
		SDL_Quit();
	}

	int Application::run()
	{
		if (m_exit_status == 1)
		{
			return m_exit_status;
		}

		// Main application loop
		m_running = true;
		while (m_running)
		{
			// Handle events
			handleSDLEvents();

			// Either wait for ROM, or tick the gameboy
			switch (m_appState)
			{
			case WAIT_FOR_ROM:
				waitForROM();
				m_dumpMemory = false; // Reset memdump bool if we're in the WAIT_FOR_ROM state so we don't immediately dump upon rom execution
				break;
			default:
				// Check if we should dump memory to file (if F3 was pressed)
				if (m_dumpMemory)
				{
					m_dumpMemory = false; // Reset memdump bool so we only dump once per press
					m_gb->ram->dumpMemoryToFile(true); // dump cartridge and ram to file
				}

				if (m_gb->cpu->isHalted())
				{
					m_mainWindow->setWindowTitle("GBEmu: Halted");
					m_gb->ppu->tick();
				}
				else
				{
					m_gb->cpu->tick();
					m_gb->ppu->tick();
				}
				break;
			}

			// Flush SDL renderer buffers
			m_mainWindow->flush();
			m_debugWindow->flush();
			SDL_Delay(0);
		}

		return m_exit_status;
	}

	void Application::stop()
	{
		m_running = false;
	}

	void Application::handleSDLEvents()
	{
		SDL_bool done = SDL_FALSE;
		SDL_Event e;
		while (!done && SDL_PollEvent(&e)) // Dequeue the first event in line
		{
			switch (e.type)
			{
			case SDL_WINDOWEVENT:
				if (e.window.event == SDL_WINDOWEVENT_CLOSE)
				{
					if (e.window.windowID == m_debugWindow->getNativeWindowID())
					{
						m_debugWindow->hide();
					}
					else // Must be main window
					{
						this->stop();
						done = SDL_TRUE;
					}
				}
				break;
			case SDL_DROPFILE:
				m_droppedFilePath = e.drop.file; // deep copy and implicit conversion to std::string
				CORE_INFO("Rompath: {}", m_droppedFilePath.c_str());
				SDL_free(e.drop.file); // Free the file
				SDL_EventState(SDL_DROPFILE, SDL_DISABLE); // Disable dropfile events
				break;
			case SDL_KEYDOWN:
				if (e.key.keysym.sym == SDLK_F3)
				{
					CORE_INFO("Key down: F3");
					m_dumpMemory = true;
				}
				else if (e.key.keysym.sym == SDLK_F2)
				{
					CORE_INFO("Key down: F2");
					m_debugWindow->toggleHidden();
				}
				break;
			}
		}
	}

	void Application::waitForROM()
	{
		// If a dropfile event hasn't triggered, m_droppedFilePath remains empty
		// so we just return and keep checking the event queue
		if (m_droppedFilePath == "")
			return;

		// Otherwise let's load the ROM and change the application state
		m_gb->cart->loadROM(m_droppedFilePath);
		m_mainWindow->setWindowTitle(); // Set to default title
		m_appState = RUN_ROM;
	}
}