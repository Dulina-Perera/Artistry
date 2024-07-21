// src/shader_manager.cc

#include <fstream>
#include <iostream>
#include <spdlog/spdlog.h>
#include <sstream>

#include "shader_manager.hh"

const std::string read_shader(const std::string &filename) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		spdlog::error("Failed to open file: {}", filename);
		return "";
	}

	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

GLuint compile_shader(const std::string &source, GLenum type) {
	GLuint shader = glCreateShader(type);

	const char *c_str = source.c_str();
	glShaderSource(shader, 1, &c_str, NULL);

	glCompileShader(shader);

	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar info_log[512];
		glGetShaderInfoLog(shader, 512, NULL, info_log);
		spdlog::error("Failed to compile shader: {}", info_log);
		return 0;
	}

	return shader;
}

GLuint link_program(const std::string &vertex_shader, const std::string &fragment_shader) {
	GLuint program = glCreateProgram();
	GLuint vs = compile_shader(read_shader(vertex_shader), GL_VERTEX_SHADER);
	GLuint fs = compile_shader(read_shader(fragment_shader), GL_FRAGMENT_SHADER);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);

	GLint success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		GLchar info_log[512];
		glGetProgramInfoLog(program, 512, NULL, info_log);
		spdlog::error("Failed to link program: {}", info_log);
		return 0;
	}

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}
