#pragma once
#ifndef SKYBOX_H
#define SKYBOX_H
#include <unordered_map>
#include <memory>
#include "mesh.h"
#include "program.h"
#include "camera.h"
namespace Zxen {
	class Skybox {
	public:
		Skybox() = default;
		~Skybox() = default;
		void Setup(MeshPtr mesh, ProgramPtr prog)
		{
			this->mesh = mesh;
			program = prog;
		}
		void Render(CameraPtr camera);
		ProgramPtr GetProgram()
		{
			return program;
		}
	private:
		MeshPtr mesh;
		ProgramPtr program;
	};

	using SkyboxPtr = std::shared_ptr<Skybox>;
}
#endif // !SKYBOX_H
