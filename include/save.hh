#pragma once

#include <GLFW/glfw3.h>
#include <string>
#include <vector>

std::vector<unsigned char> capture_frame_buffer(GLFWwindow *window, int width, int height);
void save_as_png(GLFWwindow *window);
