#ifndef SCREEN_H
#define SCREEN_H
#include <SDL2/SDL.h>
#include "Graphics.h"
#include "Log.h"

struct SDLWindowSurface
{
	SDL_Window* window;
	SDL_Renderer* renderer;
};

class Screen
{
public:
	Screen();
	~Screen();

	// Sets the color for the renderer to draw with. Returns: TRUE if renderer color successfully changed
	bool setDrawColor(Color_RGBA rgba);

	// Present the renderer buffer, and flush the backbuffer with SDL_RenderClear()
	void flush();

	// Set the title of the window
	void setWindowTitle(const char* title = "GBEmu: Running");

	// Set the window scale factor. This only takes effect if it's called BEFORE LCD.init()
	inline void setWindowScaleFactor(int scaleFactor) { this->m_scaleFactor = scaleFactor; }

private:
	SDLWindowSurface m_winStruct;
	int m_scaleFactor{ 4 };

private:
	// Calls methods below to create a window and renderer. 
	// Flushes the backbuffer. 
	// Returns: TRUE if successful
	bool init();

	bool initWinStruct();
};
#endif