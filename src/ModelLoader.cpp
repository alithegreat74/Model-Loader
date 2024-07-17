#include "ModelLoader.h"
#include "ModelLoader.h"

Mesh::Mesh(std::vector<Vertex> verticies, std::vector<unsigned int> indicies, std::vector<Texture> textures)
{
	this->vericies = verticies;
	this->indicies = indicies;
	this->textures = textures;

	SetupMesh();
}

void Mesh::Draw(ShaderProgram& shader)
{
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
		// retrieve texture number (the N in diffuse_textureN)
		std::string number;
		std::string name = textures[i].type;
		if (name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if (name == "texture_specular")
			number = std::to_string(specularNr++);

		shader.ChangeSingleUniform((name + number).c_str(), (int)i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}
	glActiveTexture(GL_TEXTURE0);


	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, indicies.size(), GL_UNSIGNED_INT, NULL);
	glBindVertexArray(0);
}

void Mesh::SetupMesh()
{
	//Generating the buffers
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vericies.size() * sizeof(Vertex), &vericies[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(unsigned int), &indicies[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

	glEnableVertexAttribArray(0);
}

Model::Model(std::string path)
{
	this->path = path;
	LoadModel(path);
}

void Model::Draw(ShaderProgram& shader)
{
	for (auto mesh : meshes) {
		mesh.Draw(shader);
	}
}

void Model::LoadModel(std::string path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate|aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "Unable to import file via assimp\n"<<importer.GetErrorString()<<std::endl;
		return;
	}

	directory = path.substr(0, path.find_last_of('\\'));
	ProcessNode(scene->mRootNode, scene);

}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(ProcessMesh(mesh, scene));
	}
	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		ProcessNode(node->mChildren[i], scene);
	}
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> verticies;
	std::vector<unsigned int> indicies;
	std::vector<Texture>textures;

	//Calculate verticies
	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		Vertex vertex;
		vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
		if (mesh->mTextureCoords[0]) 
			vertex.texCoords = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
		else
			vertex.texCoords = glm::vec2(0, 0);

		verticies.push_back(vertex);
	}

	//Calculate indicies
	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indicies.push_back(face.mIndices[j]);
	}
	//Calculate Textures

	if (mesh->mMaterialIndex >= 0) {
		aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<Texture> diffuseTex = LoadTextures(mat, aiTextureType_DIFFUSE, "texutre_diffuse");
		textures.insert(textures.end(), diffuseTex.begin(), diffuseTex.end());

		/*std::vector<Texture> specularTex = LoadTextures(mat, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularTex.begin(), specularTex.end());*/
	}
	
	return Mesh(verticies, indicies, textures);
}

std::vector<Texture> Model::LoadTextures(aiMaterial* mat, aiTextureType textureType, std::string typeName)
{
	std::vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(textureType); i++) {
		aiString path;
		mat->GetTexture(textureType, i, &path);
		Texture tex;
		tex.id = -1;
		for (auto texture : texturesLoaded) {
			if (path.C_Str() == texture.path) {
				tex.id = texture.id;
				break;
			}
		}
		if (tex.id == -1) {
			tex.id= TextureFromFile(path.C_Str(), directory);
			tex.type = typeName;
			tex.path = path.C_Str();
			textures.push_back(tex);
			texturesLoaded.push_back(tex);
		}
		
	}
	return textures;
}


unsigned int TextureFromFile(const char* path, const std::string& directory)
{
	std::string filename = std::string(path);
	if(filename.find(':')==filename.npos)
		filename = directory + '/' + filename;
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}
