#include <glad/glad.h>
#include <iostream>

#include "../include/callbacks.hh"

void cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
{
	std::cout << "Cursor position: (" << xpos << ", " << ypos << ")" << std::endl;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	std::cout << "Framebuffer size: (" << width << ", " << height << ")" << std::endl;

	glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	std::cout << "Key: " << key << (action ? " pressed." : " released.") << std::endl;

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		std::cout << "Left mouse button: " << (action ? "pressed" : "released") << " at (" << xpos << ", " << ypos << ")" << std::endl;
	}
}
