#pragma once
#ifndef MESH_H
#define MESH_H
#include <vector>
#include "shader.h"

struct Vertex{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
};

//struct Texture {
//	int id;
//};



class Mesh {
public:
	Mesh() = default;
	Mesh(std::vector<Vertex>& verts, std::vector<unsigned int>& inds, const char* nm) :vertices(verts), indices(inds), name(nm){
		LoadMesh();
	}
	~Mesh() = default;
	void LoadMesh();
	void Draw();
	void DeleteMesh();
private:
	Shader* shader = nullptr;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	const char* name;
	// std::vector<Texture> textures;
	unsigned int VBO = 0;
	unsigned int VAO = 0;
	unsigned int IBO = 0;
	unsigned int colorbuffer = 0;
};

#endif // !MESH_H
