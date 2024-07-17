#pragma once
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <windows.h>
#include <commdlg.h>


namespace UI {
	extern std::string filepath;
	extern float position[3];
	extern float scale[3];
	extern float rotation[3];
	void Start(GLFWwindow*window);
	void Update(GLFWwindow* window);
	void CleanUp();
	void FileWindow();
	void ModelTransform();
}

std::string OpenFileDialogue();