#include "mesh.h"
#include <GL/glew.h>
#include "uiframework.h"

void Mesh::LoadMesh()
{
    glGenVertexArrays(1, &VAO);
    // 1. °ó¶¨VAO
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*vertices.size(), vertices.data(), GL_STATIC_DRAW);
    shader = new Shader("F:/GitHub/CGCenter/src/shaders/test.vert", "F:/GitHub/CGCenter/src/shaders/test.frag");
    shader->ProduceProgram();

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3,  GL_FLOAT,  GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)* indices.size(), indices.data(), GL_STATIC_DRAW);

}
void Mesh::Draw()
{
    glm::mat4 modelMatrix = glm::mat4(1.0);
    shader->SetMVP(modelMatrix, UIFramework::Instance().camera->GetViewMatirx(), UIFramework::Instance().camera->GetProjectionMatrix());
    shader->use();
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    for (auto texture : textures) {
        if (texture.type == "texture_diffuse") {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture.id);
        }
    }
    glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, 0);
}

void Mesh::DeleteMesh()
{
    delete shader;
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &IBO);
    glDeleteVertexArrays(1, &VAO);
}

