#pragma once
#ifndef MESH_H
#define MESH_H
#include "shader.h"

class Mesh {
public:
	Mesh() = default;
	~Mesh() = default;
	void LoadMesh();
	void Draw();
private:
	Shader* shader = nullptr;
	unsigned int VBO = 0;
	unsigned int VAO = 0;
	unsigned int colorbuffer = 0;
};
#endif // !MESH_H
