#pragma once
#ifndef MESH_H
#define MESH_H
#include <vector>
#include <string>
#include <memory>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include "shaderBase.h"
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

struct Material {
	std::vector<Texture> texs;
	glm::vec3 colorDiffuse;
	glm::vec3 colorSpecular;
	glm::vec3 colorAmbiend;
	glm::vec3 colorEmissive;
	glm::vec3 colorTransparent;
	float opacity;
	float shininess;
	float shininessStrength;
	float reflection;
	float refraction;
	float transparentFactor;
	int shadingModel;
	int blendFunc;
};

class Mesh {
public:
	Mesh() = default;
	Mesh(std::vector<Vertex>& verts, std::vector<unsigned int>& inds, Material mat, const char* nm, std::shared_ptr<ShaderBase> prog) :vertices(verts), indices(inds), material(mat), name(nm), program(prog){
		LoadMesh();
	}
	~Mesh() = default;
	void LoadMesh();
	void Draw();
	void DeleteMesh();
private:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	const char* name;
	// std::vector<Texture> textures;
	unsigned int VBO = 0;
	unsigned int VAO = 0;
	unsigned int IBO = 0;
	unsigned int colorbuffer = 0;
	Material material;
	std::shared_ptr<ShaderBase> program;
};

#endif // !MESH_H
