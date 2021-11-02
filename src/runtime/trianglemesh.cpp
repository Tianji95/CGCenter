#include "trianglemesh.h"
#include <vector>
#include "meshconstdata.h"

void TriangleMesh::LoadMesh()
{
    indices = std::vector<unsigned int>(std::begin(g_triangleElementIndices), std::end(g_triangleElementIndices));
    vertices = std::vector<Vertex>(3);
    for (int i = 0; i < 3; i++) {
        vertices[i].position = glm::vec3(g_triangleElementVertices[3 * i], g_triangleElementVertices[3 * i + 1], g_triangleElementVertices[3 * i + 2]);
        vertices[i].normal = glm::vec3(1.0f, 1.0f, 1.0f);
        vertices[i].texCoords = glm::vec2(0.0f, 0.0f);
    }
    Mesh::LoadMesh();
}

