// include/utils.hh

#pragma once

#include <GLFW/glfw3.h>
#include <vector>

GLuint create_vertex_array_object();
GLuint create_vertex_buffer_object(const std::vector<float> &vertices);

void draw_circle(GLuint vao, GLuint vbo, const std::vector<float> &vertices, GLenum draw_mode);
