#pragma once
#ifndef SPOT_LIGHT_H
#define SPOT_LIGHT_H
#include "light.h"
#include <memory>
class SpotLight : public Light{
public:
    SpotLight(glm::vec3 pos, glm::vec3 direct, glm::vec3 amb, glm::vec3 diffu, glm::vec3 spec,
        float cO, float outerCO, float cons, float lin, float quad, int idx,
        std::shared_ptr<ShaderBase> prog):position(pos), direction(direct), Light(amb, diffu, spec, prog),
        cutOff(cO), outerCutOff(outerCO), constant(cons), linear(lin), quadratic(quad), lightIdx(idx)
    {

    }
    ~SpotLight() = default;
    virtual void SetUniforms() const override;
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

#endif // !1
