// src/main.cc

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>
#include <stdlib.h>
#include <exception>

#include "../include/drawing_manager.hh"
#include "../include/shader_manager.hh"
#include "../include/utils.hh"
#include "../include/window_manager.hh"

int main()
{
	spdlog::set_level(spdlog::level::info);
	spdlog::set_pattern("[%H:%M:%S %z] [%^%l%$] [thread %t] %v");
	spdlog::info("Starting Artistry...");

	if (!glfwInit())
	{
		spdlog::critical("Failed to initialize GLFW.");
		return EXIT_FAILURE;
	}
	spdlog::info("GLFW initialized successfully.");

	GLFWwindow *window = WindowManager::create_window(720, 720, "Artistry");
	if (!window)
	{
		glfwTerminate();
		return EXIT_FAILURE;
	}

	try
	{
		WindowManager::setup_callbacks(window);
		spdlog::info("Callbacks set up successfully.");
	}
	catch (const std::exception &e)
	{
		spdlog::error("Error setting up callbacks: {}", e.what());
		glfwDestroyWindow(window);
		glfwTerminate();
		return EXIT_FAILURE;
	}

	GLuint program = link_program("src/shaders/shader.vert", "src/shaders/shader.frag");
	glUseProgram(program);

	GLuint vao = create_vertex_array_object();

	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	spdlog::debug("Generated vertex buffer object: {}.", vbo);

	std::vector<std::vector<float>> circles;

	while (!glfwWindowShouldClose(window))
	{
		spdlog::debug("Main loop iteration");

		glClear(GL_COLOR_BUFFER_BIT);
		spdlog::debug("Color buffer cleared.");

		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		spdlog::debug("Framebuffer size: ({}, {})", width, height);

		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		spdlog::debug("Cursor position: ({}, {})", xpos, ypos);

		float x = (2 * xpos - width) / width;
		float y = (height - 2 * ypos) / height;
		const float radius = 0.005f;

		std::vector<float> current_circle = DrawingManager::draw_circle(x, y, radius);
		spdlog::debug("Drew a circle at ({}, {}) with radius {}.", x, y, radius);

		vbo = create_vertex_buffer_object(current_circle);
		spdlog::debug("Created vertex buffer object for the current circle.");

		draw_circle(vao, vbo, current_circle, GL_TRIANGLE_FAN);
		spdlog::debug("Drew the current circle.");

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			spdlog::debug("Left mouse button pressed. Adding current circle to the list.");
			circles.push_back(current_circle);
		}

		for (const auto &circle : circles)
		{
			draw_circle(vao, vbo, circle, GL_TRIANGLE_FAN);
			spdlog::debug("Drew a stored circle.");
		}

		glfwPollEvents();
		spdlog::debug("GLFW events polled.");

		glfwSwapBuffers(window);
		spdlog::debug("GLFW buffers swapped.");
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	spdlog::info("GLFW window destroyed and terminated successfully.");

	return EXIT_SUCCESS;
}
