#pragma once
#ifndef CUBEMAP_H
#define CUBEMAP_H
#include <string>
#include <vector>
#include <memory>
#include "shaderBase.h"

class CubeMap {
public:
	struct TextureDirectory {
		std::string right;
		std::string left;
		std::string top;
		std::string bottom;
		std::string front;
		std::string back;
	};
	CubeMap(std::shared_ptr<ShaderBase> prog): program(prog){ }
	~CubeMap(){ }
	void Draw();
	bool GenResources(const TextureDirectory& texDir);

protected:
	bool GenVertices();
	bool GenTextures(const TextureDirectory& texDir);

	void DelResources();
protected:
	unsigned int VAO = 0;
	unsigned int VBO = 0;
	unsigned int textureID = 0;
	std::shared_ptr<ShaderBase> program;
};

#endif // !CUBEMAP_H
