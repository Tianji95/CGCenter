#include "spotlight.h"
#include "uiframework.h"
#include<glm/gtx/transform.hpp>
void SpotLight::SetUniforms() const
{
	program->use();
	//program->setVec3("pointLights[" + std::to_string(lightIdx) + "].position", position);
	//program->setVec3("pointLights[" + std::to_string(lightIdx) + "].ambient", ambient);
	//program->setVec3("pointLights[" + std::to_string(lightIdx) + "].diffuse", diffuse);
	//program->setVec3("pointLights[" + std::to_string(lightIdx) + "].specular", specular);
	//program->setFloat("pointLights[" + std::to_string(lightIdx) + "].constant", constant);
	//program->setFloat("pointLights[" + std::to_string(lightIdx) + "].linear", linear);
	//program->setFloat("pointLights[" + std::to_string(lightIdx) + "].quadratic", quadratic);
	program->setVec3("spotLight[" + std::to_string(lightIdx) + "].position", position);
	program->setVec3("spotLight[" + std::to_string(lightIdx) + "].direction", direction);
	program->setFloat("spotLight[" + std::to_string(lightIdx) + "].cutOff", glm::cos(glm::radians(UIFramework::Instance().cutOff)));
	program->setFloat("spotLight[" + std::to_string(lightIdx) + "].outerCutOff", glm::cos(glm::radians(UIFramework::Instance().outerCutOff)));

	program->setVec3("spotLight[" + std::to_string(lightIdx) + "].ambient", UIFramework::Instance().ambientColor.x, UIFramework::Instance().ambientColor.y, UIFramework::Instance().ambientColor.z);
	program->setVec3("spotLight[" + std::to_string(lightIdx) + "].diffuse", UIFramework::Instance().diffuseColor.x, UIFramework::Instance().diffuseColor.y, UIFramework::Instance().diffuseColor.z);
	program->setVec3("spotLight[" + std::to_string(lightIdx) + "].specular", UIFramework::Instance().specularColor.x, UIFramework::Instance().specularColor.y, UIFramework::Instance().specularColor.z);
	program->setFloat("spotLight[" + std::to_string(lightIdx) + "].constant", UIFramework::Instance().cons);
	program->setFloat("spotLight[" + std::to_string(lightIdx) + "].linear", UIFramework::Instance().lin);
	program->setFloat("spotLight[" + std::to_string(lightIdx) + "].quadratic", UIFramework::Instance().quad);
}