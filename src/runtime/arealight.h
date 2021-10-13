#pragma once
#ifndef AREA_LIGHT_H
#define AREA_LIGHT_H
#include "light.h"

class AreaLight : public Light {
public:
    AreaLight(glm::vec3 pos, glm::vec3 amb, glm::vec3 diffu, glm::vec3 spec,
        float cons, float lin, float quad, int idx, std::shared_ptr<ShaderBase> prog) :
        position(pos), Light(amb, diffu, spec, prog), constant(cons), linear(lin), quadratic(quad), lightIdx(idx)
    {

    }
    ~AreaLight() = default;
    virtual void SetUniforms() const override;
private:
    glm::vec3 position;
    float constant;
    float linear;
    float quadratic;
    int lightIdx = 0;

};

#endif // !AREA_LIGHT_H
