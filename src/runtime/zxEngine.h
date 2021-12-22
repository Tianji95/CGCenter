#pragma once
#ifndef ZXENGINE_H
#define ZXENGINE_H
#include <memory>
#include "render/forwardRender.h"
namespace Zxen {
	class ZXEngine {
	public:
		ZXEngine() = default;
		~ZXEngine() = default;
		ResourceManager* CreateResourceManager();
		Scene* CreateScene();

		template<typename T>
		Render* CreateRender()
		{
			if (render == nullptr) {
				render = new T(this);
			}
			return render;
		}

		Scene* GetScene();
		ResourceManager* GetResourceManager();
		Render* GetRender();

		void DestoryRender();
		void DestoryScene();
		void DestoryResourceManager();

	private:
		ResourceManager* rsm;
		Scene* scene;
		Render* render;
	};
}
#endif // !ENGINE_H
