#include "cubemesh.h"
#include "meshconstdata.h"
namespace Zxen {
    void CubeMesh::Setup(const char* inname)
    {
        name = inname;
        vertices.vertexCount = 36;
    }

    void CubeMesh::Submit()
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_cubeArrayVertices), &g_cubeArrayVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    }
}