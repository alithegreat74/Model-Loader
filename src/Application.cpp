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

	UI::Start(window);

	

	program = new ShaderProgram(AssetLoader::GetShader("VertexShader.glsl"), AssetLoader::GetShader("FragmentShader.glsl"));
	
}

void Application::Update()
{
	glm::mat4 md(1.0f);

	program->ChangeUniform("model", md);
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_DEPTH_BUFFER_BIT| GL_COLOR_BUFFER_BIT);
		program->Bind();

		glm::mat4 md(1.0f);
		md = glm::translate(md, glm::vec3(UI::position[0],UI::position[1],UI::position[2]));
		md = glm::scale(md, glm::vec3(UI::scale[0],UI::scale[1],UI::scale[2]));
		md = glm::rotate(md,glm::radians(UI::rotation[0]), glm::vec3(1, 0, 0));
		md = glm::rotate(md,glm::radians(UI::rotation[1]), glm::vec3(0, 1, 0));
		md = glm::rotate(md,glm::radians(UI::rotation[2]), glm::vec3(0, 0, 1));
		program->ChangeUniform("model", md);

		 
		if ((UI::filepath != "" && model == nullptr)) {
			model = new Model(UI::filepath);
		}
		if (model != nullptr && UI::filepath != model->path) {
			delete model;
			model = new Model(UI::filepath);
		}
		if(model!=nullptr)
			model->Draw(*program);


		program->Unbind();

		UI::Update(window);

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
