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
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
};

#endif // !_UI_FRAME_WORK_H_

