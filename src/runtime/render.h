#pragma once
#ifndef RENDER_H
#define RENDER_H
#include <assimp/include/cimport.h>
#include <assimp/include/scene.h>
#include <assimp/include/postprocess.h>
#include "camera.h"
#include "shader.h"
class Render {
public:
	Render(Camera* cam) : camera(cam)
	{

	}
	~Render() = default;
	void GenResources();
	void DrawScene() const;
private:
	Camera* camera;
	Shader* shader;
	unsigned int VBO = 0;
	unsigned int VAO = 0;
	unsigned int colorbuffer = 0;
	const aiScene* scene = NULL;
};

#endif // !RENDER_H
