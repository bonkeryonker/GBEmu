#ifndef SCREEN_H
#define SCREEN_H
#include <SDL2/SDL.h>
#include "Graphics.h"
#include "Log.h"

struct SDLWindowSurface
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	//SDL_Surface* surface;
};

class Screen
{
public:
	Screen(int scaleFactor = 1);
	~Screen();
	// Sets the color for the renderer to draw with. Returns: TRUE if renderer color successfully changed
	bool setDrawColor(Color_RGBA rgba);
	void fillBG(SDL_Rect* bgRect);
	// Present the renderer buffer, and flush the backbuffer with SDL_RenderClear()
	void flush();
	// Set the title of the window
	void setWindowTitle(const char* title = "GBEmu: Running");
	// Set the window scale factor. This only takes effect if it's called BEFORE LCD.init()
	inline void setWindowScaleFactor(int scaleFactor) { this->windowScaleFactor = scaleFactor; }
private:
	SDLWindowSurface mainWindow;
	int windowScaleFactor;
private:
	// Calls methods below to initialize SDL, create a window, and renderer. 
	// Flushes the backbuffer. 
	// Returns: TRUE if successful
	bool init();

	bool initSDL();
	bool initMainWindow();
};
#endif