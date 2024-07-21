project(
	'artistry',
	'cpp',
	version: '0.1.0',
	default_options: [
		'buildtype=debugoptimized',
		'cpp_std=c++17',
		'warning_level=2'
	]
)

# Include directories
include_dirs = include_directories('include')

# Source files
src_files = files(
	'src/callbacks.cc',
	'src/drawing_manager.cc',
	'src/gui_manager.cc',
	'src/main.cc',
	'src/save.cc',
	'src/shader_manager.cc',
	'src/utils.cc',
	'src/window_manager.cc',
)

# Dependencies
glfw_dep = dependency('glfw3', required: true)
gtk_dep = dependency('gtk4', required: true)
imgui_dep = dependency('imgui', required: true)
opengl_dep = dependency('opengl', required: true)
spdlog_dep = dependency('spdlog', required: true)

# Manually add glad library.
glad_dep = declare_dependency(
	include_directories: include_directories('/usr/include/glad'),
	dependencies: opengl_dep,
	link_args: ['-lglad']
)

# Manually add stb library.
stb_de = declare_dependency(
	include_directories: include_directories('/usr/include/stb'),
)

# Build the executable.
executable(
	'artistry',
	src_files,
	include_directories: include_dirs,
	dependencies: [
		glad_dep,
		glfw_dep,
		gtk_dep,
		imgui_dep,
		opengl_dep,
		spdlog_dep,
		stb_de
	]
)
