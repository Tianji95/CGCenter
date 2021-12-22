#pragma once
#ifndef PLANE_MESH_H
#define PLANE_MESH_H
#include "mesh.h"
namespace Zxen {
	class PlaneMesh : public Mesh {
	public:
		PlaneMesh() = default;
		~PlaneMesh() = default;
		void SetCenter(glm::vec3& c);
		void SetScaler(glm::vec3& c);
		void DrawElements(CameraPtr camera, RenderPassType type);
	protected:
		glm::vec3 center{ 0.0f, 0.0f, 0.0f };
		glm::vec3 scaler{ 1.0f, 1.0f, 1.0f };
	};

}

#endif // !PLANE_MESH_H
