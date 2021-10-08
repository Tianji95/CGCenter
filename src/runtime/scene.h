#pragma once
#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include <string>
#include <memory>
#include "model.h"
#include "light.h"
#include "shaderBase.h"

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
	std::shared_ptr<ShaderBase> testProgram;
	std::shared_ptr<ShaderBase> mainProgram;
	std::string SRC_BASE_PATH = "F:/GitHub/CGCenter/";
};
#endif // !SCENE_H
