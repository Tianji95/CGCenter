#include "cubemappass.h"
#include <iostream>
#include <GL/glew.h>
#include "program.h"
#include "resourceManager.h"
#include "zxEngine.h"
#include "scene.h"
namespace Zxen {
    bool CubemapPass::GenResources()
    {
        ResourceManager* rsm = engine->GetResourceManager();
        skybox = rsm->GetSkyBox();
        ProgramPtr prog = skybox->GetProgram();
        // node->SetProgram(prog);
        return true;
    }

    void CubemapPass::Render()
    {
        glDepthFunc(GL_LEQUAL);
        skybox->Render(engine->GetScene()->GetCamera());
        glBindVertexArray(0);
        glDepthFunc(GL_LESS); // set depth function back to default
    }

    void CubemapPass::UpdateRenderData()
    {

    }

    void CubemapPass::InsertGraphNode(RenderGraph* renderGraph)
    {
        renderGraph->InsertGraphNode(*node);
    }
}