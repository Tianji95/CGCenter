#pragma once
#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H
#include "light.h"
namespace Zxen {
	class PointLight : public Light {
	public:
		PointLight()
		{

		}
		~PointLight() = default;
		void Setup(glm::vec3 pos, glm::vec3 amb, glm::vec3 diffu, glm::vec3 spec, float cons, float lin, float quad, int idx);

		void Setup(glm::vec3 amb, glm::vec3 diffu, glm::vec3 spec, float cons, float lin, float quad);
		virtual void SetUniforms(ProgramPtr program) const override;
	private:
		glm::vec3 position;
		float constant;
		float linear;
		float quadratic;
		int lightIdx = 0;
	};

	using PointLightPtr = std::shared_ptr<PointLight>;
}
#endif // !POINT_LIGHT_H
