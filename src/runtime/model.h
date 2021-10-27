#pragma once
#ifndef MODEL_H
#define MODEL_H
#include <vector>
#include <string>
#include <memory>
#include <assimp/Importer.hpp> 
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "mesh.h"
#include "shaderBase.h"

class Model {
public:
	Model() { }
	~Model()
	{
		DeleteModel();
	}
	void LoadModel(std::string& path);
	void Draw();
	void DeleteModel();
private:
	void ProcessNode(aiNode* node, const aiScene* scene);
	void ProcessMesh(aiMesh* mesh, const aiScene* scene);
	unsigned int TextureFromFile(const char* path, const std::string& directory);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	std::vector<std::shared_ptr<Mesh*>> meshes;
	std::vector<Texture> textures_loaded;
	std::string modelPath;
};

#endif // !MODEL_H
