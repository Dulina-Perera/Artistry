// src/gui_manager.cc

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <spdlog/spdlog.h>

#include "gui_manager.hh"
#include "save.hh"

bool dark_mode = true;
ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
ImVec4 selected_color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

float brush_size = 0.0055f;
int brush_size_display = 10;
const float min_brush_size = 0.001f;
const float max_brush_size = 0.05f;

void reset_drawing(std::vector<std::vector<float>> &circles)
{
	circles.clear();
	spdlog::info("Drawing reset");
}

void toggle_dark_white_mode(bool &dark_mode, ImVec4 &clear_color)
{
	if (dark_mode)
	{
		ImGui::StyleColorsLight();
		clear_color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	}
	else
	{
		ImGui::StyleColorsDark();
		clear_color = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	}
	dark_mode = !dark_mode;
	spdlog::info("Dark/White mode toggled");
}

void GUIManager::init(GLFWwindow *window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	spdlog::info("Setup Dear ImGui context");

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 450 core");
	spdlog::info("Setup platform/renderer backends for Dear ImGui");

	ImGui::StyleColorsDark();
	spdlog::info("Setup Dear ImGui style");
}

void GUIManager::shutdown()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	spdlog::info("Shutdown Dear ImGui");
}

void GUIManager::new_frame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void GUIManager::render()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUIManager::create_ui(std::vector<std::vector<float>> &circles)
{
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_MenuBar;

	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, 0));

	ImGui::Begin("UI Panel", nullptr, window_flags);

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Save as PNG"))
			{
				save_as_png(glfwGetCurrentContext());
			}
			if (ImGui::MenuItem("Reset"))
			{
				reset_drawing(circles);
			}
			if (ImGui::MenuItem("Dark/White Mode"))
			{
				toggle_dark_white_mode(dark_mode, clear_color);
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Palette"))
		{
			ImGui::ColorEdit3("Color", (float *)&selected_color);
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Brush"))
		{
			if (ImGui::SliderInt("Size", &brush_size_display, 1, 100)) {
        brush_size = min_brush_size + (max_brush_size - min_brush_size) * (brush_size_display - 1) / 99.0f;
      }
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Draw"))
		{

			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	ImGui::Text("fps: %.1f", ImGui::GetIO().Framerate);
	ImGui::End();
}
