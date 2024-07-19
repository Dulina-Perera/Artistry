// src/main.cc

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>

#include "../include/window_manager.hh"

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
}

int main() {
	GLFWwindow *window = WindowManager::create_window(720, 720, "Artistry");

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return EXIT_SUCCESS;
}
