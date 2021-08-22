#include "render.h"

#include <iostream>


void Render::GenResources()
{
    scene = new Scene();
    scene->LoadScene();
}

void Render::DrawScene() const
{
    glPolygonMode(GL_FRONT_AND_BACK, RENDER_MODE_MAP.at(rendermode));
    scene->Draw();
}

void Render::DeleteResources()
{
    delete scene;
}
