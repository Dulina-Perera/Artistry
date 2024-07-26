// include/window_manager.hh

#pragma once

#include <GLFW/glfw3.h>

class WindowManager
{
	public:
		static GLFWwindow *create_window(int width, int height, const char *title);
		static void set_window_icon(GLFWwindow *window, const char *icon_path);
		static void setup_callbacks(GLFWwindow *window);
};
