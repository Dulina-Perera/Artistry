#pragma once

#include <GLFW/glfw3.h>

class WindowManager {
	public:
		static GLFWwindow *create_window(int width, int height, const char *title);
};
