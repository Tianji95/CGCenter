#pragma once
#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H
#include "light.h"

class PointLight : public Light {
public:
	PointLight(glm::vec3 pos, glm::vec3 amb, glm::vec3 diffu, glm::vec3 spec, float cons, float lin, float quad, int idx, std::shared_ptr<ShaderBase> prog) :
		position(pos), Light(amb, diffu, spec, prog), constant(cons), linear(lin), quadratic(quad), lightIdx(idx)
	{

	}
	~PointLight() = default;
	virtual void SetUniforms() const override;
private:
	glm::vec3 position;
	float constant;
	float linear;
	float quadratic;
	int lightIdx = 0;
};


#endif // !POINT_LIGHT_H
