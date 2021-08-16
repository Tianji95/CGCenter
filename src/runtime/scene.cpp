#include "scene.h"
void Scene::LoadScene()
{
	Model* newmodel = new Model();
	newmodel->LoadModel();
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