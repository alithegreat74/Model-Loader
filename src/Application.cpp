#include "Application.h"


void Application::Start() {
	if (!glfwInit()) {
		std::cout << "Failed to initialize glfw\n";
		return;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(1280, 720, "Model Loader", NULL, NULL);

	if (!window) {
		std::cout << "Failed to open a window\n";
		return;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGL()) {
		std::cout << "Failzed to initialize glad\n";
		return;
	}

	AssetLoader::LoadAssets();
}

void Application::Update()
{

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
}

void Application::CleanUp()
{
	glfwTerminate();
}
