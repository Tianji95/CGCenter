#pragma once
#ifndef TRIANGLE_MESH_H
#define TRIANGLE_MESH_H
#include "planemesh.h"
namespace Zxen {
	class TriangleMesh : public PlaneMesh {
	public:
		TriangleMesh() = default;
		~TriangleMesh() = default;
		virtual void Setup(const char* ininname);
	};
}
#endif
