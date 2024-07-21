// include/gui_manager.hh

#pragma once

#include <imgui_impl_glfw.h>
#include <vector>

class GUIManager
{
	public:
		static void init(GLFWwindow *window);
		static void shutdown();
		static void new_frame();
		static void render();
		static void create_ui(std::vector<std::vector<float>> &cirlces);
};
