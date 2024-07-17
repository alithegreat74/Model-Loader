#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Renderer.h"
#include "ModelLoader.h"
#include "UserInterface.h"

namespace Application {
	static GLFWwindow* window;
	static Model* model;
	static ShaderProgram* program;
	//Sets up the projects needed components
	void Start();
	//Contains the render loop
	void Update();
	void CleanUp();
}
