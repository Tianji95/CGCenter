#pragma once
#ifndef SHADER_BASE_H
#define SHADER_BASE_H

#include <string>
#include <glm/mat4x4.hpp>

class ShaderBase {
public:
    ShaderBase(const std::string& vertexPath, const std::string& fragmentPath)
        : m_vertexPath(vertexPath), m_fragmentPath(fragmentPath){ }
    ~ShaderBase()
    {
    }

    void ProduceProgram();
    void use();
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec2(const std::string& name, const glm::vec2& value) const;
    void setVec2(const std::string& name, float x, float y) const;
    void setVec3(const std::string& name, const glm::vec3& value) const;
    void setVec3(const std::string& name, float x, float y, float z) const;
    void setVec4(const std::string& name, const glm::vec4& value) const;
    void setVec4(const std::string& name, float x, float y, float z, float w) const;
    void setMat2(const std::string& name, const glm::mat2& mat) const;
    void setMat3(const std::string& name, const glm::mat3& mat) const;
    void setMat4(const std::string& name, const glm::mat4& mat) const;
    void SetMVP(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection) const;
    unsigned int GetID();

private:
    std::string m_vertexPath;
    std::string m_fragmentPath;

    unsigned int programID = 0;
    void checkCompileErrors(unsigned int shader, std::string type);
};
#endif