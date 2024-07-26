// src/main.cc

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <gtk-4.0/gtk/gtk.h>
#include <spdlog/spdlog.h>
#include <stdlib.h>
#include <exception>

#include "drawing_manager.hh"
#include "gui_manager.hh"
#include "shader_manager.hh"
#include "utils.hh"
#include "window_manager.hh"

extern bool dark_mode;
extern ImVec4 clear_color;
extern ImVec4 selected_color;
extern float brush_size;
extern int brush_size_display;

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

	WindowManager::set_window_icon(window, "./assets/icon.png");

	glfwSwapInterval(0);

	GLuint program = link_program("src/shaders/shader.vert", "src/shaders/shader.frag");
	glUseProgram(program);

	GLuint vao = create_vertex_array_object();

	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	spdlog::debug("Generated vertex buffer object: {}.", vbo);

	GUIManager::init(window);

	std::vector<std::vector<float>> circles;

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);

		GUIManager::new_frame();
		GUIManager::create_ui(circles);

		int width, height;
		glfwGetFramebufferSize(window, &width, &height);

		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		float x = (2 * xpos - width) / width;
		float y = (height - 2 * ypos) / height;
		const float radius = brush_size;

		std::vector<float> current_circle = DrawingManager::draw_circle(x, y, radius);

		vbo = create_vertex_buffer_object(current_circle);

		draw_circle(vao, vbo, current_circle, GL_TRIANGLE_FAN);

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			circles.push_back(current_circle);
		}

		int brush_color_location = glGetUniformLocation(program, "u_BrushColor");
		glUniform4f(brush_color_location, selected_color.x, selected_color.y, selected_color.z, selected_color.w);

		for (const auto &circle : circles)
		{
			draw_circle(vao, vbo, circle, GL_TRIANGLE_FAN);
		}

		GUIManager::render();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	GUIManager::shutdown();
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
	glfwDestroyWindow(window);
	glfwTerminate();
	spdlog::info("GLFW window destroyed and terminated successfully.");

	return EXIT_SUCCESS;
}
