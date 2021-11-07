#pragma once
#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include <string>
#include <memory>
#include "model.h"
#include "light.h"
#include "cubemap.h"
#include "planemesh.h"
#include "depthpass.h"
#include "forward_main_pass.h"
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
	std::shared_ptr<DepthPass> depthPass;
	std::shared_ptr<ForwardMainPass> forwardMainPass;
};
#endif // !SCENE_H
