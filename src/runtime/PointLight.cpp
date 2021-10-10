#include "PointLight.h"

void PointLight::SetUniforms() const
{
	program->use();
	program->setVec3("pointLights[" + std::to_string(lightIdx) + "].position", position);
	program->setVec3("pointLights[" + std::to_string(lightIdx) + "].ambient", ambient);
	program->setVec3("pointLights[" + std::to_string(lightIdx) + "].diffuse", diffuse);
	program->setVec3("pointLights[" + std::to_string(lightIdx) + "].specular", specular);
	program->setFloat("pointLights[" + std::to_string(lightIdx) + "].constant", constant);
	program->setFloat("pointLights[" + std::to_string(lightIdx) + "].linear", linear);
	program->setFloat("pointLights[" + std::to_string(lightIdx) + "].quadratic", quadratic);
}
