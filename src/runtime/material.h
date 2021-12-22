#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H
#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include "texture.h"
#include "program.h"
namespace Zxen {
	class Material {
	public:
		Material(unsigned int handle) : handle(handle)
		{

		}
		~Material()
		{
		}

		unsigned int GetHandle()
		{
			return handle;
		}
	public:
		ProgramPtr program;
		unsigned int handle;
		std::vector<TexturePtr> texs;
		glm::vec3 colorDiffuse;
		glm::vec3 colorSpecular;
		glm::vec3 colorAmbiend;
		glm::vec3 colorEmissive;
		glm::vec3 colorTransparent;
		float opacity;
		float shininess;
		float shininessStrength;
		float reflection;
		float refraction;
		float transparentFactor;
		int shadingModel;
		int blendFunc;
	};
	using MaterialPtr = std::shared_ptr<Material>;
}
#endif // !MATERIAL_H
