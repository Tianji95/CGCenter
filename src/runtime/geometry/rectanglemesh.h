#pragma once
#ifndef RECTANGLE_MESH_H
#define RECTANGLE_MESH_H
#include "planemesh.h"

class RectangleMesh : public PlaneMesh {
public:
	RectangleMesh() = default;
	~RectangleMesh() = default;
	virtual void LoadMesh() override;
};


#endif // !RECTANGLE_MESH_H
