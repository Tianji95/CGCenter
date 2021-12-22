#include "mesh.h"
#include <GL/glew.h>
namespace Zxen {
    void Mesh::Submit()
    {
        glGenVertexArrays(1, &VAO);
        // 1. °ó¶¨VAO
        glBindVertexArray(VAO);
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.vertexCount, vertices.buffer, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(8 * sizeof(float)));
        glEnableVertexAttribArray(3);

        glGenBuffers(1, &IBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.GetDataTypeSize() * indices.indexCount, indices.buffer, GL_STATIC_DRAW);
    }

    void Mesh::Setup(std::vector<Vertex>& inVertices, std::vector<unsigned int>& inIndices, const char* inname)
    {
        vertices.vertexCount = inVertices.size();
        vertices.buffer = std::move(inVertices.data());
        indices.indexCount = inIndices.size();
        indices.buffer = std::move(inIndices.data());
        indices.type = GL_UNSIGNED_INT;
        name = inname;
    }

    void Mesh::DrawElements(CameraPtr camera, RenderPassType type)
    {
        if (materialMap.find(type) == materialMap.end()) {
            return;
        }
        glm::mat4 modelMatrix = glm::mat4(1.0);
        materialMap[type]->program->SetMVP(modelMatrix, camera->GetViewMatirx(), camera->GetProjectionMatrix());
        materialMap[type]->program->setVec3("cameraPos", camera->GetPosition());
        materialMap[type]->program->setFloat("material.shininess", 20.0f);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        for (unsigned int i = 0; i < materialMap[type]->texs.size(); i++) {
            auto textureID = glGetUniformLocation(materialMap[type]->program->GetID(), materialMap[type]->texs[i]->GetTextureTypeName().c_str());
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, materialMap[type]->texs[i]->GetTextureID());
            glUniform1i(textureID, i);
        }
        glDrawElements(GL_TRIANGLES, indices.indexCount, indices.type, 0);
    }

    void Mesh::DrawArrays(CameraPtr camera, RenderPassType type)
    {
        if (materialMap.find(type) == materialMap.end()) {
            return;
        }
        glm::mat4 modelMatrix = glm::mat4(1.0);
        // TODO: here glm::mat4(glm::mat3( is a bug
        materialMap[type]->program->SetMVP(modelMatrix, glm::mat4(glm::mat3(camera->GetViewMatirx())), camera->GetProjectionMatrix());
        materialMap[type]->program->setVec3("cameraPos", camera->GetPosition());
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        for (unsigned int i = 0; i < materialMap[type]->texs.size(); i++) {
            auto textureID = glGetUniformLocation(materialMap[type]->program->GetID(), materialMap[type]->texs[i]->GetTextureTypeName().c_str());
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(materialMap[type]->texs[i]->bindType, materialMap[type]->texs[i]->GetTextureID());
            glUniform1i(textureID, i);
        }
        glDrawArrays(GL_TRIANGLES, 0, vertices.vertexCount);
    }

    void Mesh::Delete()
    {
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &IBO);
        glDeleteVertexArrays(1, &VAO);
    }

    void Mesh::AddMaterials(RenderPassType type, MaterialPtr material)
    {
        materialMap[type] = material;
    }

    void Mesh::UpdateProgram(RenderPassType type, ProgramPtr program)
    {
        materialMap[type]->program = program;
    }
}