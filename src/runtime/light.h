#pragma once
#ifndef LIGHT_H
#define LIGHT_H
#include <memory>
#include <glm/vec3.hpp>
#include "shaderBase.h"

class Light {
public:
	Light()
	{
	}
	virtual ~Light() = default;

private:
	glm::vec3 direction;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	std::shared_ptr<ShaderBase> program;
};
#endif // !LIGHT_H
