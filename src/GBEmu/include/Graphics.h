#ifndef GFX_H
#define GFX_H
#include <iostream>
#include <GLFW/glfw3.h>

void errCallback_glfw(int error, const char* description)
{
	fprintf(stderr, "GLFW Error: %s\n", description);
}

void windowCloseCallback_glfw(GLFWwindow* window)
{
	printf("Window closed with callback.\n");
	glfwDestroyWindow(window);
}

bool graphicsInit()
{
	printf("Initializing GLFW... ");
	if (!glfwInit())
	{
		printf("Failed!\n");
		return false;
	}
	printf("OK.\n");

	printf("Setting window hints...");
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	printf("OK.\n");

	return true;
}

void graphicsTerminate()
{
	printf("Terminating GLFW... ");
	glfwTerminate();
	printf("OK.\n");
}

#endif