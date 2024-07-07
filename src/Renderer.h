#pragma once
#include <filesystem>
#include <unordered_map>
#include "References.h"
#include "Shader.h"


///<summary>
/// The Asset Loader class will load all the needed assets (e.g. Shaders, Textures) at the start of the application
/// it uses singleton pattern so there's only one instance of it
///</summary>
class AssetLoader {
public:
	static AssetLoader Get() {
		if (&instance == NULL)
			instance = AssetLoader();
		return instance;
	}
	void LoadAssets();
private:
	AssetLoader() = default;
	static AssetLoader instance;
	std::unordered_map<std::string, Shader*>shaders;
	std::string vertexShadersDir = "src/Shaders/Vertex";
	std::string fragmentShadersDir = "src/Shaders/Fragment";
};


/// <summary>
/// The time class uses the singlton pattern so there's only one instance of it
/// It is used to calculate time and delta time
/// </summary>
class Time
{
public:
	//Gets the only instance of the Time class
	//If there is no instance, it creates a new one
	static Time& Get() {
		if (&instance == nullptr)
			instance = Time();

		return instance;
	}
	Time(const Time&) = delete;
	//Calculates the delta time
	void CalculateTime() {
		float time;
		time = (float)glfwGetTime();
		deltaTime = time - lastFrame;
		lastFrame = time;
	}
	float DeltaTime()const {return deltaTime;}

private:
	Time() { return; }
	static Time instance;
	float lastFrame=0.0f;
	float deltaTime=0.0f;
};



