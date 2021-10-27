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
	virtual void Draw() override;
	void SetCenter(glm::vec3& c);
	void SetScaler(glm::vec3& c);
private:
	glm::vec3 center{ 0.0f, 0.0f, 0.0f };
	glm::vec3 scaler{ 1.0f, 1.0f, 1.0f };
};

#endif
