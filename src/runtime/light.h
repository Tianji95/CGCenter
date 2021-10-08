#pragma once
#ifndef LIGHT_H
#define LIGHT_H
#include <memory>
#include <glm/vec3.hpp>
#include "shaderBase.h"

class Light {
public:
	Light(glm::vec3 amb, glm::vec3 diffu, glm::vec3 spec, std::shared_ptr<ShaderBase> prog):
		ambient(amb), diffuse(diffu), specular(spec), program(prog)
	{
	}
	virtual ~Light() = default;
	virtual void SetUniforms() const = 0;
protected:
	std::shared_ptr<ShaderBase> program;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};
#endif // !LIGHT_H
