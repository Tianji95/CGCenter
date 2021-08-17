#pragma once
#ifndef MESH_H
#define MESH_H
#include "shader.h"

struct Vertex{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};
struct Texture {
	int id;
};
class Mesh {
public:
	Mesh() = default;
	~Mesh() = default;
	void LoadMesh();
	void Draw();
	void DeleteMesh();
private:
	Shader* shader = nullptr;
	unsigned int VBO = 0;
	unsigned int VAO = 0;
	unsigned int colorbuffer = 0;
};

#endif // !MESH_H
