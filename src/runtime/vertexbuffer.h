#pragma once
#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
namespace Zxen {
	struct Vertex {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 uv0;
		glm::vec2 uv1;
	};

	struct VertexBuffer {
		Vertex* buffer;
		unsigned int vertexCount;
	};
}
#endif // !VERTEX_BUFFER_H
