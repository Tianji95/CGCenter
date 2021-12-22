#include "planemesh.h"
#include <vector>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include "program.h"
namespace Zxen {
    void PlaneMesh::SetCenter(glm::vec3& c)
    {
        center = c;
    }

    void PlaneMesh::SetScaler(glm::vec3& c)
    {
        scaler = c;
    }

    void PlaneMesh::DrawElements(CameraPtr camera, RenderPassType type)
    {
        glm::mat4 modelMatrix = glm::mat4(1.0);
        modelMatrix = glm::translate(modelMatrix, center);
        modelMatrix = glm::scale(modelMatrix, scaler);
        materialMap[type]->program->use();
        materialMap[type]->program->SetMVP(modelMatrix, camera->GetViewMatirx(), camera->GetProjectionMatrix());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.indexCount, GL_UNSIGNED_INT, 0);
    }
}