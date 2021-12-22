#pragma once
#ifndef LIGHT_H
#define LIGHT_H
#include <memory>
#include <glm/vec3.hpp>
#include "program.h"
namespace Zxen {
	class Light {
	public:
		Light()
		{
		}
		virtual ~Light() = default;
		void Setup(glm::vec3 amb, glm::vec3 diffu, glm::vec3 spec)
		{
			ambient = amb;
			diffuse = diffu;
			specular = spec;
		}
		virtual void SetUniforms(ProgramPtr program) const = 0;
	protected:
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};
}
#endif // !LIGHT_H
