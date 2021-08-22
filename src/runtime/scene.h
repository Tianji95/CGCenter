#pragma once
#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include <string>
#include "model.h"
#include "light.h"

class Scene {
public:
	Scene() = default;
	~Scene()
	{
		DeleteScene();
	}
	void LoadScene();
	void Draw();
	void DeleteScene();
private:
	std::vector<Model*> models;
	std::vector<Light*> lights;
};
#endif // !SCENE_H
