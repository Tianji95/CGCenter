#include "trianglemesh.h"
#include <vector>
#include "meshconstdata.h"
namespace Zxen {
    void TriangleMesh::Setup(const char* ininname)
    {
        std::vector<unsigned int> tmpidx = std::vector<unsigned int>(std::begin(g_triangleElementIndices), std::end(g_triangleElementIndices));
        indices.indexCount = tmpidx.size();
        indices.buffer = std::move(tmpidx.data());
        indices.type = GL_UNSIGNED_INT;
        std::vector<Vertex> tmpvertices = std::vector<Vertex>(3);
        for (int i = 0; i < 3; i++) {
            tmpvertices[i].position = glm::vec3(g_triangleElementVertices[3 * i], g_triangleElementVertices[3 * i + 1], g_triangleElementVertices[3 * i + 2]);
            tmpvertices[i].normal = glm::vec3(1.0f, 1.0f, 1.0f);
            tmpvertices[i].uv0 = glm::vec2(0.0f, 0.0f);
            tmpvertices[i].uv1 = glm::vec2(0.0f, 0.0f);
        }
        vertices.vertexCount = tmpvertices.size();
        vertices.buffer = std::move(tmpvertices.data());
        name = ininname;
    }

}