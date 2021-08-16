#include "model.h"
void Model::LoadModel()
{
	Mesh* newmesh = new Mesh();
	newmesh->LoadMesh();
	meshes.push_back(newmesh);
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
