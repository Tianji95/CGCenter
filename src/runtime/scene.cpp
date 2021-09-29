#include "scene.h"
void Scene::LoadScene()
{
	auto newmodel = std::make_shared<Model>();
	// newmodel->LoadModel(std::string("F:/GitHub/CGCenter/3dmodels/backpack/backpack.obj"));
	newmodel->LoadModel(std::string("F:/GitHub/CGCenter/3dmodels/home/home.obj"));
	models.push_back(newmodel);
}

void Scene::Draw()
{
	for (auto model : models) {
		model->Draw();
	}
}

void Scene::DeleteScene()
{
	models.clear();
	lights.clear();
}