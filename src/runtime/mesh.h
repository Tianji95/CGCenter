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

struct Texture {
	unsigned int id;
	std::string type;
	std::string path;
};

class Mesh {
public:
	Mesh() = default;
	Mesh(std::vector<Vertex>& verts, std::vector<unsigned int>& inds, std::vector<Texture> texs, const char* nm) :vertices(verts), indices(inds), textures(texs), name(nm){
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
	std::vector<Texture> textures;
};

#endif // !MESH_H
