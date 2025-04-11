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
		m_mainWindow = std::make_unique<Window>();
		m_mainWindow->setWindowTitle("GBEmu: Drop ROM into window");

		// Create gameboy object
		m_gb = std::make_unique<Gameboy>();

		// We start in app state: WAIT_FOR_ROM, so let's enable that event by default for SDL
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
				break;
			default:
				if (m_gb->cpu->isHalted())
				{
					m_mainWindow->setWindowTitle("GBEmu: Halted");
				}
				else
				{
					m_gb->cpu->tick();
				}
				break;
			}

			// Update SDL window renderer
			m_mainWindow->flush();
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
			case SDL_QUIT:
				this->stop();
				done = SDL_TRUE;
				break;
			case SDL_DROPFILE:
				m_droppedFilePath = e.drop.file; // deep copy and implicit conversion to std::string
				CORE_INFO("Rompath: {}", m_droppedFilePath.c_str());
				SDL_free(e.drop.file); // Free the file
				SDL_EventState(SDL_DROPFILE, SDL_DISABLE); // Disable dropfile events
				break;
			}
		}
	}

	void Application::waitForROM()
	{
		if (m_droppedFilePath == "")
			return;

		m_gb->cart->loadROM(m_droppedFilePath);
		m_mainWindow->setWindowTitle(); // Set to default title
		m_appState = RUN_ROM;
	}
}