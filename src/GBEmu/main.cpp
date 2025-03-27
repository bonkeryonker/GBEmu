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

// TODO: Make the library link/compile with cmake
// https://www.glfw.org/docs/latest/build_guide.html
int main()
{
	if (!graphicsInit())
	{
		printf("Aborting...\n");
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
}