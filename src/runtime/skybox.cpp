#include "skybox.h"
namespace Zxen {
    void Skybox::Render(CameraPtr camera)
    {
        program->use();
        mesh->DrawArrays(camera, RenderPassType::FORWARD);
    }
}