#pragma once
#ifndef SQUARE_MESH_H
#define SQUARE_MESH_H
#include "mesh.h"

class SquareMesh : public Mesh {
public:
	SquareMesh() = default;
	~SquareMesh() = default;
	virtual void LoadMesh() override;
private:

};

#endif