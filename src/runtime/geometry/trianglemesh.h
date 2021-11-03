#pragma once
#ifndef TRIANGLE_MESH_H
#define TRIANGLE_MESH_H
#include "planemesh.h"

class TriangleMesh : public PlaneMesh {
public:
	TriangleMesh() = default;
	~TriangleMesh() = default;
	virtual void LoadMesh() override;
};

#endif
