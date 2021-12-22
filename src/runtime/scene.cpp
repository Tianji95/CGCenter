#include "scene.h"
namespace Zxen {
	CameraPtr Scene::GetCamera()
	{
		return camera;
	}

	CameraPtr Scene::CreateCamera()
	{
		camera = std::make_shared<Camera>();
		return camera;
	}
}