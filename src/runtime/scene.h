#pragma once
#ifndef SCENE_H
#define SCENE_H
#include "resourceManager.h"
#include "camera.h"
namespace Zxen {
	class ZXEngine;
	class Scene {
	public:
		Scene(ZXEngine* engine) : engine(engine)
		{
		}
		~Scene()
		{
		}
		CameraPtr GetCamera();
		CameraPtr CreateCamera();
	private:
		ZXEngine* engine = nullptr;

		int windowWidth = 1024;
		int windowHeight = 1024;
		// refractor
	// std::unordered_map<int, std::vector<Component*>> shared_data;
		CameraPtr camera = nullptr;

	};
}
#endif // !SCENE_H
