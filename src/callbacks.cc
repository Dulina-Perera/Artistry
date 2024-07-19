#include <glad/glad.h>
#include <spdlog/spdlog.h>
#include "../include/callbacks.hh"

void cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
{
	spdlog::info("Cursor position: ({}, {})", xpos, ypos);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	spdlog::info("Framebuffer size: ({}, {})", width, height);

	// Check if the width and height are valid.
	if (width > 0 && height > 0)
	{
		glViewport(0, 0, width, height);
		spdlog::info("Viewport set to ({}, {}).", width, height);
	}
	else
	{
		spdlog::warn("Invalid framebuffer size: ({}, {})", width, height);
	}
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		spdlog::info("Escape key pressed. Setting window to close.");
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	else
	{
		std::string action_str = (action == GLFW_PRESS) ? "pressed" : (action == GLFW_RELEASE) ? "released" : "unknown";
		spdlog::info("Key {} was {}.", key, action_str);
	}
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	std::string action_str = (action == GLFW_PRESS) ? "pressed" : (action == GLFW_RELEASE) ? "released" : "unknown";
	spdlog::info("Mouse button {} was {} at ({}, {}).", button, action_str, xpos, ypos);
}
