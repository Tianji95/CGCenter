#include "zxEngine.h"
#include "resourceManager.h"
#include "scene.h"
#include "render.h"
#include "render/forwardRender.h"
namespace Zxen {
	ResourceManager* ZXEngine::CreateResourceManager()
	{
		rsm = new ResourceManager();
		return rsm;
	}

	Scene* ZXEngine::CreateScene()
	{
		scene = new Scene(this);
		return scene;
	}

	Scene* ZXEngine::GetScene()
	{
		return scene;
	}

	ResourceManager* ZXEngine::GetResourceManager()
	{
		return rsm;
	}

	Render* ZXEngine::GetRender()
	{
		return render;
	}

	void ZXEngine::DestoryRender()
	{
		delete render;
	}

	void ZXEngine::DestoryScene()
	{
		delete scene;
	}

	void ZXEngine::DestoryResourceManager()
	{
		delete rsm;
	}
}