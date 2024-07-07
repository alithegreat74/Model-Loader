#include "Shader.h"

Shader::Shader(const char* filePath, unsigned int shaderType)
{
	std::string src=ReadFromFile(filePath);
	_shaderSource = src.c_str();
	object_id = glCreateShader(shaderType);
	glShaderSource(object_id, 1, &_shaderSource, NULL);
	glCompileShader(object_id);
	ValidateShader();
}

Shader::~Shader()
{
	glDeleteShader(object_id);
}

std::string Shader::ReadFromFile(const char* filePath)
{
	//Open the file
	std::ifstream stream(filePath);
	if (!stream.is_open()) {
		std::cout << "Unable to open shader file at " << filePath << "\n";
		return "";
	}

	std::string buffer, out="";
	//Read the shader file line by line
	while (std::getline(stream,buffer))
	{
		out += buffer+'\n';
	}

	return out;
}

void Shader::ValidateShader() const
{

	int success;
	glGetShaderiv(object_id, GL_COMPILE_STATUS, &success); //Checks the shader compilation status 
	if(!success)
	{
		char log[1024];
		glGetShaderInfoLog(object_id, 255, NULL, log);	//Gets the Error if the compilation is failed
		std::cout << log << "\n";
		return;
	}
}

ShaderProgram::ShaderProgram(Shader vertexShader, Shader fragmentShader)
{
	//Creates a shader program and attaches the vertex and fragment shader
	object_id = glCreateProgram();
	glAttachShader(object_id, vertexShader.GetShader());
	glAttachShader(object_id, fragmentShader.GetShader());

	glLinkProgram(object_id);
	Validate();

	Unbind();

}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(object_id);
}

void ShaderProgram::Bind() const
{
	glUseProgram(object_id);
}

void ShaderProgram::Unbind() const
{
	glUseProgram(0);
}


void ShaderProgram::ChangeSingleUniform(const char* name, float data) const
{
	glUniform1f(glGetUniformLocation(object_id, name), data);
}

void ShaderProgram::ChangeSingleUniform(const char* name, int i1) const
{
	glUniform1i(glGetUniformLocation(object_id, name), i1);
}

void ShaderProgram::ChangeUniform(const char* name, float f1, float f2, float f3,float f4)
{
	glUniform4f(glGetUniformLocation(object_id, name), f1, f2, f3, f4);
}

void ShaderProgram::ChangeUniform(const char* name, float f1, float f2, float f3)
{
	glUniform3f(glGetUniformLocation(object_id, name), f1, f2, f3);
}

void ShaderProgram::ChangeUniform(const char* name, glm::vec2 value)
{
	glUniform2f(glGetUniformLocation(object_id, name), value.x, value.y);
}

void ShaderProgram::ChangeUniform(const char* name, glm::vec3 value)
{
	glUniform3f(glGetUniformLocation(object_id, name), value.x, value.y, value.z);
}

void ShaderProgram::ChangeUniform(const char* name, glm::vec4 value)
{
	glUniform4f(glGetUniformLocation(object_id, name), value.x, value.y, value.z, value.w);
}

void ShaderProgram::ChangeUniform(const char* name, glm::mat4 value)
{
	glUniformMatrix4fv(glGetUniformLocation(object_id, name), 1, false, glm::value_ptr(value));
}

void ShaderProgram::Validate() const
{
	int success;
	glGetProgramiv(object_id, GL_LINK_STATUS, &success);	//Checks the program's linkage status
	if (!success) {
		char log[255];
		glGetProgramInfoLog(object_id, 255, NULL, log);	 //Writes the error if it has failed to link the program
		std::cout << log<<"\n";
		return;
	}
}
