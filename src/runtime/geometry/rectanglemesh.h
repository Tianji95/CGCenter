#pragma once
#ifndef RECTANGLE_MESH_H
#define RECTANGLE_MESH_H
#include "planemesh.h"
#include <memory>
namespace Zxen {
	class RectangleMesh : public PlaneMesh {
	public:
		RectangleMesh() = default;
		~RectangleMesh() = default;
		void Setup(const char* inname);
	};

	using RectangleMeshPtr = std::shared_ptr<RectangleMesh>;
}
#endif // !RECTANGLE_MESH_H
