#pragma once
#ifndef MESH_H
#define MESH_H
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include "vertexbuffer.h"
#include "indexbuffer.h"
#include "material.h"
#include "camera.h"
namespace Zxen {
	enum class RenderPassType {
		FORWARD,
		SHADOW,
		MAX_RENDERPASS
	};

	class Mesh {
	public:
		Mesh() = default;
		Mesh(unsigned int handle) :handle(handle)
		{
		}
		~Mesh() = default;
		void Setup(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, const char* name);
		void Submit();
		void DrawArrays(CameraPtr camera, RenderPassType type);
		void DrawElements(CameraPtr camera, RenderPassType type);
		void Delete();
		void AddMaterials(RenderPassType type, MaterialPtr material);
		void UpdateProgram(RenderPassType type, ProgramPtr program);
	protected:
		unsigned int handle;
		VertexBuffer vertices;
		IndexBuffer indices;
		const char* name;
		unsigned int VBO = 0;
		unsigned int VAO = 0;
		unsigned int IBO = 0;
		std::unordered_map<RenderPassType, MaterialPtr> materialMap;
	};

	using MeshPtr = std::shared_ptr<Mesh>;
}
#endif // !MESH_H
