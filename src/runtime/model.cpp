#include "model.h"
#include <iostream>


void Model::LoadModel(std::string& path)
{
	Assimp::Importer import;
	const aiScene* assimpScene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!assimpScene || assimpScene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !assimpScene->mRootNode) {
		std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
		return;
	}
	ProcessNode(assimpScene->mRootNode, assimpScene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
	// 添加当前节点中的所有Mesh  
	for (int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		this->ProcessMesh(mesh, scene);
	}
	// 递归处理该节点的子孙节点  
	for (int i = 0; i < node->mNumChildren; i++) {
		this->ProcessNode(node->mChildren[i], scene);
	}
} 

void Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	// std::vector<Texture> textures;
	for (int i = 0; i < mesh->mNumVertices; i++) {
		glm::vec3 pos;
		Vertex vertex;
		pos.x = mesh->mVertices[i].x;
		pos.y = mesh->mVertices[i].y;
		pos.z = mesh->mVertices[i].z;
		vertex.position = pos;
		if (mesh->mNormals) {
			glm::vec3 normal;
			normal.x = mesh->mNormals[i].x;
			normal.y = mesh->mNormals[i].y;
			normal.z = mesh->mNormals[i].z;
			vertex.normal = normal;
		}
		else {
			vertex.normal = glm::vec3(0.0f, 1.0f, 0.0f);
		}

		if (mesh->mTextureCoords[0]) {
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.texCoords = vec;
		}
		else {
			vertex.texCoords = glm::vec2(0.0f, 0.0f);
		}
		vertices.push_back(vertex);
	}

	for (int i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (int j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}

	meshes.push_back(std::make_shared<Mesh*>(new Mesh(vertices, indices, mesh->mName.C_Str())));
	return;
}

void Model::Draw()
{
	for (auto mesh : meshes) {
		(*mesh)->Draw();
	}
}

void Model::DeleteModel()
{
	for (auto mesh : meshes) {
		(*mesh)->DeleteMesh();
	}
	meshes.clear();
}
