// src/drawing_manager.cc

#include <cmath>
#include <spdlog/spdlog.h>
#include <vector>

#include "drawing_manager.hh"

std::vector<float> DrawingManager::draw_circle(float x, float y, float radius, int num_segments)
{
	// Log the parameters received by the function.
	spdlog::info("Drawing circle at ({}, {}) with radius {} and {} segments.", x, y, radius, num_segments);

	// Validate the input parameters.
	if (radius <= 0)
	{
		spdlog::warn("Invalid radius: {}. Must be greater than 0.", radius);
		return {}; // Return an empty vector if the radius is invalid.
	}
	if (num_segments < 3)
	{
		spdlog::warn("Invalid number of segments: {}. Must be at least 3.", num_segments);
		return {}; // Return an empty vector if the number of segments is invalid.
	}

	std::vector<float> vertices;
	vertices.reserve(num_segments * 2);

	for (int i = 0; i < num_segments; ++i)
	{
		float theta = 2.0f * M_PI * i / num_segments;
		float dx = radius * std::cosf(theta);
		float dy = radius * std::sin(theta);

		vertices.push_back(x + dx);
		vertices.push_back(y + dy);
	}

	spdlog::info("Generated {} vertices for the circle.", vertices.size() / 2); // Log the number of vertices generated.
	return vertices;
}
