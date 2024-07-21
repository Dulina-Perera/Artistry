// src/window_manager.cc

#include <glad/glad.h>
#include <spdlog/spdlog.h>

#include "callbacks.hh"
#include "window_manager.hh"

GLFWwindow *WindowManager::create_window(int width, int height, const char *title)
{
	// Create the window.
	GLFWwindow *window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (!window)
	{
		spdlog::critical("Failed to create window.");
		return nullptr;
	}
	spdlog::info("Window created successfully: {} ({}x{}).", title, width, height);

	// Make the context current
	glfwMakeContextCurrent(window);

	// Load GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		spdlog::critical("Failed to initialize GLAD.");
		glfwDestroyWindow(window); // Clean up the window if GLAD initialization fails
		return nullptr;
	}
	spdlog::info("GLAD initialized successfully.");

	// Set window hints.
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	spdlog::info("Window resizable hint set to false.");

	return window;
}

void WindowManager::setup_callbacks(GLFWwindow *window)
{
	glfwSetCursorPosCallback(window, cursor_position_callback);
	spdlog::info("Cursor position callback set.");

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	spdlog::info("Framebuffer size callback set.");

	glfwSetKeyCallback(window, key_callback);
	spdlog::info("Key callback set.");

	glfwSetMouseButtonCallback(window, mouse_button_callback);
	spdlog::info("Mouse button callback set.");
}
