#pragma once
#ifndef SPOT_LIGHT_H
#define SPOT_LIGHT_H
#include "light.h"
#include <memory>
namespace Zxen {
    class SpotLight : public Light {
    public:
        SpotLight()
        {

        }
        ~SpotLight() = default;
        virtual void SetUniforms(ProgramPtr program) const override;
        void Setup(glm::vec3 pos, glm::vec3 direct, glm::vec3 amb, glm::vec3 diffu, glm::vec3 spec,
            float cO, float outerCO, float cons, float lin, float quad, int idx);

        void Setup(glm::vec3 amb, glm::vec3 diffu, glm::vec3 spec,
            float cO, float outerCO, float cons, float lin, float quad);
    private:
        glm::vec3 position;
        glm::vec3 direction;
        float cutOff;
        float outerCutOff;
        float constant;
        float linear;
        float quadratic;

        int lightIdx = 0;
    };
    using SpotLightPtr = std::shared_ptr<SpotLight>;
}
#endif // !1
