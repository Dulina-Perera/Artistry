// src/utils.cc

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>
#include <vector>

#include "../include/utils.hh"

GLuint create_vertex_array_object() {
	GLuint vao;

	glGenVertexArrays(1, &vao);
	spdlog::debug("Generated vertex array object: {}.", vao);

	glBindVertexArray(vao);
	spdlog::debug("Bound vertex array object: {}.", vao);

	return vao;
}

GLuint create_vertex_buffer_object(const std::vector<float> &vertices) {
	GLuint vbo;

	glGenBuffers(1, &vbo);
	spdlog::debug("Generated vertex buffer object: {}.", vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	spdlog::debug("Bound vertex buffer object: {}.", vbo);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
	spdlog::debug("Buffered vertex data into vertex buffer object: {}.", vbo);

	return vbo;
}

void draw_circle(GLuint vao, GLuint vbo, const std::vector<float> &vertices, GLenum draw_mode) {
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)0);
	spdlog::debug("Enabled and set vertex attribute pointer for vertex array object: {}.", vao);

	glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizei>(vertices.size() * sizeof(float)), vertices.data(), GL_STATIC_DRAW);
	spdlog::debug("Buffered vertex data into vertex buffer object: {}.", vbo);

	glDrawArrays(draw_mode, 0, static_cast<GLsizei>(vertices.size() / 2));
	spdlog::debug("Drew circle with vertex array object: {}.", vao);

	glDisableVertexAttribArray(0);
	spdlog::debug("Disabled vertex attribute pointer for vertex array object: {}.", vao);

	glBindVertexArray(0);
	spdlog::debug("Unbound vertex array object: {}.", vao);
}
