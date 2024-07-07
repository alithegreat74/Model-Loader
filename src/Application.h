#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Renderer.h"

namespace Application {
	static GLFWwindow* window;
	//Sets up the projects needed components
	void Start();
	//Contains the render loop
	void Update();
	void CleanUp();
}
