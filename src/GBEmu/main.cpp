#include <iostream> //printf
#include <memory> // shared_ptr
#include <string>
#include "Graphics.h"
#include "Clock.h"
#include "Registers.h"
#include "CPU.h"
#include "Memory.h"
#include "Cartridge.h"
#include "SerialDebug.h"
#include "Log.h"


int main()
{
	Log::Init();
	Log::SetLogLevel(Log::GetCoreLogger(), spdlog::level::level_enum::warn);
	CORE_WARN("Logging initialized. Watch out, beavers!");
	if (!graphicsInit())
	{
		CORE_FATAL("Aborting...");
		return 1;
	}
	GLFWwindow* mainWindow = glfwCreateWindow(LCD_WIDTH * 4, LCD_HEIGHT * 4, "GBEmu", NULL, NULL);
	glfwSetWindowCloseCallback(mainWindow, windowCloseCallback_glfw);
	glfwMakeContextCurrent(mainWindow);

	while (!glfwWindowShouldClose(mainWindow))
	{
		glfwSwapBuffers(mainWindow);
		glfwPollEvents();
	}

	graphicsTerminate();
	CORE_WARN("Closing GBEmu.");
}