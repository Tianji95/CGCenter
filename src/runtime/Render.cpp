#include "render.h"
#include <iostream>
#include "zxEngine.h"
namespace Zxen {
    void Render::DrawOneFrame()
    {
        glPolygonMode(GL_FRONT_AND_BACK, RENDER_MODE_MAP.at(rendermode));
        UpdateCommonResources();
        UpdateRenderData();
        Draw();
        // renderGraph.Execute();
    }

    void Render::UpdateWindowSize(int display_w, int display_h)
    {
        windowWidth = display_w;
        windowHeight = display_h;
    }

    void Render::UpdateCommonResources()
    {
        ResourceManager* rsm = engine->GetResourceManager();
        for (auto& pointLight : rsm->GetPointLights()) {
            pointLight->Setup(glm::vec3(ambientColor.x, ambientColor.y, ambientColor.z),
                glm::vec3(diffuseColor.x, diffuseColor.y, diffuseColor.z),
                glm::vec3(specularColor.x, specularColor.y, specularColor.z),
                cons,
                lin,
                quad);
        }
        for (auto& areaLight : rsm->GetAreaLights()) {
            areaLight->Setup(glm::vec3(ambientColor.x, ambientColor.y, ambientColor.z),
                glm::vec3(diffuseColor.x, diffuseColor.y, diffuseColor.z),
                glm::vec3(specularColor.x, specularColor.y, specularColor.z),
                cons,
                lin,
                quad);
        }
        for (auto& spotLight : rsm->GetSpotLights()) {
            spotLight->Setup(glm::vec3(ambientColor.x, ambientColor.y, ambientColor.z),
                glm::vec3(diffuseColor.x, diffuseColor.y, diffuseColor.z),
                glm::vec3(specularColor.x, specularColor.y, specularColor.z),
                cutOff,
                outerCutOff,
                cons,
                lin,
                quad);
        }
    }
}