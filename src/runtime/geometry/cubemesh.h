#pragma once
#ifndef CUBE_MESH_H
#define CUBE_MESH_H
#include "mesh.h"
namespace Zxen {
	class CubeMesh : public Mesh {
	public:
		CubeMesh() = default;
		~CubeMesh() = default;
		void Setup(const char* inname);
		void Submit();
	private:

	};

	using CubeMeshPtr = std::shared_ptr<CubeMesh>;
}
#endif // !CUBE_MESH_H
