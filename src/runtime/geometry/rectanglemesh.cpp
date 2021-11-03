#include "rectanglemesh.h"
#include <vector>
#include "meshconstdata.h"

void RectangleMesh::LoadMesh()
{
    indices = std::vector<unsigned int>(std::begin(g_squareElementIndices), std::end(g_squareElementIndices));
    vertices = std::vector<Vertex>(4);
    for (int i = 0; i < 4; i++) {
        vertices[i].position = glm::vec3(g_squareElementVertices[3 * i], g_squareElementVertices[3 * i + 1], g_squareElementVertices[3 * i + 2]);
        vertices[i].normal = glm::vec3(1.0f, 1.0f, 1.0f);
        vertices[i].texCoords = glm::vec2(0.0f, 0.0f);
    }
    Mesh::LoadMesh();
}

