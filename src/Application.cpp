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
	glClear(GL_DEPTH_BUFFER_BIT| GL_COLOR_BUFFER_BIT);

	

	model = new Model("E:/3D Models/shogun/source/shogun.fbx");
	program = new ShaderProgram(AssetLoader::GetShader("VertexShader.glsl"), AssetLoader::GetShader("FragmentShader.glsl"));
	
}

void Application::Update()
{
	glm::mat4 md(1.0f);
	//md = glm::translate(md, glm::vec3(0.0f, -1.0f, 0.0f));
	md = glm::scale(md, glm::vec3(0.5f, 0.5f, 0.5f));
	md = glm::rotate(md, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	md = glm::rotate(md, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	program->ChangeUniform("model", md);
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_DEPTH_BUFFER_BIT| GL_COLOR_BUFFER_BIT);
		program->Bind();
		md = glm::rotate(md, glm::radians(0.1f), glm::vec3(0.0f, 0.0f, 1.0f));
		program->ChangeUniform("model", md);
		model->Draw(*program);
		program->Unbind();
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
