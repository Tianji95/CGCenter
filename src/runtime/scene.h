#pragma once
#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include <string>
#include <memory>
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
	std::vector<std::shared_ptr<Model>> models;
	std::vector<std::shared_ptr<Light>> lights;
};
#endif // !SCENE_H
