// Dear ImGui: standalone example application for GLFW + OpenGL 3, using programmable pipeline
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs
#include "uiframework.h"

int main(int, char**)
{
    ;
    UIFramework::Instance().Init();
    // Main loop
    while (!UIFramework::Instance().WindowShouldClose())
    {
        UIFramework::Instance().Draw();
    }
    UIFramework::Instance().Destroy();
    return 0;
}
