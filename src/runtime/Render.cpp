#include "render.h"
#include <GL/glew.h>
#include <iostream>

void Render::GenResources()
{
    assimpScene = aiImportFile("", aiProcessPreset_TargetRealtime_MaxQuality);
    scene = new Scene();
    scene->LoadScene();

}

void Render::DrawScene() const
{
    scene->Draw();
}

void Render::DeleteResources()
{
    delete scene;
}

