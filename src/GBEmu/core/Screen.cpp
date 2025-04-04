#include "Screen.h"

Screen::Screen(int scaleFactor)
{
	this->windowScaleFactor = scaleFactor;
	this->init();
	this->setDrawColor(Color_RGBA(0x00, 0x00, 0x00, 0xFF)); // black
}
Screen::~Screen()
{
	// The methods below are safe to call even if sdl failed to initialize or if the window/renderer are null
	SDL_DestroyRenderer(this->mainWindow.renderer);
	CORE_WARN("SDL Renderer destroyed!");
	SDL_DestroyWindow(this->mainWindow.window);
	CORE_WARN("SDL Window destroyed!");
	SDL_Quit();
	CORE_WARN("SDL uninitialized!");
}

bool Screen::init()
{
	if (!this->initSDL())
	{
		return false;
	}

	if (!this->initMainWindow())
	{
		return false;
	}
	// Flush the backbuffer
	if (SDL_RenderClear(this->mainWindow.renderer) < 0)
	{
		CORE_ERROR("Failed flushing the backbuffer! Err: {}", SDL_GetError());
		return false;
	}
	return true;
}

bool Screen::setDrawColor(Color_RGBA rgba)
{
	if (SDL_SetRenderDrawColor(this->mainWindow.renderer, rgba.r(), rgba.g(), rgba.b(), rgba.a()) < 0)
	{
		CORE_ERROR("Failed to set renderer draw color to {:04X}. Err: {}", (uint32_t)rgba, SDL_GetError());
		return false;
	}
	return true;
}

void Screen::fillBG(SDL_Rect* bgRect)
{
	SDL_RenderFillRect(this->mainWindow.renderer, bgRect);
}

void Screen::flush()
{
	SDL_RenderPresent(this->mainWindow.renderer);
	if (SDL_RenderClear(this->mainWindow.renderer) < 0)
	{
		CORE_ERROR("Failed flushing the backbuffer! Err: {}", SDL_GetError());
	}
}

bool Screen::initSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		CORE_ERROR("Failed to initialize SDL! Err: {}", SDL_GetError());
		return false;
	}
	CORE_WARN("SDL Initialized.");
	return true;
}

bool Screen::initMainWindow()
{
	if (SDL_CreateWindowAndRenderer(LCD_WIDTH * this->windowScaleFactor, LCD_HEIGHT * this->windowScaleFactor, 0, &(this->mainWindow.window), &(this->mainWindow.renderer)) == -1)
	{
		CORE_ERROR("Failed to create window and renderer! Err: {}", SDL_GetError());
		return false;
	}

	// Configure window
	this->setWindowTitle();
	SDL_SetWindowResizable(this->mainWindow.window, SDL_FALSE);

	CORE_WARN("Window and surface successfully created!");
	return true;
}

void Screen::setWindowTitle(const char* title)
{
	SDL_SetWindowTitle(this->mainWindow.window, title);
}