#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glm/mat4x4.hpp>

class Shader {
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath) 
        : m_vertexPath(vertexPath), m_fragmentPath(fragmentPath){ }
    ~Shader()
    {
    }

    void ProduceProgram();
    void use();
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void SetMVP(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection) const;

private:
    std::string m_vertexPath;
    std::string m_fragmentPath;

    unsigned int programID = 0;
    void checkCompileErrors(unsigned int shader, std::string type);
};
#endif