#pragma once
#ifndef RENDER_H
#define RENDER_H

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
	void DeleteResources();
private:
	Camera* camera = nullptr;
	Scene* scene = nullptr;
};

#endif // !RENDER_H
