#pragma once
#ifndef RENDER_H
#define RENDER_H

#include <unordered_map>
#include <GL/glew.h>
#include "imgui.h"
#include "camera.h"
#include "scene.h"
#include "renderpass.h"
#include "renderGraph.h"
namespace Zxen {
	class ZXEngine;
	class Render {
	public:
		Render(ZXEngine* engine) : engine(engine)
		{

		}
		~Render() = default;
		void DrawOneFrame();
		void UpdateWindowSize(int display_w, int display_h);
		virtual void Draw() = 0;
		virtual void UpdateRenderData() = 0;
		virtual void InsertGraphNode(RenderGraph* renderGraph) = 0;
		virtual void GenerateResources() = 0;
		const std::unordered_map<int, GLenum> RENDER_MODE_MAP = {
			{0, GL_POINT},
			{1, GL_LINE},
			{2, GL_FILL}
		};

		ImVec4 ambientColor = ImVec4(0.05f, 0.05f, 0.05f, 1.00f);
		ImVec4 diffuseColor = ImVec4(0.8f, 0.8f, 0.8f, 1.0f);
		ImVec4 specularColor = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);
		float cons = 1.0f;
		float lin = 0.001f;
		float quad = 0.00000075f;
		float cutOff = 100.0f;
		float outerCutOff = 115.0f;
		int rendermode = 2;
		int shadowType = 2;
		int shadowLightSize = 2;
		const char* renderModeList[3] = { "Point", "Line", "Fill" };
		const char* shadowMapTypeList[5] = { "No shadow", "shadow Hard", "PCF", "PCSS", "VSM" };
	protected:
		void UpdateCommonResources();
		ZXEngine* engine = nullptr;
		RenderGraph renderGraph;
		unsigned int windowWidth;
		unsigned int windowHeight;
	};
}
#endif // !RENDER_H
