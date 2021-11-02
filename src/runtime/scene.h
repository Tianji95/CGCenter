#pragma once
#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include <string>
#include <memory>
#include "model.h"
#include "light.h"
#include "shaderBase.h"
#include "cubemap.h"
#include "planemesh.h"


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
	std::vector<std::shared_ptr<PlaneMesh>> rectMeshes;

	std::shared_ptr<CubeMap> cubemap;
	std::shared_ptr<ShaderBase> testProgram;
	std::shared_ptr<ShaderBase> mainProgram;
	std::shared_ptr<ShaderBase> simpleColoredMeshProgram;
	std::shared_ptr<ShaderBase> skyBoxProgram;
};
#endif // !SCENE_H
