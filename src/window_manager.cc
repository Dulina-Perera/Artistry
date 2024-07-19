// src/window_manager.cc

#include <glad/glad.h>
#include <iostream>

#include "../include/window_manager.hh"

GLFWwindow *WindowManager::create_window(int width, int height, const char *title) {
	if (glfwInit() == GLFW_FALSE) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return nullptr;
	}

	GLFWwindow *window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (!window) {
		std::cerr << "Failed to create window" << std::endl;
		glfwTerminate();
		return nullptr;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return nullptr;
	}

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	return window;
}
