#include "arealight.h"
#include "uiframework.h"
void AreaLight::SetUniforms() const
{
	program->use();
	//program->setVec3("areaLights[" + std::to_string(lightIdx) + "].position", position);
	//program->setVec3("areaLights[" + std::to_string(lightIdx) + "].ambient", ambient);
	//program->setVec3("areaLights[" + std::to_string(lightIdx) + "].diffuse", diffuse);
	//program->setVec3("areaLights[" + std::to_string(lightIdx) + "].specular", specular);
	//program->setFloat("areaLights[" + std::to_string(lightIdx) + "].constant", constant);
	//program->setFloat("areaLights[" + std::to_string(lightIdx) + "].linear", linear);
	//program->setFloat("areaLights[" + std::to_string(lightIdx) + "].quadratic", quadratic);
	program->setVec3("areaLights[" + std::to_string(lightIdx) + "].position", position);
	program->setVec3("areaLights[" + std::to_string(lightIdx) + "].ambient", UIFramework::Instance().ambientColor.x, UIFramework::Instance().ambientColor.y, UIFramework::Instance().ambientColor.z);
	program->setVec3("areaLights[" + std::to_string(lightIdx) + "].diffuse", UIFramework::Instance().diffuseColor.x, UIFramework::Instance().diffuseColor.y, UIFramework::Instance().diffuseColor.z);
	program->setVec3("areaLights[" + std::to_string(lightIdx) + "].specular", UIFramework::Instance().specularColor.x, UIFramework::Instance().specularColor.y, UIFramework::Instance().specularColor.z);
	program->setFloat("areaLights[" + std::to_string(lightIdx) + "].constant", UIFramework::Instance().cons);
	program->setFloat("areaLights[" + std::to_string(lightIdx) + "].linear", UIFramework::Instance().lin);
	program->setFloat("areaLights[" + std::to_string(lightIdx) + "].quadratic", UIFramework::Instance().quad);
}