#pragma once
#ifndef RENDER_H
#define RENDER_H
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "camera.h"
#include "shader.h"
#include "scene.h"

class Render {
public:
	Render(Camera* cam) : camera(cam)
	{

	}
	~Render() = default;
	void GenResources();
	void DrawScene() const;
private:
	Camera* camera = nullptr;
	Shader* shader = nullptr;
	unsigned int VBO = 0;
	unsigned int VAO = 0;
	unsigned int colorbuffer = 0;
	const aiScene* assimpScene = nullptr;
	Scene* scene = nullptr;

};

#endif // !RENDER_H
