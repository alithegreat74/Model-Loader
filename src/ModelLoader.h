#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <vector>
#include "Shader.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <stb_image.h>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
};

struct Texture
{
	unsigned int id;
	std::string type;
	std::string path;
};

class Mesh {
public:
	std::vector<Vertex> vericies;
	std::vector<unsigned int> indicies;
	std::vector<Texture> textures;
	Mesh(std::vector<Vertex> verticies, std::vector<unsigned int>indicies, std::vector<Texture> textures);
	void Draw(ShaderProgram& shader);
private:
	unsigned int vao, vbo, ebo;
	void SetupMesh();
};

class Model {
public:
	Model(std::string path);
	void Draw(ShaderProgram& shader);
private:
	std::vector<Mesh> meshes;
	std::string directory;

	std::vector<Texture> texturesLoaded;
	void LoadModel(std::string path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> LoadTextures(aiMaterial* mat, aiTextureType textureType, std::string typeName);

};


static unsigned int TextureFromFile(const char* path, const std::string& directory);