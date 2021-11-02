#include "planemesh.h"
#include <vector>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include "program.h"
#include "uiframework.h"

void PlaneMesh::SetCenter(glm::vec3& c)
{
    center = c;
}

void PlaneMesh::SetScaler(glm::vec3& c)
{
    scaler = c;
}

void PlaneMesh::Draw()
{
    std::shared_ptr<ShaderBase> prog = Program::GetInstance().GetProgram(ProgramType::SimpleColored);
    glm::mat4 modelMatrix = glm::mat4(1.0);
    modelMatrix = glm::translate(modelMatrix, center);
    modelMatrix = glm::scale(modelMatrix, scaler);
    prog->SetMVP(modelMatrix, UIFramework::Instance().camera->GetViewMatirx(), UIFramework::Instance().camera->GetProjectionMatrix());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}