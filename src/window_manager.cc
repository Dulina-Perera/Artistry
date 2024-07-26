// src/window_manager.cc

#include <fstream>
#include <glad/glad.h>
#include <iostream>
#include <spdlog/spdlog.h>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "callbacks.hh"
#include "window_manager.hh"

GLFWwindow *WindowManager::create_window(const int width, const int height, const char *title)
{
	// Create the window.
	GLFWwindow *window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (!window)
	{
		spdlog::critical("Failed to create the primary window.");
		return nullptr;
	}
	else
	{
		spdlog::info("Successfully created the primary window.");

		// Make the window's context current.
		glfwMakeContextCurrent(window);

		// Load GLAD.
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			spdlog::critical("Failed to initialize GLAD.");
			glfwDestroyWindow(window);
			return nullptr;
		}
		else
		{
			spdlog::info("Successfully initialized GLAD.");
		}

		return window;
	}
}

void WindowManager::set_window_icon(GLFWwindow *window, const char *icon_path)
{
	int width, height, channels;

	std::ifstream file(icon_path, std::ios::binary);
	if (!file)
	{
		std::cerr << "Failed to open image file: " << icon_path << std::endl;
		return;
	}

	file.seekg(0, std::ios::end);
	size_t fileSize = file.tellg();
	file.seekg(0, std::ios::beg);

	std::vector<char> buffer(fileSize);
	file.read(buffer.data(), fileSize);
	file.close();

	unsigned char *pixels = stbi_load_from_memory(reinterpret_cast<unsigned char *>(buffer.data()), fileSize, &width, &height, &channels, STBI_rgb_alpha);
	if (!pixels)
	{
		std::cerr << "Failed to load image: " << icon_path << std::endl;
		return;
	}

	GLFWimage image;
	image.width = width;
	image.height = height;
	image.pixels = pixels;

	glfwSetWindowIcon(window, 1, &image);

	stbi_image_free(pixels);
}

void WindowManager::setup_callbacks(GLFWwindow *window)
{
	glfwSetCursorPosCallback(window, cursor_position_callback);
	spdlog::info("Set cursor position callback.");

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	spdlog::info("Set framebuffer size callback.");

	glfwSetKeyCallback(window, key_callback);
	spdlog::info("Set key callback.");

	glfwSetMouseButtonCallback(window, mouse_button_callback);
	spdlog::info("Set mouse button callback.");

	spdlog::info("Successfully set up all callbacks.");
}
