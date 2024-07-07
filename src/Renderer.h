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

	static void LoadAssets();
	static unsigned int GetShader(std::string shaderFileName);
private:
	static std::unordered_map<std::string, unsigned int>shaders;
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



