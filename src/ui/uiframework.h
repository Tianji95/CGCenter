#ifndef _UI_FRAME_WORK_H_
#define _UI_FRAME_WORK_H_

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "../runtime/render.h"
#include "../runtime/camera.h"
#include <stdio.h>
#include <GL/glew.h>
// Include glfw3.h after our OpenGL definitions
#include <GLFW/glfw3.h>
class UIFramework
{
public:
	static UIFramework& Instance()
	{
		static UIFramework ui;
		return ui;
	}
	bool Init();
	bool WindowShouldClose();
	bool Draw();
	bool Destroy();
	Camera* camera = nullptr;
	ImVec4 ambientColor = ImVec4(0.05f, 0.05f, 0.05f, 1.00f);
	ImVec4 diffuseColor = ImVec4(0.8f, 0.8f, 0.8f, 1.0f);
	ImVec4 specularColor = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);
	float cons = 1.0f;
	float lin = 0.0001f;
	float quad = 0.00000075f;
	float cutOff = 100.0f;
	float outerCutOff = 115.0f;
private:
	UIFramework()
	{
	}
	~UIFramework()
	{
	}
	UIFramework(const UIFramework&);
	UIFramework& operator=(const UIFramework&);
	Render* render = nullptr;
	GLFWwindow* window = nullptr;
	bool show_demo_window = true;
	bool show_another_window = false;
};

#endif // !_UI_FRAME_WORK_H_

