#include "PointLight.h"
namespace Zxen {
	void PointLight::Setup(glm::vec3 pos, glm::vec3 amb, glm::vec3 diffu, glm::vec3 spec, float cons, float lin, float quad, int idx)
	{
		position = pos;
		ambient = amb;
		diffuse = diffu;
		specular = spec;
		constant = cons;
		linear = lin;
		quadratic = quad;
		lightIdx = idx;
	}

	void PointLight::Setup(glm::vec3 amb, glm::vec3 diffu, glm::vec3 spec, float cons, float lin, float quad)
	{
		ambient = amb;
		diffuse = diffu;
		specular = spec;
		constant = cons;
		linear = lin;
		quadratic = quad;
	}

	void PointLight::SetUniforms(ProgramPtr program) const
	{
		program->setVec3("pointLights[" + std::to_string(lightIdx) + "].position", position);
		program->setVec3("pointLights[" + std::to_string(lightIdx) + "].ambient", ambient.x, ambient.y, ambient.z);
		program->setVec3("pointLights[" + std::to_string(lightIdx) + "].diffuse", diffuse.x, diffuse.y, diffuse.z);
		program->setVec3("pointLights[" + std::to_string(lightIdx) + "].specular", specular.x, specular.y, specular.z);
		program->setFloat("pointLights[" + std::to_string(lightIdx) + "].constant", constant);
		program->setFloat("pointLights[" + std::to_string(lightIdx) + "].linear", linear);
		program->setFloat("pointLights[" + std::to_string(lightIdx) + "].quadratic", quadratic);
	}
}