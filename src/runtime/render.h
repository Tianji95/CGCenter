#pragma once
#ifndef RENDER_H
#define RENDER_H

#include <unordered_map>
#include <GL/glew.h>
#include "camera.h"
#include "scene.h"

class Render {
public:
	Render(Camera* cam) : camera(cam)
	{

	}
	~Render() = default;
	void GenResources();
	void DrawScene() const;
	void DeleteResources();
	void UpdateWindowSize(int display_w, int display_h);
	int rendermode = 2;// default is fill mode
	int shadowType = 2;
	int shadowLightSize = 2;
	const char* renderModeList[3] = { "Point", "Line", "Fill" };
	const char* shadowMapTypeList[5] = { "No shadow", "shadow Hard", "PCF", "PCSS", "VSM" };
private:
	const std::unordered_map<int, GLenum> RENDER_MODE_MAP = {
		{0, GL_POINT},
		{1, GL_LINE},
		{2, GL_FILL}
	};

	Camera* camera = nullptr;
	Scene* scene = nullptr;
};

#endif // !RENDER_H
