#ifndef _UI_FRAME_WORK_H_
#define _UI_FRAME_WORK_H_

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include <GL/glew.h>
// Include glfw3.h after our OpenGL definitions
#include <GLFW/glfw3.h>
#include "camera.h"
namespace Zxen {
	class UIFramework {
	public:
		UIFramework()
		{
		}
		~UIFramework()
		{
		}
		UIFramework(const UIFramework&) = delete;
		UIFramework& operator=(const UIFramework&) = delete;
		bool Init();
		bool WindowShouldClose();
		bool Draw();
		bool Destroy();
	private:
		CameraPtr camera = nullptr;
		GLFWwindow* window = nullptr;
		bool show_demo_window = true;
		bool show_another_window = false;


	};
}
#endif // !_UI_FRAME_WORK_H_

