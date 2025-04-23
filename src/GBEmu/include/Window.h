#ifndef WINDOW_H
#define WINDOW_H
#include <SDL2/SDL.h>
#include <string>
#include "Graphics.h"
#include "Log.h"

typedef struct SDLRenderStruct
{
	SDL_Window* window;
	SDL_Renderer* renderer;
}WindowUtils;

class Window
{
public:
	Window();
	~Window();

	// Sets the color for the renderer to draw with. Returns: TRUE if renderer color successfully changed
	bool setDrawColor(Color_RGBA rgba);

	// Present the renderer buffer, and flush the backbuffer with SDL_RenderClear()
	void flush();

	// Set the title of the window
	void setWindowTitle(const char* title = "GBEmu: Running");

	// Set the window scale factor. This only takes effect if it's called BEFORE LCD.init()
	inline void setWindowScaleFactor(int scaleFactor) { this->m_scaleFactor = scaleFactor; }

	// Toggles the hidden/shown state of the window
	void toggleHidden();

	// Hides the window
	void hide();

	// Shows the window if hidden
	void show();

	// Getters
	inline const SDL_Window* getNativeWindow() { return this->m_winStruct.window; }
	inline const SDL_Renderer* getNativeRenderer() { return this->m_winStruct.renderer; }
	inline const Uint32 getNativeWindowID() { return SDL_GetWindowID(this->m_winStruct.window); }

private:
	WindowUtils m_winStruct;
	int m_scaleFactor{ 4 };
	bool m_isHidden{ false };
private:
	// Calls methods below to create a window and renderer. 
	// Flushes the backbuffer. 
	// Returns: TRUE if successful
	bool init();
	bool initWinStruct();
};
#endif