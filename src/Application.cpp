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
	glEnable(GL_DEPTH_TEST);
	glClear(GL_DEPTH_BUFFER_BIT);

	model = new Model("src/Models/armor/armor 2021.obj");
	program = new ShaderProgram(AssetLoader::GetShader("VertexShader.glsl"), AssetLoader::GetShader("FragmentShader.glsl"));
	program->Bind();
	
}

void Application::Update()
{
	glm::mat4 md(1.0f);
	md = glm::translate(md, glm::vec3(0.0f, -1.0f, 0.0f));
	md = glm::rotate(md, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	md = glm::scale(md, glm::vec3(0.1f, 0.1f, 0.1f));
	program->ChangeUniform("model", md);
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_DEPTH_BUFFER_BIT);
		model->Draw(*program);
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
}

void Application::CleanUp()
{
	delete model;
	delete program;
	glfwTerminate();

}
