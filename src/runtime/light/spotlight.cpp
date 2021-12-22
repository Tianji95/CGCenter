#include "spotlight.h"
#include<glm/gtx/transform.hpp>
namespace Zxen {
	void SpotLight::Setup(glm::vec3 pos, glm::vec3 direct, glm::vec3 amb, glm::vec3 diffu, glm::vec3 spec,
		float cO, float outerCO, float cons, float lin, float quad, int idx)
	{
		position = pos;
		direction = direct;
		ambient = amb;
		diffuse = diffu;
		specular = spec;
		cutOff = cO;
		outerCutOff = outerCO;
		constant = cons;
		linear = lin;
		quadratic = quad;
		lightIdx = idx;
	}


	void SpotLight::Setup(glm::vec3 amb, glm::vec3 diffu, glm::vec3 spec,
		float cO, float outerCO, float cons, float lin, float quad)
	{
		ambient = amb;
		diffuse = diffu;
		specular = spec;
		cutOff = cO;
		outerCutOff = outerCO;
		constant = cons;
		linear = lin;
		quadratic = quad;
	}

	void SpotLight::SetUniforms(ProgramPtr program) const
	{
		program->setVec3("spotLights[" + std::to_string(lightIdx) + "].position", position);
		program->setVec3("spotLights[" + std::to_string(lightIdx) + "].direction", direction);
		program->setFloat("spotLights[" + std::to_string(lightIdx) + "].cutOff", cutOff);
		program->setFloat("spotLights[" + std::to_string(lightIdx) + "].outerCutOff", outerCutOff);

		program->setVec3("spotLights[" + std::to_string(lightIdx) + "].ambient", ambient.x, ambient.y, ambient.z);
		program->setVec3("spotLights[" + std::to_string(lightIdx) + "].diffuse", diffuse.x, diffuse.y, diffuse.z);
		program->setVec3("spotLights[" + std::to_string(lightIdx) + "].specular", specular.x, specular.y, specular.z);
		program->setFloat("spotLights[" + std::to_string(lightIdx) + "].constant", constant);
		program->setFloat("spotLights[" + std::to_string(lightIdx) + "].linear", linear);
		program->setFloat("spotLights[" + std::to_string(lightIdx) + "].quadratic", quadratic);
	}
}