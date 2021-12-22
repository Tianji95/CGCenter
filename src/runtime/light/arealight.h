#pragma once
#ifndef AREA_LIGHT_H
#define AREA_LIGHT_H
#include "light.h"

namespace Zxen {
    class AreaLight : public Light {
    public:
        AreaLight()
        {
        }
        ~AreaLight() = default;
        void Setup(glm::vec3 pos, glm::vec3 amb, glm::vec3 diffu, glm::vec3 spec,
            float cons, float lin, float quad, int idx);

        void Setup(glm::vec3 amb, glm::vec3 diffu, glm::vec3 spec,
            float cons, float lin, float quad);
        virtual void SetUniforms(ProgramPtr program) const override;
    private:
        glm::vec3 position;
        float constant;
        float linear;
        float quadratic;
        int lightIdx = 0;
    };
    using AreaLightPtr = std::shared_ptr<AreaLight>;
}
#endif // !AREA_LIGHT_H
