#include "scene.h"
void Scene::LoadScene()
{
	Model* newmodel = new Model();
	newmodel->LoadModel(std::string("F:/GitHub/CGCenter/3dmodels/1wo59wc1ii-wild town/wild town/wild town.obj"));
	models.push_back(newmodel);

}

void Scene::Draw()
{
	for (Model* model : models) {
		model->Draw();
	}
}

void Scene::DeleteScene()
{
	for (Model* model : models) {
		delete model;
	}
	models.clear();
}