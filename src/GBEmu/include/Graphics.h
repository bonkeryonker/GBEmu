#ifndef GFX_H
#define GFX_H
#include <iostream>
#include <GLFW/glfw3.h>
#include "Log.h"

void errCallback_glfw(int error, const char* description)
{
	/*fprintf(stderr, "GLFW Error: %s\n", description);*/
	CORE_ERROR("GLFW Error: {}", description);
}

void windowCloseCallback_glfw(GLFWwindow* window)
{
	/*printf("Window closed with callback.\n");*/
	//spdlog::info("Window closed with callback.");
	CORE_WARN("Window closed with callback.");
	glfwDestroyWindow(window);
}

bool graphicsInit()
{
	CORE_TRACE("Initializing GLFW...");
	if (!glfwInit())
	{
		CORE_FATAL("Failed to initialize GLFW!");
		return false;
	}
	CORE_WARN("GLFW Initialized.");

	// Set window hints
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	return true;
}

void graphicsTerminate()
{
	CORE_WARN("Terminating GLFW");
	glfwTerminate();
}

#endif