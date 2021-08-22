#pragma once
#ifndef LIGHT_H
#define LIGHT_H
#include <glm/vec3.hpp>
class Light {
public:
	Light() = default;
	~Light() = default;
private:
	glm::vec3 pos;
	glm::vec3 direction;
	glm::vec3 color;
};
#endif // !LIGHT_H
