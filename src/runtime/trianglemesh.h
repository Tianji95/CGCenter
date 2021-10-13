#pragma once
#ifndef TRIANGLE_MESH_H
#define TRIANGLE_MESH_H
#include <memory>
#include "mesh.h"

class TriangleMesh : public Mesh {
public:
	TriangleMesh() = default;
	~TriangleMesh() = default;
	virtual void LoadMesh() override;
private:

};

#endif
