#include "trianglemesh.h"
#include <vector>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include "meshconstdata.h"
#include "program.h"
#include "uiframework.h"
void TriangleMesh::SetCenter(glm::vec3& c)
{
    center = c;
}

void TriangleMesh::SetScaler(glm::vec3& c)
{
    scaler = c;
}

void TriangleMesh::LoadMesh()
{
    std::vector<unsigned int> tmpindices (std::begin(g_triangleElementIndices), std::end(g_triangleElementIndices));
    std::vector<Vertex> tmpvertices(3);
    for (int i = 0; i < 3; i++) {
        tmpvertices[i].position = glm::vec3(g_triangleElementVertices[3 * i], g_triangleElementVertices[3 * i + 1], g_triangleElementVertices[3 * i + 2]);
        tmpvertices[i].normal = glm::vec3(1.0f, 1.0f, 1.0f);
        tmpvertices[i].texCoords = glm::vec2(0.0f, 0.0f);
    }
    glGenVertexArrays(1, &VAO);
    // 1. °ó¶¨VAO
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * tmpvertices.size(), tmpvertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * tmpindices.size(), tmpindices.data(), GL_STATIC_DRAW);
    indices = std::move(tmpindices);
    vertices = std::move(tmpvertices);
}

void TriangleMesh::Draw()
{
    std::shared_ptr<ShaderBase> prog = Program::GetInstance().GetProgram(ProgramType::SimpleColored);
    glm::mat4 modelMatrix = glm::mat4(1.0);
    modelMatrix = glm::translate(modelMatrix, center);
    modelMatrix = glm::scale(modelMatrix, scaler);
    prog->SetMVP(modelMatrix, UIFramework::Instance().camera->GetViewMatirx(), UIFramework::Instance().camera->GetProjectionMatrix());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT,0);
}
