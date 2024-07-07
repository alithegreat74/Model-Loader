#pragma once
#include "References.h"
#include <iostream>
#include <fstream>
#include <string>

class Shader:RendererObject {
public:
	//Reads and compiles a shader file
	Shader(const char* filePath,unsigned int shaderType);
	~Shader();
	//Reads the shader file
	std::string ReadFromFile(const char* filePath);
	//Checks the Shader's Compilation status
	void ValidateShader()const;
	unsigned int GetShader()const { return object_id; }
private:
	const char* _shaderSource;
};

class ShaderProgram :RendererObject {
public:
	//Creates a shader program and links it's shaders
	ShaderProgram(Shader vertexShader, Shader fragmentShader);
	~ShaderProgram();
	//Set it as the current active shader program
	void Bind()const;
	//Unset it as the current active shader progran
	void Unbind()const;
	//Functions to change different uniform
	//void ChangeUniform(const char* name, int i1)const;
	void ChangeSingleUniform(const char* name, int i1)const;
	void ChangeSingleUniform(const char* name, float data)const;
	void ChangeUniform(const char* name, float f1, float f2, float f3, float f4);
	void ChangeUniform(const char* name, float f1, float f2, float f3);
	void ChangeUniform(const char* name, glm::vec2 value);
	void ChangeUniform(const char* name, glm::vec3 value);
	void ChangeUniform(const char* name, glm::vec4 value);
	void ChangeUniform(const char* name, glm::mat4 value);
	//Checks the program link status

private:
	void Validate()const;
};