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
	Mesh* newmesh = new Mesh();
	newmesh->LoadMesh();
	meshes.push_back(newmesh);
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
	std::vector<int> indices;
	std::vector<Texture> textures;
	for (int i = 0; i < mesh->mNumVertices; i++) {
		glm::vec3 vector;
		Vertex vertex;
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;
		vertices.push_back(vertex);
	}
	for (int i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
	if (mesh->mTextureCoords[0]) {
		glm::vec2 vec;
		Vertex vertex;
		//vec.x = mesh->mTextureCoords[0][i].x;
		//vec.y = mesh->mTextureCoords[0][i].y;
		vertex.TexCoords = vec;
	}
	else {
		Vertex vertex;
		vertex.TexCoords = glm::vec2(0.0f, 0.0f);

	}
	// Mesh(vertices, indices, textures);
	return;
}

void Model::Draw()
{
	for (Mesh* mesh : meshes) {
		mesh->Draw();
	}
}

void Model::DeleteModel()
{
	for (Mesh* mesh : meshes) {
		mesh->DeleteMesh();
		delete mesh;
	}
	meshes.clear();
}
