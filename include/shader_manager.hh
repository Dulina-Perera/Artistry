// include/shader_manager.hh

#pragma once

#include <glad/glad.h>
#include <string>

const std::string read_shader(const std::string &filename);
GLuint compile_shader(const std::string &source, GLenum type);
GLuint link_program(const std::string &vertex_shader, const std::string &fragment_shader);
