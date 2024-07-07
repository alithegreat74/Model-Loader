#include "Renderer.h"

//Statics
AssetLoader AssetLoader::instance;
Time Time::instance;



void AssetLoader::LoadAssets()
{
	//Loading the vertex Shaders
	for (auto file : std::filesystem::directory_iterator(vertexShadersDir)) {
		Shader shader(file.path().string().c_str(), GL_VERTEX_SHADER);
		shaders.insert(std::make_pair(file.path().filename().string(), &shader));
	}
	//Loading the Fragment Shaders
	for (auto file : std::filesystem::directory_iterator(fragmentShadersDir)) {
		Shader shader(file.path().string().c_str(), GL_FRAGMENT_SHADER);
		shaders.insert(std::make_pair(file.path().filename().string(), &shader));
	}
}
