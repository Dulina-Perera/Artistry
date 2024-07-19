// src/main.cc

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>
#include <stdlib.h>
#include <exception>

#include "../include/window_manager.hh"

int main()
{
	// Initialize logging.
	spdlog::set_level(spdlog::level::info);
	spdlog::set_pattern("[%H:%M:%S %z] [%^%l%$] [thread %t] %v");
	spdlog::info("Starting Artistry...");

	// Initialize GLFW.
	if (!glfwInit())
	{
		spdlog::critical("Failed to initialize GLFW.");
		return EXIT_FAILURE;
	}
	spdlog::info("GLFW initialized successfully.");

	// Create a window.
	GLFWwindow *window = WindowManager::create_window(720, 720, "Artistry");
	if (!window)
	{
		glfwTerminate(); // Ensure GLFW is terminated if window creation fails.
		return EXIT_FAILURE;
	}

	// Set up callbacks.
	try
	{
		WindowManager::setup_callbacks(window);
		spdlog::info("Callbacks set up successfully.");
	}
	catch (const std::exception &e)
	{
		spdlog::error("Error setting up callbacks: {}", e.what());
		glfwDestroyWindow(window);
		glfwTerminate();
		return EXIT_FAILURE;
	}

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	// Clean up
	glfwDestroyWindow(window);
	glfwTerminate();
	spdlog::info("GLFW window destroyed and terminated successfully.");

	return EXIT_SUCCESS;
}
