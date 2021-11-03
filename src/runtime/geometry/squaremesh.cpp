#include "squaremesh.h"
#include <vector>
#include <GL/glew.h>
#include "meshconstdata.h"

void SquareMesh::LoadMesh()
{
    // Todo: add squaremesh
    std::vector<unsigned int> indices(std::begin(g_squareElementIndices), std::end(g_squareElementIndices));
    std::vector<Vertex> vertices(3);
    for (int i = 0; i < 3; i++) {
        vertices[i].position = glm::vec3(g_squareElementVertices[3 * i], g_squareElementVertices[3 * i + 1], g_squareElementVertices[3 * i + 2]);
        vertices[i].normal = glm::vec3(0.0f, 1.0f, 0.0f);
        vertices[i].texCoords = glm::vec2(0.0f, 0.0f);
    }
    glGenVertexArrays(1, &VAO);
    // 1. °ó¶¨VAO
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);
}