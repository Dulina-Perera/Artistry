// include/drawing_manager.hh

#pragma once

#include <GLFW/glfw3.h>
#include <vector>

class DrawingManager {
	public:
		static std::vector<float> draw_circle(float x, float y, float radius, int num_segments = 30);
};
