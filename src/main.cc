// src/main.cc

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>

#include "../include/window_manager.hh"

int main()
{
	GLFWwindow *window = WindowManager::create_window(720, 720, "Artistry");

	if (!window)
	{
		return EXIT_FAILURE;
	}
	else
	{
		WindowManager::setup_callbacks(window);

		while (!glfwWindowShouldClose(window))
		{
			glClear(GL_COLOR_BUFFER_BIT);

			glfwPollEvents();
			glfwSwapBuffers(window);
		}

		glfwDestroyWindow(window);
		glfwTerminate();

		return EXIT_SUCCESS;
	}
}
