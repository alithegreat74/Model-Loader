#include "Renderer.h"

//Statics
Time Time::instance;
std::unordered_map<std::string, unsigned int> AssetLoader::shaders;

std::string vertexShadersDir = "src/Shaders/Vertex";
std::string fragmentShadersDir = "src/Shaders/Fragment";

void AssetLoader::LoadAssets()
{
	//Loading the vertex Shaders
	for (auto file : std::filesystem::directory_iterator(vertexShadersDir)) {
		Shader shader(file.path().string().c_str(), GL_VERTEX_SHADER);
		shaders.insert(std::make_pair(file.path().filename().string(), shader.GetShader()));
	}
	//Loading the Fragment Shaders
	for (auto file : std::filesystem::directory_iterator(fragmentShadersDir)) {
		Shader shader(file.path().string().c_str(), GL_FRAGMENT_SHADER);
		shaders.insert(std::make_pair(file.path().filename().string(), shader.GetShader()));
	}
}

unsigned int AssetLoader::GetShader(std::string shaderFileName)
{
	if (shaders.find(shaderFileName) != shaders.end()) {
		return shaders[shaderFileName];
	}
	return 0;
}
