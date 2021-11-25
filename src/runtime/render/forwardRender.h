#pragma once
#ifndef FORWARD_RENDER_H
#define FORWARD_RENDER_H

#include "render.h"
#include <memory>
#include "scene.h"

class ForwardRender : public Render {
public:
	ForwardRender() = default;
	~ForwardRender() = default;
	void UpdateRenderData();
	void InsertGraphNode();
private:
	std::unique_ptr<Scene*> scene;
};

#endif // !FORWARD_RENDER_H
