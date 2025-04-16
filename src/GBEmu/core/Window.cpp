#include "Window.h"

Window::Window()
{
	this->m_scaleFactor = 4;
	this->init();
	this->setDrawColor(Color_RGBA(0x00, 0x00, 0x00, 0xFF)); // black
}
Window::~Window()
{
	// The methods below are safe to call even if sdl failed to initialize or if the window/renderer are null
	SDL_DestroyRenderer(this->m_winStruct.renderer);
	CORE_WARN("SDL Renderer destroyed!");
	SDL_DestroyWindow(this->m_winStruct.window);
	CORE_WARN("SDL Window destroyed!");
}

bool Window::init()
{
	if (!this->initWinStruct())
	{
		return false;
	}
	// Flush the backbuffer
	if (SDL_RenderClear(this->m_winStruct.renderer) < 0)
	{
		CORE_ERROR("Failed flushing the backbuffer! Err: {}", SDL_GetError());
		return false;
	}
	this->isHidden = false;
	return true;
}

bool Window::setDrawColor(Color_RGBA rgba)
{
	if (SDL_SetRenderDrawColor(this->m_winStruct.renderer, rgba.r(), rgba.g(), rgba.b(), rgba.a()) < 0)
	{
		CORE_ERROR("Failed to set renderer draw color to {:04X}. Err: {}", (uint32_t)rgba, SDL_GetError());
		return false;
	}
	return true;
}

void Window::flush()
{
	SDL_RenderPresent(this->m_winStruct.renderer);
	if (SDL_RenderClear(this->m_winStruct.renderer) < 0)
	{
		CORE_ERROR("Failed flushing the backbuffer! Err: {}", SDL_GetError());
	}
}

bool Window::initWinStruct()
{
	if (SDL_CreateWindowAndRenderer(LCD_WIDTH * m_scaleFactor, LCD_HEIGHT * m_scaleFactor, 0, &(this->m_winStruct.window), &(this->m_winStruct.renderer)) == -1)
	{
		CORE_ERROR("Failed to create window and renderer! Err: {}", SDL_GetError());
		return false;
	}

	// Configure window
	this->setWindowTitle();
	SDL_SetWindowResizable(this->m_winStruct.window, SDL_FALSE);

	CORE_WARN("Window and surface successfully created!");
	return true;
}

void Window::setWindowTitle(const char* title)
{
	SDL_SetWindowTitle(this->m_winStruct.window, title);
}

void Window::toggleHidden()
{
	if (this->isHidden)
		this->show();
	else
		this->hide();
}

void Window::hide()
{
	this->isHidden = true;
	SDL_HideWindow(this->m_winStruct.window);
	CORE_WARN("Hiding window");
}

void Window::show()
{
	this->isHidden = false;
	SDL_ShowWindow(this->m_winStruct.window);
	CORE_WARN("Showing window");
}