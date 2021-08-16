#pragma once
#ifndef MODEL_H
#define MODEL_H
#include <vector>
#include "mesh.h"
class Model {
public:
	Model() = default;
	~Model()
	{
		DeleteModel();
	}
	void LoadModel();
	void Draw();
	void DeleteModel();
private:
	std::vector<Mesh*> meshes;
};

#endif // !MODEL_H
