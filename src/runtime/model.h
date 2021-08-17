#pragma once
#ifndef MODEL_H
#define MODEL_H
#include <vector>
#include <string>
#include <assimp/Importer.hpp> 
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "mesh.h"
class Model {
public:
	Model() = default;
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
	std::vector<Mesh*> meshes;
};

#endif // !MODEL_H
